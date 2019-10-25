/* Import */
#include <fcntl.h> // Functional
#include <math.h> // Mathematics
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library
#include <string.h> // String

/* Function */
    // String To Number --- WARN (Lapys) -> Assumes the string is a C/ C++ number literal without pre-defined/ user-defined suffixes.
    const float string_to_number(char string[]) {
        // Initialization > String Length
        unsigned stringLength = ::strlen(string);

        // Logic
        if (stringLength == 1u)
            // Return
            return *string - 48;

        else {
            // Initialization > ... --- NOTE (Lapys) -> Store information about the literal type.
            bool fractional = false;
            unsigned radix = 10u; // NOTE (Lapys) -> Decimal.
            bool scientific = false;
            bool sign = false;

            // Loop > Update > String ... --- NOTE (Lapys) -> Parse leading zeroes and unary arithmetic operators.
            while (*string == '0' && *(string + 1) == '0') { string += 1; stringLength -= 1u; }
            while (*string == '-' || *string == '+') { (*string == '-') && (sign = !sign); string += 1; stringLength -= 1u; }

            // Initialization > (Number, ...)
            char stringCharacter = *string;
            float number = 0.0f;

            // Logic > Update > ... --- NOTE (Lapys) -> Determine the type of the literal before iteration.
            switch (stringCharacter) {
                case '.': fractional = true; break;
                case '0': switch (*(string + 1u)) {
                    case 'b': case 'B': radix = 2u; break;
                    case 'e': case 'E': scientific = true; break;
                    case 'x': case 'X': radix = 16u; break;
                    case '.': fractional = true; break;
                    default: radix = 8u;
                }
            }

            // Loop
            for (unsigned stringIterator = fractional; stringIterator ^ stringLength; stringIterator += 1u) {
                // Update > String Character
                stringCharacter = *(string + stringIterator);

                // Logic
                switch (radix) {
                    // [Binary]
                    case 2u:
                        // Update > Number; ...
                        (stringCharacter == '1') && (number += 2u << (stringLength - stringIterator - 2u));
                        break;

                    // [Octal]
                    case 8u:
                        // Logic > Update > (Number, ...)
                        if (stringCharacter == '8' || stringCharacter == '9') { number = 0.0f; radix = 10u; stringIterator = 0u; }
                        else stringIterator && (number += (stringCharacter - 48) * ::pow(8u, stringLength - stringIterator - 1u));

                        // ...
                        break;

                    // [Decimal]
                    case 10u: {
                        // Logic
                            // [Scientific]
                            if (scientific) {
                                // Update > String Iterator --- WARN (Lapys) -> Account for the exponentiation character.
                                stringIterator -= 1u;

                                // Definition > String Exponent ...
                                const unsigned STRING_EXPONENT_LENGTH = stringLength - stringIterator;
                                char STRING_EXPONENT[STRING_EXPONENT_LENGTH + 1u] { 0 };

                                // Loop > Update > String (Exponent, ...)
                                while (stringIterator ^ (stringLength - 1u)) {
                                    stringCharacter = *(string + (stringIterator += 1u));
                                    *(STRING_EXPONENT + (STRING_EXPONENT_LENGTH - (stringLength - stringIterator) - 1u)) = stringCharacter;
                                }

                                // Update > (Number, ...) --- NOTE (Lapys) -> Expecting nothing after the exponent.
                                number *= ::pow(10.0f, ::string_to_number(STRING_EXPONENT));
                            }

                            // [Fractional]
                            else if (fractional) {
                                // Update > String Iterator --- WARN (Lapys) -> Account for the decimal point.
                                stringIterator -= 1u;

                                // Constant > Mantissa Index
                                const unsigned MANTISSA_INDEX = stringIterator - 1u;

                                // Loop
                                while ((stringIterator ^ (stringLength - 1u)) && !(scientific)) {
                                    // Update > String Character
                                    stringCharacter = *(string + (stringIterator += 1u));

                                    // Update > (Scientific | Number) --- NOTE (Lapys) -> Numeric literal types can be utilized together.
                                    stringCharacter == 'e' || stringCharacter == 'E' ?
                                        scientific = true :
                                        number += (stringCharacter - 48) * ::pow(10, -signed(stringIterator - (MANTISSA_INDEX + 1u)));
                                }
                            }

                            // [Integral]
                            else
                                // Logic --- NOTE (Lapys) -> Semi-complex notations such as the rational/ scientific form required re-assessing the source.
                                if (stringCharacter == '.' || (stringCharacter == 'e' || stringCharacter == 'E')) {
                                    // Constant > String Characteristics Length
                                    const unsigned STRING_CHARACTERISTICS_LENGTH = stringIterator;

                                    // Update > (Number, (Fractional | Scientific))
                                    number = 0.0f;
                                    stringCharacter == '.' ? fractional = true : scientific = true;

                                    // Loop > Update > (Number, ...)
                                    while (stringIterator) {
                                        stringCharacter = *(string + (stringIterator -= 1u));
                                        number += (stringCharacter - 48) * ::pow(10u, STRING_CHARACTERISTICS_LENGTH - stringIterator - 1u);
                                    }

                                    // Update > String Iterator
                                    stringIterator = STRING_CHARACTERISTICS_LENGTH;
                                }

                                else
                                    // Update > Number
                                    number += (stringCharacter - 48) * ::pow(10u, stringLength - stringIterator - 1u);
                    } break;

                    // [Hexadecimal]
                    case 16u:
                        // Update > Number
                        (stringIterator && stringIterator ^ 1u) && (number +=
                            (stringCharacter > 47 && stringCharacter < 58 ? stringCharacter - 48 : (stringCharacter > 96 && stringCharacter < 103 ? stringCharacter - 87 : (stringCharacter > 64 && stringCharacter < 71 ? stringCharacter - 55 : 0))) *
                            ::pow(16u, stringLength - stringIterator - 1u)
                        );
                }
            }

            // Update > Number --- NOTE (Lapys) -> Unfortunately some spill-over calculations.
            (radix == 2u) && (number += 1.0f);
            number && sign && (number = -number);

            // Return
            return number;
        }
    }

/* Main */
int main(int argc, char* argv[]) {
    // Initialization > String
    char *string = NULL;

    // ...
    string = (char*) "";
    ::printf("[STRING]: \"%s\"\n", string);
    ::printf("[STRING -> NUMBER]: %f\n\n", ::string_to_number(string));

    string = (char*) "---.1e0";
    ::printf("[STRING]: \"%s\"\n", string);
    ::printf("[STRING -> NUMBER]: %f\n\n", ::string_to_number(string));

    string = (char*) "2019";
    ::printf("[STRING]: \"%s\"\n", string);
    ::printf("[STRING -> NUMBER]: %f\n\n", ::string_to_number(string));

    string = (char*) "02019";
    ::printf("[STRING]: \"%s\"\n", string);
    ::printf("[STRING -> NUMBER]: %f\n\n", ::string_to_number(string));

    string = (char*) "03743";
    ::printf("[STRING]: \"%s\"\n", string);
    ::printf("[STRING -> NUMBER]: %f\n\n", ::string_to_number(string));

    string = (char*) "0b11111100011";
    ::printf("[STRING]: \"%s\"\n", string);
    ::printf("[STRING -> NUMBER]: %f\n\n", ::string_to_number(string));

    string = (char*) "0x7E3";
    ::printf("[STRING]: \"%s\"\n", string);
    ::printf("[STRING -> NUMBER]: %f\n\n", ::string_to_number(string));

    // Return
    return 0;
}
