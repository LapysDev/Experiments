#include <cstddef>
#include <type_traits>
#include <utility>
#include <version>

#ifdef __clang__
# pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif

/* ... */
namespace {
  template <bool boolean, bool...>                          struct boolean_or                                  final { static bool const value = boolean; };
  template <bool booleanA, bool booleanB, bool... booleans> struct boolean_or<booleanA, booleanB, booleans...> final { static bool const value = boolean_or<booleanA || booleanB, booleans...>::value; };

  // ...
  template <typename base, typename = base> struct can_default_initialize                         final { static bool const value = false; };
  template <typename base>                  struct can_default_initialize<base, decltype(base())> final { static bool const value = true; };

  // ...
  template <std::size_t...>
  struct collection final {};

  // ...
  template <typename base>
  constexpr inline base instanceof() noexcept;

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
  };
}

namespace {
  template <typename base> constexpr inline typename std::enable_if<false == (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&  object) noexcept { return &object; }
  template <typename base> constexpr inline typename std::enable_if<false == (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&& object) noexcept { return &static_cast<base&>(object); }

  template <typename base> inline typename std::enable_if<false != (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&  object) noexcept { return const_cast<base*>(reinterpret_cast<base const volatile*>(&reinterpret_cast<unsigned char const volatile&>(object))); }
  template <typename base> inline typename std::enable_if<false != (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&& object) noexcept { return const_cast<base*>(reinterpret_cast<base const volatile*>(&reinterpret_cast<unsigned char const volatile&>(static_cast<base&>(object)))); }

  template <typename base, std::size_t length> constexpr inline base (*addressof(base (&object)[length])  noexcept)[length] { return &object; }
  template <typename base, std::size_t length> constexpr inline base (*addressof(base (&&object)[length]) noexcept)[length] { return &static_cast<base (&)[length]>(object); }
}

/* ... */
struct $function;
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

template <std::size_t, bool = true> struct $;
template <$operation, class...>     struct $expression;
template <typename>                 struct $object;

/* ... */
template <>
struct $<0u, false> final {
  template <std::size_t, bool>
  friend struct $;

  private:
    template <std::size_t, typename>
    struct cast;

    template <std::size_t index, typename type, typename... types>
    struct cast<index, type (types...) noexcept> final {
      template <std::size_t, bool> friend struct $;
      private: constexpr static type value(types... arguments) noexcept { return static_cast<type>($<0u, false>::template invoke<index>(std::forward<types>(arguments)...)); }
    };

    template <typename type, typename... types>
    struct cast<0u, type (types..., ...) noexcept> final {
      template <std::size_t, bool> friend struct $;
      private: constexpr static type value(types... arguments, ...) noexcept { return static_cast<type>($<0u, false>::template invoke<0u>(std::forward<types>(arguments)...)); }
    };

    #ifdef __cpp_noexcept_function_type
      template <std::size_t index, typename type, typename... types>
      struct cast<index, type (types...)> final {
        template <std::size_t, bool> friend struct $;
        private: constexpr static type value(types... arguments) { return static_cast<type>($<0u, false>::template invoke<index>(std::forward<types>(arguments)...)); }
      };

      template <typename type, typename... types>
      struct cast<0u, type (types..., ...)> final {
        template <std::size_t, bool> friend struct $;
        private: constexpr static type value(types... arguments, ...) { return static_cast<type>($<0u, false>::template invoke<0u>(std::forward<types>(arguments)...)); }
      };
    #endif

    // ...
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
      return $<0u, false>::template invoke<0u, type>();
    }

    template <std::size_t count, typename type, typename... types>
    constexpr inline static typename std::enable_if<count == 1u, type&&>::type invoke(type&& object, types&&...) noexcept {
      return std::forward<type>(object);
    }

    template <std::size_t count, typename type, typename... types>
    constexpr inline static typename std::enable_if<(count > 1u), typename pack<type&&, types&&...>::template at<(count > 1u ? count - 1u : 0u)>::type>::type invoke(type&&, types&&... objects) noexcept {
      return $<0u, false>::template invoke<count - 1u>(std::forward<types>(objects)...);
    }

  public:
    template <typename... types>
    constexpr decltype($<0u, false>::template invoke<0u>(std::declval<types>()...)) operator ()(types&&... arguments) const volatile noexcept {
      return $<0u, false>::template invoke<0u>(std::forward<types>(arguments)...);
    }

    template <typename type>
    constexpr inline operator type() const volatile noexcept {
      return $<0u, false>::template cast<0u, typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value;
    }
};

template <std::size_t index, bool>
struct $ final {
  private:
    constexpr friend $expression<$cast, $> as($ const unit) noexcept {
      return {unit};
    }

  public:
    template <typename... types>
    constexpr typename pack<types&&...>::template at<index - 1u>::type operator ()(types&&... arguments) const volatile noexcept {
      return $<0u, false>::template invoke<index>(std::forward<types>(arguments)...);
    }

    template <typename type>
    constexpr inline operator type() const volatile noexcept {
      return $<0u, false>::template cast<index, typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value;
    }
};

template <>
struct $<0u, true> final {
  template <typename... types>
  constexpr inline $(types&&...) noexcept {}

  /* ... */
  template <typename... types>
  constexpr inline decltype($<0u, false>::template invoke<0u>(std::declval<types>()...)) operator ()(types&&... arguments) const volatile noexcept {
    return $<0u, false>::template invoke<0u>(std::forward<types>(arguments)...);
  }

  template <typename type>
  constexpr inline operator type() const volatile noexcept {
    return $<0u, false>::template invoke<0u, type>();
  }
};

template <std::size_t index>
struct $<index, true> final {
  private:
    void *const reference;

  public:
    constexpr $() noexcept :
      reference(NULL)
    {}

    template <std::size_t subindex, bool referrable>
    constexpr inline $($<subindex, referrable> const volatile& unit) noexcept :
      reference(static_cast<typename std::enable_if<(index >= subindex), void*>::type>(unit.reference))
    {}

    template <std::size_t subindex, bool referrable>
    constexpr inline $($<subindex, referrable> const volatile&& unit) noexcept :
      reference(static_cast<typename std::enable_if<(index >= subindex), void*>::type>(unit.reference))
    {}

    template <typename... types>
    constexpr inline $(types&&... objects) noexcept :
      reference(const_cast<void*>(static_cast<void const volatile*>(addressof($<0u, false>::template invoke<index>(std::forward<types>(objects)...)))))
    {}

    /* ... */
    template <typename... types>
    constexpr decltype($<0u, false>::template invoke<index>(std::declval<types>()...)) operator ()(types&&... arguments) const volatile noexcept {
      return $<0u, false>::template invoke<index>(std::forward<types>(arguments)...);
    }

    template <typename type>
    constexpr inline operator type() const volatile noexcept {
      return static_cast<type>(*static_cast<typename std::remove_reference<type>::type*>(this -> reference));
    }
};
  #if defined(__clang__) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
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
  #else
    #if defined(_MSC_VER)
    # pragma warning(disable: 4172)
    #endif

    constexpr static union {
      $<0u, false> $0;
      $<1u, false> $1;
      $<2u, false> $2;
      $<3u, false> $3;
      $<3u, false> $4;
      $<3u, false> $5;
      $<3u, false> $6;
      $<3u, false> $7;
      $<3u, false> $8;
      $<3u, false> $9;
    };
  #endif

template <>
struct $expression<$nop> final {
  template <$operation, class...>
  friend struct $expression;

  private:
    template <class... subexpressions>
    struct $operands {
      template <$operation, class...>
      friend struct $expression;

      private:
        template <std::size_t index>
        constexpr typename pack<subexpressions...>::template at<index>::type operator []($<index, false> const) const noexcept;
    };

    template <class subexpression, class... subexpressions>
    struct $operands<subexpression, subexpressions...> : public $operands<subexpressions...> {
      template <$operation, class...>
      friend struct $expression;

      private:
        subexpression const value;

        /* ... */
        constexpr inline $operands() noexcept :
          $operands<subexpressions...>::$operands(),
          value()
        {}

        constexpr inline $operands(subexpression const& operand, subexpressions const&... operands) noexcept :
          $operands<subexpressions...>::$operands(operands...),
          value(operand)
        {}

      protected:
        constexpr inline subexpression const& operator []($<0u, false> const) const noexcept {
          return this -> value;
        }

        template <std::size_t index>
        constexpr inline typename pack<subexpression, subexpressions...>::template at<index>::type const& operator []($<index, false> const) const noexcept {
          return this -> $operands<subexpressions...>::operator []($<index - 1u, false>{});
        }
    };

    // ...
    template <class expression>                              struct is_referrable                                             final { static bool const value = false; };
    template <$operation operation, class... subexpressions> struct is_referrable<$expression<operation, subexpressions...> > final { static bool const value = boolean_or<is_referrable<subexpressions>::value...>::value; };
    template <typename type>                                 struct is_referrable<$object<type> >                             final { static bool const value = true; };

    // ...
    template <class $expression, typename, bool = is_referrable<$expression>::value>
    struct cast;

    template <$operation operation, class... subexpressions, typename type, typename... types>
    struct cast<$expression<operation, subexpressions...>, type (types...) noexcept, false> final {
      friend struct $expression<operation, subexpressions...>;
      private: constexpr static type value(types... arguments) noexcept { return $expression<$nop>::template invoke<operation>($expression<operation, subexpressions...>().value, std::forward<types>(arguments)...); }
    };

    #ifdef __cpp_noexcept_function_type
      template <$operation operation, class... subexpressions, typename type, typename... types>
      struct cast<$expression<operation, subexpressions...>, type (types...), false> final {
        friend struct $expression<operation, subexpressions...>;
        private: constexpr static type value(types... arguments) { return $expression<$nop>::template invoke<operation>($expression<operation, subexpressions...>().value, std::forward<types>(arguments)...); }
      };
    #endif

    /* ... */
    template <$operation operation, class $operands, class... types>
    constexpr inline static typename std::enable_if<operation == $minus, decltype(-std::declval<$operands>()[$0](std::declval<types>()...))>::type invoke($operands const& operands, types&&... arguments) noexcept {
      return -operands[$0](std::forward<types>(arguments)...);
    }
};

template <$operation operation, class... subexpressions>
struct $expression final {
  template <class, typename, bool> friend struct $expression<$nop>::cast;
  template <class...>              friend struct $expression<$nop>::$operands;

  private:
    $expression<$nop>::$operands<subexpressions...> const value;

    /* ... */
    constexpr inline $expression() noexcept :
      value()
    {}

  public:
    constexpr inline $expression(subexpressions const&... operands) noexcept :
      value(operands...)
    {}

    /* ... */
    template <typename... types>
    constexpr inline decltype($expression<$nop>::template invoke<operation>(std::declval<$expression<$nop>::$operands<subexpressions...> >(), std::declval<types>()...)) operator ()(types&&... arguments) const noexcept {
      return $expression<$nop>::template invoke<operation>(this -> value, std::forward<types>(arguments)...);
    }

    template <typename type>
    constexpr inline operator type() const volatile noexcept {
      return $expression<$nop>::template cast<$expression, typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value;
    }
};

struct $function final {
  static void *BUFFER;
};

/* ... */
template <std::size_t index, bool referrable>            constexpr $expression<$minus, $<index, false> >                           operator -($<index, referrable>                      const)            noexcept { return {$<index, false>{}}; }
template <$operation operation, class... subexpressions> constexpr $expression<$minus, $expression<operation, subexpressions...> > operator -($expression<operation, subexpressions...> const expression) noexcept { return {expression}; }
