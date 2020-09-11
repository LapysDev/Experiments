#include <stdio.h>
int main() {
  for (int i = 0; i ^ 50; ++i)
  printf("%02X ", ((char*) main)[i] & 0xFF);
}
