/* Import */
#include <iostream> // Input-Output Stream
#include <windows.h> // Windows

/* Main */
int main(void) {
    // Initialization > ...
    _ULARGE_INTEGER freeBytesAvailableToCaller {};
    _ULARGE_INTEGER totalNumberOfBytes {};
    _ULARGE_INTEGER totalNumberOfFreeBytes {};

    // ...
    std::cout << "[STATE]: " << ::GetDiskFreeSpaceExA("." /* -> "\\.\C:" or "\\.\PhysicalDrive0" */, &freeBytesAvailableToCaller, &totalNumberOfBytes, &totalNumberOfFreeBytes) << "\r\n" << std::endl;

    std::cout << "Free Bytes Available To Caller: " << freeBytesAvailableToCaller.QuadPart << std::endl;
    std::cout << "Total Number of Bytes:\t\t" << totalNumberOfBytes.QuadPart << std::endl;
    std::cout << "Total Number of Free Bytes:\t" << totalNumberOfFreeBytes.QuadPart << std::flush;

    // Return
    return 0;
}
