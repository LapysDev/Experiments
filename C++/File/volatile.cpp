#include <cstdio>
#include <cstdlib>

int volatile number = 2;
char const target[] = "number";

int main(int const, char* arguments[]) {
  std::FILE *const file = std::fopen(arguments[0], "rb");

  if (NULL == file) {
    std::perror("could not open executable");
    std::exit(EXIT_FAILURE);
  }

  else {
    long const length = (std::fseek(file, 0L, SEEK_END), std::ftell(file));
    char *const text = static_cast<char*>(std::malloc((length + 1L) * sizeof(char)));

    if (NULL == text) {
      std::perror("could not read executable");
      std::exit(EXIT_FAILURE);
    }

    else {
      // ...
      std::fseek(file, 0L, SEEK_SET);
      std::fread(text, sizeof(char), length, file);

      text[length] = '\0';

      // ...
      std::printf("searching: \r\n```\r\n%.*s\r\n```\r\n", static_cast<int>(length), text);

      // ...
      for (char *iterator = text; length != text - iterator; ++iterator) {
        char const *subiterator = target;

        while ('\0' != *subiterator) {
          if (*iterator != *subiterator) {
            while (subiterator != target)
            --iterator, --subiterator;

            break;
          }

          ++iterator, ++subiterator;
        }

        // ...
        if ('\0' == *subiterator) {
          std::puts("target found");
          std::exit(EXIT_SUCCESS);
        }
      }

      // ...
      std::puts("target not found");
    }
  }

  return EXIT_SUCCESS;
}
