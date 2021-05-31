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
#undef UNICODE

static void Draw(void);

inline void drawBMP(char const[]);
inline void drawExif(char const[]);
inline void drawGIF(char const[]);
inline void drawHEIF(char const[]);
inline void drawJFIF(char const[]);
inline void drawJPEG(char const[]);
inline void drawNetPBM(char const[]);
inline void drawPNG(char const[]);
inline void drawSVG(char const[]);
inline void drawTIFF(char const[]);
inline void drawWebP(char const[]);
inline void saveAsBMP(char const[]);
inline void saveAsExif(char const[]);
inline void saveAsGIF(char const[]);
inline void saveAsHEIF(char const[]);
inline void saveAsJFIF(char const[]);
inline void saveAsJPEG(char const[]);
inline void saveAsNetPBM(char const[]);
inline void saveAsPNG(char const[]);
inline void saveAsSVG(char const[]);
inline void saveAsTIFF(char const[]);
inline void saveAsWebP(char const[]);
inline void putPixel(unsigned short const, unsigned short const, DWORD const = 0x000000u);

/* Global */
// : Console
static HWND consoleWindowHandle = NULL;

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

            // if (NULL != consoleWindowHandle) ::ShowWindow(consoleWindowHandle, SW_HIDE);
            ::ShowWindow(windowHandle, static_cast<long>(windowAppearance));
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
            Draw();

            // ...
            ::BitBlt(windowDeviceContextHandle, 0, 0, windowWidth, windowHeight, windowMemoryDeviceContextHandle, 0, 0, SRCCOPY);
            ::ValidateRect(windowHandle, NULL);
        } return EXIT_SUCCESS;
    }

    // ...
    return ::DefWindowProc(windowHandle, message, messageParameter, messageSubparameter);
}

/* Phase > Draw */
void Draw(void) {
    // drawBMP("image.bmp");
    // drawBMP("image.bmz");
    // drawBMP("image.dib");
}

/* Function */
// : Draw Bitmap
void drawBMP(char const fileName[]) {
    HBITMAP const bitmapHandle = static_cast<HBITMAP>(::LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTCOLOR | LR_LOADFROMFILE));

    if (NULL == bitmapHandle) {
        /* CHECK IF BMZ = COMPRESSED BMP */
        /* Read as bitmap */
    }

    else {
        BITMAP bitmap;
        VOID *bitmapBits;
        HDC const bitmapDeviceContextHandle = ::CreateCompatibleDC(windowDeviceContextHandle);
        BITMAPINFO bitmapInformation;

        // ...
        ::SelectObject(bitmapDeviceContextHandle, bitmapHandle);
        ::GetObject(bitmapHandle, sizeof(BITMAP), &bitmap);

        // ...
        bitmapInformation.bmiColors -> rgbBlue = 0u;
        bitmapInformation.bmiColors -> rgbGreen = 0u;
        bitmapInformation.bmiColors -> rgbRed = 0u;
        bitmapInformation.bmiColors -> rgbReserved = 0x0u;
        bitmapInformation.bmiHeader.biBitCount = 32u;
        bitmapInformation.bmiHeader.biClrUsed = 0u;
        bitmapInformation.bmiHeader.biClrImportant = 0u;
        bitmapInformation.bmiHeader.biCompression = BI_RGB;
        bitmapInformation.bmiHeader.biHeight = bitmap.bmHeight;
        bitmapInformation.bmiHeader.biPlanes = bitmap.bmPlanes;
        bitmapInformation.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bitmapInformation.bmiHeader.biWidth = bitmap.bmWidth;
        bitmapInformation.bmiHeader.biXPelsPerMeter = ::GetDeviceCaps(windowDeviceContextHandle, HORZRES) / ::GetDeviceCaps(windowDeviceContextHandle, HORZSIZE);
        bitmapInformation.bmiHeader.biYPelsPerMeter = ::GetDeviceCaps(windowDeviceContextHandle, VERTRES) / ::GetDeviceCaps(windowDeviceContextHandle, VERTSIZE);
        bitmapInformation.bmiHeader.biSizeImage = bitmapInformation.bmiHeader.biHeight * bitmapInformation.bmiHeader.biWidth * (4u /* -> sizeof(UINT32) */);

        bitmapBits = static_cast<VOID*>(std::malloc(bitmapInformation.bmiHeader.biSizeImage * sizeof(BYTE)));

        // ...
        if (0 != ::GetDIBits(bitmapDeviceContextHandle, bitmapHandle, 0u, bitmap.bmHeight, bitmapBits, &bitmapInformation, DIB_RGB_COLORS)) {
            unsigned short const horizontalOffset = (windowWidth - bitmap.bmWidth) / 2u;
            unsigned short const verticalOffset = (windowHeight - bitmap.bmHeight) / 2u;

            for (unsigned short x = bitmap.bmWidth; x--; )
            for (unsigned short y = bitmap.bmHeight; y--; ) {
                putPixel(horizontalOffset + x, verticalOffset + y, static_cast<UINT32*>(bitmapBits)[x + (bitmap.bmWidth * (bitmap.bmHeight - y - 1L))]);
            }
        }

        // ...
        std::free(bitmapBits);
        ::DeleteObject(bitmapDeviceContextHandle);
        ::DeleteObject(bitmapHandle);
    }
}

// : Draw Exchangeable Image File Format
void drawExif(char const[]) {}

// : Draw Graphics Interchange Format
void drawGIF(char const[]) {}

// : Draw High Efficiency Image File Format
void drawHEIF(char const[]) {}

// : Draw Joint Photographic Experts Group File Interchange Format
void drawJFIF(char const[]) {}

// : Draw Joint Photographic Experts Group
void drawJPEG(char const[]) {}

// : Draw Net Portable Bitmap Format
void drawNetPBM(char const[]) {}

// : Draw Portable Network Graphics
void drawPNG(char const[]) {}

// : Draw Standard Vector Graphics
void drawSVG(char const[]) {}

// : Draw Tagged Image File Format
void drawTIFF(char const[]) {}

// : Draw Web Picture
void drawWebP(char const[]) {}

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

            windowHandle = ::CreateWindowEx(0x0, windowClassInformation.lpszClassName, "Image", WS_POPUP, windowCoordinates.cx, windowCoordinates.cy, windowWidth, windowHeight, HWND_DESKTOP, static_cast<HMENU>(NULL), windowClassInformation.hInstance, reinterpret_cast<LPVOID>(static_cast<LPARAM>(appearance)));

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
