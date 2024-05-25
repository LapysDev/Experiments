int randint(int begin = 0, int end = 10) {
  srand(rand()); // is this pointless when done multiple times?
  return begin + ((static_cast<double>(rand()) / (1.0 + RAND_MAX)) * ((end - begin) + 1));
}

/* Main */
int main() {
  for (unsigned count = 10u; count; --count)
  printf("[]: %i\n", randint());
}
