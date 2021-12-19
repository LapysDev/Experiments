#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <utility>

/* ... */
namespace std {
  namespace {
    template <bool...> struct AND { constexpr static bool value = true; };
    template <bool assertion, bool... assertions> struct AND<assertion, assertions...> { constexpr static bool value = assertion && AND<assertions...>::value; };

    // ...
    template <typename int_t, unsigned long long radix>
    struct COUNT {
      private:
        template <unsigned char control, int_t counted>
        struct evaluate {
          constexpr static std::size_t value = 1u + evaluate<control, counted / radix>::value;
        };

        template <unsigned char control>
        struct evaluate<control, 0> {
          constexpr static std::size_t value = 0u;
        };

      public:
        constexpr static std::size_t value = std::numeric_limits<int_t>::max() ? evaluate<0, std::numeric_limits<int_t>::max()>::value : 1u;
    };

    template <unsigned long long radix>
    struct COUNT<long double, radix>;
  }

  template <typename, std::size_t, class> struct basic_const_string;
  template <std::size_t length, class traits = std::char_traits<char    > > using const_string    = std::basic_const_string<char     const, length, traits>;
  template <std::size_t length, class traits = std::char_traits<char16_t> > using u16const_string = std::basic_const_string<char16_t const, length, traits>;
  template <std::size_t length, class traits = std::char_traits<char32_t> > using u32const_string = std::basic_const_string<char32_t const, length, traits>;
  template <std::size_t length, class traits = std::char_traits<wchar_t > > using wconst_string   = std::basic_const_string<wchar_t  const, length, traits>;

  template <typename char_t, std::size_t length, class traits_t>
  struct basic_const_string {
    template <typename, std::size_t, class>
    friend struct std::basic_const_string;

    private:
      // [alias]
      using type = char_t[length];

      // [data]
      type value;

      // [constructor]
      template <typename type, std::size_t... indexes>
      constexpr basic_const_string(type string[], std::index_sequence<indexes...> const)
        noexcept(AND<noexcept(char_t{string[indexes]})...>::value) :
        value{string[indexes]...}
      {}

      // [...]
      template <typename type, std::size_t capacityA, std::size_t capacityB, class traits, std::size_t... indexesA, std::size_t... indexesB>
      constexpr static std::basic_const_string<type, capacityA + capacityB, traits> concatenate(std::basic_const_string<type, capacityA, traits> const& stringA, std::basic_const_string<type, capacityB, traits> const& stringB, std::index_sequence<indexesA...> const, std::index_sequence<indexesB...> const) noexcept(noexcept(std::basic_const_string<type, capacityA + capacityB, traits>{stringA.value[indexesA]..., stringB.value[indexesB]...})) {
        return {stringA.value[indexesA]..., stringB.value[indexesB]...};
      }

      // [operator]
      template <class traits> friend inline std::basic_ostream<typename std::remove_cv<char_t>::type, traits>& operator <<(std::basic_ostream<typename std::remove_cv<char_t>::type, traits>& stream, std::basic_const_string<char_t, length, traits>&                string) { return stream.write(const_cast<char_t const*>(string.value), length); }
      template <class traits> friend inline std::basic_ostream<typename std::remove_cv<char_t>::type, traits>& operator <<(std::basic_ostream<typename std::remove_cv<char_t>::type, traits>& stream, std::basic_const_string<char_t, length, traits> const&          string) { return stream.write(const_cast<char_t const*>(string.value), length); }
      template <class traits> friend inline std::basic_ostream<typename std::remove_cv<char_t>::type, traits>& operator <<(std::basic_ostream<typename std::remove_cv<char_t>::type, traits>& stream, std::basic_const_string<char_t, length, traits> const volatile& string) { return stream.write(const_cast<char_t const*>(string.value), length); }
      template <class traits> friend inline std::basic_ostream<typename std::remove_cv<char_t>::type, traits>& operator <<(std::basic_ostream<typename std::remove_cv<char_t>::type, traits>& stream, std::basic_const_string<char_t, length, traits> volatile&       string) { return stream.write(const_cast<char_t const*>(string.value), length); }
      template <class traits> friend inline std::basic_ostream<typename std::remove_cv<char_t>::type, traits>& operator <<(std::basic_ostream<typename std::remove_cv<char_t>::type, traits>& stream, std::basic_const_string<char_t, length, traits>&&               string) { return stream.write(const_cast<char_t const*>(string.value), length); }

    public:
      // [alias]
      using difference_type = std::ptrdiff_t;
      using size_type       = std::size_t;
      using traits_type     = traits_t;
      using value_type      = char_t;

      using const_iterator         = void const;
      using const_pointer          = char_t const*;
      using const_reference        = char_t const&;
      using const_reverse_iterator = std::reverse_iterator<const_iterator>;
      using iterator               = void;
      using pointer                = char_t*;
      using reference              = char_t&;
      using reverse_iterator       = std::reverse_iterator<iterator>;

      // [data]
      static size_type const npos = -1;

      // [constructor]
      constexpr basic_const_string() noexcept(noexcept(char_t{})) :
        value{}
      {}

      template <typename type, std::size_t capacity>
      constexpr basic_const_string(type (&string)[capacity]) noexcept(noexcept(basic_const_string{string, std::make_index_sequence<(capacity < length ? capacity : length)>{}})) :
        basic_const_string<char_t, length, traits_t>::basic_const_string(string, std::make_index_sequence<(capacity < length ? capacity : length)>{})
      {}

      template <typename type, std::size_t capacity, class traits>
      constexpr basic_const_string(std::basic_const_string<type, capacity, traits> const volatile& string) noexcept(noexcept(std::basic_const_string<char_t, length, traits_t>{string.value})) :
        basic_const_string<char_t, length, traits_t>::basic_const_string(string.value)
      {}

      template <typename type, std::size_t capacity, class traits>
      constexpr basic_const_string(std::basic_const_string<type, capacity, traits>&& string) noexcept(noexcept(std::basic_const_string<char_t, length, traits_t>{string.value})) :
        basic_const_string<char_t, length, traits_t>::basic_const_string(string.value)
      {}

      template <typename type, typename... types>
      constexpr basic_const_string(type&& character, types&&... characters) noexcept(AND<noexcept(char_t{std::forward<type>(character)}), noexcept(char_t{std::forward<types>(characters)})...>::value) :
        value{character, characters...}
      {}

      // [...]
      constexpr std::basic_const_string<char_t, length != 1u ? length - 1u : 0u, traits_t> pop_back() const volatile noexcept {
        return std::basic_const_string<char_t, length != 1u ? length - 1u : 0u, traits_t>{this -> value};
      }

      // [operator]
      template <typename type>
      constexpr char_t& operator [](type&& index) const volatile noexcept {
        return this -> value[std::forward<type>(index)];
      }

      template <typename type, std::size_t capacity, class traits>
      constexpr friend bool operator ==(std::basic_const_string<char_t, length, traits_t> const volatile& stringA, std::basic_const_string<type, capacity, traits> const volatile& stringB) noexcept(noexcept()) {
        return capacity == length
      }

      constexpr operator type&()       noexcept { return this -> value; }
      constexpr operator type&() const noexcept { return this -> value; }
  };

  /* ... */
  // constexpr const_string<COUNT<unsigned long long, 10uLL>::value> to_const_string(unsigned long long const integer) noexcept {
  //   return std::const_string<1u>{"0123456789"[integer % 10uLL]} + to_const_string(integer / 10uLL).pop_back();
  // }
}

/* Main */
int main() {}

// operator basic_string_view
// operator!=
// operator<
// operator<=
// operator<=>
// operator==
// operator>
// operator>=
// operator[]

// append
// assign
// at
// back
// begin, cbegin
// clear
// compare
// contains
// copy
// data
// empty
// end, cend
// ends_with
// find
// find_first_not_of
// find_first_of
// find_last_not_of
// find_last_of
// front
// insert
// length
// max_size
// push_back
// rbegin, crbegin
// remove_prefix
// remove_suffix
// rend, crend
// replace
// rfind
// size
// starts_with
// substr
// swap

// hash
// stoi
// stol
// stoll
// stoul
// stoull
// stof
// stod
// stold

// begin
// cbegin
// cend
// crbegin
// crend
// data
// empty
// end
// rbegin
// rend
// size
// ssize
