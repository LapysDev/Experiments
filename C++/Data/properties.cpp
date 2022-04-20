#include <cstddef>
#include <cstdio>
#include <type_traits>
#include <utility>

/* ... */
namespace {
  template <typename type>
  constexpr inline static type instanceof() noexcept;

  // ...
  struct invalid final {
    // inline invalid(...) noexcept(false) { throw 0; }
    constexpr inline invalid(...) noexcept = delete;
  };

  // ... -->
  enum opdef : unsigned char {
    global,    // operator +(x, y)
    implicit,  // x + y
    namespaced // x.operator +(y)
  };

  // ...
  enum operation : unsigned char {
    assign,
    add,         assign_add,
    divide,      assign_divide,
    left_shift,  assign_left_shift,
    modulo,      assign_modulo,
    multiply,    assign_multiply,
    right_shift, assign_right_shift,
    subtract,    assign_subtract,

    bitwise_and, assign_bitwise_and,
    bitwise_or,  assign_bitwise_or,
    bitwise_xor, assign_bitwise_xor,

    boolean_and,
    boolean_or,

    equals,
    greater, equals_greater,
    lesser,  equals_lesser,
    compare,
    unequals,

    member_access,
    member_pointer_access,

    post_decrement,
    post_increment,
    pre_decrement,
    pre_increment,

    address,
    call,
    cast,
    comma,
    complement,
    dereference,
    negate,
    minus,
    plus,
    subscript
  };

  // ...
  template <typename...>
  struct pack final {};
}

namespace {
  #ifdef _MSC_VER
  # pragma warning(push)
  # pragma warning(disable: 4238) // --> nonstandard extension used: class rvalue used as lvalue
  #endif

  template <unsigned char /* operation */, unsigned char /* definition */, class /* arguments */, typename = pack<void> >
  struct assess_operation final { typedef invalid type; static bool const value = false; };

  template <typename typeA, typename typeB>    struct assess_operation<add,                   global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator +(instanceof<typeA>(), instanceof<typeB>())))> >     final { typedef decltype(operator +(instanceof<typeA>(), instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<add,                   implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() + instanceof<typeB>()))> >                final { typedef decltype(instanceof<typeA>() + instanceof<typeB>())                type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<add,                   namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator +(instanceof<typeB>())))> >      final { typedef decltype(instanceof<typeA>().operator +(instanceof<typeB>()))      type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign,                global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator =(instanceof<typeA>(), instanceof<typeB>())))> >     final { typedef decltype(operator =(instanceof<typeA>(), instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign,                implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() = instanceof<typeB>()))> >                final { typedef decltype(instanceof<typeA>() = instanceof<typeB>())                type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign,                namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator =(instanceof<typeB>())))> >      final { typedef decltype(instanceof<typeA>().operator =(instanceof<typeB>()))      type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_add,            global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator +=(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator +=(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_add,            implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() += instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() += instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_add,            namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator +=(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator +=(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_bitwise_and,    global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator &=(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator &=(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_bitwise_and,    implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() &= instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() &= instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_bitwise_and,    namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator &=(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator &=(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_bitwise_or,     global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator |=(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator |=(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_bitwise_or,     implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() |= instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() |= instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_bitwise_or,     namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator |=(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator |=(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_bitwise_xor,    global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator ^=(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator ^=(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_bitwise_xor,    implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() ^= instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() ^= instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_bitwise_xor,    namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator ^=(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator ^=(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_divide,         global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator /=(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator /=(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_divide,         implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() /= instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() /= instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_divide,         namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator /=(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator /=(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_left_shift,     global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator <<=(instanceof<typeA>(), instanceof<typeB>())))> >   final { typedef decltype(operator <<=(instanceof<typeA>(), instanceof<typeB>()))   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_left_shift,     implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() <<= instanceof<typeB>()))> >              final { typedef decltype(instanceof<typeA>() <<= instanceof<typeB>())              type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_left_shift,     namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator <<=(instanceof<typeB>())))> >    final { typedef decltype(instanceof<typeA>().operator <<=(instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_modulo,         global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator %=(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator %=(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_modulo,         implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() %= instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() %= instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_modulo,         namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator %=(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator %=(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_multiply,       global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator *=(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator *=(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_multiply,       implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() *= instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() *= instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_multiply,       namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator *=(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator *=(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_right_shift,    global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator >>=(instanceof<typeA>(), instanceof<typeB>())))> >   final { typedef decltype(operator >>=(instanceof<typeA>(), instanceof<typeB>()))   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_right_shift,    implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() >>= instanceof<typeB>()))> >              final { typedef decltype(instanceof<typeA>() >>= instanceof<typeB>())              type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_right_shift,    namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator >>=(instanceof<typeB>())))> >    final { typedef decltype(instanceof<typeA>().operator >>=(instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_subtract,       global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator -=(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator -=(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_subtract,       implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() -= instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() -= instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<assign_subtract,       namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator -=(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator -=(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<bitwise_and,           global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator &(instanceof<typeA>(), instanceof<typeB>())))> >     final { typedef decltype(operator &(instanceof<typeA>(), instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<bitwise_and,           implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() & instanceof<typeB>()))> >                final { typedef decltype(instanceof<typeA>() & instanceof<typeB>())                type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<bitwise_and,           namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator &(instanceof<typeB>())))> >      final { typedef decltype(instanceof<typeA>().operator &(instanceof<typeB>()))      type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<bitwise_or,            global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator |(instanceof<typeA>(), instanceof<typeB>())))> >     final { typedef decltype(operator |(instanceof<typeA>(), instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<bitwise_or,            implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() | instanceof<typeB>()))> >                final { typedef decltype(instanceof<typeA>() | instanceof<typeB>())                type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<bitwise_or,            namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator |(instanceof<typeB>())))> >      final { typedef decltype(instanceof<typeA>().operator |(instanceof<typeB>()))      type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<bitwise_xor,           global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator ^(instanceof<typeA>(), instanceof<typeB>())))> >     final { typedef decltype(operator ^(instanceof<typeA>(), instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<bitwise_xor,           implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() ^ instanceof<typeB>()))> >                final { typedef decltype(instanceof<typeA>() ^ instanceof<typeB>())                type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<bitwise_xor,           namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator ^(instanceof<typeB>())))> >      final { typedef decltype(instanceof<typeA>().operator ^(instanceof<typeB>()))      type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<boolean_and,           global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator &&(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator &&(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<boolean_and,           implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() && instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() && instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<boolean_and,           namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator &&(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator &&(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<boolean_or,            global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator ||(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator ||(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<boolean_or,            implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() || instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() || instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<boolean_or,            namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator ||(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator ||(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<cast,                  implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(static_cast<typeB>(instanceof<typeA>())))> >                  final { typedef decltype(static_cast<typeB>(instanceof<typeA>()))                  type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<cast,                  namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator typeB()))> >                     final { typedef decltype(instanceof<typeA>().operator typeB())                     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<comma,                 global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator ,(instanceof<typeA>(), instanceof<typeB>())))> >     final { typedef decltype(operator ,(instanceof<typeA>(), instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<comma,                 implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>(), instanceof<typeB>()))> >                 final { typedef decltype(instanceof<typeA>(), instanceof<typeB>())                 type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<comma,                 namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator ,(instanceof<typeB>())))> >      final { typedef decltype(instanceof<typeA>().operator ,(instanceof<typeB>()))      type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<divide,                global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator /(instanceof<typeA>(), instanceof<typeB>())))> >     final { typedef decltype(operator /(instanceof<typeA>(), instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<divide,                implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() / instanceof<typeB>()))> >                final { typedef decltype(instanceof<typeA>() / instanceof<typeB>())                type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<divide,                namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator /(instanceof<typeB>())))> >      final { typedef decltype(instanceof<typeA>().operator /(instanceof<typeB>()))      type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<equals,                global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator ==(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator ==(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<equals,                implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() == instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() == instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<equals,                namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator ==(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator ==(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<equals_greater,        global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator >=(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator >=(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<equals_greater,        implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() >= instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() >= instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<equals_greater,        namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator >=(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator >=(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<equals_lesser,         global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator <=(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator <=(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<equals_lesser,         implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() <= instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() <= instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<equals_lesser,         namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator <=(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator <=(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<greater,               global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator >(instanceof<typeA>(), instanceof<typeB>())))> >     final { typedef decltype(operator >(instanceof<typeA>(), instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<greater,               implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() > instanceof<typeB>()))> >                final { typedef decltype(instanceof<typeA>() > instanceof<typeB>())                type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<greater,               namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator >(instanceof<typeB>())))> >      final { typedef decltype(instanceof<typeA>().operator >(instanceof<typeB>()))      type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<left_shift,            global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator <<(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator <<(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<left_shift,            implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() << instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() << instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<left_shift,            namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator <<(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator <<(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<lesser,                global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator <(instanceof<typeA>(), instanceof<typeB>())))> >     final { typedef decltype(operator <(instanceof<typeA>(), instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<lesser,                implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() < instanceof<typeB>()))> >                final { typedef decltype(instanceof<typeA>() < instanceof<typeB>())                type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<lesser,                namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator <(instanceof<typeB>())))> >      final { typedef decltype(instanceof<typeA>().operator <(instanceof<typeB>()))      type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<member_pointer_access, global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator ->*(instanceof<typeA>(), instanceof<typeB>())))> >   final { typedef decltype(operator ->*(instanceof<typeA>(), instanceof<typeB>()))   type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<member_pointer_access, namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator ->*(instanceof<typeB>())))> >    final { typedef decltype(instanceof<typeA>().operator ->*(instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<modulo,                global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator %(instanceof<typeA>(), instanceof<typeB>())))> >     final { typedef decltype(operator %(instanceof<typeA>(), instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<modulo,                implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() % instanceof<typeB>()))> >                final { typedef decltype(instanceof<typeA>() % instanceof<typeB>())                type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<modulo,                namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator %(instanceof<typeB>())))> >      final { typedef decltype(instanceof<typeA>().operator %(instanceof<typeB>()))      type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<multiply,              global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator *(instanceof<typeA>(), instanceof<typeB>())))> >     final { typedef decltype(operator *(instanceof<typeA>(), instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<multiply,              implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() * instanceof<typeB>()))> >                final { typedef decltype(instanceof<typeA>() * instanceof<typeB>())                type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<multiply,              namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator *(instanceof<typeB>())))> >      final { typedef decltype(instanceof<typeA>().operator *(instanceof<typeB>()))      type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<right_shift,           global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator >>(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator >>(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<right_shift,           implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() >> instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() >> instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<right_shift,           namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator >>(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator >>(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<subscript,             global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator [](instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator [](instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<subscript,             implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>()[instanceof<typeB>()]))> >                 final { typedef decltype(instanceof<typeA>()[instanceof<typeB>()])                 type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<subscript,             namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator [](instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator [](instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<subtract,              global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator -(instanceof<typeA>(), instanceof<typeB>())))> >     final { typedef decltype(operator -(instanceof<typeA>(), instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<subtract,              implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() - instanceof<typeB>()))> >                final { typedef decltype(instanceof<typeA>() - instanceof<typeB>())                type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<subtract,              namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator -(instanceof<typeB>())))> >      final { typedef decltype(instanceof<typeA>().operator -(instanceof<typeB>()))      type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<unequals,              global,     pack<typeA, typeB>,    pack<decltype(static_cast<void>(operator !=(instanceof<typeA>(), instanceof<typeB>())))> >    final { typedef decltype(operator !=(instanceof<typeA>(), instanceof<typeB>()))    type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<unequals,              implicit,   pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>() != instanceof<typeB>()))> >               final { typedef decltype(instanceof<typeA>() != instanceof<typeB>())               type; static bool const value = true; };
  template <typename typeA, typename typeB>    struct assess_operation<unequals,              namespaced, pack<typeA, typeB>,    pack<decltype(static_cast<void>(instanceof<typeA>().operator !=(instanceof<typeB>())))> >     final { typedef decltype(instanceof<typeA>().operator !=(instanceof<typeB>()))     type; static bool const value = true; };
  template <typename typeA, typename... types> struct assess_operation<call,                  global,     pack<typeA, types...>, pack<decltype(static_cast<void>(operator ()(instanceof<typeA>(), instanceof<types>()...)))> > final { typedef decltype(operator ()(instanceof<typeA>(), instanceof<types>()...)) type; static bool const value = true; };
  template <typename typeA, typename... types> struct assess_operation<call,                  implicit,   pack<typeA, types...>, pack<decltype(static_cast<void>(instanceof<typeA>()(instanceof<types>()...)))> >              final { typedef decltype(instanceof<typeA>()(instanceof<types>()...))              type; static bool const value = true; };
  template <typename typeA, typename... types> struct assess_operation<call,                  namespaced, pack<typeA, types...>, pack<decltype(static_cast<void>(instanceof<typeA>().operator ()(instanceof<types>()...)))> >  final { typedef decltype(instanceof<typeA>().operator ()(instanceof<types>()...))  type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<address,               global,     pack<typeA>,           pack<decltype(static_cast<void>(operator &(instanceof<typeA>())))> >                          final { typedef decltype(operator &(instanceof<typeA>()))                          type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<address,               implicit,   pack<typeA>,           pack<decltype(static_cast<void>(&instanceof<typeA>()))> >                                     final { typedef decltype(&instanceof<typeA>())                                     type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<address,               namespaced, pack<typeA>,           pack<decltype(static_cast<void>(instanceof<typeA>().operator &()))> >                         final { typedef decltype(instanceof<typeA>().operator &())                         type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<complement,            global,     pack<typeA>,           pack<decltype(static_cast<void>(operator ~(instanceof<typeA>())))> >                          final { typedef decltype(operator ~(instanceof<typeA>()))                          type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<complement,            implicit,   pack<typeA>,           pack<decltype(static_cast<void>(~instanceof<typeA>()))> >                                     final { typedef decltype(~instanceof<typeA>())                                     type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<complement,            namespaced, pack<typeA>,           pack<decltype(static_cast<void>(instanceof<typeA>().operator ~()))> >                         final { typedef decltype(instanceof<typeA>().operator ~())                         type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<dereference,           global,     pack<typeA>,           pack<decltype(static_cast<void>(operator *(instanceof<typeA>())))> >                          final { typedef decltype(operator *(instanceof<typeA>()))                          type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<dereference,           implicit,   pack<typeA>,           pack<decltype(static_cast<void>(*instanceof<typeA>()))> >                                     final { typedef decltype(*instanceof<typeA>())                                     type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<dereference,           namespaced, pack<typeA>,           pack<decltype(static_cast<void>(instanceof<typeA>().operator *()))> >                         final { typedef decltype(instanceof<typeA>().operator *())                         type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<member_access,         namespaced, pack<typeA>,           pack<decltype(static_cast<void>(instanceof<typeA>().operator ->()))> >                        final { typedef decltype(instanceof<typeA>().operator ->())                        type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<minus,                 global,     pack<typeA>,           pack<decltype(static_cast<void>(operator -(instanceof<typeA>())))> >                          final { typedef decltype(operator -(instanceof<typeA>()))                          type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<minus,                 implicit,   pack<typeA>,           pack<decltype(static_cast<void>(-instanceof<typeA>()))> >                                     final { typedef decltype(-instanceof<typeA>())                                     type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<minus,                 namespaced, pack<typeA>,           pack<decltype(static_cast<void>(instanceof<typeA>().operator -()))> >                         final { typedef decltype(instanceof<typeA>().operator -())                         type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<negate,                global,     pack<typeA>,           pack<decltype(static_cast<void>(operator !(instanceof<typeA>())))> >                          final { typedef decltype(operator !(instanceof<typeA>()))                          type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<negate,                implicit,   pack<typeA>,           pack<decltype(static_cast<void>(!instanceof<typeA>()))> >                                     final { typedef decltype(!instanceof<typeA>())                                     type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<negate,                namespaced, pack<typeA>,           pack<decltype(static_cast<void>(instanceof<typeA>().operator !()))> >                         final { typedef decltype(instanceof<typeA>().operator !())                         type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<plus,                  global,     pack<typeA>,           pack<decltype(static_cast<void>(operator +(instanceof<typeA>())))> >                          final { typedef decltype(operator +(instanceof<typeA>()))                          type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<plus,                  implicit,   pack<typeA>,           pack<decltype(static_cast<void>(+instanceof<typeA>()))> >                                     final { typedef decltype(+instanceof<typeA>())                                     type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<plus,                  namespaced, pack<typeA>,           pack<decltype(static_cast<void>(instanceof<typeA>().operator +()))> >                         final { typedef decltype(instanceof<typeA>().operator +())                         type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<post_decrement,        global,     pack<typeA>,           pack<decltype(static_cast<void>(operator --(instanceof<typeA>(), 0)))> >                      final { typedef decltype(operator --(instanceof<typeA>(), 0))                      type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<post_decrement,        implicit,   pack<typeA>,           pack<decltype(static_cast<void>(instanceof<typeA>()--))> >                                    final { typedef decltype(instanceof<typeA>()--)                                    type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<post_decrement,        namespaced, pack<typeA>,           pack<decltype(static_cast<void>(instanceof<typeA>().operator --(0)))> >                       final { typedef decltype(instanceof<typeA>().operator --(0))                       type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<post_increment,        global,     pack<typeA>,           pack<decltype(static_cast<void>(operator ++(instanceof<typeA>(), 0)))> >                      final { typedef decltype(operator ++(instanceof<typeA>(), 0))                      type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<post_increment,        implicit,   pack<typeA>,           pack<decltype(static_cast<void>(instanceof<typeA>()++))> >                                    final { typedef decltype(instanceof<typeA>()++)                                    type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<post_increment,        namespaced, pack<typeA>,           pack<decltype(static_cast<void>(instanceof<typeA>().operator ++(0)))> >                       final { typedef decltype(instanceof<typeA>().operator ++(0))                       type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<pre_decrement,         global,     pack<typeA>,           pack<decltype(static_cast<void>(operator --(instanceof<typeA>())))> >                         final { typedef decltype(operator --(instanceof<typeA>()))                         type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<pre_decrement,         implicit,   pack<typeA>,           pack<decltype(static_cast<void>(--instanceof<typeA>()))> >                                    final { typedef decltype(--instanceof<typeA>())                                    type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<pre_decrement,         namespaced, pack<typeA>,           pack<decltype(static_cast<void>(instanceof<typeA>().operator --()))> >                        final { typedef decltype(instanceof<typeA>().operator --())                        type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<pre_increment,         global,     pack<typeA>,           pack<decltype(static_cast<void>(operator ++(instanceof<typeA>())))> >                         final { typedef decltype(operator ++(instanceof<typeA>()))                         type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<pre_increment,         implicit,   pack<typeA>,           pack<decltype(static_cast<void>(++instanceof<typeA>()))> >                                    final { typedef decltype(++instanceof<typeA>())                                    type; static bool const value = true; };
  template <typename typeA>                    struct assess_operation<pre_increment,         namespaced, pack<typeA>,           pack<decltype(static_cast<void>(instanceof<typeA>().operator ++()))> >                        final { typedef decltype(instanceof<typeA>().operator ++())                        type; static bool const value = true; };

  // ...
  template <enum opdef definition, typename type, typename... types> constexpr inline static typename std::enable_if<assess_operation<call,                  definition, pack<type&&, types&&...> >::value, typename assess_operation<call,                  definition, pack<type&&, types&&...> >::type>::type operate_call(type&& object, types&&... objects)                 noexcept(noexcept(std::declval<type>()(std::declval<types>()...)))  { return std::forward<type>(object)(std::forward<types>(objects)...); }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<assess_operation<address,               definition, pack<type&&> >            ::value, typename assess_operation<address,               definition, pack<type&&> >            ::type>::type operate_address(type&& object)                                  noexcept(noexcept(&std::declval<type>()))                           { return &std::forward<type>(object); }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<assess_operation<complement,            definition, pack<type&&> >            ::value, typename assess_operation<complement,            definition, pack<type&&> >            ::type>::type operate_complement(type&& object)                               noexcept(noexcept(~std::declval<type>()))                           { return ~std::forward<type>(object); }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<assess_operation<dereference,           definition, pack<type&&> >            ::value, typename assess_operation<dereference,           definition, pack<type&&> >            ::type>::type operate_dereference(type&& object)                              noexcept(noexcept(*std::declval<type>()))                           { return *std::forward<type>(object); }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<assess_operation<member_access,         definition, pack<type&&> >            ::value, typename assess_operation<member_access,         definition, pack<type&&> >            ::type>::type operate_member_access(type&& object)                            noexcept                                                            { return std::forward<type>(object); }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<assess_operation<minus,                 definition, pack<type&&> >            ::value, typename assess_operation<minus,                 definition, pack<type&&> >            ::type>::type operate_minus(type&& object)                                    noexcept(noexcept(-std::declval<type>()))                           { return -std::forward<type>(object); }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<assess_operation<negate,                definition, pack<type&&> >            ::value, typename assess_operation<negate,                definition, pack<type&&> >            ::type>::type operate_negate(type&& object)                                   noexcept(noexcept(!std::declval<type>()))                           { return !std::forward<type>(object); }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<assess_operation<plus,                  definition, pack<type&&> >            ::value, typename assess_operation<plus,                  definition, pack<type&&> >            ::type>::type operate_plus(type&& object)                                     noexcept(noexcept(+std::declval<type>()))                           { return +std::forward<type>(object); }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<assess_operation<post_decrement,        definition, pack<type&&> >            ::value, typename assess_operation<post_decrement,        definition, pack<type&&> >            ::type>::type operate_post_decrement(type&& object)                           noexcept(noexcept(std::declval<type>()--))                          { return std::forward<type>(object)--; }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<assess_operation<post_increment,        definition, pack<type&&> >            ::value, typename assess_operation<post_increment,        definition, pack<type&&> >            ::type>::type operate_post_increment(type&& object)                           noexcept(noexcept(std::declval<type>()++))                          { return std::forward<type>(object)++; }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<assess_operation<pre_decrement,         definition, pack<type&&> >            ::value, typename assess_operation<pre_decrement,         definition, pack<type&&> >            ::type>::type operate_pre_decrement(type&& object)                            noexcept(noexcept(--std::declval<type>()))                          { return --std::forward<type>(object); }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<assess_operation<pre_increment,         definition, pack<type&&> >            ::value, typename assess_operation<pre_increment,         definition, pack<type&&> >            ::type>::type operate_pre_increment(type&& object)                            noexcept(noexcept(++std::declval<type>()))                          { return ++std::forward<type>(object); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<add,                   definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<add,                   definition, pack<typeA&&, typeB&&> >  ::type>::type operate_add(typeA&& objectA, typeB&& objectB)                   noexcept(noexcept(std::declval<typeA>() +   std::declval<typeB>())) { return std::forward<typeA>(objectA) +   std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<assign,                definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign,                definition, pack<typeA&&, typeB&&> >  ::type>::type operate_assign(typeA&& objectA, typeB&& objectB)                noexcept(noexcept(std::declval<typeA>() =   std::declval<typeB>())) { return std::forward<typeA>(objectA) =   std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<assign_add,            definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_add,            definition, pack<typeA&&, typeB&&> >  ::type>::type operate_assign_add(typeA&& objectA, typeB&& objectB)            noexcept(noexcept(std::declval<typeA>() +=  std::declval<typeB>())) { return std::forward<typeA>(objectA) +=  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<assign_bitwise_and,    definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_bitwise_and,    definition, pack<typeA&&, typeB&&> >  ::type>::type operate_assign_bitwise_and(typeA&& objectA, typeB&& objectB)    noexcept(noexcept(std::declval<typeA>() &=  std::declval<typeB>())) { return std::forward<typeA>(objectA) &=  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<assign_bitwise_or,     definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_bitwise_or,     definition, pack<typeA&&, typeB&&> >  ::type>::type operate_assign_bitwise_or(typeA&& objectA, typeB&& objectB)     noexcept(noexcept(std::declval<typeA>() |=  std::declval<typeB>())) { return std::forward<typeA>(objectA) |=  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<assign_bitwise_xor,    definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_bitwise_xor,    definition, pack<typeA&&, typeB&&> >  ::type>::type operate_assign_bitwise_xor(typeA&& objectA, typeB&& objectB)    noexcept(noexcept(std::declval<typeA>() ^=  std::declval<typeB>())) { return std::forward<typeA>(objectA) ^=  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<assign_divide,         definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_divide,         definition, pack<typeA&&, typeB&&> >  ::type>::type operate_assign_divide(typeA&& objectA, typeB&& objectB)         noexcept(noexcept(std::declval<typeA>() /=  std::declval<typeB>())) { return std::forward<typeA>(objectA) /=  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<assign_left_shift,     definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_left_shift,     definition, pack<typeA&&, typeB&&> >  ::type>::type operate_assign_left_shift(typeA&& objectA, typeB&& objectB)     noexcept(noexcept(std::declval<typeA>() <<= std::declval<typeB>())) { return std::forward<typeA>(objectA) <<= std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<assign_modulo,         definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_modulo,         definition, pack<typeA&&, typeB&&> >  ::type>::type operate_assign_modulo(typeA&& objectA, typeB&& objectB)         noexcept(noexcept(std::declval<typeA>() %=  std::declval<typeB>())) { return std::forward<typeA>(objectA) %=  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<assign_multiply,       definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_multiply,       definition, pack<typeA&&, typeB&&> >  ::type>::type operate_assign_multiply(typeA&& objectA, typeB&& objectB)       noexcept(noexcept(std::declval<typeA>() *=  std::declval<typeB>())) { return std::forward<typeA>(objectA) *=  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<assign_right_shift,    definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_right_shift,    definition, pack<typeA&&, typeB&&> >  ::type>::type operate_assign_right_shift(typeA&& objectA, typeB&& objectB)    noexcept(noexcept(std::declval<typeA>() >>= std::declval<typeB>())) { return std::forward<typeA>(objectA) >>= std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<assign_subtract,       definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<assign_subtract,       definition, pack<typeA&&, typeB&&> >  ::type>::type operate_assign_subtract(typeA&& objectA, typeB&& objectB)       noexcept(noexcept(std::declval<typeA>() -=  std::declval<typeB>())) { return std::forward<typeA>(objectA) -=  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<bitwise_and,           definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<bitwise_and,           definition, pack<typeA&&, typeB&&> >  ::type>::type operate_bitwise_and(typeA&& objectA, typeB&& objectB)           noexcept(noexcept(std::declval<typeA>() &   std::declval<typeB>())) { return std::forward<typeA>(objectA) &   std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<bitwise_or,            definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<bitwise_or,            definition, pack<typeA&&, typeB&&> >  ::type>::type operate_bitwise_or(typeA&& objectA, typeB&& objectB)            noexcept(noexcept(std::declval<typeA>() |   std::declval<typeB>())) { return std::forward<typeA>(objectA) |   std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<bitwise_xor,           definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<bitwise_xor,           definition, pack<typeA&&, typeB&&> >  ::type>::type operate_bitwise_xor(typeA&& objectA, typeB&& objectB)           noexcept(noexcept(std::declval<typeA>() ^   std::declval<typeB>())) { return std::forward<typeA>(objectA) ^   std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<boolean_and,           definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<boolean_and,           definition, pack<typeA&&, typeB&&> >  ::type>::type operate_boolean_and(typeA&& objectA, typeB&& objectB)           noexcept(noexcept(std::declval<typeA>() &&  std::declval<typeB>())) { return std::forward<typeA>(objectA) &&  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<boolean_or,            definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<boolean_or,            definition, pack<typeA&&, typeB&&> >  ::type>::type operate_boolean_or(typeA&& objectA, typeB&& objectB)            noexcept(noexcept(std::declval<typeA>() ||  std::declval<typeB>())) { return std::forward<typeA>(objectA) ||  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<cast,                  definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<cast,                  definition, pack<typeA&&, typeB&&> >  ::type>::type operate_cast(typeA&& object)                                    noexcept(noexcept(static_cast<typeB>(std::declval<typeA>())))       { return static_cast<typeB>(std::forward<typeA>(object)); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<comma,                 definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<comma,                 definition, pack<typeA&&, typeB&&> >  ::type>::type operate_comma(typeA&& objectA, typeB&& objectB)                 noexcept(noexcept(std::declval<typeA>(),    std::declval<typeB>())) { return std::forward<typeA>(objectA),    std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<divide,                definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<divide,                definition, pack<typeA&&, typeB&&> >  ::type>::type operate_divide(typeA&& objectA, typeB&& objectB)                noexcept(noexcept(std::declval<typeA>() /   std::declval<typeB>())) { return std::forward<typeA>(objectA) /   std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<equals,                definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<equals,                definition, pack<typeA&&, typeB&&> >  ::type>::type operate_equals(typeA&& objectA, typeB&& objectB)                noexcept(noexcept(std::declval<typeA>() ==  std::declval<typeB>())) { return std::forward<typeA>(objectA) ==  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<equals_greater,        definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<equals_greater,        definition, pack<typeA&&, typeB&&> >  ::type>::type operate_equals_greater(typeA&& objectA, typeB&& objectB)        noexcept(noexcept(std::declval<typeA>() >=  std::declval<typeB>())) { return std::forward<typeA>(objectA) >=  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<equals_lesser,         definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<equals_lesser,         definition, pack<typeA&&, typeB&&> >  ::type>::type operate_equals_lesser(typeA&& objectA, typeB&& objectB)         noexcept(noexcept(std::declval<typeA>() <=  std::declval<typeB>())) { return std::forward<typeA>(objectA) <=  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<greater,               definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<greater,               definition, pack<typeA&&, typeB&&> >  ::type>::type operate_greater(typeA&& objectA, typeB&& objectB)               noexcept(noexcept(std::declval<typeA>() >   std::declval<typeB>())) { return std::forward<typeA>(objectA) >   std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<left_shift,            definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<left_shift,            definition, pack<typeA&&, typeB&&> >  ::type>::type operate_left_shift(typeA&& objectA, typeB&& objectB)            noexcept(noexcept(std::declval<typeA>() <<  std::declval<typeB>())) { return std::forward<typeA>(objectA) <<  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<lesser,                definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<lesser,                definition, pack<typeA&&, typeB&&> >  ::type>::type operate_lesser(typeA&& objectA, typeB&& objectB)                noexcept(noexcept(std::declval<typeA>() <   std::declval<typeB>())) { return std::forward<typeA>(objectA) <   std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<member_pointer_access, definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<member_pointer_access, definition, pack<typeA&&, typeB&&> >  ::type>::type operate_member_pointer_access(typeA&& objectA, typeB&& objectB) noexcept(noexcept(std::declval<typeA>() ->* std::declval<typeB>())) { return std::forward<typeA>(objectA) ->* std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<modulo,                definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<modulo,                definition, pack<typeA&&, typeB&&> >  ::type>::type operate_modulo(typeA&& objectA, typeB&& objectB)                noexcept(noexcept(std::declval<typeA>() %   std::declval<typeB>())) { return std::forward<typeA>(objectA) %   std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<multiply,              definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<multiply,              definition, pack<typeA&&, typeB&&> >  ::type>::type operate_multiply(typeA&& objectA, typeB&& objectB)              noexcept(noexcept(std::declval<typeA>() *   std::declval<typeB>())) { return std::forward<typeA>(objectA) *   std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<right_shift,           definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<right_shift,           definition, pack<typeA&&, typeB&&> >  ::type>::type operate_right_shift(typeA&& objectA, typeB&& objectB)           noexcept(noexcept(std::declval<typeA>() >>  std::declval<typeB>())) { return std::forward<typeA>(objectA) >>  std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<subscript,             definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<subscript,             definition, pack<typeA&&, typeB&&> >  ::type>::type operate_subscript(typeA&& objectA, typeB&& objectB)             noexcept(noexcept(std::declval<typeA>()[std::declval<typeB>()]))    { return std::forward<typeA>(objectA)[std::forward<typeB>(objectB)]; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<subtract,              definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<subtract,              definition, pack<typeA&&, typeB&&> >  ::type>::type operate_subtract(typeA&& objectA, typeB&& objectB)              noexcept(noexcept(std::declval<typeA>() -   std::declval<typeB>())) { return std::forward<typeA>(objectA) -   std::forward<typeB>(objectB); }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<assess_operation<unequals,              definition, pack<typeA&&, typeB&&> >  ::value, typename assess_operation<unequals,              definition, pack<typeA&&, typeB&&> >  ::type>::type operate_unequals(typeA&& objectA, typeB&& objectB)              noexcept(noexcept(std::declval<typeA>() !=  std::declval<typeB>())) { return std::forward<typeA>(objectA) !=  std::forward<typeB>(objectB); }

  template <enum opdef definition, typename type, typename... types> constexpr inline static typename std::enable_if<false == assess_operation<call,                  definition, pack<type&&, types&&...> >::value, invalid>::type operate_call(type&&, types&&...)                noexcept { return {}; }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<false == assess_operation<address,               definition, pack<type&&> >            ::value, invalid>::type operate_address(type&&)                         noexcept { return {}; }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<false == assess_operation<complement,            definition, pack<type&&> >            ::value, invalid>::type operate_complement(type&&)                      noexcept { return {}; }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<false == assess_operation<dereference,           definition, pack<type&&> >            ::value, invalid>::type operate_dereference(type&&)                     noexcept { return {}; }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<false == assess_operation<member_access,         definition, pack<type&&> >            ::value, invalid>::type operate_member_access(type&&)                   noexcept { return {}; }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<false == assess_operation<minus,                 definition, pack<type&&> >            ::value, invalid>::type operate_minus(type&&)                           noexcept { return {}; }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<false == assess_operation<negate,                definition, pack<type&&> >            ::value, invalid>::type operate_negate(type&&)                          noexcept { return {}; }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<false == assess_operation<plus,                  definition, pack<type&&> >            ::value, invalid>::type operate_plus(type&&)                            noexcept { return {}; }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<false == assess_operation<post_decrement,        definition, pack<type&&> >            ::value, invalid>::type operate_post_decrement(type&&)                  noexcept { return {}; }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<false == assess_operation<post_increment,        definition, pack<type&&> >            ::value, invalid>::type operate_post_increment(type&&)                  noexcept { return {}; }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<false == assess_operation<pre_decrement,         definition, pack<type&&> >            ::value, invalid>::type operate_pre_decrement(type&&)                   noexcept { return {}; }
  template <enum opdef definition, typename type>                    constexpr inline static typename std::enable_if<false == assess_operation<pre_increment,         definition, pack<type&&> >            ::value, invalid>::type operate_pre_increment(type&&)                   noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<add,                   definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_add(typeA&&, typeB&&)                   noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<assign,                definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign(typeA&&, typeB&&)                noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<assign_add,            definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_add(typeA&&, typeB&&)            noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<assign_bitwise_and,    definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_bitwise_and(typeA&&, typeB&&)    noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<assign_bitwise_or,     definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_bitwise_or(typeA&&, typeB&&)     noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<assign_bitwise_xor,    definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_bitwise_xor(typeA&&, typeB&&)    noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<assign_divide,         definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_divide(typeA&&, typeB&&)         noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<assign_left_shift,     definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_left_shift(typeA&&, typeB&&)     noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<assign_modulo,         definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_modulo(typeA&&, typeB&&)         noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<assign_multiply,       definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_multiply(typeA&&, typeB&&)       noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<assign_right_shift,    definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_right_shift(typeA&&, typeB&&)    noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<assign_subtract,       definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_assign_subtract(typeA&&, typeB&&)       noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<bitwise_and,           definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_bitwise_and(typeA&&, typeB&&)           noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<bitwise_or,            definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_bitwise_or(typeA&&, typeB&&)            noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<bitwise_xor,           definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_bitwise_xor(typeA&&, typeB&&)           noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<boolean_and,           definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_boolean_and(typeA&&, typeB&&)           noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<boolean_or,            definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_boolean_or(typeA&&, typeB&&)            noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<cast,                  definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_cast(typeA&&)                           noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<comma,                 definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_comma(typeA&&, typeB&&)                 noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<compare,               definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_compare(typeA&&, typeB&&)               noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<divide,                definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_divide(typeA&&, typeB&&)                noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<equals,                definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_equals(typeA&&, typeB&&)                noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<equals_greater,        definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_equals_greater(typeA&&, typeB&&)        noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<equals_lesser,         definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_equals_lesser(typeA&&, typeB&&)         noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<greater,               definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_greater(typeA&&, typeB&&)               noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<left_shift,            definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_left_shift(typeA&&, typeB&&)            noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<lesser,                definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_lesser(typeA&&, typeB&&)                noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<member_pointer_access, definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_member_pointer_access(typeA&&, typeB&&) noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<modulo,                definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_modulo(typeA&&, typeB&&)                noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<multiply,              definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_multiply(typeA&&, typeB&&)              noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<right_shift,           definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_right_shift(typeA&&, typeB&&)           noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<subscript,             definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_subscript(typeA&&, typeB&&)             noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<subtract,              definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_subtract(typeA&&, typeB&&)              noexcept { return {}; }
  template <enum opdef definition, typename typeA, typename typeB>   constexpr inline static typename std::enable_if<false == assess_operation<unequals,              definition, pack<typeA&&, typeB&&> >  ::value, invalid>::type operate_unequals(typeA&&, typeB&&)              noexcept { return {}; }

  #ifdef _MSC_VER
  # pragma warning(pop)
  #endif
}

template <typename base, class accessor = void, class mutator = void>
struct property {
  private:
    template <class subaccessor, bool = std::is_void<accessor>::value>
    struct accessor_t final {
      template <enum operation operation, typename subbase> constexpr inline static decltype(subaccessor::get(std::declval<subbase>(), instanceof<enum operation>())) value(typename std::enable_if<false != std::is_void<decltype(static_cast<void>(subaccessor::get(std::declval<subbase>(), instanceof<enum operation>())))>::value, subbase>::type&& value) noexcept { return subaccessor::get(std::forward<subbase>(value), operation); }
      template <enum operation operation, typename subbase> constexpr inline static decltype(subaccessor::get(std::declval<subbase>()))                               value(typename std::enable_if<false == std::is_void<decltype(static_cast<void>(subaccessor::get(std::declval<subbase>(), instanceof<enum operation>())))>::value, subbase>::type&& value) noexcept { return subaccessor::get(std::forward<subbase>(value)); }
    };

    template <class subaccessor>
    struct accessor_t<subaccessor, true> final {
      template <enum operation operation, typename subbase> constexpr inline static decltype(std::declval<subbase>()) value(subbase&& value) noexcept { return std::forward<subbase>(value); }
    };

    // ...
    enum base_t : unsigned char {
      aggregated = 0x1u, bounded, functional, referenced, unbounded
    };

    // ...
    template <class submutator, bool = std::is_void<mutator>::value>
    struct mutator_t final {
      template <enum operation operation, typename subbase, typename... types> constexpr inline static decltype(submutator::set(std::declval<subbase>(), instanceof<enum operation>(), std::declval<types>()...)) value(typename std::enable_if<false != std::is_void<decltype(static_cast<void>(submutator::set(std::declval<subbase>(), instanceof<enum operation>(), std::declval<types>()...)))>::value, subbase>::type&& value, types&&... arguments) noexcept { return submutator::set(std::forward<subbase>(value), operation, std::forward<types>(arguments)...); }
      template <enum operation operation, typename subbase, typename... types> constexpr inline static decltype(submutator::set(std::declval<subbase>(), std::declval<types>()...))                               value(typename std::enable_if<false == std::is_void<decltype(static_cast<void>(submutator::set(std::declval<subbase>(), instanceof<enum operation>(), std::declval<types>()...)))>::value, subbase>::type&& value, types&&... arguments) noexcept { return submutator::set(std::forward<subbase>(value), std::forward<types>(arguments)...); }
    };

    template <class submutator>
    struct mutator_t<submutator, true> final {
      template <enum operation operation, typename subbase> constexpr inline static typename std::enable_if<operation == post_decrement, decltype(std::declval<subbase>()--)>::type value(subbase&& value) noexcept { return (std::forward<subbase>(value))--; }
      template <enum operation operation, typename subbase> constexpr inline static typename std::enable_if<operation == post_increment, decltype(std::declval<subbase>()++)>::type value(subbase&& value) noexcept { return (std::forward<subbase>(value))++; }
      template <enum operation operation, typename subbase> constexpr inline static typename std::enable_if<operation == pre_decrement,  decltype(--std::declval<subbase>())>::type value(subbase&& value) noexcept { return --(std::forward<subbase>(value)); }
      template <enum operation operation, typename subbase> constexpr inline static typename std::enable_if<operation == pre_increment,  decltype(++std::declval<subbase>())>::type value(subbase&& value) noexcept { return ++(std::forward<subbase>(value)); }

      template <enum operation operation, typename subbase, typename type> constexpr inline static typename std::enable_if<operation == assign,             decltype(std::declval<subbase>() =   std::declval<type>())>::type value(subbase&& value, type&& argument) noexcept { return std::forward<subbase>(value) +=  std::forward<type>(argument); }
      template <enum operation operation, typename subbase, typename type> constexpr inline static typename std::enable_if<operation == assign_add,         decltype(std::declval<subbase>() +=  std::declval<type>())>::type value(subbase&& value, type&& argument) noexcept { return std::forward<subbase>(value) +=  std::forward<type>(argument); }
      template <enum operation operation, typename subbase, typename type> constexpr inline static typename std::enable_if<operation == assign_bitwise_and, decltype(std::declval<subbase>() &=  std::declval<type>())>::type value(subbase&& value, type&& argument) noexcept { return std::forward<subbase>(value) &=  std::forward<type>(argument); }
      template <enum operation operation, typename subbase, typename type> constexpr inline static typename std::enable_if<operation == assign_bitwise_or,  decltype(std::declval<subbase>() |=  std::declval<type>())>::type value(subbase&& value, type&& argument) noexcept { return std::forward<subbase>(value) |=  std::forward<type>(argument); }
      template <enum operation operation, typename subbase, typename type> constexpr inline static typename std::enable_if<operation == assign_bitwise_xor, decltype(std::declval<subbase>() ^=  std::declval<type>())>::type value(subbase&& value, type&& argument) noexcept { return std::forward<subbase>(value) ^=  std::forward<type>(argument); }
      template <enum operation operation, typename subbase, typename type> constexpr inline static typename std::enable_if<operation == assign_divide,      decltype(std::declval<subbase>() /=  std::declval<type>())>::type value(subbase&& value, type&& argument) noexcept { return std::forward<subbase>(value) /=  std::forward<type>(argument); }
      template <enum operation operation, typename subbase, typename type> constexpr inline static typename std::enable_if<operation == assign_left_shift,  decltype(std::declval<subbase>() <<= std::declval<type>())>::type value(subbase&& value, type&& argument) noexcept { return std::forward<subbase>(value) <<= std::forward<type>(argument); }
      template <enum operation operation, typename subbase, typename type> constexpr inline static typename std::enable_if<operation == assign_modulo,      decltype(std::declval<subbase>() %=  std::declval<type>())>::type value(subbase&& value, type&& argument) noexcept { return std::forward<subbase>(value) %=  std::forward<type>(argument); }
      template <enum operation operation, typename subbase, typename type> constexpr inline static typename std::enable_if<operation == assign_multiply,    decltype(std::declval<subbase>() *=  std::declval<type>())>::type value(subbase&& value, type&& argument) noexcept { return std::forward<subbase>(value) *=  std::forward<type>(argument); }
      template <enum operation operation, typename subbase, typename type> constexpr inline static typename std::enable_if<operation == assign_right_shift, decltype(std::declval<subbase>() >>= std::declval<type>())>::type value(subbase&& value, type&& argument) noexcept { return std::forward<subbase>(value) >>= std::forward<type>(argument); }
      template <enum operation operation, typename subbase, typename type> constexpr inline static typename std::enable_if<operation == assign_subtract,    decltype(std::declval<subbase>() -=  std::declval<type>())>::type value(subbase&& value, type&& argument) noexcept { return std::forward<subbase>(value) -=  std::forward<type>(argument); }
    };

    // ...
    typedef typename std::conditional<std::is_reference<base>::value, base, typename std::add_lvalue_reference<base>::type>::type lvalue_reference_t, reference_t;
    typedef typename std::conditional<std::is_reference<base>::value, base, typename std::add_rvalue_reference<base>::type>::type rvalue_reference_t;

    // ...
    template <typename subbase, unsigned char>
    struct value_t final {
      mutable subbase value;

      // ...
      template <typename type>
      constexpr inline value_t(type&& object) noexcept : value(std::forward<type>(object)) {}
    };

    template <typename subbase>
    struct value_t<subbase, aggregated> final {
      mutable subbase value;

      // ...
      template <typename... types>
      constexpr inline value_t(types&&... arguments) noexcept(noexcept(subbase(std::declval<types>()...))) : value(std::forward<types>(arguments)...) {}
    };

    template <typename subbase, std::size_t capacity>
    struct value_t<subbase [capacity], bounded> final {
      mutable subbase value[capacity];

      private:
        template <bool boolean, bool...>                          struct boolean_and                                  final { friend struct value_t; private: static bool const value = boolean; };
        template <bool booleanA, bool booleanB, bool... booleans> struct boolean_and<booleanA, booleanB, booleans...> final { friend struct value_t; private: static bool const value = boolean_and<booleanA && booleanB, booleans...>::value; };

        template <std::size_t index, std::size_t... indexes> struct index_sequence : public index_sequence<index - 1u, index, indexes...> {};
        template <std::size_t... indexes>                    struct index_sequence<0u, indexes...> {};

        // ...
        template <typename type, std::size_t... indexes> constexpr inline value_t(type array[], index_sequence<indexes...> const) noexcept(noexcept(subbase(instanceof<type>()))) : value{array[indexes]...} {}

      public:
        template <typename... types>                 constexpr inline value_t(types&&... elements)   noexcept(boolean_and<noexcept(subbase(std::declval<types>()))...>::value) : value{std::forward<types>(elements)...} {}
        template <typename type, std::size_t length> constexpr inline value_t(type (&array)[length]) noexcept(noexcept(value_t(instanceof<type (&)[length]>(), instanceof<index_sequence<length> >()))) : value_t<subbase[capacity], bounded>::value_t(array, index_sequence<length>{}) {}
    };

    template <typename subbase> // ->> Explicitly deter the user specifying a function type as the `base`
    struct value_t<subbase, functional>;

    template <typename subbase>
    struct value_t<subbase, referenced> final {
      subbase value;

      // ...
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
    inline property(types&&... arguments) noexcept : value(std::forward<types>(arguments)...) {
      std::puts(std::is_lvalue_reference<reference_t>::value ? "true" : "false");
    }

    // global,    // operator +(x, y)
    // implicit,  // x + y
    // namespaced // x.operator +(y)

    // ...
    constexpr friend decltype(operate_address<implicit>(accessor_t<accessor>::template value<address>(instanceof<lvalue_reference_t>()))) operator &(property const volatile&  property) noexcept(noexcept(accessor_t<accessor>::template value<address>(instanceof<lvalue_reference_t>()))) { return operate_address<implicit>(accessor_t<accessor>::template value<address>((lvalue_reference_t) property.value.value)); }
    constexpr friend decltype(operate_address<implicit>(accessor_t<accessor>::template value<address>(instanceof<rvalue_reference_t>()))) operator &(property const volatile&& property) noexcept(noexcept(accessor_t<accessor>::template value<address>(instanceof<rvalue_reference_t>()))) { return operate_address<implicit>(accessor_t<accessor>::template value<address>((rvalue_reference_t) property.value.value)); }

    // ...
    constexpr decltype(operate_member_access<namespaced>(accessor_t<accessor>::template value<member_access>(instanceof<lvalue_reference_t>()))) operator ->() const volatile noexcept(noexcept(accessor_t<accessor>::template value<member_access>(instanceof<lvalue_reference_t>()))) { return operate_member_access<namespaced>(accessor_t<accessor>::template value<member_access>((lvalue_reference_t) (this -> value.value))); }
    template <typename... types> constexpr decltype(operate_call<namespaced>(accessor_t<accessor>::template value<call>(instanceof<lvalue_reference_t>()))) operator ()(types&&... objects) const volatile noexcept(noexcept(operate_call<namespaced>(accessor_t<accessor>::template value<call>(instanceof<lvalue_reference_t>())))) { return operate_call<namespaced>(accessor_t<accessor>::template value<call, base>((lvalue_reference_t) (this -> value.value))); }

    // call,
    // cast,
    // comma,
    // complement,
    // dereference,
    // negate,
    // minus,
    // plus,
    // subscript

    // assign,
    // add,
    // assign_add,
    // divide,
    // assign_divide,
    // left_shift,
    // assign_left_shift,
    // modulo,
    // assign_modulo,
    // multiply,
    // assign_multiply,
    // right_shift,
    // assign_right_shift,
    // subtract,
    // assign_subtract,

    // bitwise_and,
    // assign_bitwise_and,
    // bitwise_or,
    // assign_bitwise_or,
    // bitwise_xor,
    // assign_bitwise_xor,

    // boolean_and,
    // boolean_or,

    // equals,
    // greater,
    // equals_greater,
    // lesser,
    // equals_lesser,
    // compare,
    // unequals,

    // member_pointer_access,

    // post_decrement,
    // post_increment,
    // pre_decrement,
    // pre_increment,
};

int function() { return 42; }
struct object {};
template struct property<int>;
template struct property<int&>;
// template struct property<int[]>;
template struct property<int[3]>;
// template struct property<int()>;
template struct property<object>;

/* Main */
int main(int, char*[]) /* noexcept */ {
  // std::printf("[int&]               : %4.5s" "\r\n", assess_operation<address, implicit, pack<int&> >               ::value ? "true" : "false");
  // std::printf("[int const&]         : %4.5s" "\r\n", assess_operation<address, implicit, pack<int const&> >         ::value ? "true" : "false");
  // std::printf("[int const volatile&]: %4.5s" "\r\n", assess_operation<address, implicit, pack<int const volatile&> >::value ? "true" : "false");
  // std::printf("[int volatile&]      : %4.5s" "\r\n", assess_operation<address, implicit, pack<int volatile&> >      ::value ? "true" : "false");
  // std::printf("[]: 0x%p" "\r\n", static_cast<void const*>(operate_address<implicit>(static_cast<int const&>(3))));
  // std::printf("[]: %i" "\r\n", *&property<int>{3});
  // std::printf("[]: %i" "\r\n", *&property<int const&>{static_cast<int const&>(3)});
  // std::printf("[]: %i" "\r\n", *&property<int const&>{3});
  // std::printf("[]: %i" "\r\n", *&property<int&&>{3});
}
