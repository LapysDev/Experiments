/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Initialization > (Number (A, B, C), Maximum)
        double numberA, numberB, numberC, max;

        // Standard > C (Output, Input)
        std::cout << "Program to test the greater of three numbers:\n" << std::endl;
        std::cout << "Number A: ";
        std::cin >> numberA;
        std::cout << "Number B: ";
        std::cin >> numberB;
        std::cout << "Number C: ";
        std::cin >> numberC;
        std::cout << std::endl;

        /* Logic
                [if:else if:else statement]

            > Update > Maximum
        */
        if (numberA > numberB && numberA > numberC)
            max = numberA;

        else if (numberB > numberA && numberB > numberC)
            max = numberB;

        else
            max = numberC;

        // Standard > C (Output, Input)
        std::cout << "Number " << (max == numberA ? "A (" : (max == numberB ? "B (" : "C (")) << max << ") is greater than Numbers " << (max == numberA ? "B and C" : (max == numberB ? "A and C" : "A and B"));

        // Return
        return 0;
    }
