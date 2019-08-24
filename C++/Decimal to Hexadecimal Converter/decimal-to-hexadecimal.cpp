/* Import */
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library Header
#include <unistd.h> // Unix Standard Header

/* Function > Convert */
char* convert(unsigned long long number) {
    // Initialization > Number Hexadecimal (Iterator)
    char* numberHexadecimal = (char*) std::malloc(sizeof(char));
    unsigned char numberHexadecimalIterator = 0;

    // Loop
    while (number) {
        // Initialization > Remainder
        unsigned long long remainder = number % 16;

        // Update > (Number Hexadecimal, Number)
        *(numberHexadecimal + (numberHexadecimalIterator += 1) - 1) = remainder + (remainder < 10 ? 48 : 55);
        number /= 16;
    }

    // Update > Number Hexadecimal
    numberHexadecimal = (char*) std::realloc(numberHexadecimal, (numberHexadecimalIterator + 1) * sizeof(char));
    *(numberHexadecimal + numberHexadecimalIterator) = '\0';

    // Initialization > Number Hexadecimal (Half) Length
    const unsigned char numberHexadecimalLength = numberHexadecimalIterator,
        numberHexadecimalHalfLength = (unsigned char) (numberHexadecimalLength / 2);

    // Loop --- NOTE (Lapys) -> Reverse the number Hexadecimal`s digits.
    while (numberHexadecimalIterator ^ numberHexadecimalHalfLength) {
        // Initialization > Number Hexadecimal Digit
        char numberHexadecimalDigit = *(numberHexadecimal + (numberHexadecimalIterator -= 1));

        // Update > Number Hexadecimal
        *(numberHexadecimal + numberHexadecimalIterator) = *(numberHexadecimal + (numberHexadecimalLength - numberHexadecimalIterator - 1));
        *(numberHexadecimal + (numberHexadecimalLength - numberHexadecimalIterator - 1)) = numberHexadecimalDigit;
    }

    // Return
    return numberHexadecimal;
}

/* Main */
int main(int argc, char* argv[]) {
    // Initialization > Hexadecimal
    char* hexadecimal = ::convert(65536);

    // Print
    ::write(STDOUT_FILENO, hexadecimal, sizeof(hexadecimal) - sizeof(char));

    // Deletion
    std::free(hexadecimal);

    // Return
    return 0;
}
