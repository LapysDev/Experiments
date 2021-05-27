/* Import --> gdi32.dll, kernel32.dll, shell32.dll, user32.dll */
#include <stdint.h> // Standard Integer
#include <cstdio>
#include <cstdlib> // C Standard Library

#include <windef.h> // Windows Definitions
#include <winbase.h> // Window Base
#include <wincon.h> // Windows Console
#include <wingdi.h> // Windows Graphics Device Interface
#include <winnt.h> // Windows New Technologies
#include <winuser.h> // Windows User
#   include <basetsd.h> // Base Type Definitions
#   include <fileapi.h> // File API
#   include <libloaderapi.h> // Library Loader API
#   include <processthreadsapi.h> // Process Threads API
#   include <shellapi.h> // Shell API
#   include <windowsx.h> // Windows Extensions API

/* Definitions > ... */
#ifdef _WIN32_WINNT
#   if _WIN32_WINNT < 0x0500
#       undef _WIN32_WINNT
#       define _WIN32_WINNT 0x0500
#   endif
#endif

static void Initiate(void);
static void Update(void);

inline void putPixel(unsigned short const, unsigned short const, DWORD const = 0x000000u);

/* Global */
// : Console
static HWND consoleWindowHandle = NULL;

// : Game
static bool gameEnded = false;

// : Pointer
static POINTS pointerCoordinates = POINTS();
static bool pointerIsPressed = false;

// : Tiles
static struct Tile {
    bool isCrossed, isKnotted;
    bool isMatched;

    Tile(void) : isCrossed(false), isKnotted(false) {}
} *activeTile = NULL, tiles[9] = {};
static DWORD tileBevelColor = 0x000000u;
static unsigned char tileBevelSize = 0u;
static DWORD tileColor = 0x000000u;
static unsigned char tileMargin = 0u;
static DWORD tileMatchColor = 0x000000u;
static DWORD tileOutlineColor = 0x000000u;
static unsigned short tileSize = 0u;

// : Window
static WNDCLASSEX windowClassInformation = WNDCLASSEX();
static HBITMAP windowDeviceContextBitmapHandle = NULL;
static HDC windowDeviceContextHandle = NULL;
static HWND windowHandle = NULL;
static int windowHeight = 0, windowWidth = 0;
static BITMAP windowMemoryDeviceContextBitmap = BITMAP();
static VOID *windowMemoryDeviceContextBitmapBits = NULL;
static HBITMAP windowMemoryDeviceContextBitmapHandle = NULL;
static HDC windowMemoryDeviceContextHandle = NULL;
static LRESULT CALLBACK windowProcedure(HWND const windowHandle, UINT const message, WPARAM const messageParameter, LPARAM const messageSubparameter) {
    switch (message) {
        /* ... */
        case WM_CLOSE: ::DestroyWindow(windowHandle); break;
        case WM_KEYDOWN: if (VK_ESCAPE == messageParameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSCOMMAND: if (SC_CLOSE == messageParameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSKEYDOWN: if (VK_F4 == messageParameter) ::DestroyWindow(windowHandle); break;

        /* ... */
        case WM_LBUTTONDOWN: {
            pointerIsPressed = true;
            ::RedrawWindow(windowHandle, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE);
        } return EXIT_SUCCESS;

        case WM_LBUTTONUP: {
            pointerIsPressed = false;
            ::RedrawWindow(windowHandle, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE);
        } return EXIT_SUCCESS;

        case WM_MOUSEMOVE: {
            if (false == pointerIsPressed) {
                pointerCoordinates.x = GET_X_LPARAM(messageSubparameter);
                pointerCoordinates.y = GET_Y_LPARAM(messageSubparameter);
            }

            ::RedrawWindow(windowHandle, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE);
        } return EXIT_SUCCESS;

        #ifdef WM_TOUCH
        case WM_TOUCH: {
            POINT touchCoordinates = POINT();
            TOUCHINPUT touchInput = TOUCHINPUT();

            ::GetTouchInputInfo(reinterpret_cast<HTOUCHINPUT>(messageSubparameter), 1u, &touchInput, sizeof(TOUCHINPUT));
            ::CloseTouchInputHandle(reinterpret_cast<HTOUCHINPUT>(messageSubparameter));

            if (false == pointerIsPressed) {
                touchCoordinates.x = TOUCH_COORD_TO_PIXEL(touchInput.x);
                touchCoordinates.y = TOUCH_COORD_TO_PIXEL(touchInput.y);
                ::ScreenToClient(windowHandle, &touchCoordinates);

                pointerIsPressed = true;
                pointerCoordinates.x = touchCoordinates.x;
                pointerCoordinates.y = touchCoordinates.y;

                ::RedrawWindow(windowHandle, NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE);
            }
        } return EXIT_SUCCESS;
        #endif

        /* ... */
        case WM_CREATE: {
            LPVOID const creationParameter = reinterpret_cast<CREATESTRUCTA const*>(messageSubparameter) -> lpCreateParams;

            int const windowAppearance = static_cast<int>(reinterpret_cast<intptr_t>(creationParameter));
            BITMAPINFO windowMemoryDeviceContextBitmapInformation = BITMAPINFO();

            // ...
            consoleWindowHandle = ::GetConsoleWindow();

            windowDeviceContextHandle = ::GetDCEx(windowHandle, NULL, CS_OWNDC | DCX_NORESETATTRS);
            windowDeviceContextBitmapHandle = ::CreateCompatibleBitmap(windowDeviceContextHandle, windowWidth, windowHeight);

            windowMemoryDeviceContextBitmapInformation.bmiColors -> rgbBlue = 0u;
            windowMemoryDeviceContextBitmapInformation.bmiColors -> rgbGreen = 0u;
            windowMemoryDeviceContextBitmapInformation.bmiColors -> rgbRed = 0u;
            windowMemoryDeviceContextBitmapInformation.bmiColors -> rgbReserved = 0x0u;
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

            windowMemoryDeviceContextHandle = ::CreateCompatibleDC(windowDeviceContextHandle);
            windowMemoryDeviceContextBitmapHandle = ::CreateDIBSection(windowMemoryDeviceContextHandle, &windowMemoryDeviceContextBitmapInformation, DIB_RGB_COLORS, &windowMemoryDeviceContextBitmapBits, NULL, 0u);

            // ...
            ::GetObject(windowMemoryDeviceContextBitmapHandle, sizeof(BITMAP), &windowMemoryDeviceContextBitmap);
            ::SelectObject(windowDeviceContextHandle, windowDeviceContextBitmapHandle);
            ::SelectObject(windowMemoryDeviceContextHandle, windowMemoryDeviceContextBitmapHandle);

            // ...
            #ifdef WM_TOUCH
                if (0 != ::GetSystemMetrics(0x5E /*SM_DIGITIZER*/))
                ::RegisterTouchWindow(windowHandle, 0x0);
            #endif

            if (NULL != consoleWindowHandle) ::ShowWindow(consoleWindowHandle, SW_HIDE);
            ::ShowWindow(windowHandle, static_cast<long>(windowAppearance));

            /* ... */
            Initiate();
        } break;

        // ...
        case WM_DESTROY: {
            ::DeleteDC(windowMemoryDeviceContextHandle), ::DeleteObject(windowMemoryDeviceContextBitmapHandle);
            ::ReleaseDC(windowHandle, windowDeviceContextHandle);

            ::PostQuitMessage(EXIT_SUCCESS);
        } break;

        // ...
        case WM_PAINT: {
            /* ... */
            Update();

            // ...
            ::BitBlt(windowDeviceContextHandle, 0, 0, windowWidth, windowHeight, windowMemoryDeviceContextHandle, 0, 0, SRCCOPY);
            ::ValidateRect(windowHandle, NULL);
        } return EXIT_SUCCESS;
    }

    // ...
    return ::DefWindowProc(windowHandle, message, messageParameter, messageSubparameter);
}

/* Phase */
// : Initiate
void Initiate(void) {
    int const windowMinimumSize = windowHeight < windowWidth ? windowHeight : windowWidth;

    tileSize = ((windowMinimumSize / /* ->> column/ row count */ 3) * 3u) / 4u;
    tileOutlineColor = 0xA0A0A0u;
    tileMatchColor = 0x6FFF6Fu;
    tileMargin = 5u;
    tileColor = 0xF0F0F0u;
    tileBevelSize = (tileSize * 1u) / 20u;
    tileBevelColor = 0xC0C0C0u;
}

// : Update
void Update(void) {
    if (false == gameEnded) {
        unsigned short const tileBeveledSize = tileSize - tileBevelSize;
        unsigned short const tilesSize = ((tileMargin * (3u - 1u)) + (tileSize * 3u));

        unsigned short const horizontalOffset = (windowWidth - tilesSize) / 2u;
        unsigned short const verticalOffset = (windowHeight - tilesSize) / 2u;

        // ... ->> State
        #if true
            for (
                int const combinations[] = {
                    0, 1, 2,
                    0, 3, 6,
                    0, 4, 8,
                    1, 4, 7,
                    2, 4, 6,
                    2, 5, 8,
                    3, 4, 5,
                    6, 7, 8
                }, *iterator = combinations + ((sizeof(combinations) / sizeof(int)) - 3);
                combinations <= iterator; iterator -= 3
            ) if (
                3 == (tiles[iterator[0]].isCrossed + tiles[iterator[1]].isCrossed + tiles[iterator[2]].isCrossed) ||
                3 == (tiles[iterator[0]].isKnotted + tiles[iterator[1]].isKnotted + tiles[iterator[2]].isKnotted)
            ) {
                gameEnded = true;

                tiles[iterator[0]].isMatched = true;
                tiles[iterator[1]].isMatched = true;
                tiles[iterator[2]].isMatched = true;
            }
        #else
            bool horizontalMatch = false, verticalMatch = false;
            bool leadingDiagonalMatch = false, trailingDiagonalMatch = false;

            {
                // ... ->> horizontal
                if (false == (horizontalMatch || leadingDiagonalMatch || trailingDiagonalMatch || verticalMatch))
                for (unsigned char row = 3u; row--; ) {
                    horizontalMatch = true;

                    for (unsigned char column = 3u; --column && horizontalMatch; )
                    horizontalMatch = (
                        2 == tiles[column + (row * 3u)].isCrossed + tiles[(column - 1u) + (row * 3u)].isCrossed ||
                        2 == tiles[column + (row * 3u)].isKnotted + tiles[(column - 1u) + (row * 3u)].isKnotted
                    );

                    if (horizontalMatch) {
                        for (unsigned char column = 3u; column--; ) tiles[column + (row * 3u)].isMatched = true;
                        gameEnded = true; break;
                    }
                }

                // ... ->> leading diagonal
                if (false == (horizontalMatch || leadingDiagonalMatch || trailingDiagonalMatch || verticalMatch)) {
                    leadingDiagonalMatch = true;

                    for (unsigned char column = 3u, row = 3u; leadingDiagonalMatch && (--column && --row); )
                    leadingDiagonalMatch = (
                        2 == tiles[column + (row * 3u)].isCrossed + tiles[(column - 1u) + ((row - 1u) * 3u)].isCrossed ||
                        2 == tiles[column + (row * 3u)].isKnotted + tiles[(column - 1u) + ((row - 1u) * 3u)].isKnotted
                    );

                    if (leadingDiagonalMatch) {
                        gameEnded = true;

                        for (unsigned char column = 3u, row = 3u; column-- && row--; )
                        tiles[column + (row * 3u)].isMatched = true;
                    }
                }

                // ... ->> trailing diagonal
                if (false == (horizontalMatch || leadingDiagonalMatch || trailingDiagonalMatch || verticalMatch)) {
                    trailingDiagonalMatch = true;

                    for (unsigned char column = 0u, row = 3u; trailingDiagonalMatch && --row; ++column)
                    trailingDiagonalMatch = (
                        2 == tiles[column + (row * 3u)].isCrossed + tiles[(column + 1u) + ((row - 1u) * 3u)].isCrossed ||
                        2 == tiles[column + (row * 3u)].isKnotted + tiles[(column + 1u) + ((row - 1u) * 3u)].isKnotted
                    );

                    if (trailingDiagonalMatch) {
                        gameEnded = true;

                        for (unsigned char column = 0u, row = 3u; row--; ++column)
                        tiles[column + (row * 3u)].isMatched = true;
                    }
                }

                // ... ->> vertical
                if (false == (horizontalMatch || leadingDiagonalMatch || trailingDiagonalMatch || verticalMatch))
                for (unsigned char column = 3u; column--; ) {
                    verticalMatch = true;

                    for (unsigned char row = 3u; --row && verticalMatch; )
                    verticalMatch = (
                        2 == tiles[column + (row * 3u)].isCrossed + tiles[column + ((row - 1u) * 3u)].isCrossed ||
                        2 == tiles[column + (row * 3u)].isKnotted + tiles[column + ((row - 1u) * 3u)].isKnotted
                    );

                    if (verticalMatch) {
                        for (unsigned char row = 3u; row--; ) tiles[column + (row * 3u)].isMatched = true;
                        gameEnded = true; break;
                    }
                }
            }
        #endif

        // ... ->> Rendering
        for (unsigned short x = tilesSize + tileMargin; x--; )
        for (unsigned short y = tilesSize + tileMargin; y--; ) {
            putPixel((horizontalOffset + x) - (tileMargin / 2u), (verticalOffset + y) - (tileMargin / 2u), 0x333333u);
        }

        for (unsigned char iterator = sizeof(tiles) / sizeof(*tiles); iterator--; ) {
            unsigned short const left = horizontalOffset + ((iterator % /* ->> column/ row count */ 3u) * (tileSize + (iterator ? tileMargin : 0u)));
            unsigned short top = verticalOffset + ((iterator / /* ->> column/ row count */ 3u) * (tileSize + (iterator ? tileMargin : 0u)));

            // ... ->> player tile select
            if (
                (left < pointerCoordinates.x && pointerCoordinates.x < (left + tileSize)) &&
                (top < pointerCoordinates.y && pointerCoordinates.y < (top + tileSize))
            ) {
                if (false == pointerIsPressed) top -= tileMargin / 2u;
                else {
                    if (NULL == activeTile) (tiles + iterator) -> isCrossed = true;
                    else if (activeTile != tiles + iterator) {
                        if (activeTile -> isCrossed) (tiles + iterator) -> isKnotted = true;
                        if (activeTile -> isKnotted) (tiles + iterator) -> isCrossed = true;
                    }

                    activeTile = tiles + iterator;
                }
            }

            // ... ->> base fill
            for (unsigned short x = tileSize; x--; )
            for (unsigned short y = tileSize; y--; ) {
                putPixel(left + x, top + y, (
                    (x > tileBeveledSize && y >= tileBevelSize) || // ->> edge (right)
                    ((x > tileBeveledSize && y < tileBevelSize) && (x - tileBeveledSize >= tileBevelSize - y)) || // ->> corner

                    (x >= tileBevelSize && y > tileBeveledSize) || // ->> edge (bottom)
                    ((y > tileBeveledSize && x < tileBevelSize) && (y - tileBeveledSize >= tileBevelSize - x)) // ->> corner
                ) ? tileBevelColor : ((tiles + iterator) -> isMatched ? tileMatchColor : tileColor));
            }

            // ... ->> bevel outline
            for (unsigned short x = tileBevelSize; tileBeveledSize != x; ++x) {
                putPixel(left + x, top + tileBevelSize, tileOutlineColor);
                putPixel(left + x, top + tileBeveledSize, tileOutlineColor);
            }

            for (unsigned short y = tileBevelSize; tileBeveledSize != y; ++y) {
                putPixel(left + tileBevelSize, top + y, tileOutlineColor);
                putPixel(left + tileBeveledSize, top + y, tileOutlineColor);
            }

            /* ... */
            if ((tiles + iterator) -> isCrossed) {
                unsigned char const crossThickness = 10u;
                unsigned char const crossSize = (tileBeveledSize * 3u) / 5u;
                unsigned char const crossOffset = (tileBeveledSize - crossSize) / 2u;
                DWORD const crossColor = 0x0060FFu;

                // ...
                for (unsigned short x = crossSize, y = crossSize; x-- && y--; )
                for (short thickness = -(static_cast<short>(crossThickness) / 2); thickness != (crossThickness / 2u); ++thickness) {
                    putPixel(crossOffset + left + x, static_cast<short>(crossOffset + top + y) + thickness, crossColor);
                    putPixel(crossOffset + left + (crossSize - x), static_cast<short>(crossOffset + top + y) + thickness, crossColor);
                }
            }

            if ((tiles + iterator) -> isKnotted) {
                unsigned char const knotCenter = tileSize / 2;
                DWORD const knotColor = 0xFF300Fu;
                unsigned char const knotRadius = ((tileBeveledSize * 3u) / 5u) / /* ->> because radius */ 2u;
                unsigned char const knotThickness = 10u;

                // ...
                for (unsigned short x = tileSize; x--; )
                for (unsigned short y = tileSize; y--; ) {
                    unsigned short const xDelta = x > knotCenter ? x - knotCenter : (knotCenter - x);
                    unsigned short const yDelta = y > knotCenter ? y - knotCenter : (knotCenter - y);
                    int const delta = (knotRadius * knotRadius) - ((xDelta * xDelta) + (yDelta * yDelta));

                    // ...
                    if ((knotRadius * knotThickness) > (delta < 0 ? -delta : delta))
                    putPixel(left + x, top + y, knotColor);
                }
            }
        }
    }

        // tiles[iterator][iterator]
        // tiles[3 - iterator - 1][iterator]
}

/* Function */
// : Put Pixel
void putPixel(unsigned short const x, unsigned short const y, DWORD const color) { static_cast<UINT32*>(windowMemoryDeviceContextBitmapBits)[x + (windowMemoryDeviceContextBitmap.bmWidth * (windowMemoryDeviceContextBitmap.bmHeight - y - 1L))] = color | (0xFFu << 0x18u); }

/* Main */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const previousInstanceHandle, LPSTR const /* commandLineArguments */, int const appearance) {
    int exitCode = EXIT_SUCCESS;
    bool instanceAlreadyRunning = false;

    // ...
    if (NULL != previousInstanceHandle) instanceAlreadyRunning = true;
    else {
        HANDLE lockHandle = NULL;

        // ...
        do {
            CHAR lockFileName[MAX_PATH] = {};
            CHAR lockFilePath[MAX_PATH + 1u] = {};

            // ...
            if (0u != ::GetTempPath(MAX_PATH + 1u, lockFilePath))
            if (0u != ::GetTempFileName(lockFilePath, "", 0000u, lockFileName)) {
                lockHandle = ::CreateFile(lockFileName, GENERIC_READ, 0u, NULL, CREATE_NEW, FILE_FLAG_DELETE_ON_CLOSE, NULL);
                if (INVALID_HANDLE_VALUE != lockHandle) {
                    instanceAlreadyRunning = ERROR_FILE_EXISTS == ::GetLastError();
                    if (false == instanceAlreadyRunning) break;
                }
            }

            // ...
            lockHandle = ::CreateMutex(NULL, TRUE, "previous_instance_assertion");
            if (NULL != lockHandle) {
                instanceAlreadyRunning = ERROR_ALREADY_EXISTS == ::GetLastError();
                if (false == instanceAlreadyRunning) break;
            }
        } while (false);

        // ...
        if (
            NULL != lockHandle &&
            INVALID_HANDLE_VALUE != lockHandle
        ) ::CloseHandle(lockHandle);
    }

    // ...
    if (instanceAlreadyRunning) exitCode = EXIT_FAILURE;
    else {
        CHAR instanceFileName[MAX_PATH] = {0};
        ::GetModuleFileName(NULL, instanceFileName, MAX_PATH);

        // ...
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

        // ...
        if (0x0 == ::RegisterClassEx(static_cast<WNDCLASSEX const*>(&windowClassInformation))) exitCode = EXIT_FAILURE;
        else {
            SIZE windowCoordinates = SIZE();
            RECT workareaRectangle = RECT();

            ::SystemParametersInfo(SPI_GETWORKAREA, 0u, static_cast<PVOID>(&workareaRectangle), 0x0);

            // ...
            windowWidth = ((workareaRectangle.right - workareaRectangle.left) * 3) / 4;
            windowHeight = ((workareaRectangle.bottom - workareaRectangle.top) * 3) / 4;

            windowCoordinates.cx = ((workareaRectangle.right - workareaRectangle.left) - windowWidth) / 2L;
            windowCoordinates.cy = ((workareaRectangle.bottom - workareaRectangle.top) - windowHeight) / 2L;

            windowHandle = ::CreateWindowEx(0x0, windowClassInformation.lpszClassName, "Tic-Tac-Toe", WS_POPUP, windowCoordinates.cx, windowCoordinates.cy, windowWidth, windowHeight, HWND_DESKTOP, static_cast<HMENU>(NULL), windowClassInformation.hInstance, reinterpret_cast<LPVOID>(static_cast<LPARAM>(appearance)));

            // ...
            if (NULL == windowHandle) exitCode = EXIT_FAILURE;
            else {
                MSG threadMessage = MSG();
                BOOL threadMessageAvailable = TRUE;

                while (FALSE == threadMessageAvailable || WM_QUIT != threadMessage.message) {
                    ::DispatchMessage(&threadMessage);
                    threadMessageAvailable = ::PeekMessage(&threadMessage, NULL, 0x0, 0x0, PM_REMOVE);
                }

                exitCode = threadMessage.wParam;
            }

            ::UnregisterClass(windowClassInformation.lpszClassName, windowClassInformation.hInstance);
        }

        ::DestroyCursor(windowClassInformation.hCursor);
    }

    // ...
    return exitCode;
}
