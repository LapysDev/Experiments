#include <cstddef>
#include <cstdio>
#include <type_traits>
#include <utility>

#if defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
# pragma warning(disable: 177)
# pragma warning(disable: 383)
# pragma warning(disable: 3280)
#endif

/* ... */
namespace {
  template <typename base>
  struct alias final {
    typedef base type;
  };

  // ...
  template <typename... bases>
  struct pack final {
    template <typename base>
    struct has final {
      private:
        template <class>                                  struct valueof                              final { friend struct has; private: static bool const value = false; };
        template <typename subbase, typename... subbases> struct valueof<pack<subbase, subbases...> > final { friend struct has; private: static bool const value = std::is_same<base, subbase>::value || valueof<pack<subbases...> >::value; };

      public:
        static bool const value = valueof<pack<bases...> >::value;
    };
  };

  // ...
  template <std::size_t, typename...>                            struct typeat;
  template <std::size_t index, typename base, typename... bases> struct typeat<index, base, bases...> final { typedef typename typeat<index - 1u, bases...>::type type; };
  template <typename base, typename... bases>                    struct typeat<0u, base, bases...>    final { typedef base type; };

  // ...
  template <typename... bases>
  struct uniqueof {
    private:
      template <class pack, typename...>                                    struct valueof                                        final { friend struct uniqueof; private: typedef pack type; };
      template <typename... packed, typename subbase, typename... subbases> struct valueof<pack<packed...>, subbase, subbases...> final { friend struct uniqueof; private: typedef typename std::conditional<pack<packed...>::template has<subbase>::value, typename valueof<pack<packed...>, subbases...>::type, typename valueof<pack<packed..., subbase>, subbases...>::type>::type type; };

    public:
      typedef typename valueof<pack<>, bases...>::type type;
  };
}

template <typename...>
struct tuple {
  template <typename...>
  friend struct tuple;

  private:
    template <std::size_t>
    struct null final {};

  #ifdef _MSC_VER
    public:
  #endif
    template <class>
    union members;

    template <typename... subbases>
    union members<pack<subbases...> > {
      template <typename...> friend struct tuple;
      private: constexpr inline members() noexcept {}
    };

    template <typename subbase, typename... subbases>
    union members<pack<subbase, subbases...> > {
      template <typename...> friend struct tuple;
      private:
        subbase const volatile     *const member;
        members<pack<subbases...> > const submember;

        /* ... */
        constexpr        members(subbase const volatile& member)               noexcept : member(&member) {}
        constexpr inline members(members<pack<subbases...> > const& submember) noexcept : submember(submember) {}

      public:
        constexpr inline operator typename std::conditional<(sizeof...(subbases) >= 0u), typeat<0u, subbase, subbases...>, alias<null<0u> > >::type::type const volatile&() const volatile noexcept { return *(this -> member); }
        constexpr inline operator typename std::conditional<(sizeof...(subbases) >= 1u), typeat<1u, subbase, subbases...>, alias<null<1u> > >::type::type const volatile&() const volatile noexcept { return this -> submember.operator typename std::conditional<(sizeof...(subbases) >= 1u), typeat<1u, subbase, subbases...>, alias<null<1u> > >::type::type const volatile&(); }
        constexpr inline operator typename std::conditional<(sizeof...(subbases) >= 2u), typeat<2u, subbase, subbases...>, alias<null<2u> > >::type::type const volatile&() const volatile noexcept { return this -> submember.operator typename std::conditional<(sizeof...(subbases) >= 2u), typeat<2u, subbase, subbases...>, alias<null<2u> > >::type::type const volatile&(); }

        template <typename type, typename std::enable_if<std::is_same<subbase, typename std::remove_cv<typename std::remove_reference<type>::type>::type>::value,           unsigned char>::type = 0x0u> constexpr explicit inline operator type() const volatile noexcept { return *const_cast<typename std::remove_reference<type>::type*>(this -> member); }
        template <typename type, typename std::enable_if<pack<subbases...>::template has<typename std::remove_cv<typename std::remove_reference<type>::type>::type>::value, unsigned char>::type = 0x0u> constexpr explicit inline operator type() const volatile noexcept { return this -> submember.operator type(); }
    };

  public:
    constexpr inline members<pack<> > operator [](std::size_t const) const volatile noexcept { return {}; }
};

template <typename base, typename... bases>
struct tuple<base, bases...> : public tuple<bases...> {
  protected:
    typedef tuple<>::members<typename uniqueof<
      typename std::remove_cv<typename std::remove_reference<base>::type>::type,
      typename std::remove_cv<typename std::remove_reference<bases>::type>::type...
    >::type> members;
    base member;

  public:
    constexpr tuple() noexcept :
      tuple<bases...>::tuple(),
      member()
    {}

    template <typename type, typename... types>
    constexpr tuple(type&& argument, types&&... arguments) noexcept :
      tuple<bases...>::tuple(std::forward<types>(arguments)...),
      member(std::forward<type>(argument))
    {}

    // ...
    constexpr members operator [](std::size_t const index) const volatile noexcept {
      return {0u == index ? members{this -> member} : this -> tuple<bases...>::operator [](index - 1u)};
    }
};

/* Main */
int main(int, char*[]) /* noexcept */ {
  // ->> the obvious
  constexpr tuple<int, int, int> object = {1, 2, 3};
  std::printf("[01]: {%i, %i, %i}" "\r\n", +object[0], +object[1], +object[2]);

  // ->> as expected
  std::printf("[02]: %c" "\r\n", tuple<char const*, char const*, unsigned>{"Hello, World!", "Lorem ipsum", 3u}[0][2]);                 // --> "Hello, World!"[2]
  std::printf("[03]: %c" "\r\n", tuple<char const*, char const*, unsigned>{"Hello, World!", "Lorem ipsum", 3u}[1][2]);                 // --> "Lorem ipsum"[2]
  std::printf("[04]: %u" "\r\n", tuple<char const*, char const*, unsigned>{"Hello, World!", "Lorem ipsum", 3u}[2] * 2u);               // --> 3u * 2u

  // ->> even with references
  std::printf("[05]: %u" "\r\n", tuple<char const (&)[14], char const (&&)[12], unsigned>{"Hello, World!", static_cast<char const (&&)[12]>("Lorem ipsum"), 3u}[2] * 3u); // --> 3u * 3u

  // ->> conversion ambiguity between `char const (&)[14]` and `char const (&)[13]`
  std::printf("[06]: %c" "\r\n", tuple<char const (&)[14], char const (&)[12], unsigned>{"Hello, World!", "Lorem ipsum", 3u}[1].operator typename alias<char const (&)[12]>::type()[2]);
  std::printf("[07]: %c" "\r\n", tuple<char const (&)[14], char const (&)[12], unsigned>{"Hello, World!", "Lorem ipsum", 3u}[0].operator typename alias<char const (&)[14]>::type()[2]);

  // ->> no compatible `char const* const&` type within `tuple`
  // std::printf("[]: %c" "\r\n", tuple<char const (&)[14], char const (&)[12], unsigned>{"Hello, World!", "Lorem ipsum", 3u}[0].operator char const* const&()[2]);

  // ->> be careful: correct data, wrong type interpretation
  std::printf("[09]: %c" "\r\n", tuple<char const (&)[14], char const (&)[12], unsigned>{"Hello, World!", "Lorem ipsum", 3u}[1].operator typename alias<char const (&)[14]>::type()[2]);
  std::printf("[10]: %u" "\r\n", tuple<char const (&)[14], char const (&)[12], unsigned>{"Hello, World!", "Lorem ipsum", 3u}[1].operator unsigned());
}
