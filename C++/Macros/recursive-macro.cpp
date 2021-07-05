// #include <cstdio>

// /* ... */
// #define boolean(x) negate(negate(x))
// #define concatenate(a, b) a ## b

// #define defer1(x) x empty()
// #define defer2(x) x empty empty()()
// #define defer3(x) x empty empty empty()()()
// #define defer4(x) x empty empty empty empty()()()()

// #define empty()

// #define first(a, ...) a
// #define second(a, b, ...) b

// #define evaluate(...)     evaluate1024(__VA_ARGS__)
// #define evaluate1024(...) evaluate512(evaluate512(__VA_ARGS__))
// #define evaluate512(...)  evaluate256(evaluate256(__VA_ARGS__))
// #define evaluate256(...)  evaluate128(evaluate128(__VA_ARGS__))
// #define evaluate128(...)  evaluate64(evaluate64(__VA_ARGS__))
// #define evaluate64(...)   evaluate32(evaluate32(__VA_ARGS__))
// #define evaluate32(...)   evaluate16(evaluate16(__VA_ARGS__))
// #define evaluate16(...)   evaluate8(evaluate8(__VA_ARGS__))
// #define evaluate8(...)    evaluate4(evaluate4(__VA_ARGS__))
// #define evaluate4(...)    evaluate2(evaluate2(__VA_ARGS__))
// #define evaluate2(...)    evaluate1(evaluate1(__VA_ARGS__))
// #define evaluate1(...)    __VA_ARGS__

// #define is_probe(...) second(__VA_ARGS__, 0)
// #define probe() ~, 1

// #define negate(x) is_probe(concatenate(negate_select_, x))
// #define negate_select_0 probe()

// #define check(condition) check_select(boolean(condition))
// #define check_select(condition) concatenate(check_select_, condition)

// #define check_select_0(...)
// #define check_select_1(...) __VA_ARGS__

// #define has_arguments(...) boolean(first(argument_end __VA_ARGS__)())
// #define argument_end() 0

// #define map(m, first, ...) m(first) check(has_arguments(__VA_ARGS__))(defer2(map_recurse)()(m, __VA_ARGS__))
// #define map_recurse() map

// #define function(x) "Hello, \"" #x "\"!" "\r\n"

// /* Main */
// int main(void) {
//     std::printf("%s", evaluate(map(function, C++, GD:Script, Visual Basic)));
// }

#include <cstdio>

/* ... */
#define argument_end() 0
#define boolean(x) negate(negate(x))
#define concatenate(a, b, ...) a ## b
#define first(a, ...) a
#define has_arguments(...) boolean(first(argument_end __VA_ARGS__)())

#define negate(x) negate_select(concatenate(negate_select_, x), 0)
# define negate_select(...) second(__VA_ARGS__, 0)
#   define negate_select_0 ~, 1

#define second(a, b, ...) b

// ...
#define IIF(c) concatenate(IIF_, has_arguments(__VA_ARGS__))
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t

#define variadic(...) variadic_select(__VA_ARGS__, variadic_n, variadic_3, variadic_2, variadic_1, variadic_0)(__VA_ARGS__)
# define variadic_select(argument0, argument1, argument2, argument3, argument4, macro, ...) macro
#   define variadic_0()                                "[]: no arguments"
#   define variadic_1(argument)                        "[" #argument "]: 1 argument"
#   define variadic_2(argument1, argument2)            "[" #argument1 ", " #argument2 "]: 2 arguments"
#   define variadic_3(argument1, argument2, argument3) "[" #argument1 ", " #argument2 ", " #argument3 "]: 3 arguments"
#   define variadic_n(...)                             "[" #__VA_ARGS__ "]: variable arguments"

/* Main */
int main(void) {
    std::printf("%s" "\r\n", IIF(has_arguments())("true", "false"));
    std::printf("%s" "\r\n", IIF(has_arguments(A))("true", "false"));
    std::printf("%s" "\r\n", IIF(has_arguments(A, B))("true", "false"));
    std::printf("%s" "\r\n", IIF(has_arguments(A, B, C))("true", "false"));
    std::printf("%s" "\r\n", IIF(has_arguments(A, B, C, D))("true", "false"));
}
