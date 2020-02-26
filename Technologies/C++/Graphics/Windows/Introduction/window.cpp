/* Import */
#include <stddef.h> // C Standard Definitions
#include <stdlib.h> // C Standard Library
#include <stdio.h> // C Standard Input-Output

#include <windows.h> // Windows

/* Function > Window Procedure */
LRESULT CALLBACK windowProcedure(HWND windowHandle, UINT message, WPARAM messageParameter, LPARAM additionalMessageParameter) {
    // Initialization > Window Procedure Invocation Count
    static size_t windowProcedureInvocationCount = 0u;

    // Logic ...; Print
    switch (message) {
        case WM_CLOSE: { ::DestroyWindow(windowHandle); ::PostQuitMessage(0); } break;
        case WM_DESTROY: ::PostQuitMessage(0); break;
        case WM_KEYDOWN: if (messageParameter == VK_ESCAPE) { ::DestroyWindow(windowHandle); ::PostQuitMessage(0); } break;
        case WM_QUIT: ::DestroyWindow(windowHandle); break;
        case WM_SYSCOMMAND: if (messageParameter == SC_CLOSE) { ::DestroyWindow(windowHandle); ::PostQuitMessage(0); } break;
        case WM_SYSKEYDOWN: if (messageParameter == VK_F4) { ::DestroyWindow(windowHandle); ::PostQuitMessage(0); } break;
    } ::printf("\r                                   \r%s%u", "Message Count: ", ++windowProcedureInvocationCount);

    // Return --- NOTE (Lapys) -> Prevent control reaching here to abate default procedures to window messages.
    return ::DefWindowProc(windowHandle, message, messageParameter, additionalMessageParameter);
}

/* Main */
int WinMain(HINSTANCE instanceHandle, HINSTANCE /*previousInstanceHandle*/, LPSTR /*programInitiationCommandLine*/, int windowAppearance) {
    // Initialization > Window ...
    WNDCLASS windowClass {CS_HREDRAW | CS_VREDRAW, &windowProcedure, 0, 0, instanceHandle, NULL, (HCURSOR) ::LoadCursor(NULL, IDC_ARROW), (HBRUSH) COLOR_WINDOW, NULL, "Window Class"};
    HWND windowHandle = NULL;
    MSG windowProcedureMessage {windowHandle, 0, EXIT_SUCCESS, 0, 0, {0L, 0L}};

    // Logic
    if (::RegisterClass(&windowClass)) {
        // Update > Window Handle
        windowHandle = ::CreateWindow(windowClass.lpszClassName, "Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, instanceHandle, NULL);

        // Logic
        if (windowHandle) {
            // Update > Window Handle
            ::ShowWindow(windowHandle, windowAppearance);
            ::UpdateWindow(windowHandle);

            // Loop > Update > Window Procedure Message
            while (::GetMessage(&windowProcedureMessage, NULL, 0, 0)) {
                ::TranslateMessage(&windowProcedureMessage);
                ::DispatchMessage(&windowProcedureMessage);
            }

            // Deletion; Terminate
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            ::exit(windowProcedureMessage.wParam);
        }

        else {
            // Deletion; Terminate
            ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
            ::exit(EXIT_FAILURE);
        }
    }

    else
        // Terminate
        ::exit(EXIT_FAILURE);

    // Return
    return EXIT_SUCCESS;
}
