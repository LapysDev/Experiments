/* Import */
#include <fcntl.h> // Functional
#include <stdlib.h> // Standard Library
#include <windows.h> // Windows

/* Global > Application ... */
char *applicationName = NULL;
int applicationStatus = 0;

/* Function > Window Procedure */
LRESULT CALLBACK windowProcedure(HWND windowHandle, UINT message, WPARAM messageParameter, LPARAM additionalMessageParameter) {
    // Logic
    switch (message) {
        // [Window Manager ...]
        case WM_CLOSE: ::DestroyWindow(windowHandle); break;
        case WM_DESTROY: ::PostQuitMessage(0); break;

        // [...]
        default: return ::DefWindowProc(windowHandle, message, messageParameter, additionalMessageParameter);
    }

    // Return
    return 0;
}

/* Main */
int WinMain(HINSTANCE handlerInstance, HINSTANCE /*previousHandlerInstance*/, LPSTR /*programInitiationCommandLine*/, int windowAppearance) {
    /* Update > Application ... */
    applicationName = (char*) "Non-Resizable Window";
    applicationStatus = EXIT_SUCCESS; // NOTE (Lapys) -> No errors; Successful exit.

    // Declaration
        // Console Active Screen Buffer Handle
        const HANDLE consoleActiveScreenBufferHandle = ::CreateFile("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, NULL);

        // Window Class ...
        WNDCLASS windowClass {};
        const HINSTANCE& windowClassHandlerInstance = handlerInstance;
        const char windowClassName[] = "DEFAULT"; // WARN (Lapys) -> Must not be empty.

    // Update > (Console Active Screen Buffer Handle, ...)
    ::SetConsoleActiveScreenBuffer(consoleActiveScreenBufferHandle);
    ::SetConsoleTitle(applicationName);

    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);

    // Deletion
    ::ZeroMemory(&windowClass, sizeof(windowClass));

    // Modification > Window Class > ...
    windowClass.cbClsExtra = 0; // NOTE (Lapys) -> Extra bytes to allocate following the window class structure.
    windowClass.cbWndExtra = 0; // NOTE (Lapys) -> Extra bytes to allocate following the window instance.
    windowClass.hbrBackground = (HBRUSH) COLOR_WINDOW; // NOTE (Lapys) -> Window background color.
    windowClass.hCursor = (HCURSOR) ::LoadCursor(NULL, IDC_ARROW); // NOTE (Lapys) -> Window cursor.
    windowClass.hIcon = NULL; // NOTE (Lapys) -> Window favorite icon.
    windowClass.hInstance = windowClassHandlerInstance;
    windowClass.lpszClassName = windowClassName;
    windowClass.lpszMenuName = NULL; // NOTE (Lapys) -> Resource name of the window class menu.
    windowClass.lpfnWndProc = &windowProcedure; // NOTE (Lapys) -> Event loop or Message queue.
    windowClass.style = CS_HREDRAW | CS_VREDRAW; // NOTE (Lapys) -> Pre-defined look of window instances of the class.

    // [Initiate]
    {
        // [Begin] ...
        ::WriteFile(consoleActiveScreenBufferHandle, "[PROGRAM INITIATED]\n\r", 21uL, NULL, NULL);

        // Logic
        if (::RegisterClass(&windowClass)) {
            // Constant > Window Handle
            const HWND windowHandle = ::CreateWindowEx(0, windowClassName, applicationName, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_OVERLAPPED | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, handlerInstance, NULL);

            // Logic
            if (windowHandle) {
                // Initialization > Window Procedure Message
                MSG windowProcedureMessage {};

                // Update > Window Handle
                ::ShowWindow(windowHandle, windowAppearance);
                ::UpdateWindow(windowHandle);

                // Loop > Logic
                while (true)
                if (::GetMessage(&windowProcedureMessage, NULL, 0, 0)) {
                    // Logic > ...
                    if (windowProcedureMessage.message == WM_QUIT) break;
                    else {
                        // Update > Window Procedure Message
                        ::TranslateMessage(&windowProcedureMessage);
                        ::DispatchMessage(&windowProcedureMessage);
                    }
                } else break;

                // Update > Application Status
                applicationStatus = windowProcedureMessage.wParam;
            } else { applicationStatus = EXIT_FAILURE; }

            // Deletion
            ::UnregisterClass(windowClassName, windowClassHandlerInstance);
        } else { applicationStatus = EXIT_FAILURE; }

        // [End] ...
        ::WriteFile(consoleActiveScreenBufferHandle, "[PROGRAM TERMINATED]\0", 21uL, NULL, NULL);
    }

    // [Terminate]
    {
        // Deletion
        ::CloseHandle(consoleActiveScreenBufferHandle);
    }

    // Return
    return applicationStatus;
}
