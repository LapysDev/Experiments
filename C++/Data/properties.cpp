#include <cstdio>
#include <type_traits>
#include <utility>

/* ... */
#ifndef __cpp_constexpr
# define constfunc(relaxed)
#elif __cplusplus < 201402L
# define constfunc(unrelaxed) constfunc_ ## unrelaxed
#   define constfunc_false constexpr
#   define constfunc_true
#else
# define constfunc(unrelaxed) constexpr
#endif

/* ... */
namespace {
  template <typename type>
  constexpr inline static type instanceof() noexcept;

  // ...
  template <typename type>
  struct alias final {};

  // ...
  struct invalid final {
    // inline invalid(...) noexcept(false) { throw 0; }
    constexpr inline invalid(...) noexcept = delete;
  };

  // ...
  enum operation : unsigned char {
    add,
    address,
    assign,
    assign_add,
    assign_bitwise_and,
    assign_bitwise_or,
    assign_bitwise_xor,
    assign_divide,
    assign_left_shift,
    assign_modulo,
    assign_multiply,
    assign_right_shift,
    assign_subtract,
    bitwise_and,
    bitwise_or,
    bitwise_xor,
    boolean_and,
    boolean_or,
    call,
    cast,
    comma,
    compare,
    complement,
    dereference,
    divide,
    equals,
    greater, equals_greater,
    left_shift,
    lesser,  equals_lesser,
    member_access,
    member_pointer_access,
    minus,
    modulo,
    multiply,
    negate,
    plus,
    post_decrement,
    post_increment,
    pre_decrement,
    pre_increment,
    right_shift,
    subscript,
    subtract,
    unequals
  };

  // ...
  template <typename...>
  struct pack final {};
}

namespace {
  template <unsigned char /* operation */, class /* arguments */, typename = alias<void> >
  struct assess_operation final { typedef invalid type; static bool const value = false; };

  template <typename typeA, typename typeB>    struct assess_operation<add,                pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() + instanceof<typeB>()))> >   final { typedef decltype(instanceof<typeA>() + instanceof<typeB>())   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign,             pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() = instanceof<typeB>()))> >   final { typedef decltype(instanceof<typeA>() = instanceof<typeB>())   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_add,         pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() += instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() += instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_bitwise_and, pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() &= instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() &= instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_bitwise_or,  pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() |= instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() |= instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_bitwise_xor, pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() ^= instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() ^= instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_divide,      pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() /= instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() /= instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_left_shift,  pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() <<= instanceof<typeB>()))> > final { typedef decltype(instanceof<typeA>() <<= instanceof<typeB>()) type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_modulo,      pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() %= instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() %= instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_multiply,    pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() *= instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() *= instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_right_shift, pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() >>= instanceof<typeB>()))> > final { typedef decltype(instanceof<typeA>() >>= instanceof<typeB>()) type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_subtract,    pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() -= instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() -= instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<bitwise_and,        pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() & instanceof<typeB>()))> >   final { typedef decltype(instanceof<typeA>() & instanceof<typeB>())   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<bitwise_or,         pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() | instanceof<typeB>()))> >   final { typedef decltype(instanceof<typeA>() | instanceof<typeB>())   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<bitwise_xor,        pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() ^ instanceof<typeB>()))> >   final { typedef decltype(instanceof<typeA>() ^ instanceof<typeB>())   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<boolean_and,        pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() && instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() && instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<boolean_or,         pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() || instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() || instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<cast,               pack<typeA, typeB>,    alias<decltype(static_cast<void>(static_cast<typeB>(instanceof<typeA>())))> >     final { typedef decltype(static_cast<typeB>(instanceof<typeA>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<comma,              pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>(), instanceof<typeB>()))> >    final { typedef decltype(instanceof<typeA>(), instanceof<typeB>())    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<divide,             pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() / instanceof<typeB>()))> >   final { typedef decltype(instanceof<typeA>() / instanceof<typeB>())   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<equals,             pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() == instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() == instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<equals_greater,     pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() >= instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() >= instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<equals_lesser,      pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() <= instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() <= instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<greater,            pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() > instanceof<typeB>()))> >   final { typedef decltype(instanceof<typeA>() > instanceof<typeB>())   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<left_shift,         pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() << instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() << instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<lesser,             pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() < instanceof<typeB>()))> >   final { typedef decltype(instanceof<typeA>() < instanceof<typeB>())   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<modulo,             pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() % instanceof<typeB>()))> >   final { typedef decltype(instanceof<typeA>() % instanceof<typeB>())   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<multiply,           pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() * instanceof<typeB>()))> >   final { typedef decltype(instanceof<typeA>() * instanceof<typeB>())   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<right_shift,        pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() >> instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() >> instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<subscript,          pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>()[instanceof<typeB>()]))> >    final { typedef decltype(instanceof<typeA>()[instanceof<typeB>()])    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<subtract,           pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() - instanceof<typeB>()))> >   final { typedef decltype(instanceof<typeA>() - instanceof<typeB>())   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<unequals,           pack<typeA, typeB>,    alias<decltype(static_cast<void>(instanceof<typeA>() != instanceof<typeB>()))> >  final { typedef decltype(instanceof<typeA>() != instanceof<typeB>())  type; static bool const value = true; };
  template <typename typeA, typename... types> struct assess_operation<call,               pack<typeA, types...>, alias<decltype(static_cast<void>(instanceof<typeA>()(instanceof<types>()...)))> > final { typedef decltype(instanceof<typeA>()(instanceof<types>()...)) type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<address,            pack<typeA>,           alias<decltype(static_cast<void>(&instanceof<typeA>()))> >                        final { typedef decltype(&instanceof<typeA>())                        type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<complement,         pack<typeA>,           alias<decltype(static_cast<void>(~instanceof<typeA>()))> >                        final { typedef decltype(~instanceof<typeA>())                        type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<dereference,        pack<typeA>,           alias<decltype(static_cast<void>(*instanceof<typeA>()))> >                        final { typedef decltype(*instanceof<typeA>())                        type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<minus,              pack<typeA>,           alias<decltype(static_cast<void>(-instanceof<typeA>()))> >                        final { typedef decltype(-instanceof<typeA>())                        type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<negate,             pack<typeA>,           alias<decltype(static_cast<void>(!instanceof<typeA>()))> >                        final { typedef decltype(!instanceof<typeA>())                        type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<plus,               pack<typeA>,           alias<decltype(static_cast<void>(+instanceof<typeA>()))> >                        final { typedef decltype(+instanceof<typeA>())                        type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<post_decrement,     pack<typeA>,           alias<decltype(static_cast<void>(instanceof<typeA>()--))> >                       final { typedef decltype(instanceof<typeA>()--)                       type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<post_increment,     pack<typeA>,           alias<decltype(static_cast<void>(instanceof<typeA>()++))> >                       final { typedef decltype(instanceof<typeA>()++)                       type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<pre_decrement,      pack<typeA>,           alias<decltype(static_cast<void>(--instanceof<typeA>()))> >                       final { typedef decltype(--instanceof<typeA>())                       type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<pre_increment,      pack<typeA>,           alias<decltype(static_cast<void>(++instanceof<typeA>()))> >                       final { typedef decltype(++instanceof<typeA>())                       type; static bool const value = true; };

  // ...
  template <typename type, typename... types> constfunc(true) inline static typename std::enable_if<assess_operation<call,                  pack<type&&, types&&...> >::value, typename assess_operation<call,                  pack<type&&, types&&...> >::type>::type operate_call(type&& object, types&&... objects)                 noexcept(noexcept(std::declval<type>()(std::declval<types>()...)))  { return static_cast<typename assess_operation<call,                  pack<type&&, types&&...> >::type>(std::forward<type>(object)(std::forward<types>(objects)...)); }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<assess_operation<address,               pack<type&&> >            ::value, typename assess_operation<address,               pack<type&&> >            ::type>::type operate_address(type&& object)                                  noexcept(noexcept(&std::declval<type>()))                           { return static_cast<typename assess_operation<address,               pack<type&&> >            ::type>(&std::forward<type>(object)); }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<assess_operation<complement,            pack<type&&> >            ::value, typename assess_operation<complement,            pack<type&&> >            ::type>::type operate_complement(type&& object)                               noexcept(noexcept(~std::declval<type>()))                           { return static_cast<typename assess_operation<complement,            pack<type&&> >            ::type>(~std::forward<type>(object)); }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<assess_operation<dereference,           pack<type&&> >            ::value, typename assess_operation<dereference,           pack<type&&> >            ::type>::type operate_dereference(type&& object)                              noexcept(noexcept(*std::declval<type>()))                           { return static_cast<typename assess_operation<dereference,           pack<type&&> >            ::type>(*std::forward<type>(object)); }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<assess_operation<member_access,         pack<type&&> >            ::value, typename assess_operation<member_access,         pack<type&&> >            ::type>::type operate_member_access(type&& object)                            noexcept                                                            { return static_cast<typename assess_operation<member_access,         pack<type&&> >            ::type>(std::forward<type>(object)); }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<assess_operation<minus,                 pack<type&&> >            ::value, typename assess_operation<minus,                 pack<type&&> >            ::type>::type operate_minus(type&& object)                                    noexcept(noexcept(-std::declval<type>()))                           { return static_cast<typename assess_operation<minus,                 pack<type&&> >            ::type>(-std::forward<type>(object)); }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<assess_operation<negate,                pack<type&&> >            ::value, typename assess_operation<negate,                pack<type&&> >            ::type>::type operate_negate(type&& object)                                   noexcept(noexcept(!std::declval<type>()))                           { return static_cast<typename assess_operation<negate,                pack<type&&> >            ::type>(!std::forward<type>(object)); }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<assess_operation<plus,                  pack<type&&> >            ::value, typename assess_operation<plus,                  pack<type&&> >            ::type>::type operate_plus(type&& object)                                     noexcept(noexcept(+std::declval<type>()))                           { return static_cast<typename assess_operation<plus,                  pack<type&&> >            ::type>(+std::forward<type>(object)); }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<assess_operation<post_decrement,        pack<type&&> >            ::value, typename assess_operation<post_decrement,        pack<type&&> >            ::type>::type operate_post_decrement(type&& object)                           noexcept(noexcept(std::declval<type>()--))                          { return static_cast<typename assess_operation<post_decrement,        pack<type&&> >            ::type>(std::forward<type>(object)--); }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<assess_operation<post_increment,        pack<type&&> >            ::value, typename assess_operation<post_increment,        pack<type&&> >            ::type>::type operate_post_increment(type&& object)                           noexcept(noexcept(std::declval<type>()++))                          { return static_cast<typename assess_operation<post_increment,        pack<type&&> >            ::type>(std::forward<type>(object)++); }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<assess_operation<pre_decrement,         pack<type&&> >            ::value, typename assess_operation<pre_decrement,         pack<type&&> >            ::type>::type operate_pre_decrement(type&& object)                            noexcept(noexcept(--std::declval<type>()))                          { return static_cast<typename assess_operation<pre_decrement,         pack<type&&> >            ::type>(--std::forward<type>(object)); }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<assess_operation<pre_increment,         pack<type&&> >            ::value, typename assess_operation<pre_increment,         pack<type&&> >            ::type>::type operate_pre_increment(type&& object)                            noexcept(noexcept(++std::declval<type>()))                          { return static_cast<typename assess_operation<pre_increment,         pack<type&&> >            ::type>(++std::forward<type>(object)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<add,                   pack<typeA&&, typeB&&> >  ::value, typename assess_operation<add,                   pack<typeA&&, typeB&&> >  ::type>::type operate_add(typeA&& objectA, typeB&& objectB)                   noexcept(noexcept(std::declval<typeA>() +   std::declval<typeB>())) { return static_cast<typename assess_operation<add,                   pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) +   std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<assign,                pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign,                pack<typeA&&, typeB&&> >  ::type>::type operate_assign(typeA&& objectA, typeB&& objectB)                noexcept(noexcept(std::declval<typeA>() =   std::declval<typeB>())) { return static_cast<typename assess_operation<assign,                pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) =   std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<assign_add,            pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_add,            pack<typeA&&, typeB&&> >  ::type>::type operate_assign_add(typeA&& objectA, typeB&& objectB)            noexcept(noexcept(std::declval<typeA>() +=  std::declval<typeB>())) { return static_cast<typename assess_operation<assign_add,            pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) +=  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<assign_bitwise_and,    pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_bitwise_and,    pack<typeA&&, typeB&&> >  ::type>::type operate_assign_bitwise_and(typeA&& objectA, typeB&& objectB)    noexcept(noexcept(std::declval<typeA>() &=  std::declval<typeB>())) { return static_cast<typename assess_operation<assign_bitwise_and,    pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) &=  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<assign_bitwise_or,     pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_bitwise_or,     pack<typeA&&, typeB&&> >  ::type>::type operate_assign_bitwise_or(typeA&& objectA, typeB&& objectB)     noexcept(noexcept(std::declval<typeA>() |=  std::declval<typeB>())) { return static_cast<typename assess_operation<assign_bitwise_or,     pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) |=  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<assign_bitwise_xor,    pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_bitwise_xor,    pack<typeA&&, typeB&&> >  ::type>::type operate_assign_bitwise_xor(typeA&& objectA, typeB&& objectB)    noexcept(noexcept(std::declval<typeA>() ^=  std::declval<typeB>())) { return static_cast<typename assess_operation<assign_bitwise_xor,    pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) ^=  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<assign_divide,         pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_divide,         pack<typeA&&, typeB&&> >  ::type>::type operate_assign_divide(typeA&& objectA, typeB&& objectB)         noexcept(noexcept(std::declval<typeA>() /=  std::declval<typeB>())) { return static_cast<typename assess_operation<assign_divide,         pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) /=  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<assign_left_shift,     pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_left_shift,     pack<typeA&&, typeB&&> >  ::type>::type operate_assign_left_shift(typeA&& objectA, typeB&& objectB)     noexcept(noexcept(std::declval<typeA>() <<= std::declval<typeB>())) { return static_cast<typename assess_operation<assign_left_shift,     pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) <<= std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<assign_modulo,         pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_modulo,         pack<typeA&&, typeB&&> >  ::type>::type operate_assign_modulo(typeA&& objectA, typeB&& objectB)         noexcept(noexcept(std::declval<typeA>() %=  std::declval<typeB>())) { return static_cast<typename assess_operation<assign_modulo,         pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) %=  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<assign_multiply,       pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_multiply,       pack<typeA&&, typeB&&> >  ::type>::type operate_assign_multiply(typeA&& objectA, typeB&& objectB)       noexcept(noexcept(std::declval<typeA>() *=  std::declval<typeB>())) { return static_cast<typename assess_operation<assign_multiply,       pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) *=  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<assign_right_shift,    pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_right_shift,    pack<typeA&&, typeB&&> >  ::type>::type operate_assign_right_shift(typeA&& objectA, typeB&& objectB)    noexcept(noexcept(std::declval<typeA>() >>= std::declval<typeB>())) { return static_cast<typename assess_operation<assign_right_shift,    pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) >>= std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<assign_subtract,       pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_subtract,       pack<typeA&&, typeB&&> >  ::type>::type operate_assign_subtract(typeA&& objectA, typeB&& objectB)       noexcept(noexcept(std::declval<typeA>() -=  std::declval<typeB>())) { return static_cast<typename assess_operation<assign_subtract,       pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) -=  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<bitwise_and,           pack<typeA&&, typeB&&> >  ::value, typename assess_operation<bitwise_and,           pack<typeA&&, typeB&&> >  ::type>::type operate_bitwise_and(typeA&& objectA, typeB&& objectB)           noexcept(noexcept(std::declval<typeA>() &   std::declval<typeB>())) { return static_cast<typename assess_operation<bitwise_and,           pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) &   std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<bitwise_or,            pack<typeA&&, typeB&&> >  ::value, typename assess_operation<bitwise_or,            pack<typeA&&, typeB&&> >  ::type>::type operate_bitwise_or(typeA&& objectA, typeB&& objectB)            noexcept(noexcept(std::declval<typeA>() |   std::declval<typeB>())) { return static_cast<typename assess_operation<bitwise_or,            pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) |   std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<bitwise_xor,           pack<typeA&&, typeB&&> >  ::value, typename assess_operation<bitwise_xor,           pack<typeA&&, typeB&&> >  ::type>::type operate_bitwise_xor(typeA&& objectA, typeB&& objectB)           noexcept(noexcept(std::declval<typeA>() ^   std::declval<typeB>())) { return static_cast<typename assess_operation<bitwise_xor,           pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) ^   std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<boolean_and,           pack<typeA&&, typeB&&> >  ::value, typename assess_operation<boolean_and,           pack<typeA&&, typeB&&> >  ::type>::type operate_boolean_and(typeA&& objectA, typeB&& objectB)           noexcept(noexcept(std::declval<typeA>() &&  std::declval<typeB>())) { return static_cast<typename assess_operation<boolean_and,           pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) &&  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<boolean_or,            pack<typeA&&, typeB&&> >  ::value, typename assess_operation<boolean_or,            pack<typeA&&, typeB&&> >  ::type>::type operate_boolean_or(typeA&& objectA, typeB&& objectB)            noexcept(noexcept(std::declval<typeA>() ||  std::declval<typeB>())) { return static_cast<typename assess_operation<boolean_or,            pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) ||  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<cast,                  pack<typeA&&, typeB> >    ::value, typename assess_operation<cast,                  pack<typeA&&, typeB> >    ::type>::type operate_cast(typeA&& object)                                    noexcept(noexcept(static_cast<typeB>(std::declval<typeA>())))       { return static_cast<typeB>(std::forward<typeA>(object)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<comma,                 pack<typeA&&, typeB&&> >  ::value, typename assess_operation<comma,                 pack<typeA&&, typeB&&> >  ::type>::type operate_comma(typeA&& objectA, typeB&& objectB)                 noexcept(noexcept(std::declval<typeA>(),    std::declval<typeB>())) { return static_cast<typename assess_operation<comma,                 pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA),    std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<divide,                pack<typeA&&, typeB&&> >  ::value, typename assess_operation<divide,                pack<typeA&&, typeB&&> >  ::type>::type operate_divide(typeA&& objectA, typeB&& objectB)                noexcept(noexcept(std::declval<typeA>() /   std::declval<typeB>())) { return static_cast<typename assess_operation<divide,                pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) /   std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<equals,                pack<typeA&&, typeB&&> >  ::value, typename assess_operation<equals,                pack<typeA&&, typeB&&> >  ::type>::type operate_equals(typeA&& objectA, typeB&& objectB)                noexcept(noexcept(std::declval<typeA>() ==  std::declval<typeB>())) { return static_cast<typename assess_operation<equals,                pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) ==  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<equals_greater,        pack<typeA&&, typeB&&> >  ::value, typename assess_operation<equals_greater,        pack<typeA&&, typeB&&> >  ::type>::type operate_equals_greater(typeA&& objectA, typeB&& objectB)        noexcept(noexcept(std::declval<typeA>() >=  std::declval<typeB>())) { return static_cast<typename assess_operation<equals_greater,        pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) >=  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<equals_lesser,         pack<typeA&&, typeB&&> >  ::value, typename assess_operation<equals_lesser,         pack<typeA&&, typeB&&> >  ::type>::type operate_equals_lesser(typeA&& objectA, typeB&& objectB)         noexcept(noexcept(std::declval<typeA>() <=  std::declval<typeB>())) { return static_cast<typename assess_operation<equals_lesser,         pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) <=  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<greater,               pack<typeA&&, typeB&&> >  ::value, typename assess_operation<greater,               pack<typeA&&, typeB&&> >  ::type>::type operate_greater(typeA&& objectA, typeB&& objectB)               noexcept(noexcept(std::declval<typeA>() >   std::declval<typeB>())) { return static_cast<typename assess_operation<greater,               pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) >   std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<left_shift,            pack<typeA&&, typeB&&> >  ::value, typename assess_operation<left_shift,            pack<typeA&&, typeB&&> >  ::type>::type operate_left_shift(typeA&& objectA, typeB&& objectB)            noexcept(noexcept(std::declval<typeA>() <<  std::declval<typeB>())) { return static_cast<typename assess_operation<left_shift,            pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) <<  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<lesser,                pack<typeA&&, typeB&&> >  ::value, typename assess_operation<lesser,                pack<typeA&&, typeB&&> >  ::type>::type operate_lesser(typeA&& objectA, typeB&& objectB)                noexcept(noexcept(std::declval<typeA>() <   std::declval<typeB>())) { return static_cast<typename assess_operation<lesser,                pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) <   std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<member_pointer_access, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<member_pointer_access, pack<typeA&&, typeB&&> >  ::type>::type operate_member_pointer_access(typeA&& objectA, typeB&& objectB) noexcept(noexcept(std::declval<typeA>() ->* std::declval<typeB>())) { return static_cast<typename assess_operation<member_pointer_access, pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) ->* std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<modulo,                pack<typeA&&, typeB&&> >  ::value, typename assess_operation<modulo,                pack<typeA&&, typeB&&> >  ::type>::type operate_modulo(typeA&& objectA, typeB&& objectB)                noexcept(noexcept(std::declval<typeA>() %   std::declval<typeB>())) { return static_cast<typename assess_operation<modulo,                pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) %   std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<multiply,              pack<typeA&&, typeB&&> >  ::value, typename assess_operation<multiply,              pack<typeA&&, typeB&&> >  ::type>::type operate_multiply(typeA&& objectA, typeB&& objectB)              noexcept(noexcept(std::declval<typeA>() *   std::declval<typeB>())) { return static_cast<typename assess_operation<multiply,              pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) *   std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<right_shift,           pack<typeA&&, typeB&&> >  ::value, typename assess_operation<right_shift,           pack<typeA&&, typeB&&> >  ::type>::type operate_right_shift(typeA&& objectA, typeB&& objectB)           noexcept(noexcept(std::declval<typeA>() >>  std::declval<typeB>())) { return static_cast<typename assess_operation<right_shift,           pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) >>  std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<subscript,             pack<typeA&&, typeB&&> >  ::value, typename assess_operation<subscript,             pack<typeA&&, typeB&&> >  ::type>::type operate_subscript(typeA&& objectA, typeB&& objectB)             noexcept(noexcept(std::declval<typeA>()[std::declval<typeB>()]))    { return static_cast<typename assess_operation<subscript,             pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA)[std::forward<typeB>(objectB)]); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<subtract,              pack<typeA&&, typeB&&> >  ::value, typename assess_operation<subtract,              pack<typeA&&, typeB&&> >  ::type>::type operate_subtract(typeA&& objectA, typeB&& objectB)              noexcept(noexcept(std::declval<typeA>() -   std::declval<typeB>())) { return static_cast<typename assess_operation<subtract,              pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) -   std::forward<typeB>(objectB)); }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<assess_operation<unequals,              pack<typeA&&, typeB&&> >  ::value, typename assess_operation<unequals,              pack<typeA&&, typeB&&> >  ::type>::type operate_unequals(typeA&& objectA, typeB&& objectB)              noexcept(noexcept(std::declval<typeA>() !=  std::declval<typeB>())) { return static_cast<typename assess_operation<unequals,              pack<typeA&&, typeB&&> >  ::type>(std::forward<typeA>(objectA) !=  std::forward<typeB>(objectB)); }

  template <typename type, typename... types> constfunc(true) inline static typename std::enable_if<false == assess_operation<call,                  pack<type&&, types&&...> >::value, invalid>::type operate_call(type&&, types&&...)                noexcept { return {}; }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<false == assess_operation<address,               pack<type&&> >            ::value, invalid>::type operate_address(type&&)                         noexcept { return {}; }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<false == assess_operation<complement,            pack<type&&> >            ::value, invalid>::type operate_complement(type&&)                      noexcept { return {}; }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<false == assess_operation<dereference,           pack<type&&> >            ::value, invalid>::type operate_dereference(type&&)                     noexcept { return {}; }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<false == assess_operation<member_access,         pack<type&&> >            ::value, invalid>::type operate_member_access(type&&)                   noexcept { return {}; }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<false == assess_operation<minus,                 pack<type&&> >            ::value, invalid>::type operate_minus(type&&)                           noexcept { return {}; }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<false == assess_operation<negate,                pack<type&&> >            ::value, invalid>::type operate_negate(type&&)                          noexcept { return {}; }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<false == assess_operation<plus,                  pack<type&&> >            ::value, invalid>::type operate_plus(type&&)                            noexcept { return {}; }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<false == assess_operation<post_decrement,        pack<type&&> >            ::value, invalid>::type operate_post_decrement(type&&)                  noexcept { return {}; }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<false == assess_operation<post_increment,        pack<type&&> >            ::value, invalid>::type operate_post_increment(type&&)                  noexcept { return {}; }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<false == assess_operation<pre_decrement,         pack<type&&> >            ::value, invalid>::type operate_pre_decrement(type&&)                   noexcept { return {}; }
  template <typename type>                    constfunc(true) inline static typename std::enable_if<false == assess_operation<pre_increment,         pack<type&&> >            ::value, invalid>::type operate_pre_increment(type&&)                   noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<add,                   pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_add(typeA&&, typeB&&)                   noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<assign,                pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign(typeA&&, typeB&&)                noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<assign_add,            pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_add(typeA&&, typeB&&)            noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<assign_bitwise_and,    pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_bitwise_and(typeA&&, typeB&&)    noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<assign_bitwise_or,     pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_bitwise_or(typeA&&, typeB&&)     noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<assign_bitwise_xor,    pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_bitwise_xor(typeA&&, typeB&&)    noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<assign_divide,         pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_divide(typeA&&, typeB&&)         noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<assign_left_shift,     pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_left_shift(typeA&&, typeB&&)     noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<assign_modulo,         pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_modulo(typeA&&, typeB&&)         noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<assign_multiply,       pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_multiply(typeA&&, typeB&&)       noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<assign_right_shift,    pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_right_shift(typeA&&, typeB&&)    noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<assign_subtract,       pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_subtract(typeA&&, typeB&&)       noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<bitwise_and,           pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_bitwise_and(typeA&&, typeB&&)           noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<bitwise_or,            pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_bitwise_or(typeA&&, typeB&&)            noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<bitwise_xor,           pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_bitwise_xor(typeA&&, typeB&&)           noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<boolean_and,           pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_boolean_and(typeA&&, typeB&&)           noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<boolean_or,            pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_boolean_or(typeA&&, typeB&&)            noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<cast,                  pack<typeA&&, typeB> >    ::value, invalid>::type operate_cast(typeA&&)                           noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<comma,                 pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_comma(typeA&&, typeB&&)                 noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<compare,               pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_compare(typeA&&, typeB&&)               noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<divide,                pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_divide(typeA&&, typeB&&)                noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<equals,                pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_equals(typeA&&, typeB&&)                noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<equals_greater,        pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_equals_greater(typeA&&, typeB&&)        noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<equals_lesser,         pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_equals_lesser(typeA&&, typeB&&)         noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<greater,               pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_greater(typeA&&, typeB&&)               noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<left_shift,            pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_left_shift(typeA&&, typeB&&)            noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<lesser,                pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_lesser(typeA&&, typeB&&)                noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<member_pointer_access, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_member_pointer_access(typeA&&, typeB&&) noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<modulo,                pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_modulo(typeA&&, typeB&&)                noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<multiply,              pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_multiply(typeA&&, typeB&&)              noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<right_shift,           pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_right_shift(typeA&&, typeB&&)           noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<subscript,             pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_subscript(typeA&&, typeB&&)             noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<subtract,              pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_subtract(typeA&&, typeB&&)              noexcept { return {}; }
  template <typename typeA, typename typeB>   constfunc(true) inline static typename std::enable_if<false == assess_operation<unequals,              pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_unequals(typeA&&, typeB&&)              noexcept { return {}; }
}

template <typename base, class accessor = void, class mutator = void>
struct property {
  private:
    template <class subaccessor, bool = std::is_void<accessor>::value>
    struct accessor_t final {
      friend struct property;
      private:
        template <enum operation operation, typename subbase> constfunc(true) inline static decltype(subaccessor::get(std::declval<subbase>(), instanceof<enum operation>())) value(typename std::enable_if<false != std::is_void<decltype(static_cast<void>(subaccessor::get(std::declval<subbase>(), instanceof<enum operation>())))>::value, subbase>::type&& value) noexcept { return subaccessor::get(std::forward<subbase>(value), operation); }
        template <enum operation operation, typename subbase> constfunc(true) inline static decltype(subaccessor::get(std::declval<subbase>()))                               value(typename std::enable_if<false == std::is_void<decltype(static_cast<void>(subaccessor::get(std::declval<subbase>(), instanceof<enum operation>())))>::value, subbase>::type&& value) noexcept { return subaccessor::get(std::forward<subbase>(value)); }
    };

    template <class subaccessor>
    struct accessor_t<subaccessor, true> final {
      friend struct property;
      private: template <enum operation operation, typename subbase> constfunc(true) inline static decltype(std::declval<subbase>()) value(subbase&& value) noexcept { return std::forward<subbase>(value); }
    };

    // ...
    enum base_t : unsigned char {
      aggregated = 0x1u, bounded, functional, referenced, unbounded
    };

    // ...
    typedef typename std::conditional<std::is_reference<base>::value, base, typename std::add_lvalue_reference<base>::type>::type lvalue_reference_t;

    // ...
    template <class submutator, bool = std::is_void<mutator>::value>
    class mutator_t final {
      friend struct property;
      private:
        template <enum operation operation, typename subbase, typename... types> constfunc(true) inline static decltype(submutator::set(std::declval<subbase>(), instanceof<enum operation>(), std::declval<types>()...)) value(typename std::enable_if<false != std::is_void<decltype(static_cast<void>(submutator::set(std::declval<subbase>(), instanceof<enum operation>(), std::declval<types>()...)))>::value, subbase>::type&& value, types&&... arguments) noexcept(noexcept(submutator::set(std::declval<subbase>(), instanceof<enum operation>(), std::declval<types>()...))) { return submutator::set(std::forward<subbase>(value), operation, std::forward<types>(arguments)...); }
        template <enum operation operation, typename subbase, typename... types> constfunc(true) inline static decltype(submutator::set(std::declval<subbase>(), std::declval<types>()...))                               value(typename std::enable_if<false == std::is_void<decltype(static_cast<void>(submutator::set(std::declval<subbase>(), instanceof<enum operation>(), std::declval<types>()...)))>::value, subbase>::type&& value, types&&... arguments) noexcept(noexcept(submutator::set(std::declval<subbase>(), std::declval<types>()...)))                               { return submutator::set(std::forward<subbase>(value), std::forward<types>(arguments)...); }
    };

    template <class submutator>
    class mutator_t<submutator, true> final {
      friend struct property;

      private:
        template <enum operation operation, typename subbase, typename type> constfunc(true) inline static typename std::enable_if<operation == assign, decltype(operate_assign(std::declval<subbase>(), std::declval<type>()))>::type                         value(subbase&& value, type&& argument) noexcept(noexcept(operate_assign(std::declval<subbase>(), std::declval<type>())))             { return operate_assign(std::forward<subbase>(value), std::forward<type>(argument)); }
        template <enum operation operation, typename subbase, typename type> constfunc(true) inline static typename std::enable_if<operation == assign_add, decltype(operate_assign_add(std::declval<subbase>(), std::declval<type>()))>::type                 value(subbase&& value, type&& argument) noexcept(noexcept(operate_assign_add(std::declval<subbase>(), std::declval<type>())))         { return operate_assign_add(std::forward<subbase>(value), std::forward<type>(argument)); }
        template <enum operation operation, typename subbase, typename type> constfunc(true) inline static typename std::enable_if<operation == assign_bitwise_and, decltype(operate_assign_bitwise_and(std::declval<subbase>(), std::declval<type>()))>::type value(subbase&& value, type&& argument) noexcept(noexcept(operate_assign_bitwise_and(std::declval<subbase>(), std::declval<type>()))) { return operate_assign_bitwise_and(std::forward<subbase>(value), std::forward<type>(argument)); }
        template <enum operation operation, typename subbase, typename type> constfunc(true) inline static typename std::enable_if<operation == assign_bitwise_or, decltype(operate_assign_bitwise_or(std::declval<subbase>(), std::declval<type>()))>::type   value(subbase&& value, type&& argument) noexcept(noexcept(operate_assign_bitwise_or(std::declval<subbase>(), std::declval<type>())))  { return operate_assign_bitwise_or(std::forward<subbase>(value), std::forward<type>(argument)); }
        template <enum operation operation, typename subbase, typename type> constfunc(true) inline static typename std::enable_if<operation == assign_bitwise_xor, decltype(operate_assign_bitwise_xor(std::declval<subbase>(), std::declval<type>()))>::type value(subbase&& value, type&& argument) noexcept(noexcept(operate_assign_bitwise_xor(std::declval<subbase>(), std::declval<type>()))) { return operate_assign_bitwise_xor(std::forward<subbase>(value), std::forward<type>(argument)); }
        template <enum operation operation, typename subbase, typename type> constfunc(true) inline static typename std::enable_if<operation == assign_divide, decltype(operate_assign_divide(std::declval<subbase>(), std::declval<type>()))>::type           value(subbase&& value, type&& argument) noexcept(noexcept(operate_assign_divide(std::declval<subbase>(), std::declval<type>())))      { return operate_assign_divide(std::forward<subbase>(value), std::forward<type>(argument)); }
        template <enum operation operation, typename subbase, typename type> constfunc(true) inline static typename std::enable_if<operation == assign_left_shift, decltype(operate_assign_left_shift(std::declval<subbase>(), std::declval<type>()))>::type   value(subbase&& value, type&& argument) noexcept(noexcept(operate_assign_left_shift(std::declval<subbase>(), std::declval<type>())))  { return operate_assign_left_shift(std::forward<subbase>(value), std::forward<type>(argument)); }
        template <enum operation operation, typename subbase, typename type> constfunc(true) inline static typename std::enable_if<operation == assign_modulo, decltype(operate_assign_modulo(std::declval<subbase>(), std::declval<type>()))>::type           value(subbase&& value, type&& argument) noexcept(noexcept(operate_assign_modulo(std::declval<subbase>(), std::declval<type>())))      { return operate_assign_modulo(std::forward<subbase>(value), std::forward<type>(argument)); }
        template <enum operation operation, typename subbase, typename type> constfunc(true) inline static typename std::enable_if<operation == assign_multiply, decltype(operate_assign_multiply(std::declval<subbase>(), std::declval<type>()))>::type       value(subbase&& value, type&& argument) noexcept(noexcept(operate_assign_multiply(std::declval<subbase>(), std::declval<type>())))    { return operate_assign_multiply(std::forward<subbase>(value), std::forward<type>(argument)); }
        template <enum operation operation, typename subbase, typename type> constfunc(true) inline static typename std::enable_if<operation == assign_right_shift, decltype(operate_assign_right_shift(std::declval<subbase>(), std::declval<type>()))>::type value(subbase&& value, type&& argument) noexcept(noexcept(operate_assign_right_shift(std::declval<subbase>(), std::declval<type>()))) { return operate_assign_right_shift(std::forward<subbase>(value), std::forward<type>(argument)); }
        template <enum operation operation, typename subbase, typename type> constfunc(true) inline static typename std::enable_if<operation == assign_subtract, decltype(operate_assign_subtract(std::declval<subbase>(), std::declval<type>()))>::type       value(subbase&& value, type&& argument) noexcept(noexcept(operate_assign_subtract(std::declval<subbase>(), std::declval<type>())))    { return operate_assign_subtract(std::forward<subbase>(value), std::forward<type>(argument)); }

        template <enum operation operation, typename subbase> constfunc(true) inline static typename std::enable_if<operation == post_decrement, decltype(operate_post_decrement(std::declval<subbase>()))>::type value(subbase&& value) noexcept(noexcept(operate_post_decrement(std::declval<subbase>()))) { return operate_post_decrement(std::forward<subbase>(value)); }
        template <enum operation operation, typename subbase> constfunc(true) inline static typename std::enable_if<operation == post_increment, decltype(operate_post_increment(std::declval<subbase>()))>::type value(subbase&& value) noexcept(noexcept(operate_post_increment(std::declval<subbase>()))) { return operate_post_increment(std::forward<subbase>(value)); }
        template <enum operation operation, typename subbase> constfunc(true) inline static typename std::enable_if<operation == pre_decrement, decltype(operate_pre_decrement(std::declval<subbase>()))>::type   value(subbase&& value) noexcept(noexcept(operate_pre_decrement(std::declval<subbase>())))  { return operate_pre_decrement(std::forward<subbase>(value)); }
        template <enum operation operation, typename subbase> constfunc(true) inline static typename std::enable_if<operation == pre_increment, decltype(operate_pre_decrement(std::declval<subbase>()))>::type   value(subbase&& value) noexcept(noexcept(operate_pre_decrement(std::declval<subbase>())))  { return operate_pre_decrement(std::forward<subbase>(value)); }
    };

    // ...
    typedef typename std::conditional<std::is_reference<base>::value, base, typename std::add_rvalue_reference<base>::type>::type rvalue_reference_t;

    // ...
    template <typename subbase, unsigned char>
    struct value_t final {
      template <typename, class, class>
      friend struct property;

      private:
        mutable subbase value;

        template <typename type>
        constfunc(true) inline value_t(type&& object) noexcept : value(std::forward<type>(object)) {}
    };

    template <typename subbase>
    struct value_t<subbase, aggregated> final {
      template <typename, class, class>
      friend struct property;

      private:
        mutable subbase value;

        template <typename... types>
        constfunc(true) inline value_t(types&&... arguments) noexcept(noexcept(subbase(std::declval<types>()...))) : value(std::forward<types>(arguments)...) {}
    };

    template <typename subbase, std::size_t capacity>
    struct value_t<subbase [capacity], bounded> final {
      template <typename, class, class>
      friend struct property;

      private:
        mutable subbase value[capacity];

        // ...
        template <bool boolean, bool...>                          struct boolean_and                                  final { friend struct value_t; private: static bool const value = boolean; };
        template <bool booleanA, bool booleanB, bool... booleans> struct boolean_and<booleanA, booleanB, booleans...> final { friend struct value_t; private: static bool const value = boolean_and<booleanA && booleanB, booleans...>::value; };

        template <std::size_t index, std::size_t... indexes> struct index_sequence                 final { typedef typename index_sequence<index - 1u, index, indexes...>::type type; };
        template <std::size_t... indexes>                    struct index_sequence<0u, indexes...> final { typedef index_sequence<0u, indexes...> type; };

        // ...
        template <typename type, std::size_t... indexes> constfunc(true) inline value_t(type array[], index_sequence<0u, indexes...> const) noexcept(noexcept(subbase(instanceof<type>()))) : value{array[indexes - 1u]...} {}

      public:
        template <typename type, std::size_t length> constfunc(true) inline value_t(type (&&array)[length]) noexcept(noexcept(value_t(instanceof<type*>(), instanceof<typename index_sequence<length>::type >()))) : value_t<subbase[capacity], bounded>::value_t(static_cast<type*>(array), typename index_sequence<length>::type{}) {}
        template <typename type, std::size_t length> constfunc(true) inline value_t(type (&array)[length])  noexcept(noexcept(value_t(instanceof<type*>(), instanceof<typename index_sequence<length>::type >()))) : value_t<subbase[capacity], bounded>::value_t(static_cast<type*>(array), typename index_sequence<length>::type{}) {}
        template <typename... types>                 constfunc(true) inline value_t(types&&... elements)    noexcept(boolean_and<noexcept(subbase(std::declval<types>()))...>::value) : value{std::forward<types>(elements)...} {}
    };

    template <typename subbase> // ->> Explicitly deter the user specifying a function type as the `base`
    struct value_t<subbase, functional>;

    template <typename subbase>
    struct value_t<subbase, referenced> final {
      template <typename, class, class>
      friend struct property;

      private:
        subbase value;

        template <typename type>
        constexpr inline value_t(type&& reference) noexcept : value(std::forward<type>(reference)) {}
    };

    template <typename subbase> // ->> Explicitly deter the user specifying an unbounded array type as the `base`
    struct value_t<subbase, unbounded>;

    /* ... */
    value_t<base,
      std::is_array    <base>::value ? 0u == std::extent<base, 0u>::value ? unbounded : bounded :
      std::is_function <base>::value ? functional                :
      std::is_reference<base>::value ? referenced                :
      std::is_scalar   <base>::value ? static_cast<base_t>(0x0u) :
      aggregated
    > value;

  public:
    template <typename... types>
    constfunc(true) inline property(types&&... arguments) noexcept : value(std::forward<types>(arguments)...) {}

    // [get, set] ... --- WARN (Lapys) -> Default setter functions use a presumptive `return` type i.e.: they `return` the object instead of the result of the modification
    /* template <typename = void> */ constfunc(true) static typename std::remove_reference<base>::type&  get(typename std::remove_reference<base>::type& object) noexcept { return object; }
    /* template <typename = void> */ constfunc(true) static typename std::remove_reference<base>::type&  get(typename std::remove_reference<base>::type& object, enum operation const) noexcept { return object; }
    /* template <typename = void> */ constfunc(true) static typename std::remove_reference<base>::type&& get(typename std::remove_reference<base>::type&& object) noexcept { return static_cast<typename std::remove_reference<base>::type&&>(object); }
    /* template <typename = void> */ constfunc(true) static typename std::remove_reference<base>::type&& get(typename std::remove_reference<base>::type&& object, enum operation const) noexcept { return static_cast<typename std::remove_reference<base>::type&&>(object); }

    template <typename type> constfunc(true) static typename std::remove_reference<base>::type&  set(typename std::remove_reference<base>::type& object, enum operation const operation) noexcept(noexcept(instanceof<typename std::remove_reference<base>::type&>()--) && noexcept(instanceof<typename std::remove_reference<base>::type&>()++) && noexcept(--instanceof<typename std::remove_reference<base>::type&>()) && noexcept(++instanceof<typename std::remove_reference<base>::type&>())) { return operation == post_decrement ? static_cast<void>(object--), object : operation == post_increment ? static_cast<void>(object++), object : operation == pre_decrement ? static_cast<void>(--object), object : operation == pre_increment ? static_cast<void>(++object), object : object; }
    template <typename type> constfunc(true) static typename std::remove_reference<base>::type&  set(typename std::remove_reference<base>::type& object, enum operation const operation, type&& argument) noexcept(noexcept(instanceof<typename std::remove_reference<base>::type&>() = std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&>() += std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&>() &= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&>() |= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&>() ^= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&>() /= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&>() <<= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&>() %= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&>() *= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&>() >>= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&>() -= std::declval<type&&>()))            { return operation == assign ? static_cast<void>(object = std::forward<type&&>(argument)), object : operation == assign_add ? static_cast<void>(object += std::forward<type&&>(argument)), object : operation == assign_bitwise_and ? static_cast<void>(object &= std::forward<type&&>(argument)), object : operation == assign_bitwise_or ? static_cast<void>(object |= std::forward<type&&>(argument)), object : operation == assign_bitwise_xor ? static_cast<void>(object ^= std::forward<type&&>(argument)), object : operation == assign_divide ? static_cast<void>(object /= std::forward<type&&>(argument)), object : operation == assign_left_shift ? static_cast<void>(object <<= std::forward<type&&>(argument)), object : operation == assign_modulo ? static_cast<void>(object %= std::forward<type&&>(argument)), object : operation == assign_multiply ? static_cast<void>(object *= std::forward<type&&>(argument)), object : operation == assign_right_shift ? static_cast<void>(object >>= std::forward<type&&>(argument)), object : operation == assign_subtract ? static_cast<void>(object -= std::forward<type&&>(argument)), object : object; }
    template <typename type> constfunc(true) static typename std::remove_reference<base>::type&& set(typename std::remove_reference<base>::type&& object, enum operation const operation) noexcept(noexcept(instanceof<typename std::remove_reference<base>::type&&>()--) && noexcept(instanceof<typename std::remove_reference<base>::type&&>()++) && noexcept(--instanceof<typename std::remove_reference<base>::type&&>()) && noexcept(++instanceof<typename std::remove_reference<base>::type&&>())) { return operation == post_decrement ? static_cast<void>(static_cast<typename std::remove_reference<base>::type&&>(object)--), object : operation == post_increment ? static_cast<void>(static_cast<typename std::remove_reference<base>::type&&>(object)++), object : operation == pre_decrement ? static_cast<void>(--static_cast<typename std::remove_reference<base>::type&&>(object)), object : operation == pre_increment ? static_cast<void>(++static_cast<typename std::remove_reference<base>::type&&>(object)), object : object; }
    template <typename type> constfunc(true) static typename std::remove_reference<base>::type&& set(typename std::remove_reference<base>::type&& object, enum operation const operation, type&& argument) noexcept(noexcept(instanceof<typename std::remove_reference<base>::type&&>() = std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&&>() += std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&&>() &= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&&>() |= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&&>() ^= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&&>() /= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&&>() <<= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&&>() %= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&&>() *= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&&>() >>= std::declval<type&&>()) && noexcept(instanceof<typename std::remove_reference<base>::type&&>() -= std::declval<type&&>())) { return static_cast<typename std::remove_reference<base>::type&&>(operation == assign ? static_cast<void>(static_cast<typename std::remove_reference<base>::type&&>(object) = std::forward<type&&>(argument)), object : operation == assign_add ? static_cast<void>(static_cast<typename std::remove_reference<base>::type&&>(object) += std::forward<type&&>(argument)), object : operation == assign_bitwise_and ? static_cast<void>(static_cast<typename std::remove_reference<base>::type&&>(object) &= std::forward<type&&>(argument)), object : operation == assign_bitwise_or ? static_cast<void>(static_cast<typename std::remove_reference<base>::type&&>(object) |= std::forward<type&&>(argument)), object : operation == assign_bitwise_xor ? static_cast<void>(static_cast<typename std::remove_reference<base>::type&&>(object) ^= std::forward<type&&>(argument)), object : operation == assign_divide ? static_cast<void>(static_cast<typename std::remove_reference<base>::type&&>(object) /= std::forward<type&&>(argument)), object : operation == assign_left_shift ? static_cast<void>(static_cast<typename std::remove_reference<base>::type&&>(object) <<= std::forward<type&&>(argument)), object : operation == assign_modulo ? static_cast<void>(static_cast<typename std::remove_reference<base>::type&&>(object) %= std::forward<type&&>(argument)), object : operation == assign_multiply ? static_cast<void>(static_cast<typename std::remove_reference<base>::type&&>(object) *= std::forward<type&&>(argument)), object : operation == assign_right_shift ? static_cast<void>(static_cast<typename std::remove_reference<base>::type&&>(object) >>= std::forward<type&&>(argument)), object : operation == assign_subtract ? static_cast<void>(static_cast<typename std::remove_reference<base>::type&&>(object) -= std::forward<type&&>(argument)), object : object); }

    // [operator] ...
    // add
    decltype(operate_plus(instanceof<lvalue_reference_t>())) constfunc(true) inline friend operator +(property const volatile& property)  noexcept { return operate_plus(static_cast<lvalue_reference_t>(property.value.value)); }
    decltype(operate_plus(instanceof<rvalue_reference_t>())) constfunc(true) inline friend operator +(property const volatile&& property) noexcept { return operate_plus(static_cast<rvalue_reference_t>(property.value.value)); }
    // address,
    // assign,
    // assign_add,
    // assign_bitwise_and,
    // assign_bitwise_or,
    // assign_bitwise_xor,
    // assign_divide,
    // assign_left_shift,
    // assign_modulo,
    // assign_multiply,
    // assign_right_shift,
    // assign_subtract,
    // bitwise_and,
    // bitwise_or,
    // bitwise_xor,
    // boolean_and,
    // boolean_or,
    // call,
    // cast,
    // comma,
    // compare,
    // complement,
    // dereference,
    // divide,
    // equals,
    // greater, equals_greater,
    // left_shift,
    // lesser,  equals_lesser,
    // member_access,
    // member_pointer_access,
    // minus,
    // modulo,
    // multiply,
    // negate,
    // plus,
    // post_decrement,
    // post_increment,
    // pre_decrement,
    // pre_increment,
    // right_shift,
    // subscript,
    // subtract,
    // unequals
};

/* ... */

#undef constfunc
#if defined(__cpp_constexpr) && __cplusplus < 201402L
# undef constfunc_false
# undef constfunc_true
#endif

/* Main */
constexpr static int array[3] = {1, 2, 3};
constexpr static int function() { return 0; }
static int modifiable = 0;
struct object {};

template struct property<int>;
template struct property<int&>;
// template struct property<int[]>;
template struct property<int[3]>;
// template struct property<int()>;
template struct property<object>;

int main(int, char*[]) /* noexcept */ {
  static_cast<void>(array);
  static_cast<void>(function);
  static_cast<void>(modifiable);

  /* ... */
  std::puts("Hello, World!");
}
