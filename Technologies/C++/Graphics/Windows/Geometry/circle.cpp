/* Import */
#include <windows.h> // Windows

/* Global > ... */
const unsigned short LENGTH = 250u;
const unsigned short ORIGIN = (unsigned short) (((float) LENGTH) * (125.0f / 100.0f));

/* Declaration > ... */
void drawOriginCrosshair(const HWND, const HDC) noexcept;
void putPixel(const HWND, const HDC, const int, const int, const COLORREF) noexcept;

/* Function */
    // Draw Circle
    void drawCircle(const HWND windowHandle, const HDC graphicsDeviceContextHandle, const unsigned short radius, const COLORREF color) noexcept {
        // Initialization > (X, Y)
        short x;
        short y;

        // Loop
        for (x = -radius; x <= radius; ++x)
        for (y = -radius; y <= radius; ++y) {
            // Initialization > (Coordinate, Distance, Thickness)
            int coordinate = (x * x) + (y * y);
            unsigned int distance = radius * radius;
            unsigned short thickness = radius;

            // Logic > ...
            if ((unsigned long) coordinate >= distance - thickness && (unsigned long) coordinate <= distance + thickness)
            ::putPixel(windowHandle, graphicsDeviceContextHandle, x, y, color);
        }
    }
    inline void drawCircle(const HWND windowHandle, const HDC graphicsDeviceContextHandle, const COLORREF color) noexcept { ::drawCircle(windowHandle, graphicsDeviceContextHandle, LENGTH, color); }

    // Draw Origin Cross Hair
    void drawOriginCrosshair(const HWND windowHandle, const HDC graphicsDeviceContextHandle) noexcept {
        // Constant > Cross Hair Color
        const COLORREF crosshairColor = RGB(51, 51, 51);

        // Initialization > Window Client Area (Bounding Box, Origin)
        RECT windowClientAreaBoundingBox {};
        COORD windowClientAreaOrigin {};

        // Update > Window Client Area (Bounding Box, Origin)
        ::GetClientRect(windowHandle, &windowClientAreaBoundingBox);

        windowClientAreaOrigin.X = windowClientAreaBoundingBox.right / 2;
        windowClientAreaOrigin.Y = windowClientAreaBoundingBox.bottom / 2;

        // Loop > Logic > ... --- REDACT (Lapys)
        for (short iterator = 0, length = (short) (((float) LENGTH) * (75.0f / 100.0f)), x, y; iterator ^ length; ++iterator) {
        if (iterator > 3) {
            x = 0 + windowClientAreaOrigin.X; y = iterator + windowClientAreaOrigin.Y; ::SetPixelV(graphicsDeviceContextHandle, x, y, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x, y + 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x, y - 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x + 1, y, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x + 1, y + 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x + 1, y - 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x - 1, y, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x - 1, y + 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x - 1, y - 1, crosshairColor);
            x = 0 + windowClientAreaOrigin.X; y = -iterator + windowClientAreaOrigin.Y; ::SetPixelV(graphicsDeviceContextHandle, x, y, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x, y + 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x, y - 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x + 1, y, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x + 1, y + 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x + 1, y - 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x - 1, y, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x - 1, y + 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x - 1, y - 1, crosshairColor);
            x = iterator + windowClientAreaOrigin.X; y = 0 + windowClientAreaOrigin.Y; ::SetPixelV(graphicsDeviceContextHandle, x, y, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x, y + 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x, y - 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x + 1, y, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x + 1, y + 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x + 1, y - 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x - 1, y, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x - 1, y + 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x - 1, y - 1, crosshairColor);
            x = -iterator + windowClientAreaOrigin.X; y = 0 + windowClientAreaOrigin.Y; ::SetPixelV(graphicsDeviceContextHandle, x, y, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x, y + 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x, y - 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x + 1, y, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x + 1, y + 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x + 1, y - 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x - 1, y, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x - 1, y + 1, crosshairColor); ::SetPixelV(graphicsDeviceContextHandle, x - 1, y - 1, crosshairColor);
        } }
    }

    // Put Pixel --- NOTE (Lapys) -> Places the pixel at the center of the window.
    inline void putPixel(const HWND windowHandle, const HDC graphicsDeviceContextHandle, const int x, const int y, const COLORREF color) noexcept {
        // Initialization > Window Client Area Bounding Box
        // : Update > Window Client Area Bounding Box
        RECT windowClientAreaBoundingBox {};
        ::GetClientRect(windowHandle, &windowClientAreaBoundingBox);

        /* .... */
        ::SetPixelV(graphicsDeviceContextHandle, x + (windowClientAreaBoundingBox.right / 2L), y + (windowClientAreaBoundingBox.bottom / 2L), color);
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
                ::drawOriginCrosshair(windowHandle, windowGraphicsDeviceContextHandle);

                /* [At Arithmetic Distances] */ {
                    for (unsigned char color = 0u, iterator = 0u, length = ((unsigned char) -1u) - 1u; iterator ^ length; (++color, ++iterator))
                    ::drawCircle(windowHandle, windowGraphicsDeviceContextHandle, iterator, RGB(color, color, color));
                }
                /* [At Crosshair] */ { ::drawCircle(windowHandle, windowGraphicsDeviceContextHandle, (unsigned short) (((float) LENGTH) * (75.0f / 100.0f)), RGB(240, 240, 240)); }
                /* [At Length] */ { ::drawCircle(windowHandle, windowGraphicsDeviceContextHandle, LENGTH, RGB(240, 240, 240)); }

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
        windowHandle = ::CreateWindowEx(0, windowClass.lpszClassName, "Circle", WS_OVERLAPPEDWINDOW | WS_VISIBLE, (::GetSystemMetrics(SM_CXSCREEN) - (ORIGIN * 2u)) / 2, (::GetSystemMetrics(SM_CYSCREEN) - (ORIGIN * 2u)) / 2, ORIGIN * 2u, ORIGIN * 2u, 0x0, 0x0, instanceHandle, 0x0);

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
