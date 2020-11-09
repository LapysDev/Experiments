#include <limits.h>
#include <stddef.h>
#include <stdio.h>

enum class ARENA_FORMAT { BINARY, CHARACTER };
static unsigned char arena[sizeof(char*) + sizeof(size_t)];

void put(ARENA_FORMAT const format) {
  for (unsigned char const *iterator = arena, *end = iterator + (sizeof(arena) / sizeof(unsigned char)); end > iterator; ) {
    ::putchar('['); switch (format) {
      case ARENA_FORMAT::BINARY: {
        unsigned char data = *iterator;

        char string[(CHAR_BIT * sizeof(unsigned char)) + /* NUL */ sizeof(char)] = {0};
        char *iterator = string + (sizeof(string) / sizeof(char));

        for (--iterator; data; data >>= 1u) *--iterator = data & 1u ? '1' : '0';
        while (iterator != string) *--iterator = '0';

        ::printf("%s", string);
      } iterator = (unsigned char*) (1 + (unsigned char*) iterator); break;

      case ARENA_FORMAT::CHARACTER: {
        char const data = *iterator;

        switch (data) {
          case '\a': ::printf("%s", "\\a"); break;
          case '\b': ::printf("%s", "\\b"); break;
          case '\f': ::printf("%s", "\\f"); break;
          case '\n': ::printf("%s", "\\n"); break;
          case '\r': ::printf("%s", "\\r"); break;
          case '\t': ::printf("%s", "\\t"); break;
          case '\v': ::printf("%s", "\\v"); break;
          case '\0': ::printf("%s", "\\0"); break;
          case '\1': ::printf("%s", "\\1"); break;
          case '\2': ::printf("%s", "\\2"); break;
          case '\3': ::printf("%s", "\\3"); break;
          case '\4': ::printf("%s", "\\4"); break;
          case '\5': ::printf("%s", "\\5"); break;
          case '\6': ::printf("%s", "\\6"); break;
          case '\16': ::printf("%s", "\\16"); break;
          case '\17': ::printf("%s", "\\17"); break;
          case '\20': ::printf("%s", "\\20"); break;
          case '\21': ::printf("%s", "\\21"); break;
          case '\22': ::printf("%s", "\\22"); break;
          case '\23': ::printf("%s", "\\23"); break;
          case '\24': ::printf("%s", "\\24"); break;
          case '\25': ::printf("%s", "\\25"); break;
          case '\26': ::printf("%s", "\\26"); break;
          case '\27': ::printf("%s", "\\27"); break;
          case '\u0018': ::printf("%s", "\\u0018"); break;
          case '\u0019': ::printf("%s", "\\u0019"); break;
          case '\u001A': ::printf("%s", "\\u001A"); break;
          case '\u001B': ::printf("%s", "\\e"); break;
          case '\u001C': ::printf("%s", "\\u001C"); break;
          case '\u001D': ::printf("%s", "\\u001D"); break;
          case '\u001E': ::printf("%s", "\\u001E"); break;
          case '\u001F': ::printf("%s", "\\u001F"); break;
          case '\u007F': ::printf("%s", "\\u007F"); break;
          case '\\': ::printf("%s", "\\"); break;
          default: ::putchar(data); break;
        }
      } iterator = (unsigned char*) (1 + (char*) iterator); break;
    } ::putchar(']');
  }

  ::printf("\r\n");
}

int main(void) {
  size_t &length = *(size_t*) (1 + (char const**) + arena);
  char const *&string = (char const*&) arena;

  put(ARENA_FORMAT::CHARACTER); length = 13u, string = "Hello, World!";
  put(ARENA_FORMAT::CHARACTER); ::printf("[... (%zu)]: %.*s" "\r\n", length, (int) length, string);

  put(ARENA_FORMAT::CHARACTER); length = 11u, string = "Lorem ipsum";
  put(ARENA_FORMAT::CHARACTER); ::printf("[... (%zu)]: %.*s" "\r\n", length, (int) length, string);

  put(ARENA_FORMAT::CHARACTER); length = 296u, string = "\"The Extremes of Good and Evil\": But I must explain to you how all this mistaken idea of denouncing pleasure and praising pain was born and I will give you a complete account of the system, and expound the actual teachings of the great explorer of the truth, the master-builder of human happiness.";
  put(ARENA_FORMAT::CHARACTER); ::printf("[... (%zu)]: %.*s" "\r\n", length, (int) length, string);
}
