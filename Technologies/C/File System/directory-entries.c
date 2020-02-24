/* Import */
#include <dirent.h> // Directory Entries
#include <errno.h> // Error Number
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library

/* Main */
int main(void) {
    // Initialization > (Directory, Entry)
    DIR *directory = opendir(".");
    struct dirent *entry;

    // Logic > Terminate
    if (ENOENT == errno) exit(EXIT_FAILURE); // NOTE (Lapys) -> Directory does not exist.
    else if (0x0 == directory) exit(EXIT_FAILURE);

    // Loop --- NOTE (Lapys) -> Also reads hidden entries.
    while ((entry = readdir(directory))) {
        // Print
        printf("Directory {\n\r\tFile Name: \"%s\"\n\r\tFile Type: %u\n\r\tInternal Node Number: %i\n\r\tRecord Length: %u\n\r}",
            entry -> d_name, // NOTE (Lapys) -> 256 static `char` array.
            (unsigned int) (unsigned char) entry -> d_type,
            (ino_t) entry -> d_ino,
            (unsigned int) (unsigned short) entry -> d_reclen
        );

        putchar('\n'); putchar('\r');
        putchar('\n'); putchar('\r');
    }

    // Terminate
    closedir(directory);

    // Return
    return EXIT_SUCCESS;
}
