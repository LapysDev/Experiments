// --> cataloger C:\Users\oluwa\OneDrive\Lapys\Catalog C:\Users\oluwa\OneDrive\Lapys\Catalog\schedule.dat
#include <ciso646> // --> and, not, or
#include <climits> // --> CHAR_BIT
#include <cstddef> // --> std::size_t
#include <cstdio>  // --> EOF, L_tmpnam, stderr, stdout; std::FILE; std::fclose(...), std::feof(...), std::ferror(...), std::fflush(...), std::fopen(...), std::fprintf(...), std::fputs(...), std::fread(...), std::fwrite(...), std::remove(...), std::rewind(...), std::tmpnam(...)
#include <cstdlib> // --> EXIT_FAILURE, EXIT_SUCCESS; std::system(...)
#include <ctime>   // --> std::time_t, std::tm; std::difftime(...), std::mktime(...), std::time(...)
#include <new>     // --> new; std:nothrow
#if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
# define _CRT_SECURE_NO_WARNINGS
# include <windows.h> // --> ::RegCloseKey(...), ::RegOpenKeyExW(...), ::RegQueryValueExW(...), ::VerifyVersionInfoW(...), ::VerSetConditionMask(...)
#   include <winternl.h> // --> ::NtCurrentTeb()
#elif defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
# include <limits.h>
# include <stdlib.h>
#endif

// /* Main --> cataloger [folder_for_cataloging] [file_for_timekeeping] */
// int main(int count, char* arguments[]) /* noexcept */ {
//   struct cataloger {
//     // ... ->> A more consistent `std::tm` binary format
//     struct timestamp {
//       bool           daylightSavings : 1u;  // --> std::tm::tm_isdst {0, INT_MIN}
//       unsigned char  day             : 5u;  // --> std::tm::tm_mday  {1, 31}
//       unsigned char  hour            : 5u;  // --> std::tm::tm_hour  {0, 23}
//       unsigned char  minute          : 6u;  // --> std::tm::tm_min   {0, 59}
//       unsigned char  month           : 4u;  // --> std::tm::tm_mon   {0, 11}
//       unsigned char  second          : 6u;  // --> std::tm::tm_sec   {0, 60..61}
//       unsigned char  weekDay         : 3u;  // --> std::tm::tm_wday  {0, 6}
//       unsigned short year            : 14u; // --> std::tm::tm_year  {1900 + ..}
//       unsigned short yearDay         : 9u;  // --> std::tm::tm_yday  {0, 365}
//     };
//   };

//   /* ... */
//   union {
//     char *catalogDirectoryPath; // ->> Directory where catalog files will be saved
//     char *catalogPath;          // ->> Path to current catalog file
//   };

//   std::time_t   currentTime                                                                          = static_cast<std::time_t>(-1); //
//   double const  catalogRecordTimeRange                                                               = 86400.00;                     // ->> Observed seconds elapsed between `catalogRecordTime` and `currentTime`; Currently set to approximately one single day
//   double        catalogRecordTimeSpan                                                                = 0.0;                          // --> std::difftime(catalogRecordTime, currentTime)
//   std::time_t   catalogRecordTime                                                                    = static_cast<std::time_t>(-1); // ->> Deserialized seconds representation of `cataloger::timestamp` from `catalogRecordFile`
//   char          catalogRecordPathBuffer[L_tmpnam + 5u /* --> ".json" */]                             = {'\0'};                       //
//   char         *catalogRecordPath                                                                    = NULL;                         //
//   std::FILE    *catalogRecordFile                                                                    = NULL;                         // ->> File which records a possibly existing `cataloger::timestamp` used to create new catalog files
//   unsigned char catalogRecordDateBuffer[sizeof(cataloger::timestamp)]                                = {0};                          // ->> Ideally zero-initialized
//   bool          catalogRecordDateDeserialized                                                        = false;                        //
//   std::tm       catalogRecordDate                                                                    = {};                           // ->> Deserialized `std::tm` representation of `cataloger::timestamp` from `catalogRecordFile`
//   char          catalogPathBuffer[2u /* --> "./" */ + 14u /* --> catalogPath */ + 1u /* --> '\0' */] = "./";                         //

//   // ... ->> Acquire `catalogDirectoryPath` and `catalogRecordPath` paths
//   catalogDirectoryPath = count > 1 and NULL != arguments[1] ? arguments[1] : catalogPathBuffer /* --> "./" */;
//   catalogRecordPath    = count > 2 and NULL != arguments[2] ? arguments[2] : std::tmpnam(catalogRecordPathBuffer);

//   if (NULL == catalogRecordPath) {
//     if (EOF != std::fputs("catalog: " "Unable to determine file path for catalog record", stderr))
//     (void) std::fflush(stderr);

//     return EXIT_FAILURE;
//   }

//   std::printf("[directory]: \"%s\"" "\r\n", catalogDirectoryPath);
//   std::printf("[record]   : \"%s\"" "\r\n", catalogRecordPath);

//   if (catalogRecordPathBuffer /* --> std::tmpnam(...) */ == catalogRecordPath) {
//     // ... ->> Remove all `catalogRecordPath` directory components except the temporary unique file name
//     for (char *iterator = catalogRecordPath; ; ++iterator)
//     if ('\0' == *iterator) {
//       while (catalogRecordPath != iterator--)
//       if (
//         *iterator == '/'
//         #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
//           or *iterator == '\\'
//         #endif
//       ) {
//         for (char *subiterator = catalogRecordPath; '\0' != *iterator; ++subiterator)
//         *subiterator = *++iterator;

//         break;
//       }

//       break;
//     }

//     // ... ->> Append `".json"` extension substring to `catalogRecordPath` e.g. `"name"` and `"name.jso"` will be extended to `"name.json"`
//     for (char *iterator = catalogRecordPath; ; ++iterator)
//     if ('\0' == *iterator or iterator - catalogRecordPath == sizeof catalogRecordPathBuffer / sizeof(char)) {
//       char const *catalogRecordFileExtension = ".json";

//       // ...
//       iterator = iterator - catalogRecordPath > 5 /* --> ".json" */ ? iterator - 5 /* --> ".json" */ : catalogRecordPath;

//       for (; '\0' != iterator[0]; ++iterator)
//       if (
//         catalogRecordFileExtension[0] == iterator[0] and
//         ('\0' == iterator[1] or (catalogRecordFileExtension[1] == iterator[1] and
//         ('\0' == iterator[2] or (catalogRecordFileExtension[2] == iterator[2] and
//         ('\0' == iterator[3] or (catalogRecordFileExtension[3] == iterator[3] and
//         ('\0' == iterator[4] or (catalogRecordFileExtension[4] == iterator[4])
//       )))))))) break;

//       for (; ; ++catalogRecordFileExtension, ++iterator) {
//         *iterator = *catalogRecordFileExtension;
//         if ('\0' == *catalogRecordFileExtension) break;
//       }

//       break;
//     }

//     std::printf("[directory]: \"%s\"" "\r\n", catalogDirectoryPath);
//     std::printf("[record]   : \"%s\"" "\r\n", catalogRecordPath);

//     // ... ->> Prepend `catalogDirectoryPath` to `catalogRecordPath`
//     for (char *iterator = catalogRecordPath; ; ++iterator)
//     if ('\0' == *iterator) {
//       std::size_t const catalogRecordPathMaximumLength = sizeof catalogRecordPathBuffer / sizeof(char);

//       // ...
//       for (char *subiterator = catalogDirectoryPath; ; ++subiterator)
//       if ('\0' == *subiterator) {
//         std::size_t const catalogRecordPathLength    = iterator    - catalogRecordPath;
//         std::size_t       catalogDirectoryPathLength = subiterator - catalogDirectoryPath;
//         bool              catalogDirectoryDelimited  = false;

//         // ...
//         while (not catalogDirectoryDelimited and catalogDirectoryPath != subiterator)
//         switch (*--subiterator) {
//           #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
//             case '\\':
//           #endif
//           case '/': catalogDirectoryDelimited = true; break;
//           case 0x09: case 0x0A: case 0x0B: case 0x0C: case 0x0D: continue; // --> 0x1680 || 0x180E || 0x2000 || 0x2001 || 0x2002 || 0x2003 || 0x2004 || 0x2005 || 0x2006 || 0x2007 || 0x2008 || 0x2009 || 0x200A || 0x200B || 0x202F || 0x205F || 0x3000 || 0xFEFF
//           default: subiterator = catalogDirectoryPath;
//         }

//         subiterator = catalogDirectoryPath + catalogDirectoryPathLength;

//         // ...
//         if (catalogDirectoryPathLength /*+ not catalogDirectoryDelimited*/ < catalogRecordPathMaximumLength - catalogRecordPathLength) {
//           for (++iterator; catalogRecordPath != iterator--; )
//           iterator[catalogDirectoryPathLength /*+ not catalogDirectoryDelimited*/] = *iterator;

//           // if (not catalogDirectoryDelimited)
//           //   iterator[catalogDirectoryPathLength] = '/';

//           for (iterator = catalogRecordPath + catalogDirectoryPathLength; catalogDirectoryPath != subiterator; --subiterator)
//           *--iterator = *--subiterator;
//         }

//         else {
//           #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
//             OSVERSIONINFOEXW operatingSystemVersionInformation = {
//               sizeof(OSVERSIONINFOEXW), // --> DWORD ::dwOSVersionInfoSize;
//               10u,                      // --> DWORD ::dwMajorVersion;
//               0u,                       // --> DWORD ::dwMinorVersion;
//               14393u,                   // --> DWORD ::dwBuildNumber; ->> Windows 10 1607 "Redstone 1" --- CITE (Lapys) -> https://learn.microsoft.com/en-us/windows/release-health/release-information
//               VER_PLATFORM_WIN32_NT,    // --> DWORD ::dwPlatformId;
//               L"",                      // --> WCHAR ::szCSDVersion[128];
//               0u,                       // --> WORD  ::wServicePackMajor;
//               0u,                       // --> WORD  ::wServicePackMinor;
//               0x00u,                    // --> WORD  ::wSuiteMask;
//               VER_NT_WORKSTATION,       // --> BYTE  ::wProductType;
//               0x0u                      // --> BYTE  ::wReserved;
//             };

//             std::size_t const pathMaximumLength         = MAX_PATH;
//             std::size_t const pathMaximumExtendedLength = (
//               // ->> Approximate --- CITE (Lapys) -> https://learn.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation
//               FALSE != ::VerifyVersionInfoW(&operatingSystemVersionInformation, VER_PRODUCT_TYPE,                                                                                    ::VerSetConditionMask(0x00uL, VER_PRODUCT_TYPE, VER_EQUAL)) and
//               FALSE != ::VerifyVersionInfoW(&operatingSystemVersionInformation, VER_BUILDNUMBER | VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR, ::VerSetConditionMask(::VerSetConditionMask(::VerSetConditionMask(::VerSetConditionMask(::VerSetConditionMask(0x00uL, VER_SERVICEPACKMINOR, VER_GREATER_EQUAL), VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL), VER_MINORVERSION, VER_GREATER_EQUAL), VER_MAJORVERSION, VER_GREATER_EQUAL), VER_BUILDNUMBER, VER_GREATER_EQUAL))
//             ) ? 32767u : 0u;
//           #elif defined __APPLE__ or defined __bsdi__ or defined __CYGWIN__ or defined __DragonFly__ or defined __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ or defined __FreeBSD__ or defined __FreeBSD_version or defined __gnu_linux__ or defined __linux or defined __linux__ or defined __MACH__ or defined __NETBSD__ or defined __NETBSD_version or defined __OpenBSD__ or defined __OS400__ or defined __QNX__ or defined __QNXNTO__ or defined __sun or defined __SVR4 or defined __svr4__ or defined __sysv__ or defined __unix or defined __unix__ or defined __VMS or defined __VMS_VER or defined _NTO_VERSION or defined _POSIX_SOURCE or defined _SYSTYPE_SVR4 or defined _XOPEN_SOURCE or defined linux or defined NetBSD0_8 or defined NetBSD0_9 or defined NetBSD1_0 or defined OpenBSD2_0 or defined OpenBSD2_1 or defined OpenBSD2_2 or defined OpenBSD2_3 or defined OpenBSD2_4 or defined OpenBSD2_5 or defined OpenBSD2_6 or defined OpenBSD2_7 or defined OpenBSD2_8 or defined OpenBSD2_9 or defined OpenBSD3_0 or defined OpenBSD3_1 or defined OpenBSD3_2 or defined OpenBSD3_3 or defined OpenBSD3_4 or defined OpenBSD3_5 or defined OpenBSD3_6 or defined OpenBSD3_7 or defined OpenBSD3_8 or defined OpenBSD3_9 or defined OpenBSD4_0 or defined OpenBSD4_1 or defined OpenBSD4_2 or defined OpenBSD4_3 or defined OpenBSD4_4 or defined OpenBSD4_5 or defined OpenBSD4_6 or defined OpenBSD4_7 or defined OpenBSD4_8 or defined OpenBSD4_9 or defined sun or defined unix or defined VMS
//             std::size_t const pathMaximumLength = PATH_MAX;
//           #endif
//           bool  catalogRecordPathExtended = false;
//           char *catalogRecordPathBuffer   = catalogRecordPath;

//           // ...
//           if (catalogRecordPathLength < pathMaximumLength and catalogDirectoryPathLength < pathMaximumLength - catalogRecordPathLength) {
//             static char buffer[pathMaximumLength];
//             catalogRecordPathBuffer = buffer;
//           }

//           #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
//             else if (catalogRecordPathLength < pathMaximumExtendedLength and catalogDirectoryPathLength < pathMaximumExtendedLength - catalogRecordPathLength) {
//               HKEY registryKeyHandle;
//               BYTE registryKeyValue[4] = {0x00u, 0x00u, 0x00u, 0x00u};

//               // ...
//               operatingSystemVersionInformation.dwBuildNumber       = 16299u; // ->> Windows 10 1709 "Redstone 3" --- CITE (Lapys) -> https://learn.microsoft.com/en-us/windows/release-health/release-information
//               operatingSystemVersionInformation.dwMajorVersion      = 10u;
//               operatingSystemVersionInformation.dwMinorVersion      = 0u;
//               operatingSystemVersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
//               operatingSystemVersionInformation.wProductType        = VER_NT_WORKSTATION;
//               operatingSystemVersionInformation.wServicePackMajor   = 0u;
//               operatingSystemVersionInformation.wServicePackMinor   = 0u;

//               if (ERROR_SUCCESS == ::RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\FileSystem\\", 0x00u, KEY_READ, &registryKeyHandle)) {
//                 DWORD registryKeySize;
//                 DWORD registryKeyType = REG_DWORD; // ->> Equivalent to `REG_DWORD_LITTLE_ENDIAN`

//                 // ...
//                 if (ERROR_SUCCESS == ::RegQueryValueExW(registryKeyHandle, L"LongPathsEnabled", static_cast<LPDWORD>(NULL), &registryKeyType, static_cast<LPBYTE>(NULL), &registryKeySize))
//                 if (registryKeySize <= 4u) {
//                   if (ERROR_SUCCESS != ::RegQueryValueExW(registryKeyHandle, L"LongPathsEnabled", static_cast<LPDWORD>(NULL), &registryKeyType, registryKeyValue, &registryKeySize)) {
//                     registryKeyValue[0] = 0x00u;
//                     registryKeyValue[1] = 0x00u;
//                     registryKeyValue[2] = 0x00u;
//                     registryKeyValue[3] = 0x00u;
//                   }
//                 }

//                 (void) ::RegCloseKey(registryKeyHandle);
//               }

//               if (
//                 FALSE != ::VerifyVersionInfoW(&operatingSystemVersionInformation, VER_PRODUCT_TYPE,                                                                                    ::VerSetConditionMask(0x00uL, VER_PRODUCT_TYPE, VER_EQUAL)) and
//                 FALSE != ::VerifyVersionInfoW(&operatingSystemVersionInformation, VER_BUILDNUMBER | VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR, ::VerSetConditionMask(::VerSetConditionMask(::VerSetConditionMask(::VerSetConditionMask(::VerSetConditionMask(0x00uL, VER_SERVICEPACKMINOR, VER_GREATER_EQUAL), VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL), VER_MINORVERSION, VER_GREATER_EQUAL), VER_MAJORVERSION, VER_GREATER_EQUAL), VER_BUILDNUMBER, VER_GREATER_EQUAL))
//                 ? (reinterpret_cast<unsigned char*>(::NtCurrentTeb() -> ProcessEnvironmentBlock)[3] & 0x80u) // --> ::NtCurrentTeb() -> ProcessEnvironmentBlock -> IsLongPathAwareProcess
//                 : *registryKeyValue == 1u
//               ) {
//                 static char buffer[32767u /* --> pathMaximumExtendedLength */]; // -> approximate size; malloc proxy

//                 catalogRecordPathBuffer   = buffer;
//                 catalogRecordPathExtended = true;
//               }
//             }
//           #endif

//           (void) catalogRecordPathExtended;
//           (void) catalogRecordPathBuffer;
//           std::puts(catalogRecordPathExtended ? "B1" : "B2");

//           // prepend \\?\ to concatenated result
//           // must be fully-qualified
//           // std::puts(NULL != std::fopen("\\\\?\\C:Users\\oluwa\\Backups & Transfers\\bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb.txt", "rb+") ? "true" : "false");
//         }

//         break;
//       }

//       break;
//     }
//   }

//   // ... ->> Normalize `catalogDirectoryPath` and `catalogRecordPath`
//   #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
//     // ... ->> Canonicalize slashes to Windows backslash separators
//     for (char *const paths[] = {catalogDirectoryPath, catalogRecordPath}, *const *iterator = paths + (sizeof paths / sizeof(char*)); iterator-- != paths; ) {
//       for (char *subiterator = *iterator; '\0' != *subiterator; ++subiterator)
//       *subiterator = *subiterator == '/' ? '\\' : *subiterator;
//     }
//   #endif

//   // ... ->> Access/ create `catalogRecordFile` from `catalogRecordPath`
//   std::printf("[directory]: \"%s\"" "\r\n", catalogDirectoryPath);
//   std::printf("[record]   : \"%s\"" "\r\n", catalogRecordPath);

//   static_cast<void>(arguments);
//   static_cast<void>(catalogDirectoryPath);
//   static_cast<void>(catalogPath);
//   static_cast<void>(catalogPathBuffer);
//   static_cast<void>(catalogRecordDate);
//   static_cast<void>(catalogRecordDateBuffer);
//   static_cast<void>(catalogRecordDateDeserialized);
//   static_cast<void>(catalogRecordFile);
//   static_cast<void>(catalogRecordPath);
//   static_cast<void>(catalogRecordPathBuffer);
//   static_cast<void>(catalogRecordTime);
//   static_cast<void>(catalogRecordTimeRange);
//   static_cast<void>(catalogRecordTimeSpan);
//   static_cast<void>(count);
//   static_cast<void>(currentTime);
// }

int main(int count, char* arguments[]) /* noexcept */ {
  struct cataloger {
    static bool removeTemporaryFileByPath(std::FILE *const file, char const path[], bool const quiet = true) {
      bool const closed = NULL == file or 0x00 == std::fclose(file);

      // ...
      if (closed and 0x00 != std::remove(path)) {
        if (not quiet) {
          if (std::fprintf(stderr, "%1.62s%s%c", "catalog:" " " "Unable to remove temporarily-generated catalog file \"", path, '"') > -1)
          (void) std::fflush(stderr);
        }

        return false;
      }

      return true;
    }
  };

  /* ... */
  std::size_t const  timeSize                          = ...;
  char              *userCatalogPath                   = NULL;                                                                        //
  std::size_t        userCatalogDirectoryLength        = 0u;                                                                          //
  bool               userCatalogDirectoryExtended      = false;                                                                       // ->> `userCatalogDirectory` has been automatically delimited
  char              *userCatalogDirectory              = NULL;                                                                        //
  std::time_t        currentTime                       = static_cast<std::time_t>(-1);                                                //
  double             catalogTimeSpan                   = 0.0;                                                                         // --> std::difftime(currentTime, catalogRecentTime)
  double /* const */ catalogTimeRange                  = 86400.00;                                                                    // ->> Observed time (in seconds) passed between `catalogTimes`; currently set to one single day
  std::time_t        catalogRecentTime                 = static_cast<std::time_t>(-1);                                                // --> std::mktime(&catalogRecentDate)
  bool               catalogRecentDateDeserialized     = false;                                                                       //
  unsigned char      catalogRecentDateBuffer[timeSize] = {0};                                                                         // ->> Ideally zero-initialized
  std::tm            catalogRecentDate                 = {};                                                                          // ->> Datetime stored in `catalogFile`
  bool const         catalogPathSpecified              = count > 1;                                                                   //
  char const *const  catalogPath                       = catalogPathSpecified ? arguments[1] : std::tmpnam(static_cast<char*>(NULL)); //
  std::FILE         *catalogFile                       = NULL;                                                                        //

  // ... ->> Track the specified directory which to create user catalogs
  for (char delimiter = '\0', *iterator = userCatalogDirectory; ; ++iterator) {
    if ('\0' == *iterator) {
      bool delimited = false;

      // ...
      delimiter                  = '\0' == delimiter ? '/' : delimiter;
      userCatalogDirectoryLength = iterator - userCatalogDirectory;

      for (char *subiterator = iterator; subiterator != userCatalogDirectory; )
      switch (*--subiterator) {
        case ' ': case '\f': case '\n': case '\r': case '\t': case '\v': break;
        case '\\': case '/': delimited = true; subiterator = userCatalogDirectory; break;
        default: subiterator = userCatalogDirectory; break;
      }

      if (false == delimited) {
        char *path = ::new (std::nothrow) char[userCatalogDirectoryLength /* --> userCatalogDirectory */ + 1u /* --> delimiter */ + 14u /* --> userCatalogPath */ + 1u /* --> '\0' */];

        // ...
        if (NULL == path) {
          if (std::fprintf(stderr, "%1.39s%s%1.26s", "catalog:" " " "Unable to allocate directory \"", userCatalogDirectory, "\" for recording catalogs" "\r\n") > -1)
            (void) std::fflush(stderr);

          // ...
          return EXIT_FAILURE;
        }

        path   += iterator - userCatalogDirectory;
        path[0] = delimiter;
        path[1] = '\0';

        while (iterator != userCatalogDirectory)
          *--path = *--iterator;

        userCatalogDirectory         = path;
        userCatalogDirectoryExtended = true;
        userCatalogDirectoryLength  += 1u;
        userCatalogPath              = userCatalogDirectory;
      }

      // ...
      break;
    }

    else switch (*iterator) {
      case '\\': case '/':
        // ... ->> Assume the contents of `arguments[2]` are safely mutable
        '\0' == delimiter ? (delimiter = *iterator) : (*iterator = delimiter);
        break;
    }
  }

  // ... ->> Prepare `userCatalogPath` for creating new user catalogs
  if (NULL == userCatalogPath) {
    userCatalogPath = ::new (std::nothrow) char[userCatalogDirectoryLength + 14u + 1u];

    if (NULL == userCatalogPath) {
      if (std::fprintf(stderr, "%1.39s%s%1.26s", "catalog:" " " "Unable to allocate directory \"", userCatalogDirectory, "\" for recording catalogs" "\r\n") > -1)
        (void) std::fflush(stderr);

      // ...
      return EXIT_FAILURE;
    }

    for (std::size_t index = userCatalogDirectoryLength; index; ) {
      --index;
      userCatalogPath[index] = userCatalogDirectory[index];
    }
  }

  // ... ->> Open catalog file (create one if the file path is not provided)
  if (NULL != catalogPath) {
    if (catalogPathSpecified)
      catalogFile = std::fopen(catalogPath, "rb+");

    else {
      catalogFile = std::fopen(catalogPath, "wb+");
      catalogFile = NULL == catalogFile or EOF == std::fclose(catalogFile) ? NULL : std::fopen(catalogPath, "rb+");
    }
  }

  if (NULL == catalogFile) {
    if (NULL == catalogPath) {
      if (EOF != std::fputs("catalog:" " " "No catalog file provided" "\r\n", stderr))
      (void) std::fflush(stderr);
    }

    else {
      if (std::fprintf(stderr, "%1.49s%s%1.3s", "catalog:" " " "Unable to access expected catalog file \"", catalogPath, "\"" "\r\n") > -1)
      (void) std::fflush(stderr);
    }

    // ...
    if (userCatalogDirectory != userCatalogPath) ::delete[] userCatalogPath;
    if (userCatalogDirectoryExtended)            ::delete[] userCatalogDirectory;

    // ...
    return EXIT_FAILURE;
  }

  // ... ->> Read `catalogDates` from `catalogFile`
  if (timeSize / sizeof(unsigned char) == std::fread(catalogRecentDateBuffer, sizeof(unsigned char), timeSize / sizeof(unsigned char), catalogFile))
    catalogRecentDateDeserialized = true;

  else if (0x00 == std::feof(catalogFile) and 0x00 != std::ferror(catalogFile)) {
    if (std::fprintf(stderr, "%1.48s%s%1.3s", "catalog:" " " "Unable to parse expected catalog file \"", catalogPath, "\"" "\r\n") > -1)
      (void) std::fflush(stderr);

    if (not catalogPathSpecified) (void) cataloger::removeTemporaryFileByPath(catalogFile, catalogPath);
    if (userCatalogDirectory != userCatalogPath) ::delete[] userCatalogPath;
    if (userCatalogDirectoryExtended)            ::delete[] userCatalogDirectory;

    // ...
    return EXIT_FAILURE;
  }

  catalogRecentDate.tm_hour  = (catalogRecentDateBuffer[0]);
  catalogRecentDate.tm_isdst = (catalogRecentDateBuffer[1]);
  catalogRecentDate.tm_mday  = (catalogRecentDateBuffer[2]);
  catalogRecentDate.tm_min   = (catalogRecentDateBuffer[3]);
  catalogRecentDate.tm_mon   = (catalogRecentDateBuffer[4]);
  catalogRecentDate.tm_sec   = (catalogRecentDateBuffer[5]);
  catalogRecentDate.tm_wday  = (catalogRecentDateBuffer[6]);
  catalogRecentDate.tm_yday  = (catalogRecentDateBuffer[7] << (CHAR_BIT * 0u)) | (catalogRecentDateBuffer[8]  << (CHAR_BIT * 1u));
  catalogRecentDate.tm_year  = (catalogRecentDateBuffer[9] << (CHAR_BIT * 0u)) | (catalogRecentDateBuffer[10] << (CHAR_BIT * 1u)) | (catalogRecentDateBuffer[11] << (CHAR_BIT * 2u)) | (catalogRecentDateBuffer[12] << (CHAR_BIT * 3u));

  // ... ->> Re-open catalog file
  if (EOF == std::fclose(catalogFile)) {
    if (std::fprintf(stderr, "%1.50s%s%1.3s", "catalog:" " " "Unable to process expected catalog file \"", catalogPath, "\"" "\r\n") > -1)
      (void) std::fflush(stderr);

    if (not catalogPathSpecified) (void) cataloger::removeTemporaryFileByPath(NULL, catalogPath);
    if (userCatalogDirectory != userCatalogPath) ::delete[] userCatalogPath;
    if (userCatalogDirectoryExtended)            ::delete[] userCatalogDirectory;

    // ...
    return EXIT_FAILURE;
  }

  catalogFile = std::fopen(catalogPath, "wb+");

  if (NULL == catalogFile) {
    if (std::fprintf(stderr, "%1.40s%s%1.3s", "catalog:" " " "Unable to access catalog file \"", catalogPath, "\"" "\r\n") > -1)
      (void) std::fflush(stderr);

    if (not catalogPathSpecified) (void) cataloger::removeTemporaryFileByPath(NULL, catalogPath);
    if (userCatalogDirectory != userCatalogPath) ::delete[] userCatalogPath;
    if (userCatalogDirectoryExtended)            ::delete[] userCatalogDirectory;

    // ...
    return EXIT_FAILURE;
  }

  // ... ->> Synchronously check if sufficient time has passed between `catalogRecentTime` and `currentTime`
  //           then update `catalogFile` and `catalogRecentTime` to reflect/ continue future checks
  currentTime       = std::time(static_cast<std::time_t*>(NULL));
  catalogRecentTime = catalogRecentDateDeserialized ? std::mktime(&catalogRecentDate) : currentTime;

  if (std::fprintf(stdout, "%1.31s%s%1.3s", "catalog:" " " "Beginning catalog in \"", userCatalogDirectory, "\"" "\r\n") > -1)
    (void) std::fflush(stdout);

  #if defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
  #endif

  for (; ; ) {
    // ... ->> Check the time between `catalogReccentTime` and `currentTime`
    currentTime = std::time(static_cast<std::time_t*>(NULL)); // ->> Redundant call for one single iteration

    if (catalogRecentTime == static_cast<std::time_t>(-1) or currentTime == static_cast<std::time_t>(-1)) {
      if (EOF != std::fputs("catalog:" " " "Unable to observe catalog datetime" "\r\n", stderr))
        (void) std::fflush(stderr);

      if (not catalogPathSpecified) (void) cataloger::removeTemporaryFileByPath(catalogFile, catalogPath);
      if (userCatalogDirectory != userCatalogPath) ::delete[] userCatalogPath;
      if (userCatalogDirectoryExtended)            ::delete[] userCatalogDirectory;

      // ...
      return EXIT_FAILURE;
    }

    catalogTimeSpan = std::difftime(currentTime, catalogRecentTime);

    // ... ->> Update `catalogFile` and `catalogRecentTime`
    if (catalogTimeSpan >= +catalogTimeRange or catalogTimeSpan <= -catalogTimeRange) {
      std::tm const *const currentDate     = std::gmtime(&currentTime);
      std::FILE           *userCatalogFile = NULL;

      // ...
      if (NULL == currentDate) {
        if (EOF != std::fputs("catalog:" " " "Unable to update catalog datetime" "\r\n", stderr))
          (void) std::fflush(stderr);

        if (not catalogPathSpecified) (void) cataloger::removeTemporaryFileByPath(catalogFile, catalogPath);
        if (userCatalogDirectory != userCatalogPath) ::delete[] userCatalogPath;
        if (userCatalogDirectoryExtended)            ::delete[] userCatalogDirectory;

        // ...
        return EXIT_FAILURE;
      }

      catalogRecentDate           = *currentDate;
      catalogRecentDateBuffer[0]  = static_cast<unsigned char>(catalogRecentDate.tm_hour);
      catalogRecentDateBuffer[1]  = static_cast<unsigned char>(catalogRecentDate.tm_isdst ? true : false);
      catalogRecentDateBuffer[2]  = static_cast<unsigned char>(catalogRecentDate.tm_mday);
      catalogRecentDateBuffer[3]  = static_cast<unsigned char>(catalogRecentDate.tm_min);
      catalogRecentDateBuffer[4]  = static_cast<unsigned char>(catalogRecentDate.tm_mon);
      catalogRecentDateBuffer[5]  = static_cast<unsigned char>(catalogRecentDate.tm_sec);
      catalogRecentDateBuffer[6]  = static_cast<unsigned char>(catalogRecentDate.tm_wday);
      catalogRecentDateBuffer[7]  = (catalogRecentDate.tm_yday >> (CHAR_BIT * 0u)) & ((((1u << (CHAR_BIT - 1u)) - 1u) << 1u) + 1u);
      catalogRecentDateBuffer[8]  = (catalogRecentDate.tm_yday >> (CHAR_BIT * 1u)) & ((((1u << (CHAR_BIT - 1u)) - 1u) << 1u) + 1u);
      catalogRecentDateBuffer[9]  = (catalogRecentDate.tm_year >> (CHAR_BIT * 0u)) & ((((1u << (CHAR_BIT - 1u)) - 1u) << 1u) + 1u);
      catalogRecentDateBuffer[10] = (catalogRecentDate.tm_year >> (CHAR_BIT * 1u)) & ((((1u << (CHAR_BIT - 1u)) - 1u) << 1u) + 1u);
      catalogRecentDateBuffer[11] = (catalogRecentDate.tm_year >> (CHAR_BIT * 2u)) & ((((1u << (CHAR_BIT - 1u)) - 1u) << 1u) + 1u);
      catalogRecentDateBuffer[12] = (catalogRecentDate.tm_year >> (CHAR_BIT * 3u)) & ((((1u << (CHAR_BIT - 1u)) - 1u) << 1u) + 1u);
      catalogRecentTime           = currentTime;

      std::rewind(catalogFile);

      if (timeSize / sizeof(unsigned char) != std::fwrite(catalogRecentDateBuffer, sizeof(unsigned char), timeSize / sizeof(unsigned char), catalogFile)) {
        if (std::fprintf(stderr, "%1.49s%s%1.3s", "catalog:" " " "Unable to update expected catalog file \"", catalogPath, "\"" "\r\n") > -1)
          (void) std::fflush(stderr);

        if (not catalogPathSpecified) (void) cataloger::removeTemporaryFileByPath(catalogFile, catalogPath);
        if (userCatalogDirectory != userCatalogPath) ::delete[] userCatalogPath;
        if (userCatalogDirectoryExtended)            ::delete[] userCatalogDirectory;

        // ...
        return EXIT_FAILURE;
      }

      // ... ->> Create a new user catalog, and open it within a new Windows Notepad instance
      userCatalogPath[userCatalogDirectoryLength + 0u]  = "0123456789"[((catalogRecentDate.tm_mon + 1) / 10) % 10];
      userCatalogPath[userCatalogDirectoryLength + 1u]  = "0123456789"[((catalogRecentDate.tm_mon + 1) / 1)  % 10];
      userCatalogPath[userCatalogDirectoryLength + 2u]  = '-';
      userCatalogPath[userCatalogDirectoryLength + 3u]  = "0123456789"[(catalogRecentDate.tm_mday / 10) % 10];
      userCatalogPath[userCatalogDirectoryLength + 4u]  = "0123456789"[(catalogRecentDate.tm_mday / 1)  % 10];
      userCatalogPath[userCatalogDirectoryLength + 5u]  = '-';
      userCatalogPath[userCatalogDirectoryLength + 6u]  = "0123456789"[((catalogRecentDate.tm_year + 1900) / 1000) % 10];
      userCatalogPath[userCatalogDirectoryLength + 7u]  = "0123456789"[((catalogRecentDate.tm_year + 1900) / 100)  % 10];
      userCatalogPath[userCatalogDirectoryLength + 8u]  = "0123456789"[((catalogRecentDate.tm_year + 1900) / 10)   % 10];
      userCatalogPath[userCatalogDirectoryLength + 9u]  = "0123456789"[((catalogRecentDate.tm_year + 1900) / 1)    % 10];
      userCatalogPath[userCatalogDirectoryLength + 10u] = '.';
      userCatalogPath[userCatalogDirectoryLength + 11u] = 'l';
      userCatalogPath[userCatalogDirectoryLength + 12u] = 'o';
      userCatalogPath[userCatalogDirectoryLength + 13u] = 'g';
      userCatalogPath[userCatalogDirectoryLength + 14u] = '\0';
      userCatalogFile                                   = std::fopen(userCatalogPath, "ab+");

      if (NULL == userCatalogFile) {
        if (std::fprintf(stderr, "%1.32s%s%1.18s", "catalog:" " " "Unable to create file \"", userCatalogPath, "\" for cataloging" "\r\n") > -1)
        (void) std::fflush(stderr);
      }

      else {
        if (std::fprintf(stdout, "%1.23s%s%1.16s", "catalog:" " " "Created file \"", userCatalogPath, "\" for catalog" "\r\n") > -1)
          (void) std::fflush(stdout);

        // ...
        if (0x00 == std::fclose(userCatalogFile) and 0x00 != std::system(static_cast<char const*>(NULL))) {
          static char *command = NULL; // ->> Memory leak (got exhausted with development at this point)

          // ...
          if (NULL == command) {
            command = ::new (std::nothrow) char[userCatalogDirectoryLength + 14u + 23u + 1u];

            if (NULL != command) {
              command[0]  = '%';
              command[1]  = 'w';
              command[2]  = 'i';
              command[3]  = 'n';
              command[4]  = 'd';
              command[5]  = 'i';
              command[6]  = 'r';
              command[7]  = '%';
              command[8]  = '/';
              command[9]  = 'n';
              command[10] = 'o';
              command[11] = 't';
              command[12] = 'e';
              command[13] = 'p';
              command[14] = 'a';
              command[15] = 'd';
              command[16] = '.';
              command[17] = 'e';
              command[18] = 'x';
              command[19] = 'e';
              command[20] = ' ';
              command[21] = '"';

              command[userCatalogDirectoryLength + 14u + 22u + 0u] = '"';
              command[userCatalogDirectoryLength + 14u + 22u + 1u] = '\0';
            }
          }

          if (NULL != command)
          for (std::size_t index = userCatalogDirectoryLength + 14u; index; ) {
            --index;
            (command + 22)[index] = userCatalogPath[index];
          }

          (void) std::system(command);
        }
      }
    }
  }

  if (userCatalogDirectoryExtended)
    ::delete[] userCatalogDirectory;

  // ...
  return EXIT_SUCCESS;
}
