/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities*/
    // Namespace > Standard
    using namespace std;

/* Function */
    // Main
    int main() {
        // Initialization > (Factorial, Integer)
        int factorial, integer;

        // Standard > C (Input, Output)
        cout << "Program to calculate the factorial of an integer:\n" << endl;
        cout << "Integer: ";
        cin >> integer;

        // Update > Factorial
        factorial = integer;

        // Loop > Update > Factorial
        while (integer != 1)
            factorial *= (integer -= 1);

        // Standard > C Output
        cout << "Factorial: " << factorial;

        // Return
        return 0;
    }
