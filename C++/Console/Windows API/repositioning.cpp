/* Import --> kernel32.dll, user32.dll */
// : C Standard Library
#include <cstdlib>   // C Standard Library

// : Windows API
#include <windef.h>  // Windows Definitions
#include <winbase.h> // Windows Base
#include <wincon.h>  // Windows Console
#include <winuser.h> // Windows User

/* ... */
void MoveConsole(HWND const window, LONG const x, LONG const y) {
    RECT bounds;
    LONG const style = ::GetWindowLongPtr(window, GWL_STYLE);

    ::GetWindowRect(window, &bounds);
    bounds.bottom += y;
    bounds.left = x;
    bounds.right += x;
    bounds.top = y;

    ::AdjustWindowRect(&bounds, style, NULL != ::GetMenu(window)); // --> Adjust the bounds to resize the client area
    ::SetWindowPos(window, NULL, bounds.left, bounds.top, bounds.right - bounds.left, bounds.bottom - bounds.top, SWP_SHOWWINDOW);
}

void WriteToConsole(HANDLE const handle, CHAR const character, SHORT const x, SHORT const y) {
    SMALL_RECT bounds;
    COORD coordinates;
    CHAR_INFO information;
    COORD size;

    // ...
    bounds.Bottom = y + 0;
    bounds.Left = x;
    bounds.Right = x + 0;
    bounds.Top = y;

    coordinates.X = 0;
    coordinates.Y = 0;

    information.Attributes = (COMMON_LVB_GRID_LVERTICAL | COMMON_LVB_LEADING_BYTE) | (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    information.Char.AsciiChar = character;

    size.X = 1;
    size.Y = 1;

    // ...
    ::WriteConsoleOutput(handle, &information, size, coordinates, &bounds);
}

/* Main */
int main(void) {
    HANDLE const consoleHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
    HWND const consoleWindow = ::GetConsoleWindow();

    // ...
    MoveConsole(consoleWindow, 0, 0);
    WriteToConsole(consoleHandle, '0', 2, 0);

    // std::system("color F0");
}
