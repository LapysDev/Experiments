/* Import */
#include <math.h> // Mathematics
#include <windows.h> // Windows

/* Global > ... */
unsigned short ANGLE = 0u;
const unsigned short LENGTH = 250u;
const unsigned short ORIGIN = (unsigned short) (((float) LENGTH) * (125.0f / 100.0f));

/* Declaration > ... */
void drawOriginCrosshair(const HWND, const HDC) noexcept;
void putPixel(const HWND, const HDC, const int, const int, const COLORREF) noexcept;

/* Function */
    // Draw Line
        // [At Angle]
        void drawLine(const HWND windowHandle, const HDC graphicsDeviceContextHandle, float angle, const COLORREF color) noexcept {
            // Loop > Update > Angle
            while (angle >= 360.0f) angle -= 360.0f;

            // Logic > ...
            if (0.0f == angle || angle == 360.0f) for (unsigned short iterator = 0u; iterator ^ LENGTH; ++iterator) ::putPixel(windowHandle, graphicsDeviceContextHandle, 0, -((short) iterator), color);
            else if (angle == 90.0f) for (unsigned short iterator = 0u; iterator ^ LENGTH; ++iterator) ::putPixel(windowHandle, graphicsDeviceContextHandle, iterator, 0, color);
            else if (angle == 180.0f) for (unsigned short iterator = 0u; iterator ^ LENGTH; ++iterator) ::putPixel(windowHandle, graphicsDeviceContextHandle, 0, iterator, color);
            else if (angle == 270.0f) for (unsigned short iterator = 0u; iterator ^ LENGTH; ++iterator) ::putPixel(windowHandle, graphicsDeviceContextHandle, -((short) iterator), 0, color);
            else {
                /* ... */
                #define LINE_DRAW_METHOD
                #  define CUSTOM_METHOD 0
                #  define PYTHAGOREAN_METHOD 1

                #undef LINE_DRAW_METHOD
                #define LINE_DRAW_METHOD CUSTOM_METHOD

                /* ... */
                #if LINE_DRAW_METHOD == CUSTOM_METHOD
                    // Initialization > (X, Y) ...
                    short x = 0;
                    float xRatio, xRatioIterator = 0.0f;
                    float xWeight = 0.0f;

                    short y = 0;
                    float yRatio, yRatioIterator = 0.0f;
                    float yWeight = -90.0f;

                    // Update > (X, Y) Weight --- NOTE (Lapys) -> The offset angle from each quadrant (with the signedness representing each sector).
                    {
                        // Initialization > Angular (Iterator, Length)
                        float angularIterator = 0.0f;
                        float angularLength = (float) (int) angle;

                        // Loop
                        for (; angularLength != angularIterator; ++angularIterator) {
                            // Logic > Update > (X, Y) Weight
                            if (angularIterator >= 0.0f && angularIterator < 90.0f) { ++xWeight; ++yWeight; }
                            else if (angularIterator >= 90.0f && angularIterator < 180.0f) { --xWeight; ++yWeight; }
                            else if (angularIterator >= 180.0f && angularIterator < 270.0f) { --xWeight; --yWeight; }
                            else if (angularIterator >= 270.0f && angularIterator < 360.0f) { ++xWeight; --yWeight; }
                        }

                        // Logic
                        if (angularIterator != angle) {
                            // Logic > Update > (X, Y) Weight
                            if (angularIterator >= 0.0f && angularIterator < 90.0f) { xWeight += angle - angularIterator; yWeight += angle - angularIterator; }
                            else if (angularIterator >= 90.0f && angularIterator < 180.0f) { xWeight -= angle - angularIterator; yWeight += angle - angularIterator; }
                            else if (angularIterator >= 180.0f && angularIterator < 270.0f) { xWeight -= angle - angularIterator; yWeight -= angle - angularIterator; }
                            else if (angularIterator >= 270.0f && angularIterator < 360.0f) { xWeight += angle - angularIterator; yWeight -= angle - angularIterator; }
                        }
                    }

                    // (Logic > )Update > (X, Y) Ratio --- NOTE (Lapys) -> Ratio between the offset angle on the X and Y axis respectively.
                    xRatio = xWeight < 0.0f ? -xWeight : xWeight;
                    yRatio = yWeight < 0.0f ? -yWeight : yWeight;

                    if (xRatio > yRatio) { yRatio /= xRatio; xRatio /= xRatio; }
                    else if (xRatio < yRatio) { xRatio /= yRatio; yRatio /= yRatio; }
                    else { xRatio /= xRatio; yRatio /= yRatio; }

                    // Loop --- NOTE (Lapys) -> Draw the line.
                    for (float iterator = 0.0f; iterator <= LENGTH; ++iterator) {
                        // Update > (X, Y) Ratio Iterator
                        xRatioIterator += xRatio;
                        yRatioIterator += yRatio;

                        // Logic > ... --- NOTE (Lapys) -> Determines the length of the line (at an angle).
                        if ((x * x) + (y * y) <= LENGTH * LENGTH)
                        ::putPixel(windowHandle, graphicsDeviceContextHandle, x, y, color);

                        // Logic > Update > ... --- NOTE (Lapys) -> Determines the angle of the line.
                        if (xRatioIterator >= 1.0f) { xWeight < 0.0f ? --x : ++x; --xRatioIterator; }
                        if (yRatioIterator >= 1.0f) { yWeight < 0.0f ? --y : ++y; --yRatioIterator; }
                    }

                #elif LINE_DRAW_METHOD == PYTHAGOREAN_METHOD
                    // Initialization > (X, Y) Iterator
                    short xIterator = 0;
                    short yIterator = 0;

                    // Loop
                    for (unsigned short iterator = 0u; iterator ^ LENGTH; ++iterator) {
                        // Initialization > (X, Y) --- NOTE (Lapys) -> Determines the angle of the line.
                        short x = xIterator / ::cos(angle * (M_PI / 180.0f));
                        short y = yIterator / ::sin(angle * (M_PI / 180.0f));

                        // Logic > ... --- NOTE (Lapys) -> Determines the length of the line (at an angle).
                        if (::(x * x) + (y * y) <= LENGTH * LENGTH)
                        ::putPixel(windowHandle, graphicsDeviceContextHandle, x, y, color);

                        // Logic > Update > (X, Y) Iterator
                        if (angle > 0.0f && angle < 90.0f) { ++xIterator; --yIterator; }
                        else if (angle > 90.0f && angle < 180.0f) { --xIterator; ++yIterator; }
                        else if (angle > 180.0f && angle < 270.0f) { ++xIterator; --yIterator; }
                        else if (angle > 270.0f && angle < 360.0f) { --xIterator; ++yIterator; }
                    }
                #endif

                #undef CUSTOM_METHOD
                #undef LINE_DRAW_METHOD
                #undef PYTHAGOREAN_METHOD
            }
        }

        // [To Coordinate]
        void drawLine(const HWND windowHandle, const HDC graphicsDeviceContextHandle, const short xTarget, const short yTarget, const COLORREF color) noexcept {
            // Initialization > Window Client Area Bounding Box
            // : Update > Window Client Area Bounding Box
            RECT windowClientAreaBoundingBox {};
            ::GetClientRect(windowHandle, &windowClientAreaBoundingBox);

            // Constant > (X, Y) Origin
            const short xOrigin = windowClientAreaBoundingBox.right / 2L;
            const short yOrigin = windowClientAreaBoundingBox.bottom / 2L;

            // Logic --- NOTE (Lapys) -> Can also optimize for diagonal, horizontal and vertical lines.
            if (false) {}
            else {
                /* ... */
                #define LINE_DRAW_METHOD
                #  define BRESENHAM_METHOD 0
                #  define CUSTOM_METHOD 1
                #  define WU_METHOD 2

                #undef LINE_DRAW_METHOD
                #define LINE_DRAW_METHOD CUSTOM_METHOD

                /* ... --- UPDATE (Lapys) */
                #if LINE_DRAW_METHOD == BRESENHAM_METHOD
                #elif LINE_DRAW_METHOD == CUSTOM_METHOD
                    // Initialization > (X, Y) ...
                    short x = 0;
                    unsigned short xDistance = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget;
                    float xRatio = 1.0f, xRatioIterator = 0.0f;

                    short y = 0;
                    unsigned short yDistance = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;
                    float yRatio = 1.0f, yRatioIterator = 0.0f;

                    // Logic > Update > (X, Y) Ratio
                    if (xDistance > yDistance) yRatio = ((float) yDistance) / (float) xDistance;
                    else if (xDistance < yDistance) xRatio = ((float) xDistance) / (float) yDistance;

                    // Loop
                    while (((x + xOrigin) ^ xTarget) && ((y + yOrigin) ^ yTarget)) {
                        // Update > (X, Y) Ratio Iterator
                        xRatioIterator += xRatio;
                        yRatioIterator += yRatio;

                        // ...
                        ::putPixel(windowHandle, graphicsDeviceContextHandle, x, y, color);

                        // Logic > Update > ...
                        if (xRatioIterator >= 1.0f) { xOrigin > xTarget ? --x : ++x; --xRatioIterator; }
                        if (yRatioIterator >= 1.0f) { yOrigin > yTarget ? --y : ++y; --yRatioIterator; }
                    }
                #endif

                #undef BRESENHAM_METHOD
                #undef CUSTOM_METHOD
                #undef LINE_DRAW_METHOD
                #undef WU_METHOD
            }
        }

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

                /* [At an Angle] */ {
                    for (float angle = 0.0f; angle <= 360.0f; ++angle)
                    ::drawLine(windowHandle, windowGraphicsDeviceContextHandle, angle, RGB(204, 204, 204));
                }
                /* [To a Coordinate] */ {
                    RECT& windowClientAreaBoundingBox = windowPaintInformation.rcPaint;

                    for (unsigned short iterator = 0u, length = 375u; iterator ^ length; ++iterator)
                    ::drawLine(windowHandle, windowGraphicsDeviceContextHandle, (unsigned short) (::rand() % (windowClientAreaBoundingBox.right - windowClientAreaBoundingBox.left)), (unsigned short) (::rand() % (windowClientAreaBoundingBox.bottom - windowClientAreaBoundingBox.top)), RGB(240, 240, 240));
                }

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
        WNDCLASS windowClass {CS_HREDRAW | CS_VREDRAW, &windowProcedure, 0, 0, instanceHandle, 0x0, (HCURSOR) ::LoadCursor(0x0, IDC_ARROW), (HBRUSH) COLOR_WINDOW + 1, 0x0, "Line Segment"};
        HWND windowHandle = 0x0;
        MSG windowProcedureMessage {windowHandle, 0, EXIT_SUCCESS, 0, 0, {0L, 0L}};

    // ...
    ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);
    ::FillConsoleOutputCharacter(screenConsoleBufferHandle, ' ', screenConsoleBufferInformation.dwSize.X * screenConsoleBufferInformation.dwSize.Y, {0L, 0L}, &screenConsoleBufferBytesWritten);
    ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
    ::SetConsoleCursorPosition(screenConsoleBufferHandle, {0, 1});
    ::SetConsoleTitle("Line Segment");
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);

    ::WriteConsoleOutputCharacter(screenConsoleBufferHandle, "[PROGRAM INITIATED]", 19, {0, 0}, &screenConsoleBufferBytesWritten);

    // Logic
    if (::RegisterClass(&windowClass)) {
        // Update > Window Handle
        windowHandle = ::CreateWindowEx(0, windowClass.lpszClassName, "Line Segment", WS_OVERLAPPEDWINDOW | WS_VISIBLE, (::GetSystemMetrics(SM_CXSCREEN) - (ORIGIN * 2u)) / 2, (::GetSystemMetrics(SM_CYSCREEN) - (ORIGIN * 2u)) / 2, ORIGIN * 2u, ORIGIN * 2u, 0x0, 0x0, instanceHandle, 0x0);

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
