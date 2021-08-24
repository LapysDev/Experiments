/* Import */
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library

/*
template <class type, class... types>
void* alloc(types... arguments) {
  void *const allocation = malloc(sizeof(type));

  new (allocation) type {arguments...};
  return allocation;
}
*/

/* Class > Pointer */
class Pointer {
    // [...]
    private:
        // Definition > Value
        void *value;

    // [...]
    public:
        // [Constructor]
        constexpr inline Pointer(void* argument) : value{argument} {}
        constexpr inline Pointer(void) : value{0x0} {}

        // [Operator] > [...]
        constexpr inline operator void*(void) const noexcept { return this -> value; }
};

/* Function > Print */
void printp(Pointer*& pointers, const unsigned char pointersLength = 5u) noexcept {
    // Loop
    for (unsigned char iterator = 0u, length = pointersLength; iterator ^ length; iterator++) {
        // Initialization > Pointer
        Pointer& pointer = *(pointers + iterator);

        // Print
        ::printf(pointer ? "%p" : "%s", (char*) (pointer ? pointer : "null"));
        ::printf("%s", iterator == length - 1u ? "]" : ", ");
    }
}

/* Main */
int main(void) {
    /* Global > Pointers
            --- NOTE ---
                #Lapys:
                    - The first set of numbers will be heap-allocated using the C standard library function `malloc`.
                    - The remaining set of numbers will be heap-allocated using the C++ `new` operator.
    */
    // : Initialization >  Pointer
    Pointer *pointers[3] {0x0, 0x0, 0x0};
    void *pointer = (void*) "";

    // Update > Pointers
    pointers[0] = (Pointer*) std::malloc(3u * sizeof(Pointer));
    pointers[1] = (Pointer*) std::calloc(5u, sizeof(Pointer));
    pointers[2] = new Pointer[3] {pointer, pointer, pointer};

    // Print
    ::printf("%s%p", "[Main]: ", pointer);
    ::putchar('\n'); ::putchar('\n'); ::putchar('\n'); ::putchar('\r');

        // [Allocated Only]
        ::printf("%s", "[Pointers] (Allocated only):               [");
        ::printp(pointers[0], 3u); ::putchar('\n'); ::putchar('\r');

        // [Allocated and Zero-Initialized]
        ::printf("%s", "[Pointers] (Allocated & Zero-Initialized): [");
        ::printp(pointers[1]); ::putchar('\n'); ::putchar('\r');

        // [Allocated and (well) Constructed]
        ::printf("%s", "[Pointers] (Allocated & Constructed):      [");
        ::printp(pointers[2], 3u); ::putchar('\n'); ::putchar('\r');

    // Print
    ::putchar('\n');

        // [Re-allocated (Shrunk) Only]
        ::printf("%s", "[Pointers] (Reallocated (Shrunk) Only):    [");
        ::printp(pointers[0] = (Pointer*) std::realloc(pointers[0], 1u * sizeof(Pointer)), 1u); ::putchar('\n'); ::putchar('\r');

        // [Re-allocated (Expanded) Only]
        ::printf("%s", "[Pointers] (Reallocated (Expanded) Only):  [");
        ::printp(pointers[0] = (Pointer*) std::realloc(pointers[0], 5u * sizeof(Pointer))); ::putchar('\n'); ::putchar('\r');

        // [Re-allocated and (well) Constructed]
        ::printf("%s", "[Pointers] (Reallocated & Constructed):  ["); {
            Pointer *pointersCopy; std::copy(pointers[2], pointers[2] + 3, pointersCopy = new Pointer[5u] {0, 0, 0, pointer, pointer});
            delete[] pointers[2]; pointers[2] = pointersCopy;
        } ::printp(pointers[2]);

    // Deletion
    std::free(pointers[0]);
    std::free(pointers[1]);

    delete[] pointers[2];

    // Return
    return EXIT_SUCCESS;
}
