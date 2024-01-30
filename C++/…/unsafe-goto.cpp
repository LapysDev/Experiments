#include <csetjmp>
#include <cstdio>

/* Main */
int main(void) {
  std::jmp_buf recovery;

  if (0 == setjmp(recovery))
    std::puts("We just crossed time & space!");

  else {
    std::puts("We're breaking the time barrier...");
    std::longjmp(recovery, 0);
  }
}
