/* Import */
#include <windows.h> // Windows

/* Function */
void HideConsole() { ::ShowWindow(::GetConsoleWindow(), SW_HIDE); }
void ShowConsole() { ::ShowWindow(::GetConsoleWindow(), SW_SHOW); }

const bool IsConsoleVisible() { return ::IsWindowVisible(::GetConsoleWindow()) != FALSE; }

/* Main */
int main(void) {
    // ...
    ::HideConsole();
    ::MessageBox(NULL, "The current active console window is hidden", "Console Visibility", MB_OK);
    ::ShowConsole(); // WARN (Lapys) -> The console window must be revealed again otherwise it will be unilaterally closed.

    // Return
    return 0;
}
