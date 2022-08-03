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
  constexpr base instanceof() noexcept;

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
        template <std::size_t subindex, typename subbase, typename... subbases> struct valueof<subindex, subbase, subbases...> final { typedef typename valueof<subindex - 1u, subbases...>::type type; };
        template <typename subbase, typename... subbases>                       struct valueof<0u, subbase, subbases...>       final { typedef subbase type; };

      public:
        typedef typename valueof<index, bases...>::type type;
    };
  };

  // ...
  template <typename base> constexpr typename std::enable_if<false == (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&  object) noexcept { return &object; }
  template <typename base> constexpr typename std::enable_if<false == (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&& object) noexcept { return &static_cast<base&>(object); }

  template <typename base> inline typename std::enable_if<false != (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&  object) noexcept { return const_cast<base*>(reinterpret_cast<base const volatile*>(&reinterpret_cast<unsigned char const volatile&>(object))); }
  template <typename base> inline typename std::enable_if<false != (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&& object) noexcept { return const_cast<base*>(reinterpret_cast<base const volatile*>(&reinterpret_cast<unsigned char const volatile&>(static_cast<base&>(object)))); }

  template <typename base, std::size_t capacity> constexpr base (*addressof(base (&object)[capacity])  noexcept)[capacity] { return &object; }
  template <typename base, std::size_t capacity> constexpr base (*addressof(base (&&object)[capacity]) noexcept)[capacity] { return &static_cast<base (&)[capacity]>(object); }

  #if __cplusplus >= 202002L || defined(__cpp_lib_bounded_array_traits) || (defined(_MSVC_LANG) && _MSVC_LANG <= 202002L)
    template <typename base> constexpr base (*addressof(base (&object)[])  noexcept)[] { return &object; }
    template <typename base> constexpr base (*addressof(base (&&object)[]) noexcept)[] { return &static_cast<base (&)[]>(object); }
  #endif
}

/* Declaration */
// $as<Object>($1).do_stuff()
// $for<n>{}($1.do_stuff())
// $for<x>{}($for<y>{}($1.do_stuff() + $2 + $3))
enum   $operation : unsigned char; // ->> shorthand `$expression` operator
struct $shorthand;                 // ->> shorthand base and namespace for runtime non-self-contained shorthand information

template <std::size_t, bool = true> struct $;                                                                                                                              // ->> shorthand
template <typename>                 struct $as;                                                                                                                            // ->> conversion shorthand
template <typename base, base>      struct $c;                                                                                                                             // ->> shorthand constant
template <typename base, typename std::enable_if<false == std::is_base_of<$shorthand, typename std::remove_reference<base>::type>::value, int>::type = 0> struct $capture; // ->> shorthand capture
template <$operation, class...>     struct $expression;                                                                                                                    // ->> composited shorthands
template <std::size_t>              struct $for;                                                                                                                           // ->> iteration function
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

/* Enumeration */
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

/* Class */
struct $shorthand {
  template <$operation, class...>
  friend struct $expression;

  private:
    /* Trait */
    template <class>                                      struct can_capture_cast                                          final { static bool const value = false; };
    template <typename base>                              struct can_capture_cast<$capture<base> >                         final { static bool const value = true; };
    template <$operation operation, class... expressions> struct can_capture_cast<$expression<operation, expressions...> > final { static bool const value = boolean_or<can_capture_cast<expressions>::value...>::value; };

    /* Class */
    template <std::size_t>
    struct $index final {};

    // ...
    template <class...>
    struct $operands {
      friend struct $shorthand;
      template <class...> friend struct $operands;

      private:
        /* Class */
        template <class subexpression, bool = can_capture_cast<subexpression>::value>
        struct $operand final {
          template <$operation, class...> friend struct $expression;
          template <class...>             friend struct $operands;

          private:
            typedef subexpression const& type;
            subexpression const value;

            /* ... */
            constexpr $operand()                           noexcept : value() {}
            constexpr $operand(subexpression const& value) noexcept : value(value) {}

            constexpr operator type() const noexcept {
              return this -> value;
            }
        };

        template <class subexpression>
        struct $operand<subexpression, false> final {
          template <$operation, class...> friend struct $expression;
          template <class...>             friend struct $operands;

          private:
            typedef subexpression type;

            /* ... */
            constexpr $operand()                     noexcept {}
            constexpr $operand(subexpression const&) noexcept {}

            /* ... */
            constexpr operator type() const noexcept {
              return {};
            }
        };

        /* ... */
        template <typename type>
        constexpr void operator [](type const) const noexcept = delete;
    };

    template <class expression, class... expressions>
    struct $operands<expression, expressions...> : public $operands<expressions...> {
      template <$operation, class...>
      friend struct $expression;

      protected:
        $operands<>::$operand<expression> const value;

        /* ... */
        constexpr $operands()                                                          noexcept : $operands<expressions...>::$operands(), value() {}
        constexpr $operands(expression const& operand, expressions const&... operands) noexcept : $operands<expressions...>::$operands(operands...), value(operand) {}

      public:
        template <std::size_t index>
        constexpr typename std::enable_if<0u == index, typename $operands<>::$operand<expression>::type>::type operator []($index<index> const) const noexcept {
          return this -> value;
        }

        template <std::size_t index>
        constexpr typename std::enable_if<0u != index, typename $operands<>::$operand<typename pack<expression, expressions...>::template at<index <= sizeof...(expressions) ? index : 0u>::type>::type>::type operator []($index<index> const) const noexcept {
          return this -> $operands<expressions...>::operator []($index<index - 1u>{});
        }
    };

    /* Constant */
    constexpr static $index<0u> $0i {};
    constexpr static $index<1u> $1i {};
    constexpr static $index<2u> $2i {}; // ->> possible ternary overloads?

    /* Trait */
    struct to final {
      struct captures final {
        template <class... expressions>
        constexpr captures($operands<expressions...> const&) noexcept {
        }

        // operands[0]
        //   operands[0]
        //     operands[0] // STOP
        //     operands[n] // END
        //   operands[1]
      };

      template <class shorthand> struct nop                                final { typedef $expression<$nop, shorthand> type; };
      template <class shorthand> struct nop<$expression<$nop, shorthand> > final { typedef $expression<$nop, shorthand> type; };
    };

    // ...
    template <class, typename = void /* ->> hint for `$0`s */>
    struct invoke;

    template <typename hint> // ->> for `$0`s
    struct invoke<$<0u, false>, hint> final {
      template <typename type>
      constexpr static typename std::enable_if<false != std::is_scalar<typename std::remove_reference<type>::type>::value, type>::type value() noexcept {
        return 0;
      }

      template <typename type>
      constexpr static typename std::enable_if<false == std::is_array<typename std::remove_reference<type>::type>::value && false == std::is_scalar<typename std::remove_reference<type>::type>::value, type>::type value() noexcept {
        return type();
      }

      template <typename type>
      constexpr static typename std::enable_if<false != std::is_array<typename std::remove_reference<type>::type>::value && false == std::is_scalar<typename std::remove_reference<type>::type>::value, typename std::remove_extent<typename std::remove_reference<type>::type>::type*>::type value() noexcept {
        return NULL;
      }

      template <typename... types>
      constexpr static typename std::conditional<(__cplusplus >= 201103L), int, void>::type value(types&&...) noexcept {
        return typename std::conditional<(__cplusplus >= 201103L), int, void>::type(0x0);
      }

      template <typename type, typename... types>
      constexpr static typename std::enable_if<can_default_initialize<type>::value, type>::type value(type&&, types&&...) noexcept {
        return invoke<$<0u, false>, hint>::value<type>();
      }

      template <typename type, std::size_t capacity, typename... types>
      constexpr static type* value(type (&)[capacity], types&&...) noexcept {
        return NULL;
      }

      template <typename type, std::size_t capacity, typename... types>
      constexpr static type* value(type (&&)[capacity], types&&...) noexcept {
        return NULL;
      }

      #if __cplusplus >= 202002L || defined(__cpp_lib_bounded_array_traits) || (defined(_MSVC_LANG) && _MSVC_LANG <= 202002L)
        template <typename type, typename... types>
        constexpr static type* value(type (&)[], types&&...) noexcept {
          return NULL;
        }

        template <typename type, typename... types>
        constexpr static type* value(type (&&)[], types&&...) noexcept {
          return NULL;
        }
      #endif
    };

    template <typename hint> // ->> for `$1`s
    struct invoke<$<1u, false>, hint> final {
      template <typename type, typename... types>
      constexpr static type&& value(type&& object, types&&...) noexcept {
        return std::forward<type>(object);
      }
    };

    template <std::size_t index, typename hint> // ->> for shorthands
    struct invoke<$<index, false>, hint> final {
      template <typename type, typename... types>
      constexpr static typename pack<type&&, types&&...>::template at<index - 1u>::type value(type&&, types&&... objects) noexcept {
        return invoke<$<index - 1u, false>, hint>::value(std::forward<types>(objects)...);
      }
    };

    template <typename base, base constant, typename hint>
    struct invoke<$c<base, constant>, hint> final {
      template <typename... types>
      constexpr static base value(types&&...) noexcept {
        return constant;
      }
    };

    template <class... expressions, typename hint> // ->> for `function&(...)`s
    struct invoke<$expression<$call, expressions...>, hint> final {
      template <class... types>
      constexpr static decltype(std::declval<$operands<expressions...> >()[$0i].template call<hint>(std::declval<types>()...)(std::declval<$operands<expressions...> >()[$1i].template call<hint>(std::declval<types>()...))) value($operands<expressions...> const& operands, types&&... arguments) noexcept {
        return operands[$0i].template call<hint>(std::forward<types>(arguments)...)(operands[$1i].template call<hint>(std::forward<types>(arguments)...));
      }
    };

    template <$operation operation, class... expressions, typename hint> // ->> for shorthand expressions
    struct invoke<$expression<operation, expressions...>, hint> final {
      template <class... types>
      constexpr static typename std::enable_if<operation == $add, decltype(std::declval<$operands<expressions...> >()[$0i].template call<hint>(std::declval<types>()...) + std::declval<$operands<expressions...> >()[$1i].template call<hint>(std::declval<types>()...))>::type value($operands<expressions...> const& operands, types&&... arguments) noexcept {
        return operands[$0i].template call<hint>(std::forward<types>(arguments)...) + operands[$1i].template call<hint>(std::forward<types>(arguments)...);
      }

      template <class... types>
      constexpr static typename std::enable_if<operation == $minus, decltype(-std::declval<$operands<expressions...> >()[$0i].template call<hint>(std::declval<types>()...))>::type value($operands<expressions...> const& operands, types&&... arguments) noexcept {
        return -operands[$0i].template call<hint>(std::forward<types>(arguments)...);
      }
    };

    // ...
    template <class shorthand, typename, bool = can_capture_cast<shorthand>::value>
    struct cast;

    template <typename type, typename... types>
    struct cast<$<0u, false>, type (types..., ...) noexcept, false> final {
      constexpr static type value(types... arguments, ...) noexcept {
        return static_cast<type>(invoke<$<0u, false>, type>::value(std::forward<types>(arguments)...));
      }

      template <class sus>
      constexpr static type (&valueof(sus&&) noexcept)(types..., ...) /*noexcept*/ {
        return value;
      }
    };

    template <std::size_t index, typename type, typename... types>
    struct cast<$<index, false>, type (types..., ...) noexcept, false> final {
      constexpr static type value(types... arguments, ...) noexcept {
        return static_cast<type>(invoke<$<index, false>, type>::value(std::forward<types>(arguments)...));
      }

      template <class sus> constexpr static type (&valueof(sus&&) noexcept)(types..., ...) noexcept {
        return value;
      }
    };

    template <std::size_t index, typename type, typename... types>
    struct cast<$<index, false>, type (types...) noexcept, false> final {
      constexpr static type value(types... arguments) noexcept {
        return static_cast<type>(invoke<$<index, false>, type>::value(std::forward<types>(arguments)...));
      }

      template <class sus> constexpr static type (&valueof(sus&&) noexcept)(types...) /*noexcept*/ {
        return value;
      }
    };

    template <typename base, base constant, typename type, typename... types>
    struct cast<$c<base, constant>, type (types...) noexcept, false> final {
      constexpr static type value(types... arguments) noexcept {
        return invoke<$c<base, constant>, type>::value(std::forward<types>(arguments)...);
      }

      template <class sus> constexpr static type (&valueof(sus&&) noexcept)(types...) /*noexcept*/ {
        return value;
      }
    };

    template <typename base, base constant, typename type, typename... types>
    struct cast<$c<base, constant>, type (types..., ...) noexcept, false> final {
      constexpr static type value(types... arguments, ...) noexcept {
        return invoke<$c<base, constant>, type>::value(std::forward<types>(arguments)...);
      }

      template <class sus> constexpr static type (&valueof(sus&&) noexcept)(types..., ...) noexcept {
        return value;
      }
    };

    template <$operation operation, class... expressions, typename type, typename... types>
    struct cast<$expression<operation, expressions...>, type (types...) noexcept, false> final {
      constexpr static type value(types... arguments) noexcept {
        return invoke<$expression<operation, expressions...>, type>::value($expression<operation, expressions...>{}.value, std::forward<types>(arguments)...);
      }

      template <class sus> constexpr static type (&valueof(sus&&) noexcept)(types...) /*noexcept*/ {
        return value;
      }
    };

    template <$operation operation, class... expressions, typename type, typename... types>
    struct cast<$expression<operation, expressions...>, type (types...) noexcept, true> final {
      constexpr static type value(types...) noexcept;

      template <class sus> constexpr static type (&valueof(sus&&) noexcept)(types...) noexcept {
        return value;
      }
    };

    template <$operation operation, class... expressions, typename type, typename... types>
    struct cast<$expression<operation, expressions...>, type (types..., ...) noexcept, false> final {
      constexpr static type value(types... arguments, ...) noexcept {
        return invoke<$expression<operation, expressions...>, type>::value($expression<operation, expressions...>{}.value, std::forward<types>(arguments)...);
      }

      template <class sus> constexpr static type (&valueof(sus&&) noexcept)(types..., ...) /*noexcept*/ {
        return value;
      }
    };

    template <$operation operation, class... expressions, typename type, typename... types>
    struct cast<$expression<operation, expressions...>, type (types..., ...) noexcept, true> final {
      constexpr static type value(types..., ...) noexcept;
    };

    #ifdef __cpp_noexcept_function_type // ->> implicitly converts `noexcept` signatures to their exception-prone counterparts
      template <class shorthand, typename type, typename... types, bool captured>
      struct cast<shorthand, type (types...), captured> final {
        constexpr static type (&value)(types...) = cast<shorthand, type (types...) noexcept, captured>::value;
        template <class sus> constexpr static type (&valueof(sus&&) noexcept)(types...) { return value; }
      };

      template <class shorthand, typename type, typename... types, bool captured>
      struct cast<shorthand, type (types..., ...), captured> final {
        constexpr static type (&value)(types..., ...) = cast<shorthand, type (types..., ...) noexcept, captured>::value;
        template <class sus> constexpr static type (&valueof(sus&&) noexcept)(types..., ...) { return value; }
      };
    #endif

    // ...
    template <class>
    struct baseof final {
      struct type {};
    };

    template <$operation operation, class expression>
    struct baseof<$expression<operation, expression> > final {
      typedef expression type;
    };

    template <$operation operation, typename base, base constant>
    struct baseof<$expression<operation, $expression<$nop, $c<base, constant> > > > final {
      typedef typename $c<base, constant>::type type;
    };

    template <$operation operation, typename base, base constant, class expression, class... expressions>
    struct baseof<$expression<operation, $expression<$nop, $c<base, constant> >, expression, expressions...> > final {
      typedef typename baseof<$expression<operation, expression, expressions...> >::type type;
    };

    template <$operation operation, $operation suboperation, class... subexpressions>
    struct baseof<$expression<operation, $expression<suboperation, subexpressions...> > > final {
      typedef typename baseof<$expression<suboperation, subexpressions...> >::type type;
    };

  public:
    static void *BUFFER;
};

// ...
template <$operation operation, class... expressions>
struct $expression : public $shorthand {
  template <$operation, class...>  friend struct $expression;
  template <class>                 friend struct $shorthand::baseof;
  template <class, typename, bool> friend struct $shorthand::cast;
  template <class, typename>       friend struct $shorthand::invoke;

  private:
    $shorthand::$operands<expressions...> const value;

  public:
    constexpr $expression()                               noexcept : value() {}
    constexpr $expression(expressions const&... operands) noexcept : value(operands...) {}

    /* ... */
    template <typename... types>
    constexpr decltype($shorthand::invoke<$expression>::value(std::declval<$shorthand::$operands<expressions...> >(), std::declval<types>()...)) operator ()(types&&... arguments) const noexcept {
      return $shorthand::invoke<$expression>::value(this -> value, std::forward<types>(arguments)...);
    }

    constexpr operator typename $shorthand::baseof<$expression>::type() const noexcept {
      return $shorthand::cast<$expression, typename std::remove_pointer<typename $shorthand::baseof<$expression>::type>::type>::valueof(*this);
    }

    template <typename type>
    constexpr operator type() const noexcept {
      return $shorthand::cast<$expression, typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::valueof(*this);
    }

  private:
    template <typename, typename... types>
    constexpr decltype(std::declval<$expression>().operator ()(std::declval<types>()...)) call(types&&... arguments) const noexcept {
      return this -> operator ()(std::forward<types>(arguments)...);
    }
};

template <typename base>
struct $expression<$nop, $capture<base> > : public $shorthand {
  template <$operation, class...>  friend struct $expression;
  template <class>                 friend struct $shorthand::baseof;
  template <class, typename, bool> friend struct $shorthand::cast;
  template <class, typename>       friend struct $shorthand::invoke;

  private:
    base&& value;

    /* ... */
    template <typename, typename... types>
    constexpr base&& call(types&&...) const noexcept {
      return static_cast<base&&>(this -> value);
    }

  public:
    constexpr $expression(base&& object)                 noexcept : value(static_cast<base&&>(object)) {}
    constexpr $expression($expression const& expression) noexcept : value(static_cast<base&&>(expression.value)) {}
};

template <typename base, base constant>
struct $expression<$nop, $c<base, constant> > : public $shorthand {
  template <$operation, class...>  friend struct $expression;
  template <class>                 friend struct $shorthand::baseof;
  template <class, typename, bool> friend struct $shorthand::cast;
  template <class, typename>       friend struct $shorthand::invoke;

  private:
    typedef base (*type)();

  public:
    template <typename... types>
    constexpr decltype($shorthand::invoke<$c<base, constant> >::value(std::declval<types>()...)) operator ()(types&&... arguments) const volatile noexcept {
      return $shorthand::invoke<$c<base, constant> >::value(std::forward<types>(arguments)...);
    }

    constexpr operator type() const volatile noexcept {
      return $shorthand::cast<$c<base, constant>, typename std::remove_pointer<type>::type>::valueof(*this);
    }

    template <typename type>
    constexpr operator type() const volatile noexcept {
      return $shorthand::cast<$c<base, constant>, typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::valueof(*this);
    }

  private:
    template <typename, typename... types>
    constexpr decltype(std::declval<$expression<$nop, $c<base, constant> > >().operator ()(std::declval<types>()...)) call(types&&... arguments) const noexcept {
      return this -> operator ()(std::forward<types>(arguments)...);
    }
};

template <std::size_t index>
struct $expression<$nop, $<index, false> > : public $shorthand {
  template <$operation, class...>  friend struct $expression;
  template <class>                 friend struct $shorthand::baseof;
  template <class, typename, bool> friend struct $shorthand::cast;
  template <class, typename>       friend struct $shorthand::invoke;

  public:
    template <typename... types>
    constexpr decltype($shorthand::invoke<$<index, false> >::value(std::declval<types>()...)) operator ()(types&&... arguments) const volatile noexcept {
      return $shorthand::invoke<$<index, false> >::value(std::forward<types>(arguments)...);
    }

    template <typename type>
    constexpr operator type() const volatile noexcept {
      return $shorthand::cast<$<index, false>, typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::valueof(*this);
    }

  private:
    template <typename type, typename... types>
    constexpr typename std::enable_if<0u == index, type>::type call(types&&...) const noexcept {
      return $shorthand::invoke<$<0u, false> >::value<type>();
    }

    template <typename type, typename... types>
    constexpr typename std::enable_if<0u != index, decltype(std::declval<$expression<$nop, $<index, false> > >().operator ()(std::declval<types>()...))>::type call(types&&... arguments) const noexcept {
      return this -> operator ()(std::forward<types>(arguments)...);
    }
};

template <>
struct $expression<$nop, $<0u, true> > : public $expression<$nop, $<0u, false> > {
  template <class, typename, bool> friend struct $shorthand::cast;
  template <class, typename>       friend struct $shorthand::invoke;

  private:
    template <typename type>
    constexpr typename std::enable_if<false == std::is_function<typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value, type>::type cast() const volatile noexcept {
      return $shorthand::invoke<$<0u, false> >::value<type>();
    }

    template <typename type>
    constexpr typename std::enable_if<false != std::is_function<typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value, type>::type cast() const volatile noexcept {
      return $shorthand::cast<$<0u, false>, typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::valueof(*this);
    }

  public:
    template <typename... types>
    constexpr $expression(types&&...) noexcept {}

    /* ... */
    template <typename type>
    constexpr operator type() const volatile noexcept {
      return this -> cast<type>();
    }
};

template <std::size_t index>
struct $expression<$nop, $<index, true> > : public $expression<$nop, $<index, false> > {
  template <class, typename, bool> friend struct $shorthand::cast;
  template <class, typename>       friend struct $shorthand::invoke;

  private:
    void *const value;

    /* ... */
    template <typename type>
    constexpr typename std::enable_if<false == std::is_function<typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value, type>::type cast() const volatile noexcept {
      return static_cast<type>(*static_cast<typename std::remove_reference<type>::type*>(this -> value));
    }

    template <typename type>
    constexpr typename std::enable_if<false != std::is_function<typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value, type>::type cast() const volatile noexcept {
      return $shorthand::cast<$<index, false>, typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::valueof(*this);
    }

  public:
    constexpr $expression() noexcept :
      value(NULL)
    {}

    template <std::size_t subindex>
    constexpr $expression($expression<$nop, $<subindex, true> > const unit) noexcept :
      value(static_cast<typename std::enable_if<(index >= subindex && 0u != subindex), void*>::type>(unit.value))
    {}

    template <typename... types>
    constexpr $expression(types&&... objects) noexcept :
      value(const_cast<void*>(static_cast<void const volatile*>(addressof($shorthand::invoke<$<index, false> >::value(std::forward<types>(objects)...)))))
    {}

    /* ... */
    template <typename type>
    constexpr operator type() const volatile noexcept {
      return this -> cast<type>();
    }
};

// ...
template <typename base>
struct $capture<base> final : public $expression<$nop, $capture<base> > {
  using $expression<$nop, $capture<base> >::$expression;
};

// ...
template <typename base, base constant>
struct $c : public $expression<$nop, $c<base, constant> > {};
  #ifdef __cpp_nontype_template_parameter_auto
    template <auto constant>
    struct $e final : public $c<typename std::enable_if<std::is_enum<decltype(constant)>::value, decltype(constant)>::type, constant> {};

    template <auto constant>
    struct $f final : public $c<typename std::enable_if<std::is_floating_point<decltype(constant)>::value, decltype(constant)>::type, constant> {};

    template <auto constant>
    struct $i final : public $c<typename std::enable_if<std::is_integral<decltype(constant)>::value && std::is_signed<decltype(constant)>::value, decltype(constant)>::type, constant> {};

    template <auto constant>
    struct $p final : public $c<typename std::enable_if<std::is_pointer<decltype(constant)>::value, decltype(constant)>::type, constant> {};

    template <auto constant>
    struct $s final : public $c<typename std::enable_if<std::is_class<decltype(constant)>::value || std::is_union<decltype(constant)>::value, decltype(constant)>::type, constant> {};

    template <auto constant>
    struct $u final : public $c<typename std::enable_if<std::is_integral<decltype(constant)>::value && std::is_unsigned<decltype(constant)>::value, decltype(constant)>::type, constant> {};
  #else
    template <std::size_t constant>
    struct $e final : public $c<std::size_t, constant> {};

    #if __cplusplus >= 202002L || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)
      template <long double constant>
      struct $f final : public $c<long double, constant> {};
    #endif

    template <signed long long constant>
    struct $i final : public $c<signed long long, constant> {};

    template <void* constant>
    struct $p final : public $c<void*, constant> {};

    template <unsigned long long constant>
    struct $u final : public $c<unsigned long long, constant> {};
  #endif

// ...
template <std::size_t index, bool referrable>
struct $ final : public $expression<$nop, $<index, referrable> > {
  using $expression<$nop, $<index, referrable> >::$expression;
};
  #if defined(__clang__) || (defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER))
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
  #else
    constexpr static union {
      $<0u, false> $0;
      $<1u, false> $1;
      $<2u, false> $2;
      $<3u, false> $3;
      $<4u, false> $4;
      $<5u, false> $5;
      $<6u, false> $6;
      $<7u, false> $7;
      $<8u, false> $8;
      $<9u, false> $9;
    };
  #endif

/* ... */
template <$operation operation, class... expressions> constexpr $expression<$minus, $expression<operation, expressions...> > operator -($expression<operation, expressions...> const expression) noexcept { return {expression}; }

template <$operation operationA, class... expressionsA, $operation operationB, class... expressionsB> constexpr $expression<$add,         $expression<operationA, expressionsA...>, $expression<operationB, expressionsB...> > operator +($expression<operationA, expressionsA...> const expressionA, $expression<operationB, expressionsB...> const expressionB) noexcept { return {expressionA, expressionB}; }
template <$operation operationA, class... expressionsA, $operation operationB, class... expressionsB> constexpr $expression<$bitwise_and, $expression<operationA, expressionsA...>, $expression<operationB, expressionsB...> > operator &($expression<operationA, expressionsA...> const expressionA, $expression<operationB, expressionsB...> const expressionB) noexcept { return {expressionA, expressionB}; }
template <$operation operationA, class... expressionsA, $operation operationB, class... expressionsB> constexpr $expression<$comma,       $expression<operationA, expressionsA...>, $expression<operationB, expressionsB...> > operator ,($expression<operationA, expressionsA...> const expressionA, $expression<operationB, expressionsB...> const expressionB) noexcept { return {expressionA, expressionB}; }

template <$operation operation, class... expressions, typename type> constexpr $expression<$add,         $expression<operation, expressions...>, $expression<$nop, $capture<type&&> > > operator +($expression<operation, expressions...> const expression, type&& object) noexcept { return {expression, std::forward<type>(object)}; }
template <$operation operation, class... expressions, typename type> constexpr $expression<$add,         $expression<$nop, $capture<type&&> >, $expression<operation, expressions...> > operator +(type&& object, $expression<operation, expressions...> const expression) noexcept { return {std::forward<type>(object), expression}; }
template <$operation operation, class... expressions, typename type> constexpr $expression<$bitwise_and, $expression<operation, expressions...>, $expression<$nop, $capture<type&&> > > operator &($expression<operation, expressions...> const expression, type&& object) noexcept { return {expression, std::forward<type>(object)}; }
template <$operation operation, class... expressions, typename type> constexpr $expression<$bitwise_and, $expression<$nop, $capture<type&&> >, $expression<operation, expressions...> > operator &(type&& object, $expression<operation, expressions...> const expression) noexcept { return {std::forward<type>(object), expression}; }
template <$operation operation, class... expressions, typename type> constexpr $expression<$comma,       $expression<operation, expressions...>, $expression<$nop, $capture<type&&> > > operator ,($expression<operation, expressions...> const expression, type&& object) noexcept { return {expression, std::forward<type>(object)}; }
template <$operation operation, class... expressions, typename type> constexpr $expression<$comma,       $expression<$nop, $capture<type&&> >, $expression<operation, expressions...> > operator ,(type&& object, $expression<operation, expressions...> const expression) noexcept { return {std::forward<type>(object), expression}; }

template <typename type, typename... types, $operation operation, class... expressions> constexpr typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $capture<type (&)(types...)> >,      $expression<operation, expressions...> > >::type operator &(type (&function)(types...),       $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
template <typename type, typename... types, $operation operation, class... expressions> constexpr typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $capture<type (&)(types..., ...)> >, $expression<operation, expressions...> > >::type operator &(type (&function)(types..., ...),  $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
template <typename type, typename... types, $operation operation, class... expressions> constexpr typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $capture<type (&)(types...)> >,      $expression<operation, expressions...> > >::type operator &(type (&&function)(types...),      $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
template <typename type, typename... types, $operation operation, class... expressions> constexpr typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $capture<type (&)(types..., ...)> >, $expression<operation, expressions...> > >::type operator &(type (&&function)(types..., ...), $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
#ifdef __cpp_noexcept_function_type
  template <typename type, typename... types, $operation operation, class... expressions> constexpr typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $capture<type (&)(types...)      noexcept> >, $expression<operation, expressions...> > >::type operator &(type (&function)(types...)       noexcept, $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
  template <typename type, typename... types, $operation operation, class... expressions> constexpr typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $capture<type (&)(types..., ...) noexcept> >, $expression<operation, expressions...> > >::type operator &(type (&function)(types..., ...)  noexcept, $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
  template <typename type, typename... types, $operation operation, class... expressions> constexpr typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $capture<type (&)(types...)      noexcept> >, $expression<operation, expressions...> > >::type operator &(type (&&function)(types...)      noexcept, $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
  template <typename type, typename... types, $operation operation, class... expressions> constexpr typename std::enable_if<operation == $comma || operation == $nop, $expression<$call, $expression<$nop, $capture<type (&)(types..., ...) noexcept> >, $expression<operation, expressions...> > >::type operator &(type (&&function)(types..., ...) noexcept, $expression<operation, expressions...> const arguments) noexcept { return {function, arguments}; }
#endif
