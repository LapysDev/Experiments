// COMPILE: del cataloger.exe && cls && clang++ -pedantic -std=c++98 -Wall -Wextra cataloger.cpp -o cataloger.exe -lcredui -lole32 -loleaut32 -ltaskschd && cataloger.exe A C:\Users\oluwa\…\cataloger-clock.dat & del cataloger.exe
// RUN    : cataloger C:/Users/oluwa/OneDrive/Lapys/Catalog C:/Users/oluwa/OneDrive/Lapys/Catalog/cataloger-clock.dat
#include <ciso646> // --> and, not, or
#include <climits> // --> CHAR_BIT
#include <clocale> // --> LC_ALL;                                            std::setlocale(…)
#include <csignal> // --> SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM; std::signal(…)
#include <cstddef> // --> NULL; std::size_t
#include <cstdio>  // --> _IONBF, EOF, L_tmpnam, stderr, stdout; std::FILE; std::fflush(…), std::fopen(…), std::fputs(…), std::fwrite(…), std::setvbuf(…), std::tmpfile(…), std::tmpnam(…)
#include <cstdlib> // --> EXIT_FAILURE, EXIT_SUCCESS;                       std::at_quick_exit(…), std::atexit(…), std::exit(…)
#include <ctime>   // --> std::time_t;                                      std::gmtime(…), std::time(…)
#include <new>     // --> delete, new; std:nothrow
#if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
# include <stdio.h>  // --> ::fileno(…)
# include <unistd.h> // --> ::isatty(…)
#elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
# define _CRT_SECURE_NO_WARNINGS
# define STRICT
# define UNICODE
# ifndef _WIN32_WINNT
#   define _WIN32_WINNT 0x0501 // --> _WIN32_WINNT_WINXP
# endif
# include <stdio.h>   // --> ::_get_pgmptr(…), ::_get_wpgmptr(…)
# include <windows.h> // --> FOREGROUND_RED, INVALID_HANDLE_VALUE, STD_ERROR_HANDLE, WINAPI; BOOL, CONSOLE_SCREEN_BUFFER_INFO, DWORD, HANDLE, HMODULE, LPCWSTR, LPDWORD, LPVOID, PCONSOLE_SCREEN_BUFFER_INFO, PSECURITY_DESCRIPTOR, TCHAR, UINT, WCHAR; ::GetModuleHandleExW(…), ::GetProcAddress(…), ::GetSystemDirectoryW(…)
#   include <oaidl.h>    // --> VARIANT
#   include <objbase.h>  // --> ::COINIT_MULTITHREADED; ::CoInitializeEx(…), ::CoInitializeSecurity(…), ::CoUninitialize(…)
#   include <objidl.h>   // --> SOLE_AUTHENTICATION_SERVICE
#   include <oleauto.h>  // --> ::SysAllocString(…), ::SysFreeString(…), ::VariantClear(…), ::VariantInit(…)
#   include <wincred.h>  // --> CREDUI_INFOW, PCtxtHandle; ::CredUIPromptForCredentialsW(…)
#   include <winerror.h> // --> FAILED, SUCCEEDED
#   include <winnt.h>    // --> HRESULT
#   include <wtypes.h>   // --> BSTR, ::VT_BSTR
#   if _WIN32_WINNT >= 0x0600 // --> _WIN32_WINNT_VISTA | _WIN32_WINNT_WS08
#     include <taskschd.h> // --> IAction, IActionCollection, IDailyTrigger, IRegisteredTask, IRegistrationInfo, IRepetitionPattern, ITaskDefinition, ITaskFolder, ITaskService, ITrigger, ITriggerCollection
#   endif
#endif

/* Main --> cataloger [log_directory] [clock_path] */
int main(int count, char* arguments[]) /* noexcept */ {
  static struct cataloger *catalog = NULL;
  struct cataloger /* final */ {
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

    static int exit(int const code) {
      if (NULL != catalog) {
        catalog -> applicationExitCode = code;

        if (catalog -> timerPathAllocated)
        ::delete[] catalog -> timerPath;
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
      NULL != catalog ? (void) catalog -> exit(catalog -> applicationExitCode) : (void) 00;
      std::exit(catalog -> applicationExitCode);
    }

    static bool warn(char const message[], std::FILE* const stream = stderr) {
      return catalog -> message(message, stream);
    }

    /* ... */
    int         applicationExitCode;
    char const *applicationName;
    char       *logDirectoryPath;
    char const *messagePrefix;
    char const *messageSuffix;
    std::FILE  *timerFileStream;
    char       *timerPath;
    bool        timerPathAllocated;
  } c = {};

  /* ... -> Initialization, then dynamic linking with vendor APIs */
  catalog                        = &c;                              //
  catalog -> applicationExitCode = EXIT_SUCCESS;                    //
  catalog -> applicationName     = "cataloger";                     //
  catalog -> logDirectoryPath    = count > 1 ? arguments[1] : NULL; //  ->> Filesystem location for storing catalogs; Assume NUL-terminated
  catalog -> messagePrefix       = "cataloger" ": ";                //
  catalog -> messageSuffix       = "\r\n";                          //
  catalog -> timerFileStream     = NULL;                            //
  catalog -> timerPath           = count > 2 ? arguments[2] : NULL; // ->> Filesystem location for serializing catalog timer; Assume NUL-terminated
  catalog -> timerPathAllocated  = false;                           //

  (void) std::signal   (SIGTERM, &catalog -> error); //
  (void) std::signal   (SIGSEGV, &catalog -> error); // ->> ¯\_(ツ)_/¯
  (void) std::signal   (SIGINT,  &catalog -> error); // ->> Handle possible user interrupts
  (void) std::signal   (SIGABRT, &catalog -> error); // ->> Handle `std::abort(…)` and `std::terminate(…)` (and `throw` expression) invocations
  (void) std::setlocale(LC_ALL,  "C.UTF-8");         //
  #if __cplusplus >= 201103L
    (void) std::at_quick_exit(&catalog -> quick_exit);
  #endif

  #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
    enum {
      credui, kernel32, ole32, oleaut32, taskschd,
      librariesLength // --> std::size_t{5zu}
    };

    BOOL                     (*FreeLibrary)             (HMODULE)                = NULL;
    HMODULE                  (*LoadLibraryExW)          (LPCWSTR, HANDLE, DWORD) = NULL;
    BOOL                     (*SetDefaultDllDirectories)(DWORD)                  = NULL;
    WCHAR                      libraryPath[MAX_PATH + 1u]                        = L"";
    UINT const                 libraryPathLength                                 = ::GetSystemDirectoryW(libraryPath, ((MAX_PATH + 1u) * sizeof(WCHAR)) / sizeof(TCHAR));
    static struct libraryinfo *libraries                                         = NULL;
    struct libraryinfo /* final */ {
      LPCWSTR const name;
      HMODULE       module;
      BOOL        (*unloader)(HMODULE);

      /* extern "C" */ static void exit() {
        for (struct libraryinfo *library = libraries; library != libraries + (NULL == libraries ? 0u : librariesLength); ++library)
        if (NULL != library -> unloader) {
          library -> unloader(library -> module); // --> FreeLibrary(…);
          library -> unloader = NULL;
        }
      }
    } l[librariesLength] = {
      {L"credui"   ".dll", NULL, NULL},
      {L"kernel32" ".dll", NULL, NULL},
      {L"ole32"    ".dll", NULL, NULL},
      {L"oleaut32" ".dll", NULL, NULL},
      {L"taskschd" ".dll", NULL, NULL}
    };

    // ...
    libraries                      = l;
    libraryPath[libraryPathLength] = L'\\';

    (void) std::atexit(&libraries -> exit);
    #if __cplusplus >= 201103L
      (void) std::at_quick_exit(&libraries -> exit);
    #endif

    if (0u != libraryPathLength) {
      // ... ->> Load the userland `kernel32` library
      for (WCHAR libraryName[] = L"kernel32" ".dll", *destination = libraryPath + (libraryPathLength + 1u), *source = libraryName; ; ++destination, ++source) {
        *destination = *source;
        if (L'\0' == *source) break;
      }

      if (FALSE != ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, libraryPath, &libraries[kernel32].module) and NULL != libraries[kernel32].module) {
        FreeLibrary              = reinterpret_cast<BOOL    (*)(HMODULE)>               (::GetProcAddress(libraries[kernel32].module, "FreeLibrary"));
        LoadLibraryExW           = reinterpret_cast<HMODULE (*)(LPCWSTR, HANDLE, DWORD)>(::GetProcAddress(libraries[kernel32].module, "LoadLibraryExW"));
        SetDefaultDllDirectories = reinterpret_cast<BOOL    (*)(DWORD)>                 (::GetProcAddress(libraries[kernel32].module, "SetDefaultDllDirectories"));
      }

      if (NULL != SetDefaultDllDirectories)
      SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_SYSTEM32);

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
    }
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
    char        catalogTimerFileNameFallback[L_tmpnam + 1u] = {};
    std::size_t catalogTimerFileNameFallbackLength          = 0u;
    std::size_t catalogTimerPathLength                      = 0u;
    bool        catalogTimerPathSuffixed                    = false; // ->> Determines if `::timerPath` (significantly) ends with `pathDelimiters[…]`
    char const  pathDelimiters[]                            = {'/'
      #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
        , '\\'
      #endif
    };
    std::size_t const pathDelimitersLength = sizeof pathDelimiters / sizeof(char);

    // ... --> catalogTimerFileNameFallback       = std::tmpnam(…) ?? …;
    //         catalogTimerFileNameFallbackLength = …;
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

    // ... --> catalogTimerPathLength   = …;
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

    // ... --> catalog -> timerFileStream = …;
    //         catalog -> timerPath…      = …;
    /* TODO: MERGE FOR BOTH VENDORS; UNC BECOMES GENERIC PREFIX */
    #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
      char             *catalogTimerPathBuffer          = NULL;
      bool              catalogTimerPathPrefixed        = false; // ->> Determines if `::timerPath` (significantly) begins with `catalogTimerPathUNCPrefix`
      char        const catalogTimerPathUNCPrefix[]     = "\\\\?\\";
      std::size_t       catalogTimerPathUNCPrefixLength = (sizeof catalogTimerPathUNCPrefix / sizeof(char)) - 1u;

      // ... --> catalogTimerPathPrefixed = …;
      for (std::size_t prefixIndex = 0u, timerIndex = 0u; ; ++prefixIndex, ++timerIndex) {
        switch (catalog -> timerPath[timerIndex]) {
          case ' ': case '\f': case '\n': case '\r': case '\t': case '\v':
          continue;
        }

        if (catalogTimerPathUNCPrefixLength == prefixIndex) {
          catalogTimerPathPrefixed = true;
          break;
        }

        if (catalog -> timerPath[timerIndex] != catalogTimerPathUNCPrefix[prefixIndex])
        break;
      }

      // ... --> catalogTimerPathBuffer = …;
      catalogTimerPathBuffer = ::new (std::nothrow) char[(catalogTimerPathPrefixed ? 0u : catalogTimerPathUNCPrefixLength) + catalogTimerPathLength + /* ->> Path delimiter */ 1u + catalogTimerFileNameFallbackLength + /* ->> NUL terminator */ 1u];

      if (NULL == catalogTimerPathBuffer) {
        if (catalogTimerPathPrefixed or MAX_PATH+0 >= catalogTimerPathLength + /* ->> Path delimiter */ 1u + catalogTimerFileNameFallbackLength + /* ->> NUL terminator */ 1u) {
          if (not catalogTimerPathSuffixed) {
            (void) catalog -> warn("Cataloger exited; No file for the catalog's internal clock specified");
            return catalog -> exit(EXIT_FAILURE);
          }

          catalogTimerPathBuffer          = ::new (std::nothrow) char[catalogTimerPathLength + /* ->> Path delimiter */ 1u + catalogTimerFileNameFallbackLength + /* ->> NUL terminator */ 1u];
          catalogTimerPathUNCPrefixLength = 0u;

          if (NULL == catalogTimerPathBuffer) {
            catalogTimerPathBuffer                   = ::new (std::nothrow) char[catalogTimerPathLength + /* ->> NUL terminator */ 1u];
            catalogTimerFileNameFallbackLength = 0u;

            if (NULL == catalogTimerPathBuffer) {
              (void) catalog -> warn("Cataloger exited; No file for the catalog's internal clock specified");
              return catalog -> exit(EXIT_FAILURE);
            }
          }
        }

        else {
          catalogTimerPathBuffer                   = ::new (std::nothrow) char[catalogTimerPathUNCPrefixLength + catalogTimerPathLength + /* ->> NUL terminator */ 1u];
          catalogTimerFileNameFallbackLength = 0u;

          if (NULL == catalogTimerPathBuffer) {
            catalogTimerPathBuffer          = ::new (std::nothrow) char[catalogTimerPathLength + /* ->> NUL terminator */ 1u];
            catalogTimerPathUNCPrefixLength = 0u;

            if (NULL == catalogTimerPathBuffer) {
              (void) catalog -> warn("Cataloger exited; No file for the catalog's internal clock specified");
              return catalog -> exit(EXIT_FAILURE);
            }
          }
        }
      }

      catalogTimerPathBuffer[catalogTimerPathLength] = '\0';

      // ...
      for (std::size_t index = 0u; index != catalogTimerPathLength; ++index)
        catalogTimerPathBuffer[index] = catalog -> timerPath[index] != '/' ? catalog -> timerPath[index] : '\\';

      catalog -> timerPath          = catalogTimerPathBuffer;
      catalog -> timerPathAllocated = true;
      catalog -> timerFileStream    = std::fopen(catalog -> timerPath, "wb+");

      if (NULL == catalog -> timerFileStream and 0u != catalogTimerPathUNCPrefixLength and not catalogTimerPathPrefixed) {
        for (std::size_t index = catalogTimerPathLength; index--; )
          catalog -> timerPath[catalogTimerPathUNCPrefixLength + index] = catalog -> timerPath[index];

        for (std::size_t index = catalogTimerPathUNCPrefixLength; index--; )
          catalog -> timerPath[index] = catalogTimerPathUNCPrefix[index];

        catalogTimerPathLength += catalogTimerPathUNCPrefixLength;
        catalog -> timerFileStream = std::fopen(catalog -> timerPath, "wb+");
      }

      if (NULL == catalog -> timerFileStream and 0u != catalogTimerFileNameFallbackLength) {
        catalog -> timerPath[catalogTimerPathLength]                                                 = '\\';
        catalog -> timerPath[catalogTimerPathLength + catalogTimerFileNameFallbackLength + 1u] = '\0';

        for (std::size_t index = 0u; index != catalogTimerFileNameFallbackLength; ++index)
          catalog -> timerPath[catalogTimerPathLength + index + 1u] = catalogTimerFileNameFallback[index];

        catalogTimerPathLength += catalogTimerFileNameFallbackLength + 1u;
        catalog -> timerFileStream = std::fopen(catalog -> timerPath, "wb+");
      }
    #else
      char *catalogTimerPathBuffer = NULL;

      // ...
      if (not catalogTimerPathSuffixed) {
        (void) catalog -> warn("Cataloger exited; No file for the catalog's internal clock specified");
        return catalog -> exit(EXIT_FAILURE);
      }

      catalogTimerPathBuffer = ::new (std::nothrow) char[catalogTimerPathLength + /* ->> Path delimiter */ 1u + catalogTimerFileNameFallbackLength + /* ->> NUL terminator */ 1u];

      if (NULL == catalogTimerPathBuffer) {
        catalogTimerPathBuffer                   = ::new (std::nothrow) char[catalogTimerPathLength + /* ->> NUL terminator */ 1u];
        catalogTimerFileNameFallbackLength = 0u;

        if (NULL == catalogTimerPathBuffer) {
          (void) catalog -> warn("Cataloger exited; No file for the catalog's internal clock specified");
          return catalog -> exit(EXIT_FAILURE);
        }
      }

      catalogTimerPathBuffer[catalogTimerPathLength] = '\0';

      for (std::size_t index = 0u; index != catalogTimerPathLength; ++index)
        catalogTimerPathBuffer[index] = catalog -> timerPath[index];

      catalog -> timerPath          = catalogTimerPathBuffer;
      catalog -> timerPathAllocated = true;
      catalog -> timerFileStream    = std::fopen(catalog -> timerPath, "wb+");

      if (NULL == catalog -> timerFileStream and 0u != catalogTimerFileNameFallbackLength) {
        catalog -> timerPath[catalogTimerPathLength]                                                 = '/';
        catalog -> timerPath[catalogTimerPathLength + catalogTimerFileNameFallbackLength + 1u] = '\0';

        for (std::size_t index = 0u; index != catalogTimerFileNameFallbackLength; ++index)
          catalog -> timerPath[catalogTimerPathLength + index + 1u] = catalogTimerFileNameFallback[index];

        catalogTimerPathLength += catalogTimerFileNameFallbackLength + 1u;
        catalog -> timerFileStream = std::fopen(catalog -> timerPath, "wb+");
      }
    #endif
  }

  if (NULL == catalog -> timerFileStream) {
    (void) catalog -> warn("Cataloger exited; No file for the catalog's internal clock specified");
    return catalog -> exit(EXIT_FAILURE);
  }

  // ... ->> NOW ACTUAL WORK
  #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
    // TODO (Lapys) -> `usleep(…)` → `nanosleep(…)`
  #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
    bool catalogClocked = false;

    // NOTE (Lapys) -> Derived from `https://learn.microsoft.com/en-us/windows/win32/taskschd/daily-trigger-example--c---`
    // TODO (Lapys) -> Windows Task Scheduler → Windows Services → `WaitForSingleObject(…)` → `SetTimer(…)` → `Sleep(…)`
    /* ... */
    if (false)
    if (SUCCEEDED(::CoInitializeEx(static_cast<LPVOID>(NULL), ::COINIT_MULTITHREADED))) {
      WCHAR               credentialsPassword[CREDUI_MAX_PASSWORD_LENGTH + 1u] = L"";                                             //
      WCHAR               credentialsUsername[CREDUI_MAX_USERNAME_LENGTH + 1u] = L"";                                             //
      CREDUI_INFOW        credentialsUIInformation                             = {};                                              //
      IRegisteredTask    *registeredTask                                       = NULL;                                            // ->> Must remain `NULL`
      IAction            *taskAction                                           = NULL;                                            //
      IActionCollection  *taskActionCollection                                 = NULL;                                            //
      BSTR const          taskAuthor                                           = ::SysAllocString(L"LapysDev");                   //
      void               *taskDailyTrigger                                     = NULL;                                            // --> IDailyTrigger*
      short const         taskDailyTriggerInterval                             = 1;                                               //
      BSTR  const         taskDailyTriggerName                                 = ::SysAllocString(L"checkup");                    //
      BSTR                taskDailyTriggerTimeEnd                              = NULL;                                            //
      WCHAR               taskDailyTriggerTimeEndBuffer[]                      = L"20xx-01-01T12:00:00";                          // --> YYYY-MM-DDTHH:MM:SS(+-)(timezone)
      BSTR                taskDailyTriggerTimeStart                            = NULL;                                            //
      WCHAR               taskDailyTriggerTimeStartBuffer[]                    = L"20xx-01-01T12:00:00";                          // --> YYYY-MM-DDTHH:MM:SS(+-)(timezone)
      ITaskDefinition    *taskDefinition                                       = NULL;                                            //
      void               *taskExecutableAction                                 = NULL;                                            // --> IExecAction*
      BSTR                taskExecutableArguments                              = ::SysAllocString(::GetCommandLineW());           //
      BSTR                taskExecutablePath                                   = NULL;                                            //
      WCHAR               taskExecutablePathBuffer[MAX_PATH + 1u]              = {};                                              //
      std::size_t const   taskExecutablePathBufferLength                       = sizeof taskExecutablePathBuffer / sizeof(WCHAR); //
      ITaskFolder        *taskFolder                                           = NULL;                                            //
      VARIANT             taskFolderPassword                                   = {};                                              //
      BSTR const          taskFolderPath                                       = ::SysAllocString(L"\\");                         // ->> Root folder
      VARIANT             taskFolderSecurityDescriptor                         = {};                                              //
      VARIANT             taskFolderUsername                                   = {};                                              //
      BSTR const          taskName                                             = ::SysAllocString(L"Cataloger checkup");          //
      IRegistrationInfo  *taskRegistrationInformation                          = NULL;                                            //
      IRepetitionPattern *taskRepititionPattern                                = NULL;                                            //
      BSTR const          taskRepititionPatternDuration                        = ::SysAllocString(L"PT4M");                       //
      BSTR const          taskRepititionPatternInterval                        = ::SysAllocString(L"PT1M");                       //
      void               *taskService                                          = NULL;                                            // --> ITaskService*
      VARIANT             taskServiceDomain                                    = {};                                              //
      VARIANT             taskServicePassword                                  = {};                                              //
      VARIANT             taskServiceServerName                                = {};                                              //
      VARIANT             taskServiceUser                                      = {};                                              //
      ITrigger           *taskTrigger                                          = NULL;                                            //
      ITriggerCollection *taskTriggerCollection                                = NULL;                                            //
      std::time_t const   time                                                 = std::time(static_cast<std::time_t*>(NULL));      //
      unsigned int        year                                                 = 2024u;                                           // --> YYYY

      // ...
      ::VariantInit(&taskFolderPassword);
      ::VariantInit(&taskFolderSecurityDescriptor);
      ::VariantInit(&taskFolderUsername);
      ::VariantInit(&taskServiceDomain);
      ::VariantInit(&taskServicePassword);
      ::VariantInit(&taskServiceServerName);
      ::VariantInit(&taskServiceUser);

      credentialsPassword[CREDUI_MAX_PASSWORD_LENGTH] = L'\0';
      credentialsUsername[CREDUI_MAX_USERNAME_LENGTH] = L'\0';
      credentialsUIInformation    .cbSize             = sizeof(CREDUI_INFOW);
      credentialsUIInformation    .hbmBanner          = static_cast<HBITMAP>(NULL);
      credentialsUIInformation    .hwndParent         = static_cast<HWND>   (NULL);
      credentialsUIInformation    .pszCaptionText     = L"Enter account information for task registration";
      credentialsUIInformation    .pszMessageText     = L"Account information for task registration";
      taskFolderPassword          .vt                 = ::VT_BSTR;
      taskFolderSecurityDescriptor.vt                 = ::VT_BSTR;
      taskFolderUsername          .vt                 = ::VT_BSTR;

      // ... --> taskDailyTriggerTimeEndBuffer[0‥3] = taskDailyTriggerTimeStartBuffer[0‥3] = __DATE__[7‥10] ?? std::itoa(std::gmtime(…) -> tm_year, …, 10);
      #ifdef __DATE__
        char const date[12] = __DATE__;

        // ...
        year = 0u;

        for (std::size_t index = 10u + 1u; index-- != 7u; )
        switch (date[index]) { // --> std::asctime(…)
          case '0': year = (year * 10u) + 0u; break;
          case '1': year = (year * 10u) + 1u; break;
          case '2': year = (year * 10u) + 2u; break;
          case '3': year = (year * 10u) + 3u; break;
          case '4': year = (year * 10u) + 4u; break;
          case '5': year = (year * 10u) + 5u; break;
          case '6': year = (year * 10u) + 6u; break;
          case '7': year = (year * 10u) + 7u; break;
          case '8': year = (year * 10u) + 8u; break;
          case '9': year = (year * 10u) + 9u; break;
        }
      #endif

      if (time != static_cast<std::time_t>(-1)) {
        std::tm *const calenderTime = std::gmtime(&time);
        year = NULL != calenderTime ? calenderTime -> tm_year + 1900 : year;
      }

      for (struct { WCHAR *text; unsigned int value; } years[] = {
        {taskDailyTriggerTimeEndBuffer,   year + 100u},
        {taskDailyTriggerTimeStartBuffer, year + 0u}
      }, *year = years; year != years + (sizeof years / sizeof *years); ++year) {
        for (std::size_t index = 3u + 1u; index--; year -> value /= 10u)
        switch (year -> value % 10u) {
          case 0u: year -> text[index] = '0'; break;
          case 1u: year -> text[index] = '1'; break;
          case 2u: year -> text[index] = '2'; break;
          case 3u: year -> text[index] = '3'; break;
          case 4u: year -> text[index] = '4'; break;
          case 5u: year -> text[index] = '5'; break;
          case 6u: year -> text[index] = '6'; break;
          case 7u: year -> text[index] = '7'; break;
          case 8u: year -> text[index] = '8'; break;
          case 9u: year -> text[index] = '9'; break;
        }
      }

      // ... --> taskExecutablePath… = …;
      if (0u == ::GetModuleFileNameW(static_cast<HMODULE>(NULL), taskExecutablePathBuffer, MAX_PATH + 1u)) {
        union { wchar_t *unicode; char *nonUnicode; } pointer = {NULL};

        // ...
        taskExecutablePathBuffer[0] = L'\0';

        if (0 != ::_get_wpgmptr(&pointer.unicode) or NULL == pointer.unicode) {
          pointer.nonUnicode = NULL;
          pointer.nonUnicode = 0 != ::_get_pgmptr(&pointer.nonUnicode) or NULL == pointer.nonUnicode ? arguments[0] : pointer.nonUnicode;

          if (NULL != pointer.nonUnicode) {
            if (taskExecutablePathBufferLength < static_cast<unsigned>(::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, pointer.nonUnicode, -1, taskExecutablePathBuffer, 0)) ? true : 0 == ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, pointer.nonUnicode, -1, taskExecutablePathBuffer, taskExecutablePathBufferLength))
            taskExecutablePathBuffer[0] = L'\0';
          }
        }

        else for (std::size_t index = 0u; ; ++index) {
          taskExecutablePathBuffer[index] = pointer.unicode[index];
          if (L'\0' == pointer.unicode[index]) break;
        }
      }

      // ...
      taskDailyTriggerTimeEnd            = ::SysAllocString(taskDailyTriggerTimeEndBuffer);
      taskDailyTriggerTimeStart          = ::SysAllocString(taskDailyTriggerTimeStartBuffer);
      taskExecutablePathBuffer[MAX_PATH] = L'\0';
      taskExecutablePath                 = ::SysAllocString(taskExecutablePathBuffer);

      if (
        NULL  != taskAuthor                    and
        NULL  != taskDailyTriggerName          and
        NULL  != taskDailyTriggerTimeEnd       and
        NULL  != taskDailyTriggerTimeStart     and
        NULL  != taskExecutablePath            and
        L'\0' != taskExecutablePathBuffer[0]   and
        NULL  != taskFolderPath                and
        NULL  != taskName                      and
        NULL  != taskRepititionPatternDuration and
        NULL  != taskRepititionPatternInterval
      ) do {
        if (FAILED(::CoInitializeSecurity(static_cast<PSECURITY_DESCRIPTOR>(NULL), -1L, static_cast<SOLE_AUTHENTICATION_SERVICE*>(NULL), static_cast<void*>(NULL), RPC_C_AUTHN_LEVEL_PKT_PRIVACY, RPC_C_IMP_LEVEL_IMPERSONATE, static_cast<void*>(NULL), 0x00u, static_cast<void*>(NULL)))) { std::puts("[ERROR #1]"); break; }
        if (FAILED(::CoCreateInstance    (::CLSID_TaskScheduler, static_cast<LPUNKNOWN>(NULL), ::CLSCTX_INPROC_SERVER, ::IID_ITaskService, &taskService)))                                                                                                                                  { std::puts("[ERROR #2]"); break; }
        if (NULL == taskService)                                                                                                                                                                                                                                                            { std::puts("[ERROR #3]"); break; }

        if (FAILED(static_cast<ITaskService*>(taskService) -> Connect  (taskServiceServerName, taskServiceUser, taskServiceDomain, taskServicePassword))) { std::puts("[ERROR #4]"); break; }
        if (FAILED(static_cast<ITaskService*>(taskService) -> GetFolder(taskFolderPath, &taskFolder)))                                                    { std::puts("[ERROR #5]"); break; }
        if (NULL == taskFolder)                                                                                                                           { std::puts("[ERROR #6]"); break; }

        (void) taskFolder -> DeleteTask(taskName, 0x00L);

        if (FAILED(static_cast<ITaskService*>(taskService) -> NewTask(0x00u, &taskDefinition))) { std::puts("[ERROR #7]"); break; }
        if (NULL == taskDefinition)                                                             { std::puts("[ERROR #8]"); break; }

        if (FAILED(taskDefinition -> get_RegistrationInfo(&taskRegistrationInformation))) { std::puts("[ERROR #9]"); break; }
        if (NULL == taskRegistrationInformation)                                          { std::puts("[ERROR #10]"); break; }

        if (FAILED(taskRegistrationInformation -> put_Author  (taskAuthor)))             { std::puts("[ERROR #11]"); break; }
        if (FAILED(taskDefinition              -> get_Triggers(&taskTriggerCollection))) { std::puts("[ERROR #12]"); break; }
        if (NULL == taskTriggerCollection)                                               { std::puts("[ERROR #13]"); break; }

        if (FAILED(taskTriggerCollection -> Create(::TASK_TRIGGER_DAILY, &taskTrigger))) { std::puts("[ERROR #14]"); break; }
        if (NULL == taskTrigger)                                                         { std::puts("[ERROR #15]"); break; }

        if (FAILED(taskTrigger -> QueryInterface(::IID_IDailyTrigger, &taskDailyTrigger))) { std::puts("[ERROR #16]"); break; }
        if (NULL == taskDailyTrigger)                                                      { std::puts("[ERROR #17]"); break; }

        if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> put_DaysInterval (taskDailyTriggerInterval)))  { std::puts("[ERROR #18]"); break; }
        if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> put_EndBoundary  (taskDailyTriggerTimeEnd)))   { std::puts("[ERROR #19]"); break; }
        if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> put_Id           (taskDailyTriggerName)))      { std::puts("[ERROR #20]"); break; }
        if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> put_StartBoundary(taskDailyTriggerTimeStart))) { std::puts("[ERROR #21]"); break; }
        if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> get_Repetition  (&taskRepititionPattern)))     { std::puts("[ERROR #22]"); break; }
        if (NULL == taskRepititionPattern)                                                                         { std::puts("[ERROR #23]"); break; }

        if (FAILED(taskRepititionPattern -> put_Duration(taskRepititionPatternDuration))) { std::puts("[ERROR #24]"); break; } // ->> `https://learn.microsoft.com/en-us/windows/win32/taskschd/taskschedulerschema-duration-repetitiontype-element`
        if (FAILED(taskRepititionPattern -> put_Interval(taskRepititionPatternInterval))) { std::puts("[ERROR #25]"); break; } // ->> `https://learn.microsoft.com/en-us/windows/win32/taskschd/taskschedulerschema-interval-repetitiontype-element`
        if (FAILED(taskDefinition        -> get_Actions (&taskActionCollection)))         { std::puts("[ERROR #26]"); break; }
        if (NULL == taskActionCollection)                                                 { std::puts("[ERROR #27]"); break; }

        if (FAILED(taskActionCollection -> Create(::TASK_ACTION_EXEC, &taskAction))) { std::puts("[ERROR #28]"); break; }
        if (NULL == taskAction)                                                      { std::puts("[ERROR #29]"); break; }

        if (FAILED(taskAction -> QueryInterface(::IID_IExecAction, &taskExecutableAction))) { std::puts("[ERROR #30]"); break; }
        if (NULL == taskExecutableAction)                                                   { std::puts("[ERROR #31]"); break; }

        if (FAILED(static_cast<IExecAction*>(taskExecutableAction) -> put_Arguments(taskExecutableArguments))) { std::puts("[ERROR #32]"); break; }
        if (FAILED(static_cast<IExecAction*>(taskExecutableAction) -> put_Path     (taskExecutablePath)))      { std::puts("[ERROR #33]"); break; }

        if (0x00u != ::CredUIPromptForCredentialsW(&credentialsUIInformation, L"", static_cast<PCtxtHandle>(NULL), 0x00u, credentialsUsername, sizeof credentialsUsername / sizeof(WCHAR), credentialsPassword, sizeof credentialsPassword / sizeof(WCHAR), static_cast<BOOL*>(NULL), CREDUI_FLAGS_ALWAYS_SHOW_UI | CREDUI_FLAGS_DO_NOT_PERSIST | CREDUI_FLAGS_GENERIC_CREDENTIALS)) {
          std::puts("[ERROR #34]");
          break;
        }

        taskFolderPassword          .bstrVal = ::SysAllocString(credentialsPassword);
        taskFolderSecurityDescriptor.bstrVal = ::SysAllocString(L"");
        taskFolderUsername          .bstrVal = ::SysAllocString(credentialsUsername);

        if (NULL == taskFolderPassword          .bstrVal) { std::puts("[ERROR #35]"); break; }
        if (NULL == taskFolderSecurityDescriptor.bstrVal) { std::puts("[ERROR #36]"); break; }
        if (NULL == taskFolderUsername          .bstrVal) { std::puts("[ERROR #37]"); break; }

        if (FAILED(taskFolder -> RegisterTaskDefinition(taskName, taskDefinition, TASK_CREATE_OR_UPDATE, taskFolderUsername, taskFolderPassword, TASK_LOGON_PASSWORD, taskFolderSecurityDescriptor, &registeredTask))) {
          std::puts("[ERROR #38]");
          break;
        }

        // ...
        catalogClocked = true;
      } while (false);

      // ...
      (void) ::VariantClear(&taskFolderUsername);
      (void) ::VariantClear(&taskServiceDomain);
      (void) ::VariantClear(&taskServicePassword);
      (void) ::VariantClear(&taskServiceServerName);
      (void) ::VariantClear(&taskServiceUser);

      if (NULL != taskAction)                  (void) taskAction                              -> Release();
      if (NULL != taskActionCollection)        (void) taskActionCollection                    -> Release();
      if (NULL != taskRepititionPattern)       (void) taskRepititionPattern                   -> Release();
      if (NULL != taskTrigger)                 (void) taskTrigger                             -> Release();
      if (NULL != taskTriggerCollection)       (void) taskTriggerCollection                   -> Release();
      if (NULL != taskRegistrationInformation) (void) taskRegistrationInformation             -> Release();
      if (NULL != taskDefinition)              (void) taskDefinition                          -> Release();
      if (NULL != taskFolder)                  (void) taskFolder                              -> Release();
      if (NULL != taskService)                 (void) static_cast<ITaskService*>(taskService) -> Release();

      if (NULL != taskAuthor)                    ::SysFreeString(taskAuthor);
      if (NULL != taskDailyTriggerName)          ::SysFreeString(taskDailyTriggerName);
      if (NULL != taskDailyTriggerTimeEnd)       ::SysFreeString(taskDailyTriggerTimeEnd);
      if (NULL != taskDailyTriggerTimeStart)     ::SysFreeString(taskDailyTriggerTimeStart);
      if (NULL != taskExecutableArguments)       ::SysFreeString(taskExecutableArguments);
      if (NULL != taskExecutablePath)            ::SysFreeString(taskExecutablePath);
      if (NULL != taskFolderPath)                ::SysFreeString(taskFolderPath);
      if (NULL != taskName)                      ::SysFreeString(taskName);
      if (NULL != taskRepititionPatternDuration) ::SysFreeString(taskRepititionPatternDuration);
      if (NULL != taskRepititionPatternInterval) ::SysFreeString(taskRepititionPatternInterval);

      ::CoUninitialize();
      (void) catalogClocked;
    }
  #endif

  // GET CURRENT DATE/ TIME
  // CHECK IF TIME ELAPSED OR IF RUN FIRST TIME
  // SPAWN LOG not as child process; format: 2023–07–07.log
  // look for non-busy waits
  // HELP SCREEN?
  // ABOUT SCREEN
  //
  // switch from pointers to indexes

  std::printf("[...]: 0x%02lX {allocated: %4.5s, name: \"%s\"}" "\r\n", (unsigned long) reinterpret_cast<uintptr_t>(catalog -> timerFileStream), catalog -> timerPathAllocated ? "true" : "false", catalog -> timerPath);
  // // ... ->> A more consistent `std::tm` binary format
  // struct timestamp {
  //   bool           daylightSavings : 1u;  // --> std::tm::tm_isdst {INT_MIN, 0}
  //   unsigned char  day             : 5u;  // --> std::tm::tm_mday  {1, 31}
  //   unsigned char  hour            : 5u;  // --> std::tm::tm_hour  {0, 23}
  //   unsigned char  minute          : 6u;  // --> std::tm::tm_min   {0, 59}
  //   unsigned char  month           : 4u;  // --> std::tm::tm_mon   {0, 11}
  //   unsigned char  second          : 6u;  // --> std::tm::tm_sec   {0, 60‥61}
  //   unsigned char  weekDay         : 3u;  // --> std::tm::tm_wday  {0, 6}
  //   unsigned short year            : 14u; // --> std::tm::tm_year  {1900 + ‥}
  //   unsigned short yearDay         : 9u;  // --> std::tm::tm_yday  {0, 365}
  // };

  //   double             catalogTimeSpan   = 0.0;                          // --> std::difftime(currentTime, catalogRecentTime)
  //   double /* const */ catalogTimeRange  = 86400.00;                     // ->> Observed time (in seconds) passed between `catalogTimes`; currently set to one single day
  //   std::time_t        catalogRecentTime = static_cast<std::time_t>(-1); // --> std::mktime(&catalogRecentDate)

  // ...
  return catalog -> exit(EXIT_SUCCESS);
}
