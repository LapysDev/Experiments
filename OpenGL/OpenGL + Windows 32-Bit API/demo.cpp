/* Import */
#include "main.hpp" // Main --- NOTE (Lapys) -> Single entry-point for all programs.
#include "win-api.hpp" // Windows 32-Bit

/* Utilization > ... */
using namespace Win32;

/* Main */
int Main(...) {
    // Print
    Console::Print(22.00 / 7.00);

    // Return
    return 0;
}
