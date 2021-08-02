/* ... --> advapi32.lib, gdi32.lib, kernel32.lib, shell32.lib, user32.lib */
/* Definition > ... */
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

/* Phase */
// : Singular `INITIATE` called by entry point;
// : Definitions for `RESET`, `TERMINATE`, `UPDATE`, more definitions are allowed & callable by programmer
static void INITIATE ();
       void RESET    ();
       void TERMINATE();
       void UPDATE   ();

LRESULT CALLBACK UPDATE(HWND const, UINT const, WPARAM const, LPARAM const);

/* Namespace */
// : Graphics
namespace Graphics {
    static unsigned char const CUBIC = 2u, QUADRATIC = 1u, LINEAR = 0u;

    // ...
    void drawCircle   (unsigned short const, unsigned short const, unsigned short, DWORD const);
    void drawEllipse  (unsigned short const, unsigned short const, unsigned short, unsigned short, DWORD const);
    void drawLine     (unsigned short const, unsigned short const, unsigned short const, unsigned short const, DWORD const);
    void drawRectangle(unsigned short const, unsigned short const, unsigned short const, unsigned short const, DWORD const);
    void drawSpline   (unsigned short, unsigned short, unsigned short, unsigned short, unsigned char const, ...);
    void drawSquare   (unsigned short const, unsigned short const, unsigned short const, DWORD const);

    void putPixel(unsigned short const, unsigned short const, DWORD const);
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

/* Function > ... */
void Graphics::drawCircle(unsigned short const xOrigin, unsigned short const yOrigin, unsigned short radius, DWORD const color) {
    unsigned short x = 0u;
    unsigned short y = radius / 2u;

    for (radius /= 2u; x != radius && y != 0u; ) {
        Graphics::putPixel(xOrigin + (radius + x), yOrigin + (radius + y), color);
        Graphics::putPixel(xOrigin + (radius + x), yOrigin + (radius - y), color);
        Graphics::putPixel(xOrigin + (radius - x), yOrigin + (radius + y), color);
        Graphics::putPixel(xOrigin + (radius - x), yOrigin + (radius - y), color);

        if ((radius * radius) > (((x + 1u) * (x + 1u)) + ((y + 0u) * (y + 0u)))) { ++x; continue; }
        if ((radius * radius) > (((x + 0u) * (x + 0u)) + ((y - 1u) * (y - 1u)))) { --y; continue; }
        if ((radius * radius) > (((x + 1u) * (x + 1u)) + ((y - 1u) * (y - 1u)))) { ++x; --y; }
    }
}

void Graphics::drawEllipse(unsigned short const xOrigin, unsigned short const yOrigin, unsigned short width, unsigned short height, DWORD const color) {
    unsigned short x = 0u;
    unsigned short y = height / 2u;

    for ((height /= 2u), (width /= 2u); x != width && y != 0u; ) {
        Graphics::putPixel(xOrigin + (width + x), yOrigin + (height + y), color);
        Graphics::putPixel(xOrigin + (width + x), yOrigin + (height - y), color);
        Graphics::putPixel(xOrigin + (width - x), yOrigin + (height + y), color);
        Graphics::putPixel(xOrigin + (width - x), yOrigin + (height - y), color);

        if ((height * width) > (((height * (x + 1u) * (x + 1u)) / width) + ((width * (y + 0u) * (y + 0u)) / height))) { ++x; continue; }
        if ((height * width) > (((height * (x + 0u) * (x + 0u)) / width) + ((width * (y - 1u) * (y - 1u)) / height))) { --y; continue; }
        if ((height * width) > (((height * (x + 1u) * (x + 1u)) / width) + ((width * (y - 1u) * (y - 1u)) / height))) { ++x; --y; }
    }
}

void Graphics::drawLine(unsigned short const xOrigin, unsigned short const yOrigin, unsigned short const xTarget, unsigned short const yTarget, DWORD const color) {
    unsigned short xInterval = 0u, yInterval = 0u;
    unsigned short const xDistance = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget, yDistance = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;
    unsigned short x = xOrigin, y = yOrigin;
    unsigned short const slope = xDistance > yDistance ? xDistance : yDistance;

    while ((x != xTarget || xOrigin == xTarget) && (y != yTarget || yOrigin == yTarget)) {
        if (xInterval >= slope) { xInterval -= slope; xOrigin < xTarget ? ++x : --x; }
        if (yInterval >= slope) { yInterval -= slope; yOrigin < yTarget ? ++y : --y; }

        xInterval += xDistance;
        yInterval += yDistance;
        Graphics::putPixel(x, y, color);
    }
}

void Graphics::drawRectangle(unsigned short const xOrigin, unsigned short const yOrigin, unsigned short const width, unsigned short const height, DWORD const color) {
    for (unsigned short iterator = height; iterator--; ) {
        Graphics::putPixel(xOrigin + 0u   , yOrigin + iterator, color);
        Graphics::putPixel(xOrigin + width, yOrigin + iterator, color);
    }

    for (unsigned short iterator = width; iterator--; ) {
        Graphics::putPixel(xOrigin + iterator, yOrigin + 0u    , color);
        Graphics::putPixel(xOrigin + iterator, yOrigin + height, color);
    }
}

void Graphics::drawSpline(unsigned short xOrigin, unsigned short yOrigin, unsigned short xTarget, unsigned short yTarget, unsigned char const count, ...) {
    std::va_list arguments;
    DWORD color;
    unsigned short maximumLength = 0u;
    unsigned short xAnchor[126], xControl[127];
    unsigned short yAnchor[126], yControl[127];

    // ... ->> Parse variadic arguments
    va_start(arguments, count);
      for (unsigned char iterator = 0u; count != iterator++; ) {
        xControl[iterator] = static_cast<unsigned short>(va_arg(arguments, unsigned int));
        yControl[iterator] = static_cast<unsigned short>(va_arg(arguments, unsigned int));
      }

      color = va_arg(arguments, DWORD);
      xControl[0] = xOrigin; xControl[count + 1u] = xTarget;
      yControl[0] = yOrigin; yControl[count + 1u] = yTarget;
    va_end(arguments);

    // ...
    for (unsigned short counter = count + 1u, *xControlIterator = xControl, *yControlIterator = yControl; counter--; ++xControlIterator, ++yControlIterator) {
        unsigned short length = 0u;

        length += xControlIterator[0] < xControlIterator[1] ? xControlIterator[1] - xControlIterator[0] : xControlIterator[0] - xControlIterator[1];
        length += yControlIterator[0] < yControlIterator[1] ? yControlIterator[1] - yControlIterator[0] : yControlIterator[0] - yControlIterator[1];
        if (length > maximumLength) maximumLength = length;
    }

    for (unsigned short length = 0u; length != maximumLength; ++length) {
        float const ratio = static_cast<float>(length) / static_cast<float>(maximumLength);

        // ...
        for (unsigned short counter = count + 1u, *xControlIterator = xControl, *yControlIterator = yControl; counter--; ++xControlIterator, ++yControlIterator) {
            xOrigin = xControlIterator[0]; xTarget = xControlIterator[1];
            yOrigin = yControlIterator[0]; yTarget = yControlIterator[1];

            unsigned short xInterval = 0u, yInterval = 0u;
            unsigned short const xDistance = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget, yDistance = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;
            unsigned short x = xOrigin, y = yOrigin;
            unsigned short const slope = xDistance > yDistance ? xDistance : yDistance;
            unsigned short const length = xDistance + yDistance;

            while ((x != xTarget || xOrigin == xTarget) && (y != yTarget || yOrigin == yTarget)) {
                unsigned short const xSubdistance = x < xTarget ? xTarget - x : x - xTarget, ySubdistance = y < yTarget ? yTarget - y : y - yTarget;
                unsigned short const sublength = xSubdistance + ySubdistance;

                if (ratio < 1.0f - (static_cast<float>(sublength) / static_cast<float>(length))) {
                    xAnchor[xControlIterator - xControl] = x;
                    yAnchor[yControlIterator - yControl] = y;
                    Graphics::putPixel(x, y, 0xFF0000u);
                    break;
                }

                if (xInterval >= slope) { xInterval -= slope; xOrigin < xTarget ? ++x : --x; }
                if (yInterval >= slope) { yInterval -= slope; yOrigin < yTarget ? ++y : --y; }
                xInterval += xDistance; yInterval += yDistance;
            }
        }

        // ...
        for (unsigned char subcount = count; subcount--; )
        for (unsigned short counter = subcount + 1u, *xAnchorIterator = xAnchor, *yAnchorIterator = yAnchor; counter--; ++xAnchorIterator, ++yAnchorIterator) {
            xOrigin = xAnchorIterator[0]; xTarget = xAnchorIterator[1];
            yOrigin = yAnchorIterator[0]; yTarget = yAnchorIterator[1];

            unsigned short xInterval = 0u, yInterval = 0u;
            unsigned short const xDistance = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget, yDistance = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;
            unsigned short x = xOrigin, y = yOrigin;
            unsigned short const slope = xDistance > yDistance ? xDistance : yDistance;
            unsigned short const length = xDistance + yDistance;

            while ((x != xTarget || xOrigin == xTarget) && (y != yTarget || yOrigin == yTarget)) {
                unsigned short const xSubdistance = x < xTarget ? xTarget - x : x - xTarget, ySubdistance = y < yTarget ? yTarget - y : y - yTarget;
                unsigned short const sublength = xSubdistance + ySubdistance;

                if (ratio < 1.0f - (static_cast<float>(sublength) / static_cast<float>(length))) {
                    xAnchor[xAnchorIterator - xAnchor] = x;
                    yAnchor[yAnchorIterator - yAnchor] = y;
                    Graphics::putPixel(x, y, 0x660000u);
                    break;
                }

                if (xInterval >= slope) { xInterval -= slope; xOrigin < xTarget ? ++x : --x; }
                if (yInterval >= slope) { yInterval -= slope; yOrigin < yTarget ? ++y : --y; }
                xInterval += xDistance; yInterval += yDistance;
            }
        }

        // ...
        Graphics::putPixel(*xAnchor, *yAnchor, color);
    }
}

void Graphics::drawSquare(unsigned short const xOrigin, unsigned short const yOrigin, unsigned short const size, DWORD const color) {
    for (unsigned short iterator = size; iterator--; ) {
        Graphics::putPixel(xOrigin + 0u      , yOrigin + iterator, color);
        Graphics::putPixel(xOrigin + iterator, yOrigin + 0u      , color);
        Graphics::putPixel(xOrigin + iterator, yOrigin + size    , color);
        Graphics::putPixel(xOrigin + size    , yOrigin + iterator, color);
    }
}

void Graphics::putPixel(unsigned short const x, unsigned short const y, DWORD const color) {
    Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY[x + (y * Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth)] = 0xFF000000u | color;
}

/* Main */
#include <csignal>
int WinMain(HINSTANCE const programHandle, HINSTANCE const, LPSTR const, int const appearance) {
    Program::HANDLE = programHandle;
    Window::APPEARANCE = appearance;

    struct segmentation { static void fault(int const) {
        std::puts("SEGFAULT: Enter to continue...");
        ::BitBlt(Window::DEVICE_CONTEXT_HANDLE, 0, 0, Window::WIDTH, Window::HEIGHT, Window::MEMORY_DEVICE_CONTEXT_HANDLE, 0, 0, SRCCOPY);
        std::getchar();
        std::exit(EXIT_FAILURE);
    } };
    std::signal(SIGSEGV, &segmentation::fault);

    // ...
    INITIATE();
    return Program::EXIT_CODE;
}

/* Phase */
/* : Initiate */
void INITIATE() {
    WNDCLASSEX classInformation;

    // ...
    ::GetModuleFileName(static_cast<HMODULE>(NULL), Program::FILE_NAME, MAX_PATH);

    Window::BACKGROUND = ::GetSysColorBrush(COLOR_WINDOW);
    Window::CURSOR     = ::LoadCursor(NULL, IDC_ARROW); // --> static_cast<HCURSOR>(::LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED))
    Window::ICON       = ::ExtractIcon(static_cast<HINSTANCE>(::GetCurrentProcess()), Program::FILE_NAME, 0u);
    Window::PROCEDURE  = static_cast<LRESULT CALLBACK (*)(HWND const, UINT const, WPARAM const, LPARAM const)>(&UPDATE);
    Window::STYLE      = WS_POPUP;
    Window::TITLE      = "Geometry";

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
            bitmapInformation.bmiHeader.biClrUsed       = 0u;
            bitmapInformation.bmiHeader.biClrImportant  = 0u;
            bitmapInformation.bmiHeader.biCompression   = BI_RGB;
            bitmapInformation.bmiHeader.biHeight        = -Window::HEIGHT;
            bitmapInformation.bmiHeader.biPlanes        = 1u;
            bitmapInformation.bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
            bitmapInformation.bmiHeader.biSizeImage     = Window::HEIGHT * Window::WIDTH * sizeof(UINT32);
            bitmapInformation.bmiHeader.biWidth         = Window::WIDTH;
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
        case WM_PAINT: {
            // // [Line]
            // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, 0u                , 0u                 , 0x606060u);
            // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, 0u                , Window::HEIGHT - 1u, 0x606060u);
            // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, 0u                , Window::HEIGHT / 2u, 0x606060u);
            // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, Window::WIDTH / 2u, 0u                 , 0x606060u);
            // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, Window::WIDTH - 1u, 0u                 , 0x606060u);
            // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, Window::WIDTH - 1u, Window::HEIGHT - 1u, 0x606060u);
            // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, Window::WIDTH - 1u, Window::HEIGHT / 2u, 0x606060u);
            // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, Window::WIDTH / 2u, Window::HEIGHT - 1u, 0x606060u);
            // Graphics::drawLine(std::rand() % Window::WIDTH, std::rand() % Window::HEIGHT, std::rand() % Window::WIDTH, std::rand() % Window::HEIGHT, 0x0F0F0Fu);

            // // [Circle, Ellipse, Rectangle, Square]
            // Graphics::drawSquare((Window::WIDTH - 200u) / 2u, (Window::HEIGHT - 200u) / 2u, 200u, 0xAA0000u);
            // Graphics::drawCircle((Window::WIDTH - 200u) / 2u, (Window::HEIGHT - 200u) / 2u, 200u, 0xCCCCCCu);

            // Graphics::drawRectangle((Window::WIDTH - 500u) / 2u, (Window::HEIGHT - 250u) / 2u, 500u, 250u, 0xAA0000u);
            // Graphics::drawEllipse  ((Window::WIDTH - 500u) / 2u, (Window::HEIGHT - 250u) / 2u, 500u, 250u, 0xCCCCCCu);

            // [Spline]
            Graphics::drawSpline(50u, 400u, 150u, 100u, Graphics::LINEAR   , 0xFFFF00u);
            Graphics::drawSpline(350u, 400u, 400u, 80u, Graphics::QUADRATIC, 500u, 200u, 0xFF00FFu);
            Graphics::drawSpline(700u, 400u, 650u, 120u, Graphics::CUBIC   , 850u, 200u, 750u, 80u, 0x00FFFFu);

            // ...
            ::BitBlt(Window::DEVICE_CONTEXT_HANDLE, 0, 0, Window::WIDTH, Window::HEIGHT, Window::MEMORY_DEVICE_CONTEXT_HANDLE, 0, 0, SRCCOPY);
        } return 0x0L;
    }

    // ...
    return ::DefWindowProc(windowHandle, message, parameter, subparameter);
}

/* : Terminate */
void TERMINATE() {
    if (NULL != Window::HANDLE) ::DestroyWindow(Window::HANDLE);
    ::UnregisterClass(Window::CLASS_NAME, Program::HANDLE);

    std::exit(Program::EXIT_CODE);
}
