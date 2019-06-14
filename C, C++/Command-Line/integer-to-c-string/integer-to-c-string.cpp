/* Import */
    // Standard Library
    #include <stdlib.h>

    // Unix Standard
    #include <unistd.h>

/* Function */
    // Characteristics Length
    const unsigned int characteristicsLength(int number) {
        // Initialization > Length
        unsigned int length = 0;

        // Loop > Update > (Length, Number)
        while (number) { length += 1; number /= 10; }

        // Return
        return length;
    }

    // To Character String
    char* toCharacterString(int arg) {
        // Initialization > (Length, Iterator, Digits, String)
        unsigned int length = characteristicsLength(arg), iterator = length;
        char digits[10] {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char* string = (char*) std::malloc(length);

        // Loop
        while (arg > 0 && iterator) {
            // Initialization > Digit
            unsigned int digit = arg % 10;

            // Update > (String, Argument)
            string[iterator -= 1] = digits[digit];
            arg = (unsigned int) arg / 10;
        }

        // Update > String
        string[length] = '\0';

        // Return
        return string;
    }

    /* Main */
    int main(int argc, char* argv[]) {
        // Initialization > Iterator
        std::size_t iterator = 50 + 1;

        // Print
        while (iterator) {
            // Initialization > String
            char* string = toCharacterString((int) 255);

            // Print
            ::write(1, string, sizeof string - 1); (iterator -= 1) && ::write(1, "\n", 1);

            // Deletion
            std::free(string);
        }

        // Return
        return 0;
    }
