#include <csignal>
#include <cstdio>

int main(void) {
  std::puts("[BEFORE]");
  while (0x0 != std::raise(SIGFPE)) continue;
  std::puts("[AFTER]");
}
