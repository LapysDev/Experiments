/* TODO (Lapys) -> POSIX support + don't rename executable itself */
#if defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
# define _CRT_SECURE_NO_WARNINGS
# define  UNICODE
# define _UNICODE
# undef  _MBCS

# include <windows.h> // --> kernel32.dll, kernel32.lib
#   include <strsafe.h>
#endif

#include <cfloat>   // --> LDBL_EPSILON
#include <climits>  // --> SIZE_MAX
#include <cmath>    // --> std::modfl(...)
#include <cstddef>  // --> std::size_t
#include <cstdio>   // --> std::fflush(...), std::fgetc(...), std::fprintf(...), std::fputc(...), std::fputs(...), std::setvbuf(...)
#include <cstdlib>  // --> std::aligned_alloc(...), std::free(...), std::malloc(...), std::qsort(...), std::realloc(...)
#include <ctime>    // --> std::time_t;    std::time(...)
#include <cwchar>   // --> std::mbstate_t; std::mbsrtowcs(...), std::wcslen(...), std::wcsncat(...), std::wcsncpy(...), std::wcsrtombs(...)
#include <new>      // --> ::new; std::nothrow
#include <stdint.h> // --> uintptr_t ->> may not be defined

/* Main */
int main(int count, char* arguments[]) /* noexcept */ {
  static struct renumerator_arena /* final */ {
    struct /* final */ {
      unsigned char      chunk[128u * 1024u]; // ->> 128 kilobytes
      renumerator_arena *chunks;              // ->> Collection of linked fixed-size storage buffers
      std::size_t        chunksCapacity;      //
      std::size_t        chunksLength;        //
    } storage;

    unsigned char *buffer;         // ->> Defaults to fixed-size `renumerator_arena::...::chunk`
    std::size_t    bufferCapacity; // ->> Defaults to `sizeof(renumerator_arena::...::chunk)`
    bool           invalidated;    // ->> `std::realloc(...)` can be tricky; See `renumerator_arena::allocate(...)`
    unsigned char *pointer;        // ->> Next un-allocated region within `renumerator_arena::buffer`

    /* ... */
    inline ~renumerator_arena() /* noexcept */ {
      for (renumerator_arena *allocator = this -> storage.chunks + (this -> storage.chunksCapacity * (NULL != this -> storage.chunks)); allocator != this -> storage.chunks; )
        (--allocator) -> ~renumerator_arena();

      std::free(this -> storage.chunks);

      if (this -> buffer != this -> storage.chunk)
      ::delete[] (this -> buffer);
    }

    /* ... */
    /* [[nodiscard]] */ inline unsigned char* allocate(std::size_t const size, std::size_t const alignment, bool const growable = true) /* noexcept */ {
      unsigned char *allocated = this -> pointer;

      // ...
      if (size > this -> bufferCapacity)
      return NULL;

      // ...
      if (0u == this -> storage.chunksLength) {
        for (; 0u != (allocated - this -> buffer) % alignment; ++allocated)
        if (this -> bufferCapacity == static_cast<std::size_t>(allocated - this -> buffer)) break;

        // ... ->> Out of memory
        if (size > static_cast<std::size_t>((this -> buffer + this -> bufferCapacity) - allocated)) {
          if (false == growable)
          return NULL;

          if (0u == this -> storage.chunksCapacity) {
            #if __cplusplus < 201103L
              this -> storage.chunks = ::new (std::malloc(sizeof(renumerator_arena) * 2u)) renumerator_arena[2]; // ->> Ideally `alignof renumerator_arena` (could be aligned by offset-ing)
            #else
              this -> storage.chunks = ::new (std::aligned_alloc(sizeof(renumerator_arena), sizeof(renumerator_arena) * 2u)) renumerator_arena[2];
            #endif

            if (NULL == this -> storage.chunks)
            return NULL;

            for (renumerator_arena *allocator = this -> storage.chunks; allocator != this -> storage.chunks + 2; ++allocator) {
              allocator -> buffer         = allocator -> storage.chunk;
              allocator -> bufferCapacity = sizeof(allocator -> storage.chunk);
              allocator -> pointer        = allocator -> buffer;
            }

            this -> storage.chunksCapacity = 2u;
          }

          this -> storage.chunksLength = 1u;

          // ...
          return this -> allocate(size, alignment, true);
        }

        this -> pointer = allocated + size;
      }

      else {
        renumerator_arena *chunks    = this -> storage.chunks;
        renumerator_arena *allocator = chunks + (this -> storage.chunksLength - 1u);

        // ... ->> Attempt allocating from a `renumerator_arena::...::chunk` within `this -> storage.chunks`
        allocated = allocator -> allocate(size, alignment, false);

        if (NULL == allocated && allocator -> pointer != allocator -> storage.chunk)
        if (growable) {
          uintptr_t const value = reinterpret_cast<uintptr_t>(chunks);

          // ... ->> Unable to track additional `renumerator_arena::...::chunk`s
          if (SIZE_MAX == this -> storage.chunksLength)
          return NULL;

          if (this -> storage.chunksCapacity == this -> storage.chunksLength) {
            std::size_t size = this -> storage.chunksCapacity;

            // ... ->> Unable to allocate additional `renumerator_arena::...::chunk`s
            if (SIZE_MAX == this -> storage.chunksCapacity) return NULL;
            for (; this -> storage.chunksCapacity > SIZE_MAX - size; size /= 2u) { if (size == 1u) return NULL; }

            chunks = static_cast<renumerator_arena*>(std::realloc(chunks, (this -> storage.chunksCapacity + size) * sizeof(renumerator_arena))); // --> std::launder(std::realloc(...))

            if (NULL == chunks)
            return NULL;

            if (
              value  != reinterpret_cast<uintptr_t>(chunks) || // ->> `std::realloc(...)` probably moved storage, can't guarantee using pointer inequality due to `chunks` possibly being invalidated
              chunks != this -> storage.chunks                 // ->> Then risk undefined behavior from accessing the possibly invalid `this -> storage.chunks` pointer to guarantee `std::realloc(...)` didn't move storage
            ) this -> invalidated = true; // ->> Storage allocated prior from `this -> storage.chunks` is now invalid

            // ... ->> Construct newly allocated `renumerator_arena`s
            this -> storage.chunksCapacity += size;
            this -> storage.chunks          = chunks;
            chunks                         += this -> storage.chunksCapacity;

            while (true) {
              allocator                   = ::new (--chunks) renumerator_arena();
              allocator -> buffer         = allocator -> storage.chunk;
              allocator -> bufferCapacity = sizeof(allocator -> storage.chunk);
              allocator -> pointer        = allocator -> buffer;

              if (this -> storage.chunksLength == static_cast<std::size_t>(chunks - this -> storage.chunks))
              break;
            }
          }

          // ... ->> Attempt allocating from a newly reserved `renumerator_arena::...::chunk`
          allocator                     = this -> storage.chunksLength++ + this -> storage.chunks;
          allocated                     = allocator -> allocate(size, alignment, false);
          this -> storage.chunksLength -= NULL == allocated;

          if (this -> invalidated)
          return NULL;
        }
      }

      // ...
      return allocated;
    }

    /* [[nodiscard]] */ inline unsigned char* reallocate(std::size_t const releaseSize, std::size_t const releaseAlignment, std::size_t const allocationSize, std::size_t const allocationAlignment, bool const growable = true) /* noexcept(noexcept(this -> release(releaseSize, releaseAlignment)) && noexcept(this -> allocate(allocationSize, allocationAlignment, growable))) */ {\
      std::size_t    const chunksLength = this -> storage.chunksLength;
      renumerator_arena   &allocator    = 0u != chunksLength ? this -> storage.chunks[chunksLength - 1u] : *this;
      unsigned char       *reallocated  = NULL;
      unsigned char *const released     = allocator.pointer;

      // ...
      if (this -> release(releaseSize, releaseAlignment))
        reallocated = this -> allocate(allocationSize, allocationAlignment, growable);

      if (NULL == reallocated) {
        allocator.pointer            = released;
        this -> storage.chunksLength = chunksLength;
      }

      // ...
      return reallocated;
    }

    /* [[nodiscard]] */ inline static char const (&size(long double amount) /* noexcept */)[30] {
      static char                                   measurement[30] = {'\0'}; // --> char[(log10(SIZE_MAX) + 1u + 2u) + 1u + max(...(B, ..., YB)) + 1u]
      enum unit_t { B, KB, MB, TB, PB, EB, ZB, YB } unit            = B;
      char const                                   *unitStrings[B | EB | KB | MB | PB | TB | YB | ZB]; // ->> Preferably `max(B, ..., ZB)`, instead

      // ...
      unitStrings[B]  = "bytes";
      unitStrings[EB] = "EB";
      unitStrings[KB] = "KB";
      unitStrings[MB] = "MB";
      unitStrings[PB] = "PB";
      unitStrings[TB] = "TB";
      unitStrings[YB] = "YB";
      unitStrings[ZB] = "ZB";

      for (; amount >= 1024.0L; amount /= 1024.0L) {
        unit = static_cast<unit_t>(static_cast<int>(unit) + 1);
        if (YB == unit) break;
      }

      amount *= 100.0L; {
        unsigned char place  = 6u;
        long double   rank   = 100000.0L;
        char         *string = measurement;

        // ...
        for (; 0u != place-- && LDBL_EPSILON < amount; rank /= 10.0L) {
          if (false) {}
          else if (amount >= rank * 9.0L) { amount -= rank * 9.0L; *(string++) = '9'; }
          else if (amount >= rank * 8.0L) { amount -= rank * 8.0L; *(string++) = '8'; }
          else if (amount >= rank * 7.0L) { amount -= rank * 7.0L; *(string++) = '7'; }
          else if (amount >= rank * 6.0L) { amount -= rank * 6.0L; *(string++) = '6'; }
          else if (amount >= rank * 5.0L) { amount -= rank * 5.0L; *(string++) = '5'; }
          else if (amount >= rank * 4.0L) { amount -= rank * 4.0L; *(string++) = '4'; }
          else if (amount >= rank * 3.0L) { amount -= rank * 3.0L; *(string++) = '3'; }
          else if (amount >= rank * 2.0L) { amount -= rank * 2.0L; *(string++) = '2'; }
          else if (amount >= rank * 1.0L) { amount -= rank * 1.0L; *(string++) = '1'; }
          else if (measurement != string) *(string++) = '0';

          if (place == 2u && LDBL_EPSILON < amount) {
            if (measurement == string)
              *(string++) = '0';

            *(string++) = '.';
          }
        }

        if (measurement == string)
          *(string++) = '0';

        *(string++) = ' ';

        for (char const *unitString = unitStrings[unit]; '\0' != *unitString; ++unitString)
          *(string++) = *unitString;

        *string = '\0';
      }

      return measurement;
    }

    /* [[nodiscard]] */ inline char const (&size() const /* noexcept */)[30] {
      std::size_t amount = this -> pointer - this -> buffer;

      // ...
      if (0u != this -> storage.chunksLength) {
        amount  = this -> bufferCapacity + ((this -> storage.chunksLength - 1u) * sizeof(this -> storage.chunk));
        amount += this -> storage.chunks[this -> storage.chunksLength - 1u].pointer - this -> storage.chunks[this -> storage.chunksLength - 1u].buffer;
      }

      return renumerator_arena::size(amount);
    }

    inline bool release(std::size_t const size, std::size_t const alignment) /* noexcept */ {
      renumerator_arena &allocator = 0u != this -> storage.chunksLength ? this -> storage.chunks[this -> storage.chunksLength - 1u] : *this;
      unsigned char     *released  = allocator.pointer;

      // ...
      if (size > static_cast<std::size_t>(released - allocator.buffer))
      return false;

      for (released -= size; ; --released) {
        if (0u == (released - allocator.buffer) % alignment) break;
        if (released == allocator.buffer) return false;
      }

      allocator.pointer             = released;
      this -> storage.chunksLength -= released == allocator.buffer;

      // ...
      return true;
    }
  } allocator = {
    // ->> Linear allocator which releases/ reserves contiguous storage in order only
    {{}, NULL, 0u, 0u}, allocator.storage.chunk, sizeof(allocator.storage.chunk), false, allocator.storage.chunk
  };

  struct renumerator;                   // ->> `renumerator::sort(...)` function for `filePaths`
  struct renumerator_format /* final */ /* ->> Convert command-line option to `renameFormat` */ {
    inline static wchar_t* convert(char const commandLineOption[], std::size_t* const size) /* noexcept */ {
      std::mbstate_t     state       = std::mbstate_t();
      char const        *option      = commandLineOption;
      std::mbstate_t     lengthState = state;
      std::size_t const  length      = std::mbsrtowcs(static_cast<wchar_t*>(NULL), &option, 0u, &lengthState);
      wchar_t           *format;

      // ...
      *size = 0u;

      if (length == static_cast<std::size_t>(-1)) return NULL;
      format = ::new (allocator.allocate((length + 1u) * sizeof(wchar_t), sizeof(char), false)) wchar_t[length + 1u];

      if (NULL == format) return NULL;
      option = commandLineOption;
      *size  = length;

      // ...
      return length == std::mbsrtowcs(format, &option, length + 1u, &state) ? format : NULL;
    }

    inline static wchar_t* convert(wchar_t const commandLineOption[], std::size_t* const size) /* noexcept */ {
      *size = std::wcslen(commandLineOption);
      return const_cast<wchar_t*>(commandLineOption);
    }
  };

  /* ... */
  bool           allocatorExhausted              = false;                        // ->> Indicator out-of-memory state for `allocator`
  bool           enumerateHiddenFiles            = false;                        // ->> Switch denoting `--hidden` command-line option
  bool           enumerateSystemFiles            = false;                        // ->> Switch denoting `--system` command-line option
  int            executableExitCode              = EXIT_SUCCESS;                 //
  bool           executableFilePathAllocated     = false;                        //
  wchar_t      **filePaths                       = NULL;                         // ->> Array                of NUL-terminated file paths
  wchar_t       *filePathsBuffer                 = NULL;                         // ->> NUL-delimited string of NUL-terminated file paths
  std::size_t    filePathsBufferSize             = 0u;                           // ->> With NUL terminator; Measured in `sizeof wchar_t`
  std::size_t    filePathsLength                 = 0u;                           // ->> Number of `filePaths`
  bool           memoryRequested                 = false;                        // ->> Switch denoting `--memory` (or `-m`) command-line option
  std::size_t    memorySize                      = 0u;                           // ->> Number of bytes allowed to be pre-allocated by the user
  int            promptToken                     = EOF;                          // ->> User input
  static bool    quietRequested                  = false;                        // ->> Switch denoting `--quiet` (or `-q`) command-line option; Toggles most diagnostic logs
  wchar_t const *renameFormat                    = L"??";                        // ->> See `--help` message for more information
  bool           renameFormatAllocated           = false;                        //
  bool           renameFormatIncludesRenameIndex = false;                        // ->> `renameFormat` includes `?` or `??` character sequences
  std::size_t    renameFormatIndex               = static_cast<std::size_t>(-1); // ->> Position within `arguments` array
  std::size_t    renameFormatLength              = 0u;                           //
  std::size_t    renameIndex                     = 1u;                           //
  bool           renameIndexRequested            = false;                        // ->> Switch denoting `--index` (or `-i`) or `--zero` (or `-z`) command-line options
  bool           renumerationDirectoryAllocated  = false;                        //
  bool           renumerationDirectoryRecognized = true;                         // ->> User specified empty directory or there was not enough memory to store it

  // ... ->> Parse command-line arguments for possible command-line options
  if (count > 2) {
    enum /* : int */ { FORMAT, HELP, HIDDEN, INDEX, MEMORY, QUIET, SYSTEM, ZERO };
    bool commandLineOptionDuplicated = false;
    bool helpRequested               = false;

    // ... ->> Iterate over `arguments`, sub-iterate over `commandLineOptions`
    for ((arguments += 2), (count = 0); NULL != *arguments; ++arguments, ++count)
    for (struct { signed type; char const *value; } const commandLineOptions[] = {
      {FORMAT, "--format"}, {FORMAT, "-f"},
      {HELP,   "--help"  }, {HELP,   "-h"},
      {HIDDEN, "--hidden"},
      {INDEX,  "--index" }, {INDEX,  "-i"},
      {MEMORY, "--memory"}, {MEMORY, "-m"},
      {QUIET,  "--quiet" }, {QUIET,  "-q"},
      {SYSTEM, "--system"},
      {ZERO,   "--zero"  }, {ZERO,   "-z"}
    }, *commandLineOption = commandLineOptions; NULL != commandLineOption && commandLineOption != commandLineOptions + (sizeof(commandLineOptions) / sizeof(*commandLineOption)); commandLineOption += NULL != commandLineOption) {
      // ... ->> Namespace featuring utilities for parsing command-line options
      struct renumerator_options /* final */ {
        // ... ->> Trim (leading whitespace) from `argument`
        inline static char* trim(char* argument) /* noexcept */ {
          for (bool trimmed = false; false == trimmed; ) {
            char const character = *argument;

            // ... --> std::isspace(character);
            switch (character) {
              case ' ': case '\f': case '\n': case '\r': case '\t': case '\v': ++argument; break;
              default: trimmed = true; break;
            }
          }

          return argument;
        }
      };

      /* ... */
      for (char *argument = renumerator_options::trim(*arguments), *option = const_cast<char*>(commandLineOption -> value); ; ++argument, ++option) {
        bool commandLineOptionRecognized = false;

        // ...
        if ('\0' == *option) {
          char *trimmedArgument = renumerator_options::trim(argument);

          // ...
          if (FORMAT == commandLineOption -> type || INDEX == commandLineOption -> type || MEMORY == commandLineOption -> type) {
            // ... ->> No value found for command-line option
            if ('\0' == *trimmedArgument) {
              if (false == quietRequested)
                (void) std::fprintf(stderr, "%1.71s%s%c", "renum: Expected corresponding command-line option value using `=` for `", commandLineOption -> value, '`');

              return EXIT_FAILURE;
            }

            // ... No value found for command-line option
            if (*trimmedArgument != '=') {
              if (argument != trimmedArgument) {
                if (false == quietRequested)
                  (void) std::fprintf(stderr, "%1.61s%s%1.43s", "renum: Expected corresponding command-line option value for `", commandLineOption -> value, "`; consider using `=` instead of whitespace");

                return EXIT_FAILURE;
              }

              commandLineOptionRecognized = false;
            }

            // ...
            else {
              commandLineOptionRecognized = true;
              trimmedArgument            += 1;

              switch (commandLineOption -> type) {
                case FORMAT: {
                  argument              = trimmedArgument;
                  renameFormat          = renumerator_format::convert(argument, &renameFormatLength);
                  renameFormatAllocated = NULL != renameFormat;
                  renameFormatIndex     = count + 2;

                  for (; '\0' != *argument; ++argument)
                    renameFormatIncludesRenameIndex = renameFormatIncludesRenameIndex || *argument == '?';

                  // ...
                  argument = trimmedArgument;

                  if (false == renameFormatIncludesRenameIndex) {
                    if (false == quietRequested)
                      (void) std::fprintf(stderr, "%1.75s%s%c", "renum: Expected `?`, `??`, or `???` character sequences in rename format: \"", argument, '"');

                    return EXIT_FAILURE;
                  }
                } break;

                case INDEX:
                case MEMORY: {
                  std::size_t const length = INDEX | MEMORY; // ->> Preferably `max(...)`, instead
                  char const       *names   [length];
                  bool             *switches[length];
                  std::size_t      &value =
                    INDEX  == commandLineOption -> type ? renameIndex :
                    MEMORY == commandLineOption -> type ? memorySize  :
                  const_cast<std::size_t&>(static_cast<std::size_t const&>(0u));

                  // ...
                  names[INDEX]  = "`--index` (`-i`)"  " " "option";
                  names[MEMORY] = "`--memory` (`-m`)" " " "option";

                  switches[INDEX]  = &renameIndexRequested;
                  switches[MEMORY] = &memoryRequested;

                  if (*switches[commandLineOption -> type]) {
                    commandLineOptionDuplicated = true;

                    (void) std::fprintf(stdout, "%1.7s%23.24s%1.27s", "renum: ", names[commandLineOption -> type], " specified more than once" "\r\n");
                    (void) std::fflush(stdout);
                  }

                  argument                             = trimmedArgument;
                  *switches[commandLineOption -> type] = true;
                  value                                = 0u;

                  // ... ->> Account for leading zeroes
                  if (*argument == '0')
                  switch (*renumerator_options::trim(argument + 1)) {
                    // ... ->> Single digit zero
                    case '\0': break;

                    // ... ->> Redundant leading zero(es)
                    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': /* --> 0 != std::isdigit(static_cast<unsigned char>(...)) */ {
                      argument = NULL;

                      if (false == quietRequested)
                      (void) std::fputs("renum: Expected integer value (with no leading zeroes) for `", stderr);
                    } break;

                    // ... ->> Invalid character
                    default: {
                      argument = NULL;

                      if (false == quietRequested)
                      (void) std::fputs("renum: Expected integer value for `", stderr);
                    } break;
                  }

                  if (NULL != argument) {
                    bool        calculable = true;
                    std::size_t rank       = 1u;

                    // ...
                    for (unsigned char digit = 0u; ; ++argument, rank *= 10u) {
                      char const        character = *argument;
                      char const *const token     = renumerator_options::trim(argument);

                      // ...
                      if ('\0' == *token)
                      break;

                      if (argument != token || (
                        /* --> 0 == std::isdigit(static_cast<unsigned char>(character)) */
                        character != '0' &&
                        character != '1' &&
                        character != '2' &&
                        character != '3' &&
                        character != '4' &&
                        character != '5' &&
                        character != '6' &&
                        character != '7' &&
                        character != '8' &&
                        character != '9'
                      )) {
                        if (false == quietRequested)
                          (void) std::fputs("renum: Expected integer value for `", stderr);

                        argument = NULL;
                        break;
                      }

                      // ... --> digit = static_cast<unsigned char>(*argument - '0');
                      switch (*argument) {
                        case '0': digit = 0u; break;
                        case '1': digit = 1u; break;
                        case '2': digit = 2u; break;
                        case '3': digit = 3u; break;
                        case '4': digit = 4u; break;
                        case '5': digit = 5u; break;
                        case '6': digit = 6u; break;
                        case '7': digit = 7u; break;
                        case '8': digit = 8u; break;
                        case '9': digit = 9u; break;
                      }

                      calculable = calculable && value <= static_cast<unsigned long>(SIZE_MAX / rank) - digit;
                      if (calculable) value = (value * 10u) + digit;
                    }

                    if (false == calculable) {
                      if (false == quietRequested)
                        (void) std::fprintf(stderr, "%1.22s%s%1.17s%2.8s%1.33s%lu%1.55s", "renum: Integer value `", (argument = trimmedArgument), "` specified for `", commandLineOption -> value, "` too large; maximum allowed is `", static_cast<unsigned long>(SIZE_MAX), "` minus the number of files in the enumerated directory");

                      return EXIT_FAILURE;
                    }
                  }

                  if (NULL == argument) {
                    if (false == quietRequested)
                      (void) std::fprintf(stderr, "%2.8s%1.28s%s%1.9s", commandLineOption -> value, "` command-line option; got `", renumerator_options::trim(argument), "` instead");

                    return EXIT_FAILURE;
                  }
                } break;
              }
            }
          }

          else if ('\0' == *trimmedArgument) {
            std::size_t const length = HELP | HIDDEN | QUIET | SYSTEM | ZERO; // ->> Preferably `max(...)`, instead
            char const       *names   [length];
            bool             *switches[length];

            // ...
            names[HELP]   = "`--help` (`-h`)"                     " " "option";
            names[HIDDEN] = "`--hidden`"                          " " "option";
            names[QUIET]  = "`--quiet` (`-q`)"                    " " "option";
            names[SYSTEM] = "`--system`"                          " " "option";
            names[ZERO]   = "`--index` (`-i`) or `--zero` (`-z`)" " " "options";

            switches[HELP]   = &helpRequested;
            switches[HIDDEN] = &enumerateHiddenFiles;
            switches[QUIET]  = &quietRequested;
            switches[SYSTEM] = &enumerateSystemFiles;
            switches[ZERO]   = &renameIndexRequested;

            // ...
            if (*switches[commandLineOption -> type]) {
              (void) std::fprintf(stdout, "%1.7s%17.43s%1.27s", "renum: ", names[commandLineOption -> type], " specified more than once" "\r\n");
              (void) std::fflush(stdout);

              commandLineOptionDuplicated = true;
            }

            commandLineOptionRecognized          = true;
            renameIndex                          = ZERO == commandLineOption -> type ? 0u : renameIndex;
            *switches[commandLineOption -> type] = true;
          }

          // ...
          if (false == commandLineOptionRecognized) {
            if (false == quietRequested) {
              (void) std::fputs("renum: `", stderr);

              for (argument = renumerator_options::trim(*arguments); ; ++argument) {
                char const token = *renumerator_options::trim(argument);

                // ...
                if ('\0' == token || token == '=') break;
                (void) std::fputc(*argument, stderr);
              }

              (void) std::fprintf(stderr, "%1.57s%2.8s%1.11s", "` is not a recognized command-line option; did you mean `", commandLineOption -> value, "`, instead?");
            }

            return EXIT_FAILURE;
          }

          commandLineOption = NULL;
          break;
        }

        if (*argument != *option) {
          if (commandLineOption != commandLineOptions + ((sizeof(commandLineOptions) / sizeof(*commandLineOption)) - 1u))
            break; // ->> Move on to the next `commandLineOptions`

          else {
            // ... ->> Unrecognized command-line option (starting with a `-` token)
            if ('-' == *renumerator_options::trim(*arguments)) {
              if (false == quietRequested) {
                (void) std::fputc('`', stderr);

                for (argument = renumerator_options::trim(*arguments); ; ++argument) {
                  char const token = *renumerator_options::trim(argument);

                  // ...
                  if ('\0' == token || token == '=') break;
                  (void) std::fputc(*argument, stderr);
                }

                (void) std::fputs("` is not a recognized command-line option", stderr);
              }

              // ...
              return EXIT_FAILURE;
            }

            // ... ->> Assume `argument` is the `--format` command-line option
            if (0 != count) {
              std::size_t       length  = 0u;
              std::size_t const maximum = 18u; // --> maximum < INT_MAX

              // ...
              for (argument = *arguments; '\0' != *argument; ++argument)
              if (++length == maximum + 1u) break;

              if (false == quietRequested)
                (void) std::fprintf(stderr, "%1.41s%1.*s%1.3s%1.13s", "renum: Unrecognized command-line option `", static_cast<int>(maximum), '\0' == **arguments ? "\0" : *arguments, length == maximum + 1u ? "..." : "\0", "` encountered");

              // ...
              return EXIT_FAILURE;
            }

            argument              = *arguments;
            renameFormat          = renumerator_format::convert(argument, &renameFormatLength);
            renameFormatAllocated = NULL != renameFormat;
            renameFormatIndex     = count + 2;

            for (; '\0' != *argument; ++argument)
              renameFormatIncludesRenameIndex = renameFormatIncludesRenameIndex || *argument == '?';

            if (false == renameFormatIncludesRenameIndex) {
              if (false == quietRequested)
                (void) std::fprintf(stderr, "%1.75s%s%c", "renum: Expected `?`, `??`, or `???` character sequences in rename format: \"", (argument = *arguments), '"');

              return EXIT_FAILURE;
            }

            break; // ->> Move on to the next `commandLineOptions`
          }
        }
      }
    }

    // ...
    if (helpRequested) {
      char const message[] =
        "renum [current_working_directory] [options] [rename_format]"                                                                                                                             "\r\n"
        "  Renames files by their indexes"                                                                                                                                                        "\r\n"
        ""                                                                                                                                                                                        "\r\n"
        "  current_working_directory = Location containing files to be renamed"                                                                                                                   "\r\n"
        "  rename_format             = New (multi-byte) name to rename files as (should be ideally valid for its filesystem);"                                                                    "\r\n"
        "                                must include either `?` or `??` character sequences (at least once) to proceed renaming files"                                                           "\r\n"
        "                                ?   = Index of a file"                                                                                                                                   "\r\n"
        "                                ??  = Evenly padded index of a file with leading zeroes"                                                                                                 "\r\n"
        "                                ??? = Name of a file"                                                                                                                                    "\r\n"
        ""                                                                                                                                                                                        "\r\n"
        "                                example(s): "                                                                                                                                            "\r\n"
        "                                - \"? - file\"  denotes \"69 - file.bmp\"       for the 69th file (with extension \"bmp\") to be renamed"                                                "\r\n"
        "                                - \"?? - file\" denotes \"069 - file.jpeg\"     for the 69th file (with extension \"jpeg\") to be renamed in a directory of a hundred (100-999) files"   "\r\n"
        "                                - \"??? file\"  denotes \"sixty-nine file.png\" for the file named \"sixty-nine\" (with extension \"png\") to be renamed; must be used with `?` or `??`" "\r\n"
        "  options                   = Command-line options to configure how files are renamed"                                                                                                   "\r\n"
        "                                --format | -f = Specifies the `rename_format`"                                                                                                           "\r\n"
        "                                --help   | -h = Logs this help message"                                                                                                                  "\r\n"
        "                                --hidden      = Renames hidden files, as well (ignored by default)"                                                                                      "\r\n"
        "                                --index  | -i = Specifies the starting offset for the file index;"                                                                                       "\r\n"
        "                                  example: \"file-?\" would denote \"file-420\" instead of \"file-69\" with an offset of 351 (420 minus 69)"                                             "\r\n"
        "                                --memory | -m = Specifies the number of bytes allowed to pre-allocate for ideally more available memory"                                                 "\r\n"
        "                                --quiet  | -q = Silences (most) output diagnostic to the standard error or output devices"                                                               "\r\n"
        "                                --system      = Renames system files, as well (ignored by default)"                                                                                      "\r\n"
        "                                --zero   | -z = Sets the starting offset for the file index to 0"                                                                                        "\0"
      ;

      return std::fprintf(stdout, "%s%1.*s", commandLineOptionDuplicated ? "\n" : "", static_cast<int>((sizeof(message) / sizeof(char)) - 2u), message) < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
    }
  }

  // ... ->> Allocate user-requested memory size
  if (memorySize > sizeof(allocator.storage.chunk)) {
    allocator.buffer = ::new (std::nothrow) unsigned char[memorySize];

    // ...
    if (NULL != allocator.buffer) {
      allocator.bufferCapacity = memorySize;
      allocator.pointer        = allocator.buffer;
    }

    else {
      allocator.buffer = allocator.storage.chunk;
      (void) std::fprintf(stdout, "%1.30s%s%1.2s", "renum: Failed to pre-allocate ", renumerator_arena::size(memorySize), "\r\n");
    }
  }

  // ... ->> Must declare `executableFilePath`, `executableFilePathLength`, `renumerationDirectory`, and `renumerationDirectoryLength` variables; See `else` case
  #if defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
    struct renumerator /* final */ {
      inline static int sort(void const* const filePathA, void const* const filePathB) /* noexcept */ {
        int const comparison = ::CompareStringEx(LOCALE_NAME_USER_DEFAULT /* --> "en-US" */, SORT_DIGITSASNUMBERS | SORT_STRINGSORT, *static_cast<wchar_t* const*>(filePathA), -1, *static_cast<wchar_t* const*>(filePathB), -1, static_cast<LPNLSVERSIONINFO>(NULL), static_cast<LPVOID>(NULL), static_cast<LPARAM>(0x00));

        // ...
        if (0 == comparison)
        return 0; // ->> Silently fails `filePathA <=> filePathB`

        switch (comparison) {
          case CSTR_EQUAL:        return 0;
          case CSTR_GREATER_THAN: return +1;
          case CSTR_LESS_THAN:    return -1;
        }

        return 0;
      }
    };

    /* ... */
    ::SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_SYSTEM32);

    // ...
    HMODULE const normaliz = ::LoadLibraryExW(L"normaliz" ".dll", static_cast<HANDLE>(NULL), 0x00u);
    HMODULE const shell32  = ::LoadLibraryExW(L"shell32"  ".dll", static_cast<HANDLE>(NULL), 0x00u);
      LPWSTR* (*const CommandLineToArgvW)(LPCWSTR, int[])                       = reinterpret_cast<LPWSTR* (*)(LPCWSTR, int[])>                      (reinterpret_cast<void*>(NULL != shell32  ? ::GetProcAddress(shell32,  "CommandLineToArgvW") : NULL));
      int     (*const NormalizeString)   (NORM_FORM, LPCWSTR, int, LPWSTR, int) = reinterpret_cast<int     (*)(NORM_FORM, LPCWSTR, int, LPWSTR, int)>(reinterpret_cast<void*>(NULL != normaliz ? ::GetProcAddress(normaliz, "NormalizeString")    : NULL));

    std::size_t       renumerationDirectoryLength     = 0u;                                                                                                                          //
    HANDLE            renumerationDirectoryFindHandle = INVALID_HANDLE_VALUE;                                                                                                        //
    WIN32_FIND_DATAW  renumerationDirectoryFindData   = {};                                                                                                                          //
    LPTSTR            renumerationDirectory           = NULL;                                                                                                                        // ->> Directory to enumerate files to be renamed
    std::size_t const subdirectorySuffixLength        = 2u;                                                                                                                          //
    LPCTSTR     const subdirectorySuffix              = L"\\*";                                                                                                                      // ->> Windows-specific character sequence which instructs its filesystem APIs to access sub-directories of a specified path
    BOOL              filesystemRedirectionDisabled   = FALSE;                                                                                                                       // ->> Indicated by `::Wow64DisableWow64FsRedirection(...)`
    PVOID             filesystemRedirection           = NULL;                                                                                                                        // ->> Used      by `::Wow64DisableWow64FsRedirection(...)`
    std::size_t       executableFilePathLength        = MAX_PATH;                                                                                                                    // ->> With NUL terminator(s)
    LPWSTR            executableFilePath              = ::new (allocator.allocate(executableFilePathLength * sizeof(WCHAR), sizeof(WCHAR), false)) WCHAR[executableFilePathLength];  // ->> Avoid renaming executable
    TCHAR       const defaultDirectory[]              = L"." "\\*";                                                                                                                  //
    int               commandLineArgumentsLength      = 0;                                                                                                                           //
    LPWSTR     *const commandLineArguments            = NULL != shell32 && NULL != CommandLineToArgvW ? CommandLineToArgvW(::GetCommandLineW(), &commandLineArgumentsLength) : NULL; // ->> UTF-16 (endian-dependent) encoded version of `arguments`

    // ... ->> Inquire `executableFilePath`
    ::SetLastError(ERROR_SUCCESS);

    while (NULL != executableFilePath) {
      DWORD const fileNameLength = ::GetModuleFileNameW(static_cast<HMODULE>(NULL), executableFilePath, static_cast<DWORD>(executableFilePathLength));

      // ...
      executableFilePathAllocated = true;

      if (FALSE == fileNameLength) {
        // ... ->> Retry `::GetModuleFileName(...)` with ideally no truncation
        if (
          ERROR_INSUFFICIENT_BUFFER == ::GetLastError() ||
          ERROR_SUCCESS             == ::GetLastError() // ->> See previous `::SetLastError(...)` call
        ) {
          bool fileNameInquirable = false;

          // ...
          for (std::size_t length = executableFilePathLength; 0u != length && executableFilePathLength > SIZE_MAX - length; length /= 2u) {
            unsigned char *const reallocation = allocator.reallocate(executableFilePathLength * sizeof(WCHAR), sizeof(WCHAR), (executableFilePathLength + length) * sizeof(WCHAR), sizeof(WCHAR), false);

            // ...
            if (NULL == reallocation) {
              allocatorExhausted = true;
              continue;
            }

            fileNameInquirable        = true;
            executableFilePathLength += length;
            executableFilePath        = ::new (reallocation) WCHAR[executableFilePathLength];
          }

          if (fileNameInquirable)
          break;

          (void) allocator.release(executableFilePathLength * sizeof(WCHAR), sizeof(WCHAR)); // --> executableFilePath
          executableFilePath = NULL;
        }

        // ... ->> Get `executableFilePath` via `extern char *::_pgmptr`, instead
        #ifndef _MSC_VER
          static_cast<void>(NormalizeString);
        #else
          char       *programPointer;
          std::size_t programPointerSize = 0u; // ->> With NUL terminator

          // ...
          if (NULL == executableFilePath) {
            bool const fileNameConvertible = (
              0x00 == ::_get_pgmptr(&programPointer) &&
              SUCCEEDED(::StringCbLengthA(static_cast<STRSAFE_PCNZCH>(programPointer), STRSAFE_MAX_CCH * sizeof(char), &programPointerSize)) // ->> Cannot retrieve length alternatively
            );

            // ...
            if (fileNameConvertible) {
              DWORD flag = MB_ERR_INVALID_CHARS | MB_PRECOMPOSED;
              int   length;

              // ...
              programPointerSize += sizeof(char);
              while (true) {
                length = ::MultiByteToWideChar(CP_THREAD_ACP, flag, programPointer, static_cast<DWORD>(programPointerSize), static_cast<LPWSTR>(NULL), 0);

                // ...
                if (0 /* --> ERROR_NO_UNICODE_TRANSLATION */ != length) { fileNameConvertible = true; break; }
                if (0x00u != flag && ERROR_INVALID_FLAGS == ::GetLastError()) { flag = 0x00u; continue; } // ->> Retry with no conversion flags set

                fileNameConvertible = false;
                break;
              }

              do if (fileNameConvertible) {
                if (length < 0) { fileNameConvertible = false; break; } // ->> While not explicitly a `::MultiByteToWideChar(...)` fail state, a positive `length` is required regardless
                executableFilePath = ::new (allocator.allocate((length + 1) * sizeof(WCHAR), sizeof(WCHAR), false)) WCHAR[length + 1];

                if (NULL == executableFilePath) { allocatorExhausted = true; fileNameConvertible = false; break; }
                executableFilePathLength = length + 1;
                length                   = ::MultiByteToWideChar(CP_THREAD_ACP, flag, programPointer, static_cast<DWORD>(programPointerSize), executableFilePath, length + 1);

                if (0 == length) { fileNameConvertible = false; break; }
                if (NULL != normaliz && NULL != NormalizeString) {
                  LPWSTR denormalized;
                  int    normalizedLength = NormalizeString(::NormalizationC, executableFilePath, length, static_cast<LPWSTR>(NULL), 0);

                  // ...
                  if (0 == normalizedLength) { fileNameConvertible = false; break; }
                  if (normalizedLength < 0) {
                    if (ERROR_INSUFFICIENT_BUFFER == ::GetLastError()) { fileNameConvertible = false; break; }
                    normalizedLength = -normalizedLength; // --> ERROR_NO_UNICODE_TRANSLATION ->> Truncate `executableFilePath` to only contain valid Unicode characters
                  }

                  denormalized = ::new (allocator.allocate((length + 1u) * sizeof(WCHAR), sizeof(WCHAR), false)) WCHAR[length]; // ->> Unspecified if `NormalizeString(...)` accepts overlapping strings
                  if (NULL == denormalized) { allocatorExhausted = true; fileNameConvertible = false; break; }

                  if (FAILED(::StringCchCopyNExW(static_cast<STRSAFE_LPWSTR>(denormalized), length + 1, executableFilePath, length, static_cast<LPTSTR*>(NULL), static_cast<std::size_t*>(NULL), STRSAFE_FILL_BEHIND_NULL | STRSAFE_FILL_ON_FAILURE)))
                    denormalized = std::wcsncpy(denormalized, executableFilePath, length);

                  if (length != normalizedLength) {
                    executableFilePath       = ::new (allocator.reallocate(length * sizeof(WCHAR), sizeof(WCHAR), (normalizedLength + 1) * sizeof(WCHAR), sizeof(WCHAR), false)) WCHAR[normalizedLength + 1];
                    executableFilePathLength = normalizedLength + 1;
                    if (NULL == executableFilePath) { allocatorExhausted = true; fileNameConvertible = false; break; }

                    if (FAILED(::StringCchCopyNExW(static_cast<STRSAFE_LPWSTR>(executableFilePath), normalizedLength + 1, denormalized, length, static_cast<LPTSTR*>(NULL), static_cast<std::size_t*>(NULL), STRSAFE_FILL_BEHIND_NULL | STRSAFE_FILL_ON_FAILURE)))
                      executableFilePath = std::wcsncpy(executableFilePath, denormalized, length);
                  }

                  normalizedLength = NormalizeString(::NormalizationC, denormalized, length, executableFilePath, normalizedLength + 1);
                  (void) allocator.release((length + 1) * sizeof(WCHAR), sizeof(WCHAR)); // --> denormalized ->> Possibly overwritten by storage for `executableFilePath` on failure
                  if (normalizedLength <= 0) { fileNameConvertible = false; break; }
                }

                executableFilePath[executableFilePathLength - 1u] = L'\0';
              } while (false);
            }

            // ...
            if (fileNameConvertible)
            break;

            (void) allocator.release(executableFilePathLength * sizeof(WCHAR), sizeof(WCHAR)); // --> executableFilePath
            executableFilePath = NULL;
          }
        #endif

        // ... ->> Get `executableFilePath` via `::CommandLineToArgvW(L"", ...)`, instead
        if (NULL == executableFilePath && NULL != shell32 && NULL != CommandLineToArgvW) {
          int           executableCommandLineArgumentsLength = 0u;
          LPWSTR *const executableCommandLineArguments       = CommandLineToArgvW(L"", &executableCommandLineArgumentsLength);

          // ...
          executableFilePathAllocated = false;

          if (NULL != executableCommandLineArguments) {
            executableFilePath = *executableCommandLineArguments;

            if (FAILED(::StringCchLengthW(executableFilePath, STRSAFE_MAX_CCH, &executableFilePathLength)))
              executableFilePathLength = std::wcslen(executableFilePath);

            ++executableFilePathLength;
            (void) ::LocalFree(executableCommandLineArguments); // ->> Ideally successfully evaluates to `NULL`
          }

          break;
        }

        executableFilePath = NULL;
      }

      if (fileNameLength < executableFilePathLength) {
        for (LPWSTR path = executableFilePath + fileNameLength; executableFilePathLength != static_cast<std::size_t>(path - executableFilePath); ++path)
        *path = L'\0'; // ->> Zero out trailing storage with NUL terminators

        break; // ->> Preferable to shrink allocated `executableFilePath` storage to `fileNameLength + 1u` characters
      }
    }

    // ... ->> Update `renameFormat`
    if (NULL != commandLineArguments && static_cast<std::size_t>(commandLineArgumentsLength) > renameFormatIndex && renameFormatIndex != static_cast<std::size_t>(-1)) {
      if (renameFormatAllocated)
        (void) allocator.release((renameFormatLength + 1u) * sizeof(wchar_t), sizeof(wchar_t)); // --> renameFormat

      renameFormat          = commandLineArguments[renameFormatIndex];
      renameFormatAllocated = false;

      if (FAILED(::StringCchLengthW(renameFormat, STRSAFE_MAX_CCH, &renameFormatLength)))
        renameFormatLength = std::wcslen(renameFormat);
    }

    // ... ->> Set `renumerationDirectory` to a user-specified command-line argument
    if (NULL != commandLineArguments && commandLineArgumentsLength > 1) {
      std::size_t commandLineArgumentLength = 0u;

      // ...
      if (FAILED(::StringCchLengthW(commandLineArguments[1], STRSAFE_MAX_CCH, &commandLineArgumentLength)))
        commandLineArgumentLength = std::wcslen(commandLineArguments[1]);

      renumerationDirectoryLength = commandLineArgumentLength + subdirectorySuffixLength;
      renumerationDirectory       = ::new (allocator.allocate((renumerationDirectoryLength + 1u) * sizeof(TCHAR), sizeof(TCHAR), false)) TCHAR[renumerationDirectoryLength + 1u];

      // ...
      if (NULL == renumerationDirectory) {
        allocatorExhausted              = true;
        renumerationDirectoryRecognized = false;
      }

      else {
        renumerationDirectoryAllocated = true;

        // ...
        if (FAILED(::StringCchCopyNExW(static_cast<STRSAFE_LPWSTR>(renumerationDirectory), renumerationDirectoryLength, commandLineArguments[1], commandLineArgumentLength + 1u, static_cast<LPTSTR*>(NULL), static_cast<std::size_t*>(NULL), STRSAFE_FILL_BEHIND_NULL | STRSAFE_FILL_ON_FAILURE)))
          renumerationDirectory = std::wcsncpy(renumerationDirectory, commandLineArguments[1], commandLineArgumentLength + 1u);

        (void) ::LocalFree(commandLineArguments); // ->> Ideally successfully evaluates to `NULL`

        // ... ->> Modify `renumerationDirectory` to be a more Windows-compatible directory path
        for (LPTSTR directory = renumerationDirectory; ; ++directory) {
          if (L'\0' == *directory) {
            while (true) {
              if (*--directory == L'\\')
                *directory = L'\0'; // ->> Remove trailing backslashes

              else {
                ++directory;

                if (FAILED(::StringCchCatNExW(directory, (renumerationDirectoryLength + 1u) - (directory - renumerationDirectory), subdirectorySuffix, subdirectorySuffixLength, static_cast<LPTSTR*>(NULL), static_cast<std::size_t*>(NULL), STRSAFE_FILL_BEHIND_NULL | STRSAFE_FILL_ON_FAILURE)))
                  (void) std::wcsncat(directory, subdirectorySuffix, subdirectorySuffixLength);

                break;
              }

              // ...
              if (renumerationDirectory == directory)
              break;
            }

            if (NULL != renumerationDirectory && L'\0' == *renumerationDirectory) {
              (void) allocator.release((renumerationDirectoryLength + 1u) * sizeof(WCHAR), sizeof(WCHAR)); // --> renumerationDirectory

              renumerationDirectory           = NULL;
              renumerationDirectoryRecognized = false;
            }

            break;
          }

          if (*directory == L'/')
            *directory = L'\\'; // ->> Replace (forward) slashes with backslashes
        }
      }
    }

    // ... ->> Set `renumerationDirectory` otherwise to the current working directory
    if (NULL == renumerationDirectory) {
      DWORD const currentDirectoryLength = ::GetCurrentDirectory(0u, static_cast<LPTSTR>(NULL)); // ->> With NUL terminator

      // ...
      if (0u != currentDirectoryLength) {
        renumerationDirectoryLength = (currentDirectoryLength - 1u) + subdirectorySuffixLength;
        renumerationDirectory       = ::new (allocator.allocate((renumerationDirectoryLength + 1u) * sizeof(WCHAR), sizeof(WCHAR), false)) TCHAR[renumerationDirectoryLength + 1u];

        // ...
        if (NULL == renumerationDirectory)
          allocatorExhausted = true;

        else {
          renumerationDirectoryAllocated = true;

          if (0u != ::GetCurrentDirectory(currentDirectoryLength, renumerationDirectory)) {
            if (FAILED(::StringCchCatNExW(renumerationDirectory + (currentDirectoryLength - 1u), renumerationDirectoryLength - (currentDirectoryLength - 1u), subdirectorySuffix, subdirectorySuffixLength, static_cast<LPTSTR*>(NULL), static_cast<std::size_t*>(NULL), STRSAFE_FILL_BEHIND_NULL | STRSAFE_FILL_ON_FAILURE)))
            (void) std::wcsncat(renumerationDirectory + (currentDirectoryLength - 1u), subdirectorySuffix, subdirectorySuffixLength);
          }
        }
      }
    }

    // ... ->> Set `renumerationDirectory` otherwise to `defaultDirectory`
    if (NULL == renumerationDirectory) {
      renumerationDirectory          = const_cast<LPTSTR>(defaultDirectory);
      renumerationDirectoryAllocated = false;

      if (FAILED(::StringCchLengthW(renumerationDirectory, STRSAFE_MAX_CCH, &renumerationDirectoryLength)))
        renumerationDirectoryLength = (sizeof(defaultDirectory) / sizeof(TCHAR)) - 1u;
    }

    // ... ->> Enumerate files in `renumerationDirectory`
    filesystemRedirectionDisabled                                                 = FALSE != ::Wow64DisableWow64FsRedirection(&filesystemRedirection);
    renumerationDirectoryFindHandle                                               = ::FindFirstFileExW(renumerationDirectory, ::FindExInfoBasic, static_cast<LPVOID>(&renumerationDirectoryFindData), ::FindExSearchNameMatch, static_cast<LPVOID>(NULL), 0x00u);
    renumerationDirectory[renumerationDirectoryLength - subdirectorySuffixLength] = L'\0';

    // ...
    if (INVALID_HANDLE_VALUE == renumerationDirectoryFindHandle) {
      executableExitCode = EXIT_FAILURE;

      switch (::GetLastError()) {
        case ERROR_NOT_SUPPORTED: {
          if (false == quietRequested)
          (void) std::fprintf(stderr, renumerationDirectoryAllocated ? "%1.32s%1.21s%1.*ls%c" : "%1.32s%1.25s", "renum: Unable to filter through ", false == renumerationDirectoryAllocated ? "current working directory" : "specified directory \"", static_cast<int>(renumerationDirectoryLength - 2u), renumerationDirectory, '"');
        } break;

        case ERROR_PATH_NOT_FOUND: {
          if (false == quietRequested)
          (void) std::fprintf(stderr, "%1.41s%1.*ls%c", "renum: Could not find specified directory \"", static_cast<int>(renumerationDirectoryLength - 2u), renumerationDirectory, '"');
        } break;

        default:
          goto filePathsNonEnumerable;
      }
    }

    else {
      std::size_t filePathsBufferLength = 0u;

      // ...
      if (false == quietRequested) {
        (void) std::fprintf(stdout, "%1.29s%1.*ls%1.6s", "renum: Enumerating files in \"", static_cast<int>(renumerationDirectoryLength - subdirectorySuffixLength), renumerationDirectory, "\"..." "\r\n");
        (void) std::fflush(stdout);
      }

      while (true) {
        if (FALSE == ::FindNextFileW(renumerationDirectoryFindHandle, &renumerationDirectoryFindData)) {
          // ... ->> Enumerated all files
          if (ERROR_NO_MORE_FILES == ::GetLastError()) {
            filePaths = ::new (allocator.allocate(filePathsLength * sizeof(wchar_t*), sizeof(wchar_t*))) wchar_t*[filePathsLength];

            if (NULL == filePaths) allocatorExhausted = true;
            else                   break;
          }

          goto filePathsNonEnumerable;
        }

        // ... ->> Enumerate acceptable file
        if (FILE_ATTRIBUTE_NORMAL == renumerationDirectoryFindData.dwFileAttributes || false == (renumerationDirectoryFindData.dwFileAttributes & (
          FILE_ATTRIBUTE_DIRECTORY |
          FILE_ATTRIBUTE_TEMPORARY |
          (enumerateHiddenFiles ? 0x00u : FILE_ATTRIBUTE_HIDDEN) |
          (enumerateSystemFiles ? 0x00u : FILE_ATTRIBUTE_SYSTEM)
        ))) {
          std::size_t fileNameLength       = MAX_PATH;                                                                 // ->> With NUL terminator
          wchar_t    *filePathBuffer       = NULL != filePathsBuffer ? filePathsBuffer + filePathsBufferLength : NULL; //
          std::size_t filePathBufferLength = (renumerationDirectoryLength - subdirectorySuffixLength) + 1u;            // ->> With NUL terminator

          // ...
          ++filePathsLength;

          // ... --> fileNameLength = ...; filePathsBufferLength = ...;
          if (SUCCEEDED(::StringCchLengthW(renumerationDirectoryFindData.cFileName, MAX_PATH, &fileNameLength)))
            ++fileNameLength;

          else { // --> ::wcsnlen(renumerationDirectoryFindData.cFileName, MAX_PATH) + 1u;
            fileNameLength = 0u;

            for (WCHAR *fileName = renumerationDirectoryFindData.cFileName; MAX_PATH != fileNameLength; ++fileName) {
              ++fileNameLength;
              if (L'\0' == *fileName) break;
            }
          }

          filePathBufferLength  += fileNameLength - 1u;
          filePathsBufferLength += filePathBufferLength + 1u; // ->> With NUL delimiter

          // ... --> filePathsBuffer = ...; filePathsBufferSize = ...;
          if (NULL == filePathsBuffer) {
            filePathsBufferSize = filePathsBufferLength;
            filePathsBuffer     = ::new (allocator.allocate(filePathsBufferSize * sizeof(wchar_t), sizeof(wchar_t))) wchar_t[filePathsBufferSize];
            filePathBuffer      = filePathsBuffer;

            if (NULL == filePathsBuffer) {
              allocatorExhausted = true;
              goto filePathsNonEnumerable;
            }
          }

          else if (filePathsBufferLength > filePathsBufferSize) {
            unsigned char *reallocation = NULL;
            std::size_t    size         = 1u;

            // ...
            for (; size < filePathsBufferLength; size *= 2u)
            if (size >= SIZE_MAX / 2u) {
              allocatorExhausted = true;
              goto filePathsNonEnumerable;
            }

            while (NULL == reallocation) {
              reallocation = allocator.reallocate(filePathsBufferSize * sizeof(wchar_t), sizeof(wchar_t), size * sizeof(wchar_t), sizeof(wchar_t));

              if (NULL == reallocation) {
                std::size_t const delta = (size - filePathsBufferLength) / 2u;

                // ...
                if (allocator.invalidated || 0u == delta) {
                  allocatorExhausted = true;
                  goto filePathsNonEnumerable;
                }

                size -= delta;
              }
            }

            filePathsBuffer = reinterpret_cast<wchar_t*>(reallocation); // --> std::launder(reinterpret_cast<wchar_t*>(reallocation));

            for (wchar_t *buffer = filePathsBuffer + filePathsBufferSize; filePathsBufferSize != size; ++buffer, ++filePathsBufferSize)
            (void) ::new (buffer) wchar_t;
          }

          // ... --> filePathBuffer = ...;
          if (FAILED(::StringCchCopyNExW(static_cast<STRSAFE_LPWSTR>(filePathBuffer), filePathBufferLength, renumerationDirectory, renumerationDirectoryLength - subdirectorySuffixLength, static_cast<LPTSTR*>(NULL), static_cast<std::size_t*>(NULL), STRSAFE_FILL_BEHIND_NULL | STRSAFE_FILL_ON_FAILURE)))
            filePathBuffer = std::wcsncpy(filePathBuffer, renumerationDirectory, renumerationDirectoryLength - subdirectorySuffixLength);

          filePathBuffer[(renumerationDirectoryLength - subdirectorySuffixLength) + 0u] = L'\\';
          filePathBuffer[(renumerationDirectoryLength - subdirectorySuffixLength) + 1u] = L'\0';

          if (FAILED(::StringCchCatNExW(filePathBuffer + (renumerationDirectoryLength - subdirectorySuffixLength) + 1, fileNameLength, renumerationDirectoryFindData.cFileName, fileNameLength - 1u, static_cast<LPTSTR*>(NULL), static_cast<std::size_t*>(NULL), STRSAFE_FILL_BEHIND_NULL | STRSAFE_FILL_ON_FAILURE)))
            (void) std::wcsncat(filePathBuffer + (renumerationDirectoryLength - subdirectorySuffixLength) + 1, renumerationDirectoryFindData.cFileName, fileNameLength - 1u);

          filePathBuffer[((renumerationDirectoryLength - subdirectorySuffixLength) + (fileNameLength - 1u) + 1u) + 0u] = L'\0'; // ->> Terminate `filePathBuffer`  with NUL
          filePathBuffer[((renumerationDirectoryLength - subdirectorySuffixLength) + (fileNameLength - 1u) + 1u) + 1u] = L'\0'; // ->> Delimit   `filePathsBuffer` with NUL
        }
      }
    }

    // ...
    if (false) filePathsNonEnumerable: {
      executableExitCode = EXIT_FAILURE;

      if (false == quietRequested) {
        (void) (renumerationDirectoryAllocated
          ? std::fprintf(stderr, "%1.51s%1.*ls%c", "renum: Unable to enumerate through (all) files in \"", static_cast<int>(renumerationDirectoryLength - 2u), renumerationDirectory, '"')
          : std::fprintf(stderr, "%1.79s",         "renum: Unable to enumerate through (all) files in the current working directory")
        );

        if (allocatorExhausted)
          (void) std::fprintf(stderr, "%1.17s%s%1.6s", " (out of memory: ", allocator.size(), " used)");

        (void) std::fflush(stderr);
      }
    }

    // ... ->> Ideally successfully evaluates not to `FALSE` (for both function calls)
    if (filesystemRedirectionDisabled)                           (void) ::Wow64RevertWow64FsRedirection(filesystemRedirection);
    if (INVALID_HANDLE_VALUE != renumerationDirectoryFindHandle) (void) ::FindClose(renumerationDirectoryFindHandle);
  #else
    struct renumerator /* final */ {
      inline static int sort(void const* const, void const* const) /* noexcept = delete */;
    };

    /* ... */
    wchar_t const *const executableFilePath          = NULL; // ->> With NUL terminator(s)
    std::size_t    const executableFilePathLength    = 0u;   //
    wchar_t const *const renumerationDirectory       = NULL; //
    std::size_t    const renumerationDirectoryLength = 0u;   //

    // ...
    if (false == quietRequested)
      (void) std::fputs("renum: Unable to enumerate files", stderr);

    return EXIT_FAILURE;
  #endif

  // ... ->> Ensure `renameFormat` uses valid character sequences
  if (NULL == renameFormat) {
    executableExitCode = EXIT_FAILURE;
    (void) (renameFormatIndex != static_cast<std::size_t>(-1)
      ? std::fprintf(stderr, "%1.31s%s%1.11s", "renum: Unusable rename format \"", arguments[renameFormatIndex - 2u], "\" specified")
      : std::fputs("renum: Unusable rename format specified", stderr)
    );
  }

  for (wchar_t const *format = renameFormat, *renumerationSequence = NULL; ; ++format) {
    if (L'\0' == *format) {
      if (NULL == renumerationSequence) {
        executableExitCode = EXIT_FAILURE;

        if (false == quietRequested)
        (void) std::fprintf(stderr, "%1.22s%1.*ls%1.55s", "renum: Rename format \"", static_cast<int>(renameFormatLength), renameFormat, "\" must include either `?` or `??` character sequences" "\r\n");
      }

      break;
    }

    if (*(format + 0) != L'?') continue;
    if (*(format + 1) != L'?') { renumerationSequence = format;   continue; }
    if (*(format + 2) != L'?') { renumerationSequence = format++; continue; }

    format += 2;
  }

  // ... ->> Ensure `renameIndex` does not overflow past its maximum
  if (renameIndex > SIZE_MAX - filePathsLength) {
    executableExitCode = EXIT_FAILURE;

    if (false == quietRequested)
    (void) std::fprintf(stderr, "%1.19s%lu%1.68s%lu%1.34s%lu", "renum: File index (", static_cast<unsigned long>(renameIndex), ") would erroneously overflow given the number of encountered files (", static_cast<unsigned long>(filePathsLength), "); exceeding the maximum index of ", static_cast<unsigned long>(SIZE_MAX));
  }

  // ... ->> Ensure there are files to enumerate or rename
  if (0u == filePathsLength) {
    if (false == quietRequested)
    (void) std::fputs("\r\n" "renum: No files encountered.", stdout);
  }

  // ...
  if (EXIT_FAILURE != executableExitCode && 0u != filePathsLength) {
    // ... ->> Conditionally ascertain if the files enumerated from `renumerationDirectory` are intended to be renamed
    if (false == renumerationDirectoryRecognized) {
      (void) std::fprintf(stdout, "%1.43s%1.*ls%1.17s", "       " "Do you wish to rename the files in \"", static_cast<int>(renumerationDirectoryLength - subdirectorySuffixLength), renumerationDirectory, "\"? [Y]es / [N]o:" " ");
      (void) std::fflush(stdout);
    }

    for (unsigned char reprompted = 0u; ; ++reprompted) {
      if (false == renumerationDirectoryRecognized) {
        if (0u != reprompted) {
          // ... ->> Stop trying to ascertain ...
          if (reprompted > 10u) {
            (void) std::fputs("renum: Prompt received unrecognized replies. Terminating...", stdout);
            (void) std::fflush(stdout);

            break;
          }

          (void) std::fputs("       " "  please reply 'Y' (for \"Yes\") or 'N' (for \"No\") to rename files or not:" " ", stdout);
          (void) std::fflush(stdout);
        }

        for (bool promptReplied = false; ; promptReplied = true) {
          promptToken = std::fgetc(stdin); // ->> Assumed `\n` stored in `stdin` after `promptToken` is read

          if (0u == reprompted || promptReplied) break;
          if ('\n' == static_cast<char>(promptToken)) continue;
        }
      }

      // ...
      if ((false == renumerationDirectoryRecognized && EOF == promptToken) || static_cast<char>(promptToken) == 'N' || static_cast<char>(promptToken) == 'n') {
        executableExitCode = EXIT_FAILURE;
        break;
      }

      // ... ->> Prepare to rename all files
      if (renumerationDirectoryRecognized || static_cast<char>(promptToken) == 'Y' || static_cast<char>(promptToken) == 'y' || static_cast<char>(promptToken) == '\n') {
        // ... ->> Namespace featuring utilities for asserting/ evaluating `filePaths`
        struct renumerator_assert /* final */ {
          // ... ->> Convert NUL-terminated paths in `filePaths` to usable values for some file renaming function
          #if defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
            inline static wchar_t const* renamableof(wchar_t const filePath[], std::size_t* const size) /* noexcept */ {
              *size = std::wcslen(filePath);
              return filePath;
            }
          #else
            // ... ->> Similar code to `renumerator_format::convert(...)`
            inline static char const* renamableof(wchar_t const filePath[], std::size_t* const size) /* noexcept */ {
              std::mbstate_t     state             = {};
              char              *renamableFilePath = NULL;
              wchar_t     const *path              = filePath;
              std::mbstate_t     lengthState       = state;
              std::size_t const  length            = std::wcsrtombs(static_cast<char*>(NULL), &path, 0u, &lengthState);

              // ...
              *size = 0u;

              if (length == static_cast<std::size_t>(-1)) return NULL;
              renamableFilePath = reinterpret_cast<char*>(allocator.allocate(length + sizeof(char), sizeof(char), false));

              if (NULL == renamableFilePath) {
                allocatorExhausted = true;
                return NULL;
              }

              path  = filePath;
              *size = length / sizeof(char);

              // ...
              return length == std::wcsrtombs(renamableFilePath, &path, length + sizeof(char), &state) ? renamableFilePath : NULL;
            }
          #endif
        };

        /* ... */
        std::size_t fileExtensionMaximumLength = 0u;
        std::size_t fileNameMaximumLength      = 0u;
        bool        renamable                  = true;
        std::size_t renameIndexLength          = 0u;
        long double renameIndexThreshold       = static_cast<long double>(filePathsLength) / 10.0L;
        bool        renameLogged               = false;
        wchar_t    *renamePath                 = NULL;
        std::size_t renamePathLength           = 1u;
        std::time_t renameTimestamp            = std::time(static_cast<std::time_t*>(NULL));

        // ... --> fileNameMaximumLength = ...; filePaths[] = ...;
        for (wchar_t *buffer = filePathsBuffer, **paths = filePaths; L'\0' != *buffer; ++buffer, ++paths) {
          std::size_t    fileExtensionLength = 0u;
          std::size_t    fileNameLength      = 0u;
          wchar_t *const filePath            = buffer;

          // ... ->> Assume `filePath` is formatted as `renumerationDirectory\fileName.[fileExtension]`
          *paths  = filePath;
          buffer += std::wcslen(buffer);

          // ... --> fileExtensionLength = ...; fileNameLength = ...;
          for (wchar_t *subbuffer = buffer - 1; ; --subbuffer)
          if (filePath == subbuffer || *subbuffer == L'\\') {
            for (subbuffer += filePath != subbuffer; buffer != subbuffer; ++subbuffer) {
              if (*subbuffer == L'.') {
                while (buffer != ++subbuffer)
                  ++fileExtensionLength;

                break;
              }

              ++fileNameLength;
            }

            break;
          }

          // ... --> fileExtensionMaximumLength = ...; fileNameMaximumLength = ...;
          if (fileExtensionMaximumLength < fileExtensionLength) fileExtensionMaximumLength = fileExtensionLength;
          if (fileNameMaximumLength      < fileNameLength)      fileNameMaximumLength      = fileNameLength;
        }

        // ... --> renameIndexLength = ...; renamePathLength = ...;
        for (std::size_t length = filePathsLength + renameIndex; 0u != length; length /= 10u)
          ++renameIndexLength;

        for (wchar_t const *format = renameFormat; L'\0' != *format; ++format) {
          if      (*(format + 0) != L'?') { renamePathLength += 1u;                                 }
          else if (*(format + 1) != L'?') { renamePathLength += renameIndexLength;                  }
          else if (*(format + 2) != L'?') { renamePathLength += renameIndexLength;     format += 1; }
          else                            { renamePathLength += fileNameMaximumLength; format += 2; }
        }

        renamePathLength += fileExtensionMaximumLength + (renumerationDirectoryLength - subdirectorySuffixLength) + 1u;
        renamePath        = ::new (allocator.allocate((renamePathLength + 1u) * sizeof(wchar_t), sizeof(wchar_t))) wchar_t[renamePathLength + 1u];

        if (NULL == renamePath) {
          if (false == quietRequested)
            (void) std::fprintf(stderr, "%1.46s%s%1.6s", "renum: Unable to rename files (out of memory: ", allocator.size(), " used)");

          allocatorExhausted = true;
          executableExitCode = EXIT_FAILURE;

          break;
        }

        // ... ->> Lexicographically sort which enumerated files get renamed in order
        if (false == quietRequested) {
          (void) std::fputs("renum: Indexing files..." "\r\n", stdout);
          (void) std::fflush(stdout);
        }

        std::qsort(filePaths, filePathsLength, sizeof(wchar_t*), &renumerator::sort);

        // ... ->> Ensure that all enumerated files are renamable
        for (wchar_t **paths = filePaths; filePathsLength != static_cast<std::size_t>(paths - filePaths); ++paths) {
          #if defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
            // --> break
          #else
            std::size_t renamableFilePathLength = 0u;
            char const *renamableFilePath       = renumerator_assert::renamableof(*paths, &renamableFilePathLength);

            // ...
            if (NULL == renamableFilePath) {
              if (false == quietRequested) {
                (void) std::fprintf(stderr, "%1.30s%ls%1.3s", "renum: Unable to rename file \"", *paths, "\"" "\r\n");
                (void) std::fflush(stderr);
              }

              renamable = false;
            }

            else if (0u != renamableFilePathLength)
              (void) allocator.release(renamableFilePathLength, sizeof(char)); // --> renamableFilePath
          #endif
        }

        if (false == renamable) {
          (void) std::fputs("\r\n" "renum: Unable to rename all files.", stderr);
          executableExitCode = EXIT_FAILURE;

          break;
        }

        // ... ->> Rename all enumerated files; Errors can not be undone until the loop is completed
        if (false == quietRequested) {
          (void) std::fputs("renum: Renaming files..." "\r\n\n", stdout);
          (void) std::fflush(stdout);
        }

        // ... ->> Produce faster error diagnostics ideally
        if (false == quietRequested) {
          std::size_t const stderrBufferSize = filePathsLength * (94u + fileExtensionMaximumLength + fileNameMaximumLength + renamePathLength + 1u);
          char       *const stderrBuffer     = reinterpret_cast<char*>(allocator.allocate(stderrBufferSize * sizeof(char), sizeof(char), false));

          // ...
          if (NULL != stderrBuffer) {
            if (0 != std::setvbuf(stderr, stderrBuffer, _IOFBF, BUFSIZ))
            (void) allocator.release(stderrBufferSize * sizeof(char), sizeof(char)); // --> stderrBuffer
          }
        }

        for (wchar_t **paths = filePaths; filePathsLength != static_cast<std::size_t>(paths - filePaths); ++paths, ++renameIndex) {
          wchar_t    *const filePath      = *paths;
          std::size_t const filePathIndex = static_cast<std::size_t>(paths - filePaths) + 1u;
          std::time_t const logTimestamp  = static_cast<std::time_t>(3); // ->> Possibly 3 calendar seconds
          std::time_t const timestamp     = std::time(static_cast<std::time_t*>(NULL));

          // ... ->> Do not rename executable
          if (NULL != executableFilePath && 0 == std::wcscmp(executableFilePath, filePath))
          continue;

          // ... ->> Format `renamePath`; File directory
          renamePath                                                         = std::wcsncpy(renamePath, renumerationDirectory, renumerationDirectoryLength - subdirectorySuffixLength);
          renamePath[renumerationDirectoryLength - subdirectorySuffixLength] = L'\\';
          renamable                                                          = true;

          for (wchar_t *format = const_cast<wchar_t*>(renameFormat), *path = renamePath + (renumerationDirectoryLength - subdirectorySuffixLength) + 1; ; ++format) {
            // ... ->> File extension
            if (L'\0' == *format) {
              wchar_t *subpath = filePath;

              // ...
              while (L'\0' != *subpath)
                ++subpath;

              while (filePath != --subpath)
              if (*subpath == L'.') {
                while (L'\0' != *subpath)
                  *(path++) = *(subpath++);

                break;
              }

              *path = L'\0';
              break;
            }

            // ... ->> File path
            if (*format != L'?')
              *(path++) = *format;

            else if (*(format + 1) != L'?') {
              std::size_t indexLength = 0u;

              // ...
              if (0u == renameIndex) indexLength = 1u;
              else for (std::size_t index = renameIndex; 0u != index; index /= 10u) ++indexLength;

              for (std::size_t index = renameIndex, length = indexLength; 0u != length; index /= 10u)
                path[--length] = L"0123456789"[index % 10u];

              path += indexLength;
            }

            else if (*(format + 2) != L'?') {
              for (std::size_t index = renameIndex, length = renameIndexLength; 0u != length; index /= 10u)
                path[--length] = L"0123456789"[index % 10u];

              ++format;
              path += renameIndexLength;
            }

            else {
              wchar_t *subpath = filePath;

              // ...
              while (L'\0' != *subpath)
                ++subpath;

              while (filePath != --subpath)
              if (*subpath == L'\\') break;

              for (subpath += filePath != subpath; ; ++subpath) {
                if (L'\0' == *subpath || *subpath == L'.') break;
                *(path++) = *subpath;
              }

              format += 2;
            }
          }

          // ... ->> Rename file
          #if defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
            struct renumerator_rename /* final */ {
              wchar_t const *filePath;
              wchar_t const *renamePath;
              std::size_t    filePathIndex;
              std::size_t    filePathsLength;
              std::time_t    logTimestamp;
              std::time_t    renameTimestamp;

              /* ... */
              inline static DWORD CALLBACK onprogress(LARGE_INTEGER const fileSize, LARGE_INTEGER const transferSize, LARGE_INTEGER const, LARGE_INTEGER const, DWORD const, DWORD const, HANDLE const, HANDLE const, LPVOID const data) /* noexcept */ {
                if (false == quietRequested) {
                  renumerator_rename &renameData = *static_cast<renumerator_rename*>(data);
                  std::time_t  const  timestamp  = std::time(static_cast<std::time_t*>(NULL));

                  // ...
                  if (timestamp != static_cast<std::time_t>(-1)) {
                    if (renameData.renameTimestamp == static_cast<std::time_t>(-1))
                      renameData.renameTimestamp = timestamp;

                    else if (renameData.logTimestamp < timestamp - renameData.renameTimestamp) {
                      std::size_t    ratio = 0u;
                      ULARGE_INTEGER size  = {0u, 0u};

                      // ...
                      if (fileSize.HighPart >= 0L && transferSize.HighPart >= 0L)
                      while (SIZE_MAX != ratio) {
                        unsigned char carry                  = 0u;
                        DWORD         sizeSegments        [] = {size.HighPart, size.LowPart};
                        DWORD const   transferSizeSegments[] = {static_cast<DWORD>(transferSize.HighPart), transferSize.LowPart};

                        // ... --> size += transferSize
                        for (unsigned char index = 2u; index--; )
                        for (unsigned char rank = 0u; rank != CHAR_BIT * sizeof(DWORD); ++rank) {
                          unsigned char const sizeDigit         = (sizeSegments        [index] >> rank) & 1u;
                          unsigned char const transferSizeDigit = (transferSizeSegments[index] >> rank) & 1u;

                          // ...
                          if (0u != carry || 0u != sizeDigit || 0u != transferSizeDigit) {
                            carry                = 0u != sizeDigit && 0u != transferSizeDigit;
                            sizeSegments[index] |= (0u == carry) << rank;
                          }
                        }

                        ++ratio;
                        size.HighPart = sizeSegments[0];
                        size.LowPart  = sizeSegments[1];

                        // ...
                        if (0u == size.HighPart && 0u == size.LowPart) {
                          ratio = 0u != transferSize.HighPart || 0u != transferSize.LowPart;
                          break;
                        }

                        if (static_cast<DWORD>(fileSize.HighPart) <= size.HighPart || fileSize.LowPart <= size.LowPart)
                          break;
                      }

                      renameData.renameTimestamp = timestamp;

                      // ...
                      (void) (fileSize.HighPart < 0L || transferSize.HighPart < 0L
                        ? std::fprintf(stdout, "%1.7s%s%1.9s" "%0.2Lf" "%1.3s%lu%1.3s%lu%1.8s%1.*ls%1.6s%1.*ls%c", "renum: ", renameData.filePathIndex == 1u ? "" : "  ", "Renaming ", (0u != ratio ? 1.00L / static_cast<long double>(ratio) : 0.00L) * 100.0L, "% (", static_cast<unsigned long>(renameData.filePathIndex), " / ", static_cast<unsigned long>(renameData.filePathsLength), ") done \"", static_cast<int>(std::wcslen(renameData.filePath) - 2u), renameData.filePath, "\" to \"", static_cast<int>(std::wcslen(renameData.renamePath) - 2u), renameData.renamePath, '"')
                        : std::fprintf(stdout, "%1.7s%s%1.9s" "%1.3s"  "%1.3s%lu%1.3s%lu%1.8s%1.*ls%1.6s%1.*ls%c", "renum: ", renameData.filePathIndex == 1u ? "" : "  ", "Renaming ", "???",                                                                    "% (", static_cast<unsigned long>(renameData.filePathIndex), " / ", static_cast<unsigned long>(renameData.filePathsLength), ") done \"", static_cast<int>(std::wcslen(renameData.filePath) - 2u), renameData.filePath, "\" to \"", static_cast<int>(std::wcslen(renameData.renamePath) - 2u), renameData.renamePath, '"')
                      ), std::fflush(stdout);
                    }
                  }
                }

                return PROGRESS_CONTINUE;
              }
            };

            /* ... */
            std::size_t        filePathLength = 0u;
            renumerator_rename renameData     = {filePath, renamePath, filePathIndex, filePathsLength, renameTimestamp, logTimestamp};

            // ...
            for (wchar_t *subpaths[] = {filePath, renamePath}, **path = subpaths; path != subpaths + (sizeof(subpaths) / sizeof(wchar_t*)); ++path) {
              for (wchar_t *destination = *path; ; ++destination)
              if (L'\0' == *destination) {
                #if false // ->> The documentation says prepend, but does not seem to work
                  for (wchar_t *source = destination + 2; ; --destination, --source) {
                    *source = *destination;

                    if (destination == *path) {
                      *--source = L'?';
                      *--source = L'\\';

                      break;
                    }
                  }
                #endif

                #if false // ->> This appends instead, otherwise `filePath` and `renamePath` may be restricted to `MAX_PATH` characters overall
                  *(destination++) = L'\\';
                  *(destination++) = L'?';
                  *destination     = L'\0';
                #endif

                break;
              }
            }

            renamable = FALSE != ::MoveFileWithProgressW(renumerator_assert::renamableof(filePath, &filePathLength), renumerator_assert::renamableof(renamePath, &renamePathLength), static_cast<LPPROGRESS_ROUTINE>(&renumerator_rename::onprogress), static_cast<LPVOID>(&renameData), MOVEFILE_WRITE_THROUGH);
          #else
            std::size_t       renamableFilePathLength   = 0u;
            char const *const renamableFilePath         = renumerator_assert::renamableof(filePath, &renamableFilePathLength);
            std::size_t       renamableRenamePathLength = 0u;
            char const *const renamableRenamePath       = renumerator_assert::renamableof(renamePath, &renamableRenamePathLength);

            // ...
            renamable = NULL != renamableFilePath && NULL != renamableRenamePath;
            renamable = renamable && 0 == std::rename(renamableFilePath, renamableRenamePath);

            if (0u != renamableFilePathLength)   (void) allocator.release((renamableFilePathLength   + 1u) * sizeof(char), sizeof(char)); // --> renamableFilePath
            if (0u != renamableRenamePathLength) (void) allocator.release((renamableRenamePathLength + 1u) * sizeof(char), sizeof(char)); // --> renamableRenamePath
          #endif

          // ... ->> Log progress
          if (
            // ->> Error
            false == renamable ||

            // ->> Progress
            filePathIndex > renameIndexThreshold                    || // ->> Enough files renamed to be logged
            (renameLogged && filePathIndex == filePathsLength - 1u) || // ->> Last file renamed to be logged
            static_cast<std::size_t>(renameIndexThreshold) == 1u    || // ->> Likely to log first file, anyway
            (                                                          // ->> Enough time elapsed to log
              renameTimestamp != static_cast<std::time_t>(-1) &&
              timestamp       != static_cast<std::time_t>(-1) &&
              logTimestamp < timestamp - renameTimestamp
            )
          ) {
            long double const renameCompletionRate = (static_cast<long double>(filePathIndex) / static_cast<long double>(filePathsLength)) * 100.0L;

            // ...
            if (false == quietRequested) (void) (renamable
              ? std::fflush(stderr), std::fprintf(stdout, "%1.7s%0.2Lf%1.3s%lu%1.3s%lu%1.17s%ls%1.6s%ls%1.3s", "renum: ", renameCompletionRate, "% (", static_cast<unsigned long>(filePathIndex), " / ", static_cast<unsigned long>(filePathsLength), ") done. Renamed \"", filePath, "\" to \"", renamePath, "\"" "\r\n"), std::fflush(stdout)
              : std::fprintf(stderr, "%1.7s%0.2Lf%1.3s%lu%1.3s%lu%1.26s%ls%1.6s%ls%1.3s", "renum: ", renameCompletionRate, "% (", static_cast<unsigned long>(filePathIndex), " / ", static_cast<unsigned long>(filePathsLength), ") done. Unable to rename \"", filePath, "\" to \"", renamePath, "\"" "\r\n")
            );

            renameIndexThreshold += static_cast<long double>(filePathsLength) / 10.0L;
            renameLogged          = true;
            renameTimestamp       = timestamp;
          }

          if (renameTimestamp == static_cast<std::time_t>(-1) && timestamp != static_cast<std::time_t>(-1))
            renameTimestamp = timestamp;
        }

        // ...
        if (false == quietRequested) (void) std::fputs("\r\n" "renum: Files renamed.", stdout);
        if (NULL != renamePath) (void) allocator.release((renamePathLength + 1u) * sizeof(char), sizeof(char)); // --> renamePath

        break;
      }
    }
  }

  // ... ->> Release allocated memory
  if (NULL != filePaths)              (void) allocator.release(filePathsLength                    * sizeof(wchar_t*),               sizeof(wchar_t*));               // --> filePaths
  if (NULL != filePathsBuffer)        (void) allocator.release(filePathsBufferSize                * sizeof(wchar_t),                sizeof(wchar_t));                // --> filePathsBuffer
  if (executableFilePathAllocated)    (void) allocator.release(executableFilePathLength           * sizeof(*executableFilePath),    sizeof(*executableFilePath));    // --> executableFilePath
  if (renumerationDirectoryAllocated) (void) allocator.release((renumerationDirectoryLength + 1u) * sizeof(*renumerationDirectory), sizeof(*renumerationDirectory)); // --> renumerationDirectory
  if (renameFormatAllocated)          (void) allocator.release((renameFormatLength + 1u)          * sizeof(wchar_t),                sizeof(wchar_t));                // --> renameFormat

  // ...
  return executableExitCode;
}
