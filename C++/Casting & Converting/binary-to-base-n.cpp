/* Import */
#include <math.h> // Mathematics
#include <stdlib.h> // Standard Library
#include <stdio.h>
#include <string.h> // String

/* Function --- NOTE (Lapys) -> Assumes all arguments are syntactically valid & unsigned. */
    // Binary To Decimal
    const float binary_string_to_decimal_number(char binaryString[]) {
        // Initialization > (Has Indexed Characteristics, Binary String Digit, Decimal Number)
        bool hasIndexedCharacteristics = false; // NOTE (Lapys) -> Ignore trailing `0`'s.
        char binaryStringDigit = *binaryString;
        float decimalNumber = 0.0f;

        // Loop
        while (binaryStringDigit)
            // Logic
            if (hasIndexedCharacteristics) {
                // Initialization > (Binary String Iterator, Mantissa Index)
                long binaryStringIterator;
                unsigned mantissaIndex = 0u;

                // Loop > Update > (Mantissa Index, Binary String Digit) ---NOTE (Lapys) -> Search for the binary mantissa.
                while (binaryStringDigit && (binaryStringDigit ^ '.')) { mantissaIndex += 1u; binaryStringDigit = *(binaryString + mantissaIndex); }

                // [Binary Characteristics -> Decimal Characteristics]
                // : Update > Binary String Iterator
                // : Loop
                binaryStringIterator = mantissaIndex;
                while (binaryStringIterator) {
                    // : Constant > Exponent
                    // : Update > Decimal Number
                    const unsigned EXPONENT = mantissaIndex - (binaryStringIterator -= 1) - 1u;
                    decimalNumber += float(*(binaryString + binaryStringIterator) == '1' ? (EXPONENT ? 2u << (EXPONENT - 1u) : 1u) : 0u);
                }

                // [Binary Mantissa -> Decimal Mantissa]
                if (*(binaryString + mantissaIndex) == '.') {
                    // Update > (Binary String) (Digit, Iterator) --- WARN (Lapys) -> Do not index the separator symbol `'.'`.
                    binaryString += 1u;
                    binaryStringDigit = *(binaryString + mantissaIndex);
                    binaryStringIterator = 0;

                    // Loop
                    while (binaryStringDigit) {
                        // Constant > Exponent
                        const float EXPONENT = binaryStringIterator;

                        // Update > (Decimal Number, Binary String Digit)
                        decimalNumber += binaryStringDigit == '1' ? ::powf(2.0f, -(EXPONENT + 1.0f)) : 0.0f;
                        binaryStringDigit = *(binaryString + (binaryStringIterator += 1) + mantissaIndex);
                    }
                }
            }

            else if (binaryStringDigit == '0') {
                // Update > Binary String (Digit) --- NOTE (Lapys) -> Continue searching for non-trailing `0`'s.
                binaryString += 1;
                binaryStringDigit = *binaryString;
            }

            else
                // Update > Has Indexed Characteristics
                hasIndexedCharacteristics = true;

        // Return
        return decimalNumber;
    }
    const char* binary_string_to_decimal_string(char binaryString[]) { // NOTE (Lapys) -> Really just converts decimal numbers into decimal strings.
        // Constant > Decimal Number
        const float DECIMAL_NUMBER = ::binary_string_to_decimal_number((char*) binaryString);

        // Initialization > Decimal (Number ..., String) --- NOTE (Lapys) -> Splitting the number into its component parts like this is viable because its mantissa not be repeating.
        unsigned decimalNumberCharacteristics = DECIMAL_NUMBER;
        unsigned decimalNumberCharacteristicsCardinality = 0u;
        float decimalNumberMantissa = DECIMAL_NUMBER - decimalNumberCharacteristics;
        unsigned decimalNumberMantissaCardinality = 0u;

        static char *decimalString = NULL;

        // Deletion; Update > Decimal String
        std::free(decimalString);
        decimalString = (char*) std::malloc(::strlen(binaryString) * sizeof(char));

        // [Decimal Number Characteristics] Logic
        if (decimalNumberCharacteristics) {
            // (Loop > )Update > Decimal (Number Characteristics ..., String)
            while (decimalNumberCharacteristics) { *(decimalString + decimalNumberCharacteristicsCardinality) = (decimalNumberCharacteristics % 10u) + 48u; decimalNumberCharacteristics /= 10u; decimalNumberCharacteristicsCardinality += 1u; }
            *(decimalString + decimalNumberCharacteristicsCardinality) = '\0';
            ::strrev(decimalString);
        }

        else {
            // Update > Decimal (Number Characteristics ..., String)
            decimalNumberCharacteristicsCardinality += 1u;
            *decimalString = '0';
        }

        // [Decimal Mantissa] Logic
        if (decimalNumberMantissa) {
            // Update > Decimal (Number Mantissa Cardinality, String)
            decimalNumberMantissaCardinality += 1u;
            *(decimalString + decimalNumberCharacteristicsCardinality) = '.';

            // Loop > Update > Decimal (Number Mantissa ..., String)
            while (decimalNumberMantissa - float(unsigned(decimalNumberMantissa))) {
                decimalNumberMantissa *= 10.0f;
                *(decimalString + (decimalNumberCharacteristicsCardinality + decimalNumberMantissaCardinality)) = (unsigned(decimalNumberMantissa) % 10u) + 48u;
                decimalNumberMantissaCardinality += 1u;
            }
        }

        // Update > Decimal String
        decimalString = (char*) std::realloc(decimalString, (decimalNumberCharacteristicsCardinality + decimalNumberMantissaCardinality + 1u) * sizeof(char));
        *(decimalString + (decimalNumberCharacteristicsCardinality + decimalNumberMantissaCardinality)) = '\0';

        // Return
        return decimalString;
    }

    // Binary To Radix --- FLAG (Lapys) -> Fails on really large numbers.
    const char* binary_string_to_radix_string(const char binaryString[], const unsigned radix) {
        // Constant > Decimal Number
        const float DECIMAL_NUMBER = ::binary_string_to_decimal_number((char*) binaryString);

        // Initialization > (Decimal Number (Characteristics, Mantissa) ..., Radix String)
        unsigned decimalNumberCharacteristics = DECIMAL_NUMBER;
        unsigned decimalNumberCharacteristicsCardinality = 0u;
        float decimalNumberMantissa = DECIMAL_NUMBER - decimalNumberCharacteristics;
        unsigned decimalNumberMantissaCardinality = 0u;

        static char *radixString = NULL;

        // Deletion; Update > Radix String
        std::free(radixString);
        radixString = (char*) std::malloc(::strlen(binaryString) * sizeof(char));

        // Logic
        if (decimalNumberCharacteristics)
            // Loop
            while (decimalNumberCharacteristics) {
                // Constant > Radix Characteristics Digit
                const unsigned RADIX_CHARACTERISTICS_DIGIT = decimalNumberCharacteristics % radix;

                // Update > (Decimal Number Characteristics (Cardinality), Radix String)
                *(radixString + decimalNumberCharacteristicsCardinality) = RADIX_CHARACTERISTICS_DIGIT + (RADIX_CHARACTERISTICS_DIGIT > 9u && RADIX_CHARACTERISTICS_DIGIT < 36u ? 55u : 48u);
                decimalNumberCharacteristics /= radix;
                decimalNumberCharacteristicsCardinality += 1u;
            }

        else {
            // Update > (Decimal Number Characteristics Cardinality, Radix String)
            decimalNumberCharacteristicsCardinality += 1u;
            *radixString = '0';
        }

        // Logic
        if (decimalNumberMantissa) {
            // Update > (Decimal Number Mantissa Cardinality, Radix String)
            decimalNumberMantissaCardinality += 1u;
            *(radixString + decimalNumberMantissaCardinality) = '.';

            // Loop
            while (decimalNumberMantissa - float(unsigned(decimalNumberMantissa))) {
                // Constant > Radix Mantissa Digit
                const unsigned RADIX_MANTISSA_DIGIT = unsigned(decimalNumberMantissa *= radix) % radix;

                // Update > (Decimal Number Mantissa Cardinality, Radix String)
                *(radixString + (decimalNumberCharacteristicsCardinality + decimalNumberMantissaCardinality)) = RADIX_MANTISSA_DIGIT + (RADIX_MANTISSA_DIGIT > 9u && RADIX_MANTISSA_DIGIT < 36u ? 55u : 48u);
                decimalNumberMantissaCardinality += 1u;
            }
        }

        // Update > Radix String
        radixString = (char*) std::realloc(radixString, (decimalNumberCharacteristicsCardinality + decimalNumberMantissaCardinality + 1u) * sizeof(char));
        *(radixString + (decimalNumberCharacteristicsCardinality + decimalNumberMantissaCardinality)) = '\0';

        // Return
        return radixString;
    }

/* Main */
int main(int argc, char* argv[]) {
    // Initialization > (Binary, ...)
    char *binary = NULL, *decimal = NULL, *hexadecimal = NULL, *octal = NULL;

    // ...
    ::printf("\n");

    binary  = (char*) "1";
    decimal = (char*) ::binary_string_to_decimal_string(binary); hexadecimal = (char*) ::binary_string_to_radix_string(binary, 16); octal = (char*) ::binary_string_to_radix_string(binary, 8);
    ::printf("[BINARY (2)]: %s\n\n", binary); ::printf("[DECIMAL (10)]: %s\n", decimal); ::printf("[HEXADECIMAL (16)]: %s\n", hexadecimal); ::printf("[OCTAL (8)]: %s\n", octal);
    ::printf("\n========================================\n\n");

    binary  = (char*) "01";
    decimal = (char*) ::binary_string_to_decimal_string(binary); hexadecimal = (char*) ::binary_string_to_radix_string(binary, 16); octal = (char*) ::binary_string_to_radix_string(binary, 8);
    ::printf("[BINARY (2)]: %s\n\n", binary); ::printf("[DECIMAL (10)]: %s\n", decimal); ::printf("[HEXADECIMAL (16)]: %s\n", hexadecimal); ::printf("[OCTAL (8)]: %s\n", octal);
    ::printf("\n========================================\n\n");

    binary  = (char*) "10";
    decimal = (char*) ::binary_string_to_decimal_string(binary); hexadecimal = (char*) ::binary_string_to_radix_string(binary, 16); octal = (char*) ::binary_string_to_radix_string(binary, 8);
    ::printf("[BINARY (2)]: %s\n\n", binary); ::printf("[DECIMAL (10)]: %s\n", decimal); ::printf("[HEXADECIMAL (16)]: %s\n", hexadecimal); ::printf("[OCTAL (8)]: %s\n", octal);
    ::printf("\n========================================\n\n");

    binary  = (char*) "101.11";
    decimal = (char*) ::binary_string_to_decimal_string(binary); hexadecimal = (char*) ::binary_string_to_radix_string(binary, 16); octal = (char*) ::binary_string_to_radix_string(binary, 8);
    ::printf("[BINARY (2)]: %s\n\n", binary); ::printf("[DECIMAL (10)]: %s\n", decimal); ::printf("[HEXADECIMAL (16)]: %s\n", hexadecimal); ::printf("[OCTAL (8)]: %s\n", octal);
    ::printf("\n========================================\n\n");

    binary  = (char*) "1010101010.0110101";
    decimal = (char*) ::binary_string_to_decimal_string(binary); hexadecimal = (char*) ::binary_string_to_radix_string(binary, 16); octal = (char*) ::binary_string_to_radix_string(binary, 8);
    ::printf("[BINARY (2)]: %s\n\n", binary); ::printf("[DECIMAL (10)]: %s\n", decimal); ::printf("[HEXADECIMAL (16)]: %s\n", hexadecimal); ::printf("[OCTAL (8)]: %s\n", octal);

    // Return
    return 0;
}
