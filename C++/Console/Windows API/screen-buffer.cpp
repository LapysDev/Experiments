/* Import */
#include <windows.h> // Windows

/* Main */
int main(void) {
    // Declaration > Console
    DWORD bytesWritten = 0;
    HANDLE console = ::CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    // ...
    ::SetConsoleActiveScreenBuffer(console);

    // Loop
    while (true) {
        // ...
        ::WriteConsoleOutputCharacter(console, "Hello, World!", 13, {0, 0}, &bytesWritten);

        ::WriteConsoleOutputCharacter(console, "[Press `Ctrl + C` to exit...]", 29, {0, 1}, &bytesWritten);
        ::WriteConsoleOutputCharacter(console, "(Or don`t)", 10, {30, 1}, &bytesWritten);

        // Reset > ...
        bytesWritten = 0;
    }

    // Return
    return 0;
}
