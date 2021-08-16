#include <stdarg.h>
#include <stdio.h>

// Stops printing at 0
void puts(int argument...) {
  va_list arguments;
  va_start(arguments, argument);

  do printf("[%i]", argument);
  while (argument = va_arg(arguments, int));

  va_end(arguments);
}

int main(void) { puts(42, 69, 420, 1337, 0); }
