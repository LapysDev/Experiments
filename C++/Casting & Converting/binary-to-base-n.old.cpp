/* Import > String */
#include <cmath> // C Mathematics
#include <cstring> // C String
#include <iostream> // Input-Output Stream

/* Function > ... */
const unsigned decimalStringToNumber(const char decimalString[]) {
    // : Constant > Decimal String Length
    // : Initialization > Decimal Number
    const unsigned DECIMAL_STRING_LENGTH = ::strlen(decimalString);
    unsigned decimalNumber = 0u, decimalStringIterator = DECIMAL_STRING_LENGTH;

    // Loop
    while (decimalStringIterator) {
        // : Constant > Decimal String Digit
        // : Update > Decimal Number
        const char DECIMAL_STRING_DIGIT = *(decimalString + (DECIMAL_STRING_LENGTH - (decimalStringIterator -= 1u) - 1u));
        decimalNumber += (DECIMAL_STRING_DIGIT - 48u) * ::pow(10u, decimalStringIterator);
    }

    // Return
    return decimalNumber;
}

const char* binaryToDecimal(const char binaryString[]) {
    // Constant > ...
    const unsigned BINARY_STRING_LENGTH = ::strlen(binaryString);

    // Initialization > ...
    unsigned binaryStringIterator = BINARY_STRING_LENGTH;
    unsigned decimalNumber = 0u; static char *decimalString = NULL;

    // Deletion
    std::free(decimalString);

    // Loop
    while (binaryStringIterator) {
        // : Constant > Binary String Digit
        // : Update > Decimal Number
        const char BINARY_STRING_DIGIT = *(binaryString + (BINARY_STRING_LENGTH - (binaryStringIterator -= 1u) - 1u));
        decimalNumber += BINARY_STRING_DIGIT == '1' ? ::pow(2u, binaryStringIterator) : 0u;
    }

    // Update > Decimal String
    decimalString = (char*) std::malloc(BINARY_STRING_LENGTH * sizeof(char));
    ::sprintf(decimalString, "%u", decimalNumber);

    // Return
    return decimalString;
} const char* binaryToDecimal(std::string binaryString) { return ::binaryToDecimal(binaryString.c_str()); }

const char* binaryToHexadecimal(const char binaryString[]) {
    // Initialization > ...
    unsigned decimal = ::decimalStringToNumber(::binaryToDecimal(binaryString));
    static char *hexadecimalString = NULL;
    unsigned hexadecimalStringIterator = 0u;

    // Deletion; Update > Hexadecimal String
    std::free(hexadecimalString);
    hexadecimalString = (char*) std::malloc(::strlen(binaryString));

    // Loop
    while (decimal) {
        // Constant > Remainder
        const unsigned REMAINDER = decimal % 16u;

        // Update > (Decimal, Hexadecimal String)
        decimal /= 16u;
        hexadecimalString = (char*) std::realloc(hexadecimalString, (hexadecimalStringIterator + 1u) * sizeof(char));

        // Logic > ...
        if (REMAINDER > 9 && REMAINDER < 16) *(hexadecimalString + hexadecimalStringIterator) = REMAINDER + 55u;
        else *(hexadecimalString + hexadecimalStringIterator) = REMAINDER + 48u;

        // Update > Hexadecimal String Iterator
        hexadecimalStringIterator += 1u;
    }

    // Update > Hexadecimal String
    *(hexadecimalString + hexadecimalStringIterator) = '\0';
    ::strrev(hexadecimalString);

    // Return
    return hexadecimalString;
} const char* binaryToHexadecimal(std::string binaryString) { return ::binaryToHexadecimal(binaryString.c_str()); }

const char* binaryToOctal(const char binaryString[]) {
    // Initialization > ...
    unsigned decimal = ::decimalStringToNumber(::binaryToDecimal(binaryString));
    static char *octalString = NULL;
    unsigned octalStringIterator = 0u;

    // Deletion; Update > Octal String
    std::free(octalString);
    octalString = (char*) std::malloc(::strlen(binaryString));

    // Loop
    while (decimal) {
        // Constant > Remainder
        const unsigned REMAINDER = decimal % 16u;

        // Update > (Decimal, Octal String)
        decimal /= 8u;
        octalString = (char*) std::realloc(octalString, (octalStringIterator + 1u) * sizeof(char));

        // Update > Octal String (Iterator)
        *(octalString + octalStringIterator) = REMAINDER + 48u;
        octalStringIterator += 1u;
    }

    // Update > Octal String
    *(octalString + octalStringIterator) = '\0';
    ::strrev(octalString);

    // Return
    return octalString;
} const char* binaryToOctal(std::string binaryString) { return ::binaryToOctal(binaryString.c_str()); }

/* Main */
int main(int argc, char* argv[]) {
    // Initialization > (Binary, Decimal, Hexadecimal, Octal)
    std::string binary, decimal, hexadecimal, octal;

    // Print
    std::cout << "Enter a binary integer: "; std::cin >> binary; std::cout << std::endl;

    std::cout << "Binary Form: " << binary << std::endl;
    std::cout << "Decimal Form: " << ::binaryToDecimal(binary) << std::endl;
    std::cout << "Hexadecimal Form: " << ::binaryToHexadecimal(binary) << std::endl;
    std::cout << "Octal Form: " << ::binaryToOctal(binary) << std::endl;

    // Return
    return 0;
}
