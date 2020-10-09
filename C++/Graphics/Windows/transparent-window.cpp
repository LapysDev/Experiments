/* Import */
#include <stdlib.h> // Standard Library
#include <windows.h> // Windows

/* Main */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const, LPSTR const, int const) {
    // Initialization > (Console Window Handle, Window Class)
    HWND const consoleWindowHandle = ::GetConsoleWindow();
    WNDCLASSEX windowClass = {}; {
        windowClass.cbClsExtra = 0;
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.cbWndExtra = 0;
        windowClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
        windowClass.hCursor = (HCURSOR) ::LoadCursor(NULL, IDC_ARROW);
        windowClass.hIcon = (HICON) NULL;
        windowClass.hIconSm = (HICON) NULL;
        windowClass.hInstance = instanceHandle;
        windowClass.lpfnWndProc = &::DefWindowProc;
        windowClass.lpszClassName = "transparent-window";
        windowClass.lpszMenuName = NULL;
        windowClass.style = 0x0;
    }

    // Logic > ...
    if (NULL != consoleWindowHandle)
    ::ShowWindow(consoleWindowHandle, SW_HIDE);

    // Logic > ...
    if (0u == ::RegisterClassEx((WNDCLASSEX const*) &windowClass)) {
        // Deletion; Terminate
        ::DestroyCursor(windowClass.hCursor);
        ::exit(EXIT_FAILURE);
    }

    else {
        // Constant > Window Handle
        HWND const windowHandle = ::CreateWindowEx(
            WS_EX_LAYERED, windowClass.lpszClassName, "Transparent Layered Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            HWND_DESKTOP, (HMENU) NULL, windowClass.hInstance, NULL
        );

        // Logic > ...
        if (NULL == windowHandle) {
            // Deletion; Terminate
            ::DestroyCursor(windowClass.hCursor);
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            ::exit(EXIT_FAILURE);
        }

        else {
            // Initialization > Window Procedure Message
            MSG windowProcedureMessage = {};

            // ...; Loop
            ::SetLayeredWindowAttributes(windowHandle, RGB(127, 127, 127), 127u, LWA_ALPHA | LWA_COLORKEY);
            while (::GetMessage(&windowProcedureMessage, NULL, 0x0, 0x0)) {
                // Logic > ...
                if (WM_CLOSE == windowProcedureMessage.message) ::DestroyWindow(windowHandle);
                if (WM_DESTROY == windowProcedureMessage.message || WM_QUIT == windowProcedureMessage.message) break;
                else ::DispatchMessage(&windowProcedureMessage);
            }

            // Deletion; Terminate
            ::DestroyCursor(windowClass.hCursor);
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            ::exit(windowProcedureMessage.wParam);
        }
    }

    return EXIT_SUCCESS;
}
