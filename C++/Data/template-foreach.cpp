#include <cstddef>
#include <cstdio>

#include <array>

/* ... */
namespace std { // undefined extension
  // can be re-worked to use lambdas, instead (somehow)
  template <std::size_t index, template <std::size_t> class callback>
  void iterate(void) {
    callback<index - 1u>::invoke();
    iterate<index - 1u, callback>();
  }
}

/* ... */
std::array<char const*, 3u> names = {"Mary", "John", "Bob"};

template <std::size_t index>
struct print {
  // the loop body
  static void invoke(void) {
    // to get it the right-way-round: `length - index - 1u`
    std::printf("[%zu]: \"%s\"" "\r\n", index, names[index]);
  }
};

template <> // the loop end condition
void std::iterate<0u, print>(void) {}

/* Main */
int main(void) {
  // the loop starting clause
  //   note how we ignore "Bob" 🐢
  std::iterate<2u, print>();
}
