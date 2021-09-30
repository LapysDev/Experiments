/* ... --> advapi32.lib, gdi32.lib, kernel32.lib, shell32.lib, user32.lib */
/* Definition > ... */
#undef UNICODE

/* Import */
// : [C Standard Library]
#include <stdbool.h> // Standard Boolean
#include <stdint.h>  // Standard Integers

// : [C++ Standard Library]
#include <cstdarg> // C Standard Arguments
#include <cstdio>
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
  static uint8_t const CUBIC = 2u, QUADRATIC = 1u, LINEAR = 0u;

  // ...
  namespace Transform {
    void rotate   (uint16_t const, uint16_t const, uint16_t const, uint16_t const, float const, DWORD const);
    void scale    (uint16_t const, uint16_t const, uint16_t const, uint16_t const, float const, DWORD const);
    void skew     (uint16_t const, uint16_t const, uint16_t const, uint16_t const, float const, DWORD const);
    void translate(uint16_t const, uint16_t const, uint16_t const, uint16_t const, float const, DWORD const);
  }

  void drawCircle   (void (*const)(uint16_t, uint16_t, uint16_t, uint16_t, float, DWORD), uint16_t const, uint16_t const, uint16_t, DWORD const, float const);
  void drawEllipse  (void (*const)(uint16_t, uint16_t, uint16_t, uint16_t, float, DWORD), uint16_t const, uint16_t const, uint16_t, uint16_t, DWORD const, float const);
  void drawLine     (void (*const)(uint16_t, uint16_t, uint16_t, uint16_t, float, DWORD), uint16_t const, uint16_t const, uint16_t const, uint16_t const, DWORD const, float const);
  void drawRectangle(void (*const)(uint16_t, uint16_t, uint16_t, uint16_t, float, DWORD), uint16_t const, uint16_t const, uint16_t const, uint16_t const, DWORD const, float const);
  void drawSpline   (void (*const)(uint16_t, uint16_t, uint16_t, uint16_t, float, DWORD), uint16_t, uint16_t, uint16_t, uint16_t, uint8_t, std::va_list);
  void drawSpline   (void (*const function)(uint16_t, uint16_t, uint16_t, uint16_t, float, DWORD), uint16_t const xOrigin, uint16_t const yOrigin, uint16_t const xTarget, uint16_t const yTarget, uint8_t const degree, ...) { std::va_list arguments; va_start(arguments, degree); return Graphics::drawSpline(function, xOrigin, yOrigin, xTarget, yTarget, degree, arguments); }
  void drawSquare   (void (*const)(uint16_t, uint16_t, uint16_t, uint16_t, float, DWORD), uint16_t const, uint16_t const, uint16_t const, DWORD const, float const);
  void putPixel(uint16_t const, uint16_t const, uint16_t const, uint16_t const, float const, DWORD const);

  void drawCircle   (uint16_t const x, uint16_t const y, uint16_t radius, DWORD const color, float const value) { return Graphics::drawCircle(&Graphics::putPixel, x, y, radius, color, value); }
  void drawEllipse  (uint16_t const x, uint16_t const y, uint16_t width, uint16_t height, DWORD const color, float const value) { return Graphics::drawEllipse(&Graphics::putPixel, x, y, width, height, color, value); }
  void drawLine     (uint16_t const xOrigin, uint16_t const yOrigin, uint16_t const xTarget, uint16_t const yTarget, DWORD const color, float const value) { return Graphics::drawLine(&Graphics::putPixel, xOrigin, yOrigin, xTarget, yTarget, color, value); }
  void drawRectangle(uint16_t const x, uint16_t const y, uint16_t const width, uint16_t const height, DWORD const color, float const value) { return Graphics::drawRectangle(&Graphics::putPixel, x, y, width, height, color, value); }
  void drawSpline   (uint16_t const xOrigin, uint16_t const yOrigin, uint16_t const xTarget, uint16_t const yTarget, uint8_t const degree, std::va_list arguments) { return Graphics::drawSpline(&Graphics::putPixel, xOrigin, yOrigin, xTarget, yTarget, degree, arguments); }
  void drawSpline   (uint16_t const xOrigin, uint16_t const yOrigin, uint16_t const xTarget, uint16_t const yTarget, uint8_t const degree, ...) { std::va_list arguments; va_start(arguments, degree); return Graphics::drawSpline(xOrigin, yOrigin, xTarget, yTarget, degree, arguments); }
  void drawSquare   (uint16_t const x, uint16_t const y, uint16_t const size, DWORD const color, float const value) { return Graphics::drawSquare(&Graphics::putPixel, x, y, size, color, value); }
  void putPixel(uint16_t const x, uint16_t const y, DWORD const color) { Graphics::putPixel(0u, 0u, x, y, 0.0f, color); }
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
void Graphics::drawCircle(void (*const function)(uint16_t, uint16_t, uint16_t, uint16_t, float, DWORD), uint16_t const xOrigin, uint16_t const yOrigin, uint16_t radius, DWORD const color, float const value) {
  uint16_t x = 0u;
  uint16_t y = radius / 2u;

  radius /= 2u;
  while (true) {
    function(xOrigin, yOrigin, xOrigin + (radius + x), yOrigin + (radius + y), value, color);
    function(xOrigin, yOrigin, xOrigin + (radius + x), yOrigin + (radius - y), value, color);
    function(xOrigin, yOrigin, xOrigin + (radius - x), yOrigin + (radius + y), value, color);
    function(xOrigin, yOrigin, xOrigin + (radius - x), yOrigin + (radius - y), value, color);

    // ...
    if (x == radius || y == 0u) break;

    if ((radius * radius) > (((x + 1u) * (x + 1u)) + ((y + 0u) * (y + 0u)))) { ++x; continue; }
    if ((radius * radius) > (((x + 0u) * (x + 0u)) + ((y - 1u) * (y - 1u)))) { --y; continue; }
    if ((radius * radius) > (((x + 1u) * (x + 1u)) + ((y - 1u) * (y - 1u)))) { ++x; --y; }
  }
}

void Graphics::drawEllipse(void (*const function)(uint16_t, uint16_t, uint16_t, uint16_t, float, DWORD), uint16_t const xOrigin, uint16_t const yOrigin, uint16_t width, uint16_t height, DWORD const color, float const value) {
  uint16_t x = 0u;
  uint16_t y = height / 2u;

  height /= 2u; width /= 2u;
  while (true) {
    function(xOrigin, yOrigin, xOrigin + (width + x), yOrigin + (height + y), value, color);
    function(xOrigin, yOrigin, xOrigin + (width + x), yOrigin + (height - y), value, color);
    function(xOrigin, yOrigin, xOrigin + (width - x), yOrigin + (height + y), value, color);
    function(xOrigin, yOrigin, xOrigin + (width - x), yOrigin + (height - y), value, color);

    // ...
    if (x == width || y == 0u) break;

    if ((height * width) > (((height * (x + 1u) * (x + 1u)) / width) + ((width * (y + 0u) * (y + 0u)) / height))) { ++x; continue; }
    if ((height * width) > (((height * (x + 0u) * (x + 0u)) / width) + ((width * (y - 1u) * (y - 1u)) / height))) { --y; continue; }
    if ((height * width) > (((height * (x + 1u) * (x + 1u)) / width) + ((width * (y - 1u) * (y - 1u)) / height))) { ++x; --y; }
  }
}

void Graphics::drawLine(void (*const function)(uint16_t, uint16_t, uint16_t, uint16_t, float, DWORD), uint16_t const xOrigin, uint16_t const yOrigin, uint16_t const xTarget, uint16_t const yTarget, DWORD const color, float const value) {
  uint16_t x = xOrigin;
  uint16_t y = yOrigin;
  uint16_t const xDistance = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget;
  uint16_t const yDistance = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;
  uint16_t xSlopeInterval = 0u;
  uint16_t ySlopeInterval = 0u;

  uint16_t const slope = xDistance > yDistance ? xDistance : yDistance;

  // ...
  while ((x != xTarget || xOrigin == xTarget) && (y != yTarget || yOrigin == yTarget)) {
    if (slope <= xSlopeInterval) { xSlopeInterval -= slope; xOrigin < xTarget ? ++x : --x; }
    if (slope <= ySlopeInterval) { ySlopeInterval -= slope; yOrigin < yTarget ? ++y : --y; }

    xSlopeInterval += xDistance;
    ySlopeInterval += yDistance;
    function(xOrigin, yOrigin, x, y, value, color);
  }
}

void Graphics::drawRectangle(void (*const function)(uint16_t, uint16_t, uint16_t, uint16_t, float, DWORD), uint16_t const xOrigin, uint16_t const yOrigin, uint16_t const width, uint16_t const height, DWORD const color, float const value) {
  for (uint16_t iterator = width + 1u; iterator--; ) {
    function(xOrigin, yOrigin, xOrigin + iterator, yOrigin + height, value, color);
    function(xOrigin, yOrigin, xOrigin + iterator, yOrigin + 0u    , value, color);
  }

  for (uint16_t iterator = height + 1u; iterator--; ) {
    function(xOrigin, yOrigin, xOrigin + width, yOrigin + iterator, value, color);
    function(xOrigin, yOrigin, xOrigin + 0u   , yOrigin + iterator, value, color);
  }
}

void Graphics::drawSpline(void (*const function)(uint16_t, uint16_t, uint16_t, uint16_t, float, DWORD), uint16_t xOrigin, uint16_t yOrigin, uint16_t xTarget, uint16_t yTarget, uint8_t degree, std::va_list arguments) {
  DWORD color;
  uint16_t const totalSamples = 0u == degree ? 1u : 50u;
  float value;
  uint16_t xControl[126], xSubcontrol[126];
  uint16_t yControl[126], ySubcontrol[126];
  uint16_t xFormer = xOrigin;
  uint16_t yFormer = yOrigin;

  // ...
  for (uint8_t iterator = 0u; degree != iterator; ++iterator) {
    xControl[iterator + 1u] = static_cast<uint16_t>(va_arg(arguments, unsigned int));
    yControl[iterator + 1u] = static_cast<uint16_t>(va_arg(arguments, unsigned int));
  }

  color = va_arg(arguments, DWORD);
  value = static_cast<double>(va_arg(arguments, double));
  degree += 2u;
  xControl[0] = xOrigin; xControl[degree - 1u] = xTarget;
  yControl[0] = yOrigin; yControl[degree - 1u] = yTarget;

  va_end(arguments);

  for (uint16_t currentSamples = totalSamples; currentSamples--; ) {
    uint16_t slope;
    uint16_t x;
    uint16_t y;
    uint16_t xDistance;
    uint16_t yDistance;
    uint16_t xSlopeInterval;
    uint16_t ySlopeInterval;

    // ...
    for (uint8_t iterator = degree; iterator--; ) {
      xSubcontrol[iterator] = xControl[iterator];
      ySubcontrol[iterator] = yControl[iterator];
    }

    for (uint8_t subdegree = degree; --subdegree; )
    for (uint8_t iterator = 0u; iterator != subdegree; ++iterator) {
      uint16_t totalLength;

      // ...
      xTarget = xSubcontrol[iterator + 1u];
      yTarget = ySubcontrol[iterator + 1u];
      xOrigin = xSubcontrol[iterator + 0u];
      yOrigin = ySubcontrol[iterator + 0u];

      xSlopeInterval = 0u;
      ySlopeInterval = 0u;
      xDistance = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget;
      yDistance = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;
      x = xOrigin;
      y = yOrigin;

      totalLength = xDistance + yDistance;
      slope = xDistance > yDistance ? xDistance : yDistance;

      // ...
      for (uint16_t currentLength = totalLength; (x != xTarget || xOrigin == xTarget) && (y != yTarget || yOrigin == yTarget); ) {
        if (slope <= xSlopeInterval) { --currentLength; xSlopeInterval -= slope; xOrigin < xTarget ? ++x : --x; }
        if (slope <= ySlopeInterval) { --currentLength; ySlopeInterval -= slope; yOrigin < yTarget ? ++y : --y; }

        xSlopeInterval += xDistance;
        ySlopeInterval += yDistance;
        if (static_cast<float>(currentLength) / static_cast<float>(totalLength) <= static_cast<float>(currentSamples) / static_cast<float>(totalSamples)) {
          xSubcontrol[iterator] = x;
          ySubcontrol[iterator] = y;
          break;
        }
      }
    }

    // ...
    xTarget = xFormer;
    yTarget = yFormer;
    xOrigin = x;
    yOrigin = y;

    xSlopeInterval = 0u;
    ySlopeInterval = 0u;
    xFormer = x;
    yFormer = y;
    xDistance = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget;
    yDistance = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;

    slope = xDistance > yDistance ? xDistance : yDistance;

    // ...
    while ((x != xTarget || xOrigin == xTarget) && (y != yTarget || yOrigin == yTarget)) {
      if (slope <= xSlopeInterval) { xSlopeInterval -= slope; xOrigin < xTarget ? ++x : --x; }
      if (slope <= ySlopeInterval) { ySlopeInterval -= slope; yOrigin < yTarget ? ++y : --y; }

      xSlopeInterval += xDistance;
      ySlopeInterval += yDistance;
      function(*xControl, *yControl, x, y, value, color);
    }
  }
}

void Graphics::drawSquare(void (*const function)(uint16_t, uint16_t, uint16_t, uint16_t, float, DWORD), uint16_t const xOrigin, uint16_t const yOrigin, uint16_t const size, DWORD const color, float const value) {
  for (uint16_t iterator = size + 1u; iterator--; ) {
    function(xOrigin, yOrigin, xOrigin + size    , yOrigin + iterator, value, color);
    function(xOrigin, yOrigin, xOrigin + 0u      , yOrigin + iterator, value, color);
    function(xOrigin, yOrigin, xOrigin + iterator, yOrigin + size    , value, color);
    function(xOrigin, yOrigin, xOrigin + iterator, yOrigin + 0u      , value, color);
  }
}

void Graphics::putPixel(uint16_t const, uint16_t const, uint16_t const x, uint16_t const y, float const, DWORD const color) {
  if (x >= Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth || y >= Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmHeight) return;
  Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY[x + (y * Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth)] = 0xFF000000u | color;
}

#include <cmath>
void Graphics::Transform::rotate(uint16_t xAnchor, uint16_t yAnchor, uint16_t x, uint16_t y, float angle, DWORD const color) {
  angle *= 245850922.0f / 78256779.0f;
  angle /= 180.0f;

  Graphics::putPixel(x, y, color);
  Graphics::putPixel(
    xAnchor + ((::cosf(angle) * (x - xAnchor)) - (::sinf(angle) * (y - yAnchor))),
    yAnchor + ((::sinf(angle) * (x - xAnchor)) + (::cosf(angle) * (y - yAnchor))),
    0xFF00FFu
  );
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
  ::GetModuleFileName(static_cast<HMODULE>(NULL), Program::FILE_NAME, MAX_PATH);

  Window::BACKGROUND = ::GetSysColorBrush(COLOR_WINDOW);
  Window::CURSOR     = ::LoadCursor(static_cast<HINSTANCE>(NULL), IDC_ARROW); // --> static_cast<HCURSOR>(::LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED))
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

    Window::HANDLE = ::CreateWindowEx(Window::STYLE_EXTENSION, Window::CLASS_NAME, Window::TITLE, Window::STYLE, Window::LEFT, Window::TOP, Window::WIDTH, Window::HEIGHT, NULL, static_cast<HMENU>(NULL), Program::HANDLE, reinterpret_cast<LPVOID>(static_cast<LPARAM>(Window::APPEARANCE)));
    if (NULL == Window::HANDLE) TERMINATE();

    for (BOOL available = false; WM_QUIT != Program::THREAD_MESSAGE.message; ) {
      available = ::PeekMessage(&Program::THREAD_MESSAGE, static_cast<HWND>(NULL), 0x0u, 0x0u, PM_REMOVE);
      if (FALSE != available) ::DispatchMessage(&Program::THREAD_MESSAGE);

      Program::EXIT_CODE = Program::THREAD_MESSAGE.wParam;
    }
  }
}

/* : Update */
static float SUS = 0.0f;
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
      ::ShowWindow(windowHandle, static_cast<long>(static_cast<int>(reinterpret_cast<intptr_t>(creationParameter))));
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
      SUS = SUS != 360.0f ? SUS + 1.0f : 0.0f;
      std::printf("[...]: %f" "\r\n", SUS);
    } break;
    case WM_ERASEBKGND: return 0x1L;
    case WM_PAINT: {
      // // [Line]
      // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, 0u                , 0u                 , 0x606060u, 0.0f);
      // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, 0u                , Window::HEIGHT - 1u, 0x606060u, 0.0f);
      // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, 0u                , Window::HEIGHT / 2u, 0x606060u, 0.0f);
      // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, Window::WIDTH / 2u, 0u                 , 0x606060u, 0.0f);
      // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, Window::WIDTH - 1u, 0u                 , 0x606060u, 0.0f);
      // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, Window::WIDTH - 1u, Window::HEIGHT - 1u, 0x606060u, 0.0f);
      // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, Window::WIDTH - 1u, Window::HEIGHT / 2u, 0x606060u, 0.0f);
      // Graphics::drawLine(Window::WIDTH / 2u, Window::HEIGHT / 2u, Window::WIDTH / 2u, Window::HEIGHT - 1u, 0x606060u, 0.0f);
      // Graphics::drawLine(std::rand() % Window::WIDTH, std::rand() % Window::HEIGHT, std::rand() % Window::WIDTH, std::rand() % Window::HEIGHT, 0x0F0F0Fu, 0.0f);

      // // [Circle, Ellipse, Rectangle, Square]
      // Graphics::drawSquare((Window::WIDTH - 200u) / 2u, (Window::HEIGHT - 200u) / 2u, 200u, 0xAA0000u, 0.0f);
      // Graphics::drawCircle((Window::WIDTH - 200u) / 2u, (Window::HEIGHT - 200u) / 2u, 200u, 0xCCCCCCu, 0.0f);
      // Graphics::drawCircle((Window::WIDTH - 200u) / 2u, (Window::HEIGHT - 200u) / 2u, 200u, 0xCCCCCCu, 0.0f);

      // Graphics::drawRectangle((Window::WIDTH - 500u) / 2u, (Window::HEIGHT - 250u) / 2u, 500u, 250u, 0xAA0000u, 0.0f);
      // Graphics::drawEllipse  ((Window::WIDTH - 500u) / 2u, (Window::HEIGHT - 250u) / 2u, 500u, 250u, 0xCCCCCCu, 0.0f);

      // // [Spline]
      // Graphics::drawSpline(1u, Window::HEIGHT - 1u, Window::WIDTH - 1u, Window::HEIGHT - 1u, Graphics::LINEAR, 0x009900u, 0.0f);
      // Graphics::drawSpline(1u, Window::HEIGHT - 1u, Window::WIDTH - 1u, Window::HEIGHT - 1u, Graphics::QUADRATIC, Window::WIDTH / 2u, 0u, 0x009900u, 0.0f);
      // Graphics::drawSpline(1u, Window::HEIGHT - 1u, Window::WIDTH - 1u, Window::HEIGHT - 1u, Graphics::CUBIC, 0u, 0u, Window::WIDTH - 1u, 0u, 0x009900u, 0.0f);
      // Graphics::drawSpline(1u, Window::HEIGHT - 1u, Window::WIDTH - 1u, Window::HEIGHT - 1u, 3u, 0u, 0u, Window::WIDTH / 2u, 0u, Window::WIDTH - 1u, 0u, 0x009900u, 0.0f);

      // [...]
      for (uint16_t y = Window::HEIGHT; y--; )
      for (uint16_t x = Window::WIDTH; x--; ) {
        Graphics::putPixel(x, y, 0x000000u);
      }
      // Graphics::drawLine(&Graphics::putPixel, 300u, 200u, 300u, 300u, 0x0000FFu, 0.0f);
      // Graphics::drawLine(&Graphics::Transform::rotate, 300u, 200u, 400u, 200u, 0x00FF00u,  0.0f);

      // Graphics::drawLine(&Graphics::putPixel, 300u, 275u, 300u, 375u, 0x0000FFu, SUS);
      // Graphics::drawLine(&Graphics::Transform::rotate, 300u, 275u, 400u, 275u, 0x0000FFu, SUS);

      // Graphics::drawLine(&Graphics::putPixel, 300u, 350u, 300u, 450u, 0x0000FFu, 90.0f);
      // Graphics::drawLine(&Graphics::Transform::rotate, 300u, 350u, 400u, 350u, 0x00FFFFu, 90.0f);
      // Graphics::drawRectangle(&Graphics::Transform::rotate, 400u, 200u, 100u, 200u, 0x0000FFu, 45.0f);
      Graphics::drawSquare(&Graphics::putPixel, 400u, 200u, 150u, 0x0000FFu, SUS);
      Graphics::drawSquare(&Graphics::Transform::rotate, 400u, 200u, 150u, 0x0000FFu, SUS);

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
