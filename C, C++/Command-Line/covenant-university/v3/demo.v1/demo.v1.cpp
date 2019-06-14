/* Library */
    // File Stream
    #include <fstream>

    // Input-Output Stream
    #include <iostream>

/* Function */
    /* Main
            --- NOTE ---
                #Lapys: Did you know the `main` function is part of an unknown namespace object?
    */
    int main(int argc, char* argv[]) {
        /* Standard > C Output
                --- NOTE ---
                    #Lapys:
                        - There is also the `ios` namespace (do some research there).
                        - It has members that act as file-based options.
        */
        std::cout << "Program to create & modify files on a local machine.\n" << std::endl;

        /* Initialization > (Input, Output) (File)
                --- NOTE ---
                    #Lapys: Could be re-written as:
                        std::ifstream inputFile("input.txt");
                        std::ofstream outputFile("output.txt");
        */
        std::ifstream inputFile;
        std::ofstream outputFile;
        std::fstream file;

        /* (Input, Output) File > Open
                --- NOTE ---
                    #Lapys:
                        - Open the respective files.
                        - If the directory does not exist for the Input File, it fails (becomes `false`).

                        - If the directory does not exist for the Output File, it creates the file.
                            Otherwise it clears the file content.

                        - You can test for if the file fails or not via the `is_open` method.
        */
        inputFile.open("input.txt");
        outputFile.open("output.txt");

        /* Logic
                [if statement]
        */
        if (outputFile) {
            outputFile << "This is a sample text file for output";
            outputFile.put('.');
        }

        // Standard > C Output
        std::cout << "Input File:\n    ";

        /* Loop
                [while statement]

                --- NOTE ---
                    #Lapys: Output files have no `eof` or `get` methods.
        */
        while (!inputFile.eof()) {
            // Initialization > (Character, Line)
            char character;
            std::string line;

            /* Logic
                    [if:else statement]

                    --- NOTE ---
                        #Lapys: Character-by-character iterations are more accurate, but slower.
            */
            if (false) {
                // Input File > Get > Character
                inputFile.get(character);

                // Standard > C Output
                std::cout << character;
            }

            else {
                // Get Line > Input File > Line
                getline(inputFile, line);

                // Standard > C Output
                std::cout << line;
            }
        }

        // (Input, Output) File > Close
        inputFile.close();
        outputFile.close();

        // Return
        return 0;
    }
