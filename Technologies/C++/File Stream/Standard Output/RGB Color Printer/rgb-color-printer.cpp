/* Import */
#include <fstream> // File Stream
#include <unistd.h> // Unix Standard Library

/* Main */
int main(int argc, char* argv[]) {
    // Initialization > ...
    std::ofstream file;
    char *string = new char[19u + 1u];

    // Update > ...
    file.open("rgb-color-scheme.txt");
    *string = 'r'; *(string + 1) = 'g'; *(string + 2) = 'b'; *(string + 3) = '('; *(string + 19) = '\0';

    // Loop
    for (unsigned short colorChannelAIterator = 0u; colorChannelAIterator ^ 255u; colorChannelAIterator += 1u)
    for (unsigned short colorChannelBIterator = 0u; colorChannelBIterator ^ 255u; colorChannelBIterator += 1u)
    for (unsigned short colorChannelCIterator = 0u; colorChannelCIterator ^ 255u; colorChannelCIterator += 1u) {
        // Initialization > ((Red, Green, Blue) Color Channel Value, Length)
        unsigned char redColorChannelValue = colorChannelAIterator;
        unsigned char greenColorChannelValue = colorChannelBIterator;
        unsigned char blueColorChannelValue = colorChannelCIterator;

        unsigned char length = 4u;

        // [Write Red] ...
        if (redColorChannelValue < 10u) { *(string + length) = redColorChannelValue + 48u; length += 1u; }
        else if (redColorChannelValue < 100u) { *(string + (length + 1u)) = (redColorChannelValue % 10u) + 48u; *(string + length) = ((redColorChannelValue / 10u) % 10u) + 48u; length += 2u; }
        else { *(string + (length + 2u)) = (redColorChannelValue % 10u) + 48u; redColorChannelValue /= 10u; *(string + (length + 1u)) = (redColorChannelValue % 10u) + 48u; redColorChannelValue /= 10u; *(string + length) = (redColorChannelValue % 10u) + 48u; length += 3u; }

        // [...] ...
        length -= 1u; *(string + (length += 1u)) = ','; *(string + (length += 1u)) = ' '; length += 1u;

        // [Write Green] ...
        if (greenColorChannelValue < 10u) { *(string + length) = greenColorChannelValue + 48u; length += 1u; }
        else if (greenColorChannelValue < 100u) { *(string + (length + 1u)) = (greenColorChannelValue % 10u) + 48u; *(string + length) = ((greenColorChannelValue / 10u) % 10u) + 48u; length += 2u; }
        else { *(string + (length + 2u)) = (greenColorChannelValue % 10u) + 48u; greenColorChannelValue /= 10u; *(string + (length + 1u)) = (greenColorChannelValue % 10u) + 48u; greenColorChannelValue /= 10u; *(string + length) = (greenColorChannelValue % 10u) + 48u; length += 3u; }

        // [...] ...
        length -= 1u; *(string + (length += 1u)) = ','; *(string + (length += 1u)) = ' '; length += 1u;

        // [Write Blue] ...
        if (blueColorChannelValue < 10u) { *(string + length) = blueColorChannelValue + 48u; length += 1u; }
        else if (blueColorChannelValue < 100u) { *(string + (length + 1u)) = (blueColorChannelValue % 10u) + 48u; *(string + length) = ((blueColorChannelValue / 10u) % 10u) + 48u; length += 2u; }
        else { *(string + (length + 2u)) = (blueColorChannelValue % 10u) + 48u; blueColorChannelValue /= 10u; *(string + (length + 1u)) = (blueColorChannelValue % 10u) + 48u; blueColorChannelValue /= 10u; *(string + length) = (blueColorChannelValue % 10u) + 48u; length += 3u; }

        // ...
        length -= 1u; *(string + (length += 1u)) = ')'; *(string + (length += 1u)) = '\n'; length += 1u;

        // ...
        // file << string;
        ::write(1, string, length);
        std::fflush(stdout);

        // ...
        while (length ^ 4u) *(string + (length -= 1u)) = '\0';
    }

    // ...; Deletion
    file.close();
    delete[] string;

    // Return
    return 0;
}
