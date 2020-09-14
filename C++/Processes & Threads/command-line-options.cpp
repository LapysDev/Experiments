/* Import */
#include <stdio.h> // Standard Input/ Output
#include <stdlib.h> // Standard Library
#include <string.h> // String

/* Function > Put Argument String --- NOTE (Lapys) -> Adheres to basic string delimiting, unlike the native `char argv[]` or `CommandLineToArgv(...)` implementations. */
template <class print_t, class output_t, class... types>
void putArgumentString(char const arguments[], int const initialIndex, print_t print, output_t output, types... parameters) {
    // Initialization > (Argument, Delimiter, Index ..., Paired)
    char const *argument = arguments;
    char delimiter = '\0';
    int index = initialIndex;
    char indexString[10] = {};
    bool paired = false;

    // Loop > Logic
    for (char const *const end = arguments + (::strlen(arguments) + 1u), *iterator = arguments; end != iterator; ++iterator)
    switch (*iterator) {
        /*null_break:   */ case '\0': delimiter = '\0'; goto whitespace_break; break;
        /*string_break: */ case '"': case '\'': {
            // Logic --- NOTE (Lapys) ->
            if ('\0' == delimiter) { // Start of the string-delimited argument or argument value.
                // ... Update > Paired
                for (char const *subiterator = iterator - 1; arguments != subiterator; --subiterator)
                if ('=' == *subiterator) { paired = true; break; }
                else if (' ' ^ *subiterator) { paired = false; break; }

                // ... Update > (Argument, Delimiter)
                if (false == paired) argument = iterator + 1;
                delimiter = *iterator;
            }

            else { // End of the string-delimited argument.
                // Initialization > Escaped
                bool escaped = false;

                // ... Update > Escaped
                for (char const *subiterator = iterator - 1; arguments != subiterator; --subiterator)
                if ('\\' == *subiterator) escaped = false == escaped;
                else break;

                // Logic
                if (false == escaped) {
                    // Print
                    print(output, "[", 1u, parameters...);
                    print(output, indexString, ::sprintf(indexString, "%i", index++), parameters...);
                    print(output, "]: \"", 4u, parameters...);

                    // Logic > ... Print
                    if (false == paired) print(output, argument, iterator - argument, parameters...);
                    else {
                        paired = false;

                        while (delimiter ^ *argument) print(output, argument++, 1u, parameters...);
                        ++argument, print(output, argument, iterator - argument, parameters...);
                    }

                    // Print
                    print(output, "\"\r\n", 3u, parameters...);

                    // ... Update > Argument ...
                    argument = iterator; delimiter = '\0'; // NOTE (Lapys) -> Move to the argument.
                    while (' ' == *++argument) ++iterator; // NOTE (Lapys) -> Skip whitespace after string-delimiter.
                }
            }
        } break;

        whitespace_break: case ' ': if ('\0' == delimiter && argument != iterator) {
            // Print ...
            print(output, "[", 1u, parameters...);
            print(output, indexString, ::sprintf(indexString, "%i", index++), parameters...);
            print(output, "]: \"", 4u, parameters...);
            print(output, argument, iterator - argument, parameters...);
            print(output, "\"\r\n", 3u, parameters...);

            argument = iterator + 1; // NOTE (Lapys) -> Move to the argument.
        } break;
    }
}

/* Logic */
#if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
    /* Import */
    #ifdef q4_WCE // Input/ Output
    #   include <io.h>
    #endif
    #include <stdint.h> // Standard Integers
    #include <wchar.h> // Wide Characters -- Window
    #include <windows.h> // Windows

    /* Main */
    int WinMain(HINSTANCE const, HINSTANCE const, LPSTR const arguments, int const) {
        // Initialization > Console Active Screen Buffer Handle
        HANDLE consoleActiveScreenBufferHandle = INVALID_HANDLE_VALUE;

        // Logic > ... Update > Console Active Screen Buffer Handle --- NOTE (Lapys) -> Get an output `HANDLE`.
        if (INVALID_HANDLE_VALUE == consoleActiveScreenBufferHandle) consoleActiveScreenBufferHandle = ::CreateFileW(L"CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, NULL);
        if (INVALID_HANDLE_VALUE == consoleActiveScreenBufferHandle) consoleActiveScreenBufferHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
        if (INVALID_HANDLE_VALUE == consoleActiveScreenBufferHandle) {
            // Initialization > Handle
            #ifdef q4_WCE
                intptr_t const handle = ::_fileno(stdout);
            #else
                intptr_t const handle = ::_fileno(stdout); // --> ::_get_osfhandle(...)
            #endif

            // ... Update > ...
            ::FlushFileBuffers((HANDLE) handle);
            consoleActiveScreenBufferHandle = ::CreateFileMappingW((HANDLE) handle, NULL, PAGE_READONLY, 0, 0, NULL);
        }

        // Logic
        if (INVALID_HANDLE_VALUE == consoleActiveScreenBufferHandle) ::exit(EXIT_FAILURE); // ERROR (Lapys)
        else if (0 == ::SetConsoleActiveScreenBuffer(consoleActiveScreenBufferHandle)) ::exit(EXIT_FAILURE); // ERROR (Lapys)
        else {
            // Constant > Path
            LPWSTR const path = (LPWSTR) ::malloc(MAX_PATH * sizeof(WCHAR));

            // Logic > ...
            if (NULL == path) { ::CloseHandle(consoleActiveScreenBufferHandle); ::exit(EXIT_FAILURE); } // ERROR (Lapys)
            else if (0 == ::GetModuleFileNameW(NULL, path, MAX_PATH)) { ::CloseHandle(consoleActiveScreenBufferHandle); ::free(path); ::exit(EXIT_FAILURE); } // ERROR (Lapys)
            else {
                // Initialization > (Argument, Length, Size)
                LPSTR argument;
                int const length = (int) ::wcslen(path);
                int const size = ::WideCharToMultiByte(CP_UTF8, 0x0, path, length, NULL, 0, NULL, NULL);

                // Update > Argument ...
                argument = (LPSTR) ::malloc(size);

                // Logic > ...
                if (NULL == argument) { ::CloseHandle(consoleActiveScreenBufferHandle); ::free(path); ::exit(EXIT_FAILURE); } // ERROR (Lapys)
                else { // NOTE (Lapys) -> Escape characters from the command-line itself (e.g.: `^`) aren't evaluated within the `arguments`.
                    // Update > Argument; ...
                    ::WideCharToMultiByte(CP_UTF8, 0x0, path, -1, argument, length, NULL, NULL);
                    ::free(path);

                    // Print
                    // : Deletion
                    ::WriteFile(consoleActiveScreenBufferHandle, "[0]: \"", 6u, NULL, NULL);
                    ::WriteFile(consoleActiveScreenBufferHandle, argument, length, NULL, NULL);
                    ::WriteFile(consoleActiveScreenBufferHandle, "\"\r\n", 3u, NULL, NULL);

                    ::free(argument);

                    // ...
                    // : Deletion
                    putArgumentString(arguments, 1, &::WriteFile, consoleActiveScreenBufferHandle, (LPDWORD) NULL, (LPOVERLAPPED) NULL);
                    ::CloseHandle(consoleActiveScreenBufferHandle);
                }
            }
        }

        // Return
        return EXIT_SUCCESS;
    }

#elif defined(__gnu_linux__) || defined(linux) || defined(__linux) || defined(__linux__)
    /* Import */
    #include <unistd.h> // UNIX Standard Library

    /* Main */
    int main(void) {
        // Constant > Stream
        FILE const *stream = ::fopen("proc/self/cmdline");

        // Logic
        if (NULL == stream) ::exit(EXIT_FAILURE); // ERROR (Lapys)
        else {
            // Constant > (Position, Length, Arguments)
            long const position = ::ftell(stream);
            long const length = ::fseek(stream, 0L, SEEK_END), ::ftell(stream);
            char *const arguments = (char*) ::malloc((length + 1u) * sizeof(char));

            // Logic
            if (NULL == arguments) { ::fclose(stream); ::exit(EXIT_FAILURE); } // ERROR (Lapys)
            else {
                // Update > Arguments ...
                ::fseek(stream, 0L, SEEK_SET);
                ::fread(arguments, sizeof(char), length, stream);
                // --> ::fseek(stream, position, SEEK_SET);
                *(arguments + length) = '\0';

                // ...
                // : Deletion
                putArgumentString(arguments, 0, &::write, STDOUT_FILENO);
                ::fclose(stream);
            }
        }

        // Return
        return EXIT_SUCCESS;
    }

#else
    /* Main */
    int main(void) { return EXIT_FAILURE; }
#endif
