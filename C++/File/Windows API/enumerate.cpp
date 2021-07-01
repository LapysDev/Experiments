/* Definitions > ... */
#undef UNICODE

/* Import --> kernel32.dll */
// : [C Standard Library]
#include <cstddef>    // C Standard Definitions
#include <cstdio>     // C Standard Input/ Output
#include <cstring>    // C String

// : [Windows API]
#include <windef.h>   // Windows Definitions
#include <winbase.h>  // Windows Base
# include <fileapi.h> // File API

/* Main */
int main(int const count, char* arguments[]) {
    char directory[MAX_PATH + 2] = {0};

    WIN32_FIND_DATA findData;
    HANDLE fileHandle;

    // ...
    std::strcpy(directory, count == 1 ? "" : arguments[1]);
    std::strcat(directory, "\\*");
    while (NULL != std::strstr(directory, "/")) *std::strstr(directory, "/") = '\\';

    fileHandle = ::FindFirstFile(directory, &findData);

    // ...
    std::printf("Searching directory: \"%s\"" "\r\n", directory);
    do {
        if (false == (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        std::printf("\"%s\"" "\r\n", findData.cFileName);
    } while (FALSE != ::FindNextFile(fileHandle, &findData));

   ::FindClose(fileHandle);
}
