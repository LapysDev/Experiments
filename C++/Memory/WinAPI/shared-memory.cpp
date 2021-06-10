/* Import > ... --> kernel32.dll */
#include <cstdio> // C Standard Input/ Output
#include <cstdlib> // C Standard Library
#include <cstring> // C String

#undef UNICODE
#include <windef.h> // Windows Definitions
#include <winbase.h> // Windows Base
#  include <memoryapi.h> // Memory API

/* Main */
int main(int const, char* arguments[]) {
    HANDLE fileMappingHandle;
    LPSTR buffer;

    // ...
    if (0 == std::strncmp(*arguments, "first", 5u)) {
        fileMappingHandle = ::CreateFileMapping(
            INVALID_HANDLE_VALUE, // ->> Use paging file
            NULL, // ->> Default security
            PAGE_READWRITE,
            0u, // ->> Maximum object size (high-order word)
            256u, // ->> Maximum object size (low-order word)
            "Global" "\\" "Lapys" // ->> Name
        );

        if (NULL == fileMappingHandle) {
            std::fprintf(stderr, "[Type Error (%lu)]: Unable to create file mapping object", ::GetLastError());
            std::exit(EXIT_FAILURE);
        }

        else if (ERROR_ALREADY_EXISTS == ::GetLastError())
        std::fputs("[Warning]: File mapping object already exists" "\r\n", stderr);

        // ...
        buffer = static_cast<LPSTR>(/* --> LPVOID */ ::MapViewOfFile(
            fileMappingHandle,
            FILE_MAP_ALL_ACCESS, // ->> Read/ write permission
            0u, // ->> High offset
            0u, // ->> Low offset
            256u
        ));

        if (NULL == buffer) {
            ::CloseHandle(fileMappingHandle);

            std::fprintf(stderr, "[Access Error (%lu)]: Could not map view of file", ::GetLastError());
            std::exit(EXIT_FAILURE);
        }

        // ...
        for (char const *const message = "Message from first process", *iterator = message; ; ++iterator) {
            buffer[iterator - message] = *iterator;
            if ('\0' == *iterator) break;
        }

        std::printf("Saved message: \"%s\"" "\r\n", buffer);
        std::puts("Press any key to continue..."); std::getchar();

        // ...
        ::UnmapViewOfFile(buffer);
        ::CloseHandle(fileMappingHandle);
    }

    if (0 == std::strncmp(*arguments, "second", 6u)) {
        fileMappingHandle = ::OpenFileMapping(
            FILE_MAP_ALL_ACCESS,
            FALSE, // ->> Do not inherit the file mapping object name
            "Global" "\\" "Lapys" // ->> Name
        );

        if (NULL == fileMappingHandle) {
            std::fprintf(stderr, "[Access Error (%lu)]: Unable to open file mapping object", ::GetLastError());
            std::exit(EXIT_FAILURE);
        }

        // ...
        buffer = static_cast<LPSTR>(/* --> LPVOID */ ::MapViewOfFile(
            fileMappingHandle,
            FILE_MAP_ALL_ACCESS, // ->> Read/ write permission
            0u, // ->> High offset
            0u, // ->> Low offset
            256u
        ));

        if (NULL == buffer) {
            ::CloseHandle(fileMappingHandle);

            std::fprintf(stderr, "[Access Error (%lu)]: Could not map view of file", ::GetLastError());
            std::exit(EXIT_FAILURE);
        }

        // ...
        std::printf("Read message: \"%s\"" "\r\n", buffer);
        std::puts("Press any key to continue..."); std::getchar();

        // ...
        ::UnmapViewOfFile(buffer);
        ::CloseHandle(fileMappingHandle);
    }

    return EXIT_SUCCESS;
}
