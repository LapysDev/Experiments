#include <csignal>
#include <cstdio>
#include <cstdlib>

static void terminate_handler(void) {
  std::puts("[TERMINATED]");
}

static void signal_handler(int const signal) {
  switch (signal) {
    case SIGABRT: std::puts("[ABORTED]");              break;
    case SIGFPE : std::puts("[FLOATING-POINT ERROR]"); break;
    case SIGILL : std::puts("[ILLEGAL INSTRUCTION]");  break;
    case SIGINT : std::puts("[INTERRUPT]");            break;
    case SIGSEGV: std::puts("[SEGMENTATION ERROR]");   break;
    case SIGTERM: std::puts("[TERMINATED]");           break;

    /* case SIGALRM: break; */
    /* case SIGBUS: break; */
    /* case SIGCHLD: break; */
    /* case SIGCONT: break; */
    /* case SIGEMT: break; */
    /* case SIGHUP: break; */
    /* case SIGIO: break; */
    /* case SIGIOT: break; */
    /* case SIGKILL: break; */
    /* case SIGPIPE: break; */
    /* case SIGPOLL: break; */
    /* case SIGPROF: break; */
    /* case SIGPWR: break; */
    /* case SIGQUIT: break; */
    /* case SIGRTMAX: break; */
    /* case SIGRTMIN: break; */
    /* case SIGSTKFLT: break; */
    /* case SIGSTOP: break; */
    /* case SIGSYS: break; */
    /* case SIGTRAP: break; */
    /* case SIGTSTP: break; */
    /* case SIGTTIN: break; */
    /* case SIGTTOU: break; */
    /* case SIGURG: break; */
    /* case SIGUSR1: break; */
    /* case SIGUSR2: break; */
    /* case SIGVTALRM: break; */
    /* case SIGXCPU: break; */
    /* case SIGXFSZ: break; */
    /* case SIGWINCH: break; */

    /* case SIGCLD: break; */
    /* case SIGEMT: break; */
    /* case SIGINFO: break; */
    /* case SIGLOST: break; */
    /* case SIGPWR: break; */
    /* case SIGSTKFLT: break; */
    /* case SIGUNUSED: break; */
  }

  std::exit(EXIT_SUCCESS);
}

/* Main */
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
  std::puts("[...]");

  return EXIT_SUCCESS;
}
