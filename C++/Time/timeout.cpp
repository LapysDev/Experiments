/* Import > ... */
// : [C/ C++ Standard Library]
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

// : [POSIX Standard Library] ->> Compile with `-pthread`
#if defined(__gnu_linux__) || defined(linux) || defined(__linux) || defined(__linux__) || defined(__unix) || defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
# include <cerrno>
# include <climits>
# include <pthread.h>
# include <time.h>
# include <unistd.h>
#endif

// : [Windows API] ->> Link relevant DLLs
#if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
# include <windows.h>
#endif

/* Namespace > Timeout */
struct Timeout final {
  /* Types > ... */
  // : [Identifier] ->> Analog to ECMAScript's `setTimeout(...)` interval IDs
  typedef std::ptrdiff_t timeout_id_t;

  // : [Information] ->> Persists information about (asynchronous) timeouts
  template <typename... types>
  struct timeout_info_t final {
    friend class Timeout;

    private:
      template <std::size_t size, std::size_t...>                   struct maxof                 final { public: static std::size_t const value = size; };
      template <std::size_t a, std::size_t b, std::size_t... sizes> struct maxof<a, b, sizes...> final { public: static std::size_t const value = maxof<(a > b ? a : b), sizes...>::value; };

      typedef std::byte (argument_t)[maxof<1u, sizeof(typename std::remove_reference<types>::type*)...>::value];

      // ... ->>
      argument_t     arguments[0u == sizeof...(types) ? 1u : sizeof...(types)]; // addressable references to arguments passed onto the timeout
      void         (*function)(...) noexcept;                                   // awaiting callback to be invoked when the timeout delay elapses
      unsigned const milliseconds;                                              // amount determining the timeout delay
      bool           set;                                                       // marked for ignoring awaiting callback invocation

      // ... ->>
      template <typename type>
      inline static type& iterative_cast(typename timeout_info_t::argument_t** const iterator) noexcept {
        // unpack the `arguments` onto a `function` call
        return *reinterpret_cast<typename std::remove_reference<type>::type*>((*iterator)++);
      }

      inline static std::byte* iterative_copy(typename timeout_info_t::argument_t** const iterator, std::byte const volatile* const address, std::size_t const size) noexcept {
        // assign the arguments' addresses to each addressable reference
        return std::uninitialized_copy(address, address + size, *((*iterator)++));
      }

    public:
      template <typename type>
      constexpr timeout_info_t(type& function, unsigned const milliseconds, types&... arguments) noexcept : arguments{}, function(reinterpret_cast<void (*)(...) noexcept>(&function)), milliseconds(milliseconds), set(true) {
        typename timeout_info_t::argument_t *iterator = this -> arguments;
        ([](...) { /* Do nothing... */ })(iterator, timeout_info_t::iterative_copy(&iterator, reinterpret_cast<std::byte const volatile*>(std::addressof(arguments)), sizeof(types))...);
      }
  };

  // : [Status] ->> Enforces a callback invocation, with a notification of its timeout's state
  // enum timeout_status_t;

  /* Constants > ... */
  enum : timeout_id_t                   { NO_ID = -1, SYNC_ID = -2 };
  enum timeout_status_t : unsigned char { FAILED_STATUS = false, SUCCEEDED_STATUS = true, CLEARED_STATUS };

  private:
    /* ... */
    inline static timeout_info_t<> *pool   = NULL; // ->> once allocated, always reserved -- until process termination
    inline static std::size_t       volume = 0u;   // ->> memory amount (in bytes) reserved

    /* Functions > ... */
    // : [Clear] ->> Mark specified timeout information to ignore its awaiting callback invocation
    template <typename... types>
    inline static void clear(timeout_info_t<types...>* const information) noexcept {
      information -> function = NULL;
      information -> set      = false;
    }

    // : [Generate] ->> Register a `timeout_info_t` into the `Timeout::pool`
    template <typename type, typename... types>
    static timeout_info_t<types...>* generate(type const& function, unsigned const milliseconds, types&... arguments) noexcept {
      std::size_t threshold = 1u;

      // ... ->> Search for cleared timeout information to re-register (remove from code flow to have each timeout use a unique `timeout_id_t`)
      // for (timeout_info_t<>* iterator = Timeout::pool; iterator != Timeout::pool + Timeout::volume; ++iterator) {
      //   timeout_info_t<> *const information = std::launder(iterator);

      //   if (NULL == information -> function && false == information -> set)
      //   return new (information) timeout_info_t<types...>{function, milliseconds, arguments...};
      // }

      // ... ->> Allocate & register new timeout information
      while (Timeout::volume > threshold)
      threshold = (threshold * 5u) / 2u;

      if (Timeout::volume == 0u || Timeout::volume == threshold) {
        std::size_t const size = (threshold * 5u) / 2u;
        void *const allocation = std::realloc(Timeout::pool, size * sizeof(timeout_info_t<types...>));

        if (NULL == allocation) return NULL;
        Timeout::pool = static_cast<timeout_info_t<>*>(allocation);
      }

      return new (Timeout::volume++ + Timeout::pool) timeout_info_t<types...>{function, milliseconds, arguments...};
    }

    // : [Invoke] ->> Proxy to appropriately `invoke` a timeout's awaiting callback
    template <typename, typename...>
    struct invoke;

    template <typename base, typename... bases, typename... types>
    struct invoke<base (&)(bases...) noexcept, types...> final {
      constexpr invoke(timeout_status_t const status, base (&function)(bases...) noexcept, types&&... arguments) noexcept {
        if (Timeout::SUCCEEDED_STATUS != status) return;
        static_cast<void>(function(std::forward<types>(arguments)...));
      }
    };

    template <typename base, typename... bases, typename... types>
    struct invoke<base (&)(timeout_status_t, bases...) noexcept, types...> final {
      constexpr invoke(timeout_status_t const status, base (&function)(timeout_status_t, bases...) noexcept, types&&... arguments) noexcept {
        static_cast<void>(function(status, std::forward<types>(arguments)...));
      }
    };

    // : [Set] ->> Actual interface for the `Timeout::set(...)` function
    template <class timeout_info_t, typename type, typename... types>
    static timeout_id_t set(bool const asynchronous, timeout_info_t* const information, type& function, unsigned const milliseconds, types&&... arguments) noexcept {
      unsigned const microseconds = milliseconds * 1000u;
      long           nanoseconds  = milliseconds * 1000000u;
      unsigned const seconds      = milliseconds / 1000u;

      // ...
      static_cast<void>(microseconds);
      static_cast<void>(nanoseconds);

      #if defined(__gnu_linux__) || defined(linux) || defined(__linux) || defined(__linux__) || defined(__unix) || defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
        if (asynchronous) {
          pthread_t thread;

          // ...
          if (0x0 != ::pthread_create(&thread, static_cast<pthread_attr_t const*>(NULL), +[](void* const argument) -> void* {
            timeout_info_t *const                information = std::launder(static_cast<timeout_info_t*>(argument));
            typename timeout_info_t::argument_t *iterator    = information -> arguments;

            // ...
            static_cast<void>(iterator);

            Timeout::set<timeout_info_t>(false, information, reinterpret_cast<type&>(*(information -> function)), information -> milliseconds, std::forward<types>(timeout_info_t::template iterative_cast<types>(&iterator))...);
            Timeout::clear(information);
            ::pthread_exit(NULL);

            return NULL;
          }, information)) {
            Timeout::invoke<type&, types...>(NULL == information || information -> set ? Timeout::FAILED_STATUS : Timeout::CLEARED_STATUS, function, std::forward<types>(arguments)...);
            Timeout::clear(information);

            return Timeout::NO_ID;
          }

          return information - reinterpret_cast<timeout_info_t*>(Timeout::pool);
        }

        else {
          #if _BSD_SOURCE || _DEFAULT_SOURCE || (_XOPEN_SOURCE >= 500 && false == (_POSIX_C_SOURCE >= 200809L))
            while (microseconds <= 1000000u) {
              timeout_id_t     identifier;
              timeout_status_t status;

              // ...
              if (0x0 == ::usleep(microseconds)) { identifier = Timeout::SYNC_ID; status = NULL == information || information -> set ? Timeout::SUCCEEDED_STATUS : Timeout::CLEARED_STATUS; }
              else if (EINTR == errno) { identifier = Timeout::NO_ID; status = NULL == information || information -> set ? Timeout::FAILED_STATUS : Timeout::CLEARED_STATUS; }
              else break;

              Timeout::invoke<type&, types...>(status, function, std::forward<types>(arguments)...);
              return identifier;
            }
          #endif
          #if _POSIX_C_SOURCE >= 199309L
            timespec remain; // ->> unsure if `remain` & `requested` could occupy the same memory
            timespec requested;

            // ...
            if ((LONG_MAX < nanoseconds) || (milliseconds > nanoseconds)) requested.tv_sec = seconds;
            else {
              requested.tv_nsec = nanoseconds;
              while (nanoseconds > 999999999L) nanoseconds -= 999999999L;

              requested.tv_sec  = (requested.tv_nsec - nanoseconds) / 1000000000uL;
              requested.tv_nsec = nanoseconds;
            }

            while (true) {
              if (0x0 == ::nanosleep(&requested, &remain)) {
                Timeout::invoke<type&, types...>(NULL == information || information -> set ? Timeout::SUCCEEDED_STATUS : Timeout::CLEARED_STATUS, function, std::forward<types>(arguments)...);
                return Timeout::SYNC_ID;
              }

              if (EINTR != errno) break;
              requested.tv_nsec = remain.tv_nsec;
              requested.tv_sec  = remain.tv_sec;
            }
          #endif
        }
      #endif

      #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
        if (asynchronous) {
          static HANDLE threadHandle = NULL;

          // ...
          if (NULL != threadHandle)
          ::CloseHandle(threadHandle);

          threadHandle = ::CreateThread(static_cast<LPSECURITY_ATTRIBUTES>(NULL), 0u, static_cast<LPTHREAD_START_ROUTINE>(+[](LPVOID const parameter) -> DWORD WINAPI {
            timeout_info_t  *const               information = std::launder(static_cast<timeout_info_t*>(parameter));
            typename timeout_info_t::argument_t *iterator    = information -> arguments;

            // ...
            static_cast<void>(iterator);

            Timeout::set<timeout_info_t>(false, information, reinterpret_cast<type&>(*(information -> function)), information -> milliseconds, std::forward<types>(timeout_info_t::template iterative_cast<types>(&iterator))...);
            Timeout::clear(information);

            return 0x0u;
          }), static_cast<LPVOID>(information), 0x0u, static_cast<LPDWORD>(NULL));

          if (NULL == threadHandle) {
            Timeout::invoke<type&, types...>(NULL == information || information -> set ? Timeout::FAILED_STATUS : Timeout::CLEARED_STATUS, function, std::forward<types>(arguments)...);
            Timeout::clear(information);

            return Timeout::NO_ID;
          }

          return information - reinterpret_cast<timeout_info_t*>(Timeout::pool);
        }

        else if (INFINITE != milliseconds) {
          ::Sleep(milliseconds);

          Timeout::invoke<type&, types...>(NULL == information || information -> set ? Timeout::SUCCEEDED_STATUS : Timeout::CLEARED_STATUS, function, std::forward<types>(arguments)...);
          return Timeout::SYNC_ID;
        }
      #endif

      // ... ->> busy-wait
      if (false == asynchronous) {
        std::time_t const recent = std::time(static_cast<std::time_t*>(NULL));

        // ...
        if (recent == static_cast<std::time_t>(-1))
        return Timeout::NO_ID;

        while (true) {
          std::time_t const current = std::time(static_cast<std::time_t*>(NULL));

          // ...
          if (recent == static_cast<std::time_t>(-1))
          return Timeout::NO_ID;

          if (seconds < current - recent) {
            Timeout::invoke<type&, types...>(NULL == information || information -> set ? Timeout::SUCCEEDED_STATUS : Timeout::CLEARED_STATUS, function, std::forward<types>(arguments)...);
            return Timeout::SYNC_ID;
          }
        }
      }

      return Timeout::NO_ID;
    }

  public:
    /* Function > ... */
    // : [Clear] ->> Mark specified timeout information to ignore its awaiting callback invocation
    inline static void clear(timeout_id_t const id) noexcept {
      if (Timeout::NO_ID == id || Timeout::SYNC_ID == id) return;
      std::launder(Timeout::pool + id) -> set = false;
    }

    // : [Set] ->> Proxy interface for the `Timeout::set(...)` function
    template <typename type, typename... types>
    inline static timeout_id_t set(type (&function)(types...) noexcept, unsigned const milliseconds, types&&... arguments) noexcept {
      return Timeout::set<timeout_info_t<types...> >(false, NULL, function, milliseconds, std::forward<types>(arguments)...);
    }

    template <typename type, typename... types>
    inline static timeout_id_t set(type (&function)(timeout_status_t, types...) noexcept, unsigned const milliseconds, types&&... arguments) noexcept {
      return Timeout::set<timeout_info_t<types...> >(false, NULL, function, milliseconds, std::forward<types>(arguments)...);
    }

    template <typename type, typename... types>
    inline static timeout_id_t set(bool const asynchronous, type (&function)(types...) noexcept, unsigned const milliseconds, types&&... arguments) noexcept {
      timeout_info_t<types...> *information = NULL;

      // ...
      if (asynchronous) {
        information = Timeout::generate(function, milliseconds, arguments...);
        if (NULL == information) { Timeout::invoke<type (&)(types...) noexcept, types...>(Timeout::FAILED_STATUS, function, std::forward<types>(arguments)...); return Timeout::NO_ID; }
      }

      return Timeout::set<timeout_info_t<types...> >(asynchronous, information, function, milliseconds, std::forward<types>(arguments)...);
    }

    template <typename type, typename... types>
    inline static timeout_id_t set(bool const asynchronous, type (&function)(timeout_status_t, types...) noexcept, unsigned const milliseconds, types&&... arguments) noexcept {
      timeout_info_t<types...> *information = NULL;

      // ...
      if (asynchronous) {
        information = Timeout::generate(function, milliseconds, arguments...);
        if (NULL == information) { Timeout::invoke<type (&)(timeout_status_t, types...) noexcept, types...>(Timeout::FAILED_STATUS, function, std::forward<types>(arguments)...); return Timeout::NO_ID; }
      }

      return Timeout::set<timeout_info_t<types...> >(asynchronous, information, function, milliseconds, std::forward<types>(arguments)...);
    }
};

typedef Timeout::timeout_id_t     timeout_id_t;
typedef Timeout::timeout_status_t timeout_status_t;

/* Function > ... */
inline static void clearTimeout(timeout_id_t const id) noexcept {
  return Timeout::clear(id);
}

inline timeout_id_t setInterval(...) noexcept; // UPDATE (Lapys)

template <typename... types>
inline static timeout_id_t setTimeout(types&&... arguments) noexcept {
  return Timeout::set(std::forward<types>(arguments)...);
}

/* Main --- CITE (Lapys) -> https://developer.mozilla.org/en-US/docs/Web/API/setTimeout --- NOTE (Lapys) -> */
int main(int, char*[]) /* noexcept */ {
  // set-up the timeout demonstrations
  setTimeout(true, *+[](std::FILE* const output) noexcept { std::fprintf(output, "This is the first message"  "\r\n"); }, 5000u, stdout);
  setTimeout(true, *+[](std::FILE* const output) noexcept { std::fprintf(output, "This is the second message" "\r\n"); }, 3000u, stdout);
  setTimeout(true, *+[](std::FILE* const output) noexcept { std::fprintf(output, "This is the third message"  "\r\n"); }, 1000u, stdout);
  clearTimeout(setTimeout(true, *+[](std::FILE* const output) noexcept { std::fprintf(output, "This message never shows" "\r\n"); }, 0u, stdout));

  // wait until all asynchronous timeouts are completed
  // by blocking the `main(...)` function synchronously
  setTimeout(*+[]() noexcept {}, 6000u);

  return EXIT_SUCCESS;
}
