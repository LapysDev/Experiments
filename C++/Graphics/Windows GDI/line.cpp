/* Import --> gdi32.dll, kernel32.dll, shell32.dll, user32.dll */
// : [C Standard Library]
#include <stdint.h> // Standard Integers

// : [C++ Standard Library]
#include <cstdarg> // C Standard Arguments
#include <cstdio>
#include <cstdlib> // C Standard Library

// : [Windows API]
#include <windef.h> // Windows Definitions
#include <winbase.h> // Windows Base
#include <wingdi.h> // Windows Graphics Device Interface (GDI)
#include <winnt.h> // Windows New Technologies
#include <winuser.h> // Windows User

#include <basetsd.h> // Base Type Definitions
#include <fileapi.h> // File API
#include <libloaderapi.h> // Library Loader API
#include <processthreadsapi.h> // Process & Threads API
#include <shellapi.h> // Shell API

/* Phase > Draw */
static void Draw(void);

/* Definition > ... */
inline void drawCircle(unsigned short const, unsigned short const, unsigned short const);
inline void drawLine(unsigned short const, unsigned short const, unsigned short const, unsigned short const);
inline void drawSpline(unsigned short const, unsigned short const, unsigned short const);

inline int getPixel(unsigned short const, unsigned short const);
inline void putPixel(unsigned short const, unsigned short const, DWORD const = 0x000000u);

/* Global > Window ... */
static WNDCLASSEX windowClassInformation = WNDCLASSEX();
static HBITMAP windowDeviceContextBitmapHandle = NULL;
static HDC windowDeviceContextHandle = NULL;
static HWND windowHandle = NULL;
static int windowHeight = 500, windowWidth = 500;
static BITMAP windowMemoryDeviceContextBitmap = BITMAP();
static VOID *windowMemoryDeviceContextBitmapBits = NULL;
static HBITMAP windowMemoryDeviceContextBitmapHandle = NULL;
static HDC windowMemoryDeviceContextHandle = NULL;
static LRESULT CALLBACK windowProcedure(HWND const windowHandle, UINT const message, WPARAM const messageParameter, LPARAM const messageSubparameter) {
    // Logic
    switch (message) {
        // [...]
        case WM_CLOSE: ::DestroyWindow(windowHandle); break;
        case WM_KEYDOWN: if (VK_ESCAPE == messageParameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSCOMMAND: if (SC_CLOSE == messageParameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSKEYDOWN: if (VK_F4 == messageParameter) ::DestroyWindow(windowHandle); break;

        // [Create]
        case WM_CREATE: {
            // Initialization > (Creation Parameter, Window ...)
            LPVOID const creationParameter = reinterpret_cast<CREATESTRUCTA const*>(messageSubparameter) -> lpCreateParams;

            int const windowAppearance = static_cast<int>(reinterpret_cast<intptr_t>(creationParameter));
            BITMAPINFO windowMemoryDeviceContextBitmapInformation = BITMAPINFO();

            // Update > Window ...
            windowDeviceContextHandle = ::GetDCEx(windowHandle, NULL, CS_OWNDC | DCX_NORESETATTRS);
            windowDeviceContextBitmapHandle = ::CreateCompatibleBitmap(windowDeviceContextHandle, windowWidth, windowHeight);
            windowMemoryDeviceContextHandle = ::CreateCompatibleDC(windowDeviceContextHandle);

            ::ZeroMemory(&windowMemoryDeviceContextBitmapInformation, sizeof(BITMAPINFO)); {
                windowMemoryDeviceContextBitmapInformation.bmiHeader.biBitCount = 32u;
                windowMemoryDeviceContextBitmapInformation.bmiHeader.biClrUsed = 0u;
                windowMemoryDeviceContextBitmapInformation.bmiHeader.biClrImportant = 0u;
                windowMemoryDeviceContextBitmapInformation.bmiHeader.biCompression = BI_RGB;
                windowMemoryDeviceContextBitmapInformation.bmiHeader.biHeight = windowHeight;
                windowMemoryDeviceContextBitmapInformation.bmiHeader.biPlanes = 1u;
                windowMemoryDeviceContextBitmapInformation.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
                windowMemoryDeviceContextBitmapInformation.bmiHeader.biWidth = windowWidth;
                windowMemoryDeviceContextBitmapInformation.bmiHeader.biXPelsPerMeter = ::GetDeviceCaps(windowDeviceContextHandle, HORZRES) / ::GetDeviceCaps(windowDeviceContextHandle, HORZSIZE);
                windowMemoryDeviceContextBitmapInformation.bmiHeader.biYPelsPerMeter = ::GetDeviceCaps(windowDeviceContextHandle, VERTRES) / ::GetDeviceCaps(windowDeviceContextHandle, VERTSIZE);
                windowMemoryDeviceContextBitmapInformation.bmiHeader.biSizeImage = windowMemoryDeviceContextBitmapInformation.bmiHeader.biHeight * windowMemoryDeviceContextBitmapInformation.bmiHeader.biWidth * (4u /* -> sizeof(UINT32) */);
            }

            windowMemoryDeviceContextBitmapHandle = ::CreateDIBSection(windowMemoryDeviceContextHandle, &windowMemoryDeviceContextBitmapInformation, DIB_RGB_COLORS, &windowMemoryDeviceContextBitmapBits, NULL, 0u);
            ::GetObject(windowMemoryDeviceContextBitmapHandle, sizeof(BITMAP), &windowMemoryDeviceContextBitmap);

            // ...
            ::SelectObject(windowDeviceContextHandle, windowDeviceContextBitmapHandle);
            ::SelectObject(windowMemoryDeviceContextHandle, windowMemoryDeviceContextBitmapHandle);
            ::SetBkMode(windowMemoryDeviceContextHandle, TRANSPARENT);

            ::ShowWindow(windowHandle, static_cast<long>(windowAppearance));
        } break;

        // [Destroy]
        case WM_DESTROY: {
            // ...
            ::DeleteDC(windowMemoryDeviceContextHandle);
            ::DeleteObject(windowMemoryDeviceContextBitmapHandle);
            ::ReleaseDC(windowHandle, windowDeviceContextHandle);

            // Deletion
            ::PostQuitMessage(EXIT_SUCCESS);
        } break;

        // [Paint]
        case WM_PAINT: {
            // ...
            Draw();

            ::BitBlt(windowDeviceContextHandle, 0, 0, windowWidth, windowHeight, windowMemoryDeviceContextHandle, 0, 0, SRCCOPY);
            ::ValidateRect(windowHandle, NULL);
        } return EXIT_SUCCESS;
    }

    // Return
    return ::DefWindowProc(windowHandle, message, messageParameter, messageSubparameter);
}

/* Function */
    // Draw Spline
    void drawCircle(unsigned short const xAnchor, unsigned short const yAnchor, unsigned short const radius) {
        // Initialization > (... Neighbor, X, Y)
        enum { east, north, northeast, northwest, south, southeast, southwest, west } currentNeighbor = northwest, recentNeighbor;
        int x = xAnchor + radius, y = yAnchor;

        // Loop --- NOTE (Lapys)
        do {
            // Initialization > (... Delta, Reversed)
            unsigned short const xDelta = x > xAnchor ? x - xAnchor : (xAnchor - x);
            unsigned short const yDelta = y > yAnchor ? y - yAnchor : (yAnchor - y);
            int const delta = (radius * radius) - ((xDelta * xDelta) + (yDelta * yDelta));

            bool reversed = false;

            // ... Update > Reversed -> Prevent the Current Neighbor infinitely reversing back onto itself.
            switch (currentNeighbor) {
                case east: reversed = recentNeighbor == northwest || recentNeighbor == southwest || recentNeighbor == west; break;
                case north: reversed = recentNeighbor == south || recentNeighbor == southeast || recentNeighbor == southwest; break;
                case northeast: reversed = recentNeighbor == south || recentNeighbor == southwest || recentNeighbor == west; break;
                case northwest: reversed = recentNeighbor == east || recentNeighbor == south || recentNeighbor == southeast; break;
                case south: reversed = recentNeighbor == north || recentNeighbor == northeast || recentNeighbor == northwest; break;
                case southeast: reversed = recentNeighbor == north || recentNeighbor == northwest || recentNeighbor == west; break;
                case southwest: reversed = recentNeighbor == east || recentNeighbor == north || recentNeighbor == northeast; break;
                case west: reversed = recentNeighbor == east || recentNeighbor == northeast || recentNeighbor == southeast; break;
            }

            // Logic > ...
            if (false == reversed && radius >= (delta < 0 ? -delta : delta)) {
                recentNeighbor = currentNeighbor;
                currentNeighbor = northwest;

                putPixel(x, y);
            }

            else switch (currentNeighbor) {
                // Update > ... Neighbor -> Assert next neighboring pixel, clock-wise.
                //                          Reset the translation from checking neighboring pixels.
                case east: --x; currentNeighbor = southeast; break;
                case north: ++y; currentNeighbor = northeast; break;
                case northeast: --x; ++y; currentNeighbor = east; break;
                case northwest: ++x; ++y; currentNeighbor = north; break;
                case south: --y; currentNeighbor = southwest; break;
                case southeast: --x; --y; currentNeighbor = south; break;
                case southwest: ++x; --y; currentNeighbor = west; break;
                case west: return; // -> Checked all neighboring pixels.
            }

            // Update > ... -> Check next neighboring pixel matches circle circumference.
            //                 This works because the circumference is continuous.
            switch (currentNeighbor) {
                case east: ++x; break;
                case north: --y; break;
                case northeast: ++x; --y; break;
                case northwest: --x; --y; break;
                case south: ++y; break;
                case southeast: ++x; ++y; break;
                case southwest: --x; ++y; break;
                case west: --x; break;
            }
        } while (false == (x == xAnchor + radius && y == yAnchor));
    }

    // Draw Line --- NOTE (Lapys)
    void drawLine(unsigned short const xOrigin, unsigned short const yOrigin, unsigned short const xTarget, unsigned short const yTarget) {
        // Initialization > (X ..., Y ...)
            // : ...
            int x = xOrigin;
            int y = yOrigin;

            // : Delta -> Distance between origin & targets.
            unsigned short const xDelta = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget; // -> Run
            unsigned short const yDelta = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget; // -> Rise

            // : Slope -> Determine iterative translation value from origin -- based on how much the X & Y axes are relatively displaced.
            float const xSlope = xDelta < yDelta ? static_cast<float>(xDelta) / static_cast<float>(yDelta) : 1.0f;
            float const ySlope = xDelta > yDelta ? static_cast<float>(yDelta) / static_cast<float>(xDelta) : 1.0f;

        // Loop > ... -> Sequentially translate from origin to target based on displacement ratios & relative quadrants.
        for (float xSlopeIterator = 0.0f, ySlopeIterator = 0.0f; false == (x == xTarget && y == yTarget); ) {
            putPixel(x, y);

            xSlopeIterator += xSlope;
            ySlopeIterator += ySlope;

            if (xSlopeIterator >= 1.0f) { xOrigin > xTarget ? --x : ++x; --xSlopeIterator; }
            if (ySlopeIterator >= 1.0f) { yOrigin > yTarget ? --y : ++y; --ySlopeIterator; }
        }
    }

    // Draw Spline
    // void drawSpline(unsigned short const x, unsigned short const y, unsigned short const point) {}

    // Get Pixel (Color) -> Whitish tone between ~50% - 100% intensity. (based on `x` & `y` coordinates)
    // Put Pixel -> (0 >= x <= windowMemoryDeviceContextBitmap.bmWidth) && (0 >= y <= windowMemoryDeviceContextBitmap.bmHeight)
    int getPixel(unsigned short const x, unsigned short const y) { int const intensity = static_cast<int>(127.0f + (255.0f - 127.0f) * ((1.0f * (static_cast<float>(x + y) / 2.0f)) / windowHeight)); return RGB(intensity, intensity, intensity); }
    void putPixel(unsigned short const x, unsigned short const y, DWORD const color) { static_cast<UINT32*>(windowMemoryDeviceContextBitmapBits)[x + ((windowMemoryDeviceContextBitmap.bmHeight - y - 1L) * windowMemoryDeviceContextBitmap.bmWidth)] = (0xFFu << 0x18u) | (0x000000u == color ? getPixel(x, y) : color); }

/* Phase > Draw --- NOTE (Lapys) -> Geometry Demonstration. */
void Draw(void) {
    // [Window Border]
    for (int x = windowWidth - 1; ~x; --x) putPixel(x, windowHeight - 1u); // -> Bottom.
    for (int y = windowHeight - 1; ~y; --y) putPixel(0u, y); // -> Left.
    for (int y = windowHeight - 1; ~y; --y) putPixel(windowWidth - 1u, y); // -> Right.
    for (int x = windowWidth - 1; ~x; --x) putPixel(x, 0u); // -> Top.

    // [Right-angled Lines] ...
    drawLine(windowWidth / 2u, windowHeight / 2u, windowWidth * (000.0f / 100.0f), windowHeight * (000.0f / 100.0f));
    drawLine(windowWidth / 2u, windowHeight / 2u, windowWidth * (000.0f / 100.0f), windowHeight * (050.0f / 100.0f));
    drawLine(windowWidth / 2u, windowHeight / 2u, windowWidth * (000.0f / 100.0f), windowHeight * (100.0f / 100.0f));

    drawLine(windowWidth / 2u, windowHeight / 2u, windowWidth * (050.0f / 100.0f), windowHeight * (000.0f / 100.0f));
    drawLine(windowWidth / 2u, windowHeight / 2u, windowWidth * (050.0f / 100.0f), windowHeight * (100.0f / 100.0f));

    drawLine(windowWidth / 2u, windowHeight / 2u, windowWidth * (100.0f / 100.0f), windowHeight * (000.0f / 100.0f));
    drawLine(windowWidth / 2u, windowHeight / 2u, windowWidth * (100.0f / 100.0f), windowHeight * (050.0f / 100.0f));
    drawLine(windowWidth / 2u, windowHeight / 2u, windowWidth * (100.0f / 100.0f), windowHeight * (100.0f / 100.0f));

    // [Circles] ...
    for (unsigned char radius = 0u; radius != 255u; radius += 17u)
    drawCircle(windowWidth / 2u, windowHeight / 2u, radius);

    // [Splines] ...
    // drawSpline(20u, 20u, 100u, 100u, 80u, 50u);
}

/* Main --- NOTE (Lapys) */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const previousInstanceHandle, LPSTR const /* commandLineArguments */, int const appearance) {
    // Initialization > (Exit Code, Instance ..., Lock Handle)
    int exitCode = EXIT_SUCCESS;
    bool instanceAlreadyRunning = false;
    CHAR instanceFileName[MAX_PATH] = {0};
    HANDLE lockHandle = NULL;

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
        windowClassInformation.hbrBackground = ::GetSysColorBrush(COLOR_WINDOWTEXT) /* --> ::GetSysColorBrush(COLOR_WINDOW) */;
        windowClassInformation.hCursor = static_cast<HCURSOR>(::LoadCursor(instanceHandle, IDC_ARROW)) /* --> static_cast<HCURSOR>(::LoadImage(instanceHandle, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)) */;
        windowClassInformation.hIcon = static_cast<HICON>(::ExtractIcon(instanceHandle, instanceFileName, 0u));
        windowClassInformation.hIconSm = static_cast<HICON>(NULL);
        windowClassInformation.hInstance = instanceHandle;
        windowClassInformation.lpfnWndProc = &windowProcedure;
        windowClassInformation.lpszClassName = "window";
        windowClassInformation.lpszMenuName = static_cast<LPCSTR>(NULL);
        windowClassInformation.style = CS_GLOBALCLASS | CS_OWNDC;

        // Logic > ...
        if (0x0 == ::RegisterClassEx(static_cast<WNDCLASSEX const*>(&windowClassInformation))) exitCode = EXIT_FAILURE;
        else {
            // Initialization > (Window Coordinates, Work Area Rectangle)
            SIZE windowCoordinates = SIZE();
            RECT workareaRectangle = RECT();

            // Update > (Work Area Rectangle, Window ...)
            ::SystemParametersInfo(SPI_GETWORKAREA, 0u, static_cast<PVOID>(&workareaRectangle), 0x0);

            windowWidth = (workareaRectangle.right - workareaRectangle.left) * (75.0f / 100.0f);
            windowHeight = (workareaRectangle.bottom - workareaRectangle.top) * (75.0f / 100.0f);
                windowHeight = windowWidth = (windowHeight < windowWidth ? windowHeight : windowWidth);
            windowCoordinates.cx = ((workareaRectangle.right - workareaRectangle.left) - windowWidth) / 2L;
            windowCoordinates.cy = ((workareaRectangle.bottom - workareaRectangle.top) - windowHeight) / 2L;

            // Update > Window Handle
            windowHandle = ::CreateWindowEx(0x0, windowClassInformation.lpszClassName, "Geometry Graphics Demonstration", WS_POPUP /* -> Remove borders & title bar. */, windowCoordinates.cx, windowCoordinates.cy, windowWidth, windowHeight, HWND_DESKTOP, static_cast<HMENU>(NULL), windowClassInformation.hInstance, reinterpret_cast<LPVOID>(static_cast<LPARAM>(appearance)));

            // Logic > ...
            if (NULL == windowHandle) exitCode = EXIT_FAILURE;
            else {
                // ...; Loop > Update ...
                MSG threadMessage = {};
                for (
                    BOOL threadMessageAvailable = FALSE; FALSE == threadMessageAvailable || WM_QUIT != threadMessage.message;
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
