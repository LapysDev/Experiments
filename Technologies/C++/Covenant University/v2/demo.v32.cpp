/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Even
    void even(int number);

    // Odd
    void odd(int number);

    // Main
    int main(int argc, char* argv[]) {
        // Standard > C Output
        std::cout << "Program to determine if a number is even or odd.\n" << std::endl;

        int number;

        do {
            std::cout << "Type a number (or key in `0` to quit): ";
            std::cin >> number;
            odd(number);
        } while (number != 0);

        // Return
        return 0;
    }

    // Even
    void even(int number) {
        if (number % 2 == 0)
            std::cout << "Number is even" << std::endl;

        else
            odd(number);
    }

    // Odd
    void odd(int number) {
        if (number % 2 != 0)
            std::cout << "Number is odd" << std::endl;

        else
            even(number);
    }
