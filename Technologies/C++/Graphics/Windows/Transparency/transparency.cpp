/* Import */
#include <windows.h> // Windows

/* Function */
    // Draw Transparent Window
    void drawTransparentWindow(const HWND windowHandle, const HDC graphicsDeviceContextHandle) noexcept {
        // Initialization > (Display ..., Window Bounding Box)
        HDC displayGraphicsDeviceContext;
        int displayHeight, displayWidth;

        RECT windowBoundingBox {};

        // Update > (Display ..., Window Handle)
        displayGraphicsDeviceContext = ::GetDC(NULL);
        displayHeight = ::GetSystemMetrics(SM_CYVIRTUALSCREEN);
        displayWidth = ::GetSystemMetrics(SM_CXVIRTUALSCREEN);

        ::GetWindowRect(windowHandle, &windowBoundingBox);

        // Update > Graphics Device Context Handle
        ::BitBlt(
            graphicsDeviceContextHandle,
            0, 0,
            displayWidth, displayHeight,
            displayGraphicsDeviceContext,
            windowBoundingBox.left, windowBoundingBox.top,
            SRCCOPY
        );

        // Deletion
        ::DeleteDC(displayGraphicsDeviceContext);
    }

    /* Window Procedure */
    LRESULT CALLBACK windowProcedure(HWND windowHandle, UINT message, WPARAM messageParameter, LPARAM additionalMessageParameter) noexcept {
        // Logic
        switch (message) {
            // [Paint]
            case WM_PAINT: {
                // Initialization > Window (Graphics Device Context Handle, Paint Information)
                HDC windowGraphicsDeviceContextHandle;
                PAINTSTRUCT windowPaintInformation;

                // Update > Window Graphics Device Context Handle
                windowGraphicsDeviceContextHandle = ::BeginPaint(windowHandle, &windowPaintInformation);

                /* ... */
                ::drawTransparentWindow(windowHandle, windowGraphicsDeviceContextHandle);

                // Deletion
                ::ReleaseDC(windowHandle, windowGraphicsDeviceContextHandle);
                ::EndPaint(windowHandle, &windowPaintInformation);
            } break;

            /* ... */
            case WM_CLOSE: case WM_DESTROY: case WM_QUIT: case WM_KEYDOWN: {
                // Logic > ...
                if (message != WM_KEYDOWN || messageParameter == VK_ESCAPE) {
                    ::DestroyWindow(windowHandle);
                    ::PostQuitMessage(0);
                }
            } break;
        }

        // Return
        return ::DefWindowProc(windowHandle, message, messageParameter, additionalMessageParameter);
    }

/* Main */
int WinMain(HINSTANCE instanceHandle, HINSTANCE /*previousInstanceHandle*/, LPSTR /*programInitiationCommandLine*/, int windowAppearance) {
    /* Global > Program Status */
    int PROGRAM_STATUS = EXIT_SUCCESS;

    /* Initialization */
        // Screen Console Buffer (Bytes Written, Handle, Information)
        DWORD screenConsoleBufferBytesWritten;
        HANDLE screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0x0, OPEN_ALWAYS, 0, 0x0);
        CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation;

        // Window (Class, Handle, Procedure Message)
        WNDCLASS windowClass {CS_HREDRAW | CS_VREDRAW, &windowProcedure, 0, 0, instanceHandle, 0x0, (HCURSOR) ::LoadCursor(0x0, IDC_ARROW), (HBRUSH) COLOR_WINDOW + 1, 0x0, "Circle"};
        HWND windowHandle = 0x0;
        MSG windowProcedureMessage {windowHandle, 0, EXIT_SUCCESS, 0, 0, {0L, 0L}};

    // ...
    ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);
    ::FillConsoleOutputCharacter(screenConsoleBufferHandle, ' ', screenConsoleBufferInformation.dwSize.X * screenConsoleBufferInformation.dwSize.Y, {0L, 0L}, &screenConsoleBufferBytesWritten);
    ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
    ::SetConsoleCursorPosition(screenConsoleBufferHandle, {0, 1});
    ::SetConsoleTitle("Circle");
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);

    ::WriteConsoleOutputCharacter(screenConsoleBufferHandle, "[PROGRAM INITIATED]", 19, {0, 0}, &screenConsoleBufferBytesWritten);

    // Logic
    if (::RegisterClass(&windowClass)) {
        // Update > Window Handle
        windowHandle = ::CreateWindowEx(0, windowClass.lpszClassName, "Circle", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0x0, 0x0, instanceHandle, 0x0);

        // Logic > ...
        if (windowHandle) {
            // Update > Window Handle
            ::ShowWindow(windowHandle, windowAppearance);
            ::UpdateWindow(windowHandle);

            // Loop
            while (::GetMessage(&windowProcedureMessage, 0x0, 0, 0)) {
                // Update > Window Procedure Message
                ::TranslateMessage(&windowProcedureMessage);
                ::DispatchMessage(&windowProcedureMessage);
            }

            // Update > Program Status
            PROGRAM_STATUS = windowProcedureMessage.wParam;
        }

        else
            // Terminate
            ::exit(PROGRAM_STATUS = EXIT_FAILURE);

        // Deletion
        ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
    }

    else
        // Terminate
        ::exit(PROGRAM_STATUS = EXIT_FAILURE);

    // ...
    ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);
    ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);

    ::WriteConsoleOutputCharacter(screenConsoleBufferHandle, "[PROGRAM TERMINATED]", 20, {0, (short) (screenConsoleBufferInformation.dwCursorPosition.Y + 1)}, &screenConsoleBufferBytesWritten);
    ::SetConsoleCursorPosition(screenConsoleBufferHandle, {0, (short) (screenConsoleBufferInformation.dwCursorPosition.Y + 1)});

    // Return
    return PROGRAM_STATUS;
}
