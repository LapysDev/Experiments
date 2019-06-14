/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities*/
    // Namespace > Standard
    using namespace std;

/* Function */
    // Main
    int main() {
        // Standard > C (Input, Output)
        cout << "Program to countdown a set of integers:\n" << endl;

        /* Loop
                [for statement]
        */
        for (int iterator = 0; iterator != 10; iterator += 1) {
            // Standard > C Output
            cout << iterator << ", ";

            /* Logic
                    [if statement]
            */
            if (iterator == 7) {
                // Standard > C Output
                cout << "[Countdown Aborted]";

                // Break
                break;
            }
        }

        // Return
        return 0;
    }
