/* ... --- NOTE (Lapys) -> Double-buffering not implemented. */
#undef UNICODE

/* Import */
#include <stddef.h> // Standard Definitions
#include <stdlib.h> // Standard Library
#include <stdio.h> // Standard Input/ Output
#include <windows.h> // Windows

/* Global */
    /* Button ... */
    COLORREF const BUTTON_BACKGROUND_COLOR = RGB(0, 0, 204);
    LONG const BUTTON_BOTTOM_PADDING = 20L, BUTTON_TOP_PADDING = 20L;
    LONG const BUTTON_LEFT_PADDING = 40L, BUTTON_RIGHT_PADDING = 40L;
    HFONT BUTTON_FONT = NULL;
    char const BUTTON_FONT_FAMILY[] = "Calibri Light";
    long const BUTTON_FONT_SIZE = 48L;
    void BUTTON_PROCEDURE(HDC const, UINT const, POINT const);
    RECT BUTTON_RECTANGLE = {};
    enum {ACTIVE, IDLE, DISABLED, FOCUSED, HOVERED} BUTTON_STATE = IDLE;
    COLORREF const BUTTON_TEXT_COLOR = RGB(255, 255, 255);
    char const BUTTON_TEXT_CONTENT[] = "Button";

    /* Window ... */
    int WINDOW_APPEARANCE = 0x0;
    COLORREF const WINDOW_BACKGROUND_COLOR = RGB(207, 207, 255);
    RECT WINDOW_BACKGROUND_RECTANGLE = {};
    HFONT WINDOW_FONT = NULL;
    char const WINDOW_FONT_FAMILY[] = "Calibri Light";
    long const WINDOW_FONT_SIZE = 18L;
    int const WINDOW_HEIGHT = 500, WINDOW_WIDTH = 500;
    COLORREF const WINDOW_TEXT_COLOR = RGB(255, 255, 255);
    char const WINDOW_TITLE[] = "The Button";

    WNDCLASS WINDOW_CLASS = {};
    HDC WINDOW_BACKGROUND_GRAPHICS_DEVICE_CONTEXT_HANDLE = NULL;
    HDC WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE = NULL;
    HBITMAP WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_BITMAP_HANDLE = NULL;
    HDC WINDOW_ONSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE = NULL;
    LRESULT CALLBACK WINDOW_PROCEDURE(HWND const, UINT const, WPARAM const, LPARAM const);

    ULONG64 WINDOW_CURRENT_TIMESTAMP = 0uL, WINDOW_RECENT_TIMESTAMP = 0uL;
    WORD const WINDOW_REPAINT_RATE = 1000u / 60u;
    ULONG WINDOW_TIMESTAMP_FREQUENCY = 2000uL;

/* Function */
    /* Button Procedure */
    void BUTTON_PROCEDURE(HDC const windowGraphicsDeviceContext, UINT const message, POINT const) {
        // Logic
        switch (message) {
            // [Create]
            case WM_CREATE: { // Initialization > ... Button; ...
                BUTTON_FONT = ::CreateFont(BUTTON_FONT_SIZE, FW_DONTCARE, FALSE, TRUE, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, BUTTON_FONT_FAMILY);
            } break;

            // [Destroy]
            case WM_DESTROY: { // Deletion > ... Button; ...
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

                HGDIOBJ windowGraphicsDeviceContextFont;
                COLORREF windowGraphicsDeviceContextTextColor;

                // Update > Window Graphics Device Context ...
                windowGraphicsDeviceContextFont = ::SelectObject(windowGraphicsDeviceContext, BUTTON_FONT);
                windowGraphicsDeviceContextTextColor = ::SetTextColor(windowGraphicsDeviceContext, BUTTON_TEXT_COLOR);

                ::GetTextExtentPoint32A(windowGraphicsDeviceContext, BUTTON_TEXT_CONTENT, ::strlen(BUTTON_TEXT_CONTENT), &buttonTextContentSize);

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
                ::FillRect(windowGraphicsDeviceContext, &BUTTON_RECTANGLE, buttonBackgroundColorBrush);
                ::DrawText(windowGraphicsDeviceContext, BUTTON_TEXT_CONTENT, -1, &buttonTextContentRectangle, DT_LEFT | DT_NOCLIP | DT_SINGLELINE | DT_TOP);

                // Deletion; Reset
                ::DeleteObject(buttonBackgroundColorBrush);

                ::SelectObject(windowGraphicsDeviceContext, windowGraphicsDeviceContextFont);
                ::SetTextColor(windowGraphicsDeviceContext, windowGraphicsDeviceContextTextColor);
            } break;
        }
    }

    /* Window Procedure */
    LRESULT CALLBACK WINDOW_PROCEDURE(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
        // Initialization > (Cursor Position, ...)
        POINT cursorPosition = {};
        constexpr SHORT const virtualKeySize = (SHORT) (1 << (sizeof(SHORT) * 8 - 1));

        // Update > Window (Current, Recent) Timestamp
        WINDOW_CURRENT_TIMESTAMP = __rdtsc();
        WINDOW_RECENT_TIMESTAMP = 0u == WINDOW_RECENT_TIMESTAMP || WINDOW_REPAINT_RATE < (WINDOW_CURRENT_TIMESTAMP - WINDOW_RECENT_TIMESTAMP) / WINDOW_TIMESTAMP_FREQUENCY / 1000uL ? WINDOW_CURRENT_TIMESTAMP : WINDOW_RECENT_TIMESTAMP;

        // [Process Window Message] Logic --- REDACT (Lapys)
        switch (message) {
            // [...]
            case WM_CLOSE: goto Destroy; break;
            case WM_KEYDOWN: if (VK_ESCAPE == parameter) goto Destroy; break;
            case WM_SYSCOMMAND: if (SC_CLOSE == parameter) goto Destroy; break;
            case WM_SYSKEYDOWN: if (VK_F4 == parameter) goto Destroy; break;

            // [Create]
            case WM_CREATE: { // Initialize > Window ...; ...
                WINDOW_BACKGROUND_GRAPHICS_DEVICE_CONTEXT_HANDLE = ::GetDCEx(NULL, NULL, CS_OWNDC | DCX_NORESETATTRS | DCX_WINDOW);
                WINDOW_FONT = ::CreateFont(WINDOW_FONT_SIZE, FW_DONTCARE, FALSE, TRUE, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, WINDOW_FONT_FAMILY);
                WINDOW_ONSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE = ::GetDCEx(windowHandle, NULL, CS_OWNDC | DCX_NORESETATTRS);
                WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE = ::CreateCompatibleDC(WINDOW_ONSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE);
                WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_BITMAP_HANDLE = ::CreateCompatibleBitmap(WINDOW_ONSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, WINDOW_WIDTH, WINDOW_HEIGHT);

                ::SelectObject(WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_BITMAP_HANDLE);
                ::SetBkMode(WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, TRANSPARENT);
                {
                    // ::SetLayeredWindowAttributes(windowHandle, 0x000000, 255u, LWA_ALPHA | LWA_COLORKEY);

                    BLENDFUNCTION blendFunction = {};
                    blendFunction.AlphaFormat = AC_SRC_ALPHA;
                    blendFunction.BlendFlags = 0x0;
                    blendFunction.BlendOp = AC_SRC_OVER;
                    blendFunction.SourceConstantAlpha = 255u;
                    // POINT point = {0L, 0L};
                    // SIZE size = {WINDOW_WIDTH, WINDOW_HEIGHT};
                    if (FALSE == ::UpdateLayeredWindow(
                        windowHandle, WINDOW_BACKGROUND_GRAPHICS_DEVICE_CONTEXT_HANDLE,
                        NULL, NULL,
                        WINDOW_ONSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE,
                        NULL, 0x000000,
                        &blendFunction, ULW_ALPHA | ULW_COLORKEY
                    )) ::printf("[ERROR]: %lu", ::GetLastError());
                }
                ::ShowWindow(windowHandle, WINDOW_APPEARANCE);

                BUTTON_PROCEDURE(WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, message, cursorPosition);
            } break;

            // [Destroy]
            case WM_DESTROY: { // Deletion > Window ...; ...
                ::DeleteDC(WINDOW_BACKGROUND_GRAPHICS_DEVICE_CONTEXT_HANDLE);
                ::DeleteObject(WINDOW_FONT);
                ::DeleteDC(WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE);
                ::DeleteObject(WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_BITMAP_HANDLE);
                ::ReleaseDC(windowHandle, WINDOW_ONSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE);

                ::PostQuitMessage(EXIT_SUCCESS);
                BUTTON_PROCEDURE(WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, message, cursorPosition);
            } break;

            // [Paint]
            case WM_PAINT: { // Update > Window ...; ...
                HGDIOBJ windowOffscreenGraphicsDeviceContextFont;
                COLORREF windowOffscreenGraphicsDeviceContextTextColor;
                RECT windowTextContentRectangle = {};
                LONG const windowTextContentVerticalPadding = 2L;

                windowOffscreenGraphicsDeviceContextFont = ::SelectObject(WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, WINDOW_FONT);
                windowOffscreenGraphicsDeviceContextTextColor = ::SetTextColor(WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, WINDOW_TEXT_COLOR);
                windowTextContentRectangle = {10L, 10L, 100L, 10L};

                ::BitBlt(
                    WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, 0, 0,
                    WINDOW_BACKGROUND_RECTANGLE.right - WINDOW_BACKGROUND_RECTANGLE.left, WINDOW_BACKGROUND_RECTANGLE.bottom - WINDOW_BACKGROUND_RECTANGLE.top,
                    WINDOW_BACKGROUND_GRAPHICS_DEVICE_CONTEXT_HANDLE, 0, 0,
                    SRCCOPY
                );
                for (
                    char const *const textGuides[] = {
                        "Exit Window: 'Alt + F4' hotkey, 'Esc' key",
                        "Fullscreen: 'F11' key",
                        "",
                        "Activate Button: 'Enter' key, 'Left-Click' button",
                        "Select Button: 'Tab' key"
                    }, *const *iterator = textGuides, *const *const end = iterator + (sizeof(textGuides) / sizeof(char*));
                    end != iterator; ++iterator
                ) {
                    windowTextContentRectangle.top = windowTextContentRectangle.bottom + windowTextContentVerticalPadding;
                    windowTextContentRectangle.bottom = WINDOW_FONT_SIZE + windowTextContentRectangle.top + windowTextContentVerticalPadding;

                    ::DrawText(WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, *iterator, -1, &windowTextContentRectangle, DT_LEFT | DT_NOCLIP | DT_SINGLELINE | DT_TOP);
                }
                BUTTON_PROCEDURE(WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, message, cursorPosition);

                ::BitBlt(WINDOW_ONSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, 0, 0, SRCCOPY);

                ::SelectObject(WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, windowOffscreenGraphicsDeviceContextFont);
                ::SetTextColor(WINDOW_OFFSCREEN_GRAPHICS_DEVICE_CONTEXT_HANDLE, windowOffscreenGraphicsDeviceContextTextColor);
                ::ValidateRect(windowHandle, NULL);
            } return EXIT_SUCCESS;
        }

        // [Repaint] Logic
        if (WINDOW_CURRENT_TIMESTAMP == WINDOW_RECENT_TIMESTAMP) {
            // ... Update > Button ... State
            BUTTON_STATE = IDLE; {
                // [Keyboard]
                if (windowHandle == ::GetActiveWindow()) {
                    if (::GetAsyncKeyState(VK_RETURN) & virtualKeySize) BUTTON_STATE = ACTIVE;
                    else if (::GetAsyncKeyState(VK_TAB) & virtualKeySize) BUTTON_STATE = FOCUSED;
                }

                // [Pointer]
                if (::GetCursorPos(&cursorPosition)) {
                    ::MapWindowPoints(HWND_DESKTOP, windowHandle, &cursorPosition, 1); // WARN (Lapys) -> May fail.
                    if (
                        (cursorPosition.x >= BUTTON_RECTANGLE.left && cursorPosition.x <= BUTTON_RECTANGLE.right) &&
                        (cursorPosition.y >= BUTTON_RECTANGLE.top && cursorPosition.y <= BUTTON_RECTANGLE.bottom)
                    ) BUTTON_STATE = ::GetAsyncKeyState(VK_LBUTTON) & virtualKeySize ? ACTIVE : (IDLE == BUTTON_STATE ? HOVERED : BUTTON_STATE);
                }
            }

            // ...
            ::RedrawWindow(windowHandle, NULL, NULL, RDW_INVALIDATE | RDW_NOCHILDREN);
        }

        // [Evaluate, Destroy] ...
        Evaluate: return ::DefWindowProc(windowHandle, message, parameter, subparameter);
        Destroy: ::DestroyWindow(windowHandle); goto Evaluate;
    }

/* Main */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const previousInstanceHandle, LPSTR const, int const appearance) {
    // Initialization > (Exit Code, ...)
    int exitCode = EXIT_SUCCESS;
    HANDLE lock;

    // Update > Window ... --- REDACT (Lapys)
    WINDOW_APPEARANCE = appearance;

    WINDOW_CLASS.cbClsExtra = 0;
    WINDOW_CLASS.cbWndExtra = 0;
    WINDOW_CLASS.hbrBackground = (HBRUSH) ::CreateSolidBrush(WINDOW_BACKGROUND_COLOR);
    WINDOW_CLASS.hCursor = (HCURSOR) ::LoadCursor(NULL, IDC_ARROW); // -> ::LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
    WINDOW_CLASS.hIcon = (HICON) NULL;
    WINDOW_CLASS.hInstance = instanceHandle;
    WINDOW_CLASS.lpfnWndProc = &WINDOW_PROCEDURE;
    WINDOW_CLASS.lpszClassName = "window";
    WINDOW_CLASS.lpszMenuName = NULL;
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
    if (0u == ::RegisterClass(&WINDOW_CLASS)) exitCode = EXIT_FAILURE;
    else {
        // ...; Logic > ...
        ::SystemParametersInfo(SPI_GETWORKAREA, 0u, (PVOID) &WINDOW_BACKGROUND_RECTANGLE, 0u);
        if (NULL != ::CreateWindowEx(
            WS_EX_LAYERED | WS_EX_TRANSPARENT, WINDOW_CLASS.lpszClassName, WINDOW_TITLE, WS_POPUP,
            ((WINDOW_BACKGROUND_RECTANGLE.right - WINDOW_BACKGROUND_RECTANGLE.left) - WINDOW_WIDTH) / 2,
            ((WINDOW_BACKGROUND_RECTANGLE.bottom - WINDOW_BACKGROUND_RECTANGLE.top) - WINDOW_HEIGHT) / 2,
            WINDOW_WIDTH, WINDOW_HEIGHT, NULL, (HMENU) NULL, WINDOW_CLASS.hInstance, NULL
        )) { // ... Window Procedure Message
            MSG windowProcedureMessage = {};
            for (
                BOOL available = FALSE; FALSE == available || WM_QUIT != windowProcedureMessage.message;
                available = ::PeekMessage(&windowProcedureMessage, NULL, 0x0, 0x0, PM_REMOVE)
            ) { ::TranslateMessage(&windowProcedureMessage); ::DispatchMessage(&windowProcedureMessage); }

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
