/* gcc link.c link.s -no-pie -g -o link.exe */
#include <stdio.h>
#include <stdlib.h>

extern int put(void);
int main(int const count, char const* const arguments[]) { put(); return EXIT_SUCCESS; }
