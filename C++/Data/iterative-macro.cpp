#include <cstdio>

/* ... */
#define concatenate(argument1, argument2) argument1 ## argument2
#define defer(macro, ...) macro(__VA_ARGS__)
#define empty()
#define second(argument1, argument2, ...) argument2

#define repeat(...) repeat_setup(__VA_ARGS__, until, until, ~)
# define repeat_begin(function, separator, condition, argument, next, ...) \
  defer(concatenate, repeat_condition_is_, condition(argument, next, __VA_ARGS__))(repeat_continue, repeat_end)( \
    function, \
    defer(concatenate, repeat_condition_is_, condition(next, __VA_ARGS__))(separator, repeat_separator), \
    repeat_stall(repeat_recurse)()(function, separator, condition, next, __VA_ARGS__, ~), \
    argument, next, __VA_ARGS__ \
  )
# define repeat_condition(argument, ...) defer(concatenate, repeat_condition_, defer(second, repeat_condition_found_ ## argument, pass, ~))(argument)
#   define repeat_condition_accept(condition)   condition
#   define repeat_condition_fallback(condition) repeat_condition
#   define repeat_condition_fail(argument) false
#   define repeat_condition_pass(argument) true
#   define repeat_condition_is_false(truthy, falsy) falsy
#   define repeat_condition_is_true(truthy, falsy)  truthy
#     define repeat_condition_found_until       ~, fail
#     define repeat_condition_selection_default ~, fallback
# define repeat_continue(function, separator, repeater, argument, ...) function(argument) separator(argument, __VA_ARGS__) repeater
# define repeat_end(function, separator, repeater, argument, ...)
# define repeat_function(argument) argument
#   define repeat_function_accept(function)   function
#   define repeat_function_fallback(function) repeat_function
#     define repeat_function_selection_default ~, fallback
# define repeat_parse(...) repeat_parse_12(__VA_ARGS__)
#   define repeat_parse_1(...)  __VA_ARGS__
#   define repeat_parse_2(...)  repeat_parse_1(repeat_parse_1(__VA_ARGS__))
#   define repeat_parse_3(...)  repeat_parse_2(repeat_parse_2(__VA_ARGS__))
#   define repeat_parse_4(...)  repeat_parse_3(repeat_parse_3(__VA_ARGS__))
#   define repeat_parse_5(...)  repeat_parse_4(repeat_parse_4(__VA_ARGS__))
#   define repeat_parse_6(...)  repeat_parse_5(repeat_parse_5(__VA_ARGS__))
#   define repeat_parse_7(...)  repeat_parse_6(repeat_parse_6(__VA_ARGS__))
#   define repeat_parse_8(...)  repeat_parse_7(repeat_parse_7(__VA_ARGS__))
#   define repeat_parse_9(...)  repeat_parse_8(repeat_parse_8(__VA_ARGS__))
#   define repeat_parse_10(...) repeat_parse_9(repeat_parse_9(__VA_ARGS__))
#   define repeat_parse_11(...) repeat_parse_10(repeat_parse_10(__VA_ARGS__))
#   define repeat_parse_12(...) repeat_parse_11(repeat_parse_11(__VA_ARGS__))
# define repeat_separator(...)
#   define repeat_separator_accept(separator)   separator
#   define repeat_separator_fallback(separator) repeat_separator
#     define repeat_separator_selection_default ~, fallback
# define repeat_setup(function, condition, separator, ...) repeat_parse(repeat_begin( \
  defer(concatenate, repeat_function_ , defer(second, repeat_function_selection_  ## function , accept, ~))(function ), \
  defer(concatenate, repeat_separator_, defer(second, repeat_separator_selection_ ## separator, accept, ~))(separator), \
  defer(concatenate, repeat_condition_, defer(second, repeat_condition_selection_ ## condition, accept, ~))(condition), \
  __VA_ARGS__ \
))
# define repeat_stall(argument) repeat_stall_12(argument)
#   define repeat_stall_1(argument)  argument empty()
#   define repeat_stall_2(argument)  argument empty empty()()
#   define repeat_stall_3(argument)  argument empty empty empty()()()
#   define repeat_stall_4(argument)  argument empty empty empty empty()()()()
#   define repeat_stall_5(argument)  argument empty empty empty empty empty()()()()()
#   define repeat_stall_6(argument)  argument empty empty empty empty empty empty()()()()()()
#   define repeat_stall_7(argument)  argument empty empty empty empty empty empty empty()()()()()()()
#   define repeat_stall_8(argument)  argument empty empty empty empty empty empty empty empty()()()()()()()()
#   define repeat_stall_9(argument)  argument empty empty empty empty empty empty empty empty empty()()()()()()()()()
#   define repeat_stall_10(argument) argument empty empty empty empty empty empty empty empty empty empty()()()()()()()()()()
#   define repeat_stall_11(argument) argument empty empty empty empty empty empty empty empty empty empty empty()()()()()()()()()()()
#   define repeat_stall_12(argument) argument empty empty empty empty empty empty empty empty empty empty empty empty()()()()()()()()()()()()
# define repeat_recurse() repeat_begin

/* Main */
#define add(...) +
#define pass(integer) integer

int main() {
  std::printf("[]: %i" "\r\n", repeat(pass, default, add) + 0u);
  std::printf("[]: %i" "\r\n", repeat(pass, default, add, 1u) + 0u);
  std::printf("[]: %i" "\r\n", repeat(pass, default, add, 1u, 1u) + 0u);
  std::printf("[]: %i" "\r\n", repeat(pass, default, add, 1u, 1u, 1u) + 0u);
}
