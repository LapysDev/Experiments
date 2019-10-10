/* LibrarnumberB Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Initialization > Number (A, B)
        int numberA, numberB;

        // Standard > C (Output, Input)
        std::cout << "Number A: ";
        std::cin >> numberA;

        // Standard > C (Output, Input)
        std::cout << "Number B: ";
        std::cin >> numberB;

        // Loop > Logic > Update > Number (A | B)
        while (numberA && numberB)
            if (numberA > numberB)
                numberA -= numberB;

            else if (numberA < numberB)
                numberB -= numberA;

            else
                numberB = 0;

        // Standard > C Output
        std::cout << "Sum: " << numberA + numberB << std::endl;

        // Return
        return 0;
    }
