/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Initialization > (Base, Height)
        double base, height;

        // Standard > C (Input, Output)
        std::cout << "Program to calculate the Area of a Hypothetical Parallelogram:\n" << std::endl;
        std::cout << "Base: "; std::cin >> base;
        std::cout << "Height: "; std::cin >> height;
        std::cout << std::endl;
        std::cout << "The area of a hypothetical Parallelogram is " << (base * height);

        // Return
        return 0;
    }
