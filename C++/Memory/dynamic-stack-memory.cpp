/* Import */
#include <stddef.h> // Standard Definition
#include <stdio.h> // Standard Input-Output
#if defined(__TOS_WIN__) || defined(_WIN16) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__) // Microsoft Windows
#  include <malloc.h> // Memory Allocation
#else
#  include <stdlib.h> // Standard Library
#endif

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
    // Global > Pointers
    Pointer *pointers;

    // Logic > Update > Pointers
    #if defined(__ANDROID__) || defined(__gnu_linux__) || defined(linux) || defined(__linux) || defined(__linux__)
        pointers = (Pointer*) ::alloca(5u * sizeof(Pointer));
    #elif defined(__TOS_WIN__) || defined(_WIN16) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
        pointers = (Pointer*) ::_alloca(5u * sizeof(Pointer));
    #endif

    // Print
    ::printf("%s", "[Pointers] (Allocated only): [");
    ::printp(pointers);

    // Return
    return EXIT_SUCCESS;
}
