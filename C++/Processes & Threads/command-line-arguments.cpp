/* Import */
#include <stdio.h> // Standard Input/ Output
#include <stdlib.h> // Standard Library

/* Logic */
#if defined(__NT__) || defined(__TOS_WIN__) || defined(_WIN16) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__)
    /* Import */
    #ifdef q4_WCE // Input/ Output
    #   include <io.h>
    #endif
    #include <stdint.h> // Standard Integers
    #include <windows.h> // Windows

    /* Main */
    int WinMain(HINSTANCE const, HINSTANCE const, LPSTR const argumentString, int const) {
        // Initialization > Console Active Screen Buffer Handle
        HANDLE consoleActiveScreenBufferHandle = INVALID_HANDLE_VALUE;

        // Logic > ... Update > Console Active Screen Buffer Handle --- NOTE (Lapys) -> Get an output `HANDLE`.
        if (INVALID_HANDLE_VALUE == consoleActiveScreenBufferHandle) consoleActiveScreenBufferHandle = ::CreateFileW(L"CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, NULL);
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
            // Initialization > Argument ... --- WARN (Lapys) -> `CommandLineToArgvA(...)` may not be available for some implementations.
            int argumentCount;
            LPWSTR *const arguments = ::CommandLineToArgvW(::GetCommandLineW(), &argumentCount);

            // Logic -->
            if (NULL == arguments) { /* argumentString --- NOTE (Lapys) -> Parse the executable path, Parse the `argumentString` as a vector of arguments. */
                // Constant > Path
                LPWSTR const path = (LPWSTR) ::malloc(MAX_PATH * sizeof(WCHAR));

                // Logic > ...
                if (NULL == path) ::CloseHandle(consoleActiveScreenBufferHandle); // ERROR (Lapys)
                else if (0 == ::GetModuleFileNameW(NULL, path, MAX_PATH)) { ::CloseHandle(consoleActiveScreenBufferHandle); ::free(path); } // ERROR (Lapys)
                else {
                    // Initialization > (Argument, Length, Size)
                    LPSTR argument;
                    int const length = (int) ::wcslen(path);
                    int const size = ::WideCharToMultiByte(CP_UTF8, 0x0, path, length, NULL, 0, NULL, NULL);

                    // Update > Argument (Count)
                    argument = (LPSTR) ::malloc(size);
                    argumentCount = 0;

                    // Logic
                    if (NULL == argument) { ::CloseHandle(consoleActiveScreenBufferHandle); ::free(path); ::exit(EXIT_FAILURE); } // ERROR (Lapys)
                    else { // NOTE (Lapys) -> Escape characters from the command-line itself (e.g.: `^`) aren't evaluated within the `argumentString`.
                        // Initialization > (Delimiter, End)
                        CHAR delimiter = '\0';
                        LPSTR end = argumentString + ::strlen(argumentString);

                        // Update > Argument; ...
                        ::WideCharToMultiByte(CP_UTF8, 0x0, path, -1, argument, length, NULL, NULL);
                        ::free(path);

                        // Print
                        // : Deletion
                        ::WriteFile(consoleActiveScreenBufferHandle, "[0]: \"", 6u, NULL, NULL);
                        ::WriteFile(consoleActiveScreenBufferHandle, argument, length, NULL, NULL);
                        ::WriteFile(consoleActiveScreenBufferHandle, "\"\r\n", 3u, NULL, NULL);

                        ::free(argument);

                        // ... Update > (Argument, End)
                        argument = argumentString;
                        while (' ' == *(end - 1)) --end;

                        // Loop > Logic
                        for (LPSTR iterator = argumentString; ; ++iterator) {
                            // Logic
                            if (end == iterator) {
                                // Logic > ...
                                if ('\0' == delimiter) break;
                                else { // NOTE (Lapys) -> The native implementation assumes the remaining parameters are not string-delimited.
                                    // Update > (Delimiter, Iterator)
                                    delimiter = '\0';
                                    iterator = ++argument;
                                }
                            }

                            else switch (*iterator) {
                                // [String Delimited]
                                case '"': case '\'': {
                                    // Initialization > Escaped
                                    bool escaped = false;

                                    // Loop > Update > Escaped
                                    for (LPSTR subiterator = iterator - 1; argumentString < subiterator && '\\' == *subiterator; --subiterator)
                                    escaped = false == escaped;

                                    // Logic
                                    if (false == escaped) {
                                        // Logic
                                        if ('\0' == delimiter) {
                                            // Update > Delimiter
                                            delimiter = *iterator;

                                            // Logic --> `argument=value`
                                            if (false == (argumentString != iterator && '=' == *(iterator - 1))) {
                                                // ... Print
                                                ++argumentCount; {
                                                    ::WriteFile(consoleActiveScreenBufferHandle, "[", 1u, NULL, NULL);
                                                    for (int exponent = 1, value = argumentCount; exponent; exponent *= 10, value /= 10) { if (0 == value) for (char digit; exponent /= 10; ) ::WriteFile(consoleActiveScreenBufferHandle, &(digit = *("0123456789" + ((argumentCount / exponent) % 10))), 1u, NULL, NULL); }
                                                    ::WriteFile(consoleActiveScreenBufferHandle, "]: \"", 4u, NULL, NULL);
                                                    ::WriteFile(consoleActiveScreenBufferHandle, argument, iterator - argument, NULL, NULL);
                                                    ::WriteFile(consoleActiveScreenBufferHandle, "\"\r\n", 3u, NULL, NULL);
                                                }

                                                // Update > Argument
                                                argument = iterator + 1;
                                            }
                                        }

                                        else if (delimiter == *iterator) {
                                            // ... Print
                                            ++argumentCount; {
                                                ::WriteFile(consoleActiveScreenBufferHandle, "[", 1u, NULL, NULL);
                                                for (int exponent = 1, value = argumentCount; exponent; exponent *= 10, value /= 10) { if (0 == value) for (char digit; exponent /= 10; ) ::WriteFile(consoleActiveScreenBufferHandle, &(digit = *("0123456789" + ((argumentCount / exponent) % 10))), 1u, NULL, NULL); }
                                                ::WriteFile(consoleActiveScreenBufferHandle, "]: \"", 4u, NULL, NULL);

                                                if (argument == iterator) ::WriteFile(consoleActiveScreenBufferHandle, argument, 1u, NULL, NULL);
                                                else if (argument != argumentString && delimiter == *(argument - 1)) ::WriteFile(consoleActiveScreenBufferHandle, argument, iterator - argument, NULL, NULL);
                                                else {
                                                    while (delimiter ^ *argument) ::WriteFile(consoleActiveScreenBufferHandle, argument++, 1u, NULL, NULL);
                                                    ++argument; ::WriteFile(consoleActiveScreenBufferHandle, argument, iterator - argument, NULL, NULL);
                                                }

                                                ::WriteFile(consoleActiveScreenBufferHandle, "\"\r\n", 3u, NULL, NULL);
                                            }

                                            // Loop > Update > Iterator
                                            if (argument == iterator) {
                                                while (delimiter == *iterator && end != iterator) ++iterator;
                                                --iterator;
                                            }

                                            // Update > (Argument, Delimiter)
                                            argument = iterator + 1;
                                            delimiter = '\0';
                                        }
                                    }
                                } break;

                                // [Whitespace Delimited]
                                case ' ': if ('\0' == delimiter) {
                                    // Logic
                                    if (argument != iterator) {
                                        // ... Print
                                        ++argumentCount; {
                                            ::WriteFile(consoleActiveScreenBufferHandle, "[", 1u, NULL, NULL);
                                            for (int exponent = 1, value = argumentCount; exponent; exponent *= 10, value /= 10) { if (0 == value) for (char digit; exponent /= 10; ) ::WriteFile(consoleActiveScreenBufferHandle, &(digit = *("0123456789" + ((argumentCount / exponent) % 10))), 1u, NULL, NULL); }
                                            ::WriteFile(consoleActiveScreenBufferHandle, "]: \"", 4u, NULL, NULL);
                                            ::WriteFile(consoleActiveScreenBufferHandle, argument, iterator - argument, NULL, NULL);
                                            ::WriteFile(consoleActiveScreenBufferHandle, "\"\r\n", 3u, NULL, NULL);
                                        }
                                    }

                                    // Update > Argument
                                    argument = iterator + 1;
                                } break;
                            }
                        }

                        // Logic
                        if (argument != end) {
                            // ... Print
                            ++argumentCount; {
                                ::WriteFile(consoleActiveScreenBufferHandle, "[", 1u, NULL, NULL);
                                for (int exponent = 1, value = argumentCount; exponent; exponent *= 10, value /= 10) { if (0 == value) for (char digit; exponent /= 10; ) ::WriteFile(consoleActiveScreenBufferHandle, &(digit = *("0123456789" + ((argumentCount / exponent) % 10))), 1u, NULL, NULL); }
                                ::WriteFile(consoleActiveScreenBufferHandle, "]: \"", 4u, NULL, NULL);
                                ::WriteFile(consoleActiveScreenBufferHandle, argument, end - argument, NULL, NULL);
                                ::WriteFile(consoleActiveScreenBufferHandle, "\"\r\n", 3u, NULL, NULL);
                            }
                        }

                        // Deletion
                        ::CloseHandle(consoleActiveScreenBufferHandle);
                    }
                }
            }

            else if (argumentCount) { /* arguments --- NOTE (Lapys) -> Parse the `arguments` as a vector of ASCII arguments to be compatible with `char argv[]`'s implementation. */
                // Initialization > Argument
                // : Loop
                LPSTR argument = NULL;
                for (LPWSTR *iterator = arguments; (NULL != argument || arguments == iterator) && argumentCount != iterator - arguments; ++iterator) {
                    // Constant > (Length, Size)
                    int const length = (int) ::wcslen(*iterator);
                    int const size = ::WideCharToMultiByte(CP_UTF8, 0x0, *iterator, length, NULL, 0, NULL, NULL);

                    // Update > Allocation --- NOTE (Lapys) -> Initially invoked with a `NULL` `argument`.
                    argument = (LPSTR) ::realloc(argument, size * sizeof(CHAR));

                    // Logic
                    if (NULL == argument) { ::free(argument); argument = NULL; } // ERROR (Lapys)
                    else {
                        // Constant > Index
                        int const index = iterator - arguments;

                        // ... Print
                        ::WideCharToMultiByte(CP_UTF8, 0x0, *iterator, -1, argument, length, NULL, NULL); {
                            ::WriteFile(consoleActiveScreenBufferHandle, "[", 1u, NULL, NULL);
                            if (index) { for (int exponent = 1, value = index; exponent; exponent *= 10, value /= 10) if (0 == value) for (char digit; exponent /= 10; ) ::WriteFile(consoleActiveScreenBufferHandle, &(digit = *("0123456789" + ((index / exponent) % 10))), 1u, NULL, NULL); } else ::WriteFile(consoleActiveScreenBufferHandle, "0", 1u, NULL, NULL);
                            ::WriteFile(consoleActiveScreenBufferHandle, "]: \"", 4u, NULL, NULL);
                            ::WriteFile(consoleActiveScreenBufferHandle, argument, length, NULL, NULL);
                            ::WriteFile(consoleActiveScreenBufferHandle, "\"\r\n", 3u, NULL, NULL);
                        }
                    }
                }

                // ... Deletion
                ::LocalFree(arguments);
                ::CloseHandle(consoleActiveScreenBufferHandle);

                if (NULL == argument) ::exit(EXIT_FAILURE); // ERROR (Lapys)
                else ::free(argument);
            }
        }

        // Return
        return EXIT_SUCCESS;
    }

#else
    /* Main */
    int main(int const count, char const* const arguments[]) {
        // Loop > Print
        for (int iterator = 0; count ^ iterator; ++iterator)
        ::printf("[%i]: \"%s\"\r\n", iterator, arguments[iterator]);

        // Return
        return EXIT_SUCCESS;
    }
#endif
