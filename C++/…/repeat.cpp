#define concatenate(a, b) a ## b
#define defer(macro, a, b) macro(__VA_ARGS__, a, b)
#define repeat(expressions) struct { inline void invoke() const { for (expressions)
#define until } } const defer(concatenate, repeater, __LINE__); defer(concatenate, repeater, __LINE__).invoke();

/* Main */
int main() {
  // basic
  repeat (int i = 0; i < 3; i++) continue; until

  // scoped
  repeat (int i = 0; i < 3; i++) {
    break; return;
  } until

  // nested
  repeat (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      break;
      return;
    }
  } until
}
