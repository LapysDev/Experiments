#include <stdlib.h>

// Format each element of an (int) array.
void build(int array[], int length, int (&handler)(int element)) {
   int iterator = length;
   while (iterator) { iterator -= 1; array[iterator] = handler(array[iterator]); }
}

// Return a set of the multiples of Number ÷ Count lower than or equal to the Number.
int* step(int number, int count) {
    float difference = number / count;
    int* steps = (int*) malloc(20) /* This was an array literal in JavaScript but I think this counts... :P */;
    bool hasStepped = false;

    while (count) {
        steps[count -= 1] = (hasStepped ? steps[count + 1] : 0) + difference;
        hasStepped = true;
    }

     return steps;
}

/* Assert if an element is within an (int) array */
bool includes(int array[], int element, int length, int iterationStopCount = 4) {
    if (length == 1)
        return array[0] == element;

    else if (length) {
        int iterator = length;

        // Perform a Reversed Linear Search
        if (iterationStopCount == 1)
             while (iterator) if (array[iterator -= 1] == element) return true;

        // Perform what I call a "Gradient Search"
        else {
            /*
                This condition is here because I do not know
                the algorithm behaves otherwise.
            */
            if (iterationStopCount > length) iterationStopCount = length;

            bool hasRedundantIterations = length % iterationStopCount;
            int* iterationStops = step(length, iterationStopCount),
                iterationStopsLength = iterationStopCount;

            build(iterationStops, [](int step) { return step >> 0; });

            iterator -= iterationStops[1];
            iterationStops[0] = 0;

            if (iterator != -1)
            while (iterator) {
                int iterationStopsIterator = iterationStopsLength;

                iterator -= 1;

                while (iterationStopsIterator)
                if (array[iterator + iterationStops[iterationStopsIterator -= 1]] == element)
                    return true;
            }
        }
    }

    return false;
}
