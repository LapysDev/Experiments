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
        char fileName[MAX_PATH] = {0};

        if (false == (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            std::strcpy(fileName, findData.cFileName);

            if (4L > std::strstr(fileName, ".") - fileName) {
                char name[4];

                *std::strstr(fileName, ".") = '\0';
                std::strcpy(name, fileName);
                std::strcpy(fileName, "0000");
                std::strcpy(fileName + (4u - std::strlen(name)), name);
                std::strcat(fileName, std::strstr(findData.cFileName, "."));

                std::printf("\"%s\" -> \"%s\"" "\r\n", findData.cFileName, fileName);
                ::MoveFile(findData.cFileName, fileName);
            } else std::printf("\"%s\"" "\r\n", fileName);
        }
    } while (FALSE != ::FindNextFile(fileHandle, &findData));

   ::FindClose(fileHandle);
}
