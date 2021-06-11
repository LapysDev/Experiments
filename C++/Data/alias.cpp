#include <cstddef>
#include <type_traits>
#include <utility>

/* Namespace > Standard Library --- WARN (Lapys) -> Extending the standard library is undefined. */
namespace std {
  template <typename> struct alias_t;
  template <typename> struct base_of_t;

  template <typename, typename> struct immutable_accessor;
  template <typename, typename> struct inaccessible_mutator;
  template <bool, typename, typename> struct member_type;

  template <typename> struct is_array_pointer;
  template <typename> struct is_array_reference;
  template <typename> struct is_base;
  template <typename> struct is_function_pointer;
  template <typename> struct is_function_reference;
  template <typename> struct is_noexcept;
  #if __cplusplus && __cplusplus < 201402L
    template <typename> struct is_final;
  #endif
}

namespace std {
  template <typename base_t>
  struct alias_t final {
    private: base_t value;
    public:
      constexpr explicit alias_t(base_t const& argument) noexcept(std::is_noexcept<base_t>::value) : value{argument} {}
      template <typename... types> constexpr explicit alias_t(types... arguments) noexcept(std::is_noexcept<base_t>::value) : value{std::forward<types>(arguments)...} {}

      template <typename = base_t> constexpr alias_t operator +(void) const noexcept { return +(this -> value); }
      template <typename = base_t> constexpr alias_t operator -(void) const noexcept { return -(this -> value); }
      template <typename type = base_t> constexpr typename std::base_of_t<type>::type& operator *(void) const noexcept { return *(this -> value); }
      template <typename type> inline alias_t& operator =(type const& value) { this -> value = value; return *this; }
      template <typename type> inline alias_t& operator +=(type const& value) { this -> value += value; return *this; }
      template <typename type> inline alias_t& operator -=(type const& value) { this -> value -= value; return *this; }
      template <typename type> inline alias_t& operator *=(type const& value) { this -> value *= value; return *this; }
      template <typename type> inline alias_t& operator /=(type const& value) { this -> value /= value; return *this; }
      template <typename type> inline alias_t& operator %=(type const& value) { this -> value %= value; return *this; }
      template <typename type> inline alias_t& operator &=(type const& value) { this -> value &= value; return *this; }
      template <typename type> inline alias_t& operator |=(type const& value) { this -> value |= value; return *this; }
      template <typename type> inline alias_t& operator ^=(type const& value) { this -> value ^= value; return *this; }
      template <typename type> inline alias_t& operator <<=(type const& value) { this -> value <<= value; return *this; }
      template <typename type> inline alias_t& operator >>=(type const& value) { this -> value >>= value; return *this; }
      template <typename = base_t> inline alias_t& operator ++(void) { ++(this -> value); return *this; }
      template <typename = base_t> inline alias_t& operator ++(int const) { (this -> value)++; return *this; }
      template <typename = base_t> inline alias_t& operator --(void) { --(this -> value); return *this; }
      template <typename = base_t> inline alias_t& operator --(int const) { (this -> value)--; return *this; }
      template <typename index_t, typename type = base_t> constexpr inline typename std::enable_if<std::is_array_pointer<type>::value, typename std::base_of_t<type>::type&>::type operator [](index_t const& index) const noexcept { return const_cast<typename std::base_of_t<type>::type&>((*(this -> value))[index]); }
      template <typename index_t, typename type = base_t> constexpr inline typename std::enable_if<std::is_array<type>::value || std::is_array_reference<type>::value, typename std::base_of_t<type>::type&>::type operator [](index_t const& index) const noexcept { return const_cast<typename std::base_of_t<type>::type&>(this -> value[index]); }
      template <typename type = base_t, typename... types> inline typename std::enable_if<std::is_function_pointer<type>::value, typename std::base_of_t<type>::type>::type operator()(types... arguments) const noexcept(std::is_noexcept<type>::value) { return (*(this -> value))(std::forward<types>(arguments)...); }
      template <typename type = base_t, typename... types> inline typename std::enable_if<std::is_function<type>::value || std::is_function_reference<type>::value, typename std::base_of_t<type>::type>::type operator()(types... arguments) const noexcept(std::is_noexcept<type>::value) { return this -> value(std::forward<types>(arguments)...); }
      constexpr explicit operator base_t&(void) noexcept { return this -> value; }
      constexpr explicit operator base_t const&(void) const noexcept { return this -> value; }
  };

  template <typename type_t> struct base_of_t final : public std::enable_if<std::is_enum<type_t>::value, typename std::underlying_type<type_t>::type> {};
  template <typename type_t> struct base_of_t<type_t*> final { typedef type_t type; };
  template <typename type_t> struct base_of_t<type_t&> final { typedef type_t type; };
  template <typename type_t, std::size_t length> struct base_of_t<type_t [length]> final { typedef type_t type; };
  template <typename type_t, std::size_t length> struct base_of_t<type_t (&)[length]> final { typedef type_t type; };
  template <typename type_t, std::size_t length> struct base_of_t<type_t (*)[length]> final { typedef type_t type; };
  template <typename return_t, typename... types> struct base_of_t<return_t (types...)> final { typedef return_t type; };
  template <typename return_t, typename... types> struct base_of_t<return_t (&)(types...)> final { typedef return_t type; };
  template <typename return_t, typename... types> struct base_of_t<return_t (&)(types..., ...)> final { typedef return_t type; };
  template <typename return_t, typename... types> struct base_of_t<return_t (*)(types...)> final { typedef return_t type; };
  template <typename return_t, typename... types> struct base_of_t<return_t (*)(types..., ...)> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...)> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) const> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) const volatile> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) volatile> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...)&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) const&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) const volatile&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) volatile&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...)&&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) const&&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) const volatile&&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) volatile&&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...)&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...) const&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...) const volatile&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...) volatile&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...)&&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...) const&&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...) const volatile&&> final { typedef return_t type; };
  template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...) volatile&&> final { typedef return_t type; };

  #if defined(__cplusplus) && __cplusplus > 201402L
    template <typename return_t, typename... types> struct base_of_t<return_t (types...) noexcept> final { typedef return_t type; };
    template <typename return_t, typename... types> struct base_of_t<return_t (&)(types...) noexcept> final { typedef return_t type; };
    template <typename return_t, typename... types> struct base_of_t<return_t (&)(types..., ...) noexcept> final { typedef return_t type; };
    template <typename return_t, typename... types> struct base_of_t<return_t (*)(types...) noexcept> final { typedef return_t type; };
    template <typename return_t, typename... types> struct base_of_t<return_t (*)(types..., ...) noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) const noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) const volatile noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) volatile noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) const& noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) const volatile& noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) volatile& noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) const&& noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) const volatile&& noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types...) volatile&& noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...) const& noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...) const volatile& noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...) volatile& noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...) const&& noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...) const volatile&& noexcept> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of_t<return_t (object_t::*)(types..., ...) volatile&& noexcept> final { typedef return_t type; };
  #endif

  template <class object_t, typename member_t>
  struct member_type<false, object_t, member_t> : public member_t {
    friend object_t;

    public:
      template <typename... types> constexpr inline member_type(types... arguments) : member_t{std::forward<types>(arguments)...} {}

      inline member_t& valueOf(void) noexcept { return *this; }
      constexpr inline member_t const& valueOf(void) const noexcept { return *this; }
  };

  template <class object_t, typename member_t>
  struct member_type<true, object_t, member_t> {
    friend object_t;

    protected: member_t value;
    public:
      template <typename type = member_t, typename std::enable_if<true == std::is_base<type>::value, signed int>::type = 0> constexpr inline member_type(member_t const& argument) noexcept : value{argument} {}
      template <typename type = member_t, typename std::enable_if<true == std::is_base<type>::value, signed int>::type = 0, typename... types> constexpr inline member_type(types... arguments) noexcept : value{std::forward<types>(arguments)...} {}

      template <typename type = member_t, typename std::enable_if<false == std::is_base<type>::value, unsigned int>::type = 0> constexpr inline member_type(member_t const& argument) : value{argument} {}
      template <typename type = member_t, typename std::enable_if<false == std::is_base<type>::value, unsigned int>::type = 0, typename... types> constexpr inline member_type(types... arguments) : value{std::forward<types>(arguments)...} {}

      inline member_t& valueOf(void) noexcept { return this -> value; }
      constexpr inline member_t const& valueOf(void) const noexcept { return this -> value; }
  };
    template <class object_t, typename member_t>
    struct immutable_accessor final : public std::member_type<std::is_base<member_t>::value || std::is_final<member_t>::value, object_t, member_t> { friend object_t;
      public:
        using member_type<std::is_base<member_t>::value || std::is_final<member_t>::value, object_t, member_t>::member_type;

        template <typename = member_t> constexpr immutable_accessor operator +(void) const noexcept { return +(this -> valueOf()); }
        template <typename = member_t> constexpr immutable_accessor operator -(void) const noexcept { return -(this -> valueOf()); }
        template <typename type = member_t> constexpr typename std::remove_const<typename std::base_of_t<type>::type>::type const& operator *(void) const noexcept { return const_cast<typename std::base_of_t<type>::type&>(*(this -> valueOf())); }
        template <typename index_t, typename type = member_t> constexpr typename std::enable_if<std::is_array_pointer<type>::value, typename std::remove_const<typename std::base_of_t<type>::type> const&>::type operator [](index_t const& index) const noexcept { return const_cast<typename std::base_of_t<type>::type&>((*(this -> valueOf()))[index]); }
        template <typename index_t, typename type = member_t> constexpr typename std::enable_if<std::is_array<type>::value || std::is_array_reference<type>::value, typename std::remove_const<typename std::base_of_t<type>::type>::type const&>::type operator [](index_t const& index) const noexcept { return const_cast<typename std::base_of_t<type>::type&>(this -> valueOf()[index]); }
        template <typename type = member_t, typename... types> inline typename std::enable_if<std::is_function_pointer<type>::value, typename std::base_of_t<type>::type>::type operator ()(types... arguments) const noexcept(std::is_noexcept<type>::value) { return (*(this -> valueOf()))(std::forward<types>(arguments)...); }
        template <typename type = member_t, typename... types> inline typename std::enable_if<std::is_function<type>::value || std::is_function_reference<type>::value, typename std::base_of_t<type>::type>::type operator ()(types... arguments) const noexcept(std::is_noexcept<type>::value) { return this -> valueOf()(std::forward<types>(arguments)...); }
        constexpr operator member_t const&(void) const noexcept { return this -> valueOf(); }
    };

    template <class object_t, typename member_t>
    struct inaccessible_mutator final : public std::member_type<std::is_base<member_t>::value || std::is_final<member_t>::value, object_t, member_t> { friend object_t;
      private:
        constexpr operator member_t&(void) noexcept { return this -> valueOf(); }
        constexpr operator member_t const&(void) const noexcept { return this -> valueOf(); }

      public:
        using member_type<std::is_base<member_t>::value || std::is_final<member_t>::value, object_t, member_t>::member_type;

        template <typename = member_t> constexpr inaccessible_mutator operator +(void) const noexcept { return +(this -> valueOf()); }
        template <typename = member_t> constexpr inaccessible_mutator operator -(void) const noexcept { return -(this -> valueOf()); }
        template <typename type = member_t> constexpr immutable_accessor<object_t, typename std::base_of_t<type>::type&> operator *(void) const noexcept { return *(this -> valueOf()); }
        template <typename type = member_t> inline inaccessible_mutator& operator =(type const& value) { this -> valueOf() = value; return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator +=(type const& value) { this -> valueOf() += value; return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator -=(type const& value) { this -> valueOf() -= value; return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator *=(type const& value) { this -> valueOf() *= value; return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator /=(type const& value) { this -> valueOf() /= value; return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator %=(type const& value) { this -> valueOf() %= value; return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator &=(type const& value) { this -> valueOf() &= value; return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator |=(type const& value) { this -> valueOf() |= value; return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator ^=(type const& value) { this -> valueOf() ^= value; return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator <<=(type const& value) { this -> valueOf() <<= value; return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator >>=(type const& value) { this -> valueOf() >>= value; return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator ++(void) { ++(this -> valueOf()); return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator ++(int const) { (this -> valueOf())++; return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator --(void) { --(this -> valueOf()); return *this; }
        template <typename type = member_t> inline inaccessible_mutator& operator --(int const) { (this -> valueOf())--; return *this; }
        template <typename index_t, typename type = member_t> constexpr typename std::enable_if<std::is_array_pointer<type>::value, inaccessible_mutator<object_t, typename std::base_of_t<type>::type&>>::type operator [](index_t const& index) const noexcept { return const_cast<typename std::base_of_t<type>::type&>((*(this -> valueOf()))[index]); }
        template <typename index_t, typename type = member_t> constexpr typename std::enable_if<std::is_array<type>::value || std::is_array_reference<type>::value, inaccessible_mutator<object_t, typename std::base_of_t<type>::type&>>::type operator [](index_t const& index) const noexcept { return const_cast<typename std::base_of_t<type>::type&>(this -> valueOf()[index]); }
    };

  template <typename> struct is_array_pointer final : public std::false_type {};
  template <typename type, std::size_t length> struct is_array_pointer<type (*)[length]> final : public std::true_type {};
  template <typename> struct is_array_reference final : public std::false_type {};
  template <typename type, std::size_t length> struct is_array_reference<type (&)[length]> final : public std::true_type {};

  template <typename type> struct is_base final : public std::conditional<std::is_function<type>::value || std::is_function_reference<type>::value || std::is_pointer<type>::value || std::is_reference<type>::value, std::true_type, std::false_type>::type {};
  template <> struct is_base<char> final : public std::true_type {};
  template <> struct is_base<double> final : public std::true_type {};
  template <> struct is_base<float> final : public std::true_type {};
  template <> struct is_base<int> final : public std::true_type {};
  template <> struct is_base<long> final : public std::true_type {};
  template <> struct is_base<long double> final : public std::true_type {};
  template <> struct is_base<long long> final : public std::true_type {};
  template <> struct is_base<short> final : public std::true_type {};
  template <> struct is_base<signed char> final : public std::true_type {};
  template <> struct is_base<unsigned char> final : public std::true_type {};
  template <> struct is_base<unsigned int> final : public std::true_type {};
  template <> struct is_base<unsigned long> final : public std::true_type {};
  template <> struct is_base<unsigned long long> final : public std::true_type {};
  template <> struct is_base<unsigned short> final : public std::true_type {};
  template <> struct is_base<wchar_t> final : public std::true_type {};
  template <> struct is_base<void> final : public std::true_type {};
  template <typename type, std::size_t length> struct is_base<type [length]> final : public std::conditional<std::is_base<type>::value, std::true_type, std::false_type>::type {};

  #if __cplusplus && __cplusplus < 201402L
    template <typename type> // WARN (Lapys) -> Bound to be incorrect.
    struct is_final final : public std::conditional<
      #if defined(__GNUC__)
        __is_final(type)
      #elif defined(__clang__) || defined(_MSVC_VER)
        #if defined(__is_final)
          __is_final(type)
        #elif defined(__is_sealed)
          __is_sealed(type)
        #endif
      #else
        false
      #endif
      , std::true_type, std::false_type
    >::type {};
  #endif

  template <typename> struct is_function_pointer final : public std::false_type {};
  template <typename return_t, typename... types> struct is_function_pointer<return_t (*)(types...)> final : public std::true_type {};
  template <typename return_t, typename... types> struct is_function_pointer<return_t (*)(types..., ...)> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...)> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) const> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) const volatile> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) volatile> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...)&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) const&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) const volatile&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) volatile&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...)&&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) const&&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) const volatile&&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) volatile&&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...)&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...) const&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...) const volatile&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...) volatile&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...)&&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...) const&&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...) const volatile&&> final : public std::true_type {};
  template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...) volatile&&> final : public std::true_type {};

  #if defined(__cplusplus) && __cplusplus > 201402L
    template <typename return_t, typename... types> struct is_function_pointer<return_t (*)(types...) noexcept> final : public std::true_type {};
    template <typename return_t, typename... types> struct is_function_pointer<return_t (*)(types..., ...) noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) const noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) const volatile noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) volatile noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) const& noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) const volatile& noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) volatile& noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) const&& noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) const volatile&& noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types...) volatile&& noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...) const& noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...) const volatile& noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...) volatile& noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...) const&& noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...) const volatile&& noexcept> final : public std::true_type {};
    template <class object_t, typename return_t, typename... types> struct is_function_pointer<return_t (object_t::*)(types..., ...) volatile&& noexcept> final : public std::true_type {};
  #endif

  template <typename> struct is_function_reference final : public std::false_type {};
  template <typename return_t, typename... types> struct is_function_reference<return_t (&)(types...)> final : public std::true_type {};
  template <typename return_t, typename... types> struct is_function_reference<return_t (&)(types..., ...)> final : public std::true_type {};

  #if defined(__cplusplus) && __cplusplus > 201402L
    template <typename return_t, typename... types> struct is_function_reference<return_t (&)(types...) noexcept> final : public std::true_type {};
    template <typename return_t, typename... types> struct is_function_reference<return_t (&)(types..., ...) noexcept> final : public std::true_type {};
  #endif

  template <typename> struct is_noexcept final : public std::true_type {};
  template <typename return_t, typename... types> struct is_noexcept<return_t (types...)> final : public std::false_type {};
  template <typename return_t, typename... types> struct is_noexcept<return_t (&)(types...)> final : public std::false_type {};
  template <typename return_t, typename... types> struct is_noexcept<return_t (&)(types..., ...)> final : public std::false_type {};
  template <typename return_t, typename... types> struct is_noexcept<return_t (*)(types...)> final : public std::false_type {};
  template <typename return_t, typename... types> struct is_noexcept<return_t (*)(types..., ...)> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types...)> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types...) const> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types...) const volatile> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types...) volatile> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types...)&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types...) const&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types...) const volatile&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types...) volatile&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types...)&&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types...) const&&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types...) const volatile&&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types...) volatile&&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types..., ...)&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types..., ...) const&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types..., ...) const volatile&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types..., ...) volatile&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types..., ...)&&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types..., ...) const&&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types..., ...) const volatile&&> final : public std::false_type {};
  template <class object_t, typename return_t, typename... types> struct is_noexcept<return_t (object_t::*)(types..., ...) volatile&&> final : public std::false_type {};
}
