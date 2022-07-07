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
// $as<Object>($1).do_stuff()
// $for<n>{}($1.do_stuff())
// $for<x>{}($for<y>{}($1.do_stuff() + $2 + $3))
enum   $operation : unsigned char; // ->> shorthand `$expression` operator
struct $shorthand;                 // ->> namespace for runtime non-self-contained shorthand information

template <std::size_t, bool = true> struct $;                                                                                                                                                              // ->> shorthand
template <typename>                 struct $as;                                                                                                                                                            // ->> conversion shorthand
template <typename base, base>      struct $c;                                                                                                                                                             // ->> shorthand constant
template <typename base, typename std::enable_if<false == std::is_base_of<$shorthand, typename std::remove_cv<typename std::remove_reference<base>::type>::type>::value, int>::type = 0> struct $captured; // ->> shorthand capture
template <$operation, class...>     struct $expression;                                                                                                                                                    // ->> composited shorthands
template <std::size_t>              struct $for;                                                                                                                                                           // ->> iteration function
  #ifdef __cpp_nontype_template_parameter_auto //
    template <auto>        struct $e;          // ->> shorthand enumeration constant
  #else                                        //
    template <std::size_t> struct $e;          // ->> shorthand enumeration constant
  #endif                                       //
  #                                            //
  #ifdef __cpp_nontype_template_parameter_auto //
    template <auto>        struct $f;          // ->> shorthand floating-point constant
  #elif __cplusplus >= 202002L                 //
    template <long double> struct $f;          // ->> shorthand floating-point constant
  #elif defined(_MSVC_LANG)                    //
  # if _MSVC_LANG >= 202002L                   //
    template <long double> struct $f;          // ->> shorthand floating-point constant
  # endif                                      //
  #endif                                       //
  #                                            //
  #ifdef __cpp_nontype_template_parameter_auto //
    template <auto>               struct $i;   // ->> shorthand signed integer constant
    template <auto>               struct $u;   // ->> shorthand unsigned integer constant
  #else                                        //
    template <signed long long>   struct $i;   // ->> shorthand signed integer constant
    template <unsigned long long> struct $u;   // ->> shorthand unsigned integer constant
  #endif                                       //
  #                                            //
  #ifdef __cpp_nontype_template_parameter_auto //
    template <auto>  struct $p;                // ->> shorthand pointer constant
    template <auto>  struct $s;                // ->> shorthand user-defined constant
  #else                                        //
    template <void*> struct $p;                // ->> shorthand pointer constant
  #endif                                       //

/* Class, Enumeration */
struct $shorthand {
  public:
  static void *BUFFER;
};

// ...
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
  $call,
  $cast,
  $comma,
  $compare,
  $complement,
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
struct $expression<$nop> : public $shorthand {
  template <$operation, class...>
  friend struct $expression;

  private:
    /* Trait */
    template <class shorthand> struct to_nop                                final { friend struct $expression; private: typedef $expression<$nop, shorthand> type; };
    template <class shorthand> struct to_nop<$expression<$nop, shorthand> > final { friend struct $expression; private: typedef $expression<$nop, shorthand> type; };

    // ...
    template <class expression>
    struct to_arguments final {
      friend struct $expression;
      private: typedef $expression<$comma, expression> type;
    };

    template <$operation operation, $operation suboperation, class... subexpressions, class expression, class... expressions>
    struct to_arguments<$expression<operation, $expression<suboperation, subexpressions...>, $expression<$comma, expression, expressions...> > > final {
      friend struct $expression;
      private: typedef typename to_arguments<$expression<$comma, $expression<operation, typename to_nop<subexpressions>::type..., expression>, $expression<suboperation, expressions...> > >::type type;
    };

    template <class... expressions>
    struct to_arguments<$expression<$comma, expressions...> > final {
      friend struct $expression;
      private:
        template <class, class...>
        struct valueof;

        template <class... arguments>
        struct valueof<pack<arguments...> > final {
          friend struct to_arguments;
          private: typedef $expression<$comma, arguments...> type;
        };

        template <class... arguments, class... subarguments, class... subexpressions>
        struct valueof<pack<arguments...>, $expression<$comma, subarguments...>, subexpressions...> final {
          friend struct to_arguments;
          private: typedef typename valueof<pack<arguments..., subarguments...>, subexpressions...>::type type;
        };

        template <class... arguments, class subexpression, class... subexpressions>
        struct valueof<pack<arguments...>, subexpression, subexpressions...> final {
          friend struct to_arguments;
          private: typedef typename valueof<pack<arguments..., subexpression>, subexpressions...>::type type;
        };

        /* ... */
        typedef typename valueof<pack<>, typename to_arguments<expressions>::type...>::type type;
    };

    // ...
    template <class>                                      struct is_captured                                          final { static bool const value = false; };
    template <typename base>                              struct is_captured<$captured<base> >                        final { static bool const value = true;  };
    template <$operation operation, class... expressions> struct is_captured<$expression<operation, expressions...> > final { static bool const value = boolean_or<is_captured<expressions>::value...>::value; };

    // ...
    template <class>                                      struct is_arbitrary                                          final { static bool const value = false; };
    template <bool referrable>                            struct is_arbitrary<$<0u, referrable> >                      final { static bool const value = true;  };
    template <typename base, base constant>               struct is_arbitrary<$c<base, constant> >                     final { static bool const value = true;  };
    template <typename base>                              struct is_arbitrary<$captured<base> >                        final { static bool const value = true;  };
    template <$operation operation, class... expressions> struct is_arbitrary<$expression<operation, expressions...> > final { static bool const value = boolean_or<is_arbitrary<expressions>::value...>::value; };

    // ...
    template <class shorthand, typename, bool = is_arbitrary<shorthand>::value, bool = is_captured<shorthand>::value>
    struct cast;

    template <$operation operation, class... expressions, typename type, typename... types, bool arbitrary>
    struct cast<$expression<operation, expressions...>, type (types...) noexcept, arbitrary, false> final {
      constexpr static type value(types... arguments) noexcept { return $expression<$nop>::template invoke<$expression<operation, expressions...> >::value($expression<operation, expressions...>{}.value, std::forward<types>(arguments)...); }
    };

    template <$operation operation, class... expressions, typename type, typename... types, bool arbitrary>
    struct cast<$expression<operation, expressions...>, type (types...) noexcept, arbitrary, true> final {
      constexpr static type value(types... arguments) noexcept;
    };

    template <$operation operation, class... expressions, typename type, typename... types>
    struct cast<$expression<operation, expressions...>, type (types..., ...) noexcept, true, false> final {
      constexpr static type value(types... arguments, ...) noexcept { return $expression<$nop>::template invoke<$expression<operation, expressions...> >::value($expression<operation, expressions...>{}.value, std::forward<types>(arguments)...); }
    };

    template <typename base, base constant, typename type, typename... types>
    struct cast<$c<base, constant>, type (types...) noexcept, true, false> final {
      constexpr static type value(types...) noexcept { return static_cast<type>(constant); }
    };

    template <std::size_t index, typename type, typename... types, bool arbitrary>
    struct cast<$<index, false>, type (types...) noexcept, arbitrary, false> final {
      constexpr static type value(types... arguments) noexcept { return static_cast<type>($expression<$nop>::template invoke<$<index, false> >::value(std::forward<types>(arguments)...)); }
    };

    template <typename type, typename... types>
    struct cast<$<0u, false>, type (types..., ...) noexcept, true, false> final {
      constexpr static type value(types... arguments, ...) noexcept { return static_cast<type>($expression<$nop>::template invoke<$<0u, false> >::value(std::forward<types>(arguments)...)); }
    };

    #ifdef __cpp_noexcept_function_type
      template <class shorthand, typename type, typename... types, bool arbitrary>
      struct cast<shorthand, type (types...), arbitrary, false> final {
        constexpr static type (&value)(types...) = cast<shorthand, type (types...) noexcept, arbitrary, false>::value;
      };

      template <class shorthand, typename type, typename... types, bool arbitrary>
      struct cast<shorthand, type (types..., ...), arbitrary, false> final {
        constexpr static type (&value)(types..., ...) = cast<shorthand, type (types..., ...) noexcept, arbitrary, false>::value;
      };
    #endif

    /* Class */
    template <class expression>
    struct $arguments final {
      friend struct $expression;

      private:
        template <class type>
        constexpr inline $arguments(type&&) noexcept {}
    };

    // ...
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
        constexpr inline typename std::enable_if<0u != index, typename $operands<>::$operand<typename pack<expression, expressions...>::template at<index <= sizeof...(expressions) ? index : 0u>::type>::type>::type operator []($operands<>::$index<index> const) const noexcept {
          return this -> $operands<expressions...>::operator []($operands<>::$index<index - 1u>{});
        }
    };

    /* ... */
    constexpr static $operands<>::$index<0u> $0 {};
    constexpr static $operands<>::$index<1u> $1 {};
    constexpr static $operands<>::$index<2u> $2 {};

    /* ... */
    template <class>
    struct invoke;

    template <bool referrable>
    struct invoke<$<0u, referrable> > final {
      template <typename type>
      constexpr inline static typename std::enable_if<std::is_array<typename std::remove_reference<type>::type>::value, typename std::remove_extent<type>::type>::type value() noexcept {
        return NULL;
      }

      template <typename type>
      constexpr inline static typename std::enable_if<false != std::is_scalar<type>::value, type>::type value() noexcept {
        return 0;
      }

      template <typename type>
      constexpr inline static typename std::enable_if<false == std::is_scalar<type>::value, type>::type value() noexcept {
        return type();
      }

      template <typename... types>
      constexpr inline static typename std::conditional<(__cplusplus >= 201103L), void, int>::type value(types&&...) noexcept {
        return typename std::conditional<(__cplusplus >= 201103L), void, int>::type(0x0);
      }

      template <typename type, typename... types>
      constexpr inline static typename std::enable_if<can_default_initialize<type>::value, type>::type value(type&&, types&&...) noexcept {
        return value<type>();
      }

      template <typename type, std::size_t capacity, typename... types>
      constexpr inline static type* value(type (&)[capacity], types&&...) noexcept {
        return NULL;
      }

      template <typename type, std::size_t capacity, typename... types>
      constexpr inline static type* value(type (&&)[capacity], types&&...) noexcept {
        return NULL;
      }

      #if __cplusplus >= 202002L || defined(__cpp_lib_bounded_array_traits) || (defined(_MSVC_LANG) && _MSVC_LANG <= 202002L)
        template <typename type, typename... types>
        constexpr inline static type* value(type (&)[], types&&...) noexcept {
          return NULL;
        }

        template <typename type, typename... types>
        constexpr inline static type* value(type (&&)[], types&&...) noexcept {
          return NULL;
        }
      #endif
    };

    template <bool referrable>
    struct invoke<$<1u, referrable> > final {
      template <typename type, typename... types>
      constexpr inline static type&& value(type&& object, types&&...) noexcept {
        return std::forward<type>(object);
      }
    };

    template <std::size_t index, bool referrable>
    struct invoke<$<index, referrable> > final {
      template <typename type, typename... types>
      constexpr inline static typename pack<type&&, types&&...>::template at<(index > 1u ? index - 1u : 0u)>::type value(type&&, types&&... objects) noexcept {
        return invoke<$<index - 1u> >::value(std::forward<types>(objects)...);
      }
    };

    template <$operation operation, class... expressions>
    struct invoke<$expression<operation, expressions...> > final {
      typedef $operands<expressions...> $operands;

      /* ... */
      template <class... types>
      constexpr inline static typename std::enable_if<operation == $add, decltype(std::declval<$operands>()[$0](std::declval<types>()...) + std::declval<$operands>()[$1](std::declval<types>()...))>::type value($operands const& operands, types&&... arguments) noexcept {
        return operands[$0](std::forward<types>(arguments)...) + operands[$1](std::forward<types>(arguments)...);
      }

      template <class... types>
      constexpr inline static typename std::enable_if<operation == $call, decltype(apply(std::declval<$operands>()[$0](std::declval<types>()...), std::declval<$arguments<typename to_arguments<decltype(std::declval<$operands>()[$1])>::type> >(), std::declval<types>()...))>::type value($operands const& operands, types&&... arguments) noexcept {
        return apply(operands[$0](std::forward<types>(arguments)...), $arguments<typename to_arguments<decltype(operands[$1])>::type>{operands[$1]}, std::forward<types>(arguments)...);
      }

      template <class... types>
      constexpr inline static typename std::enable_if<operation == $minus, decltype(-std::declval<$operands>()[$0](std::declval<types>()...))>::type value($operands const& operands, types&&... arguments) noexcept {
        return -operands[$0](std::forward<types>(arguments)...);
      }
    };

    // ... ->> deferred function shorthand call
    template <typename type, class... expressions, typename... types>
    inline static int apply(type const& function, $arguments<$expression<$comma, expressions...> > const&, types&&... arguments) noexcept {
      return function(expressions{}(std::forward<types>(arguments)...)...);
    }
};

template <$operation operation, class... expressions>
struct $expression : public $shorthand {
  template <class, typename, bool> friend struct $expression<$nop>::cast;
  template <class...>              friend struct $expression<$nop>::$operands;

  private:
    $expression<$nop>::$operands<expressions...> const value;

  public:
    constexpr inline $expression() noexcept :
      value()
    {}

    constexpr inline $expression(expressions const&... operands) noexcept :
      value(operands...)
    {}

    /* ... */
    template <typename... types>
    constexpr inline decltype($expression<$nop>::template invoke<$expression>::value(std::declval<$expression<$nop>::$operands<expressions...> >(), std::declval<types>()...)) operator ()(types&&... arguments) const noexcept {
      return $expression<$nop>::template invoke<$expression>::value(this -> value, std::forward<types>(arguments)...);
    }

    template <typename type>
    constexpr inline operator type() const noexcept {
      return $expression<$nop>::template cast<$expression, typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value;
    }
};

template <typename base>
struct $expression<$nop, $captured<base> > : public $shorthand {
  private:
    base&& value;

  public:
    constexpr $expression(base&& object) noexcept :
      value(static_cast<base&&>(object))
    {}

    constexpr inline $expression($expression const& expression) noexcept :
      value(static_cast<base&&>(expression.value))
    {}

    /* ... */
    template <typename... types>
    constexpr inline base&& operator ()(types&&...) const noexcept {
      return static_cast<base&&>(this -> value);
    }
};

template <typename base, base constant>
struct $expression<$nop, $c<base, constant> > : public $shorthand {
  template <typename... types>
  constexpr inline base operator ()(types&&...) const volatile noexcept {
    return constant;
  }

  template <typename type>
  constexpr inline operator type() const volatile noexcept {
    return $expression<$nop>::template cast<$c<base, constant>, typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value;
  }
};

template <std::size_t index>
struct $expression<$nop, $<index, false> > : public $shorthand {
  template <typename... types>
  constexpr inline decltype($expression<$nop>::template invoke<$<index, false> >::value(std::declval<types>()...)) operator ()(types&&... arguments) const volatile noexcept {
    return $expression<$nop>::template invoke<$<index, false> >::value(std::forward<types>(arguments)...);
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
    return $expression<$nop>::template invoke<$<0u, false> >::value<type>();
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
      value(const_cast<void*>(static_cast<void const volatile*>(addressof($expression<$nop>::template invoke<$<index, false> >::value(std::forward<types>(objects)...)))))
    {}

    /* ... */
    template <typename type>
    constexpr inline operator type() const volatile noexcept {
      return static_cast<type>(*static_cast<typename std::remove_reference<type>::type*>(this -> value));
    }
};

// ...
template <typename base>
struct $captured<base> final : public $expression<$nop, $captured<base> > {
  using $expression<$nop, $captured<base> >::$expression;
};

// ...
template <typename base, base constant>
struct $c : public $expression<$nop, $c<base, constant> > {};
  #ifdef __cpp_nontype_template_parameter_auto
    template <auto constant>
    struct $u final : public $c<typename std::enable_if<std::is_integral<decltype(constant)>::value && std::is_unsigned<decltype(constant)>::value, decltype(constant)>::type, constant> {};
  #else
    template <unsigned long long constant>
    struct $u final : public $c<unsigned long long, constant> {};
  #endif

  // ...
  #ifdef __cpp_nontype_template_parameter_auto
    template <auto constant>
    struct $p final : public $c<typename std::enable_if<std::is_pointer<decltype(constant)>::value, decltype(constant)>::type, constant> {};

    template <auto constant>
    struct $s final : public $c<typename std::enable_if<std::is_class<decltype(constant)>::value || std::is_union<decltype(constant)>::value, decltype(constant)>::type, constant> {};
  #else
    template <void* constant>
    struct $p final : public $c<void*, constant> {};
  #endif

  // ...
  #ifdef __cpp_nontype_template_parameter_auto
    template <auto constant>
    struct $i final : public $c<typename std::enable_if<std::is_integral<decltype(constant)>::value && std::is_signed<decltype(constant)>::value, decltype(constant)>::type, constant> {};
  #else
    template <signed long long constant>
    struct $i final : public $c<signed long long, constant> {};
  #endif

  // ...
  #ifdef __cpp_nontype_template_parameter_auto
    template <auto constant>
    struct $f final : public $c<typename std::enable_if<std::is_floating_point<decltype(constant)>::value, decltype(constant)>::type, constant> {};
  #elif __cplusplus >= 202002L
    template <long double constant>
    struct $f final : public $c<long double, constant> {};
  #elif defined(_MSVC_LANG)
  # if _MSVC_LANG >= 202002L
    template <long double constant>
    struct $f final : public $c<long double, constant> {};
  # endif
  #endif

  // ...
  #ifdef __cpp_nontype_template_parameter_auto
    template <auto constant>
    struct $e final : public $c<typename std::enable_if<std::is_enum<decltype(constant)>::value, decltype(constant)>::type, constant> {};
  #else
    template <std::size_t constant>
    struct $e final : public $c<std::size_t, constant> {};
  #endif

// ...
template <std::size_t index, bool referrable>
struct $ final : public $expression<$nop, $<index, referrable> > {
  using $expression<$nop, $<index, referrable> >::$expression;
};
  constexpr static $<0u, false> $0 {};
  constexpr static $<1u, false> $1 {};
  constexpr static $<2u, false> $2 {};
  constexpr static $<3u, false> $3 {};
  constexpr static $<4u, false> $4 {};
  constexpr static $<5u, false> $5 {};
  constexpr static $<6u, false> $6 {};
  constexpr static $<7u, false> $7 {};
  constexpr static $<8u, false> $8 {};
  constexpr static $<9u, false> $9 {};

/* ... */
template <$operation operation, class... expressions> constexpr inline $expression<$minus, $expression<operation, expressions...> > operator -($expression<operation, expressions...> const expression) noexcept { return {expression}; }

template <$operation operationA, class... expressionsA, $operation operationB, class... expressionsB> constexpr inline $expression<$add,         $expression<operationA, expressionsA...>, $expression<operationB, expressionsB...> > operator +($expression<operationA, expressionsA...> const expressionA, $expression<operationB, expressionsB...> const expressionB) noexcept { return {expressionA, expressionB}; }
template <$operation operationA, class... expressionsA, $operation operationB, class... expressionsB> constexpr inline $expression<$bitwise_and, $expression<operationA, expressionsA...>, $expression<operationB, expressionsB...> > operator &($expression<operationA, expressionsA...> const expressionA, $expression<operationB, expressionsB...> const expressionB) noexcept { return {expressionA, expressionB}; }
template <$operation operationA, class... expressionsA, $operation operationB, class... expressionsB> constexpr inline $expression<$comma,       $expression<operationA, expressionsA...>, $expression<operationB, expressionsB...> > operator ,($expression<operationA, expressionsA...> const expressionA, $expression<operationB, expressionsB...> const expressionB) noexcept { return {expressionA, expressionB}; }

template <$operation operation, class... expressions, typename type> constexpr inline $expression<$add,         $expression<operation, expressions...>, $expression<$nop, $captured<type&&> > > operator +($expression<operation, expressions...> const expression, type&& object) noexcept { return {expression, std::forward<type>(object)}; }
template <$operation operation, class... expressions, typename type> constexpr inline $expression<$add,         $expression<$nop, $captured<type&&> >, $expression<operation, expressions...> > operator +(type&& object, $expression<operation, expressions...> const expression) noexcept { return {std::forward<type>(object), expression}; }
template <$operation operation, class... expressions, typename type> constexpr inline $expression<$bitwise_and, $expression<operation, expressions...>, $expression<$nop, $captured<type&&> > > operator &($expression<operation, expressions...> const expression, type&& object) noexcept { return {expression, std::forward<type>(object)}; }
template <$operation operation, class... expressions, typename type> constexpr inline $expression<$bitwise_and, $expression<$nop, $captured<type&&> >, $expression<operation, expressions...> > operator &(type&& object, $expression<operation, expressions...> const expression) noexcept { return {std::forward<type>(object), expression}; }
template <$operation operation, class... expressions, typename type> constexpr inline $expression<$comma,       $expression<operation, expressions...>, $expression<$nop, $captured<type&&> > > operator ,($expression<operation, expressions...> const expression, type&& object) noexcept { return {expression, std::forward<type>(object)}; }
template <$operation operation, class... expressions, typename type> constexpr inline $expression<$comma,       $expression<$nop, $captured<type&&> >, $expression<operation, expressions...> > operator ,(type&& object, $expression<operation, expressions...> const expression) noexcept { return {std::forward<type>(object), expression}; }

template <typename type, typename... types, $operation operation, class... expressions> constexpr inline typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $captured<type (&)(types...)> >,      $expression<operation, expressions...> > >::type operator &(type (&function)(types...),       $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
template <typename type, typename... types, $operation operation, class... expressions> constexpr inline typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $captured<type (&)(types..., ...)> >, $expression<operation, expressions...> > >::type operator &(type (&function)(types..., ...),  $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
template <typename type, typename... types, $operation operation, class... expressions> constexpr inline typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $captured<type (&)(types...)> >,      $expression<operation, expressions...> > >::type operator &(type (&&function)(types...),      $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
template <typename type, typename... types, $operation operation, class... expressions> constexpr inline typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $captured<type (&)(types..., ...)> >, $expression<operation, expressions...> > >::type operator &(type (&&function)(types..., ...), $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
#ifdef __cpp_noexcept_function_type
  template <typename type, typename... types, $operation operation, class... expressions> constexpr inline typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $captured<type (&)(types...)      noexcept> >, $expression<operation, expressions...> > >::type operator &(type (&function)(types...)       noexcept, $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
  template <typename type, typename... types, $operation operation, class... expressions> constexpr inline typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $captured<type (&)(types..., ...) noexcept> >, $expression<operation, expressions...> > >::type operator &(type (&function)(types..., ...)  noexcept, $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
  template <typename type, typename... types, $operation operation, class... expressions> constexpr inline typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $captured<type (&)(types...)      noexcept> >, $expression<operation, expressions...> > >::type operator &(type (&&function)(types...)      noexcept, $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
  template <typename type, typename... types, $operation operation, class... expressions> constexpr inline typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $captured<type (&)(types..., ...) noexcept> >, $expression<operation, expressions...> > >::type operator &(type (&&function)(types..., ...) noexcept, $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
#endif
