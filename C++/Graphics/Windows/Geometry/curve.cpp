/* Import */
#include <stdio.h>
#include <windows.h> // Windows

/* Global > ... */
const unsigned short LENGTH = 250u;
const unsigned short ORIGIN = (unsigned short) (((float) LENGTH) * (125.0f / 100.0f));

/* Declaration > ... */
void putPixel(const HDC, const int, const int, const COLORREF) noexcept;

/* Function */
    // Draw Curve
    void drawCurve(const HDC graphicsDeviceContextHandle, const short xStart, const short yStart, const short xEnd, const short yEnd, const short xAuxiliary, const short yAuxiliary, const COLORREF color) noexcept {
        // Initialization > (X, Y) ...
        short x, xIterator;
        unsigned short xDistance;
        float xRatio, xRatioIterator;

        short y, yIterator;
        unsigned short yDistance;
        float yRatio, yRatioIterator;

        // Update > (X, Y) ...
        xDistance = xStart < xEnd ? xEnd - xStart : xStart - xEnd;
        xIterator = 0; xRatioIterator = 0.0f;

        yDistance = yStart < yEnd ? yEnd - yStart : yStart - yEnd;
        yIterator = 0; yRatioIterator = 0.0f;

        if (xDistance > yDistance) { xRatio = 1.0f; yRatio = ((float) yDistance) / (float) xDistance; }
        else if (xDistance < yDistance) { xRatio = ((float) xDistance) / (float) yDistance; yRatio = 1.0f; }
        else { xRatio = 1.0f; yRatio = 1.0f; }

        // Loop
        while (
            ((xIterator + xStart) ^ xEnd) &&
            ((yIterator + yStart) ^ yEnd)
        ) {
            // Update > (X, Y) ...
            xRatioIterator += xRatio;
            yRatioIterator += yRatio;

            x = xIterator;
            y = yIterator;

            // ...
            ::putPixel(graphicsDeviceContextHandle, x, y, color);

            // Logic > Update > ...
            if (xRatioIterator >= 1.0f) { xStart > xEnd ? --xIterator : ++xIterator; --xRatioIterator; }
            if (yRatioIterator >= 1.0f) { yStart > yEnd ? --yIterator : ++yIterator; --yRatioIterator; }
        }
    }
    void drawCurve(const HDC graphicsDeviceContextHandle, const short xStart, const short yStart, const short xEnd, const short yEnd, const short xAuxiliarys[], const short yAuxiliarys[], const COLORREF color) noexcept;

    // Put Pixel
    inline void putPixel(const HDC graphicsDeviceContextHandle, const int x, const int y, const COLORREF color) noexcept { ::SetPixelV(graphicsDeviceContextHandle, x, y, color); }

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
                ::drawCurve(windowGraphicsDeviceContextHandle,
                    0, 0, LENGTH, LENGTH,
                    LENGTH + (LENGTH / 3u), (LENGTH / 2u) + (LENGTH / 4u),
                    RGB(240, 240, 240)
                );

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
        WNDCLASS windowClass {CS_HREDRAW | CS_VREDRAW, &windowProcedure, 0, 0, instanceHandle, 0x0, (HCURSOR) ::LoadCursor(0x0, IDC_ARROW), (HBRUSH) COLOR_WINDOW + 1, 0x0, "Curve"};
        HWND windowHandle = 0x0;
        MSG windowProcedureMessage {windowHandle, 0, EXIT_SUCCESS, 0, 0, {0L, 0L}};

    // ...
    ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);
    ::FillConsoleOutputCharacter(screenConsoleBufferHandle, ' ', screenConsoleBufferInformation.dwSize.X * screenConsoleBufferInformation.dwSize.Y, {0L, 0L}, &screenConsoleBufferBytesWritten);
    ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
    ::SetConsoleCursorPosition(screenConsoleBufferHandle, {0, 1});
    ::SetConsoleTitle("Curve");
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);

    ::WriteConsoleOutputCharacter(screenConsoleBufferHandle, "[PROGRAM INITIATED]", 19, {0, 0}, &screenConsoleBufferBytesWritten);

    // Logic
    if (::RegisterClass(&windowClass)) {
        // Update > Window Handle
        windowHandle = ::CreateWindowEx(0, windowClass.lpszClassName, "Curve", WS_OVERLAPPEDWINDOW | WS_VISIBLE, (::GetSystemMetrics(SM_CXSCREEN) - (ORIGIN * 2u)) / 2, (::GetSystemMetrics(SM_CYSCREEN) - (ORIGIN * 2u)) / 2, ORIGIN * 2u, ORIGIN * 2u, 0x0, 0x0, instanceHandle, 0x0);

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
