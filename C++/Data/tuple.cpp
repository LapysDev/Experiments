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
  constexpr inline base instanceof() noexcept;
}

namespace {
  template <typename base>
  struct alias final {
    typedef base type;
  };

  // ...
  template <std::size_t...>
  struct collection final {};

  // ...
  template <typename, bool membered, typename = void> struct has_overloaded_addressof                                                                            final { static bool const value = false; };
  template <typename base>                            struct has_overloaded_addressof<base, false, decltype(static_cast<void>(operator &(instanceof<base>())))>  final { static bool const value = true; };
  template <typename base>                            struct has_overloaded_addressof<base, true,  decltype(static_cast<void>(instanceof<base>().operator &()))> final { static bool const value = true; };

  // ...
  template <typename... bases>
  struct pack final {
    template <std::size_t index>
    struct at final {
      private:
        template <std::size_t, typename...>
        struct valueof;

        template <std::size_t subindex, typename subbase, typename... subbases>
        struct valueof<subindex, subbase, subbases...> final {
          friend struct at;
          private: typedef typename valueof<subindex - 1u, subbases...>::type type;
        };

        template <typename subbase, typename... subbases>
        struct valueof<0u, subbase, subbases...> final {
          friend struct at;
          private: typedef subbase type;
        };

      public:
        typedef typename valueof<index, bases...>::type type;
    };

    // ...
    template <typename type>
    struct has final {
      private:
        template <typename...>
        struct valueof final {
          friend struct has;
          private: static bool const value = false;
        };

        template <typename subbase, typename... subbases>
        struct valueof<subbase, subbases...> final {
          friend struct has;
          private: static bool const value = valueof<subbases...>::value;
        };

        template <typename... subbases>
        struct valueof<type, subbases...> final {
          friend struct has;
          private: static bool const value = true;
        };

      public:
        static bool const value = valueof<bases...>::value;
    };

    // ...
    struct uniqueof final {
      private:
        template <class pack, typename...>
        struct valueof final {
          friend struct uniqueof;
          private: typedef pack type;
        };

        template <typename... packed, typename subbase, typename... subbases>
        struct valueof<pack<packed...>, subbase, subbases...> final {
          friend struct uniqueof;
          private: typedef typename std::conditional<
            pack<packed...>::template has<subbase>::value,
            typename valueof<pack<packed...>,          subbases...>::type,
            typename valueof<pack<packed..., subbase>, subbases...>::type
          >::type type;
        };

      public:
        typedef typename valueof<pack<>, bases...>::type type;
    };

    /* ... */
    static std::size_t const length = sizeof...(bases);
  };
}

namespace {
  template <typename base> constexpr inline typename std::enable_if<false == (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&  object) noexcept { return &object; }
  template <typename base> constexpr inline typename std::enable_if<false == (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&& object) noexcept { return &static_cast<base&>(object); }

  template <typename base> inline typename std::enable_if<false != (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&  object) noexcept { return const_cast<base*>(reinterpret_cast<base const volatile*>(&reinterpret_cast<unsigned char const volatile&>(object))); }
  template <typename base> inline typename std::enable_if<false != (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&& object) noexcept { return const_cast<base*>(reinterpret_cast<base const volatile*>(&reinterpret_cast<unsigned char const volatile&>(static_cast<base&>(object)))); }

  template <typename base, std::size_t capacity> constexpr inline base (*addressof(base (&object)[capacity])  noexcept)[capacity] { return &object; }
  template <typename base, std::size_t capacity> constexpr inline base (*addressof(base (&&object)[capacity]) noexcept)[capacity] { return &static_cast<base (&)[capacity]>(object); }

  #if __cplusplus >= 202002L || defined(__cpp_lib_bounded_array_traits) || (defined(_MSVC_LANG) && _MSVC_LANG <= 202002L)
    template <typename base> constexpr inline base (*addressof(base (&object)[])  noexcept)[] { return &object; }
    template <typename base> constexpr inline base (*addressof(base (&&object)[]) noexcept)[] { return &static_cast<base (&)[]>(object); }
  #endif
}

// ...
template <typename...>
struct tuple final {
  constexpr tuple() noexcept {}

  template <typename type>
  constexpr void operator [](type&&) const volatile noexcept = delete;
};

template <typename base, typename... bases>
struct tuple<base, bases...> final {
  #if defined(_MSC_VER)
    public:
  #else
    private:
  #endif
    template <typename, class> struct members;
    template <std::size_t>     struct nonmember;
    template <typename...>     struct tuplevalue;

    /* ... */
    template <typename subbase, class submembers>
    struct members final {
      template <typename, class> friend struct members;
      template <typename...>     friend struct tuplevalue;

      private:
        template <std::size_t index>
        struct memberstype final {
          private:
            template <bool, template <std::size_t> class, template <std::size_t> class>
            struct valueof;

            template <template <std::size_t> class subbaseA, template <std::size_t> class subbaseB>
            struct valueof<false, subbaseA, subbaseB> final {
              friend struct memberstype;
              private: typedef subbaseB<index> type;
            };

            template <template <std::size_t> class subbaseA, template <std::size_t> class subbaseB>
            struct valueof<true, subbaseA, subbaseB> final {
              friend struct memberstype;
              private: typedef subbaseA<index> type;
            };

          public:
            typedef typename valueof<(pack<base, bases...>::uniqueof::type::length > index), pack<base, bases...>::uniqueof::type::template at, nonmember>::type::type type;
        };

        /* ... */
        std::size_t const index;
        union {
          typename std::remove_reference<subbase>::type *const value;
          submembers const values;
        };

        // ...
        template <typename type>
        constexpr inline typename std::enable_if<false != std::is_convertible<subbase&, type>::value, type>::type cast(std::size_t index) const noexcept {
          #if defined(_MSC_VER)
            if (0u == index) return static_cast<type>(*(this -> value));
            return this -> values.template cast<type>(--index);
          #else
            return 0u == index ? static_cast<type>(*(this -> value)) : this -> values.template cast<type>(--index);
          #endif
        }

        template <typename type>
        constexpr inline typename std::enable_if<false == std::is_convertible<subbase&, type>::value, type>::type cast(std::size_t index) const noexcept {
          return this -> values.template cast<type>(--index);
        }

        /* ... */
        constexpr inline members(std::size_t const index, subbase& value) noexcept : index(index), value(addressof(value)) {}
        constexpr inline members(std::size_t const index, submembers&& members) noexcept : index(index), values(members) {}

      public:
        constexpr inline operator typename memberstype<0u>::type&() const& noexcept { return this -> cast<typename memberstype<0u>::type&>(this -> index); }
        constexpr inline operator typename memberstype<1u>::type&() const& noexcept { return this -> cast<typename memberstype<1u>::type&>(this -> index); }
        constexpr inline operator typename memberstype<2u>::type&() const& noexcept { return this -> cast<typename memberstype<2u>::type&>(this -> index); }
        constexpr inline operator typename memberstype<3u>::type&() const& noexcept { return this -> cast<typename memberstype<3u>::type&>(this -> index); }
        constexpr inline operator typename memberstype<4u>::type&() const& noexcept { return this -> cast<typename memberstype<4u>::type&>(this -> index); }
        constexpr inline operator typename memberstype<5u>::type&() const& noexcept { return this -> cast<typename memberstype<5u>::type&>(this -> index); }
        constexpr inline operator typename memberstype<6u>::type&() const& noexcept { return this -> cast<typename memberstype<6u>::type&>(this -> index); }
        constexpr inline operator typename memberstype<7u>::type&() const& noexcept { return this -> cast<typename memberstype<7u>::type&>(this -> index); }
        constexpr inline operator typename memberstype<8u>::type&() const& noexcept { return this -> cast<typename memberstype<8u>::type&>(this -> index); }
        constexpr inline operator typename memberstype<9u>::type&() const& noexcept { return this -> cast<typename memberstype<9u>::type&>(this -> index); }

        template <typename type>
        constexpr explicit inline operator type() const noexcept {
          return this -> cast<type>(this -> index);
        }
    };

    template <typename subbase>
    struct members<subbase, subbase> final {
      template <typename, class>
      friend struct members;

      private:
        template <typename type>
        constexpr inline type cast(std::size_t const index) const noexcept {
          return (this ->* static_cast<type (members::*)(std::size_t) const noexcept>(NULL))(index);
        }
    };

  private:
    template <std::size_t index>
    struct nonmember final {
      typedef nonmember<index> type;

      /* ... */
      template <typename... types>
      constexpr nonmember(types&&...) noexcept = delete;
    };

    // ...
    template <typename...>
    struct tuplevalue {
      friend struct tuple;

      protected:
        typedef members<void, void> tuplemembers;

        /* ... */
        constexpr inline tuplevalue() noexcept {}

        template <typename type>
        constexpr inline tuplemembers operator [](type&&) const volatile noexcept {
          return {};
        }
    };

    template <typename subbase, typename... subbases>
    struct tuplevalue<subbase, subbases...> : public tuplevalue<subbases...> {
      friend struct tuple;

      private:
        subbase member;

      protected:
        typedef members<subbase, typename tuplevalue<subbases...>::tuplemembers> tuplemembers;

        /* ... */
        constexpr inline tuplevalue() noexcept :
          tuplevalue<subbases...>::tuplevalue(),
          member()
        {}

        template <typename type, typename... types>
        constexpr inline tuplevalue(type&& argument, types&&... arguments) noexcept :
          tuplevalue<subbases...>::tuplevalue(std::forward<types>(arguments)...),
          member(std::forward<type>(argument))
        {}

        // ...
        constexpr inline tuplemembers operator [](std::size_t const index) const volatile noexcept {
          return 0u == index
          ? tuplemembers{index, const_cast<subbase&>(const_cast<subbase const volatile&>(this -> member))}
          : tuplemembers{index, this -> tuplevalue<subbases...>::operator [](index - 1u)};
        }

        constexpr inline subbase& operator [](std::integral_constant<std::size_t, 0u> const) const volatile noexcept {
          return const_cast<subbase&>(this -> member);
        }

        template <std::size_t index>
        constexpr inline decltype(std::declval<tuplevalue<subbases...> const volatile&>().operator [](std::integral_constant<std::size_t, index - 1u>{})) operator [](std::integral_constant<std::size_t, index> const) const volatile noexcept {
          return this -> tuplevalue<subbases...>::operator [](std::integral_constant<std::size_t, index - 1u>{});
        }
    };

    /* ... */
    tuplevalue<base, bases...> value;

  public:
    template <typename... types>
    constexpr tuple(types&&... arguments) noexcept :
      value(std::forward<types>(arguments)...)
    {}

    // ...
    template <typename type>
    constexpr decltype(std::declval<decltype(tuple::value)>().operator [](std::declval<type>())) operator [](type&& index) const volatile noexcept {
      return this -> value.operator [](std::forward<type>(index));
    }
};

template <std::size_t index, typename... types>
constexpr inline decltype(std::declval<tuple<types...> const volatile&>().operator [](std::integral_constant<std::size_t, index>{})) get(tuple<types...> const volatile& tuple) noexcept {
  return tuple.operator [](std::integral_constant<std::size_t, index>{});
}

template <std::size_t index, typename... types>
constexpr inline decltype(std::declval<tuple<types...> const volatile&&>().operator [](std::integral_constant<std::size_t, index>{})) get(tuple<types...> const volatile&& tuple) noexcept {
  return tuple.operator [](std::integral_constant<std::size_t, index>{});
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  // ->> accessing different members (an explicit/ implicit cast is necessary)
  constexpr tuple<int, float, int, int> object = {1, 2.5f, 3 /* default-initialized... */};
  std::printf("[01]: {%i, %f, %i, %i}" "\r\n", object[0].operator int&(), object[1].operator float&(), object[2].operator int&(), object[3].operator int&());

  // ->> accessing members of compatible types (copies, convertibles, ...)
  std::printf("[02]: %i"  "\r\n", tuple<int>{4}[0].operator int());
  std::printf("[03]: %hi" "\r\n", tuple<int>{5}[0].operator short());
  std::printf("[04]: %li" "\r\n", tuple<int>{6}[0].operator long());

  // ->> accessing members implicitly (ambiguous when multiple members can be alternatively accessed the same way)
  std::printf("[05]: %i"   "\r\n", +tuple<int>{7}[0]);
  std::printf("[06]: '%c'" "\r\n", tuple<char const*>{"Hello"}[0][0]);

  // ->> specifying reference members
  std::printf("[07]: '%c'" "\r\n", tuple<char const (&) [6]>{"Hello"}[0][1]);
  std::printf("[08]: '%c'" "\r\n", tuple<char const (&&)[6]>{static_cast<char const (&&)[6]>("Hello")}[0][2]);

  // ->> of course `static_cast`/ C-style casting works
  std::printf("[09]: '%c'" "\r\n", static_cast<char const*>(tuple<char const*>{"Hello"}[0])[3]);
  std::printf("[08]: '%c'" "\r\n", ((char const*) tuple<char const*>{static_cast<char const (&&)[6]>("Hello")}[0])[4]);

  // ->> template-aided member access
  std::printf("[10]: %c" "\r\n", tuple<char, unsigned>{'8', 9u}[std::integral_constant<std::size_t, 0u>{}]);
  std::printf("[11]: %u" "\r\n", tuple<char, unsigned>{'8', 9u}[std::integral_constant<std::size_t, 1u>{}]);

  std::printf("[12]: %hu" "\r\n", get<0u>(tuple<char, unsigned long>{'\n', 11uL}));
  std::printf("[13]: %lu" "\r\n", get<1u>(tuple<char, unsigned long>{'\n', 11uL}));

  // ->> yes, it's compile-time
  enum { value = tuple<int>{}[0] };
  std::printf("[14]: %i" "\r\n", static_cast<int>(value));

  // // ->> invalid member access causes a null (member function) pointer dereference
  // std::printf("[]: %p" "\r\n", +tuple<int>{}[0].operator void*()); // `int` and `void*` are not compatible
  // std::printf("[]: %i" "\r\n", +tuple<int>{}[1]);                  // out-of-bounds access
}
