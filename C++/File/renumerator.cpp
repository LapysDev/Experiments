/* OPTION TO RENAME HIDDEN FILES, TOO? */
/* Definitions */
#if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
# define UNICODE
#endif

/* Import */
#include <cctype>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <cstdlib>

#if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
# include <ctype.h>
# include <string.h>
# include <wchar.h>
# include <windows.h>
#   include <processenv.h> // --> kernel32.lib
#   include <psapi.h>      // --> kernel32.lib | psapi.lib
#   include <shellapi.h>   // --> shell32.lib
#   include <shlwapi.h>    // --> shlwapi.lib
#endif

/* Main */
int main(int, char* arguments[]) /* noexcept */ {
  struct Option {
    enum { FORMAT = 0x1, HELP, START_INDEX } flag;
    char const                              *name;
    bool                                     valued;
  };

  // ...
  char const  *applicationName  = NULL == *arguments || '\0' == **arguments ? NULL : *arguments;                      // ->> ignore renaming the executable file (likely)
  std::size_t  fileIndex        = 1u;                                                                                 // ->> numerical index to rename files
  char const  *fileNameFormat   = NULL;                                                                               // ->> format string to rename files
  char const   sourceName    [] = __FILE__;                                                                           // ->> ignore renaming the source file
  Option       programOption;                                                                                         // ->> specified options from command-line arguments
  Option const programOptions[] = {                                                                                   //
    {Option::FORMAT,      "f", true},  {Option::FORMAT,      "-format", true},                                        //
    {Option::HELP,        "h", false}, {Option::HELP,        "-help",   false},                                       //
    {Option::START_INDEX, "i", true},  {Option::START_INDEX, "-index",  true}, {Option::START_INDEX, "-start",  true} //
  };

  #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
    int              commandLineArgumentCount;                                                                                                                                                                                                                                                                                                                                     //
    wchar_t          workingPath[MAX_PATH + 4u] = {L'.', L'\\', L'*', L'\0'};                                                                                                                                                                                                                                                                                                      // ->> filesystem search location to rename expected files
    LPWSTR *const    programPath                = ::CommandLineToArgvW(L"", &commandLineArgumentCount);                                                                                                                                                                                                                                                                            //
    LPWSTR const     programNameBuffer          = static_cast<LPWSTR>(NULL == programPath ? NULL : std::calloc(32767u, sizeof(WCHAR)));                                                                                                                                                                                                                                            //
    LPWSTR const     programName                = NULL != programPath ? ::wcsrchr(*programPath, L'\\') + 1 : 0x0u != ::GetModuleFileNameW(static_cast<HMODULE>(NULL), programNameBuffer, 32767u) ? ::wcsrchr(programNameBuffer, L'\\') + 1 : 0x0u != ::GetModuleBaseName(::GetCurrentProcess(), static_cast<HMODULE>(NULL), programNameBuffer, 32767u) ? programNameBuffer : NULL; // ->> ignore renaming the executable file (more likely)
    BOOLEAN          fileSystemRedirectionEnabled;                                                                                                                                                                                                                                                                                                                                 //
    HANDLE           fileSearchHandle;                                                                                                                                                                                                                                                                                                                                             //
    wchar_t        (*fileNames)      [MAX_PATH] = NULL;                                                                                                                                                                                                                                                                                                                            // ->> (sorted) list of files to rename
    WIN32_FIND_DATAW fileInformation;                                                                                                                                                                                                                                                                                                                                              //
    LPWSTR *const    commandLineArguments       = ::CommandLineToArgvW(static_cast<LPCWSTR>(::GetCommandLineW()), &commandLineArgumentCount);                                                                                                                                                                                                                                      // ->> allow non-ASCII encoding (unlike `arguments`)
  #elif (defined(__APPLE__) && defined(__MACH__)) || (defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__unix) || defined(__unix__) || defined(linux))
    ...
  #endif

  // ... ->> Modify `applicationName` (like `sourceName` or others...) to a valid file name
  #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
    applicationName = NULL == applicationName ? NULL : ::PathFindFileNameA(applicationName);
  #elif (defined(__APPLE__) && defined(__MACH__)) || (defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__unix) || defined(__unix__) || defined(linux))
    applicationName = ...;
  #endif

  /* ... ->> Determine `fileIndex` and `workingPath` from the command-line arguments */
  #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
    std::free(programNameBuffer), ::LocalFree(programPath);
    if (NULL != commandLineArguments) {
      LPWSTR *arguments = commandLineArguments;

      // ...
      while (0 != commandLineArgumentCount--) {
        LPWSTR argument = *++arguments;
        while (0 != ::iswspace(*argument)) ++argument;

        switch (*argument) {
          case L'\0': ::LocalFree(commandLineArguments); goto empty_option;
          case L'-':
        }
      }
    }

    else
  #elif (defined(__APPLE__) && defined(__MACH__)) || (defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__unix) || defined(__unix__) || defined(linux))
    ...
  #endif

  for (char const *const *argumentsIterator = ++arguments; ; ++argumentsIterator) {
    char const *argumentIterator = *argumentsIterator;

    // ...
    if (NULL == argumentIterator) break;
    while (0 != std::isspace(static_cast<unsigned char>(*argumentIterator))) ++argumentIterator;

    // ...
    switch (*argumentIterator) {
      case '\0':
      empty_option: {
        std::fputs("Command-line argument must not be empty.", stderr);
        return EXIT_FAILURE;
      } break;

      case '-': {
        for (Option *option = options; option != options + (sizeof(options) / sizeof(*options)); ++option)
        if (argumentIterator[1] == option -> name[0]) for (char const *iteratorA = argumentIterator + 1, *iteratorB = option -> name; ; ++iteratorA, ++iteratorB) {
          if ('\0' == *iteratorB) {
            while (0 != std::isspace(static_cast<unsigned char>(*iteratorA))) ++iteratorA;
            if (*iteratorA != (option -> valued ? '=' : '\0')) goto invalid_option;

            argumentIterator      = iteratorA + 1;
            programOption = *option;

            goto valid_option;
          }

          if ('\0' == *iteratorA || *iteratorA != *iteratorB)
          break;
        }

        invalid_option: {
          std::fprintf(stderr, "%1.23s%s%1.71s", "Command-line argument `", argumentIterator, "` must be a valid program option. (use the `--help` option for details)");
          return EXIT_FAILURE;
        }

        valid_option: switch (programOption.flag) {
          case Option::FORMAT:
            fileNameFormat = argumentIterator;
            break;

          case Option::HELP: {
            if (arguments != argumentsIterator || NULL != arguments[1]) {
              std::fputs("`--help` option must be used exclusive to other program options.", stderr);
              return EXIT_FAILURE;
            }

            return std::fprintf(stdout, "%1.82s%s%1.221s",
              "Renames directory files in a numerically progressive order. (starting from 1)" "\r\n" "\r\n\t",
              NULL == applicationName ? "renum" : applicationName,
              " " "[options...]"                                                                               "\r\n" "\r\n\t"
                "options:"                                                                                     "\r\n\t\t"
                  "-f, --format"          "\t\t" "Specifies file renaming format. (`%i` for the rename count)" "\r\n\t\t"
                  "-h, --help"            "\t\t" "Log information on program usage."                           "\r\n\t\t"
                  "-i, --index, --start"  "\t"   "Specifies starting count for renaming files."                ""
            ), EXIT_SUCCESS;
          } break;

          case Option::START_INDEX: {
            while (0 != std::isspace(static_cast<unsigned char>(*argumentIterator)))
            ++argumentIterator;

            if ('\0' == *argumentIterator) {
              std::fprintf(stderr, "%1.43s%s%1.2s", "Expected a value for command-line option `-", programOption.name, "`.");
              return EXIT_FAILURE;
            }

            for (char const *fileIndexSource = argumentIterator; ; ++argumentIterator) {
              if (0 != std::isdigit(static_cast<unsigned char>(*argumentIterator))) continue;
              else if ('\0' == *argumentIterator || 0 != std::isspace(static_cast<unsigned char>(*argumentIterator))) {
                while (0 != std::isspace(static_cast<unsigned char>(*argumentIterator))) ++argumentIterator;
                if ('\0' == *argumentIterator) {
                  while (0 != std::isspace(static_cast<unsigned char>(*argumentIterator))) --argumentIterator;
                  for (fileIndex = 0u; argumentIterator != fileIndexSource; fileIndex = (fileIndex * 10u) + (*(fileIndexSource++) - '0')) { if (fileIndex > ULONG_MAX / 10uL) goto invalid_value; }

                  break;
                }
              }

              invalid_value: {
                std::fprintf(stderr, "%1.40s%s%1.41s%lu%c", "Invalid value for command-line option `-", programOption.name, "`, expected an integer count. (less than ", ULONG_MAX, ')');
                return EXIT_FAILURE;
              }
            }
          } break;
        }
      } break;

      default: {
        if (arguments == argumentsIterator) {
          argumentIterator = *argumentsIterator;

          // ...
          #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
            int const argumentLength = ::lstrlenA(argumentIterator);
            wchar_t  *directory      = workingPath;

            // ...
            if (0 == argumentLength) {
              *(directory++) = L'*';
              *(directory++) = L'\0';

              continue;
            }

            else if (MAX_PATH < argumentLength) {
              if (((*argumentIterator >= 'A' && *argumentIterator <= 'Z') || (*argumentIterator >= 'a' && *argumentIterator <= 'z')) && ':' == *(argumentIterator + 1)) argumentIterator += 2;
              switch (*argumentIterator) { case '/': ++argumentIterator; break; case '\\': ++argumentIterator; if ('\\' == *argumentIterator) goto invalid_argument; }

              for (bool delimitedPathComponent = true; ; ++argumentIterator) {
                char const character = *argumentIterator;

                // ...
                if (delimitedPathComponent) for (char const *const reservedPathComponents[] = {"AUX", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9", "CON", "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9", "NUL", "PRN"}, *const *reservedPathComponent = reservedPathComponents; reservedPathComponent != reservedPathComponents + (sizeof(reservedPathComponents) / sizeof(char*)); ++reservedPathComponent)
                if (character == **reservedPathComponent) for (char const *iteratorA = argumentIterator, *iteratorB = *reservedPathComponent; ; ) {
                  if (*++iteratorA != *++iteratorB) break;
                  if ('\0' == *iteratorA) { if ('\0' == *iteratorB) goto invalid_argument; break; }
                  if ('\0' == *iteratorB) { if ('\0' == *iteratorA) goto invalid_argument; break; }
                }

                // ...
                if ('\0' == character || '\\' == character || '/' == character) {
                  switch (argumentIterator[-1]) {
                    case ' ': case '.': goto invalid_argument;
                    case '\\': case '/': switch (character) { case '\\': case '/': goto invalid_argument; }
                  }

                  if ('\0' == character) break;
                  delimitedPathComponent = true; continue;
                }

                else switch (character) {
                  case '<': case '>': case ':': case '"': case '|': case '?': case '*': goto invalid_argument;
                  default: if (static_cast<unsigned char>(character) < 32u || static_cast<unsigned>(character) > 255u) goto invalid_argument;
                }

                // ...
                delimitedPathComponent = false;
              }
            }

            else if ((BOOL) FILE_ATTRIBUTE_DIRECTORY != ::PathIsDirectoryA(argumentIterator))
              goto invalid_argument;

            // ... ->> Set the program's `workingPath`
            if (argumentLength + 1u > MAX_PATH) {
              *(directory++) = L'\\';
              *(directory++) = L'\\';
              *(directory++) = L'?';
              *(directory++) = L'\\';
            }

            if (argumentLength + 1 == ::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, *argumentsIterator, -1, directory, (sizeof(workingPath) / sizeof(wchar_t)) - (directory - workingPath))) {
              // ... ->> Partly normalize the specified `workingPath`
              for (; L'\0' != *directory; ++directory)
              if (L'/' == *directory) *directory = L'\\';

              // ... ->> Search files within the `workingPath` itself
              *(directory++) = L'\\';
              *(directory++) = L'*';
              *(directory++) = L'\0';

              continue;
            }
          #endif
        }

        invalid_argument: {
          argumentIterator = *argumentsIterator;

          std::fputs("Command-line argument \"", stderr);
          for (std::size_t length = 48u; '\0' != *argumentIterator; ++argumentIterator, --length) { if (0u == length) { std::fputs(" " "...", stderr); break; } std::fputc(*argumentIterator, stderr); }
          std::fputs("\" must be an existing valid directory or program option. (use the `--help` option for details)", stderr);

          return EXIT_FAILURE;
        }
      }
    }
  }

  // if (NULL == fileNameFormat)
  // fileNameFormat = "%i";

  // #if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
  //   fileSystemRedirectionEnabled = ::Wow64EnableWow64FsRedirection(FALSE);
  //   fileSearchHandle             = ::FindFirstFileW(workingPath, &fileInformation);

  //   // ...
  //   if (ERROR_FILE_NOT_FOUND == ::GetLastError()) {
  //     std::fputs("Found no files to rename.", stdout);
  //     return EXIT_SUCCESS;
  //   }

  //   if (INVALID_HANDLE_VALUE == fileSearchHandle) {
  //     std::fprintf(stderr, "%1.32s%ls%1.2s", "Could not access the directory \"", workingPath, "\".");
  //     return EXIT_FAILURE;
  //   }

  //   // ...
  //   for (std::size_t fileCount = 0u; FALSE != ::FindNextFileW(fileSearchHandle, &fileInformation); ) /* --> ERROR_NO_MORE_FILES == ::GetLastError() */ {
  //     for (std::size_t count = 0u; count <= fileCount; count = 0u != count ? count * 2u : 1u)
  //     if (count == fileCount) {
  //       void *const allocation = std::realloc(fileNames, ((0u != count ? count * 2u : 1u) + 1u) * sizeof(wchar_t[MAX_PATH]));

  //       // ...
  //       if (NULL == allocation) {
  //         std::free(fileNames);
  //         std::fputs("Could not rename files due to insufficient memory.", stderr);

  //         return EXIT_FAILURE;
  //       }

  //       fileNames = static_cast<wchar_t (*)[MAX_PATH]>(allocation);
  //     }

  //     // ...
  //     for (std::size_t index = MAX_PATH; index--; )
  //     fileNames[fileCount][index] = fileInformation.cFileName[index];

  //     for (wchar_t (*fileNamesIterator)[MAX_PATH] = fileNames; fileNamesIterator != fileNames + fileCount; ++fileNamesIterator)
  //     for (std::size_t index = 0u; MAX_PATH != index; ++index) {
  //       if (fileInformation.cFileName[index] < (*fileNamesIterator)[index])
  //       break;

  //       if (fileInformation.cFileName[index] > (*fileNamesIterator)[index]) {
  //         for (wchar_t (*fileNamesSubiterator)[MAX_PATH] = fileNames + fileCount; fileNamesIterator != fileNamesSubiterator--; )
  //         for (index = MAX_PATH; index--; ) fileNamesSubiterator[1][index] = fileNamesSubiterator[0][index];

  //         for (index = MAX_PATH; index--; )
  //         (*fileNamesIterator)[index] = fileInformation.cFileName[index];

  //         // ...
  //         fileNamesIterator = fileNames + (fileCount - 1u);
  //         break;
  //       }
  //     }

  //     *(fileNames[++fileCount]) = L'\0';
  //   }

  //   for (wchar_t (*fileName)[MAX_PATH] = fileNames; L'\0' != **fileName; ++fileName)
  //   std::printf("[]: \"%ls\"" "\r\n", *fileName);

  //   std::free(fileNames);
  //   if (TRUE == fileSystemRedirectionEnabled) ::Wow64EnableWow64FsRedirection(TRUE);
  //   if (FALSE != ::FindClose(fileSearchHandle)) return EXIT_FAILURE;
  // #endif

  // // char const *applicationName                 = NULL == *arguments || '\0' == **arguments ? NULL : *arguments; // ->> ignore the executable file
  // // std::size_t fileIndex                       = 1u;                                                            // ->> numerical index to rename files
  // // char const *fileNameFormat                  = NULL;                                                          // ->> format string to rename files
  // // char       *fileNames                       = NULL;                                                          //
  // // char const  sourceName                   [] = __FILE__;                                                      // ->> ignore the source file
  // // wchar_t     workingPath[MAX_PATH + 4u] = {L'\0'};                                                       // ->> filesystem location to rename expected files
  // static_cast<void>(applicationName);
  // static_cast<void>(fileIndex);
  // static_cast<void>(fileNames);
  // static_cast<void>(sourceName);
  // static_cast<void>(workingPath);

  // ...
  return EXIT_SUCCESS;
}
