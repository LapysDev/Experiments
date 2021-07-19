#include <cstdio>

int main() {
  using std::printf;

  /* ... */
  int copyable = 1;
  static int persistent = 2;
  int referable = 3;

  // ...
  struct { int copy; void operator ()() { printf("[cpy]: %i" "\r\n", copy); } } copycapture = {copyable};
  struct { void operator ()() { printf("[nil]: %i" "\r\n", persistent); } } nocapture;
  struct { int *reference; void operator ()() { printf("[ref]: %i" "\r\n", *reference); } } refcapture = {&referable};

  /* ... */
  copycapture();
  nocapture();
  refcapture();
}
