#include <iostream>

int main() {
    int i = 7;
    char* p2 = reinterpret_cast<char*>(&i);

    if(p2[0] == '\x7') std::cout << "This system is little-endian\n";
    else std::cout << "This system is big-endian\n";
}
