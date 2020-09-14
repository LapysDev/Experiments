#include <stdarg.h>
#include <stdio.h>

void put(int numbers...) {
    va_list arguments;
    va_start(arguments, numbers);

    for (int argument = numbers; 0x0 != argument; argument = va_arg(arguments, int))
    ::printf("[%i]", argument);

    va_end(arguments);
}

template <class... types>
void put_packed(types... arguments) { put(arguments...); }

int main(void) { put_packed(1, 3, 3, 7, 0x0); }
