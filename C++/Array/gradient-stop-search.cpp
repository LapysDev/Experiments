/* Import */
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library
#include <time.h> //  Time

/* Function > Gradient Search */
signed gradient_stop_search(unsigned short* array, const unsigned searchElement, const unsigned arrayLength, const unsigned stopCount = 4u) {
    // : Constant > Stop Length
    // : Initialization > Array Iterator
    const unsigned STOP_LENGTH = (float) arrayLength / (float) stopCount;
    unsigned arrayIterator = STOP_LENGTH + (arrayLength - (STOP_LENGTH * stopCount));

    // Loop
    while (arrayIterator) {
        // Initialization > Stop Iterator
        unsigned stopIterator = stopCount;

        // Update > Array Iterator
        arrayIterator -= 1;

        // Loop
        while (stopIterator) {
            // Constant > Array Index
            const unsigned arrayIndex = arrayIterator + (stopCount * (stopIterator -= 1u));

            // Logic > Return
            if (arrayIndex < arrayLength && array[arrayIndex] == searchElement) return arrayLength - arrayIndex - 1u;
        }
    }

    // Return
    return -1;
}

/* Main */
int main(void) {
    // ...
    ::srand(::time(NULL));

    // Constant > ...
    const unsigned short ARRAY_LENGTH = (::rand() % 19u) + 1u;
    unsigned short ARRAY[ARRAY_LENGTH] { 0 };

    const unsigned short SEARCH_ELEMENT = ::rand() % 10u;
    const unsigned short STOP_COUNT = ::rand() % ARRAY_LENGTH;

    // Update > Array
    // { unsigned short iterator = ARRAY_LENGTH; while (iterator) ARRAY[iterator -= 1] = iterator; }
    { unsigned short iterator = ARRAY_LENGTH; while (iterator) ARRAY[iterator -= 1] = ::rand() % 10u; }

    // Print
    ::printf("%s", "Array: ["); { unsigned short iterator = ARRAY_LENGTH; while (iterator) { ::printf("%i", ARRAY[iterator -= 1]); if (iterator) ::printf(", "); } } ::printf("%s", "]\n");
    ::printf("Gradient Search (\n\tSearch Element: %i,\n\tStop Count: %i\n): %i", SEARCH_ELEMENT, STOP_COUNT, ::gradient_stop_search(ARRAY, SEARCH_ELEMENT, ARRAY_LENGTH, STOP_COUNT));

    // Return
    return 0;
}
