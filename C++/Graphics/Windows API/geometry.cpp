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

/* Phase > ... */
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
    void drawSpline   (unsigned short const, unsigned short const, unsigned short const, unsigned short const, unsigned char const, ...);
    void drawSquare   (unsigned short const, unsigned short const, unsigned short const, DWORD const);

    void putPixel(unsigned short const, unsigned short const, DWORD const);
    void rotateBy(unsigned short const, unsigned short const, float const);
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

    radius /= 2u;
    while (true) {
        Graphics::putPixel(xOrigin + (radius + x), yOrigin + (radius + y), color);
        Graphics::putPixel(xOrigin + (radius + x), yOrigin + (radius - y), color);
        Graphics::putPixel(xOrigin + (radius - x), yOrigin + (radius + y), color);
        Graphics::putPixel(xOrigin + (radius - x), yOrigin + (radius - y), color);

        // ...
        if (x == radius || y == 0u) break;

        if ((radius * radius) > (((x + 1u) * (x + 1u)) + ((y + 0u) * (y + 0u)))) { ++x; continue; }
        if ((radius * radius) > (((x + 0u) * (x + 0u)) + ((y - 1u) * (y - 1u)))) { --y; continue; }
        if ((radius * radius) > (((x + 1u) * (x + 1u)) + ((y - 1u) * (y - 1u)))) { ++x; --y; }
    }
}

void Graphics::drawEllipse(unsigned short const xOrigin, unsigned short const yOrigin, unsigned short width, unsigned short height, DWORD const color) {
    unsigned short x = 0u;
    unsigned short y = height / 2u;

    height /= 2u; width /= 2u;
    while (true) {
        Graphics::putPixel(xOrigin + (width + x), yOrigin + (height + y), color);
        Graphics::putPixel(xOrigin + (width + x), yOrigin + (height - y), color);
        Graphics::putPixel(xOrigin + (width - x), yOrigin + (height + y), color);
        Graphics::putPixel(xOrigin + (width - x), yOrigin + (height - y), color);

        // ...
        if (x == width || y == 0u) break;

        if ((height * width) > (((height * (x + 1u) * (x + 1u)) / width) + ((width * (y + 0u) * (y + 0u)) / height))) { ++x; continue; }
        if ((height * width) > (((height * (x + 0u) * (x + 0u)) / width) + ((width * (y - 1u) * (y - 1u)) / height))) { --y; continue; }
        if ((height * width) > (((height * (x + 1u) * (x + 1u)) / width) + ((width * (y - 1u) * (y - 1u)) / height))) { ++x; --y; }
    }
}

void Graphics::drawLine(unsigned short const xOrigin, unsigned short const yOrigin, unsigned short const xTarget, unsigned short const yTarget, DWORD const color) {
    unsigned short xSlopeInterval = 0u;
    unsigned short ySlopeInterval = 0u;

    unsigned short const xDistance = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget;
    unsigned short const yDistance = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;

    unsigned short x = xOrigin;
    unsigned short y = yOrigin;

    unsigned short const slope = xDistance > yDistance ? xDistance : yDistance;

    // ...
    while ((x != xTarget || xOrigin == xTarget) && (y != yTarget || yOrigin == yTarget)) {
        if (slope <= xSlopeInterval) { xSlopeInterval -= slope; xOrigin < xTarget ? ++x : --x; }
        if (slope <= ySlopeInterval) { ySlopeInterval -= slope; yOrigin < yTarget ? ++y : --y; }

        xSlopeInterval += xDistance;
        ySlopeInterval += yDistance;
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

static unsigned short SUS = 1u;
void Graphics::drawSpline(unsigned short const xOrigin, unsigned short const yOrigin, unsigned short const xTarget, unsigned short const yTarget, unsigned char const count, ...) {
    std::va_list arguments;
    DWORD color;
    unsigned short maximumLength = 0u;

    unsigned short xControl[127], yControl[127];
    unsigned short xCurrent = xOrigin, yCurrent = yOrigin;
    unsigned short xRecent, yRecent;
    unsigned short xSubcontrol[126], ySubcontrol[126];

    // ...
    va_start(arguments, count);
      for (unsigned char iterator = 0u; count != iterator++; ) {
        xControl[iterator] = static_cast<unsigned short>(va_arg(arguments, unsigned int));
        yControl[iterator] = static_cast<unsigned short>(va_arg(arguments, unsigned int));
      }

      color = va_arg(arguments, DWORD);
      xControl[0] = xOrigin; xControl[count + 1u] = xTarget;
      yControl[0] = yOrigin; yControl[count + 1u] = yTarget;

      for (unsigned char iterator = count + 1u; iterator; --iterator) {
        unsigned short length = 0u;
        unsigned short const xOrigin = xControl[iterator - 1u];
        unsigned short const yOrigin = yControl[iterator - 1u];
        unsigned short const xTarget = xControl[iterator - 0u];
        unsigned short const yTarget = yControl[iterator - 0u];

        // ...
        length += xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget;
        length += yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;

        if (length > maximumLength) maximumLength = length;
      }
    va_end(arguments);

    // ...
    maximumLength = SUS;
    for (unsigned char iterator = count + 1u; iterator; --iterator) {
        unsigned short const xTarget = xControl[iterator - 0u];
        unsigned short const yTarget = yControl[iterator - 0u];
        unsigned short const xOrigin = xControl[iterator - 1u];
        unsigned short const yOrigin = yControl[iterator - 1u];

        Graphics::drawLine(xOrigin, yOrigin, xTarget, yTarget, 0xFF0000u);
    }

    // ...
    for (unsigned short currentLength = 1u; currentLength != maximumLength; ++currentLength) {
        // ...
        for (unsigned char iterator = count + 1u; iterator; --iterator) {
            unsigned short const xTarget        = xControl[iterator - 0u];
            unsigned short const yTarget        = yControl[iterator - 0u];
            unsigned short       xSlopeInterval = 0u;
            unsigned short       ySlopeInterval = 0u;
            unsigned short const xOrigin        = xControl[iterator - 1u];
            unsigned short const yOrigin        = yControl[iterator - 1u];
            unsigned short const xDistance      = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget;
            unsigned short const yDistance      = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;
            unsigned short x = xOrigin;
            unsigned short y = yOrigin;

            unsigned short const slope  = xDistance > yDistance ? xDistance : yDistance;
            unsigned short const length = xDistance + yDistance;

            // ...
            for (unsigned int interval = currentLength * length; (x != xTarget || xOrigin == xTarget) && (y != yTarget || yOrigin == yTarget); ) {
                if (0u == interval) {
                    xSubcontrol[iterator - 1u] = x;
                    ySubcontrol[iterator - 1u] = y;

                    break;
                }

                if (slope <= xSlopeInterval) { interval = (interval > maximumLength) * (interval - maximumLength); xSlopeInterval -= slope; xOrigin < xTarget ? ++x : --x; }
                if (slope <= ySlopeInterval) { interval = (interval > maximumLength) * (interval - maximumLength); ySlopeInterval -= slope; yOrigin < yTarget ? ++y : --y; }

                xSlopeInterval += xDistance;
                ySlopeInterval += yDistance;

                if ((0xFF000000u | color) != Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY[x + (y * Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth)])
                Graphics::putPixel(x, y, 0xFF0000u);
            }
        }

        // ...
        for (unsigned char subcount = count; subcount--; ) {
            unsigned short submaximumLength = 0u;

            for (unsigned char iterator = subcount + 1u; iterator; --iterator) {
                unsigned short sublength = 0u;
                unsigned short const xTarget = xSubcontrol[iterator - 0u];
                unsigned short const yTarget = ySubcontrol[iterator - 0u];
                unsigned short const xOrigin = xSubcontrol[iterator - 1u];
                unsigned short const yOrigin = ySubcontrol[iterator - 1u];

                sublength += xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget;
                sublength += yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;

                if (sublength > submaximumLength) submaximumLength = sublength;
            }

            for (unsigned char iterator = subcount + 1u; iterator; --iterator) {
                unsigned short const xTarget        = xSubcontrol[iterator - 0u];
                unsigned short const yTarget        = ySubcontrol[iterator - 0u];
                unsigned short       xSlopeInterval = 0u;
                unsigned short       ySlopeInterval = 0u;
                unsigned short const xOrigin        = xSubcontrol[iterator - 1u];
                unsigned short const yOrigin        = ySubcontrol[iterator - 1u];
                unsigned short const xDistance      = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget;
                unsigned short const yDistance      = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;
                unsigned short x = xOrigin;
                unsigned short y = yOrigin;

                unsigned short const sublength = xDistance + yDistance;
                unsigned short const slope     = xDistance > yDistance ? xDistance : yDistance;

                // ...
                for (float interval = static_cast<float>(sublength) * (static_cast<float>(currentLength * submaximumLength) / static_cast<float>(maximumLength)); (x != xTarget || xOrigin == xTarget) && (y != yTarget || yOrigin == yTarget); ) {
                    if (interval <= 0.0f) {
                        xSubcontrol[iterator - 1u] = x;
                        ySubcontrol[iterator - 1u] = y;

                        break;
                    }

                    if (slope <= xSlopeInterval) { interval = (interval > submaximumLength) * (interval - submaximumLength); xSlopeInterval -= slope; xOrigin < xTarget ? ++x : --x; }
                    if (slope <= ySlopeInterval) { interval = (interval > submaximumLength) * (interval - submaximumLength); ySlopeInterval -= slope; yOrigin < yTarget ? ++y : --y; }

                    xSlopeInterval += xDistance;
                    ySlopeInterval += yDistance;

                    if (color != (Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY[x + (y * Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth)] & 0xFFFFFFu))
                    Graphics::putPixel(x, y, (iterator == 3u ? 0x000030u : iterator == 2u ? 0x003000u : 0x300000u) | Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY[x + (y * Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth)]);
                }
            }
        }

        // ... ->> accumulated {x, y}
        // if (xCurrent != *xSubcontrol && yCurrent != *ySubcontrol) {
        //     xRecent = xCurrent; yRecent = yCurrent;
        //     xCurrent = *xSubcontrol; yCurrent = *ySubcontrol;

        //     if (xCurrent != xRecent && yCurrent != yRecent) Graphics::drawLine(xRecent, yRecent, xCurrent, yCurrent, color);
        // }

        static_cast<void>(xCurrent); static_cast<void>(yCurrent);
        static_cast<void>(xRecent); static_cast<void>(yRecent);
        Graphics::putPixel(*xSubcontrol, *ySubcontrol, color);
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
        std::fputs("SEGFAULT: Enter to continue...", stderr);
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
            bitmapInformation.bmiHeader.biCompression   = BI_RGB;
            bitmapInformation.bmiHeader.biClrImportant  = 0u;
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
        case WM_KEYUP: {
            ++SUS;
            for (unsigned short y = Window::HEIGHT; y--; )
            for (unsigned short x = Window::WIDTH; x--; ) {
                Graphics::putPixel(x, y, 0x000000u);
            }
        } break;

        case WM_ERASEBKGND: return 0x1L;
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
            // Graphics::drawCircle((Window::WIDTH - 200u) / 2u, (Window::HEIGHT - 200u) / 2u, 200u, 0xCCCCCCu);

            // Graphics::drawRectangle((Window::WIDTH - 500u) / 2u, (Window::HEIGHT - 250u) / 2u, 500u, 250u, 0xAA0000u);
            // Graphics::drawEllipse  ((Window::WIDTH - 500u) / 2u, (Window::HEIGHT - 250u) / 2u, 500u, 250u, 0xCCCCCCu);

            // [Spline]
            Graphics::drawSpline(50u , 400u, 150u, 100u, Graphics::LINEAR   , 0xFFFF00u);
            Graphics::drawSpline(200u, 400u, 200u, 100u, Graphics::QUADRATIC, 300u, 250u, 0xFF00FFu);
            Graphics::drawSpline(350u, 400u, 550u, 100u, Graphics::CUBIC    , 550u, 400u, 350u, 100u, 0x00FFFFu);
            Graphics::drawSpline(650u, 400u, 950u, 400u, 3u                 , 650u, 100u, 950u, 100u, 800u, 400u, 0xF0F0F0u);

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
