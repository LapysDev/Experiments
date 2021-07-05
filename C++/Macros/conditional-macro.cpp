#include <cstdio>

/* ... */
#define boolean(x) negate(negate(x))

#define check(x, pass, fail) check_select(boolean(x))(pass, fail)
# define check_select(x) concatenate(check_select_, x)
#   define check_select_0(pass, fail)     fail
#   define check_select_false(pass, fail) fail
#   define check_select_1(pass, fail)     pass
#   define check_select_true(pass, fail)  pass

#define concatenate(a, b) a ## b

#define negate(x) negate_select(concatenate(negate_select_, x), 0)
# define negate_select(...) second(__VA_ARGS__, 0)
#   define negate_select_0 ~, 1

#define second(a, b, ...) b

/* Main */
int main(void) {
    std::printf("[0] : %s" "\r\n", check(0 , "true", "false"));
    std::printf("[1] : %s" "\r\n", check(1 , "true", "false"));
    std::printf("[69]: %s" "\r\n", check(69, "true", "false"));
}
