#include <cstddef>
#include <type_traits>
#include <utility>
#include <version>

#ifdef __clang__
# pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif

/* Trait */
namespace {
  template <bool boolean, bool...>                          struct boolean_or                                  final { static bool const value = boolean; };
  template <bool booleanA, bool booleanB, bool... booleans> struct boolean_or<booleanA, booleanB, booleans...> final { static bool const value = boolean_or<booleanA || booleanB, booleans...>::value; };

  // ...
  template <typename base, typename = base> struct can_default_initialize                         final { static bool const value = false; };
  template <typename base>                  struct can_default_initialize<base, decltype(base())> final { static bool const value = true;  };

  // ...
  template <std::size_t...>
  struct collection final {};

  // ...
  template <typename base>
  constexpr inline base instanceof() noexcept;

  // ...
  template <typename, bool membered, typename = void> struct has_overloaded_addressof                                                                            final { static bool const value = false; };
  template <typename base>                            struct has_overloaded_addressof<base, false, decltype(static_cast<void>(operator &(instanceof<base>())))>  final { static bool const value = true;  };
  template <typename base>                            struct has_overloaded_addressof<base, true,  decltype(static_cast<void>(instanceof<base>().operator &()))> final { static bool const value = true;  };

  // ...
  template <typename... bases>
  struct pack final {
    template <std::size_t index>
    struct at final {
      private:
        template <std::size_t, typename...>                                     struct valueof;
        template <std::size_t subindex, typename subbase, typename... subbases> struct valueof<subindex, subbase, subbases...> final { friend struct at; private: typedef typename valueof<subindex - 1u, subbases...>::type type; };
        template <typename subbase, typename... subbases>                       struct valueof<0u, subbase, subbases...>       final { friend struct at; private: typedef subbase type; };

      public:
        typedef typename valueof<index, bases...>::type type;
    };
  };

  // ...
  template <typename base> constexpr inline typename std::enable_if<false == (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&  object) noexcept { return &object; }
  template <typename base> constexpr inline typename std::enable_if<false == (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&& object) noexcept { return &static_cast<base&>(object); }

  template <typename base> inline typename std::enable_if<false != (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&  object) noexcept { return const_cast<base*>(reinterpret_cast<base const volatile*>(&reinterpret_cast<unsigned char const volatile&>(object))); }
  template <typename base> inline typename std::enable_if<false != (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&& object) noexcept { return const_cast<base*>(reinterpret_cast<base const volatile*>(&reinterpret_cast<unsigned char const volatile&>(static_cast<base&>(object)))); }

  template <typename base, std::size_t length> constexpr inline base (*addressof(base (&object)[length])  noexcept)[length] { return &object; }
  template <typename base, std::size_t length> constexpr inline base (*addressof(base (&&object)[length]) noexcept)[length] { return &static_cast<base (&)[length]>(object); }
}

/* Declaration */
struct $function;                  // ->> namespace for function pointers from captured shorthands
enum   $operation : unsigned char; // ->> shorthand `$expression` operator

template <std::size_t, bool = true> struct $;           // ->> shorthand
template <typename>                 struct $as;         // ->> conversion shorthand
template <typename type, type>      struct $c;          // ->> shorthand constant
template <typename>                 struct $captured;   // ->> shorthand capture
template <$operation, class...>     struct $expression; // ->> composited shorthands
template <std::size_t>              struct $for;        // ->> iteration function
template <signed long long>         struct $i;          // ->> shorthand signed integer constant
template <unsigned long long>       struct $u;          // ->> shorthand unsigned integer constant
#ifdef __cpp_nontype_template_parameter_auto            //
  template <auto>        struct $f;                     // ->> shorthand floating-point constant
#elif __cplusplus >= 202002L                            //
  template <long double> struct $f;                     // ->> shorthand floating-point constant
#elif defined(_MSVC_LANG)                               //
# if _MSVC_LANG >= 202002L                              //
  template <long double> struct $f;                     // ->> shorthand floating-point constant
# endif                                                 //
#endif                                                  //
#ifdef __cpp_nontype_template_parameter_auto            //
  template <auto>  struct $p;                           // ->> shorthand pointer constant
  template <auto>  struct $s;                           // ->> shorthand user-defined constant
#else                                                   //
  template <void*> struct $p;                           // ->> shorthand pointer constant
#endif                                                  //

/* Class, Enumeration */
// $1 + $2
// $as<Object>($1).do_stuff()
// $for<n>{}($1.do_stuff())
// $for<x>{}($for<y>{}($1.do_stuff() + $2 + $3))
// std::printf&($1, $2)
enum $operation : unsigned char {
  $add,
  $address,
  $assign,
  $assign_add,
  $assign_bitwise_and,
  $assign_bitwise_or,
  $assign_bitwise_xor,
  $assign_divide,
  $assign_left_shift,
  $assign_modulo,
  $assign_multiply,
  $assign_right_shift,
  $assign_subtract,
  $bitwise_and,
  $bitwise_or,
  $bitwise_xor,
  $boolean_and,
  $boolean_or,
  $comma,
  $compare,
  $complement,
  $cast,
  $dereference,
  $divide,
  $equals,
  $equals_greater,
  $equals_lesser,
  $greater,
  $left_shift,
  $lesser,
  $member_access,
  $member_pointer_access,
  $minus,
  $modulo,
  $multiply,
  $negate,
  $nop,
  $plus,
  $post_decrement,
  $post_increment,
  $pre_decrement,
  $pre_increment,
  $right_shift,
  $subscript,
  $subtract,
  $unequals
};

// ...
template <>
struct $expression<$nop> final {
  template <std::size_t, bool>    friend struct $;
  template <$operation, class...> friend struct $expression;

  private:
    /* Trait */
    template <class>                                      struct is_arbitrary                                          final { static bool const value = false; };
    template <bool referrable>                            struct is_arbitrary<$<0u, referrable> >                      final { static bool const value = true;  };
    template <$operation operation, class... expressions> struct is_arbitrary<$expression<operation, expressions...> > final { static bool const value = boolean_or<is_arbitrary<expressions>::value...>::value; };

    template <class>                                      struct is_captured                                          final { static bool const value = false; };
    template <typename type>                              struct is_captured<$captured<type> >                        final { static bool const value = true;  };
    template <$operation operation, class... expressions> struct is_captured<$expression<operation, expressions...> > final { static bool const value = boolean_or<is_captured<expressions>::value...>::value; };

    // ...
    template <class shorthand, typename, bool = is_arbitrary<shorthand>::value, bool = is_captured<shorthand>::value>
    struct cast;

    template <$operation operation, class... expressions, typename type, typename... types, bool arbitrary>
    struct cast<$expression<operation, expressions...>, type (types...) noexcept, arbitrary, false> final {
      friend struct $expression<operation, expressions...>;
      private: constexpr static type value(types... arguments) noexcept { return $expression<$nop>::template reinvoke<operation>($expression<operation, expressions...>().value, std::forward<types>(arguments)...); }
    };

    template <$operation operation, class... expressions, typename type, typename... types>
    struct cast<$expression<operation, expressions...>, type (types..., ...) noexcept, true, false> final {
      friend struct $expression<operation, expressions...>;
      private: constexpr static type value(types... arguments, ...) noexcept { return $expression<$nop>::template reinvoke<operation>($expression<operation, expressions...>().value, std::forward<types>(arguments)...); }
    };

    template <std::size_t index, typename type, typename... types, bool arbitrary>
    struct cast<$<index, false>, type (types...) noexcept, arbitrary, false> final {
      friend struct $expression<$nop, $<index, false> >;
      private: constexpr static type value(types... arguments) noexcept { return static_cast<type>($expression<$nop>::template invoke<index>(std::forward<types>(arguments)...)); }
    };

    template <typename type, typename... types>
    struct cast<$<0u, false>, type (types..., ...) noexcept, true, false> final {
      friend struct $expression<$nop, $<0u, false> >;
      private: constexpr static type value(types... arguments, ...) noexcept { return static_cast<type>($expression<$nop>::template invoke<0u>(std::forward<types>(arguments)...)); }
    };

    #ifdef __cpp_noexcept_function_type
      template <class shorthand, typename type, typename... types, bool arbitrary>
      struct cast<shorthand, type (types...), arbitrary, false> final {
        friend struct shorthand;
        private: constexpr static type (&value)(types...) = cast<shorthand, type (types...) noexcept, false>::value;
      };

      template <class shorthand, typename type, typename... types, bool arbitrary>
      struct cast<shorthand, type (types..., ...), arbitrary, false> final {
        friend struct shorthand;
        private: constexpr static type (&value)(types..., ...) = cast<shorthand, type (types..., ...) noexcept, false>::value;
      };
    #endif

    /* Class */
    template <class...>
    struct $operands {
      template <$operation, class...>
      friend struct $expression;

      private:
        /* Class */
        template <std::size_t>
        struct $index final {};

        // ...
        template <class expression, bool = is_captured<expression>::value>
        struct $operand final {
          template <class...>
          friend struct $operands;

          private:
            typedef expression const& type;
            expression const value;

            /* ... */
            constexpr inline $operand() noexcept : value() {}
            constexpr inline $operand(expression const& value) noexcept : value(value) {}

            constexpr inline operator expression const&() const noexcept { return this -> value; }
        };

        template <class expression>
        struct $operand<expression, false> final {
          template <class...>
          friend struct $operands;

          private:
            typedef expression type;

            /* ... ->> explicit empty-base-optimization */
            constexpr inline $operand() noexcept {}
            constexpr inline $operand(expression const&) noexcept {}

            /* ... */
            constexpr inline operator expression() const noexcept {
              return {};
            }
        };

        /* ... */
        template <std::size_t index>
        constexpr void operator []($index<index> const) const noexcept = delete;
    };

    template <class expression, class... expressions>
    struct $operands<expression, expressions...> : public $operands<expressions...> {
      template <$operation, class...>
      friend struct $expression;

      private:
        $operands<>::$operand<expression> const value;

        /* ... */
        constexpr inline $operands() noexcept :
          $operands<expressions...>::$operands(), value()
        {}

        constexpr inline $operands(expression const& operand, expressions const&... operands) noexcept :
          $operands<expressions...>::$operands(operands...), value(operand)
        {}

      protected:
        template <std::size_t index>
        constexpr inline typename std::enable_if<0u == index, typename $operands<>::$operand<expression>::type>::type operator []($operands<>::$index<index> const) const noexcept {
          return this -> value;
        }

        template <std::size_t index>
        constexpr inline typename std::enable_if<0u != index && index <= sizeof...(expressions), typename $operands<>::$operand<typename pack<expression, expressions...>::template at<index <= sizeof...(expressions) ? index : 0u>::type>::type>::type operator []($operands<>::$index<index> const) const noexcept {
          return this -> $operands<expressions...>::operator []($operands<>::$index<index - 1u>{});
        }
    };

    /* ... */
    constexpr static $operands<>::$index<0u> $0 {};
    constexpr static $operands<>::$index<1u> $1 {};
    constexpr static $operands<>::$index<2u> $2 {};

    /* ... */
    template <std::size_t count, typename type>
    constexpr inline static typename std::enable_if<count == 0u && std::is_array<typename std::remove_reference<type>::type>::value, typename std::remove_extent<type>::type>::type invoke() noexcept {
      return NULL;
    }

    template <std::size_t count, typename type>
    constexpr inline static typename std::enable_if<count == 0u && false != std::is_scalar<type>::value, type>::type invoke() noexcept {
      return 0;
    }

    template <std::size_t count, typename type>
    constexpr inline static typename std::enable_if<count == 0u && false == std::is_scalar<type>::value, type>::type invoke() noexcept {
      return type();
    }

    template <std::size_t count, typename... types>
    constexpr inline static typename std::enable_if<count == 0u, typename std::conditional<(__cplusplus >= 201103L), void, int>::type>::type invoke(types&&...) noexcept {
      return typename std::conditional<(__cplusplus >= 201103L), void, int>::type(0x0);
    }

    template <std::size_t count, typename type, typename... types>
    constexpr inline static typename std::enable_if<count == 0u && can_default_initialize<type>::value, type>::type invoke(type&&, types&&...) noexcept {
      return $expression<$nop>::template invoke<0u, type>();
    }

    template <std::size_t count, typename type, std::size_t capacity, typename... types>
    constexpr inline static typename std::enable_if<count == 0u, type*>::type invoke(type (&)[capacity], types&&...) noexcept {
      return NULL;
    }

    template <std::size_t count, typename type, std::size_t capacity, typename... types>
    constexpr inline static typename std::enable_if<count == 0u, type*>::type invoke(type (&&)[capacity], types&&...) noexcept {
      return NULL;
    }

    template <std::size_t count, typename type, typename... types>
    constexpr inline static typename std::enable_if<count == 1u, type&&>::type invoke(type&& object, types&&...) noexcept {
      return std::forward<type>(object);
    }

    template <std::size_t count, typename type, typename... types>
    constexpr inline static typename std::enable_if<(count > 1u), typename pack<type&&, types&&...>::template at<(count > 1u ? count - 1u : 0u)>::type>::type invoke(type&&, types&&... objects) noexcept {
      return $expression<$nop>::template invoke<count - 1u>(std::forward<types>(objects)...);
    }

    // ...
    template <$operation operation, class $operands, class... types>
    constexpr inline static typename std::enable_if<operation == $add, decltype(std::declval<$operands>()[$0](std::declval<types>()...) + std::declval<$operands>()[$1](std::declval<types>()...))>::type reinvoke($operands const& operands, types&&... arguments) noexcept {
      return operands[$0](std::forward<types>(arguments)...) + operands[$1](std::forward<types>(arguments)...);
    }

    template <$operation operation, class $operands, class... types>
    constexpr inline static typename std::enable_if<operation == $minus, decltype(-std::declval<$operands>()[$0](std::declval<types>()...))>::type reinvoke($operands const& operands, types&&... arguments) noexcept {
      return -operands[$0](std::forward<types>(arguments)...);
    }
};

template <$operation operation, class... subexpressions>
struct $expression final {
  template <class, typename, bool> friend struct $expression<$nop>::cast;
  template <class...>              friend struct $expression<$nop>::$operands;

  private:
    $expression<$nop>::$operands<subexpressions...> const value;

  public:
    constexpr inline $expression() noexcept :
      value()
    {}

    constexpr inline $expression(subexpressions const&... operands) noexcept :
      value(operands...)
    {}

    /* ... */
    template <typename... types>
    constexpr inline decltype($expression<$nop>::template reinvoke<operation>(std::declval<$expression<$nop>::$operands<subexpressions...> >(), std::declval<types>()...)) operator ()(types&&... arguments) const noexcept {
      return $expression<$nop>::template reinvoke<operation>(this -> value, std::forward<types>(arguments)...);
    }

    template <typename type>
    constexpr inline operator type() const noexcept {
      return $expression<$nop>::template cast<$expression, typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value;
    }
};

template <typename base>
struct $expression<$nop, $captured<base> > {
  private:
    base&& value;

  public:
    template <typename type>
    constexpr $expression(type&& object) noexcept :
      value(std::forward<type>(object))
    {}

    /* ... */
    template <typename... types>
    constexpr inline base&& operator ()(types&&...) const noexcept {
      return static_cast<base&&>(this -> value);
    }
};

template <std::size_t index>
struct $expression<$nop, $<index, false> > {
  template <typename... types>
  constexpr inline decltype($expression<$nop>::template invoke<index>(std::declval<types>()...)) operator ()(types&&... arguments) const volatile noexcept {
    return $expression<$nop>::template invoke<index>(std::forward<types>(arguments)...);
  }

  template <typename type>
  constexpr inline operator type() const volatile noexcept {
    return $expression<$nop>::template cast<$<index, false>, typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value;
  }
};

template <>
struct $expression<$nop, $<0u, true> > : public $expression<$nop, $<0u, false> > {
  template <typename... types>
  constexpr inline $expression(types&&...) noexcept {}

  /* ... */
  template <typename type>
  constexpr inline operator type() const volatile noexcept {
    return $expression<$nop>::template invoke<0u, type>();
  }
};

template <std::size_t index>
struct $expression<$nop, $<index, true> > : public $expression<$nop, $<index, false> > {
  template <$operation, class...>
  friend struct $expression;

  private:
    void *const value;

  public:
    constexpr inline $expression() noexcept :
      value(NULL)
    {}

    template <std::size_t subindex>
    constexpr inline $expression($expression<$nop, $<subindex, true> > const unit) noexcept :
      value(static_cast<typename std::enable_if<(index >= subindex && 0u != subindex), void*>::type>(unit.value))
    {}

    template <typename... types>
    constexpr inline $expression(types&&... objects) noexcept :
      value(const_cast<void*>(static_cast<void const volatile*>(addressof($expression<$nop>::template invoke<index>(std::forward<types>(objects)...)))))
    {}

    /* ... */
    template <typename type>
    constexpr inline operator type() const volatile noexcept {
      return static_cast<type>(*static_cast<typename std::remove_reference<type>::type*>(this -> value));
    }
};

// ...
struct $function final {
  public:
  static void *BUFFER;
};

// ...
template <typename base>
struct $captured final : public $expression<$nop, $captured<base> > {
  using $expression<$nop, $captured<base> >::$expression;
};

// ...
template <std::size_t index, bool referrable>
struct $ final : public $expression<$nop, $<index, referrable> > {
  using $expression<$nop, $<index, referrable> >::$expression;
};
  constexpr static $<0u, false> $0 {};
  constexpr static $<1u, false> $1 {};
  constexpr static $<2u, false> $2 {};
  constexpr static $<3u, false> $3 {};
  constexpr static $<3u, false> $4 {};
  constexpr static $<3u, false> $5 {};
  constexpr static $<3u, false> $6 {};
  constexpr static $<3u, false> $7 {};
  constexpr static $<3u, false> $8 {};
  constexpr static $<3u, false> $9 {};

// /* ... */
template <$operation operation, class... subexpressions> constexpr inline $expression<$minus, $expression<operation, subexpressions...> > operator -($expression<operation, subexpressions...> const expression) noexcept { return {expression}; }

template <$operation operationA, $operation operationB, class... subexpressionsA, class... subexpressionsB> constexpr inline $expression<$add, $expression<operationA, subexpressionsA...>, $expression<operationB, subexpressionsB...> > operator +($expression<operationA, subexpressionsA...> const expressionA, $expression<operationB, subexpressionsB...> const expressionB) noexcept { return {expressionA, expressionB}; }
