#include <array>
#include <cstddef>
#include <cstdio>
#include <type_traits>
#include <utility>
#include <version>

#if defined(_ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning(disable: 114)
# pragma warning(disable: 383)
# pragma warning(disable: 473)
# pragma warning(disable: 3280)
#elif defined(_MSC_VER)
# pragma warning(disable: 4459)
#endif

/* ... */
template <typename...> struct argument;
template <typename...> struct arguments;

/* ... */
template <typename...>
struct argument final {
  template <typename...>
  friend struct argument;

  private:
    constexpr argument(...) noexcept {}

  public:
    #if defined(__clang__)
    # pragma clang diagnostic ignored "-Wclass-conversion"
    #elif defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
    # pragma warning(disable: 597)
    #elif defined(__GNUC__)
    # pragma GCC diagnostic ignored "-Wclass-conversion"
    #endif
    #if __cpp_constexpr >= 201304L
      constexpr operator void() const noexcept {}
    #else
      inline operator void() const noexcept {}
    #endif

    template <typename type>
    constexpr operator type() const noexcept {
      static_assert(0u != sizeof(type), "Invalid index into `arguments`");
      return static_cast<type>(const_cast<type&>(*static_cast<typename std::remove_reference<type>::type const volatile*>(NULL)));
    }
};

template <typename base, typename... bases>
struct argument<base, bases...> final {
  template <typename...> friend struct argument;
  template <typename...> friend struct arguments;

  template <typename subbase, typename... subbases>
  constexpr friend std::size_t indexof(argument<subbase, subbases...> const /* volatile */&) noexcept;

  private:
    #if defined(__clang__)
    # pragma clang diagnostic ignored "-Wint-to-pointer-cast"
    #elif defined(__GNUC__)
    # pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
    #endif
    template <typename subbase, typename = subbase>
    union can_cast { static bool const value = false; };

    template <typename subbase>
    union can_cast<subbase, decltype((subbase) std::declval<base>())> { static bool const value = true; };

    // ...
    bool const next;
    union {
      typename std::remove_reference<base>::type *const value;
      argument<bases...>                          const values;
    };

    // ...
    template <std::size_t index, typename std::enable_if<0u == index, unsigned char>::type = 0x00u>
    constexpr argument(arguments<base, bases...> const* const args, std::integral_constant<std::size_t, index> const) noexcept :
      next (false),
      value(&(args -> reference))
    {}

    template <std::size_t index, typename std::enable_if<0u != index, unsigned char>::type = 0x00u>
    constexpr argument(arguments<base, bases...> const* const args, std::integral_constant<std::size_t, index> const) noexcept :
      next  (true),
      values(static_cast<arguments<bases...> const*>(args), std::integral_constant<std::size_t, index - (index != 0u)>{})
    {}

    // ...
    template <typename type, typename std::enable_if<false == can_cast<type>::value, unsigned char>::type = 0x00u>
    constexpr static type cast(base&&) noexcept {
      static_assert(0u != sizeof(base), "Invalid cast from `argument`");
      return static_cast<type>(const_cast<type&>(*static_cast<typename std::remove_reference<type>::type const volatile*>(NULL)));
    }

    template <typename type, typename std::enable_if<false != can_cast<type>::value, unsigned char>::type = 0x00u>
    constexpr static type cast(base&& object) noexcept {
      #if defined(__clang__)
      # pragma clang diagnostic ignored "-Wreturn-local-addr"
      #elif defined(__GNUC__)
      # pragma GCC diagnostic ignored "-Wreturn-local-addr"
      #endif
      return (type) std::forward<base>(object);
    }

  public:
    constexpr operator base&&() const noexcept {
      return this -> next ? this -> values.operator base&&() : static_cast<base&&>(*(this -> value));
    }

    #if defined(__clang__)
    # pragma clang diagnostic ignored "-Wclass-conversion"
    #elif defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
    # pragma warning(disable: 597)
    #elif defined(__GNUC__)
    # pragma GCC diagnostic ignored "-Wclass-conversion"
    #endif
    #if __cpp_constexpr >= 201304L
      constexpr operator void() const noexcept {}
    #else
      inline operator void() const noexcept {}
    #endif

    template <typename type>
    constexpr explicit operator type() const noexcept {
      return this -> next ? this -> values.operator type() : cast<type>(static_cast<base&&>(*(this -> value)));
    }
};

// ...
template <typename...>
struct arguments {
  protected:
    template <std::size_t index>
    union at { typedef at<index> type; };

    union iterator;

  public:
    template <typename type>
    constexpr arguments<type> operator =(type&& object) const& noexcept {
      return {{}, static_cast<type&&>(object)};
    }

    template <typename type>
    constexpr explicit operator type() const noexcept {
      static_assert(0u != sizeof(type), "Invalid cast from `arguments`");
      return static_cast<type>(const_cast<type&>(*static_cast<typename std::remove_reference<type>::type const volatile*>(NULL)));
    }

    #if defined(__clang__)
    # pragma clang diagnostic ignored "-Wclass-conversion"
    #elif defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
    # pragma warning(disable: 597)
    #elif defined(__GNUC__)
    # pragma GCC diagnostic ignored "-Wclass-conversion"
    #endif
    #if __cpp_constexpr >= 201304L
      constexpr operator void() const noexcept {}
    #else
      inline operator void() const noexcept {}
    #endif
};

template <typename base, typename... bases>
struct arguments<base, bases...> : public arguments<bases...> {
  public:
    base &&reference;

    /* ... */
    template <std::size_t index, typename = void>
    union at { typedef typename arguments<bases...>::template at<index - (index != 0u)>::type type; };

    template <typename dummy>
    union at<0u, dummy> { typedef base type; };

    // ...
    template <bool boolean, bool...>
    union boolean_or { static bool const value = boolean; };

    template <bool booleanA, bool booleanB, bool... booleans>
    union boolean_or<booleanA, booleanB, booleans...> { static bool const value = boolean_or<booleanA || booleanB, booleans...>::value; };

    // ...
    struct iterator final {
      arguments const /* volatile */ &args;
      std::size_t                     index;

      /* ... */
      constexpr iterator(arguments const /* volatile */& args, std::size_t const index) noexcept :
        args (args),
        index(index)
      {}

      // ...
      constexpr friend bool operator !=(iterator& current, iterator& end) noexcept {
        return current.index != end.index;
      }

      constexpr argument<base, bases...> operator *() const& noexcept {
        return this -> args.operator [](this -> index);
      }

      inline iterator& operator ++()& noexcept {
        ++(this -> index);
        return *this;
      }
    };

    // ...
    template <typename subbase, typename = void>
    union signedof { typedef subbase type; };

    template <typename dummy>
    union signedof<unsigned char, dummy> { typedef signed char type; };

    template <typename dummy>
    union signedof<unsigned int, dummy> { typedef signed int type; };

    template <typename dummy>
    union signedof<unsigned long, dummy> { typedef signed long type; };

    template <typename dummy>
    union signedof<unsigned long long, dummy> { typedef signed long long type; };

    template <typename dummy>
    union signedof<unsigned short, dummy> { typedef signed short type; };

  public:
    constexpr arguments(arguments const /* volatile */& args) noexcept :
      arguments<bases...>::arguments(static_cast<arguments<bases...> const /* volatile */&>(args)),
      reference(static_cast<base&&>(args.reference))
    {}

    constexpr arguments(arguments<bases...> const /* volatile */& args, base&& object) noexcept :
      arguments<bases...>::arguments(args),
      reference(static_cast<base&&>(object))
    {}

    constexpr arguments(base&& object, bases&&... objects) noexcept :
      arguments<bases...>::arguments(static_cast<bases&&>(objects)...),
      reference(static_cast<base&&>(object))
    {}

    /* ... */
    constexpr iterator begin() const /* volatile */ noexcept {
      return {*this, 0u};
    }

    constexpr iterator end() const /* volatile */ noexcept {
      return {*this, sizeof...(bases) + 1u};
    }

    /* ... */
    template <typename type>
    constexpr friend arguments<type, base, bases...> operator ,(arguments const /* volatile */& args, type&& object) noexcept {
      return {args, static_cast<type&&>(object)};
    }

    template <std::size_t constantIndex = 0u>
    constexpr argument<base, bases...> operator [](std::size_t const index) const /* volatile */ noexcept {
      return constantIndex == sizeof...(bases) + 1u ? argument<base, bases...>{NULL, std::integral_constant<std::size_t, 0u>{}} : (
        sizeof...(bases) - constantIndex == index
        ? argument<base, bases...>{this, std::integral_constant<std::size_t, constantIndex>{}}
        : this -> operator []<constantIndex + (constantIndex != sizeof...(bases) + 1u)>(index)
      );
    }

    constexpr operator base&&() const /* volatile */ noexcept {
      return static_cast<base&&>(this -> reference);
    }

    template <typename type>
    constexpr explicit operator type() const /* volatile */ noexcept {
      return (
        std::is_same<
          typename signedof<typename std::remove_cv<typename std::remove_reference<base>::type>::type>::type,
          typename signedof<typename std::remove_cv<typename std::remove_reference<type>::type>::type>::type
        >::value ?
        argument<base>::template cast<type>(static_cast<base&&>(this -> reference)) :

        boolean_or<false, std::is_same<
          typename signedof<typename std::remove_cv<typename std::remove_reference<bases>::type>::type>::type,
          typename signedof<typename std::remove_cv<typename std::remove_reference<type> ::type>::type>::type
        >::value...>::value ?
        this -> arguments<bases...>::operator type() :

        argument<base>::template can_cast<type>::value ?
        argument<base>::template cast<type>(static_cast<base&&>(this -> reference)) :

        this -> arguments<bases...>::operator type()
      );
    }
};

/* ... */
constexpr arguments<> args;

/* ... */
template <std::size_t index, typename base, typename... bases>
constexpr typename std::enable_if<index == sizeof...(bases), typename arguments<base, bases...>::template at<sizeof...(bases) - index>::type>::type&& get(arguments<base, bases...> const /* volatile */& args) noexcept {
  return static_cast<typename arguments<base, bases...>::template at<sizeof...(bases) - index>::type&&>(args.reference);
}

template <std::size_t index, typename base, typename... bases>
constexpr typename std::enable_if<index != sizeof...(bases), typename arguments<base, bases...>::template at<sizeof...(bases) - index>::type>::type&& get(arguments<base, bases...> const /* volatile */& args) noexcept {
  return get<index>(static_cast<arguments<bases...> const /* volatile */&>(args));
}

// ...
constexpr std::size_t indexof(argument<> const volatile&) noexcept {
  return 0u;
}

template <typename base, typename... bases>
constexpr std::size_t indexof(argument<base, bases...> const /* volatile */& arg) noexcept {
  return arg.next ? indexof(arg.values) + 1u : 0u;
}

/* Main */
#include <csignal>
#include <cstdlib>
int main(int, char*[]) /* noexcept */ {
  std::signal(SIGSEGV, +[](int const) { std::puts("SIGSEGV"); std::exit(EXIT_SUCCESS); });
  std::puts("[get<...>(arguments<char const (&)[2], double, int>)]:");
  std::printf("  " "%i" "\r\n", get<0u>((args = 0, 1.0, "2")));
  std::printf("  " "%f" "\r\n", get<1u>((args = 0, 1.0, "2")));
  std::printf("  " "%s" "\r\n", get<2u>((args = 0, 1.0, "2")));

  std::puts("[arguments<char const (&)[2], double, int>]");
  std::printf("  " "%i" "\r\n",                 (args = 0, 1.0, "2") & 3);
  std::printf("  " "%u" "\r\n", (unsigned char) (args = 0, 1.0, "2"));
  std::printf("  " "%c" "\r\n",                *(args = 0, 1.0, "2"));

  std::puts("[arguments<char const (&)[2], double, int>::operator ...]:");
  typedef      int&&    A;     std::printf("  " "%i" "\r\n", (args = 0, 1.0, "2").operator A());
  typedef      double&& B;     std::printf("  " "%f" "\r\n", (args = 0, 1.0, "2").operator B());
  typedef char const  (&C)[2]; std::printf("  " "%s" "\r\n", (args = 0, 1.0, "2").operator C());

  std::puts("[arguments<char const (&)[2], double, int>::operator ..?]:");
  typedef unsigned    D; std::printf("  " "%u" "\r\n", (args = 0, 1.0, "2").operator D());
  typedef float       E; std::printf("  " "%f" "\r\n", (args = 0, 1.0, "2").operator E());
  typedef char const *F; std::printf("  " "%s" "\r\n", (args = 0, 1.0, "2").operator F());

  std::puts("[arguments<char const (&)[2], double, int>::operator []]:");
  typedef      int&&    G;     std::printf("  " "%i" "\r\n", (args = 0, 1.0, "2")[0].operator G());
  typedef      double&& H;     std::printf("  " "%f" "\r\n", (args = 0, 1.0, "2")[1].operator H());
  typedef char const  (&I)[2]; std::printf("  " "%s" "\r\n", (args = 0, 1.0, "2")[2].operator I());

  // ...
  std::puts("[get<...>(arguments<int, int, int>)]:");
  std::printf("  " "%i" "\r\n", get<0u>((args = 3, 4, 5)));
  std::printf("  " "%i" "\r\n", get<1u>((args = 3, 4, 5)));
  std::printf("  " "%i" "\r\n", get<2u>((args = 3, 4, 5)));

  std::puts("[arguments<int, int, int>]");
  std::printf("  " "%i" "\r\n",               (args = 3, 4, 5) % 6);
  std::printf("  " "%i" "\r\n", (signed char) (args = 3, 4, 5));
  std::printf("  " "%i" "\r\n",              +(args = 3, 4, 5));

  std::puts("[arguments<int, int, int>::operator ...]:");
  typedef int&& J; std::printf("  " "%i" "\r\n", (args = 3, 4, 5).operator J());
  typedef int&& K; std::printf("  " "%i" "\r\n", (args = 3, 4, 5).operator K());
  typedef int&& L; std::printf("  " "%i" "\r\n", (args = 3, 4, 5).operator L());

  std::puts("[arguments<int, int, int>::operator ..?]:");
  typedef long long                                           M; std::printf("  " "%lli" "\r\n" , (args = 3, 4, 5).operator M());
  typedef void                                               *N; std::printf("  " "%p"   "\r\n",  (args = 3, 4, 5).operator N());
  typedef struct O { O(...) {} operator int() { return 5; } } O; std::printf("  " "%i"   "\r\n", +(args = 3, 4, 5).operator O());

  std::puts("[arguments<int, int, int>::operator []]:");
  typedef int&& P; std::printf("  " "%i" "\r\n", (args = 3, 4, 5)[0].operator P());
  typedef int&& Q; std::printf("  " "%i" "\r\n", (args = 3, 4, 5)[1].operator Q());
  typedef int&& R; std::printf("  " "%i" "\r\n", (args = 3, 4, 5)[2].operator R());

  // ...
  std::puts("[for ... : ...]:");
  for (argument<char const (&)[2], double, int, char> &&arg : (args = '6', 7, 8.0, "9"))
  switch (indexof(arg)) {
    case 0u: std::printf("  " "%s" "\r\n", static_cast<char const (&)[2]>(arg)); break;
    case 1u: std::printf("  " "%f" "\r\n", static_cast<double>           (arg)); break;
    case 2u: std::printf("  " "%i" "\r\n", static_cast<int>              (arg)); break;
    case 3u: std::printf("  " "%c" "\r\n", static_cast<char>             (arg)); break;
  }

  for (int &&arg : (args = -6, -7, -8, -9))
  std::printf("  " "%i" "\r\n", arg);

  // ...
  std::puts("[...]:");

  constexpr struct {
    std::array<char const*, 2u> first, second;
    std::array<char const*, 2u> operator [](arguments<int, int> indexes) const {
      return {
        this -> first [indexes[0]],
        this -> second[indexes[1]]
      };
    }
  } pairs = {{"A", "B"}, {"C", "D"}};

  for (char const *const &element : pairs[args = 0, 1])
  std::printf("  " "%s" "\r\n", element);
}
