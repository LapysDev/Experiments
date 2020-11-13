/* ... */
#include <stdio.h>
#include <string.h>

/* File, Number, String */
static struct {
  char content[7] = {0};
  char name[L_tmpnam + 5 + 5] = "log [";
  FILE *stream = NULL;
} file = {};
static double number = 0.00;
static char string[24] = {0};

/* Main */
int main(void) {
  /* File Initialization */ {
    // Name
    file.name[5] = '0'; // ::tmpnam(file.name + 5);
    ::strcat(file.name, "].log");

    // Stream
    file.stream = ::fopen(file.name, "w+");

    // Content
    ::fwrite("1.234a", sizeof(char), 6u, file.stream);
    ::rewind(file.stream); // -> ::fseek(file.stream, 0L, SEEK_SET);
    ::fread(file.content, sizeof(char), 6u, file.stream);
  }

  /* File Information */ {
    ::printf("[File Content]: `%s`" "\r\n", file.content);
    ::printf("[File Name]: \"%s\"" "\r\n", file.name);
    ::printf("[File Stream]: %p" "\r\n", (void*) file.stream);
  } ::putchar('\n');

  /* ... */ {
    ::rewind(file.stream);
    ::fscanf(file.stream, "%lf", &number);
    ::fscanf(file.stream, "%s", string);

    ::printf("[File End Reached]: %s" "\r\n", ::feof(file.stream) ? "true" : "false");
    ::printf("[Number]: %lf" "\r\n", number);
    ::printf("[String]: \"%s\"" "\r\n", string);
  } ::putchar('\n');

  /* File Clean-up */
  ::fclose(file.stream);
  ::remove(file.name);
}
