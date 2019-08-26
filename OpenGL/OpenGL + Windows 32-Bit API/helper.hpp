/* Import */
#include <fcntl.h> // Functional
#include <stdlib.h> // Standard Library
#include <unistd.h> // Unix Standard

/* Global > Flag */
const struct FUNCTION_ARGUMENT_FLAG { public: template <typename type> type operator =(type argument) const { return argument; } } FLAG;

/* Namespace */
    // ...
    namespace Console {};
    namespace Data { namespace String {} };
    namespace File { namespace RequestFlag {} };

    // Data
    namespace Data {
        /* Namespace */
            // Pointer
            namespace Pointer {
                /* Functions > ... */
                const void* AllocateMemory(const unsigned size) { return ::malloc(size); }
                const void* AllocateMemory(void* pointer, const unsigned size) { return (pointer = ::malloc(size)); }
                void FreeMemory(void* pointer) { ::free(pointer); }
            }

            // Number
            namespace Number {
                /* Functions > ... */
                const unsigned int GetCharacteristicsLength(int number) { unsigned int length = 0; while (number) { length += 1; number /= 10; } return length; }
                const unsigned short GetMantissLength(long double number) {
                    // Initialization > (Integer, Length)
                    unsigned long long integer = number;
                    unsigned short length = 0;

                    // Loop > Update > (...)
                    while (number > integer && integer) { number *= 10; integer = number; length += 1; }

                    // Return
                    return length;
                }
            }

            // String --- NOTE (Lapys) -> Most helper functions here assume its `string` parameter is well-formed.
            namespace String {
                /* Functions > ... */
                void EmptyString(char* string) { while (*string) { *string = '\0'; string += 1; } }
                const unsigned GetLength(const char* string) { char *pointer = (char*) string; while (*pointer) pointer += 1; return pointer - string; }
            }

        /* Function */
            // Number To String
            const char* NumberToString(const double number) {
                char *string = NULL;

                // Return
                return string;
            }
            const char* NumberToString(int number) {
                // Initialization > ...
                char digits[10] {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

                const unsigned int characteristicsLength = Number::GetCharacteristicsLength(number);
                unsigned int characteristicsIterator = characteristicsLength;

                char* string = (char*) Pointer::AllocateMemory(characteristicsLength);

                // (Loop > )Update > ...
                while (number > 0 && characteristicsIterator) { *(string + (characteristicsIterator -= 1)) = *(digits + (number % 10)); number = (unsigned int) number / 10; }
                *(string + characteristicsLength) = '\0';

                // Return
                return string;
            }
    } using namespace Data;

    // File
    namespace File {
        /* Namespace > Request Flag */
        namespace RequestFlag { const int Append = O_APPEND; const int Create = O_CREAT; const int ReadOnly = O_RDONLY; const int ReadWrite = O_RDWR; const int Rewrite = O_TRUNC; const int WriteOnly = O_WRONLY; }

        /* Function */
            // Close File By Descriptor
            const int CloseFileByDescriptor(const int fileDescriptor) { return ::close(fileDescriptor) < 0; }

            // Read By Buffer From File
            const long ReadByBufferFromFile(void* buffer, const unsigned bufferSize) { return ::read(0, buffer, bufferSize); }
            const long ReadByBufferFromFile(const int fileDescriptor, void* buffer, const unsigned bufferSize) { return ::read(fileDescriptor, buffer, bufferSize); }

            // Request File By Descriptor
            const int RequestFileByDescriptor(const char* path, const int requestFlag = File::RequestFlag::Append | File::RequestFlag::ReadWrite) { return ::open(path, requestFlag); }
            const int RequestFileByDescriptor(const char* path, const int requestFlag, const int requestMode) { return ::open(path, requestFlag, requestMode); }

            // Write By Buffer To File
            const long WriteByBufferToFile(const void* buffer, const unsigned bufferSize) { return ::write(1, buffer, bufferSize); }
            const long WriteByBufferToFile(const int fileDescriptor, const void* buffer, const unsigned bufferSize) { return ::write(fileDescriptor, buffer, bufferSize); }
    }

    // Console
    namespace Console {
        // Print
        const int Print(const char* string) { const unsigned stringLength = String::GetLength(string); return File::WriteByBufferToFile(string, sizeof(char) * stringLength) == stringLength ? 0 : -1; }
        const int Print(char* string) { return Console::Print((const char*) string); }
        const int Print(const double number) { char *string = (char*) Data::NumberToString(number); Console::Print(string); Pointer::FreeMemory(string); }
        const int Print(const int number) { char *string = (char*) Data::NumberToString(number); Console::Print(string); Pointer::FreeMemory(string); }

        // Scan
        const int Scan(char* string, const unsigned STRING_LENGTH) { return File::ReadByBufferFromFile(string, STRING_LENGTH) < 0 ? -1 : 0; }
        const int Scan(char* string) { return Console::Scan(string, FLAG = String::GetLength(string)) < 0 ? -1 : 0; }
        const int Scan(const int string) { return 0; }
    }
