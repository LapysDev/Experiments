/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities*/
    // Namespace > Standard
    using namespace std;

/* Function */
    // Main
    int main() {
        // Initialization > (First Iteration, Iteration Count, Length)
        bool firstIteration = false;
        int iterationCount, length;

        // Standard > C (Input, Output)
        cout << "Program to repeat a set of statements:\n" << endl;
        cout << "Iteration Count: ";
        cin >> iterationCount;

        // Update > Length
        length = iterationCount;

        /* Loop
                [while statement]
        */
        do {
            /* Logic
                    [if:else statement]
            */
            if (firstIteration) {
                // Standard > C Output
                cout << (length - iterationCount) + 1 << ". Repeated set of statements..." << endl;

                // Update > Iteration Count
                iterationCount -= 1;
            }

            else {
                // Standard > C Output
                cout << "*. First executed set of statements..." << endl;

                // Update > First Iteration
                firstIteration = true;
            }
        } while (iterationCount);

        // Standard > C Output
        cout << "\nFinish!";

        // Return
        return 0;
    }
