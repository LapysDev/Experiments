// COMPILE: del cataloger.exe && cls && clang++ -pedantic -std=c++98 -Wall -Wextra cataloger.cpp -o cataloger.exe -ltaskschd && cataloger.exe A C:\Users\oluwa\…\cataloger-clock.dat & del cataloger.exe
// RUN    : cataloger C:/Users/oluwa/OneDrive/Lapys/Catalog C:/Users/oluwa/OneDrive/Lapys/Catalog/cataloger-clock.dat
#include <cerrno>  // --> EILSEQ, errno
#include <ciso646> // --> and, not, or
#include <climits> // --> CHAR_BIT, UCHAR_MAX
#include <clocale> // --> LC_ALL;                                            std::setlocale(…)
#include <csignal> // --> SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM; std::signal(…)
#include <cstddef> // --> NULL; std::size_t
#include <cstdio>  // --> _IONBF, EOF, L_tmpnam, stderr, stdin, stdout; std::FILE; std::fflush(…), std::fopen(…, "ccs=UTF-8"), std::fputs(…), std::fwrite(…), std::setvbuf(…), std::tmpfile(…), std::tmpnam(…)
#include <cstdlib> // --> EXIT_FAILURE, EXIT_SUCCESS;                              std::at_quick_exit(…), std::atexit(…), std::exit(…)
#include <ctime>   // --> std::time_t;                                             std::gmtime(…), std::time(…)
#include <cwchar>  // --> std::fgetwc(…), std::fputws(…), std::fwide(…)
#include <new>     // --> delete, new; std:nothrow
#if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
# include <stdio.h>  // --> ::fileno(…)
# include <unistd.h> // --> ::isatty(…)
#elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
# if defined _MSC_BUILD or defined _MSC_FULL_VER or defined _MSC_VER
#   pragma comment(lib, "kernel32.lib")
#   pragma comment(lib, "taskschd.lib")
# endif
# define _CRT_SECURE_NO_WARNINGS // ->> C Run-Time security                    --> `https://learn.microsoft.com/en-us/cpp/c-runtime-library/security-features-in-the-crt`
# define CINTERFACE              // ->> C Interface for Component Object Model --> `https://learn.microsoft.com/en-us/windows/win32/com/the-component-object-model`
# define STRICT                  // ->> Strict type checking                   --> `https://learn.microsoft.com/en-us/windows/win32/winprog/enabling-strict`
# define UNICODE                 // ->> Unicode preference                     --> `https://learn.microsoft.com/en-us/windows/win32/learnwin32/working-with-strings`
# ifndef _WIN32_WINNT            //
#   define _WIN32_WINNT 0x0501 // --> _WIN32_WINNT_WINXP
# endif
# include <io.h>      // --> ::_isatty(…)
# include <stdio.h>   // --> ::_fileno(…), ::_get_pgmptr(…), ::_get_wpgmptr(…)
# include <windows.h> // --> CP_UTF8, ERROR_CANCELLED, ERROR_SUCCESS, FOREGROUND_RED, INVALID_HANDLE_VALUE, MAX_PATH, MB_ERR_INVALID_CHARS, STD_ERROR_HANDLE, WINAPI; BOOL, CONSOLE_SCREEN_BUFFER_INFO, DWORD, HANDLE, HLOCAL, HMODULE, LONG, LPBOOL, LPCCH, LPCVOID, LPCWCH, LPCWSTR, LPDWORD, LPSERVICE_MAIN_FUNCTIONW, LPUNKNOWN, LPVOID, LPWSTR, OLECHAR, PCONSOLE_SCREEN_BUFFER_INFO, PCWSTR, PSECURITY_DESCRIPTOR, PWSTR, REFCLSID, REFIID, SERVICE_TABLE_ENTRYW, TCHAR, UINT, VARIANTARG, WCHAR; ::GetModuleHandleExW(…), ::GetProcAddress(…), ::GetSystemDirectoryW(…)
#   include <oaidl.h>         // --> VARIANT, VARIANTARG
#   include <objbase.h>       // --> ::COINIT_MULTITHREADED
#   include <objidl.h>        // --> SOLE_AUTHENTICATION_SERVICE
#   include <rpcdce.h>        // --> RPC_C_AUTHN_LEVEL_PKT_PRIVACY, RPC_C_IMP_LEVEL_IMPERSONATE
#   include <wincred.h>       // --> CREDUI_FLAGS_ALWAYS_SHOW_UI, CREDUI_FLAGS_DO_NOT_PERSIST, CREDUI_FLAGS_GENERIC_CREDENTIALS, CREDUI_MAX_PASSWORD_LENGTH, CREDUI_MAX_USERNAME_LENGTH, CREDUIAPI; CREDUI_INFOW, PCtxtHandle
#   include <winerror.h>      // --> FAILED, SUCCEEDED
#   include <winnt.h>         // --> HRESULT
#   include <wtypes.h>        // --> BSTR, ::VT_BSTR
#   include <wtypesbase.h>    // --> ::CLSCTX_INPROC_SERVER
#   if _WIN32_WINNT >= 0x0600 // --> _WIN32_WINNT_VISTA | _WIN32_WINNT_WS08
#     include <taskschd.h> // --> IAction, IActionCollection, IDailyTrigger, IRegisteredTask, IRegistrationInfo, IRepetitionPattern, ITaskDefinition, ITaskFolder, ITaskService, ITrigger, ITriggerCollection; ::CLSID_TaskScheduler, ::IID_IDailyTrigger, ::IID_IExecAction, ::IID_ITaskService, ::TASK_ACTION_EXEC, ::TASK_CREATE_OR_UPDATE, ::TASK_LOGON_PASSWORD, ::TASK_TRIGGER_DAILY
#   endif
#endif

/* Main --> catalog [log_directory] [clock_path] [rerun] */
int main(int count, char* arguments[]) /* noexcept */ {
  static struct catalog *catalog = NULL;
  static struct catalog /* final */ {
    enum { MESSAGE_MAXIMUM_LENGTH = 256u };           // --> std::size_t
    union formatinfo { unsigned char metadata[32]; }; // ->> Arbitrarily-sized

    /* ... */
    /* [[noreturn]] extern "C" */ static void error(int const signal) {
      if (NULL != catalog)
      switch (signal) {
        case SIGABRT: (void) catalog -> exit((catalog -> warn("Cataloger stopped by abormal termination"),               EXIT_FAILURE));                break;
        case SIGFPE : (void) catalog -> exit((catalog -> warn("Cataloger stopped by a floating-point exception"),        EXIT_FAILURE));                break;
        case SIGILL : (void) catalog -> exit((catalog -> warn("Cataloger stopped by an invalid executable instruction"), EXIT_FAILURE));                break;
        case SIGINT : (void) catalog -> exit((catalog -> warn("Cataloger stopped by an external interrupt")            ? EXIT_SUCCESS : EXIT_FAILURE)); break;
        case SIGSEGV: (void) catalog -> exit((catalog -> warn("Cataloger stopped by impermissible memory access"),       EXIT_FAILURE));                break;
        case SIGTERM: (void) catalog -> exit((catalog -> warn("Cataloger stopped by a termination request"),             EXIT_FAILURE));                break;

        /* case SIGALRM, SIGBUS, SIGCHLD, SIGCONT, SIGEMT, SIGHUP,    SIGIO, SIGIOT, SIGKILL, SIGPIPE, SIGPOLL, SIGPROF, SIGPWR, SIGQUIT, SIGRTMAX, SIGRTMIN, SIGSTKFLT, SIGSTOP, SIGSYS, SIGTRAP, SIGTSTP, SIGTTIN, SIGTTOU, SIGURG, SIGUSR1, SIGUSR2, SIGVTALRM, SIGXCPU, SIGXFSZ, SIGWINCH: break; */
        /* case SIGCLD,  SIGEMT, SIGINFO, SIGLOST, SIGPWR, SIGSTKFLT, SIGUNUSED                                                                                                                                                                                                              : break; */
        default: (void) catalog -> exit((catalog -> warn("Cataloger stopped"), EXIT_FAILURE)); break;
      }

      catalog = NULL;
      std::exit(EXIT_FAILURE);
    }

    /* [[noreturn]] */ static int exit(int const code) {
      if (NULL != catalog) {
        if (catalog -> timerPathAllocated)      ::delete[]  catalog -> timerPath;
        if (NULL != catalog -> timerFileStream) std::fclose(catalog -> timerFileStream);

        catalog -> applicationExitCode = code;
        catalog -> timerFileStream     = NULL;
      }

      catalog = NULL;
      std::exit(code);

      return code;
    }

    static bool format(std::FILE* const stream, bool const recolor = true, formatinfo* const information = NULL) {
      std::size_t const informationMetadataSize = sizeof information -> metadata / sizeof(unsigned char);
      bool              supported               = false;
      #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
        int const streamDescriptor = stream == stderr ? ::fileno(stream) /* --> STDERR_FILENO */ : -1;

        // ...
        supported = streamDescriptor != -1 and ::isatty(streamDescriptor) == 1;
      #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
        BOOL   WINAPI            (*GetConsoleMode)            (HANDLE, LPDWORD)                     = NULL;
        BOOL   WINAPI            (*GetConsoleScreenBufferInfo)(HANDLE, PCONSOLE_SCREEN_BUFFER_INFO) = NULL;
        HANDLE WINAPI            (*GetStdHandle)              (DWORD)                               = NULL;
        BOOL   WINAPI            (*SetConsoleMode)            (HANDLE, DWORD)                       = NULL;
        BOOL   WINAPI            (*SetConsoleTextAttribute)   (HANDLE, WORD)                        = NULL;
        HMODULE                    libraryModule                                                    = NULL;
        WCHAR const                libraryName[]                                                    = L"kernel32" ".dll";
        WCHAR                      libraryPath[MAX_PATH + 1u]                                       = L"";
        UINT const                 libraryPathLength                                                = ::GetSystemDirectoryW(libraryPath, ((MAX_PATH + 1u) * sizeof(WCHAR)) / sizeof(TCHAR));
        DWORD                      streamConsoleMode                                                = 0x00u;
        CONSOLE_SCREEN_BUFFER_INFO streamConsoleScreenBufferInformation                             = {};
        HANDLE                     streamStandardDeviceHandle                                       = NULL;

        // ...
        if (0u != libraryPathLength) {
          libraryPath[libraryPathLength] = L'\\';

          for (std::size_t index = 0u; ; ++index) {
            libraryPath[index + libraryPathLength + 1u] = libraryName[index];
            if (L'\0' == libraryName[index]) break;
          }

          if (FALSE != ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, libraryPath, &libraryModule) and NULL != libraryModule) {
            GetConsoleMode             = reinterpret_cast<BOOL   WINAPI (*)(HANDLE, LPDWORD)>                    (::GetProcAddress(libraryModule, "GetConsoleMode"));
            GetConsoleScreenBufferInfo = reinterpret_cast<BOOL   WINAPI (*)(HANDLE, PCONSOLE_SCREEN_BUFFER_INFO)>(::GetProcAddress(libraryModule, "GetConsoleScreenBufferInfo"));
            GetStdHandle               = reinterpret_cast<HANDLE WINAPI (*)(DWORD)>                              (::GetProcAddress(libraryModule, "GetStdHandle"));
            SetConsoleMode             = reinterpret_cast<BOOL   WINAPI (*)(HANDLE, DWORD)>                      (::GetProcAddress(libraryModule, "SetConsoleMode"));
            SetConsoleTextAttribute    = reinterpret_cast<BOOL   WINAPI (*)(HANDLE, WORD)>                       (::GetProcAddress(libraryModule, "SetConsoleTextAttribute"));
          }
        }

        streamStandardDeviceHandle = stream == stderr ? NULL != GetStdHandle ? GetStdHandle(STD_ERROR_HANDLE) : NULL : NULL;
        supported                  = INVALID_HANDLE_VALUE != streamStandardDeviceHandle and NULL != streamStandardDeviceHandle;
      #endif

      // ...
      (void) informationMetadataSize;
      (void) stream;

      if (supported and not recolor) {
        #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
          return std::fwrite("\x1B" "[00m", sizeof(char), 5u, stream) == 5u;
        #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
          if (NULL != information)
          if (NULL != SetConsoleTextAttribute) {
            if (true == information -> metadata[0])
            return std::fwrite("\x1B" "[00m", sizeof(char), 5u, stream) == 5u;

            // ...
            if (informationMetadataSize >= sizeof streamConsoleScreenBufferInformation.wAttributes) {
              for (std::size_t index = sizeof streamConsoleScreenBufferInformation.wAttributes; index; --index)
              streamConsoleScreenBufferInformation.wAttributes = information -> metadata[index] | (streamConsoleScreenBufferInformation.wAttributes << CHAR_BIT);
            }

            return FALSE != SetConsoleTextAttribute(streamStandardDeviceHandle, streamConsoleScreenBufferInformation.wAttributes);
          }
        #endif
      }

      else if (supported) {
        #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
          return stream == stderr ? std::fwrite("\x1B" "[31m", sizeof(char), 5u, stream) == 5u : true;
        #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
          if (NULL != information)
          if (NULL != GetConsoleMode and NULL != GetConsoleScreenBufferInfo and NULL != SetConsoleMode and NULL != SetConsoleTextAttribute) {
            if (FALSE != GetConsoleMode(streamStandardDeviceHandle, &streamConsoleMode))
            if (FALSE != SetConsoleMode(streamStandardDeviceHandle, streamConsoleMode | /* --> ENABLE_VIRTUAL_TERMINAL_PROCESSING */ 0x0004u)) {
              information -> metadata[0] = true;
              return stream == stderr ? std::fwrite("\x1B" "[31m", sizeof(char), 5u, stream) == 5u : true;
            }

            // ...
            if (FALSE != GetConsoleScreenBufferInfo(streamStandardDeviceHandle, &streamConsoleScreenBufferInformation)) {
              information -> metadata[0] = false;

              if (informationMetadataSize >= sizeof streamConsoleScreenBufferInformation.wAttributes) {
                for (std::size_t index = 0u; index != sizeof streamConsoleScreenBufferInformation.wAttributes; streamConsoleScreenBufferInformation.wAttributes >>= CHAR_BIT)
                information -> metadata[++index] = static_cast<unsigned char>(streamConsoleScreenBufferInformation.wAttributes & UCHAR_MAX);
              }

              return stream == stderr ? FALSE != SetConsoleTextAttribute(streamStandardDeviceHandle, FOREGROUND_RED) : true;
            }
          }
        #endif
      }

      return false;
    }

    static bool message(char const message[], std::FILE* const stream = stdout) {
      char        const messageOverflowSuffix[]     = "…" "\r\n"; // ->> Source literal encoding to multi-byte NUL-terminated string
      std::size_t const messageOverflowSuffixLength = (sizeof messageOverflowSuffix / sizeof(char)) - 1u;
      bool              messageOverflowed           = false;
      bool              messageOutputted            = false;
      bool              messageFormatted            = false;
      union formatinfo  messageFormatInformation    = {};
      char const *const messageComponents[]         = {catalog -> messagePrefix, message, catalog -> messageSuffix};
      std::size_t const messageComponentsLength     = sizeof messageComponents / sizeof(char const*);
      std::size_t       messageBufferLength         = 0u;
      char              messageBuffer[MESSAGE_MAXIMUM_LENGTH + messageOverflowSuffixLength + /* ->> NUL terminator */ 1u];

      // ...
      if (NULL == message or NULL == stream)
      return true;

      // ... --> message‥ = …; messageBuffer[…] = messageComponents[…][…];
      for (std::size_t index = 0u; index != messageComponentsLength; ++index) {
        char const *const messageComponent         = messageComponents[index];
        bool const        messageComponentIsAffix  = message                  != messageComponent;
        bool const        messageComponentIsSuffix = catalog -> messageSuffix == messageComponent or index == messageComponentsLength - 1u;

        // ...
        if (NULL == messageComponent) {
          if (messageComponentIsAffix) continue;
          else                         break;
        }

        for (std::size_t subindex = 0u; ; ++subindex) {
          bool messageComponentSuffixed = false; // ->> Determines if the `messageComponent` before `::messageSuffix` (or `message`) repeatedly ends with `::messageSuffix`

          // ... --> messageComponentSuffixed = …;
          if (NULL != catalog -> messageSuffix and not messageComponentIsAffix)
          for (std::size_t componentIndex = 0u, suffixIndex = 0u; ; ) {
            if ('\0' == messageComponent[componentIndex]) {
              messageComponentSuffixed = suffixIndex and '\0' == catalog -> messageSuffix[suffixIndex];
              break; // ->> Possibly ends with `::messageSuffix`
            }

            if ('\0' == catalog -> messageSuffix[suffixIndex]) {
              suffixIndex = 0u;
              continue; // ->> Continue checks for repeats
            }

            if (messageComponent[componentIndex++] != catalog -> messageSuffix[suffixIndex++])
            break;
          }

          // ...
          if (messageComponentSuffixed or '\0' == messageComponent[subindex])
          break;

          if (MESSAGE_MAXIMUM_LENGTH <= messageBufferLength) {
            messageBufferLength = MESSAGE_MAXIMUM_LENGTH - (messageComponentIsSuffix ? subindex : 0u);
            messageOverflowed   = true; // ->> Completely elide `messageComponent` if `…IsSuffix` instead of truncating it

            break;
          }

          messageBuffer[messageBufferLength++] = messageComponent[subindex];
        }
      }

      if (messageOverflowed) {
        for (std::size_t index = 0u; index != messageOverflowSuffixLength; ++index)
        messageBuffer[messageBufferLength++] = messageOverflowSuffix[index];
      }

      // ...
      (void) std::fflush (stream);
      (void) std::setvbuf(stream, NULL, _IONBF, 0u);

      messageBuffer[messageBufferLength] = '\0';
      messageFormatted                   = catalog -> format(stream, true, &messageFormatInformation);
      messageOutputted                   = EOF != std::fputs(messageBuffer, stream);

      messageOutputted ? (void) std::fflush      (stream)                                   : std::clearerr(stream);
      messageFormatted ? (void) catalog -> format(stream, false, &messageFormatInformation) : (void) 00;

      // ...
      return messageOutputted;
    }

    /* [[noreturn]] extern "C" */ static void quick_exit() {
      if (NULL != catalog)
        (void) catalog -> exit(catalog -> applicationExitCode);

      std::exit(EXIT_SUCCESS); // ->> Cleanup regardless
    }

    static bool warn(char const message[], std::FILE* const stream = stderr) {
      return catalog -> message(message, stream);
    }

    /* ... */
    int         applicationExitCode;
    char const *applicationName;
    bool        clocked;
    char       *logDirectoryPath;
    char const *messagePrefix;
    char const *messageSuffix;
    bool        rerun;
    std::FILE  *timerFileStream;
    char       *timerPath;
    bool        timerPathAllocated;
  } c = {};

  /* ... -> Vendor API setup, then initialization */
  #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
    enum {
      advapi32, credui, kernel32, ole32, oleaut32, shell32,
      librariesLength // --> std::size_t{…}
    };

    WCHAR                      libraryPath[MAX_PATH + 1u] = L"";
    UINT const                 libraryPathLength          = ::GetSystemDirectoryW(libraryPath, ((MAX_PATH + 1u) * sizeof(WCHAR)) / sizeof(TCHAR));
    static struct libraryinfo *libraries                  = NULL;
    static struct libraryinfo /* final */ {
      LPCWSTR const name;
      HMODULE       module;
      BOOL        (*unloader)(HMODULE);

      /* extern "C" */ static void exit() {
        for (struct libraryinfo *library = libraries; library != libraries + (NULL == libraries ? 0u : librariesLength); ++library)
        if (NULL != library -> module and /* --> FreeLibrary(…) */ NULL != library -> unloader) {
          library -> unloader(library -> module);

          library -> module   = NULL;
          library -> unloader = NULL;
        }
      }
    } l[librariesLength] = {
      {L"advapi32" ".dll", NULL, NULL},
      {L"credui"   ".dll", NULL, NULL},
      {L"kernel32" ".dll", NULL, NULL},
      {L"ole32"    ".dll", NULL, NULL},
      {L"oleaut32" ".dll", NULL, NULL},
      {L"shell32"  ".dll", NULL, NULL}
    };

    // ...
    libraries                      = l;
    libraryPath[libraryPathLength] = L'\\';

    (void) std::atexit(&libraries -> exit);
    #if __cplusplus >= 201103L
      (void) std::at_quick_exit(&libraries -> exit);
    #endif

    if (0u != libraryPathLength) {
      LPWSTR* (*CommandLineToArgvW)      (LPCWSTR, int*)                                       = NULL;
      BOOL    (*FreeLibrary)             (HMODULE)                                             = NULL;
      LPWSTR  (*GetCommandLineW)         ()                                                    = NULL;
      HMODULE (*LoadLibraryExW)          (LPCWSTR, HANDLE, DWORD)                              = NULL;
      HLOCAL  (*LocalFree)               (HLOCAL)                                              = NULL;
      BOOL    (*SetDefaultDllDirectories)(DWORD)                                               = NULL;
      int     (*WideCharToMultiByte)     (UINT, DWORD, LPCWCH, int, LPSTR, int, LPCCH, LPBOOL) = NULL;

      // ... ->> Load the userland `kernel32` library
      for (WCHAR *destination = libraryPath + (libraryPathLength + 1u), *source = const_cast<WCHAR*>(libraries[kernel32].name); ; ++destination, ++source) {
        *destination = *source;
        if (L'\0' == *source) break;
      }

      if (FALSE != ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, libraryPath, &libraries[kernel32].module))
      if (NULL != libraries[kernel32].module) {
        FreeLibrary              = reinterpret_cast<BOOL    (*)(HMODULE)>                                            (::GetProcAddress(libraries[kernel32].module, "FreeLibrary"));
        GetCommandLineW          = reinterpret_cast<LPWSTR  (*)()>                                                   (::GetProcAddress(libraries[kernel32].module, "GetCommandLineW"));
        LoadLibraryExW           = reinterpret_cast<HMODULE (*)(LPCWSTR, HANDLE, DWORD)>                             (::GetProcAddress(libraries[kernel32].module, "LoadLibraryExW"));
        LocalFree                = reinterpret_cast<HLOCAL  (*)(HLOCAL)>                                             (::GetProcAddress(libraries[kernel32].module, "LocalFree"));
        SetDefaultDllDirectories = reinterpret_cast<BOOL    (*)(DWORD)>                                              (::GetProcAddress(libraries[kernel32].module, "SetDefaultDllDirectories"));
        WideCharToMultiByte      = reinterpret_cast<int     (*)(UINT, DWORD, LPCWCH, int, LPSTR, int, LPCCH, LPBOOL)>(::GetProcAddress(libraries[kernel32].module, "WideCharToMultiByte"));
      }

      if (NULL != SetDefaultDllDirectories)
      (void) SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_SYSTEM32);

      // ... ->> Load other used Windows API libraries —
      for (struct libraryinfo *library = libraries; library != libraries + librariesLength; ++library)
      if (NULL == library -> module) { // ->> — except the already loaded userland `kernel32` library
        for (std::size_t index = 0u; ; ++index) {
          libraryPath[index + libraryPathLength + 1u] = library -> name[index];
          if (L'\0' == library -> name[index]) break;
        }

        if (FALSE == ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, libraryPath, &library -> module) or NULL == library -> module) {
          library -> module   = LoadLibraryExW(libraryPath, static_cast<HANDLE>(NULL), LOAD_WITH_ALTERED_SEARCH_PATH);
          library -> unloader = NULL == library -> module ? NULL : FreeLibrary;
        }
      }

      // ...
      if (NULL != libraries[shell32].module)
      CommandLineToArgvW = reinterpret_cast<LPWSTR* (*)(LPCWSTR, int*)>(::GetProcAddress(libraries[shell32].module, "CommandLineToArgvW"));

      // ... ->> Normalize standard C/ C++ command-line `arguments` to vendor-specific Windows `commandLineArguments`
      if (NULL != CommandLineToArgvW and NULL != GetCommandLineW) {
        int           commandLineArgumentsLength = 0;
        LPWSTR *const commandLineArguments       = CommandLineToArgvW(GetCommandLineW(), &commandLineArgumentsLength);

        // ...
        if (NULL != commandLineArguments and commandLineArgumentsLength <= count) {
          if (NULL != WideCharToMultiByte) {
            char       *allocation = NULL;
            std::size_t size       = 0u;

            // ...
            for (int index = 0; commandLineArgumentsLength != index; ++index) {
              int const commandLineArgumentSize = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, commandLineArguments[index], -1, static_cast<LPSTR>(NULL), 0u, static_cast<LPCCH>(NULL), static_cast<LPBOOL>(NULL));

              // ...
              if (0 == commandLineArgumentSize) {
                size = 0u;
                break;
              }

              size += commandLineArgumentSize;
            }

            if (0u != size) {
              size       = /* ->> Non-NUL characters */ (size / sizeof(char)) + /* ->> NUL terminators */ (commandLineArgumentsLength * sizeof(char));
              allocation = ::new (std::nothrow) char[size]; // ->> Potential memory leak
            }

            if (NULL != allocation) {
              char *iterator   = allocation;
              bool  normalized = false;

              // ...
              for (int index = 0; commandLineArgumentsLength != index; ++index) {
                int const commandLineArgumentSize = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, commandLineArguments[index], -1, iterator, size, static_cast<LPCCH>(NULL), static_cast<LPBOOL>(NULL));

                // ...
                if (0 == commandLineArgumentSize)
                continue;

                arguments[index] = iterator; // ->> Normalize standard C/ C++ command-line argument
                iterator        += commandLineArgumentSize;
                normalized       = true;
              }

              if (not normalized)
              ::delete[] allocation;
            }
          }

          if (NULL != LocalFree)
          (void) LocalFree(commandLineArguments);
        }
      }
    }
  #endif

  catalog                        = &c;                                 //
  catalog -> applicationExitCode = EXIT_SUCCESS;                       //
  catalog -> applicationName     = "Cataloger";                        //
  catalog -> clocked             = false;                              // ->> Catalog's internal clock is active
  catalog -> logDirectoryPath    = count > 1 ? arguments[1] : NULL;    // ->> Filesystem location for storing catalogs; Assume NUL-terminated
  catalog -> messagePrefix       = "cataloger" ": ";                   //
  catalog -> messageSuffix       = "\r\n";                             //
  catalog -> rerun               = count > 3 and NULL != arguments[3]; // ->> Catalog is re-executed
  catalog -> timerFileStream     = NULL;                               //
  catalog -> timerPath           = count > 2 ? arguments[2] : NULL;    // ->> Filesystem location for serializing catalog timer; Assume NUL-terminated
  catalog -> timerPathAllocated  = false;                              //

  (void) std::signal   (SIGTERM, &catalog -> error); //
  (void) std::signal   (SIGSEGV, &catalog -> error); // ->> ¯\_(ツ)_/¯
  (void) std::signal   (SIGINT,  &catalog -> error); // ->> Handle possible user interrupts
  (void) std::signal   (SIGABRT, &catalog -> error); // ->> Handle `std::abort(…)` and `std::terminate(…)` (and `throw` expression) invocations
  (void) std::setlocale(LC_ALL,  "C.UTF-8");         //
  #if __cplusplus >= 201103L                         //
    (void) std::at_quick_exit(&catalog -> quick_exit);
  #endif

  // ... --> catalog -> logDirectoryPath = …;
  if (NULL == catalog -> logDirectoryPath) {
    (void) catalog -> message("No directory for logs specified; defaulting to the current working directory, instead");
    catalog -> logDirectoryPath = const_cast<char*>("./");
  }

  if (NULL == catalog -> timerPath)
  (void) catalog -> message("No directory for the catalog's internal clock specified; defaulting to the current working directory, instead");

  // ... --> catalog -> timerFileStream = …;
  catalog -> timerFileStream = NULL == catalog -> timerPath ? std::tmpfile() : std::fopen(catalog -> timerPath, "wb+");

  if (NULL == catalog -> timerFileStream and NULL != catalog -> timerPath) {
    char        catalogTimerFileNameFallback[L_tmpnam + 1u] = {};    //
    std::size_t catalogTimerFileNameFallbackLength          = 0u;    //
    char       *catalogTimerPathBuffer                      = NULL;  // ->> Non-null if `::timerPathAllocated` and assigned to `::timerPath` afterward
    std::size_t catalogTimerPathLength                      = 0u;    //
    char const *catalogTimerPathPrefix                      = "";    //
    bool        catalogTimerPathPrefixed                    = false; // ->> Determines if `::timerPath` (significantly) begins with `catalogTimerPathPrefix`
    std::size_t catalogTimerPathPrefixLength                = 0u;    //
    bool        catalogTimerPathSuffixed                    = false; // ->> Determines if `::timerPath` (significantly) ends   with `pathDelimiters[…]`
    char const  pathDelimiters[]                            = {'/'
      #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
        , '\\'
      #endif
    };
    std::size_t const pathDelimitersLength = sizeof pathDelimiters / sizeof(char);

    // ... --> catalogTimerFileNameFallback       = std::strrchr(std::tmpnam(…) ?? …, '/' | …);
    //         catalogTimerFileNameFallbackLength = std::strlen (catalogTimerFileNameFallback);
    if (catalogTimerFileNameFallback != std::tmpnam(catalogTimerFileNameFallback)) {
      char        const fallback[]     = "cataloger-clock.dat";
      std::size_t const fallbackLength = (sizeof fallback / sizeof(char)) - 1u;

      // ...
      for (std::size_t index = 0u; ; ++index) {
        catalogTimerFileNameFallback[index] = fallback[index];

        if (fallbackLength == index or index == (sizeof catalogTimerFileNameFallback / sizeof(char)) - 1u) {
          catalogTimerFileNameFallback[index] = '\0';
          break;
        }
      }
    }

    while ('\0' != catalogTimerFileNameFallback[catalogTimerFileNameFallbackLength])
    ++catalogTimerFileNameFallbackLength;

    for (std::size_t index = catalogTimerFileNameFallbackLength; index--; ) {
      // ... ->> Unique names only, rather than unique file paths
      for (std::size_t subindex = 0u; pathDelimitersLength != subindex; ++subindex)
      if (catalogTimerFileNameFallback[index] == pathDelimiters[subindex]) {
        catalogTimerFileNameFallbackLength -= ++index;

        for (subindex = 0u; subindex <= catalogTimerFileNameFallbackLength; ++index, ++subindex)
        catalogTimerFileNameFallback[subindex] = catalogTimerFileNameFallback[index];

        index = 0u;
        break;
      }
    }

    // ... --> catalogTimerPathLength   = std::strlen(catalog -> timerPath | …);
    //         catalogTimerPathSuffixed = …;
    for (; '\0' != catalog -> timerPath[catalogTimerPathLength]; ++catalogTimerPathLength) {
      for (std::size_t subindex = 0u; pathDelimitersLength != subindex; ++subindex)
      if (catalog -> timerPath[catalogTimerPathLength] == pathDelimiters[subindex]) {
        for (char *iterator = catalog -> timerPath + (catalogTimerPathLength + 1u); ; ++iterator) {
          switch (*iterator) {
            case ' ': case '\f': case '\n': case '\r': case '\t': case '\v':
            continue;
          }

          catalogTimerPathSuffixed = '\0' == *iterator;
          break;
        }
      }

      if (catalogTimerPathSuffixed)
      break;
    }

    // ... --> catalogTimerPathPrefix… = …;
    #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
      catalogTimerPathPrefix       = "\\\\?\\";
      catalogTimerPathPrefixLength = MAX_PATH < catalogTimerPathLength + /* ->> Path delimiter */ 1u + catalogTimerFileNameFallbackLength + /* ->> NUL terminator */ 1u ? 3u : 0u;
    #endif

    // ... --> catalogTimerPathPrefixed = …;
    for (std::size_t prefixIndex = 0u, timerIndex = 0u; ; ++timerIndex) {
      if (catalogTimerPathPrefixLength == prefixIndex) {
        catalogTimerPathPrefixed     = true;
        catalogTimerPathPrefixLength = 0u;

        break;
      }

      switch (catalog -> timerPath[timerIndex]) {
        case ' ': case '\f': case '\n': case '\r': case '\t': case '\v':
        continue;
      }

      if (catalog -> timerPath[timerIndex] != catalogTimerPathPrefix[prefixIndex++])
      break;
    }

    // ... --> catalogTimerPathBuffer = …; ->> Just resizing
    catalogTimerPathBuffer = ::new (std::nothrow) char[catalogTimerPathPrefixLength + catalogTimerPathLength + /* ->> Path delimiter */ 1u + catalogTimerFileNameFallbackLength + /* ->> NUL terminator */ 1u];

    if (NULL == catalogTimerPathBuffer) {
      if (not catalogTimerPathPrefixed) {
        catalogTimerPathBuffer             = ::new (std::nothrow) char[catalogTimerPathPrefixLength + catalogTimerPathLength + /* ->> NUL terminator */ 1u];
        catalogTimerFileNameFallbackLength = 0u;
      }

      else if (not catalogTimerPathSuffixed) {
        (void) catalog -> warn("Cataloger exited; No file for the catalog's internal clock specified");
        return catalog -> exit(EXIT_FAILURE);
      }

      else
        catalogTimerPathBuffer = ::new (std::nothrow) char[catalogTimerPathLength + /* ->> Path delimiter */ 1u + catalogTimerFileNameFallbackLength + /* ->> NUL terminator */ 1u];
    }

    if (NULL == catalogTimerPathBuffer) {
      catalogTimerPathBuffer       = ::new (std::nothrow) char[catalogTimerPathLength + /* ->> NUL terminator */ 1u];
      catalogTimerPathPrefixLength = 0u;

      if (NULL == catalogTimerPathBuffer) {
        (void) catalog -> warn("Cataloger exited; No file for the catalog's internal clock specified");
        return catalog -> exit(EXIT_FAILURE);
      }
    }

    catalogTimerPathBuffer[catalogTimerPathLength] = '\0';

    for (std::size_t index = 0u; index != catalogTimerPathLength; ++index)
    catalogTimerPathBuffer[index] = catalog -> timerPath[index] != '/' ? catalog -> timerPath[index] : '\\';

    // ... --> catalog -> timerFileStream = …;
    //         catalog -> timerPath…      = …;
    catalog -> timerPath          = catalogTimerPathBuffer;
    catalog -> timerPathAllocated = true;
    catalog -> timerFileStream    = std::fopen(catalog -> timerPath, "wb+");

    if (NULL == catalog -> timerFileStream)
    if (0u != catalogTimerPathPrefixLength) {
      for (std::size_t index = catalogTimerPathLength; index--; )
        catalog -> timerPath[catalogTimerPathPrefixLength + index] = catalog -> timerPath[index];

      for (std::size_t index = catalogTimerPathPrefixLength; index--; )
        catalog -> timerPath[index] = catalogTimerPathPrefix[index];

      catalogTimerPathLength    += catalogTimerPathPrefixLength;
      catalog -> timerFileStream = std::fopen(catalog -> timerPath, "wb+");
    }

    if (NULL == catalog -> timerFileStream)
    if (0u != catalogTimerFileNameFallbackLength) {
      catalog -> timerPath[catalogTimerPathLength]                                           = '\\';
      catalog -> timerPath[catalogTimerPathLength + catalogTimerFileNameFallbackLength + 1u] = '\0';

      for (std::size_t index = 0u; index != catalogTimerFileNameFallbackLength; ++index)
        catalog -> timerPath[catalogTimerPathLength + index + 1u] = catalogTimerFileNameFallback[index];

      catalogTimerPathLength    += catalogTimerFileNameFallbackLength + 1u;
      catalog -> timerFileStream = std::fopen(catalog -> timerPath, "wb+");
    }
  }

  // ...
  if (NULL == catalog -> timerFileStream) {
    (void) catalog -> warn("Cataloger exited; No file for the catalog's internal clock specified");
    return catalog -> exit(EXIT_FAILURE);
  }

  /* ... ->> Activate internal clock */
  #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
    // TODO (Lapys) -> `usleep(…)` → `nanosleep(…)`
  #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
    /* ... ->> Windows Task Scheduler */
    if (not catalog -> clocked and not catalog -> rerun)
    if (NULL != libraries[credui].module and NULL != libraries[kernel32].module and NULL != libraries[ole32].module and NULL != libraries[oleaut32].module) {
      HRESULT (*const CoCreateInstance)                  (REFCLSID, LPUNKNOWN, DWORD, REFIID, LPVOID)                                                         = reinterpret_cast<HRESULT         (*)(REFCLSID, LPUNKNOWN, DWORD, REFIID, LPVOID)>                                                        (::GetProcAddress(libraries[ole32]   .module, "CoCreateInstance"));
      HRESULT (*const CoInitializeEx)                    (LPVOID, DWORD)                                                                                      = reinterpret_cast<HRESULT         (*)(LPVOID, DWORD)>                                                                                     (::GetProcAddress(libraries[ole32]   .module, "CoInitializeEx"));
      HRESULT (*const CoInitializeSecurity)              (PSECURITY_DESCRIPTOR, LONG, SOLE_AUTHENTICATION_SERVICE*, void*, DWORD, DWORD, void*, DWORD, void*) = reinterpret_cast<HRESULT         (*)(PSECURITY_DESCRIPTOR, LONG, SOLE_AUTHENTICATION_SERVICE*, void*, DWORD, DWORD, void*, DWORD, void*)>(::GetProcAddress(libraries[ole32]   .module, "CoInitializeSecurity"));
      void    (*const CoUninitialize)                    ()                                                                                                   = reinterpret_cast<void            (*)()>                                                                                                  (::GetProcAddress(libraries[ole32]   .module, "CoUninitialize"));
      DWORD   (*const CredUIPromptForCredentialsW)       (PCREDUI_INFOW, PCWSTR, PCtxtHandle, DWORD, PWSTR, ULONG, PWSTR, ULONG, BOOL*, DWORD)                = reinterpret_cast<CREDUIAPI DWORD (*)(PCREDUI_INFOW, PCWSTR, PCtxtHandle, DWORD, PWSTR, ULONG, PWSTR, ULONG, BOOL*, DWORD)>               (::GetProcAddress(libraries[credui]  .module, "CredUIPromptForCredentialsW"));
      DWORD   (*const CredUIPromptForWindowsCredentialsW)(PCREDUI_INFOW, DWORD, ULONG*, LPCVOID, ULONG, LPVOID*, ULONG*, BOOL*, DWORD)                        = reinterpret_cast<CREDUIAPI DWORD (*)(PCREDUI_INFOW, DWORD, ULONG*, LPCVOID, ULONG, LPVOID*, ULONG*, BOOL*, DWORD)>                       (::GetProcAddress(libraries[credui]  .module, "CredUIPromptForWindowsCredentialsW"));
      BOOL    (*const CredUnPackAuthenticationBufferW)   (DWORD, PVOID, DWORD, LPWSTR, DWORD*, LPWSTR, DWORD*, LPWSTR, DWORD*)                                = reinterpret_cast<CREDUIAPI BOOL  (*)(DWORD, PVOID, DWORD, LPWSTR, DWORD*, LPWSTR, DWORD*, LPWSTR, DWORD*)>                               (::GetProcAddress(libraries[credui]  .module, "CredUnPackAuthenticationBufferW"));
      LPWSTR  (*const GetCommandLineW)                   ()                                                                                                   = reinterpret_cast<LPWSTR          (*)()>                                                                                                  (::GetProcAddress(libraries[kernel32].module, "GetCommandLineW"));
      DWORD   (*const GetModuleFileNameW)                (HMODULE, LPWSTR, DWORD)                                                                             = reinterpret_cast<DWORD           (*)(HMODULE, LPWSTR, DWORD)>                                                                            (::GetProcAddress(libraries[kernel32].module, "GetModuleFileNameW"));
      int     (*const MultiByteToWideChar)               (UINT, DWORD, LPCCH, int, LPWSTR, int)                                                               = reinterpret_cast<int             (*)(UINT, DWORD, LPCCH, int, LPWSTR, int)>                                                              (::GetProcAddress(libraries[kernel32].module, "MultiByteToWideChar"));
      BSTR    (*const SysAllocString)                    (OLECHAR const*)                                                                                     = reinterpret_cast<BSTR            (*)(OLECHAR const*)>                                                                                    (::GetProcAddress(libraries[oleaut32].module, "SysAllocString"));
      void    (*const SysFreeString)                     (BSTR)                                                                                               = reinterpret_cast<void            (*)(BSTR)>                                                                                              (::GetProcAddress(libraries[oleaut32].module, "SysFreeString"));
      HRESULT (*const VariantClear)                      (VARIANTARG*)                                                                                        = reinterpret_cast<HRESULT         (*)(VARIANTARG*)>                                                                                       (::GetProcAddress(libraries[oleaut32].module, "VariantClear"));
      void    (*const VariantInit)                       (VARIANTARG*)                                                                                        = reinterpret_cast<void            (*)(VARIANTARG*)>                                                                                       (::GetProcAddress(libraries[oleaut32].module, "VariantInit"));

      // ... -> Derived from `https://learn.microsoft.com/en-us/windows/win32/taskschd/daily-trigger-example--c---`
      if (NULL != CoCreateInstance and NULL != CoInitializeEx and NULL != CoInitializeSecurity and NULL != CoUninitialize and NULL != SysAllocString and NULL != VariantInit and (NULL != CredUIPromptForCredentialsW or (NULL != CredUIPromptForWindowsCredentialsW and NULL != CredUnPackAuthenticationBufferW)))
      if (SUCCEEDED(CoInitializeEx(static_cast<LPVOID>(NULL), ::COINIT_MULTITHREADED))) {
        #ifdef __DATE__ // --> "Mmm DD YYYY"
          char const DATE[12] = __DATE__; // --> std::asctime(…)
        #else
          char const DATE[] = "Jan 00 2024";
        #endif
        #ifdef __TIME__ // --> "HH:MM:SS"
          char const TIME[9] = __TIME__;
        #else
          char const TIME[] = "12:00:00";
        #endif
        LPVOID              credentialsAuthenticationBuffer                             = NULL;                                                   // --> CredUIPromptForWindowsCredentialsW(…)
        ULONG               credentialsAuthenticationBufferSize                         = 0u;                                                     // --> CredUIPromptForWindowsCredentialsW(…)
        ULONG               credentialsAuthenticationPackage                            = 0x00u;                                                  // --> CredUIPromptForWindowsCredentialsW(…)
        WCHAR               credentialsDomainName[CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1u] = L"";                                                    // --> CredUnPackAuthenticationBufferW   (…)
        DWORD               credentialsDomainNameSize                                   = sizeof credentialsDomainName / sizeof(WCHAR);           // --> CredUnPackAuthenticationBufferW   (…)
        WCHAR               credentialsPassword[CREDUI_MAX_PASSWORD_LENGTH + 1u]        = L"";                                                    // --> CredUIPromptForCredentialsW(…) or CredUnPackAuthenticationBufferW(…)
        DWORD               credentialsPasswordSize                                     = sizeof credentialsPassword / sizeof(WCHAR);             // --> CredUIPromptForCredentialsW(…) or CredUnPackAuthenticationBufferW(…)
        WCHAR const         credentialsPromptCaption[CREDUI_MAX_CAPTION_LENGTH]         = L"Cataloger";                                           // --> catalog -> applicationName
        WCHAR const         credentialsPromptMessage[CREDUI_MAX_MESSAGE_LENGTH]         = L"Set up internal clock via the Task Scheduler ⏱️";     //
        WCHAR               credentialsUsername[CREDUI_MAX_USERNAME_LENGTH + 1u]        = L"";                                                    // --> CredUIPromptForCredentialsW(…) or CredUnPackAuthenticationBufferW(…)
        DWORD               credentialsUsernameSize                                     = sizeof credentialsUsername / sizeof(WCHAR);             // --> CredUIPromptForCredentialsW(…) or CredUnPackAuthenticationBufferW(…)
        CREDUI_INFOW        credentialsUIInformation                                    = {};                                                     //
        IRegisteredTask    *registeredTask                                              = NULL;                                                   // ->> Must remain `NULL`
        int                 standardInputDescriptor                                     = -1;                                                     //
        bool                standardInputIsTeletype                                     = false;                                                  //
        bool                standardInputNewlined                                       = true;                                                   //
        IAction            *taskAction                                                  = NULL;                                                   //
        IActionCollection  *taskActionCollection                                        = NULL;                                                   //
        BSTR const          taskAuthor                                                  = SysAllocString(L"LapysDev");                            //
        BSTR const          taskDescription                                             = SysAllocString(L"Cataloger internal clock ⏱️");         //
        void               *taskDailyTrigger                                            = NULL;                                                   // --> IDailyTrigger*
        short const         taskDailyTriggerInterval                                    = 1;                                                      //
        BSTR  const         taskDailyTriggerName                                        = SysAllocString(L"checkup");                             //
        BSTR                taskDailyTriggerTimeEnd                                     = NULL;                                                   //
        WCHAR               taskDailyTriggerTimeEndBuffer[]                             = L"20\0\0-01-01" "T" "\0\0:\0\0:\0\0";                   // --> YYYY-MM-DDTHH:MM:SS(+-)(timezone)
        BSTR                taskDailyTriggerTimeStart                                   = NULL;                                                   //
        WCHAR               taskDailyTriggerTimeStartBuffer[]                           = L"20\0\0-01-01" "T" "\0\0:\0\0:\0\0";                   // --> YYYY-MM-DDTHH:MM:SS(+-)(timezone)
        ITaskDefinition    *taskDefinition                                              = NULL;                                                   //
        void               *taskExecutableAction                                        = NULL;                                                   // --> IExecAction*
        BSTR                taskExecutableArguments                                     = NULL;                                                   // --> GetCommandLineW(…)
        WCHAR              *taskExecutableArgumentsBuffer                               = NULL;                                                   //
        BSTR                taskExecutablePath                                          = NULL;                                                   // --> GetModuleFileNameW(…)
        WCHAR               taskExecutablePathBuffer[MAX_PATH + 1u]                     = {};                                                     //
        std::size_t const   taskExecutablePathBufferLength                              = sizeof taskExecutablePathBuffer / sizeof(WCHAR);        //
        ITaskFolder        *taskFolder                                                  = NULL;                                                   //
        VARIANT             taskFolderPassword                                          = {};                                                     //
        BSTR const          taskFolderPath                                              = SysAllocString(L"\\");                                  // ->> Root folder
        VARIANT             taskFolderSecurityDescriptor                                = {};                                                     //
        VARIANT             taskFolderUsername                                          = {};                                                     //
        BSTR const          taskName                                                    = SysAllocString(L"Cataloger");                           //
        IRegistrationInfo  *taskRegistrationInformation                                 = NULL;                                                   //
        IRepetitionPattern *taskRepititionPattern                                       = NULL;                                                   //
        BSTR const          taskRepititionPatternDuration                               = SysAllocString(L"PT4M");                                // ->> `https://learn.microsoft.com/en-us/windows/win32/taskschd/taskschedulerschema-duration-repetitiontype-element`
        BSTR const          taskRepititionPatternInterval                               = SysAllocString(L"PT1M");                                // ->> `https://learn.microsoft.com/en-us/windows/win32/taskschd/taskschedulerschema-interval-repetitiontype-element`
        void               *taskService                                                 = NULL;                                                   // --> ITaskService*
        VARIANT             taskServiceDomain                                           = {};                                                     //
        VARIANT             taskServicePassword                                         = {};                                                     //
        VARIANT             taskServiceServerName                                       = {};                                                     //
        VARIANT             taskServiceUser                                             = {};                                                     //
        ITrigger           *taskTrigger                                                 = NULL;                                                   //
        ITriggerCollection *taskTriggerCollection                                       = NULL;                                                   //
        struct {
          std::time_t const value;                //
          unsigned int      year;                 // --> YYYY
          unsigned int      hour, minute, second; // --> HH:MM:SS
        } time = {std::time(static_cast<std::time_t*>(NULL)), 0000u, 00u, 00u, 00u};

        // ... --> time = …;
        for (struct { char const *text; unsigned int *time; std::size_t begin, end; } const indexes[] = {
          {TIME, &time.hour,   0u, 1u},
          {TIME, &time.minute, 3u, 4u},
          {TIME, &time.second, 6u, 7u},
          {DATE, &time.year,   7u, 10u}
        }, *index = indexes; index != indexes + (sizeof indexes / sizeof *indexes); ++index) {
          for (std::size_t subindex = index -> end + 1u; index -> begin != subindex--; )
          switch (index -> text[subindex]) {
            case '0': *(index -> time) = (*(index -> time) * 10u) + 0u; break;
            case '1': *(index -> time) = (*(index -> time) * 10u) + 1u; break;
            case '2': *(index -> time) = (*(index -> time) * 10u) + 2u; break;
            case '3': *(index -> time) = (*(index -> time) * 10u) + 3u; break;
            case '4': *(index -> time) = (*(index -> time) * 10u) + 4u; break;
            case '5': *(index -> time) = (*(index -> time) * 10u) + 5u; break;
            case '6': *(index -> time) = (*(index -> time) * 10u) + 6u; break;
            case '7': *(index -> time) = (*(index -> time) * 10u) + 7u; break;
            case '8': *(index -> time) = (*(index -> time) * 10u) + 8u; break;
            case '9': *(index -> time) = (*(index -> time) * 10u) + 9u; break;
          }
        }

        if (time.value != static_cast<std::time_t>(-1)) {
          struct std::tm *const calenderTime = std::gmtime(&time.value);

          if (NULL != calenderTime) {
            time.hour   = calenderTime -> tm_hour;
            time.minute = calenderTime -> tm_min;
            time.second = calenderTime -> tm_sec  % /* ->> Correct for C89 leap-second defect */ 61;
            time.year   = calenderTime -> tm_year + 1900;
          }
        }

        // ... --> taskExecutablePath… = …;
        if (NULL == GetModuleFileNameW or 0u == GetModuleFileNameW(static_cast<HMODULE>(NULL), taskExecutablePathBuffer, MAX_PATH + 1u)) {
          union { wchar_t *unicode; char *nonUnicode; } pointer = {NULL};

          // ...
          taskExecutablePathBuffer[0] = L'\0';

          if (0 == ::_get_wpgmptr(&pointer.unicode)) {
            for (std::size_t index = 0u; ; ++index) {
              taskExecutablePathBuffer[index] = pointer.unicode[index];
              if (L'\0' == pointer.unicode[index]) break;
            }
          }

          else if (NULL != MultiByteToWideChar) {
            pointer.nonUnicode = NULL;
            pointer.nonUnicode = 0 != ::_get_pgmptr(&pointer.nonUnicode) or NULL == pointer.nonUnicode ? arguments[0] : pointer.nonUnicode;

            if (NULL != pointer.nonUnicode)
            if (taskExecutablePathBufferLength >= static_cast<unsigned>(MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, pointer.nonUnicode, -1, static_cast<LPWSTR>(NULL), 0))) {
              if (0 == MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, pointer.nonUnicode, -1, taskExecutablePathBuffer, taskExecutablePathBufferLength))
              taskExecutablePathBuffer[0] = L'\0';
            }
          }
        }

        // ... --> taskExecutableArguments… = …;
        if (NULL != GetCommandLineW) {
          LPWSTR const      commandLine                    = GetCommandLineW();
          std::size_t       commandLineLength              = 0u;
          WCHAR       const commandLineRerunArgument[]     = L"--rerun";
          std::size_t const commandLineRerunArgumentLength = (sizeof commandLineRerunArgument / sizeof(WCHAR)) - 1u;

          // ...
          while (L'\0' != commandLine[commandLineLength])
          ++commandLineLength;

          taskExecutableArgumentsBuffer = ::new (std::nothrow) WCHAR[commandLineLength + commandLineRerunArgumentLength + /* ->> NUL terminator */ 1u];

          if (NULL != taskExecutableArgumentsBuffer) {
            taskExecutableArgumentsBuffer[commandLineLength + commandLineRerunArgumentLength] = L'\0';

            for (std::size_t index = 0u; index != commandLineLength; ++index)
            taskExecutableArgumentsBuffer[index] = commandLine[index];

            for (std::size_t index = 0u; index != commandLineRerunArgumentLength; ++index)
            taskExecutableArgumentsBuffer[commandLineLength + index] = commandLineRerunArgument[index];
          }
        }

        // ... --> taskDailyTriggerTime…Buffer[…] = …;
        for (struct { WCHAR *text; unsigned int time; std::size_t begin, end; } indexes[] = {
          {taskDailyTriggerTimeEndBuffer,   time.hour,        11u, 12u},
          {taskDailyTriggerTimeEndBuffer,   time.minute,      14u, 15u},
          {taskDailyTriggerTimeEndBuffer,   time.second,      17u, 18u},
          {taskDailyTriggerTimeEndBuffer,   time.year + 100u, 0u,  3u},
          {taskDailyTriggerTimeStartBuffer, time.hour,        11u, 12u},
          {taskDailyTriggerTimeStartBuffer, time.minute,      14u, 15u},
          {taskDailyTriggerTimeStartBuffer, time.second,      17u, 18u},
          {taskDailyTriggerTimeStartBuffer, time.year,        0u,  3u},
        }, *index = indexes; index != indexes + (sizeof indexes / sizeof *indexes); ++index) {
          for (std::size_t subindex = index -> end + 1u; index -> begin != subindex--; index -> time /= 10u)
          index -> text[subindex] = "0123456789"[index -> time % 10u];
        }

        // ...
        VariantInit(&taskFolderPassword);
        VariantInit(&taskFolderSecurityDescriptor);
        VariantInit(&taskFolderUsername);
        VariantInit(&taskServiceDomain);
        VariantInit(&taskServicePassword);
        VariantInit(&taskServiceServerName);
        VariantInit(&taskServiceUser);

        credentialsPassword[credentialsPasswordSize - 1u] = L'\0';
        credentialsUsername[credentialsUsernameSize - 1u] = L'\0';
        credentialsUIInformation.cbSize                   = sizeof(CREDUI_INFOW);
        credentialsUIInformation.hbmBanner                = static_cast<HBITMAP>(NULL);
        credentialsUIInformation.hwndParent               = static_cast<HWND>   (NULL);
        credentialsUIInformation.pszCaptionText           = credentialsPromptCaption;
        credentialsUIInformation.pszMessageText           = credentialsPromptMessage;
        taskDailyTriggerTimeEnd                           = SysAllocString(taskDailyTriggerTimeEndBuffer);
        taskDailyTriggerTimeStart                         = SysAllocString(taskDailyTriggerTimeStartBuffer);
        taskFolderPassword          .vt                   = ::VT_BSTR;
        taskFolderSecurityDescriptor.bstrVal              = NULL;
        taskFolderSecurityDescriptor.vt                   = ::VT_BSTR;
        taskFolderUsername          .vt                   = ::VT_BSTR;
        taskExecutableArguments                           = NULL != taskExecutableArgumentsBuffer ? SysAllocString(taskExecutableArgumentsBuffer) : NULL;
        taskExecutablePathBuffer[MAX_PATH]                = L'\0';
        taskExecutablePath                                = SysAllocString(taskExecutablePathBuffer);

        ::delete[] taskExecutableArgumentsBuffer;

        if (
          NULL  != taskAuthor                    and
          NULL  != taskDailyTriggerName          and
          NULL  != taskDailyTriggerTimeEnd       and
          NULL  != taskDailyTriggerTimeStart     and
          NULL  != taskExecutableArguments       and
          NULL  != taskExecutablePath            and
          L'\0' != taskExecutablePathBuffer[0]   and
          NULL  != taskFolderPath                and
          NULL  != taskName                      and
          NULL  != taskRepititionPatternDuration and
          NULL  != taskRepititionPatternInterval
        ) do {
          if (FAILED(CoInitializeSecurity(static_cast<PSECURITY_DESCRIPTOR>(NULL), -1L, static_cast<SOLE_AUTHENTICATION_SERVICE*>(NULL), static_cast<void*>(NULL), RPC_C_AUTHN_LEVEL_PKT_PRIVACY, RPC_C_IMP_LEVEL_IMPERSONATE, static_cast<void*>(NULL), 0x00u, static_cast<void*>(NULL)))) break;
          if (FAILED(CoCreateInstance    (::CLSID_TaskScheduler, static_cast<LPUNKNOWN>(NULL), ::CLSCTX_INPROC_SERVER, ::IID_ITaskService, &taskService)))                                                                                                                                  break;
          if (NULL == taskService)                                                                                                                                                                                                                                                          break;

          if (FAILED(static_cast<ITaskService*>(taskService) -> lpVtbl -> Connect  (static_cast<ITaskService*>(taskService), taskServiceServerName, taskServiceUser, taskServiceDomain, taskServicePassword))) break;
          if (FAILED(static_cast<ITaskService*>(taskService) -> lpVtbl -> GetFolder(static_cast<ITaskService*>(taskService), taskFolderPath, &taskFolder)))                                                    break;
          if (NULL == taskFolder)                                                                                                                                                                              break;

          if (FAILED(static_cast<ITaskService*>(taskService) -> lpVtbl -> NewTask(static_cast<ITaskService*>(taskService), 0x00u, &taskDefinition))) break;
          if (NULL == taskDefinition)                                                                                                                break;

          if (FAILED(taskDefinition -> lpVtbl -> get_RegistrationInfo(taskDefinition, &taskRegistrationInformation))) break;
          if (NULL == taskRegistrationInformation)                                                                    break;

          if (FAILED(taskRegistrationInformation -> lpVtbl -> put_Description(taskRegistrationInformation, taskDescription))) { /* Do nothing… */ }
          if (FAILED(taskRegistrationInformation -> lpVtbl -> put_Author     (taskRegistrationInformation, taskAuthor)))            break;
          if (FAILED(taskDefinition              -> lpVtbl -> get_Triggers   (taskDefinition,             &taskTriggerCollection))) break;
          if (NULL == taskTriggerCollection)                                                                                        break;

          if (FAILED(taskTriggerCollection -> lpVtbl -> Create(taskTriggerCollection, ::TASK_TRIGGER_DAILY, &taskTrigger))) break;
          if (NULL == taskTrigger)                                                                                          break;

          if (FAILED(taskTrigger -> lpVtbl -> QueryInterface(taskTrigger, ::IID_IDailyTrigger, &taskDailyTrigger))) break;
          if (NULL == taskDailyTrigger)                                                                             break;

          if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> lpVtbl -> put_DaysInterval (static_cast<IDailyTrigger*>(taskDailyTrigger),  taskDailyTriggerInterval)))  break;
          if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> lpVtbl -> put_EndBoundary  (static_cast<IDailyTrigger*>(taskDailyTrigger),  taskDailyTriggerTimeEnd)))   break;
          if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> lpVtbl -> put_Id           (static_cast<IDailyTrigger*>(taskDailyTrigger),  taskDailyTriggerName)))      break;
          if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> lpVtbl -> put_StartBoundary(static_cast<IDailyTrigger*>(taskDailyTrigger),  taskDailyTriggerTimeStart))) break;
          if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> lpVtbl -> get_Repetition   (static_cast<IDailyTrigger*>(taskDailyTrigger), &taskRepititionPattern)))     break;
          if (NULL == taskRepititionPattern)                                                                                                                                   break;

          if (FAILED(taskRepititionPattern -> lpVtbl -> put_Duration(taskRepititionPattern, taskRepititionPatternDuration))) break;
          if (FAILED(taskRepititionPattern -> lpVtbl -> put_Interval(taskRepititionPattern, taskRepititionPatternInterval))) break;
          if (FAILED(taskDefinition        -> lpVtbl -> get_Actions (taskDefinition,       &taskActionCollection)))          break;
          if (NULL == taskActionCollection)                                                                                  break;

          if (FAILED(taskActionCollection -> lpVtbl -> Create(taskActionCollection, ::TASK_ACTION_EXEC, &taskAction))) break;
          if (NULL == taskAction)                                                                                      break;

          if (FAILED(taskAction -> lpVtbl -> QueryInterface(taskAction, ::IID_IExecAction, &taskExecutableAction))) break;
          if (NULL == taskExecutableAction)                                                                         break;

          if (FAILED(static_cast<IExecAction*>(taskExecutableAction) -> lpVtbl -> put_Arguments(static_cast<IExecAction*>(taskExecutableAction), taskExecutableArguments))) break;
          if (FAILED(static_cast<IExecAction*>(taskExecutableAction) -> lpVtbl -> put_Path     (static_cast<IExecAction*>(taskExecutableAction), taskExecutablePath)))      break;

          // ... --> credentialsPassword = …; credentialsUsername = …;
          credentialsAuthenticationBuffer = &credentialsAuthenticationBuffer;
          do {
            // --> catalog -> message(credentialsPromptMessage);
            if (EOF == std::fputs(catalog -> messagePrefix, stdout))
            break;

            (void) std::fputws(credentialsPromptMessage, stdout);
            (void) std::fputs (catalog -> messageSuffix, stdout);
          } while (false);

          // ...
          if (NULL != credentialsAuthenticationBuffer) { // --> std::fgetws(…)
            (void) std::fwide(stdin, +1);

            standardInputDescriptor = ::_fileno(stdin);
            standardInputIsTeletype = standardInputDescriptor != -1 and 0 != ::_isatty(standardInputDescriptor);

            for (struct { wchar_t const detailMessage[14u + /* ->> NUL terminator */ 1u]; WCHAR *detail; std::size_t detailLength; } const credentials[] = {
              {L"\r\n" "  " "Username: ", credentialsUsername, credentialsUsernameSize - 1u},
              {L"\r\n" "  " "Password: ", credentialsPassword, credentialsPasswordSize - 1u}
            }, *credential = credentials; credential != credentials + (sizeof credentials / sizeof *credentials); ++credential) {
              if (NULL == credentialsAuthenticationBuffer)
              break;

              // ...
              if (EOF == std::fputws(credential -> detailMessage + (standardInputIsTeletype and standardInputNewlined ? /* ->> CRLF newline */ 2u : 0u), stdout))
                credentialsAuthenticationBuffer = NULL;

              else for (std::size_t length = 0u; ; ++length) {
                std::wint_t character = WEOF;

                // ...
                if (credential -> detailLength <= length) {
                  (void) catalog -> warn("Unable to set up internal clock via the Task Scheduler; Insufficient memory");
                  credentialsAuthenticationBuffer = NULL;

                  break;
                }

                character             = std::fgetwc(stdin);
                standardInputNewlined = L'\n' == static_cast<wchar_t>(character);

                if (WEOF == character or standardInputNewlined) {
                  // credentialsAuthenticationBuffer = EILSEQ == errno ? NULL : credentialsAuthenticationBuffer;
                  credential -> detail[length] = L'\0';
                  break;
                }

                credential -> detail[length] = character;
              }
            }
          }

          if (NULL == credentialsAuthenticationBuffer) // --> CredUIPromptForWindowsCredentialsW(…)
          if (NULL != CredUIPromptForWindowsCredentialsW and NULL != CredUnPackAuthenticationBufferW) {
            DWORD const credentialsPrompted = CredUIPromptForWindowsCredentialsW(&credentialsUIInformation, 0x00u, &credentialsAuthenticationPackage, static_cast<LPCVOID>(NULL), 0u, &credentialsAuthenticationBuffer, &credentialsAuthenticationBufferSize, static_cast<BOOL*>(NULL), CREDUIWIN_ENUMERATE_CURRENT_USER | CREDUIWIN_GENERIC);

            // ...
            if (ERROR_CANCELLED == credentialsPrompted) {
              (void) catalog -> warn("Rejected internal clock set up");
              break;
            }

            else if (ERROR_SUCCESS == credentialsPrompted) {
              if (FALSE == CredUnPackAuthenticationBufferW(0x1u /* --> CRED_PACK_PROTECTED_CREDENTIALS */, credentialsAuthenticationBuffer, credentialsAuthenticationBufferSize, credentialsUsername, &credentialsUsernameSize, credentialsDomainName, &credentialsDomainNameSize, credentialsPassword, &credentialsPasswordSize))
              credentialsAuthenticationBuffer = NULL;
            }
          }

          if (NULL == credentialsAuthenticationBuffer) // --> CredUIPromptForCredentialsW(…)
          if (NULL != CredUIPromptForCredentialsW) {
            DWORD const credentialsPrompted = CredUIPromptForCredentialsW(&credentialsUIInformation, L"", static_cast<PCtxtHandle>(NULL), 0x00u, credentialsUsername, credentialsUsernameSize, credentialsPassword, credentialsPasswordSize, static_cast<BOOL*>(NULL), CREDUI_FLAGS_ALWAYS_SHOW_UI | CREDUI_FLAGS_DO_NOT_PERSIST | CREDUI_FLAGS_GENERIC_CREDENTIALS);

            // ...
            if (ERROR_CANCELLED == credentialsPrompted) {
              (void) catalog -> warn("Rejected internal clock set up");
              break;
            }
          }

          (void) taskFolder -> lpVtbl -> DeleteTask(taskFolder, taskName, 0x00L);
          taskFolderPassword.bstrVal = SysAllocString(credentialsPassword);
          taskFolderUsername.bstrVal = SysAllocString(credentialsUsername);

          if (FAILED(taskFolder -> lpVtbl -> RegisterTaskDefinition(taskFolder, taskName, taskDefinition, ::TASK_CREATE_OR_UPDATE, taskFolderUsername, taskFolderPassword, ::TASK_LOGON_PASSWORD, taskFolderSecurityDescriptor, &registeredTask))) {
            (void) catalog -> warn("Unable to set up internal clock via the Task Scheduler; Failed task registration");
            break;
          }

          // catalog -> clocked = true;
        } while (false);

        // ...
        if (NULL != VariantClear) {
          (void) VariantClear(&taskFolderUsername);
          (void) VariantClear(&taskServiceDomain);
          (void) VariantClear(&taskServicePassword);
          (void) VariantClear(&taskServiceServerName);
          (void) VariantClear(&taskServiceUser);
        }

        if (NULL != taskAction)                  (void) taskAction                              -> lpVtbl -> Release(taskAction);
        if (NULL != taskActionCollection)        (void) taskActionCollection                    -> lpVtbl -> Release(taskActionCollection);
        if (NULL != taskRepititionPattern)       (void) taskRepititionPattern                   -> lpVtbl -> Release(taskRepititionPattern);
        if (NULL != taskTrigger)                 (void) taskTrigger                             -> lpVtbl -> Release(taskTrigger);
        if (NULL != taskTriggerCollection)       (void) taskTriggerCollection                   -> lpVtbl -> Release(taskTriggerCollection);
        if (NULL != taskRegistrationInformation) (void) taskRegistrationInformation             -> lpVtbl -> Release(taskRegistrationInformation);
        if (NULL != taskDefinition)              (void) taskDefinition                          -> lpVtbl -> Release(taskDefinition);
        if (NULL != taskFolder)                  (void) taskFolder                              -> lpVtbl -> Release(taskFolder);
        if (NULL != taskService)                 (void) static_cast<ITaskService*>(taskService) -> lpVtbl -> Release(static_cast<ITaskService*>(taskService));

        if (NULL != SysFreeString) {
          SysFreeString(taskAuthor);
          SysFreeString(taskDailyTriggerName);
          SysFreeString(taskDailyTriggerTimeEnd);
          SysFreeString(taskDailyTriggerTimeStart);
          SysFreeString(taskDescription);
          SysFreeString(taskExecutableArguments);
          SysFreeString(taskExecutablePath);
          SysFreeString(taskFolderPath);
          SysFreeString(taskName);
          SysFreeString(taskRepititionPatternDuration);
          SysFreeString(taskRepititionPatternInterval);
        }

        CoUninitialize();
      }
    }

    /* ... ->> Windows Services */
    if (not catalog -> clocked)
    if (NULL != libraries[advapi32].module) {
      BOOL (*const StartServiceCtrlDispatcherW)(SERVICE_TABLE_ENTRYW const*) = reinterpret_cast<BOOL (*)(SERVICE_TABLE_ENTRYW const*)>(::GetProcAddress(libraries[advapi32].module, "StartServiceCtrlDispatcherW"));
      struct /* final */ {
        static void WINAPI main(DWORD count, LPWSTR arguments[]) {
          // // Global variables
          // SERVICE_STATUS g_ServiceStatus = {};
          // SERVICE_STATUS_HANDLE g_StatusHandle = nullptr;
          // HANDLE g_ServiceStopEvent = INVALID_HANDLE_VALUE;

          // // Function that performs the task
          // void PerformTask() {
          //     // Task: Print message to console (or any other function/task)
          //     std::cout << "Task is being performed" << std::endl;
          // }

          // // Function that will be called every 24 hours
          // void CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
          //     PerformTask(); // Execute the task
          // }

          // // Service control handler function
          // void WINAPI ServiceCtrlHandler(DWORD CtrlCode) {
          //     switch (CtrlCode) {
          //         case SERVICE_CONTROL_STOP:
          //             if (g_ServiceStatus.dwCurrentState != SERVICE_RUNNING)
          //                 break;

          //             g_ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
          //             SetServiceStatus(g_StatusHandle, &g_ServiceStatus);

          //             // Signal the service to stop
          //             SetEvent(g_ServiceStopEvent);
          //             break;

          //         default:
          //             break;
          //     }
          // }

          // // Main service function
          // void WINAPI ServiceMain(DWORD argc, LPTSTR *argv) {
          //     g_StatusHandle = RegisterServiceCtrlHandler(_T("MyService"), ServiceCtrlHandler);
          //     if (g_StatusHandle == nullptr) {
          //         return;
          //     }

          //     // Service status initialization
          //     g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
          //     g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
          //     g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
          //     g_ServiceStatus.dwWin32ExitCode = 0;
          //     g_ServiceStatus.dwServiceSpecificExitCode = 0;
          //     g_ServiceStatus.dwCheckPoint = 0;

          //     // Register the service status
          //     SetServiceStatus(g_StatusHandle, &g_ServiceStatus);

          //     // Create an event to signal service stop
          //     g_ServiceStopEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
          //     if (g_ServiceStopEvent == nullptr) {
          //         g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
          //         g_ServiceStatus.dwWin32ExitCode = GetLastError();
          //         SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
          //         return;
          //     }

          //     // Create a timer to execute the task every 24 hours (86400000 milliseconds)
          //     HANDLE hTimer = nullptr;
          //     HANDLE hTimerQueue = CreateTimerQueue();
          //     if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, TimerRoutine, nullptr, 0, 86400000, 0)) {
          //         g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
          //         g_ServiceStatus.dwWin32ExitCode = GetLastError();
          //         SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
          //         return;
          //     }

          //     // Wait until the service is stopped
          //     WaitForSingleObject(g_ServiceStopEvent, INFINITE);

          //     // Cleanup and stop
          //     DeleteTimerQueue(hTimerQueue);
          //     CloseHandle(g_ServiceStopEvent);

          //     g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
          //     SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
          // }
        }
      } const service = {};

      // ...
      if (NULL != StartServiceCtrlDispatcher) {
        SERVICE_TABLE_ENTRYW const serviceEntries[] = {{L"Cataloger", reinterpret_cast<LPSERVICE_MAIN_FUNCTIONW>(&service.main)}, {NULL, NULL}};
        catalog -> clocked = FALSE != StartServiceCtrlDispatcher(serviceEntries);
      }
    }

    // TODO (Lapys) -> `WaitForSingleObject(…)` → `SetTimer(…)` → `Sleep(…)`
    if (not catalog -> clocked) {}
  #else
  #endif

  // GET CURRENT DATE/ TIME
  // CHECK IF TIME ELAPSED OR IF RUN FIRST TIME
  // SPAWN LOG not as child process; format: 2023–07–07.log
  // HELP SCREEN?
  // ABOUT SCREEN

  std::printf("[...]: 0x%02lX {allocated: %4.5s, name: \"%s\"}" "\r\n", (unsigned long) reinterpret_cast<uintptr_t>(catalog -> timerFileStream), catalog -> timerPathAllocated ? "true" : "false", catalog -> timerPath);

  // ...
  return catalog -> exit(EXIT_SUCCESS);
}
