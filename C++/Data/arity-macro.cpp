#define concatenate(argument1, argument2) argument1 ## argument2
#define defer(macro, ...) macro(__VA_ARGS__)
#define second(argument1, argument2, ...) argument2

#define arity(count) defer(concatenate, arity_, defer(second, arity_check_ ## count, fail, ~))(count)
# define arity_fail(count)
# define arity_pass(count) concatenate(arity_, count)
#   define arity_0
#   define arity_1 1
#   define arity_2 2, arity_1
#   define arity_3 3, arity_2
#   define arity_4 4, arity_3
#   define arity_5 5, arity_4
#   define arity_6 6, arity_5
#   define arity_7 7, arity_6
#   define arity_8 8, arity_7

#   define arity_check_1 ~, pass
#   define arity_check_2 ~, pass
#   define arity_check_3 ~, pass
#   define arity_check_4 ~, pass
#   define arity_check_5 ~, pass
#   define arity_check_6 ~, pass
#   define arity_check_7 ~, pass
#   define arity_check_8 ~, pass
