/* Import */
// : C++ Standard Library
#include <cstddef> // C Standard Definition
#include <cstdlib> // C Standard Library
#include <type_traits> // Type Traits
#include <utility> // Utility

// : Windows
#include <windef.h> // Windows Definitions
#include <winuser.h> // Windows User

/* Definition > ... */
#define __MAIN__ int main(int const, char const* const[])
#define __WINDOWS__MAIN__ int WinMain(HINSTANCE const, HINSTANCE const, LPSTR const, int const)
#define __WINDOWS_DLL__MAIN__ BOOL WINAPI DllMain(HINSTANCE const, DWORD const, LPVOID const)

/* Namespace > Standard Library --- WARN (Lapys) -> Extending the standard library is undefined. */
namespace std {
    template <typename> struct alias;
    template <bool, typename> struct alias_implementation;
    template <typename> struct base_of;
    template <class, typename> struct data_accessor;
    template <bool, class, typename> struct data_member;
    template <class, typename> struct data_mutator;
    template <class, typename> struct function_accessor;
    template <class, typename> struct function_member;
    template <class, typename> struct function_mutator;
    template <typename> struct is_array_pointer;
    template <typename> struct is_array_reference;
    template <typename> struct is_base;
    template <typename> struct is_function_pointer;
    template <typename> struct is_function_reference;
    template <typename> struct is_inheritable;
    template <typename> struct is_noexcept;

    #if __cplusplus && __cplusplus < 201402L
        template <typename> struct is_final;
    #endif
}

namespace std {
    // ...
    template <typename type>
    struct alias : public alias_implementation<type, std::is_inheritable<type>::value> {
        public:
            template <typename = type> constexpr auto operator *(void) const noexcept -> decltype(*(this -> valueOf())) { return *(this -> valueOf()); }
            template <typename subtype, typename = type> constexpr auto operator =(subtype value) const noexcept -> decltype(this -> valueOf() = value) { return this -> valueOf() = value; }
            template <typename subtype, typename = type> constexpr auto operator +=(subtype value) const noexcept -> decltype(this -> valueOf() += value) { return this -> valueOf() += value; }
            template <typename subtype, typename = type> constexpr auto operator -=(subtype value) const noexcept -> decltype(this -> valueOf() -= value) { return this -> valueOf() -= value; }
            template <typename subtype, typename = type> constexpr auto operator *=(subtype value) const noexcept -> decltype(this -> valueOf() *= value) { return this -> valueOf() *= value; }
            template <typename subtype, typename = type> constexpr auto operator /=(subtype value) const noexcept -> decltype(this -> valueOf() /= value) { return this -> valueOf() /= value; }
            template <typename subtype, typename = type> constexpr auto operator %=(subtype value) const noexcept -> decltype(this -> valueOf() %= value) { return this -> valueOf() %= value; }
            template <typename subtype, typename = type> constexpr auto operator &=(subtype value) const noexcept -> decltype(this -> valueOf() &= value) { return this -> valueOf() &= value; }
            template <typename subtype, typename = type> constexpr auto operator |=(subtype value) const noexcept -> decltype(this -> valueOf() |= value) { return this -> valueOf() |= value; }
            template <typename subtype, typename = type> constexpr auto operator ^=(subtype value) const noexcept -> decltype(this -> valueOf() ^= value) { return this -> valueOf() ^= value; }
            template <typename subtype, typename = type> constexpr auto operator <<=(subtype value) const noexcept -> decltype(this -> valueOf() <<= value) { return this -> valueOf() <<= value; }
            template <typename subtype, typename = type> constexpr auto operator >>=(subtype value) const noexcept -> decltype(this -> valueOf() >>= value) { return this -> valueOf() >>= value; }
            template <typename = type> constexpr auto operator ++(void) const noexcept -> decltype(++(this -> valueOf())) { return ++(this -> valueOf()); }
            template <typename = type> constexpr auto operator ++(int const) const noexcept -> decltype((this -> valueOf())++) { return (this -> valueOf())++; }
            template <typename = type> constexpr auto operator --(void) const noexcept -> decltype(--(this -> valueOf())) { return --(this -> valueOf()); }
            template <typename = type> inline auto operator --(int const) noexcept -> decltype((this -> valueOf())--) { return (this -> valueOf())--; }
            template <typename = type> constexpr auto operator --(int const) const noexcept -> decltype((this -> valueOf())--) { return (this -> valueOf())--; }
    };
      // ...
      template <typename type>
      struct alias_implementation<type, false> {
          protected:
              type value;
              constexpr inline type& valueOf(void) const noexcept { return const_cast<type&>(this -> value); }

          public:
              constexpr inline data_member(type const& argument) noexcept(std::is_base<type>::value) : value{argument} {}
              template <typename... types> constexpr inline data_member(types... arguments) noexcept(std::is_base<type>::value) : value{std::forward<types>(arguments)...} {}
      };

      template <typename type>
      struct alias_implementation<type, true> : public type {
          protected: constexpr inline type& valueOf(void) const noexcept { return const_cast<type&>(*this); }
          public: template <typename... types> constexpr inline alias_data(types... arguments) noexcept : type{std::forward<types>(arguments)...} {}
      };

    // ...
    template <typename type>
    struct is_inheritable : public std::conditional<std::is_base<type>::value || false == std::is_final<type>::value, std::true_type, std::false_type>::type {};

  template <class object_t, typename member_t>
  struct data_member<true, object_t, member_t> {
    public:
      inline operator member_t&(void) noexcept { return this -> valueOf(); }
      constexpr operator member_t const&(void) const noexcept { return this -> valueOf(); }
  };

    template <typename base_t>
    struct alias final {
        private: base_t value;
        public:
            constexpr explicit alias(base_t const& argument) noexcept(std::is_noexcept<base_t>::value) : value{argument} {}
            template <typename... types> constexpr explicit alias(types... arguments) noexcept(std::is_noexcept<base_t>::value) : value{std::forward<types>(arguments)...} {}

            template <typename = base_t> constexpr alias operator +(void) const noexcept { return +(this -> value); }
            template <typename = base_t> constexpr alias operator -(void) const noexcept { return -(this -> value); }
            template <typename type = base_t> constexpr typename std::base_of<type>::type& operator *(void) const noexcept { return *(this -> value); }
            template <typename type> inline alias& operator =(type const& value) { this -> value = value; return *this; }
            template <typename type> inline alias& operator +=(type const& value) { this -> value += value; return *this; }
            template <typename type> inline alias& operator -=(type const& value) { this -> value -= value; return *this; }
            template <typename type> inline alias& operator *=(type const& value) { this -> value *= value; return *this; }
            template <typename type> inline alias& operator /=(type const& value) { this -> value /= value; return *this; }
            template <typename type> inline alias& operator %=(type const& value) { this -> value %= value; return *this; }
            template <typename type> inline alias& operator &=(type const& value) { this -> value &= value; return *this; }
            template <typename type> inline alias& operator |=(type const& value) { this -> value |= value; return *this; }
            template <typename type> inline alias& operator ^=(type const& value) { this -> value ^= value; return *this; }
            template <typename type> inline alias& operator <<=(type const& value) { this -> value <<= value; return *this; }
            template <typename type> inline alias& operator >>=(type const& value) { this -> value >>= value; return *this; }
            template <typename = base_t> inline alias& operator ++(void) { ++(this -> value); return *this; }
            template <typename = base_t> inline alias& operator ++(int const) { (this -> value)++; return *this; }
            template <typename = base_t> inline alias& operator --(void) { --(this -> value); return *this; }
            template <typename = base_t> inline alias& operator --(int const) { (this -> value)--; return *this; }
            template <typename index_t, typename type = base_t> constexpr inline typename std::enable_if<std::is_array_pointer<type>::value, typename std::base_of<type>::type&>::type operator [](index_t const& index) const noexcept { return const_cast<typename std::base_of<type>::type&>((*(this -> value))[index]); }
            template <typename index_t, typename type = base_t> constexpr inline typename std::enable_if<std::is_array<type>::value || std::is_array_reference<type>::value, typename std::base_of<type>::type&>::type operator [](index_t const& index) const noexcept { return const_cast<typename std::base_of<type>::type&>(this -> value[index]); }
            template <typename type = base_t, typename... types> inline typename std::enable_if<std::is_function_pointer<type>::value, typename std::base_of<type>::type>::type operator()(types... arguments) const noexcept(std::is_noexcept<type>::value) { return (*(this -> value))(std::forward<types>(arguments)...); }
            template <typename type = base_t, typename... types> inline typename std::enable_if<std::is_function<type>::value || std::is_function_reference<type>::value, typename std::base_of<type>::type>::type operator()(types... arguments) const noexcept(std::is_noexcept<type>::value) { return this -> value(std::forward<types>(arguments)...); }
            constexpr explicit operator base_t&(void) noexcept { return this -> value; }
            constexpr explicit operator base_t const&(void) const noexcept { return this -> value; }
    };

    template <typename type_t> struct base_of final : public std::enable_if<std::is_enum<type_t>::value, typename std::underlying_type<type_t>::type> {};
    template <typename type_t> struct base_of<type_t*> final { typedef type_t type; };
    template <typename type_t> struct base_of<type_t&> final { typedef type_t type; };
    template <typename type_t, std::size_t length> struct base_of<type_t [length]> final { typedef type_t type; };
    template <typename type_t, std::size_t length> struct base_of<type_t (&)[length]> final { typedef type_t type; };
    template <typename type_t, std::size_t length> struct base_of<type_t (*)[length]> final { typedef type_t type; };
    template <typename return_t, typename... types> struct base_of<return_t (types...)> final { typedef return_t type; };
    template <typename return_t, typename... types> struct base_of<return_t (&)(types...)> final { typedef return_t type; };
    template <typename return_t, typename... types> struct base_of<return_t (&)(types..., ...)> final { typedef return_t type; };
    template <typename return_t, typename... types> struct base_of<return_t (*)(types...)> final { typedef return_t type; };
    template <typename return_t, typename... types> struct base_of<return_t (*)(types..., ...)> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...)> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) const> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) const volatile> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) volatile> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...)&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) const&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) const volatile&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) volatile&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...)&&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) const&&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) const volatile&&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) volatile&&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...)&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...) const&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...) const volatile&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...) volatile&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...)&&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...) const&&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...) const volatile&&> final { typedef return_t type; };
    template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...) volatile&&> final { typedef return_t type; };

    #if defined(__cplusplus) && __cplusplus > 201402L
      template <typename return_t, typename... types> struct base_of<return_t (types...) noexcept> final { typedef return_t type; };
      template <typename return_t, typename... types> struct base_of<return_t (&)(types...) noexcept> final { typedef return_t type; };
      template <typename return_t, typename... types> struct base_of<return_t (&)(types..., ...) noexcept> final { typedef return_t type; };
      template <typename return_t, typename... types> struct base_of<return_t (*)(types...) noexcept> final { typedef return_t type; };
      template <typename return_t, typename... types> struct base_of<return_t (*)(types..., ...) noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) const noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) const volatile noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) volatile noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) const& noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) const volatile& noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) volatile& noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) const&& noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) const volatile&& noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types...) volatile&& noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...) const& noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...) const volatile& noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...) volatile& noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...) const&& noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...) const volatile&& noexcept> final { typedef return_t type; };
      template <class object_t, typename return_t, typename... types> struct base_of<return_t (object_t::*)(types..., ...) volatile&& noexcept> final { typedef return_t type; };
    #endif

  template <class object_t, typename member_t>
  struct data_member<false, object_t, member_t> : public member_t {
    friend object_t;

    protected:
      inline member_t& valueOf(void) noexcept { return *this; }
      constexpr inline member_t const& valueOf(void) const noexcept { return *this; }

    public:
      template <typename... types> constexpr inline data_member(types... arguments) : member_t{std::forward<types>(arguments)...} {}
  };

  template <class object_t, typename member_t>
  struct data_member<true, object_t, member_t> {
    friend object_t;

    protected:
      member_t value;

      inline member_t& valueOf(void) noexcept { return this -> value; }
      constexpr inline member_t const& valueOf(void) const noexcept { return this -> value; }

    public:
      template <typename type = member_t, typename std::enable_if<true == std::is_base<type>::value, signed int>::type = 0> constexpr inline data_member(member_t const& argument) noexcept : value{argument} {}
      template <typename type = member_t, typename std::enable_if<true == std::is_base<type>::value, signed int>::type = 0, typename... types> constexpr inline data_member(types... arguments) noexcept : value{std::forward<types>(arguments)...} {}

      template <typename type = member_t, typename std::enable_if<false == std::is_base<type>::value, unsigned int>::type = 0> constexpr inline data_member(member_t const& argument) : value{argument} {}
      template <typename type = member_t, typename std::enable_if<false == std::is_base<type>::value, unsigned int>::type = 0, typename... types> constexpr inline data_member(types... arguments) : value{std::forward<types>(arguments)...} {}

      // ...
      template <typename = member_t> constexpr member_t operator +(void) const noexcept { return +(this -> valueOf()); }
      template <typename = member_t> constexpr member_t operator -(void) const noexcept { return -(this -> valueOf()); }
      template <typename type = member_t> constexpr member_t<object_t, typename std::base_of<type>::type&> operator *(void) const noexcept { return *(this -> valueOf()); }
      template <typename type = member_t> inline member_t& operator =(type const& value) { return this -> valueOf() = value, *this; }
      template <typename type = member_t> inline member_t& operator +=(type const& value) { return this -> valueOf() += value, *this; }
      template <typename type = member_t> inline member_t& operator -=(type const& value) { return this -> valueOf() -= value, *this; }
      template <typename type = member_t> inline member_t& operator *=(type const& value) { return this -> valueOf() *= value, *this; }
      template <typename type = member_t> inline member_t& operator /=(type const& value) { return this -> valueOf() /= value, *this; }
      template <typename type = member_t> inline member_t& operator %=(type const& value) { return this -> valueOf() %= value, *this; }
      template <typename type = member_t> inline member_t& operator &=(type const& value) { return this -> valueOf() &= value, *this; }
      template <typename type = member_t> inline member_t& operator |=(type const& value) { return this -> valueOf() |= value, *this; }
      template <typename type = member_t> inline member_t& operator ^=(type const& value) { return this -> valueOf() ^= value, *this; }
      template <typename type = member_t> inline member_t& operator <<=(type const& value) { return this -> valueOf() <<= value, *this; }
      template <typename type = member_t> inline member_t& operator >>=(type const& value) { return this -> valueOf() >>= value, *this; }
      template <typename type = member_t> inline member_t& operator ++(void) { return ++(this -> valueOf()), *this; }
      template <typename type = member_t> inline member_t& operator ++(int const) { return (this -> valueOf())++, *this; }
      template <typename type = member_t> inline member_t& operator --(void) { return --(this -> valueOf()), *this; }
      template <typename type = member_t> inline member_t& operator --(int const) { return (this -> valueOf())--, *this; }

      inline operator member_t&(void) noexcept { return this -> valueOf(); }
      constexpr operator member_t const&(void) const noexcept { return this -> valueOf(); }
  };
    template <class object_t, typename member_t>
    struct data_accessor final : public std::data_member<std::is_base<member_t>::value || std::is_final<member_t>::value, object_t, member_t> { friend object_t;
      public:
        using data_member<std::is_base<member_t>::value || std::is_final<member_t>::value, object_t, member_t>::data_member;

        template <typename = member_t> constexpr data_accessor operator +(void) const noexcept { return +(this -> valueOf()); }
        template <typename = member_t> constexpr data_accessor operator -(void) const noexcept { return -(this -> valueOf()); }
        template <typename type = member_t> constexpr typename std::remove_const<typename std::base_of<type>::type>::type const& operator *(void) const noexcept { return const_cast<typename std::base_of<type>::type&>(*(this -> valueOf())); }
        template <typename index_t, typename type = member_t> constexpr typename std::enable_if<std::is_array_pointer<type>::value, typename std::remove_const<typename std::base_of<type>::type> const&>::type operator [](index_t const& index) const noexcept { return const_cast<typename std::base_of<type>::type&>((*(this -> valueOf()))[index]); }
        template <typename index_t, typename type = member_t> constexpr typename std::enable_if<std::is_array<type>::value || std::is_array_reference<type>::value, typename std::remove_const<typename std::base_of<type>::type>::type const&>::type operator [](index_t const& index) const noexcept { return const_cast<typename std::base_of<type>::type&>(this -> valueOf()[index]); }
        template <typename type = member_t, typename... types> inline typename std::enable_if<std::is_function_pointer<type>::value, typename std::base_of<type>::type>::type operator ()(types... arguments) const noexcept(std::is_noexcept<type>::value) { return (*(this -> valueOf()))(std::forward<types>(arguments)...); }
        template <typename type = member_t, typename... types> inline typename std::enable_if<std::is_function<type>::value || std::is_function_reference<type>::value, typename std::base_of<type>::type>::type operator ()(types... arguments) const noexcept(std::is_noexcept<type>::value) { return this -> valueOf()(std::forward<types>(arguments)...); }
        constexpr operator member_t const&(void) const noexcept { return this -> valueOf(); }
    };

    template <class object_t, typename member_t>
    struct data_mutator final : public std::data_member<std::is_base<member_t>::value || std::is_final<member_t>::value, object_t, member_t> { friend object_t;
      private:
        inline operator member_t&(void) noexcept { return this -> valueOf(); }
        constexpr operator member_t const&(void) const noexcept { return this -> valueOf(); }

      public:
        using data_member<std::is_base<member_t>::value || std::is_final<member_t>::value, object_t, member_t>::data_member;

        template <typename = member_t> constexpr data_mutator operator +(void) const noexcept { return +(this -> valueOf()); }
        template <typename = member_t> constexpr data_mutator operator -(void) const noexcept { return -(this -> valueOf()); }
        template <typename type = member_t> constexpr data_mutator<object_t, typename std::base_of<type>::type&> operator *(void) const noexcept { return *(this -> valueOf()); }
        template <typename type = member_t> inline data_mutator& operator =(type const& value) { this -> valueOf() = value; return *this; }
        template <typename type = member_t> inline data_mutator& operator +=(type const& value) { this -> valueOf() += value; return *this; }
        template <typename type = member_t> inline data_mutator& operator -=(type const& value) { this -> valueOf() -= value; return *this; }
        template <typename type = member_t> inline data_mutator& operator *=(type const& value) { this -> valueOf() *= value; return *this; }
        template <typename type = member_t> inline data_mutator& operator /=(type const& value) { this -> valueOf() /= value; return *this; }
        template <typename type = member_t> inline data_mutator& operator %=(type const& value) { this -> valueOf() %= value; return *this; }
        template <typename type = member_t> inline data_mutator& operator &=(type const& value) { this -> valueOf() &= value; return *this; }
        template <typename type = member_t> inline data_mutator& operator |=(type const& value) { this -> valueOf() |= value; return *this; }
        template <typename type = member_t> inline data_mutator& operator ^=(type const& value) { this -> valueOf() ^= value; return *this; }
        template <typename type = member_t> inline data_mutator& operator <<=(type const& value) { this -> valueOf() <<= value; return *this; }
        template <typename type = member_t> inline data_mutator& operator >>=(type const& value) { this -> valueOf() >>= value; return *this; }
        template <typename type = member_t> inline data_mutator& operator ++(void) { ++(this -> valueOf()); return *this; }
        template <typename type = member_t> inline data_mutator& operator ++(int const) { (this -> valueOf())++; return *this; }
        template <typename type = member_t> inline data_mutator& operator --(void) { --(this -> valueOf()); return *this; }
        template <typename type = member_t> inline data_mutator& operator --(int const) { (this -> valueOf())--; return *this; }
        template <typename index_t, typename type = member_t> constexpr typename std::enable_if<std::is_array_pointer<type>::value, data_mutator<object_t, typename std::base_of<type>::type&>>::type operator [](index_t const& index) const noexcept { return const_cast<typename std::base_of<type>::type&>((*(this -> valueOf()))[index]); }
        template <typename index_t, typename type = member_t> constexpr typename std::enable_if<std::is_array<type>::value || std::is_array_reference<type>::value, data_mutator<object_t, typename std::base_of<type>::type&>>::type operator [](index_t const& index) const noexcept { return const_cast<typename std::base_of<type>::type&>(this -> valueOf()[index]); }
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

/* Definition > ... */
class Application;
class Utility;

/* Class */
/* : Utility */
class Utility final {
    // [...]
    public:
        // Definition > ...
        class Memory;
        class String;
};

/* : Application */
class Application final {
    /* ... */
    friend __MAIN__;
    friend __WINDOWS__MAIN__;
    friend __WINDOWS_DLL__MAIN__;

    // [...]
    public:
        // Definition > ...
        class Error;
        class Window;

    // [...]
    private:
        std::data_accessor<Application, Window const*> primaryWindow;
        std::data_member<Application, char const*> title;
};

/* Class > Application */
class Application final {
    // [...]
    private:
        /* Definition > ... */
        static Window const PRIMARY_WINDOW;
        int exitCode;

    // [...]
    public:
        /* Definition > ... */
        std::data_accessor<Application, Window const*> primaryWindow;
        char const *&title;

        /* [Constructor] */
        constexpr Application(void) noexcept;

        /* Method > ... */
        void Initiate (void); bool Initiate (int...);
        void Reset    (void); void Reset    (int...);
        void Update   (void); bool Update   (int...);
        void Terminate(void); void Terminate(int...);
};
    /* Error */
    class Application::Error final { public:
        enum class Result : signed char { FAILED = -1, UNIMPLEMENTED = -2, NONE = 0x0, FALSIFIED = 1, FORCED = 0x7FFFFFFF };

        std::data_accessor<Error, char const*> const message;
        constexpr Error(char const message[]) noexcept : message{message} {}
    };

    /* Window */
    class Application::Window final {
        friend Application;

        private: static inline PROCEDURE(HWND const, UINT const, WPARAM const, LPARAM const);
        public:
            std::data_accessor<Window, HWND> handle;
            std::data_accessor<Window, LONG> height;
            std::data_accessor<Window, bool> isFocused;
            std::data_accessor<Window, char const*> title;
            std::data_accessor<Window, LONG> width;

            constexpr Window(SIZE const size, char const title[]) noexcept : handle{NULL}, height{size.cy}, isFocused{false}, title{title}, width{size.cx} {}
            inline ~Window(void) {}
    };

/* Definition > ... */
typedef Application::Error Error;
typedef Application::Window Window;

/* Modification > Application */
    // Primary Window
    Window const Application::PRIMARY_WINDOW = Window {};

    // [Constructor]
    constexpr Application::Application(void) noexcept : exitCode{EXIT_SUCCESS}, primaryWindow{&Application::PRIMARY_WINDOW}, title{Application::PRIMARY_WINDOW.title} {}

    // Phase
    // : Initiate
    void Application::Initiate(void) {
        // Logic
        if (Application::Initiate(EXIT_SUCCESS)) {
        }
    }

    // : Reset
    void Application::Reset(void) {}

    // : Update
    void Application::Update(void) {}

    // : Terminate
    void Application::Terminate(void) {
        Application::Terminate(EXIT_SUCCESS);
    }

/* Global > ... */
Application APPLICATION = Application {};

/* Main */
__MAIN__ {
    /* ... */
    Application::Initiate();
    Application::Terminate();

    // Return
    return EXIT_SUCCESS;
}
