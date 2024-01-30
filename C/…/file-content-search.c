#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Main */
int main(int const count, char* const arguments[]) {
  if (count < 3) {
    switch (count) {
      case 1: fputs("Usage: [search file] [search string] [[options]]", stderr); break;
      case 2: fputs("Error: Missing search string", stderr); break;
    }

    exit(EXIT_FAILURE);
  }

  else {
    FILE *const file = fopen(arguments[1], "rb");
    char const *const string = arguments[2];
    enum option_t {
      NONE = 0x0,
      CASE_INSENSITIVE = 0x1
    } option = NONE;

    // ...
    if (NULL == file) {
      fprintf(stderr, "Could not search the file \"%s\"", arguments[1]);
      exit(EXIT_FAILURE);
    }

    else {
      size_t column = 0u;
      size_t index  = 0u;
      size_t line   = 1u;

      // ...
      if (count > 3) {
        for (
          struct {
            char const *const string;
            enum option_t const value;
          } const options[] = {
            {"-i", CASE_INSENSITIVE},
            {"--insensitive", CASE_INSENSITIVE}
          }, *iterator = options + (sizeof options / sizeof *options);
          iterator-- != options;
        ) for (char const *argument = arguments[3], *subiterator = iterator -> string; ; ++argument, ++subiterator) {
          if (*argument != *subiterator) break;

          if ('\0' == *subiterator) { option |= CASE_INSENSITIVE; break; }
          if ('\0' == *argument) break;
        }
      }

      for (size_t count = 0u; ; ) {
        char const character = fgetc(file);

        // ...
        if (EOF == character) {
          fprintf(stdout, "\n" "%u %smatches for \"%s\" found", count, option & CASE_INSENSITIVE ? "(case-insensitive)" " " : "", string);
          break;
        }

        if ('\n' != character) ++column;
        else { column = 0u; ++line; }

        // ...
        if (0u != index) {
          if ('\0' == string[index]) {
            fprintf(stdout, "Match found in [line %u, column %u]" "\r\n", line, column - index);

            ++count;
            index = 0u;
          }

          else if (
            option & CASE_INSENSITIVE
            ? tolower(character) != tolower(string[index])
            : character != string[index]
          )
            index = 0u;

          else
            ++index;
        }

        if (
          option & CASE_INSENSITIVE
          ? tolower(character) == tolower(string[0])
          : character == string[0]
        ) index = 1u;
      }

      // ...
      fclose(file);
    }
  }

  return EXIT_SUCCESS;
}
