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
    #include <wchar.h> // Wide Characters -- Window
    #include <windows.h> // Windows

    /* Main */
    int WinMain(HINSTANCE const, HINSTANCE const, LPSTR const, int const) {
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

            // Logic
            if (NULL == arguments && 0 == argumentCount) { // ERROR (Lapys)
                // Deletion; ...
                ::CloseHandle(consoleActiveScreenBufferHandle);
                ::exit(EXIT_FAILURE);
            }

            else {
                // Initialization > Argument
                // : Loop
                LPSTR argument = NULL;
                for (LPWSTR *iterator = arguments; (NULL != argument || arguments == iterator) && argumentCount != iterator - arguments; ++iterator) {
                    // Constant > (Length, Size)
                    int const length = (int) ::wcslen(*iterator);
                    int const size = ::WideCharToMultiByte(CP_UTF8, 0x0, *iterator, length, NULL, 0, NULL, NULL);

                    // Update > Argument --- NOTE (Lapys) -> Initially invoked with a `NULL` `argument`.
                    // : Logic
                    argument = (LPSTR) ::realloc(argument, size);
                    if (NULL != argument) {
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
        // ... Print
        for (int iterator = 0; count ^ iterator; ++iterator)
        ::printf("[%i]: \"%s\"\r\n", iterator, *(arguments + iterator));

        // Return
        return EXIT_SUCCESS;
    }
#endif
