#include <stdint.h>
#include <cstdio>

/* Main */
int main(void) {
  uint16_t composited = 0u;
  uint8_t segmented[2] = {0u, 0u};

  while (composited != UINT8_MAX * 2u) {
    std::printf("[composited]: %hu" "\r\n", composited);
    std::printf("[segmented] : %hu" "\r\n", (segmented[0] << 0u) | (segmented[1] << 8u));
    std::puts("");

    ++composited;

    segmented[1] += 255u == segmented[0];
    segmented[0] += 1u;
  }
}
