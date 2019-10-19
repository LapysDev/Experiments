/* Import */
#include <fcntl.h> // Functional
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library
#include <string.h> // String

/* Function */
    // Number To String --- WARN (Lapys) -> Assumes unsigned magnitudes.
    const char* number_to_string(unsigned number) {
        // Initialization > (Cardinality, String)
        unsigned cardinality = 0u;
        static char *string = NULL;

        // Deletion
        std::free(string);

        // Logic
        if (number) {
            // Update > String
            string = (char*) std::malloc(1 * sizeof(char));

            // Update > (String, ...)
            while (number) { string = (char*) std::realloc(string, (cardinality + 2u) * sizeof(char)); *(string + cardinality) = (number % 10u) + 48u; cardinality += 1u; number /= 10u; }

            // Update > String
            *(string + cardinality) = '\0'; ::strrev(string);
        }

        else {
            // Update > String
            string = (char*) std::malloc(2 * sizeof(char));
            *string = '0'; *(string + 1) = '\0';
        }

        // Return
        return string;
    }
    const char* number_to_string(const float number) {
        // Initialization > ((Characteristics, Mantissa) ..., String)
        unsigned characteristics = number;
        unsigned characteristicsCardinality = 0u;

        float mantissa = number - characteristics;
        unsigned mantissaCardinality = 0u;

        static char *string = NULL;

        // Deletion
        std::free(string);

        // Update > (String, ...)
        string = (char*) ::number_to_string(characteristics);
        characteristicsCardinality = ::strlen(string);

        // Logic
        if (mantissa) {
            // Update > (String, ...)
            *(string + characteristicsCardinality) = '.';
            mantissaCardinality += 1u;

            // Loop
            while (mantissa - float(unsigned(mantissa))) {
                // Update > (Mantissa ..., String)
                mantissa *= 10.0f;

                string = (char*) std::realloc(string, ((characteristicsCardinality + mantissaCardinality) + 2u) * sizeof(char));
                *(string + (characteristicsCardinality + mantissaCardinality)) = (unsigned(mantissa) % 10u) + 48u;

                mantissaCardinality += 1u;
            }
        }

        // Update > String
        *(string + (characteristicsCardinality + mantissaCardinality)) = '\0';

        // Return
        return string;
    }

/* Main */
int main(int argc, char* argv[]) {
    // Initialization
    unsigned integer; float rational;

    // ...
    integer = 2020u; ::printf("[INTEGER]: %i\n", integer); ::printf("[INTEGER -> STRING]: %s\n\n", ::number_to_string(integer));
    rational = 2020.0f; ::printf("[RATIONAL]: %f\n", rational); ::printf("[RATIONAL -> STRING]: %s\n---------------------------------------------\n", ::number_to_string(rational));

    integer = 101u; ::printf("[INTEGER]: %i\n", integer); ::printf("[INTEGER -> STRING]: %s\n\n", ::number_to_string(integer));
    rational = 1.01f; ::printf("[RATIONAL]: %f\n", rational); ::printf("[RATIONAL -> STRING]: %s\n---------------------------------------------\n", ::number_to_string(rational));

    integer = -1u; ::printf("[INTEGER]: %i\n", integer); ::printf("[INTEGER -> STRING]: %s\n\n", ::number_to_string(integer));
    rational = (22.0f / 7.0f); ::printf("[RATIONAL]: %f\n", rational); ::printf("[RATIONAL -> STRING]: %s\n---------------------------------------------\n", ::number_to_string(rational));

    // Return
    return 0;
}
