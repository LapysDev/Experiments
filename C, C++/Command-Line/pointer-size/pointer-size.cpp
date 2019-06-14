#include <cstdlib>
#include <iostream>

class structure { int variableA, variableB; };

int main(int argc, char* argv[]) {
    structure structureA, *structureAPointer = (structure*) std::malloc(sizeof(structureA));

    std::cout << "Size [Pointer]: " << sizeof(structureAPointer) << std::endl;
    std::cout << "Size [Value]: " << sizeof(structureA) << std::endl;

    std::free(structureAPointer);

    return 0;
}
