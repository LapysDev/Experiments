/* Import --> kernel32.dll, shell32.dll, user32.dll */
// : [C Standard Library]
#include <stdint.h> // Standard Integers

// : [C++ Standard Library]
#include <cstdlib> // C Standard Library

// : [Windows API]
#include <windef.h> // Windows Definitions
#include <winbase.h> // Windows Base
#include <winnt.h> // Windows New Technologies
#include <winuser.h> // Windows User

#include <basetsd.h> // Base Type Definitions
#include <fileapi.h> // File API
#include <libloaderapi.h> // Library Loader API
#include <processthreadsapi.h> // Process & Threads API
#include <shellapi.h> // Shell API

/* Function > Window Procedure */
LRESULT CALLBACK windowProcedure(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
    // Logic
    switch (message) {
        // [...]
        case WM_CLOSE: ::DestroyWindow(windowHandle); break;
        case WM_KEYDOWN: if (VK_ESCAPE == parameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSCOMMAND: if (SC_CLOSE == parameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSKEYDOWN: if (VK_F4 == parameter) ::DestroyWindow(windowHandle); break;

        // [Create, Destroy]
        case WM_CREATE: ::ShowWindow(windowHandle, static_cast<long>(reinterpret_cast<intptr_t>(static_cast<LPVOID>(reinterpret_cast<CREATESTRUCTA const*>(subparameter) -> lpCreateParams)))); break;
        case WM_DESTROY: ::PostQuitMessage(EXIT_SUCCESS); break;
    }

    // Return
    return ::DefWindowProc(windowHandle, message, parameter, subparameter);
}

/* Main --- NOTE (Lapys) */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const previousInstanceHandle, LPSTR const /* commandLineArguments */, int const appearance) {
    // Initialization > (Exit Code, Instance ..., Lock Handle, Window ...)
    int exitCode = EXIT_SUCCESS;

    bool instanceAlreadyRunning = false;
    CHAR instanceFileName[MAX_PATH] = {0};

    HANDLE lockHandle = NULL;

    WNDCLASSEX windowClassInformation = WNDCLASSEX();
    HWND windowHandle = NULL;

    // Update > Instance File Name
    ::GetModuleFileName(NULL, instanceFileName, MAX_PATH);

    // Logic > ... -> Detect multiple instances of this program being executed.
    if (NULL != previousInstanceHandle) instanceAlreadyRunning = true;
    else for (; false;) {
        // Initialization > Lock File (Name, Path)
        CHAR lockFileName[MAX_PATH] = {};
        CHAR lockFilePath[MAX_PATH + 1u] = {};

        // Logic
        if (0u != ::GetTempPath(MAX_PATH + 1u, lockFilePath))
        if (0u != ::GetTempFileName(lockFilePath, "", 0000u, lockFileName)) {
            // ...; Logic
            lockHandle = ::CreateFile(lockFileName, GENERIC_READ, 0u, NULL, CREATE_NEW, FILE_FLAG_DELETE_ON_CLOSE, NULL);
            if (INVALID_HANDLE_VALUE != lockHandle) {
                // ... Update > Instance Already Running; ...
                switch (::GetLastError()) {
                    case ERROR_FILE_EXISTS: instanceAlreadyRunning = true; break;
                    case ERROR_SUCCESS: instanceAlreadyRunning = false; break;
                }

                if (false == instanceAlreadyRunning)
                continue;
            }
        }

        // ...; Logic
        lockHandle = ::CreateMutex(NULL, TRUE, "PreviousInstanceAssertion");
        if (NULL != lockHandle) {
            // ... Update > Instance Already Running
            switch (::GetLastError()) {
                case ERROR_ALREADY_EXISTS: instanceAlreadyRunning = true; break;
                case ERROR_SUCCESS: instanceAlreadyRunning = false; break;
            }
        }
    }

    // Logic > ... -> Create an (application) Window.
    if (instanceAlreadyRunning) exitCode = EXIT_FAILURE;
    else {
        // Modification > Window Class Information > ...
        windowClassInformation.cbClsExtra = 0;
        windowClassInformation.cbSize = sizeof(WNDCLASSEX);
        windowClassInformation.cbWndExtra = 0;
        windowClassInformation.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
        windowClassInformation.hCursor = static_cast<HCURSOR>(::LoadCursor(instanceHandle, IDC_ARROW)) /* --> static_cast<HCURSOR>(::LoadImage(instanceHandle, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)) */;
        windowClassInformation.hIcon = static_cast<HICON>(::ExtractIcon(instanceHandle, instanceFileName, 0u));
        windowClassInformation.hIconSm = static_cast<HICON>(NULL);
        windowClassInformation.hInstance = instanceHandle;
        windowClassInformation.lpfnWndProc = &windowProcedure;
        windowClassInformation.lpszClassName = "window";
        windowClassInformation.lpszMenuName = static_cast<LPCSTR>(NULL);
        windowClassInformation.style = CS_GLOBALCLASS | CS_OWNDC;

        // Logic
        if (0x0 == ::RegisterClassEx(static_cast<WNDCLASSEX const*>(&windowClassInformation)))
            // Error
            exitCode = EXIT_FAILURE;

        else {
            // Update > Window Handle
            windowHandle = ::CreateWindowEx(
                0x0, windowClassInformation.lpszClassName, "Windows GDI Application", WS_OVERLAPPEDWINDOW /* -> Default borders & title bar. */,
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                HWND_DESKTOP, static_cast<HMENU>(NULL), windowClassInformation.hInstance, reinterpret_cast<LPVOID>(static_cast<LPARAM>(appearance))
            );

            // Logic
            if (NULL == windowHandle)
                // Error
                exitCode = EXIT_FAILURE;

            else {
                // ...; Loop > Update ...
                MSG threadMessage = {};
                for (
                    BOOL threadMessageAvailable = TRUE; FALSE == threadMessageAvailable || WM_QUIT != threadMessage.message;
                    threadMessageAvailable = ::PeekMessage(&threadMessage, NULL, 0x0, 0x0, PM_REMOVE)
                ) ::DispatchMessage(&threadMessage);

                // Update > Exit Code
                exitCode = threadMessage.wParam;
            }

            // Termination
            ::UnregisterClass(windowClassInformation.lpszClassName, windowClassInformation.hInstance);
        }

        // Deletion
        if (INVALID_HANDLE_VALUE != lockHandle && NULL != lockHandle) { ::CloseHandle(lockHandle); }
        ::DestroyCursor(windowClassInformation.hCursor);
    }

    // Return
    return exitCode;
}
