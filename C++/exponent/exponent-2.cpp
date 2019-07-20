/* Library */
    // Input-Output Stream
    #include <iostream>

/* Function */
    /* Main */
    int main(int argc, char* argv[]) {
        /* Initialization > (Base, Exponent, Denominator, Numerator)
                --- NOTE ---
                    #Lapys: Denominator and numerator of the exponent.
        */
        long double base, exponent,
            denominator = 1, numerator;

        // Standard > C Output
        std::cout << "Program to calculate the rational exponent of a number.\n" << std::endl;

        // Standard > C (Output, Input)
        std::cout << "Base: ";
        std::cin >> base;

        // Standard > C (Output, Input)
        std::cout << "Exponent: ";
        std::cin >> exponent;

        /* Loop
                [while statement]

                --- NOTE ---
                    #Lapys: Convert exponent to rational.

            > Update > (Denominator, Exponent)
        */
        while (exponent != static_cast<int>(exponent)) {
            denominator *= 10;
            exponent *= 10;
        }

        /* Update > Numerator
                --- NOTE ---
                    #Lapys: Base ^ Exponent = Base ^ (Numerator / Denominator)
        */
        numerator = exponent;

        // Initialization > (...)
        int t_x = numerator,
            t_y = denominator,
            temp;

        /* Loop
                [while statement]

            > Update > (...)
        */
        while (t_y) {
            temp = t_x % t_y;
            t_x = t_y;
            t_y = temp;
        }

        /* Update > (Denominator, Numerator)
                --- NOTE ---
                    #Lapys: Simplifying the Numerator ÷ Denominator expression to its lowest terms.
        */
        denominator /= t_x;
        numerator /= t_x;

        /* Initialization > ((Previous) Result, Tolerance, Base Raised by Numerator, Previous Result Raised by Denominator)
                --- NOTE ---
                    #Lapys:
                        - Exponent = Base ^ (Numerator / Denominator)

                        - Rising both sides to the Denominator`s power.
                            -- Base ^ Numerator = Exponent ^ Denominator

                        - Passing all terms to one side of the equation.
                            -- (Base ^ Numerator) - (Exponent ^ Denominator) = 0

                        - Finding the root with Newton`s Method.
        */
        long double result, previousResult = 1, tolerance = 1,
            baseRaisedByNumerator = base,
            previousResultRaisedByDenominator;

        /* Loop
                [for statement]

            > Update > Base Raised by Numerator
        */
        for (unsigned int iterator = 1; iterator < numerator; iterator += 1)
            baseRaisedByNumerator *= base;

        /* Loop
                [while statement]

                --- NOTE ---
                    #Lapys: The level of tolerance determines how `precision` of the result.
        */
        while (tolerance > .001) {
            // Update > Previous Result Raised by Denominator
            previousResultRaisedByDenominator = previousResult;

            /* Loop
                    [for statement]

                > Update > Previous Result Raised by Denominator
            */
            for (unsigned int iterator = 1; iterator < denominator; iterator += 1)
                previousResultRaisedByDenominator *= previousResult;

            // Update > Result
            result = previousResult - (previousResultRaisedByDenominator - baseRaisedByNumerator) / (denominator * (previousResultRaisedByDenominator / previousResult));

            /* Update > Tolerance
                    --- NOTE ---
                        #Lapys: Newton`s Method iterations.
            */
            tolerance = ((result - previousResult) / previousResult) * 100;

            // Update > (Tolerance, Previous Result)
            (tolerance < 0) && (tolerance = -tolerance);
            previousResult = result;
        }

        // Standard > C Output
        std::cout << std::endl;
        std::cout << "Result: " << result;

        // Return
        return 0;
    }
