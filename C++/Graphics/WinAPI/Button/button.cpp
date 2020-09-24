/* ... */
#undef UNICODE

/* Import */
#include <stddef.h> // Standard Definitions
#include <stdlib.h> // Standard Library
#include <stdio.h> // Standard Input/ Output
#include <windows.h> // Windows

/* Global */
    /* Button ... */
    COLORREF const BUTTON_BACKGROUND_COLOR = RGB(0, 0, 204);
    long const BUTTON_BOTTOM_PADDING = 20L, BUTTON_TOP_PADDING = 20L;
    long const BUTTON_LEFT_PADDING = 40L, BUTTON_RIGHT_PADDING = 40L;
    char const BUTTON_FONT_FAMILY[] = "Calibri Light";
    long const BUTTON_FONT_SIZE = 48L;
    void BUTTON_PROCEDURE(HDC const, POINT const);
    RECT BUTTON_RECTANGLE = {};
    enum {ACTIVE, IDLE, DISABLED, FOCUSED, HOVERED} BUTTON_STATE = IDLE, BUTTON_TRANSITION_STATE = BUTTON_STATE;
    COLORREF const BUTTON_TEXT_COLOR = RGB(255, 255, 255);
    char const BUTTON_TEXT_CONTENT[] = "Button";

    /* Window ... */
    int WINDOW_APPEARANCE = 0x0;
    COLORREF const WINDOW_BACKGROUND_COLOR = RGB(255, 255, 255);
    int const WINDOW_HEIGHT = 500, WINDOW_WIDTH = 500;
    char const WINDOW_TITLE[] = "The Button";

    WNDCLASS WINDOW_CLASS = {};
    HDC WINDOW_GRAPHICS_DEVICE_CONTEXT_HANDLE = NULL;
    HWND WINDOW_HANDLE = NULL;
    LRESULT CALLBACK WINDOW_PROCEDURE(HWND const, UINT const, WPARAM const, LPARAM const);
    MSG WINDOW_PROCEDURE_MESSAGE = {};
    WORD const WINDOW_REPAINT_RATE = 1000u / 60u;
    SYSTEMTIME WINDOW_CURRENT_TIMESTAMP = {}, WINDOW_RECENT_TIMESTAMP = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};

/* Function */
    /* Button Procedure */
    void BUTTON_PROCEDURE(HDC const graphicsDeviceContextHandle, POINT const) {
        // Initialization > Button
            // ... Color ...
            COLORREF buttonBackgroundColor = BUTTON_BACKGROUND_COLOR;
            HBRUSH buttonBackgroundColorBrush = NULL;
            struct { WORD red, green, blue; } buttonBackgroundColorChannels = {
                GetRValue(buttonBackgroundColor),
                GetGValue(buttonBackgroundColor),
                GetBValue(buttonBackgroundColor)
            };

            // ... (Font, Text Content) ...
            HFONT const buttonFont = ::CreateFont(BUTTON_FONT_SIZE, FW_DONTCARE, FALSE, TRUE, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, BUTTON_FONT_FAMILY);
            RECT buttonTextContentRectangle = {};
            SIZE buttonTextContentSize = {};

        // Update > (Graphics Device Context, Button Text Content Size)
        ::SelectObject(graphicsDeviceContextHandle, buttonFont);
        ::SetTextColor(graphicsDeviceContextHandle, BUTTON_TEXT_COLOR);

        ::GetTextExtentPoint32A(graphicsDeviceContextHandle, BUTTON_TEXT_CONTENT, ::strlen(BUTTON_TEXT_CONTENT), &buttonTextContentSize);

        // Modification > Button (Text Content) Rectangle > ...
        buttonTextContentRectangle.left = (WINDOW_WIDTH - buttonTextContentSize.cx) / 2L;
        buttonTextContentRectangle.top = (WINDOW_HEIGHT - buttonTextContentSize.cy) / 2L;
        buttonTextContentRectangle.bottom = buttonTextContentSize.cy + buttonTextContentRectangle.top;
        buttonTextContentRectangle.right = buttonTextContentSize.cx + buttonTextContentRectangle.left;

        BUTTON_RECTANGLE.bottom = buttonTextContentRectangle.bottom + BUTTON_BOTTOM_PADDING;
        BUTTON_RECTANGLE.left = buttonTextContentRectangle.left - BUTTON_LEFT_PADDING;
        BUTTON_RECTANGLE.right = buttonTextContentRectangle.right + BUTTON_RIGHT_PADDING;
        BUTTON_RECTANGLE.top = buttonTextContentRectangle.top - BUTTON_TOP_PADDING;

        // Logic > ... Update > Button Background Color Channels
        switch (BUTTON_TRANSITION_STATE) {
            case ACTIVE: buttonBackgroundColorChannels = {255u, 0u, 0u}; break;
            case DISABLED: buttonBackgroundColorChannels = {0u, 0u, 0u}; break;
            case FOCUSED: buttonBackgroundColorChannels = {255u, 107u, 0u}; break;
            case HOVERED: buttonBackgroundColorChannels = {0u, 107u, 255u}; break;

            // ...
            case IDLE: break;
        } buttonBackgroundColor = RGB(buttonBackgroundColorChannels.red, buttonBackgroundColorChannels.green, buttonBackgroundColorChannels.blue);
        buttonBackgroundColorBrush = (HBRUSH) ::CreateSolidBrush(buttonBackgroundColor);

        // ...
        ::FillRect(graphicsDeviceContextHandle, &BUTTON_RECTANGLE, buttonBackgroundColorBrush);
        ::DrawText(graphicsDeviceContextHandle, BUTTON_TEXT_CONTENT, -1, &buttonTextContentRectangle, DT_LEFT | DT_NOCLIP | DT_SINGLELINE | DT_TOP);

        // Deletion
        ::DeleteObject(buttonBackgroundColorBrush);
        ::DeleteObject(buttonFont);
    }

    /* Window Procedure */
    LRESULT CALLBACK WINDOW_PROCEDURE(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
        // Initialization > Prompt Window Repaint
        bool promptWindowRepaint = false;

        // [Process Windows Timestamp] ... Logic > ... Update > Prompt Window Repaint
        ::GetSystemTime(&WINDOW_CURRENT_TIMESTAMP);
        if (WINDOW_REPAINT_RATE < (
            ((8640000uL * WINDOW_CURRENT_TIMESTAMP.wDay) + (60480000uL * WINDOW_CURRENT_TIMESTAMP.wDayOfWeek) + (360000uL * WINDOW_CURRENT_TIMESTAMP.wHour) + (1uL * WINDOW_CURRENT_TIMESTAMP.wMilliseconds) + (60000uL * WINDOW_CURRENT_TIMESTAMP.wMinute) + (1000uL * WINDOW_CURRENT_TIMESTAMP.wSecond)) -
            ((8640000uL * WINDOW_RECENT_TIMESTAMP.wDay) + (60480000uL * WINDOW_RECENT_TIMESTAMP.wDayOfWeek) + (360000uL * WINDOW_RECENT_TIMESTAMP.wHour) + (1uL * WINDOW_RECENT_TIMESTAMP.wMilliseconds) + (60000uL * WINDOW_RECENT_TIMESTAMP.wMinute) + (1000uL * WINDOW_RECENT_TIMESTAMP.wSecond))
        ) || 0u == WINDOW_RECENT_TIMESTAMP.wDay + WINDOW_RECENT_TIMESTAMP.wDayOfWeek + WINDOW_RECENT_TIMESTAMP.wHour + WINDOW_RECENT_TIMESTAMP.wMilliseconds + WINDOW_RECENT_TIMESTAMP.wMinute + WINDOW_RECENT_TIMESTAMP.wMonth + WINDOW_RECENT_TIMESTAMP.wSecond + WINDOW_RECENT_TIMESTAMP.wYear) {
            // ...
            promptWindowRepaint = true;

            WINDOW_RECENT_TIMESTAMP.wDay = WINDOW_CURRENT_TIMESTAMP.wDay;
            WINDOW_RECENT_TIMESTAMP.wDayOfWeek = WINDOW_CURRENT_TIMESTAMP.wDayOfWeek;
            WINDOW_RECENT_TIMESTAMP.wHour = WINDOW_CURRENT_TIMESTAMP.wHour;
            WINDOW_RECENT_TIMESTAMP.wMilliseconds = WINDOW_CURRENT_TIMESTAMP.wMilliseconds;
            WINDOW_RECENT_TIMESTAMP.wMinute = WINDOW_CURRENT_TIMESTAMP.wMinute;
            WINDOW_RECENT_TIMESTAMP.wMonth = WINDOW_CURRENT_TIMESTAMP.wMonth;
            WINDOW_RECENT_TIMESTAMP.wSecond = WINDOW_CURRENT_TIMESTAMP.wSecond;
            WINDOW_RECENT_TIMESTAMP.wYear = WINDOW_CURRENT_TIMESTAMP.wYear;
        }

        // [Process Windows Message] Logic > ...
        switch (message) {
            case WM_CLOSE: goto Terminate; break;
            case WM_DESTROY: ::PostQuitMessage(EXIT_SUCCESS); break;
            case WM_KEYDOWN: if (VK_ESCAPE == parameter) goto Terminate; break;
            case WM_SYSCOMMAND: if (SC_CLOSE == parameter) goto Terminate; break;
            case WM_SYSKEYDOWN: if (VK_F4 == parameter) goto Terminate; break;
        }

        // [Repaint] ...
        if (promptWindowRepaint) {
            // Initialization > ...
            POINT cursorPosition = {};
            constexpr SHORT const virtualKeySize = (SHORT) (1 << (sizeof(SHORT) * 8 - 1));

            /* ... Update > Button ... State */ BUTTON_STATE = IDLE; {
                // [Pointer]
                if (::GetCursorPos(&cursorPosition) && ::ScreenToClient(WINDOW_HANDLE, &cursorPosition)) {
                    if (
                        (cursorPosition.x >= BUTTON_RECTANGLE.left && cursorPosition.x <= BUTTON_RECTANGLE.right) &&
                        (cursorPosition.y >= BUTTON_RECTANGLE.top && cursorPosition.y <= BUTTON_RECTANGLE.bottom)
                    ) BUTTON_STATE = HOVERED;
                }

                // [Keyboard]
                if (WINDOW_HANDLE == ::GetActiveWindow()) {
                    if (::GetAsyncKeyState(VK_RETURN) & virtualKeySize) BUTTON_STATE = ACTIVE;
                    else if (::GetAsyncKeyState(VK_TAB) & virtualKeySize) BUTTON_STATE = FOCUSED;
                }
            } BUTTON_TRANSITION_STATE = BUTTON_STATE;

            // ...
            BUTTON_PROCEDURE(WINDOW_GRAPHICS_DEVICE_CONTEXT_HANDLE, cursorPosition);
        }

        // [Evaluate, Terminate] ...
        Evaluate: return ::DefWindowProc(windowHandle, message, parameter, subparameter);
        Terminate: ::DestroyWindow(windowHandle); goto Evaluate;
    }

/* Main */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const, LPSTR const, int const appearance) {
    // Initialization > Exit Code
    int exitCode = EXIT_SUCCESS;

    // Update > Window ...
    WINDOW_APPEARANCE = appearance;

    WINDOW_CLASS.cbClsExtra = 0;
    WINDOW_CLASS.cbWndExtra = 0;
    WINDOW_CLASS.hbrBackground = (HBRUSH) ::CreateSolidBrush(WINDOW_BACKGROUND_COLOR);
    WINDOW_CLASS.hCursor = (HCURSOR) ::LoadCursor(NULL, IDC_ARROW);
    WINDOW_CLASS.hIcon = NULL;
    WINDOW_CLASS.hInstance = instanceHandle;
    WINDOW_CLASS.lpfnWndProc = &WINDOW_PROCEDURE;
    WINDOW_CLASS.lpszClassName = "window";
    WINDOW_CLASS.lpszMenuName = NULL;
    WINDOW_CLASS.style = 0x0;

    WINDOW_PROCEDURE_MESSAGE.lParam = 0x0;
    WINDOW_PROCEDURE_MESSAGE.message = WM_NULL;
    WINDOW_PROCEDURE_MESSAGE.pt = {0L, 0L};
    WINDOW_PROCEDURE_MESSAGE.wParam = EXIT_SUCCESS;
    WINDOW_PROCEDURE_MESSAGE.time = 0u;

    // Logic > ...
    if (0u == ::RegisterClass(&WINDOW_CLASS)) exitCode = EXIT_FAILURE;
    else {
        // Initialization > Screen Rectangle
        RECT screenRectangle = {};

        // Update > (..., Window Handle) --- NOTE (Lapys) ->
        ::SystemParametersInfo(SPI_GETWORKAREA, 0u, (PVOID) &screenRectangle, 0u);
        WINDOW_HANDLE = ::CreateWindow(
            WINDOW_CLASS.lpszClassName, WINDOW_TITLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            ((screenRectangle.right - screenRectangle.left) - WINDOW_WIDTH) / 2,  // x
            ((screenRectangle.bottom - screenRectangle.top) - WINDOW_HEIGHT) / 2, // y
            WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, WINDOW_CLASS.hInstance, NULL
        );

        // Logic > ...
        if (NULL == WINDOW_HANDLE) { exitCode = EXIT_FAILURE; goto PreTerminate; }
        else {
            // Update > Window ...
            WINDOW_GRAPHICS_DEVICE_CONTEXT_HANDLE = ::GetWindowDC(WINDOW_HANDLE);
            ::SetBkMode(WINDOW_GRAPHICS_DEVICE_CONTEXT_HANDLE, TRANSPARENT);

            ::ShowWindow(WINDOW_HANDLE, WINDOW_APPEARANCE);
            ::UpdateWindow(WINDOW_HANDLE);

            // Loop > Update > Window Procedure message
            for (
                BOOL available = FALSE; false == available || WM_QUIT != WINDOW_PROCEDURE_MESSAGE.message;
                available = ::PeekMessage(&WINDOW_PROCEDURE_MESSAGE, NULL, 0x0, 0x0, PM_REMOVE)
            ) {
                ::TranslateMessage(&WINDOW_PROCEDURE_MESSAGE);
                ::DispatchMessage(&WINDOW_PROCEDURE_MESSAGE);
            }

            // ...
            exitCode = WINDOW_PROCEDURE_MESSAGE.wParam;
            goto PreTerminate;
        }
    }

    // [... Terminate] ...
    Terminate: return exitCode;
    PreTerminate: {
        ::DeleteObject(WINDOW_CLASS.hbrBackground);
        ::UnregisterClass(WINDOW_CLASS.lpszClassName, WINDOW_CLASS.hInstance);
        ::ReleaseDC(WINDOW_HANDLE, WINDOW_GRAPHICS_DEVICE_CONTEXT_HANDLE);
    } goto Terminate;
}
