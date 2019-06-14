/* Header Files */
    // File Stream
    #include <fstream>

    // Input-Output Stream
    #include <iostream>

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

/* Function */
    /* Main */
    int main() {
        // Initialization > Number
        ifstream number("NUMBER.TXT");

        /* Logic
                [if statement]
        */
        if (number.is_open()) {
            // Initialization > (Digit, Even, Odd)
            char digit;
            ofstream even("EVEN.TXT"), odd("ODD.TXT");

            // Loop
            while (!number.eof()) {
                // Update > Digit
                number.get(digit);

                // Logic
                if (digit == '2' || digit == '4' || digit == '6' || digit == '8')
                    // Update > Even
                    even.put(digit);

                else if (digit == '3' || digit == '5' || digit == '7' || digit == '9')
                    // Update > Odd
                    odd.put(digit);
            }
        }

        // Number > Close
        number.close();

        // Return
        return 0;
    }
