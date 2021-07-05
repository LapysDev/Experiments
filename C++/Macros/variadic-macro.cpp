#include <cstdio>

/* ... */
#define variadic(...) variadic_select(~, __VA_ARGS__, variadic_n, variadic_3, variadic_2, variadic_1, variadic_0)(__VA_ARGS__)
#define variadic_select(argument0, argument1, argument2, argument3, argument4, macro, ...) macro

#define variadic_0()                                "[]: no arguments"
#define variadic_1(argument)                        "[" #argument "]: 1 argument"
#define variadic_2(argument1, argument2)            "[" #argument1 ", " #argument2 "]: 2 arguments"
#define variadic_3(argument1, argument2, argument3) "[" #argument1 ", " #argument2 ", " #argument3 "]: 3 arguments"
#define variadic_n(...)                             "[" #__VA_ARGS__ "]: variable arguments"

/* Main */
int main(void) {
    std::puts(variadic());
    std::puts(variadic(A));
    std::puts(variadic(A, B));
    std::puts(variadic(A, B, C));
    std::puts(variadic(A, B, C, D));
}
