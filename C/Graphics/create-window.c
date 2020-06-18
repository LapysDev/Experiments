/* Import */
#include <stdlib.h> // Standard Library
#include <windows.h> // Windows

// Function > Window Procedure
LRESULT CALLBACK windowProcedure(HWND windowHandle, unsigned int message, WPARAM argument, LPARAM subargument) {
    // Logic > ...
    switch (message) {
        case WM_CLOSE: DestroyWindow(windowHandle); // NOTE (Lapys) -> Moderator to `CreateWindow...` invocation.
        case WM_DESTROY: case WM_QUIT: PostQuitMessage(0x0); /* -> PostMessage(HWND_BROADCAST, 0x0, 0, 0); */ break;
    }

    // Return
    return DefWindowProc(windowHandle, message, argument, subargument);
}

/* Main */
int APIENTRY WinMain(HINSTANCE instanceHandle, HINSTANCE previousInstanceHandle, LPSTR programArguments, int windowAppearance) { (void) previousInstanceHandle; (void) programArguments;
    // Initialization > Window ...
    WNDCLASS windowClass = {
        .style = CS_HREDRAW | CS_VREDRAW, // NOTE (Lapys) -> Pre-defined look of window instances of the class.
        .lpfnWndProc = &windowProcedure, // NOTE (Lapys) -> Event loop or Message queue.
        .cbClsExtra = 0x0, // NOTE (Lapys) -> Extra bytes to allocate following the window class structure.
        .cbWndExtra = 0x0, // NOTE (Lapys) -> Extra bytes to allocate following the window instance.
        .hInstance = instanceHandle,
        .hIcon = 0x0, // NOTE (Lapys) -> Window favorite icon.
        .hCursor = (HCURSOR) LoadCursor(0x0, IDC_ARROW), // NOTE (Lapys) -> Window cursor.
        .hbrBackground = (HBRUSH) COLOR_WINDOW + 1, // NOTE (Lapys) -> Window background color.
        .lpszMenuName = 0x0, // NOTE (Lapys) -> Resource name of the window class menu.
        .lpszClassName = "Window Default Class Name"
    };
    HWND windowHandle = NULL;
    MSG windowProcedureMessage = {
        .hwnd = windowHandle,
        .message = 0x0,
        .wParam = EXIT_SUCCESS,
        .lParam = 0x0,
        .time = 0x0,
        .pt = {0L, 0L}
    };

    // Logic > ...
    if (RegisterClass(&windowClass)) {
        // Logic > ...
        if ((windowHandle = CreateWindowEx(
            0x0, // NOTE (Lapys) -> Extended style.
            windowClass.lpszClassName, "Window Name",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE, // NOTE (Lapys) -> Style.
            CW_USEDEFAULT, CW_USEDEFAULT, // NOTE (Lapys) -> XY position.
            (int) ((float) GetSystemMetrics(SM_CXSCREEN) * (75.0f / 100.0f)),
            (int) ((float) GetSystemMetrics(SM_CYSCREEN) * (75.0f / 100.0f)), // NOTE (Lapys) -> Height & width (irrespectively).
            NULL, // NOTE (Lapys) -> Parent window.
            NULL, // NOTE (Lapys) -> Menu?
            instanceHandle,
            NULL // NOTE (Lapys) -> Instantiation event.
        ))) {
            // ...
            FreeConsole(); // NOTE (Lapys) -> Not using the console terminal.

            ShowWindow(windowHandle, windowAppearance);
            UpdateWindow(windowHandle);

            // Loop
            while (
                GetMessage(&windowProcedureMessage, NULL, 0, 0 /* NOTE (Lapys) -> `0, 0` are the ranges of acceptable window messages (events). */)
                /* PeekMessage(&windowProcedureMessage, NULL, 0, 0, (PM_NOREMOVE | PM_REMOVE) | PM_NOYIELD) */
            ) {
                // Update > Window Procedure Message
                TranslateMessage(&windowProcedureMessage);
                DispatchMessage(&windowProcedureMessage);
            }

            // Logic > Terminate
            if (EXIT_SUCCESS != windowProcedureMessage.wParam) abort();
        } else abort();

        // Deletion
        UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
    } else abort();

    // Return
    return EXIT_SUCCESS;
}
