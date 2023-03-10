/* ... ->> See `struct $shorthand::operation_value::variant`
    --- CITE ---
      #Lapys:
        - Circle:                                             https://lapys.godbolt.org/z/qMn1qd43e
        - Clang, GNU, Intel, Microsoft Visual Studio, NVIDIA: https://lapys.godbolt.org/z/r3METo98K

    --- TODO ---
      #Lapys:
        - Optimize integral-only operations ie: `(($1 + $2) + $3) + $4` to `($1 + $2) + ($3 + $4)`, making them independent
        - Pre-compute constant operations
*/
#include <atomic>      // --> std::atomic_bool, std::atomic_char, std::atomic_char16_t, std::atomic_char32_t, std::atomic_char8_t, std::atomic_flag, std::atomic_int, std::atomic_int16_t, std::atomic_int32_t, std::atomic_int64_t, std::atomic_int8_t, std::atomic_int_fast16_t, std::atomic_int_fast32_t, std::atomic_int_fast64_t, std::atomic_int_fast8_t, std::atomic_int_least16_t, std::atomic_int_least32_t, std::atomic_int_least64_t, std::atomic_int_least8_t, std::atomic_intmax_t, std::atomic_intptr_t, std::atomic_llong, std::atomic_long, std::atomic_ptrdiff_t, std::atomic_schar, std::atomic_short, std::atomic_size_t, std::atomic_uchar, std::atomic_uint, std::atomic_uint16_t, std::atomic_uint32_t, std::atomic_uint64_t, std::atomic_uint8_t, std::atomic_uint_fast16_t, std::atomic_uint_fast32_t, std::atomic_uint_fast64_t, std::atomic_uint_fast8_t, std::atomic_uint_least16_t, std::atomic_uint_least32_t, std::atomic_uint_least64_t, std::atomic_uint_least8_t, std::atomic_uintmax_t, std::atomic_uintptr_t, std::atomic_ullong, std::atomic_ulong, std::atomic_ushort, std::atomic_wchar_t, std::memory_order
#include <climits>     //
#include <cstdarg>     // --> std::va_list
#include <cstddef>     // --> std::byte, std::max_align_t, std::nullptr_t
#include <cstdlib>     // --> std::div_t, std::ldiv_t, std::lldiv_t
#include <exception>   // --> std::bad_exception, std::exception, std::exception_ptr, std::nested_exception, std::terminate_handler, std::unexpected_handler
#include <functional>  // --> std::bad_function_call, std::bit_and<void>, std::bit_not<>, std::bit_or<void>, std::bit_xor<void>, std::divides<void>, std::equal_to<void>, std::greater<void>, std::greater_equal<void>, std::identity, std::less<void>, std::less_equal<void>, std::logical_and<void>, std::logical_not<void>, std::logical_or<void>, std::minus<void>, std::modulus<void>, std::multiplies<void>, std::negate<void>, std::not_equal_to<void>, std::plus<void>, decltype(std::placeholders::_1), decltype(std::placeholders::_2)
#include <iterator>    // --> std::bidirectional_iterator_tag, std::contiguous_iterator_tag, std::default_sentinel_t, std::forward_iterator_tag, std::input_iterator_tag, std::output_iterator_tag, std::random_access_iterator_tag, std::unreachable_sentinel_t
#include <memory>      // --> std::allocator_arg_t, std::bad_weak_ptr, std::owner_less<void>, std::pointer_safety
#include <new>         // --> std::align_val_t, std::bad_alloc, std::bad_array_new_length, std::destroying_delete_t, std::new_handler, std::nothrow_t
#include <ratio>       // --> std::atto, std::centi, std::deca, std::deci, std::exa, std::femto, std::giga, std::hecto, std::kilo, std::mega, std::micro, std::milli, std::nano, std::peta, std::pico, std::tera, std::yocto, std::yotta, std::zepto, std::zetta
#include <stdint.h>    //
#include <type_traits> // --> std::false_type, std::true_type, std::void_t
#include <typeinfo>    // --> std::bad_cast, std::bad_typeid, std::type_info
#include <utility>     // --> std::in_place_t, std::piecewise_construct_t
#if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 202002L || (defined(__circle_lang__) || defined(__clang__) || defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__GNUC__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER))
# include <version>
#endif
#ifdef __cpp_lib_endian
# include <bit> // --> std::endian
#endif
#ifdef __cpp_lib_three_way_comparison
# include <compare> // --> std::compare_three_way, std::compare_three_way_result, std::partial_ordering, std::strong_ordering, std::weak_ordering
# ifdef __cpp_lib_coroutine
#   include <coroutine> // --> std::coroutine_handle<void>, std::coroutine_handle<std::noop_coroutine_promise>, std::noop_coroutine_handle, std::noop_coroutine_promise, std::suspend_always, std::suspend_never
# endif
#endif
#ifdef __cpp_lib_ranges
# include <ranges> // --> std::dangling, std::from_range_t, std::subrange_kind
#endif
#ifdef __cpp_lib_source_location
# include <source_location> // --> std::source_location
#endif

/* ... ->> Functor expression, coerce-able to a free function */
struct $shorthand {
  private:
    // ... ->> Metafunction for evaluating operation validity without implicit rvalue-reference-qualification unlike `std::declval<...>()`
    template <typename type>
    constexpr static type instanceof() noexcept;

    // ... ->> Constants denoting the number of `$shorthand::operand`s in an `$shorthand::operation`
    enum class operation_arity : unsigned char {
      nullary  = 0u,
      unary    = 1u,
      binary   = 2u,
      ternary  = 3u,
      variadic = static_cast<unsigned char>(-1)
    };

    // ... ->> Metafunctions denoting C++ operators; used as type-agnostic `$shorthand::operation`s, which are un-preferably type-erased
    struct operation_information final {
      // ... -> Fallback metafunction
      struct nop {
        constexpr static bool   value               = false;
        constexpr static void (*valueof)() noexcept = nullptr;
      };

      template <typename = void, typename...> struct add                   final : public nop {};
      template <typename = void, typename...> struct address               final : public nop {};
      template <typename = void, typename...> struct assign                final : public nop {};
      template <typename = void, typename...> struct assign_add            final : public nop {};
      template <typename = void, typename...> struct assign_bitwise_and    final : public nop {};
      template <typename = void, typename...> struct assign_bitwise_or     final : public nop {};
      template <typename = void, typename...> struct assign_bitwise_xor    final : public nop {};
      template <typename = void, typename...> struct assign_divide         final : public nop {};
      template <typename = void, typename...> struct assign_left_shift     final : public nop {};
      template <typename = void, typename...> struct assign_modulo         final : public nop {};
      template <typename = void, typename...> struct assign_multiply       final : public nop {};
      template <typename = void, typename...> struct assign_right_shift    final : public nop {};
      template <typename = void, typename...> struct assign_subtract       final : public nop {};
      template <typename = void, typename...> struct bitwise_and           final : public nop {};
      template <typename = void, typename...> struct bitwise_or            final : public nop {};
      template <typename = void, typename...> struct bitwise_xor           final : public nop {};
      template <typename = void, typename...> struct boolean_and           final : public nop {};
      template <typename = void, typename...> struct boolean_or            final : public nop {};
      template <typename = void, typename...> struct call                  final : public nop {};
      template <typename = void, typename...> struct cast                  final : public nop {};
      template <typename = void, typename...> struct comma                 final : public nop {};
      template <typename = void, typename...> struct compare               final : public nop {};
      template <typename = void, typename...> struct complement            final : public nop {};
      template <typename = void, typename...> struct construct             final : public nop {};
      template <typename = void, typename...> struct dereference           final : public nop {};
      template <typename = void, typename...> struct destruct              final : public nop {};
      template <typename = void, typename...> struct divide                final : public nop {};
      template <typename = void, typename...> struct equals                final : public nop {};
      template <typename = void, typename...> struct equals_greater        final : public nop {};
      template <typename = void, typename...> struct equals_lesser         final : public nop {};
      template <typename = void, typename...> struct greater               final : public nop {};
      template <typename = void, typename...> struct initialize            final : public nop {};
      template <typename = void, typename...> struct left_shift            final : public nop {};
      template <typename = void, typename...> struct lesser                final : public nop {};
      template <typename = void, typename...> struct member_access         final : public nop {};
      template <typename = void, typename...> struct member_pointer_access final : public nop {};
      template <typename = void, typename...> struct minus                 final : public nop {};
      template <typename = void, typename...> struct modulo                final : public nop {};
      template <typename = void, typename...> struct multiply              final : public nop {};
      template <typename = void, typename...> struct negate                final : public nop {};
      template <typename = void, typename...> struct overloaded_address    final : public nop {};
      template <typename = void, typename...> struct plus                  final : public nop {};
      template <typename = void, typename...> struct post_decrement        final : public nop {};
      template <typename = void, typename...> struct post_increment        final : public nop {};
      template <typename = void, typename...> struct pre_decrement         final : public nop {};
      template <typename = void, typename...> struct pre_increment         final : public nop {};
      template <typename = void, typename...> struct right_shift           final : public nop {};
      template <typename = void, typename...> struct self                  final : public nop {};
      template <typename = void, typename...> struct subscript             final : public nop {};
      template <typename = void, typename...> struct subtract              final : public nop {};
      template <typename = void, typename...> struct ternary               final : public nop {};
      template <typename = void, typename...> struct unequal               final : public nop {};

      // ...
      template <typename base> struct address           <decltype(static_cast<void>(&instanceof<base>())),              base> final { static bool const value = true; constexpr static decltype(&instanceof<base>())              valueof(base&& operand) noexcept(noexcept(&instanceof<base>()))              { return &static_cast<base>(std::forward<base>(operand));              } };
      template <typename base> struct complement        <decltype(static_cast<void>(~instanceof<base>())),              base> final { static bool const value = true; constexpr static decltype(~instanceof<base>())              valueof(base&& operand) noexcept(noexcept(~instanceof<base>()))              { return ~static_cast<base>(std::forward<base>(operand));              } };
      template <typename base> struct dereference       <decltype(static_cast<void>(*instanceof<base>())),              base> final { static bool const value = true; constexpr static decltype(*instanceof<base>())              valueof(base&& operand) noexcept(noexcept(*instanceof<base>()))              { return *static_cast<base>(std::forward<base>(operand));              } };
      template <typename base> struct destruct          <decltype(static_cast<void>(instanceof<base>().~base())),       base> final { static bool const value = true; constexpr static decltype(instanceof<base>().~base())       valueof(base&& operand) noexcept(noexcept(instanceof<base>().~base()))       { return static_cast<base>(std::forward<base>(operand)).~base();       } };
      template <typename base> struct member_access     <decltype(static_cast<void>(instanceof<base>().operator ->())), base> final { static bool const value = true; constexpr static decltype(instanceof<base>().operator ->()) valueof(base&& operand) noexcept(noexcept(instanceof<base>().operator ->())) { return static_cast<base>(std::forward<base>(operand)).operator ->(); } };
      template <typename base> struct minus             <decltype(static_cast<void>(-instanceof<base>())),              base> final { static bool const value = true; constexpr static decltype(-instanceof<base>())              valueof(base&& operand) noexcept(noexcept(-instanceof<base>()))              { return -static_cast<base>(std::forward<base>(operand));              } };
      template <typename base> struct negate            <decltype(static_cast<void>(!instanceof<base>())),              base> final { static bool const value = true; constexpr static decltype(!instanceof<base>())              valueof(base&& operand) noexcept(noexcept(!instanceof<base>()))              { return !static_cast<base>(std::forward<base>(operand));              } };
      template <typename base> struct overloaded_address<decltype(static_cast<void>(instanceof<base>().operator &())),  base> final { static bool const value = true; constexpr static decltype(instanceof<base>().operator &())  valueof(base&& operand) noexcept(noexcept(instanceof<base>().operator &()))  { return static_cast<base>(std::forward<base>(operand)).operator &();  } };
      template <typename base> struct plus              <decltype(static_cast<void>(+instanceof<base>())),              base> final { static bool const value = true; constexpr static decltype(+instanceof<base>())              valueof(base&& operand) noexcept(noexcept(+instanceof<base>()))              { return +static_cast<base>(std::forward<base>(operand));              } };
      template <typename base> struct post_decrement    <decltype(static_cast<void>(instanceof<base>()--)),             base> final { static bool const value = true; constexpr static decltype(instanceof<base>()--)             valueof(base&& operand) noexcept(noexcept(instanceof<base>()--))             { return static_cast<base>(std::forward<base>(operand))--;             } };
      template <typename base> struct post_increment    <decltype(static_cast<void>(instanceof<base>()++)),             base> final { static bool const value = true; constexpr static decltype(instanceof<base>()++)             valueof(base&& operand) noexcept(noexcept(instanceof<base>()++))             { return static_cast<base>(std::forward<base>(operand))++;             } };
      template <typename base> struct pre_decrement     <decltype(static_cast<void>(--instanceof<base>())),             base> final { static bool const value = true; constexpr static decltype(--instanceof<base>())             valueof(base&& operand) noexcept(noexcept(--instanceof<base>()))             { return --static_cast<base>(std::forward<base>(operand));             } };
      template <typename base> struct pre_increment     <decltype(static_cast<void>(++instanceof<base>())),             base> final { static bool const value = true; constexpr static decltype(++instanceof<base>())             valueof(base&& operand) noexcept(noexcept(++instanceof<base>()))             { return ++static_cast<base>(std::forward<base>(operand));             } };
      template <typename base> struct self              <void,                                                          base> final { static bool const value = true; constexpr static decltype(instanceof<base>())               valueof(base&& operand) noexcept                                             { return static_cast<base>(std::forward<base>(operand));               } };

      template <typename baseA, typename baseB> struct add                  <decltype(static_cast<void>(instanceof<baseA>()   + instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()   + instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()   + instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))   + static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct assign               <decltype(static_cast<void>(instanceof<baseA>()   = instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()   = instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()   = instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))   = static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct assign_add           <decltype(static_cast<void>(instanceof<baseA>()  += instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  += instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  += instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  += static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct assign_bitwise_and   <decltype(static_cast<void>(instanceof<baseA>()  &= instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  &= instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  &= instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  &= static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct assign_bitwise_or    <decltype(static_cast<void>(instanceof<baseA>()  |= instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  |= instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  |= instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  |= static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct assign_bitwise_xor   <decltype(static_cast<void>(instanceof<baseA>()  ^= instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  ^= instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  ^= instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  ^= static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct assign_divide        <decltype(static_cast<void>(instanceof<baseA>()  /= instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  /= instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  /= instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  /= static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct assign_left_shift    <decltype(static_cast<void>(instanceof<baseA>() <<= instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>() <<= instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>() <<= instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA)) <<= static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct assign_modulo        <decltype(static_cast<void>(instanceof<baseA>()  %= instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  %= instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  %= instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  %= static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct assign_multiply      <decltype(static_cast<void>(instanceof<baseA>()  *= instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  *= instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  *= instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  *= static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct assign_right_shift   <decltype(static_cast<void>(instanceof<baseA>() >>= instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>() >>= instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>() >>= instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA)) >>= static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct assign_subtract      <decltype(static_cast<void>(instanceof<baseA>()  -= instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  -= instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  -= instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  -= static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct bitwise_and          <decltype(static_cast<void>(instanceof<baseA>()   & instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()   & instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()   & instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))   & static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct bitwise_or           <decltype(static_cast<void>(instanceof<baseA>()   | instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()   | instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()   | instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))   | static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct bitwise_xor          <decltype(static_cast<void>(instanceof<baseA>()   ^ instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()   ^ instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()   ^ instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))   ^ static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct boolean_and          <decltype(static_cast<void>(instanceof<baseA>()  && instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  && instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  && instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  && static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct boolean_or           <decltype(static_cast<void>(instanceof<baseA>()  || instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  || instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  || instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  || static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct cast                 <decltype(static_cast<void>((baseB) instanceof<baseA>())),                 baseA, baseB> final { static bool const value = true; constexpr static decltype((baseB) instanceof<baseA>())                   valueof(baseA&& operand)                    noexcept(noexcept((baseB) instanceof<baseA>()))                 { return (baseB) static_cast<baseA>(std::forward<baseA>(operand));                                                  } };
      template <typename baseA, typename baseB> struct comma                <decltype(static_cast<void>(instanceof<baseA>()   , instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()   , instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()   , instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))   , static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct divide               <decltype(static_cast<void>(instanceof<baseA>()   / instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()   / instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()   / instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))   / static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct equals               <decltype(static_cast<void>(instanceof<baseA>()  == instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  == instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  == instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  == static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct equals_greater       <decltype(static_cast<void>(instanceof<baseA>()  >= instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  >= instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  >= instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  >= static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct equals_lesser        <decltype(static_cast<void>(instanceof<baseA>()  <= instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  <= instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  <= instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  <= static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct greater              <decltype(static_cast<void>(instanceof<baseA>()   > instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()   > instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()   > instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))   > static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct left_shift           <decltype(static_cast<void>(instanceof<baseA>()  << instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  << instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  << instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  << static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct lesser               <decltype(static_cast<void>(instanceof<baseA>()   < instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()   < instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()   < instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))   < static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct member_pointer_access<decltype(static_cast<void>(instanceof<baseA>() ->* instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>() ->* instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>() ->* instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA)) ->* static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct modulo               <decltype(static_cast<void>(instanceof<baseA>()   % instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()   % instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()   % instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))   % static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct multiply             <decltype(static_cast<void>(instanceof<baseA>()   * instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()   * instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()   * instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))   * static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct right_shift          <decltype(static_cast<void>(instanceof<baseA>()  >> instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  >> instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  >> instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  >> static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct subscript            <decltype(static_cast<void>(instanceof<baseA>()[instanceof<baseB>()])),    baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()[instanceof<baseB>()]))    valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()[instanceof<baseB>()]))    { return (static_cast<baseA>(std::forward<baseA>(operandA))[static_cast<baseB>(std::forward<baseB>(operandB))]);    } };
      template <typename baseA, typename baseB> struct subtract             <decltype(static_cast<void>(instanceof<baseA>()   - instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()   - instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()   - instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))   - static_cast<baseB>(std::forward<baseB>(operandB))); } };
      template <typename baseA, typename baseB> struct unequal              <decltype(static_cast<void>(instanceof<baseA>()  != instanceof<baseB>())), baseA, baseB> final { static bool const value = true; constexpr static decltype((instanceof<baseA>()  != instanceof<baseB>())) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>()  != instanceof<baseB>())) { return (static_cast<baseA>(std::forward<baseA>(operandA))  != static_cast<baseB>(std::forward<baseB>(operandB))); } };

      #ifdef __cpp_impl_three_way_comparison
        template <typename baseA, typename baseB>
        struct compare<decltype(static_cast<void>(instanceof<baseA>() <=> instanceof<baseB>())), baseA, baseB> final {
          static bool const value = true;

          constexpr static decltype(instanceof<baseA>() <=> instanceof<baseB>()) valueof(baseA&& operandA, baseB&& operandB) noexcept(noexcept(instanceof<baseA>() <=> instanceof<baseB>())) {
            return (static_cast<baseA>(std::forward<baseA>(operandA)) <=> static_cast<baseB>(std::forward<baseB>(operandB)));
          }
        };
      #endif

      template <typename baseA, typename baseB, typename baseC>
      struct ternary<decltype(static_cast<void>(instanceof<baseA>() ? instanceof<baseB>() : instanceof<baseC>())), baseA, baseB, baseC> final {
        static bool const value = true;

        constexpr static decltype(instanceof<baseA>() ? instanceof<baseB>() : instanceof<baseC>()) valueof(baseA&& operandA, baseB&& operandB, baseC&& operandC) noexcept(noexcept(instanceof<baseA>() ? instanceof<baseB>() : instanceof<baseC>())) {
          return static_cast<baseA>(std::forward<baseA>(operandA)) ? static_cast<baseB>(std::forward<baseB>(operandB)) : static_cast<baseC>(std::forward<baseC>(operandC));
        }
      };

      template <typename base, typename... bases> struct call      <decltype(static_cast<void>(instanceof<base>()(instanceof<bases>()...))), base, bases...> final { static bool const value = true; constexpr static decltype(instanceof<base>()(instanceof<bases>()...)) valueof(base&& operand, bases&&... operands) noexcept(noexcept(instanceof<base>()(instanceof<bases>()...))) { return static_cast<base>(std::forward<base>(operand))(static_cast<base>(std::forward<bases>(operands))...); } };
      template <typename base, typename... bases> struct construct <decltype(static_cast<void>(base(instanceof<bases>()...))),               base, bases...> final { static bool const value = true; constexpr static base                                                 valueof(bases&&... operands)                 noexcept(noexcept(base(instanceof<bases>()...)))               { return base(static_cast<base>(std::forward<bases>(operands))...);                                           } };
      template <typename base, typename... bases> struct initialize<decltype(static_cast<void>(base{instanceof<bases>()...})),               base, bases...> final { static bool const value = true; constexpr static base                                                 valueof(bases&&... operands)                 noexcept(noexcept(base{instanceof<bases>()...}))               { return {static_cast<base>(std::forward<bases>(operands))...};                                               } };
    };

    // ... ->> `$shorthand::evaluation` of `$shorthand::operation` on `$shorthand::operand`s (or `$shorthand::$operand`s themselves)
    struct operation_value final {
      friend struct $shorthand;

      public:
        // ... ->> Flags denoting types optimized for constant evaluation from `$shorthand::operation_value` values
        enum class type : unsigned char {
          undefined = 0x0u, // ->> Unsupported for constant evaluation
          decimal, function, integer, method, pointer, property, standard
        };

      private:
        // ... ->> Statically-allocated object for persisting the `type::undefined` return values of `$shorthand::evaluation`
        template <typename base>
        struct allocation final {
          static struct type final {
            private:
              base value;

            public:
              template <typename type>
              void* operator =(type&&) const noexcept {
                std::puts("bruh");
                return NULL;
              }
          } value;
        };

        // ...
        struct qualifier final {
          // ... ->> Constants denoting type qualifiers (known array bound qualifiers are `std::size_t` representations of `enum type`)
          enum type : std::size_t {
            pointer   = static_cast<std::size_t>(-1),
            unbounded = static_cast<std::size_t>(-2)
          };

          // ... ->> Ordered list of type qualifiers (array bound, const-volatile, pointer, reference, ...)
          template <type...>
          struct collection final {
            // ... ->> Apply type qualifications onto specified `base`
            template <typename base>
            struct apply final {
              typedef base type;
            };
          };

          template <type qualifier, type... qualifiers>
          struct collection<qualifier, qualifiers...> final {
            // ... ->> See `struct collection<>::apply`
            template <typename base>
            struct apply final {
              typedef typename collection<qualifiers...>::template apply<
                typename std::conditional<qualifier == operation_value::qualifier::pointer,   base*,
                typename std::conditional<qualifier == operation_value::qualifier::unbounded, base[],
                  base[static_cast<std::size_t>(qualifier)]
                >::type>::type
              >::type type;
            };

            /* ... */
            constexpr static type value[] = {qualifier, qualifiers...};
          };

          // ...
          template <typename baseType, class baseCollection = qualifier::collection<> >
          struct collection_information {
            typedef baseType       base;
            typedef baseCollection collection;
          };

          template <typename base, type... qualifiers>                       struct collection_information<base&,                collection<qualifiers...> > : public collection_information<base, collection<qualifiers...> >                                         {};
          template <typename base, type... qualifiers>                       struct collection_information<base&&,               collection<qualifiers...> > : public collection_information<base, collection<qualifiers...> >                                         {};
          template <typename base, type... qualifiers>                       struct collection_information<base*,                collection<qualifiers...> > : public collection_information<base, collection<qualifiers..., qualifier::pointer> >                     {};
          template <typename base, type... qualifiers>                       struct collection_information<base* const,          collection<qualifiers...> > : public collection_information<base, collection<qualifiers..., qualifier::pointer> >                     {};
          template <typename base, type... qualifiers>                       struct collection_information<base* const volatile, collection<qualifiers...> > : public collection_information<base, collection<qualifiers..., qualifier::pointer> >                     {};
          template <typename base, type... qualifiers>                       struct collection_information<base* volatile,       collection<qualifiers...> > : public collection_information<base, collection<qualifiers..., qualifier::pointer> >                     {};
          template <typename base, type... qualifiers>                       struct collection_information<base[],               collection<qualifiers...> > : public collection_information<base, collection<qualifiers..., qualifier::unbounded> >                   {};
          template <typename base, std::size_t capacity, type... qualifiers> struct collection_information<base[capacity],       collection<qualifiers...> > : public collection_information<base, collection<qualifiers..., static_cast<qualifier::type>(capacity)> > {};
        };

        // ...
        template <typename base>
        struct type_information final {};

        // ... ->> `union` class (zero-cost) abstraction with generic members
        template <typename... bases>
        struct variant final {
          template <typename>
          struct is_convertible final {
            static bool const value = false;
          };

          // ...
          template <typename = void>
          struct is_explicitly_destructible final {
            static bool const value = false;
          };

          // ...
          template <typename>
          struct is_initializable final {
            static bool const value = false;
          };

          /* ... */
          template <typename type>
          constexpr variant(type&&) noexcept {}
        };

        template <typename base, typename... bases>
        struct variant<base, bases...> final {
          template <typename = void>
          struct is_explicitly_destructible final {
            static bool const value = operation_information::destruct<void, base>::value && false == std::is_trivially_destructible<base>::value;
          };

          // ...
          template <typename subbase>
          struct is_convertible final {
            static bool const value = false == is_explicitly_destructible<>::value && (
              operation_information::cast<void, base&, subbase>::value ||
              variant<bases...>::template is_convertible  <subbase>::value
            );
          };

          // ...
          template <typename subbase>
          struct is_initializable final {
            static bool const value = false == is_explicitly_destructible<>::value && (
              operation_information::construct<void, typename std::conditional<std::is_reference<base>::value, base const volatile&, base>::type, subbase>::value ||
              variant<bases...>::template is_initializable<subbase>::value
            );
          };

          // ... --- TODO (Lapys) -> Standard members must all be copy-constructed
          template <typename subbase>
          struct nonmember final {
            template <typename type, typename std::enable_if<std::is_same<subbase, typename std::remove_cv<typename std::remove_reference<type>::type>::type>::value, std::nullptr_t>::type = nullptr>
            constexpr nonmember(type&&) noexcept = delete;
          };

          // ...
          template <typename subbase, typename = void>
          struct member {
            typename std::conditional<std::is_lvalue_reference<base>::value, typename std::remove_reference<base>::type const volatile&,
            typename std::conditional<std::is_rvalue_reference<base>::value, typename std::remove_reference<base>::type const volatile&&,
              typename std::conditional<is_explicitly_destructible<>::value, nonmember, base>::type
            >::type>::type value;

            /* ... */
            template <typename type>
            constexpr member(type&& value) noexcept(noexcept(decltype(member::value)(std::declval<type>()))) :
              value(std::forward<type>(value))
            {}
          };

          template <typename subbase>
          struct member<subbase, typename std::enable_if<operation_information::construct<void, subbase, subbase>::value, void>::type> final : public member<subbase, std::nullptr_t> {
            template <typename type>
            constexpr member(type&& value) noexcept(noexcept((decltype(member::value)) std::declval<type>()) && noexcept(decltype(member::value)(instanceof<decltype(member::value)>()))) :
              member<subbase, std::nullptr_t>::member((decltype(member::value)) std::forward<type>(value))
            {}
          };

          /* ... */
          union {
            variant<bases...> next;
            member <base>     value;
          };

          /* ... */
          template <typename type, typename std::enable_if<is_initializable<type&&>::value && false != operation_information::construct<void, base, type&&>::value, std::nullptr_t>::type = nullptr>
          constexpr variant(type&& value) noexcept(noexcept(member<base>(std::declval<type>()))) :
            value(std::forward<type>(value))
          {}

          template <typename type, typename std::enable_if<is_initializable<type&&>::value && false == operation_information::construct<void, base, type&&>::value, std::nullptr_t>::type = nullptr>
          constexpr variant(type&& value) noexcept(noexcept(variant<bases...>(std::declval<type>()))) :
            next(std::forward<type>(value))
          {}

          /* ... */
          template <typename type, typename std::enable_if<is_convertible<type&&>::value && false != operation_information::cast<void, base, type&>::value, std::nullptr_t>::type = nullptr>
          constexpr operator type&() const noexcept {
            return (type&) this -> value.value;
          }

          template <typename type, typename std::enable_if<is_convertible<type&&>::value && false == operation_information::cast<void, base, type&>::value, std::nullptr_t>::type = nullptr>
          constexpr operator type&() const noexcept {
            return (type&) this -> next;
          }
        };

        // ... ->> Constant-evaluated representation of `$shorthand::operation_value` values
        struct value final {
          friend struct operation_value;

          private:
            union {
              unsigned char               initializer : 1; //
              long double                 decimal;         // ->> Preserves floating-point          value
              void                      (*function)();     // ->> Preserves (free) function pointer value
              uintmax_t                   integer;         // ->> Preserves integer                 value
              void         ($shorthand::* method)();       // ->> Preserves function member pointer value
              void                       *pointer;         // ->> Preserves object pointer          value
              unsigned char $shorthand::* property;        // ->> Preserves data member pointer     value
              variant<                                     // ->> Preserves (freestanding-implementation only) standard library container value --- TODO (Lapys) -> Consider possibly-attributed types like `std::va_list`?
                std::allocator_arg_t, std::atomic_bool, std::atomic_char, std::atomic_flag, std::atomic_int, std::atomic_int_fast16_t, std::atomic_int_fast32_t, std::atomic_int_fast64_t, std::atomic_int_fast8_t, std::atomic_int_least16_t, std::atomic_int_least32_t, std::atomic_int_least64_t, std::atomic_int_least8_t, std::atomic_intmax_t, std::atomic_llong, std::atomic_long, std::atomic_ptrdiff_t, std::atomic_schar, std::atomic_short, std::atomic_size_t, std::atomic_uchar, std::atomic_uint, std::atomic_uint_fast16_t, std::atomic_uint_fast32_t, std::atomic_uint_fast64_t, std::atomic_uint_fast8_t, std::atomic_uint_least16_t, std::atomic_uint_least32_t, std::atomic_uint_least64_t, std::atomic_uint_least8_t, std::atomic_uintmax_t, std::atomic_ullong, std::atomic_ulong, std::atomic_ushort, std::atomic_wchar_t, std::atto,
                std::bad_alloc, std::bad_array_new_length, std::bad_cast, std::bad_exception, std::bad_function_call, std::bad_typeid, std::bad_weak_ptr, std::bidirectional_iterator_tag,
                std::centi,
                std::deca, std::deci, std::div_t,
                std::exa, std::exception, std::exception_ptr,
                std::false_type, std::femto, std::forward_iterator_tag,
                std::giga,
                std::hecto,
                std::input_iterator_tag,
                std::kilo,
                std::ldiv_t, std::lldiv_t,
                std::max_align_t, std::mega, std::memory_order, std::micro, std::milli,
                std::nano, std::nested_exception, std::new_handler, std::nothrow_t, std::nullptr_t,
                std::output_iterator_tag, std::owner_less<void>,
                std::peta, std::pico, std::piecewise_construct_t,
                std::random_access_iterator_tag,
                std::tera, std::terminate_handler, std::true_type, std::type_info const&,
                std::va_list*, std::va_list const*, std::va_list const volatile*, std::va_list volatile*,
                decltype(std::placeholders::_1), decltype(std::placeholders::_2),
                #ifdef __cpp_aligned_new
                  std::align_val_t,
                #endif
                #ifdef __cpp_char8_t
                  std::atomic_char8_t,
                #endif
                #ifdef __cpp_lib_byte
                  std::byte,
                #endif
                #ifdef __cpp_lib_endian
                  std::endian,
                #endif
                #ifdef __cpp_lib_ranges
                  std::dangling,
                  std::from_range_t,
                  std::subrange_kind,
                #endif
                #ifdef __cpp_lib_source_location
                  std::source_location,
                #endif
                #ifdef __cpp_lib_three_way_comparison
                  std::compare_three_way, std::compare_three_way_result,
                  std::partial_ordering,
                  std::strong_ordering,
                  std::weak_ordering,
                  #ifdef __cpp_lib_coroutine
                    std::coroutine_handle<void>, std::coroutine_handle<std::noop_coroutine_promise>,
                    std::noop_coroutine_handle, std::noop_coroutine_promise,
                    std::suspend_always, std::suspend_never,
                  #endif
                #endif
                #ifdef __cpp_unicode_characters
                  std::atomic_char16_t, std::atomic_char32_t,
                #endif
                #if defined(INT16_MAX) && defined(INT16_MIN)
                  std::atomic_int16_t,
                #endif
                #if defined(INT32_MAX) && defined(INT32_MIN)
                  std::atomic_int32_t,
                #endif
                #if defined(INT64_MAX) && defined(INT64_MIN)
                  std::atomic_int64_t,
                #endif
                #if defined(INT8_MAX)  && defined(INT8_MIN)
                  std::atomic_int8_t,
                #endif
                #if defined(INTPTR_MAX) && defined(INTPTR_MIN)
                  std::atomic_intptr_t,
                #endif
                #if defined(UINT16_MAX) && defined(UINT16_MIN)
                  std::atomic_uint16_t,
                #endif
                #if defined(UINT32_MAX) && defined(UINT32_MIN)
                  std::atomic_uint32_t,
                #endif
                #if defined(UINT64_MAX) && defined(UINT64_MIN)
                  std::atomic_uint64_t,
                #endif
                #if defined(UINT8_MAX)  && defined(UINT8_MIN)
                  std::atomic_uint8_t,
                #endif
                #if defined(UINTPTR_MAX) && defined(UINTPTR_MIN)
                  std::atomic_uintptr_t,
                #endif
                #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 201402L
                  std::bit_and      <void>, // --> $bitwise_and
                  std::bit_not      <>    , // --> $complement
                  std::bit_or       <void>, // --> $bitwise_or
                  std::bit_xor      <void>, // --> $bitwise_xor
                  std::divides      <void>, // --> $divide
                  std::equal_to     <void>, // --> $equals
                  std::greater      <void>, // --> $greater
                  std::greater_equal<void>, // --> $equals_greater
                  std::less         <void>, // --> $lesser
                  std::less_equal   <void>, // --> $equals_lesser
                  std::logical_and  <void>, // --> $boolean_and
                  std::logical_not  <void>, // --> $negate
                  std::logical_or   <void>, // --> $boolean_or
                  std::minus        <void>, // --> $subtract
                  std::modulus      <void>, // --> $modulo
                  std::multiplies   <void>, // --> $multiply
                  std::negate       <void>, // --> $minus
                  std::not_equal_to <void>, // --> $unequals
                  std::plus         <void>, // --> $add
                #endif
                #if ((defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) < 201703L) && false == defined(__clang__)
                  std::unexpected_handler,
                #endif
                #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 201703L
                  std::in_place_t,
                #endif
                #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 202002L
                  std::contiguous_iterator_tag,
                  std::default_sentinel_t, std::destroying_delete_t,
                  std::identity, // --> $self
                  std::unreachable_sentinel_t,
                #endif
                #if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) <= 202002L // --> < 2023..L
                  std::pointer_safety,
                #endif
                unsigned char
              > standard;
            };

          public:
            operation_value::type const type;

            /* ... */
            constexpr value() noexcept :
              initializer(),
              type       (operation_value::type::undefined)
            {}

            template <typename type, typename std::enable_if<std::is_floating_point<typename std::remove_reference<type>::type>::value, std::nullptr_t>::type = nullptr>
            constexpr value(type&& value) noexcept :
              decimal(value),
              type   (operation_value::type::decimal)
            {}

            template <typename type, typename std::enable_if<std::is_function<typename std::remove_pointer<typename std::remove_reference<type>::type>::type>::value, std::nullptr_t>::type = nullptr>
            constexpr value(type&& value) noexcept :
              function((void (*)()) value),
              type    (operation_value::type::function)
            {}

            template <typename type, typename std::enable_if<std::is_enum<typename std::remove_reference<type>::type>::value || std::is_integral<typename std::remove_reference<type>::type>::value, std::nullptr_t>::type = nullptr>
            constexpr value(type&& value) noexcept :
              integer(+value),
              type   (operation_value::type::integer)
            {}

            template <typename type, typename std::enable_if<std::is_pointer<typename std::remove_reference<type>::type>::value || std::is_same<decltype(nullptr), typename std::remove_cv<typename std::remove_reference<type>::type>::type>::value, std::nullptr_t>::type = nullptr>
            constexpr value(type&& value) noexcept :
              pointer(const_cast<void*>(static_cast<void const volatile*>(value))),
              type   (operation_value::type::pointer)
            {}

            template <typename type, typename std::enable_if<std::is_member_pointer<typename std::remove_reference<type>::type>::value, std::nullptr_t>::type = nullptr>
            constexpr value(type&& value) noexcept :
              property((unsigned char $shorthand::*) value),
              type    (operation_value::type::property)
            {}

            template <typename type, typename std::enable_if<operation_information::construct<void, decltype(value::standard), type&&>::value && false == (
              std::is_enum                   <typename std::remove_reference<type>::type>                                               ::value ||
              std::is_floating_point         <typename std::remove_reference<type>::type>                                               ::value ||
              std::is_function               <typename std::remove_pointer<typename std::remove_reference<type>::type>::type>           ::value ||
              std::is_integral               <typename std::remove_reference<type>::type>                                               ::value ||
              std::is_pointer                <typename std::remove_reference<type>::type>                                               ::value ||
              std::is_member_function_pointer<typename std::remove_reference<type>::type>                                               ::value ||
              std::is_member_pointer         <typename std::remove_reference<type>::type>                                               ::value ||
              std::is_same                   <std::nullptr_t, typename std::remove_cv<typename std::remove_reference<type>::type>::type>::value
            ), std::nullptr_t>::type = nullptr>
            constexpr value(type&& value) noexcept(noexcept(decltype(value::standard)(std::declval<type>()))) :
              standard(std::forward<type>(value)),
              type    (operation_value::type::standard)
            {}

            #ifndef _MSC_VER
              template <typename type, typename std::enable_if<std::is_member_function_pointer<typename std::remove_reference<type>::type>::value, std::nullptr_t>::type = nullptr>
              constexpr value(type&& value) noexcept :
                method((void ($shorthand::*)()) value),
                type  (operation_value::type::method)
              {}
            #endif
        };

      /* ... */
      private:
        std::type_info const                                  &baseType;           // ->> Base type information of value evaluated from `$shorthand`
        typename operation_value::qualifier::type const        qualifiers[12];     // ->> Type qualifier(s) of value evaluated from `$shorthand`; Presumed maximum of     12 to 256 type-qualifiers
        typename operation_value::qualifier::type const *const extendedQualifiers; // ->>                                                         Extended maximum beyond 12 to 256 type-qualifiers
        void                                            *const reference;          // ->> Reference to value evaluated from `$shorthand`; Preserves object representation

      public:
        operation_value::value const  value;     // ->> Representation   of value evaluated from `$shorthand`; Preserves value  representation
        std::size_t            const  alignment; // ->> Byte offset      of value evaluated from `$shorthand`
        std::size_t            const  size;      // ->> Byte size        of value evaluated from `$shorthand`
        std::type_info         const &type;      // ->> Type information of value evaluated from `$shorthand`

      /* ... */
      private:
        constexpr explicit operation_value() noexcept = delete;

        template <typename type, typename base, qualifier::type... baseQualifiers, typename std::enable_if<false != operation_information::construct<void, decltype(operation_value::value), type&&>::value, std::nullptr_t>::type = nullptr>
        constexpr explicit operation_value(type&& value, void const volatile* const address, type_information<base> const, qualifier::collection<baseQualifiers...> const, qualifier::type const extendedQualifiers[]) noexcept(noexcept(decltype(operation_value::value)(std::declval<type>()))) :
          baseType          (typeid(base)),               // ->> Compile-time
          qualifiers        {baseQualifiers...},          // ->> Compile-time
          extendedQualifiers(extendedQualifiers),         // ->> Possibly statically-allocated compile-time
          reference         (const_cast<void*>(address)), // ->> Possibly compile-time address-of
          value             (std::forward<type>(value)),  // ->> Possibly compile-time object (and copy-initialization)
          alignment         (alignof(type)),              // ->> Compile-time
          size              (sizeof (type)),              // ->> Compile-time
          type              (typeid (type))               // ->> Compile-time
        {}

        template <typename type, typename base, qualifier::type... baseQualifiers, typename std::enable_if<false == operation_information::construct<void, decltype(operation_value::value), type&&>::value, std::nullptr_t>::type = nullptr>
        constexpr explicit operation_value(type&&, void const volatile* const address, type_information<base> const, qualifier::collection<baseQualifiers...> const, qualifier::type const extendedQualifiers[]) noexcept :
          baseType          (typeid(base)),               //
          qualifiers        {baseQualifiers...},          //
          extendedQualifiers(extendedQualifiers),         //
          reference         (const_cast<void*>(address)), //
          value             (),                           // ->> Compile-time; See previous declaration of `operation_value(...)`
          alignment         (alignof(type)),              //
          size              (sizeof (type)),              //
          type              (typeid (type))               //
        {}

        template <typename type, typename base = type, qualifier::type... qualifiers, typename std::enable_if<sizeof...(qualifiers) == sizeof(decltype(operation_value::qualifiers)) / sizeof(qualifier::type), std::nullptr_t>::type = nullptr>
        constexpr explicit operation_value(type&& value, void const volatile* const address, type_information<base> const, qualifier::collection<qualifiers...> const) noexcept(noexcept(operation_value(std::declval<type>(), NULL, type_information<base>{}, {}, NULL))) :
          operation_value::operation_value(std::forward<type>(value), address, type_information<base>{}, qualifier::collection<qualifiers...>{}, NULL)
        {}

        template <typename type, typename base = type, qualifier::type... qualifiers, typename std::enable_if<(sizeof...(qualifiers) < sizeof(decltype(operation_value::qualifiers)) / sizeof(qualifier::type)), std::nullptr_t>::type = nullptr>
        constexpr explicit operation_value(type&& value, void const volatile* const address, type_information<base> const, qualifier::collection<qualifiers...> const) noexcept(noexcept(operation_value(std::declval<type>(), NULL, type_information<base>{}, {}, NULL))) :
          operation_value::operation_value(std::forward<type>(value), address, type_information<base>{}, qualifier::collection<qualifiers..., static_cast<qualifier::type>(0x0u)>{}, NULL)
        {}

        template <typename type, typename base = type, qualifier::type... qualifiers, typename std::enable_if<(sizeof...(qualifiers) > sizeof(decltype(operation_value::qualifiers)) / sizeof(qualifier::type)), std::nullptr_t>::type = nullptr>
        constexpr explicit operation_value(type&& value, void const volatile* const address, type_information<base> const, qualifier::collection<qualifiers...> const) noexcept(noexcept(operation_value(std::declval<type>(), NULL, type_information<base>{}, {}, NULL))) :
          operation_value::operation_value(std::forward<type>(value), address, type_information<base>{}, qualifier::collection<static_cast<qualifier::type>(0x0u)>{}, qualifier::collection<qualifiers...>::value)
        {}

        // ... ->> `$shorthand::operand`s only
        template <typename type, typename std::enable_if<false != (
          std::is_reference<type>::value ||
          operation_information::construct<void, decltype(operation_value::value), type&&>::value
        ), std::nullptr_t>::type = nullptr>
        constexpr operation_value(operation_value (*const)(operation_value const[]), type&& value) noexcept(noexcept(operation_value(std::declval<type>()))) :
          operation_value::operation_value(std::forward<type>(value))
        {}

        template <typename type, typename std::enable_if<false == (
          std::is_reference<type>::value ||
          operation_information::construct<void, decltype(operation_value::value), type&&>::value
        ), std::nullptr_t>::type = nullptr>
        constexpr operation_value(operation_value (*const)(operation_value const[]), type&& value) noexcept(noexcept(operation_value(instanceof<type&&>()))) :
          operation_value::operation_value(static_cast<type&&>(value))
        {}

      public:
        template <typename type, typename std::enable_if<(
          std::is_lvalue_reference<type>::value &&
          false != operation_information::overloaded_address<void, type&&>::value
        ), std::nullptr_t>::type = nullptr>
        inline operation_value(type&& value) noexcept(noexcept(operation_value(std::declval<type>(), NULL, {}, {}))) :
          operation_value::operation_value(
            std::forward<type>(value),
            &const_cast<unsigned char&>(reinterpret_cast<unsigned char const volatile&>(value)),
            type_information<typename qualifier::collection_information<type>::base>{},
            typename qualifier::collection_information<type>::collection{}
          )
        {}

        template <typename type, typename std::enable_if<(
          std::is_lvalue_reference<type>::value &&
          false == operation_information::overloaded_address<void, type&&>::value
        ), std::nullptr_t>::type = nullptr>
        constexpr operation_value(type&& value) noexcept(noexcept(operation_value(std::declval<type>(), NULL, {}, {}))) :
          operation_value::operation_value(
            std::forward<type>(value),
            &value,
            type_information<typename qualifier::collection_information<type>::base>{},
            typename qualifier::collection_information<type>::collection{}
          )
        {}

        template <typename type, typename std::enable_if<(
          std::is_rvalue_reference<type>::value
        ), std::nullptr_t>::type = nullptr>
        constexpr operation_value(type&& value) noexcept(noexcept(operation_value(instanceof<typename std::remove_reference<type>::type&>()))) :
          operation_value::operation_value((typename std::remove_reference<type>::type&) value)
        {}

        template <typename type, typename std::enable_if<(
          false == std::is_reference<type>::value &&
          false != operation_information::construct<void, decltype(operation_value::value), type&&>::value
        ), std::nullptr_t>::type = nullptr>
        constexpr operation_value(type&& value) noexcept(noexcept(operation_value(std::declval<type>(), NULL, {}, {}))) :
          operation_value::operation_value(
            std::forward<type>(value),
            NULL,
            type_information<typename qualifier::collection_information<type>::base>{},
            typename qualifier::collection_information<type>::collection{}
          )
        {}

        template <typename type, typename std::enable_if<(
          false == std::is_reference<type>::value                                                             &&
          false == operation_information::construct<void, decltype(operation_value::value),    type&&>::value &&
          false != operation_information::construct<void, typename std::remove_cv<type>::type, type&&>::value
        ), std::nullptr_t>::type = nullptr>
        constexpr /* inline */ operation_value(type&& value) noexcept(noexcept(operation_value(std::declval<type>(), NULL, {}, {}))) :
          operation_value::operation_value(
            std::forward<type>(value),
            (allocation<typename std::remove_cv<type>::type>::value = std::forward<type>(value)),
            type_information<typename qualifier::collection_information<type>::base>{},
            typename qualifier::collection_information<type>::collection{}
          )
        {}

        template <typename type, typename std::enable_if<(
          false == std::is_reference<type>::value                                                             &&
          false == operation_information::construct<void, decltype(operation_value::value),    type&&>::value &&
          false == operation_information::construct<void, typename std::remove_cv<type>::type, type&&>::value
        ), std::nullptr_t>::type = nullptr>
        constexpr operation_value(type&&) noexcept = delete;

        /* ... */
        // #ifdef __circle_lang__
        // #else
        //   template <typename type>
        //   constexpr operator type() const noexcept {
        //     typedef allocation<typename std::remove_cv<typename std::remove_reference<type>::type>::type> allocation;
        //     return ...;
        //   }
        // #endif
    };

  public:
    typedef $shorthand::operation_value evaluation;
    typedef $shorthand::operation_value operand;

    // ... ->> Type-erased function without generic or template template function parameters available ie: `auto (*)(auto&&...)`
    typedef $shorthand::evaluation (*operation)($shorthand::operand const[]);

  private:
    typedef $shorthand::evaluation (*$void)($shorthand::operand const[]); // ->> Disambiguation trait type; used for SFINAE/ specializations

    /* ... */
    constexpr static $shorthand::evaluation (*$voidop)($shorthand::operand const[]) noexcept = nullptr;

    public: template <class information, unsigned char arity>
    static $shorthand::evaluation $op($shorthand::operand const[]) noexcept(false) /* --> throw(std::runtime_error) */ {
      return {[]{}};
      // return {42};
    }
};
  template <typename base>
  typename $shorthand::operation_value::allocation<base>::type $shorthand::operation_value::allocation<base>::value = {};

#include <cstdio>
int main() { $shorthand::$op<void, 0u>(NULL); }

// /* Main */
// #include <cstdio>

// // ...
// template <intmax_t value>
// struct $int : public $s<value> {
//   constexpr static $void (*$fused_multiply_add)($operand const (&&operands)[], ) noexcept(false) {
//     return $voidop;
//   }

//   template <class... $shorthands>
//   constexpr $expression<$int::$fused_multiply_add, $<>, $<>, $<> > fused_multiply_add($shorthands&&... operands) const volatile noexcept(noexcept(...)) {
//     return {*this, std::forward<$shorthands>(operands)...};
//   }
// };

// (int) $int<a>{}.fused_multiply_add($s<b>{}, $s<c>{})

// // ...
// int main(int, char*[]) /* noexcept */ {
//   /* Function call */
//   $0(static_cast<void*>(NULL), 1, 2.0);                               // --> void
//   std::printf("[]: %p" "\r\n", $1(static_cast<void*>(NULL), 1, 2.0)); // --> void*&&
//   std::printf("[]: %i" "\r\n", $2(static_cast<void*>(NULL), 1, 2.0)); // --> int  &&
//   std::printf("[]: %f" "\r\n", $3(static_cast<void*>(NULL), 1, 2.0)); // --> float&&
//   std::puts("...");

//   /* Function cast */
//   typedef int (function)(int, ...); // ->> Variadics supported, but the optional arguments get ignored

//   #if defined(__circle_lang__) || defined(__clang__)                                                  //
//     std::printf("[]: %i"    "\r\n", static_cast<function*>($1)(3));                                   // --> int&&
//     std::printf("[]: %4.5s" "\r\n", static_cast<function*>($1) == (function*) $1 ? "true" : "false"); // ->> Conversion operator call
//   #else                                                                                               //
//     std::printf("[]: %i"    "\r\n", $1.operator function*()(3));                                      // --> int&&
//     std::printf("[]: %i"    "\r\n", $1.operator function&()(3));                                      // --> int&&
//     std::printf("[]: %4.5s" "\r\n", $1.operator function*() == (function*) $1 ? "true" : "false");    // ->> Conversion operator call
//     std::printf("[]: %4.5s" "\r\n", $1.operator function&() == (function&) $1 ? "true" : "false");    // ->> Wary of cast-to-reference
//   #endif                                                                                              //
//   std::puts("...");

//   /* Constructor as function call */
//   std::printf("[]: %i" "\r\n", static_cast<int>($<1u>{}    (4.0f))); // ->> Constructor (call), then function call
//   std::printf("[]: %i" "\r\n", static_cast<int>($<1u>      (4.0f))); // ->> Undefined behavior a la `*(int*) (void*) &(float&&{...})`
//   std::printf("[]: %i" "\r\n", static_cast<int>($<1u, int> (4.0f))); // ->> Defined   behavior a la `(int)  float&&{...}` via `private` `int`  member access
//   std::printf("[]: %i" "\r\n", static_cast<int>($<1u, int&>(4.0f))); // ->> Undefined behavior a la `(int&) float&&{...}` via `private` `int&` member access
//   std::puts("...");

//   /* Constants */
//   std::printf("[]: %llu" "\r\n",                                    ($u<5uLL>{})()); // --> unsigned int
//   std::printf("[]: %lli" "\r\n", static_cast<signed long long (*)()>($s<-5LL>{})()); // --> signed   int
//   std::puts("...");

//   /* Function expression */
//   // std::printf("[]: %zu" "\r\n", sizeof($expression<$comma, $expression<$self, $<1u> >,        $expression<$self, $<2u> >, $void>));
//   // std::printf("[]: %zu" "\r\n", sizeof($expression<$comma, $expression<$self, $object<int> >, $expression<$self, $<2u> >, $void>));
//   // std::printf("[]: %1.1s" "\r\n", std::puts&($1)("6"));
//   std::puts("...");

//   /* Expression */
//   // std::puts&($1), std::printf&($1, $2)
//   // std::bsearch(&static_cast<int const&>(42), {1, 2, 3, 4, 5}, 5u, sizeof(int), [](void const* a, void const* b) { return *(int*) a < *(int*) b ? -1 : *(int*) a > *(int*) b ? +1 : 0; });
//   // std::bsearch(&static_cast<int const&>(42), {1, 2, 3, 4, 5}, 5u, sizeof(int), *$as<int*>($1) < *$as<int*>($2) ? -1 : *$as<int*>($1) > *$as<int*>($2) ? +1 : 0);

//   /* ... */
//   return EXIT_SUCCESS;
// }
