/* Import */
#include <fstream> // File Stream
#include <iostream> // Input-Output Stream

/* Main */
int main(int argc, char* argv[]) {
    // Initialization > FIle
    std::ofstream file;

    // File > Open
    file.open("ascii-characters.txt");

    // Loop
    for (unsigned char iterator = 0u, length = -1; iterator ^ length; iterator += 1u) {
        // Constant > Character (Sequence)
        const char character = (short) iterator;
        char characterSequence[4] = {character, ',', ' ', '\0'};

        std::cout << '\'' << character << '\'' << (iterator == length - 1u ? "" : ", ");

        // Update > File
        file << characterSequence;
    }

    // File > Close
    file.close();

    // Return
    return 0;
}
