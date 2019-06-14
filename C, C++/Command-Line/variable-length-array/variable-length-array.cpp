/* Import */
    // C Standard Input-Output
    #include <cstdio>

/* Function */
    // Add To Front
    void addToFront(int array[], unsigned int index) {}
    template <typename type, typename... types> void addToFront(int array[], unsigned int index, type arg, types... args) { *(array + ((index += 1) - 1)) = arg; addToFront(array, index, args...); }

    // Get Arguments Length
    inline unsigned int getArgumentsLength() { return 0; }
    template <typename type, typename... types> const unsigned int getArgumentsLength(type arg, types... args) { return 1 + getArgumentsLength(args...); }

    // Get Variable Length Array
    template <typename... types>
    int* getVariableLengthArray(types... args) {
        // Initialization > (Length, Array)
        unsigned int length = getArgumentsLength(args...);
        int* array = new int[length];

        // Add to Front
        addToFront(array, 0, args...);

        // Return
        return array;
    }

    // Main
    int main(int argc, char* argv[]) {
        // Initialization > Array
        int* array = getVariableLengthArray(1, 0, 1, 2, 3, 5);

        // Print
        std::printf("[%i, ", *array);
        std::printf("%i, ", *(array += 1));
        std::printf("%i, ", *(array += 1));
        std::printf("%i, ", *(array += 1));
        std::printf("%i, ", *(array += 1));
        std::printf("%i]", *(array += 1));

        // Return
        return 0;
    }
