#include <cfloat>
#include <ciso646>
#include <cstdio>
#include <stdint.h>

/* ... */
long double truncate(long double const number) {
  long double truncation = 1.00L;

  // ...
  if (number <  0.00L)                             return -truncate(-number);
  if (number != number or number == 1.00L / 0.00L) return number;
  if (number <= UINTMAX_MAX)                       return static_cast<uintmax_t>(number);

  // ... ->> Count up to `number` in multiples of `truncation`
  for (long double rate = 1.00L; number > truncation; ) {
    long double const increment = truncation / rate;

    // ...
    if (increment < 1.00L or increment != truncate(increment))
      break;

    if (truncation <= LDBL_MAX - increment) {
      if (number < truncation + increment)
        break;

      truncation += increment;
      continue;
    }

    rate *= 2.00L;
  }

  // ... ->> Count up to `number` in multiples of two where `rate >= 1.00L`
  for (long double rate = 1.00L; number != truncation; ) {
    while (truncation == truncation + rate or (number > truncation + rate and rate <= LDBL_MAX / 2.00L))
      rate *= 2.00L;

    while (number < truncation + rate and rate > 1.00L)
      rate /= 2.00L;

    if (number < truncation + rate)
      break;

    truncation += rate;
  }

  // ...
  return truncation;
}

/* Main */
#include <cmath>
#include <cstdlib>
#include <ctime>

int main(int, char*[]) /* noexcept */ {
  std::time_t timestamp        = std::time(static_cast<std::time_t*>(NULL));
  std::time_t timestampCurrent = timestamp;

  // ...
  std::srand(timestamp);

  for (long double integer = UINTMAX_MAX, end = LDBL_MAX; integer <= end; ) {
    long double const mantissa   = (static_cast<long double>(std::rand() % RAND_MAX) / RAND_MAX) / 10.00L;
    long double const next       = std::truncl(std::nextafterl(integer, HUGE_VALL));
    long double const number     = integer + mantissa;
    long double const truncation = truncate(number);

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

    integer += next >= 1.00L ? next : 1.00L;
  }

  std::fprintf(stdout, "%1.4s", "done");
}
