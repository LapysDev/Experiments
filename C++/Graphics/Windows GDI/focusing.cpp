/* Import > ... --> kernel32.dll, user32.dll */
#include <cstdio> // C Standard Input/ Output
#include <cstdlib> // C Standard Library

#undef UNICODE
#include <windef.h> // Windows Definitions
#include <winerror.h> // Windows Error
#include <winuser.h> // Windows User
#  include <errhandlingapi.h> // Error Handling API

/* Main */
int WinMain(HINSTANCE const, HINSTANCE const, LPSTR const commandLineArguments, int const) {
    LPCSTR const targetWindowTitle = commandLineArguments;
    HWND const targetWindowHandle = ::FindWindow(NULL, targetWindowTitle);

    // ...
    if (NULL == targetWindowHandle) {
        std::fprintf(stderr, "[Reference Error]: Could not find specified window (with title \"%s\")", targetWindowTitle);
        std::exit(EXIT_FAILURE);
    }

    else {
        // ... ->> Visuals
        FLASHWINFO targetWindowFlashInformation;

        targetWindowFlashInformation.cbSize = sizeof(FLASHWINFO);
        targetWindowFlashInformation.dwFlags = FLASHW_CAPTION | FLASHW_TRAY;
        targetWindowFlashInformation.dwTimeout = 0u; // ->> default time in milliseconds.
        targetWindowFlashInformation.hwnd = targetWindowHandle;
        targetWindowFlashInformation.uCount = 3u;

        ::FlashWindowEx(&targetWindowFlashInformation);
        if (FALSE != ::ShowWindow(targetWindowHandle, SW_RESTORE)) {
            if (FALSE != ::SetForegroundWindow(targetWindowHandle))
            std::fputs("[Warning]: Could not order specified window to the UI foreground" "\r\n", stderr);
        }

        // ... ->> Activate window
        if (::SetActiveWindow(targetWindowHandle) == static_cast<HWND>(NULL)) {
            switch (::GetLastError()) {
                case ERROR_ACCESS_DENIED: std::fputs("[Security Error]: Specified window denied access (not attached to the current calling thread's message queue)", stderr); break;
                default: std::fputs("[Reference Error]: Could not activate window", stderr); break;
            }

            std::exit(EXIT_FAILURE);
        }

        // ... ->> Set keyboard focus
        if (::SetFocus(targetWindowHandle) == static_cast<HWND>(NULL))
        switch (::GetLastError()) {
            case ERROR_ACCESS_DENIED: std::fputs("[Security Error]: Specified window denied access (not attached to the current calling thread's message queue)", stderr); break;
            case ERROR_INVALID_PARAMETER: std::fputs("[Reference Error]: Specified window is disabled", stderr); break;

            default: std::fputs("[Reference Error]: Could not focus keyboard input on specified window", stderr); break;
        }
    }

    // ...
    return EXIT_SUCCESS;
}
