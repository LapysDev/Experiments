/* ... */
#undef UNICODE

/* Import */
#include <stddef.h> // Standard Definitions
#include <stdlib.h> // Standard Library
#include <stdio.h> // Standard Input/ Output
#include <windows.h> // Windows

/* Global > ... */
COLORREF const BUTTON_BACKGROUND_COLOR = RGB(0, 0, 204); // -> 107
long const BUTTON_BOTTOM_PADDING = 20L, BUTTON_TOP_PADDING = 20L;
COLORREF const BUTTON_COLOR = RGB(255, 255, 255);
char const BUTTON_FONT_FAMILY[] = "Calibri Light";
long const BUTTON_FONT_SIZE = 48L;
long const BUTTON_LEFT_PADDING = 40L, BUTTON_RIGHT_PADDING = 40L;
void BUTTON_PROCEDURE(HWND const, WPARAM const, LPARAM const);
RECT BUTTON_RECTANGLE = {};
enum {ACTIVE, IDLE, DISABLED, FOCUSED, HOVERED} BUTTON_STATE = IDLE;
SYSTEMTIME BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP = {}, BUTTON_STATE_TRANSITION_START_TIMESTAMP = {};
WORD BUTTON_STATE_TRANSITION_DURATION = 0u;
struct { inline operator DWORD(void) const noexcept { return ((86400000uL * BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wDay) + (604800000uL * BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wDayOfWeek) + (3600000uL * BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wHour) + (1uL * BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wMilliseconds) + (60000uL * BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wMinute) + (1000uL * BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wSecond)) - ((86400000uL * BUTTON_STATE_TRANSITION_START_TIMESTAMP.wDay) + (604800000uL * BUTTON_STATE_TRANSITION_START_TIMESTAMP.wDayOfWeek) + (3600000uL * BUTTON_STATE_TRANSITION_START_TIMESTAMP.wHour) + (1uL * BUTTON_STATE_TRANSITION_START_TIMESTAMP.wMilliseconds) + (60000uL * BUTTON_STATE_TRANSITION_START_TIMESTAMP.wMinute) + (1000uL * BUTTON_STATE_TRANSITION_START_TIMESTAMP.wSecond)); } } const BUTTON_STATE_TRANSITION_ELAPSED = {};
char const BUTTON_TEXT_CONTENT[] = "Button";

int WINDOW_APPEARANCE = 0x0;
COLORREF const WINDOW_BACKGROUND_COLOR = RGB(255, 255, 255);
WNDCLASS WINDOW_CLASS = {};
HWND WINDOW_HANDLE = NULL;
int const WINDOW_HEIGHT = 500, WINDOW_WIDTH = 500;
LRESULT CALLBACK WINDOW_PROCEDURE(HWND const, UINT const, WPARAM const, LPARAM const);
MSG WINDOW_PROCEDURE_MESSAGE = {};
unsigned char const WINDOW_REPAINT_RATE = 60u;
char const WINDOW_TITLE[] = "The Button";

/* Update > ... Procedure */
void BUTTON_PROCEDURE(HDC const graphicsDeviceContextHandle, WPARAM const, LPARAM const) {
    COLORREF buttonBackgroundColor = BUTTON_BACKGROUND_COLOR;
    HBRUSH buttonBackgroundColorBrush = NULL;
    struct { WORD red, green, blue; } buttonBackgroundColorChannels = {GetRValue(buttonBackgroundColor), GetGValue(buttonBackgroundColor), GetBValue(buttonBackgroundColor)};
    HFONT buttonFont = ::CreateFont(BUTTON_FONT_SIZE, FW_DONTCARE, FALSE, TRUE, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, BUTTON_FONT_FAMILY);
    float const buttonStateTransitionProgress = (100.0f * (float) BUTTON_STATE_TRANSITION_ELAPSED) / (float) BUTTON_STATE_TRANSITION_DURATION;
    RECT buttonTextContentRectangle = {};
    SIZE buttonTextContentSize = {};

    ::SelectObject(graphicsDeviceContextHandle, buttonFont);
    ::SetBkMode(graphicsDeviceContextHandle, TRANSPARENT);
    ::SetTextColor(graphicsDeviceContextHandle, BUTTON_COLOR);

    ::GetTextExtentPoint32A(graphicsDeviceContextHandle, BUTTON_TEXT_CONTENT, ::strlen(BUTTON_TEXT_CONTENT), &buttonTextContentSize);

    buttonTextContentRectangle.left = (WINDOW_WIDTH - buttonTextContentSize.cx) / 2L;
    buttonTextContentRectangle.top = (WINDOW_HEIGHT - buttonTextContentSize.cy) / 2L;
    buttonTextContentRectangle.bottom = buttonTextContentSize.cy + buttonTextContentRectangle.top;
    buttonTextContentRectangle.right = buttonTextContentSize.cx + buttonTextContentRectangle.left;

    BUTTON_RECTANGLE.bottom = buttonTextContentRectangle.bottom + BUTTON_BOTTOM_PADDING;
    BUTTON_RECTANGLE.left = buttonTextContentRectangle.left - BUTTON_LEFT_PADDING;
    BUTTON_RECTANGLE.right = buttonTextContentRectangle.right + BUTTON_RIGHT_PADDING;
    BUTTON_RECTANGLE.top = buttonTextContentRectangle.top - BUTTON_TOP_PADDING;

    // Logic
    switch (BUTTON_STATE) {
        case ACTIVE: {
            int const intensity = buttonStateTransitionProgress * 51.0f;

            (void) intensity;
            buttonBackgroundColorChannels.blue = 0u;
            buttonBackgroundColorChannels.green = 0u;
            buttonBackgroundColorChannels.red = 255u;
            // buttonBackgroundColorChannels.blue = buttonBackgroundColorChannels.blue + (intensity * (buttonBackgroundColorChannels.blue < 255 / 2 ? 1 : -1));
            // buttonBackgroundColorChannels.green = buttonBackgroundColorChannels.green + (intensity * (buttonBackgroundColorChannels.green < 255 / 2 ? 1 : -1));
            // buttonBackgroundColorChannels.red = buttonBackgroundColorChannels.red + (intensity * (buttonBackgroundColorChannels.red < 255 / 2 ? 1 : -1));
        } break;
        case DISABLED: break;
        case FOCUSED: break;
        case HOVERED: break;

        // ...
        case IDLE: break;
    }
    buttonBackgroundColor = RGB(buttonBackgroundColorChannels.red, buttonBackgroundColorChannels.green, buttonBackgroundColorChannels.blue);
    buttonBackgroundColorBrush = (HBRUSH) ::CreateSolidBrush(buttonBackgroundColor);

    ::FillRect(graphicsDeviceContextHandle, &BUTTON_RECTANGLE, buttonBackgroundColorBrush);
    ::DrawText(graphicsDeviceContextHandle, BUTTON_TEXT_CONTENT, -1, &buttonTextContentRectangle, DT_LEFT | DT_NOCLIP | DT_SINGLELINE | DT_TOP);

    // Deletion
    ::DeleteObject(buttonBackgroundColorBrush);
    ::DeleteObject(buttonFont);
}

// Window Procedure
LRESULT CALLBACK WINDOW_PROCEDURE(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
    return ::DefWindowProc(windowHandle, message, parameter, subparameter);
    // /* [Acknowledge User Event] */ {
    //     // ... Update > Button State Transition ...
    //     ::GetSystemTime(&BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP);
    //     if (0u == BUTTON_STATE_TRANSITION_START_TIMESTAMP.wDay + BUTTON_STATE_TRANSITION_START_TIMESTAMP.wDayOfWeek + BUTTON_STATE_TRANSITION_START_TIMESTAMP.wHour + BUTTON_STATE_TRANSITION_START_TIMESTAMP.wMilliseconds + BUTTON_STATE_TRANSITION_START_TIMESTAMP.wMinute + BUTTON_STATE_TRANSITION_START_TIMESTAMP.wMonth + BUTTON_STATE_TRANSITION_START_TIMESTAMP.wSecond + BUTTON_STATE_TRANSITION_START_TIMESTAMP.wYear) {
    //         BUTTON_STATE_TRANSITION_START_TIMESTAMP.wDay = BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wDay;
    //         BUTTON_STATE_TRANSITION_START_TIMESTAMP.wDayOfWeek = BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wDayOfWeek;
    //         BUTTON_STATE_TRANSITION_START_TIMESTAMP.wHour = BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wHour;
    //         BUTTON_STATE_TRANSITION_START_TIMESTAMP.wMilliseconds = BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wMilliseconds;
    //         BUTTON_STATE_TRANSITION_START_TIMESTAMP.wMinute = BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wMinute;
    //         BUTTON_STATE_TRANSITION_START_TIMESTAMP.wMonth = BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wMonth;
    //         BUTTON_STATE_TRANSITION_START_TIMESTAMP.wSecond = BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wSecond;
    //         BUTTON_STATE_TRANSITION_START_TIMESTAMP.wYear = BUTTON_STATE_TRANSITION_CURRENT_TIMESTAMP.wYear;
    //     }

    //     // Logic > Update > Button State
    //     if (::GetAsyncKeyState(VK_RETURN) & (1u << (sizeof(SHORT) * 8u - 1u))) BUTTON_STATE = ACTIVE;
    // }

    // /* [Process Window] */ {
    //     bool allowRepaint = false;
    //     static unsigned char windowRepaintRate = 0u;

    //     ::printf("\r%*c\r[RATE (%u)]: %u", 64, ' ', message, windowRepaintRate++);
    //     // if (WINDOW_REPAINT_RATE == windowRepaintRate++) {
    //     //     allowRepaint = true;
    //     //     windowRepaintRate = 0u;
    //     // }

    //     // Logic > ...
    //     switch (message) {
    //         case WM_CLOSE: goto Terminate; break;
    //         case WM_DESTROY: ::PostQuitMessage(0); break;
    //         case WM_KEYDOWN: if (parameter == VK_ESCAPE) goto Terminate; break;
    //         case WM_QUIT: goto Terminate; break;
    //         case WM_SYSCOMMAND: if (parameter == SC_CLOSE) goto Terminate; break;
    //         case WM_SYSKEYDOWN: if (parameter == VK_F4) goto Terminate; break;

    //         case WM_PAINT: {
    //             // Initialization > (Paint Information, Graphics Device Context Handle)
    //             PAINTSTRUCT paintInformation = {};
    //             HDC const graphicsDeviceContextHandle = ::BeginPaint(windowHandle, &paintInformation);

    //             // ...
    //             BUTTON_PROCEDURE(graphicsDeviceContextHandle, parameter, subparameter);

    //             // Deletion
    //             ::ReleaseDC(windowHandle, graphicsDeviceContextHandle);
    //             ::EndPaint(windowHandle, &paintInformation);

    //             // ... [Repaint]
    //             if (allowRepaint) ::InvalidateRect(windowHandle, &BUTTON_RECTANGLE, TRUE);
    //         } break;
    //     }
    // }

    // /* [Process User Event] */ {
    //     // Logic
    //     if (IDLE != BUTTON_STATE) {
    //         // ... Update > Button State Transition ...
    //         ::GetSystemTime(&BUTTON_STATE_TRANSITION_START_TIMESTAMP);
    //         switch (BUTTON_STATE) {
    //             case ACTIVE: BUTTON_STATE_TRANSITION_DURATION = 1000u; break;
    //             case DISABLED: BUTTON_STATE_TRANSITION_DURATION = 0u; break;
    //             case FOCUSED: BUTTON_STATE_TRANSITION_DURATION = 0u; break;
    //             case HOVERED: BUTTON_STATE_TRANSITION_DURATION = 0u; break;

    //             // ...
    //             case IDLE: break;
    //         }
    //     }

    //     // Logic > Update > Button State ...
    //     if (BUTTON_STATE_TRANSITION_DURATION < BUTTON_STATE_TRANSITION_ELAPSED) {
    //         BUTTON_STATE = IDLE;
    //         BUTTON_STATE_TRANSITION_DURATION = 0u;
    //     }
    // }

    // // [Evaluate, Terminate] ...
    // Evaluate: return ::DefWindowProc(windowHandle, message, parameter, subparameter);
    // Terminate: ::DestroyWindow(windowHandle); goto Evaluate;
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
    WINDOW_CLASS.style = CS_HREDRAW | CS_VREDRAW;

    WINDOW_PROCEDURE_MESSAGE.lParam = 0x0;
    WINDOW_PROCEDURE_MESSAGE.message = 0x0;
    WINDOW_PROCEDURE_MESSAGE.pt.x = 0L;
    WINDOW_PROCEDURE_MESSAGE.pt.y = 0L;
    WINDOW_PROCEDURE_MESSAGE.wParam = EXIT_SUCCESS;
    WINDOW_PROCEDURE_MESSAGE.time = 0u;

    // Logic
    if (::RegisterClass(&WINDOW_CLASS)) {
        // Initialization > Screen Rectangle
        RECT screenRectangle = {};
        ::SystemParametersInfo(SPI_GETWORKAREA, 0u, (PVOID) &screenRectangle, 0u);

        // Update > Window Handle --- NOTE (Lapys) ->
        WINDOW_HANDLE = ::CreateWindow(
            WINDOW_CLASS.lpszClassName, WINDOW_TITLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            ((screenRectangle.right - screenRectangle.left) - WINDOW_WIDTH) / 2,  // x
            ((screenRectangle.bottom - screenRectangle.top) - WINDOW_HEIGHT) / 2, // y
            WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, WINDOW_CLASS.hInstance, NULL
        );

        // Logic
        if (NULL == WINDOW_HANDLE) { exitCode = EXIT_FAILURE; goto Terminate; }
        else {
            // Update > Window Handle
            ::ShowWindow(WINDOW_HANDLE, WINDOW_APPEARANCE);
            ::UpdateWindow(WINDOW_HANDLE);

            // Loop > Update > Window Procedure message
            while (::PeekMessage(&WINDOW_PROCEDURE_MESSAGE, WINDOW_HANDLE, 0x0, 0x0, PM_REMOVE)) {
                ::TranslateMessage(&WINDOW_PROCEDURE_MESSAGE);
                ::DispatchMessage(&WINDOW_PROCEDURE_MESSAGE);
            }

            // ...
            exitCode = WINDOW_PROCEDURE_MESSAGE.wParam; goto Terminate;
        }
    } else exitCode = EXIT_FAILURE;

    // Terminate; Return
    return exitCode;
    Terminate: {
        ::DeleteObject(WINDOW_CLASS.hbrBackground);
        ::UnregisterClass(WINDOW_CLASS.lpszClassName, WINDOW_CLASS.hInstance);
    } return exitCode;
}
