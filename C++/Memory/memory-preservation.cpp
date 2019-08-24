#include <iostream>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int* array = (int*) std::malloc(3 * sizeof(int));

    std::cout << "REALLOC ROUTINE" << std::endl; std::cout << std::endl;
    std::cout << "[Initialize first three array elements]" << std::endl;
    array[0] = 1; array[1] = 0; array[2] = 1;

    std::cout << "Array: [" << array[0] << ", " << array[1] << ", " << array[2] << ']' << std::endl;

    std::cout << std::endl;

    std::cout << "[Updating byte size of array for 6 elements instead]" << std::endl;
    array = (int*) std::realloc(array, 6 * sizeof(int));

    std::cout << "Array: [" << array[0] << ", " << array[1] << ", " << array[2] << ']' << std::endl;

    std::free(array);

    std::cout << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << std::endl;

    std::cout << "MALLOC ROUTINE" << std::endl; std::cout << std::endl;
    array = (int*) std::malloc(3 * sizeof(int));

    std::cout << "[Initialize first three array elements]" << std::endl;
    array[0] = 1; array[1] = 0; array[2] = 1;

    std::cout << "Array: [" << array[0] << ", " << array[1] << ", " << array[2] << ']' << std::endl;

    std::cout << std::endl;

    std::cout << "[Updating byte size of array for 6 elements instead]" << std::endl;
    std::free(array);
    array = (int*) std::malloc(6 * sizeof(int));

    std::cout << "Array: [" << array[0] << ", " << array[1] << ", " << array[2] << ']' << std::endl;

    std::free(array);

    return 0;
}
