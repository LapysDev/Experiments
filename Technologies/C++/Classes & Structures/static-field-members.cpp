/* Import */
#include <stdio.h> // Standard Input-Output

/* Class > Human */
class Human {
    // [...]
    public:
        // [Constructor]
        inline Human() { Human::total += 1u; }

        // Modification > Total
        static unsigned total;
};

/* Modification > Human > Total */
unsigned Human::total = 0;

/* Main */
int main(void) {
    // [Begin] ...
    ::printf("%s", "[PROGRAM INITIATED]\n");

    // ...
    ::printf("Number of Humans: %u\n", Human::total);

    for (unsigned char iterator = 0u; iterator ^ 5u; iterator += 1u) Human();
    ::printf("Number of Humans: %u\n", Human::total);

    // [End] ...
    ::printf("%s", "[PROGRAM TERMINATED]");

    // Return
    return 0;
}
