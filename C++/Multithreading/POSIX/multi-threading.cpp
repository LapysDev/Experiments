/* Import */
#include <cstdio>
#include <cstdlib>
#if defined(__APPLE__) || defined(__bsdi__) || defined(__CYGWIN__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(linux) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
# include <pthread.h>
# include <unistd.h>
#elif defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
# include <windows.h>
#endif

/* Main */
int main(int, char*[]) {
  struct program;

  #if defined(__APPLE__) || defined(__bsdi__) || defined(__CYGWIN__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(linux) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
    pthread_t thread;
    struct program {
      static void* submain(void* const argument) {
        std::printf("[submain @ %lx]: %p" "\r\n", static_cast<unsigned long>(::pthread_self()), argument);
        return NULL; // --> ::pthread_exit(NULL);
      }
    };

    // ...
    std::printf("[main @ %lx : begin]" "\r\n", static_cast<unsigned long>(::pthread_self()));

    if (0 == ::pthread_create(&thread, static_cast<pthread_attr_t const*>(NULL), &program::submain, static_cast<void*>(NULL) /* ->> `submain(...)` argument */)) {
      void *exitCode = NULL;

      // ...
      std::printf("[submain @ %lx : begin]" "\r\n", static_cast<unsigned long>(thread));
      std::puts(0 == ::pthread_join(thread, &exitCode /* ->> optionally nullable */) ? "[submain : end]" : "[submain : un-begun]");
    }

    std::puts("[main : end]");
  #elif defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
    HANDLE thread;
    DWORD  threadId;
    struct program {
      static DWORD WINAPI submain(LPVOID const argument) {
        std::printf("[submain @ %lx]: %p" "\r\n", static_cast<unsigned long>(::GetCurrentThreadId()), static_cast<void*>(argument));
        return EXIT_SUCCESS; // ->> Must never be `STILL_ACTIVE` ->> `::ExitThread(EXIT_SUCCESS)` does not perform full cleanup
      }
    };

    // ...
    std::printf("[main @ %lx : begin]" "\r\n", static_cast<unsigned long>(::GetCurrentThreadId()));
    thread = ::CreateThread(static_cast<LPSECURITY_ATTRIBUTES>(NULL), 0u, static_cast<LPTHREAD_START_ROUTINE>(&program::submain), static_cast<LPVOID>(NULL) /* ->> `submain(...)` argument */, 0x00000000u, &threadId);

    if (NULL != thread) {
      std::printf("[submain @ %lx : begin]" "\r\n", static_cast<unsigned long>(threadId));
      // ... ->> Unsure when the created thread runs
      std::puts("[submain : end]");
    }

    std::puts("[main : end]");
  #endif
}
