/* Library Files */
    // Windows Header
    #include <windows.h>

/* Utilities */
    // Standard
    using namespace std;

/* Function */
    /* Main */
    int main(int argc, char* argv[]) {
        // Initialization > (Console, Iterator)
        HANDLE console; unsigned char iterator = 1;

        // Update > Console
        console = GetStdHandle(STD_OUTPUT_HANDLE);

        /* Loop
                [for statement]

            > (Set Console Text Attribute > Console), (Standard > C Output)
        */
        for (iterator; iterator ^ 255; iterator += 1) {
            SetConsoleTextAttribute(console, iterator);
            std::cout << iterator << ". I want to be nice today!" << std::endl;
        }

        // Return
        return 0;
    }
