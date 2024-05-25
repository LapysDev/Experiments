/* Import */
#include <math.h> // Mathematics
#include <stdlib.h> // Standard Library

/* Constant > (Indeterminate, Infinity, Not-A-Number) --- REDACT (Lapys) */
struct { public:
  inline operator double(void) const noexcept {
    static unsigned long const indeterminateBitRepresentation[2] = {0x00000000, 0xFFF80000}; // NOTE (Lapys) -> IEEE-754 hexadecimal form.
    return *((double const*) indeterminateBitRepresentation);
  }
} const Indeterminate;

struct { public:
  constexpr inline operator float(void) const noexcept {
    #ifdef INFINITY
        return INFINITY;
    #elif defined(HUGE_VAL)
        return HUGE_VAL;
    #endif
  }
} const Infinity;

struct { public: constexpr inline operator float(void) const noexcept { return NAN; } } const NaN;

/* Main */
int main(void) {
  // Return
  return EXIT_SUCCESS;
}
