/* Import */
#include <climits>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <new>
#include <stdint.h>
#ifdef _MSVC_LANG
# if _MSVC_LANG >= 202002L
#   include <version>
# endif
#elif __cplusplus >= 202002L
# include <version>
#elif defined(__clang__) || defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__GNUC__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER)
# include <version>
#endif

#if defined(__APPLE__) || defined(__bsdi__) || defined(__CYGWIN__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(linux) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
# include <pthread.h> // --> -pthread; ::pthread_self()
#elif defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
# include <windows.h> // --> <processthreadsapi.h>; ::GetCurrentThreadId()
#endif

/* Main */
int main(int, char*[]) /* noexcept */ {}
