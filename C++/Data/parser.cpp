// • UTF-32 little-endian with Byte Order Mark (U+FEFF) {0xFF, 0xFE, 0x00, 0x00} -> zero-width no-break space
// • UTF-32 big-endian    with Byte Order Mark (U+FEFF) {0x00, 0x00, 0xFE, 0xFF} -> zero-width no-break space
// • UTF-16 big-endian    with Byte Order Mark (U+FEFF) {0xFE, 0xFF}             -> zero-width no-break space
// • UTF-16 little-endian with Byte Order Mark (U+FEFF) {0xFF, 0xFE}             -> zero-width no-break space
// • UTF-8                with Byte Order Mark (U+FEFF) {0xEF, 0xBB, 0xBF}       -> U+2060
// • Western (Windows 1252)
// • UTF-8
// • UTF-16 system endian
// • UTF-32
// • ASCII
#include <climits>
#include <cstddef>
#include <cstdio>
#include <version>

/* ... */
#if __cpp_constexpr >= 201304L
  constexpr
#endif
inline char const /* volatile */* parse(
  char const /* volatile */ source[],
  char       /* volatile */ target[],
  std::size_t (*const previousTokens)[2] = NULL
) /* noexcept */ {
  enum {
    nop = 0x00u,
    add,
    bitwise_and, bitwise_or, bitwise_xor,
    boolean_and, boolean_or,
    compare, complement,
    divide,
    equals,
    left_shift,
    greater, greater_equals,
    lesser, lesser_equals,
    minus, modulo, multiply,
    negate,
    plus,
    right_shift,
    subtract,
    ternary_check,
    unequals
  } const precedence[] = {multiply, divide, modulo, add, subtract, left_shift, right_shift, compare, lesser, lesser_equals, greater, greater_equals, equals, unequals, bitwise_and, bitwise_xor, bitwise_or, boolean_and, boolean_or, ternary_check};

  char const *const reservedTokens[] = {"function", "mod", "rem", "var", "!", "%", "&", "*", "+", "-", "/", ":", "<", "=", ">", "?", "^", "{", "|", "}", "~", " ", "\f", "\n", "\r", "\t", "\v", "«", "»", "×", "÷", "≠", "≤", "≥"};
  std::size_t       tokens[2][1024]  = {};
  std::size_t       tokenCount       = 0u;

  /* ... */
  if (NULL == source)
  return "global _start\nsection .text\n  _start:\n    mov eax, 0x1\n    mov bx, 0x0\n    int 0x80\n";

  // (-((1 + 5) * 2 % 3 - 2))^5-1

  for (char const /* volatile */ *iterator = source; '\0' != *iterator; ++iterator)
  for (char const *const *reservedToken = reservedTokens; reservedToken != reservedTokens + (sizeof(reservedTokens) / sizeof(char const*)); ++reservedToken) {
    std::size_t token[2] = {iterator - source, 0u};

    // ...
    for (char const *subiteratorA = iterator, *subiteratorB = *reservedToken; *subiteratorA == *subiteratorB; ++subiteratorA, ++subiteratorB)
    if ('\0' == *subiteratorB) {
      token[1] = subiteratorB - *reservedToken;
      switch (**reservedToken) {
        case ' ': case '\f': case '\n': case '\r': case '\t': case '\v': {
          for (bool whitespace = true; whitespace; )
          switch (*iterator) {
            case ' ': case '\f': case '\n': case '\r': case '\t': case '\v':
              ++iterator;
              ++token[1];

              break;

            default:
              whitespace = false;
          }
        }
      }

      break;
    }

    iterator += token[1] - (0u != token[1]);
  }

  // ...
  return target;
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  constexpr char const *parsed = parse(NULL, NULL);
  std::fputs(parsed, stdout);

  return 0x0;
}
