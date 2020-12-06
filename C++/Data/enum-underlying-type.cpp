#include <cstdio>
#include <type_traits>

void put(bool const) { std::puts("[bool]"); }
void put(char const) { std::puts("[char]"); }
void put(char16_t const) { std::puts("[char16_t]"); }
void put(char32_t const) { std::puts("[char32_t]"); }
void put(double const) { std::puts("[double]"); }
void put(float const) { std::puts("[float]"); }
void put(int const) { std::puts("[int]"); }
void put(long const) { std::puts("[long]"); }
void put(long double const) { std::puts("[long double]"); }
void put(long long const) { std::puts("[long long]"); }
void put(short const) { std::puts("[short]"); }
void put(signed char const) { std::puts("[signed char]"); }
void put(unsigned char const) { std::puts("[unsigned char]"); }
void put(unsigned int const) { std::puts("[unsigned int]"); }
void put(unsigned long const) { std::puts("[unsigned long]"); }
void put(unsigned long long const) { std::puts("[unsigned long long]"); }
void put(unsigned short const) { std::puts("[unsigned short]"); }
void put(wchar_t const) { std::puts("[wchar_t]"); }
template <typename type> void put(type* const) { std::puts("[void*]"); }
template <typename type> void put(type const) { std::puts("[...]"); }

int main(void) {
  enum e1 {};
  enum class e2 {};
  enum class e3 : unsigned {};
  enum class e4 : int {};

  ::put(typename std::underlying_type<e1>::type {});
  ::put(typename std::underlying_type<e2>::type {});
  ::put(typename std::underlying_type<e3>::type {});
  ::put(typename std::underlying_type<e4>::type {});
}
