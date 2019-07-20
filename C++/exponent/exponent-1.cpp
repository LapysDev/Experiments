/* Library */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Power
    long double pow(long double base, long double exponent);

    // Root
    long double root(long double base, int exponent) {
        // Initialization > (Constant, Iterator, Matrix)
        const int constant = 6;
        int iterator = 0;
        long double matrix[constant] = {1};

        // Loop > Update > Matrix
        for (iterator; iterator < constant - 1; iterator += 1)
            matrix[iterator + 1] = (1.0 / exponent) * ((exponent - 1) * matrix[iterator] + base / pow(matrix[iterator], exponent - 1));

        // Return
        return matrix[constant - 1];
    }

    // Power
    long double pow(long double base, long double exponent) {
        // {Null Base} Logic > Return
        if (!base)
            return 0;

        /* Logic
                [if:else if:else statement]
        */
            // {Null Exponent}
            if (!exponent)
                // Return
                return 1;

            // {Negative Exponent}
            else if (exponent < 0)
                // Return
                return 1 / pow(base, exponent);

            // {Fractional Exponent}
            else if (exponent > 0 && exponent < 1)
                // Return
                return root(base, 1 / exponent);

            // {Fractional Exponent}
            else if (!(static_cast<int>(exponent) % 2)) {
                // Initialization > Half Power
                long double halfPower = pow(base, exponent / 2);

                // Return
                return halfPower * halfPower;
            }

            // {Integer Exponent} Return
            return base * pow(base, exponent - 1);
    }

    /* Main */
    int main(int argc, char* argv[]) {
        // Initialization > (Base, Exponent)
        long double base, exponent;

        // Standard > C Output
        std::cout << "Program to calculate the rational exponent of a number.\n" << std::endl;

        // Standard > C (Output, Input)
        std::cout << "Base: ";
        std::cin >> base;

        // Standard > C (Output, Input)
        std::cout << "Exponent: ";
        std::cin >> exponent;

        // Standard > C Output
        std::cout << std::endl;

        // Standard > C Output
        std::cout << "Power: " << pow(base, exponent);

        // Return
        return 0;
    }
