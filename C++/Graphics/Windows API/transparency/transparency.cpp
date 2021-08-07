/* ... --> advapi32.lib, dwmapi.lib, gdi32.lib, kernel32.lib, msimg32.lib, shell32.lib, user32.lib */
/* Definition > ... */
#ifndef PW_RENDERFULLCONTENT
# define PW_RENDERFULLCONTENT 0x00000002
#endif
#define _WIN32_WINNT 0x0501

#undef UNICODE

/* Import */
// : [C Standard Library]
#include <stdbool.h> // Standard Boolean
#include <stdint.h>  // Standard Integers

// : [C++ Standard Library]
#include <cstdarg> // C Standard Arguments
#include <cstdio>  // C Standard Input/ Output
#include <cstdlib> // C Standard Library

// : [Windows API]
#include <windows.h> // Windows
# include <d3d9.h>   // Direct 3D v9
# include <dwmapi.h> // Desktop Window Manager API

/* Phase > ... */
static void INITIATE ();
       void RESET    ();
       void TERMINATE();
       void UPDATE   ();

LRESULT CALLBACK UPDATE(HWND const, UINT const, WPARAM const, LPARAM const);

/* Namespace */
// : Graphics
namespace Graphics {
    static struct Direct3D {
      private: LPDIRECT3D9 value;
      public:
        Direct3D() : value() {}
        Direct3D(LPDIRECT3D9 const value) : value(value) {}

        // ...
        LPDIRECT3DDEVICE9     DEVICE = NULL;
        D3DPRESENT_PARAMETERS PRESENTATION_PARAMETERS;

        // ...
        LPDIRECT3D9 operator ->() const { return this -> value; }
        operator LPDIRECT3D9&() { return const_cast<LPDIRECT3D9&>(this -> value); }
    } Direct3D = NULL;
}

// : Program
namespace Program {
    static int       EXIT_CODE           = EXIT_SUCCESS;
    static CHAR      FILE_NAME[MAX_PATH] = {'\0'};
    static HINSTANCE HANDLE              = NULL;
    static MSG       THREAD_MESSAGE      = MSG();
}

// : Window
namespace Window {
    static int     APPEARANCE      = SW_SHOW;
    static HBRUSH  BACKGROUND      = NULL;
    static LPCSTR  CLASS_NAME      = "window";
    static UINT    CLASS_STYLE     = CS_GLOBALCLASS | CS_OWNDC;
    static HCURSOR CURSOR          = NULL;
    static HICON   FAVICON         = NULL;
    static HWND    HANDLE          = NULL;
    static int     HEIGHT          = -1;
    static HICON   ICON            = NULL;
    static int     LEFT            = -1;
    static LRESULT CALLBACK (*PROCEDURE)(HWND const, UINT const, WPARAM const, LPARAM const) = &::DefWindowProc;
    static DWORD   STYLE           = WS_OVERLAPPEDWINDOW;
    static DWORD   STYLE_EXTENSION = 0x00000000L;
    static LPCSTR  TITLE           = "";
    static int     TOP             = -1;
    static int     WIDTH           = -1;

    // ... ->> Renderers
    static HBITMAP DEVICE_CONTEXT_BITMAP_HANDLE        = NULL;
    static HDC     DEVICE_CONTEXT_HANDLE               = NULL;

    static BITMAP  MEMORY_DEVICE_CONTEXT_BITMAP        = ::BITMAP();
    static HBITMAP MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE = NULL;
    static UINT32 *MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY = NULL;
    static HDC     MEMORY_DEVICE_CONTEXT_HANDLE        = NULL;
}

/* Main */
int WinMain(HINSTANCE const programHandle, HINSTANCE const, LPSTR const, int const appearance) {
    Program::HANDLE = programHandle;
    Window::APPEARANCE = appearance;

    // ...
    INITIATE();
    return Program::EXIT_CODE;
}

/* Phase */
/* : Initiate */
void INITIATE() {
    WNDCLASSEX classInformation;

    // ...
    if (NULL == Window::HANDLE)
    ::GetModuleFileName(static_cast<HMODULE>(NULL), Program::FILE_NAME, MAX_PATH);

    Window::BACKGROUND = ::GetSysColorBrush(COLOR_WINDOW);
    Window::CURSOR     = ::LoadCursor(NULL, IDC_ARROW); // --> static_cast<HCURSOR>(::LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED))
    Window::ICON       = ::ExtractIcon(static_cast<HINSTANCE>(::GetCurrentProcess()), Program::FILE_NAME, 0u);
    Window::PROCEDURE  = static_cast<LRESULT CALLBACK (*)(HWND const, UINT const, WPARAM const, LPARAM const)>(&UPDATE);
    Window::STYLE      = WS_POPUP;
    Window::TITLE      = "Transparency";

    // ...
    classInformation.cbClsExtra    = 0;
    classInformation.cbSize        = sizeof(WNDCLASSEX);
    classInformation.cbWndExtra    = 0;
    classInformation.hbrBackground = Window::BACKGROUND;
    classInformation.hCursor       = Window::CURSOR;
    classInformation.hIcon         = Window::ICON;
    classInformation.hIconSm       = Window::FAVICON;
    classInformation.hInstance     = Program::HANDLE;
    classInformation.lpfnWndProc   = Window::PROCEDURE;
    classInformation.lpszClassName = Window::CLASS_NAME;
    classInformation.lpszMenuName  = static_cast<LPCSTR>(NULL);
    classInformation.style         = Window::CLASS_STYLE;

    // ...
    if (0x0 == ::RegisterClassEx(const_cast<WNDCLASSEX const*>(&classInformation))) TERMINATE();
    else {
        if (Window::HEIGHT == -1 || Window::LEFT == -1 || Window::TOP == -1 || Window::WIDTH == -1) {
            RECT workareaBounds;
            ::SystemParametersInfo(SPI_GETWORKAREA, 0x0000u, static_cast<PVOID>(&workareaBounds), 0x0u);

            // ...
            if (Window::HEIGHT == -1) Window::HEIGHT = ((workareaBounds.bottom - workareaBounds.top) * 3) / 4;
            if (Window::WIDTH  == -1) Window::WIDTH  = ((workareaBounds.right - workareaBounds.left) * 3) / 4;

            if (Window::LEFT   == -1) Window::LEFT   = (((workareaBounds.right - workareaBounds.left) - Window::WIDTH ) * 1) / 2;
            if (Window::TOP    == -1) Window::TOP    = (((workareaBounds.bottom - workareaBounds.top) - Window::HEIGHT) * 1) / 2;
        }

        Window::HANDLE = ::CreateWindowEx(
            Window::STYLE_EXTENSION, Window::CLASS_NAME, Window::TITLE, Window::STYLE,
            Window::LEFT, Window::TOP, Window::WIDTH, Window::HEIGHT,
            NULL /* --> HWND_DESKTOP */, static_cast<HMENU>(NULL), Program::HANDLE,
            reinterpret_cast<LPVOID>(static_cast<LPARAM>(Window::APPEARANCE))
        );

        // ...
        if (NULL == Window::HANDLE) TERMINATE();
        else for (bool available = false; WM_QUIT != Program::THREAD_MESSAGE.message; ) {
            available = ::PeekMessage(&Program::THREAD_MESSAGE, NULL, 0x0u, 0x0u, PM_REMOVE);
            if (FALSE != available) ::DispatchMessage(&Program::THREAD_MESSAGE);

            Program::EXIT_CODE = Program::THREAD_MESSAGE.wParam;
        }
    }
}

/* : Update */
LRESULT CALLBACK UPDATE(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
    switch (message) {
        /* ... */
        case WM_CLOSE     :                             ::DestroyWindow(windowHandle); break;
        case WM_KEYDOWN   : if (VK_ESCAPE == parameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSCOMMAND: if (SC_CLOSE  == parameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSKEYDOWN: if (VK_F4     == parameter) ::DestroyWindow(windowHandle); break;

        /* ... */
        case WM_CREATE: {
            BITMAPINFO bitmapInformation;
            LPVOID const creationParameter = reinterpret_cast<CREATESTRUCTA const*>(subparameter) -> lpCreateParams;

            /* ... */
            Window::DEVICE_CONTEXT_HANDLE = ::GetDCEx(windowHandle, static_cast<HRGN>(NULL), DCX_LOCKWINDOWUPDATE | DCX_NORESETATTRS | DCX_WINDOW);
            if (NULL == Window::DEVICE_CONTEXT_HANDLE) TERMINATE();

            Window::DEVICE_CONTEXT_BITMAP_HANDLE = ::CreateCompatibleBitmap(Window::DEVICE_CONTEXT_HANDLE, Window::WIDTH, Window::HEIGHT);
            if (NULL == Window::DEVICE_CONTEXT_BITMAP_HANDLE) TERMINATE();

            // ...
            bitmapInformation.bmiColors -> rgbBlue      = 0u;
            bitmapInformation.bmiColors -> rgbGreen     = 0u;
            bitmapInformation.bmiColors -> rgbRed       = 0u;
            bitmapInformation.bmiColors -> rgbReserved  = 0x0u;
            bitmapInformation.bmiHeader.biBitCount      = 32u;
            bitmapInformation.bmiHeader.biClrImportant  = 0u;
            bitmapInformation.bmiHeader.biClrUsed       = 0u;
            bitmapInformation.bmiHeader.biCompression   = BI_RGB;
            bitmapInformation.bmiHeader.biHeight        = -Window::HEIGHT;
            bitmapInformation.bmiHeader.biPlanes        = 1u;
            bitmapInformation.bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
            bitmapInformation.bmiHeader.biSizeImage     = Window::HEIGHT * Window::WIDTH * sizeof(UINT32);
            bitmapInformation.bmiHeader.biWidth         = +Window::WIDTH;
            bitmapInformation.bmiHeader.biXPelsPerMeter = ::GetDeviceCaps(Window::DEVICE_CONTEXT_HANDLE, HORZRES) / ::GetDeviceCaps(Window::DEVICE_CONTEXT_HANDLE, HORZSIZE);
            bitmapInformation.bmiHeader.biYPelsPerMeter = ::GetDeviceCaps(Window::DEVICE_CONTEXT_HANDLE, VERTRES) / ::GetDeviceCaps(Window::DEVICE_CONTEXT_HANDLE, VERTSIZE);

            // ...
            Window::MEMORY_DEVICE_CONTEXT_HANDLE = ::CreateCompatibleDC(Window::DEVICE_CONTEXT_HANDLE);
            if (NULL == Window::MEMORY_DEVICE_CONTEXT_HANDLE) TERMINATE();

            Window::MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE = ::CreateDIBSection(Window::MEMORY_DEVICE_CONTEXT_HANDLE, &bitmapInformation, DIB_RGB_COLORS, static_cast<VOID**>(static_cast<void*>(&Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY)), NULL, 0u);
            if (NULL == Window::MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE && NULL == Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY) TERMINATE();

            /* ... */
            // ::FreeConsole();
            ::GetObject(Window::MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE, sizeof(BITMAP), &Window::MEMORY_DEVICE_CONTEXT_BITMAP);

            ::SelectObject(Window::DEVICE_CONTEXT_HANDLE, Window::DEVICE_CONTEXT_BITMAP_HANDLE);
            ::SelectObject(Window::MEMORY_DEVICE_CONTEXT_HANDLE, Window::MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE);
            ::ShowWindow(windowHandle, /* --> SW_SHOWDEFAULT */ static_cast<long>(static_cast<int>(reinterpret_cast<intptr_t>(creationParameter))));
        } break;

        // ...
        case WM_DESTROY: {
            ::DeleteDC(Window::MEMORY_DEVICE_CONTEXT_HANDLE); ::DeleteObject(Window::MEMORY_DEVICE_CONTEXT_BITMAP_HANDLE);
            ::ReleaseDC(windowHandle, Window::DEVICE_CONTEXT_HANDLE);
            Window::HANDLE = NULL;

            ::PostQuitMessage(EXIT_SUCCESS);
        } break;

        /* ... */
        case WM_ERASEBKGND: return 0x1L;
        case WM_PAINT: {
            RECT hitTestRectangle;

            // ... ->> Assert the window is visible
            if (NULLREGION != ::GetClipBox(Window::DEVICE_CONTEXT_HANDLE, &hitTestRectangle) && FALSE == ::IsIconic(Window::HANDLE) && ::IsWindowVisible(Window::HANDLE)) {
                HWND       desktopWallpaperWindowHandle = NULL;
                HWND const programManagerWindowHandle   = ::FindWindowW(L"ProgMan", NULL);
                RECT       windowRectangle;

                // ...
                windowRectangle.bottom = Window::TOP  + Window::HEIGHT;
                windowRectangle.left   = Window::LEFT + 0u;
                windowRectangle.right  = Window::LEFT + Window::WIDTH;
                windowRectangle.top    = Window::TOP  + 0u;

                // ... ->> Send message request to spawn a worker behind the desktop icons (otherwise do nothing)
                ::SendMessageTimeout(programManagerWindowHandle, 0x052Cu, 0x0u, 0x0L, SMTO_NORMAL, 1000u, static_cast<PDWORD_PTR>(NULL));

                // ... --- UPDATE (Lapys) -> Filter for windows with differing capture/ monitor display behavior ->> Enumerate the windows that are behind
                for (HWND windowHandleIterator = Window::HANDLE; NULL != windowHandleIterator; windowHandleIterator = ::GetWindow(windowHandleIterator, GW_HWNDNEXT)) {
                    HDC        backgroundWindowDeviceContextHandle;
                    HWND const backgroundWindowHandle       = windowHandleIterator;
                    INT        backgroundWindowIsCloaked    = FALSE; // ->> checks for actual visibility, as opposed to just checking for the `WS_VISIBLE` style with `IsWindowVisible(...)`
                    bool       backgroundWindowIsObscured   = false; // ->> checks if the window is completely obscured by an above sibling
                    BYTE       backgroundWindowOpacity      = 255u;
                    RECT       backgroundWindowRectangle;

                    // ... ->> Retrieve the window for desktop wallpapers via a spawned worker
                    if (NULL == desktopWallpaperWindowHandle && NULL != ::FindWindowExW(backgroundWindowHandle, NULL, L"SHELLDLL_DefView", NULL))
                    desktopWallpaperWindowHandle = ::FindWindowExW(NULL, backgroundWindowHandle, L"WorkerW", NULL);

                    // ... ->> Filter for top-level level windows only
                    if (Window::HANDLE != backgroundWindowHandle && backgroundWindowHandle == ::GetAncestor(backgroundWindowHandle, GA_ROOT)) {
                        // ... ->> Filter for non-cloaked, non-iconic, visible windows only
                        ::DwmGetWindowAttribute(backgroundWindowHandle, DWMWA_CLOAKED, &backgroundWindowIsCloaked, sizeof(INT));
                        if (FALSE == backgroundWindowIsCloaked && FALSE == ::IsIconic(backgroundWindowHandle) && ::IsWindowVisible(backgroundWindowHandle)) {
                            // ... ->> Retrieve the background window bounds and opacity.
                            ::GetWindowRect(backgroundWindowHandle, &backgroundWindowRectangle); // ->> Correct for drop shadows via `DWMWA_EXTENDED_FRAME_BOUNDS` and exclusive `bottom`/ `right` values.
                            ::DwmGetWindowAttribute(backgroundWindowHandle, DWMWA_EXTENDED_FRAME_BOUNDS, &backgroundWindowRectangle, sizeof(RECT));

                            ::GetLayeredWindowAttributes(backgroundWindowHandle, static_cast<COLORREF*>(NULL), &backgroundWindowOpacity, static_cast<DWORD*>(NULL));

                            // ...
                            backgroundWindowDeviceContextHandle = ::GetDCEx(backgroundWindowHandle, NULL, CS_OWNDC | DCX_NORESETATTRS | DCX_WINDOW);
                            if (NULL != backgroundWindowDeviceContextHandle) {
                                unsigned short const backgroundWindowHeight = backgroundWindowRectangle.bottom - backgroundWindowRectangle.top ;
                                unsigned short const backgroundWindowWidth  = backgroundWindowRectangle.right  - backgroundWindowRectangle.left;

                                // ... ->> Filter for non-obscured intersecting/ wrapping windows only
                                if (NULLREGION != ::GetClipBox(backgroundWindowDeviceContextHandle, &hitTestRectangle) && FALSE != ::IntersectRect(&hitTestRectangle, &backgroundWindowRectangle, &windowRectangle))
                                for (HWND subwindowHandleIterator = backgroundWindowHandle; Window::HANDLE != subwindowHandleIterator; subwindowHandleIterator = ::GetWindow(subwindowHandleIterator, GW_HWNDPREV)) {
                                    HWND const backgroundSubwindowHandle = subwindowHandleIterator;
                                    RECT       backgroundSubwindowRectangle;

                                    if (backgroundWindowHandle != backgroundSubwindowHandle) {
                                        ::GetWindowRect(backgroundSubwindowHandle, &backgroundSubwindowRectangle);
                                        if (
                                            backgroundWindowRectangle.bottom <= backgroundSubwindowRectangle.bottom &&
                                            backgroundWindowRectangle.left   >= backgroundSubwindowRectangle.left   &&
                                            backgroundWindowRectangle.top    >= backgroundSubwindowRectangle.top    &&
                                            backgroundWindowRectangle.right  <= backgroundSubwindowRectangle.right
                                        ) { backgroundWindowIsObscured = true; break; }
                                    }
                                }

                                // ...
                                if (false == backgroundWindowIsObscured) {
                                    static_cast<void>(backgroundWindowDeviceContextHandle);
                                    static_cast<void>(backgroundWindowHandle);
                                    static_cast<void>(backgroundWindowHeight);
                                    static_cast<void>(backgroundWindowOpacity);
                                    static_cast<void>(backgroundWindowRectangle);
                                    static_cast<void>(backgroundWindowWidth);
                                    static_cast<void>(desktopWallpaperWindowHandle);
                                    static_cast<void>(windowRectangle);

                                    // ::PrintWindow(backgroundWindowHandle, Window::MEMORY_DEVICE_CONTEXT_HANDLE, PW_RENDERFULLCONTENT);
                                    // ::BitBlt(Window::MEMORY_DEVICE_CONTEXT_HANDLE, 0, 0, backgroundWindowWidth, backgroundWindowHeight, backgroundWindowDeviceContextHandle, 0, 0, SRCCOPY);
                                    // BLENDFUNCTION blendFunction;

                                    // blendFunction.AlphaFormat = AC_SRC_ALPHA;
                                    // blendFunction.BlendFlags = 0x0u;
                                    // blendFunction.BlendOp = AC_SRC_OVER;
                                    // blendFunction.SourceConstantAlpha = 255u;

                                    // ::AlphaBlend(
                                    //     Window::MEMORY_DEVICE_CONTEXT_HANDLE,
                                    //     backgroundWindowRectangle.left, backgroundWindowRectangle.top, backgroundWindowRectangle.right, backgroundWindowRectangle.bottom,
                                    //     backgroundWindowDeviceContextHandle,
                                    //     0, 0, backgroundWindowRectangle.right, backgroundWindowRectangle.bottom,
                                    //     blendFunction
                                    // );
                                }

                                // ...
                                ::DeleteDC(backgroundWindowDeviceContextHandle);
                            }
                        }
                    }
                }
            }

            // ...
            ::BitBlt(Window::DEVICE_CONTEXT_HANDLE, 0, 0, Window::WIDTH, Window::HEIGHT, Window::MEMORY_DEVICE_CONTEXT_HANDLE, 0, 0, SRCCOPY);
        } return 0x0L;
    }

    // ...
    return ::DefWindowProc(windowHandle, message, parameter, subparameter);
}

/* : Reset */
void RESET() { return INITIATE(); }

/* : Terminate */
void TERMINATE() {
    if (NULL != Window::HANDLE) ::DestroyWindow(Window::HANDLE);
    ::UnregisterClass(Window::CLASS_NAME, Program::HANDLE);

    std::exit(Program::EXIT_CODE);
}
