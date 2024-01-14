/* ...
    --- CITE ---
      #Lapys:
        - Circle:                                             https://lapys.godbolt.org/z/qMn1qd43e
        - Clang, GNU, Intel, Microsoft Visual Studio, NVIDIA: https://lapys.godbolt.org/z/r3METo98K
*/
#include <ciso646>    // --> and, or, not
#include <climits>    //
#include <cstdarg>    // --> std::va_list
#include <cstddef>    // --> offsetof, std::byte, std::max_align_t, std::nullptr_t
#include <cstdlib>    // --> std::div_t, std::ldiv_t, std::lldiv_t
#include <exception>  // --> std::bad_exception, std::exception, std::exception_ptr, std::nested_exception, std::terminate_handler, std::unexpected_handler
#include <functional> // --> std::bad_function_call, std::bit_and<void>, std::bit_not<>, std::bit_or<void>, std::bit_xor<void>, std::divides<void>, std::equal_to<void>, std::greater<void>, std::greater_equal<void>, std::identity, std::less<void>, std::less_equal<void>, std::logical_and<void>, std::logical_not<void>, std::logical_or<void>, std::minus<void>, std::modulus<void>, std::multiplies<void>, std::negate<void>, std::not_equal_to<void>, std::plus<void>, decltype(std::placeholders::_1), decltype(std::placeholders::_2)
#include <iterator>   // --> std::bidirectional_iterator_tag, std::contiguous_iterator_tag, std::default_sentinel_t, std::forward_iterator_tag, std::input_iterator_tag, std::output_iterator_tag, std::random_access_iterator_tag, std::unreachable_sentinel_t
#include <memory>     // --> std::allocator_arg_t, std::bad_weak_ptr, std::owner_less<void>, std::pointer_safety
#include <new>        // --> std::align_val_t, std::bad_alloc, std::bad_array_new_length, std::destroying_delete_t, std::new_handler, std::nothrow_t
#include <stdint.h>   //
#include <typeinfo>   // --> std::bad_cast, std::bad_typeid, std::type_info
#include <utility>    // --> std::in_place_t, std::piecewise_construct_t
#if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201103L
# include <atomic>      // --> std::atomic_bool, std::atomic_char, std::atomic_char16_t, std::atomic_char32_t, std::atomic_char8_t, std::atomic_flag, std::atomic_int, std::atomic_int16_t, std::atomic_int32_t, std::atomic_int64_t, std::atomic_int8_t, std::atomic_int_fast16_t, std::atomic_int_fast32_t, std::atomic_int_fast64_t, std::atomic_int_fast8_t, std::atomic_int_least16_t, std::atomic_int_least32_t, std::atomic_int_least64_t, std::atomic_int_least8_t, std::atomic_intmax_t, std::atomic_intptr_t, std::atomic_llong, std::atomic_long, std::atomic_ptrdiff_t, std::atomic_schar, std::atomic_short, std::atomic_size_t, std::atomic_uchar, std::atomic_uint, std::atomic_uint16_t, std::atomic_uint32_t, std::atomic_uint64_t, std::atomic_uint8_t, std::atomic_uint_fast16_t, std::atomic_uint_fast32_t, std::atomic_uint_fast64_t, std::atomic_uint_fast8_t, std::atomic_uint_least16_t, std::atomic_uint_least32_t, std::atomic_uint_least64_t, std::atomic_uint_least8_t, std::atomic_uintmax_t, std::atomic_uintptr_t, std::atomic_ullong, std::atomic_ulong, std::atomic_ushort, std::atomic_wchar_t, std::memory_order
# include <ratio>       // --> std::atto, std::centi, std::deca, std::deci, std::exa, std::femto, std::giga, std::hecto, std::kilo, std::mega, std::micro, std::milli, std::nano, std::peta, std::pico, std::tera, std::yocto, std::yotta, std::zepto, std::zetta
# include <type_traits> // --> std::false_type, std::is_trivially_destructible, std::true_type, std::void_t
#endif
#if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 202002L or (defined __circle_lang__ or defined __clang__ or defined __CUDACC_VER_BUILD__ or defined __CUDACC_VER_MAJOR__ or defined __CUDACC_VER_MINOR__ or defined __GNUC__ or defined __ICC or defined __INTEL_COMPILER or defined __INTEL_LLVM_COMPILER or defined __NVCC__ or defined __NVCOMPILER)
# include <version>
#endif
#ifdef __cpp_lib_endian
# include <bit> // --> std::endian
#endif
#ifdef __cpp_lib_three_way_comparison
# include <compare> // --> std::compare_three_way, std::partial_ordering, std::strong_ordering, std::weak_ordering
# ifdef __cpp_lib_coroutine
#   include <coroutine> // --> std::coroutine_handle<void>, std::noop_coroutine_handle, std::noop_coroutine_promise, std::suspend_always, std::suspend_never
# endif
#endif
#ifdef __cpp_lib_print
# include <print> // --> std::vprint_unicode, std::vprint_nonunicode
#endif
#ifdef __cpp_lib_ranges
# include <ranges> // --> std::dangling, std::from_range_t, std::subrange_kind
#endif
#ifdef __cpp_lib_source_location
# include <source_location> // --> std::source_location
#endif
#ifdef __cpp_lib_spanstream
# include <spanstream> // --> std::ispanstream, std::ospanstream, std::spanbuf, std::spanstream, std::wispanstream, std::wospanstream, std::wspanbuf, std::wspanstream
#endif
#ifdef __cpp_lib_stacktrace
# include <stacktrace> // --> std::stacktrace, std::stacktrace_entry
#endif
#if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 202002L // --> __cpp_lib_format
# include <format> // --> std::format_args, std::wformat_args
#endif
#if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) > 202002L // --> __cpp_lib_expected
# include <expected> // --> std::unexpect_t
# include <stdfloat> // --> std::bfloat16_t, std::float128_t, std::float16_t, std::float32_t, std::float64_t
#endif

/* ... */
#define sfinaeptr nullptr

typedef union null_t  &null;
typedef std::nullptr_t sfinaeptr_t;

// ... --> forward_cast<T>(T{}), instanceof<T>()
template <typename type> constexpr type&& forward_cast(type&  object) noexcept { return static_cast<type&&>(object); }
template <typename type> constexpr type&& forward_cast(type&& object) noexcept { return static_cast<type&&>(object); }

template <typename type> constexpr type instanceof() noexcept;

// ... --> arrayof<T, N>
template <typename base, std::size_t capacity>
struct arrayof final {
  typedef base type[capacity];
};

// ... --> conditional
template <bool, typename = null, typename = null>
struct conditional;

template <>                               struct conditional<true>                final {};
template <typename base>                  struct conditional<false, base>         final {};
template <typename baseA, typename baseB> struct conditional<false, baseA, baseB> final { typedef baseB type; };
template <typename baseA, typename baseB> struct conditional<true,  baseA, baseB> final { typedef baseA type; };

// ... --> at<N, Ts...>
template <std::size_t index, typename...>
struct at final {
  typedef null type;

  // ...
  template <typename... types>
  constexpr static typename conditional<(index > sizeof...(types)), sfinaeptr_t>::type value(types&&...) noexcept {
    static_assert(index <= sizeof...(types) + 1u, "Too few arguments passed to function");
    return sfinaeptr;
  }

  template <typename type, typename... types> constexpr static typename conditional<(0u == index and index <= sizeof...(types) + 1u), typename at<index, type&&, types&&...>::type>::type value(type&& argument, types&&...)  noexcept { return forward_cast<type>(argument); }
  template <typename type, typename... types> constexpr static typename conditional<(0u != index and index <= sizeof...(types) + 1u), typename at<index, type&&, types&&...>::type>::type value(type&&, types&&... arguments) noexcept { return at<index - 1u>::value(forward_cast<types>(arguments)...); }
};

template                    <typename base, typename... bases> struct at<0u,    base, bases...> final { typedef base                                    type; };
template <std::size_t index, typename base, typename... bases> struct at<index, base, bases...> final { typedef typename at<index - 1u, bases...>::type type; };

// ... --> is_union<T>
template <class base>
struct is_union final {
  private:
    template <typename type> constexpr static bool const (&valueof(sfinaeptr_t const, unsigned char type::* const = NULL) noexcept)[true  + 1u];
    template <typename>      constexpr static bool const (&valueof(...)                                                   noexcept)[false + 1u];

  public:
    static bool const value =
      #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201103L
        std::is_union<base>::value or
      #elif defined __circle_lang__ or defined __clang__ or defined __CUDACC_VER_BUILD__ or defined __CUDACC_VER_MAJOR__ or defined __CUDACC_VER_MINOR__ or defined __NVCC__ or defined __NVCOMPILER or defined __GNUC__ or defined __ICC or defined __INTEL_COMPILER or defined __INTEL_LLVM_COMPILER or defined __llvm__
      # ifdef __has_builtin
      #   if __has_builtin(__is_union)
            __is_union(base) or
      #   endif
      # endif
      #elif defined _MSC_VER
        __is_union(base) or
      #endif
    sizeof(bool const (&)[true + 1u]) == sizeof valueof<base>(sfinaeptr);
};

// ... --> is_class<T>
template <class base>
struct is_class final {
  static bool const value =
    #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201103L
      std::is_class<base>::value or
    #elif defined __circle_lang__ or defined __clang__ or defined __CUDACC_VER_BUILD__ or defined __CUDACC_VER_MAJOR__ or defined __CUDACC_VER_MINOR__ or defined __NVCC__ or defined __NVCOMPILER or defined __GNUC__ or defined __ICC or defined __INTEL_COMPILER or defined __INTEL_LLVM_COMPILER or defined __llvm__
    # ifdef __has_builtin
    #   if __has_builtin(__is_class)
          __is_class(base) or
    #   endif
    # endif
    #elif defined _MSC_VER
      __is_class(base) or
    #endif
  is_union<base>::value;
};

// ... --> is_const<T>
template <typename>      struct is_const             final { static bool const value = false; };
template <typename base> struct is_const<base const> final { static bool const value = true; };

// ... --> is_decimal<T>
template <typename> struct is_decimal              final { static bool const value = false; };
template <>         struct is_decimal<double>      final { static bool const value = true; };
template <>         struct is_decimal<float>       final { static bool const value = true; };
template <>         struct is_decimal<long double> final { static bool const value = true; };

// ... --> is_integer<T>
template <typename> struct is_integer                     final { static bool const value = false; };
template <>         struct is_integer<int>                final { static bool const value = true; };
template <>         struct is_integer<long>               final { static bool const value = true; };
template <>         struct is_integer<long long>          final { static bool const value = true; };
template <>         struct is_integer<short>              final { static bool const value = true; };
template <>         struct is_integer<signed char>        final { static bool const value = true; };
template <>         struct is_integer<unsigned char>      final { static bool const value = true; };
template <>         struct is_integer<unsigned int>       final { static bool const value = true; };
template <>         struct is_integer<unsigned long>      final { static bool const value = true; };
template <>         struct is_integer<unsigned long long> final { static bool const value = true; };
template <>         struct is_integer<unsigned short>     final { static bool const value = true; };

// ... --> is_lvalue_reference<T>
template <typename>      struct is_lvalue_reference        final { static bool const value = false; };
template <typename base> struct is_lvalue_reference<base&> final { static bool const value = true; };

// ... --> is_member_pointer<T>
template <typename>                    struct is_member_pointer                                final { static bool const value = false; };
template <typename baseA, class baseB> struct is_member_pointer<baseA baseB::*>                final { static bool const value = true; };
template <typename baseA, class baseB> struct is_member_pointer<baseA baseB::* const>          final { static bool const value = true; };
template <typename baseA, class baseB> struct is_member_pointer<baseA baseB::* const volatile> final { static bool const value = true; };
template <typename baseA, class baseB> struct is_member_pointer<baseA baseB::*       volatile> final { static bool const value = true; };

// ... --> is_null<T>
template <typename> struct is_null       final { static bool const value = false; };
template <>         struct is_null<null> final { static bool const value = true; };

// ... --> is_pointer<T>
template <typename>      struct is_pointer                       final { static bool const value = false; };
template <typename base> struct is_pointer<base*>                final { static bool const value = true; };
template <typename base> struct is_pointer<base* const>          final { static bool const value = true; };
template <typename base> struct is_pointer<base* const volatile> final { static bool const value = true; };
template <typename base> struct is_pointer<base*       volatile> final { static bool const value = true; };

// ... --> is_rvalue_reference<T>
template <typename>      struct is_rvalue_reference         final { static bool const value = false; };
template <typename base> struct is_rvalue_reference<base&&> final { static bool const value = true; };

// ... --> is_reference<T>
template <typename base>
struct is_reference final {
  static bool const value = is_lvalue_reference<base>::value or is_rvalue_reference<base>::value;
};

// ... --> is_same<T, U>
template <typename baseA, typename baseB> struct is_same             final { static bool const value = false; };
template <typename base>                  struct is_same<base, base> final { static bool const value = true;  };

// ... --> is_void<T>
template <typename> struct is_void                      final { static bool const value = false; };
template <>         struct is_void<void>                final { static bool const value = true; };
template <>         struct is_void<void const>          final { static bool const value = true; };
template <>         struct is_void<void const volatile> final { static bool const value = true; };
template <>         struct is_void<void       volatile> final { static bool const value = true; };

// ... --> is_volatile<T>
template <typename>      struct is_volatile                final { static bool const value = false; };
template <typename base> struct is_volatile<base volatile> final { static bool const value = true; };

// ... --> is_enum<T>
template <typename base>
struct is_enum final {
  private:
    template <typename type> constexpr static bool (&valueof(sfinaeptr_t const, bool const (*const)[sizeof static_cast<std::size_t>(+instanceof<type>())] = NULL) noexcept)[true  + 1u];
    template <typename>      constexpr static bool (&valueof(...)                                                                                                 noexcept)[false + 1u];

  public:
    static bool const value =
      #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201103L
        std::is_enum<base>::value or
      #elif defined __circle_lang__ or defined __clang__ or defined __CUDACC_VER_BUILD__ or defined __CUDACC_VER_MAJOR__ or defined __CUDACC_VER_MINOR__ or defined __NVCC__ or defined __NVCOMPILER or defined __GNUC__ or defined __ICC or defined __INTEL_COMPILER or defined __INTEL_LLVM_COMPILER or defined __llvm__
      # ifdef __has_builtin
      #   if __has_builtin(__is_enum)
            __is_enum(base) or
      #   endif
      # endif
      #elif defined _MSC_VER
        __is_enum(base) or
      #endif
    (not is_class<base>::value and not is_integer<base>::value and not is_pointer<base>::value and not is_void<base>::value and not is_same<base, std::nullptr_t>::value and sizeof(bool const (&)[true + 1u]) == sizeof valueof<base>(sfinaeptr));
};

// ... --> is_function<T>
template <typename base>
struct is_function final {
  static bool const value = not is_const<base const>::value and not is_reference<base>::value and not is_volatile<base volatile>::value;
};

// ... --> max<Ns...>
template <std::size_t size, std::size_t...>                           struct max                         final { static std::size_t const value = size; };
template <std::size_t sizeA, std::size_t sizeB, std::size_t... sizes> struct max<sizeA, sizeB, sizes...> final { static std::size_t const value = max<(sizeA > sizeB ? sizeA : sizeB), sizes...>::value; };

// ... --> remove_const<T>
template <typename base> struct remove_const             final { typedef base type; };
template <typename base> struct remove_const<base const> final { typedef base type; };

// ... --> remove_lvalue_reference<T>
template <typename base> struct remove_lvalue_reference        final { typedef base type; };
template <typename base> struct remove_lvalue_reference<base&> final { typedef base type; };

// ... --> remove_pointer<T>
template <typename base> struct remove_pointer                       final { typedef base type; };
template <typename base> struct remove_pointer<base*>                final { typedef base type; };
template <typename base> struct remove_pointer<base* const>          final { typedef base type; };
template <typename base> struct remove_pointer<base* const volatile> final { typedef base type; };
template <typename base> struct remove_pointer<base*       volatile> final { typedef base type; };

// ... --> remove_rvalue_reference<T>
template <typename base> struct remove_rvalue_reference         final { typedef base type; };
template <typename base> struct remove_rvalue_reference<base&&> final { typedef base type; };

// ... --> remove_volatile<T>
template <typename base> struct remove_volatile                final { typedef base type; };
template <typename base> struct remove_volatile<base volatile> final { typedef base type; };

// ... --> remove_cv<T>, remove_qualifiers<T>, remove_reference<T>
template <typename base> struct remove_reference  final { typedef typename remove_lvalue_reference<typename remove_rvalue_reference<base>::type>::type type; };
template <typename base> struct remove_cv         final { typedef typename remove_const           <typename remove_volatile        <base>::type>::type type; };
template <typename base> struct remove_qualifiers final { typedef typename remove_cv              <typename remove_reference       <base>::type>::type type; };

/* Shorthand */
enum $$ : unsigned char {
  $c = 0x01u, // ->> Constant: Allows compile-time evaluation of constructed `$n` shorthands
  $o = 0x02u, // ->> Object  : Allows constructor elision e.g.: `$1(...) == $n<1u>(...)`

  $co = static_cast<$$>(static_cast<unsigned char>($c) | static_cast<unsigned char>($o)),
  $oc = static_cast<$$>(static_cast<unsigned char>($o) | static_cast<unsigned char>($c))
};

// ...
union $op {
  enum $$ : unsigned char {
    add, address, assign, assign_add, assign_bitwise_and, assign_bitwise_or, assign_bitwise_xor, assign_divide, assign_left_shift, assign_modulo, assign_multiply, assign_right_shift, assign_subtract,
    bitwise_and, bitwise_or, bitwise_xor, boolean_and, boolean_or,
    call, cast, comma, compare, complement, construct,
    dereference, destruct, divide,
    equals, equals_greater, equals_lesser,
    greater,
    initialize,
    left_shift, lesser,
    member_access, member_pointer_access, minus, modulo, multiply,
    negate,
    overloaded_address,
    plus, post_decrement, post_increment, pre_decrement, pre_increment,
    right_shift,
    self, subscript, subtract,
    ternary,
    unequal
  };
};

// ...
template <$op::$$, class = null, class = null, class = null /* , ... */>
struct $lambda;

// ...
template <
  std::size_t, $$ state = $o,
  bool /* $$c */ = static_cast<bool>(static_cast<unsigned char>(state) & static_cast<unsigned char>($c)),
  bool /* $$o */ = static_cast<bool>(static_cast<unsigned char>(state) & static_cast<unsigned char>($o))
  // , ...
> struct $n;

// ...
struct $shorthand {
  template <$op::$$, class, class, class>
  friend struct $lambda;

  protected:
    template <std::size_t, typename>
    struct cast;

    template <std::size_t arity, typename base, typename... bases> struct cast<arity, base (bases...)      noexcept> { static std::size_t const adicity = sizeof...(bases); constexpr static base value(bases... arguments)      noexcept { return static_cast<base>($n<arity, $c>{}.operator ()(static_cast<bases>(arguments)...)); } };
    template <std::size_t arity, typename base, typename... bases> struct cast<arity, base (bases..., ...) noexcept> { static std::size_t const adicity = sizeof...(bases); constexpr static base value(bases... arguments, ...) noexcept { return static_cast<base>($n<arity, $c>{}.operator ()(static_cast<bases>(arguments)...)); } };

    #ifdef __cpp_noexcept_function_type
      template <std::size_t arity, typename base, typename... bases> struct cast<arity, base (bases...)>      : public cast<arity, base (bases...)      noexcept> {};
      template <std::size_t arity, typename base, typename... bases> struct cast<arity, base (bases..., ...)> : public cast<arity, base (bases..., ...) noexcept> {};
    #endif

    // ...
    enum enumeration : unsigned long long {};

    // ...
    union standard {
      enum type : unsigned char {
        _ = 0x0Cu,
        align_val_t, allocator_arg_t, atomic_bool, atomic_char, atomic_char16_t, atomic_char32_t, atomic_char8_t, atomic_flag, atomic_int, atomic_llong, atomic_long, atomic_schar, atomic_short, atomic_uchar, atomic_uint, atomic_ullong, atomic_ulong, atomic_ushort, atomic_wchar_t, atto,
        bad_alloc, bad_array_new_length, bad_cast, bad_exception, bad_function_call, bad_typeid, bad_weak_ptr, bfloat16_t, bidirectional_iterator_tag, bit_and, bit_not, bit_or, bit_xor, byte,
        centi, compare_three_way, contiguous_iterator_tag, coroutine_handle,
        dangling, deca, deci, default_sentinel_t, divides, destroying_delete_t, div_t,
        endian, equal_to, exa, exception, exception_ptr,
        false_type, femto, float128_t, float16_t, float32_t, float64_t, forward_iterator_tag, from_range_t,
        giga, greater, greater_equal,
        hecto,
        identity, in_place_t, input_iterator_tag,
        kilo,
        ldiv_t, less, less_equal, lldiv_t, logical_and, logical_not, logical_or,
        max_align_t, mega, memory_order, micro, milli, minus, modulus, multiplies,
        nano, negate, nested_exception, new_terminate_unexpected_handler, noop_coroutine_handle, noop_coroutine_promise, not_equal_to, nothrow_t, nullptr_t,
        output_iterator_tag, owner_less,
        partial_ordering, peta, pico, piecewise_construct_t, placeholders_1, placeholders_2, plus, pointer_safety,
        random_access_iterator_tag,
        tera, true_type, type_info,
        source_location, strong_ordering, subrange_kind, suspend_always, suspend_never,
        unexpected_handler, unreachable_sentinel_t,
        va_list,
        weak_ordering
      };
    };

    // ...
    enum type : unsigned char {
      _ = 0x00u,
      decimal,
      enumeration,
      function,
      integer,
      member,
      null,
      pointer,
      reference,
      shorthand, standard,
      undefined
    };

    // ...
    struct undefined final {
      private:
        struct layout final {
          unsigned char value[max<
            sizeof(std::allocator_arg_t), sizeof(std::atomic_bool), sizeof(std::atomic_char), sizeof(std::atomic_flag), sizeof(std::atomic_int), sizeof(std::atomic_llong), sizeof(std::atomic_long), sizeof(std::atomic_schar), sizeof(std::atomic_short), sizeof(std::atomic_uchar), sizeof(std::atomic_uint), sizeof(std::atomic_ullong), sizeof(std::atomic_ulong), sizeof(std::atomic_ushort), sizeof(std::atomic_wchar_t), sizeof(std::atto),
            sizeof(std::bad_alloc), sizeof(std::bad_array_new_length), sizeof(std::bad_cast), sizeof(std::bad_exception), sizeof(std::bad_function_call), sizeof(std::bad_typeid), sizeof(std::bad_weak_ptr), sizeof(std::bidirectional_iterator_tag),
            sizeof(std::centi),
            sizeof(std::deca), sizeof(std::deci), sizeof(std::div_t),
            sizeof(std::exa), sizeof(std::exception), sizeof(std::exception_ptr),
            sizeof(std::false_type), sizeof(std::femto), sizeof(std::forward_iterator_tag),
            sizeof(std::giga),
            sizeof(std::hecto),
            sizeof(std::input_iterator_tag),
            sizeof(std::kilo),
            sizeof(std::ldiv_t), sizeof(std::lldiv_t),
            sizeof(std::max_align_t), sizeof(std::mega), sizeof(std::memory_order), sizeof(std::micro), sizeof(std::milli),
            sizeof(std::nano), sizeof(std::nested_exception), sizeof(std::new_handler), sizeof(std::nothrow_t), sizeof(std::nullptr_t),
            sizeof(std::output_iterator_tag), sizeof(std::owner_less<void>),
            sizeof(std::peta), sizeof(std::pico), sizeof(std::piecewise_construct_t), sizeof(decltype(std::placeholders::_1)), sizeof(decltype(std::placeholders::_2)),
            sizeof(std::random_access_iterator_tag),
            sizeof(std::tera), sizeof(std::true_type), sizeof(std::type_info),
            sizeof(std::va_list),
            #ifdef __cpp_aligned_new
              sizeof(std::align_val_t),
            #endif
            #ifdef __cpp_char8_t
              sizeof(std::atomic_char8_t),
            #endif
            #ifdef __cpp_lib_byte
              sizeof(std::byte),
            #endif
            #ifdef __cpp_lib_endian
              sizeof(std::endian),
            #endif
            #ifdef __cpp_lib_ranges
              sizeof(std::ranges::dangling),
              sizeof(std::ranges::subrange_kind),
            #endif
            #ifdef __cpp_lib_source_location
              sizeof(std::source_location),
            #endif
            #ifdef __cpp_lib_three_way_comparison
              sizeof(std::compare_three_way),
              sizeof(std::partial_ordering),
              sizeof(std::strong_ordering),
              sizeof(std::weak_ordering),
              #ifdef __cpp_lib_coroutine
                sizeof(std::coroutine_handle<void>),
                sizeof(std::noop_coroutine_handle), sizeof(std::noop_coroutine_promise),
                sizeof(std::suspend_always), sizeof(std::suspend_never),
              #endif
            #endif
            #ifdef __cpp_unicode_characters
              sizeof(std::atomic_char16_t), sizeof(std::atomic_char32_t),
            #endif
            #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201402L
              sizeof(std::bit_and<void>), sizeof(std::bit_not<>), sizeof(std::bit_or<void>), sizeof(std::bit_xor<void>),
              sizeof(std::divides<void>),
              sizeof(std::equal_to<void>),
              sizeof(std::greater<void>), sizeof(std::greater_equal<void>),
              sizeof(std::less<void>), sizeof(std::less_equal<void>), sizeof(std::logical_and<void>), sizeof(std::logical_not<void>), sizeof(std::logical_or<void>),
              sizeof(std::minus<void>), sizeof(std::modulus<void>), sizeof(std::multiplies<void>),
              sizeof(std::negate<void>), sizeof(std::not_equal_to<void>),
              sizeof(std::plus<void>),
            #endif
            #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201703L
              sizeof(std::in_place_t),
            #endif
            #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 202002L
              sizeof(std::contiguous_iterator_tag),
              sizeof(std::default_sentinel_t), sizeof(std::destroying_delete_t),
              sizeof(std::identity),
              sizeof(std::unreachable_sentinel_t),
            #endif
            #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) <= 202002L // --> < 2023..L
              sizeof(std::pointer_safety),
            #endif
            #if defined __STDCPP_BFLOAT16_T__
              sizeof(std::bfloat16_t),
            #endif
            #if defined __STDCPP_FLOAT16_T__
              sizeof(std::float16_t),
            #endif
            #if defined __STDCPP_FLOAT32_T__
              sizeof(std::float32_t),
            #endif
            #if defined __STDCPP_FLOAT64_T__
              sizeof(std::float64_t),
            #endif
            #if defined __STDCPP_FLOAT128_T__
              sizeof(std::float128_t),
            #endif
            sizeof(enum enumeration), sizeof(long double), sizeof(sfinaeptr_t $shorthand::*), sizeof(unsigned long long), sizeof(void (*)(...)), sizeof(void*)
          >::value];
          void *address;
        };

        #ifdef offsetof
          static std::size_t const padding = offsetof(layout, address) - (0u /* --> offsetof(layout, value) */ + sizeof layout::value);
        #else
          static std::size_t const padding = 0u;
        #endif

      public:
        alignas(void*) unsigned char value[sizeof layout::value - padding - (sizeof layout::address >= sizeof layout::value - padding ? sizeof layout::value - padding - 1u : sizeof layout::address)];
        void                        *address;
    };

    // ...
    struct value final {
      union {
        long double               const decimal;
        enum enumeration          const enumeration;
        void                    (*const function)(...) noexcept;
        unsigned long long        const integer;
        sfinaeptr_t $shorthand:: *const member;
        sfinaeptr_t               const null;
        void                     *const pointer;
        unsigned char            *const reference;
        struct undefined          const undefined;

        std::allocator_arg_t            const std_allocator_arg_t;
        std::atomic_flag               *const std_atomic_flag;
        std::atto                       const std_atto;
        std::bidirectional_iterator_tag const std_bidirectional_iterator_tag;
        std::centi                      const std_centi;
        std::deca                       const std_deca;
        std::deci                       const std_deci;
        std::div_t                      const std_div_t;
        std::exa                        const std_exa;
        std::false_type                 const std_false_type;
        std::femto                      const std_femto;
        std::forward_iterator_tag       const std_forward_iterator_tag;
        std::giga                       const std_giga;
        std::hecto                      const std_hecto;
        std::input_iterator_tag         const std_input_iterator_tag;
        std::kilo                       const std_kilo;
        std::ldiv_t                     const std_ldiv_t;
        std::lldiv_t                    const std_lldiv_t;
        std::max_align_t                const std_max_align_t;
        std::mega                       const std_mega;
        std::memory_order               const std_memory_order;
        std::micro                      const std_micro;
        std::milli                      const std_milli;
        std::nano                       const std_nano;
        std::new_handler                const std_new_terminate_unexpected_handler; // --> std::terminate_handler, std::unexpected_handler
        std::nothrow_t                  const std_nothrow_t;
        std::nullptr_t                  const std_nullptr_t;
        std::output_iterator_tag        const std_output_iterator_tag;
        std::owner_less<void>           const std_owner_less;
        std::peta                       const std_peta;
        std::pico                       const std_pico;
        std::piecewise_construct_t      const std_piecewise_construct_t;
        decltype(std::placeholders::_1) const std_placeholders_1;
        decltype(std::placeholders::_2) const std_placeholders_2;
        std::random_access_iterator_tag const std_random_access_iterator_tag;
        std::tera                       const std_tera;
        std::true_type                  const std_true_type;
        std::type_info const           *const std_type_info;
        std::va_list                   *const std_va_list;
        #ifdef __cpp_aligned_new
          std::align_val_t const std_align_val_t;
        #endif
        #ifdef __cpp_lib_byte
          std::byte const std_byte;
        #endif
        #ifdef __cpp_lib_endian
          std::endian const std_endian;
        #endif
        #ifdef __cpp_lib_ranges
          std::ranges::dangling      const std_dangling;
          std::ranges::subrange_kind const std_subrange_kind;
        #endif
        #ifdef __cpp_lib_source_location
          std::source_location const std_source_location;
        #endif
        #ifdef __cpp_lib_three_way_comparison
          std::compare_three_way const std_compare_three_way;
          std::partial_ordering  const std_partial_ordering;
          std::strong_ordering   const std_strong_ordering;
          std::weak_ordering     const std_weak_ordering;
          #ifdef __cpp_lib_coroutine
            std::coroutine_handle<void> const std_coroutine_handle;
            std::noop_coroutine_handle  const std_noop_coroutine_handle;
            std::noop_coroutine_promise const std_noop_coroutine_promise;
            std::suspend_always         const std_suspend_always;
            std::suspend_never          const std_suspend_never;
          #endif
        #endif
        #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201402L
          std::bit_and      <void> const std_bit_and;
          std::bit_not      <>     const std_bit_not;
          std::bit_or       <void> const std_bit_or;
          std::bit_xor      <void> const std_bit_xor;
          std::divides      <void> const std_divides;
          std::equal_to     <void> const std_equal_to;
          std::greater      <void> const std_greater;
          std::greater_equal<void> const std_greater_equal;
          std::less         <void> const std_less;
          std::less_equal   <void> const std_less_equal;
          std::logical_and  <void> const std_logical_and;
          std::logical_not  <void> const std_logical_not;
          std::logical_or   <void> const std_logical_or;
          std::minus        <void> const std_minus;
          std::modulus      <void> const std_modulus;
          std::multiplies   <void> const std_multiplies;
          std::negate       <void> const std_negate;
          std::not_equal_to <void> const std_not_equal_to;
          std::plus         <void> const std_plus;
        #endif
        #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201703L
          std::in_place_t const std_in_place_t;
        #endif
        #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 202002L
          std::contiguous_iterator_tag const std_contiguous_iterator_tag;
          std::default_sentinel_t      const std_default_sentinel_t;
          std::destroying_delete_t     const std_destroying_delete_t;
          std::identity                const std_identity;
          std::unreachable_sentinel_t  const std_unreachable_sentinel_t;
        #endif
        #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) <= 202002L // --> < 2023..L
          std::pointer_safety const std_pointer_safety;
        #endif
        #if defined __STDCPP_BFLOAT16_T__
          std::bfloat16_t const std_bfloat16_t;
        #endif
        #if defined __STDCPP_FLOAT16_T__
          std::float16_t const std_float16_t;
        #endif
        #if defined __STDCPP_FLOAT32_T__
          std::float32_t const std_float32_t;
        #endif
        #if defined __STDCPP_FLOAT64_T__
          std::float64_t const std_float64_t;
        #endif
        #if defined __STDCPP_FLOAT128_T__
          std::float128_t const std_float128_t;
        #endif
        alignas(std::atomic_bool)          unsigned char const std_atomic_bool         [sizeof(std::atomic_bool)];
        alignas(std::atomic_char)          unsigned char const std_atomic_char         [sizeof(std::atomic_char)];
        alignas(std::atomic_int)           unsigned char const std_atomic_int          [sizeof(std::atomic_int)];
        alignas(std::atomic_llong)         unsigned char const std_atomic_llong        [sizeof(std::atomic_llong)];
        alignas(std::atomic_long)          unsigned char const std_atomic_long         [sizeof(std::atomic_long)];
        alignas(std::atomic_schar)         unsigned char const std_atomic_schar        [sizeof(std::atomic_schar)];
        alignas(std::atomic_short)         unsigned char const std_atomic_short        [sizeof(std::atomic_short)];
        alignas(std::atomic_uchar)         unsigned char const std_atomic_uchar        [sizeof(std::atomic_uchar)];
        alignas(std::atomic_uint)          unsigned char const std_atomic_uint         [sizeof(std::atomic_uint)];
        alignas(std::atomic_ullong)        unsigned char const std_atomic_ullong       [sizeof(std::atomic_ullong)];
        alignas(std::atomic_ulong)         unsigned char const std_atomic_ulong        [sizeof(std::atomic_ulong)];
        alignas(std::atomic_ushort)        unsigned char const std_atomic_ushort       [sizeof(std::atomic_ushort)];
        alignas(std::atomic_wchar_t)       unsigned char const std_atomic_wchar_t      [sizeof(std::atomic_wchar_t)];
        alignas(std::bad_alloc)            unsigned char const std_bad_alloc           [sizeof(std::bad_alloc)];
        alignas(std::bad_array_new_length) unsigned char const std_bad_array_new_length[sizeof(std::bad_array_new_length)];
        alignas(std::bad_cast)             unsigned char const std_bad_cast            [sizeof(std::bad_cast)];
        alignas(std::bad_exception)        unsigned char const std_bad_exception       [sizeof(std::bad_exception)];
        alignas(std::bad_function_call)    unsigned char const std_bad_function_call   [sizeof(std::bad_function_call)];
        alignas(std::bad_typeid)           unsigned char const std_bad_typeid          [sizeof(std::bad_typeid)];
        alignas(std::bad_weak_ptr)         unsigned char const std_bad_weak_ptr        [sizeof(std::bad_weak_ptr)];
        alignas(std::exception)            unsigned char const std_exception           [sizeof(std::exception)];
        alignas(std::exception_ptr)        unsigned char const std_exception_ptr       [sizeof(std::exception_ptr)];
        alignas(std::nested_exception)     unsigned char const std_nested_exception    [sizeof(std::nested_exception)];
        #ifdef __cpp_unicode_characters
          alignas(std::atomic_char16_t) unsigned char const std_atomic_char16_t[sizeof(std::atomic_char16_t)];
          alignas(std::atomic_char32_t) unsigned char const std_atomic_char32_t[sizeof(std::atomic_char32_t)];
        #endif
        #ifdef __cpp_char8_t
          alignas(std::atomic_char8_t) unsigned char const std_atomic_char8_t[sizeof(std::atomic_char8_t)];
        #endif
      };
      std::type_info const *const metadata;
      enum type             const type;

      // ...
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::shorthand][arity], ...)                                          noexcept = delete;
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::decimal]  [arity], long double                     const  value) noexcept                                                                                           : decimal                              (value),   metadata(NULL /* --> &typeid(long double) */),                     type($shorthand::decimal)                                                            {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::integer]  [arity], unsigned long long              const  value) noexcept                                                                                           : integer                              (value),   metadata(NULL /* --> &typeid(unsigned long long) */),              type($shorthand::integer)                                                            {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::pointer]  [arity], void const volatile*            const  value) noexcept                                                                                           : pointer            (const_cast<void*>(value)),  metadata(NULL /* --> &typeid(void*) */),                           type($shorthand::pointer)                                                            {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], decltype(std::placeholders::_1) const  value) noexcept(noexcept(decltype(std::placeholders::_1)(instanceof<decltype(std::placeholders::_1)>()))) : std_placeholders_1                   (value),   metadata(NULL /* --> &typeid(decltype(std::placeholders::_1)) */), type(static_cast<enum type>($shorthand::standard::placeholders_1))                   {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], decltype(std::placeholders::_2) const  value) noexcept(noexcept(decltype(std::placeholders::_2)(instanceof<decltype(std::placeholders::_2)>()))) : std_placeholders_2                   (value),   metadata(NULL /* --> &typeid(decltype(std::placeholders::_2)) */), type(static_cast<enum type>($shorthand::standard::placeholders_2))                   {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::allocator_arg_t            const  value) noexcept(noexcept(std::allocator_arg_t           (instanceof<std::allocator_arg_t>           ()))) : std_allocator_arg_t                  (value),   metadata(NULL /* --> &typeid(std::allocator_arg_t) */),            type(static_cast<enum type>($shorthand::standard::allocator_arg_t))                  {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::atomic_flag&                      value) noexcept                                                                                           : std_atomic_flag                     (&value),   metadata(NULL /* --> &typeid(std::atomic_flag) */),                type(static_cast<enum type>($shorthand::standard::atomic_flag))                      {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::atto                       const  value) noexcept(noexcept(std::atto                      (instanceof<std::atto>                      ()))) : std_atto                             (value),   metadata(NULL /* --> &typeid(std::atto) */),                       type(static_cast<enum type>($shorthand::standard::atto))                             {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::bidirectional_iterator_tag const  value) noexcept(noexcept(std::bidirectional_iterator_tag(instanceof<std::bidirectional_iterator_tag>()))) : std_bidirectional_iterator_tag       (value),   metadata(NULL /* --> &typeid(std::bidirectional_iterator_tag) */), type(static_cast<enum type>($shorthand::standard::bidirectional_iterator_tag))       {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::centi                      const  value) noexcept(noexcept(std::centi                     (instanceof<std::centi>                     ()))) : std_centi                            (value),   metadata(NULL /* --> &typeid(std::centi) */),                      type(static_cast<enum type>($shorthand::standard::centi))                            {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::deca                       const  value) noexcept(noexcept(std::deca                      (instanceof<std::deca>                      ()))) : std_deca                             (value),   metadata(NULL /* --> &typeid(std::deca) */),                       type(static_cast<enum type>($shorthand::standard::deca))                             {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::deci                       const  value) noexcept(noexcept(std::deci                      (instanceof<std::deci>                      ()))) : std_deci                             (value),   metadata(NULL /* --> &typeid(std::deci) */),                       type(static_cast<enum type>($shorthand::standard::deci))                             {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::div_t                      const  value) noexcept(noexcept(std::div_t                     (instanceof<std::div_t>                     ()))) : std_div_t                            (value),   metadata(NULL /* --> &typeid(std::div_t) */),                      type(static_cast<enum type>($shorthand::standard::div_t))                            {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::exa                        const  value) noexcept(noexcept(std::exa                       (instanceof<std::exa>                       ()))) : std_exa                              (value),   metadata(NULL /* --> &typeid(std::exa) */),                        type(static_cast<enum type>($shorthand::standard::exa))                              {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::false_type                 const  value) noexcept(noexcept(std::false_type                (instanceof<std::false_type>                ()))) : std_false_type                       (value),   metadata(NULL /* --> &typeid(std::false_type) */),                 type(static_cast<enum type>($shorthand::standard::false_type))                       {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::femto                      const  value) noexcept(noexcept(std::femto                     (instanceof<std::femto>                     ()))) : std_femto                            (value),   metadata(NULL /* --> &typeid(std::femto) */),                      type(static_cast<enum type>($shorthand::standard::femto))                            {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::forward_iterator_tag       const  value) noexcept(noexcept(std::forward_iterator_tag      (instanceof<std::forward_iterator_tag>      ()))) : std_forward_iterator_tag             (value),   metadata(NULL /* --> &typeid(std::forward_iterator_tag) */),       type(static_cast<enum type>($shorthand::standard::forward_iterator_tag))             {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::giga                       const  value) noexcept(noexcept(std::giga                      (instanceof<std::giga>                      ()))) : std_giga                             (value),   metadata(NULL /* --> &typeid(std::giga) */),                       type(static_cast<enum type>($shorthand::standard::giga))                             {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::hecto                      const  value) noexcept(noexcept(std::hecto                     (instanceof<std::hecto>                     ()))) : std_hecto                            (value),   metadata(NULL /* --> &typeid(std::hecto) */),                      type(static_cast<enum type>($shorthand::standard::hecto))                            {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::input_iterator_tag         const  value) noexcept(noexcept(std::input_iterator_tag        (instanceof<std::input_iterator_tag>        ()))) : std_input_iterator_tag               (value),   metadata(NULL /* --> &typeid(std::input_iterator_tag) */),         type(static_cast<enum type>($shorthand::standard::input_iterator_tag))               {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::kilo                       const  value) noexcept(noexcept(std::kilo                      (instanceof<std::kilo>                      ()))) : std_kilo                             (value),   metadata(NULL /* --> &typeid(std::kilo) */),                       type(static_cast<enum type>($shorthand::standard::kilo))                             {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::ldiv_t                     const  value) noexcept(noexcept(std::ldiv_t                    (instanceof<std::ldiv_t>                    ()))) : std_ldiv_t                           (value),   metadata(NULL /* --> &typeid(std::ldiv_t) */),                     type(static_cast<enum type>($shorthand::standard::ldiv_t))                           {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::lldiv_t                    const  value) noexcept(noexcept(std::lldiv_t                   (instanceof<std::lldiv_t>                   ()))) : std_lldiv_t                          (value),   metadata(NULL /* --> &typeid(std::lldiv_t) */),                    type(static_cast<enum type>($shorthand::standard::lldiv_t))                          {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::max_align_t                const  value) noexcept(noexcept(std::max_align_t               (instanceof<std::max_align_t>               ()))) : std_max_align_t                      (value),   metadata(NULL /* --> &typeid(std::max_align_t) */),                type(static_cast<enum type>($shorthand::standard::max_align_t))                      {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::mega                       const  value) noexcept(noexcept(std::mega                      (instanceof<std::mega>                      ()))) : std_mega                             (value),   metadata(NULL /* --> &typeid(std::mega) */),                       type(static_cast<enum type>($shorthand::standard::mega))                             {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::memory_order               const  value) noexcept(noexcept(std::memory_order              (instanceof<std::memory_order>              ()))) : std_memory_order                     (value),   metadata(NULL /* --> &typeid(std::memory_order) */),               type(static_cast<enum type>($shorthand::standard::memory_order))                     {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::micro                      const  value) noexcept(noexcept(std::micro                     (instanceof<std::micro>                     ()))) : std_micro                            (value),   metadata(NULL /* --> &typeid(std::micro) */),                      type(static_cast<enum type>($shorthand::standard::micro))                            {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::milli                      const  value) noexcept(noexcept(std::milli                     (instanceof<std::milli>                     ()))) : std_milli                            (value),   metadata(NULL /* --> &typeid(std::milli) */),                      type(static_cast<enum type>($shorthand::standard::milli))                            {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::nano                       const  value) noexcept(noexcept(std::nano                      (instanceof<std::nano>                      ()))) : std_nano                             (value),   metadata(NULL /* --> &typeid(std::nano) */),                       type(static_cast<enum type>($shorthand::standard::nano))                             {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::new_handler                const  value) noexcept(noexcept(std::new_handler               (instanceof<std::new_handler>               ()))) : std_new_terminate_unexpected_handler (value),   metadata(NULL /* --> &typeid(std::new_handler) */),                type(static_cast<enum type>($shorthand::standard::new_terminate_unexpected_handler)) {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::nothrow_t                  const  value) noexcept(noexcept(std::nothrow_t                 (instanceof<std::nothrow_t>                 ()))) : std_nothrow_t                        (value),   metadata(NULL /* --> &typeid(std::nothrow_t) */),                  type(static_cast<enum type>($shorthand::standard::nothrow_t))                        {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::nullptr_t                  const)        noexcept(noexcept(std::nullptr_t                 (nullptr)))                                       : std_nullptr_t                        (nullptr), metadata(NULL /* --> &typeid(std::nullptr_t) */),                  type(static_cast<enum type>($shorthand::standard::nullptr_t))                        {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::output_iterator_tag        const  value) noexcept(noexcept(std::output_iterator_tag       (instanceof<std::output_iterator_tag>       ()))) : std_output_iterator_tag              (value),   metadata(NULL /* --> &typeid(std::output_iterator_tag) */),        type(static_cast<enum type>($shorthand::standard::output_iterator_tag))              {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::owner_less<void>           const  value) noexcept(noexcept(std::owner_less<void>          (instanceof<std::owner_less<void> >         ()))) : std_owner_less                       (value),   metadata(NULL /* --> &typeid(std::owner_less<void>) */),           type(static_cast<enum type>($shorthand::standard::owner_less))                       {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::peta                       const  value) noexcept(noexcept(std::peta                      (instanceof<std::peta>                      ()))) : std_peta                             (value),   metadata(NULL /* --> &typeid(std::peta) */),                       type(static_cast<enum type>($shorthand::standard::peta))                             {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::pico                       const  value) noexcept(noexcept(std::pico                      (instanceof<std::pico>                      ()))) : std_pico                             (value),   metadata(NULL /* --> &typeid(std::pico) */),                       type(static_cast<enum type>($shorthand::standard::pico))                             {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::piecewise_construct_t      const  value) noexcept(noexcept(std::piecewise_construct_t     (instanceof<std::piecewise_construct_t>     ()))) : std_piecewise_construct_t            (value),   metadata(NULL /* --> &typeid(std::piecewise_construct_t) */),      type(static_cast<enum type>($shorthand::standard::piecewise_construct_t))            {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::random_access_iterator_tag const  value) noexcept(noexcept(std::random_access_iterator_tag(instanceof<std::random_access_iterator_tag>()))) : std_random_access_iterator_tag       (value),   metadata(NULL /* --> &typeid(std::random_access_iterator_tag) */), type(static_cast<enum type>($shorthand::standard::random_access_iterator_tag))       {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::tera                       const  value) noexcept(noexcept(std::tera                      (instanceof<std::tera>                      ()))) : std_tera                             (value),   metadata(NULL /* --> &typeid(std::tera) */),                       type(static_cast<enum type>($shorthand::standard::tera))                             {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::true_type                  const  value) noexcept(noexcept(std::true_type                 (instanceof<std::true_type>                 ()))) : std_true_type                        (value),   metadata(NULL /* --> &typeid(std::true_type) */),                  type(static_cast<enum type>($shorthand::standard::true_type))                        {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::type_info                  const& value) noexcept                                                                                           : std_type_info                       (&value),   metadata(NULL /* --> &typeid(std::type_info) */),                  type(static_cast<enum type>($shorthand::standard::type_info))                        {}
      template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard] [arity], std::va_list*                          value) noexcept                                                                                           : std_va_list                          (value),   metadata(NULL /* --> &typeid(std::va_list*) */),                   type(static_cast<enum type>($shorthand::standard::va_list))                          {}
      #ifdef __cpp_aligned_new
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::align_val_t const value) noexcept(noexcept(std::align_val_t(instanceof<std::align_val_t>()))) : std_align_val_t(value), metadata(NULL /* --> &typeid(std::align_val_t) */), type(static_cast<enum type>($shorthand::standard::align_val_t)) {}
      #endif
      #ifdef __cpp_lib_byte
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::byte const value) noexcept(noexcept(std::byte(instanceof<std::byte>()))) : std_byte(value), metadata(NULL /* --> &typeid(std::byte) */), type(static_cast<enum type>($shorthand::standard::byte)) {}
      #endif
      #ifdef __cpp_lib_endian
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::endian const value) noexcept(noexcept(std::endian(instanceof<std::endian>()))) : std_endian(value), metadata(NULL /* --> &typeid(std::endian) */), type(static_cast<enum type>($shorthand::standard::endian)) {}
      #endif
      #ifdef __cpp_lib_ranges
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::ranges::dangling      const value) noexcept(noexcept(std::ranges::dangling     (instanceof<std::ranges::dangling>     ()))) : std_dangling     (value), metadata(NULL /* --> &typeid(std::ranges::dangling) */),      type(static_cast<enum type>($shorthand::standard::dangling))      {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::ranges::subrange_kind const value) noexcept(noexcept(std::ranges::subrange_kind(instanceof<std::ranges::subrange_kind>()))) : std_subrange_kind(value), metadata(NULL /* --> &typeid(std::ranges::subrange_kind) */), type(static_cast<enum type>($shorthand::standard::subrange_kind)) {}
      #endif
      #ifdef __cpp_lib_source_location
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::source_location const value) noexcept(noexcept(std::source_location(instanceof<std::source_location>()))) : std_source_location(value), metadata(NULL /* --> &typeid(std::source_location) */), type(static_cast<enum type>($shorthand::standard::source_location)) {}
      #endif
      #ifdef __cpp_lib_three_way_comparison
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::compare_three_way const value) noexcept(noexcept(std::compare_three_way(instanceof<std::compare_three_way>()))) : std_compare_three_way(value), metadata(NULL /* --> &typeid(std::compare_three_way) */), type(static_cast<enum type>($shorthand::standard::compare_three_way)) {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::partial_ordering  const value) noexcept(noexcept(std::partial_ordering (instanceof<std::partial_ordering> ()))) : std_partial_ordering (value), metadata(NULL /* --> &typeid(std::partial_ordering) */),  type(static_cast<enum type>($shorthand::standard::partial_ordering))  {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::strong_ordering   const value) noexcept(noexcept(std::strong_ordering  (instanceof<std::strong_ordering>  ()))) : std_strong_ordering  (value), metadata(NULL /* --> &typeid(std::strong_ordering) */),   type(static_cast<enum type>($shorthand::standard::strong_ordering))   {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::weak_ordering     const value) noexcept(noexcept(std::weak_ordering    (instanceof<std::weak_ordering>    ()))) : std_weak_ordering    (value), metadata(NULL /* --> &typeid(std::weak_ordering) */),     type(static_cast<enum type>($shorthand::standard::weak_ordering))     {}
        #ifdef __cpp_lib_coroutine
          template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::coroutine_handle<void> const value) noexcept(noexcept(std::coroutine_handle<void>(instanceof<std::coroutine_handle<void> >()))) : std_coroutine_handle      (value), metadata(NULL /* --> &typeid(std::coroutine_handle) */),       type(static_cast<enum type>($shorthand::standard::coroutine_handle))       {}
          template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::noop_coroutine_handle  const value) noexcept(noexcept(std::noop_coroutine_handle (instanceof<std::noop_coroutine_handle>  ()))) : std_noop_coroutine_handle (value), metadata(NULL /* --> &typeid(std::noop_coroutine_handle) */),  type(static_cast<enum type>($shorthand::standard::noop_coroutine_handle))  {}
          template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::noop_coroutine_promise const value) noexcept(noexcept(std::noop_coroutine_promise(instanceof<std::noop_coroutine_promise> ()))) : std_noop_coroutine_promise(value), metadata(NULL /* --> &typeid(std::noop_coroutine_promise) */), type(static_cast<enum type>($shorthand::standard::noop_coroutine_promise)) {}
          template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::suspend_always         const value) noexcept(noexcept(std::suspend_always        (instanceof<std::suspend_always>         ()))) : std_suspend_always        (value), metadata(NULL /* --> &typeid(std::suspend_always) */),         type(static_cast<enum type>($shorthand::standard::suspend_always))         {}
          template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::suspend_never          const value) noexcept(noexcept(std::suspend_never         (instanceof<std::suspend_never>          ()))) : std_suspend_never         (value), metadata(NULL /* --> &typeid(std::suspend_never) */),          type(static_cast<enum type>($shorthand::standard::suspend_never))          {}
        #endif
      #endif
      #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201402L
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::bit_and      <void> const value) noexcept(noexcept(std::bit_and      <void>(instanceof<std::bit_and      <void> >()))) : std_bit_and      (value), metadata(NULL /* --> &typeid(std::bit_and      <void>) */), type(static_cast<enum type>($shorthand::standard::bit_and))       {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::bit_not      <>     const value) noexcept(noexcept(std::bit_not      <>    (instanceof<std::bit_not      <> >    ()))) : std_bit_not      (value), metadata(NULL /* --> &typeid(std::bit_not      <>) */),     type(static_cast<enum type>($shorthand::standard::bit_not))       {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::bit_or       <void> const value) noexcept(noexcept(std::bit_or       <void>(instanceof<std::bit_or       <void> >()))) : std_bit_or       (value), metadata(NULL /* --> &typeid(std::bit_or       <void>) */), type(static_cast<enum type>($shorthand::standard::bit_or))        {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::bit_xor      <void> const value) noexcept(noexcept(std::bit_xor      <void>(instanceof<std::bit_xor      <void> >()))) : std_bit_xor      (value), metadata(NULL /* --> &typeid(std::bit_xor      <void>) */), type(static_cast<enum type>($shorthand::standard::bit_xor))       {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::divides      <void> const value) noexcept(noexcept(std::divides      <void>(instanceof<std::divides      <void> >()))) : std_divides      (value), metadata(NULL /* --> &typeid(std::divides      <void>) */), type(static_cast<enum type>($shorthand::standard::divides))       {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::equal_to     <void> const value) noexcept(noexcept(std::equal_to     <void>(instanceof<std::equal_to     <void> >()))) : std_equal_to     (value), metadata(NULL /* --> &typeid(std::equal_to     <void>) */), type(static_cast<enum type>($shorthand::standard::equal_to))      {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::greater      <void> const value) noexcept(noexcept(std::greater      <void>(instanceof<std::greater      <void> >()))) : std_greater      (value), metadata(NULL /* --> &typeid(std::greater      <void>) */), type(static_cast<enum type>($shorthand::standard::greater))       {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::greater_equal<void> const value) noexcept(noexcept(std::greater_equal<void>(instanceof<std::greater_equal<void> >()))) : std_greater_equal(value), metadata(NULL /* --> &typeid(std::greater_equal<void>) */), type(static_cast<enum type>($shorthand::standard::greater_equal)) {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::less         <void> const value) noexcept(noexcept(std::less         <void>(instanceof<std::less         <void> >()))) : std_less         (value), metadata(NULL /* --> &typeid(std::less         <void>) */), type(static_cast<enum type>($shorthand::standard::less))          {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::less_equal   <void> const value) noexcept(noexcept(std::less_equal   <void>(instanceof<std::less_equal   <void> >()))) : std_less_equal   (value), metadata(NULL /* --> &typeid(std::less_equal   <void>) */), type(static_cast<enum type>($shorthand::standard::less_equal))    {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::logical_and  <void> const value) noexcept(noexcept(std::logical_and  <void>(instanceof<std::logical_and  <void> >()))) : std_logical_and  (value), metadata(NULL /* --> &typeid(std::logical_and  <void>) */), type(static_cast<enum type>($shorthand::standard::logical_and))   {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::logical_not  <void> const value) noexcept(noexcept(std::logical_not  <void>(instanceof<std::logical_not  <void> >()))) : std_logical_not  (value), metadata(NULL /* --> &typeid(std::logical_not  <void>) */), type(static_cast<enum type>($shorthand::standard::logical_not))   {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::logical_or   <void> const value) noexcept(noexcept(std::logical_or   <void>(instanceof<std::logical_or   <void> >()))) : std_logical_or   (value), metadata(NULL /* --> &typeid(std::logical_or   <void>) */), type(static_cast<enum type>($shorthand::standard::logical_or))    {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::minus        <void> const value) noexcept(noexcept(std::minus        <void>(instanceof<std::minus        <void> >()))) : std_minus        (value), metadata(NULL /* --> &typeid(std::minus        <void>) */), type(static_cast<enum type>($shorthand::standard::minus))         {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::modulus      <void> const value) noexcept(noexcept(std::modulus      <void>(instanceof<std::modulus      <void> >()))) : std_modulus      (value), metadata(NULL /* --> &typeid(std::modulus      <void>) */), type(static_cast<enum type>($shorthand::standard::modulus))       {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::multiplies   <void> const value) noexcept(noexcept(std::multiplies   <void>(instanceof<std::multiplies   <void> >()))) : std_multiplies   (value), metadata(NULL /* --> &typeid(std::multiplies   <void>) */), type(static_cast<enum type>($shorthand::standard::multiplies))    {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::negate       <void> const value) noexcept(noexcept(std::negate       <void>(instanceof<std::negate       <void> >()))) : std_negate       (value), metadata(NULL /* --> &typeid(std::negate       <void>) */), type(static_cast<enum type>($shorthand::standard::negate))        {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::not_equal_to <void> const value) noexcept(noexcept(std::not_equal_to <void>(instanceof<std::not_equal_to <void> >()))) : std_not_equal_to (value), metadata(NULL /* --> &typeid(std::not_equal_to <void>) */), type(static_cast<enum type>($shorthand::standard::not_equal_to))  {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::plus         <void> const value) noexcept(noexcept(std::plus         <void>(instanceof<std::plus         <void> >()))) : std_plus         (value), metadata(NULL /* --> &typeid(std::plus         <void>) */), type(static_cast<enum type>($shorthand::standard::plus))          {}
      #endif
      #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201703L
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::in_place_t const value) noexcept(noexcept(std::in_place_t(instanceof<std::in_place_t>()))) : std_in_place_t(value), metadata(NULL /* --> &typeid(std::in_place_t) */), type(static_cast<enum type>($shorthand::standard::in_place_t)) {}
      #endif
      #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 202002L
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::contiguous_iterator_tag const value) noexcept(noexcept(std::contiguous_iterator_tag(instanceof<std::contiguous_iterator_tag>()))) : std_contiguous_iterator_tag(value), metadata(NULL /* --> &typeid(std::contiguous_iterator_tag) */), type(static_cast<enum type>($shorthand::standard::contiguous_iterator_tag)) {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::default_sentinel_t      const value) noexcept(noexcept(std::default_sentinel_t     (instanceof<std::default_sentinel_t>     ()))) : std_default_sentinel_t     (value), metadata(NULL /* --> &typeid(std::default_sentinel_t) */),      type(static_cast<enum type>($shorthand::standard::default_sentinel_t))      {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::destroying_delete_t     const value) noexcept(noexcept(std::destroying_delete_t    (instanceof<std::destroying_delete_t>    ()))) : std_destroying_delete_t    (value), metadata(NULL /* --> &typeid(std::destroying_delete_t) */),     type(static_cast<enum type>($shorthand::standard::destroying_delete_t))     {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::identity                const value) noexcept(noexcept(std::identity               (instanceof<std::identity>               ()))) : std_identity               (value), metadata(NULL /* --> &typeid(std::identity) */),                type(static_cast<enum type>($shorthand::standard::identity))                {}
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::unreachable_sentinel_t  const value) noexcept(noexcept(std::unreachable_sentinel_t (instanceof<std::unreachable_sentinel_t> ()))) : std_unreachable_sentinel_t (value), metadata(NULL /* --> &typeid(std::unreachable_sentinel_t)  */), type(static_cast<enum type>($shorthand::standard::unreachable_sentinel_t))  {}
      #endif
      #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) <= 202002L // --> < 2023..L
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::pointer_safety const value) noexcept(noexcept(std::pointer_safety(instanceof<std::pointer_safety>()))) : std_pointer_safety(value), metadata(NULL /* --> &typeid(std::pointer_safety) */), type(static_cast<enum type>($shorthand::standard::pointer_safety)) {}
      #endif
      #if defined __STDCPP_BFLOAT16_T__
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::bfloat16_t const value) noexcept(noexcept(std::bfloat16_t(instanceof<std::bfloat16_t>()))) : std_bfloat16_t(value), metadata(NULL /* --> &typeid(std::bfloat16_t) */), type(static_cast<enum type>($shorthand::standard::bfloat16_t)) {}
      #endif
      #if defined __STDCPP_FLOAT16_T__
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::float16_t const value) noexcept(noexcept(std::float16_t(instanceof<std::float16_t>()))) : std_float16_t(value), metadata(NULL /* --> &typeid(std::float16_t) */), type(static_cast<enum type>($shorthand::standard::float16_t)) {}
      #endif
      #if defined __STDCPP_FLOAT32_T__
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::float32_t const value) noexcept(noexcept(std::float32_t(instanceof<std::float32_t>()))) : std_float32_t(value), metadata(NULL /* --> &typeid(std::float32_t) */), type(static_cast<enum type>($shorthand::standard::float32_t)) {}
      #endif
      #if defined __STDCPP_FLOAT64_T__
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::float64_t const value) noexcept(noexcept(std::float64_t(instanceof<std::float64_t>()))) : std_float64_t(value), metadata(NULL /* --> &typeid(std::float64_t) */), type(static_cast<enum type>($shorthand::standard::float64_t)) {}
      #endif
      #if defined __STDCPP_FLOAT128_T__
        template <std::size_t arity> constexpr value(bool const (*const)[$shorthand::standard][arity], std::float128_t const value) noexcept(noexcept(std::float128_t(instanceof<std::float128_t>()))) : std_float128_t(value), metadata(NULL /* --> &typeid(std::float128_t) */), type(static_cast<enum type>($shorthand::standard::float128_t)) {}
      #endif
      template <std::size_t arity, typename typed> constexpr value(bool const (*const)[$shorthand::enumeration][arity], typed const value) noexcept : enumeration(static_cast<enum enumeration>(value)), metadata(&typeid(typed)),                      type($shorthand::enumeration) {}
      template <std::size_t arity, typename typed> constexpr value(bool const (*const)[$shorthand::null]       [arity], typed&&)           noexcept : null       (sfinaeptr),                            metadata(NULL /* --> &typeid(sfinaeptr_t) */), type($shorthand::null)        { static_assert(0u == arity, "Shorthand can not accept arguments or too few arguments passed to shorthand"); }

      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_bool          const& value) noexcept(noexcept(std::atomic_bool         (instanceof<std::atomic_bool          const&>().load()))) : std_atomic_bool         {0x00u}, metadata(&typeid(std::atomic_bool)),          type(static_cast<enum type>($shorthand::standard::atomic_bool))          { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_bool)]>         (this -> std_atomic_bool))          std::atomic_bool         (value.load()); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_char          const& value) noexcept(noexcept(std::atomic_char         (instanceof<std::atomic_char          const&>().load()))) : std_atomic_char         {0x00u}, metadata(&typeid(std::atomic_char)),          type(static_cast<enum type>($shorthand::standard::atomic_char))          { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_char)]>         (this -> std_atomic_char))          std::atomic_char         (value.load()); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_int           const& value) noexcept(noexcept(std::atomic_int          (instanceof<std::atomic_int           const&>().load()))) : std_atomic_int          {0x00u}, metadata(&typeid(std::atomic_int)),           type(static_cast<enum type>($shorthand::standard::atomic_int))           { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_int)]>          (this -> std_atomic_int))           std::atomic_int          (value.load()); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_llong         const& value) noexcept(noexcept(std::atomic_llong        (instanceof<std::atomic_llong         const&>().load()))) : std_atomic_llong        {0x00u}, metadata(&typeid(std::atomic_llong)),         type(static_cast<enum type>($shorthand::standard::atomic_llong))         { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_llong)]>        (this -> std_atomic_llong))         std::atomic_llong        (value.load()); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_long          const& value) noexcept(noexcept(std::atomic_long         (instanceof<std::atomic_long          const&>().load()))) : std_atomic_long         {0x00u}, metadata(&typeid(std::atomic_long)),          type(static_cast<enum type>($shorthand::standard::atomic_long))          { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_long)]>         (this -> std_atomic_long))          std::atomic_long         (value.load()); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_schar         const& value) noexcept(noexcept(std::atomic_schar        (instanceof<std::atomic_schar         const&>().load()))) : std_atomic_schar        {0x00u}, metadata(&typeid(std::atomic_schar)),         type(static_cast<enum type>($shorthand::standard::atomic_schar))         { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_schar)]>        (this -> std_atomic_schar))         std::atomic_schar        (value.load()); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_short         const& value) noexcept(noexcept(std::atomic_short        (instanceof<std::atomic_short         const&>().load()))) : std_atomic_short        {0x00u}, metadata(&typeid(std::atomic_short)),         type(static_cast<enum type>($shorthand::standard::atomic_short))         { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_short)]>        (this -> std_atomic_short))         std::atomic_short        (value.load()); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_uchar         const& value) noexcept(noexcept(std::atomic_uchar        (instanceof<std::atomic_uchar         const&>().load()))) : std_atomic_uchar        {0x00u}, metadata(&typeid(std::atomic_uchar)),         type(static_cast<enum type>($shorthand::standard::atomic_uchar))         { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_uchar)]>        (this -> std_atomic_uchar))         std::atomic_uchar        (value.load()); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_uint          const& value) noexcept(noexcept(std::atomic_uint         (instanceof<std::atomic_uint          const&>().load()))) : std_atomic_uint         {0x00u}, metadata(&typeid(std::atomic_uint)),          type(static_cast<enum type>($shorthand::standard::atomic_uint))          { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_uint)]>         (this -> std_atomic_uint))          std::atomic_uint         (value.load()); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_ullong        const& value) noexcept(noexcept(std::atomic_ullong       (instanceof<std::atomic_ullong        const&>().load()))) : std_atomic_ullong       {0x00u}, metadata(&typeid(std::atomic_ullong)),        type(static_cast<enum type>($shorthand::standard::atomic_ullong))        { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_ullong)]>       (this -> std_atomic_ullong))        std::atomic_ullong       (value.load()); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_ulong         const& value) noexcept(noexcept(std::atomic_ulong        (instanceof<std::atomic_ulong         const&>().load()))) : std_atomic_ulong        {0x00u}, metadata(&typeid(std::atomic_ulong)),         type(static_cast<enum type>($shorthand::standard::atomic_ulong))         { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_ulong)]>        (this -> std_atomic_ulong))         std::atomic_ulong        (value.load()); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_ushort        const& value) noexcept(noexcept(std::atomic_ushort       (instanceof<std::atomic_ushort        const&>().load()))) : std_atomic_ushort       {0x00u}, metadata(&typeid(std::atomic_ushort)),        type(static_cast<enum type>($shorthand::standard::atomic_ushort))        { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_ushort)]>       (this -> std_atomic_ushort))        std::atomic_ushort       (value.load()); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_wchar_t       const& value) noexcept(noexcept(std::atomic_wchar_t      (instanceof<std::atomic_wchar_t       const&>().load()))) : std_atomic_wchar_t      {0x00u}, metadata(&typeid(std::atomic_wchar_t)),       type(static_cast<enum type>($shorthand::standard::atomic_wchar_t))       { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_wchar_t)]>      (this -> std_atomic_wchar_t))       std::atomic_wchar_t      (value.load()); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::bad_alloc            const& value) noexcept(noexcept(std::bad_alloc           (instanceof<std::bad_alloc            const&>())))        : std_bad_alloc           {0x00u}, metadata(&typeid(std::bad_alloc)),            type(static_cast<enum type>($shorthand::standard::bad_alloc))            { (void) ::new (const_cast<unsigned char (&)[sizeof(std::bad_alloc)]>           (this -> std_bad_alloc))            std::bad_alloc           (value); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::bad_array_new_length const& value) noexcept(noexcept(std::bad_array_new_length(instanceof<std::bad_array_new_length const&>())))        : std_bad_array_new_length{0x00u}, metadata(&typeid(std::bad_array_new_length)), type(static_cast<enum type>($shorthand::standard::bad_array_new_length)) { (void) ::new (const_cast<unsigned char (&)[sizeof(std::bad_array_new_length)]>(this -> std_bad_array_new_length)) std::bad_array_new_length(value); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::bad_exception        const& value) noexcept(noexcept(std::bad_exception       (instanceof<std::bad_exception        const&>())))        : std_bad_exception       {0x00u}, metadata(&typeid(std::bad_exception)),        type(static_cast<enum type>($shorthand::standard::bad_exception))        { (void) ::new (const_cast<unsigned char (&)[sizeof(std::bad_exception)]>       (this -> std_bad_exception))        std::bad_exception       (value); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::bad_function_call    const& value) noexcept(noexcept(std::bad_function_call   (instanceof<std::bad_function_call    const&>())))        : std_bad_function_call   {0x00u}, metadata(&typeid(std::bad_function_call)),    type(static_cast<enum type>($shorthand::standard::bad_function_call))    { (void) ::new (const_cast<unsigned char (&)[sizeof(std::bad_function_call)]>   (this -> std_bad_function_call))    std::bad_function_call   (value); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::bad_typeid           const& value) noexcept(noexcept(std::bad_typeid          (instanceof<std::bad_typeid           const&>())))        : std_bad_typeid          {0x00u}, metadata(&typeid(std::bad_typeid)),           type(static_cast<enum type>($shorthand::standard::bad_typeid))           { (void) ::new (const_cast<unsigned char (&)[sizeof(std::bad_typeid)]>          (this -> std_bad_typeid))           std::bad_typeid          (value); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::bad_weak_ptr         const& value) noexcept(noexcept(std::bad_weak_ptr        (instanceof<std::bad_weak_ptr         const&>())))        : std_bad_weak_ptr        {0x00u}, metadata(&typeid(std::bad_weak_ptr)),         type(static_cast<enum type>($shorthand::standard::bad_weak_ptr))         { (void) ::new (const_cast<unsigned char (&)[sizeof(std::bad_weak_ptr)]>        (this -> std_bad_weak_ptr))         std::bad_weak_ptr        (value); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::exception            const& value) noexcept(noexcept(std::exception           (instanceof<std::exception            const&>())))        : std_exception           {0x00u}, metadata(&typeid(std::exception)),            type(static_cast<enum type>($shorthand::standard::exception))            { (void) ::new (const_cast<unsigned char (&)[sizeof(std::exception)]>           (this -> std_exception))            std::exception           (value); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::exception_ptr        const  value) noexcept(noexcept(std::exception_ptr       (instanceof<std::exception_ptr>              ())))        : std_exception_ptr       {0x00u}, metadata(&typeid(std::exception_ptr)),        type(static_cast<enum type>($shorthand::standard::exception_ptr))        { (void) ::new (const_cast<unsigned char (&)[sizeof(std::exception_ptr)]>       (this -> std_exception_ptr))        std::exception_ptr       (value); }
      template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::nested_exception     const& value) noexcept(noexcept(std::nested_exception    (instanceof<std::nested_exception     const&>())))        : std_nested_exception    {0x00u}, metadata(&typeid(std::nested_exception)),     type(static_cast<enum type>($shorthand::standard::nested_exception))     { (void) ::new (const_cast<unsigned char (&)[sizeof(std::nested_exception)]>    (this -> std_nested_exception))     std::nested_exception    (value); }
      #ifdef __cpp_char8_t
        template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_char8_t const& value) noexcept(noexcept(std::atomic_char8_t(instanceof<std::atomic_char8_t const&>().load()))) : std_atomic_char8_t{0x00u}, metadata(&typeid(std::atomic_char8_t)), type(static_cast<enum type>($shorthand::standard::atomic_char8_t)) { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_char8_t)]>(this -> std_atomic_char8_t)) std::atomic_char8_t(value.load()); }
      #endif
      #ifdef __cpp_unicode_characters
        template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_char16_t const& value) noexcept(noexcept(std::atomic_char16_t(instanceof<std::atomic_char16_t const&>().load()))) : std_atomic_char16_t{0x00u}, metadata(&typeid(std::atomic_char16_t)), type(static_cast<enum type>($shorthand::standard::atomic_char16_t)) { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_char16_t)]>(this -> std_atomic_char16_t)) std::atomic_char16_t(value.load()); }
        template <std::size_t arity> inline value(bool const (*const)[$shorthand::standard][arity], std::atomic_char32_t const& value) noexcept(noexcept(std::atomic_char32_t(instanceof<std::atomic_char32_t const&>().load()))) : std_atomic_char32_t{0x00u}, metadata(&typeid(std::atomic_char32_t)), type(static_cast<enum type>($shorthand::standard::atomic_char32_t)) { (void) ::new (const_cast<unsigned char (&)[sizeof(std::atomic_char32_t)]>(this -> std_atomic_char32_t)) std::atomic_char32_t(value.load()); }
      #endif

      template <std::size_t arity, typename typed>                    inline value(bool const (*const)[$shorthand::reference][arity], typed&               value)                 noexcept : reference(const_cast<unsigned char*>(&reinterpret_cast<unsigned char const volatile&>(value))), metadata(&typeid(typed)),                 type($shorthand::reference) {}
      template <std::size_t arity, typename typeA, class typeB>       inline value(bool const (*const)[$shorthand::member]   [arity], typeA typeB::* const value)                 noexcept : member   (reinterpret_cast<sfinaeptr_t $shorthand::*>                                (value)),  metadata(&typeid(typeA typeB::*)),        type($shorthand::member)    {}
      template <std::size_t arity, typename typed, typename... types> inline value(bool const (*const)[$shorthand::function] [arity], typed        (*const value)(types...))      noexcept : function (reinterpret_cast<void (*)(...) noexcept>                                   (value)),  metadata(&typeid(typed (types...))),      type($shorthand::function)  {}
      template <std::size_t arity, typename typed, typename... types> inline value(bool const (*const)[$shorthand::function] [arity], typed        (*const value)(types..., ...)) noexcept : function (reinterpret_cast<void (*)(...) noexcept>                                   (value)),  metadata(&typeid(typed (types..., ...))), type($shorthand::function)  {}

      template <std::size_t arity, typename typed>
      inline value(bool const (*const)[$shorthand::undefined][arity], typed&& value) noexcept(noexcept(typename remove_reference<typed>::type(instanceof<typed&&>()))) :
        undefined{{0x00u}, ::new (const_cast<unsigned char*>(this -> undefined.value + (alignof(typed) > alignof(unsigned char[sizeof undefined::value / sizeof(unsigned char)]) ? alignof(typed) - alignof(unsigned char[sizeof undefined::value / sizeof(unsigned char)]) : 0u))) typename remove_reference<typed>::type(forward_cast<typed>(value))},
        metadata (&typeid(typed)),
        type     ($shorthand::undefined)
      {}

      template <std::size_t arityA, std::size_t arityB, $$ state, bool $$c>
      constexpr value(bool const (*const)[$shorthand::shorthand][arityA], $n<arityB, state, $$c, true> const& shorthand) noexcept(noexcept(value(instanceof<value const&>()))) :
        value::value(shorthand.value)
      {}
    };

  public:
    template <class base, class = typename remove_qualifiers<base>::type>
    struct is_shorthand final {
      static bool const value = false;
    };

    template <class base, $op::$$ operation, class... shorthands>
    struct is_shorthand<base, $lambda<operation, shorthands...> > final {
      static bool const value = true;
    };

    template <class base, std::size_t arity, $$ state, bool... states>
    struct is_shorthand<base, $n<arity, state, states...> > final {
      static bool const value = true;
    };

    // ...
    template <$$, typename>
    struct is final {
      static bool const value = false;
    };

    template <typename base>
    struct is<$c, base> final {
      private: typedef typename remove_qualifiers<base>::type type;
      public: static bool const value = (
        is_decimal  <type>::value or
        is_enum     <type>::value or
        is_integer  <type>::value or
        is_pointer  <type>::value or
        is_shorthand<type>::value or

        is_same<type, decltype(std::placeholders::_1)>::value or
        is_same<type, decltype(std::placeholders::_2)>::value or
        is_same<type, std::allocator_arg_t>           ::value or
        is_same<type, std::atto>                      ::value or
        is_same<type, std::bidirectional_iterator_tag>::value or
        is_same<type, std::centi>                     ::value or
        is_same<type, std::deca>                      ::value or
        is_same<type, std::deci>                      ::value or
        is_same<type, std::div_t>                     ::value or
        is_same<type, std::exa>                       ::value or
        is_same<type, std::false_type>                ::value or
        is_same<type, std::femto>                     ::value or
        is_same<type, std::forward_iterator_tag>      ::value or
        is_same<type, std::giga>                      ::value or
        is_same<type, std::hecto>                     ::value or
        is_same<type, std::input_iterator_tag>        ::value or
        is_same<type, std::kilo>                      ::value or
        is_same<type, std::ldiv_t>                    ::value or
        is_same<type, std::lldiv_t>                   ::value or
        is_same<type, std::max_align_t>               ::value or
        is_same<type, std::mega>                      ::value or
        is_same<type, std::memory_order>              ::value or
        is_same<type, std::micro>                     ::value or
        is_same<type, std::milli>                     ::value or
        is_same<type, std::nano>                      ::value or
        is_same<type, std::new_handler>               ::value or
        is_same<type, std::nothrow_t>                 ::value or
        is_same<type, std::nullptr_t>                 ::value or
        is_same<type, std::output_iterator_tag>       ::value or
        is_same<type, std::owner_less<void> >         ::value or
        is_same<type, std::peta>                      ::value or
        is_same<type, std::pico>                      ::value or
        is_same<type, std::piecewise_construct_t>     ::value or
        is_same<type, std::random_access_iterator_tag>::value or
        is_same<type, std::tera>                      ::value or
        is_same<type, std::true_type>                 ::value or
        is_same<type, std::type_info>                 ::value or
        is_same<type, std::va_list*>                  ::value or
        is_same<type, std::va_list const*>            ::value or
        is_same<type, std::va_list const volatile*>   ::value or
        is_same<type, std::va_list       volatile*>   ::value or
        #ifdef __cpp_aligned_new
          is_same<type, std::align_val_t>::value or
        #endif
        #ifdef __cpp_char8_t
          is_same<type, std::atomic_char8_t>::value or
        #endif
        #ifdef __cpp_lib_byte
          is_same<type, std::byte>::value or
        #endif
        #ifdef __cpp_lib_endian
          is_same<type, std::endian>::value or
        #endif
        #ifdef __cpp_lib_ranges
          is_same<type, std::ranges::dangling>     ::value or
          is_same<type, std::ranges::subrange_kind>::value or
        #endif
        #ifdef __cpp_lib_source_location
          is_same<type, std::source_location>::value or
        #endif
        #ifdef __cpp_lib_three_way_comparison
          is_same<type, std::compare_three_way>::value or
          is_same<type, std::partial_ordering> ::value or
          is_same<type, std::strong_ordering>  ::value or
          is_same<type, std::weak_ordering>    ::value or
          #ifdef __cpp_lib_coroutine
            is_same<type, std::coroutine_handle<void> >::value or
            is_same<type, std::noop_coroutine_handle>  ::value or
            is_same<type, std::noop_coroutine_promise> ::value or
            is_same<type, std::suspend_always>         ::value or
            is_same<type, std::suspend_never>          ::value or
          #endif
        #endif
        #ifdef __cpp_unicode_characters
          is_same<type, std::atomic_char16_t>::value or
          is_same<type, std::atomic_char32_t>::value or
        #endif
        #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201402L
          is_same<type, std::bit_and      <void> >::value or
          is_same<type, std::bit_not      <> >    ::value or
          is_same<type, std::bit_or       <void> >::value or
          is_same<type, std::bit_xor      <void> >::value or
          is_same<type, std::divides      <void> >::value or
          is_same<type, std::equal_to     <void> >::value or
          is_same<type, std::greater      <void> >::value or
          is_same<type, std::greater_equal<void> >::value or
          is_same<type, std::less         <void> >::value or
          is_same<type, std::less_equal   <void> >::value or
          is_same<type, std::logical_and  <void> >::value or
          is_same<type, std::logical_not  <void> >::value or
          is_same<type, std::logical_or   <void> >::value or
          is_same<type, std::minus        <void> >::value or
          is_same<type, std::modulus      <void> >::value or
          is_same<type, std::multiplies   <void> >::value or
          is_same<type, std::negate       <void> >::value or
          is_same<type, std::not_equal_to <void> >::value or
          is_same<type, std::plus         <void> >::value or
        #endif
        #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201703L
          is_same<type, std::in_place_t>::value or
        #endif
        #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 202002L
          is_same<type, std::contiguous_iterator_tag>::value or
          is_same<type, std::default_sentinel_t>     ::value or
          is_same<type, std::destroying_delete_t>    ::value or
          is_same<type, std::identity>               ::value or
          is_same<type, std::unreachable_sentinel_t> ::value or
        #endif
        #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) <= 202002L // --> < 2023..L
          is_same<type, std::pointer_safety>::value or
        #endif
        #if defined __STDCPP_BFLOAT16_T__
          is_same<type, std::bfloat16_t>::value or
        #endif
        #if defined __STDCPP_FLOAT16_T__
          is_same<type, std::float16_t>::value or
        #endif
        #if defined __STDCPP_FLOAT32_T__
          is_same<type, std::float32_t>::value or
        #endif
        #if defined __STDCPP_FLOAT64_T__
          is_same<type, std::float64_t>::value or
        #endif
        #if defined __STDCPP_FLOAT128_T__
          is_same<type, std::float128_t>::value or
        #endif
        false
      );
    };

    template <std::size_t arity, $$ state, bool $$c>
    struct is<$o, $n<arity, state, $$c, true> > final {
      static bool const value = true;
    };

    template <$op::$$ operation>
    struct is<$o, $lambda<operation> > final {
      static bool const value = false;
    };

    template <$op::$$ operation, class shorthand, class... shorthands>
    struct is<$o, $lambda<operation, shorthand, shorthands...> > final {
      static bool const value = is<$o, shorthand>::value or is<$o, $lambda<operation, shorthands...> >::value;
    };

  private:
    template <class... shorthands>
    struct members final : members<typename arrayof<shorthands, true + is<$o, shorthands>::value>::type...> {
      constexpr members(shorthands const&... values) noexcept(noexcept(members<typename arrayof<shorthands, true + is<$o, shorthands>::value>::type...>(instanceof<shorthands const&>()...))) :
        members<typename arrayof<shorthands, true + is<$o, shorthands>::value>::type...>::members(values...)
      {}
    };

    template <class shorthand> struct members<shorthand[false + 1u]> {                  constexpr members(shorthand const&)       noexcept                                                                     {} template <std::size_t index> constexpr typename conditional<0u == index, shorthand>::type        at() const noexcept { return {}; } };
    template <class shorthand> struct members<shorthand[true  + 1u]> { shorthand value; constexpr members(shorthand const& value) noexcept(noexcept(shorthand(instanceof<shorthand const&>()))) : value(value) {} template <std::size_t index> constexpr typename conditional<0u == index, shorthand>::type const& at() const noexcept { return this -> value; } };

    template <class shorthandA, class shorthandB> struct members<shorthandA[false + 1u], shorthandB[false + 1u]> {                                       constexpr members(shorthandA const&,        shorthandB const&)        noexcept                                                                                                                                                   {} template <std::size_t index> constexpr typename conditional<0u == index, shorthandA>::type        at() const noexcept { return {}; }             template <std::size_t index> constexpr typename conditional<index == 1u, shorthandB>::type        at() const noexcept { return {}; } };
    template <class shorthandA, class shorthandB> struct members<shorthandA[false + 1u], shorthandB[true  + 1u]> { shorthandB value;                     constexpr members(shorthandA const&,        shorthandB const& value)  noexcept(noexcept(shorthandB(instanceof<shorthandB const&>())))                                                           :                 value (value)  {} template <std::size_t index> constexpr typename conditional<0u == index, shorthandA>::type        at() const noexcept { return {}; }             template <std::size_t index> constexpr typename conditional<index == 1u, shorthandB>::type const& at() const noexcept { return this -> value; } };
    template <class shorthandA, class shorthandB> struct members<shorthandA[true  + 1u], shorthandB[false + 1u]> { shorthandA value;                     constexpr members(shorthandA const& value,  shorthandB const&)        noexcept(noexcept(shorthandA(instanceof<shorthandA const&>())))                                                           : value (value)                  {} template <std::size_t index> constexpr typename conditional<0u == index, shorthandA>::type const& at() const noexcept { return this -> value; }  template <std::size_t index> constexpr typename conditional<index == 1u, shorthandB>::type        at() const noexcept { return {}; } };
    template <class shorthandA, class shorthandB> struct members<shorthandA[true  + 1u], shorthandB[true  + 1u]> { shorthandA valueA; shorthandB valueB; constexpr members(shorthandA const& valueA, shorthandB const& valueB) noexcept(noexcept(shorthandA(instanceof<shorthandA const&>())) and noexcept(shorthandB(instanceof<shorthandB const&>()))) : valueA(valueA), valueB(valueB) {} template <std::size_t index> constexpr typename conditional<0u == index, shorthandA>::type const& at() const noexcept { return this -> valueA; } template <std::size_t index> constexpr typename conditional<index == 1u, shorthandB>::type const& at() const noexcept { return this -> valueB; } };

    template <class shorthandA, class shorthandB, class shorthandC> struct members<shorthandA[false + 1u], shorthandB[false + 1u], shorthandC[false + 1u]> {                                                          constexpr members(shorthandA const&,        shorthandB const&,        shorthandC const&)        noexcept                                                                                                                                                                                                                             {} template <std::size_t index> constexpr typename conditional<0u == index, shorthandA>::type        at() const noexcept { return {}; }             template <std::size_t index> constexpr typename conditional<index == 1u, shorthandB>::type        at() const noexcept { return {}; }             template <std::size_t index> constexpr typename conditional<index == 2u, shorthandC>::type        at() const noexcept { return {}; } };
    template <class shorthandA, class shorthandB, class shorthandC> struct members<shorthandA[false + 1u], shorthandB[false + 1u], shorthandC[true  + 1u]> {                                       shorthandC value;  constexpr members(shorthandA const&,        shorthandB const&,        shorthandC const& value)  noexcept(noexcept(shorthandC(instanceof<shorthandC const&>())))                                                                                                                     :                                 value (value)  {} template <std::size_t index> constexpr typename conditional<0u == index, shorthandA>::type        at() const noexcept { return {}; }             template <std::size_t index> constexpr typename conditional<index == 1u, shorthandB>::type        at() const noexcept { return {}; }             template <std::size_t index> constexpr typename conditional<index == 2u, shorthandC>::type const& at() const noexcept { return this -> value; } };
    template <class shorthandA, class shorthandB, class shorthandC> struct members<shorthandA[false + 1u], shorthandB[true  + 1u], shorthandC[false + 1u]> {                    shorthandB value;                     constexpr members(shorthandA const&,        shorthandB const& value,  shorthandC const&)        noexcept(noexcept(shorthandB(instanceof<shorthandB const&>())))                                                                                                                     :                 value (value)                  {} template <std::size_t index> constexpr typename conditional<0u == index, shorthandA>::type        at() const noexcept { return {}; }             template <std::size_t index> constexpr typename conditional<index == 1u, shorthandB>::type const& at() const noexcept { return this -> value; }  template <std::size_t index> constexpr typename conditional<index == 2u, shorthandC>::type        at() const noexcept { return {}; } };
    template <class shorthandA, class shorthandB, class shorthandC> struct members<shorthandA[false + 1u], shorthandB[true  + 1u], shorthandC[true  + 1u]> {                    shorthandB valueB; shorthandC valueC; constexpr members(shorthandA const&,        shorthandB const& valueB, shorthandC const& valueC) noexcept(noexcept(shorthandB(instanceof<shorthandB const&>())) and noexcept(shorthandC(instanceof<shorthandC const&>())))                                                           :                 valueB(valueB), valueC(valueC) {} template <std::size_t index> constexpr typename conditional<0u == index, shorthandA>::type        at() const noexcept { return {}; }             template <std::size_t index> constexpr typename conditional<index == 1u, shorthandB>::type const& at() const noexcept { return this -> valueB; } template <std::size_t index> constexpr typename conditional<index == 2u, shorthandC>::type const& at() const noexcept { return this -> valueC; } };
    template <class shorthandA, class shorthandB, class shorthandC> struct members<shorthandA[true  + 1u], shorthandB[false + 1u], shorthandC[false + 1u]> { shorthandA value;                                        constexpr members(shorthandA const& value,  shorthandB const&,        shorthandC const&)        noexcept(noexcept(shorthandA(instanceof<shorthandA const&>())))                                                                                                                     : value (value)                                  {} template <std::size_t index> constexpr typename conditional<0u == index, shorthandA>::type const& at() const noexcept { return this -> value; }  template <std::size_t index> constexpr typename conditional<index == 1u, shorthandB>::type        at() const noexcept { return {}; }             template <std::size_t index> constexpr typename conditional<index == 2u, shorthandC>::type        at() const noexcept { return {}; } };
    template <class shorthandA, class shorthandB, class shorthandC> struct members<shorthandA[true  + 1u], shorthandB[false + 1u], shorthandC[true  + 1u]> { shorthandA valueA;                    shorthandC valueC; constexpr members(shorthandA const& valueA, shorthandB const&,        shorthandC const& valueC) noexcept(noexcept(shorthandA(instanceof<shorthandA const&>())) and noexcept(shorthandC(instanceof<shorthandC const&>())))                                                           : valueA(valueA),                 valueC(valueC) {} template <std::size_t index> constexpr typename conditional<0u == index, shorthandA>::type const& at() const noexcept { return this -> valueA; } template <std::size_t index> constexpr typename conditional<index == 1u, shorthandB>::type        at() const noexcept { return {}; }             template <std::size_t index> constexpr typename conditional<index == 2u, shorthandC>::type const& at() const noexcept { return this -> valueC; } };
    template <class shorthandA, class shorthandB, class shorthandC> struct members<shorthandA[true  + 1u], shorthandB[true  + 1u], shorthandC[false + 1u]> { shorthandA valueA; shorthandB valueB;                    constexpr members(shorthandA const& valueA, shorthandB const& valueB, shorthandC const&)        noexcept(noexcept(shorthandA(instanceof<shorthandA const&>())) and noexcept(shorthandB(instanceof<shorthandC const&>())))                                                           : valueA(valueA), valueB(valueB)                 {} template <std::size_t index> constexpr typename conditional<0u == index, shorthandA>::type const& at() const noexcept { return this -> valueA; } template <std::size_t index> constexpr typename conditional<index == 1u, shorthandB>::type const& at() const noexcept { return this -> valueB; } template <std::size_t index> constexpr typename conditional<index == 2u, shorthandC>::type        at() const noexcept { return {}; } };
    template <class shorthandA, class shorthandB, class shorthandC> struct members<shorthandA[true  + 1u], shorthandB[true  + 1u], shorthandC[true  + 1u]> { shorthandA valueA; shorthandB valueB; shorthandC valueC; constexpr members(shorthandA const& valueA, shorthandB const& valueB, shorthandC const& valueC) noexcept(noexcept(shorthandA(instanceof<shorthandA const&>())) and noexcept(shorthandB(instanceof<shorthandB const&>())) and noexcept(shorthandC(instanceof<shorthandC const&>()))) : valueA(valueA), valueB(valueB), valueC(valueC) {} template <std::size_t index> constexpr typename conditional<0u == index, shorthandA>::type const& at() const noexcept { return this -> valueA; } template <std::size_t index> constexpr typename conditional<index == 1u, shorthandB>::type const& at() const noexcept { return this -> valueB; } template <std::size_t index> constexpr typename conditional<index == 2u, shorthandC>::type const& at() const noexcept { return this -> valueC; } };
};

// ...
template <std::size_t arity, $$, bool, bool>
struct $n : public $shorthand {
  template <typename... types>
  constexpr typename conditional<0u == arity or sizeof...(types) != sizeof...(types), void>::type operator ()(types&&...) const volatile noexcept {
    return static_cast<void>(sfinaeptr);
  }

  template <typename... types>
  constexpr typename conditional<(arity > sizeof...(types)), sfinaeptr_t>::type operator ()(types&&...) const volatile noexcept {
    static_assert(arity <= sizeof...(types) + 1u, "Too few arguments passed to shorthand");
    return sfinaeptr;
  }

  template <typename type, typename... types>
  constexpr typename conditional<arity == 1u and arity <= sizeof...(types) + 1u, type&&>::type operator ()(type&& argument, types&&...) const volatile noexcept {
    return forward_cast<type>(argument);
  }

  template <typename type, typename... types>
  constexpr typename conditional<(arity > 1u and arity <= sizeof...(types) + 1u), typename at<arity - 1u, type&&, types&&...>::type>::type operator ()(type&&, types&&... arguments) const volatile noexcept {
    return $n<arity - 1u>{}.operator ()(forward_cast<types>(arguments)...);
  }

  // ...
  template <typename type>
  constexpr operator type() const noexcept {
    static_assert(is_function<typename remove_pointer<typename remove_qualifiers<type>::type>::type>::value, "Expected conversion from shorthand to function type");
    static_assert(arity <= cast<arity, typename remove_pointer<typename remove_qualifiers<type>::type>::type>::adicity, "Can not convert shorthand to given function type");

    return cast<arity, typename remove_pointer<typename remove_qualifiers<type>::type>::type>::value;
  }
};

template <std::size_t arity, $$ state, bool $$c>
struct $n<arity, state, $$c, true /* --> $$o */> : public $n<arity, state, $$c, false>, public $shorthand {
  template <std::size_t, $$, bool, bool>
  friend struct $n;

  friend struct $shorthand::value;

  private:
    template <typename base, typename subbase = typename remove_qualifiers<base>::type>
    struct valueof final {
      static type const value = (
        is_shorthand       <subbase>                               ::value ? $shorthand::shorthand   :
        is_function        <typename remove_pointer<subbase>::type>::value ? $shorthand::function    :
        is_lvalue_reference<base>                                  ::value ? $shorthand::reference   :
        is_decimal         <subbase>                               ::value ? $shorthand::decimal     :
        is_enum            <subbase>                               ::value ? $shorthand::enumeration :
        is_integer         <subbase>                               ::value ? $shorthand::integer     :
        is_member_pointer  <subbase>                               ::value ? $shorthand::member      :
        is_pointer         <subbase>                               ::value ? $shorthand::pointer     :

        is_same<subbase, decltype(std::placeholders::_1)>::value or
        is_same<subbase, decltype(std::placeholders::_2)>::value or
        is_same<subbase, std::allocator_arg_t>           ::value or
        is_same<subbase, std::atto>                      ::value or
        is_same<subbase, std::bidirectional_iterator_tag>::value or
        is_same<subbase, std::centi>                     ::value or
        is_same<subbase, std::deca>                      ::value or
        is_same<subbase, std::deci>                      ::value or
        is_same<subbase, std::div_t>                     ::value or
        is_same<subbase, std::exa>                       ::value or
        is_same<subbase, std::false_type>                ::value or
        is_same<subbase, std::femto>                     ::value or
        is_same<subbase, std::forward_iterator_tag>      ::value or
        is_same<subbase, std::giga>                      ::value or
        is_same<subbase, std::hecto>                     ::value or
        is_same<subbase, std::input_iterator_tag>        ::value or
        is_same<subbase, std::kilo>                      ::value or
        is_same<subbase, std::ldiv_t>                    ::value or
        is_same<subbase, std::lldiv_t>                   ::value or
        is_same<subbase, std::max_align_t>               ::value or
        is_same<subbase, std::mega>                      ::value or
        is_same<subbase, std::memory_order>              ::value or
        is_same<subbase, std::micro>                     ::value or
        is_same<subbase, std::milli>                     ::value or
        is_same<subbase, std::nano>                      ::value or
        is_same<subbase, std::new_handler>               ::value or
        is_same<subbase, std::nothrow_t>                 ::value or
        is_same<subbase, std::nullptr_t>                 ::value or
        is_same<subbase, std::output_iterator_tag>       ::value or
        is_same<subbase, std::owner_less<void> >         ::value or
        is_same<subbase, std::peta>                      ::value or
        is_same<subbase, std::pico>                      ::value or
        is_same<subbase, std::piecewise_construct_t>     ::value or
        is_same<subbase, std::random_access_iterator_tag>::value or
        is_same<subbase, std::tera>                      ::value or
        is_same<subbase, std::true_type>                 ::value or
        is_same<subbase, std::type_info>                 ::value or
        is_same<subbase, std::va_list*>                  ::value or
        is_same<subbase, std::va_list const*>            ::value or
        is_same<subbase, std::va_list const volatile*>   ::value or
        is_same<subbase, std::va_list       volatile*>   ::value or
        #ifdef __cpp_aligned_new
          is_same<subbase, std::align_val_t>::value or
        #endif
        #ifdef __cpp_char8_t
          is_same<subbase, std::atomic_char8_t>::value or
        #endif
        #ifdef __cpp_lib_byte
          is_same<subbase, std::byte>::value or
        #endif
        #ifdef __cpp_lib_endian
          is_same<subbase, std::endian>::value or
        #endif
        #ifdef __cpp_lib_ranges
          is_same<subbase, std::ranges::dangling>     ::value or
          is_same<subbase, std::ranges::subrange_kind>::value or
        #endif
        #ifdef __cpp_lib_source_location
          is_same<subbase, std::source_location>::value or
        #endif
        #ifdef __cpp_lib_three_way_comparison
          is_same<subbase, std::compare_three_way>::value or
          is_same<subbase, std::partial_ordering> ::value or
          is_same<subbase, std::strong_ordering>  ::value or
          is_same<subbase, std::weak_ordering>    ::value or
          #ifdef __cpp_lib_coroutine
            is_same<subbase, std::coroutine_handle<void> >::value or
            is_same<subbase, std::noop_coroutine_handle>  ::value or
            is_same<subbase, std::noop_coroutine_promise> ::value or
            is_same<subbase, std::suspend_always>         ::value or
            is_same<subbase, std::suspend_never>          ::value or
          #endif
        #endif
        #ifdef __cpp_unicode_characters
          is_same<subbase, std::atomic_char16_t>::value or
          is_same<subbase, std::atomic_char32_t>::value or
        #endif
        #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201402L
          is_same<subbase, std::bit_and      <void> >::value or
          is_same<subbase, std::bit_not      <> >    ::value or
          is_same<subbase, std::bit_or       <void> >::value or
          is_same<subbase, std::bit_xor      <void> >::value or
          is_same<subbase, std::divides      <void> >::value or
          is_same<subbase, std::equal_to     <void> >::value or
          is_same<subbase, std::greater      <void> >::value or
          is_same<subbase, std::greater_equal<void> >::value or
          is_same<subbase, std::less         <void> >::value or
          is_same<subbase, std::less_equal   <void> >::value or
          is_same<subbase, std::logical_and  <void> >::value or
          is_same<subbase, std::logical_not  <void> >::value or
          is_same<subbase, std::logical_or   <void> >::value or
          is_same<subbase, std::minus        <void> >::value or
          is_same<subbase, std::modulus      <void> >::value or
          is_same<subbase, std::multiplies   <void> >::value or
          is_same<subbase, std::negate       <void> >::value or
          is_same<subbase, std::not_equal_to <void> >::value or
          is_same<subbase, std::plus         <void> >::value or
        #endif
        #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201703L
          is_same<subbase, std::in_place_t>::value or
        #endif
        #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 202002L
          is_same<subbase, std::contiguous_iterator_tag>::value or
          is_same<subbase, std::default_sentinel_t>     ::value or
          is_same<subbase, std::destroying_delete_t>    ::value or
          is_same<subbase, std::identity>               ::value or
          is_same<subbase, std::unreachable_sentinel_t> ::value or
        #endif
        #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) <= 202002L // --> < 2023..L
          is_same<subbase, std::pointer_safety>::value or
        #endif
        #if defined __STDCPP_BFLOAT16_T__
          is_same<subbase, std::bfloat16_t>::value or
        #endif
        #if defined __STDCPP_FLOAT16_T__
          is_same<subbase, std::float16_t>::value or
        #endif
        #if defined __STDCPP_FLOAT32_T__
          is_same<subbase, std::float32_t>::value or
        #endif
        #if defined __STDCPP_FLOAT64_T__
          is_same<subbase, std::float64_t>::value or
        #endif
        #if defined __STDCPP_FLOAT128_T__
          is_same<subbase, std::float128_t>::value or
        #endif
        (0u == (static_cast<unsigned char>(state) & static_cast<unsigned char>($c)) and (
          is_same<subbase, std::atomic_bool>                ::value or
          is_same<subbase, std::atomic_char>                ::value or
          is_same<subbase, std::atomic_flag*>               ::value or
          is_same<subbase, std::atomic_flag const*>         ::value or
          is_same<subbase, std::atomic_flag const volatile*>::value or
          is_same<subbase, std::atomic_flag       volatile*>::value or
          is_same<subbase, std::atomic_int>                 ::value or
          is_same<subbase, std::atomic_llong>               ::value or
          is_same<subbase, std::atomic_long>                ::value or
          is_same<subbase, std::atomic_schar>               ::value or
          is_same<subbase, std::atomic_short>               ::value or
          is_same<subbase, std::atomic_uchar>               ::value or
          is_same<subbase, std::atomic_uint>                ::value or
          is_same<subbase, std::atomic_ullong>              ::value or
          is_same<subbase, std::atomic_ulong>               ::value or
          is_same<subbase, std::atomic_ushort>              ::value or
          is_same<subbase, std::atomic_wchar_t>             ::value or
          is_same<subbase, std::bad_alloc>                  ::value or
          is_same<subbase, std::bad_array_new_length>       ::value or
          is_same<subbase, std::bad_cast>                   ::value or
          is_same<subbase, std::bad_exception>              ::value or
          is_same<subbase, std::bad_function_call>          ::value or
          is_same<subbase, std::bad_typeid>                 ::value or
          is_same<subbase, std::bad_weak_ptr>               ::value or
          is_same<subbase, std::exception>                  ::value or
          is_same<subbase, std::exception_ptr>              ::value or
          is_same<subbase, std::nested_exception>           ::value
        )) ? $shorthand::standard :

        (std::is_trivially_destructible<subbase>::value)                    and
        (is_rvalue_reference<base>::value or not is_reference<base>::value) and
        (alignof(typename conditional<is_function<subbase>::value or is_void<subbase>::value, subbase*, subbase>::type) <= alignof(unsigned char[sizeof undefined::value / sizeof(unsigned char)])
          ? sizeof undefined::value >= sizeof(typename conditional<is_function<subbase>::value or is_void<subbase>::value, subbase*, subbase>::type) and 0u == alignof(unsigned char[sizeof undefined::value / sizeof(unsigned char)]) % alignof(typename conditional<is_function<subbase>::value or is_void<subbase>::value, subbase*, subbase>::type)
          : sizeof undefined::value >= sizeof(typename conditional<is_function<subbase>::value or is_void<subbase>::value, subbase*, subbase>::type) + (alignof(typename conditional<is_function<subbase>::value or is_void<subbase>::value, subbase*, subbase>::type) - alignof(unsigned char[sizeof undefined::value / sizeof(unsigned char)]))
        ) ? $shorthand::undefined :

        $shorthand::null
      );
    };

    // ...
    template <typename base>
    struct nocast final {
      constexpr static base (*value)() noexcept = NULL;
    };

    // ...
    template <std::size_t, typename base, typename = typename remove_qualifiers<base>::type, enum $shorthand::type = valueof<base>::value>
    struct cast final {
      constexpr static base value($shorthand::value const&) noexcept {
        static_assert(0u == sizeof(base), "Can not convert shorthand");
        return nocast<base>::value();
      }
    };

    template <std::size_t subarity> struct cast<subarity, void,                void, $shorthand::null> final { constexpr static sfinaeptr_t value($shorthand::value const&) noexcept { return sfinaeptr; } };
    template <std::size_t subarity> struct cast<subarity, void const,          void, $shorthand::null> final { constexpr static sfinaeptr_t value($shorthand::value const&) noexcept { return sfinaeptr; } };
    template <std::size_t subarity> struct cast<subarity, void const volatile, void, $shorthand::null> final { constexpr static sfinaeptr_t value($shorthand::value const&) noexcept { return sfinaeptr; } };
    template <std::size_t subarity> struct cast<subarity, void       volatile, void, $shorthand::null> final { constexpr static sfinaeptr_t value($shorthand::value const&) noexcept { return sfinaeptr; } };

    template <std::size_t subarity, typename base> struct cast<subarity, base, decltype(std::placeholders::_1),  $shorthand::standard> final { constexpr static decltype(std::placeholders::_1)  value($shorthand::value const& value) noexcept { return value.std_placeholders_1; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, decltype(std::placeholders::_2),  $shorthand::standard> final { constexpr static decltype(std::placeholders::_2)  value($shorthand::value const& value) noexcept { return value.std_placeholders_2; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::allocator_arg_t,             $shorthand::standard> final { constexpr static std::allocator_arg_t             value($shorthand::value const& value) noexcept { return value.std_allocator_arg_t; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_bool,                 $shorthand::standard> final { constexpr static std::atomic_bool                 value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_bool const*>(value.std_atomic_bool) /* --> std::launder(...) */ -> load()}; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_char,                 $shorthand::standard> final { constexpr static std::atomic_char                 value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_char const*>(value.std_atomic_char) /* --> std::launder(...) */ -> load()}; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_flag*,                $shorthand::standard> final { constexpr static std::atomic_flag*                value($shorthand::value const& value) noexcept { return value.std_atomic_flag; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_flag const*,          $shorthand::standard> final { constexpr static std::atomic_flag const*          value($shorthand::value const& value) noexcept { return value.std_atomic_flag; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_flag const volatile*, $shorthand::standard> final { constexpr static std::atomic_flag const volatile* value($shorthand::value const& value) noexcept { return value.std_atomic_flag; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_flag       volatile*, $shorthand::standard> final { constexpr static std::atomic_flag       volatile* value($shorthand::value const& value) noexcept { return value.std_atomic_flag; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_int,                  $shorthand::standard> final { constexpr static std::atomic_int                  value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_int     const*>(value.std_atomic_int)     /* --> std::launder(...) */ -> load()}; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_llong,                $shorthand::standard> final { constexpr static std::atomic_llong                value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_llong   const*>(value.std_atomic_llong)   /* --> std::launder(...) */ -> load()}; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_long,                 $shorthand::standard> final { constexpr static std::atomic_long                 value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_long    const*>(value.std_atomic_long)    /* --> std::launder(...) */ -> load()}; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_schar,                $shorthand::standard> final { constexpr static std::atomic_schar                value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_schar   const*>(value.std_atomic_schar)   /* --> std::launder(...) */ -> load()}; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_short,                $shorthand::standard> final { constexpr static std::atomic_short                value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_short   const*>(value.std_atomic_short)   /* --> std::launder(...) */ -> load()}; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_uchar,                $shorthand::standard> final { constexpr static std::atomic_uchar                value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_uchar   const*>(value.std_atomic_uchar)   /* --> std::launder(...) */ -> load()}; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_uint,                 $shorthand::standard> final { constexpr static std::atomic_uint                 value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_uint    const*>(value.std_atomic_uint)    /* --> std::launder(...) */ -> load()}; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_ullong,               $shorthand::standard> final { constexpr static std::atomic_ullong               value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_ullong  const*>(value.std_atomic_ullong)  /* --> std::launder(...) */ -> load()}; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_ulong,                $shorthand::standard> final { constexpr static std::atomic_ulong                value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_ulong   const*>(value.std_atomic_ulong)   /* --> std::launder(...) */ -> load()}; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_ushort,               $shorthand::standard> final { constexpr static std::atomic_ushort               value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_ushort  const*>(value.std_atomic_ushort)  /* --> std::launder(...) */ -> load()}; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_wchar_t,              $shorthand::standard> final { constexpr static std::atomic_wchar_t              value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_wchar_t const*>(value.std_atomic_wchar_t) /* --> std::launder(...) */ -> load()}; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::atto,                        $shorthand::standard> final { constexpr static std::atto                        value($shorthand::value const& value) noexcept { return value.std_atto; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::bad_alloc,                   $shorthand::standard> final { inline    static std::bad_alloc                   value($shorthand::value const& value) noexcept { return *reinterpret_cast<std::bad_alloc            const*>(value.std_bad_alloc);            /* --> std::launder(...) */ } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::bad_array_new_length,        $shorthand::standard> final { inline    static std::bad_array_new_length        value($shorthand::value const& value) noexcept { return *reinterpret_cast<std::bad_array_new_length const*>(value.std_bad_array_new_length); /* --> std::launder(...) */ } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::bad_cast,                    $shorthand::standard> final { inline    static std::bad_cast                    value($shorthand::value const& value) noexcept { return *reinterpret_cast<std::bad_cast             const*>(value.std_bad_cast);             /* --> std::launder(...) */ } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::bad_exception,               $shorthand::standard> final { inline    static std::bad_exception               value($shorthand::value const& value) noexcept { return *reinterpret_cast<std::bad_exception        const*>(value.std_bad_exception);        /* --> std::launder(...) */ } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::bad_function_call,           $shorthand::standard> final { inline    static std::bad_function_call           value($shorthand::value const& value) noexcept { return *reinterpret_cast<std::bad_function_call    const*>(value.std_bad_function_call);    /* --> std::launder(...) */ } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::bad_typeid,                  $shorthand::standard> final { inline    static std::bad_typeid                  value($shorthand::value const& value) noexcept { return *reinterpret_cast<std::bad_typeid           const*>(value.std_bad_typeid);           /* --> std::launder(...) */ } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::bad_weak_ptr,                $shorthand::standard> final { inline    static std::bad_weak_ptr                value($shorthand::value const& value) noexcept { return *reinterpret_cast<std::bad_weak_ptr         const*>(value.std_bad_weak_ptr);         /* --> std::launder(...) */ } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::bidirectional_iterator_tag,  $shorthand::standard> final { constexpr static std::bidirectional_iterator_tag  value($shorthand::value const& value) noexcept { return value.std_bidirectional_iterator_tag; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::centi,                       $shorthand::standard> final { constexpr static std::centi                       value($shorthand::value const& value) noexcept { return value.std_centi; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::deca,                        $shorthand::standard> final { constexpr static std::deca                        value($shorthand::value const& value) noexcept { return value.std_deca; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::deci,                        $shorthand::standard> final { constexpr static std::deci                        value($shorthand::value const& value) noexcept { return value.std_deci; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::div_t,                       $shorthand::standard> final { constexpr static std::div_t                       value($shorthand::value const& value) noexcept { return value.std_div_t; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::exa,                         $shorthand::standard> final { constexpr static std::exa                         value($shorthand::value const& value) noexcept { return value.std_exa; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::exception,                   $shorthand::standard> final { inline    static std::exception                   value($shorthand::value const& value) noexcept { return *reinterpret_cast<std::exception     const*>(value.std_exception);     /* --> std::launder(...) */ } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::exception_ptr,               $shorthand::standard> final { inline    static std::exception_ptr               value($shorthand::value const& value) noexcept { return *reinterpret_cast<std::exception_ptr const*>(value.std_exception_ptr); /* --> std::launder(...) */ } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::false_type,                  $shorthand::standard> final { constexpr static std::false_type                  value($shorthand::value const& value) noexcept { return value.std_false_type; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::femto,                       $shorthand::standard> final { constexpr static std::femto                       value($shorthand::value const& value) noexcept { return value.std_femto; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::forward_iterator_tag,        $shorthand::standard> final { constexpr static std::forward_iterator_tag        value($shorthand::value const& value) noexcept { return value.std_forward_iterator_tag; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::giga,                        $shorthand::standard> final { constexpr static std::giga                        value($shorthand::value const& value) noexcept { return value.std_giga; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::hecto,                       $shorthand::standard> final { constexpr static std::hecto                       value($shorthand::value const& value) noexcept { return value.std_hecto; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::input_iterator_tag,          $shorthand::standard> final { constexpr static std::input_iterator_tag          value($shorthand::value const& value) noexcept { return value.std_input_iterator_tag; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::kilo,                        $shorthand::standard> final { constexpr static std::kilo                        value($shorthand::value const& value) noexcept { return value.std_kilo; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::ldiv_t,                      $shorthand::standard> final { constexpr static std::ldiv_t                      value($shorthand::value const& value) noexcept { return value.std_ldiv_t; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::lldiv_t,                     $shorthand::standard> final { constexpr static std::lldiv_t                     value($shorthand::value const& value) noexcept { return value.std_lldiv_t; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::max_align_t,                 $shorthand::standard> final { constexpr static std::max_align_t                 value($shorthand::value const& value) noexcept { return value.std_max_align_t; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::mega,                        $shorthand::standard> final { constexpr static std::mega                        value($shorthand::value const& value) noexcept { return value.std_mega; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::memory_order,                $shorthand::standard> final { constexpr static std::memory_order                value($shorthand::value const& value) noexcept { return value.std_memory_order; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::micro,                       $shorthand::standard> final { constexpr static std::micro                       value($shorthand::value const& value) noexcept { return value.std_micro; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::milli,                       $shorthand::standard> final { constexpr static std::milli                       value($shorthand::value const& value) noexcept { return value.std_milli; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::nano,                        $shorthand::standard> final { constexpr static std::nano                        value($shorthand::value const& value) noexcept { return value.std_nano; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::nested_exception,            $shorthand::standard> final { inline    static std::nested_exception            value($shorthand::value const& value) noexcept { return *reinterpret_cast<std::nested_exception const*>(value.std_nested_exception); /* --> std::launder(...) */ } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::new_handler,                 $shorthand::standard> final { constexpr static std::new_handler                 value($shorthand::value const& value) noexcept { return value.std_new_terminate_unexpected_handler; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::nothrow_t,                   $shorthand::standard> final { constexpr static std::nothrow_t                   value($shorthand::value const& value) noexcept { return value.std_nothrow_t; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::nullptr_t,                   $shorthand::standard> final { constexpr static std::nullptr_t                   value($shorthand::value const& value) noexcept { return value.std_nullptr_t; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::output_iterator_tag,         $shorthand::standard> final { constexpr static std::output_iterator_tag         value($shorthand::value const& value) noexcept { return value.std_output_iterator_tag; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::owner_less<void>,            $shorthand::standard> final { constexpr static std::owner_less<void>            value($shorthand::value const& value) noexcept { return value.std_owner_less; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::peta,                        $shorthand::standard> final { constexpr static std::peta                        value($shorthand::value const& value) noexcept { return value.std_peta; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::pico,                        $shorthand::standard> final { constexpr static std::pico                        value($shorthand::value const& value) noexcept { return value.std_pico; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::piecewise_construct_t,       $shorthand::standard> final { constexpr static std::piecewise_construct_t       value($shorthand::value const& value) noexcept { return value.std_piecewise_construct_t; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::random_access_iterator_tag,  $shorthand::standard> final { constexpr static std::random_access_iterator_tag  value($shorthand::value const& value) noexcept { return value.std_random_access_iterator_tag; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::tera,                        $shorthand::standard> final { constexpr static std::tera                        value($shorthand::value const& value) noexcept { return value.std_tera; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::true_type,                   $shorthand::standard> final { constexpr static std::true_type                   value($shorthand::value const& value) noexcept { return value.std_true_type; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::type_info,                   $shorthand::standard> final { constexpr static std::type_info const&            value($shorthand::value const& value) noexcept { return *value.std_type_info; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::va_list*,                    $shorthand::standard> final { constexpr static std::va_list*                    value($shorthand::value const& value) noexcept { return value.std_va_list; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::va_list const*,              $shorthand::standard> final { constexpr static std::va_list const*              value($shorthand::value const& value) noexcept { return value.std_va_list; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::va_list const volatile*,     $shorthand::standard> final { constexpr static std::va_list const volatile*     value($shorthand::value const& value) noexcept { return value.std_va_list; } };
    template <std::size_t subarity, typename base> struct cast<subarity, base, std::va_list       volatile*,     $shorthand::standard> final { constexpr static std::va_list       volatile*     value($shorthand::value const& value) noexcept { return value.std_va_list; } };
    #ifdef __cpp_aligned_new
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::align_val_t, $shorthand::standard> final { constexpr static std::align_val_t value($shorthand::value const& value) noexcept { return value.std_align_val_t; } };
    #endif
    #ifdef __cpp_char8_t
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_char8_t, $shorthand::standard> final { constexpr static std::atomic_char8_t value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_char8_t const*>(value.std_atomic_char8_t) /* --> std::launder(...) */ -> load()}; } };
    #endif
    #ifdef __cpp_lib_byte
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::byte, $shorthand::standard> final { constexpr static std::byte value($shorthand::value const& value) noexcept { return value.std_byte; } };
    #endif
    #ifdef __cpp_lib_endian
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::endian, $shorthand::standard> final { constexpr static std::endian value($shorthand::value const& value) noexcept { return value.std_endian; } };
    #endif
    #ifdef __cpp_lib_ranges
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::ranges::dangling,      $shorthand::standard> final { constexpr static std::ranges::dangling      value($shorthand::value const& value) noexcept { return value.std_dangling; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::ranges::subrange_kind, $shorthand::standard> final { constexpr static std::ranges::subrange_kind value($shorthand::value const& value) noexcept { return value.std_subrange_kind; } };
    #endif
    #ifdef __cpp_lib_source_location
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::source_location, $shorthand::standard> final { constexpr static std::source_location value($shorthand::value const& value) noexcept { return value.std_source_location; } };
    #endif
    #ifdef __cpp_lib_three_way_comparison
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::compare_three_way, $shorthand::standard> final { constexpr static std::compare_three_way value($shorthand::value const& value) noexcept { return value.std_compare_three_way; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::partial_ordering,  $shorthand::standard> final { constexpr static std::partial_ordering  value($shorthand::value const& value) noexcept { return value.std_partial_ordering; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::strong_ordering,   $shorthand::standard> final { constexpr static std::strong_ordering   value($shorthand::value const& value) noexcept { return value.std_strong_ordering; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::weak_ordering,     $shorthand::standard> final { constexpr static std::weak_ordering     value($shorthand::value const& value) noexcept { return value.std_weak_ordering; } };
      #ifdef __cpp_lib_coroutine
        template <std::size_t subarity, typename base> struct cast<subarity, base, std::coroutine_handle<void>, $shorthand::standard> final { constexpr static std::coroutine_handle<void> value($shorthand::value const& value) noexcept { return value.std_coroutine_handle; } };
        template <std::size_t subarity, typename base> struct cast<subarity, base, std::noop_coroutine_handle,  $shorthand::standard> final { constexpr static std::noop_coroutine_handle  value($shorthand::value const& value) noexcept { return value.std_noop_coroutine_handle; } };
        template <std::size_t subarity, typename base> struct cast<subarity, base, std::noop_coroutine_promise, $shorthand::standard> final { constexpr static std::noop_coroutine_promise value($shorthand::value const& value) noexcept { return value.std_noop_coroutine_promise; } };
        template <std::size_t subarity, typename base> struct cast<subarity, base, std::suspend_always,         $shorthand::standard> final { constexpr static std::suspend_always         value($shorthand::value const& value) noexcept { return value.std_suspend_always; } };
        template <std::size_t subarity, typename base> struct cast<subarity, base, std::suspend_never,          $shorthand::standard> final { constexpr static std::suspend_never          value($shorthand::value const& value) noexcept { return value.std_suspend_never; } };
      #endif
    #endif
    #ifdef __cpp_unicode_characters
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_char16_t, $shorthand::standard> final { constexpr static std::atomic_char16_t value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_char16_t const*>(value.std_atomic_char16_t) /* --> std::launder(...) */ -> load()}; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::atomic_char32_t, $shorthand::standard> final { constexpr static std::atomic_char32_t value($shorthand::value const& value) noexcept { return {reinterpret_cast<std::atomic_char32_t const*>(value.std_atomic_char32_t) /* --> std::launder(...) */ -> load()}; } };
    #endif
    #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201402L
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::bit_and      <void>, $shorthand::standard> final { constexpr static std::bit_and      <void> value($shorthand::value const& value) noexcept { return value.std_bit_and; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::bit_not      <>,     $shorthand::standard> final { constexpr static std::bit_not      <>     value($shorthand::value const& value) noexcept { return value.std_bit_not; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::bit_or       <void>, $shorthand::standard> final { constexpr static std::bit_or       <void> value($shorthand::value const& value) noexcept { return value.std_bit_or; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::bit_xor      <void>, $shorthand::standard> final { constexpr static std::bit_xor      <void> value($shorthand::value const& value) noexcept { return value.std_bit_xor; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::divides      <void>, $shorthand::standard> final { constexpr static std::divides      <void> value($shorthand::value const& value) noexcept { return value.std_divides; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::equal_to     <void>, $shorthand::standard> final { constexpr static std::equal_to     <void> value($shorthand::value const& value) noexcept { return value.std_equal_to; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::greater      <void>, $shorthand::standard> final { constexpr static std::greater      <void> value($shorthand::value const& value) noexcept { return value.std_greater; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::greater_equal<void>, $shorthand::standard> final { constexpr static std::greater_equal<void> value($shorthand::value const& value) noexcept { return value.std_greater_equal; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::less         <void>, $shorthand::standard> final { constexpr static std::less         <void> value($shorthand::value const& value) noexcept { return value.std_less; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::less_equal   <void>, $shorthand::standard> final { constexpr static std::less_equal   <void> value($shorthand::value const& value) noexcept { return value.std_less_equal; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::logical_and  <void>, $shorthand::standard> final { constexpr static std::logical_and  <void> value($shorthand::value const& value) noexcept { return value.std_logical_and; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::logical_not  <void>, $shorthand::standard> final { constexpr static std::logical_not  <void> value($shorthand::value const& value) noexcept { return value.std_logical_not; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::logical_or   <void>, $shorthand::standard> final { constexpr static std::logical_or   <void> value($shorthand::value const& value) noexcept { return value.std_logical_or; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::minus        <void>, $shorthand::standard> final { constexpr static std::minus        <void> value($shorthand::value const& value) noexcept { return value.std_minus; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::modulus      <void>, $shorthand::standard> final { constexpr static std::modulus      <void> value($shorthand::value const& value) noexcept { return value.std_modulus; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::multiplies   <void>, $shorthand::standard> final { constexpr static std::multiplies   <void> value($shorthand::value const& value) noexcept { return value.std_multiplies; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::negate       <void>, $shorthand::standard> final { constexpr static std::negate       <void> value($shorthand::value const& value) noexcept { return value.std_negate; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::not_equal_to <void>, $shorthand::standard> final { constexpr static std::not_equal_to <void> value($shorthand::value const& value) noexcept { return value.std_not_equal_to; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::plus         <void>, $shorthand::standard> final { constexpr static std::plus         <void> value($shorthand::value const& value) noexcept { return value.std_plus; } };
    #endif
    #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 201703L
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::in_place_t, $shorthand::standard> final { constexpr static std::in_place_t value($shorthand::value const& value) noexcept { return value.std_in_place_t; } };
    #endif
    #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) >= 202002L
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::contiguous_iterator_tag, $shorthand::standard> final { constexpr static std::contiguous_iterator_tag value($shorthand::value const& value) noexcept { return value.std_contiguous_iterator_tag; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::default_sentinel_t,      $shorthand::standard> final { constexpr static std::default_sentinel_t      value($shorthand::value const& value) noexcept { return value.std_default_sentinel_t; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::destroying_delete_t,     $shorthand::standard> final { constexpr static std::destroying_delete_t     value($shorthand::value const& value) noexcept { return value.std_destroying_delete_t; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::identity,                $shorthand::standard> final { constexpr static std::identity                value($shorthand::value const& value) noexcept { return value.std_identity; } };
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::unreachable_sentinel_t,  $shorthand::standard> final { constexpr static std::unreachable_sentinel_t  value($shorthand::value const& value) noexcept { return value.std_unreachable_sentinel_t; } };
    #endif
    #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) <= 202002L // --> < 2023..L
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::pointer_safety, $shorthand::standard> final { constexpr static std::pointer_safety value($shorthand::value const& value) noexcept { return value.std_pointer_safety; } };
    #endif
    #if defined __STDCPP_BFLOAT16_T__
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::bfloat16_t, $shorthand::standard> final { constexpr static std::bfloat16_t value($shorthand::value const& value) noexcept { return value.std_bfloat16_t; } };
    #endif
    #if defined __STDCPP_FLOAT16_T__
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::float16_t, $shorthand::standard> final { constexpr static std::float16_t value($shorthand::value const& value) noexcept { return value.std_float16_t; } };
    #endif
    #if defined __STDCPP_FLOAT32_T__
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::float32_t, $shorthand::standard> final { constexpr static std::float32_t value($shorthand::value const& value) noexcept { return value.std_float32_t; } };
    #endif
    #if defined __STDCPP_FLOAT64_T__
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::float64_t, $shorthand::standard> final { constexpr static std::float64_t value($shorthand::value const& value) noexcept { return value.std_float64_t; } };
    #endif
    #if defined __STDCPP_FLOAT128_T__
      template <std::size_t subarity, typename base> struct cast<subarity, base, std::float128_t, $shorthand::standard> final { constexpr static std::float128_t value($shorthand::value const& value) noexcept { return value.std_float128_t; } };
    #endif

    template <std::size_t subarity, typename base, typename subbase>
    struct cast<subarity, base, subbase, $shorthand::decimal> final {
      constexpr static base value($shorthand::value const& value) noexcept {
        return
          value.type == $shorthand::decimal     ? static_cast<base>(value.decimal)     :
          value.type == $shorthand::enumeration ? static_cast<base>(value.enumeration) :
          value.type == $shorthand::integer     ? static_cast<base>(value.integer)     :
          #ifdef __STDCPP_BFLOAT16_T__
            value.type == $shorthand::standard::bfloat16_t ? static_cast<base>(value.std_bfloat16_t) :
          #endif
          #ifdef __STDCPP_FLOAT16_T__
            value.type == $shorthand::standard::float16_t ? static_cast<base>(value.std_float16_t) :
          #endif
          #ifdef __STDCPP_FLOAT32_T__
            value.type == $shorthand::standard::float32_t ? static_cast<base>(value.std_float32_t) :
          #endif
          #ifdef __STDCPP_FLOAT64_T__
            value.type == $shorthand::standard::float64_t ? static_cast<base>(value.std_float64_t) :
          #endif
          #ifdef __STDCPP_FLOAT128_T__
            value.type == $shorthand::standard::float128_t ? static_cast<base>(value.std_float128_t) :
          #endif
        nocast<base>::value();
      }
    };

    template <std::size_t subarity, typename base, typename subbase>
    struct cast<subarity, base, subbase, $shorthand::enumeration> final {
      constexpr static base value($shorthand::value const& value) noexcept {
        return
          value.type == $shorthand::enumeration                               ? static_cast<base>(value.enumeration)      :
          value.type == $shorthand::integer                                   ? static_cast<base>(value.integer)          :
          value.type == static_cast<type>($shorthand::standard::memory_order) ? static_cast<base>(value.std_memory_order) :
          #ifdef __cpp_aligned_new
            value.type == static_cast<type>($shorthand::standard::align_val_t) ? static_cast<base>(value.std_align_val_t) :
          #endif
          #ifdef __cpp_lib_byte
            value.type == static_cast<type>($shorthand::standard::byte) ? static_cast<base>(value.std_byte) :
          #endif
          #ifdef __cpp_lib_endian
            value.type == static_cast<type>($shorthand::standard::endian) ? static_cast<base>(value.std_endian) :
          #endif
          #ifdef __cpp_lib_ranges
            value.type == static_cast<type>($shorthand::standard::subrange_kind) ? static_cast<base>(value.std_subrange_kind) :
          #endif
          #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) <= 202002L // --> < 2023..L
            value.type == static_cast<type>($shorthand::standard::pointer_safety) ? static_cast<base>(value.std_pointer_safety) :
          #endif
        nocast<base>::value();
      }
    };

    template <std::size_t subarity, typename base, typename subbase>
    struct cast<subarity, base, subbase, $shorthand::integer> final {
      constexpr static base value($shorthand::value const& value) noexcept {
        return
          value.type == $shorthand::decimal                                     ? static_cast<base>(value.decimal)                                                                                       :
          value.type == $shorthand::enumeration                                 ? static_cast<base>(value.enumeration)                                                                                   :
          value.type == $shorthand::integer                                     ? static_cast<base>(value.integer)                                                                                       :
          value.type == static_cast<type>($shorthand::standard::atomic_bool)    ? static_cast<base>(*reinterpret_cast<std::atomic_bool    const*>(value.std_atomic_bool))    /* --> std::launder(...) */ :
          value.type == static_cast<type>($shorthand::standard::atomic_char)    ? static_cast<base>(*reinterpret_cast<std::atomic_char    const*>(value.std_atomic_char))    /* --> std::launder(...) */ :
          value.type == static_cast<type>($shorthand::standard::atomic_int)     ? static_cast<base>(*reinterpret_cast<std::atomic_int     const*>(value.std_atomic_int))     /* --> std::launder(...) */ :
          value.type == static_cast<type>($shorthand::standard::atomic_llong)   ? static_cast<base>(*reinterpret_cast<std::atomic_llong   const*>(value.std_atomic_llong))   /* --> std::launder(...) */ :
          value.type == static_cast<type>($shorthand::standard::atomic_long)    ? static_cast<base>(*reinterpret_cast<std::atomic_long    const*>(value.std_atomic_long))    /* --> std::launder(...) */ :
          value.type == static_cast<type>($shorthand::standard::atomic_schar)   ? static_cast<base>(*reinterpret_cast<std::atomic_schar   const*>(value.std_atomic_schar))   /* --> std::launder(...) */ :
          value.type == static_cast<type>($shorthand::standard::atomic_short)   ? static_cast<base>(*reinterpret_cast<std::atomic_short   const*>(value.std_atomic_short))   /* --> std::launder(...) */ :
          value.type == static_cast<type>($shorthand::standard::atomic_uchar)   ? static_cast<base>(*reinterpret_cast<std::atomic_uchar   const*>(value.std_atomic_uchar))   /* --> std::launder(...) */ :
          value.type == static_cast<type>($shorthand::standard::atomic_uint)    ? static_cast<base>(*reinterpret_cast<std::atomic_uint    const*>(value.std_atomic_uint))    /* --> std::launder(...) */ :
          value.type == static_cast<type>($shorthand::standard::atomic_ullong)  ? static_cast<base>(*reinterpret_cast<std::atomic_ullong  const*>(value.std_atomic_ullong))  /* --> std::launder(...) */ :
          value.type == static_cast<type>($shorthand::standard::atomic_ulong)   ? static_cast<base>(*reinterpret_cast<std::atomic_ulong   const*>(value.std_atomic_ulong))   /* --> std::launder(...) */ :
          value.type == static_cast<type>($shorthand::standard::atomic_ushort)  ? static_cast<base>(*reinterpret_cast<std::atomic_ushort  const*>(value.std_atomic_ushort))  /* --> std::launder(...) */ :
          value.type == static_cast<type>($shorthand::standard::atomic_wchar_t) ? static_cast<base>(*reinterpret_cast<std::atomic_wchar_t const*>(value.std_atomic_wchar_t)) /* --> std::launder(...) */ :
          value.type == static_cast<type>($shorthand::standard::memory_order)   ? static_cast<base>(value.std_memory_order)                                                                              :
          #ifdef __cpp_aligned_new
            value.type == static_cast<type>($shorthand::standard::align_val_t) ? static_cast<base>(value.std_align_val_t) :
          #endif
          #ifdef __cpp_char8_t
            value.type == static_cast<type>($shorthand::standard::atomic_char8_t) ? static_cast<base>(*reinterpret_cast<std::atomic_char8_t const*>(value.std_atomic_char8_t)) /* --> std::launder(...) */ :
          #endif
          #ifdef __cpp_lib_byte
            value.type == static_cast<type>($shorthand::standard::byte) ? static_cast<base>(value.std_byte) :
          #endif
          #ifdef __cpp_lib_endian
            value.type == static_cast<type>($shorthand::standard::endian) ? static_cast<base>(value.std_endian) :
          #endif
          #ifdef __cpp_lib_ranges
            value.type == static_cast<type>($shorthand::standard::subrange_kind) ? static_cast<base>(value.std_subrange_kind) :
          #endif
          #ifdef __cpp_unicode_characters
            value.type == static_cast<type>($shorthand::standard::atomic_char16_t) ? static_cast<base>(*reinterpret_cast<std::atomic_char16_t const*>(value.std_atomic_char16_t)) /* --> std::launder(...) */ :
            value.type == static_cast<type>($shorthand::standard::atomic_char32_t) ? static_cast<base>(*reinterpret_cast<std::atomic_char32_t const*>(value.std_atomic_char32_t)) /* --> std::launder(...) */ :
          #endif
          #if (defined _MSVC_LANG ? _MSVC_LANG : __cplusplus) <= 202002L // --> < 2023..L
            value.type == static_cast<type>($shorthand::standard::pointer_safety) ? static_cast<base>(value.std_pointer_safety) :
          #endif
          #ifdef __STDCPP_BFLOAT16_T__
            value.type == $shorthand::standard::bfloat16_t ? static_cast<base>(value.std_bfloat16_t) :
          #endif
          #ifdef __STDCPP_FLOAT16_T__
            value.type == $shorthand::standard::float16_t ? static_cast<base>(value.std_float16_t) :
          #endif
          #ifdef __STDCPP_FLOAT32_T__
            value.type == $shorthand::standard::float32_t ? static_cast<base>(value.std_float32_t) :
          #endif
          #ifdef __STDCPP_FLOAT64_T__
            value.type == $shorthand::standard::float64_t ? static_cast<base>(value.std_float64_t) :
          #endif
          #ifdef __STDCPP_FLOAT128_T__
            value.type == $shorthand::standard::float128_t ? static_cast<base>(value.std_float128_t) :
          #endif
        nocast<base>::value();
      }
    };

    template <std::size_t subarity, typename base, typename subbase> struct cast<subarity, base, subbase, $shorthand::function>  final { constexpr static base value($shorthand::value const& value) noexcept { return value.type == $shorthand::function ? (base) *value.function : value.type == static_cast<type>($shorthand::standard::new_terminate_unexpected_handler) and is_same<subbase, typename remove_qualifiers<std::new_handler>::type>::value ? static_cast<base>(value.std_new_terminate_unexpected_handler) : nocast<base>::value(); } };
    template <std::size_t subarity, typename base, typename subbase> struct cast<subarity, base, subbase, $shorthand::member>    final { constexpr static base value($shorthand::value const& value) noexcept { return value.type == $shorthand::member ? (base) value.member : value.type == static_cast<type>($shorthand::standard::nullptr_t) ? static_cast<base>(NULL) : nocast<base>::value(); } };
    template <std::size_t subarity, typename base, typename subbase> struct cast<subarity, base, subbase, $shorthand::null>      final { constexpr static base value($shorthand::value const& value) noexcept { static_assert(0u == sizeof(base), "Can not convert shorthand"); return value.type == $shorthand::null ? (base) value.null : nocast<base>::value(); } };
    template <std::size_t subarity, typename base, typename subbase> struct cast<subarity, base, subbase, $shorthand::pointer>   final { constexpr static base value($shorthand::value const& value) noexcept { return value.type == $shorthand::pointer ? static_cast<base>(value.pointer) : value.type == static_cast<type>($shorthand::standard::nullptr_t) ? static_cast<base>(NULL) : value.type == static_cast<type>($shorthand::standard::va_list) and is_same<typename remove_cv<typename remove_pointer<subbase>::type>::type, std::va_list>::value ? (base) value.std_va_list : nocast<base>::value(); } };
    template <std::size_t subarity, typename base, typename subbase> struct cast<subarity, base, subbase, $shorthand::reference> final { constexpr static base value($shorthand::value const& value) noexcept { return value.type == $shorthand::reference ? *reinterpret_cast<typename remove_reference<base>::type*>(value.reference) /* --> std::launder(...) */ : nocast<base>::value(); } };
    template <std::size_t subarity, typename base, typename subbase> struct cast<subarity, base, subbase, $shorthand::shorthand> final { constexpr static base value($shorthand::value const&)       noexcept { static_assert(0u == sizeof(base), "Can not convert shorthand"); return nocast<base>::value(); } };
    template <std::size_t subarity, typename base, typename subbase> struct cast<subarity, base, subbase, $shorthand::undefined> final { constexpr static base value($shorthand::value const& value) noexcept { return NULL != value.metadata and value.metadata -> hash_code() == typeid(base).hash_code() and value.type == $shorthand::undefined ? *static_cast<base*>(value.undefined.address) : nocast<base>::value(); } };

    template <std::size_t subarity, typename base, $$ substate, bool $$$c>
    struct cast<subarity, base, $n<0u, substate, $$$c, true>, $shorthand::shorthand> final {
      constexpr static base value($shorthand::value const&) noexcept {
        return {};
      }
    };

    template <std::size_t subarityA, typename base, std::size_t subarityB, $$ substate, bool $$$c>
    struct cast<subarityA, base, $n<subarityB, substate, $$$c, true>, $shorthand::shorthand> final {
      constexpr static base value($shorthand::value const& value) noexcept {
        return {value};
      }
    };

    /* ... */
    $shorthand::value const value;

    // ...
    constexpr $n($shorthand::value const& value) noexcept(noexcept($shorthand::value(instanceof<$shorthand::value const&>()))) :
      value(value)
    {}

  public:
    template <typename... types>
    constexpr $n(types&&... arguments) noexcept(noexcept($shorthand::value(
      instanceof<bool const (*)[valueof<typename at<(arity > sizeof...(types) ? 0u : arity), void, types&&...>::type>::value][arity]>(),
      instanceof<typename at<(arity > sizeof...(types) ? 0u : arity), sfinaeptr_t, types&&...>::type>()
    ))) : value(
      static_cast<bool const (*)[valueof<typename at<(arity > sizeof...(types) ? 0u : arity), void, types&&...>::type>::value][arity]>(NULL),
      at<(arity > sizeof...(types) ? 0u : arity)>::value(sfinaeptr, forward_cast<types>(arguments)...)
    ) {}

    // ...
    template <typename type>
    constexpr operator type() const volatile noexcept {
      static_assert(arity, "Can not convert shorthand");
      return static_cast<type>(cast<arity, type>::value(const_cast<$shorthand::value const&>(this -> value)));
    }
};

template <std::size_t arity, $$ state>
struct $n<arity, state, false /* --> $$c */, true /* --> $$o */> : public $n<arity, state, true, true>, public $shorthand {
  template <std::size_t, $$, bool, bool>
  friend struct $n;

  // ...
  template <typename... types>
  inline $n(types&&... arguments) noexcept :
    $n<arity, state, true, true>::$n(forward_cast<types&&>(arguments)...)
  {}

  inline ~$n() noexcept {
    $n<arity, state, true, true> *const shorthand = this;

    // ...
    switch (static_cast<unsigned char>(shorthand -> value.type)) {
      case $shorthand::standard::atomic_bool         : (void) shorthand -> value.std_atomic_bool;                                                                                                                                    break;
      case $shorthand::standard::atomic_char         : (void) shorthand -> value.std_atomic_char;                                                                                                                                    break;
      case $shorthand::standard::atomic_int          : (void) shorthand -> value.std_atomic_int;                                                                                                                                     break;
      case $shorthand::standard::atomic_llong        : (void) shorthand -> value.std_atomic_llong;                                                                                                                                   break;
      case $shorthand::standard::atomic_long         : (void) shorthand -> value.std_atomic_long;                                                                                                                                    break;
      case $shorthand::standard::atomic_schar        : (void) shorthand -> value.std_atomic_schar;                                                                                                                                   break;
      case $shorthand::standard::atomic_short        : (void) shorthand -> value.std_atomic_short;                                                                                                                                   break;
      case $shorthand::standard::atomic_uchar        : (void) shorthand -> value.std_atomic_uchar;                                                                                                                                   break;
      case $shorthand::standard::atomic_uint         : (void) shorthand -> value.std_atomic_uint;                                                                                                                                    break;
      case $shorthand::standard::atomic_ullong       : (void) shorthand -> value.std_atomic_ullong;                                                                                                                                  break;
      case $shorthand::standard::atomic_ulong        : (void) shorthand -> value.std_atomic_ulong;                                                                                                                                   break;
      case $shorthand::standard::atomic_ushort       : (void) shorthand -> value.std_atomic_ushort;                                                                                                                                  break;
      case $shorthand::standard::atomic_wchar_t      : (void) shorthand -> value.std_atomic_wchar_t;                                                                                                                                 break;
      case $shorthand::standard::bad_alloc           : reinterpret_cast<std::bad_alloc*>           (const_cast<unsigned char*>(shorthand -> value.std_bad_alloc))            /* --> std::launder(...) */ -> ~bad_alloc           (); break;
      case $shorthand::standard::bad_array_new_length: reinterpret_cast<std::bad_array_new_length*>(const_cast<unsigned char*>(shorthand -> value.std_bad_array_new_length)) /* --> std::launder(...) */ -> ~bad_array_new_length(); break;
      case $shorthand::standard::bad_exception       : reinterpret_cast<std::bad_exception*>       (const_cast<unsigned char*>(shorthand -> value.std_bad_exception))        /* --> std::launder(...) */ -> ~bad_exception       (); break;
      case $shorthand::standard::bad_function_call   : reinterpret_cast<std::bad_function_call*>   (const_cast<unsigned char*>(shorthand -> value.std_bad_function_call))    /* --> std::launder(...) */ -> ~bad_function_call   (); break;
      case $shorthand::standard::bad_typeid          : reinterpret_cast<std::bad_typeid*>          (const_cast<unsigned char*>(shorthand -> value.std_bad_typeid))           /* --> std::launder(...) */ -> ~bad_typeid          (); break;
      case $shorthand::standard::bad_weak_ptr        : reinterpret_cast<std::bad_weak_ptr*>        (const_cast<unsigned char*>(shorthand -> value.std_bad_weak_ptr))         /* --> std::launder(...) */ -> ~bad_weak_ptr        (); break;
      case $shorthand::standard::exception           : reinterpret_cast<std::exception*>           (const_cast<unsigned char*>(shorthand -> value.std_exception))            /* --> std::launder(...) */ -> ~exception           (); break;
      case $shorthand::standard::exception_ptr       : reinterpret_cast<std::exception_ptr*>       (const_cast<unsigned char*>(shorthand -> value.std_exception_ptr))        /* --> std::launder(...) */ -> ~exception_ptr       (); break;
      case $shorthand::standard::nested_exception    : reinterpret_cast<std::nested_exception*>    (const_cast<unsigned char*>(shorthand -> value.std_nested_exception))     /* --> std::launder(...) */ -> ~nested_exception    (); break;
      #ifdef __cpp_char8_t
        case $shorthand::standard::atomic_char8_t: (void) shorthand -> value.std_atomic_char8_t; break;
      #endif
      #ifdef __cpp_unicode_characters
        case $shorthand::standard::atomic_char16_t: (void) shorthand -> value.std_atomic_char16_t; break;
        case $shorthand::standard::atomic_char32_t: (void) shorthand -> value.std_atomic_char32_t; break;
      #endif
      case $shorthand::undefined: (void) shorthand -> value.undefined; break;
    }
  }
};

// ...
template <class shorthandA, class shorthandB>
struct $lambda<$op::add, shorthandA, shorthandB> final {
  private: $shorthand::members<shorthandA, shorthandB> operands;
  public:
    constexpr $lambda(shorthandA const& operandA, shorthandB const& operandB) noexcept(noexcept($shorthand::members<shorthandA, shorthandB>(operandA, operandB))) : operands(operandA, operandB) {}
};

  template <typename type, $op::$$ operation, class... shorthands> constexpr $lambda<$op::add, $lambda<operation, shorthands...>, typename conditional<not $shorthand::template is_shorthand<type>::value, typename conditional<$shorthand::template is<$c, type>::value, $n<1u, $co>, $n<1u, $o> >::type, typename remove_qualifiers<type>::type>::type> operator +($lambda<operation, shorthands...> const& shorthand, type&& value) noexcept { return {shorthand, forward_cast<type>(value)}; }
  template <typename type, $op::$$ operation, class... shorthands> constexpr $lambda<$op::add, typename conditional<not $shorthand::template is_shorthand<type>::value, typename conditional<$shorthand::template is<$c, type>::value, $n<1u, $co>, $n<1u, $o> >::type>::type, $lambda<operation, shorthands...> >                                        operator +(type&& value, $lambda<operation, shorthands...> const& shorthand) noexcept { return {forward_cast<type>(value), shorthand}; }

  template <typename type, std::size_t index, $$ state, bool... states> constexpr $lambda<$op::add, $n<index, state, states...>, typename conditional<not $shorthand::template is_shorthand<type>::value, typename conditional<$shorthand::template is<$c, type>::value, $n<1u, $co>, $n<1u, $o> >::type, typename remove_qualifiers<type>::type>::type> operator +($n<index, state, states...> const& shorthand, type&& value) noexcept { return {shorthand, forward_cast<type>(value)}; }
  template <typename type, std::size_t index, $$ state, bool... states> constexpr $lambda<$op::add, typename conditional<not $shorthand::template is_shorthand<type>::value, typename conditional<$shorthand::template is<$c, type>::value, $n<1u, $co>, $n<1u, $o> >::type>::type, $n<index, state, states...> >                                        operator +(type&& value, $n<index, state, states...> const& shorthand) noexcept { return {forward_cast<type>(value), shorthand}; }

/* Constant */
constexpr static $n<0u, $c> $0 = {};
constexpr static $n<1u, $c> $1 = {};
constexpr static $n<2u, $c> $2 = {};
constexpr static $n<3u, $c> $3 = {};
constexpr static $n<4u, $c> $4 = {};
constexpr static $n<5u, $c> $5 = {};
constexpr static $n<6u, $c> $6 = {};
constexpr static $n<7u, $c> $7 = {};
constexpr static $n<8u, $c> $8 = {};
constexpr static $n<9u, $c> $9 = {};

constexpr static $lambda<$op::add, $n<1u, $c>, $n<2u, $c> > $add  = $1 + $2;
constexpr static $n<1u, $c>                                 $self = $1;
// --> $bitwise_and
// --> $bitwise_or
// --> $bitwise_xor
// --> $boolean_and
// --> $boolean_or
// --> $complement
// --> $divide
// --> $equals
// --> $equals_greater
// --> $equals_lesser
// --> $greater
// --> $lesser
// --> $minus
// --> $modulo
// --> $multiply
// --> $negate
// --> $subtract
// --> $unequals

/* Main */
int main(int, char*[]) /* noexcept */ {
  constexpr decltype($add) add      = {$add};
  constexpr auto           more_add = add + $3;

  (void) add;
  (void) more_add;
  // del shorthand.exe & cls && clang++ -pedantic-errors -std=c++11 -Wall -Werror -Wextra -Wno-dollar-in-identifier-extension -Wno-inaccessible-base -Wno-unused-const-variable shorthand.cpp -o shorthand.exe && shorthand.exe & del shorthand.exe
  // del shorthand.exe & cls && g++ -pedantic-errors -std=c++11 -Wall -Werror -Wextra -Wno-ignored-attributes -Wno-inaccessible-base -Wno-unused-const-variable shorthand.cpp -o shorthand.exe && shorthand.exe & del shorthand.exe
  // del shorthand.exe shorthand.obj & cls && cl /std:c++14 /W4 /wd4584 shorthand.cpp && shorthand.exe & del shorthand.exe shorthand.obj
  // del shorthand.exe shorthand.obj & cls && icl -std=c++11 -Wall -Werror -w3 -wd2415,3280,4131 shorthand.cpp -o shorthand.exe && shorthand.exe & del shorthand.exe shorthand.obj
  // rm ./shorthand & clear && circle shorthand.cpp --pedantic -std=c++11 -Wall -Werror -Wextra && ./shorthand || rm ./shorthand
}
