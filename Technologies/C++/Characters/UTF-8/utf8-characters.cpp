/* Import */
#include <codecvt> // Code Converter
#include <cuchar> // C Universal Characters
#include <fstream> // File Stream

#include <stdlib.h> // Standard Library
#include <unistd.h> // Unix Standard Library

/* Global > Total --- NOTE (Lapys) -> Number of characters to write. */
const unsigned long total = -1; // NOTE (Lapys) -> Hopefully 2 ^ 32.

// Modification > Standard [Library] > Wide End-Line
inline namespace std { std::wostream& wendl(std::wostream& wideOutputStream) { return wideOutputStream.put(L'\n').put(L'\r').flush(); } }

/* Function > Get Progress [Bar] Buffer
        --- NOTE (Lapys) -> Example arguments: 64%, 4 GB, 250-character width.
        --- WARN (Lapys) ->
            - Byte size is also mentioned.
            - Not built for Buffer Length`s less than 27.
*/
const char* getProgressBuffer(const float completionRate, const unsigned long long totalBytesize, const unsigned BUFFER_LENGTH = 100u) {
    // Declaration > (Buffer, Completion Length)
    static char *buffer = NULL;
    const unsigned completionLength = (unsigned(completionRate) * BUFFER_LENGTH) / 100u;

    // Deletion; Update > Buffer
    delete[] buffer;
    buffer = new char[BUFFER_LENGTH + 1u];

    for (unsigned iterator = 0u; iterator ^ BUFFER_LENGTH; iterator += 1u) *(buffer + iterator) = '\xB0';
    for (unsigned iterator = 0u; iterator ^ completionLength; iterator += 1u) *(buffer + iterator) = '\xDB';
    *(buffer + BUFFER_LENGTH) = '\0';

    // Logic
    if (BUFFER_LENGTH > 10u)
        // Logic
        if (BUFFER_LENGTH < 28u) {
            // Declaration > Completion Rate ...
            char completionRateBuffer[3 + 1 + 3 + 1] {0};
            unsigned completionRateBufferLength = sizeof(completionRateBuffer);

            // [Completion Rate]
            {
                // Declaration > Completion Rate (Characteristics, Mantissa)
                unsigned completionRateCharacteristics = unsigned(completionRate);
                float completionRateMantissa = completionRate - completionRateCharacteristics;

                // Update > Completion Rate Buffer
                *(completionRateBuffer + 4) = (((unsigned char) (completionRateMantissa *= 10.0f)) % 10u) + 48u;
                *(completionRateBuffer + 5) = (((unsigned char) (completionRateMantissa *= 10.0f)) % 10u) + 48u;
                *(completionRateBuffer + 6) = (((unsigned char) (completionRateMantissa *= 10.0f)) % 10u) + 48u;
                *(completionRateBuffer + 7) = '%';
                *(completionRateBuffer + 3) = '.';
                *(completionRateBuffer + 2) = (completionRateCharacteristics % 10u) + 48u; completionRateCharacteristics /= 10u;
                *(completionRateBuffer + 1) = (completionRateCharacteristics % 10u) + 48u; completionRateCharacteristics /= 10u;
                *completionRateBuffer = (completionRateCharacteristics % 10u) + 48u; completionRateCharacteristics /= 10u;
            }

            // [Details Buffer]
            {
                // : Declaration > Details Buffer ...
                // : ... Update > Buffer
                const unsigned detailsBufferPivot = (BUFFER_LENGTH - completionRateBufferLength) / 2u;
                for (unsigned iterator = 0u; iterator ^ completionRateBufferLength; iterator += 1u) *(buffer + detailsBufferPivot + iterator) = *(completionRateBuffer + iterator);
            }
        }

        else {
            // Declaration > (Byte Size, Completion Rate) ...
            const unsigned long long bytesize = totalBytesize * (completionRate / 100.0f);
            char bytesizeBuffer[(4 + 1 + 5) + 3] {0}; // NOTE (Lapys) -> Does not work without the extra memory for some reason.
            unsigned bytesizeBufferLength = 0u;

            char completionRateBuffer[3 + 1 + 5 + 1] {0};
            unsigned completionRateBufferLength = sizeof(completionRateBuffer);

            // [Byte Size]
            {
                // Logic --- NOTE (Lapys) -> If byte size details are to be outputted.
                if (totalBytesize) {
                    // Declaration > Size
                    long double size = bytesize;

                    // Update > Size
                    while (size >= 1024.00) size /= 1024.00;

                    // [...] --- NOTE (Lapys) -> Write the Size to the Size Buffer.
                    {
                        // Declaration > Size (Characteristics, Mantissa)
                        unsigned short sizeCharacteristics = (unsigned short) size;
                        float sizeMantissa = size - sizeCharacteristics;

                        // Logic > ... > Update > Byte Size Buffer --- MINIFY (Lapys)
                        // : Characteristics : Mantissa
                        if (sizeCharacteristics) { while (sizeCharacteristics) { *(bytesizeBuffer + bytesizeBufferLength) = (sizeCharacteristics % 10u) + 48u; bytesizeBufferLength += 1u; sizeCharacteristics /= 10u; } for (unsigned iterator = 0u, length = bytesizeBufferLength / 2u; iterator ^ length; iterator += 1u) { const char bytesizeBufferCharacter = *(bytesizeBuffer + iterator); *(bytesizeBuffer + iterator) ^= *(bytesizeBuffer + (bytesizeBufferLength - iterator - 1u)); *(bytesizeBuffer + (bytesizeBufferLength - iterator - 1u)) ^= *(bytesizeBuffer + iterator); *(bytesizeBuffer + iterator) ^= *(bytesizeBuffer + (bytesizeBufferLength - iterator - 1u)); } }
                        else { *(bytesizeBuffer + bytesizeBufferLength) = '0'; bytesizeBufferLength += 1u; }

                        if (sizeMantissa) { *(bytesizeBuffer + bytesizeBufferLength) = '.'; bytesizeBufferLength += 1u; while (sizeMantissa && sizeMantissa < 10000.0f && sizeMantissa - (unsigned short) sizeMantissa) { sizeMantissa *= 10.0f; *(bytesizeBuffer + bytesizeBufferLength) = (((unsigned char) sizeMantissa) % 10u) + 48u; bytesizeBufferLength += 1u; } }
                    }

                    // Update > Byte Size Buffer
                    *(bytesizeBuffer + bytesizeBufferLength) = ' ';
                    bytesizeBufferLength += 1u;

                    /* Logic > Update > Byte Size Buffer
                            : Gigabytes : Megabytes : Kilobytes : Bytes
                    */
                    if (bytesize >= 1024uLL * 1024uLL * 1024uLL) { *(bytesizeBuffer + bytesizeBufferLength) = 'G'; bytesizeBufferLength += 1u; *(bytesizeBuffer + bytesizeBufferLength) = 'B'; bytesizeBufferLength += 1u; }
                    else if (bytesize >= 1024uLL * 1024uLL) { *(bytesizeBuffer + bytesizeBufferLength) = 'M'; bytesizeBufferLength += 1u; *(bytesizeBuffer + bytesizeBufferLength) = 'B'; bytesizeBufferLength += 1u; }
                    else if (bytesize >= 1024uLL) { *(bytesizeBuffer + bytesizeBufferLength) = 'K'; bytesizeBufferLength += 1u; *(bytesizeBuffer + bytesizeBufferLength) = 'B'; bytesizeBufferLength += 1u; }
                    else { *(bytesizeBuffer + bytesizeBufferLength) = 'b'; bytesizeBufferLength += 1u; *(bytesizeBuffer + bytesizeBufferLength) = 'y'; bytesizeBufferLength += 1u; *(bytesizeBuffer + bytesizeBufferLength) = 't'; bytesizeBufferLength += 1u; *(bytesizeBuffer + bytesizeBufferLength) = 'e'; bytesizeBufferLength += 1u; if (bytesize ^ 1uLL) { *(bytesizeBuffer + bytesizeBufferLength) = 's'; bytesizeBufferLength += 1u; } }
                }
            }

            // [Completion Rate]
            {
                // Declaration > Completion Rate (Characteristics, Mantissa)
                unsigned completionRateCharacteristics = unsigned(completionRate);
                float completionRateMantissa = completionRate - completionRateCharacteristics;

                // Update > Completion Rate Buffer
                *(completionRateBuffer + 4) = (((unsigned char) (completionRateMantissa *= 10.0f)) % 10u) + 48u;
                *(completionRateBuffer + 5) = (((unsigned char) (completionRateMantissa *= 10.0f)) % 10u) + 48u;
                *(completionRateBuffer + 6) = (((unsigned char) (completionRateMantissa *= 10.0f)) % 10u) + 48u;
                *(completionRateBuffer + 7) = (((unsigned char) (completionRateMantissa *= 10.0f)) % 10u) + 48u;
                *(completionRateBuffer + 8) = (((unsigned char) (completionRateMantissa *= 10.0f)) % 10u) + 48u;
                *(completionRateBuffer + 9) = '%';
                *(completionRateBuffer + 3) = '.';
                *(completionRateBuffer + 2) = (completionRateCharacteristics % 10u) + 48u; completionRateCharacteristics /= 10u;
                *(completionRateBuffer + 1) = (completionRateCharacteristics % 10u) + 48u; completionRateCharacteristics /= 10u;
                *completionRateBuffer = (completionRateCharacteristics % 10u) + 48u; completionRateCharacteristics /= 10u;
            }

            // [Details Buffer]
            {
                // Declaration > Details Buffer ...
                unsigned detailsBufferLength = 0u;
                const unsigned detailsBufferPivot = (BUFFER_LENGTH - (bytesizeBufferLength + completionRateBufferLength + 3u)) / 2u;

                // ... Update > Buffer
                for (unsigned iterator = 0u; iterator ^ completionRateBufferLength; iterator += 1u) { *(buffer + (detailsBufferLength + detailsBufferPivot)) = *(completionRateBuffer + iterator); detailsBufferLength += 1u; }
                *(buffer + detailsBufferLength + detailsBufferPivot) = ' '; detailsBufferLength += 1u;
                *(buffer + detailsBufferLength + detailsBufferPivot) = '|'; detailsBufferLength += 1u;
                *(buffer + detailsBufferLength + detailsBufferPivot) = ' '; detailsBufferLength += 1u;
                for (unsigned iterator = 0u; iterator ^ bytesizeBufferLength; iterator += 1u) { *(buffer + (detailsBufferLength + detailsBufferPivot)) = *(bytesizeBuffer + iterator); detailsBufferLength += 1u; }
            }
        }

    // Return
    return buffer;
}

/* Main */
int main(int argumentCount, char* argumentVector[]) {
    // Initialization > (File Stream, ...)
    std::wfstream fileStream;
    unsigned char totalCardinality = 0u;

    // Update > (File Stream, ...)
    fileStream.imbue(std::locale(fileStream.getloc(), new std::codecvt_utf16<wchar_t, 0x10FFFF, static_cast<std::codecvt_mode>(std::consume_header | std::little_endian | std::generate_header)>(1)));
    fileStream.open("utf8-characters.txt", std::ios::binary | std::ios::out);

    for (unsigned long iterator = total; iterator; iterator /= 10uL) totalCardinality += 1u;

    // [Main]
    {
        // Declaration > Progress Buffer ...
        const unsigned char progressBufferLength = (((unsigned char) ::rand()) % 100u) + 10u;
        unsigned long progressBufferRefreshRate = (unsigned long) (total * 0.000116);

        // Update > Progress Buffer ...
        (progressBufferRefreshRate < 5000uL) && (progressBufferRefreshRate = 5000uL);
        (progressBufferRefreshRate < 1uL) && (progressBufferRefreshRate = 1uL);

        // Loop --- NOTE (Lapys) -> Iterate through the character set.
        for (unsigned long iterator = 0uL; iterator ^ total; iterator += 1uL) {
            // Declaration > (Character, ...)
            const wchar_t character = iterator;

            unsigned long long index = ((unsigned long long) iterator) + 1uLL;
            unsigned char indexCardinality = 0u; // NOTE (Lapys) -> For padding the index.

            // Update > ...
            for (unsigned long long subiterator = index; subiterator; subiterator /= 10uLL) indexCardinality += 1u;

            for (unsigned char subiterator = totalCardinality - indexCardinality; subiterator; subiterator -= 1u) fileStream << L'0';
            fileStream << iterator << L": '" << character << L'\'';
            if (iterator ^ total) fileStream << std::wendl;

            // Logic --- NOTE (Lapys) -> Refresh the progress buffer.
            if (!(iterator % progressBufferRefreshRate)) {
                // ...
                ::write(STDOUT_FILENO, "\r ", 2);
                for (unsigned char subiterator = 0u; subiterator ^ progressBufferLength; subiterator += 1u) ::write(STDOUT_FILENO, " ", 1);
                ::write(STDOUT_FILENO, " \r", 2);

                ::write(STDOUT_FILENO, "[", 1);
                ::write(STDOUT_FILENO, ::getProgressBuffer((100.0f * float(iterator)) / float(total), total, progressBufferLength /* -> FLAG */), progressBufferLength);
                ::write(STDOUT_FILENO, "]", 1);
            }
        }

        // ...
        ::write(STDOUT_FILENO, "\r", 1);

        ::write(STDOUT_FILENO, "[", 1);
        ::write(STDOUT_FILENO, ::getProgressBuffer(100.0f, total, progressBufferLength), progressBufferLength);
        ::write(STDOUT_FILENO, "]", 1);
    }

    // Update > File Stream
    fileStream.close();

    // Return
    return 0;
}
