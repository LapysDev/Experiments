/* Import */
#include <fcntl.h> // Functional
#include <stdlib.h> // Standard Library
#include <windows.h> // Windows

#include <iostream>

/* Global > Application ... */
HANDLE applicationConsoleActiveScreenBufferHandle = NULL;
char *applicationName = NULL;
int applicationStatus = 0;

/* Declaration > ... */
const BITMAP captureImage(void); // NOTE (Lapys) -> Renders display into an image format.
HBITMAP createImageMask(const HBITMAP, const COLORREF);
bool downloadImage(const BITMAP);
void drawImage(const char[], const HWND);
COLORREF getPixelColorFromImage(const char[], const unsigned, const unsigned);

/* Function */
    // Capture Image
    const BITMAP captureImage();

    // Create Image Mask --- NOTE (Lapys) -> Monochrome (two colors only) cast of a bitmap.
    HBITMAP createImageMask(const HBITMAP bitmapHandle, const COLORREF transparencyColor) {
        // Initialization > Bitmap (Mask) ...
        BITMAP bitmap;
        HDC bitmapGraphicsDeviceContext = ::CreateCompatibleDC(NULL);

        HDC bitmapMaskGraphicsDeviceContext = ::CreateCompatibleDC(NULL);
        HBITMAP bitmapMaskHandle;

        // Update > Bitmap (Mask) ...
        ::GetObject(bitmapHandle, sizeof(BITMAP), &bitmap);
        bitmapMaskHandle = ::CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, 1, 1, NULL);

        ::SelectObject(bitmapGraphicsDeviceContext, (HGDIOBJ) (HBITMAP) bitmapHandle);
        ::SelectObject(bitmapMaskGraphicsDeviceContext, (HGDIOBJ) (HBITMAP) bitmapMaskHandle);

        ::SetBkColor(bitmapGraphicsDeviceContext, transparencyColor);

        ::BitBlt(bitmapMaskGraphicsDeviceContext, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapGraphicsDeviceContext, 0, 0, SRCCOPY);
        ::BitBlt(bitmapGraphicsDeviceContext, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapMaskGraphicsDeviceContext, 0, 0, SRCINVERT);

        // Deletion
        ::DeleteDC(bitmapGraphicsDeviceContext);
        ::DeleteDC(bitmapMaskGraphicsDeviceContext);

        // Return
        return bitmapMaskHandle;
    }

    // Download Image
    bool downloadImage(const BITMAP bitmap);

    // Draw Image [From File]
    void drawImage(const char imageFilepath[], const HWND windowHandle) {
        // Initialization > Bitmap Handle
        HBITMAP bitmapHandle;

        // Update > Bitmap Handle
        bitmapHandle = (HBITMAP) ::LoadImage((HMODULE) ::GetWindowLong(windowHandle, GWL_HINSTANCE), imageFilepath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

        // Logic
        if (bitmapHandle == NULL)
            // Error
            ::WriteFile(applicationConsoleActiveScreenBufferHandle, "[ERROR]: Unable to retrieve specified image file\n\0\r", 51uL, NULL, NULL);

        else {
            // Initialization > (Bitmap ..., Graphics Device Context, Paint Information, ...)
            BITMAP bitmap;
            HDC bitmapGraphicsDeviceContext;
            HBITMAP bitmapMaskHandle = ::createImageMask(bitmapHandle, ::getPixelColorFromImage(imageFilepath, 0u, 0u));

            HDC graphicsDeviceContext;
            PAINTSTRUCT paintInformation;

            // Update > (Bitmap ..., Graphics Device Context)
            graphicsDeviceContext = ::BeginPaint(windowHandle, &paintInformation);

            bitmapGraphicsDeviceContext = ::CreateCompatibleDC(graphicsDeviceContext);
            ::GetObject(bitmapHandle, sizeof(BITMAP), &bitmap);

            // ...
            ::SelectObject(bitmapGraphicsDeviceContext, bitmapMaskHandle);
            ::BitBlt(graphicsDeviceContext, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapGraphicsDeviceContext, 0, 0, SRCAND);

            ::SelectObject(bitmapGraphicsDeviceContext, bitmapHandle);
            ::BitBlt(graphicsDeviceContext, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapGraphicsDeviceContext, 0, 0, SRCPAINT);

            // Deletion
            ::DeleteDC(bitmapGraphicsDeviceContext);
            ::DeleteObject(bitmapHandle);
            ::ReleaseDC(windowHandle, graphicsDeviceContext);
            ::EndPaint(windowHandle, &paintInformation);
        }
    }

    // Get Pixel Color From Image [File]
    COLORREF getPixelColorFromImage(const char imageFilepath[], const unsigned xIndex, const unsigned yIndex) {
        // Initialization > (Bitmap Handle, Color)
        HBITMAP bitmapHandle;
        COLORREF color;

        // Update > Bitmap Handle
        bitmapHandle = (HBITMAP) ::LoadImage(NULL, imageFilepath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

        // Logic
        if (bitmapHandle == NULL)
            // Error
            ::WriteFile(applicationConsoleActiveScreenBufferHandle, "[ERROR]: Unable to retrieve specified image file\n\0\r", 51uL, NULL, NULL);

        else {
            // Initialization > (Graphics Device Context, ...)
            HDC graphicsDeviceContext = ::CreateCompatibleDC(NULL);

            // Update > (Graphics Device Context, Color)
            ::SelectObject(graphicsDeviceContext, bitmapHandle);
            color = ::GetPixel(graphicsDeviceContext, xIndex, yIndex);

            // Deletion
            ::DeleteDC(graphicsDeviceContext);
            ::DeleteObject(bitmapHandle);
        }

        // Return
        return color;
    }

    /* Window Procedure */
    LRESULT CALLBACK windowProcedure(HWND windowHandle, UINT message, WPARAM messageParameter, LPARAM additionalMessageParameter) {
        // Logic
        switch (message) {
            // [Window Manager ...]
            case WM_CLOSE: ::DestroyWindow(windowHandle); break;
            case WM_CREATE: break;
            case WM_DESTROY: ::PostQuitMessage(0); break;
            case WM_PAINT: {
                // ...
                ::drawImage("image.masked.bmp", windowHandle);
            } break;

            // [...]
            default: return ::DefWindowProc(windowHandle, message, messageParameter, additionalMessageParameter);
        }

        // Return
        return 0;
    }

/* Main */
int WinMain(HINSTANCE handlerInstance, HINSTANCE /*previousHandlerInstance*/, LPSTR /*programInitiationCommandLine*/, int windowAppearance) {
    /* Update > Application ... */
    applicationConsoleActiveScreenBufferHandle = ::CreateFile("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, NULL);
    applicationName = (char*) "Image";
    applicationStatus = EXIT_SUCCESS; // NOTE (Lapys) -> No errors; Successful exit.

    // Declaration
        // Console Active Screen Buffer Handle
        const HANDLE consoleActiveScreenBufferHandle = applicationConsoleActiveScreenBufferHandle;

        // Window Class ...
        WNDCLASS windowClass {};
        const HINSTANCE& windowClassHandlerInstance = handlerInstance;
        const char windowClassName[] = "DEFAULT"; // WARN (Lapys) -> Must not be empty.

    // Update > (Console Active Screen Buffer Handle, ...)
    ::SetConsoleActiveScreenBuffer(consoleActiveScreenBufferHandle);
    ::SetConsoleTitle(applicationName);

    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);

    // Deletion
    ::ZeroMemory(&windowClass, sizeof(windowClass));

    // Modification > Window Class > ...
    windowClass.cbClsExtra = 0; // NOTE (Lapys) -> Extra bytes to allocate following the window class structure.
    windowClass.cbWndExtra = 0; // NOTE (Lapys) -> Extra bytes to allocate following the window instance.
    windowClass.hbrBackground = (HBRUSH) COLOR_WINDOW; // NOTE (Lapys) -> Window background color.
    windowClass.hCursor = (HCURSOR) ::LoadCursor(NULL, IDC_ARROW); // NOTE (Lapys) -> Window cursor.
    windowClass.hIcon = NULL; // NOTE (Lapys) -> Window favorite icon.
    windowClass.hInstance = windowClassHandlerInstance;
    windowClass.lpszClassName = windowClassName;
    windowClass.lpszMenuName = NULL; // NOTE (Lapys) -> Resource name of the window class menu.
    windowClass.lpfnWndProc = &windowProcedure; // NOTE (Lapys) -> Event loop or Message queue.
    windowClass.style = CS_HREDRAW | CS_VREDRAW; // NOTE (Lapys) -> Pre-defined look of window instances of the class.

    // [Initiate]
    {
        // [Begin] ...
        ::WriteFile(consoleActiveScreenBufferHandle, "[PROGRAM INITIATED]\n\r", 21uL, NULL, NULL);

        // Logic
        if (::RegisterClass(&windowClass)) {
            // Constant > Window Handle
            const HWND windowHandle = ::CreateWindowEx(0, windowClassName, applicationName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, handlerInstance, NULL);

            // Logic
            if (windowHandle) {
                // Initialization > Window Procedure Message
                MSG windowProcedureMessage {};

                // Update > Window Handle
                ::ShowWindow(windowHandle, windowAppearance);
                ::UpdateWindow(windowHandle);

                // Loop > Logic
                while (true)
                if (::GetMessage(&windowProcedureMessage, NULL, 0, 0)) {
                    // Logic > ...
                    if (windowProcedureMessage.message == WM_QUIT) break;
                    else {
                        // Update > Window Procedure Message
                        ::TranslateMessage(&windowProcedureMessage);
                        ::DispatchMessage(&windowProcedureMessage);
                    }
                } else break;

                // Update > Application Status
                applicationStatus = windowProcedureMessage.wParam;
            } else { applicationStatus = EXIT_FAILURE; }

            // Deletion
            ::UnregisterClass(windowClassName, windowClassHandlerInstance);
        } else { applicationStatus = EXIT_FAILURE; }

        // [End] ...
        ::WriteFile(consoleActiveScreenBufferHandle, "[PROGRAM TERMINATED]\0", 21uL, NULL, NULL);
    }

    // [Terminate]
    {
        // Deletion
        ::CloseHandle(applicationConsoleActiveScreenBufferHandle);
    }

    // Return
    return applicationStatus;
}
