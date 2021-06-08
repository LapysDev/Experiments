#include <cerrno>
#include <clocale>
#include <cstdio>
#include <cstdlib>
#include <cwchar>

/* ... */
wchar_t const* to_hex(std::wint_t character) {
    wchar_t *iterator;
    static wchar_t string[8];

    if (character < 0) {
        for (iterator = const_cast<wchar_t*>(to_hex(-character)) + 7; iterator != string; --iterator)
        *iterator = *(iterator - 1);

        *iterator = L'-';
    }

    else {
        string[6] = L'\0';
        string[7] = L'\0';

        iterator = string + 6;
        for (*--iterator = L'0'; character; character >>= 4L) *(iterator--) = L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[character % 16L];
        while (iterator != string) *(iterator--) = L'0';

        string[0] = L'0';
        string[1] = L'x';
    }

    return static_cast<wchar_t const*>(string);
}

/* Main */
int main(void) {
    FILE *const file = std::fopen("file.txt", "rb");

    if (NULL == file) {
        std::fputws(L"[I/O Error]: Could not open file for reading", stderr);
        std::exit(EXIT_FAILURE);
    }

    // ...
    std::setlocale(LC_ALL, "en_US.UTF-8");
    while (true) {
        std::wint_t const character = std::fgetwc(file);

        // ...
        if (EILSEQ == errno) {
            std::fputws(L"[Encoding Error]: Encountered byte sequence/ character does not correspond to a valid wide character code", stderr);
            std::exit(EXIT_FAILURE);
        }

        // ...
        if (WEOF == character) break;
        else {
            wchar_t buffer[7] = {character, L'\0'};
            wchar_t const *const hexadecimal = to_hex(character);
            wchar_t const *sequence = const_cast<wchar_t const*>(buffer);

            switch (character) {
                case L'\0': sequence = L"\\0"; break;
                case L'\1': sequence = L"\\1"; break;
                case L'\2': sequence = L"\\2"; break;
                case L'\3': sequence = L"\\3"; break;
                case L'\4': sequence = L"\\4"; break;
                case L'\5': sequence = L"\\5"; break;
                case L'\6': sequence = L"\\6"; break;
                case L'\7': sequence = L"\\7"; break;
                case L'\b': sequence = L"\\b"; break;
                case L'\f': sequence = L"\\f"; break;
                case L'\n': sequence = L"\\n"; break;
                case L'\r': sequence = L"\\r"; break;
                case L'\t': sequence = L"\\t"; break;
                case L'\v': sequence = L"\\v"; break;
                default: {
                    if (EOF == std::wctob(character)) {
                        wchar_t *sequenceIterator = buffer - 1;

                        for (wchar_t const *hexadecimalIterator = hexadecimal; L'\0' != *hexadecimalIterator; ++hexadecimalIterator)
                        *++sequenceIterator = *hexadecimalIterator;

                        *++sequenceIterator = L'\0';
                        buffer[0] = L'\\';
                        buffer[1] = L'u';
                    }
                } break;
            }

            std::wprintf(L"'%ls': %ls" L"\r\n", sequence, hexadecimal);
        }
    }

    std::fclose(file);

    // ...
    return EXIT_SUCCESS;
}
