#include <cstdio>

/* ... */
#define concatenate(argument1, argument2) argument1 ## argument2
#define defer(macro, ...) macro(__VA_ARGS__)
#define first(argument, ...) argument
#define second(argument1, argument2, ...) argument2

#define map(...) map_parse(map_begin(__VA_ARGS__))
# define map_arity_fail(...)
# define map_arity_pass(...) __VA_ARGS__
# define map_begin(function, separator, argument, ...) function(argument) map_check(map_separator, first(map_niladic_check __VA_ARGS__)())(separator) map_check(map_arity, first(map_niladic_check __VA_ARGS__)())(map_stall(map_recurse)()(function, separator, __VA_ARGS__))
# define map_check(macro, argument) defer(concatenate, macro ## _, defer(second, concatenate(map_check_, argument), pass))
#   define map_check_fail ~, fail
#   define map_check_pass
# define map_niladic_check() fail
# define map_parse(...) map_parse_8(__VA_ARGS__)
#   define map_parse_1(...) __VA_ARGS__
#   define map_parse_2(...)  map_parse_1(map_parse_1(__VA_ARGS__))
#   define map_parse_3(...)  map_parse_2(map_parse_2(__VA_ARGS__))
#   define map_parse_4(...)  map_parse_3(map_parse_3(__VA_ARGS__))
#   define map_parse_5(...)  map_parse_4(map_parse_4(__VA_ARGS__))
#   define map_parse_6(...)  map_parse_5(map_parse_5(__VA_ARGS__))
#   define map_parse_7(...)  map_parse_6(map_parse_6(__VA_ARGS__))
#   define map_parse_8(...)  map_parse_7(map_parse_7(__VA_ARGS__))
#   define map_parse_9(...)  map_parse_8(map_parse_8(__VA_ARGS__))
#   define map_parse_10(...) map_parse_9(map_parse_9(__VA_ARGS__))
#   define map_parse_11(...) map_parse_10(map_parse_10(__VA_ARGS__))
#   define map_parse_12(...) map_parse_11(map_parse_11(__VA_ARGS__))
# define map_separator_fail(separator)
# define map_separator_pass(separator) separator()
# define map_stall(argument) map_stall_8(argument)
# define map_stall_null()
#   define map_stall_1(argument)  argument map_stall_null()
#   define map_stall_2(argument)  argument map_stall_null map_stall_null()()
#   define map_stall_3(argument)  argument map_stall_null map_stall_null map_stall_null()()()
#   define map_stall_4(argument)  argument map_stall_null map_stall_null map_stall_null map_stall_null()()()()
#   define map_stall_5(argument)  argument map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null()()()()()
#   define map_stall_6(argument)  argument map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null()()()()()()
#   define map_stall_7(argument)  argument map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null()()()()()()()
#   define map_stall_8(argument)  argument map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null()()()()()()()()
#   define map_stall_9(argument)  argument map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null()()()()()()()()()
#   define map_stall_10(argument) argument map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null()()()()()()()()()()
#   define map_stall_11(argument) argument map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null()()()()()()()()()()()
#   define map_stall_12(argument) argument map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null map_stall_null()()()()()()()()()()()()
# define map_recurse() map_begin

/* Main */
#define greet(name) "Hello, \"" #name "\"!" "\r\n"
# define space()
#define square(literal) (literal * literal)
# define plus() +
#define stringify(argument) #argument
# define comma() ,

int main() {
  std::printf("%s, %s", map(stringify, comma, Hello, number:));
  std::printf(" %i" "\r\n\n", map(square, plus, 1, 2, 3, 4));
  std::printf("%s", map(greet, space, C++, GD:Script, Visual Basic));
}
