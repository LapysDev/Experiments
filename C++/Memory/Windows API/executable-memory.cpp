/* NOTE (Lapys) -> See the `mmap` function from the POSIX C standard. */
/* Import */
#include <stdio.h> // Standard Input-Output
#include <string.h> // String
#include <windows.h> // Windows

/* Main */
int main(void) {
    /* Global > (Function) (Code, Return Value) --- NOTE (Lapys) -> Dynamically created function with dynamically allocated executable memory. */
    unsigned (*function)(void) = 0x0;
    const unsigned char functionCode[6] { // NOTE (Lapys) -> `unsigned char` data type is used for the instructions and parameters.
        0xB8, // NOTE (Lapys) -> Move to `EAX` register instruction.
        0xE4, 0x07, 0x00, 0x00, // -> 2020
        0xC3 // NOTE (Lapys) -> Return from the `EAX` register (this instruction is necessary).
    };
    unsigned functionReturnValue = 0u;

    // Initialization > (Buffer, Page Size, Previous Access Protection Value, System Information)
    void *buffer;
    std::size_t pageSize;
    DWORD previousAccessProtectionValue;
    SYSTEM_INFO systemInformation;

    // Update > (Buffer, Page Size, System Information)
    ::GetSystemInfo(&systemInformation);

    pageSize = systemInformation.dwPageSize;

    buffer = ::VirtualAlloc(0x0, pageSize, MEM_COMMIT, PAGE_READWRITE); // NOTE (Lapys) -> Prepare the memory in which the machine code will be (it`s not executable yet).
    ::memcpy(buffer, (const unsigned char*) functionCode, 6u); // NOTE (Lapys) -> Copy the machine code into memory.
    ::VirtualProtect(buffer, 6, PAGE_EXECUTE_READ, &previousAccessProtectionValue); // NOTE (Lapys) -> Mark the memory as executable.

    function = (unsigned(*)(void)) buffer; // NOTE (Lapys) -> Interpret the beginning of the (currently) executable memory as the entry point of a function taking no arguments and returning a 4-byte integer.
    functionReturnValue = function(); // NOTE (Lapys) -> Invoke the dynamically-created function.

    // Deletion --- NOTE (Lapys) -> Free the executable memory.
    ::VirtualFree(buffer, 0, MEM_RELEASE);

    // Loop > Print
    for (unsigned iterator = functionReturnValue; iterator; iterator /= 10u) ::putchar('\0');
    for (unsigned iterator = functionReturnValue; iterator; iterator /= 10u) { ::putchar('\b'); ::putchar(((char) (iterator % 10u)) + 48); ::putchar('\b'); }
        /* ::putchar('\n'); ::putchar('\r'); */

    // Return
    return EXIT_SUCCESS;
}
