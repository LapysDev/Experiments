#include <stdio.h>

#define BIT_8(n) n, "is lower or equal than 8"
#define BIT_N(n) n, "is greater than 8"

// Identify values less than 8; make the second argument 8
#define LT_8_0 ~,8
#define LT_8_1 ~,8
#define LT_8_2 ~,8
#define LT_8_3 ~,8
#define LT_8_4 ~,8
#define LT_8_5 ~,8
#define LT_8_6 ~,8
#define LT_8_7 ~,8
#define LT_8_8 ~,8

// Helper macros.  Delays let arguments be processed before the macros is run.
#define MERGE(A, B) A ## B
#define MERGE_DELAY(A, B) MERGE(A,B)
#define ARG2(A,B,...) B
#define ARG2_DELAY(A,B,...) ARG2(A,B,__VA_ARGS__)

// Return 8 or N depending if n <= 8...
#define LT_8(n) ARG2_DELAY( MERGE(LT_8_, n), N,~ )

#define BIT(n) MERGE_DELAY(BIT_, LT_8(n))(n)

int main() {
  printf("%d %s\n", BIT(9));
  return 0;
}
