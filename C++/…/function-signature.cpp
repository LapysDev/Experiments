#include <cstdio>

/* ... */
auto put_deferred(char const message[]) -> void { std::puts(message); }
put_deprecated(message) char const message[]; { std::puts(message); return; }
constexpr static auto &put_lambda = *[](char const message[]) { std::puts(message); return; };

void put(char const message[]) { std::puts(message); }

/* Main */
int main(int, char*[]) /* noexcept */ {
  put_deferred  ("[1] Hello, World!");
  put_deprecated("[2] Hello, World!");
  put_lambda    ("[3] Hello, World!");
  put           ("[4] Hello, World!");
}
