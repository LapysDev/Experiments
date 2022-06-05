#include <cstddef>
#include <type_traits>
#include <utility>
#include <version>

#ifdef __clang__
# pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif

/* ... */
namespace {
  // --> pack<Ts...>
  template <typename...>
  struct pack final {};

  // --> assess_function<T>::type f(assess_function<T>::types..., assess_function<>::variadic);
  template <typename>
  struct assess_function;

  template <typename base, typename... bases> struct assess_function<base (*)              (bases...)>      final { typedef base type; typedef pack<bases...> types; static bool const variadic = false; };
  template <typename base, typename... bases> struct assess_function<base (*)              (bases..., ...)> final { typedef base type; typedef pack<bases...> types; static bool const variadic = true;  };
  template <typename base, typename... bases> struct assess_function<base (*const)         (bases...)>      final { typedef base type; typedef pack<bases...> types; static bool const variadic = false; };
  template <typename base, typename... bases> struct assess_function<base (*const)         (bases..., ...)> final { typedef base type; typedef pack<bases...> types; static bool const variadic = true;  };
  template <typename base, typename... bases> struct assess_function<base (*const volatile)(bases...)>      final { typedef base type; typedef pack<bases...> types; static bool const variadic = false; };
  template <typename base, typename... bases> struct assess_function<base (*const volatile)(bases..., ...)> final { typedef base type; typedef pack<bases...> types; static bool const variadic = true;  };
  template <typename base, typename... bases> struct assess_function<base (*volatile)      (bases...)>      final { typedef base type; typedef pack<bases...> types; static bool const variadic = false; };
  template <typename base, typename... bases> struct assess_function<base (*volatile)      (bases..., ...)> final { typedef base type; typedef pack<bases...> types; static bool const variadic = true;  };

  #ifdef __cpp_noexcept_function_type
    template <typename base, typename... bases> struct assess_function<base (*)              (bases...)      noexcept> final { typedef base type; typedef pack<bases...> types; static bool const variadic = false; };
    template <typename base, typename... bases> struct assess_function<base (*)              (bases..., ...) noexcept> final { typedef base type; typedef pack<bases...> types; static bool const variadic = true;  };
    template <typename base, typename... bases> struct assess_function<base (*const)         (bases...)      noexcept> final { typedef base type; typedef pack<bases...> types; static bool const variadic = false; };
    template <typename base, typename... bases> struct assess_function<base (*const)         (bases..., ...) noexcept> final { typedef base type; typedef pack<bases...> types; static bool const variadic = true;  };
    template <typename base, typename... bases> struct assess_function<base (*const volatile)(bases...)      noexcept> final { typedef base type; typedef pack<bases...> types; static bool const variadic = false; };
    template <typename base, typename... bases> struct assess_function<base (*const volatile)(bases..., ...) noexcept> final { typedef base type; typedef pack<bases...> types; static bool const variadic = true;  };
    template <typename base, typename... bases> struct assess_function<base (*volatile)      (bases...)      noexcept> final { typedef base type; typedef pack<bases...> types; static bool const variadic = false; };
    template <typename base, typename... bases> struct assess_function<base (*volatile)      (bases..., ...) noexcept> final { typedef base type; typedef pack<bases...> types; static bool const variadic = true;  };
  #endif

  // --> instanceof<T>()
  template <typename base>
  constexpr inline base instanceof() noexcept;

  // --> has_overloaded_addressof<T>::value
  template <typename, bool membered, typename = void> struct has_overloaded_addressof                                                                            final { static bool const value = false; };
  template <typename base>                            struct has_overloaded_addressof<base, false, decltype(static_cast<void>(operator &(instanceof<base>())))>  final { static bool const value = true;  };
  template <typename base>                            struct has_overloaded_addressof<base, true,  decltype(static_cast<void>(instanceof<base>().operator &()))> final { static bool const value = true;  };

  // --> collection<size_t...>
  template <std::size_t...>
  struct collection final {};

  // --> boolean_and<bool...>::value
  template <bool boolean, bool...>                          struct boolean_and                                  final { static bool const value = boolean; };
  template <bool booleanA, bool booleanB, bool... booleans> struct boolean_and<booleanA, booleanB, booleans...> final { static bool const value = boolean_and<booleanA && booleanB, booleans...>::value; };

  // --> addressof(...)
  template <typename base> constexpr inline typename std::enable_if<false == (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base& object)  noexcept { return &object; }
  template <typename base> constexpr inline typename std::enable_if<false == (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&& object) noexcept { return &static_cast<base&>(object); }

  template <typename base> inline typename std::enable_if<false != (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base& object)  noexcept { return const_cast<base*>(reinterpret_cast<base const volatile*>(&reinterpret_cast<unsigned char const volatile&>(object))); }
  template <typename base> inline typename std::enable_if<false != (has_overloaded_addressof<base, false>::value || has_overloaded_addressof<base, true>::value), base>::type* addressof(base&& object) noexcept { return const_cast<base*>(reinterpret_cast<base const volatile*>(&reinterpret_cast<unsigned char const volatile&>(static_cast<base&>(object)))); }

  template <typename base, std::size_t length> constexpr inline base (*addressof(base (&object)[length])  noexcept)[length] { return &object; }
  template <typename base, std::size_t length> constexpr inline base (*addressof(base (&&object)[length]) noexcept)[length] { return &static_cast<base (&)[length]>(object); }
}

/* ... ->> cast operations disallowed ie: `static_cast<int>($1) == [](auto n) { return static_cast<int>(n); }` */
template <std::size_t index, bool referenced = true>
struct $ {
  template <std::size_t, bool>
  friend struct $;

  private:
    template <std::size_t, typename...>                            struct typeat                        final { typedef struct $nil type; };
    template <typename base, typename... bases>                    struct typeat<1u,    base, bases...> final { typedef base type; };
    template <std::size_t count, typename base, typename... bases> struct typeat<count, base, bases...> final { typedef typename typeat<count - 1u, bases...>::type type; };

    /* ... */
    // ->> convert to function pointer
    template <bool variadic, typename type, typename... types>
    constexpr inline static typename std::enable_if<(index <= sizeof...(types)), typename std::conditional<variadic, type (*)(types..., ...) noexcept, type (*)(types...) noexcept>::type>::type cast(pack<types...> const) noexcept {
      return &$::template value<index, variadic, type, types...>::function;
    }

    // ->> interface for getting the value based on its `index`
    template <std::size_t count, typename... types>                constexpr inline static typename std::enable_if<count == 0u, typename std::conditional<(__cplusplus >= 201103L), void, int>::type>::type    invoke(types&&...)                 noexcept { return static_cast<typename std::conditional<(__cplusplus >= 201103L), void, int>::type>(0x0); }
    template <std::size_t count, typename type, typename... types> constexpr inline static typename std::enable_if<count == 1u, decltype(std::declval<type>())>::type                                          invoke(type&& object, types&&...)  noexcept { return std::forward<type>(object); }
    template <std::size_t count, typename type, typename... types> constexpr inline static typename std::enable_if<(count > 1u), decltype(std::declval<typename typeat<count, type, types...>::type>())>::type invoke(type&&, types&&... objects) noexcept { return $::template invoke<count - (1u != count)>(std::forward<types>(objects)...); }

    // ->> interface containing converted function (the user has to be wary of non-trivially copyable types)
    template <std::size_t, bool, typename, typename...>            struct value;
    template <std::size_t arity, typename type, typename... types> struct value<arity, false, type, types...> final { friend struct $; private: constexpr static type function(types... arguments) noexcept { return static_cast<type>($::template invoke<index>(arguments...)); } };
    template <std::size_t arity, typename type, typename... types> struct value<arity, true,  type, types...> final { friend struct $; private: constexpr static type function(types..., ...) noexcept = delete; };                          // ->> `delete`d because no way to forward the `va_arg`s
    template <typename type, typename... types>                    struct value<0u,    true,  type, types...> final { friend struct $; private: constexpr static type function(types..., ...) noexcept { return static_cast<void>(0x0); } }; // ->> `$0` does nothing with the `va_args`

  public:
    // ... ->> call `$`
    template <typename... types>
    constexpr decltype($::template invoke<index>(std::declval<types>()...)) operator ()(types&&... arguments) const volatile noexcept {
      return $::template invoke<index>(std::forward<types>(arguments)...);
    }

    // ... ->> cast `$` to its base function pointer
    template <typename type>
    constexpr explicit operator type() const volatile noexcept {
      return $::template cast<assess_function<type>::variadic, typename assess_function<type>::type>(typename assess_function<type>::types{});
    }
};

template <std::size_t index>
struct $<index, true> final : public $<index, false> {
  private:
    void* const instance;

  public:
    constexpr inline $() noexcept : instance(NULL) {}
    template <typename... types> constexpr inline $(types&&... arguments) noexcept : instance(const_cast<void*>(static_cast<void const volatile*>(addressof($::template invoke<index>(std::forward<types>(arguments)...))))) {}

    // ... ->> treat rvalue constructions as `$` calls
    template <typename type>
    constexpr operator type() const volatile&& noexcept {
      return *static_cast<typename std::enable_if<false == (std::is_function<typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value && std::is_pointer<typename std::remove_reference<type>::type>::value), typename std::remove_reference<type>::type*>::type>(this -> instance);
    }
};

enum $op : unsigned char {
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
  $dereference,
  $divide,
  $equals,
  $greater, $equals_greater,
  $left_shift,
  $lesser, $equals_lesser,
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

template <typename type>
struct $obj final {
  private:
    typename std::conditional<std::is_lvalue_reference<type>::value, type&, type&&>::type const reference;

  public:
    constexpr inline $obj($obj const& object) noexcept : reference(std::forward<type>(object.reference)) {}
    constexpr inline $obj(type&&      object) noexcept : reference(std::forward<type>(object))           {}

    /* ... */
    template <typename... types>
    constexpr inline typename std::conditional<std::is_lvalue_reference<type>::value, type&, type&&>::type operator ()(types&&...) const volatile noexcept {
      return static_cast<typename std::conditional<std::is_lvalue_reference<type>::value, type&, type&&>::type>(this -> reference);
    }
};

template <enum $op operation, class... expressions>
struct $expr final {
  template <enum $op subop, class...>
  friend struct $expr;

  private:
    template <unsigned char, class...>
    struct $ref final { // ->> Empty-base optimized where `arity` is expected to be `0u`
      template <enum $op subop, class...> friend struct $expr;
      template <unsigned char, class...> friend struct $ref;

      private:
        constexpr inline $ref($ref const&) noexcept {}
        template <typename... types> constexpr inline $ref(collection<> const, types&&...) noexcept {}
    };

    template <class subexpression>
    struct $ref<1u, subexpression> final {
      template <enum $op subop, class...> friend struct $expr;
      private:
        subexpression const operand;

        /* ... */
        constexpr inline $ref($ref const& reference) noexcept : operand(reference.operand) {}
        template <std::size_t index, typename... types> constexpr inline $ref(collection<index> const, types&&... operands) noexcept : operand($<index, false>{}(std::forward<types>(operands)...)) {}
    };

    template <class subexpressionA, class subexpressionB>
    struct $ref<2u, subexpressionA, subexpressionB> final {
      template <enum $op subop, class...> friend struct $expr;
      private:
        subexpressionA const operandA;
        subexpressionB const operandB;

        /* ... */
        constexpr inline $ref($ref const& reference) noexcept : operandA(reference.operandA), operandB(reference.operandB) {}
        template <std::size_t indexA, std::size_t indexB, typename... types> constexpr inline $ref(collection<indexA, indexB> const, types&&... operands) noexcept : operandA($<indexA, false>{}(std::forward<types>(operands)...)), operandB($<indexB, false>{}(std::forward<types>(operands)...)) {}
    };

    // ...
    template <class>                                                     struct is_referenced                                                   final { template <enum $op subop, class...> friend struct $expr; private: static bool const value = false; };
    template <enum $op suboperation, class subexpression, typename type> struct is_referenced<$expr<suboperation, $obj<type>, subexpression> >  final { template <enum $op subop, class...> friend struct $expr; private: static bool const value = true; };
    template <enum $op suboperation, class subexpression, typename type> struct is_referenced<$expr<suboperation, subexpression, $obj<type> > > final { template <enum $op subop, class...> friend struct $expr; private: static bool const value = true; };
    template <enum $op suboperation, class... subexpressions>            struct is_referenced<$expr<suboperation, subexpressions...> >          final { template <enum $op subop, class...> friend struct $expr; private: static bool const value = boolean_and<is_referenced<subexpressions>::value...>::value; };
    template <typename type>                                             struct is_referenced<$obj<type> >                                      final { template <enum $op subop, class...> friend struct $expr; private: static bool const value = true; };

    template <class, class...>                                                                        struct get_referenced;
    template <unsigned char arity, class... referenced>                                               struct get_referenced<$ref<arity, referenced...> >                                  final { friend struct $expr; private: typedef $ref<arity, referenced...> type; };
    template <unsigned char arity, class... referenced, class subexpression, class... subexpressions> struct get_referenced<$ref<arity, referenced...>, subexpression, subexpressions...> final { friend struct $expr; private: typedef typename std::conditional<is_referenced<subexpression>::value, typename get_referenced<$ref<arity + 1u, referenced..., subexpression>, subexpressions...>::type, typename get_referenced<$ref<arity, referenced...>, subexpressions...>::type>::type type; };
    template <std::size_t... indexes>                                                                 struct get_referenced<collection<indexes...> >                                      final { friend struct $expr; private: typedef collection<indexes...> type; };
    template <std::size_t... indexes, class subexpression, class... subexpressions>                   struct get_referenced<collection<indexes...>, subexpression, subexpressions...>     final { friend struct $expr; private: typedef typename std::conditional<is_referenced<subexpression>::value, typename get_referenced<collection<indexes..., sizeof...(expressions) - sizeof...(subexpressions)>, subexpressions...>::type, typename get_referenced<collection<indexes...>, subexpressions...>::type>::type type; };

    template <std::size_t, class...>                         struct expressionat                        final { template <enum $op subop, class...> friend struct $expr; private: typedef struct $nil type; };
    template <class base, class... bases>                    struct expressionat<0u,    base, bases...> final { template <enum $op subop, class...> friend struct $expr; private: typedef base type; };
    template <std::size_t count, class base, class... bases> struct expressionat<count, base, bases...> final { template <enum $op subop, class...> friend struct $expr; private: typedef typename expressionat<count - 1u, bases...>::type type; };

    /* ... */
    static unsigned char const arity = operation == $add || operation == $assign || operation == $assign_add || operation == $assign_bitwise_and || operation == $assign_bitwise_or || operation == $assign_bitwise_xor || operation == $assign_divide || operation == $assign_left_shift || operation == $assign_modulo || operation == $assign_multiply || operation == $assign_right_shift || operation == $assign_subtract || operation == $bitwise_and || operation == $bitwise_or || operation == $bitwise_xor || operation == $boolean_and || operation == $boolean_or || operation == $comma || operation == $compare || operation == $divide || operation == $equals || operation == $equals_greater || operation == $equals_lesser || operation == $greater || operation == $left_shift || operation == $lesser || operation == $member_access || operation == $member_pointer_access || operation == $modulo || operation == $multiply || operation == $right_shift || operation == $subscript || operation == $subtract || operation == $unequals ? 2u : operation == $address || operation == $complement || operation == $dereference || operation == $minus || operation == $negate || operation == $plus || operation == $post_decrement || operation == $post_increment || operation == $pre_decrement || operation == $pre_increment ? 1u : 0u;
    typename get_referenced<$ref<0u>, expressions...>::type const operands;

    /* ... */
    // ->> convert to function pointer
    template <bool variadic, typename type, typename... types>
    constexpr inline static typename std::conditional<variadic, type (*)(types..., ...) noexcept, type (*)(types...) noexcept>::type cast(pack<types...> const) noexcept {
      return &$expr::template value<arity, variadic, type, types...>::function;
    }

    // ->> `operation == ...` to add more operations
    template <typename typeA, typename typeB, typename... types>
    constexpr inline static typename std::enable_if<operation == $add, decltype(std::declval<typeA>()(std::declval<types>()...) + std::declval<typeB>()(std::declval<types>()...))>::type invoke(typeA&& expressionA, typeB&& expressionB, types&&... arguments) noexcept {
      return std::forward<typeA>(expressionA)(std::forward<types>(arguments)...) + std::forward<typeB>(expressionB)(std::forward<types>(arguments)...);
    }

    template <typename type, typename... types>
    constexpr inline static typename std::enable_if<operation == $minus, decltype(+std::declval<type>()(std::declval<types>()...))>::type invoke(type&& expression, types&&... arguments) noexcept {
      return -std::forward<type>(expression)(std::forward<types>(arguments)...);
    }

    // ->> interface containing converted function (the user has to be wary of non-trivially copyable types)
    template <unsigned char, bool, typename type, typename... types> struct value;
    template <typename type, typename... types>                      struct value<1u, false, type, types...>   final { friend struct $expr; private: constexpr static type function(types... arguments) noexcept { return static_cast<type>($expr::invoke(typename expressionat<0u, expressions...>::type{},                                                    static_cast<types>(arguments)...)); } };
    template <typename type, typename... types>                      struct value<2u, false, type, types...>   final { friend struct $expr; private: constexpr static type function(types... arguments) noexcept { return static_cast<type>($expr::invoke(typename expressionat<0u, expressions...>::type{}, typename expressionat<1u, expressions...>::type{}, static_cast<types>(arguments)...)); } };
    template <unsigned char arity, typename type, typename... types> struct value<arity, true, type, types...> final { friend struct $expr; private: constexpr static type function(types..., ...) noexcept = delete; };

  public:
    template <typename... types>
    constexpr inline $expr(types&&... ops) noexcept : operands(typename get_referenced<collection<>, expressions...>::type{}, std::forward<types>(ops)...) {}

    /* ... */
    // ->> call `$expr`
    template <typename... types> constexpr inline typename std::enable_if<arity == 1u && false != is_referenced<typename expressionat<0u, expressions...>::type>::value,                                                                                   decltype($expr::invoke(instanceof<typename expressionat<0u, expressions...>::type const volatile&>(),                                                                                std::declval<types>()...))>::type operator ()(types&&... arguments) const volatile noexcept { return $expr::invoke(this -> operands.operand,                                                                             std::forward<types>(arguments)...); }
    template <typename... types> constexpr inline typename std::enable_if<arity == 1u && false == is_referenced<typename expressionat<0u, expressions...>::type>::value,                                                                                   decltype($expr::invoke(instanceof<typename expressionat<0u, expressions...>::type&&>(),                                                                                              std::declval<types>()...))>::type operator ()(types&&... arguments) const volatile noexcept { return $expr::invoke(typename expressionat<0u, expressions...>::type{},                                                    std::forward<types>(arguments)...); }
    template <typename... types> constexpr inline typename std::enable_if<arity == 2u && false != is_referenced<typename expressionat<0u, expressions...>::type>::value && false != is_referenced<typename expressionat<1u, expressions...>::type>::value, decltype($expr::invoke(instanceof<typename expressionat<0u, expressions...>::type const volatile&>(), instanceof<typename expressionat<1u, expressions...>::type const volatile&>(), std::declval<types>()...))>::type operator ()(types&&... arguments) const volatile noexcept { return $expr::invoke(this -> operands.operandA,                         this -> operands.operandB,                         std::forward<types>(arguments)...); }
    template <typename... types> constexpr inline typename std::enable_if<arity == 2u && false != is_referenced<typename expressionat<0u, expressions...>::type>::value && false == is_referenced<typename expressionat<1u, expressions...>::type>::value, decltype($expr::invoke(instanceof<typename expressionat<0u, expressions...>::type const volatile&>(), instanceof<typename expressionat<1u, expressions...>::type&&>(),               std::declval<types>()...))>::type operator ()(types&&... arguments) const volatile noexcept { return $expr::invoke(this -> operands.operand,                          typename expressionat<1u, expressions...>::type{}, std::forward<types>(arguments)...); }
    template <typename... types> constexpr inline typename std::enable_if<arity == 2u && false == is_referenced<typename expressionat<0u, expressions...>::type>::value && false != is_referenced<typename expressionat<1u, expressions...>::type>::value, decltype($expr::invoke(instanceof<typename expressionat<0u, expressions...>::type&&>(),               instanceof<typename expressionat<1u, expressions...>::type const volatile&>(), std::declval<types>()...))>::type operator ()(types&&... arguments) const volatile noexcept { return $expr::invoke(typename expressionat<0u, expressions...>::type{}, this -> operands.operand,                          std::forward<types>(arguments)...); }
    template <typename... types> constexpr inline typename std::enable_if<arity == 2u && false == is_referenced<typename expressionat<0u, expressions...>::type>::value && false == is_referenced<typename expressionat<1u, expressions...>::type>::value, decltype($expr::invoke(instanceof<typename expressionat<0u, expressions...>::type&&>(),               instanceof<typename expressionat<1u, expressions...>::type&&>(),               std::declval<types>()...))>::type operator ()(types&&... arguments) const volatile noexcept { return $expr::invoke(typename expressionat<0u, expressions...>::type{}, typename expressionat<1u, expressions...>::type{}, std::forward<types>(arguments)...); }
  
    // ->> cast `$expr` to its base function pointer
    template <typename type>
    constexpr explicit operator type() const volatile noexcept {
      return $expr::template cast<assess_function<type>::variadic, typename assess_function<type>::type>(typename assess_function<type>::types{});
    }
};

template <>
struct $expr<$nop> final {
  struct $func final {
    void (*function)(...) noexcept;
  };

  void *FUNCTIONS;
};

/* ... */
template <enum $op operation, class... expressions> constexpr inline $expr<$minus, $expr<operation, expressions...> > operator -($expr<operation, expressions...> const volatile expression) noexcept { return {const_cast<$expr<operation, expressions...> const&>(expression)}; }
template <std::size_t index, bool referenced>       constexpr inline $expr<$minus, $<index, referenced>             > operator -($<index, referenced>             const volatile unit)       noexcept { return {const_cast<$<index, referenced> const&>(unit)}; }

template <enum $op operationA, class... expressionsA, enum $op operationB, class... expressionsB> constexpr inline $expr<$add, $expr<operationA, expressionsA...>, $expr<operationB, expressionsB...> > operator +($expr<operationA, expressionsA...> const volatile expressionA, $expr<operationB, expressionsB...> const volatile expressionB) noexcept { return {const_cast<$expr<operationA, expressionsA...> const&>(expressionA), const_cast<$expr<operationB, expressionsB...> const&>(expressionB)}; }
template <enum $op operation, class... expressions, std::size_t index, bool referenced>           constexpr inline $expr<$add, $expr<operation, expressions...>,   $<index, referenced>               > operator +($expr<operation, expressions...>   const volatile expression,  $<index, referenced>               const volatile unit)        noexcept { return {const_cast<$expr<operation, expressions...> const&>(expression), const_cast<$<index, referenced> const&>(unit)}; }
template <enum $op operation, class... expressions, typename type>                                constexpr inline $expr<$add, $expr<operation, expressions...>,   $obj<type>                         > operator +($expr<operation, expressions...>   const volatile expression,  type&&                                            object)      noexcept { return {const_cast<$expr<operation, expressions...> const&>(expression), std::forward<type>(object)}; }
template <std::size_t index, bool referenced, enum $op operation, class... expressions>           constexpr inline $expr<$add, $<index, referenced>,               $expr<operation, expressions...>   > operator +($<index, referenced>               const volatile unit,        $expr<operation, expressions...>   const volatile expression)  noexcept { return {const_cast<$<index, referenced> const&>(unit), expression}; }
template <std::size_t indexA, bool referencedA, std::size_t indexB, bool referencedB>             constexpr inline $expr<$add, $<indexA, referencedA>,             $<indexB, referencedB>             > operator +($<indexA, referencedA>             const volatile unitA,       $<indexB, referencedB>             const volatile unitB)       noexcept { return {const_cast<$<indexA, referencedA> const&>(unitA), const_cast<$<indexB, referencedB> const&>(unitB)}; }
template <std::size_t index, bool referenced, typename type>                                      constexpr inline $expr<$add, $<index, referenced>,               $obj<type>                         > operator +($<index, referenced>               const volatile unit,        type&&                                            object)      noexcept { return $expr<$add, $<index, referenced>, $obj<type> >(const_cast<$<index, referenced> const&>(unit), std::forward<type>(object)); }
template <enum $op operation, class... expressions, typename type>                                constexpr inline $expr<$add, $obj<type>,                         $expr<operation, expressions...>   > operator +(type&&                                            object,      $expr<operation, expressions...>   const volatile expression)  noexcept { return {std::forward<type>(object), const_cast<$expr<operation, expressions...> const&>(expression)}; }
template <std::size_t index, bool referenced, typename type>                                      constexpr inline $expr<$add, $obj<type>,                         $<index, referenced>               > operator +(type&&                                            object,      $<index, referenced>               const volatile unit)        noexcept { return {std::forward<type>(object), const_cast<$<index, referenced> const&>(unit)}; }

/* ... */
#if defined(__clang__) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
  constexpr static $<0u, false> $0 {};
  constexpr static $<1u, false> $1 {};
  constexpr static $<2u, false> $2 {};
  constexpr static $<3u, false> $3 {};
#else
  constexpr static union {
    $<0u, false> $0;
    $<1u, false> $1;
    $<2u, false> $2;
    $<3u, false> $3;
  };
#endif
