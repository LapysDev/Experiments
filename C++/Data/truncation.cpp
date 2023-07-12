#include <cfloat>
#include <ciso646>
#include <cstdio>
#include <stdint.h>

/* ... */
long double trunc(long double /*const*/ number) {
  long double characteristics = 1.00L;

  // ...
  if (number <  0.00L)                             return -trunc(-number);
  if (number != number or number == 1.00L / 0.00L) return number;
  if (number <  1.00L)       return 0.00L;
  // if (number <= UINTMAX_MAX) return static_cast<uintmax_t>(number);

  // ... ->> Count up to `number` in multiples of `characteristics`
  for (long double rate = 1.00L; characteristics < number; ) {
    long double const increment = characteristics / rate;

    // ...
    if (increment < 1.00L or increment != static_cast<unsigned long long>/*trunc*/(increment))
      break;

    if (characteristics <= FLT_MAX /* ... */ - increment) {
      if (number < characteristics + increment)
        break;

      characteristics += increment;
      continue;
    }

    rate *= 2.00L;
  }

  // ... ->> Count up to `number` in multiples of two (`rate`)
  for (long double rate = 1.00L; ; rate = 1.00L) {
    while (characteristics == characteristics + rate or (number > characteristics + rate and rate <= LDBL_MAX / 2.00L))
      rate *= 2.00L;

    rate /= number < characteristics + rate ? 2.00L : 1.00L;
    if (number <= characteristics + rate) break;

    std::printf("[>]: %Lf %Lf %Lf" "\r\n", characteristics, number, rate);
    characteristics += rate;
  }

  // still lesser, now what?

  // ...
  return characteristics;
}

/* Main */
#include <cstdlib>
#include <ctime>

int main(int, char*[]) /* noexcept */ {
  bool const test = false;

  // ...
  std::printf("[...]: %Lf" "\r\n", static_cast<long double>(FLT_MAX));
  std::printf("[...]: %Lf" "\r\n", trunc(FLT_MAX));

  if (test) {
    std::time_t timestamp        = std::time(static_cast<std::time_t*>(NULL));
    std::time_t timestampCurrent = timestamp;

    // ...
    std::srand(timestamp);

    for (long double integer = UINTMAX_MAX, end = LDBL_MAX; integer <= end; ++integer) {
      long double const mantissa   = (static_cast<long double>(std::rand() % RAND_MAX) / RAND_MAX) / 10.00L;
      long double const number     = integer + mantissa;
      long double const truncation = trunc(number);

      // ...
      timestamp = timestamp == static_cast<std::time_t>(-1) ? std::time(static_cast<std::time_t*>(NULL)) : timestamp;

      if (timestamp != static_cast<std::time_t>(-1)) {
        timestampCurrent = std::time(static_cast<std::time_t*>(NULL));

        if (timestampCurrent != static_cast<std::time_t>(-1) and std::difftime(timestampCurrent, timestamp) > 1.50L) {
          (void) std::fprintf(stdout, "%1.10s%Lf%1.10s", "inspected ", integer, " numbers" "\r\n");
          timestamp = timestampCurrent;
        }
      }

      if (integer != truncation)
      (void) std::fprintf(stdout, "%1.8s%Lf%1.11s%Lf%1.3s%Lf%1.5s%Lf%1.2s", "inspect ", number, "; expected ", integer, " + ", mantissa, " got ", truncation, "\r\n");
    }

    std::fprintf(stdout, "%1.4s", "done");
  }
}
