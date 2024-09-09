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
  static struct cataloger *catalog = NULL;
  static struct cataloger /* final */ {
    enum              { MESSAGE_MAXIMUM_LENGTH = 256u };                     // --> std::size_t
    union formatinfo  { unsigned char metadata[32]; };                       // ->> Arbitrarily-sized
    enum  formatstyle { FORMAT_INITIAL = 0x00u, FORMAT_ERROR, FORMAT_WARN }; // --> bool

    /* ... */
    static void clock() {
      // ... ->> Runs every `::timerInterval` elapsed
    }

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

    static bool format(std::FILE* const stream, enum formatstyle const style, union formatinfo* const information = NULL) {
      std::size_t const informationMetadataSize = sizeof information -> metadata / sizeof(unsigned char);
      bool              styleSupported          = false;
      #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
        int const streamDescriptor = ::fileno(stream);

        // ...
        styleSupported = streamDescriptor != -1 and ::isatty(streamDescriptor) == 1;
      #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
        BOOL   WINAPI            (*GetConsoleMode)            (HANDLE, LPDWORD)                     = NULL;
        BOOL   WINAPI            (*GetConsoleScreenBufferInfo)(HANDLE, PCONSOLE_SCREEN_BUFFER_INFO) = NULL;
        HANDLE WINAPI            (*GetStdHandle)              (DWORD)                               = NULL;
        BOOL   WINAPI            (*SetConsoleMode)            (HANDLE, DWORD)                       = NULL;
        BOOL   WINAPI            (*SetConsoleTextAttribute)   (HANDLE, WORD)                        = NULL;
        HMODULE                    libraryModuleHandle                                              = NULL;
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

          if (FALSE != ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, libraryPath, &libraryModuleHandle))
          if (NULL != libraryModuleHandle) {
            GetConsoleMode             = reinterpret_cast<BOOL   WINAPI (*)(HANDLE, LPDWORD)>                    (::GetProcAddress(libraryModuleHandle, "GetConsoleMode"));             // --> <windows.h>
            GetConsoleScreenBufferInfo = reinterpret_cast<BOOL   WINAPI (*)(HANDLE, PCONSOLE_SCREEN_BUFFER_INFO)>(::GetProcAddress(libraryModuleHandle, "GetConsoleScreenBufferInfo")); // --> <windows.h>
            GetStdHandle               = reinterpret_cast<HANDLE WINAPI (*)(DWORD)>                              (::GetProcAddress(libraryModuleHandle, "GetStdHandle"));               // --> <windows.h>
            SetConsoleMode             = reinterpret_cast<BOOL   WINAPI (*)(HANDLE, DWORD)>                      (::GetProcAddress(libraryModuleHandle, "SetConsoleMode"));             // --> <windows.h>
            SetConsoleTextAttribute    = reinterpret_cast<BOOL   WINAPI (*)(HANDLE, WORD)>                       (::GetProcAddress(libraryModuleHandle, "SetConsoleTextAttribute"));    // --> <windows.h>
          }
        }

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
      union character {
        static void spanof(unsigned char const character[], std::size_t const stride, std::size_t* const begin, std::size_t* const end) {
          std::size_t characterBegin = 0u;
          std::size_t characterEnd   = stride;

          // ... ->> Ignores `character` endianness, leading bytes, and trailing bytes (assumes it is a distinct set of `stride` code units)
          for (; characterBegin != stride; ++characterBegin) {
            if (0x00u != character[characterBegin])
            break;
          }

          for (std::size_t index = characterBegin, redundant = false; ; ++index) {
            characterEnd = index;

            if (index == stride or redundant)
            break;

            for (++characterEnd, redundant = true; characterEnd != stride; ++characterEnd)
            if (0x00u != character[characterEnd]) {
              redundant = false;
              break;
            }
          }

          // ...
          if (NULL != begin) *begin = characterBegin;
          if (NULL != end)   *end   = characterEnd;
        }
      };

      std::size_t       messageLength               = 0u;                                                 // ->> Bytes
      std::size_t       messageOutputLength         = 0u;                                                 //
      bool              messageOutputted            = false;                                              //
      bool              messageOverflowed           = false;                                              //
      char        const messageOverflowSuffix[]     = "…" "\r\n";                                         // ->> Source literal encoding to multi-byte NUL-terminated string
      std::size_t const messageOverflowSuffixLength = (sizeof messageOverflowSuffix / sizeof(char)) - 1u; //
      bool              messageSuffixed             = false;                                              //
      std::size_t       messageSuffixLength         = 0u;                                                 //
      bool              messageSuffixSignificance   = true;                                               //
      char              messageOutput[MESSAGE_MAXIMUM_LENGTH + messageOverflowSuffixLength + /* ->> NUL terminator */ 1u];

      // ...
      if (NULL == message or NULL == stream) return true;
      if (MESSAGE_MAXIMUM_LENGTH < stride)   return false;

      // ... --> messageLength = …;
      for (std::size_t index = 0u; ; index += stride) {
        unsigned char const *character      = static_cast<unsigned char const*>(message) + index;
        bool                 characterIsNUL = true;

        // ... ->> Assumes `character` NUL is a complete set of zeroed code units
        for (std::size_t subindex = 0u; subindex != stride; ++subindex)
        if (0x00u != character[subindex]) {
          characterIsNUL = false;
          break;
        }

        if (characterIsNUL or MESSAGE_MAXIMUM_LENGTH == index) {
          messageLength = index;
          break;
        }
      }

      // ... ->> Truncate significant (non-whitespace trailing) `::messageSuffix` repeats
      if (NULL != catalog -> messageSuffix) {
        // ... --> messageSuffixLength = …;
        while ('\0' != catalog -> messageSuffix[messageSuffixLength] and MESSAGE_MAXIMUM_LENGTH != messageSuffixLength)
        ++messageSuffixLength;

        // ...
        for (std::size_t messageIndex = messageLength, messageSuffixIndex = messageSuffixLength, messageTrimIndex = messageIndex, messageTrimSubindex = stride; messageIndex and messageSuffixSignificance; messageIndex -= stride) {
          unsigned char const *const character      = static_cast<unsigned char const*>(message) + (messageIndex - stride);
          std::size_t                characterBegin = 0u;
          std::size_t                characterEnd   = stride;

          // ... --> characterBegin = …; characterEnd = …;
          character::spanof(character, stride, &characterBegin, &characterEnd);

          // ... --> messageLength = …;
          //     ->> Search last significant (non-whitespace trailing) occurrence of `::messageSuffix`
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
              for (bool suffixed = true; messageLength != messageTrimIndex; messageTrimIndex += stride) {
                unsigned char const *const character      = static_cast<unsigned char const*>(message) + messageTrimIndex;
                std::size_t                characterBegin = 0u;
                std::size_t                characterEnd   = stride;

                // ... --> messageSuffixSignificance = …;
                character::spanof(character, stride, &characterBegin, &characterEnd);

                characterBegin      = 0u == messageTrimSubindex ? characterBegin : messageTrimSubindex;
                messageTrimSubindex = 0u;

                for (std::size_t subindex = characterBegin; characterEnd != subindex; ++subindex) {
                  // ... ->> First code unit is the end of `::messageSuffix`, so it is ignored
                  if (suffixed) {
                    suffixed = false;
                    continue;
                  }

                  // ...
                  switch (static_cast<char>(character[subindex])) {
                    case '\f': case '\n': case '\r': case '\t': case '\v': case ' ':
                    continue;
                  }

                  messageSuffixSignificance = false;
                  break;
                }

                if (not messageSuffixSignificance)
                break;
              }

              // ... --> messageLength = …;
              //     ->> Truncate `message` by tracking the first instance in the last set of contiguous `::messageSuffix` repeats
              if (not messageSuffixSignificance)
              break;

              messageLength      = subindex + (messageIndex - stride);
              messageSuffixed    = true;
              messageSuffixIndex = messageSuffixLength;
            }
          }
        }
      }

      // ... --> messageOutput[messageOutputLength++…] = …;
      if (NULL != messagePrefix and not messageOverflowed)
      for (std::size_t index = 0u; '\0' != catalog -> messagePrefix[index]; ++index) {
        if (MESSAGE_MAXIMUM_LENGTH == messageOutputLength) {
          messageOverflowed = true;
          break;
        }

        messageOutput[messageOutputLength++] = catalog -> messagePrefix[index]
      }

      if (not messageOverflowed) {
        for (std::size_t index = 0u; index < messageLength; index += stride) {
          unsigned char const *const character      = static_cast<unsigned char const*>(message) + index;
          std::size_t                characterBegin = 0u;
          std::size_t                characterEnd   = stride;

          // ... --> characterBegin = …; characterEnd = …;
          character::spanof(character, stride, &characterBegin, &characterEnd);

          // ... CHECK IF PREFIX REPEATS and IGNORE
        }
        // for (std::size_t index = 0u, length = 0u; ; index += stride) {
        //   unsigned char const *const character      = reinterpret_cast<unsigned char const*>(encoded) + index;
        //   bool                       characterIsNUL = true;
        //   std::size_t                currentIndex   = 0u;
        //   std::size_t                nextIndex      = 0u;

        //   for (bool redundant = false; currentIndex != stride and not redundant; ++currentIndex) {
        //     nextIndex           = currentIndex + 1u;
        //     unencoded[length++] = static_cast<char>(character[currentIndex]);

        //     for (redundant = true; nextIndex != stride; ++nextIndex)
        //     if (0x00u != character[nextIndex]) {
        //       redundant = false;
        //       break;
        //     }

        //     if (not redundant and 0x00u == character[currentIndex]) {
        //       length           -= currentIndex;
        //       unencoded[length++] = '?';

        //       break;
        //     }
        //   }
        // }
      }

      (void) messageSuffixed;

      // POSSIBLY CHECK REPEATS FOR PREFIX?
      // ... --> messageOutput… = …;
      // if (NULL != catalog -> messagePrefix and not messageOverflowed)
      // for (std::size_t index = 0u; '\0' != catalog -> messagePrefix[index]; ++index) {
      //   if (MESSAGE_MAXIMUM_LENGTH == messageOutputLength) {
      //     messageOverflowed = true;
      //     break;
      //   }

      //   messageOutput[messageOutputLength++] = catalog -> messagePrefix[index];
      // }

      // if (messageOverflowed) {
      //   for (std::size_t index = 0u; index != messageOverflowSuffixLength; ++index)
      //   messageOutput[messageOutputLength++] = messageOverflowSuffix[index];
      // }

      // ...
      // (void) std::fflush (stream);                                       // ->> Ensure the `stream` delivers the `messageOutput` immediately
      // (void) std::setvbuf(stream, static_cast<char*>(NULL), _IONBF, 0u); //

      // messageOutput[messageOutputLength] = '\0';
      // messageOutputted                   = EOF != std::fputs(messageOutput, stream);

      // messageOutputted ? (void) std::fflush(stream) : std::clearerr(stream);

      // ...
      return messageOutputted;
    }
      static bool message(char    const message[], std::FILE* const stream = stdout) { return catalog -> message(message, stream, sizeof(char)); }
      static bool message(wchar_t const message[], std::FILE* const stream = stdout) { return catalog -> message(message, stream, sizeof(wchar_t)); }

    /* [[noreturn]] extern "C" */ static void quick_exit() {
      if (NULL != catalog)
        (void) catalog -> exit(catalog -> applicationExitCode);

      // ... ->> Cleanup regardless
      std::exit(EXIT_SUCCESS);
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
    int         applicationExitCode; // ->> For `::quick_exit(…)` primarily
    char const *applicationName;
    bool        clocked;
    char       *logDirectoryPath;
    char const *messagePrefix;
    char const *messageSuffix;
    bool        rerun;
    std::FILE  *timerFileStream;
    std::size_t timerInterval;
    char       *timerPath;
    bool        timerPathAllocated;
  } c = {};

  /* ... -> Vendor API setup, then initialization */
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

      /* extern "C" */ static void exit() {
        for (struct libraryinfo *library = libraries; library != libraries + (NULL == libraries ? 0u : librariesLength); ++library)
        if (NULL != library -> moduleHandle and /* --> FreeLibrary(…) */ NULL != library -> unloader) {
          library -> unloader(library -> moduleHandle);

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

      if (FALSE != ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, libraryPath, &libraries[kernel32].moduleHandle))
      if (NULL != libraries[kernel32].moduleHandle) {
        FreeLibrary              = reinterpret_cast<BOOL    (*)(HMODULE)>                                            (::GetProcAddress(libraries[kernel32].moduleHandle, "FreeLibrary"));              // --> <windows.h>
        GetCommandLineW          = reinterpret_cast<LPWSTR  (*)()>                                                   (::GetProcAddress(libraries[kernel32].moduleHandle, "GetCommandLineW"));          // --> <windows.h> → <processenv.h>
        LoadLibraryExW           = reinterpret_cast<HMODULE (*)(LPCWSTR, HANDLE, DWORD)>                             (::GetProcAddress(libraries[kernel32].moduleHandle, "LoadLibraryExW"));           // --> <windows.h>
        LocalFree                = reinterpret_cast<HLOCAL  (*)(HLOCAL)>                                             (::GetProcAddress(libraries[kernel32].moduleHandle, "LocalFree"));                // --> <windows.h>
        SetDefaultDllDirectories = reinterpret_cast<BOOL    (*)(DWORD)>                                              (::GetProcAddress(libraries[kernel32].moduleHandle, "SetDefaultDllDirectories")); // --> <windows.h>
        WideCharToMultiByte      = reinterpret_cast<int     (*)(UINT, DWORD, LPCWCH, int, LPSTR, int, LPCCH, LPBOOL)>(::GetProcAddress(libraries[kernel32].moduleHandle, "WideCharToMultiByte"));      // --> <windows.h>
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

        if (FALSE == ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, libraryPath, &library -> moduleHandle) or NULL == library -> moduleHandle) {
          library -> moduleHandle = LoadLibraryExW(libraryPath, static_cast<HANDLE>(NULL), LOAD_WITH_ALTERED_SEARCH_PATH);
          library -> unloader     = NULL == library -> moduleHandle ? NULL : FreeLibrary;
        }
      }

      // ...
      if (NULL != libraries[shell32].moduleHandle)
      CommandLineToArgvW = reinterpret_cast<LPWSTR* (*)(LPCWSTR, int*)>(::GetProcAddress(libraries[shell32].moduleHandle, "CommandLineToArgvW")); // --> <shellapi.h>

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
  catalog -> timerInterval       = 86400000u;                          // ->> Milliseconds
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

  /* ... ->> Execute internal clock */
  if (catalog -> rerun)
    catalog -> clock();

  else {
  #if false // TODO (Lapys)
    #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
      // TODO (Lapys) -> Linus service → `usleep(…)` → `nanosleep(…)`
    #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
      DWORD           (*GetModuleFileNameW) (HMODULE, LPWSTR, DWORD)               = NULL;
      BOOL            (*GetModuleHandleExA) (DWORD, LPCSTR, HMODULE*)              = NULL;
      int             (*MultiByteToWideChar)(UINT, DWORD, LPCCH, int, LPWSTR, int) = NULL;
      WCHAR             applicationFilePath[MAX_PATH + 1u]                         = {};
      std::size_t const applicationFilePathLength                                  = sizeof applicationFilePath / sizeof(WCHAR);
      HMODULE           applicationModuleHandle                                    = NULL;
      static WCHAR      applicationName[]                                          = L"Cataloger"; // --> ::MultiByteToWideChar(…, catalog -> applicationName, …)
      HMODULE           argumentModuleHandle                                       = NULL;
      char             *programPointer                                             = NULL; // --> ::_pgmptr
      wchar_t          *programPointerW                                            = NULL; // --> ::_wpgmptr

      // ...
      if (NULL != libraries[kernel32].moduleHandle) {
        GetModuleFileNameW  = reinterpret_cast<DWORD (*)(HMODULE, LPWSTR, DWORD)>              (::GetProcAddress(libraries[kernel32].moduleHandle, "GetModuleFileNameW"));  // --> <windows.h>
        GetModuleHandleExA  = reinterpret_cast<BOOL  (*)(DWORD, LPCSTR, HMODULE*)>             (::GetProcAddress(libraries[kernel32].moduleHandle, "GetModuleHandleExA"));  // --> <windows.h>
        MultiByteToWideChar = reinterpret_cast<int   (*)(UINT, DWORD, LPCCH, int, LPWSTR, int)>(::GetProcAddress(libraries[kernel32].moduleHandle, "MultiByteToWideChar")); // --> <windows.h>
      }

      // ... --> applicationModuleHandle = GetModuleHandleEx…(…);
      //         argumentModuleHandle    = GetModuleHandleExA(…);
      if (NULL != GetModuleHandleExA) {
        applicationModuleHandle = FALSE == GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, static_cast<LPCSTR>(NULL), &applicationModuleHandle) ? NULL : applicationModuleHandle;
        argumentModuleHandle    = FALSE == GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, arguments[0],              &argumentModuleHandle)    ? NULL : argumentModuleHandle;
      }

      applicationModuleHandle = NULL == applicationModuleHandle and FALSE == ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, static_cast<LPWSTR>(NULL), &applicationModuleHandle) ? NULL : applicationModuleHandle;

      // ... --> programPointer… = ::_get_…pgmptr(…);
      programPointer  = 0 != ::_get_pgmptr (&programPointer)  ? applicationModuleHandle == argumentModuleHandle ? arguments[0] : NULL : programPointer;
      programPointerW = 0 != ::_get_wpgmptr(&programPointerW) ?                                                                  NULL : programPointerW;

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
            catalog -> clock();
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
            HANDLE                        timerHandle                                                                                      = NULL;                                                                                                                                                                                               //
            HANDLE                        timerQueueHandle                                                                                 = NULL;                                                                                                                                                                                               //

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
            timerQueueHandle                            = CreateTimerQueue();

            do {
              if (NULL == service -> statusHandle or NULL == timerQueueHandle)
              break;

              if (NULL == service -> stopEvent or FALSE == CreateTimerQueueTimer(&timerHandle, timerQueueHandle, &service -> callback, static_cast<PVOID>(service), 0u, catalog -> timerInterval, 0x00u)) {
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
            if (NULL != timerQueueHandle and NULL != DeleteTimerQueueEx) { (void) DeleteTimerQueueEx(timerQueueHandle, static_cast<HANDLE>(NULL)); timerQueueHandle = NULL; }
            if (NULL != timerQueueHandle and NULL != DeleteTimerQueue)   { (void) DeleteTimerQueue  (timerQueueHandle);                            timerQueueHandle = NULL; }

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

  std::printf("[...]: 0x%02lX {allocated: %4.5s, name: \"%s\"}" "\r\n", (unsigned long) reinterpret_cast<uintptr_t>(catalog -> timerFileStream), catalog -> timerPathAllocated ? "true" : "false", catalog -> timerPath);

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
