#include <ciso646> // --> and, not, or
#include <climits> // --> CHAR_BIT
#include <clocale> // --> LC_ALL;                                std::setlocale(…)
#include <csignal> // --> SIGSEGV;                               std::signal(…)
#include <cstddef> // --> NULL;                                  std::size_t
#include <cstdio>  // --> _IONBF, EOF, L_tmpnam, stderr, stdout; std::FILE; std::fflush(…), std::fopen(…), std::fputs(…), std::fwrite(…), std::setvbuf(…), std::tmpfile(…), std::tmpnam(…)
#include <cstdlib> // --> EXIT_FAILURE, EXIT_SUCCESS;            std::exit(…)
#include <ctime>   //
#include <new>     // --> new; std:nothrow
#if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
# include <stdio.h>  // --> ::fileno(…)
# include <unistd.h> // --> ::isatty(…)
#elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
# define _CRT_SECURE_NO_WARNINGS
# include <windows.h> // --> ENABLE_VIRTUAL_TERMINAL_PROCESSING, FOREGROUND_RED, INVALID_HANDLE_VALUE, PSECURITY_DESCRIPTOR, STD_ERROR_HANDLE; CONSOLE_SCREEN_BUFFER_INFO, DWORD, HANDLE; ::GetConsoleMode(…), ::GetConsoleScreenBufferInfo(…), ::GetStdHandle(…), ::SetConsoleMode(…), ::SetConsoleTextAttribute(…)
#   include <objbase.h>  // --> ::COINIT_MULTITHREADED; ::CoInitializeEx(…), ::CoInitializeSecurity(…), ::CoUninitialize(…)
#   include <objidl.h>   // --> SOLE_AUTHENTICATION_SERVICE
#   include <winerror.h> // --> FAILED, SUCCEEDED
#   include <winnt.h>    // --> HRESULT
#   if _WIN32_WINNT+0 >= 0x0600 // --> _WIN32_WINNT_VISTA | _WIN32_WINNT_WS08
#     include <comutil.h>  // --> _bstr_t, _variant_t
#     include <taskschd.h> // --> IAction, IActionCollection, IDailyTrigger, IRegistrationInfo, IRepetitionPattern, ITaskDefinition, ITaskFolder, ITaskService, ITrigger, ITriggerCollection
#   endif
#endif

/* Main --> cataloger [log_directory] [clock_path] */
// COMPILE: del cataloger.exe && cls && clang++ -pedantic -std=c++98 -Wall -Wextra cataloger.cpp -o cataloger.exe -lole32 -loleaut32 && cataloger.exe A C:\Users\oluwa\…\cataloger-clock.dat & del cataloger.exe
// RUN    : cataloger C:/Users/oluwa/OneDrive/Lapys/Catalog C:/Users/oluwa/OneDrive/Lapys/Catalog/cataloger-clock.dat
int main(int count, char* arguments[]) /* noexcept */ {
  static struct cataloger *catalogAddress = NULL;
  struct cataloger /* final */ {
    enum /* : std::size_t */ { MESSAGE_MAXIMUM_LENGTH = 256u };
    union formatinfo { unsigned char metadata[32]; /* ->> Arbitrarily-sized */ };

    /* ... */
    /* [[noreturn]] extern "C" */ static void error(int const signal) {
      bool (*const message)(char const[], std::FILE*) = NULL == catalogAddress ? NULL : &catalogAddress -> message;

      // ...
      if (NULL != message) {
        catalogAddress = NULL;

        switch (signal) {
          case SIGABRT: std::exit((message("Cataloger stopped by abormal termination",               stderr),  EXIT_FAILURE));                break;
          case SIGFPE : std::exit((message("Cataloger stopped by a floating-point exception",        stderr),  EXIT_FAILURE));                break;
          case SIGILL : std::exit((message("Cataloger stopped by an invalid executable instruction", stderr),  EXIT_FAILURE));                break;
          case SIGINT : std::exit((message("Cataloger stopped by an external interrupt",             stderr) ? EXIT_SUCCESS : EXIT_FAILURE)); break;
          case SIGSEGV: std::exit((message("Cataloger stopped by impermissible memory access",       stderr),  EXIT_FAILURE));                break;
          case SIGTERM: std::exit((message("Cataloger stopped by a termination request",             stderr),  EXIT_FAILURE));                break;
          /* case SIGALRM, SIGBUS, SIGCHLD, SIGCONT, SIGEMT, SIGHUP,    SIGIO, SIGIOT, SIGKILL, SIGPIPE, SIGPOLL, SIGPROF, SIGPWR, SIGQUIT, SIGRTMAX, SIGRTMIN, SIGSTKFLT, SIGSTOP, SIGSYS, SIGTRAP, SIGTSTP, SIGTTIN, SIGTTOU, SIGURG, SIGUSR1, SIGUSR2, SIGVTALRM, SIGXCPU, SIGXFSZ, SIGWINCH: break; */
          /* case SIGCLD,  SIGEMT, SIGINFO, SIGLOST, SIGPWR, SIGSTKFLT, SIGUNUSED                                                                                                                                                                                                              : break; */
        }

        message("Cataloger stopped", stderr);
      }

      std::exit(EXIT_FAILURE);
    }

    static bool format(std::FILE* const stream, bool const recolor = true, formatinfo* const information = NULL) {
      #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
        int const streamDescriptor = stream == stderr ? ::fileno(stream) /* --> STDERR_FILENO */ : -1;

        // ...
        (void) information;

        if (streamDescriptor != -1 and ::isatty(streamDescriptor) == 1) {
          if (not recolor)
            return std::fwrite("\x1B" "[00m", sizeof(char), 5u, stream) == 5u;

          return stream == stderr ? std::fwrite("\x1B" "[31m", sizeof(char), 5u, stream) == 5u : true;
        }
      #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
        CONSOLE_SCREEN_BUFFER_INFO streamConsoleScreenBufferInformation = {};
        HANDLE const               streamStandardDeviceHandle           = stream == stderr ? ::GetStdHandle(STD_ERROR_HANDLE) : NULL;

        // ...
        if (INVALID_HANDLE_VALUE != streamStandardDeviceHandle and NULL != streamStandardDeviceHandle) {
          if (not recolor)
          if (NULL != information) {
            if (true == information -> metadata[0])
            return std::fwrite("\x1B" "[00m", sizeof(char), 5u, stream) == 5u;

            if (sizeof information -> metadata / sizeof(unsigned char) >= sizeof(DWORD)) {
              for (std::size_t index = sizeof(DWORD); index; --index)
              streamConsoleScreenBufferInformation.wAttributes = information -> metadata[index] | (streamConsoleScreenBufferInformation.wAttributes << CHAR_BIT);
            }

            return FALSE != ::SetConsoleTextAttribute(streamStandardDeviceHandle, streamConsoleScreenBufferInformation.wAttributes);
          }

          #ifdef ENABLE_VIRTUAL_TERMINAL_PROCESSING // --> _WIN32_WINNT_WIN10
            DWORD streamConsoleMode = 0x00u;

            // ...
            if (FALSE != ::GetConsoleMode(streamStandardDeviceHandle, &streamConsoleMode))
            if (FALSE != ::SetConsoleMode(streamStandardDeviceHandle, streamConsoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING+0)) {
              if (NULL != information)
              information -> metadata[0] = true;

              return stream == stderr ? std::fwrite("\x1B" "[31m", sizeof(char), 5u, stream) == 5u : true;
            }
          #endif

          if (FALSE != ::GetConsoleScreenBufferInfo(streamStandardDeviceHandle, &streamConsoleScreenBufferInformation)) {
            if (NULL != information) {
              information -> metadata[0] = false;

              if (sizeof information -> metadata / sizeof(unsigned char) >= sizeof(DWORD)) {
                for (std::size_t index = 0u; index != sizeof(DWORD); streamConsoleScreenBufferInformation.wAttributes >>= CHAR_BIT)
                information -> metadata[++index] = static_cast<unsigned char>(streamConsoleScreenBufferInformation.wAttributes & UCHAR_MAX);
              }
            }

            return stream == stderr ? FALSE != ::SetConsoleTextAttribute(streamStandardDeviceHandle, FOREGROUND_RED) : true;
          }
        }
      #endif

      return false;
    }

    static bool message(char const message[], std::FILE* const stream = stdout) {
      if (NULL == catalogAddress)            return false;
      if (NULL == message or NULL == stream) return true;

      char        const messageOverflowSuffix[]     = "…" "\r\n";                                                                  // ->> Source literal encoding to multi-byte NUL-terminated string
      std::size_t const messageOverflowSuffixLength = (sizeof messageOverflowSuffix / sizeof(char)) - 1u;                          //
      bool              messageOverflowed           = false;                                                                       //
      bool              messageOutputted            = false;                                                                       //
      bool              messageFormatted            = false;                                                                       //
      formatinfo        messageFormatInformation    = {};                                                                          //
      char const *const messageComponents[]         = {catalogAddress -> messagePrefix, message, catalogAddress -> messageSuffix}; //
      std::size_t       messageBufferLength         = 0u;                                                                          //
      char              messageBuffer[MESSAGE_MAXIMUM_LENGTH + messageOverflowSuffixLength + /* ->> NUL terminator */ 1u];         //

      // ...
      for (std::size_t index = 0u; index != sizeof messageComponents / sizeof(char const*); ++index) {
        char const *const messageComponent         = messageComponents[index];
        bool const        messageComponentIsAffix  = message != messageComponent;
        bool const        messageComponentIsSuffix = messageComponent == catalogAddress -> messageSuffix or index == (sizeof messageComponents / sizeof(char const*)) - 1u;

        // ...
        if (NULL == messageComponent) {
          if (messageComponentIsAffix)
          continue;

          break;
        }

        for (std::size_t subindex = 0u; ; ++subindex) {
          bool messageComponentSuffixed = false; // ->> Determines if the `messageComponent` before `::messageSuffix` (or `message`) repeatedly ends with `::messageSuffix`

          // ... --> messageComponentSuffixed = …;
          if (NULL != catalogAddress -> messageSuffix and not messageComponentIsAffix)
          for (std::size_t componentIndex = 0u, suffixIndex = 0u; ; ) {
            if ('\0' == messageComponent[componentIndex]) {
              messageComponentSuffixed = suffixIndex and '\0' == catalogAddress -> messageSuffix[suffixIndex];
              break; // ->> Possibly ends with `::messageSuffix`
            }

            if ('\0' == catalogAddress -> messageSuffix[suffixIndex]) {
              suffixIndex = 0u;
              continue; // ->> Continue checks for repeats
            }

            if (messageComponent[componentIndex++] != catalogAddress -> messageSuffix[suffixIndex++])
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

      (void) std::fflush (stream);
      (void) std::setvbuf(stream, NULL, _IONBF, 0u);

      messageBuffer[messageBufferLength] = '\0';
      messageFormatted                   = catalogAddress -> format(stream, true, &messageFormatInformation);
      messageOutputted                   = EOF != std::fputs(messageBuffer, stream);

      messageOutputted ? (void) std::fflush             (stream)                                   : std::clearerr(stream);
      messageFormatted ? (void) catalogAddress -> format(stream, false, &messageFormatInformation) : (void) 00;

      return messageOutputted;
    }

    static bool warn(char const message[], std::FILE* const stream = stderr) {
      return catalogAddress -> message(message, stream);
    }

    /* ... */
    char const *applicationName;
    char       *logDirectoryPath;
    char const *messagePrefix;
    char const *messageSuffix;
    std::FILE  *timerFileStream;
    char       *timerPath;
    bool        timerPathAllocated;
  } catalog = {};

  // ...
  (void) std::setlocale(LC_ALL,  "LC_TIME=C.UTF-8");
  (void) std::signal   (SIGSEGV, &catalog.error);

  catalogAddress             = &catalog;                        //
  catalog.applicationName    = "cataloger";                     //
  catalog.logDirectoryPath   = count > 1 ? arguments[1] : NULL; //  ->> Filesystem location for storing catalogs; Assume NUL-terminated
  catalog.messagePrefix      = "cataloger" ": ";                //
  catalog.messageSuffix      = "\r\n";                          //
  catalog.timerFileStream    = NULL;                            //
  catalog.timerPath          = count > 2 ? arguments[2] : NULL; // ->> Filesystem location for serializing catalog timer; Assume NUL-terminated
  catalog.timerPathAllocated = false;                           //

  // ...
  if (NULL == catalog.logDirectoryPath) {
    (void) catalog.message("No directory for logs specified; defaulting to the current working directory, instead");
    catalog.logDirectoryPath = const_cast<char*>("./");
  }

  if (NULL == catalog.timerPath)
  (void) catalog.message("No directory for the catalog's internal clock specified; defaulting to the current working directory, instead");

  // ... --> catalog.timerFileStream = …;
  if (NULL == catalog.timerPath)
    catalog.timerFileStream = std::tmpfile();

  else {
    catalog.timerFileStream = std::fopen(catalog.timerPath, "wb+");

    if (NULL == catalog.timerFileStream) {
      char  const catalogTimerFileNameFallback      [] = "cataloger-clock.dat";
      char        catalogTimerFileNameFallbackBuffer[L_tmpnam + (sizeof catalogTimerFileNameFallback / sizeof(char))];
      std::size_t catalogTimerFileNameFallbackBufferLength = 0u;
      std::size_t catalogTimerPathLength                   = 0u;
      bool        catalogTimerPathSuffixed                 = false; // ->> Determines if `::timerPath` (significantly) ends with `pathDelimiters[…]`
      char  const pathDelimiters[]                         = {'/'
        #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
          , '\\'
        #endif
      };

      // ... --> catalogTimerFileNameFallbackBuffer       = std::tmpnam(…) ?? catalogTimerFileNameFallback;
      //         catalogTimerFileNameFallbackBufferLength = …;
      catalogTimerFileNameFallbackBuffer[(sizeof catalogTimerFileNameFallbackBuffer / sizeof(char)) - 1u] = '\0';

      if (catalogTimerFileNameFallbackBuffer != std::tmpnam(catalogTimerFileNameFallbackBuffer)) {
        for (std::size_t index = 0u; index != sizeof catalogTimerFileNameFallback / sizeof(char); ++index)
        catalogTimerFileNameFallbackBuffer[index] = catalogTimerFileNameFallback[index];
      }

      while ('\0' != catalogTimerFileNameFallbackBuffer[catalogTimerFileNameFallbackBufferLength])
      ++catalogTimerFileNameFallbackBufferLength;

      for (std::size_t index = catalogTimerFileNameFallbackBufferLength; index--; ) {
        // ... ->> Unique names only, rather than unique file paths
        for (std::size_t subindex = 0u; subindex != sizeof pathDelimiters / sizeof(char); ++subindex)
        if (catalogTimerFileNameFallbackBuffer[index] == pathDelimiters[subindex]) {
          catalogTimerFileNameFallbackBufferLength -= ++index;

          for (subindex = 0u; subindex <= catalogTimerFileNameFallbackBufferLength; ++index, ++subindex)
          catalogTimerFileNameFallbackBuffer[subindex] = catalogTimerFileNameFallbackBuffer[index];

          index = 0u;
          break;
        }
      }

      // ... --> catalog.timerPath        = …;
      //         catalogTimerPathLength   = …;
      //         catalogTimerPathSuffixed = …;
      for (; '\0' != catalog.timerPath[catalogTimerPathLength]; ++catalogTimerPathLength) {
        for (std::size_t subindex = 0u; subindex != sizeof pathDelimiters / sizeof(char); ++subindex)
        if (catalog.timerPath[catalogTimerPathLength] == pathDelimiters[subindex]) {
          for (char *iterator = catalog.timerPath + (catalogTimerPathLength + 1u); ; ++iterator) {
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

      // ...
      #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
        char             *catalogTimerPathBuffer          = NULL;
        bool              catalogTimerPathPrefixed        = false; // ->> Determines if `::timerPath` (significantly) begins with `catalogTimerPathUNCPrefix`
        char        const catalogTimerPathUNCPrefix[]     = "\\\\?\\";
        std::size_t       catalogTimerPathUNCPrefixLength = (sizeof catalogTimerPathUNCPrefix / sizeof(char)) - 1u;

        // ... --> catalogTimerPathPrefixed = …;
        for (std::size_t prefixIndex = 0u, timerIndex = 0u; ; ++prefixIndex, ++timerIndex) {
          switch (catalog.timerPath[timerIndex]) {
            case ' ': case '\f': case '\n': case '\r': case '\t': case '\v':
            continue;
          }

          if (catalogTimerPathUNCPrefixLength == prefixIndex) {
            catalogTimerPathPrefixed = true;
            break;
          }

          if (catalog.timerPath[timerIndex] != catalogTimerPathUNCPrefix[prefixIndex])
          break;
        }

        // ...
        catalogTimerPathBuffer = ::new (std::nothrow) char[(catalogTimerPathPrefixed ? 0u : catalogTimerPathUNCPrefixLength) + catalogTimerPathLength + /* ->> Path delimiter */ 1u + catalogTimerFileNameFallbackBufferLength + /* ->> NUL terminator */ 1u];

        if (NULL == catalogTimerPathBuffer) {
          if (catalogTimerPathPrefixed or MAX_PATH+0 >= catalogTimerPathLength + /* ->> Path delimiter */ 1u + catalogTimerFileNameFallbackBufferLength + /* ->> NUL terminator */ 1u) {
            if (not catalogTimerPathSuffixed) {
              (void) catalog.warn("Cataloger exited; No file for the catalog's internal clock specified");
              return EXIT_FAILURE;
            }

            catalogTimerPathBuffer          = ::new (std::nothrow) char[catalogTimerPathLength + /* ->> Path delimiter */ 1u + catalogTimerFileNameFallbackBufferLength + /* ->> NUL terminator */ 1u];
            catalogTimerPathUNCPrefixLength = 0u;

            if (NULL == catalogTimerPathBuffer) {
              catalogTimerPathBuffer                   = ::new (std::nothrow) char[catalogTimerPathLength + /* ->> NUL terminator */ 1u];
              catalogTimerFileNameFallbackBufferLength = 0u;

              if (NULL == catalogTimerPathBuffer) {
                (void) catalog.warn("Cataloger exited; No file for the catalog's internal clock specified");
                return EXIT_FAILURE;
              }
            }
          }

          else {
            catalogTimerPathBuffer                   = ::new (std::nothrow) char[catalogTimerPathUNCPrefixLength + catalogTimerPathLength + /* ->> NUL terminator */ 1u];
            catalogTimerFileNameFallbackBufferLength = 0u;

            if (NULL == catalogTimerPathBuffer) {
              catalogTimerPathBuffer          = ::new (std::nothrow) char[catalogTimerPathLength + /* ->> NUL terminator */ 1u];
              catalogTimerPathUNCPrefixLength = 0u;

              if (NULL == catalogTimerPathBuffer) {
                (void) catalog.warn("Cataloger exited; No file for the catalog's internal clock specified");
                return EXIT_FAILURE;
              }
            }
          }
        }

        catalogTimerPathBuffer[catalogTimerPathLength] = '\0';

        for (std::size_t index = 0u; index != catalogTimerPathLength; ++index)
          catalogTimerPathBuffer[index] = catalog.timerPath[index] != '/' ? catalog.timerPath[index] : '\\';

        catalog.timerPath          = catalogTimerPathBuffer;
        catalog.timerPathAllocated = true;
        catalog.timerFileStream    = std::fopen(catalog.timerPath, "wb+");

        if (NULL == catalog.timerFileStream and 0u != catalogTimerPathUNCPrefixLength and not catalogTimerPathPrefixed) {
          for (std::size_t index = catalogTimerPathLength; index--; )
            catalog.timerPath[catalogTimerPathUNCPrefixLength + index] = catalog.timerPath[index];

          for (std::size_t index = catalogTimerPathUNCPrefixLength; index--; )
            catalog.timerPath[index] = catalogTimerPathUNCPrefix[index];

          catalogTimerPathLength += catalogTimerPathUNCPrefixLength;
          catalog.timerFileStream = std::fopen(catalog.timerPath, "wb+");
        }

        if (NULL == catalog.timerFileStream and 0u != catalogTimerFileNameFallbackBufferLength) {
          catalog.timerPath[catalogTimerPathLength]                                                 = '\\';
          catalog.timerPath[catalogTimerPathLength + catalogTimerFileNameFallbackBufferLength + 1u] = '\0';

          for (std::size_t index = 0u; index != catalogTimerFileNameFallbackBufferLength; ++index)
            catalog.timerPath[catalogTimerPathLength + index + 1u] = catalogTimerFileNameFallbackBuffer[index];

          catalogTimerPathLength += catalogTimerFileNameFallbackBufferLength + 1u;
          catalog.timerFileStream = std::fopen(catalog.timerPath, "wb+");
        }
      #else
        char *catalogTimerPathBuffer = NULL;

        // ...
        if (not catalogTimerPathSuffixed) {
          (void) catalog.warn("Cataloger exited; No file for the catalog's internal clock specified");
          return EXIT_FAILURE;
        }

        catalogTimerPathBuffer = ::new (std::nothrow) char[catalogTimerPathLength + /* ->> Path delimiter */ 1u + catalogTimerFileNameFallbackBufferLength + /* ->> NUL terminator */ 1u];

        if (NULL == catalogTimerPathBuffer) {
          catalogTimerPathBuffer                   = ::new (std::nothrow) char[catalogTimerPathLength + /* ->> NUL terminator */ 1u];
          catalogTimerFileNameFallbackBufferLength = 0u;

          if (NULL == catalogTimerPathBuffer) {
            (void) catalog.warn("Cataloger exited; No file for the catalog's internal clock specified");
            return EXIT_FAILURE;
          }
        }

        catalogTimerPathBuffer[catalogTimerPathLength] = '\0';

        for (std::size_t index = 0u; index != catalogTimerPathLength; ++index)
          catalogTimerPathBuffer[index] = catalog.timerPath[index];

        catalog.timerPath          = catalogTimerPathBuffer;
        catalog.timerPathAllocated = true;
        catalog.timerFileStream    = std::fopen(catalog.timerPath, "wb+");

        if (NULL == catalog.timerFileStream and 0u != catalogTimerFileNameFallbackBufferLength) {
          catalog.timerPath[catalogTimerPathLength]                                                 = '/';
          catalog.timerPath[catalogTimerPathLength + catalogTimerFileNameFallbackBufferLength + 1u] = '\0';

          for (std::size_t index = 0u; index != catalogTimerFileNameFallbackBufferLength; ++index)
            catalog.timerPath[catalogTimerPathLength + index + 1u] = catalogTimerFileNameFallbackBuffer[index];

          catalogTimerPathLength += catalogTimerFileNameFallbackBufferLength + 1u;
          catalog.timerFileStream = std::fopen(catalog.timerPath, "wb+");
        }
      #endif
    }
  }

  if (NULL == catalog.timerFileStream) {
    (void) catalog.warn("Cataloger exited; No file for the catalog's internal clock specified");
    return EXIT_FAILURE;
  }

  // ...
  #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
    // `usleep(…)` → `nanosleep(…)`
  #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
    bool catalogClocked = false;

    // ...
    // Windows Task Scheduler → Windows Services → `WaitForSingleObject(…)` → `SetTimer(…)` → `Sleep(…)`
    /* ... https://learn.microsoft.com/en-us/windows/win32/taskschd/daily-trigger-example--c--- */
    if (SUCCEEDED(::CoInitializeEx(static_cast<LPVOID>(NULL), ::COINIT_MULTITHREADED))) {
      do {
        IAction            *taskAction                  = NULL;                   //
        IActionCollection  *taskActionCollection        = NULL;                   //
        void               *taskExecutableAction        = NULL;                   // --> IExecAction*
        WCHAR const         taskAuthor[]                = L"LapysDev";            //
        void               *taskDailyTrigger            = NULL;                   // --> IDailyTrigger*
        short const         taskDailyTriggerInterval    = 1;                      //
        WCHAR const         taskDailyTriggerName     [] = L"checkup";             //
        WCHAR               taskDailyTriggerTimeEnd  [] = L"20xx-01-01T12:00:00"; // --> YYYY-MM-DDTHH:MM:SS(+-)(timezone)
        WCHAR               taskDailyTriggerTimeStart[] = L"20xx-01-01T12:00:00"; // --> YYYY-MM-DDTHH:MM:SS(+-)(timezone)
        ITaskDefinition    *taskDefinition              = NULL;                   //
        ITaskFolder        *taskFolder                  = NULL;                   //
        WCHAR const         taskFolderPath[]            = L"\\";                  // ->> Root
        WCHAR const         taskName      []            = L"Cataloger checkup";   //
        IRegistrationInfo  *taskRegistrationInformation = NULL;                   //
        IRepetitionPattern *taskRepititionPattern       = NULL;                   //
        void               *taskService                 = NULL;                   // --> ITaskService*
        ITrigger           *taskTrigger                 = NULL;                   //
        ITriggerCollection *taskTriggerCollection       = NULL;                   //

        // ...
        if (FAILED(::CoInitializeSecurity(static_cast<PSECURITY_DESCRIPTOR>(NULL), -1L, static_cast<SOLE_AUTHENTICATION_SERVICE*>(NULL), static_cast<void*>(NULL), RPC_C_AUTHN_LEVEL_PKT_PRIVACY, RPC_C_IMP_LEVEL_IMPERSONATE, static_cast<void*>(NULL), 0x00u, static_cast<void*>(NULL)))) break;
        if (FAILED(::CoCreateInstance    (::CLSID_TaskScheduler, static_cast<LPUNKNOWN>(NULL), ::CLSCTX_INPROC_SERVER, ::IID_ITaskService, &taskService)))                                                                                                                                  break;
        if (NULL == taskService)                                                                                                                                                                                                                                                            break;

        if (FAILED(static_cast<ITaskService*>(taskService) -> Connect  (::_variant_t(), ::_variant_t(), ::_variant_t(), ::_variant_t()))) break;
        if (FAILED(static_cast<ITaskService*>(taskService) -> GetFolder(::_bstr_t(taskFolderPath), &taskFolder)))                         break;
        if (NULL == taskFolder)                                                                                                           break;

        (void) taskFolder -> DeleteTask(::_bstr_t(taskName, 0x00L));

        if (FAILED(static_cast<ITaskService*>(taskService) -> NewTask(0x00u, &taskDefinition))) break;
        if (NULL == taskDefinition)                                                             break;

        if (FAILED(taskDefinition -> get_RegistrationInfo(&taskRegistrationInformation))) break;
        if (NULL == taskRegistrationInformation)                                          break;

        if (FAILED(taskRegistrationInformation -> put_Author  (::_bstr_t(taskAuthor))))  break;
        if (FAILED(taskDefinition              -> get_Triggers(&taskTriggerCollection))) break;
        if (NULL == taskTriggerCollection)                                               break;

        if (FAILED(taskTriggerCollection -> Create(::TASK_TRIGGER_DAILY, &taskTrigger))) break;
        if (NULL == taskTrigger)                                                         break;

        if (FAILED(taskTrigger -> QueryInterface(::IID_IDailyTrigger, &taskDailyTrigger))) break;
        if (NULL == taskDailyTrigger)                                                      break;

        taskDailyTriggerTimeEnd taskDailyTriggerTimeStart; // ->> SET APPROPRIATE YEARs

        if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> put_DaysInterval           (taskDailyTriggerInterval)))   break;
        if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> put_EndBoundary  (::_bstr_t(taskDailyTriggerTimeEnd))))   break;
        if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> put_Id           (::_bstr_t(taskDailyTriggerName))))      break;
        if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> put_StartBoundary(::_bstr_t(taskDailyTriggerTimeStart)))) break;
        if (FAILED(static_cast<IDailyTrigger*>(taskDailyTrigger) -> get_Repitition            (&taskRepititionPattern)))      break;
        if (NULL == taskRepititionPattern)                                                                                    break;

        if (FAILED(taskRepititionPattern -> put_Duration(::_bstr_t(L"PT4M"))))    break;
        if (FAILED(taskRepititionPattern -> put_Interval(::_bstr_t(L"PT1M"))))    break;
        if (FAILED(taskDefinition        -> get_Actions (&taskActionCollection))) break;
        if (NULL == taskActionCollection)                                         break;

        if (FAILED(taskActionCollection -> Create(::TASK_ACTION_EXEC, &taskAction))) break;
        if (NULL == taskAction)                                                      break;

        /* ... */
        catalogClocked = true;
      } while (false);

      // ...
      if (NULL != taskAction)                  (void) taskAction                              -> Release();
      if (NULL != taskActionCollection)        (void) taskActionCollection                    -> Release();
      if (NULL != taskRepititionPattern)       (void) taskRepititionPattern                   -> Release();
      if (NULL != taskTrigger)                 (void) taskTrigger                             -> Release();
      if (NULL != taskTriggerCollection)       (void) taskTriggerCollection                   -> Release();
      if (NULL != taskRegistrationInformation) (void) taskRegistrationInformation             -> Release();
      if (NULL != taskDefinition)              (void) taskDefinition                          -> Release();
      if (NULL != taskFolder)                  (void) taskFolder                              -> Release();
      if (NULL != taskService)                 (void) static_cast<ITaskService*>(taskService) -> Release();

      ::CoUninitialize();
    }

    // LPCWSTR wszTaskName = L"Daily Trigger Test Task";
    // wstring wstrExecutablePath = _wgetenv( L"WINDIR") + L"\\SYSTEM32\\NOTEPAD.EXE";
    // ITaskService *pService = NULL;
    // ITaskFolder *pRootFolder = NULL;
    // ITaskDefinition *pTask = NULL;
    // IRegistrationInfo *pRegInfo= NULL;
    // ITriggerCollection *pTriggerCollection = NULL;
    // ITrigger *pTrigger = NULL;
    // IDailyTrigger *pDailyTrigger = NULL;
    // IRepetitionPattern *pRepetitionPattern = NULL;
    // IActionCollection *pActionCollection = NULL;
    // IAction *pAction = NULL;
    // IExecAction *pExecAction = NULL;

    // hr = pAction->QueryInterface(
    //     IID_IExecAction, (void**) &pExecAction );
    // pAction->Release();
    // if( FAILED(hr) )
    // {
    //     printf("\nQueryInterface call failed for IExecAction: %x", hr );
    //     pRootFolder->Release();
    //     pTask->Release();
    //     CoUninitialize();
    //     return 1;
    // }

    // //  Set the path of the executable to notepad.exe.
    // hr = pExecAction->put_Path( _bstr_t( wstrExecutablePath.c_str() ) );
    // pExecAction->Release();
    // if( FAILED(hr) )
    // {
    //     printf("\nCannot put the executable path: %x", hr );
    //     pRootFolder->Release();
    //     pTask->Release();
    //     CoUninitialize();
    //     return 1;
    // }

    // //  ------------------------------------------------------
    // //  Securely get the user name and password. The task will
    // //  be created to run with the credentials from the supplied
    // //  user name and password.
    // CREDUI_INFO cui;
    // TCHAR pszName[CREDUI_MAX_USERNAME_LENGTH] = TEXT("");
    // TCHAR pszPwd[CREDUI_MAX_PASSWORD_LENGTH] = TEXT("");
    // BOOL fSave;
    // DWORD dwErr;

    // cui.cbSize = sizeof(CREDUI_INFO);
    // cui.hwndParent = NULL;
    // //  Ensure that MessageText and CaptionText identify
    // //  what credentials to use and which application requires them.
    // cui.pszMessageText = TEXT("Account information for task registration:");
    // cui.pszCaptionText = TEXT("Enter Account Information for Task Registration");
    // cui.hbmBanner = NULL;
    // fSave = FALSE;

    // //  Create the UI asking for the credentials.
    // dwErr = CredUIPromptForCredentials(
    //     &cui,                             //  CREDUI_INFO structure
    //     TEXT(""),                         //  Target for credentials
    //     NULL,                             //  Reserved
    //     0,                                //  Reason
    //     pszName,                          //  User name
    //     CREDUI_MAX_USERNAME_LENGTH,       //  Max number for user name
    //     pszPwd,                           //  Password
    //     CREDUI_MAX_PASSWORD_LENGTH,       //  Max number for password
    //     &fSave,                           //  State of save check box
    //     CREDUI_FLAGS_GENERIC_CREDENTIALS |  //  Flags
    //     CREDUI_FLAGS_ALWAYS_SHOW_UI |
    //     CREDUI_FLAGS_DO_NOT_PERSIST);

    // if(dwErr)
    // {
    //     cout << "Did not get credentials." << endl;
    //     CoUninitialize();
    //     return 1;
    // }

    // //  ------------------------------------------------------
    // //  Save the task in the root folder.
    // IRegisteredTask *pRegisteredTask = NULL;
    // hr = pRootFolder->RegisterTaskDefinition(
    //         _bstr_t( wszTaskName ),
    //         pTask,
    //         TASK_CREATE_OR_UPDATE,
    //         _variant_t(_bstr_t(pszName)),
    //         _variant_t(_bstr_t(pszPwd)),
    //         TASK_LOGON_PASSWORD,
    //         _variant_t(L""),
    //         &pRegisteredTask);
    // if( FAILED(hr) )
    // {
    //     printf("\nError saving the Task : %x", hr );
    //     pRootFolder->Release();
    //     pTask->Release();
    //     CoUninitialize();
    //     SecureZeroMemory(pszName, sizeof(pszName));
    //     SecureZeroMemory(pszPwd, sizeof(pszPwd));
    //     return 1;
    // }

    // printf("\n Success! Task successfully registered. " );

    // //  Clean up
    // pRootFolder->Release();
    // pTask->Release();
    // pRegisteredTask->Release();
    // CoUninitialize();
    // SecureZeroMemory(pszName, sizeof(pszName));
    // SecureZeroMemory(pszPwd, sizeof(pszPwd));
  #endif

  // GET CURRENT DATE/ TIME
  // CHECK IF TIME ELAPSED OR IF RUN FIRST TIME
  // SPAWN LOG not as child process; format: 2023–07–07.log
  // look for non-busy waits
  // HELP SCREEN?
  // ABOUT SCREEN
  //
  // switch from pointers to indexes

  std::printf("[...]: 0x%02lX {allocated: %4.5s, name: \"%s\"}" "\r\n", (unsigned long) reinterpret_cast<uintptr_t>(catalog.timerFileStream), catalog.timerPathAllocated ? "true" : "false", catalog.timerPath);
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
}
