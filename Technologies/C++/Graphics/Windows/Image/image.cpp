/* Import */
#include <iostream>
#include <stdlib.h> // Standard Library
#include <windows.h> // Windows

/* Definition */
#ifndef EXIT_FAILURE
#define EXIT_FAILURE -1
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef NULL
#define NULL 0x0
#endif

/* Namespace > Image */
namespace Image {
    /* Function */
        // Create Bitmap From Display
        HBITMAP createBitmapFromDisplay() {
            // Initialization > (Bitmap, Display) ...
            HDC bitmapGraphicsDeviceContext;
            HGDIOBJ bitmapDummyObject;
            HBITMAP bitmapHandle;

            HDC displayGraphicsDeviceContext;
            int displayHeight, displayWidth;

            // Update > (Display, Bitmap) ...
            displayGraphicsDeviceContext = ::GetDC(NULL);
            displayHeight = ::GetSystemMetrics(SM_CYVIRTUALSCREEN);
            displayWidth = ::GetSystemMetrics(SM_CXVIRTUALSCREEN);

            bitmapGraphicsDeviceContext = ::CreateCompatibleDC(displayGraphicsDeviceContext);
            bitmapHandle = ::CreateCompatibleBitmap( displayGraphicsDeviceContext, displayWidth, displayHeight);

            // Update > ... Graphics Device Context
            bitmapDummyObject = ::SelectObject(bitmapGraphicsDeviceContext, bitmapHandle);
            ::BitBlt(bitmapGraphicsDeviceContext, 0,0, displayWidth, displayHeight, displayGraphicsDeviceContext, 0, 0, SRCCOPY);
            bitmapHandle = (HBITMAP) ::SelectObject(bitmapGraphicsDeviceContext, bitmapDummyObject);

            // Deletion
            ::ReleaseDC(NULL, displayGraphicsDeviceContext);
            ::DeleteDC(bitmapGraphicsDeviceContext);

            // Return
            return bitmapHandle;
        }

        // Create Bitmap Mask [From Color]
        HBITMAP createBitmapMask(HBITMAP bitmapHandle, const COLORREF transparencyColor) {
            // Evaluation > Bitmap Mask Handle
            HBITMAP bitmapMaskHandle;

            // Initialization > Bitmap (Mask) ...
            BITMAP bitmap;
            HGDIOBJ bitmapDummyObject;
            HDC bitmapGraphicsDeviceContext = ::CreateCompatibleDC(NULL);

            HGDIOBJ bitmapMaskDummyObject;
            HDC bitmapMaskGraphicsDeviceContext = ::CreateCompatibleDC(NULL);

            // Update > Bitmap (Mask Handle)
            ::GetObject(bitmapHandle, sizeof(BITMAP), &bitmap);
            bitmapMaskHandle = ::CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, 1, 1, NULL);

            // Update > ... Graphics Device Context
            bitmapDummyObject = ::SelectObject(bitmapGraphicsDeviceContext, (HGDIOBJ) (HBITMAP) bitmapHandle);
            bitmapMaskDummyObject = ::SelectObject(bitmapMaskGraphicsDeviceContext, (HGDIOBJ) (HBITMAP) bitmapMaskHandle);

            // Logic
            #if true
                // Loop > Update > Bitmap Mask Graphics Device Context --- WARN (Lapys) -> Ad-hoc method for creating the image mask.
                for (unsigned bitmapPixelRowIterator = 0u; bitmapPixelRowIterator ^ bitmap.bmWidth; bitmapPixelRowIterator++)
                for (unsigned bitmapPixelColumnIterator = 0u; bitmapPixelColumnIterator ^ bitmap.bmHeight; bitmapPixelColumnIterator++)
                    ::GetPixel(bitmapGraphicsDeviceContext, bitmapPixelRowIterator, bitmapPixelColumnIterator) == transparencyColor ?
                    ::SetPixelV(bitmapMaskGraphicsDeviceContext, bitmapPixelRowIterator, bitmapPixelColumnIterator, 16777215 /* -> RGB(255, 255, 255) */) :
                    ::SetPixelV(bitmapMaskGraphicsDeviceContext, bitmapPixelRowIterator, bitmapPixelColumnIterator, 0);
            #else
                // Update > ... Graphics Device Context --- WARN (Lapys) -> This code doesn`t work for some God-forsaken reason; Weeks have gone into rectifying this, don`t fix it!.
                ::SetBkColor(bitmapMaskGraphicsDeviceContext, transparencyColor);
                ::BitBlt(bitmapMaskGraphicsDeviceContext, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapGraphicsDeviceContext, 0, 0, SRCCOPY);

                ::BitBlt(bitmapGraphicsDeviceContext, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapMaskGraphicsDeviceContext, 0, 0, SRCINVERT);
            #endif

            // Update > Bitmap Mask Handle
            /*bitmapHandle = (HBITMAP) */::SelectObject(bitmapGraphicsDeviceContext, bitmapDummyObject);
            bitmapMaskHandle = (HBITMAP) ::SelectObject(bitmapMaskGraphicsDeviceContext, bitmapMaskDummyObject);

            // Deletion
            ::DeleteDC(bitmapGraphicsDeviceContext);
            ::DeleteDC(bitmapMaskGraphicsDeviceContext);

            // Return
            return bitmapMaskHandle;
        }
        HBITMAP createBitmapMask(HBITMAP bitmapHandle) {
            // Initialization > (Bitmap ..., Transparency Color)
            HGDIOBJ bitmapDummyObject;
            HDC bitmapGraphicsDeviceContext = ::CreateCompatibleDC(NULL);

            COLORREF transparencyColor = 0;

            // ...; Update > Transparency Color; ...
            bitmapDummyObject = ::SelectObject(bitmapGraphicsDeviceContext, bitmapHandle);
            transparencyColor = ::GetPixel(bitmapGraphicsDeviceContext, 0, 0);

            ::SelectObject(bitmapGraphicsDeviceContext, bitmapDummyObject);

            // Deletion
            ::DeleteDC(bitmapGraphicsDeviceContext);

            // Return
            return Image::createBitmapMask(bitmapHandle, transparencyColor);
        }

        // Download Image

        // Draw Image [To Window]
        void drawImage(HBITMAP bitmapHandle, const HWND windowHandle, const int xCoordinate = 0, const int yCoordinate = 0) {
            // Initialization  > (Bitmap, Window) ...
            BITMAP bitmap;
            HGDIOBJ bitmapDummyObject;
            HDC bitmapGraphicsDeviceContext;

            HDC windowGraphicsDeviceContext;
            PAINTSTRUCT windowPaintInformation;

            // Update > (Bitmap, ... Graphics Device Context)
            ::GetObject(bitmapHandle, sizeof(BITMAP), &bitmap);

            windowGraphicsDeviceContext = ::BeginPaint(windowHandle, &windowPaintInformation);
            bitmapGraphicsDeviceContext = ::CreateCompatibleDC(windowGraphicsDeviceContext);

            // Update > ... Graphics Device Context
            bitmapDummyObject = ::SelectObject(bitmapGraphicsDeviceContext, bitmapHandle);
            ::BitBlt(windowGraphicsDeviceContext, xCoordinate, yCoordinate, bitmap.bmWidth, bitmap.bmHeight, bitmapGraphicsDeviceContext, 0, 0, SRCCOPY);
            /*bitmapHandle = (HBITMAP) */::SelectObject(bitmapGraphicsDeviceContext, bitmapDummyObject);

            // Deletion
            ::DeleteObject(bitmapDummyObject);
            ::DeleteDC(bitmapGraphicsDeviceContext);
            ::DeleteObject(bitmapHandle);

            ::ReleaseDC(windowHandle, windowGraphicsDeviceContext);
            ::EndPaint(windowHandle, &windowPaintInformation);
        }

        // Request Bitmap File --- NOTE (Lapys) -> Bitmap may be OEM or stand-alone if the instance handle is `NULL`.
        HBITMAP requestBitmapFile(const char* filepath, HINSTANCE instanceHandle = (HMODULE) ::GetWindowLong(::GetActiveWindow(), GWL_HINSTANCE)) {
            // Logic > Update > Instance Handle
            if (::GetLastError()) instanceHandle = NULL;

            // Evaluation > Bitmap Handle
            HBITMAP bitmapHandle = (HBITMAP) ::LoadImage(instanceHandle, filepath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

            // Logic
            if (NULL == bitmapHandle) {
                // Initialization > (Error ID (Buffer ...), ... Console Buffer Handle)
                const unsigned short errorID = ::GetLastError();
                char errorIDBuffer[6] {'0', '\0', '\0', '\0', '\0', '\0'};
                char *errorIDBufferPointer = errorIDBuffer;

                HANDLE screenConsoleBufferHandle; // NOTE (Lapys) -> Keep the current active screen buffer active afterwards.
                const HANDLE recentActiveScreenConsoleBufferHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);

                // Update > Screen Console Buffer Handle; ...
                screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, NULL);
                ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);

                // Logic > Update > Error ID Buffer ...
                if (errorID) {
                    for (unsigned short iterator = errorID; iterator; iterator /= 10u) errorIDBufferPointer++;
                    for (unsigned short iterator = errorID; iterator; iterator /= 10u) *(--errorIDBufferPointer) = '0' + (char) (iterator % 10u);
                }

                // ... Print
                ::WriteFile(screenConsoleBufferHandle, "[ERROR (", 8uL, NULL, NULL);
                for (; *errorIDBufferPointer; errorIDBufferPointer++) ::WriteFile(screenConsoleBufferHandle, errorIDBufferPointer, 1uL, NULL, NULL);
                ::WriteFile(screenConsoleBufferHandle, ")]: Unable to retrieve requested bitmap file\n\r\0", 47uL, NULL, NULL);

                // Deletion; ...
                ::CloseHandle(screenConsoleBufferHandle);
                ::SetConsoleActiveScreenBuffer(recentActiveScreenConsoleBufferHandle);

                // Terminate
                ::exit(EXIT_FAILURE);
            }

            // Return
            return bitmapHandle;
        }
}

/* Declaration > Generic Window Class Procedure */
LRESULT CALLBACK genericWindowClassProcedure(HWND, UINT, WPARAM, LPARAM);

/* Global */
    // Image File Path
    char *imageFilepath = (char*) "assets/image.bmp";

    // Generic Window Class
    const WNDCLASS genericWindowClass {
        CS_HREDRAW | CS_VREDRAW, /* -> `style` --- NOTE (Lapys) -> Pre-defined look of window instances of the class. */
        &genericWindowClassProcedure, /* -> `lpfnWndProc`  --- NOTE (Lapys) -> Event loop or Message queue.*/
        0, /* -> `cbClsExtra` --- NOTE (Lapys) -> Extra bytes to allocate following the window class structure. */
        0, /* -> `cbWndExtra` --- NOTE (Lapys) -> Extra bytes to allocate following the window instance. */
        NULL, /* -> `hInstance` */
        NULL, /* -> `hIcon` --- NOTE (Lapys) -> Window favorite icon. */
        (HCURSOR) ::LoadCursor(NULL, IDC_ARROW), /* -> `hCursor` --- NOTE (Lapys) -> Window cursor. */
        (HBRUSH) COLOR_WINDOW, /* -> `hbrBackground` --- NOTE (Lapys) -> Window background color. */
        NULL, /* -> `lpszMenuName` --- NOTE (Lapys) -> Resource name of the window class menu. */
        "Image" /* -> `lpszClassName` */
    };

/* Function > Generic Window Class Procedure */
LRESULT CALLBACK genericWindowClassProcedure(HWND windowHandle, UINT message, WPARAM messageParameter, LPARAM additionalMessageParameter) {
    // Logic
    switch (message) {
        // [Window Manager ...]
        case WM_CLOSE: ::DestroyWindow(windowHandle); break;
        case WM_DESTROY: ::PostQuitMessage(0); break;
        case WM_PAINT: {
            // Initialization > ...
            HBITMAP image = Image::requestBitmapFile(imageFilepath);
            HBITMAP displayImage = Image::createBitmapFromDisplay();
            HBITMAP maskedImage = Image::createBitmapMask(image, RGB(0, 0, 255));

            Image::drawImage(displayImage, windowHandle);
        } break;
    }

    // Return
    return ::DefWindowProc(windowHandle, message, messageParameter, additionalMessageParameter);
}

/* Main */
int WinMain(HINSTANCE instanceHandle, HINSTANCE /*previousInstanceHandle*/, LPSTR programInitiationCommandLine, int windowAppearance) {
    // Global > (Program Status, Screen Console Buffer Handle)
    int programStatus = EXIT_SUCCESS;
    HANDLE screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, NULL);

    // [Begin] Print
    ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
    ::WriteFile(screenConsoleBufferHandle, "[PROGRAM INITIATED]\n\r", 21uL, NULL, NULL);

    // ...
    ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
    ::SetConsoleTitle("Image");
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);

    // Logic Update > Image File Path
    if (NULL != programInitiationCommandLine && *programInitiationCommandLine ^ '\0') imageFilepath = programInitiationCommandLine;

    // Logic
    if (::RegisterClass(&genericWindowClass)) {
        // Constant > Window Handle
        const HWND windowHandle = ::CreateWindowEx(0, genericWindowClass.lpszClassName, "Image", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, instanceHandle, NULL);

        // Logic
        if (windowHandle) {
            // Initialization > Window Procedure Message
            MSG windowProcedureMessage {};

            // Update > Window Handle
            ::ShowWindow(windowHandle, windowAppearance);
            ::UpdateWindow(windowHandle);

            // Loop > Logic
            while (::GetMessage(&windowProcedureMessage, NULL, 0, 0))
                if (windowProcedureMessage.message == WM_QUIT) break;
                else {
                    // Update > Window Procedure Message
                    ::TranslateMessage(&windowProcedureMessage);
                    ::DispatchMessage(&windowProcedureMessage);
                }

            // Update > Program Status
            programStatus = windowProcedureMessage.wParam;
        }

        else {
            const unsigned short errorID = ::GetLastError();
            char errorMessageBoxCaption[14] {'E', 'R', 'R', 'O', 'R', ' ', '(', '0', '\0', '\0', '\0', '\0', ')', '\0'};
            char *errorIDBuffer = errorMessageBoxCaption + 7;

            if (errorID) {
                char *errorMessageBoxCaptionPointer = errorMessageBoxCaption + 7;
                for (unsigned short iterator = errorID; iterator; iterator /= 10u) errorMessageBoxCaptionPointer++;
                *errorMessageBoxCaptionPointer = ')';
                *(errorMessageBoxCaptionPointer + 1) = '\0';
                for (unsigned short iterator = errorID; iterator; iterator /= 10u) *(--errorMessageBoxCaptionPointer) = '0' + (char) (iterator % 10u);
            }

            else {
                *(errorMessageBoxCaption + 8) = ')';
                *(errorMessageBoxCaption + 9) = '\0';
            }

            ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
            ::WriteFile(screenConsoleBufferHandle, "[ERROR (", 8uL, NULL, NULL);
            for (; *errorIDBuffer ^ ')'; errorIDBuffer++) ::WriteFile(screenConsoleBufferHandle, errorIDBuffer, 1uL, NULL, NULL);
            ::WriteFile(screenConsoleBufferHandle, ")]: Unable to create window\n\r\0", 30uL, NULL, NULL);
            ::MessageBox(NULL, "Unable to create window", errorMessageBoxCaption, MB_ICONERROR | MB_OK | MB_SETFOREGROUND);

            ::exit(programStatus = EXIT_FAILURE);
        }

        // Deletion
        ::UnregisterClass(genericWindowClass.lpszClassName, genericWindowClass.hInstance);
    }

    else {
        const unsigned short errorID = ::GetLastError();
        char errorMessageBoxCaption[14] {'E', 'R', 'R', 'O', 'R', ' ', '(', '0', '\0', '\0', '\0', '\0', ')', '\0'};
        char *errorIDBuffer = errorMessageBoxCaption + 7;

        if (errorID) {
            char *errorMessageBoxCaptionPointer = errorMessageBoxCaption + 7;
            for (unsigned short iterator = errorID; iterator; iterator /= 10u) errorMessageBoxCaptionPointer++;
            *(errorMessageBoxCaptionPointer + 1) = ')';
            *(errorMessageBoxCaptionPointer + 2) = '\0';
            for (unsigned short iterator = errorID; iterator; iterator /= 10u) *(--errorMessageBoxCaptionPointer) = '0' + (char) (iterator % 10u);
        }

        else {
            *(errorMessageBoxCaption + 8) = ')';
            *(errorMessageBoxCaption + 9) = '\0';
        }

        ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
        ::WriteFile(screenConsoleBufferHandle, "[ERROR (", 8uL, NULL, NULL);
        for (; *errorIDBuffer ^ ')'; errorIDBuffer++) ::WriteFile(screenConsoleBufferHandle, errorIDBuffer, 1uL, NULL, NULL);
        ::WriteFile(screenConsoleBufferHandle, ")]: Unable to create window (due to failing window class)\n\r\0", 60uL, NULL, NULL);
        ::MessageBox(NULL, "Unable to create window (due to failing window class)", errorMessageBoxCaption, MB_ICONERROR | MB_OK | MB_SETFOREGROUND);

        ::exit(programStatus = EXIT_FAILURE);
    }

    // [End] Print
    ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
    ::WriteFile(screenConsoleBufferHandle, "[PROGRAM TERMINATED]\0", 21uL, NULL, NULL);

    // Return
    return programStatus;
}
