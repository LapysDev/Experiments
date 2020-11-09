#include <stdio.h>

auto put_deferred(char const message[]) -> void { ::puts(message); }
put_deprecated(message) char const message[]; { ::puts(message); return; }
constexpr static auto const &put_lambda = [](char const message[]) { ::puts(message); return; };

void put(char const message[]) { ::puts(message); }

int main(void) {
  put_deprecated("[1] Hello, World!");
  put_deferred("[2] Hello, World!");
  put_lambda("[3] Hello, World!");
  put("[4] Hello, World!");
}
