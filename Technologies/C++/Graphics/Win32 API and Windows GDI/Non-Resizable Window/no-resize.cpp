/* Definition --- NOTE (Lapys) -> Hopefully these are accurate. */
#define NULL ((void*) 0)
#define STDOUT_FILENO 1

/* Import */
#include <unistd.h> // UNIX Standard
#include <windows.h> // Windows

/* Function > Window ... */
LRESULT CALLBACK windowProcedure(HWND window, unsigned message, unsigned messageParameter, long additionalMessageParameter) {
    // Logic
    switch (message) {
        case WM_CLOSE: ::DestroyWindow(window); ::PostQuitMessage(0); break;
        case WM_DESTROY: ::PostQuitMessage(0); break;
        default: return ::DefWindowProc(window, message, messageParameter, additionalMessageParameter);
    }

    // Return
    return 0;
}

/* Main */
int WinMain(HINSTANCE handlerInstance, HINSTANCE previousHandlerInstance, LPSTR programInitiationCommandLine, int windowAppearance) {
    // [Begin] ...
    ::write(STDOUT_FILENO, "[PROGRAM INITIATED]\n", 20u);

    // Declaration > Window Class ...
    WNDCLASS windowClass {};

    const char windowClassName[] = "Window Class Name";
    HINSTANCE& windowHandlerInstance = handlerInstance;

    // Deletion
    ::ZeroMemory(&windowClass, sizeof(windowClass));

    // Modification > Window Class > ...
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
    windowClass.hCursor = (HCURSOR) ::LoadCursor(NULL, IDC_ARROW);
    windowClass.hIcon = NULL;
    windowClass.hInstance = windowHandlerInstance;
    windowClass.lpszClassName = windowClassName;
    windowClass.lpszMenuName = NULL;
    windowClass.lpfnWndProc = &windowProcedure;
    windowClass.style = CS_HREDRAW | CS_VREDRAW;

    // Logic
    if (::RegisterClass(&windowClass)) {
        // Declaration > Window
        HWND window = ::CreateWindowEx(0, windowClassName, "Image Capture", WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_OVERLAPPED | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, handlerInstance, NULL);

        // Logic
        if (window) {
            // Initialization > Window ...
            MSG windowProcedureMessage {};

            // ...
            ::ShowWindow(window, windowAppearance);
            ::UpdateWindow(window);

            // Loop --- NOTE (Lapys) -> Event loop.
            while (true) {
                // Logic
                if (::GetMessage(&windowProcedureMessage, NULL, 0, 0)) {
                    // Logic
                    if (windowProcedureMessage.message == WM_QUIT) break;
                    else {
                        // ...
                        ::TranslateMessage(&windowProcedureMessage);
                        ::DispatchMessage(&windowProcedureMessage);
                    }
                } else break;
            }
        }

        // Deletion
        ::UnregisterClass(windowClassName, windowHandlerInstance);
    }

    // [End] ...
    ::write(STDOUT_FILENO, "\n[PROGRAM TERMINATED]", 21u);

    // Return
    return 0;
}
