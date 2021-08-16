#include <cstddef>
#include <cstdio>

template <std::size_t, std::size_t> struct concatenator;
template <std::size_t, std::size_t...> struct index_sequence;

/* ... */
template <std::size_t capacityA, std::size_t capacityB>
struct concatenator {
  char value[(capacityA + capacityB) - 1u];

  template <std::size_t... indexesA, std::size_t... indexesB>
  constexpr concatenator(char const (&stringA)[capacityA], char const (&stringB)[capacityB], index_sequence<0u, indexesA...> const, index_sequence<0u, indexesB...> const) :
    value{stringA[indexesA]..., stringB[indexesB]...}
  {}

  constexpr concatenator(char const (&stringA)[capacityA], char const (&stringB)[capacityB]) :
    concatenator(stringA, stringB, index_sequence<capacityA - 1u>(), index_sequence<capacityB - 1u>())
  {}
};

template <std::size_t count, std::size_t... indexes>
struct index_sequence : index_sequence<count - 1u, count - 1u, indexes...> {};

template <std::size_t... indexes>
struct index_sequence<0u, indexes...> {};

/* Main */
template <std::size_t length>
class String {
  private:
    typedef char (string_t)[length];
    string_t data;

    template <std::size_t capacity, std::size_t... indexes>
    constexpr String(char const (&string)[capacity], index_sequence<0u, indexes...> const) :
      data{string[indexes]..., '\0'}
    {}

  public:
    template <std::size_t capacity>
    constexpr String(char const (&string)[capacity]) :
      String(string, index_sequence<capacity>())
    {}

    template <std::size_t capacityA, std::size_t capacityB, std::size_t... capacities>
    constexpr String(char const (&stringA)[capacityA], char const (&stringB)[capacityB], char const (&...strings)[capacities]) :
      String(concatenator<capacityA, capacityB>(stringA, stringB).value, strings...)
    {}

    constexpr operator string_t const&() const { return this -> data; }
};

int main() {
  std::printf("\"%s\"" "\r\n", static_cast<char const*>(String<16u>("Hello, World!")));
  std::printf("\"%s\"" "\r\n", static_cast<char const*>(String<16u>("Hello", ", World!")));
  std::printf("\"%s\"" "\r\n", static_cast<char const*>(String<38u>("Hello", ", World!", " " "This actually worked!")));
}
