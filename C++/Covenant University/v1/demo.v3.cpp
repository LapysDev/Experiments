#include <iostream>
using namespace std;
int main() {
    // Create a space in memory.
    std::string name;

    // Printing this to the screen (as a prompt).
    std::cout << "What is your name: ";

    // Get user`s input from their keyboard and
    // push the input to Name.
    std::cin >> name;

    // Print this to screen.
    std::cout << "\nYour name is " << name;

    return 0;
}
