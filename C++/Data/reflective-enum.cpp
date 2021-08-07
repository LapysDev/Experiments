#include <cstdio>

/* ... */
#define concatenate(argument1, argument2) argument1 ## argument2
#define count(...) ( \
    count_arity(__VA_ARGS__, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, ~) + \
    count_niladic(first(count_arity __VA_ARGS__)(~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, ~, fail)) \
)
# define count_arity(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, _125, count, ...) count
# define count_niladic(argument) defer(second, concatenate(count_niladic_, argument), 1)
#   define count_niladic_fail ~, 0
#define defer(macro, ...) macro(__VA_ARGS__)
#define first(argument, ...) argument
#define second(argument1, argument2, ...) argument2

// ...
#define reflenum(name)                               \
  struct name {                                      \
    private:                                         \
      int value;                                     \
                                                     \
    public:                                          \
      name() : value() {}                            \
      name(int const value) : value(value) {}        \
                                                     \
      operator int() const { return this -> value; } \
  reflenum_definition

# define reflenum_cast(item) static_cast<void>(item)
# define reflenum_definition(...)                                                    \
    private:                                                                         \
      static unsigned char const COUNT  = count(__VA_ARGS__);                        \
      static unsigned long const LENGTH = sizeof(#__VA_ARGS__) / sizeof(char const); \
                                                                                     \
    public:                                                                          \
      enum { __VA_ARGS__ };                                                          \
                                                                                     \
                                                                                     \
      static unsigned char countItems() {                                            \
        return COUNT;                                                                \
      }                                                                              \
                                                                                     \
      static char const (&getItemNames())[COUNT + 1][LENGTH] {                       \
        char const source[] = #__VA_ARGS__, *begin = source, *end = source;          \
        static char items[COUNT + 1][LENGTH] = {};                                   \
                                                                                     \
        for (char (*iterator)[LENGTH] = items; ; ++end)                              \
        if (',' == *end || '\0' == *end) {                                           \
          char *item = *iterator;                                                    \
                                                                                     \
          while (' ' == *begin || '\n' == *begin) ++begin;                           \
          while (begin != end) {                                                     \
            if (                                                                     \
              '=' == *begin ||                                                       \
              ' ' == *begin || '\n' == *begin                                        \
            ) { *item = '\0'; break; }                                               \
            *(item++) = *(begin++);                                                  \
          }                                                                          \
                                                                                     \
          begin = end + 1; ++iterator;                                               \
          if ('\0' == *end) { (*iterator)[0] = '\0'; break; }                        \
        }                                                                            \
                                                                                     \
        return const_cast<char const (&)[COUNT + 1][LENGTH]>(items);                 \
      }                                                                              \
                                                                                     \
      static int const (&getItemValues())[COUNT + 1] {                               \
        static int items[COUNT + 1] = {0};                                           \
        static int& index = items[COUNT];                                            \
                                                                                     \
        index = 0; {                                                                 \
          struct pseudo_enum {                                                       \
            pseudo_enum() { items[index] = items[index - 1] + 1; ++index; }          \
            pseudo_enum(int const value) { items[index++] = value; }                 \
                                                                                     \
            void operator ,(int const) const {}                                      \
            void operator ,(pseudo_enum const) const {}                              \
          } __VA_ARGS__;                                                             \
                                                                                     \
          reflenum_cast(__VA_ARGS__, 0);                                             \
        }                                                                            \
                                                                                     \
        return const_cast<int const (&)[COUNT + 1]>(items);                          \
      }                                                                              \
  }

/* Main */
reflenum (Color)(RED = -1, GREEN, BLUE = 0x45, TRANSPARENT);

int main() {
  Color const color = Color();

  // ... -> can't be used in `switch` statements
  std::printf("[enum Color()]: %i" "\r\n", static_cast<int>(color)); // some unspecified value

  std::printf("%17s", "[enum Color  ]: {");
    for (unsigned char iterator = 0u, length = Color::countItems(); iterator != length; ++iterator)
    std::printf("%s = %i" "%s", Color::getItemNames()[iterator], Color::getItemValues()[iterator], iterator == length - 1u ? "" : ", ");
  std::printf("%3s", "}" "\r\n");

  std::printf("[enum Color::RED        ]: %i" "\r\n", static_cast<int>(Color::RED));
  std::printf("[enum Color::GREEN      ]: %i" "\r\n", static_cast<int>(Color::GREEN));
  std::printf("[enum Color::BLUE       ]: %i" "\r\n", static_cast<int>(Color::BLUE));
  std::printf("[enum Color::TRANSPARENT]: %i" "\r\n", static_cast<int>(Color::TRANSPARENT));
}
