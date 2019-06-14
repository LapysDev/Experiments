/* Header Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

/* Function */
    // Main
    int main() {
        // Initialization > Number
        int number;

        // C (Output, Input)
        cout << "Input a number: ";
        cin >> number;

        // Loop > C Output
        for (int iterator = 1; iterator != 11; iterator += 1)
            cout << 8 << " x " << iterator << " = " << (8 * iterator) << endl;

        // Return
        return 0;
    }
