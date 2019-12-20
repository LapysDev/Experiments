/* Import */
#include <fcntl.h> // Functional --- NOTE (Lapys) -> `NULL` macro.
#include <locale.h> // Locale --- NOTE (Lapys) -> `std::setlocale` function.
#include <math.h> // Mathematics --- NOTE (Lapys) -> `std::sin` function.
#include <stdio.h> // Standard Input-Output --- NOTE (Lapys) -> `::printf` function and `STDOUT_FILENO` constant.
#include <stdlib.h> // Standard Library --- NOTE (Lapys) -> `::srand` function.
#include <time.h> // Time --- NOTE (Lapys) -> `::time` function.
#include <unistd.h> // UNIX Standard --- NOTE (Lapys) -> `::write` function.

/* Function > Sine */
inline float sine(const float radian) {
    // Initialization > (Evaluation, Permutation Term, Signedness)
    float evaluation = radian;
    float permutationTerm = radian;
    signed char signedness = -1;

    // Loop
    for (unsigned char iterator = 1u; iterator ^ 15u; iterator += 1u) {
        // Update > (Evaluation, Permutation Term, Signedness)
        evaluation = evaluation + signedness * permutationTerm * radian * radian / (2u * iterator * (2u * iterator + 1u));
        permutationTerm = permutationTerm * radian * radian / (2u * iterator * (2u * iterator + 1u));
        signedness = signedness == 1 ? -1 : 1;
    }

    // Return
    return evaluation;
}

/* Main */
int main(void) {
    // Initialization > File
    FILE *file = ::fopen("sine.txt", "w");

    // ...
    {
        // ... --- NOTE (Lapys) -> Set the seed to the current time.
        ::srand(::time(NULL));

        // Loop
        for (unsigned short accuracy = 0u, iterator = 0u, length = (unsigned short) -1; iterator ^ length; iterator += 1u) {
            // Initialization > (..., Approximation, Evaluation)
            float number = ((float) (::rand() % 100) / 100.0f) * (::rand() % 2 ? 1.0f : -1.0f);

            float approximation = ::sine(number);
            float evaluation = std::sin(number);

            // Logic > ...
            if (!iterator || iterator == length - 1u || !(iterator % 100u)) {
                ::write(STDOUT_FILENO, "\r                                                                         \r", 75u);

                ::write(STDOUT_FILENO, "Accuracy: ", 10u);
                ::printf("%f", (100.0f * (float) accuracy) / (float) iterator);
                ::write(STDOUT_FILENO, "%", 1u);

                ::write(STDOUT_FILENO, " | ", 3u);

                ::write(STDOUT_FILENO, "Comparisons: ", 13u);
                ::printf("%f", (100.0f * (float) iterator) / (float) length);
                ::write(STDOUT_FILENO, "% (", 3u); ::printf("%u", iterator); ::write(STDOUT_FILENO, ")", 1u);
            }

            // Print
                // [Number]
                ::fwrite("Number: ", STDOUT_FILENO, 8u, file); ::fprintf(file, "%f", number);
                ::setlocale(LC_ALL, ""); // -> "English_United States.1252"
                { ::fputc(wchar_t(176u), file); }
                ::setlocale(LC_ALL, "C");
                ::fwrite("\n\n\r", STDOUT_FILENO, 3u, file);

                // [Approximation]
                ::fwrite("Approximated Sine: ", STDOUT_FILENO, 19u, file);
                ::fprintf(file, "%f", approximation);
                ::fwrite("\n\r", STDOUT_FILENO, 2u, file);

                // [Evaluation]
                ::fwrite("Evaluated Sine: ", STDOUT_FILENO, 16u, file);
                ::fprintf(file, "%f", evaluation);
                ::fwrite("\n\n\r", STDOUT_FILENO, 3u, file);

                // [...]
                ::fwrite("Approximated Sine == Evaluated Sine? ", STDOUT_FILENO, 37u, file);
                if (approximation == evaluation) {
                    accuracy += 1u;
                    ::fwrite("true", STDOUT_FILENO, 4u, file);
                } else ::fwrite("false", STDOUT_FILENO, 5u, file);
                ::fwrite("\n==========================================\n", STDOUT_FILENO, 44u, file);
        }

        // ...
        ::write(STDOUT_FILENO, "\n[DONE]", 7u);
    }

    // Deletion
    ::fclose(file);

    // Return
    return 0;
}
