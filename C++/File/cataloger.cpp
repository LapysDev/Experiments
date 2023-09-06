// --> C:\LapysDev\miscellaneous\cataloger.exe C:\Users\oluwa\OneDrive\Lapys\Catalog\schedule.dat C:\Users\oluwa\OneDrive\Lapys\Catalog
// --> cataloger C:\Users\oluwa\OneDrive\Lapys\Catalog\schedule.dat C:\Users\oluwa\OneDrive\Lapys\Catalog
#include <ciso646> // --> and, not, or
#include <climits> // --> CHAR_BIT
#include <cstddef> // --> std::size_t
#include <cstdio>  // --> EOF, stderr, stdout; std::FILE; std::fclose(...), std::feof(...), std::ferror(...), std::fflush(...), std::fopen(...), std::fprintf(...), std::fputs(...), std::fread(...), std::fwrite(...), std::remove(...), std::rewind(...), std::tmpnam(...)
#include <cstdlib> // --> EXIT_FAILURE, EXIT_SUCCESS; std::system(...)
#include <ctime>   // --> std::time_t, std::tm; std::difftime(...), std::mktime(...), std::time(...)
#include <new>     // --> new; std:nothrow
#if defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
# define _CRT_SECURE_NO_WARNINGS
# include <windows.h>
#endif

/* Main --> cataloger [file_for_timekeeping] [folder_for_cataloging] */
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
  std::size_t const timeSize = (
    1u + // --> std::tm::tm_hour
    1u + // --> std::tm::tm_isdst
    1u + // --> std::tm::tm_mday
    1u + // --> std::tm::tm_min
    1u + // --> std::tm::tm_mon
    1u + // --> std::tm::tm_sec
    1u + // --> std::tm::tm_wday
    2u + // --> std::tm::tm_yday
    4u + // --> std::tm::tm_year
    0u
  ) * sizeof(unsigned char);

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
  if (count > 2) {
    userCatalogDirectory = arguments[2];

    if (NULL == userCatalogDirectory) {
      if (EOF != std::fputs("catalog:" " " "No directory specified for recording catalogs" "\r\n", stderr))
        (void) std::fflush(stderr);

      // ...
      return EXIT_FAILURE;
    }
  }

  else {
    static char path[2u /* --> "./" */ + 14u /* --> userCatalogPath */ + 1u /* --> '\0' */] = "./";

    // ...
    userCatalogDirectory = path;
    userCatalogPath      = userCatalogDirectory;
  }

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

  #if defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
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
