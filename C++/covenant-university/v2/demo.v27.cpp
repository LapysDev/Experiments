/* LibrarnumberB Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Harmonic
    long double harmonic(int index) {
        // Initialization > Term
        long double term = 0;

        /* Loop
                [while statement]

            > Update > (Term, Index)
        */
        while (index) {
            term += 1 / static_cast<long double>(index);
            index -= 1;
        }

        // Return
        return term;
    }

    // Main
    int main(int argc, char* argv[]) {
        // Initialization > (Integer)
        int integer;

        // Standard > C Output
        std::cout << "Program to calculate the nth Term in a Harmonic series.\n" << std::endl;

        // Standard > C (Output, Input)
        std::cout << "Integer (Positive): ";
        std::cin >> integer;

        // Standard > C Output
        std::cout << "nth Term: " << harmonic(integer);

        return 0;
    }
