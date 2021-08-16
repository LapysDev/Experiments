#include <climits>
#include <cstddef>
#include <cstdio>

/* ... */
namespace {
  #if __cplusplus >= 2011uL
    typedef signed   long long intmax_t;
    typedef unsigned long long uintmax_t;
  #else
    typedef signed   long intmax_t;
    typedef unsigned long uintmax_t;
  #endif

  // ...
  template <typename type> type&  forward(type&  argument) { return argument; }
  template <typename type> type&& forward(type&& argument) { return argument; }

  template <typename type> type instantiate();

  constexpr unsigned char lengthof(uintmax_t const number, uintmax_t const radix = 10u) { return 0u != number ? 1u + lengthof(number / radix) : 0u; }
  constexpr unsigned char lengthof(intmax_t  const number, uintmax_t const radix = 10u) { return lengthof(static_cast<uintmax_t>(0 > number ? -number : number), radix); }
  constexpr std::size_t lengthof(char const string[]) { return '\0' != *string ? 1u + lengthof(string + 1) : 0u; }

  // ... ->> array indexing
  template <std::size_t count, std::size_t... indexes> struct index_sequence : index_sequence<count - 1u, count - 1u, indexes...> {};
  template <std::size_t... indexes> struct index_sequence<0u, indexes...> {};

  // ... ->> substitution validation
  template <std::size_t> struct assertion;

  template <typename, typename, typename = assertion<sizeof(bool)> > struct assert { static bool const value = false; };
  template <typename base, typename type> struct assert<base, type, assertion<sizeof(base(instantiate<type>()), false)> > { static bool const value = true; };

  // ... ->> utility
  template <std::size_t capacityA, std::size_t capacityB>
  struct concatenate {
    char value[(capacityA + capacityB) - 1u];

    // ...
    constexpr concatenate(char const (&stringA)[capacityA], char const (&stringB)[capacityB]) : concatenate(stringA, stringB, index_sequence<capacityA - 1u>(), index_sequence<capacityB - 1u>()) {}

    template <std::size_t... indexesA, std::size_t... indexesB>
    constexpr concatenate(char const (&stringA)[capacityA], char const (&stringB)[capacityB], index_sequence<0u, indexesA...> const, index_sequence<0u, indexesB...> const) : value{stringA[indexesA]..., stringB[indexesB]...} {}
  };

  template <std::size_t length>
  class string {
    private:
      template <std::size_t capacity>
      constexpr string(char const (&string)[capacity]) : string<length>::string(string, index_sequence<capacity>()) {}

      template <std::size_t capacity, std::size_t const... indexes>
      constexpr string(char const (&string)[capacity], index_sequence<0u, indexes...> const) : value{string[indexes]...} {}

    public:
      char value[length];

      constexpr string(char const (&string)[length]) : string<length>::string(string, index_sequence<length>()) {}
      constexpr string(string<length> const& string) : string<length>::string(string.value) {}
      template <typename... types> constexpr string(char const character, types const... characters) : value{character, characters...} {}
  };

  struct convert {
    constexpr string<19u> str(unsigned const number, string<19u> string, unsigned char length) { return 0u != number ? ((string.value[19u - length - 1u] = "0123456789"[number % 10u]), str(number / 10u, string, length + 1u)) : string; }
    constexpr string<19u> str(unsigned const number) { return slice(19u - len(number), str(number, string<19u>(), 0u)); }

    private:
      #if __cplusplus >= 2011uL
        constexpr static UINTMAX_LENGTH = lengthof(ULLONG_MAX);
      #else
        constexpr static UINTMAX_LENGTH = lengthof(ULONG_MAX);
      #endif

    public:
      constexpr convert(uintmax_t const number) { return slice(UINTMAX_LENGTH - len(number), convert(number, string<0u>(), 0u)); }
  };
}

// ...
template <std::size_t length, bool>
struct CreateValidString;

template <std::size_t length>
struct CreateValidString<length, false> {
  template <std::size_t capacity>
  constexpr static auto invoke(char const (&string)[capacity]) ->
    decltype(CreateValidString<length + 1u, assert<::string<length + 1u>, char const (&)[capacity]>::value>::invoke(string))
  {
    return CreateValidString<length + 1u, assert<::string<length + 1u>, char const (&)[capacity]>::value>::invoke(string);
  }
};

template <std::size_t length>
struct CreateValidString<length, true > {
  template <std::size_t capacity>
  constexpr static string<length> invoke(char const (&string)[capacity]) {
    return ::string<length>(string);
  }
};

// ...
constexpr char const (&print())[1] { return ""; }
template <typename type, typename... types> constexpr int print(type&&, types&&...;

/* Main */
int main() {
  print(1, "B");
  // constexpr string<6u> string = CreateValidString<0u, false>::invoke("Lapys");
  // std::printf("%s", static_cast<char const (&)[6]>(string));
}
