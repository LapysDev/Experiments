/* Header Files */
    // Input-Output Stream
    #include <iostream>

/* Utilities */
    // Namespace > Standard Library
    using namespace std;

/* Class */
    // Generic Class
    class Generic_Class {
        // Initialization > String
        string string = "Hello, World!";

        // Function > Print
        friend void print(Generic_Class genericObject);
    };

/* Function */
    // Print
    void print(Generic_Class genericObject) { cout << genericObject.string; }

    // Main
    int main() {
        // Print
        print(Generic_Class());

        // Return
        return 0;
    }
