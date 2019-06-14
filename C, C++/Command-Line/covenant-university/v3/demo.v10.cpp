/* Library */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Print
    void print(char* arg) { std::cout << "Character Array Print: " << arg; }
    void print(double arg) { std::cout << "Double-Precision Print: " << arg; }
    void print(float arg) { std::cout << "Floating-Point Print: " << arg; }
    void print(int arg) { std::cout << "Integer Print: " << arg; }

    // Print Line
    void printl() { std::cout << std::endl; }

    /* Main */
    int main(int argc, char* argv[]) {
        // Print
        print("Hello, World!"); printl();
        print(2.35); printl();
        print(2.35f); printl();
        print(2); printl();

        // Return
        return 0;
    }
