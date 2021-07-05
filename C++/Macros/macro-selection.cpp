#include <cstdio>

/* ... */
#define concatenate(a, b) a ## b
#define defer(macro, ...) macro(__VA_ARGS__)

#define select(x) defer(concatenate, select_, defer(second, select_ ## x, fail, ~))(x)
# define select_pass(x) "`" #x "`\tpassed selection"
# define select_fail(x) "`" #x "`\tfailed selection"
#   define select_literally ~, pass
#   define select_anything  ~, pass

#define second(a, b, ...) b

/* Main */
int main(void) {
  std::printf("[...]: \"%s\"" "\r\n", select(literally));
  std::printf("[...]: \"%s\"" "\r\n", select(anything)) ;

  std::printf("[...]: \"%s\"" "\r\n", select(probably));
  std::printf("[...]: \"%s\"" "\r\n", select(nothing)) ;

  std::printf("[...]: \"%s\"" "\r\n", select(pass));
  std::printf("[...]: \"%s\"" "\r\n", select(fail));
}
