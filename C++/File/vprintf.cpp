#include <stdarg.h>
#include <stdio.h>

void WriteFormatted(char const* const format = "[...]\r\n", ...) {
    va_list arguments;

    va_start(arguments, format);
    ::vfprintf(stdout, format, arguments);
    va_end(arguments);
}

int main(void) {
    WriteFormatted();
    WriteFormatted("Call with 0 variable arguments.\r\n");
    WriteFormatted("Call with %u variable argument.\r\n", 1u);
    WriteFormatted("Call with %u variable %s.\r\n", 2u, "arguments");
}
