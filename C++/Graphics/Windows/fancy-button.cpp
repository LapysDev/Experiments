/* ...
    --- NOTE (Lapys) -> Double-buffering not implemented.
    --- RESOURCE (Lapys) -> gdi32.lib, msimg32.lib, dwmapi.lib, user32.lib
*/
#undef UNICODE

/* Import */
#include <stddef.h> // Standard Definitions
#include <stdlib.h> // Standard Library
#include <stdio.h> // Standard Input/ Output
#include <windows.h> // Windows
#   include <dwmapi.h> // Desktop Window Manager API
#   include <wingdi.h> // Windows GDI

/* Polyfill > Print Window > Render Full Content */
#ifndef PW_RENDERFULLCONTENT
#   define PW_RENDERFULLCONTENT 0x00000002
#endif

/* Global */
    /* Button ... */
    // : [Styles]
    COLORREF const BUTTON_BACKGROUND_COLOR = RGB(0, 0, 204);
    LONG const BUTTON_BOTTOM_PADDING = 20L, BUTTON_TOP_PADDING = 20L;
    LONG const BUTTON_LEFT_PADDING = 40L, BUTTON_RIGHT_PADDING = 40L;
    HFONT BUTTON_FONT = NULL;
    char const BUTTON_FONT_FAMILY[] = "Calibri Light";
    long const BUTTON_FONT_SIZE = 48L;
    COLORREF const BUTTON_TEXT_COLOR = RGB(255, 255, 255);
    char const BUTTON_TEXT_CONTENT[] = "Button";

    // : [...]
    void BUTTON_PAINT_PROCEDURE(HDC const, UINT const, POINT const);
    RECT BUTTON_RECTANGLE = {};
    enum {ACTIVE, IDLE, DISABLED, FOCUSED, HOVERED} BUTTON_STATE = IDLE;

    /* Window ... */
    // : [Configurations]
    ULONG64 WINDOW_CURRENT_TIMESTAMP = 0uL, WINDOW_RECENT_TIMESTAMP = 0uL;
    WORD const WINDOW_REPAINT_RATE = 1000u / 60u;
    ULONG WINDOW_TIMESTAMP_FREQUENCY = 2000uL;

    // : [Styles]
    int WINDOW_APPEARANCE = 0x0;
    COLORREF const WINDOW_BACKGROUND_COLOR = RGB(0, 15, 102);
    char const WINDOW_FONT_FAMILY[] = "Calibri Light";
    long const WINDOW_FONT_SIZE = 18L;
    int const WINDOW_HEIGHT = 500, WINDOW_WIDTH = 500;
    COLORREF const WINDOW_TEXT_COLOR = RGB(255, 255, 255);
    char const WINDOW_TITLE[] = "Fancy Button";

    // : [...]
    RECT WINDOW_BACKGROUND_RECTANGLE = {}, WINDOW_RECTANGLE = {};
    WNDCLASSEX WINDOW_CLASS = {};
    HFONT WINDOW_FONT = NULL;
    HWND WINDOW_HANDLE = NULL;
    HDC WINDOW_OFFSCREEN_DEVICE_CONTEXT_HANDLE = NULL;
    HBITMAP WINDOW_OFFSCREEN_DEVICE_CONTEXT_BITMAP_HANDLE = NULL;
    HDC WINDOW_ONSCREEN_DEVICE_CONTEXT_HANDLE = NULL;
    void WINDOW_PAINT_BACKGROUND_PROCEDURE(HDC const, UINT const, HWND const);
    LRESULT CALLBACK WINDOW_PROCEDURE(HWND const, UINT const, WPARAM const, LPARAM const);

/* Function */
    /* Button Paint Procedure */
    void BUTTON_PAINT_PROCEDURE(HDC const windowDeviceContextHandle, UINT const message, POINT const) {
        // Logic
        switch (message) {
            // [Create]
            case WM_CREATE: {
                // Update > ... Button
                BUTTON_FONT = ::CreateFont(BUTTON_FONT_SIZE, FW_DONTCARE, FALSE, TRUE, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, BUTTON_FONT_FAMILY);
            } break;

            // [Destroy]
            case WM_DESTROY: {
                // Deletion > ... Button
                ::DeleteObject(BUTTON_FONT);
            } break;

            // [Paint]
            case WM_PAINT: {
                // Initialization > (Button ..., ...)
                COLORREF buttonBackgroundColor = BUTTON_BACKGROUND_COLOR;
                HBRUSH buttonBackgroundColorBrush;
                struct { BYTE red, green, blue; } buttonBackgroundColorChannels = {
                    GetRValue(buttonBackgroundColor),
                    GetGValue(buttonBackgroundColor),
                    GetBValue(buttonBackgroundColor)
                };
                RECT buttonTextContentRectangle = {};
                SIZE buttonTextContentSize = {};

                HGDIOBJ windowDeviceContextFont;
                COLORREF windowDeviceContextTextColor;

                // Update > Window Device Context ...
                windowDeviceContextFont = ::SelectObject(windowDeviceContextHandle, BUTTON_FONT);
                windowDeviceContextTextColor = ::SetTextColor(windowDeviceContextHandle, BUTTON_TEXT_COLOR);

                ::GetTextExtentPoint32A(windowDeviceContextHandle, BUTTON_TEXT_CONTENT, ::strlen(BUTTON_TEXT_CONTENT), &buttonTextContentSize);

                // Modification > Button ... Rectangle > (Bottom, Left, Right, Top)
                buttonTextContentRectangle.left = (WINDOW_WIDTH - buttonTextContentSize.cx) / 2L;
                buttonTextContentRectangle.top = (WINDOW_HEIGHT - buttonTextContentSize.cy) / 2L;
                buttonTextContentRectangle.bottom = buttonTextContentSize.cy + buttonTextContentRectangle.top;
                buttonTextContentRectangle.right = buttonTextContentSize.cx + buttonTextContentRectangle.left;

                BUTTON_RECTANGLE.bottom = buttonTextContentRectangle.bottom + BUTTON_BOTTOM_PADDING;
                BUTTON_RECTANGLE.left = buttonTextContentRectangle.left - BUTTON_LEFT_PADDING;
                BUTTON_RECTANGLE.right = buttonTextContentRectangle.right + BUTTON_RIGHT_PADDING;
                BUTTON_RECTANGLE.top = buttonTextContentRectangle.top - BUTTON_TOP_PADDING;

                // ... Update > Button Background Color ...
                switch (BUTTON_STATE) {
                    case ACTIVE: buttonBackgroundColorChannels = {255u, 0u, 0u}; break;
                    case DISABLED: buttonBackgroundColorChannels = {0u, 0u, 0u}; break;
                    case IDLE: break;
                    case FOCUSED: buttonBackgroundColorChannels = {255u, 107u, 0u}; break;
                    case HOVERED: buttonBackgroundColorChannels = {0u, 107u, 255u}; break;
                }
                buttonBackgroundColor = RGB(buttonBackgroundColorChannels.red, buttonBackgroundColorChannels.green, buttonBackgroundColorChannels.blue);
                buttonBackgroundColorBrush = (HBRUSH) ::CreateSolidBrush(buttonBackgroundColor);

                // ...
                ::FillRect(windowDeviceContextHandle, &BUTTON_RECTANGLE, buttonBackgroundColorBrush);
                ::DrawText(windowDeviceContextHandle, BUTTON_TEXT_CONTENT, -1, &buttonTextContentRectangle, DT_LEFT | DT_NOCLIP | DT_SINGLELINE | DT_TOP);

                // Deletion; Reset
                ::DeleteObject(buttonBackgroundColorBrush);

                ::SelectObject(windowDeviceContextHandle, windowDeviceContextFont);
                ::SetTextColor(windowDeviceContextHandle, windowDeviceContextTextColor);
            } break;
        }
    }

    /* Window Procedure */
    LRESULT CALLBACK WINDOW_PROCEDURE(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
        // Initialization > (Cursor Position, ...)
        POINT cursorPosition = {};
        constexpr SHORT const virtualKeySize = (SHORT) (1 << (sizeof(SHORT) * 8 - 1));

        // [Update] ...
        {
            // Update > Window ... Timestamp
            WINDOW_CURRENT_TIMESTAMP = __rdtsc();
            WINDOW_HANDLE = windowHandle;
            WINDOW_RECENT_TIMESTAMP = 0uL == WINDOW_RECENT_TIMESTAMP || WINDOW_REPAINT_RATE < (WINDOW_CURRENT_TIMESTAMP - WINDOW_RECENT_TIMESTAMP) / WINDOW_TIMESTAMP_FREQUENCY / 1000uL ? WINDOW_CURRENT_TIMESTAMP : WINDOW_RECENT_TIMESTAMP;
            ::GetWindowRect(WINDOW_HANDLE, &WINDOW_RECTANGLE);
        } switch (message) {
            // [...]
            case WM_CLOSE: goto Destroy; break;
            case WM_ERASEBKGND: return EXIT_SUCCESS; break;
            case WM_KEYDOWN: if (VK_ESCAPE == parameter) goto Destroy; break;
            case WM_SYSCOMMAND: if (SC_CLOSE == parameter) goto Destroy; break;
            case WM_SYSKEYDOWN: if (VK_F4 == parameter) goto Destroy; break;

            // [Create]
            case WM_CREATE: {
                // Update > Window ...
                WINDOW_FONT = ::CreateFont(WINDOW_FONT_SIZE, FW_DONTCARE, FALSE, TRUE, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, WINDOW_FONT_FAMILY);
                WINDOW_ONSCREEN_DEVICE_CONTEXT_HANDLE = ::GetDCEx(WINDOW_HANDLE, NULL, CS_OWNDC | DCX_NORESETATTRS);
                WINDOW_OFFSCREEN_DEVICE_CONTEXT_HANDLE = ::CreateCompatibleDC(WINDOW_ONSCREEN_DEVICE_CONTEXT_HANDLE);
                WINDOW_OFFSCREEN_DEVICE_CONTEXT_BITMAP_HANDLE = ::CreateCompatibleBitmap(WINDOW_ONSCREEN_DEVICE_CONTEXT_HANDLE, WINDOW_WIDTH, WINDOW_HEIGHT);

                ::SelectObject(WINDOW_OFFSCREEN_DEVICE_CONTEXT_HANDLE, WINDOW_OFFSCREEN_DEVICE_CONTEXT_BITMAP_HANDLE);
                ::SetBkMode(WINDOW_OFFSCREEN_DEVICE_CONTEXT_HANDLE, TRANSPARENT);
                ::ShowWindow(WINDOW_HANDLE, WINDOW_APPEARANCE);

                // ...
                BUTTON_PAINT_PROCEDURE(NULL, WM_CREATE, cursorPosition);
                WINDOW_PAINT_BACKGROUND_PROCEDURE(NULL, WM_CREATE, NULL);
            } break;

            // [Destroy]
            case WM_DESTROY: {
                // Deletion > Window ...
                // : Terminate
                ::DeleteObject(WINDOW_FONT);
                ::DeleteDC(WINDOW_OFFSCREEN_DEVICE_CONTEXT_HANDLE);
                ::DeleteObject(WINDOW_OFFSCREEN_DEVICE_CONTEXT_BITMAP_HANDLE);
                ::ReleaseDC(WINDOW_HANDLE, WINDOW_ONSCREEN_DEVICE_CONTEXT_HANDLE);

                ::PostQuitMessage(EXIT_SUCCESS);

                // ...
                BUTTON_PAINT_PROCEDURE(NULL, WM_DESTROY, cursorPosition);
                WINDOW_PAINT_BACKGROUND_PROCEDURE(NULL, WM_DESTROY, NULL);
            } break;

            // [Paint]
            case WM_PAINT: {
                // Initialization > Window ...
                HGDIOBJ const windowOffscreenDeviceContextFont = ::SelectObject(WINDOW_OFFSCREEN_DEVICE_CONTEXT_HANDLE, WINDOW_FONT);
                COLORREF const windowOffscreenDeviceContextTextColor = ::SetTextColor(WINDOW_OFFSCREEN_DEVICE_CONTEXT_HANDLE, WINDOW_TEXT_COLOR);

                /* ... */ {
                    // [...]
                    WINDOW_PAINT_BACKGROUND_PROCEDURE(NULL, WM_CLEAR, NULL); {
                        for (HWND windowHandle = WINDOW_HANDLE; NULL != windowHandle; windowHandle = ::GetWindow(windowHandle, GW_HWNDNEXT))
                        if (windowHandle == ::GetAncestor(windowHandle, GA_ROOT)) WINDOW_PAINT_BACKGROUND_PROCEDURE(NULL, WM_NCHITTEST, windowHandle);
                    } WINDOW_PAINT_BACKGROUND_PROCEDURE(WINDOW_OFFSCREEN_DEVICE_CONTEXT_HANDLE, WM_PAINT, NULL);

                    // [...]
                    // BUTTON_PAINT_PROCEDURE(WINDOW_OFFSCREEN_DEVICE_CONTEXT_HANDLE, WM_PAINT, cursorPosition);

                    /* [Text Guides] */ {
                        // Initialization > ...
                        RECT windowTextContentRectangle = {10L, 10L, 100L, 10L};
                        LONG const windowTextContentVerticalPadding = 2L;

                        // Loop > ... Update > Window Off-Screen Device Context Handle
                        for (char const *const textGuides[] = {
                            "Exit Window: 'Alt + F4' hotkey, 'Esc' key", "Fullscreen: 'F11' key", "",
                            "Activate Button: 'Enter' key, 'Left-Click' button", "Select Button: 'Tab' key"
                        }, *const *iterator = textGuides, *const *const end = iterator + (sizeof(textGuides) / sizeof(char*)); end != iterator; ++iterator) {
                            windowTextContentRectangle.top = windowTextContentRectangle.bottom + windowTextContentVerticalPadding;
                            windowTextContentRectangle.bottom = WINDOW_FONT_SIZE + windowTextContentRectangle.top + windowTextContentVerticalPadding;

                            ::DrawText(WINDOW_OFFSCREEN_DEVICE_CONTEXT_HANDLE, *iterator, -1, &windowTextContentRectangle, DT_LEFT | DT_NOCLIP | DT_SINGLELINE | DT_TOP);
                        }
                    }
                }

                // Update > Window On-Screen Device Context Handle
                ::BitBlt(WINDOW_ONSCREEN_DEVICE_CONTEXT_HANDLE, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_OFFSCREEN_DEVICE_CONTEXT_HANDLE, 0, 0, SRCCOPY);

                // Reset > Window ...
                ::SelectObject(WINDOW_OFFSCREEN_DEVICE_CONTEXT_HANDLE, windowOffscreenDeviceContextFont);
                ::SetTextColor(WINDOW_OFFSCREEN_DEVICE_CONTEXT_HANDLE, windowOffscreenDeviceContextTextColor);
                ::ValidateRect(WINDOW_HANDLE, NULL);
            } return EXIT_SUCCESS;
        }

        // [Repaint] Logic
        if (WINDOW_CURRENT_TIMESTAMP == WINDOW_RECENT_TIMESTAMP) {
            // ... Update > Button ... State
            BUTTON_STATE = IDLE; {
                // [Keyboard]
                if (WINDOW_HANDLE == ::GetActiveWindow()) {
                    if (::GetAsyncKeyState(VK_RETURN) & virtualKeySize) BUTTON_STATE = ACTIVE;
                    else if (::GetAsyncKeyState(VK_TAB) & virtualKeySize) BUTTON_STATE = FOCUSED;
                }

                // [Pointer]
                if (::GetCursorPos(&cursorPosition)) {
                    ::MapWindowPoints(HWND_DESKTOP, WINDOW_HANDLE, &cursorPosition, 1); // WARN (Lapys) -> May fail.
                    if (
                        (cursorPosition.x >= BUTTON_RECTANGLE.left && cursorPosition.x <= BUTTON_RECTANGLE.right) &&
                        (cursorPosition.y >= BUTTON_RECTANGLE.top && cursorPosition.y <= BUTTON_RECTANGLE.bottom)
                    ) BUTTON_STATE = ::GetAsyncKeyState(VK_LBUTTON) & virtualKeySize ? ACTIVE : (IDLE == BUTTON_STATE ? HOVERED : BUTTON_STATE);
                }
            }

            // ...
            ::RedrawWindow(WINDOW_HANDLE, NULL, NULL, RDW_INVALIDATE | RDW_NOCHILDREN);
        }

        // [Evaluate, Destroy] ...
        Evaluate: return ::DefWindowProc(WINDOW_HANDLE, message, parameter, subparameter);
        Destroy: ::DestroyWindow(WINDOW_HANDLE); goto Evaluate;
    }
        /* Window Paint Background Procedure */
        void WINDOW_PAINT_BACKGROUND_PROCEDURE(HDC const windowDeviceContextHandle, UINT const message, HWND const windowHandle) {
            // Initialization
            // : Recent Window Device Context Handle
            static HDC recentWindowDeviceContextHandle = NULL;

            // : ... Background Window Information List (Length)
            static struct { BYTE opacity; RECT rectangle; HWND windowHandle; }
                windowInformation = {0u, {0L, 0L, 0L, 0L}, NULL},
                *windowBackgroundWindowInformationList = NULL;
            static unsigned windowBackgroundWindowInformationListLength = 0u;

            // : Window Memory Device Context Handle --- NOTE (Lapys) -> `PrintWindow(...)` shenanigans.
            static HDC windowMemoryDeviceContextHandle = NULL;
            static HBITMAP windowMemoryDeviceContextBitmapHandle = NULL;

            // Logic
            switch (message) {
                // [Clear, Create]
                case WM_CLEAR: windowBackgroundWindowInformationListLength = 0u; break;
                case WM_CREATE: {
                    // ... Update > ... Background Window Information List
                    void *const allocation = ::malloc(16u * sizeof(windowInformation));
                    ::memcpy(&windowBackgroundWindowInformationList, &allocation, sizeof(void*));
                } break;

                // [Destroy]
                case WM_DESTROY: {
                    // ... Deletion
                    if (NULL != windowMemoryDeviceContextHandle) ::DeleteDC(windowMemoryDeviceContextHandle);
                    if (NULL != windowMemoryDeviceContextBitmapHandle) ::DeleteObject(windowMemoryDeviceContextBitmapHandle);

                    ::free(windowBackgroundWindowInformationList);
                } break;

                // [Non-Client Hit Test]
                case WM_NCHITTEST: if (WINDOW_HANDLE != windowHandle) {
                    // Initialization > Window Is Cloaked
                    INT windowIsCloaked = FALSE;

                    // ...; Logic
                    ::DwmGetWindowAttribute(windowHandle, DWMWA_CLOAKED, &windowIsCloaked, sizeof(INT));
                    if (FALSE == windowIsCloaked && FALSE == ::IsIconic(windowHandle) && ::IsWindowVisible(windowHandle)) {
                        // Initialization > Window ...
                        HDC const windowDeviceContextHandle = ::GetDCEx(windowHandle, NULL, CS_OWNDC | DCX_NORESETATTRS | DCX_WINDOW);
                        RECT windowHitTestRectangle = {};
                        RECT windowRectangle = {};

                        // Update > Window Rectangle
                        // : Logic
                        ::GetWindowRect(windowHandle, &windowRectangle);
                        if (NULLREGION != ::GetClipBox(windowDeviceContextHandle, &windowHitTestRectangle) && ::IntersectRect(&windowHitTestRectangle, &windowRectangle, &WINDOW_RECTANGLE)) {
                            // Initialization > Window (Is Obscured, Opacity)
                            bool windowIsObscured = false;
                            BYTE windowOpacity = 255u;

                            // ...; Logic
                            ::GetLayeredWindowAttributes(windowHandle, NULL, &windowOpacity, NULL);
                            if (255u == windowOpacity) {
                                // Loop
                                for (unsigned iterator = windowBackgroundWindowInformationListLength; iterator--; ) {
                                    // Constant > ... Background Window Rectangle
                                    RECT const& windowBackgroundWindowRectangle = (windowBackgroundWindowInformationList + iterator) -> rectangle;

                                    // ... Update > Window Is Obscured
                                    if (
                                        windowRectangle.bottom <= windowBackgroundWindowRectangle.bottom &&
                                        windowRectangle.left <= windowBackgroundWindowRectangle.left &&
                                        windowRectangle.right >= windowBackgroundWindowRectangle.right &&
                                        windowRectangle.top <= windowBackgroundWindowRectangle.top
                                    ) { windowIsObscured = true; break; }
                                }
                            }

                            // Logic > ... Update > ... Background Window Information List --- REDACT (Lapys)
                            if (false == windowIsObscured) {
                                size_t capacity = 16u;

                                while (capacity < windowBackgroundWindowInformationListLength) capacity = (capacity * 3u) / 2u;
                                if (16u != capacity) {
                                    void *const allocation = ::realloc(windowBackgroundWindowInformationList, capacity * sizeof(windowInformation));
                                    ::memcpy(&windowBackgroundWindowInformationList, &allocation, sizeof(void*));
                                }

                                windowBackgroundWindowInformationList[windowBackgroundWindowInformationListLength++] = {
                                    windowOpacity, windowRectangle, windowHandle
                                };
                            }
                        }

                        // Deletion
                        ::ReleaseDC(windowHandle, windowDeviceContextHandle);
                    }
                } break;

                // [Paint]
                case WM_PAINT: {
                    // ...
                    RECT const windowRectangle = {0L, 0L, WINDOW_RECTANGLE.right - WINDOW_RECTANGLE.left, WINDOW_RECTANGLE.bottom - WINDOW_RECTANGLE.top};
                    ::FillRect(windowDeviceContextHandle, &windowRectangle, WINDOW_CLASS.hbrBackground);

                    // Logic --- NOTE (Lapys) -> Reset the memory device contexts used for the specified `windowDeviceContext`.
                    if (recentWindowDeviceContextHandle != windowDeviceContextHandle) {
                        // ... Deletion
                        if (NULL != windowMemoryDeviceContextHandle) ::DeleteDC(windowMemoryDeviceContextHandle);
                        if (NULL != windowMemoryDeviceContextBitmapHandle) ::DeleteObject(windowMemoryDeviceContextBitmapHandle);

                        // Update > ... Window (Memory) Device Context ... Handle
                        recentWindowDeviceContextHandle = windowDeviceContextHandle;
                        windowMemoryDeviceContextHandle = ::CreateCompatibleDC(windowDeviceContextHandle);
                        windowMemoryDeviceContextBitmapHandle = ::CreateCompatibleBitmap(windowDeviceContextHandle, ::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN));

                        ::SelectObject(windowMemoryDeviceContextHandle, windowMemoryDeviceContextBitmapHandle);
                    }

                    // Loop
                    for (unsigned iterator = windowBackgroundWindowInformationListLength; iterator--; ) {
                        // Constant > ... Background Window (Window Handle, Opacity, Rectangle)
                        HWND const& windowBackgroundWindowHandle = (windowBackgroundWindowInformationList + iterator) -> windowHandle;
                        RECT& windowBackgroundWindowRectangle = (windowBackgroundWindowInformationList + iterator) -> rectangle;
                        BYTE const& windowBackgroundWindowOpacity = (windowBackgroundWindowInformationList + iterator) -> opacity;

                        bool const windowBackgroundWindowIsClientOnly = 0 == (::GetWindowLong(WINDOW_HANDLE, GWL_STYLE) & WS_POPUP);

                        // Modification > ... Background Window Rectangle
                        windowBackgroundWindowRectangle.bottom -= windowBackgroundWindowRectangle.top;
                        windowBackgroundWindowRectangle.right -= windowBackgroundWindowRectangle.left;

                        windowBackgroundWindowRectangle.left -= WINDOW_RECTANGLE.left;
                        windowBackgroundWindowRectangle.left -= windowBackgroundWindowIsClientOnly * ::GetSystemMetrics(SM_CXSIZEFRAME);

                        windowBackgroundWindowRectangle.top -= WINDOW_RECTANGLE.top;
                        windowBackgroundWindowRectangle.top -= windowBackgroundWindowIsClientOnly * (::GetSystemMetrics(SM_CYCAPTION) + ::GetSystemMetrics(SM_CYSIZEFRAME));

                        (windowBackgroundWindowRectangle.bottom > WINDOW_HEIGHT - windowBackgroundWindowRectangle.top) &&
                        (windowBackgroundWindowRectangle.bottom = WINDOW_HEIGHT - windowBackgroundWindowRectangle.top);

                        (windowBackgroundWindowRectangle.right > WINDOW_WIDTH - windowBackgroundWindowRectangle.left) &&
                        (windowBackgroundWindowRectangle.right = WINDOW_WIDTH - windowBackgroundWindowRectangle.left);

                        // ...
                        ::PrintWindow(windowBackgroundWindowHandle, windowMemoryDeviceContextHandle, PW_RENDERFULLCONTENT);
                        ::AlphaBlend(
                            windowDeviceContextHandle,
                            windowBackgroundWindowRectangle.left,
                            windowBackgroundWindowRectangle.top,
                            windowBackgroundWindowRectangle.right,
                            windowBackgroundWindowRectangle.bottom,
                            windowMemoryDeviceContextHandle,
                            0,
                            0,
                            windowBackgroundWindowRectangle.right,
                            windowBackgroundWindowRectangle.bottom,
                            BLENDFUNCTION {AC_SRC_OVER, 0x0, windowBackgroundWindowOpacity, AC_SRC_ALPHA}
                        );
                    }
                } break;
            }
        }

/* Main */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const previousInstanceHandle, LPSTR const, int const appearance) {
    // Initialization > (Exit Code, ...)
    int exitCode = EXIT_SUCCESS;
    HANDLE lock = NULL;

    // Update > Window ... --- REDACT (Lapys)
    WINDOW_APPEARANCE = appearance;

    WINDOW_CLASS.cbClsExtra = 0;
    WINDOW_CLASS.cbSize = sizeof(WNDCLASSEX);
    WINDOW_CLASS.cbWndExtra = 0;
    WINDOW_CLASS.hbrBackground = (HBRUSH) ::CreateSolidBrush(WINDOW_BACKGROUND_COLOR);
    WINDOW_CLASS.hCursor = (HCURSOR) ::LoadCursor(NULL, IDC_ARROW); // -> ::LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
    WINDOW_CLASS.hIcon = (HICON) NULL;
    WINDOW_CLASS.hIconSm = (HICON) NULL;
    WINDOW_CLASS.hInstance = instanceHandle; // -> ::GetModuleHandle(NULL);
    WINDOW_CLASS.lpfnWndProc = &WINDOW_PROCEDURE;
    WINDOW_CLASS.lpszClassName = "window";
    WINDOW_CLASS.lpszMenuName = (LPCSTR) NULL;
    WINDOW_CLASS.style = 0x0;

    WINDOW_TIMESTAMP_FREQUENCY = 2000uL; {
        HKEY registryKey;
        if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0u, KEY_READ, &registryKey)) {
            ULONG size = 4uL;

            ::RegQueryValueEx(registryKey, "~MHz", NULL, NULL, (LPBYTE) &WINDOW_TIMESTAMP_FREQUENCY, &size);
            ::RegCloseKey(registryKey);
        }
    }

    /* [Assert Previous (Program) Instance by] ...
        --- NOTE ---
            #Lapys: Experiment to prevent multiple instances of the executable being "invoked".
    */ {
        // [Handle]
        goto AssertPreviousInstanceByHandle;
        AssertPreviousInstanceByHandle: if (NULL != previousInstanceHandle) goto Terminate;

        // [Lock File]
        goto AssertPreviousInstanceByLockFile;
        AssertPreviousInstanceByLockFile: {
            // Initialization > Lock ...
            CHAR lockFileName[MAX_PATH] = {};
            CHAR lockFilePath[MAX_PATH + 1] = {};

            // ... Update > Lock
            if (0u == ::GetTempPath(MAX_PATH + 1u, lockFilePath)) goto AssertPreviousInstanceByMutex;
            if (0u == ::GetTempFileName(lockFilePath, "", 0000, lockFileName)) goto AssertPreviousInstanceByMutex;
            lock = ::CreateFile(lockFileName, GENERIC_READ, 0u, NULL, CREATE_NEW, FILE_FLAG_DELETE_ON_CLOSE, NULL);

            // Logic > ...
            if (INVALID_HANDLE_VALUE == lock) goto AssertPreviousInstanceByMutex;
            switch (::GetLastError()) {
                case ERROR_FILE_EXISTS: exitCode = EXIT_FAILURE; goto Terminate; break;
                case ERROR_SUCCESS: break;
                default: goto AssertPreviousInstanceByMutex; break;
            } goto EvaluatedPreviousInstance;
        }

        // [Mutex]
        goto AssertPreviousInstanceByMutex;
        AssertPreviousInstanceByMutex: {
            // Update > Lock
            lock = ::CreateMutex(NULL, TRUE, "PreviousInstanceAssertion");

            // Logic > ...
            if (NULL != lock)
            switch (::GetLastError()) {
                case ERROR_ALREADY_EXISTS: exitCode = EXIT_FAILURE; goto Terminate; break;
                case ERROR_SUCCESS: break;
                default: break;
            }
        }

        // [...]
        EvaluatedPreviousInstance: {}
    }

    // Logic > ...
    if (0u == ::RegisterClassEx((WNDCLASSEX const*) &WINDOW_CLASS)) exitCode = EXIT_FAILURE;
    else {
        // Update > Window Rectangle
        ::SystemParametersInfo(SPI_GETWORKAREA, 0u, (PVOID) &WINDOW_RECTANGLE, 0u);
        WINDOW_RECTANGLE.left = ((WINDOW_RECTANGLE.right - WINDOW_RECTANGLE.left) - WINDOW_WIDTH) / 2L;
        WINDOW_RECTANGLE.top = ((WINDOW_RECTANGLE.bottom - WINDOW_RECTANGLE.top) - WINDOW_HEIGHT) / 2L;
        WINDOW_RECTANGLE.bottom = WINDOW_RECTANGLE.left + WINDOW_WIDTH;
        WINDOW_RECTANGLE.right = WINDOW_RECTANGLE.top + WINDOW_HEIGHT;

        // Logic > ... Window Procedure Message
        if (NULL != (WINDOW_HANDLE = ::CreateWindowEx(
            WS_EX_TOPMOST, WINDOW_CLASS.lpszClassName, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
            WINDOW_RECTANGLE.left, WINDOW_RECTANGLE.top, WINDOW_WIDTH, WINDOW_HEIGHT,
            HWND_DESKTOP, (HMENU) NULL, WINDOW_CLASS.hInstance, NULL
        ))) {
            MSG windowProcedureMessage = {};
            for (
                BOOL available = FALSE; FALSE == available || WM_QUIT != windowProcedureMessage.message;
                available = ::PeekMessage(&windowProcedureMessage, NULL, 0x0, 0x0, PM_REMOVE)
            ) ::DispatchMessage(&windowProcedureMessage);

            exitCode = windowProcedureMessage.wParam;
        } else exitCode = EXIT_FAILURE;

        // ...
        goto TerminateWithCleanup;
    }

    // [Terminate ...] ...
    Terminate: return exitCode;
    TerminateWithCleanup: {
        ::DestroyCursor(WINDOW_CLASS.hCursor);
        ::UnregisterClass(WINDOW_CLASS.lpszClassName, WINDOW_CLASS.hInstance);

        if (INVALID_HANDLE_VALUE != lock && NULL != lock) ::CloseHandle(lock);
    } goto Terminate;
}
