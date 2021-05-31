#include <csignal>
#include <cstdio>
#include <cstdlib>

static void terminate_handler(void) { std::puts("[TERMINATED]"); }
static void signal_handler(int const signal) {
  switch (signal) {
    case SIGABRT: std::puts("[ABORTED]"); break;
    case SIGFPE: std::puts("[FLOATING-POINT ERROR]"); break;
    case SIGILL: std::puts("[ILLEGAL INSTRUCTION]"); break;
    case SIGINT: std::puts("[INTERRUPT]"); break;
    case SIGSEGV: std::puts("[SEGMENTATION ERROR]"); break;
    case SIGTERM: std::puts("[TERMINATED]"); break;
  }

   SIG_DFL(signal);
}

int main(void) {
  int *const pointer = NULL;

  std::atexit(&terminate_handler);
  std::signal(SIGABRT, &signal_handler);
  std::signal(SIGFPE, &signal_handler);
  std::signal(SIGILL, &signal_handler);
  std::signal(SIGINT, &signal_handler);
  std::signal(SIGSEGV, &signal_handler);
  std::signal(SIGTERM, &signal_handler);

  std::printf("[...]: %i" "\r\n", *pointer);
  return EXIT_SUCCESS;
}
