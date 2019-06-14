/* Library */
    // Bits > Standard C++ Header
    #include <bits/stdc++.h>

    // C Time
    #include <ctime>

    // Input-Output Stream
    #include <iostream>

/* Function */
    // N-th Root
    long double nthRoot(int number, int proponent) {
        // Standard > Seed Random > (Standard > Time)
        std::srand(std::time(NULL));

        /* Initialization > ((Previous) Result, Tolerance, Limit)
                --- NOTE ---
                    #Lapys:
                        - Initially guess a random number between 0 and 9 for the previous result.
                        - The lower the tolerance, the more `precise` the result.
                        - Initialize the difference between two roots via the limit.
        */
        long double previousResult = std::rand() % 10,
            tolerance = .001, limit = 2147483647, result;

        /* Loop
                [while statement]

                --- NOTE ---
                    #Lapys: Loop until desired accuracy is reached.

            > Update > ((Previous) Result, Limit)
        */
        while (limit > tolerance) {
            /* Update > Result
                    --- NOTE ---
                        #Lapys: Calculate result from previous value via Newton`s method.
            */
            result = ((proponent - 1.0) * previousResult + static_cast<double>(number) / std::pow(previousResult, proponent - 1)) / static_cast<double>(proponent);

            // Update > (Limit, Previous Result)
            limit = result - previousResult;
            (limit < 0) && (limit = -limit);
            previousResult = result;
        }

        // Return
        return result;
    }

    /* Main */
    int main(int argc, char* argv[]) {
        // Initialization > (Number, Proponent)
        long double number, proponent;

        // Standard > C Output
        std::cout << "Program to calculate the nth-root of a number.\n" << std::endl;

        // Standard > C (Output, Input)
        std::cout << "Number: ";
        std::cin >> number;

        // Standard > C (Output, Input)
        std::cout << "Proponent: ";
        std::cin >> proponent;

        // Standard > C Output
        std::cout << std::endl;

        // Standard > C Output
        std::cout << "N-th Root: " << nthRoot(number, proponent);

        // Return
        return 0;
    }
