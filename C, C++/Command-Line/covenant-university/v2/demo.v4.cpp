/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Initialization > (Balance, Rate)
        double balance, rate;

        // Standard > C (Output, Input)
        std::cout << "Program to calculate interest:\n" << std::endl;
        std::cout << "Balance: "; std::cin >> balance;
        std::cout << "Rate: "; std::cin >> rate;

        // Update > Rate
        rate /= 100;

        // Standard > C (Output, Input)
        std::cout << std::endl;
        std::cout << "The proceeding interest after 1 year: " << (balance = balance + (balance * rate)) << std::endl;
        std::cout << "The interest after 2 years: " << balance + (balance * rate);

        // Return
        return 0;
    }
