/* Import > String */
#include <stddef.h> // Standard Definition
#include <string.h> // String

/* Function */
const char* binaryToDecimal(const char binaryString[]) {
    // : Constant > Binary String Length
    // : Initialization > Decimal String
    const unsigned BINARY_STRING_LENGTH = ::strlen(binaryString);
    static char *decimalString = NULL;

    // Deletion
    std::free(decimalString);

    // Return
    return decimalString;
}

/* Main */
int main(void) {
    // Return
    return 0;
}
