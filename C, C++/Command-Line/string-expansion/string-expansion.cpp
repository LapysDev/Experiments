/* Import */
    // Standard Library
    #include <stdlib.h>

    // Unix Standard
    #include <unistd.h>

/* Function */
    // Request String
    constexpr inline static char* requestString() {
        // Initialization > (Length, String)
        std::size_t length = 5 + 1;
        char* string = (char*) std::malloc(length);

        // Update > String --- NOTE (Lapys) -> `"Hello"`.
        *string = 'H'; *(string + 1) = 'e'; *(string + 2) = 'l'; *(string + 3) = 'l'; *(string + 4) = 'o'; *(string + 5) = '\0';

        // Return
        return string;
    }

    /* Main */
    int main(int argc, char* argv[]) {
        // Initialization > String
        char* string = ::requestString();

        // Print
        ::write(1, "[Packed]  : ", 12); ::write(1, string, 5); ::write(1, "\n", 1);

        // Update > String
        string = (char*) std::realloc(string, 13 + 1);
        *(string + 5) = ','; *(string + 6) = ' '; *(string + 7) = 'W'; *(string + 8) = 'o'; *(string + 9) = 'r'; *(string + 10) = 'l'; *(string + 11) = 'd'; *(string + 12) = '!'; *(string + 13) = '\0';

        // Print
        ::write(1, "[Expanded]: ", 12); ::write(1, string, 13); ::write(1, "\n", 1);

        // Deletion
        std::free(string);

        // Return
        return 0;
    }
