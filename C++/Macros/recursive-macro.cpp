#include <cstdio>

/* ... */
#define boolean(argument) is_probe(concatenate(boolean_select_, argument))
#define boolean_select_0 ~, 0

#define check(argument) check_select(boolean(argument))
#define check_select(argument) concatenate(check_select_, argument)
#define check_select_0(...)
#define check_select_1(...) __VA_ARGS__

#define concatenate(a, b) a ## b

#define defer1(x) x empty()
#define defer2(x) x empty empty()()
#define defer3(x) x empty empty empty()()()
#define defer4(x) x empty empty empty empty()()()()

#define empty()

#define first(a, ...) a
#define second(a, b, ...) b

#define evaluate(...)     evaluate1024(__VA_ARGS__)
#define evaluate1024(...) evaluate512(evaluate512(__VA_ARGS__))
#define evaluate512(...)  evaluate256(evaluate256(__VA_ARGS__))
#define evaluate256(...)  evaluate128(evaluate128(__VA_ARGS__))
#define evaluate128(...)  evaluate64(evaluate64(__VA_ARGS__))
#define evaluate64(...)   evaluate32(evaluate32(__VA_ARGS__))
#define evaluate32(...)   evaluate16(evaluate16(__VA_ARGS__))
#define evaluate16(...)   evaluate8(evaluate8(__VA_ARGS__))
#define evaluate8(...)    evaluate4(evaluate4(__VA_ARGS__))
#define evaluate4(...)    evaluate2(evaluate2(__VA_ARGS__))
#define evaluate2(...)    evaluate1(evaluate1(__VA_ARGS__))
#define evaluate1(...)    __VA_ARGS__

#define is_probe(...) second(__VA_ARGS__, 1)

#define has_arguments(...) boolean(first(argument_end __VA_ARGS__)())
#define argument_end() 0

#define map(function, argument, ...) function(argument) check(has_arguments(__VA_ARGS__)) (defer2(map_recurse)()(function, __VA_ARGS__))
#define map_recurse() map

/* Main */
#define greet(name) "Hello, \"" #name "\"!" "\r\n"

int main(void) {
    std::printf("%s", evaluate(map(greet, C++, GD:Script, Visual Basic)));
}
