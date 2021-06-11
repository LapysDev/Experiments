#include <cstdio>
#include <cstdlib>

#include <bit>

/* ... -> (Ideally compile-time) `return` array generated within the function. */
int (&GetHeapArray(void))[2] {
  // Post-C++ 20 version: `new` is not compile-time(?)
  return *std::bit_cast<int (*)[2]>(
    new int[2] {0x45, -420}
  );

  // Pre-C++ 20 version: `reinterpret_cast` is not compile-time
  return *reinterpret_cast<int (*)[2]>(
    // ⚠ Requires C++11 and after
    new int[2] {0x45, -420}
  ); // deleted on process termination

  // C version: `malloc(...)` is not compile-time
  return *static_cast<int (*)[2]>(
    // ⚠ un-initialized
    std::malloc(sizeof(int [2]))
  ); // destroyed on process termination
}

static void const* GetReinterpretedArray(void) {
  static union array {
    public: int value[2] = {0x45, -420};
  } const array = {};

  // destroyed on process termination
  return const_cast<void*>(static_cast<void const*>(&array));
}

static int (&GetStackArray(void))[2] {
  static int array[2] = {0x45, -420};
  return array; // destroyed on process termination
}

// ⚠ Requires C++14 and after
static auto GetStructureArray(void) {
  struct array final {
    private: typedef int (&type)[2];
    public:
      int value[2] = {0x45, -420};

      // pretend to be an array reference
      operator type(void) { return this -> value; }
  } const array = {};

  // persists data via copy
  return array;
}

/* Main */
int main(void) {
  std::printf("Heap Array (ref.)          : [%i, %i]" "\r\n", GetHeapArray()[0], GetHeapArray()[1]);
  std::printf("Stack Array (ref.)         : [%i, %i]" "\r\n", GetStackArray()[0], GetStackArray()[1]);

  std::printf("Structure Array            : [%i, %i]" "\r\n", GetStructureArray()[0], GetStructureArray()[1]);
  std::printf("Re-interpreted Array (ref.): [%i, %i]" "\r\n",
    (*static_cast<int const (*)[2]>(GetReinterpretedArray()))[0],
    (*static_cast<int const (*)[2]>(GetReinterpretedArray()))[1]
  );

  // ...
  return EXIT_SUCCESS;
}
