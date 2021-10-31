#include <cstddef>
#include <cstdio>
#include <type_traits>
#include <utility>
#if __cplusplus >= 202002L
# include <compare>
#endif

/* ... */
namespace {
  template <typename base>
  struct property_accessor {
    constexpr inline static base& get(base& value) noexcept { return value; }
  };

  template <typename base>
  struct property_mutator {
    template <typename type> constexpr inline static auto set            (base& value, type&& argument) noexcept(noexcept(value =   std::forward<type>(argument))) -> decltype(value =   std::forward<type>(argument)) { return value =   std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_add        (base& value, type&& argument) noexcept(noexcept(value +=  std::forward<type>(argument))) -> decltype(value +=  std::forward<type>(argument)) { return value +=  std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_bitwise_and(base& value, type&& argument) noexcept(noexcept(value &=  std::forward<type>(argument))) -> decltype(value &=  std::forward<type>(argument)) { return value &=  std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_bitwise_or (base& value, type&& argument) noexcept(noexcept(value |=  std::forward<type>(argument))) -> decltype(value |=  std::forward<type>(argument)) { return value |=  std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_bitwise_xor(base& value, type&& argument) noexcept(noexcept(value ^=  std::forward<type>(argument))) -> decltype(value ^=  std::forward<type>(argument)) { return value ^=  std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_divide     (base& value, type&& argument) noexcept(noexcept(value /=  std::forward<type>(argument))) -> decltype(value /=  std::forward<type>(argument)) { return value /=  std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_modulo     (base& value, type&& argument) noexcept(noexcept(value %=  std::forward<type>(argument))) -> decltype(value %=  std::forward<type>(argument)) { return value %=  std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_multiply   (base& value, type&& argument) noexcept(noexcept(value *=  std::forward<type>(argument))) -> decltype(value *=  std::forward<type>(argument)) { return value *=  std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_shift_left (base& value, type&& argument) noexcept(noexcept(value <<= std::forward<type>(argument))) -> decltype(value <<= std::forward<type>(argument)) { return value <<= std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_shift_right(base& value, type&& argument) noexcept(noexcept(value >>= std::forward<type>(argument))) -> decltype(value >>= std::forward<type>(argument)) { return value >>= std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_subtract   (base& value, type&& argument) noexcept(noexcept(value -=  std::forward<type>(argument))) -> decltype(value -=  std::forward<type>(argument)) { return value -=  std::forward<type>(argument); }
  };

  struct property_void final {
    constexpr property_void(...) noexcept {}
  };

  // ...
  namespace detect {
    namespace {
      struct property_mutator_set_add_lookup         { unsigned char const set_add;         };
      struct property_mutator_set_bitwise_and_lookup { unsigned char const set_bitwise_and; };
      struct property_mutator_set_bitwise_or_lookup  { unsigned char const set_bitwise_or;  };
      struct property_mutator_set_bitwise_xor_lookup { unsigned char const set_bitwise_xor; };
      struct property_mutator_set_divide_lookup      { unsigned char const set_divide;      };
      struct property_mutator_set_modulo_lookup      { unsigned char const set_modulo;      };
      struct property_mutator_set_multiply_lookup    { unsigned char const set_multiply;    };
      struct property_mutator_set_shift_left_lookup  { unsigned char const set_shift_left;  };
      struct property_mutator_set_shift_right_lookup { unsigned char const set_shift_right; };
      struct property_mutator_set_subtract_lookup    { unsigned char const set_subtract;    };
    }

    namespace {
      template <class object>
      union is_derivable {
        enum { value = false == (
          std::is_union<object>::value ||
          #if __cplusplus >= 201402L
            std::is_final<object>::value
          #elif (defined(__clang__) || defined(__clang_major__) || defined(__clang_minor__) || defined(__clang_patchlevel__))
            __is_final(object)
          #elif (defined(__GNUC__) || defined(__GNUG__) || defined(__GNUC_MINOR__) || defined(__GNUC_PATCHLEVEL__)) && defined(__is_final)
            __is_final(object)
          #elif (defined(_MSC_VER))
            __is_sealed(object)
          #else
            false
          #endif
        ) };
      };

      template <class object, class... lookups>
      struct member_name_lookup : public object, public lookups... {};
    }

    // ...
    template <typename, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union add_operator { enum { value = false }; };
    template <typename base, typename type> union add_operator<base, type, typename std::integral_constant<std::size_t, sizeof(std::declval<base>() += std::declval<type>())>::value_type> { enum { value = true }; };

    template <typename, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union bitwise_and_operator { enum { value = false }; };
    template <typename base, typename type> union bitwise_and_operator<base, type, typename std::integral_constant<std::size_t, sizeof(std::declval<base>() &= std::declval<type>())>::value_type> { enum { value = true }; };

    template <typename, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union bitwise_or_operator { enum { value = false }; };
    template <typename base, typename type> union bitwise_or_operator<base, type, typename std::integral_constant<std::size_t, sizeof(std::declval<base>() |= std::declval<type>())>::value_type> { enum { value = true }; };

    template <typename, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union bitwise_xor_operator { enum { value = false }; };
    template <typename base, typename type> union bitwise_xor_operator<base, type, typename std::integral_constant<std::size_t, sizeof(std::declval<base>() ^= std::declval<type>())>::value_type> { enum { value = true }; };

    template <typename, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union divide_operator { enum { value = false }; };
    template <typename base, typename type> union divide_operator<base, type, typename std::integral_constant<std::size_t, sizeof(std::declval<base>() /= std::declval<type>())>::value_type> { enum { value = true }; };

    template <class, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union member_access_pointer_operator { enum { value = false }; };
    template <class object> union member_access_pointer_operator<object, typename std::integral_constant<std::size_t, sizeof(std::declval<object>().operator ->(), false)>::value_type> { enum { value = true }; };

    template <typename, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union modulo_operator { enum { value = false }; };
    template <typename base, typename type> union modulo_operator<base, type, typename std::integral_constant<std::size_t, sizeof(std::declval<base>() %= std::declval<type>())>::value_type> { enum { value = true }; };

    template <typename, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union multiply_operator { enum { value = false }; };
    template <typename base, typename type> union multiply_operator<base, type, typename std::integral_constant<std::size_t, sizeof(std::declval<base>() *= std::declval<type>())>::value_type> { enum { value = true }; };

    template <typename, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union shift_left_operator { enum { value = false }; };
    template <typename base, typename type> union shift_left_operator<base, type, typename std::integral_constant<std::size_t, sizeof(std::declval<base>() <<= std::declval<type>())>::value_type> { enum { value = true }; };

    template <typename, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union shift_right_operator { enum { value = false }; };
    template <typename base, typename type> union shift_right_operator<base, type, typename std::integral_constant<std::size_t, sizeof(std::declval<base>() >>= std::declval<type>())>::value_type> { enum { value = true }; };

    template <typename, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union subtract_operator { enum { value = false }; };
    template <typename base, typename type> union subtract_operator<base, type, typename std::integral_constant<std::size_t, sizeof(std::declval<base>() -= std::declval<type>())>::value_type> { enum { value = true }; };

    // ...
    template <class mutator, typename type>
    union mutator_set_copy {
      private:
        template <class submutator> constexpr static typename std::enable_if<std::is_same<decltype(submutator::set(std::declval<type>(), std::declval<type>())), decltype(submutator::set(std::declval<type>(), std::declval<type>()))>::value, bool>::type resolve() noexcept { return true; }

        template <class, typename = bool> union assert { enum { value = false }; };
        template <class submutator> union assert<submutator, decltype(resolve<submutator>())> { enum { value = true }; };

      public:
        enum { value = assert<mutator>::value };
    };

    template <class mutator, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = is_derivable<mutator>::value> union mutator_set_add { enum { value = false == derivable }; };
    template <class mutator> union mutator_set_add<mutator, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<mutator, property_mutator_set_add_lookup>::set_add)>::value_type, false> { enum { value = false }; };
    template <class mutator> union mutator_set_add<mutator, decltype(sizeof(&mutator::set_add)), true> { enum { value = true }; };

    template <class mutator, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = is_derivable<mutator>::value> union mutator_set_bitwise_and { enum { value = false == derivable }; };
    template <class mutator> union mutator_set_bitwise_and<mutator, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<mutator, property_mutator_set_bitwise_and_lookup>::set_bitwise_and)>::value_type, false> { enum { value = false }; };
    template <class mutator> union mutator_set_bitwise_and<mutator, decltype(sizeof(&mutator::set_bitwise_and)), true> { enum { value = true }; };

    template <class mutator, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = is_derivable<mutator>::value> union mutator_set_bitwise_or { enum { value = false == derivable }; };
    template <class mutator> union mutator_set_bitwise_or<mutator, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<mutator, property_mutator_set_bitwise_or_lookup>::set_bitwise_or)>::value_type, false> { enum { value = false }; };
    template <class mutator> union mutator_set_bitwise_or<mutator, decltype(sizeof(&mutator::set_bitwise_or)), true> { enum { value = true }; };

    template <class mutator, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = is_derivable<mutator>::value> union mutator_set_bitwise_xor { enum { value = false == derivable }; };
    template <class mutator> union mutator_set_bitwise_xor<mutator, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<mutator, property_mutator_set_bitwise_xor_lookup>::set_bitwise_xor)>::value_type, false> { enum { value = false }; };
    template <class mutator> union mutator_set_bitwise_xor<mutator, decltype(sizeof(&mutator::set_bitwise_xor)), true> { enum { value = true }; };

    template <class mutator, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = is_derivable<mutator>::value> union mutator_set_divide { enum { value = false == derivable }; };
    template <class mutator> union mutator_set_divide<mutator, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<mutator, property_mutator_set_divide_lookup>::set_divide)>::value_type, false> { enum { value = false }; };
    template <class mutator> union mutator_set_divide<mutator, decltype(sizeof(&mutator::set_divide)), true> { enum { value = true }; };

    template <class mutator, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = is_derivable<mutator>::value> union mutator_set_modulo { enum { value = false == derivable }; };
    template <class mutator> union mutator_set_modulo<mutator, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<mutator, property_mutator_set_modulo_lookup>::set_modulo)>::value_type, false> { enum { value = false }; };
    template <class mutator> union mutator_set_modulo<mutator, decltype(sizeof(&mutator::set_modulo)), true> { enum { value = true }; };

    template <class mutator, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = is_derivable<mutator>::value> union mutator_set_multiply { enum { value = false == derivable }; };
    template <class mutator> union mutator_set_multiply<mutator, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<mutator, property_mutator_set_multiply_lookup>::set_multiply)>::value_type, false> { enum { value = false }; };
    template <class mutator> union mutator_set_multiply<mutator, decltype(sizeof(&mutator::set_multiply)), true> { enum { value = true }; };

    template <class mutator, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = is_derivable<mutator>::value> union mutator_set_shift_left { enum { value = false == derivable }; };
    template <class mutator> union mutator_set_shift_left<mutator, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<mutator, property_mutator_set_shift_left_lookup>::set_shift_left)>::value_type, false> { enum { value = false }; };
    template <class mutator> union mutator_set_shift_left<mutator, decltype(sizeof(&mutator::set_shift_left)), true> { enum { value = true }; };

    template <class mutator, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = is_derivable<mutator>::value> union mutator_set_shift_right { enum { value = false == derivable }; };
    template <class mutator> union mutator_set_shift_right<mutator, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<mutator, property_mutator_set_shift_right_lookup>::set_shift_right)>::value_type, false> { enum { value = false }; };
    template <class mutator> union mutator_set_shift_right<mutator, decltype(sizeof(&mutator::set_shift_right)), true> { enum { value = true }; };

    template <class mutator, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = is_derivable<mutator>::value> union mutator_set_subtract { enum { value = false == derivable }; };
    template <class mutator> union mutator_set_subtract<mutator, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<mutator, property_mutator_set_subtract_lookup>::set_subtract)>::value_type, false> { enum { value = false }; };
    template <class mutator> union mutator_set_subtract<mutator, decltype(sizeof(&mutator::set_subtract)), true> { enum { value = true }; };
  }

  namespace request {
    template <class mutator, typename base, bool = detect::mutator_set_copy<mutator, base>::value> union mutator_set_copy;
    template <class mutator, typename base> union mutator_set_copy<mutator, base, false> { constexpr inline static property_void value(base&      , base&         ) noexcept; };
    template <class mutator, typename base> union mutator_set_copy<mutator, base, true>  { constexpr inline static auto          value(base& value, base& argument) noexcept(noexcept(mutator::set(value, argument))) -> decltype(mutator::set(value, argument)) { return mutator::set(value, argument); } };

    template <class mutator, bool = detect::mutator_set_add<mutator>::value>         union mutator_set_add;
    template <class mutator> union mutator_set_add<mutator, false>         { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value + std::forward<type>(argument)))) -> decltype(mutator::set(value, value + std::forward<type>(argument))) { return mutator::set(value, value + std::forward<type>(argument)); } };
    template <class mutator> union mutator_set_add<mutator, true>          { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_add(value, std::forward<type>(argument)))) -> decltype(mutator::set_add(value, std::forward<type>(argument))) { return mutator::set_add(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_bitwise_and<mutator>::value> union mutator_set_bitwise_and;
    template <class mutator> union mutator_set_bitwise_and<mutator, false> { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value & std::forward<type>(argument)))) -> decltype(mutator::set(value, value & std::forward<type>(argument))) { return mutator::set(value, value & std::forward<type>(argument)); } };
    template <class mutator> union mutator_set_bitwise_and<mutator, true>  { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_bitwise_and(value, std::forward<type>(argument)))) -> decltype(mutator::set_bitwise_and(value, std::forward<type>(argument))) { return mutator::set_bitwise_and(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_bitwise_or<mutator>::value>  union mutator_set_bitwise_or;
    template <class mutator> union mutator_set_bitwise_or<mutator, false>  { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value | std::forward<type>(argument)))) -> decltype(mutator::set(value, value | std::forward<type>(argument))) { return mutator::set(value, value | std::forward<type>(argument)); } };
    template <class mutator> union mutator_set_bitwise_or<mutator, true>   { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_bitwise_or(value, std::forward<type>(argument)))) -> decltype(mutator::set_bitwise_or(value, std::forward<type>(argument))) { return mutator::set_bitwise_or(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_bitwise_xor<mutator>::value> union mutator_set_bitwise_xor;
    template <class mutator> union mutator_set_bitwise_xor<mutator, false> { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value ^ std::forward<type>(argument)))) -> decltype(mutator::set(value, value ^ std::forward<type>(argument))) { return mutator::set(value, value ^ std::forward<type>(argument)); } };
    template <class mutator> union mutator_set_bitwise_xor<mutator, true>  { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_bitwise_xor(value, std::forward<type>(argument)))) -> decltype(mutator::set_bitwise_xor(value, std::forward<type>(argument))) { return mutator::set_bitwise_xor(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_divide<mutator>::value>      union mutator_set_divide;
    template <class mutator> union mutator_set_divide<mutator, false>      { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value / std::forward<type>(argument)))) -> decltype(mutator::set(value, value / std::forward<type>(argument))) { return mutator::set(value, value / std::forward<type>(argument)); } };
    template <class mutator> union mutator_set_divide<mutator, true>       { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_divide(value, std::forward<type>(argument)))) -> decltype(mutator::set_divide(value, std::forward<type>(argument))) { return mutator::set_divide(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_modulo<mutator>::value>      union mutator_set_modulo;
    template <class mutator> union mutator_set_modulo<mutator, false>      { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value % std::forward<type>(argument)))) -> decltype(mutator::set(value, value % std::forward<type>(argument))) { return mutator::set(value, value % std::forward<type>(argument)); } };
    template <class mutator> union mutator_set_modulo<mutator, true>       { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_modulo(value, std::forward<type>(argument)))) -> decltype(mutator::set_modulo(value, std::forward<type>(argument))) { return mutator::set_modulo(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_multiply<mutator>::value>    union mutator_set_multiply;
    template <class mutator> union mutator_set_multiply<mutator, false>    { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value * std::forward<type>(argument)))) -> decltype(mutator::set(value, value * std::forward<type>(argument))) { return mutator::set(value, value * std::forward<type>(argument)); } };
    template <class mutator> union mutator_set_multiply<mutator, true>     { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_multiply(value, std::forward<type>(argument)))) -> decltype(mutator::set_multiply(value, std::forward<type>(argument))) { return mutator::set_multiply(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_shift_left<mutator>::value>  union mutator_set_shift_left;
    template <class mutator> union mutator_set_shift_left<mutator, false>  { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value << std::forward<type>(argument)))) -> decltype(mutator::set(value, value << std::forward<type>(argument))) { return mutator::set(value, value << std::forward<type>(argument)); } };
    template <class mutator> union mutator_set_shift_left<mutator, true>   { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_shift_left(value, std::forward<type>(argument)))) -> decltype(mutator::set_shift_left(value, std::forward<type>(argument))) { return mutator::set_shift_left(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_shift_right<mutator>::value> union mutator_set_shift_right;
    template <class mutator> union mutator_set_shift_right<mutator, false> { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value >> std::forward<type>(argument)))) -> decltype(mutator::set(value, value >> std::forward<type>(argument))) { return mutator::set(value, value >> std::forward<type>(argument)); } };
    template <class mutator> union mutator_set_shift_right<mutator, true>  { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_shift_right(value, std::forward<type>(argument)))) -> decltype(mutator::set_shift_right(value, std::forward<type>(argument))) { return mutator::set_shift_right(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_subtract<mutator>::value>    union mutator_set_subtract;
    template <class mutator> union mutator_set_subtract<mutator, false>    { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value - std::forward<type>(argument)))) -> decltype(mutator::set(value, value - std::forward<type>(argument))) { return mutator::set(value, value - std::forward<type>(argument)); } };
    template <class mutator> union mutator_set_subtract<mutator, true>     { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_subtract(value, std::forward<type>(argument)))) -> decltype(mutator::set_subtract(value, std::forward<type>(argument))) { return mutator::set_subtract(value, std::forward<type>(argument)); } };
  }
}

// ...
template <typename base, class accessor_type = void, class mutator_type = void>
struct property final {
  template <typename, class, class>
  friend struct property;

  private:
    base value;

    // ...
    typedef typename std::conditional<std::is_same<void, typename std::remove_cv<accessor_type>::type>::value, property_accessor<base>, accessor_type>::type accessor;
    typedef typename std::conditional<std::is_same<void, typename std::remove_cv<mutator_type >::type>::value, property_mutator <base>, mutator_type >::type mutator;

    constexpr inline base& evaluate() const noexcept {
      return const_cast<base&>(this->value);
    }

  public:
    constexpr inline property(property<base> const& property) noexcept(noexcept(base(property.evaluate()))) :
      value{property.evaluate()}
    {}

    constexpr inline property(property<base>&& property) noexcept(noexcept(base(property.evaluate()))) :
      value{property.evaluate()}
    {}

    template <typename... types>
    constexpr explicit inline property(types&&... arguments) noexcept(noexcept(base(std::forward<types>(arguments)...))) :
      value{std::forward<types>(arguments)...}
    {}

    // ...
    constexpr inline base& operator ->() const noexcept(std::is_class<typename std::remove_pointer<base>::type>::value || detect::member_access_pointer_operator<base>::value) { return accessor::get(this->evaluate()); }
    constexpr inline auto operator =(property<base> const& property) const noexcept(noexcept(mutator::set(this->evaluate(), property.evaluate()))) -> decltype(request::mutator_set_copy<mutator, base>::value(this->evaluate(), property.evaluate())) { return mutator::set(this->evaluate(), property.evaluate()); }
    constexpr inline auto operator =(property<base>&& property) const noexcept(noexcept(mutator::set(this->evaluate(), property.evaluate()))) -> decltype(request::mutator_set_copy<mutator, base>::value(this->evaluate(), property.evaluate())) { return mutator::set(this->evaluate(), property.evaluate()); }
    template <typename type> constexpr inline auto operator =(type&& argument) const noexcept(noexcept(mutator::set(this->evaluate(), std::forward<type>(argument)))) -> decltype(mutator::set(this->evaluate(), std::forward<type>(argument))) { return mutator::set(this->evaluate(), std::forward<type>(argument)); }
    template <typename type> constexpr inline auto operator [](type&& argument) const noexcept(noexcept(accessor::get(this->evaluate())[std::forward<type>(argument)])) -> decltype(accessor::get(this->evaluate())[std::forward<type>(argument)]) { return accessor::get(this->evaluate())[std::forward<type>(argument)]; }

    template <typename subbase, class subaccessor, class submutator> constexpr friend inline auto operator &(property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(&accessor::get(property.evaluate()))) -> decltype(&accessor::get(property.evaluate())) { return &accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator ->*(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) ->* argument)) -> decltype(accessor::get(property.evaluate()) ->* argument) { return accessor::get(property.evaluate()) ->* argument; }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator +(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) + argument)) -> decltype(accessor::get(property.evaluate()) + argument) { return accessor::get(property.evaluate()) + argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator +(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument + accessor::get(property.evaluate()))) -> decltype(argument + accessor::get(property.evaluate())) { return argument + accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator -(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) - argument)) -> decltype(accessor::get(property.evaluate()) - argument) { return accessor::get(property.evaluate()) - argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator -(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument - accessor::get(property.evaluate()))) -> decltype(argument - accessor::get(property.evaluate())) { return argument - accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator *(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) * argument)) -> decltype(accessor::get(property.evaluate()) * argument) { return accessor::get(property.evaluate()) * argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator *(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument * accessor::get(property.evaluate()))) -> decltype(argument * accessor::get(property.evaluate())) { return argument * accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator /(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) / argument)) -> decltype(accessor::get(property.evaluate()) / argument) { return accessor::get(property.evaluate()) / argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator /(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument / accessor::get(property.evaluate()))) -> decltype(argument / accessor::get(property.evaluate())) { return argument / accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator %(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) % argument)) -> decltype(accessor::get(property.evaluate()) % argument) { return accessor::get(property.evaluate()) % argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator %(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument % accessor::get(property.evaluate()))) -> decltype(argument % accessor::get(property.evaluate())) { return argument % accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator &(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) & argument)) -> decltype(accessor::get(property.evaluate()) & argument) { return accessor::get(property.evaluate()) & argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator &(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument & accessor::get(property.evaluate()))) -> decltype(argument & accessor::get(property.evaluate())) { return argument & accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator |(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) | argument)) -> decltype(accessor::get(property.evaluate()) | argument) { return accessor::get(property.evaluate()) | argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator |(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument | accessor::get(property.evaluate()))) -> decltype(argument | accessor::get(property.evaluate())) { return argument | accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator ^(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) ^ argument)) -> decltype(accessor::get(property.evaluate()) ^ argument) { return accessor::get(property.evaluate()) ^ argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator ^(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument ^ accessor::get(property.evaluate()))) -> decltype(argument ^ accessor::get(property.evaluate())) { return argument ^ accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator <<(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) << argument)) -> decltype(accessor::get(property.evaluate()) << argument) { return accessor::get(property.evaluate()) << argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator <<(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument << accessor::get(property.evaluate()))) -> decltype(argument << accessor::get(property.evaluate())) { return argument << accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator >>(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) >> argument)) -> decltype(accessor::get(property.evaluate()) >> argument) { return accessor::get(property.evaluate()) >> argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator >>(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument >> accessor::get(property.evaluate()))) -> decltype(argument >> accessor::get(property.evaluate())) { return argument >> accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator <(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) < argument)) -> decltype(accessor::get(property.evaluate()) < argument) { return accessor::get(property.evaluate()) < argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator <(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument < accessor::get(property.evaluate()))) -> decltype(argument < accessor::get(property.evaluate())) { return argument < accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator >(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) > argument)) -> decltype(accessor::get(property.evaluate()) > argument) { return accessor::get(property.evaluate()) > argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator >(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument > accessor::get(property.evaluate()))) -> decltype(argument > accessor::get(property.evaluate())) { return argument > accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator ==(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) == argument)) -> decltype(accessor::get(property.evaluate()) == argument) { return accessor::get(property.evaluate()) == argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator ==(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument == accessor::get(property.evaluate()))) -> decltype(argument == accessor::get(property.evaluate())) { return argument == accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator !=(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) != argument)) -> decltype(accessor::get(property.evaluate()) != argument) { return accessor::get(property.evaluate()) != argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator !=(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument != accessor::get(property.evaluate()))) -> decltype(argument != accessor::get(property.evaluate())) { return argument != accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator <=(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) <= argument)) -> decltype(accessor::get(property.evaluate()) <= argument) { return accessor::get(property.evaluate()) <= argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator <=(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument <= accessor::get(property.evaluate()))) -> decltype(argument <= accessor::get(property.evaluate())) { return argument <= accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator >=(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) >= argument)) -> decltype(accessor::get(property.evaluate()) >= argument) { return accessor::get(property.evaluate()) >= argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator >=(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument >= accessor::get(property.evaluate()))) -> decltype(argument >= accessor::get(property.evaluate())) { return argument >= accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator &&(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) && argument)) -> decltype(accessor::get(property.evaluate()) && argument) { return accessor::get(property.evaluate()) && argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator &&(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument && accessor::get(property.evaluate()))) -> decltype(argument && accessor::get(property.evaluate())) { return argument && accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator ||(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) || argument)) -> decltype(accessor::get(property.evaluate()) || argument) { return accessor::get(property.evaluate()) || argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator ||(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument || accessor::get(property.evaluate()))) -> decltype(argument || accessor::get(property.evaluate())) { return argument || accessor::get(property.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator ,(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()), argument)) -> decltype(accessor::get(property.evaluate()), argument) { return accessor::get(property.evaluate()), argument; }
    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator ,(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument, accessor::get(property.evaluate()))) -> decltype(argument, accessor::get(property.evaluate())) { return argument, accessor::get(property.evaluate()); }
    template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator ,(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()), accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()), accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()), accessor::get(propertyB.evaluate()); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator +=(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(request::mutator_set_add<mutator>::value(property.evaluate(), argument))) -> typename std::enable_if<detect::add_operator<subbase&, type>::value, decltype(request::mutator_set_add<mutator>::value(property.evaluate(), argument))>::type { return request::mutator_set_add<mutator>::value(property.evaluate(), argument); }
    template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator +=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorA, submutatorB> const& propertyB) noexcept(noexcept(request::mutator_set_add<mutator>::value(propertyA.evaluate(), propertyB.value))) -> typename std::enable_if<detect::add_operator<subbaseA&, subbaseB>::value, decltype(request::mutator_set_add<mutator>::value(propertyA.evaluate(), propertyB.value))>::type { return request::mutator_set_add<mutator>::value(propertyA.evaluate(), propertyB.value); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator -=(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(request::mutator_set_subtract<mutator>::value(property.evaluate(), argument))) -> typename std::enable_if<detect::subtract_operator<subbase&, type>::value, decltype(request::mutator_set_subtract<mutator>::value(property.evaluate(), argument))>::type { return request::mutator_set_subtract<mutator>::value(property.evaluate(), argument); }
    template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator -=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorA, submutatorB> const& propertyB) noexcept(noexcept(request::mutator_set_subtract<mutator>::value(propertyA.evaluate(), propertyB.value))) -> typename std::enable_if<detect::subtract_operator<subbaseA&, subbaseB>::value, decltype(request::mutator_set_subtract<mutator>::value(propertyA.evaluate(), propertyB.value))>::type { return request::mutator_set_subtract<mutator>::value(propertyA.evaluate(), propertyB.value); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator *=(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(request::mutator_set_multiply<mutator>::value(property.evaluate(), argument))) -> typename std::enable_if<detect::multiply_operator<subbase&, type>::value, decltype(request::mutator_set_multiply<mutator>::value(property.evaluate(), argument))>::type { return request::mutator_set_multiply<mutator>::value(property.evaluate(), argument); }
    template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator *=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorA, submutatorB> const& propertyB) noexcept(noexcept(request::mutator_set_multiply<mutator>::value(propertyA.evaluate(), propertyB.value))) -> typename std::enable_if<detect::multiply_operator<subbaseA&, subbaseB>::value, decltype(request::mutator_set_multiply<mutator>::value(propertyA.evaluate(), propertyB.value))>::type { return request::mutator_set_multiply<mutator>::value(propertyA.evaluate(), propertyB.value); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator /=(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(request::mutator_set_divide<mutator>::value(property.evaluate(), argument))) -> typename std::enable_if<detect::divide_operator<subbase&, type>::value, decltype(request::mutator_set_divide<mutator>::value(property.evaluate(), argument))>::type { return request::mutator_set_divide<mutator>::value(property.evaluate(), argument); }
    template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator /=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorA, submutatorB> const& propertyB) noexcept(noexcept(request::mutator_set_divide<mutator>::value(propertyA.evaluate(), propertyB.value))) -> typename std::enable_if<detect::divide_operator<subbaseA&, subbaseB>::value, decltype(request::mutator_set_divide<mutator>::value(propertyA.evaluate(), propertyB.value))>::type { return request::mutator_set_divide<mutator>::value(propertyA.evaluate(), propertyB.value); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator %=(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(request::mutator_set_modulo<mutator>::value(property.evaluate(), argument))) -> typename std::enable_if<detect::modulo_operator<subbase&, type>::value, decltype(request::mutator_set_modulo<mutator>::value(property.evaluate(), argument))>::type { return request::mutator_set_modulo<mutator>::value(property.evaluate(), argument); }
    template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator %=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorA, submutatorB> const& propertyB) noexcept(noexcept(request::mutator_set_modulo<mutator>::value(propertyA.evaluate(), propertyB.value))) -> typename std::enable_if<detect::modulo_operator<subbaseA&, subbaseB>::value, decltype(request::mutator_set_modulo<mutator>::value(propertyA.evaluate(), propertyB.value))>::type { return request::mutator_set_modulo<mutator>::value(propertyA.evaluate(), propertyB.value); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator &=(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(request::mutator_set_bitwise_and<mutator>::value(property.evaluate(), argument))) -> typename std::enable_if<detect::bitwise_and_operator<subbase&, type>::value, decltype(request::mutator_set_bitwise_and<mutator>::value(property.evaluate(), argument))>::type { return request::mutator_set_bitwise_and<mutator>::value(property.evaluate(), argument); }
    template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator &=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorA, submutatorB> const& propertyB) noexcept(noexcept(request::mutator_set_bitwise_and<mutator>::value(propertyA.evaluate(), propertyB.value))) -> typename std::enable_if<detect::bitwise_and_operator<subbaseA&, subbaseB>::value, decltype(request::mutator_set_bitwise_and<mutator>::value(propertyA.evaluate(), propertyB.value))>::type { return request::mutator_set_bitwise_and<mutator>::value(propertyA.evaluate(), propertyB.value); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator |=(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(request::mutator_set_bitwise_or<mutator>::value(property.evaluate(), argument))) -> typename std::enable_if<detect::bitwise_or_operator<subbase&, type>::value, decltype(request::mutator_set_bitwise_or<mutator>::value(property.evaluate(), argument))>::type { return request::mutator_set_bitwise_or<mutator>::value(property.evaluate(), argument); }
    template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator |=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorA, submutatorB> const& propertyB) noexcept(noexcept(request::mutator_set_bitwise_or<mutator>::value(propertyA.evaluate(), propertyB.value))) -> typename std::enable_if<detect::bitwise_or_operator<subbaseA&, subbaseB>::value, decltype(request::mutator_set_bitwise_or<mutator>::value(propertyA.evaluate(), propertyB.value))>::type { return request::mutator_set_bitwise_or<mutator>::value(propertyA.evaluate(), propertyB.value); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator ^=(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(request::mutator_set_bitwise_xor<mutator>::value(property.evaluate(), argument))) -> typename std::enable_if<detect::bitwise_xor_operator<subbase&, type>::value, decltype(request::mutator_set_bitwise_xor<mutator>::value(property.evaluate(), argument))>::type { return request::mutator_set_bitwise_xor<mutator>::value(property.evaluate(), argument); }
    template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator ^=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorA, submutatorB> const& propertyB) noexcept(noexcept(request::mutator_set_bitwise_xor<mutator>::value(propertyA.evaluate(), propertyB.value))) -> typename std::enable_if<detect::bitwise_xor_operator<subbaseA&, subbaseB>::value, decltype(request::mutator_set_bitwise_xor<mutator>::value(propertyA.evaluate(), propertyB.value))>::type { return request::mutator_set_bitwise_xor<mutator>::value(propertyA.evaluate(), propertyB.value); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator <<=(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(request::mutator_set_shift_left<mutator>::value(property.evaluate(), argument))) -> typename std::enable_if<detect::shift_left_operator<subbase&, type>::value, decltype(request::mutator_set_shift_left<mutator>::value(property.evaluate(), argument))>::type { return request::mutator_set_shift_left<mutator>::value(property.evaluate(), argument); }
    template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator <<=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorA, submutatorB> const& propertyB) noexcept(noexcept(request::mutator_set_shift_left<mutator>::value(propertyA.evaluate(), propertyB.value))) -> typename std::enable_if<detect::shift_left_operator<subbaseA&, subbaseB>::value, decltype(request::mutator_set_shift_left<mutator>::value(propertyA.evaluate(), propertyB.value))>::type { return request::mutator_set_shift_left<mutator>::value(propertyA.evaluate(), propertyB.value); }

    template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator >>=(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(request::mutator_set_shift_right<mutator>::value(property.evaluate(), argument))) -> typename std::enable_if<detect::shift_right_operator<subbase&, type>::value, decltype(request::mutator_set_shift_right<mutator>::value(property.evaluate(), argument))>::type { return request::mutator_set_shift_right<mutator>::value(property.evaluate(), argument); }
    template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator >>=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorA, submutatorB> const& propertyB) noexcept(noexcept(request::mutator_set_shift_right<mutator>::value(propertyA.evaluate(), propertyB.value))) -> typename std::enable_if<detect::shift_right_operator<subbaseA&, subbaseB>::value, decltype(request::mutator_set_shift_right<mutator>::value(propertyA.evaluate(), propertyB.value))>::type { return request::mutator_set_shift_right<mutator>::value(propertyA.evaluate(), propertyB.value); }

    constexpr inline operator typename std::conditional<std::is_same<base&, decltype(accessor::get(std::declval<base&>()))>::value, base&, property_void>::type() const noexcept { return accessor::get(this->evaluate()); }

    template <typename type> constexpr inline operator type() const noexcept { return accessor::get(this->evaluate()); }
    template <typename type> constexpr inline operator type&() const noexcept { return accessor::get(this->evaluate()); }
    template <typename type> constexpr inline operator type&&() const noexcept { return accessor::get(this->evaluate()); }

    // ...
    #ifdef __cpp_impl_coroutine
      template <typename subbase, class subaccessor, class submutator> /* constexpr */ friend inline auto operator co_await(property<subbase, subaccessor, submutator> const& property) noexcept { co_return accessor::get(const_cast<base&>(property.value)); }
    #endif

    #ifdef __cpp_impl_three_way_comparison
      template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator <=>(property<subbase, subaccessor, submutator> const& property, type&& argument) noexcept(noexcept(accessor::get(property.evaluate()) <=> argument)) -> decltype(accessor::get(property.evaluate()) <=> argument) { return accessor::get(property.evaluate()) <=> argument; }
      template <typename subbase, class subaccessor, class submutator, typename type> constexpr friend inline auto operator <=>(type&& argument, property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(argument <=> accessor::get(property.evaluate()))) -> decltype(argument <=> accessor::get(property.evaluate())) { return argument <=> accessor::get(property.evaluate()); }

      #if false == defined(__INTEL_COMPILER)
        template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator <=>(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) <=> accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) <=> accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) <=> accessor::get(propertyB.evaluate()); }
      #endif
    #endif

    // ...
    #if defined(__INTEL_COMPILER)
      template <typename... types> constexpr inline decltype(accessor::get(std::declval<base&>())(std::forward<types>()...)) operator ()(types&&... arguments) const noexcept { return accessor::get(this->evaluate())(std::forward<types>(arguments)...); }

      template <typename subbase, class subaccessor, class submutator> constexpr friend inline decltype(+accessor::get(std::declval<subbase&>())) operator +(property<subbase, subaccessor, submutator> const& property) noexcept { return +accessor::get(property.evaluate()); }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline decltype(-accessor::get(std::declval<subbase&>())) operator -(property<subbase, subaccessor, submutator> const& property) noexcept { return -accessor::get(property.evaluate()); }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline decltype(*accessor::get(std::declval<subbase&>())) operator *(property<subbase, subaccessor, submutator> const& property) noexcept { return *accessor::get(property.evaluate()); }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline decltype(~accessor::get(std::declval<subbase&>())) operator ~(property<subbase, subaccessor, submutator> const& property) noexcept { return ~accessor::get(property.evaluate()); }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline decltype(!accessor::get(std::declval<subbase&>())) operator !(property<subbase, subaccessor, submutator> const& property) noexcept { return !accessor::get(property.evaluate()); }

      template <typename subbase, class subaccessor, class submutator> constexpr friend inline decltype(++accessor::get(std::declval<subbase&>())) operator ++(property<subbase, subaccessor, submutator> const& property) noexcept { return ++accessor::get(property.evaluate()); }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline decltype(--accessor::get(std::declval<subbase&>())) operator --(property<subbase, subaccessor, submutator> const& property) noexcept { return --accessor::get(property.evaluate()); }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline decltype(accessor::get(std::declval<subbase&>())++) operator ++(property<subbase, subaccessor, submutator> const& property, int const) noexcept { return accessor::get(property.evaluate())++; }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline decltype(accessor::get(std::declval<subbase&>())--) operator --(property<subbase, subaccessor, submutator> const& property, int const) noexcept { return accessor::get(property.evaluate())--; }

      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) +  accessor::get(std::declval<subbaseB&>())) operator + (property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) +  accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) -  accessor::get(std::declval<subbaseB&>())) operator - (property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) -  accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) *  accessor::get(std::declval<subbaseB&>())) operator * (property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) *  accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) /  accessor::get(std::declval<subbaseB&>())) operator / (property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) /  accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) %  accessor::get(std::declval<subbaseB&>())) operator % (property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) %  accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) &  accessor::get(std::declval<subbaseB&>())) operator & (property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) &  accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) |  accessor::get(std::declval<subbaseB&>())) operator | (property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) |  accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) ^  accessor::get(std::declval<subbaseB&>())) operator ^ (property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) ^  accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) << accessor::get(std::declval<subbaseB&>())) operator <<(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) << accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) >> accessor::get(std::declval<subbaseB&>())) operator >>(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) >> accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) <  accessor::get(std::declval<subbaseB&>())) operator < (property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) <  accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) >  accessor::get(std::declval<subbaseB&>())) operator > (property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) >  accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) == accessor::get(std::declval<subbaseB&>())) operator ==(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) == accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) != accessor::get(std::declval<subbaseB&>())) operator !=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) != accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) <= accessor::get(std::declval<subbaseB&>())) operator <=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) <= accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) >= accessor::get(std::declval<subbaseB&>())) operator >=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) >= accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) && accessor::get(std::declval<subbaseB&>())) operator &&(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) && accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline decltype(accessor::get(std::declval<subbaseA&>()) || accessor::get(std::declval<subbaseB&>())) operator ||(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept { return accessor::get(propertyA.evaluate()) || accessor::get(propertyB.evaluate()); }
    #else
      template <typename... types> constexpr inline auto operator ()(types&&... arguments) const noexcept(noexcept(accessor::get(this->evaluate())(std::forward<types>(arguments)...))) -> decltype(accessor::get(this->evaluate())(std::forward<types>(arguments)...)) { return accessor::get(this->evaluate())(std::forward<types>(arguments)...); }

      template <typename subbase, class subaccessor, class submutator> constexpr friend inline auto operator +(property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(+accessor::get(property.evaluate()))) -> decltype(+accessor::get(property.evaluate())) { return +accessor::get(property.evaluate()); }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline auto operator -(property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(-accessor::get(property.evaluate()))) -> decltype(-accessor::get(property.evaluate())) { return -accessor::get(property.evaluate()); }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline auto operator *(property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(*accessor::get(property.evaluate()))) -> decltype(*accessor::get(property.evaluate())) { return *accessor::get(property.evaluate()); }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline auto operator ~(property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(~accessor::get(property.evaluate()))) -> decltype(~accessor::get(property.evaluate())) { return ~accessor::get(property.evaluate()); }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline auto operator !(property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(!accessor::get(property.evaluate()))) -> decltype(!accessor::get(property.evaluate())) { return !accessor::get(property.evaluate()); }

      template <typename subbase, class subaccessor, class submutator> constexpr friend inline auto operator ++(property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(++accessor::get(property.evaluate()))) -> decltype(++accessor::get(property.evaluate())) { return ++accessor::get(property.evaluate()); }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline auto operator --(property<subbase, subaccessor, submutator> const& property) noexcept(noexcept(--accessor::get(property.evaluate()))) -> decltype(--accessor::get(property.evaluate())) { return --accessor::get(property.evaluate()); }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline auto operator ++(property<subbase, subaccessor, submutator> const& property, int const) noexcept(noexcept(accessor::get(property.evaluate())++)) -> decltype(accessor::get(property.evaluate())++) { return accessor::get(property.evaluate())++; }
      template <typename subbase, class subaccessor, class submutator> constexpr friend inline auto operator --(property<subbase, subaccessor, submutator> const& property, int const) noexcept(noexcept(accessor::get(property.evaluate())--)) -> decltype(accessor::get(property.evaluate())--) { return accessor::get(property.evaluate())--; }

      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator +(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) + accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) + accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) + accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator -(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) - accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) - accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) - accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator *(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) * accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) * accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) * accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator /(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) / accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) / accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) / accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator %(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) % accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) % accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) % accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator &(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) & accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) & accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) & accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator |(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) | accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) | accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) | accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator ^(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) ^ accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) ^ accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) ^ accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator <<(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) << accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) << accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) << accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator >>(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) >> accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) >> accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) >> accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator <(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) < accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) < accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) < accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator >(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) > accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) > accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) > accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator ==(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) == accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) == accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) == accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator !=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) != accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) != accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) != accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator <=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) <= accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) <= accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) <= accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator >=(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) >= accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) >= accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) >= accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator &&(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) && accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) && accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) && accessor::get(propertyB.evaluate()); }
      template <typename subbaseA, class subaccessorA, class submutatorA, typename subbaseB, class subaccessorB, class submutatorB> constexpr friend inline auto operator ||(property<subbaseA, subaccessorA, submutatorA> const& propertyA, property<subbaseB, subaccessorB, submutatorB> const& propertyB) noexcept(noexcept(accessor::get(propertyA.evaluate()) || accessor::get(propertyB.evaluate()))) -> decltype(accessor::get(propertyA.evaluate()) || accessor::get(propertyB.evaluate())) { return accessor::get(propertyA.evaluate()) || accessor::get(propertyB.evaluate()); }
    #endif
};

template <typename base, class accessor, class mutator>
struct property<property<base>, accessor, mutator>;

/* Main */
int main() {}
