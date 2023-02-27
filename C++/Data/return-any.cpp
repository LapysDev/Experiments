#include <cstdio>
#include <new>
#include <type_traits>
#include <utility>
#include <version>

/* ... */
struct any final {
  private:
    template <typename base, typename = void>
    struct addressof final {
      template <typename type, typename std::enable_if<std::is_same<typename std::remove_cv<typename std::remove_reference<base>::type>::type, typename std::remove_cv<typename std::remove_reference<type>::type>::type>::value, std::nullptr_t>::type = nullptr>
      constexpr static typename std::remove_reference<base>::type* value(type&& object) noexcept {
        return const_cast<typename std::remove_reference<base>::type*>(&static_cast<type&>(std::forward<type>(object)));
      }
    };

    template <typename base>
    struct addressof<base, decltype(static_cast<void>(std::declval<base&>().operator &()))> final {
      template <typename type, typename std::enable_if<std::is_same<typename std::remove_cv<typename std::remove_reference<base>::type>::type, typename std::remove_cv<typename std::remove_reference<type>::type>::type>::value, std::nullptr_t>::type = nullptr>
      inline static typename std::remove_reference<base>::type* value(type&& object) noexcept {
        return reinterpret_cast<typename std::remove_reference<base>::type*>(&reinterpret_cast<unsigned char const volatile&>(static_cast<type&>(std::forward<type>(object))));
      }
    };

    // ...
    template <typename base>
    struct allocation final {
      template <typename subbase = typename std::remove_cv<base>::type>
      struct nontype final {
        struct {
          struct {
            #ifdef __circle_lang__
              template <typename type>
              constexpr operator type&() noexcept = delete;

              template <typename type>
              constexpr operator type&&() const noexcept = delete;
            #else
              template <typename type>
              constexpr operator type() const noexcept = delete;
            #endif
          } value;
        } object;

        /* ... */
        constexpr void* operator &() const noexcept {
          return NULL;
        }

        template <typename type>
        constexpr void* operator =(type&& value) const noexcept {
          return const_cast<void*>(static_cast<void const volatile*>(addressof<type>::value(std::forward<type>(value))));
        }
      };

      // ...
      template <typename subbase = typename std::remove_cv<base>::type, typename = void>
      struct type final {
        union object {
          #ifdef __circle_lang__
            unsigned char initializer : 1;
          #else
            unsigned char : 0;
          #endif
          subbase value;
        } object;

        /* ... */
        constexpr type() noexcept :
          object{}
        {}

        /* ... */
        constexpr subbase* operator &() const noexcept {
          return addressof<subbase>::value(this -> object.value);
        }

        template <typename type>
        constexpr void* operator =(type&& value) const noexcept(noexcept(subbase(std::declval<type>()))) {
          return ::new (this -> operator &()) subbase(std::forward<type>(value));
        }
      };

      template <typename subbase>
      struct type<subbase, typename std::enable_if<false == std::is_trivially_destructible<subbase>::value, decltype(std::declval<subbase>().~subbase())>::type> final {
        union object {
          #ifdef __circle_lang__
            unsigned char initializer : 1;
          #else
            unsigned char : 0;
          #endif
          subbase value;

          /* ... */
          #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 202002L
            constexpr
          #endif
          inline ~object() noexcept(noexcept(std::declval<subbase>().~subbase())) {
            this -> value.~subbase();
          }
        } object;
        bool initialized /* = false; */;

        /* ... */
        constexpr subbase* operator &() const noexcept {
          return this -> initialized ? addressof<subbase>::value(this -> object.value) : NULL;
        }

        template <typename type>
        /* constexpr */ inline void* operator =(type&& value) noexcept(noexcept(subbase(std::declval<type>())) && noexcept(std::declval<subbase>().~subbase())) {
          return
            (false == this -> initialized ? static_cast<void>(this -> initialized = true) : this -> object.value.~subbase()),
            ::new (this -> operator &()) subbase(std::forward<type>(value));
        }
      };

      /* ... */
      static typename std::conditional<std::is_default_constructible<base>::value, type<>, nontype<> >::type value;
    };

    /* ... */
    void *value;

  public:
    template <typename type, typename std::enable_if<false != std::is_reference<type>::value, std::nullptr_t>::type = nullptr>
    constexpr any(type&& value) noexcept :
      value(const_cast<void*>(static_cast<void const volatile*>(addressof<type>::value(std::forward<type>(value)))))
    {}

    template <typename type, typename std::enable_if<false == std::is_reference<type>::value, std::nullptr_t>::type = nullptr>
    constexpr any(type&& value) noexcept :
      value(allocation<type>::value = std::forward<type>(value))
    {}

    /* ... */
    #ifdef __circle_lang__
      template <typename type>
      constexpr operator type&() noexcept {
        typedef allocation<typename std::remove_cv<type>::type> allocation;
        return this -> value == &allocation::value ? static_cast<type&>(allocation::value.object.value) : *static_cast<typename std::remove_reference<type>::type*>(this -> value);
      }

      template <typename type>
      constexpr operator type&&() const noexcept {
        typedef allocation<typename std::remove_cv<type>::type> allocation;
        return this -> value == &allocation::value ? static_cast<type&&>(allocation::value.object.value) : static_cast<type&&>(*static_cast<typename std::remove_reference<type>::type*>(this -> value));
      }
    #else
      template <typename type>
      constexpr operator type() const noexcept {
        typedef allocation<typename std::remove_cv<typename std::remove_reference<type>::type>::type> allocation;
        #ifdef _MSC_VER
          if (this -> value == &allocation::value) return static_cast<type>(allocation::value.object.value); return
        #else
          return this -> value == &allocation::value ?    static_cast<type>(allocation::value.object.value) :
        #endif
        static_cast<type>(*static_cast<typename std::remove_reference<type>::type*>(this -> value));
      }
    #endif
};
  template <typename base>
  typename std::conditional<
    std::is_default_constructible<base>::value,
    typename any::allocation<base>::template type   <>,
    typename any::allocation<base>::template nontype<>
  >::type any::allocation<base>::value = {};

/* Main */
#include <string>

int main(int, char*[]) /* noexcept */ {
  std::printf("%i"     "\r\n", any{42}          .operator int());
  std::printf("%i"     "\r\n", any{*new int(42)}.operator int());
  std::printf("\"%s\"" "\r\n", any{std::string("Hello, World!")}.operator std::string  ().c_str());
  std::printf("\"%s\"" "\r\n", any{std::string("Lorem ipsum")}  .operator std::string& ().c_str());
  std::printf("\"%s\"" "\r\n", any{std::string("Lapys")}        .operator std::string&&().c_str());
}
