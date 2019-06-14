/* Library Files */
    // Input-Output Stream
    #include <iostream>

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Initialization > Score
        int score;

        // Standard > C (Output, Input)
        std::cout << "Program to test the grade of a student:\n" << std::endl;
        std::cout << "Score: ";
        std::cin >> score;

        // Logic > (Standard > C Output)
        if (score > 69 && score < 101) std::cout << "Grade: A\n\nJob well done!";
        else if (score > 59 && score < 70) std::cout << "Grade: B\n\nGreat performance";
        else if (score > 49 && score < 60) std::cout << "Grade: C\n\nYou can do better";
        else if (score > 44 && score < 50) std::cout << "Grade: D\n\nThere`s always room for improvement";
        else if (score < 46) std::cout << "Grade F\n\nThe best revenge for failure is success";


        // Return
        return 0;
    }
