// --> cataloger C:\Users\oluwa\OneDrive\Lapys\Catalog C:\Users\oluwa\OneDrive\Lapys\Catalog\schedule.dat
#include <ciso646> // --> and, not, or
#include <clocale> // --> LC_ALL;                        std::setlocale(…)
#include <csignal> // --> SIGSEGV;                       std::signal(…)
#include <cstddef> // --> NULL;                          std::size_t
#include <cstdio>  // --> EOF, L_tmpnam, stderr, stdout; std::FILE; std::fflush(…), std::fopen(…), std::fputs(…), std::fwrite(…), std::tmpnam(…), std::tmpfile(…)
#include <cstdlib> // --> EXIT_FAILURE, EXIT_SUCCESS;    std::exit(…)
#include <ctime>   //
#include <new>     // --> new;                           std:nothrow
#if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
# include <stdio.h>  // --> STDERR_FILENO; ::fileno(…)
# include <unistd.h> // --> ::isatty(…)
#elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
# define _CRT_SECURE_NO_WARNINGS
# include <windows.h> // --> ENABLE_VIRTUAL_TERMINAL_PROCESSING, FOREGROUND_RED, HANDLE, INVALID_HANDLE_VALUE, STD_ERROR_HANDLE; ::GetConsoleMode(…), ::GetConsoleScreenBufferInfo(…), ::GetStdHandle(…), ::SetConsoleMode(…), ::SetConsoleTextAttribute(…)
#endif

/* Main --> cataloger [log_path] [clock] */
int main(int count, char* arguments[]) /* noexcept */ {
  static struct cataloger *catalogAddress = NULL;
  struct cataloger /* final */ {
    enum /* : std::size_t */ { MESSAGE_MAXIMUM_LENGTH = 256u };

    /* [[noreturn]] extern "C" */ static void fault(int const signal) {
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

    static bool message(char const message[], std::FILE* const stream = stdout) {
      char        const messageTerminator[]         = "\r\n";                                             // ->> Source literal encoding to multi-byte NUL-terminated string
      std::size_t const messageTerminatorLength     = (sizeof messageTerminator     / sizeof(char)) - 1u; //
      char        const messageOverflowSuffix[]     = "…";                                                // ->> Source literal encoding to multi-byte NUL-terminated string
      std::size_t const messageOverflowSuffixLength = (sizeof messageOverflowSuffix / sizeof(char)) - 1u; //
      bool              messageOverflowed           = false;                                              //
      std::size_t       messageBufferLength         = 0u;                                                 //
      char              messageBuffer[MESSAGE_MAXIMUM_LENGTH + messageOverflowSuffixLength + messageTerminatorLength + /* ->> NUL terminator */ 1u];

      // ...
      if (NULL == message or NULL == stream)
      return true;

      // ... --> messageBuffer… += components[…];
      for (char const *const components[] = {catalogAddress -> messagePrefix, message, catalogAddress -> messageSuffix}, *const *component = components; component != components + (sizeof components / sizeof(char const*)); ++component) {
        bool const affix  = *component != message;
        bool const suffix = *component == catalogAddress -> messageSuffix or component == components + ((sizeof components / sizeof(char const*)) - 1u);

        // ...
        if (affix and NULL == *component)
        continue;

        for (char *destination = messageBuffer + messageBufferLength, *source = const_cast<char*>(*component); ; ++destination, ++source) {
          bool suffixed = false; // ->> Determines if `message` (or the `component` before `::messageSuffix`) (repeatedly) ends with `::messageSuffix`

          // ... --> suffixed = …;
          if (not affix and 0u != messageOverflowSuffixLength)
          for (char const *string = source, *substring = messageOverflowSuffix; ; ) {
            if ('\0' == *string)    { suffixed  = '\0' == *substring;    break; }
            if ('\0' == *substring) { substring = messageOverflowSuffix; continue; }

            if (*(string++) != *(substring++))
            break;
          }

          // ...
          if (suffixed or '\0' == *source) {
            messageBufferLength = destination - messageBuffer;
            break;
          }

          if (MESSAGE_MAXIMUM_LENGTH <= destination - messageBuffer) {
            messageBufferLength = MESSAGE_MAXIMUM_LENGTH - (suffix ? source - *component : 0u);
            messageOverflowed   = true; // ->> Completely elide `suffix` `component`s instead of truncating them
            break;
          }

          // ... --> messageBuffer[…] = …;
          *destination = *source;
        }
      }

      if (messageOverflowed) {
        for (char const *const components[] = {messageOverflowSuffix, messageTerminator}, *const *component = components; component != components + (sizeof components / sizeof(char const*)); ++component)
        for (char *destination = messageBuffer + messageBufferLength, *source = const_cast<char*>(*component); ; ++destination, ++source) {
          if ('\0' == *source) {
            messageBufferLength = destination - messageBuffer;
            break;
          }

          *destination = *source;
        }
      }

      // ...
      (void) std::fflush(stream);
      std::setbuf(stream, NULL);
      messageBuffer[messageBufferLength] = '\0';

      #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
        bool messageFormatted = false;

        // ...
        if (stream == stderr) {
          int const streamDescriptor = ::fileno(stderr);

          if (::isatty(streamDescriptor != -1 ? streamDescriptor : STDERR_FILENO) == 1)
          messageFormatted = std::fwrite("\x1B" "[31m", sizeof(char), 5u, stream) == 5u;
        }
      #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
        bool                       messageFormatted                     = false;
        DWORD                      streamConsoleMode                    = 0x00u;
        CONSOLE_SCREEN_BUFFER_INFO streamConsoleScreenBufferInformation = {};
        HANDLE                     streamStandardDeviceHandle           = NULL;
        bool                       streamSupportsANSIFormatting         = false;

        // ...
        if (stream == stderr) {
          streamStandardDeviceHandle = ::GetStdHandle(STD_ERROR_HANDLE);

          if (INVALID_HANDLE_VALUE != streamStandardDeviceHandle and NULL != streamStandardDeviceHandle) {
            #ifdef ENABLE_VIRTUAL_TERMINAL_PROCESSING  // --> _WIN32_WINNT_WIN10
              if (FALSE != ::GetConsoleMode(streamStandardDeviceHandle, &streamConsoleMode) ? FALSE != ::SetConsoleMode(streamStandardDeviceHandle, streamConsoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING) : false) {
                messageFormatted             = std::fwrite("\x1B" "[31m", sizeof(char), 5u, stream) == 5u;
                streamSupportsANSIFormatting = true;
              } else
            #endif

            if (FALSE != ::GetConsoleScreenBufferInfo(streamStandardDeviceHandle, &streamConsoleScreenBufferInformation))
            messageFormatted = FALSE != ::SetConsoleTextAttribute(streamStandardDeviceHandle, FOREGROUND_RED);
          }
        }
      #endif

      if (EOF != std::fputs(messageBuffer, stream))
        (void) std::fflush(stream);

      else {
        std::clearerr(stream);
        return false;
      }

      #if defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
        if (messageFormatted)
        (void) std::fwrite("\x1B" "[0m", sizeof(char), 4u, stream);
      #elif defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
        if (messageFormatted) {
          if (streamSupportsANSIFormatting)
            (void) std::fwrite("\x1B" "[0m", sizeof(char), 4u, stream);

          else
            (void) ::SetConsoleTextAttribute(streamStandardDeviceHandle, streamConsoleScreenBufferInformation.wAttributes);
        }
      #endif

      return true;
    }

    static bool warn(char const message[], std::FILE* const stream = stderr) {
      return catalogAddress -> message(message, stream);
    }

    /* ... */
    char const *applicationName;           //
    char const *logDirectoryPath;          // ->> Filesystem location for storing catalogs
    bool        logDirectoryPathAllocated; //
    char const *messagePrefix;             //
    char const *messageSuffix;             //
    std::FILE  *timerFileStream;           //
    char       *timerPath;                 // ->> Filesystem location for serializing catalog timer
    bool        timerPathAllocated;        //
  } catalog = {};

  // ...
  (void) std::setlocale(LC_ALL,  "LC_TIME=C.UTF-8");
  (void) std::signal   (SIGSEGV, &catalog.fault);

  catalogAddress                    = &catalog;                        //
  catalog.applicationName           = "cataloger";                     //
  catalog.logDirectoryPath          = count > 1 ? arguments[1] : NULL; // ->> Assume NUL-terminated
  catalog.logDirectoryPathAllocated = false;                           //
  catalog.messagePrefix             = "cataloger" ": ";                //
  catalog.messageSuffix             = "\r\n";                          //
  catalog.timerFileStream           = NULL;                            //
  catalog.timerPath                 = count > 2 ? arguments[2] : NULL; // ->> Assume NUL-terminated
  catalog.timerPathAllocated        = false;                           //

  // ...
  if (NULL == catalog.logDirectoryPath) {
    (void) catalog.message("No directory for logs specified; defaulting to the current working directory, instead");
    catalog.logDirectoryPath = "./";
  }

  if (NULL == catalog.timerPath)
  (void) catalog.message("No directory for the catalog's internal clock specified; defaulting to the current working directory, instead");

  // ...
  if (NULL == catalog.timerPath)
    catalog.timerFileStream = std::tmpfile();

  else {
    char        const catalogTimerFileNameFallback      [] = "cataloger-clock.dat";
    char              catalogTimerFileNameFallbackBuffer[L_tmpnam + (sizeof catalogTimerFileNameFallback / sizeof(char))];
    std::size_t       catalogTimerFileNameFallbackBufferLength = 0u;
    char             *catalogTimerPathBuffer                   = NULL;
    std::size_t       catalogTimerPathLength                   = 0u;
    bool              catalogTimerPathSuffixed                 = false; // ->> Determines if `::timerPath` (significantly) ends with `pathDelimiter`
    char        const pathDelimiters[]                         = {'/'
      #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
        , '\\'
      #endif
    };

    // ... --> catalogTimerFileNameFallbackBuffer = std::tmpnam(…) ?? catalogTimerFileNameFallback; catalogTimerFileNameFallbackBufferLength = …;
    catalogTimerFileNameFallbackBuffer[(sizeof catalogTimerFileNameFallbackBuffer / sizeof(char)) - 1u] = '\0';

    for (char *destination = catalogTimerFileNameFallbackBuffer, *source = NULL == std::tmpnam(catalogTimerFileNameFallbackBuffer) ? const_cast<char*>(catalogTimerFileNameFallback) : catalogTimerFileNameFallbackBuffer; ; ++source) {
      *(destination++) = *source;

      if ('\0' == *source) {
        catalogTimerFileNameFallbackBufferLength = destination - catalogTimerFileNameFallbackBuffer;
        break;
      }

      for (char const *pathDelimiter = pathDelimiters; pathDelimiter != pathDelimiters + (sizeof pathDelimiters / sizeof(char)); ++pathDelimiter)
      if (*pathDelimiter == *source) { // ->> Unique names only, rather than unique file paths
        destination  = catalogTimerFileNameFallbackBuffer;
        *destination = '\0';
      }
    }

    // ... --> catalog.timerPath = …; catalogTimerPathLength = …; catalogTimerPathSuffixed = …;
    for (char *iterator = catalog.timerPath; ; ++iterator) {
      for (char const *pathDelimiter = pathDelimiters; pathDelimiter != pathDelimiters + (sizeof pathDelimiters / sizeof(char)); ++pathDelimiter) {
        if (*iterator == *pathDelimiter)
        for (char *subiterator = iterator + 1; ; ++subiterator) {
          switch (*subiterator) {
            case ' ': case '\f': case '\n': case '\r': case '\t': case '\v':
            continue;
          }

          catalogTimerPathSuffixed = '\0' == *subiterator;
          break;
        }
      }

      if (catalogTimerPathSuffixed or '\0' == *iterator) {
        catalogTimerPathLength                    = iterator - catalog.timerPath;
        catalog.timerPath[catalogTimerPathLength] = '\0'; // ->> Possible `std::raise(SIGSEGV)` despite C++ standard guarantee for modifiable argument strings?

        break;
      }
    }

    if (catalogTimerPathSuffixed and 0u == catalogTimerFileNameFallbackBufferLength) {
      (void) catalog.warn("Cataloger exited; no file for the catalog's internal clock specified");
      return EXIT_FAILURE;
    }

    // ...
    #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
      bool              catalogerTimerPathPrefixed      = false; // ->> Determines if `::timerPath` (significantly) begins with `catalogTimerPathUNCPrefix`
      char        const catalogTimerPathUNCPrefix[]     = "\\\\?\\";
      std::size_t const catalogTimerPathUNCPrefixLength = sizeof catalogTimerPathUNCPrefix / sizeof(char);

      // ... --> catalogerTimerPathPrefixed = …;
      for (char const *string = catalog.timerPath, *substring = catalogTimerPathUNCPrefix; ; ++string, ++substring) {
        switch (*string) {
          case ' ': case '\f': case '\n': case '\r': case '\t': case '\v':
            ++string;
            continue;
        }

        if ('\0' == *substring) {
          catalogerTimerPathPrefixed = true;
          break;
        }

        if (*string != *substring)
        break;
      }

      // ... ->> Attempt to qualify `catalog.timerPath` as a NUL-terminated UNC (Universal Naming Convention) directory —
      if (not catalogerTimerPathPrefixed or catalogTimerPathSuffixed) {
        catalogTimerPathBuffer = ::new (std::nothrow) char[(catalogerTimerPathPrefixed ? 0u : catalogTimerPathUNCPrefixLength) + catalogTimerPathLength + (catalogTimerPathSuffixed ? catalogTimerFileNameFallbackBufferLength + 1u : 0u) + 1u];

        /* Don’t repeat yourself… */
        if (NULL != catalogTimerPathBuffer) {
          std::size_t catalogTimerPathBufferLength = 0u;

          // ...
          for (char const *const components[] = {catalogerTimerPathPrefixed ? "" : catalogTimerPathUNCPrefix, catalog.timerPath, catalogTimerPathSuffixed ? "\\" : "", catalogTimerPathSuffixed ? catalogTimerFileNameFallbackBuffer : ""}, *const *component = components; component != components + (sizeof components / sizeof(char const*)); ++component) {
            for (char *destination = catalogTimerPathBuffer + catalogTimerPathBufferLength, *source = const_cast<char*>(*component); ; ++destination, ++source) {
              *destination = *source == '/' ? '\\' : *source;

              if ('\0' == *source) {
                catalogTimerPathBufferLength += source - *component;
                break;
              }
            }
          }

          catalogTimerPathBuffer[catalogTimerPathBufferLength] = '\0';
          catalog.timerPath                                    = catalogTimerPathBuffer;
          catalog.timerPathAllocated                           = true;
        }

        else if (catalogTimerPathSuffixed) {
          (void) catalog.warn("Cataloger exited; no file for the catalog's internal clock specified");
          return EXIT_FAILURE;
        }
      }
    #else
      // — while ensuring `catalog.timerPath` is interpreted as a file directory
      if (catalogTimerPathSuffixed) {
        catalogTimerPathBuffer = ::new (std::nothrow) char[catalogTimerPathLength + (catalogTimerPathSuffixed ? catalogTimerFileNameFallbackBufferLength + 1u : 0u) + 1u];

        /* Don’t repeat yourself… */
        if (NULL != catalogTimerPathBuffer) {
          std::size_t catalogTimerPathBufferLength = 0u;

          // ...
          for (char const *const components[] = {catalog.timerPath, catalogTimerPathSuffixed ? "/" : "", catalogTimerPathSuffixed ? catalogTimerFileNameFallbackBuffer : ""}, *const *component = components; component != components + (sizeof components / sizeof(char const*)); ++component) {
            for (char *destination = catalogTimerPathBuffer + catalogTimerPathBufferLength, *source = const_cast<char*>(*component); ; ++destination, ++source) {
              *destination = *source;

              if ('\0' == *source) {
                catalogTimerPathBufferLength += source - *component;
                break;
              }
            }
          }

          catalogTimerPathBuffer[catalogTimerPathBufferLength] = '\0';
          catalog.timerPath                                    = catalogTimerPathBuffer;
          catalog.timerPathAllocated                           = true;
        }

        else {
          (void) catalog.warn("Cataloger exited; no file for the catalog's internal clock specified");
          return EXIT_FAILURE;
        }
      }
    #endif

    catalog.timerFileStream = std::fopen(catalog.timerPath, "wb+");
  }

  // CHECK IF TIMER FILE STREAM CREARED
  // GET CURRENT DATE/ TIME
  // CHECK IF TIME ELAPSED OR IF RUN FIRST TIME
  // SPAWN LOG not as child process; format: 2023–07–07.log
  // look for non-busy waits
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
