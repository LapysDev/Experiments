/* Import */
#include <errno.h> // Error Number
#include <fcntl.h> // File Control
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library
#include <unistd.h> // UNIX Standard Library

/* Main */
int main(void) {
    // Constant > File ...
    char const* const fileName = ::tmpnam(NULL); // NOTE (Lapys) -> Also acts as the file`s path name.
    int const fileDescriptor = ::open(fileName, O_CREAT | O_RDWR);

    // Print [File]
    ::write(STDOUT_FILENO, "File = {\n\r\tDescriptor = ", 24u);
    if (fileDescriptor < 0) ::write(STDOUT_FILENO, "-", 1u);
    for (unsigned int iterator = 1e9, length = 1u, trailing = true; iterator || length; (iterator /= 10u, length = 0u)) {
        unsigned char const digit = ((fileDescriptor < 0 ? -fileDescriptor : fileDescriptor) % (iterator * 10u)) / iterator;
        if (digit || false == trailing) { ::write(STDOUT_FILENO, "0123456789" + digit, 1u); trailing = false; }
    }
    ::write(STDOUT_FILENO, ",\n\r\tName = \"", 12u);
    if (fileName) for (char *iterator = (char*) fileName; *(iterator++); ) if ('\0' == *iterator) ::write(STDOUT_FILENO, fileName, (size_t) (iterator - fileName));
    ::write(STDOUT_FILENO, "\"\n\r}\0", 6u);

    // [Error] Logic --- NOTE (Lapys) -> `open` function invocation has failed.
    if (-1 == fileDescriptor) {
        // Initialization > Error ...
        char *error_code_syntax = NULL;
        char *error_description = NULL;

        // Print [Error]
        ::write(STDOUT_FILENO, "\n\n\r[ERROR 0x", 12u);

        for (unsigned long long iterator = 4294967296u, trailing = true; iterator; iterator /= 16u) {
            unsigned char const digit = (errno % (iterator * 16u)) / iterator;
            if (digit || false == trailing) { ::write(STDOUT_FILENO, "0123456789ABCDEF" + digit, 1u); trailing = false; }
        }

        switch (errno) {
            case EACCES: error_code_syntax = (char*) "EACCES"; error_description = (char*) "The requested access to the file is not allowed;\n\r\tor search permission is denied for one of the directories in the path prefix of path name;\n\r\tor the file did not exist yet and write access to the parent directory is not allowed"; break;
            case EAGAIN: error_code_syntax = (char*) "EAGAIN"; error_description = (char*) "File path name names the slave side of a pseudo-terminal device that is locked"; break;
            case EBADF: error_code_syntax = (char*) "EBADF"; error_description = (char*) "File specified with an invalid file descriptor"; break;
            case EEXIST: error_code_syntax = (char*) "EEXIST"; error_description = (char*) "File path name already exists and `O_CREAT` and `O_EXCL` file descriptors were used"; break;
            case EFAULT: error_code_syntax = (char*) "EFAULT"; error_description = (char*) "File path name points outside your accessible address space"; break;
            case EFBIG /* -> `EOVERFLOW` */: error_code_syntax = (char*) "EOVERFLOW"; error_description = (char*) "File path name refers to a regular file that is too large to be opened"; break;
            case EINTR: error_code_syntax = (char*) "EINTR"; error_description = (char*) "While blocked waiting to complete an open of a slow device, the call was interrupted by a signal handler"; break;
            case EINVAL: error_code_syntax = (char*) "EINVAL"; error_description = (char*) "The filesystem does not support the specified file descriptor (e.g.: `O_DIRECT`);\n\r\tor `O_TMPFILE` was specified in flags, but neither `O_RDWR` nor `O_WRONLY` was specified;\n\r\tor the file descriptor specified `O_CREAT` and the final component (\"basename\") of the new file's path name is invalid"; break;
            case EIO: error_code_syntax = (char*) "EIO"; error_description = (char*) "File path name names a `STREAMS` file and a hangup or error occurred during the function invocation"; break;
            case EISDIR: error_code_syntax = (char*) "EISDIR"; error_description = (char*) "File path name refers to a directory and the access requested involved writing;\n\r\tor `O_TMPFILE` and one of `O_RDWR` or `O_WRONLY` were specified file descriptors, but this kernel version does not provide the `O_TMPFILE` functionality"; break;
            case EMFILE: error_code_syntax = (char*) "EMFILE"; error_description = (char*) "The per-process limit on the number of open file descriptors has been reached"; break;
            case ENAMETOOLONG: error_code_syntax = (char*) "ENAMETOOLONG"; error_description = (char*) "File path name was too long"; break;
            case ENFILE: error_code_syntax = (char*) "ENFILE"; error_description = (char*) "The system-wide limit on the total number of open files has been reached"; break;
            case ENODEV: error_code_syntax = (char*) "ENODEV"; error_description = (char*) "File path name refers to a device special file and no corresponding device exists"; break;
            case ENOENT: error_code_syntax = (char*) "ENOENT"; error_description = (char*) "`O_CREAT` file descriptor is not set and the named file does not exist;\n\r\tor a directory component in path name does not exist or is a dangling symbolic link;\n\r\tor file path name refers to a nonexistent directory;\n\r\tor `O_TMPFILE` and one of `O_RDWR` or `O_WRONLY` were specified file descriptors, but this kernel version does not provide the `O_TMPFILE` functionality"; break;
            case ENOMEM: error_code_syntax = (char*) "ENOMEM"; error_description = (char*) "The named file is a FIFO (first-in-first-out), but memory for the FIFO buffer can't be allocated because the per-user hard limit on memory allocation for pipes has been reached and the caller is not privileged;\n\r\tor insufficient kernel memory was available"; break;
            case ENOSPC: error_code_syntax = (char*) "ENOSPC"; error_description = (char*) "File path name was to be created but the device containing path name has no room for the new file"; break;
            case ENOTDIR: error_code_syntax = (char*) "ENOTDIR"; error_description = (char*) "A component used as a directory in path name is not a valid directory;\n\r\tor the `O_DIRECTORY` file descriptor was specified and path name was not a directory"; break;
            case ENXIO: error_code_syntax = (char*) "ENXIO"; error_description = (char*) "`O_NONBLOCK | O_WRONLY` file descriptors are set, the named file is a FIFO (first-in-first-out), and no process has the FIFO open for reading;\n\r\tor the file is a device special file and no corresponding device exists;\n\r\tor the file is a UNIX domain socket"; break;
            case EPERM: error_code_syntax = (char*) "EPERM"; error_description = (char*) "The `O_NOATIME` file descriptor was specified, but the effective user ID of the caller did not match the owner of the file and the caller was not privileged;\n\r\tor the operation was prevented by a file seal"; break;
            case EROFS: error_code_syntax = (char*) "EROFS"; error_description = (char*) "File path name refers to a file on a read-only filesystem and write access was requested"; break;
        }

        if (error_code_syntax && error_description) {
            ::write(STDOUT_FILENO, " (`", 3u);
            if (error_code_syntax) for (char *iterator = (char*) error_code_syntax; *(iterator++); ) if ('\0' == *iterator) ::write(STDOUT_FILENO, error_code_syntax, (size_t) (iterator - error_code_syntax));
            ::write(STDOUT_FILENO, "`)]: \"", 6u);
            if (error_description) for (char *iterator = (char*) error_description; *(iterator++); ) if ('\0' == *iterator) ::write(STDOUT_FILENO, error_description, (size_t) (iterator - error_description));
            ::write(STDOUT_FILENO, "\"\0", 2u);
        } else ::write(STDOUT_FILENO, "]\0", 2u);
    }

    // Deletion
    ::close(fileDescriptor);
    ::remove(fileName);

    // Return
    return EXIT_SUCCESS;
}
