/* Import */
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library
#include <windows.h> // Windows

/* Main --- NOTE (Lapys) -> See the `records.c` file for more references. */
int main(void) {
    // Initialization > File ...
    DWORD fileAttribute = ::GetFileAttributes("record-assertion.cpp");
    bool fileExists = false;

    // Logic > ...
    if (fileAttribute == INVALID_FILE_ATTRIBUTES) ::fprintf(stderr, "%s", "Invalid directory");
    if (fileAttribute & FILE_ATTRIBUTE_DIRECTORY) { fileExists = true; ::printf("%s", "Directory exists"); }

    if (false == fileExists) ::printf("%s", "Directory not existing");

    // Return
    return EXIT_SUCCESS;
}
