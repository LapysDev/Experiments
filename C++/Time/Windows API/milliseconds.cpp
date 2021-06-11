/* Import --- CODE (Lapys) */
#include <inttypes.h> // Integer Types -> PRId64
#include <stdio.h> // Standard Input/ Output -> printf(...)
#include <stdlib.h> // Standard Library -> EXIT_SUCCESS
#include <windows.h> // Windows
#   include <intrin.h> // (Compiler) Intrinsics -> __rdtsc()
#   include <synchapi.h> // Synchronization API -> Sleep(int)
#   include <sysinfoapi.h> // System Information API -> GetSystemTime(LPSYSTEMTIME)
#   include <winreg.h> // Windows Registry -> Reg...(...)

/* Function > Get CPU Frequency (in MegaHertz (MHz)) */
ULONG GetCPUFrequencyInMegaHertz(void) {
    // Initialization > (Frequency, Registry Key)
    ULONG frequency = 2000uL;
    HKEY registryKey;

    // Logic
    if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0u, KEY_READ, &registryKey)) {
        // Initialization > ...
        ULONG size = 4uL;

        // Update > Registry Key
        ::RegQueryValueEx(registryKey, "~MHz", NULL, NULL, (LPBYTE) &frequency, &size);
        ::RegCloseKey(registryKey);
    }

    // Return
    return frequency;
}

/* Main */
int main(void) {
    // Initialization > (Frequency, (End, Start, ...) Time ...)
    ULONG const frequency = ::GetCPUFrequencyInMegaHertz();
    ULONG64 endTime, startTime;
    SYSTEMTIME endTimestamp = {}, startTimestamp = {};
    constexpr DWORD const suspensionTime = 15u;

    // Update > ... Time ...
    startTime = __rdtsc();
    ::Sleep(suspensionTime);
    endTime = __rdtsc();

    ::GetSystemTime(&startTimestamp);
    ::Sleep(suspensionTime);
    ::GetSystemTime(&endTimestamp);

    // Print
    ::printf(
        "After suspending for %lu, the elapsed time (in milliseconds) estimated via the" "\r\n"
        "\t- `RDTSC` (Read Time-Stamp Counter) instruction is %" PRId64 ";" "\r\n"
        "\t- `GetSystemInfo(...)` (System Information API) function is %u;" "\r\n"

        "\n\twith a %lu mega Hertz clock frequency",

        suspensionTime,
        ((endTime - startTime) / frequency) / 1000uL,
        (endTimestamp.wDay + endTimestamp.wDayOfWeek + endTimestamp.wHour + endTimestamp.wMilliseconds + endTimestamp.wMinute + endTimestamp.wMonth + endTimestamp.wSecond + endTimestamp.wYear) - (startTimestamp.wDay + startTimestamp.wDayOfWeek + startTimestamp.wHour + startTimestamp.wMilliseconds + startTimestamp.wMinute + startTimestamp.wMonth + startTimestamp.wSecond + startTimestamp.wYear),

        frequency
    );

    // Return
    return EXIT_SUCCESS;
}
