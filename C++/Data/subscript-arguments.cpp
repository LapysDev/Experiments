#include <array>
#include <cstddef>
#include <cstdio>
#include <type_traits>
#include <version>

#if defined(__clang__)
# pragma clang diagnostic ignored "-Wclass-conversion"
# pragma clang diagnostic ignored "-Wint-to-pointer-cast"
# pragma clang diagnostic ignored "-Wnull-dereference"
# pragma clang diagnostic ignored "-Wreturn-stack-address"
# pragma clang diagnostic ignored "-Wunused-const-variable"
#elif defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning(disable: 111)
# pragma warning(disable: 114)
# pragma warning(disable: 327)
# pragma warning(disable: 383)
# pragma warning(disable: 473)
# pragma warning(disable: 593)
# pragma warning(disable: 597)
# pragma warning(disable: 810)
# pragma warning(disable: 1418)
# pragma warning(disable: 1419)
# pragma warning(disable: 2415)
# pragma warning(disable: 3280)
#elif defined(__GNUC__)
# pragma GCC diagnostic ignored "-Waddress"
# pragma GCC diagnostic ignored "-Wclass-conversion"
# pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
# pragma GCC diagnostic ignored "-Wnonnull-compare"
# pragma GCC diagnostic ignored "-Wreturn-local-addr"
#elif defined(_MSC_VER)
# pragma warning(disable: 4172)
# pragma warning(disable: 4302)
# pragma warning(disable: 4311)
# pragma warning(disable: 4312)
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

  public : constexpr argument() noexcept {}
  private: constexpr argument(void const volatile* const, std::integral_constant<std::size_t, 0u> const) noexcept {}

  public:
    #if __cpp_constexpr >= 201304L
      constexpr operator void() const volatile noexcept {}
    #else
      inline operator void() const volatile noexcept {}
    #endif

    template <typename type>
    constexpr operator type() const volatile noexcept {
      static_assert(0u != sizeof(type), "Invalid index into `arguments`");
      return static_cast<type>(const_cast<type&>(*static_cast<typename std::remove_reference<type>::type const volatile*>(NULL)));
    }
};

template <typename base, typename... bases>
struct argument<base, bases...> final {
  template <typename...> friend struct argument;
  template <typename...> friend struct arguments;

  template <typename subbase, typename... subbases>
  constexpr friend std::size_t lastindexof(argument<subbase, subbases...> const /* volatile */&) noexcept;

  private:
    template <typename subbase, typename = subbase>
    union can_cast { static bool const value = false; };

    template <typename subbase>
    union can_cast<subbase, decltype((subbase) std::declval<base>())> { static bool const value = true; };

    /* ... */
    bool const next;
    union {
      typename std::remove_reference<base>::type *const value;
      argument<bases...>                          const values;
    };

    /* ... */
    template <std::size_t index, typename std::enable_if<0u == index, unsigned char>::type = 0x00u>
    constexpr argument(arguments<base, bases...> const /* volatile */* const args, std::integral_constant<std::size_t, index> const) noexcept :
      next (false),
      value(NULL == args ? nullptr : &(args -> reference))
    {}

    template <std::size_t index, typename std::enable_if<0u != index, unsigned char>::type = 0x00u>
    constexpr argument(arguments<base, bases...> const /* volatile */* const args, std::integral_constant<std::size_t, index> const) noexcept :
      next  (true),
      values(static_cast<arguments<bases...> const /* volatile */*>(args), std::integral_constant<std::size_t, index - (index != 0u)>{})
    {}

    /* ... */
    template <typename type, typename std::enable_if<false == can_cast<type>::value, unsigned char>::type = 0x00u>
    constexpr static type cast(base&&) noexcept {
      static_assert(0u != sizeof(base), "Invalid cast from `argument`");
      return static_cast<type>(const_cast<type&>(*static_cast<typename std::remove_reference<type>::type const volatile*>(NULL)));
    }

    template <typename type, typename std::enable_if<false != can_cast<type>::value, unsigned char>::type = 0x00u>
    constexpr static type cast(base&& object) noexcept {
      return (type) static_cast<base&&>(object);
    }

  public:
    constexpr operator base&&() const noexcept {
      #if __cpp_constexpr >= 201304L
        if (this -> next) return this -> values.operator base&&();
        return static_cast<base&&>(*(this -> value));
      #else
        return this -> next ? this -> values.operator base&&() : static_cast<base&&>(*(this -> value));
      #endif
    }

    #if __cpp_constexpr >= 201304L
      constexpr operator void() const noexcept {}
    #else
      inline operator void() const noexcept {}
    #endif

    template <typename type>
    constexpr operator type() const noexcept {
      #if __cpp_constexpr >= 201304L
        if (this -> next) return this -> values.operator type();
        return cast<type>(static_cast<base&&>(*(this -> value)));
      #else
        return this -> next ? this -> values.operator type() : cast<type>(static_cast<base&&>(*(this -> value)));
      #endif
    }
};

// ...
template <typename...>
struct arguments {
  protected:
    template <std::size_t index>
    union at { typedef at<index> type; };

    // ...
    union iterator {
      unsigned char dummy;

      /* ... */
      constexpr friend bool operator !=(iterator const, iterator const) noexcept {
        return false;
      }

      constexpr argument<> operator *() const& noexcept {
        return {};
      }

      constexpr iterator const& operator ++() const& noexcept {
        return *this;
      }
    };

  public:
    constexpr iterator begin() const volatile noexcept {
      return {};
    }

    constexpr iterator end() const volatile noexcept {
      return {};
    }

    /* ... */
    template <typename type>
    constexpr arguments<type> operator =(type&& object) const& noexcept {
      return {{}, static_cast<type&&>(object)};
    }

    constexpr argument<> operator [](std::size_t const) const volatile noexcept {
      return {};
    }

    template <typename type>
    constexpr explicit operator type() const volatile noexcept {
      static_assert(0u != sizeof(type), "Invalid cast from `arguments`");
      return static_cast<type>(const_cast<type&>(*static_cast<typename std::remove_reference<type>::type const volatile*>(NULL)));
    }

    #if __cpp_constexpr >= 201304L
      constexpr operator void() const volatile noexcept {}
    #else
      inline operator void() const volatile noexcept {}
    #endif
};

template <typename base, typename... bases>
struct arguments<base, bases...> : public arguments<bases...> {
  protected:
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
        return this -> args[this -> index];
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

    /* ... */
    template <typename...>
    friend struct argument;

    template <std::size_t index, typename subbase, typename... subbases> constexpr friend typename std::enable_if<index == sizeof...(subbases), typename arguments<subbase, subbases...>::template at<sizeof...(subbases) - index>::type>::type&& get(arguments<subbase, subbases...> const /* volatile */&) noexcept;
    template <std::size_t index, typename subbase, typename... subbases> constexpr friend typename std::enable_if<index != sizeof...(subbases), typename arguments<subbase, subbases...>::template at<sizeof...(subbases) - index>::type>::type&& get(arguments<subbase, subbases...> const /* volatile */&) noexcept;

    /* ... */
    base &&reference;

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
      return (
        constantIndex == sizeof...(bases) + 1u ?
        argument<base, bases...>{NULL, std::integral_constant<std::size_t, 0u>{}} :

        sizeof...(bases) - constantIndex == index ?
        argument<base, bases...>{this, std::integral_constant<std::size_t, constantIndex>{}} :

        this -> operator []<constantIndex + (constantIndex != sizeof...(bases) + 1u)>(index)
      );
    }

    constexpr operator base&&() const /* volatile */ noexcept {
      return static_cast<base&&>(this -> reference);
    }

    template <typename type>
    explicit operator type() const /* volatile */ noexcept {
      #if __cpp_constexpr >= 201304L
        if (std::is_same<
          typename signedof<typename std::remove_cv<typename std::remove_reference<base>::type>::type>::type,
          typename signedof<typename std::remove_cv<typename std::remove_reference<type>::type>::type>::type
        >::value) return argument<base>::template cast<type>(static_cast<base&&>(this -> reference));

        if (boolean_or<false, std::is_same<
          typename signedof<typename std::remove_cv<typename std::remove_reference<bases>::type>::type>::type,
          typename signedof<typename std::remove_cv<typename std::remove_reference<type> ::type>::type>::type
        >::value...>::value) return static_cast<type>(*static_cast<arguments<bases...> const*>(this));

        if (argument<base>::template can_cast<type>::value)
        return argument<base>::template cast<type>(static_cast<base&&>(this -> reference));

        return static_cast<type>(*static_cast<arguments<bases...> const*>(this));
      #else
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
          static_cast<type>(*static_cast<arguments<bases...> const*>(this)) :

          argument<base>::template can_cast<type>::value ?
          argument<base>::template cast<type>(static_cast<base&&>(this -> reference)) :

          static_cast<type>(*static_cast<arguments<bases...> const*>(this))
        );
      #endif
    }
};

/* ... */
constexpr arguments<> args;

/* ... */
constexpr std::size_t lastindexof(argument<> const volatile&) noexcept {
  return 0u;
}

template <typename base, typename... bases>
constexpr std::size_t lastindexof(argument<base, bases...> const /* volatile */& arg) noexcept {
  return arg.next ? lastindexof(arg.values) + 1u : 0u;
}

// ...
template <typename... bases>
constexpr std::size_t indexof(argument<bases...> const /* volatile */& arg) noexcept {
  return sizeof...(bases) - lastindexof(arg) - 1u;
}

// ...
template <std::size_t index, typename base, typename... bases>
constexpr typename std::enable_if<index == sizeof...(bases), typename arguments<base, bases...>::template at<sizeof...(bases) - index>::type>::type&& get(arguments<base, bases...> const /* volatile */& args) noexcept {
  return static_cast<typename arguments<base, bases...>::template at<sizeof...(bases) - index>::type&&>(args.reference);
}

template <std::size_t index, typename base, typename... bases>
constexpr typename std::enable_if<index != sizeof...(bases), typename arguments<base, bases...>::template at<sizeof...(bases) - index>::type>::type&& get(arguments<base, bases...> const /* volatile */& args) noexcept {
  return get<index>(static_cast<arguments<bases...> const /* volatile */&>(args));
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  std::puts("[get<...>(arguments<char const (&)[2], double, int>)]:");
  std::printf("  " "%i" "\r\n", get<0u>((args = 0, 1.0f, "2")));
  std::printf("  " "%f" "\r\n", get<1u>((args = 0, 1.0f, "2")));
  std::printf("  " "%s" "\r\n", get<2u>((args = 0, 1.0f, "2")));

  std::puts("[arguments<char const (&)[2], double, int>]");
  #if defined(__circle_lang__)
    std::printf("  " "%i" "\r\n", (args = 0, 1.0f, "2") & 3);
    std::printf("  " "%f" "\r\n", ([](float      value)   { return value; })((args = 0, 1.0f, "2")));
    std::printf("  " "%s" "\r\n", ([](char const value[]) { return value; })((args = 0, 1.0f, "2")));
  #elif defined(__clang__)
    std::printf("  " "%i" "\r\n", ([](int   value) { return value; })((args = 0, 1.0f, "2")));
    std::printf("  " "%f" "\r\n", ([](float value) { return value; })((args = 0, 1.0f, "2")));
    std::printf("  " "%c" "\r\n", *(args = 0, 1.0f, "2"));
  #elif defined(__GNUC__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(_MSC_VER)
    std::printf("  " "%i" "\r\n", (args = 0, 1.0f, "2") & 3);
    std::printf("  " "%f" "\r\n", ([](float value) { return value; })((args = 0, 1.0f, "2")));
    std::printf("  " "%c" "\r\n", *(args = 0, 1.0f, "2"));
  #endif

  std::puts("[arguments<char const (&)[2], double, int>::operator ...]:");
  typedef int        &&A;     std::printf("  " "%i" "\r\n", (args = 0, 1.0f, "2").operator A());
  typedef float      &&B;     std::printf("  " "%f" "\r\n", (args = 0, 1.0f, "2").operator B());
  typedef char const (&C)[2]; std::printf("  " "%s" "\r\n", (args = 0, 1.0f, "2").operator C());

  std::puts("[arguments<char const (&)[2], double, int>::operator ..?]:");
  typedef unsigned    D; std::printf("  " "%u" "\r\n", (args = 0, 1.0f, "2").operator D());
  typedef double      E; std::printf("  " "%f" "\r\n", (args = 0, 1.0f, "2").operator E());
  typedef char const *F; std::printf("  " "%s" "\r\n", (args = 0, 1.0f, "2").operator F());

  std::puts("[arguments<char const (&)[2], double, int>::operator []]:");
  #ifdef __circle_lang__
    typedef int         G; std::printf("  " "%i" "\r\n", (args = 0, 1.0f, "2")[0].operator G());
    typedef float       H; std::printf("  " "%f" "\r\n", (args = 0, 1.0f, "2")[1].operator H());
    typedef char const *I; std::printf("  " "%s" "\r\n", (args = 0, 1.0f, "2")[2].operator I());
  #else
    typedef int        &&G;     std::printf("  " "%i" "\r\n", (args = 0, 1.0f, "2")[0].operator G());
    typedef float      &&H;     std::printf("  " "%f" "\r\n", (args = 0, 1.0f, "2")[1].operator H());
    typedef char const (&I)[2]; std::printf("  " "%s" "\r\n", (args = 0, 1.0f, "2")[2].operator I());
  #endif

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
  typedef long long                             M; std::printf("  " "%lli" "\r\n" , (args = 3, 4, 5).operator M());
  typedef void                                 *N; std::printf("  " "%p"   "\r\n",  (args = 3, 4, 5).operator N());
  typedef struct O { int value = 5; O(...) {} } O; std::printf("  " "%i"   "\r\n",  (args = 3, 4, 5).operator O().value);

  std::puts("[arguments<int, int, int>::operator []]:");
  #ifdef __circle_lang__
    typedef int P; std::printf("  " "%i" "\r\n", (args = 3, 4, 5)[0].operator P());
    typedef int Q; std::printf("  " "%i" "\r\n", (args = 3, 4, 5)[1].operator Q());
    typedef int R; std::printf("  " "%i" "\r\n", (args = 3, 4, 5)[2].operator R());
  #else
    typedef int&& P; std::printf("  " "%i" "\r\n", (args = 3, 4, 5)[0].operator P());
    typedef int&& Q; std::printf("  " "%i" "\r\n", (args = 3, 4, 5)[1].operator Q());
    typedef int&& R; std::printf("  " "%i" "\r\n", (args = 3, 4, 5)[2].operator R());
  #endif

  // ...
  std::puts("[for ... : arguments<>]");
  for (argument<> arg : (args)) static_cast<void>(arg);

  std::puts("[for ... : arguments<char const (&)[2], double, int, char>]:");
  for (argument<char const (&)[2], float, int, char> &&arg : (args = '6', 7, 8.0f, "9"))
  switch (indexof(arg)) {
    case 0u: typedef char        S; std::printf("  " "%c" "\r\n", arg.operator S()); break;
    case 1u: typedef int         T; std::printf("  " "%i" "\r\n", arg.operator T()); break;
    case 2u: typedef float       U; std::printf("  " "%f" "\r\n", arg.operator U()); break;
    case 3u: typedef char const *V; std::printf("  " "%s" "\r\n", arg.operator V()); break;
  }

  std::puts("[for ... : arguments<int, int, int, int>]:");
  for (argument<int, int, int, int> &&arg : (args = 6, 7, 8, 9)) std::printf("  " "%i" "\r\n", arg.operator int());

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
