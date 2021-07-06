#include <cstdio>

/* ... */
#define concatenate(argument1, argument2) argument1 ## argument2
#define defer(macro, ...) macro(__VA_ARGS__)
#define second(argument1, argument2, ...) argument2

#define select(argument) defer(concatenate, select_, defer(second, select_ ## argument, fail, ~))(argument)
# define select_fail(argument) "`" #argument "`\tfailed selection"
# define select_pass(argument) "`" #argument "`\tpassed selection"
#   define select_anything  ~, pass
#   define select_literally ~, pass

/* Main */
int main(void) {
    std::printf("[...]: \"%s\"" "\r\n", select(anything)) ;
    std::printf("[...]: \"%s\"" "\r\n", select(literally));

    std::printf("[...]: \"%s\"" "\r\n", select(nothing)) ;
    std::printf("[...]: \"%s\"" "\r\n", select(probably));

    std::printf("[...]: \"%s\"" "\r\n", select(fail));
    std::printf("[...]: \"%s\"" "\r\n", select(pass));
}
