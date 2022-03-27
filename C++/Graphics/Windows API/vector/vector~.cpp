/* ... --> advapi32.lib, gdi32.lib, kernel32.lib, shell32.lib, user32.lib */
/* Definition > ... */
#undef UNICODE

/* Import */
// : [C Standard Library]
#include <stdbool.h> // Standard Boolean
#include <stdint.h>  // Standard Integers

// : [C++ Standard Library]
#include <cmath>   // C Mathematics
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
union Graphics {
  private:
    // ...
    enum { LINEAR = 0u, QUADRATIC = 1u, CUBIC = 2u };

    // ...
    static void drawCircle   (bool (*const)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const, uint_least16_t const, uint_least16_t const, uint_least16_t, DWORD const);
    static void drawEllipse  (bool (*const)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const, uint_least16_t const, uint_least16_t const, uint_least16_t, uint_least16_t, DWORD const);
    static void drawLine     (bool (*const)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const, uint_least16_t const, uint_least16_t const, uint_least16_t const, uint_least16_t const, DWORD const);
    static void drawRectangle(bool (*const)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const, uint_least16_t const, uint_least16_t const, uint_least16_t const, uint_least16_t const, DWORD const);
    static void drawSpline   (bool (*const)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const, uint_least16_t, uint_least16_t, uint_least16_t, uint_least16_t, uint_least8_t);
    static void drawSquare   (bool (*const)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const, uint_least16_t const, uint_least16_t const, uint_least16_t const, DWORD const);

    static void putPixel(bool (*const* const)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const, uint_least16_t const, uint_least16_t const, uint_least16_t const, uint_least16_t const, DWORD const);
    static void putPixel(bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const values, uint_least16_t const xOrigin, uint_least16_t const yOrigin, uint_least16_t const x, uint_least16_t const y, DWORD const color) { Graphics::putPixel(&function, values, xOrigin, yOrigin, x, y, color); }

  public:
    union Transform {
      static bool rotate   (uint_least16_t (*const)[2], uint_least16_t const, uint_least16_t const, float const);
      static bool scale    (uint_least16_t (*const)[2], uint_least16_t const, uint_least16_t const, float const, float const);
      static bool skew     (uint_least16_t (*const)[2], uint_least16_t const, uint_least16_t const, float const, float const);
      static bool translate(uint_least16_t (*const)[2], int_least32_t const, int_least32_t const);
    };

    // ...
    static void clear();

    static void drawCircle   (bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), uint_least16_t const x, uint_least16_t const y, uint_least16_t const radius, DWORD const color, ...) { std::va_list values; va_start(values, color); Graphics::drawCircle(function, &values, x, y, radius, color); va_end(values); }
    static void drawCircle   (uint_least16_t const x, uint_least16_t const y, uint_least16_t const radius, DWORD const color) { Graphics::drawCircle(static_cast<bool (*)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...)>(NULL), NULL, x, y, radius, color); }

    static void drawEllipse  (bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), uint_least16_t const x, uint_least16_t const y, uint_least16_t const width, uint_least16_t const height, DWORD const color, ...) { std::va_list values; va_start(values, color); Graphics::drawEllipse(function, &values, x, y, width, height, color); va_end(values); }
    static void drawEllipse  (uint_least16_t const x, uint_least16_t const y, uint_least16_t const width, uint_least16_t const height, DWORD const color) { Graphics::drawEllipse(static_cast<bool (*)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...)>(NULL), NULL, x, y, width, height, color); }

    static void drawLine     (bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), uint_least16_t const xOrigin, uint_least16_t const yOrigin, uint_least16_t const xTarget, uint_least16_t const yTarget, DWORD const color, ...) { std::va_list values; va_start(values, color); Graphics::drawLine(function, &values, xOrigin, yOrigin, xTarget, yTarget, color); va_end(values); }
    static void drawLine     (uint_least16_t const xOrigin, uint_least16_t const yOrigin, uint_least16_t const xTarget, uint_least16_t const yTarget, DWORD const color) { Graphics::drawLine(static_cast<bool (*)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...)>(NULL), NULL, xOrigin, yOrigin, xTarget, yTarget, color); }

    static void drawPoint    (bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), uint_least16_t const x, uint_least16_t const y, DWORD const color, ...) { std::va_list values; va_start(values, color); Graphics::putPixel(&function, &values, x, y, x, y, color); va_end(values); }
    static void drawPoint    (uint_least16_t const x, uint_least16_t const y, DWORD const color) { Graphics::putPixel(static_cast<bool (*)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...)>(NULL), NULL, x, y, x, y, color); }

    static void drawRectangle(bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), uint_least16_t const x, uint_least16_t const y, uint_least16_t const width, uint_least16_t const height, DWORD const color, ...) { std::va_list values; va_start(values, color); Graphics::drawRectangle(function, &values, x, y, width, height, color); va_end(values); }
    static void drawRectangle(uint_least16_t const x, uint_least16_t const y, uint_least16_t const width, uint_least16_t const height, DWORD const color) { Graphics::drawRectangle(static_cast<bool (*)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...)>(NULL), NULL, x, y, width, height, color); }

    static void drawSpline   (bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), uint_least16_t const xOrigin, uint_least16_t const yOrigin, uint_least16_t const xTarget, uint_least16_t const yTarget, uint_least8_t const degree, ...) { std::va_list values; va_start(values, degree); Graphics::drawSpline(function, &values, xOrigin, yOrigin, xTarget, yTarget, degree); va_end(values); }
    static void drawSpline   (uint_least16_t const xOrigin, uint_least16_t const yOrigin, uint_least16_t const xTarget, uint_least16_t const yTarget, uint_least8_t const degree) { Graphics::drawSpline(static_cast<bool (*)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...)>(NULL), NULL, xOrigin, yOrigin, xTarget, yTarget, degree); }

    static void drawSquare   (bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), uint_least16_t const x, uint_least16_t const y, uint_least16_t const size, DWORD const color, ...) { std::va_list values; va_start(values, color); Graphics::drawSquare(function, &values, x, y, size, color); va_end(values); }
    static void drawSquare   (uint_least16_t const x, uint_least16_t const y, uint_least16_t const size, DWORD const color) { Graphics::drawSquare(static_cast<bool (*)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...)>(NULL), NULL, x, y, size, color); }

    static void parseFont(char const[]);
};

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
void Graphics::clear() {
  for (UINT32 *iterator = Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY + (Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmHeight * Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth); iterator-- != Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY; )
  *iterator ^= *iterator;
}

void Graphics::drawCircle(bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const values, uint_least16_t const xOrigin, uint_least16_t const yOrigin, uint_least16_t radius, DWORD const color) {
  uint_least16_t x = 0u;
  uint_least16_t y = radius / 2u;

  radius /= 2u;
  while (true) {
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + (radius + x), yOrigin + (radius + y), color);
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + (radius + x), yOrigin + (radius - y), color);
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + (radius - x), yOrigin + (radius + y), color);
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + (radius - x), yOrigin + (radius - y), color);

    // ...
    if (x == radius || y == 0u) break;

    if ((radius * radius) > (((x + 1u) * (x + 1u)) + ((y + 0u) * (y + 0u)))) { ++x; continue; }
    if ((radius * radius) > (((x + 0u) * (x + 0u)) + ((y - 1u) * (y - 1u)))) { --y; continue; }
    if ((radius * radius) > (((x + 1u) * (x + 1u)) + ((y - 1u) * (y - 1u)))) { ++x; --y; }
  }
}

void Graphics::drawEllipse(bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const values, uint_least16_t const xOrigin, uint_least16_t const yOrigin, uint_least16_t width, uint_least16_t height, DWORD const color) {
  uint_least16_t x = 0u;
  uint_least16_t y = height / 2u;

  height /= 2u; width /= 2u;
  while (true) {
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + (width + x), yOrigin + (height + y), color);
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + (width + x), yOrigin + (height - y), color);
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + (width - x), yOrigin + (height + y), color);
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + (width - x), yOrigin + (height - y), color);

    // ...
    if (x == width || y == 0u) break;

    if ((height * width) > (((height * (x + 1u) * (x + 1u)) / width) + ((width * (y + 0u) * (y + 0u)) / height))) { ++x; continue; }
    if ((height * width) > (((height * (x + 0u) * (x + 0u)) / width) + ((width * (y - 1u) * (y - 1u)) / height))) { --y; continue; }
    if ((height * width) > (((height * (x + 1u) * (x + 1u)) / width) + ((width * (y - 1u) * (y - 1u)) / height))) { ++x; --y; }
  }
}

void Graphics::drawLine(bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const values, uint_least16_t const xOrigin, uint_least16_t const yOrigin, uint_least16_t const xTarget, uint_least16_t const yTarget, DWORD const color) {
  uint_least16_t x = xOrigin;
  uint_least16_t y = yOrigin;
  uint_least16_t const xDistance = xOrigin < xTarget ? xTarget - xOrigin : xOrigin - xTarget;
  uint_least16_t const yDistance = yOrigin < yTarget ? yTarget - yOrigin : yOrigin - yTarget;
  uint_least16_t xSlopeInterval = 0u;
  uint_least16_t ySlopeInterval = 0u;

  uint_least16_t const slope = xDistance > yDistance ? xDistance : yDistance;

  // ...
  while ((x != xTarget || xOrigin == xTarget) && (y != yTarget || yOrigin == yTarget)) {
    if (slope <= xSlopeInterval) { xSlopeInterval -= slope; xOrigin < xTarget ? ++x : --x; }
    if (slope <= ySlopeInterval) { ySlopeInterval -= slope; yOrigin < yTarget ? ++y : --y; }

    xSlopeInterval += xDistance;
    ySlopeInterval += yDistance;
    Graphics::putPixel(&function, values, xOrigin, yOrigin, x, y, color);
  }
}

void Graphics::drawRectangle(bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const values, uint_least16_t const xOrigin, uint_least16_t const yOrigin, uint_least16_t const width, uint_least16_t const height, DWORD const color) {
  for (uint_least16_t iterator = width; iterator--; ) {
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + iterator, yOrigin + height, color);
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + iterator, yOrigin + 0u    , color);
  }

  for (uint_least16_t iterator = height; iterator--; ) {
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + width, yOrigin + iterator, color);
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + 0u   , yOrigin + iterator, color);
  }
}

void Graphics::drawSpline(bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const values, uint_least16_t xOrigin, uint_least16_t yOrigin, uint_least16_t xTarget, uint_least16_t yTarget, uint_least8_t degree) {
  DWORD color;
  uint_least16_t const totalSamples = 0u == degree ? 1u : 50u;
  uint_least16_t xControl[126], xSubcontrol[126];
  uint_least16_t yControl[126], ySubcontrol[126];
  uint_least16_t xFormer = xOrigin;
  uint_least16_t yFormer = yOrigin;

  // ...
  for (uint_least8_t iterator = 0u; degree != iterator; ++iterator) {
    xControl[iterator + 1u] = static_cast<uint_least16_t>(va_arg(*values, unsigned int));
    yControl[iterator + 1u] = static_cast<uint_least16_t>(va_arg(*values, unsigned int));
  }

  color = va_arg(*values, DWORD);
  degree += 2u;
  xControl[0] = xOrigin; xControl[degree - 1u] = xTarget;
  yControl[0] = yOrigin; yControl[degree - 1u] = yTarget;

  for (uint_least16_t currentSamples = totalSamples; currentSamples--; ) {
    uint_least16_t slope;
    uint_least16_t x;
    uint_least16_t y;
    uint_least16_t xDistance;
    uint_least16_t yDistance;
    uint_least16_t xSlopeInterval;
    uint_least16_t ySlopeInterval;

    // ...
    for (uint_least8_t iterator = degree; iterator--; ) {
      xSubcontrol[iterator] = xControl[iterator];
      ySubcontrol[iterator] = yControl[iterator];
    }

    for (uint_least8_t subdegree = degree; --subdegree; )
    for (uint_least8_t iterator = 0u; iterator != subdegree; ++iterator) {
      uint_least16_t totalLength;

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
      for (uint_least16_t currentLength = totalLength; (x != xTarget || xOrigin == xTarget) && (y != yTarget || yOrigin == yTarget); ) {
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
      Graphics::putPixel(&function, values, *xControl, *yControl, x, y, color);
    }
  }
}

void Graphics::drawSquare(bool (*const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const values, uint_least16_t const xOrigin, uint_least16_t const yOrigin, uint_least16_t const size, DWORD const color) {
  for (uint_least16_t iterator = size; iterator--; ) {
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + size    , yOrigin + iterator, color);
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + 0u      , yOrigin + iterator, color);
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + iterator, yOrigin + size    , color);
    Graphics::putPixel(&function, values, xOrigin, yOrigin, xOrigin + iterator, yOrigin + 0u      , color);
  }
}

void Graphics::parseFont(char const path[]) {
  static_cast<void>(path);
}

void Graphics::putPixel(bool (*const *const function)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, ...), std::va_list* const values, uint_least16_t const xOrigin, uint_least16_t const yOrigin, uint_least16_t const x, uint_least16_t const y, DWORD const color) {
  uint_least16_t coordinates[2] = {x, y};

  if (NULL == *function) {}
  else if (&Graphics::Transform::rotate    == *static_cast<bool (* const*)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, float)>       (static_cast<void const*>(function))) { if (false == Transform::rotate   (&coordinates, xOrigin, yOrigin, static_cast<float>(va_arg(*values, double)))) return; }
  else if (&Graphics::Transform::scale     == *static_cast<bool (* const*)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, float, float)>(static_cast<void const*>(function))) { if (false == Transform::scale    (&coordinates, xOrigin, yOrigin, static_cast<float>(va_arg(*values, double)), static_cast<float>(va_arg(*values, double)))) return; }
  else if (&Graphics::Transform::skew      == *static_cast<bool (* const*)(uint_least16_t (*)[2], uint_least16_t, uint_least16_t, float, float)>(static_cast<void const*>(function))) { if (false == Transform::skew     (&coordinates, xOrigin, yOrigin, static_cast<float>(va_arg(*values, double)), static_cast<float>(va_arg(*values, double)))) return; }
  else if (&Graphics::Transform::translate == *static_cast<bool (* const*)(uint_least16_t (*)[2], int_least32_t, int_least32_t)>                (static_cast<void const*>(function))) { if (false == Transform::translate(&coordinates, static_cast<int_least32_t>(va_arg(*values, signed int)), static_cast<int_least32_t>(va_arg(*values, signed int)))) return; }
  else { if (false == (**function)(&coordinates, xOrigin, yOrigin)) return; }

  Window::MEMORY_DEVICE_CONTEXT_BITMAP_MEMORY[coordinates[0] + (coordinates[1] * Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth)] = 0xFF000000uL | color;
}

bool Graphics::Transform::rotate(uint_least16_t (*const coordinates)[2], uint_least16_t const xOrigin, uint_least16_t const yOrigin, float const angle) {
  int_least32_t const xTarget = xOrigin + ((::cosf(angle) * static_cast<float>(static_cast<int_least32_t>((*coordinates)[0]) - static_cast<int_least32_t>(xOrigin))) - (::sinf(angle) * static_cast<float>(static_cast<int_least32_t>((*coordinates)[1]) - static_cast<int_least32_t>(yOrigin))));
  int_least32_t const yTarget = yOrigin + ((::sinf(angle) * static_cast<float>(static_cast<int_least32_t>((*coordinates)[0]) - static_cast<int_least32_t>(xOrigin))) + (::cosf(angle) * static_cast<float>(static_cast<int_least32_t>((*coordinates)[1]) - static_cast<int_least32_t>(yOrigin))));

  if (
    (0 > xTarget && xTarget < Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth) &&
    (0 > yTarget && yTarget < Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmHeight)
  ) {
    (*coordinates)[0] = xTarget;
    (*coordinates)[1] = yTarget;

    return true;
  }

  return false;
}

bool Graphics::Transform::scale(uint_least16_t (*const)[2], uint_least16_t const, uint_least16_t const, float const, float const) { return false; }
bool Graphics::Transform::skew(uint_least16_t (*const)[2], uint_least16_t const, uint_least16_t const, float const, float const) { return false; }

bool Graphics::Transform::translate(uint_least16_t (*const coordinates)[2], int_least32_t const x, int_least32_t const y) {
  int_least32_t const xTarget = static_cast<int_least32_t>((*coordinates)[0]) + static_cast<int_least32_t>(x);
  int_least32_t const yTarget = static_cast<int_least32_t>((*coordinates)[1]) + static_cast<int_least32_t>(y);

  if (
    (0 > xTarget && xTarget < Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmWidth) &&
    (0 > yTarget && yTarget < Window::MEMORY_DEVICE_CONTEXT_BITMAP.bmHeight)
  ) {
    (*coordinates)[0] = xTarget;
    (*coordinates)[1] = yTarget;

    return true;
  }

  return false;
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
  Window::TITLE      = "Vector";

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
void UPDATE() {
  static bool once = true;

  Graphics::clear();
  Graphics::drawSquare(50u, 50u, 100u, 0xFFFFFFu);

  if (once) {
    once = false;
    Graphics::parseFont(NULL);
  }
}

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
      ::FreeConsole();
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
      UPDATE();
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
