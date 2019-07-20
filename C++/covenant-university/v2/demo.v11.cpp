/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities*/
    // Namespace > Standard
    using namespace std;

/* Function */
    // Main
    int main() {
        // Initialization > Grade
        char grade = ' ';

        // Standard > C (Input, Output)
        cout << "Program to comment a grade:\n" << endl;
        cout << "Grade: ";
        cin >> grade;
        cout << "Comment: ";

        /* Logic
                [switch:case:default statement]

            > (Standard > C Output)
        */
        switch (grade) {
            case 'A': cout << "Excellent!" << endl; break;
            case 'B': cout << "Outstanding!" << endl; break;
            case 'C': cout << "Good!" << endl; break;
            case 'D': cout << "Can do better!" << endl; break;
            case 'E': cout << "Just passed!" << endl; break;
            case 'F': cout << "You failed!" << endl; break;
            default: cout << "Invalid grade";
        }

        // Return
        return 0;
    }
