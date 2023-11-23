// ... --> g++ -pedantic-errors -std=c++98 -Wall -Werror -Wextra window.cpp -o window
#include <cstdio>
#include <cstdlib>
#include <windows.h>

/* Main */
int main(int, char*[]) {
  struct windowNamespace {
    static LRESULT procedure(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
      switch (message) {
        case WM_CLOSE  : (void) ::DestroyWindow(windowHandle); break;
        case WM_DESTROY: ::PostQuitMessage(EXIT_SUCCESS);      break;
      }

      return ::DefWindowProcW(windowHandle, message, parameter, subparameter);
    }
  };
  MSG         threadMessage = {};
  WNDCLASSEXW windowClass   = {};
  HWND        windowHandle  = NULL;

  // ...
  windowClass.cbClsExtra    = 0u;
  windowClass.cbSize        = sizeof(WNDCLASSEX);
  windowClass.cbWndExtra    = 0u;
  windowClass.hbrBackground = static_cast<HBRUSH> (NULL);
  windowClass.hCursor       = static_cast<HCURSOR>(NULL);
  windowClass.hIcon         = static_cast<HICON>  (NULL);
  windowClass.hIconSm       = static_cast<HICON>  (NULL);
  windowClass.hInstance     = ::GetModuleHandleW(static_cast<LPCWSTR>(NULL));
  windowClass.lpfnWndProc   = reinterpret_cast<WNDPROC>(&windowNamespace::procedure);
  windowClass.lpszClassName = L"class";
  windowClass.lpszMenuName  = static_cast<LPCWSTR>(NULL);
  windowClass.style         = CS_GLOBALCLASS | CS_HREDRAW | CS_OWNDC | CS_VREDRAW;

  if (0x00u == ::RegisterClassExW(&windowClass)) {
    std::fputs("Unable to register window class" "\r\n", stderr);
    std::exit(EXIT_FAILURE);
  }

  windowHandle = ::CreateWindowExW(0x00000000u, windowClass.lpszClassName, L"Hello, World!", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, static_cast<HWND>(NULL), static_cast<HMENU>(NULL), windowClass.hInstance, static_cast<LPVOID>(NULL));

  if (NULL == windowHandle) {
    std::fputs("Unable to create window" "\r\n", stderr);
    std::exit(EXIT_FAILURE);
  }

  (void) ::ShowWindow  (windowHandle, SW_SHOW);
  (void) ::UpdateWindow(windowHandle);

  while (::GetMessage(&threadMessage, windowHandle, 0x00u, 0x00u) > FALSE) {
    ::TranslateMessage(&threadMessage);
    ::DispatchMessage (&threadMessage);
  }

  return threadMessage.wParam;
}
