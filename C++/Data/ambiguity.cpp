void put(void) {}
void put(...) {}
void put(int = 0) {}

void put(signed char, signed long) {}
void put(signed long, signed char) {}

/* Main */
int main(void) {
  put();
  put(0, 0);
}
