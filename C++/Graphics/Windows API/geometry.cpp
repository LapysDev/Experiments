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
  static uint8_t const CUBIC = 2u, QUADRATIC = 1u, LINEAR = 0u;

  // ...
  void drawCircle   (uint16_t const, uint16_t const, uint16_t, DWORD const);
  void drawEllipse  (uint16_t const, uint16_t const, uint16_t, uint16_t, DWORD const);
  void drawLine     (uint16_t const, uint16_t const, uint16_t const, uint16_t const, DWORD const);
  void drawRectangle(uint16_t const, uint16_t const, uint16_t const, uint16_t const, DWORD const);
  void drawSpline   (uint16_t const, uint16_t const, uint16_t const, uint16_t const, uint8_t, ...);
  void drawSquare   (uint16_t const, uint16_t const, uint16_t const, DWORD const);

  void putPixel(uint16_t const, uint16_t const, DWORD const);
  void rotateBy(uint16_t const, uint16_t const, float const);
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
void Graphics::drawCircle(uint16_t const xOrigin, uint16_t const yOrigin, uint16_t radius, DWORD const color) {
  uint16_t x = 0u;
  uint16_t y = radius / 2u;

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

void Graphics::drawEllipse(uint16_t const xOrigin, uint16_t const yOrigin, uint16_t width, uint16_t height, DWORD const color) {
  uint16_t x = 0u;
  uint16_t y = height / 2u;

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

void Graphics::drawLine(uint16_t const xOrigin, uint16_t const yOrigin, uint16_t const xTarget, uint16_t const yTarget, DWORD const color) {
  uint16_t xSlopeInterval = 0u;
  uint16_t ySlopeInterval = 0u;

  uint16_t const xDistance = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget;
  uint16_t const yDistance = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;

  uint16_t x = xOrigin;
  uint16_t y = yOrigin;

  uint16_t const slope = xDistance > yDistance ? xDistance : yDistance;

  // ...
  while ((x != xTarget || xOrigin == xTarget) && (y != yTarget || yOrigin == yTarget)) {
    if (slope <= xSlopeInterval) { xSlopeInterval -= slope; xOrigin < xTarget ? ++x : --x; }
    if (slope <= ySlopeInterval) { ySlopeInterval -= slope; yOrigin < yTarget ? ++y : --y; }

    xSlopeInterval += xDistance;
    ySlopeInterval += yDistance;
    Graphics::putPixel(x, y, color);
  }
}

void Graphics::drawRectangle(uint16_t const xOrigin, uint16_t const yOrigin, uint16_t const width, uint16_t const height, DWORD const color) {
  for (uint16_t iterator = height; iterator--; ) {
    Graphics::putPixel(xOrigin + 0u   , yOrigin + iterator, color);
    Graphics::putPixel(xOrigin + width, yOrigin + iterator, color);
  }

  for (uint16_t iterator = width; iterator--; ) {
    Graphics::putPixel(xOrigin + iterator, yOrigin + 0u    , color);
    Graphics::putPixel(xOrigin + iterator, yOrigin + height, color);
  }
}

void Graphics::drawSpline(uint16_t const xOrigin, uint16_t const yOrigin, uint16_t const xTarget, uint16_t const yTarget, uint8_t count, ...) {
  std::va_list arguments;
  DWORD color;
  uint16_t maximumLength = 0u;
  uint16_t maximumRatio;
  uint16_t xControl[126];
  uint16_t yControl[126];

  va_start(arguments, count);
    for (uint8_t iterator = 0u; count != iterator; ++iterator) {
      xControl[iterator + 1u] = static_cast<uint16_t>(va_arg(arguments, unsigned int));
      yControl[iterator + 1u] = static_cast<uint16_t>(va_arg(arguments, unsigned int));
    }

    color = va_arg(arguments, DWORD);
    count += 2u;
    xControl[0] = xOrigin; xControl[count - 1u] = xTarget;
    yControl[0] = yOrigin; yControl[count - 1u] = yTarget;
  va_end(arguments);

  // ...
  for (uint8_t iterator = count; --iterator; ) {
    uint16_t const xDistance = xControl[iterator] < xControl[iterator - 1u] ? xControl[iterator - 1u] - xControl[iterator] : xControl[iterator] - xControl[iterator - 1u];
    uint16_t const yDistance = yControl[iterator] < yControl[iterator - 1u] ? yControl[iterator - 1u] - yControl[iterator] : yControl[iterator] - yControl[iterator - 1u];

    Graphics::drawLine(xControl[iterator], yControl[iterator], xControl[iterator - 1u], yControl[iterator - 1u], 0xFF0000u);
    if (maximumLength < xDistance + yDistance)
    maximumLength = xDistance + yDistance;
  }

  for (maximumRatio = maximumLength; maximumRatio; --maximumRatio) {
    uint16_t x, xRecent;
    uint16_t y, yRecent;
    uint16_t xSubcontrol[126] = {xControl[0], xControl[1], xControl[2], xControl[3], xControl[4], xControl[5], xControl[6], xControl[7], xControl[8], xControl[9], xControl[10], xControl[11], xControl[12], xControl[13], xControl[14], xControl[15], xControl[16], xControl[17], xControl[18], xControl[19], xControl[20], xControl[21], xControl[22], xControl[23], xControl[24], xControl[25], xControl[26], xControl[27], xControl[28], xControl[29], xControl[30], xControl[31], xControl[32], xControl[33], xControl[34], xControl[35], xControl[36], xControl[37], xControl[38], xControl[39], xControl[40], xControl[41], xControl[42], xControl[43], xControl[44], xControl[45], xControl[46], xControl[47], xControl[48], xControl[49], xControl[50], xControl[51], xControl[52], xControl[53], xControl[54], xControl[55], xControl[56], xControl[57], xControl[58], xControl[59], xControl[60], xControl[61], xControl[62], xControl[63], xControl[64], xControl[65], xControl[66], xControl[67], xControl[68], xControl[69], xControl[70], xControl[71], xControl[72], xControl[73], xControl[74], xControl[75], xControl[76], xControl[77], xControl[78], xControl[79], xControl[80], xControl[81], xControl[82], xControl[83], xControl[84], xControl[85], xControl[86], xControl[87], xControl[88], xControl[89], xControl[90], xControl[91], xControl[92], xControl[93], xControl[94], xControl[95], xControl[96], xControl[97], xControl[98], xControl[99], xControl[100], xControl[101], xControl[102], xControl[103], xControl[104], xControl[105], xControl[106], xControl[107], xControl[108], xControl[109], xControl[110], xControl[111], xControl[112], xControl[113], xControl[114], xControl[115], xControl[116], xControl[117], xControl[118], xControl[119], xControl[120], xControl[121], xControl[122], xControl[123], xControl[124], xControl[125]};
    uint16_t ySubcontrol[126] = {yControl[0], yControl[1], yControl[2], yControl[3], yControl[4], yControl[5], yControl[6], yControl[7], yControl[8], yControl[9], yControl[10], yControl[11], yControl[12], yControl[13], yControl[14], yControl[15], yControl[16], yControl[17], yControl[18], yControl[19], yControl[20], yControl[21], yControl[22], yControl[23], yControl[24], yControl[25], yControl[26], yControl[27], yControl[28], yControl[29], yControl[30], yControl[31], yControl[32], yControl[33], yControl[34], yControl[35], yControl[36], yControl[37], yControl[38], yControl[39], yControl[40], yControl[41], yControl[42], yControl[43], yControl[44], yControl[45], yControl[46], yControl[47], yControl[48], yControl[49], yControl[50], yControl[51], yControl[52], yControl[53], yControl[54], yControl[55], yControl[56], yControl[57], yControl[58], yControl[59], yControl[60], yControl[61], yControl[62], yControl[63], yControl[64], yControl[65], yControl[66], yControl[67], yControl[68], yControl[69], yControl[70], yControl[71], yControl[72], yControl[73], yControl[74], yControl[75], yControl[76], yControl[77], yControl[78], yControl[79], yControl[80], yControl[81], yControl[82], yControl[83], yControl[84], yControl[85], yControl[86], yControl[87], yControl[88], yControl[89], yControl[90], yControl[91], yControl[92], yControl[93], yControl[94], yControl[95], yControl[96], yControl[97], yControl[98], yControl[99], yControl[100], yControl[101], yControl[102], yControl[103], yControl[104], yControl[105], yControl[106], yControl[107], yControl[108], yControl[109], yControl[110], yControl[111], yControl[112], yControl[113], yControl[114], yControl[115], yControl[116], yControl[117], yControl[118], yControl[119], yControl[120], yControl[121], yControl[122], yControl[123], yControl[124], yControl[125]};

    for (uint8_t subcount = count; subcount; ) {
      if (0u == --subcount) {
        Graphics::putPixel(x, y, color);
        // x == xRecent && y == yRecent ? Graphics::putPixel(x, y, color) : Graphics::drawLine(xRecent, yRecent, x, y, color);
      }

      else for (uint8_t iterator = 0u; iterator != subcount; ++iterator) {
        uint16_t const xTarget = xSubcontrol[iterator + 1u];
        uint16_t const yTarget = ySubcontrol[iterator + 1u];
        uint16_t const xOrigin = xSubcontrol[iterator + 0u];
        uint16_t const yOrigin = ySubcontrol[iterator + 0u];

        uint16_t xSlopeInterval = 0u;
        uint16_t ySlopeInterval = 0u;
        uint16_t const xDistance = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget;
        uint16_t const yDistance = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;

        uint16_t ratio;
        uint16_t const slope = xDistance > yDistance ? xDistance : yDistance;
        uint16_t const length = xDistance + yDistance;

        // ...
        x = xOrigin; xRecent = x;
        y = yOrigin; yRecent = y;

        while ((x != xTarget || xOrigin == xTarget) && (y != yTarget || yOrigin == yTarget)) {
          if (slope <= xSlopeInterval) { xSlopeInterval -= slope; xRecent = xOrigin < xTarget ? x++ : x--; }
          if (slope <= ySlopeInterval) { ySlopeInterval -= slope; yRecent = yOrigin < yTarget ? y++ : y--; }

          ratio = (x < xTarget ? xTarget - x : x - xTarget) + (y < yTarget ? yTarget - y : y - yTarget);
          xSlopeInterval += xDistance;
          ySlopeInterval += yDistance;

          if (maximumLength - maximumRatio == ((length - ratio) * maximumLength) / length) {
            xSubcontrol[iterator] = x;
            ySubcontrol[iterator] = y;
            break;
          }

          else if (maximumLength - maximumRatio < ((length - ratio) * maximumLength) / length) {
            xSubcontrol[iterator] = xRecent;
            ySubcontrol[iterator] = yRecent;
            break;
          }
        }
      }
    }
  }
}

void Graphics::drawSquare(uint16_t const xOrigin, uint16_t const yOrigin, uint16_t const size, DWORD const color) {
  for (uint16_t iterator = size; iterator--; ) {
    Graphics::putPixel(xOrigin + 0u      , yOrigin + iterator, color);
    Graphics::putPixel(xOrigin + iterator, yOrigin + 0u      , color);
    Graphics::putPixel(xOrigin + iterator, yOrigin + size    , color);
    Graphics::putPixel(xOrigin + size    , yOrigin + iterator, color);
  }
}

void Graphics::putPixel(uint16_t const x, uint16_t const y, DWORD const color) {
  Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY[x + (y * Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth)] = 0xFF000000u | color;
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

    Window::HANDLE = ::CreateWindowEx(Window::STYLE_EXTENSION, Window::CLASS_NAME, Window::TITLE, Window::STYLE, Window::LEFT, Window::TOP, Window::WIDTH, Window::HEIGHT, NULL, static_cast<HMENU>(NULL), Program::HANDLE, reinterpret_cast<LPVOID>(static_cast<LPARAM>(Window::APPEARANCE)));
    if (NULL == Window::HANDLE) TERMINATE();

    for (bool available = false; WM_QUIT != Program::THREAD_MESSAGE.message; ) {
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
