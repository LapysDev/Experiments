// COMPILE: del cataloger.exe && cls && clang++ -pedantic -std=c++98 -Wall -Wextra -Wno-c++11-long-long cataloger.cpp -o cataloger.exe -ltaskschd && cataloger.exe A C:\Users\oluwa\…\cataloger-clock.dat & del cataloger.exe
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
#   define _WIN32_WINNT 0x0600 // --> _WIN32_WINNT_WINXP+
# endif
# include <io.h>      // --> ::_isatty(…)
# include <stdio.h>   // --> ::_fileno(…), ::_get_pgmptr(…), ::_get_wpgmptr(…)
# include <windows.h> // --> CP_UTF8, ERROR_CANCELLED, ERROR_INVALID_HANDLE, ERROR_SUCCESS, FOREGROUND_GREEN, FOREGROUND_RED, INFINITE, INVALID_HANDLE_VALUE, MAX_PATH, MB_ERR_INVALID_CHARS, NO_ERROR, SC_MANAGER_ALL_ACCESS, SERVICE_ACCEPT_STOP, SERVICE_ALL_ACCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL, SERVICE_RUNNING, SERVICE_STOP_PENDING, SERVICE_STOPPED, SERVICE_WIN32_OWN_PROCESS, STD_ERROR_HANDLE, WINAPI; BOOL, CONSOLE_SCREEN_BUFFER_INFO, DWORD, HANDLE, HLOCAL, HMODULE, LONG, LPBOOL, LPCCH, LPCSTR, LPCVOID, LPCWCH, LPCWSTR, LPDWORD, LPSECURITY_ATTRIBUTES, LPSERVICE_STATUS, LPUNKNOWN, LPVOID, LPWSTR, OLECHAR, PCONSOLE_SCREEN_BUFFER_INFO, PCWSTR, PHANDLE, PSECURITY_DESCRIPTOR, PVOID, PWSTR, REFCLSID, REFIID, SC_HANDLE, SERVICE_STATUS, SERVICE_STATUS_HANDLE, SERVICE_TABLE_ENTRYW, TCHAR, UINT, VARIANTARG, WAIT_FAILED, WAITORTIMERCALLBACK, WCHAR; ::GetModuleHandleExW(…), ::GetProcAddress(…), ::GetSystemDirectoryW(…)
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

/* Main --> cataloger [log_directory] [clock_path] [rerun] */
int main(int count, char* arguments[]) /* noexcept */ {
  /* ... -> Vendor setup */
  #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
    enum {
      advapi32, credui, kernel32, ole32, oleaut32, shell32, taskschd,
      librariesLength // --> std::size_t{…}
    };

    WCHAR                      libraryPath[MAX_PATH + 1u] = L"";
    UINT const                 libraryPathLength          = ::GetSystemDirectoryW(libraryPath, ((MAX_PATH + 1u) * sizeof(WCHAR)) / sizeof(TCHAR));
    static struct libraryinfo *libraries                  = NULL;
    static struct libraryinfo /* final */ {
      LPCWSTR const name;
      HMODULE       moduleHandle;
      BOOL        (*unloader)(HMODULE);

      static void exit() /* extern "C" */ {
        for (struct libraryinfo *library = libraries; library != libraries + (NULL == libraries ? 0u : librariesLength); ++library)
        if (NULL != library -> moduleHandle and NULL != library -> unloader) {
          library -> unloader(library -> moduleHandle); // --> FreeLibrary(…)

          library -> moduleHandle = NULL;
          library -> unloader     = NULL;
        }
      }
    } l[librariesLength] = {
      {L"advapi32" ".dll", NULL, NULL},
      {L"credui"   ".dll", NULL, NULL},
      {L"kernel32" ".dll", NULL, NULL},
      {L"ole32"    ".dll", NULL, NULL},
      {L"oleaut32" ".dll", NULL, NULL},
      {L"shell32"  ".dll", NULL, NULL},
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
      BOOL    (*FreeLibrary)             (HMODULE)                = NULL;
      HMODULE (*LoadLibraryExW)          (LPCWSTR, HANDLE, DWORD) = NULL;
      BOOL    (*SetDefaultDllDirectories)(DWORD)                  = NULL;

      // ... ->> Load the userland `kernel32` library
      for (std::size_t index = 0u; ; ++index) {
        libraryPath[index + libraryPathLength + 1u] = libraries[kernel32].name[index];
        if (L'\0' == libraries[kernel32].name[index]) break;
      }

      if (FALSE != ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, libraryPath, &libraries[kernel32].moduleHandle))
      if (NULL != libraries[kernel32].moduleHandle) {
        FreeLibrary              = reinterpret_cast<BOOL    (*)(HMODULE)>               (::GetProcAddress(libraries[kernel32].moduleHandle, "FreeLibrary"));              // --> <windows.h>
        LoadLibraryExW           = reinterpret_cast<HMODULE (*)(LPCWSTR, HANDLE, DWORD)>(::GetProcAddress(libraries[kernel32].moduleHandle, "LoadLibraryExW"));           // --> <windows.h>
        SetDefaultDllDirectories = reinterpret_cast<BOOL    (*)(DWORD)>                 (::GetProcAddress(libraries[kernel32].moduleHandle, "SetDefaultDllDirectories")); // --> <windows.h>
      }

      if (NULL != SetDefaultDllDirectories)
      (void) SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_SYSTEM32);

      // ... ->> Load other used Windows API libraries —
      for (struct libraryinfo *library = libraries; library != libraries + librariesLength; ++library)
      if (NULL == library -> moduleHandle) { // ->> — except the already loaded userland `kernel32` library
        for (std::size_t index = 0u; ; ++index) {
          libraryPath[index + libraryPathLength + 1u] = library -> name[index];
          if (L'\0' == library -> name[index]) break;
        }

        if (FALSE != ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, libraryPath, &library -> moduleHandle))
        if (NULL != library -> moduleHandle) continue;

        library -> moduleHandle = LoadLibraryExW(libraryPath, static_cast<HANDLE>(NULL), LOAD_WITH_ALTERED_SEARCH_PATH);
        library -> unloader     = NULL == library -> moduleHandle ? NULL : FreeLibrary;
      }
    }
  #endif

  /* ... ->> Application `start()` */
  static struct cataloger *catalog = NULL;
  static struct cataloger /* final */ {
    enum               { MESSAGE_MAXIMUM_LENGTH = 256u }; // --> std::size_t
    union  formatinfo  { unsigned char metadata[32]; };   // ->> Arbitrarily-sized
    enum   formatstyle { FORMAT_INITIAL = 0x00u, FORMAT_ERROR, FORMAT_WARN };
    struct parsecmd /* final */ {
      /* ... ->> `NULL`-ish `::…name`s represent unrecognized command-line arguments */
      enum { ABOUT, CLOCK, HELP, LOG, RERUN } command;                           // ->> Command-line option identifier
      char const                             *name;                              // ->> Multi-byte NUL-terminated text representing the                                                          name of the command-line option; Optionally `NULL`
      char const                             *longName;                          // ->> Multi-byte NUL-terminated text representing the        long  (prefixed by `::commandLineOptionLongTag`)  name of the command-line option; Optionally `NULL`
      char const                             *shortName;                         // ->> Multi-byte NUL-terminated text representing the alias/ short (prefixed by `::commandLineOptionShortTag`) name of the command-line option; Optionally `NULL`
      std::size_t                             valueCount;                        // ->> Number of command-line arguments (after `::argument`) evaluated
      bool                                  (*validate)(struct parsecmd const*); // ->> Predicate function determining the validity of this command-line option; Called through command-line `parse()`; Optionally `NULL`
      char                                   *argument;                          // ->> Command-line argument representing the              command-line option; Set    through command-line `parse()`
      char                                   *value;                             // ->> Command-line argument representing the value of the command-line option; Set    through command-line `parse()`
      union {                                                                    //
        unsigned char metadata[sizeof(void*)];                                   // ->> Arbitrarily-sized
        void   *const _;                                                         // ->> Alignment
      }

      /* ... ->> Default `::validate` predicates */
      static bool UNVALUED(struct parsecmd const* option) { return NULL == option -> value; }
      static bool VALUED  (struct parsecmd const* option) { return NULL != option -> value; }
    };

    /* ... */
    static void error(int const signal) /* [[noreturn]] extern "C" */ {
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

    static int exit(int const code) /* [[noreturn]] */ {
      if (NULL != catalog) {
        if (catalog -> clockPathAllocated)      ::delete[]  catalog -> clockPath;
        if (NULL != catalog -> clockFileStream) std::fclose(catalog -> clockFileStream);

        catalog -> applicationExitCode = code;
        catalog -> clockFileStream     = NULL;
      }

      catalog = NULL;
      std::exit(code);

      return code;
    }

    static bool format(std::FILE* const stream, enum formatstyle const style, union formatinfo* const information = NULL) {
      std::size_t const informationMetadataSize = sizeof information -> metadata / sizeof(unsigned char);
      bool              styleSupported          = false;
      #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
        int const streamDescriptor = ::fileno(stream);

        // ...
        styleSupported = streamDescriptor != -1 and ::isatty(streamDescriptor) == 1;
      #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
        BOOL   WINAPI      (*const GetConsoleMode)            (HANDLE, LPDWORD)                     = NULL == libraries[kernel32].moduleHandle ? reinterpret_cast<BOOL   WINAPI (*)(HANDLE, LPDWORD)>                    (::GetProcAddress(libraryModuleHandle, "GetConsoleMode"));             // --> <windows.h>
        BOOL   WINAPI      (*const GetConsoleScreenBufferInfo)(HANDLE, PCONSOLE_SCREEN_BUFFER_INFO) = NULL == libraries[kernel32].moduleHandle ? reinterpret_cast<BOOL   WINAPI (*)(HANDLE, PCONSOLE_SCREEN_BUFFER_INFO)>(::GetProcAddress(libraryModuleHandle, "GetConsoleScreenBufferInfo")); // --> <windows.h>
        HANDLE WINAPI      (*const GetStdHandle)              (DWORD)                               = NULL == libraries[kernel32].moduleHandle ? reinterpret_cast<HANDLE WINAPI (*)(DWORD)>                              (::GetProcAddress(libraryModuleHandle, "GetStdHandle"));               // --> <windows.h>
        BOOL   WINAPI      (*const SetConsoleMode)            (HANDLE, DWORD)                       = NULL == libraries[kernel32].moduleHandle ? reinterpret_cast<BOOL   WINAPI (*)(HANDLE, DWORD)>                      (::GetProcAddress(libraryModuleHandle, "SetConsoleMode"));             // --> <windows.h>
        BOOL   WINAPI      (*const SetConsoleTextAttribute)   (HANDLE, WORD)                        = NULL == libraries[kernel32].moduleHandle ? reinterpret_cast<BOOL   WINAPI (*)(HANDLE, WORD)>                       (::GetProcAddress(libraryModuleHandle, "SetConsoleTextAttribute"));    // --> <windows.h>
        HMODULE                    libraryModuleHandle                                              = NULL;
        DWORD                      streamConsoleMode                                                = 0x00u;
        CONSOLE_SCREEN_BUFFER_INFO streamConsoleScreenBufferInformation                             = {};
        HANDLE                     streamStandardDeviceHandle                                       = NULL;

        // ...
        streamStandardDeviceHandle = NULL != GetStdHandle ? GetStdHandle(STD_ERROR_HANDLE) : NULL;
        styleSupported             = INVALID_HANDLE_VALUE != streamStandardDeviceHandle and NULL != streamStandardDeviceHandle;
      #endif

      // ...
      (void) informationMetadataSize;
      (void) stream;

      if (styleSupported)
      switch (style) {
        case FORMAT_ERROR:
        case FORMAT_WARN : {
          #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
            switch (style) {
              case FORMAT_ERROR: return std::fwrite("\x1B" "[31m", sizeof(char), 5u, stream) == 5u;
              case FORMAT_WARN : return std::fwrite("\x1B" "[33m", sizeof(char), 5u, stream) == 5u;
            }
          #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
            if (NULL != information and NULL != GetConsoleMode and NULL != SetConsoleMode) {
              if (FALSE != GetConsoleMode(streamStandardDeviceHandle, &streamConsoleMode))
              if (FALSE != SetConsoleMode(streamStandardDeviceHandle, streamConsoleMode | /* --> ENABLE_VIRTUAL_TERMINAL_PROCESSING */ 0x0004u)) {
                information -> metadata[0] = true;

                switch (style) {
                  /* Don’t repeat yourself… */
                  case FORMAT_ERROR: return std::fwrite("\x1B" "[31m", sizeof(char), 5u, stream) == 5u;
                  case FORMAT_WARN : return std::fwrite("\x1B" "[33m", sizeof(char), 5u, stream) == 5u;
                  default:           return true;
                }
              }
            }

            if (NULL != information and NULL != GetConsoleScreenBufferInfo and NULL != SetConsoleTextAttribute)
            if (FALSE != GetConsoleScreenBufferInfo(streamStandardDeviceHandle, &streamConsoleScreenBufferInformation)) {
              information -> metadata[0] = false;

              if (informationMetadataSize >= sizeof streamConsoleScreenBufferInformation.wAttributes) {
                for (std::size_t index = 0u; index != sizeof streamConsoleScreenBufferInformation.wAttributes; streamConsoleScreenBufferInformation.wAttributes >>= CHAR_BIT)
                information -> metadata[++index] = static_cast<unsigned char>(streamConsoleScreenBufferInformation.wAttributes & UCHAR_MAX);
              }

              switch (style) {
                case FORMAT_ERROR: return FALSE != SetConsoleTextAttribute(streamStandardDeviceHandle, FOREGROUND_RED);
                case FORMAT_WARN : return FALSE != SetConsoleTextAttribute(streamStandardDeviceHandle, FOREGROUND_GREEN | FOREGROUND_RED);
                default:           return true;
              }
            }
          #endif
        } break;

        case FORMAT_INITIAL: {
          #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
            return std::fwrite("\x1B" "[00m", sizeof(char), 5u, stream) == 5u;
          #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
            /* Don’t repeat yourself… */
            if (NULL != information and information -> metadata[0] == static_cast<unsigned char>(true))
            return std::fwrite("\x1B" "[00m", sizeof(char), 5u, stream) == 5u;

            if (NULL != information and information -> metadata[0] == static_cast<unsigned char>(false) and NULL != SetConsoleTextAttribute) {
              if (informationMetadataSize >= sizeof streamConsoleScreenBufferInformation.wAttributes) {
                for (std::size_t index = sizeof streamConsoleScreenBufferInformation.wAttributes; index; --index)
                streamConsoleScreenBufferInformation.wAttributes = information -> metadata[index] | (streamConsoleScreenBufferInformation.wAttributes << CHAR_BIT);
              }

              return FALSE != SetConsoleTextAttribute(streamStandardDeviceHandle, streamConsoleScreenBufferInformation.wAttributes);
            }
          #endif
        } break;
      }

      return false;
    }

    static bool message(void const* const message, std::FILE* const stream, std::size_t const stride) {
      typedef union {
        static void spanof(unsigned char const character[], std::size_t const stride, std::size_t* const begin, std::size_t* const end) {
          // ... ->> Ignores `character` endianness, leading bytes, and trailing bytes (assumes it is a distinct set of `stride` code units)
          for (; *begin != stride; ++*begin) {
            if (0x00u != character[*begin])
            break;
          }

          for (std::size_t index = *begin, redundant = false; ; ++index) {
            *end = index;

            if (index == stride or redundant)
            break;

            for (++*end, redundant = true; *end != stride; ++*end)
            if (0x00u != character[*end]) {
              redundant = false;
              break;
            }
          }
        }
      } character;

      std::size_t       messageBegin              = 0u;                                           //
      std::size_t       messageEnd                = 0u;                                           //
      std::size_t       messageLength             = 0u;                                           //
      std::size_t       messageOutputLength       = 0u;                                           //
      bool              messageOutputted          = false;                                        //
      char const        messageOverflow[]         = "…" "\r\n";                                   // ->> Source literal encoding to multi-byte NUL-terminated string
      bool              messageOverflowed         = false;                                        //
      std::size_t const messageOverflowLength     = (sizeof messageOverflow / sizeof(char)) - 1u; //
      std::size_t       messagePrefixLength       = 0u;                                           //
      std::size_t       messageSuffixLength       = 0u;                                           //
      bool              messageSuffixSignificance = true;                                         // ->> `message` ends with `::messageSuffix` followed by whitespace
      char              messageOutput[MESSAGE_MAXIMUM_LENGTH + messageOverflowLength + /* ->> NUL terminator */ 1u];

      // ...
      if (NULL == message or NULL == stream) return true;
      if (MESSAGE_MAXIMUM_LENGTH < stride)   return false;

      // ... --> messageLength = …;
      for (std::size_t index = 0u; ; index += stride) {
        unsigned char const *character      = static_cast<unsigned char const*>(message) + index;
        bool                 characterIsNUL = true;

        // ... ->> Assumes `character` NUL is a complete set of zeroed code units
        for (std::size_t subindex = 0u; stride != subindex; ++subindex)
        if (0x00u != character[subindex]) {
          characterIsNUL = false;
          break;
        }

        if (characterIsNUL or MESSAGE_MAXIMUM_LENGTH + 1u == index) {
          messageLength = index;
          break;
        }
      }

      messageBegin = 0u;
      messageEnd   = messageLength;

      // ... ->> Truncate (non-whitespace leading) `::messagePrefix` repeats
      if (NULL != catalog -> messagePrefix) {
        // ... --> messagePrefixLength = …;
        while (MESSAGE_MAXIMUM_LENGTH + 1u != messagePrefixLength and '\0' != catalog -> messagePrefix[messagePrefixLength])
        ++messagePrefixLength;

        // ...
        for (std::size_t messageIndex = 0u, messagePrefixed = true, messagePrefixIndex = 0u; messageIndex != messageLength and messagePrefixed; messageIndex += stride) {
          unsigned char const *const character      = static_cast<unsigned char const*>(message) + messageIndex;
          std::size_t                characterBegin = 0u;
          std::size_t                characterEnd   = stride;

          // ... --> messageBegin = …;
          //     ->> Assume first occurrence of `::messagePrefix` begins the `message`
          character::spanof(character, stride, &characterBegin, &characterEnd);

          for (std::size_t subindex = characterBegin; characterEnd != subindex; ) {
            // ... ->> Follow iteratively next character/ code unit for `::messagePrefix`
            if (catalog -> messagePrefix[messagePrefixIndex++] != character[subindex++]) {
              messagePrefixed = false;
              break;
            }

            // ... ->> Found `::messagePrefix`
            if (messagePrefixIndex == messagePrefixLength) {
              // ... ->> Truncate `message` by this (repeat) instance of `::messagePrefix`
              messageBegin       = messageIndex + subindex;
              messagePrefixIndex = 0u;
            }
          }
        }
      }

      // ... ->> Truncate (whitespace trailing) `::messageSuffix` repeats
      if (NULL != catalog -> messageSuffix) {
        // ... --> messageSuffixLength = …;
        while (MESSAGE_MAXIMUM_LENGTH + 1u != messageSuffixLength and '\0' != catalog -> messageSuffix[messageSuffixLength])
        ++messageSuffixLength;

        // ...
        for (std::size_t messageIndex = messageLength, messageSuffixed = false, messageSuffixIndex = messageSuffixLength, messageTrimIndex = messageIndex, messageTrimSubindex = stride; messageIndex and messageSuffixSignificance; messageIndex -= stride) {
          unsigned char const *const character      = static_cast<unsigned char const*>(message) + (messageIndex - stride);
          std::size_t                characterBegin = 0u;
          std::size_t                characterEnd   = stride;

          // ... --> messageEnd = …;
          //     ->> Search last occurrence of `::messageSuffix`
          character::spanof(character, stride, &characterBegin, &characterEnd);

          for (std::size_t subindex = characterEnd; characterBegin != subindex; ) {
            // ... ->> Search iteratively next character/ code unit for `::messageSuffix`
            if (messageSuffixIndex == messageSuffixLength) {
              messageTrimIndex    = messageIndex - stride;
              messageTrimSubindex = subindex     - 1u;
            }

            if (catalog -> messageSuffix[--messageSuffixIndex] != character[--subindex]) {
              messageSuffixIndex = messageSuffixLength;
              continue;
            }

            // ... ->> Found `::messageSuffix`
            if (0u == messageSuffixIndex) {
              // ... ->> Determine `::messageSuffix` significance i.e.: trailed by whitespace
              if (not messageSuffixed)
              for (bool suffixed = true; messageEnd != messageTrimIndex and messageSuffixSignificance; messageTrimIndex += stride) {
                unsigned char const *const character      = static_cast<unsigned char const*>(message) + messageTrimIndex;
                std::size_t                characterBegin = 0u;
                std::size_t                characterEnd   = stride;

                // ... --> messageSuffixSignificance = …;
                character::spanof(character, stride, &characterBegin, &characterEnd);

                characterBegin      = 0u == messageTrimSubindex ? characterBegin : messageTrimSubindex;
                messageTrimSubindex = 0u;

                for (std::size_t subindex = characterBegin; characterEnd != subindex and messageSuffixSignificance; ++subindex, suffixed = false)
                if (not suffixed) { // ->> First code unit is the end of `::messageSuffix`, so it is ignored
                  switch (static_cast<char>(character[subindex])) {
                    case '\f': case '\n': case '\r': case '\t': case '\v': case ' ':
                    continue;
                  }

                  messageSuffixSignificance = false;
                }
              }

              // ... ->> `::messageSuffix` must be significant to be truncated off `message`
              if (not messageSuffixSignificance)
              break;

              // ... ->> Truncate `message` by tracking the first instance in the last set of contiguous `::messageSuffix` repeats
              messageEnd         = subindex + (messageIndex - stride);
              messageSuffixed    = true; // ->> For symmetry with `messagePrefixed` only
              messageSuffixIndex = messageSuffixLength;
            }
          }
        }
      }

      // ... --> messageOutput[messageOutputLength++…] = …;
      for (std::size_t index = 0u; index != messagePrefixLength and not messageOverflowed; ++index) {
        messageOutput[messageOutputLength++] = catalog -> messagePrefix[index];

        if (MESSAGE_MAXIMUM_LENGTH == messageOutputLength)
        messageOverflowed = true;
      }

      for (std::size_t index = 0u; index != messageLength and not messageOverflowed; index += stride) {
        unsigned char const *const character      = static_cast<unsigned char const*>(message) + index;
        std::size_t                characterBegin = 0u;
        std::size_t                characterEnd   = stride;

        // ...
        character::spanof(character, stride, &characterBegin, &characterEnd);

        for (std::size_t subindex = 0u; characterEnd != subindex; ++subindex)
        if (messageBegin <= index + subindex and messageEnd > index + subindex) {
          messageOutput[messageOutputLength++] = static_cast<char>(character[subindex]);

          if (MESSAGE_MAXIMUM_LENGTH == messageOutputLength) {
            messageOverflowed = true;
            break;
          }
        }
      }

      for (std::size_t index = 0u; index != messageSuffixLength and not messageOverflowed; ++index) {
        messageOutput[messageOutputLength++] = catalog -> messageSuffix[index];

        if (MESSAGE_MAXIMUM_LENGTH == messageOutputLength) {
          messageOutputLength -= index + 1u;
          messageOverflowed    = true;
        }
      }

      if (messageOverflowed) {
        for (std::size_t index = 0u; index != messageOverflowLength; ++index)
        messageOutput[messageOutputLength++] = messageOverflow[index];
      }

      messageOutput[messageOutputLength] = '\0';

      // ...
      (void) std::fflush (stream); // ->> Ensure the `stream` delivers the `messageOutput` immediately
      (void) std::setvbuf(stream, static_cast<char*>(NULL), _IONBF, 0u);

      messageOutputted = EOF != std::fputs (messageOutput, stream);
      messageOutputted ? (void) std::fflush(stream) : std::clearerr(stream);

      // ...
      return messageOutputted;
    }
      static bool message(char    const message[], std::FILE* const stream = stdout) { return catalog -> message(message, stream, sizeof(char)); }
      static bool message(wchar_t const message[], std::FILE* const stream = stdout) { return catalog -> message(message, stream, sizeof(wchar_t)); }

    static void parse(char* arguments[], std::size_t const argumentsLength, struct parsecmd options[], std::size_t optionsLength) {
      typedef union {
        static char* nextchar(char* argument) {
          while ('\0' != *argument)
          switch (*argument) {
            case '\f': case '\n': case '\r': case '\t': case '\v': case ' ': continue;
            default: return argument;
          }

          return argument;
        }
      } argument;

      // ...
      for (std::size_t argumentIndex = 0u; argumentIndex != argumentsLength; ++argumentIndex) {
        struct parsecmd *argumentOption = NULL;

        // ... TODO
        for (struct parsecmd *option = options; NULL == argumentOption and option != options + optionsLength; ++option) {
          typedef struct parsecmd parsecmd;
          char const     *const argument       = arguments[argumentIndex];
          struct parsecmd const fallbackOption = *option;

          // ... ->> Match based on the `option` name
          for (char const *parsecmd:: *const names[] = {&parsecmd::name, &parsecmd::longName, &parsecmd::shortName}, *parsecmd:: *const *name = names; NULL == argumentOption and name != names + (sizeof names / sizeof(char const* parsecmd::*)); ++name)
          if (NULL != catalog ->* *name) {
            std::size_t        index      = 0u;
            bool               tagged     = true;
            std::size_t        tagOffset  = 0u;
            char const *const *tags       = NULL;
            std::size_t        tagsLength = 0u;

            // ... --> tags… = …; tagOffset = …;
            if (&parsecmd::longName  == *name) { tags = catalog -> commandLineOptionLongTags;  tagsLength = catalog -> commandLineOptionLongTagsLength;  }
            if (&parsecmd::shortName == *name) { tags = catalog -> commandLineOptionShortTags; tagsLength = catalog -> commandLineOptionShortTagsLength; }

            if (NULL == tags or 0u == tagsLength) {
              tagged     = false;
              tags       = &"";
              tagsLength = 1u;
            }

            tagOffset = tagged ? argument::nextchar(argument) - argument : tagOffset;

            // ... ->> Validate based on the `tag`
            for (std::size_t tagIndex = 0u; tagIndex != tagsLength; ++tagIndex) {
              char const *tag = tags[tagIndex];

              // ...
              for (std::size_t subindex = 0u; ; ++subindex) {
                if ('\0' == tag[subindex]) {
                  index = subindex + tagOffset;
                  break;
                }

                if ('\0' == argument[subindex + tagOffset] or argument[subindex + tagOffset] != tag[subindex]) {
                  tag = NULL;
                  break;
                }
              }

              if (NULL == tag)
              continue;

              // ...
              index = tagged ? argument::nextchar(argument + index) - argument : index;

              // CHECK THE NAME
              // CHECK FOR TRIM BEFORE END/ VALUE TAG

              argumentOption = ...; // IT'S COOL
            }
          }

          for (..) {
            // option -> argument
            //   option -> name
            //   catalog -> commandLineOptionShortTags option -> shortName
            //   catalog -> commandLineOptionLongTags  option -> longName

            // ... ->> Ensure the name constitutes the entire `argument` or precedes its value
            if (NULL != argumentOption)
            for (bool valued = false; '\0' != argument[index]; ++index) {
              switch (argument[index]) {
                case '\f': case '\n': case '\r': case '\t': case '\v': case ' ':
                continue;
              }

              for (char const *const *commandLineOptionValueTag = catalog -> commandLineOptionValueTags; commandLineOptionValueTag != catalog -> commandLineOptionValueTags + catalog -> commandLineOptionValueTagsLength; ++commandLineOptionValueTag)
              for (std::size_t subindex = 0u; ; ++subindex) {
                if (argument[index + subindex] != (*commandLineOptionValueTag)[subindex])
                break;

                if ('\0' == (*commandLineOptionValueTag)[subindex]) {
                  valued = true;
                  break;
                }
              }

              if (valued)
              break;

              argumentOption = NULL;
            }

            if (NULL != argumentOption)
            break;
          }

          // ... ->> Match based on the value
          if (NULL != catalog -> commandLineOptionValueTags and catalog -> commandLineOptionValueTagsLength)
          // for (index = 0u; index != catalog -> commandLineOptionValueTagsLength; ++index) {
          //   char const *const commandLineOptionValueTag = catalog -> commandLineOptionValueTags[index];
          // }
          // option -> value
          //   catalog -> commandLineOptionValueTags option -> valueCount

          // option -> validate
          //   *option = fallbackOption
        }

        for (struct parsecmd *option = options; NULL == argumentOption and option != options + optionsLength; ++option) {
          if (NULL == option -> longName and NULL == option -> name and NULL == option -> shortName) {
            // option -> validate();
            //   *option = fallbackOption
          }
        }

        // ...
        if (NULL != argumentOption) {
          // argumentOption -> argument = argument;
          // argumentOption -> value    = ???;
        }
      }
    }

    static void quick_exit() /* [[noreturn]] extern "C" */ {
      if (NULL != catalog)
        (void) catalog -> exit(catalog -> applicationExitCode);

      // ... ->> Cleanup regardless
      std::exit(EXIT_SUCCESS);
    }

    static void start(char* arguments[], std::size_t const length) {
      union parse {
        static bool sequenced(struct parsecmd const* option) {
          struct parsecmd const *const sequenced = static_cast<struct parsecmd const*>(reinterpret_cast<void*>(option -> metadata));
          return NULL != sequenced -> argument; // ->> Waits for its `sequenced` command-line option before a successful `parse()`
        }
      };

      char const *const commandLineOptionLongTags [] = {"--"};
      char const *const commandLineOptionShortTags[] = {"-", "/"};
      char const *const commandLineOptionValueTags[] = {"=", ":"};
      struct parsecmd   commandLineOptions        [] = {
        {parsecmd::ABOUT, "?",  "about", NULL, 0u, &parsecmd::UNVALUED,  NULL, NULL, {}},
        {parsecmd::CLOCK, NULL, NULL,    NULL, 0u, &parse   ::sequenced, NULL, NULL, {}}, // --> 1
        {parsecmd::CLOCK, NULL, "clock", "c",  0u, &parsecmd::VALUED,    NULL, NULL, {}},
        {parsecmd::CLOCK, NULL, "clock", "c",  1u, &parsecmd::VALUED,    NULL, NULL, {}},
        {parsecmd::CLOCK, NULL, NULL,    "t",  0u, &parsecmd::VALUED,    NULL, NULL, {}},
        {parsecmd::CLOCK, NULL, NULL,    "t",  1u, &parsecmd::VALUED,    NULL, NULL, {}},
        {parsecmd::HELP,  NULL, "help",  "h",  0u, &parsecmd::UNVALUED,  NULL, NULL, {}},
        {parsecmd::LOG,   NULL, NULL,    NULL, 0u, NULL,                 NULL, NULL, {}}, // --> 7
        {parsecmd::RERUN, NULL, "rerun", "r",  0u, &parsecmd::UNVALUED,  NULL, NULL, {}}
      };

      // ...
      (void) ::new (commandLineOptions[1].metadata) void*(commandLineOptions + 7); // ->> `parse::sequenced(…)` after `commandLineOptions[7]`

      catalog -> applicationExitCode              = EXIT_SUCCESS;                                            // ->> Used by `::quick_exit(…)` primarily
      catalog -> applicationName                  = "Cataloger";                                             //
      catalog -> clocked                          = false;                                                   // ->> Catalog's internal clock is active
      catalog -> clockFileStream                  = NULL;                                                    // ->> File stream representing the Catalog's internal clock
      catalog -> clockInterval                    = 86400000u;                                               // ->> Milliseconds
      catalog -> clockPathAllocated               = false;                                                   //
      catalog -> commandLineArguments             = arguments;                                               // ->> Useful for determining how the standard C/ C++ command-line `arguments` were evaluated; Optionally `NULL`-terminated
      catalog -> commandLineArgumentsLength       = length;                                                  //
      catalog -> commandLineOptionLongTags        = commandLineOptionLongTags;                               // ->> Prefix that denotes long command-line options interchangeably; Optionally `NULL`
      catalog -> commandLineOptionLongTagsLength  = sizeof commandLineOptionLongTags / sizeof(char const*);  //
      catalog -> commandLineOptionShortTags       = commandLineOptionShortTags;                              // ->> Prefix that denotes short command-line options interchangeably; Optionally `NULL`
      catalog -> commandLineOptionShortTagsLength = sizeof commandLineOptionShortTags / sizeof(char const*); //
      catalog -> commandLineOptionValueTags       = commandLineOptionValueTags;                              // ->> Affix that denotes valued command-line options interchangeably; Optionally `NULL`
      catalog -> commandLineOptionValueTagsLength = sizeof commandLineOptionValueTags / sizeof(char const*); //
      catalog -> messagePrefix                    = "cataloger" ": ";                                        // ->> Used by `::message(…)` primarily; Optionally `NULL`
      catalog -> messageSuffix                    = "\r\n";                                                  // ->> Used by `::message(…)` primarily; Optionally `NULL`

      #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
        LPWSTR* (*const CommandLineToArgvW) (LPCWSTR, int*)                                       = NULL == libraries[shell32] .moduleHandle ? NULL : reinterpret_cast<LPWSTR* (*)(LPCWSTR, int*)>                                      (::GetProcAddress(libraries[shell32] .moduleHandle, "CommandLineToArgvW"));  // --> <shellapi.h>
        LPWSTR  (*const GetCommandLineW)    ()                                                    = NULL == libraries[kernel32].moduleHandle ? NULL : reinterpret_cast<LPWSTR  (*)()>                                                   (::GetProcAddress(libraries[kernel32].moduleHandle, "GetCommandLineW"));     // --> <windows.h> → <processenv.h>
        BOOL    (*const GetModuleHandleExA) (DWORD, LPCSTR, HMODULE*)                             = NULL == libraries[kernel32].moduleHandle ? NULL : reinterpret_cast<BOOL    (*)(DWORD, LPCSTR, HMODULE*)>                            (::GetProcAddress(libraries[kernel32].moduleHandle, "GetModuleHandleExA"));  // --> <windows.h>
        HLOCAL  (*const LocalFree)          (HLOCAL)                                              = NULL == libraries[kernel32].moduleHandle ? NULL : reinterpret_cast<HLOCAL  (*)(HLOCAL)>                                             (::GetProcAddress(libraries[kernel32].moduleHandle, "LocalFree"));           // --> <windows.h>
        int     (*const WideCharToMultiByte)(UINT, DWORD, LPCWCH, int, LPSTR, int, LPCCH, LPBOOL) = NULL == libraries[kernel32].moduleHandle ? NULL : reinterpret_cast<int     (*)(UINT, DWORD, LPCWCH, int, LPSTR, int, LPCCH, LPBOOL)>(::GetProcAddress(libraries[kernel32].moduleHandle, "WideCharToMultiByte")); // --> <windows.h>
        HMODULE         applicationModuleHandle                                                   = NULL;
        HMODULE         argumentModuleHandle                                                      = NULL;

        // ... ->> Normalize standard C/ C++ command-line `arguments` to vendor-specific Windows `commandLineArguments`
        if (NULL != CommandLineToArgvW and NULL != GetCommandLineW) {
          int           commandLineArgumentsLength = 0;
          LPWSTR *const commandLineArguments       = CommandLineToArgvW(GetCommandLineW(), &commandLineArgumentsLength);

          // ...
          if (NULL != WideCharToMultiByte)
          if (NULL != commandLineArguments and static_cast<unsigned>(commandLineArgumentsLength) <= length) {
            char       *allocation = NULL, *iterator = NULL;
            bool        normalized = false;
            std::size_t size       = 0u;

            // ...
            for (int index = 0; commandLineArgumentsLength != index; ++index) {
              int const commandLineArgumentSize = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, commandLineArguments[index], -1, static_cast<LPSTR>(NULL), 0u, static_cast<LPCCH>(NULL), static_cast<LPBOOL>(NULL));

              // ...
              if (0 == commandLineArgumentSize) { size = 0u; break; }
              size += commandLineArgumentSize;
            }

            allocation = size ? /* ->> Likely memory leak */ ::new (std::nothrow) char[size = /* ->> Non-NUL characters */ (size / sizeof(char)) + /* ->> NUL terminators */ (commandLineArgumentsLength * sizeof(char))] : NULL;
            iterator   = allocation;

            // ... --> catalog -> commandLineArguments[…] = …;
            if (NULL != allocation)
            for (int index = 0; commandLineArgumentsLength != index; ++index) {
              int const commandLineArgumentSize = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, commandLineArguments[index], -1, iterator, size, static_cast<LPCCH>(NULL), static_cast<LPBOOL>(NULL));

              if (0 != commandLineArgumentSize) {
                catalog -> commandLineArguments[index] = iterator; // ->> Normalize standard C/ C++ command-line argument
                iterator                              += commandLineArgumentSize;
                normalized                             = true;
              }
            }

            if (not normalized)
            ::delete[] allocation;
          }

          if (NULL != LocalFree)
          (void) LocalFree(commandLineArguments);
        }

        // ... ->> Ignore the standard C/ C++ command-line string used to execute this application
        if (NULL != GetModuleHandleExA) {
          if (
            FALSE !=   GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, catalog -> commandLineArguments[0], &argumentModuleHandle) and
            FALSE != ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, static_cast<LPWSTR>(NULL),          &applicationModuleHandle)
          ) {
            catalog -> commandLineArguments       += applicationModuleHandle == argumentModuleHandle;
            catalog -> commandLineArgumentsLength -= applicationModuleHandle == argumentModuleHandle;
          }
        }
      #endif

      // ... TODO -> Handle parse properly
      catalog -> parse(catalog -> commandLineArguments, catalog -> commandLineArgumentsLength, commandLineOptions, sizeof commandLineOptions / sizeof *commandLineOptions);
      catalog -> clockPath                        = length > 2u ? arguments[2] : NULL;    // ->> Filesystem location for serializing Catalog clock; Assume NUL-terminated
      catalog -> commandLineOptionLongTags        = &"--";                                //
      catalog -> commandLineOptionLongTagsLength  = 0u;                                   //
      catalog -> commandLineOptionShortTags       = &"-";                                 //
      catalog -> commandLineOptionShortTagsLength = 0u;                                   //
      catalog -> commandLineOptionValueTags       = &"=";                                 //
      catalog -> commandLineOptionValueTagsLength = 0u;                                   //
      catalog -> logDirectoryPath                 = length > 1u ? arguments[1] : NULL;    // ->> Filesystem location for storing catalogs; Assume NUL-terminated
      catalog -> rerun                            = length > 3u and NULL != arguments[3]; // ->> Catalog is re-executed

      // ... ->> Handle unexpected application `error()`
      (void) std::signal   (SIGTERM, &catalog -> error); //
      (void) std::signal   (SIGSEGV, &catalog -> error); // ->> ¯\_(ツ)_/¯
      (void) std::signal   (SIGINT,  &catalog -> error); // ->> Handle possible user interrupts
      (void) std::signal   (SIGABRT, &catalog -> error); // ->> Handle `std::abort(…)` and `std::terminate(…)` (and `throw` expression) invocations
      (void) std::setlocale(LC_ALL,  "C.UTF-8");         //
      #if __cplusplus >= 201103L                         //
        (void) std::at_quick_exit(&catalog -> quick_exit);
      #endif
    }

    static void update() {
      // ... ->> Ideally runs every `::clockInterval` elapsed
      return;
    }

    static bool warn(void const* const message, std::FILE* const stream, std::size_t const stride) {
      union formatinfo messageFormatInformation = {};
      bool             messageFormatted         = false;
      bool             messageOutputted         = false;

      // ...
      messageFormatted = catalog -> format (stream, FORMAT_ERROR, &messageFormatInformation);
      messageOutputted = catalog -> message(message, stream, stride);

      if (messageFormatted)
      (void) catalog -> format(stream, FORMAT_INITIAL, &messageFormatInformation);

      // ...
      return messageOutputted;
    }
      static bool warn(char    const message[], std::FILE* const stream = stderr) { return catalog -> warn(message, stream, sizeof(char)); }
      static bool warn(wchar_t const message[], std::FILE* const stream = stderr) { return catalog -> warn(message, stream, sizeof(wchar_t)); }

    /* ... */
    int                applicationExitCode;
    char const        *applicationName;
    bool               clocked;
    std::FILE         *clockFileStream;
    std::size_t        clockInterval;
    char              *clockPath;
    bool               clockPathAllocated;
    char             **commandLineArguments;
    std::size_t        commandLineArgumentsLength;
    char const *const *commandLineOptionLongTags;
    std::size_t        commandLineOptionLongTagsLength;
    char const *const *commandLineOptionShortTags;
    std::size_t        commandLineOptionShortTagsLength;
    char const *const *commandLineOptionValueTags;
    std::size_t        commandLineOptionValueTagsLength;
    char const        *logDirectoryPath;
    char const        *messagePrefix;
    char const        *messageSuffix;
    bool               rerun;
  } c = {};

  catalog = &c;                       //
  catalog -> start(arguments, count); // ->> Initialization

  // ... --> catalog -> logDirectoryPath = …;
  if (NULL == catalog -> logDirectoryPath) {
    (void) catalog -> message("No directory for logs specified; defaulting to the current working directory instead");
    catalog -> logDirectoryPath = "./";
  }

  // ... --> catalog -> clockFileStream = …;
  if (NULL == catalog -> clockPath) {
    (void) catalog -> message("No directory for the catalog's internal clock specified; defaulting to fallback instead");
    catalog -> clockFileStream = std::tmpfile();
  } else catalog -> clockFileStream = std::fopen(catalog -> clockPath, "wb+");

  if (NULL == catalog -> clockFileStream and NULL != catalog -> clockPath) {
    char        catalogClockFileNameFallback[L_tmpnam + 1u] = {};    //
    std::size_t catalogClockFileNameFallbackLength          = 0u;    //
    char       *catalogClockPathBuffer                      = NULL;  // ->> Non-null when `::clockPathAllocated` and assigned to `::clockPath` afterward
    std::size_t catalogClockPathLength                      = 0u;    //
    char const *catalogClockPathPrefix                      = "";    //
    bool        catalogClockPathPrefixed                    = false; // ->> Determines `::clockPath` (significantly) begins with `catalogClockPathPrefix`
    std::size_t catalogClockPathPrefixLength                = 0u;    //
    bool        catalogClockPathSuffixed                    = false; // ->> Determines `::clockPath` (significantly) ends   with `pathDelimiters[…]`
    char const  pathDelimiters[]                            = {'/'
      #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
        , '\\'
      #endif
    };
    std::size_t const pathDelimitersLength = sizeof pathDelimiters / sizeof(char);

    // ... --> catalogClockFileNameFallback       = std::strrchr(std::tmpnam(…) ?? …, '/' | …);
    //         catalogClockFileNameFallbackLength = std::strlen (catalogClockFileNameFallback);
    if (catalogClockFileNameFallback != std::tmpnam(catalogClockFileNameFallback)) {
      char        const fallback[]     = "cataloger-clock.dat";
      std::size_t const fallbackLength = (sizeof fallback / sizeof(char)) - 1u;

      // ...
      for (std::size_t index = 0u; ; ++index) {
        catalogClockFileNameFallback[index] = fallback[index];

        if (fallbackLength == index or index == (sizeof catalogClockFileNameFallback / sizeof(char)) - 1u) {
          catalogClockFileNameFallback[index] = '\0';
          break;
        }
      }
    }

    while ('\0' != catalogClockFileNameFallback[catalogClockFileNameFallbackLength])
    ++catalogClockFileNameFallbackLength;

    for (std::size_t index = catalogClockFileNameFallbackLength; index--; ) {
      // ... ->> Unique names only, rather than unique file paths
      for (std::size_t subindex = 0u; pathDelimitersLength != subindex; ++subindex)
      if (catalogClockFileNameFallback[index] == pathDelimiters[subindex]) {
        catalogClockFileNameFallbackLength -= ++index;

        for (subindex = 0u; subindex <= catalogClockFileNameFallbackLength; ++index, ++subindex)
        catalogClockFileNameFallback[subindex] = catalogClockFileNameFallback[index];

        index = 0u;
        break;
      }
    }

    // ... --> catalogClockPathLength   = std::strlen(catalog -> clockPath | …);
    //         catalogClockPathSuffixed = …;
    for (; '\0' != catalog -> clockPath[catalogClockPathLength]; ++catalogClockPathLength) {
      for (std::size_t subindex = 0u; pathDelimitersLength != subindex; ++subindex)
      if (catalog -> clockPath[catalogClockPathLength] == pathDelimiters[subindex]) {
        for (char *iterator = catalog -> clockPath + (catalogClockPathLength + 1u); ; ++iterator) {
          switch (*iterator) {
            case '\f': case '\n': case '\r': case '\t': case '\v': case ' ':
            continue;
          }

          catalogClockPathSuffixed = '\0' == *iterator;
          break;
        }
      }

      if (catalogClockPathSuffixed)
      break;
    }

    // ... --> catalogClockPathPrefix… = …;
    #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
      catalogClockPathPrefix       = "\\\\?\\";
      catalogClockPathPrefixLength = MAX_PATH < catalogClockPathLength + /* ->> Path delimiter */ 1u + catalogClockFileNameFallbackLength + /* ->> NUL terminator */ 1u ? 3u : 0u;
    #endif

    // ... --> catalogClockPathPrefixed = …;
    for (std::size_t clockIndex = 0u, prefixIndex = 0u; ; ++clockIndex) {
      if (catalogClockPathPrefixLength == prefixIndex) {
        catalogClockPathPrefixed     = true;
        catalogClockPathPrefixLength = 0u;

        break;
      }

      switch (catalog -> clockPath[clockIndex]) {
        case '\f': case '\n': case '\r': case '\t': case '\v': case ' ':
        continue;
      }

      if (catalog -> clockPath[clockIndex] != catalogClockPathPrefix[prefixIndex++])
      break;
    }

    // ... --> catalogClockPathBuffer = …; ->> Just resizing
    catalogClockPathBuffer = ::new (std::nothrow) char[catalogClockPathPrefixLength + catalogClockPathLength + /* ->> Path delimiter */ 1u + catalogClockFileNameFallbackLength + /* ->> NUL terminator */ 1u];

    if (NULL == catalogClockPathBuffer) {
      if (not catalogClockPathPrefixed) {
        catalogClockPathBuffer             = ::new (std::nothrow) char[catalogClockPathPrefixLength + catalogClockPathLength + /* ->> NUL terminator */ 1u];
        catalogClockFileNameFallbackLength = 0u;
      }

      else if (not catalogClockPathSuffixed) {
        (void) catalog -> warn("Cataloger exited; No file for the catalog's internal clock specified");
        return catalog -> exit(EXIT_FAILURE);
      }

      else
        catalogClockPathBuffer = ::new (std::nothrow) char[catalogClockPathLength + /* ->> Path delimiter */ 1u + catalogClockFileNameFallbackLength + /* ->> NUL terminator */ 1u];
    }

    if (NULL == catalogClockPathBuffer) {
      catalogClockPathBuffer       = ::new (std::nothrow) char[catalogClockPathLength + /* ->> NUL terminator */ 1u];
      catalogClockPathPrefixLength = 0u;

      if (NULL == catalogClockPathBuffer) {
        (void) catalog -> warn("Cataloger exited; No file for the catalog's internal clock specified");
        return catalog -> exit(EXIT_FAILURE);
      }
    }

    catalogClockPathBuffer[catalogClockPathLength] = '\0';

    for (std::size_t index = 0u; index != catalogClockPathLength; ++index)
    catalogClockPathBuffer[index] = catalog -> clockPath[index] != '/' ? catalog -> clockPath[index] : '\\';

    // ... --> catalog -> clockFileStream = …;
    //         catalog -> clockPath…      = …;
    catalog -> clockPathAllocated = true;
    catalog -> clockPath          = catalogClockPathBuffer;
    catalog -> clockFileStream    = std::fopen(catalog -> clockPath, "wb+");

    if (NULL == catalog -> clockFileStream)
    if (0u != catalogClockPathPrefixLength) {
      for (std::size_t index = catalogClockPathLength; index--; )
        catalog -> clockPath[catalogClockPathPrefixLength + index] = catalog -> clockPath[index];

      for (std::size_t index = catalogClockPathPrefixLength; index--; )
        catalog -> clockPath[index] = catalogClockPathPrefix[index];

      catalogClockPathLength    += catalogClockPathPrefixLength;
      catalog -> clockFileStream = std::fopen(catalog -> clockPath, "wb+");
    }

    if (NULL == catalog -> clockFileStream)
    if (0u != catalogClockFileNameFallbackLength) {
      catalog -> clockPath[catalogClockPathLength]                                           = '\\';
      catalog -> clockPath[catalogClockPathLength + catalogClockFileNameFallbackLength + 1u] = '\0';

      for (std::size_t index = 0u; index != catalogClockFileNameFallbackLength; ++index)
        catalog -> clockPath[catalogClockPathLength + index + 1u] = catalogClockFileNameFallback[index];

      catalogClockPathLength    += catalogClockFileNameFallbackLength + 1u;
      catalog -> clockFileStream = std::fopen(catalog -> clockPath, "wb+");
    }
  }

  // ...
  if (NULL == catalog -> clockFileStream) {
    (void) catalog -> warn("Cataloger exited; No file for the catalog's internal clock specified");
    return catalog -> exit(EXIT_FAILURE);
  }

  /* ... ->> Execute internal clock */
  if (catalog -> rerun)
    catalog -> update();

  else {
  #if false // TODO (Lapys)
    #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
      // TODO (Lapys) -> Linux service → `usleep(…)` → `nanosleep(…)`
    #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
      DWORD     (*const GetModuleFileNameW) (HMODULE, LPWSTR, DWORD)               = NULL == libraries[kernel32].moduleHandle ? NULL : reinterpret_cast<DWORD (*)(HMODULE, LPWSTR, DWORD)>              (::GetProcAddress(libraries[kernel32].moduleHandle, "GetModuleFileNameW"));  // --> <windows.h>
      int       (*const MultiByteToWideChar)(UINT, DWORD, LPCCH, int, LPWSTR, int) = NULL == libraries[kernel32].moduleHandle ? NULL : reinterpret_cast<int   (*)(UINT, DWORD, LPCCH, int, LPWSTR, int)>(::GetProcAddress(libraries[kernel32].moduleHandle, "MultiByteToWideChar")); // --> <windows.h>
      WCHAR             applicationFilePath[MAX_PATH + 1u]                         = {};
      std::size_t const applicationFilePathLength                                  = sizeof applicationFilePath / sizeof(WCHAR);
      HMODULE           applicationModuleHandle                                    = NULL;
      static WCHAR      applicationName[]                                          = L"Cataloger"; // --> ::MultiByteToWideChar(…, catalog -> applicationName, …)
      HMODULE           argumentModuleHandle                                       = NULL;
      char             *programPointer                                             = NULL; // --> ::_pgmptr
      wchar_t          *programPointerW                                            = NULL; // --> ::_wpgmptr

      // ... --> programPointer… = ::_get_…pgmptr(…);
      programPointer  = 0 != ::_get_pgmptr (&programPointer)  ? arguments + 1 == catalog -> commandLineArguments ? arguments[0] : NULL : programPointer;
      programPointerW = 0 != ::_get_wpgmptr(&programPointerW) ?                                                                   NULL : programPointerW;

      // ... --> applicationFilePath = …;
      if (NULL == GetModuleFileNameW or FALSE == GetModuleFileNameW(static_cast<HMODULE>(NULL), applicationFilePath, applicationFilePathLength)) {
        applicationFilePath[0] = L'\0';

        // ...
        if (NULL != programPointerW)
        for (std::size_t index = 0u; ; ++index) {
          applicationFilePath[index] = programPointerW[index];
          if (L'\0' == programPointerW[index]) break;
        }

        else if (NULL != programPointer) {
          if (NULL != MultiByteToWideChar and applicationFilePathLength >= static_cast<unsigned>(MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, programPointer, -1, static_cast<LPWSTR>(NULL), 0))) {
            if (0 == MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, programPointer, -1, applicationFilePath, applicationFilePathLength))
            applicationFilePath[0] = L'\0';
          }
        }
      }

      applicationFilePath[MAX_PATH] = L'\0';

      /* ... ->> Windows Task Scheduler --- TODO (Lapys) -> Remove `false` condition */
      if _WIN32_WINNT >= 0x0600
        if (false and not catalog -> clocked)
        if (NULL != libraries[credui].moduleHandle and NULL != libraries[kernel32].moduleHandle and NULL != libraries[ole32].moduleHandle and NULL != libraries[oleaut32].moduleHandle and NULL != libraries[taskschd].moduleHandle) {
          HRESULT (*const CoCreateInstance)                  (REFCLSID, LPUNKNOWN, DWORD, REFIID, LPVOID)                                                         = reinterpret_cast<HRESULT         (*)(REFCLSID, LPUNKNOWN, DWORD, REFIID, LPVOID)>                                                        (::GetProcAddress(libraries[ole32]   .moduleHandle, "CoCreateInstance"));                   // --> <objbase.h>
          HRESULT (*const CoInitializeEx)                    (LPVOID, DWORD)                                                                                      = reinterpret_cast<HRESULT         (*)(LPVOID, DWORD)>                                                                                     (::GetProcAddress(libraries[ole32]   .moduleHandle, "CoInitializeEx"));                     // --> <objbase.h>
          HRESULT (*const CoInitializeSecurity)              (PSECURITY_DESCRIPTOR, LONG, SOLE_AUTHENTICATION_SERVICE*, void*, DWORD, DWORD, void*, DWORD, void*) = reinterpret_cast<HRESULT         (*)(PSECURITY_DESCRIPTOR, LONG, SOLE_AUTHENTICATION_SERVICE*, void*, DWORD, DWORD, void*, DWORD, void*)>(::GetProcAddress(libraries[ole32]   .moduleHandle, "CoInitializeSecurity"));               // --> <objbase.h>
          void    (*const CoUninitialize)                    ()                                                                                                   = reinterpret_cast<void            (*)()>                                                                                                  (::GetProcAddress(libraries[ole32]   .moduleHandle, "CoUninitialize"));                     // --> <objbase.h>
          DWORD   (*const CredUIPromptForCredentialsW)       (PCREDUI_INFOW, PCWSTR, PCtxtHandle, DWORD, PWSTR, ULONG, PWSTR, ULONG, BOOL*, DWORD)                = reinterpret_cast<CREDUIAPI DWORD (*)(PCREDUI_INFOW, PCWSTR, PCtxtHandle, DWORD, PWSTR, ULONG, PWSTR, ULONG, BOOL*, DWORD)>               (::GetProcAddress(libraries[credui]  .moduleHandle, "CredUIPromptForCredentialsW"));        // --> <wincred.h>
          DWORD   (*const CredUIPromptForWindowsCredentialsW)(PCREDUI_INFOW, DWORD, ULONG*, LPCVOID, ULONG, LPVOID*, ULONG*, BOOL*, DWORD)                        = reinterpret_cast<CREDUIAPI DWORD (*)(PCREDUI_INFOW, DWORD, ULONG*, LPCVOID, ULONG, LPVOID*, ULONG*, BOOL*, DWORD)>                       (::GetProcAddress(libraries[credui]  .moduleHandle, "CredUIPromptForWindowsCredentialsW")); // --> <wincred.h>
          BOOL    (*const CredUnPackAuthenticationBufferW)   (DWORD, PVOID, DWORD, LPWSTR, DWORD*, LPWSTR, DWORD*, LPWSTR, DWORD*)                                = reinterpret_cast<CREDUIAPI BOOL  (*)(DWORD, PVOID, DWORD, LPWSTR, DWORD*, LPWSTR, DWORD*, LPWSTR, DWORD*)>                               (::GetProcAddress(libraries[credui]  .moduleHandle, "CredUnPackAuthenticationBufferW"));    // --> <wincred.h>
          LPWSTR  (*const GetCommandLineW)                   ()                                                                                                   = reinterpret_cast<LPWSTR          (*)()>                                                                                                  (::GetProcAddress(libraries[kernel32].moduleHandle, "GetCommandLineW"));                    // --> <windows.h> → <processenv.h>
          BSTR    (*const SysAllocString)                    (OLECHAR const*)                                                                                     = reinterpret_cast<BSTR            (*)(OLECHAR const*)>                                                                                    (::GetProcAddress(libraries[oleaut32].moduleHandle, "SysAllocString"));                     // --> <oleauto.h>
          void    (*const SysFreeString)                     (BSTR)                                                                                               = reinterpret_cast<void            (*)(BSTR)>                                                                                              (::GetProcAddress(libraries[oleaut32].moduleHandle, "SysFreeString"));                      // --> <oleauto.h>
          HRESULT (*const VariantClear)                      (VARIANTARG*)                                                                                        = reinterpret_cast<HRESULT         (*)(VARIANTARG*)>                                                                                       (::GetProcAddress(libraries[oleaut32].moduleHandle, "VariantClear"));                       // --> <oleauto.h>
          void    (*const VariantInit)                       (VARIANTARG*)                                                                                        = reinterpret_cast<void            (*)(VARIANTARG*)>                                                                                       (::GetProcAddress(libraries[oleaut32].moduleHandle, "VariantInit"));                        // --> <oleauto.h>

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
            WCHAR const *const  credentialsPromptCaption                                    = applicationName;                                        // --> WCHAR[CREDUI_MAX_CAPTION_LENGTH]
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
            ITaskFolder        *taskFolder                                                  = NULL;                                                   //
            VARIANT             taskFolderPassword                                          = {};                                                     //
            BSTR const          taskFolderPath                                              = SysAllocString(L"\\");                                  // ->> Root folder
            VARIANT             taskFolderSecurityDescriptor                                = {};                                                     //
            VARIANT             taskFolderUsername                                          = {};                                                     //
            BSTR const          taskName                                                    = SysAllocString(applicationName);                        //
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
            taskExecutablePath                                = SysAllocString(applicationFilePath);

            ::delete[] taskExecutableArgumentsBuffer;

            if (
              NULL  != taskAuthor                    and
              NULL  != taskDailyTriggerName          and
              NULL  != taskDailyTriggerTimeEnd       and
              NULL  != taskDailyTriggerTimeStart     and
              NULL  != taskExecutableArguments       and
              NULL  != taskExecutablePath            and
              L'\0' != applicationFilePath[0]   and
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
              (void) std::fwide(stdin, +1);

              standardInputDescriptor = ::_fileno(stdin);
              standardInputIsTeletype = standardInputDescriptor != -1 and 0 != ::_isatty(standardInputDescriptor);

              do {
                // --> catalog -> message(credentialsPromptMessage);
                if (EOF == std::fputs(catalog -> messagePrefix, stdout))
                break;

                (void) std::fputws(credentialsPromptMessage, stdout);
                (void) std::fputs (catalog -> messageSuffix, stdout);
              } while (false);

              // ...
              if (standardInputIsTeletype) { // --> std::fgetws(…)
                credentialsAuthenticationBuffer = &credentialsAuthenticationBuffer;

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
      #endif

      /* ... ->> Windows Services --- TODO (Lapys) -> Get it working for basic test */
      if (not catalog -> clocked)
      if (NULL != libraries[advapi32].moduleHandle and NULL != libraries[kernel32].moduleHandle) {
        SC_HANDLE          (*const CreateServiceW)             (SC_HANDLE, LPCWSTR, LPCWSTR, DWORD, DWORD, DWORD, DWORD, LPCWSTR, LPCWSTR, LPDWORD, LPCWSTR, LPCWSTR, LPCWSTR) = reinterpret_cast<SC_HANDLE (*)(SC_HANDLE, LPCWSTR, LPCWSTR, DWORD, DWORD, DWORD, DWORD, LPCWSTR, LPCWSTR, LPDWORD, LPCWSTR, LPCWSTR, LPCWSTR)>(::GetProcAddress(libraries[advapi32].moduleHandle, "CreateServiceW"));              // --> <windows.h>
        SC_HANDLE          (*const OpenSCManagerW)             (LPCWSTR, LPCWSTR, DWORD)                                                                                       = reinterpret_cast<SC_HANDLE (*)(LPCWSTR, LPCWSTR, DWORD)>                                                                                      (::GetProcAddress(libraries[advapi32].moduleHandle, "OpenSCManagerW"));              // --> <windows.h>
        BOOL               (*const StartServiceCtrlDispatcherW)(SERVICE_TABLE_ENTRYW const*)                                                                                   = reinterpret_cast<BOOL      (*)(SERVICE_TABLE_ENTRYW const*)>                                                                                  (::GetProcAddress(libraries[advapi32].moduleHandle, "StartServiceCtrlDispatcherW")); // --> <windows.h>
        SC_HANDLE                  serviceControlManagerHandle                                                                                                                 = NULL;                                                                                                                                                                                                                              //
        SC_HANDLE                  serviceControlServiceHandle                                                                                                                 = NULL;                                                                                                                                                                                                                              //
        SERVICE_TABLE_ENTRYW       serviceEntries[]                                                                                                                            = {{NULL, NULL}, {NULL, NULL}};                                                                                                                                                                                                      //
        static struct serviceinfo *service                                                                                                                                     = NULL;                                                                                                                                                                                                                              //
        static struct serviceinfo /* final */ {
          static void CALLBACK callback(PVOID const /* parameter */, BOOLEAN const /* triggered */) {
            catalog -> update();
          }

          static DWORD WINAPI control(DWORD const code, DWORD const /* event */, LPVOID const /* eventData */, LPVOID const /* parameter */) {
            BOOL (*const SetEvent)        (HANDLE)                                  = reinterpret_cast<BOOL (*)(HANDLE)>                                 (::GetProcAddress(libraries[kernel32].moduleHandle, "SetEvent"));         // --> <windows.h> → <synchapi.h>
            BOOL (*const SetServiceStatus)(SERVICE_STATUS_HANDLE, LPSERVICE_STATUS) = reinterpret_cast<BOOL (*)(SERVICE_STATUS_HANDLE, LPSERVICE_STATUS)>(::GetProcAddress(libraries[advapi32].moduleHandle, "SetServiceStatus")); // --> <windows.h>

            // ...
            if (NULL != SetEvent and NULL != SetServiceStatus and NULL != service)
            if (SERVICE_CONTROL_STOP == code and SERVICE_RUNNING == service -> status.dwCurrentState) {
              service -> status.dwCurrentState = SERVICE_STOP_PENDING;

              (void) SetServiceStatus(service -> statusHandle, &service -> status);
              (void) SetEvent        (service -> stopEvent);
            }

            return NO_ERROR;
          }

          static void WINAPI main(DWORD const /* count */, LPWSTR /* arguments */ []) {
            BOOL                  (*const CloseHandle)                  (HANDLE)                                                           = reinterpret_cast<BOOL                  (*)(HANDLE)>                                                          (::GetProcAddress(libraries[kernel32].moduleHandle, "CloseHandle"));                   // --> <windows.h>
            HANDLE                (*const CreateEventW)                 (LPSECURITY_ATTRIBUTES, BOOL, BOOL, LPCWSTR)                       = reinterpret_cast<HANDLE                (*)(LPSECURITY_ATTRIBUTES, BOOL, BOOL, LPCWSTR)>                      (::GetProcAddress(libraries[kernel32].moduleHandle, "CreateEventW"));                  // --> <windows.h> → <synchapi.h>
            HANDLE                (*const CreateTimerQueue)             ()                                                                 = reinterpret_cast<HANDLE                (*)()>                                                                (::GetProcAddress(libraries[kernel32].moduleHandle, "CreateTimerQueue"));              // --> <threadpoollegacyapiset.h>
            BOOL                  (*const CreateTimerQueueTimer)        (PHANDLE, HANDLE, WAITORTIMERCALLBACK, PVOID, DWORD, DWORD, ULONG) = reinterpret_cast<BOOL                  (*)(PHANDLE, HANDLE, WAITORTIMERCALLBACK, PVOID, DWORD, DWORD, ULONG)>(::GetProcAddress(libraries[kernel32].moduleHandle, "CreateTimerQueueTimer"));         // --> <threadpoollegacyapiset.h>
            BOOL                  (*const DeleteTimerQueue)             (HANDLE)                                                           = reinterpret_cast<BOOL                  (*)(HANDLE)>                                                          (::GetProcAddress(libraries[kernel32].moduleHandle, "DeleteTimerQueue"));              // --> <threadpoollegacyapiset.h>
            BOOL                  (*const DeleteTimerQueueEx)           (HANDLE, HANDLE)                                                   = reinterpret_cast<BOOL                  (*)(HANDLE, HANDLE)>                                                  (::GetProcAddress(libraries[kernel32].moduleHandle, "DeleteTimerQueueEx"));            // --> <threadpoollegacyapiset.h>
            DWORD                 (*const GetLastError)                 ()                                                                 = reinterpret_cast<DWORD                 (*)()>                                                                (::GetProcAddress(libraries[kernel32].moduleHandle, "GetLastError"));                  // --> <windows.h>
            SERVICE_STATUS_HANDLE (*const RegisterServiceCtrlHandlerExW)(LPCWSTR, LPHANDLER_FUNCTION_EX, LPVOID)                           = reinterpret_cast<SERVICE_STATUS_HANDLE (*)(LPCWSTR, LPHANDLER_FUNCTION_EX, LPVOID)>                          (::GetProcAddress(libraries[advapi32].moduleHandle, "RegisterServiceCtrlHandlerExW")); // --> <windows.h>
            BOOL                  (*const SetServiceStatus)             (SERVICE_STATUS_HANDLE, LPSERVICE_STATUS)                          = reinterpret_cast<BOOL                  (*)(SERVICE_STATUS_HANDLE, LPSERVICE_STATUS)>                         (::GetProcAddress(libraries[advapi32].moduleHandle, "SetServiceStatus"));              // --> <windows.h>
            DWORD                 (*const WaitForSingleObject)          (HANDLE, DWORD)                                                    = reinterpret_cast<DWORD                 (*)(HANDLE, DWORD)>                                                   (::GetProcAddress(libraries[kernel32].moduleHandle, "WaitForSingleObject"));           // --> <windows.h> → <synchapi.h>
            HANDLE                        clockHandle                                                                                      = NULL;                                                                                                                                                                                               //
            HANDLE                        clockQueueHandle                                                                                 = NULL;                                                                                                                                                                                               //

            // ...
            return;
            if (NULL == CreateEventW or NULL == CreateTimerQueue or NULL == CreateTimerQueueTimer or NULL == RegisterServiceCtrlHandlerExW or NULL == SetServiceStatus or NULL == WaitForSingleObject) {
              catalog -> clocked = false;
              return;
            }

            catalog -> clocked                          = false;
            service -> status.dwCheckPoint              = 0u;
            service -> status.dwControlsAccepted        = SERVICE_ACCEPT_STOP;
            service -> status.dwCurrentState            = SERVICE_RUNNING;
            service -> status.dwServiceSpecificExitCode = 0x00u; // ->> Ignored unless `ERROR_SERVICE_SPECIFIC_ERROR == ::dwWin32ExitCode`
            service -> status.dwServiceType             = SERVICE_WIN32_OWN_PROCESS;
            service -> status.dwWin32ExitCode           = NO_ERROR;
            service -> statusHandle                     = RegisterServiceCtrlHandlerExW(applicationName, &service -> control, static_cast<LPVOID>(service));
            service -> stopEvent                        = CreateEventW(static_cast<LPSECURITY_ATTRIBUTES>(NULL), TRUE, FALSE, static_cast<LPCWSTR>(NULL)); // ->> `CloseHandle(…)` (if non-`NULL`) on program termination
            clockQueueHandle                            = CreateTimerQueue();

            do {
              if (NULL == service -> statusHandle or NULL == clockQueueHandle)
              break;

              if (NULL == service -> stopEvent or FALSE == CreateTimerQueueTimer(&clockHandle, clockQueueHandle, &service -> callback, static_cast<PVOID>(service), 0u, catalog -> clockInterval, 0x00u)) {
                service -> status.dwCurrentState  = SERVICE_STOPPED;
                service -> status.dwWin32ExitCode = NULL == GetLastError ? ERROR_INVALID_HANDLE : GetLastError();
                (void) SetServiceStatus(service -> statusHandle, &service -> status);

                break;
              }

              if (FALSE       == SetServiceStatus   (service -> statusHandle, &service -> status)) break;
              if (WAIT_FAILED == WaitForSingleObject(service -> stopEvent,    INFINITE))           break;

              // ...
              catalog -> clocked = true;
            } while (false);

            if (INVALID_HANDLE_VALUE != service -> stopEvent and NULL != service -> stopEvent and NULL != CloseHandle) (void) CloseHandle(service -> stopEvent);
            if (NULL != clockQueueHandle and NULL != DeleteTimerQueueEx) { (void) DeleteTimerQueueEx(clockQueueHandle, static_cast<HANDLE>(NULL)); clockQueueHandle = NULL; }
            if (NULL != clockQueueHandle and NULL != DeleteTimerQueue)   { (void) DeleteTimerQueue  (clockQueueHandle);                            clockQueueHandle = NULL; }

            service -> status.dwCurrentState = SERVICE_STOPPED;
            (void) SetServiceStatus(service -> statusHandle, &service -> status);
          }

          /* ... */
          SERVICE_STATUS        status;
          SERVICE_STATUS_HANDLE statusHandle;
          HANDLE                stopEvent;
        } s = {};

        // ...
        service                         = &s;
        service        -> statusHandle  = NULL;
        service        -> stopEvent     = INVALID_HANDLE_VALUE;
        serviceEntries -> lpServiceName = applicationName;
        serviceEntries -> lpServiceProc = &service -> main; // --> LPSERVICE_MAIN_FUNCTIONW

        if (
          NULL != ::GetProcAddress(libraries[kernel32].moduleHandle, "CreateEventW")                  and // --> <windows.h> → <synchapi.h>
          NULL != ::GetProcAddress(libraries[kernel32].moduleHandle, "CreateTimerQueue")              and // --> <threadpoollegacyapiset.h>
          NULL != ::GetProcAddress(libraries[kernel32].moduleHandle, "CreateTimerQueueTimer")         and // --> <threadpoollegacyapiset.h>
          NULL != ::GetProcAddress(libraries[advapi32].moduleHandle, "RegisterServiceCtrlHandlerExW") and // --> <windows.h>
          NULL != ::GetProcAddress(libraries[kernel32].moduleHandle, "SetEvent")                      and // --> <windows.h> → <synchapi.h>
          NULL != ::GetProcAddress(libraries[advapi32].moduleHandle, "SetServiceStatus")              and // --> <windows.h>
          NULL != ::GetProcAddress(libraries[kernel32].moduleHandle, "WaitForSingleObject")           and // --> <windows.h> → <synchapi.h>
          NULL != CreateServiceW and NULL != OpenSCManagerW and NULL != StartServiceCtrlDispatcherW
        ) {
          serviceControlManagerHandle = OpenSCManagerW(static_cast<LPCWSTR>(NULL), static_cast<LPCWSTR>(NULL), SC_MANAGER_ALL_ACCESS);

          if (NULL != serviceControlManagerHandle) {
            serviceControlServiceHandle = CreateServiceW(serviceControlManagerHandle, /* --> WCHAR[256] */ L"cataloger", /* --> WCHAR[256] */ applicationName, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
              L"c:\\abc.exe",            // path to service's binary
              NULL,                      // no load ordering group
              NULL,                      // no tag identifier
              NULL,                      // no dependencies
              L"NT AUTHORITY\\NetworkService",
              L"");                     // no password
            catalog -> clocked          = FALSE != StartServiceCtrlDispatcherW(serviceEntries);
          }
        }
      }

      // TODO (Lapys) -> `WaitForSingleObject(…)` → `SetTimer(…)` → `Sleep(…)`
      if (not catalog -> clocked) {}
    #endif

    // MANUAL METHOD
  #endif
  }

  // GET CURRENT DATE/ TIME
  // CHECK IF TIME ELAPSED OR IF RUN FIRST TIME
  // SPAWN LOG not as child process; format: 2023–07–07.log
  // HELP SCREEN?
  // ABOUT SCREEN

  std::printf("[...]: 0x%02lX {allocated: %4.5s, name: \"%s\"}" "\r\n", (unsigned long) reinterpret_cast<uintptr_t>(catalog -> clockFileStream), catalog -> clockPathAllocated ? "true" : "false", catalog -> clockPath);

  // ...
  return catalog -> exit(EXIT_SUCCESS);
}

// int __cdecl _tmain(int argc, TCHAR* argv[])
// {
//     const SERVICE_TABLE_ENTRY dispatchTable[] = {
//         {serviceName, static_cast<LPSERVICE_MAIN_FUNCTION>(ServiceMainCallback)},
//         {NULL, NULL}
//     };

//     if (!StartServiceCtrlDispatcher(dispatchTable)) {
//         // if registration fails with ERROR_FAILED_SERVICE_CONTROLLER_CONNECT
//         // this usually means we're running as console application
//         if (GetLastError() == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT) {
//             return CommonEntry(argc, argv, true);
//         }
//         return -1;
//     }

//     return 0;
// }
// this is what my entry point looks like
// for reference
// // callback registered with and called by the Service Control Manager
// VOID WINAPI ServiceMainCallback(DWORD argc, LPTSTR* argv)
// {
//     CommonEntry(argc, argv);
// }
