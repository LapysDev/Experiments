/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Sum
    template <typename data>
    long double sum(data array[]) {
        // Initialization > (Iterator, Length, Sum)
        int iterator = 0, length = sizeof(array) - 1;
        long double sum = 0;

        // Loop > Update > Sum
        for (iterator; iterator != length; iterator += 1)
            sum += static_cast<long double>(*(array + iterator));

        // Return
        return sum;
    }

    // Main
    int main(int argc, char* argv[]) {
        // Initialization > (Iterator, Length)
        int iterator = 0, length;

        // Standard > C Output
        std::cout << "Program to print the sum of a set of numbers.\n" << std::endl;

        // Standard > C (Output, Input)
        std::cout << "Length: ";
        std::cin >> length;

        // Initialization > Array
        double array[length];

        /* Loop
                Index Array.

            > Standard > C (Output, Input)
        */
        for (iterator; iterator != length; iterator += 1) {
            std::cout << "   " << iterator << ": ";
            std::cin >> array[iterator];
        }

        // Standard > C Output
        std::cout << std::endl;
        std::cout << "Sum: " << sum(array);

        // Return
        return 0;
    }
