#include <compare>
#include <cstddef>
#include <cstdio>
#include <type_traits>
#include <utility>

/* ... */
namespace {
  template <typename base>
  struct property_accessor {
    constexpr inline static base& get(base& value) noexcept { return value; }
  };

  template <typename base>
  struct property_mutator {
    template <typename type> constexpr inline static auto set            (base& value, type&& argument) noexcept(noexcept(value =  std::forward<type>(argument))) -> decltype(value =  std::forward<type>(argument)) { return value =  std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_add        (base& value, type&& argument) noexcept(noexcept(value += std::forward<type>(argument))) -> decltype(value += std::forward<type>(argument)) { return value += std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_bitwise_and(base& value, type&& argument) noexcept(noexcept(value &= std::forward<type>(argument))) -> decltype(value &= std::forward<type>(argument)) { return value &= std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_bitwise_or (base& value, type&& argument) noexcept(noexcept(value |= std::forward<type>(argument))) -> decltype(value |= std::forward<type>(argument)) { return value |= std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_bitwise_xor(base& value, type&& argument) noexcept(noexcept(value ^= std::forward<type>(argument))) -> decltype(value ^= std::forward<type>(argument)) { return value ^= std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_divide     (base& value, type&& argument) noexcept(noexcept(value /= std::forward<type>(argument))) -> decltype(value /= std::forward<type>(argument)) { return value /= std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_modulo     (base& value, type&& argument) noexcept(noexcept(value %= std::forward<type>(argument))) -> decltype(value %= std::forward<type>(argument)) { return value %= std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_multiply   (base& value, type&& argument) noexcept(noexcept(value *= std::forward<type>(argument))) -> decltype(value *= std::forward<type>(argument)) { return value *= std::forward<type>(argument); }
    template <typename type> constexpr inline static auto set_subtract   (base& value, type&& argument) noexcept(noexcept(value -= std::forward<type>(argument))) -> decltype(value -= std::forward<type>(argument)) { return value -= std::forward<type>(argument); }
  };

  // ...
  namespace detect {
    namespace {
      struct property_mutator_set_add_lookup         { unsigned char const set_add; };
      struct property_mutator_set_bitwise_and_lookup { unsigned char const set_bitwise_and; };
      struct property_mutator_set_bitwise_or_lookup  { unsigned char const set_bitwise_or; };
      struct property_mutator_set_bitwise_xor_lookup { unsigned char const set_bitwise_xor; };
      struct property_mutator_set_divide_lookup      { unsigned char const set_divide; };
      struct property_mutator_set_modulo_lookup      { unsigned char const set_modulo; };
      struct property_mutator_set_multiply_lookup    { unsigned char const set_multiply; };
      struct property_mutator_set_subtract_lookup    { unsigned char const set_subtract; };

      template <class object, class... lookups>
      struct member_name_lookup : public object, public lookups... {};
    }

    // ...
    template <class, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union add_operator { enum { value = false }; };
    template <class object, typename type> union add_operator<object, type, typename std::integral_constant<std::size_t, sizeof(std::declval<object>() += std::declval<type>())>::value_type> { enum { value = true }; };

    template <class, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union bitwise_and_operator { enum { value = false }; };
    template <class object, typename type> union bitwise_and_operator<object, type, typename std::integral_constant<std::size_t, sizeof(std::declval<object>() &= std::declval<type>())>::value_type> { enum { value = true }; };

    template <class, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union bitwise_or_operator { enum { value = false }; };
    template <class object, typename type> union bitwise_or_operator<object, type, typename std::integral_constant<std::size_t, sizeof(std::declval<object>() |= std::declval<type>())>::value_type> { enum { value = true }; };

    template <class, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union bitwise_xor_operator { enum { value = false }; };
    template <class object, typename type> union bitwise_xor_operator<object, type, typename std::integral_constant<std::size_t, sizeof(std::declval<object>() ^= std::declval<type>())>::value_type> { enum { value = true }; };

    template <class, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union divide_operator { enum { value = false }; };
    template <class object, typename type> union divide_operator<object, type, typename std::integral_constant<std::size_t, sizeof(std::declval<object>() /= std::declval<type>())>::value_type> { enum { value = true }; };

    template <class, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union member_access_operator { enum { value = false }; };
    template <class object> union member_access_operator<object, typename std::integral_constant<std::size_t, sizeof(std::declval<object>().operator ->(), false)>::value_type> { enum { value = true }; };

    template <class, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union modulo_operator { enum { value = false }; };
    template <class object, typename type> union modulo_operator<object, type, typename std::integral_constant<std::size_t, sizeof(std::declval<object>() %= std::declval<type>())>::value_type> { enum { value = true }; };

    template <class, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union multiply_operator { enum { value = false }; };
    template <class object, typename type> union multiply_operator<object, type, typename std::integral_constant<std::size_t, sizeof(std::declval<object>() *= std::declval<type>())>::value_type> { enum { value = true }; };

    template <class, typename, typename = typename std::integral_constant<std::size_t, 0u>::value_type> union subtract_operator { enum { value = false }; };
    template <class object, typename type> union subtract_operator<object, type, typename std::integral_constant<std::size_t, sizeof(std::declval<object>() -= std::declval<type>())>::value_type> { enum { value = true }; };

    // ...
    template <class object, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = std::is_final<object>::value || std::is_union<object>::value> union mutator_set_add { enum { value = false == derivable }; };
    template <class object> union mutator_set_add<object, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<object, property_mutator_set_add_lookup>::set_add)>::value_type, false> { enum { value = false }; };
    template <class object> union mutator_set_add<object, decltype(sizeof(&object::set_add)), true> { enum { value = true }; };

    template <class object, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = std::is_final<object>::value || std::is_union<object>::value> union mutator_set_bitwise_and { enum { value = false == derivable }; };
    template <class object> union mutator_set_bitwise_and<object, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<object, property_mutator_set_bitwise_and_lookup>::set_bitwise_and)>::value_type, false> { enum { value = false }; };
    template <class object> union mutator_set_bitwise_and<object, decltype(sizeof(&object::set_bitwise_and)), true> { enum { value = true }; };

    template <class object, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = std::is_final<object>::value || std::is_union<object>::value> union mutator_set_bitwise_or { enum { value = false == derivable }; };
    template <class object> union mutator_set_bitwise_or<object, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<object, property_mutator_set_bitwise_or_lookup>::set_bitwise_or)>::value_type, false> { enum { value = false }; };
    template <class object> union mutator_set_bitwise_or<object, decltype(sizeof(&object::set_bitwise_or)), true> { enum { value = true }; };

    template <class object, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = std::is_final<object>::value || std::is_union<object>::value> union mutator_set_bitwise_xor { enum { value = false == derivable }; };
    template <class object> union mutator_set_bitwise_xor<object, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<object, property_mutator_set_bitwise_xor_lookup>::set_bitwise_xor)>::value_type, false> { enum { value = false }; };
    template <class object> union mutator_set_bitwise_xor<object, decltype(sizeof(&object::set_bitwise_xor)), true> { enum { value = true }; };

    template <class object, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = std::is_final<object>::value || std::is_union<object>::value> union mutator_set_divide { enum { value = false == derivable }; };
    template <class object> union mutator_set_divide<object, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<object, property_mutator_set_divide_lookup>::set_divide)>::value_type, false> { enum { value = false }; };
    template <class object> union mutator_set_divide<object, decltype(sizeof(&object::set_divide)), true> { enum { value = true }; };

    template <class object, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = std::is_final<object>::value || std::is_union<object>::value> union mutator_set_modulo { enum { value = false == derivable }; };
    template <class object> union mutator_set_modulo<object, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<object, property_mutator_set_modulo_lookup>::set_modulo)>::value_type, false> { enum { value = false }; };
    template <class object> union mutator_set_modulo<object, decltype(sizeof(&object::set_modulo)), true> { enum { value = true }; };

    template <class object, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = std::is_final<object>::value || std::is_union<object>::value> union mutator_set_multiply { enum { value = false == derivable }; };
    template <class object> union mutator_set_multiply<object, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<object, property_mutator_set_multiply_lookup>::set_multiply)>::value_type, false> { enum { value = false }; };
    template <class object> union mutator_set_multiply<object, decltype(sizeof(&object::set_multiply)), true> { enum { value = true }; };

    template <class object, typename = typename std::integral_constant<std::size_t, 0u>::value_type, bool derivable = std::is_final<object>::value || std::is_union<object>::value> union mutator_set_subtract { enum { value = false == derivable }; };
    template <class object> union mutator_set_subtract<object, typename std::integral_constant<std::size_t, sizeof(member_name_lookup<object, property_mutator_set_subtract_lookup>::set_subtract)>::value_type, false> { enum { value = false }; };
    template <class object> union mutator_set_subtract<object, decltype(sizeof(&object::set_subtract)), true> { enum { value = true }; };
  }

  namespace request {
    template <class mutator, bool = detect::mutator_set_add<mutator>::value>         union set_add;
    template <class mutator> union set_add<mutator, false>         { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value + std::forward<type>(argument)))) -> decltype(mutator::set(value, value + std::forward<type>(argument))) { return mutator::set(value, value + std::forward<type>(argument)); } };
    template <class mutator> union set_add<mutator, true>          { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_add(value, std::forward<type>(argument)))) -> decltype(mutator::set_add(value, std::forward<type>(argument))) { return mutator::set_add(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_bitwise_and<mutator>::value> union set_bitwise_and;
    template <class mutator> union set_bitwise_and<mutator, false> { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value & std::forward<type>(argument)))) -> decltype(mutator::set(value, value & std::forward<type>(argument))) { return mutator::set(value, value & std::forward<type>(argument)); } };
    template <class mutator> union set_bitwise_and<mutator, true>  { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_bitwise_and(value, std::forward<type>(argument)))) -> decltype(mutator::set_bitwise_and(value, std::forward<type>(argument))) { return mutator::set_bitwise_and(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_bitwise_or<mutator>::value>  union set_bitwise_or;
    template <class mutator> union set_bitwise_or<mutator, false>  { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value | std::forward<type>(argument)))) -> decltype(mutator::set(value, value | std::forward<type>(argument))) { return mutator::set(value, value | std::forward<type>(argument)); } };
    template <class mutator> union set_bitwise_or<mutator, true>   { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_bitwise_or(value, std::forward<type>(argument)))) -> decltype(mutator::set_bitwise_or(value, std::forward<type>(argument))) { return mutator::set_bitwise_or(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_bitwise_xor<mutator>::value> union set_bitwise_xor;
    template <class mutator> union set_bitwise_xor<mutator, false> { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value ^ std::forward<type>(argument)))) -> decltype(mutator::set(value, value ^ std::forward<type>(argument))) { return mutator::set(value, value ^ std::forward<type>(argument)); } };
    template <class mutator> union set_bitwise_xor<mutator, true>  { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_bitwise_xor(value, std::forward<type>(argument)))) -> decltype(mutator::set_bitwise_xor(value, std::forward<type>(argument))) { return mutator::set_bitwise_xor(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_divide<mutator>::value>      union set_divide;
    template <class mutator> union set_divide<mutator, false>      { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value / std::forward<type>(argument)))) -> decltype(mutator::set(value, value / std::forward<type>(argument))) { return mutator::set(value, value / std::forward<type>(argument)); } };
    template <class mutator> union set_divide<mutator, true>       { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_divide(value, std::forward<type>(argument)))) -> decltype(mutator::set_divide(value, std::forward<type>(argument))) { return mutator::set_divide(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_modulo<mutator>::value>      union set_modulo;
    template <class mutator> union set_modulo<mutator, false>      { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value % std::forward<type>(argument)))) -> decltype(mutator::set(value, value % std::forward<type>(argument))) { return mutator::set(value, value % std::forward<type>(argument)); } };
    template <class mutator> union set_modulo<mutator, true>       { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_modulo(value, std::forward<type>(argument)))) -> decltype(mutator::set_modulo(value, std::forward<type>(argument))) { return mutator::set_modulo(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_multiply<mutator>::value>    union set_multiply;
    template <class mutator> union set_multiply<mutator, false>    { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value * std::forward<type>(argument)))) -> decltype(mutator::set(value, value * std::forward<type>(argument))) { return mutator::set(value, value * std::forward<type>(argument)); } };
    template <class mutator> union set_multiply<mutator, true>     { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_multiply(value, std::forward<type>(argument)))) -> decltype(mutator::set_multiply(value, std::forward<type>(argument))) { return mutator::set_multiply(value, std::forward<type>(argument)); } };

    template <class mutator, bool = detect::mutator_set_subtract<mutator>::value>    union set_subtract;
    template <class mutator> union set_subtract<mutator, false>    { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set(value, value - std::forward<type>(argument)))) -> decltype(mutator::set(value, value - std::forward<type>(argument))) { return mutator::set(value, value - std::forward<type>(argument)); } };
    template <class mutator> union set_subtract<mutator, true>     { template <typename base, typename type> constexpr inline static auto value(base& value, type&& argument) noexcept(noexcept(mutator::set_subtract(value, std::forward<type>(argument)))) -> decltype(mutator::set_subtract(value, std::forward<type>(argument))) { return mutator::set_subtract(value, std::forward<type>(argument)); } };
  }
}

// ...
template <typename base, class accessor_type = void, class mutator_type = void>
struct property final {
  template <typename, class, class>
  friend struct property;

  private:
    base value;

    typedef typename std::conditional<std::is_same<void, typename std::remove_cv<accessor_type>::type>::value, property_accessor<base>, accessor_type>::type accessor;
    typedef typename std::conditional<std::is_same<void, typename std::remove_cv<mutator_type >::type>::value, property_mutator <base>, mutator_type >::type mutator;

  public:
    template <typename... types>
    constexpr inline property(types&&... arguments) noexcept(noexcept(base(std::forward<types>(arguments)...))) :
      value(std::forward<types>(arguments)...)
    {}

    // ...
    constexpr inline base& operator ->() const noexcept(std::is_class<typename std::remove_pointer<base>::type>::value || detect::member_access_operator<base>::value) { return accessor::get(const_cast<base&>(this->value)); }
    template <typename type> constexpr inline auto operator =(type&& argument) const noexcept(noexcept(mutator::set(const_cast<base&>(this->value), std::forward<type>(argument)))) -> decltype(mutator::set(const_cast<base&>(this->value), std::forward<type>(argument))) { return mutator::set(const_cast<base&>(this->value), std::forward<type>(argument)); }
    template <typename type> constexpr inline auto operator [](type&& argument) const noexcept(noexcept(accessor::get(const_cast<base&>(this->value))[std::forward<type>(argument)])) -> decltype(accessor::get(const_cast<base&>(this->value))[std::forward<type>(argument)]) { return accessor::get(const_cast<base&>(this->value))[std::forward<type>(argument)]; }
    template <typename... types> constexpr inline auto operator ()(types&&... arguments) const noexcept(noexcept(accessor::get(const_cast<base&>(this->value))(std::forward<types>(arguments)...))) -> decltype(accessor::get(const_cast<base&>(this->value))(std::forward<types>(arguments)...)) { return accessor::get(const_cast<base&>(this->value))(std::forward<types>(arguments)...); }

    template <typename subbase> constexpr friend inline auto operator +(property<subbase> const& property) noexcept(noexcept(+accessor::get(const_cast<subbase&>(property.value)))) -> decltype(+accessor::get(const_cast<subbase&>(property.value))) { return +accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbase> constexpr friend inline auto operator -(property<subbase> const& property) noexcept(noexcept(-accessor::get(const_cast<subbase&>(property.value)))) -> decltype(-accessor::get(const_cast<subbase&>(property.value))) { return -accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbase> constexpr friend inline auto operator ~(property<subbase> const& property) noexcept(noexcept(~accessor::get(const_cast<subbase&>(property.value)))) -> decltype(~accessor::get(const_cast<subbase&>(property.value))) { return ~accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbase> constexpr friend inline auto operator !(property<subbase> const& property) noexcept(noexcept(!accessor::get(const_cast<subbase&>(property.value)))) -> decltype(!accessor::get(const_cast<subbase&>(property.value))) { return !accessor::get(const_cast<subbase&>(property.value)); }

    template <typename subbase> constexpr friend inline auto operator ++(property<subbase> const& property) noexcept(noexcept(++accessor::get(const_cast<subbase&>(property.value)))) -> decltype(++accessor::get(const_cast<subbase&>(property.value))) { return ++accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbase> constexpr friend inline auto operator --(property<subbase> const& property) noexcept(noexcept(--accessor::get(const_cast<subbase&>(property.value)))) -> decltype(--accessor::get(const_cast<subbase&>(property.value))) { return --accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbase> constexpr friend inline auto operator ++(property<subbase> const& property, int const) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value))++)) -> decltype(accessor::get(const_cast<subbase&>(property.value))++) { return accessor::get(const_cast<subbase&>(property.value))++; }
    template <typename subbase> constexpr friend inline auto operator --(property<subbase> const& property, int const) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value))--)) -> decltype(accessor::get(const_cast<subbase&>(property.value))--) { return accessor::get(const_cast<subbase&>(property.value))--; }

    template <typename subbase, typename type> constexpr friend inline auto operator ->*(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) ->* argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) ->* argument) { return accessor::get(const_cast<subbase&>(property.value)) ->* argument; }

    template <typename subbase, typename type> constexpr friend inline auto operator +(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) + argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) + argument) { return accessor::get(const_cast<subbase&>(property.value)) + argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator +(type&& argument, property<subbase> const& property) noexcept(noexcept(argument + accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument + accessor::get(const_cast<subbase&>(property.value))) { return argument + accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator +(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) + accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) + accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) + accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator -(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) - argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) - argument) { return accessor::get(const_cast<subbase&>(property.value)) - argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator -(type&& argument, property<subbase> const& property) noexcept(noexcept(argument - accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument - accessor::get(const_cast<subbase&>(property.value))) { return argument - accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator -(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) - accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) - accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) - accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator *(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) * argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) * argument) { return accessor::get(const_cast<subbase&>(property.value)) * argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator *(type&& argument, property<subbase> const& property) noexcept(noexcept(argument * accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument * accessor::get(const_cast<subbase&>(property.value))) { return argument * accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator *(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) * accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) * accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) * accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator /(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) / argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) / argument) { return accessor::get(const_cast<subbase&>(property.value)) / argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator /(type&& argument, property<subbase> const& property) noexcept(noexcept(argument / accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument / accessor::get(const_cast<subbase&>(property.value))) { return argument / accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator /(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) / accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) / accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) / accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator %(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) % argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) % argument) { return accessor::get(const_cast<subbase&>(property.value)) % argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator %(type&& argument, property<subbase> const& property) noexcept(noexcept(argument % accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument % accessor::get(const_cast<subbase&>(property.value))) { return argument % accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator %(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) % accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) % accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) % accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator &(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) & argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) & argument) { return accessor::get(const_cast<subbase&>(property.value)) & argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator &(type&& argument, property<subbase> const& property) noexcept(noexcept(argument & accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument & accessor::get(const_cast<subbase&>(property.value))) { return argument & accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator &(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) & accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) & accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) & accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator |(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) | argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) | argument) { return accessor::get(const_cast<subbase&>(property.value)) | argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator |(type&& argument, property<subbase> const& property) noexcept(noexcept(argument | accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument | accessor::get(const_cast<subbase&>(property.value))) { return argument | accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator |(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) | accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) | accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) | accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator ^(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) ^ argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) ^ argument) { return accessor::get(const_cast<subbase&>(property.value)) ^ argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator ^(type&& argument, property<subbase> const& property) noexcept(noexcept(argument ^ accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument ^ accessor::get(const_cast<subbase&>(property.value))) { return argument ^ accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator ^(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) ^ accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) ^ accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) ^ accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator <<(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) << argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) << argument) { return accessor::get(const_cast<subbase&>(property.value)) << argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator <<(type&& argument, property<subbase> const& property) noexcept(noexcept(argument << accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument << accessor::get(const_cast<subbase&>(property.value))) { return argument << accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator <<(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) << accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) << accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) << accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator >>(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) >> argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) >> argument) { return accessor::get(const_cast<subbase&>(property.value)) >> argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator >>(type&& argument, property<subbase> const& property) noexcept(noexcept(argument >> accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument >> accessor::get(const_cast<subbase&>(property.value))) { return argument >> accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator >>(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) >> accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) >> accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) >> accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator <(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) < argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) < argument) { return accessor::get(const_cast<subbase&>(property.value)) < argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator <(type&& argument, property<subbase> const& property) noexcept(noexcept(argument < accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument < accessor::get(const_cast<subbase&>(property.value))) { return argument < accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator <(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) < accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) < accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) < accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator >(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) > argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) > argument) { return accessor::get(const_cast<subbase&>(property.value)) > argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator >(type&& argument, property<subbase> const& property) noexcept(noexcept(argument > accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument > accessor::get(const_cast<subbase&>(property.value))) { return argument > accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator >(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) > accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) > accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) > accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator ==(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) == argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) == argument) { return accessor::get(const_cast<subbase&>(property.value)) == argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator ==(type&& argument, property<subbase> const& property) noexcept(noexcept(argument == accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument == accessor::get(const_cast<subbase&>(property.value))) { return argument == accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator ==(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) == accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) == accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) == accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator !=(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) != argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) != argument) { return accessor::get(const_cast<subbase&>(property.value)) != argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator !=(type&& argument, property<subbase> const& property) noexcept(noexcept(argument != accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument != accessor::get(const_cast<subbase&>(property.value))) { return argument != accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator !=(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) != accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) != accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) != accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator <=(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) <= argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) <= argument) { return accessor::get(const_cast<subbase&>(property.value)) <= argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator <=(type&& argument, property<subbase> const& property) noexcept(noexcept(argument <= accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument <= accessor::get(const_cast<subbase&>(property.value))) { return argument <= accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator <=(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) <= accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) <= accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) <= accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator >=(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) >= argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) >= argument) { return accessor::get(const_cast<subbase&>(property.value)) >= argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator >=(type&& argument, property<subbase> const& property) noexcept(noexcept(argument >= accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument >= accessor::get(const_cast<subbase&>(property.value))) { return argument >= accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator >=(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) >= accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) >= accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) >= accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator &&(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) && argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) && argument) { return accessor::get(const_cast<subbase&>(property.value)) && argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator &&(type&& argument, property<subbase> const& property) noexcept(noexcept(argument && accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument && accessor::get(const_cast<subbase&>(property.value))) { return argument && accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator &&(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) && accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) && accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) && accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator ||(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) || argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) || argument) { return accessor::get(const_cast<subbase&>(property.value)) || argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator ||(type&& argument, property<subbase> const& property) noexcept(noexcept(argument || accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument || accessor::get(const_cast<subbase&>(property.value))) { return argument || accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator ||(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) || accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) || accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) || accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator ,(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)), argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)), argument) { return accessor::get(const_cast<subbase&>(property.value)), argument; }
    template <typename subbase, typename type> constexpr friend inline auto operator ,(type&& argument, property<subbase> const& property) noexcept(noexcept(argument, accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument, accessor::get(const_cast<subbase&>(property.value))) { return argument, accessor::get(const_cast<subbase&>(property.value)); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator ,(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)), accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)), accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)), accessor::get(const_cast<subbaseB&>(propertyB.value)); }

    template <typename subbase, typename type> constexpr friend inline auto operator +=(property<subbase> const& property, type&& argument) noexcept(noexcept(request::set_add<mutator>::value(const_cast<subbase&>(property.value), argument))) -> typename std::enable_if<detect::add_operator<subbase, type>::value, decltype(request::set_add<mutator>::value(const_cast<subbase&>(property.value), argument))>::type { return request::set_add<mutator>::value(const_cast<subbase&>(property.value), argument); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator +=(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(request::set_add<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))) -> typename std::enable_if<detect::add_operator<subbaseA, subbaseB>::value, decltype(request::set_add<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))>::type { return request::set_add<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value); }

    template <typename subbase, typename type> constexpr friend inline auto operator &=(property<subbase> const& property, type&& argument) noexcept(noexcept(request::set_bitwise_and<mutator>::value(const_cast<subbase&>(property.value), argument))) -> typename std::enable_if<detect::bitwise_and_operator<subbase, type>::value, decltype(request::set_bitwise_and<mutator>::value(const_cast<subbase&>(property.value), argument))>::type { return request::set_bitwise_and<mutator>::value(const_cast<subbase&>(property.value), argument); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator &=(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(request::set_bitwise_and<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))) -> typename std::enable_if<detect::bitwise_and_operator<subbaseA, subbaseB>::value, decltype(request::set_bitwise_and<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))>::type { return request::set_bitwise_and<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value); }

    template <typename subbase, typename type> constexpr friend inline auto operator |=(property<subbase> const& property, type&& argument) noexcept(noexcept(request::set_bitwise_or<mutator>::value(const_cast<subbase&>(property.value), argument))) -> typename std::enable_if<detect::bitwise_or_operator<subbase, type>::value, decltype(request::set_bitwise_or<mutator>::value(const_cast<subbase&>(property.value), argument))>::type { return request::set_bitwise_or<mutator>::value(const_cast<subbase&>(property.value), argument); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator |=(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(request::set_bitwise_or<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))) -> typename std::enable_if<detect::bitwise_or_operator<subbaseA, subbaseB>::value, decltype(request::set_bitwise_or<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))>::type { return request::set_bitwise_or<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value); }

    template <typename subbase, typename type> constexpr friend inline auto operator ^=(property<subbase> const& property, type&& argument) noexcept(noexcept(request::set_bitwise_xor<mutator>::value(const_cast<subbase&>(property.value), argument))) -> typename std::enable_if<detect::bitwise_xor_operator<subbase, type>::value, decltype(request::set_bitwise_xor<mutator>::value(const_cast<subbase&>(property.value), argument))>::type { return request::set_bitwise_xor<mutator>::value(const_cast<subbase&>(property.value), argument); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator ^=(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(request::set_bitwise_xor<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))) -> typename std::enable_if<detect::bitwise_xor_operator<subbaseA, subbaseB>::value, decltype(request::set_bitwise_xor<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))>::type { return request::set_bitwise_xor<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value); }

    template <typename subbase, typename type> constexpr friend inline auto operator /=(property<subbase> const& property, type&& argument) noexcept(noexcept(request::set_divide<mutator>::value(const_cast<subbase&>(property.value), argument))) -> typename std::enable_if<detect::divide_operator<subbase, type>::value, decltype(request::set_divide<mutator>::value(const_cast<subbase&>(property.value), argument))>::type { return request::set_divide<mutator>::value(const_cast<subbase&>(property.value), argument); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator /=(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(request::set_divide<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))) -> typename std::enable_if<detect::divide_operator<subbaseA, subbaseB>::value, decltype(request::set_divide<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))>::type { return request::set_divide<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value); }

    template <typename subbase, typename type> constexpr friend inline auto operator %=(property<subbase> const& property, type&& argument) noexcept(noexcept(request::set_modulo<mutator>::value(const_cast<subbase&>(property.value), argument))) -> typename std::enable_if<detect::modulo_operator<subbase, type>::value, decltype(request::set_modulo<mutator>::value(const_cast<subbase&>(property.value), argument))>::type { return request::set_modulo<mutator>::value(const_cast<subbase&>(property.value), argument); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator %=(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(request::set_modulo<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))) -> typename std::enable_if<detect::modulo_operator<subbaseA, subbaseB>::value, decltype(request::set_modulo<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))>::type { return request::set_modulo<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value); }

    template <typename subbase, typename type> constexpr friend inline auto operator *=(property<subbase> const& property, type&& argument) noexcept(noexcept(request::set_multiply<mutator>::value(const_cast<subbase&>(property.value), argument))) -> typename std::enable_if<detect::multiply_operator<subbase, type>::value, decltype(request::set_multiply<mutator>::value(const_cast<subbase&>(property.value), argument))>::type { return request::set_multiply<mutator>::value(const_cast<subbase&>(property.value), argument); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator *=(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(request::set_multiply<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))) -> typename std::enable_if<detect::multiply_operator<subbaseA, subbaseB>::value, decltype(request::set_multiply<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))>::type { return request::set_multiply<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value); }

    template <typename subbase, typename type> constexpr friend inline auto operator -=(property<subbase> const& property, type&& argument) noexcept(noexcept(request::set_subtract<mutator>::value(const_cast<subbase&>(property.value), argument))) -> typename std::enable_if<detect::subtract_operator<subbase, type>::value, decltype(request::set_subtract<mutator>::value(const_cast<subbase&>(property.value), argument))>::type { return request::set_subtract<mutator>::value(const_cast<subbase&>(property.value), argument); }
    template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator -=(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(request::set_subtract<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))) -> typename std::enable_if<detect::subtract_operator<subbaseA, subbaseB>::value, decltype(request::set_subtract<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value))>::type { return request::set_subtract<mutator>::value(const_cast<subbaseA&>(propertyA.value), propertyB.value); }

    constexpr inline operator base&() noexcept { return accessor::get(this->value); }
    constexpr inline operator base const&() const noexcept { return accessor::get(const_cast<base&>(this->value)); }

    template <typename type>
    constexpr inline operator type() const noexcept { return accessor::get(const_cast<base&>(this->value)); }

    #ifdef __cpp_impl_coroutine
      template <typename subbase> /* constexpr */ friend inline auto operator co_await(property<subbase> const& property) noexcept { co_return accessor::get(const_cast<base&>(property.value)); }
    #endif

    #ifdef __cpp_impl_three_way_comparison
      template <typename subbase, typename type> constexpr friend inline auto operator <=>(property<subbase> const& property, type&& argument) noexcept(noexcept(accessor::get(const_cast<subbase&>(property.value)) <=> argument)) -> decltype(accessor::get(const_cast<subbase&>(property.value)) <=> argument) { return accessor::get(const_cast<subbase&>(property.value)) <=> argument; }
      template <typename subbase, typename type> constexpr friend inline auto operator <=>(type&& argument, property<subbase> const& property) noexcept(noexcept(argument <=> accessor::get(const_cast<subbase&>(property.value)))) -> decltype(argument <=> accessor::get(const_cast<subbase&>(property.value))) { return argument <=> accessor::get(const_cast<subbase&>(property.value)); }
      template <typename subbaseA, typename subbaseB> constexpr friend inline auto operator <=>(property<subbaseA> const& propertyA, property<subbaseB> const& propertyB) noexcept(noexcept(accessor::get(const_cast<subbaseA&>(propertyA.value)) <=> accessor::get(const_cast<subbaseB&>(propertyB.value)))) -> decltype(accessor::get(const_cast<subbaseA&>(propertyA.value)) <=> accessor::get(const_cast<subbaseB&>(propertyB.value))) { return accessor::get(const_cast<subbaseA&>(propertyA.value)) <=> accessor::get(const_cast<subbaseB&>(propertyB.value)); }
    #endif
};

template <typename base, class accessor, class mutator>
struct property<property<base>, accessor, mutator>;

/* Main */
struct Number {
  int value;
  
  Number(int const = 0) : value(42) {}
  
  operator int() const { return value; }
  int& operator ++() { return ++value; }
  int& operator = (int const) { return value; }
  int& operator +=(int const) { return value; }
};

int main() {
  Number a;
  property<Number> b;

  // ...
  std::printf("[Number]: %i" "\r\n", +Number{});
  std::printf("[Number]: %i" "\r\n", Number{} + 0);
  std::printf("[Number]: %i" "\r\n", 0 + Number{});
  std::printf("[Number]: %i" "\r\n", Number{}.operator int());
  std::printf("[Number]: %i" "\r\n", static_cast<int>(Number{}));
  std::printf("[Number]: %i" "\r\n", ++a);
  std::printf("[Number]: %i" "\r\n", a += 1);
  std::printf("[Number]: %lu" "\r\n", static_cast<unsigned long>(sizeof(a)));

  std::printf("[property<...>]: %i" "\r\n", +property<Number>{});
  std::printf("[property<...>]: %i" "\r\n", property<Number>{} + 0);
  std::printf("[property<...>]: %i" "\r\n", 0 + property<Number>{});
  std::printf("[property<...>]: %i" "\r\n", property<Number>{}.operator int());
  std::printf("[property<...>]: %i" "\r\n", static_cast<int>(property<Number>{}));
  std::printf("[property<...>]: %i" "\r\n", ++b);
  std::printf("[property<...>]: %i" "\r\n", b += 1);
  std::printf("[property<...>]: %lu" "\r\n", static_cast<unsigned long>(sizeof(b)));
}
