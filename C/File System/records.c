/* Import */
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library

#include <fcntl.h> // Functional
#include <sys/stat.h> // System > Statistics
#include <sys/types.h> // System > Types
#include <unistd.h> // UNIX Standard Library

#include <windows.h> // Windows

/* Main */
int main(void) {
    // Initialization > ...
    FILE *fileEntry;
    char key;
    struct stat status {};

    // [Initiate] ...
    fileEntry = fopen("file.l", "w");

    if (stat("entry", &status) == -1) mkdir("entry");
    if (stat("entry/subdirectory", &status) == -1) mkdir("entry/subdirectory");

    // [Update] ...
    CopyFile("file.l", "file-copy.l", false); // NOTE (Lapys) -> On other platforms, the file may be manually copied.
    if (rename("entry", "directory") == -1) MoveFile("entry", "directory");

    // Print; Terminate
    printf("%s", "Press any key to continue...");
    scanf("%c", &key);

    // [Terminate] Deletion
    fclose(fileEntry);
    if (remove("file.l") == -1) DeleteFile("file.l");
    if (remove("file-copy.l") == -1) DeleteFile("file-copy.l");

    if (remove("directory/subdirectory") == -1) RemoveDirectory("directory/subdirectory");
    if (remove("directory") == -1) RemoveDirectory("directory"); // WARN (Lapys) -> All sub-directories must be deleted first.

    // Return
    return EXIT_SUCCESS;
}
