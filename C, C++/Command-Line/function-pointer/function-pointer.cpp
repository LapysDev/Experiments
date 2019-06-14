/* Header Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Output
    inline void output(const char* message) { std::cout << message; }

    // Print
    inline void print(void (*printer)(const char*), const char* message) { printer(message); }

    // Main
    int main(int argc, char* argv[]) {
        // Test
        print(output, "Hello, World!");

        // Return
        return 0;
    }
