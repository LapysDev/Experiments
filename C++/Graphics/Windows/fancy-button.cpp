/* ...
    --- CODE (Lapys) -> C++20
        advapi32.lib, dwmapi.lib, gdi32.lib, kernel32.lib, msimg32.lib, user32.lib

    --- NOTE (Lapys) -> Single window; Single animated, stylized button.
    --- WARN (Lapys) -> Double-buffering not implemented.
*/

/* Definitions > ... */
#define NO_STRICT
#define WIN32_LEAN_AND_MEAN

#undef STRICT
#undef UNICODE

/* Import */
#include <stdio.h>

#include <stddef.h> // Standard Definitions
#include <stdlib.h> // Standard Library
#include <windows.h> // Windows
#include <windowsx.h> // Windows Extensions
#   include <basetsd.h> // Basic Types Definition
#   include <dwmapi.h> // Desktop Window Manager API
#   include <heapapi.h> // Heap API
#   include <windef.h> // Windows Definitions
#   ifndef NOGDI // Windows GDI (Graphics Device Interface)
#       include <wingdi.h>
#   endif
#   include <winnt.h> // Windows NT
#   include <winuser.h> // Windows User

/* Polyfill > Print Window > Render Full Content */
#ifndef PW_RENDERFULLCONTENT
#   define PW_RENDERFULLCONTENT 0x00000002
#endif

/* Global */
    /* ... */
    static ULONG64 CURRENT_TIMESTAMP = 0uL, RECENT_TIMESTAMP = 0uL;
    static WORD const REPAINT_RATE = 1000u / 60u;
    static ULONG TIMESTAMP_FREQUENCY = 2000uL;

    /* Button ... */
    static struct {
        struct { HFONT font = NULL; } handles = {};
        struct {
            struct {
                COLORREF const color = RGB(0x00, 0x00, 0xFF) /* ?? ::GetSysColor(COLOR_WINDOW) */;
            } const background = {};

            struct {
                LPCSTR const family = "Calibri Light";
                LONG const size = 48L;
            } const font = {};

            struct {
                LONG const bottom = 20L, top = 20L;
                LONG const left = 40L, right = 40L;
            } const padding = {};

            COLORREF const color = RGB(0xFF, 0xFF, 0xFF);
            INT const height = -1; // NOTE (Lapys) -> Negative values denote automatic sizes.
            INT const width = -1;
        } const style = {};

        static VOID CALLBACK procedure(UINT const, WPARAM const, LPARAM const);
        RECT rectangle = {0L, 0L, 0L, 0L};
        enum states {ACTIVE, IDLE, DISABLED, FOCUSED, HOVERED} state = IDLE;
        LPCSTR const textContent = "Button";
    } BUTTON = {};

    /* Window ... */
    static struct {
        struct {
            HDC deviceContext = NULL;
            HFONT font = NULL;
            HDC memoryDeviceContext = NULL;
            HBITMAP memoryDeviceContextBitmap = NULL;
        } handles = {};

        struct {
            struct {
                COLORREF const color = RGB(0x00, 0x30, 0xCC) /* ?? ::GetSysColor(COLOR_WINDOW) */;
                BYTE const opacity = 127u;
            } const background = {};

            struct {
                LPCSTR const family = "Calibri Light";
                LONG const size = 18L;
            } const font = {};

            COLORREF const color = RGB(0xFF, 0xFF, 0xFF);
            INT const height = 500;
            INT const width = 500;
        } const style = {};

        INT appearance = 0x0;
        WNDCLASSEX classInformation = {};
        HWND handle = NULL;
        static LRESULT CALLBACK procedure(HWND const, UINT const, WPARAM const, LPARAM const);
        RECT rectangle = {0L, 0L, 0L, 0L};
        LPCSTR const title = "Fancy Button";
    } WINDOW = {};

/* Modification > ... > Procedure */
    /* Button */
    VOID CALLBACK decltype(BUTTON)::procedure(UINT const message, WPARAM const parameter, LPARAM const subparameter) {
        // Constant > (Cursor Position, Window Device Context Handle)
        POINT const cursorPosition = 0x0 == subparameter ? POINT() : *(POINT const*) subparameter;
        HDC const& windowDeviceContextHandle = (HDC) parameter;

        // Logic
        switch (message) {
            // [Create, Destroy]
            case WM_CREATE: BUTTON.handles.font = ::CreateFont(BUTTON.style.font.size, FW_DONTCARE, FALSE, TRUE, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, BUTTON.style.font.family); break;
            case WM_DESTROY: ::DeleteObject(BUTTON.handles.font); break;

            // [Paint] --- CHECKPOINT (Lapys)
            case WM_PAINT: {
                (void) cursorPosition;
                (void) windowDeviceContextHandle;
            } break;
        }
    }

    /* Window */
    LRESULT CALLBACK decltype(WINDOW)::procedure(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
        // Initialization
        // : Cursor Position ...
        static POINT cursorPosition = {};
        static BOOL cursorPositionEvaluated = FALSE;

        // : Window Background
        static struct {
            struct {
                HDC deviceContext;
                HBITMAP deviceContextBitmap;
            } handles = {};

            struct { HWND handle; BYTE opacity; RECT rectangle; }
                windowInformation = {NULL, 0u, {0L, 0L, 0L, 0L}},
                *windowInformationList = NULL;
            unsigned windowInformationListLength = 0u;
        } windowBackground = {};

        // : ...
        LPVOID allocation = NULL;
        constexpr SHORT const virtualKeySize = (SHORT) (1 << (sizeof(SHORT) * 8 - 1));

        /* [Update] */ {
            // Update > (Current, Recent) Timestamp
            CURRENT_TIMESTAMP = __rdtsc();
            RECENT_TIMESTAMP = 0uL == RECENT_TIMESTAMP || REPAINT_RATE < (CURRENT_TIMESTAMP - RECENT_TIMESTAMP) / TIMESTAMP_FREQUENCY / 1000uL ? CURRENT_TIMESTAMP : RECENT_TIMESTAMP;

            // Modification > (Button, Window) > ...
            BUTTON.state = BUTTON.states::IDLE;

            WINDOW.handle = windowHandle;
            ::GetWindowRect(WINDOW.handle, &WINDOW.rectangle);
        }

        // [Tick] Logic --- CHECKPOINT (Lapys)
        if (CURRENT_TIMESTAMP == RECENT_TIMESTAMP) {
            ::RedrawWindow(WINDOW.handle, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_NOCHILDREN);
        }

        // [Dispatch Message] Logic
        switch (message) {
            // [...]
            case WM_CLOSE: goto Destroy;
            case WM_ERASEBKGND: return EXIT_SUCCESS;
            case WM_SYSCOMMAND: if (SC_CLOSE == parameter) goto Destroy; break;
            case WM_SYSKEYDOWN: if (VK_F4 == parameter) goto Destroy; break;

            // [Create]
            case WM_CREATE: {
                // Modification > ...
                WINDOW.handles.deviceContext = ::GetDCEx(WINDOW.handle, NULL, CS_OWNDC | DCX_NORESETATTRS);
                WINDOW.handles.font = ::CreateFont(WINDOW.style.font.size, FW_DONTCARE, FALSE, TRUE, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, WINDOW.style.font.family);
                WINDOW.handles.memoryDeviceContext = ::CreateCompatibleDC(WINDOW.handles.deviceContext);
                WINDOW.handles.memoryDeviceContextBitmap = ::CreateCompatibleBitmap(WINDOW.handles.deviceContext, WINDOW.style.width, WINDOW.style.height);

                windowBackground.handles.deviceContext = ::CreateCompatibleDC(WINDOW.handles.deviceContext);
                windowBackground.handles.deviceContextBitmap = ::CreateCompatibleBitmap(WINDOW.handles.deviceContext, ::GetSystemMetrics(SM_CXMAXTRACK), ::GetSystemMetrics(SM_CYMAXTRACK));
                if (255u ^ WINDOW.style.background.opacity) ::CopyMemory(&windowBackground.windowInformationList, &(allocation = ::HeapAlloc(::GetProcessHeap(), HEAP_NO_SERIALIZE, 16u * sizeof(windowBackground.windowInformation))), sizeof(void*));

                // Update > ...
                ::SelectObject(WINDOW.handles.memoryDeviceContext, WINDOW.handles.memoryDeviceContextBitmap);
                ::SetBkMode(WINDOW.handles.memoryDeviceContext, TRANSPARENT);
                ::ShowWindow(WINDOW.handle, WINDOW.appearance);

                ::SelectObject(windowBackground.handles.deviceContext, windowBackground.handles.deviceContextBitmap);

                // ...
                BUTTON.procedure(message, 0x0, 0x0);
            } break;

            // [Destroy]
            case WM_DESTROY: {
                // Deletion
                ::DeleteDC(windowBackground.handles.deviceContext);
                ::DeleteObject(windowBackground.handles.deviceContextBitmap);
                if (NULL != windowBackground.windowInformationList) ::HeapFree(::GetProcessHeap(), HEAP_NO_SERIALIZE, (LPVOID) windowBackground.windowInformationList);

                ::DeleteObject(WINDOW.handles.font);
                ::DeleteDC(WINDOW.handles.memoryDeviceContext); // NOTE (Lapys) -> The selected bitmap handle gets released here.
                ::DeleteObject(WINDOW.handles.memoryDeviceContextBitmap);
                ::ReleaseDC(WINDOW.handle, WINDOW.handles.deviceContext);

                // Terminate; ...
                ::PostQuitMessage(EXIT_SUCCESS);
                BUTTON.procedure(message, 0x0, 0x0);
            } break;

            // [Key ...]
            case WM_KEYDOWN:
            case WM_KEYUP: {
                // Logic > ...
                if (VK_ESCAPE == parameter) goto Destroy;
                switch (parameter) {
                    case VK_RETURN: if (
                        BUTTON.states::IDLE == BUTTON.state ||
                        BUTTON.states::HOVERED == BUTTON.state
                    ) { BUTTON.state = BUTTON.states::ACTIVE; } break;

                    case VK_TAB: if (WM_KEYUP == message) {
                        decltype(BUTTON)::states const state = ::GetAsyncKeyState(VK_SHIFT) & virtualKeySize ? BUTTON.states::DISABLED : BUTTON.states::FOCUSED;
                        BUTTON.state = BUTTON.state == state ? BUTTON.states::IDLE : state;
                    } break;
                }
            } break;

            // [Mouse Move]
            case WM_MOUSEMOVE: {
                // Update > Cursor Position ...
                cursorPosition.x = GET_X_LPARAM(subparameter);
                cursorPosition.y = GET_Y_LPARAM(subparameter);
                cursorPositionEvaluated = true;

                // Logic > Modification > Button > State
                if (BUTTON.states::IDLE == BUTTON.state && (
                    (cursorPosition.x >= BUTTON.rectangle.left && cursorPosition.x <= BUTTON.rectangle.right) &&
                    (cursorPosition.y >= BUTTON.rectangle.top && cursorPosition.y <= BUTTON.rectangle.bottom)
                )) BUTTON.state = BUTTON.states::HOVERED;
            } break;

            // [Paint]
            case WM_PAINT: {
                // Constant > Window Memory Device Context Information
                struct {
                    HGDIOBJ const fontHandle = ::SelectObject(WINDOW.handles.memoryDeviceContext, WINDOW.handles.font);
                    COLORREF const textColor = ::SetTextColor(WINDOW.handles.memoryDeviceContext, WINDOW.style.color);
                } const windowMemoryDeviceContextInformation = {};

                /* ... */ {
                    /* [Transparent Background] */
                    if (255u ^ WINDOW.style.background.opacity) {
                        // Modification > Window Background > Window Information List Length
                        windowBackground.windowInformationListLength = 0u;

                        // Loop > Logic --- NOTE (Lapys) -> Iterate background windows.
                        for (HWND windowHandle = WINDOW.handle; NULL != windowHandle; windowHandle = ::GetWindow(windowHandle, GW_HWNDNEXT))
                        if (windowHandle == ::GetAncestor(windowHandle, GA_ROOT)) {
                            // Logic --- NOTE (Lapys) -> Do not iterate the current `WINDOW`.
                            if (WINDOW.handle != windowHandle) {
                                // Initialization > Window Is Cloaked
                                INT windowIsCloaked = FALSE;

                                // ... Logic --- NOTE (Lapys) -> Ignore cloaked, iconic, & non-visible windows.
                                ::DwmGetWindowAttribute(windowHandle, DWMWA_CLOAKED, &windowIsCloaked, sizeof(INT));
                                if (FALSE == windowIsCloaked && FALSE == ::IsIconic(windowHandle) && ::IsWindowVisible(windowHandle)) {
                                    // Initialization > Window ...
                                    HDC const windowDeviceContextHandle = ::GetDCEx(windowHandle, NULL, CS_OWNDC | DCX_NORESETATTRS | DCX_WINDOW);
                                    RECT windowHitTestRectangle = {};
                                    RECT windowRectangle = {};

                                    // ... Logic --- NOTE (Lapys) -> Ignore non-intersecting / wrapping windows (against the `WINDOW`).
                                    ::GetWindowRect(windowHandle, &windowRectangle);
                                    if (
                                        ::IntersectRect(&windowHitTestRectangle, &windowRectangle, &WINDOW.rectangle) &&
                                        NULLREGION != ::GetClipBox(windowDeviceContextHandle, &windowHitTestRectangle)
                                    ) {
                                        // Initialization > Window (Is Obscured, Opacity)
                                        BOOL windowIsObscured = FALSE;
                                        BYTE windowOpacity = 255u;

                                        // Logic --- NOTE (Lapys) -> Assert translucent windows.
                                        if (::GetWindowLongPtr(WINDOW.handle, GWL_EXSTYLE) & WS_EX_LAYERED) {
                                            // Update > Window (Is Obscured, Opacity)
                                            ::GetLayeredWindowAttributes(windowHandle, NULL, &windowOpacity, NULL);
                                            windowIsObscured = 255u ^ windowOpacity;
                                        }

                                        // Logic --- NOTE (Lapys) -> Ignore non-intersecting / wrapping windows (against other background windows).
                                        if (FALSE == windowIsObscured)
                                        for (unsigned iterator = windowBackground.windowInformationListLength; iterator--; ) {
                                            // Constant > ... Background Window Rectangle
                                            RECT const& windowBackgroundWindowRectangle = (windowBackground.windowInformationList + iterator) -> rectangle;

                                            // ... Update > Window Is Obscured
                                            if (
                                                windowRectangle.bottom <= windowBackgroundWindowRectangle.bottom &&
                                                windowRectangle.left <= windowBackgroundWindowRectangle.left &&
                                                windowRectangle.right >= windowBackgroundWindowRectangle.right &&
                                                windowRectangle.top <= windowBackgroundWindowRectangle.top
                                            ) { windowIsObscured = TRUE; break; }
                                        }

                                        // Logic --- NOTe (Lapys) -> Ignore obscured windows.
                                        if (FALSE == windowIsObscured) {
                                            // Constant > ... Size
                                            HANDLE const processHeap = ::GetProcessHeap();
                                            SIZE_T const windowBackgroundWindowInformationListSize = ::HeapSize(processHeap, HEAP_NO_SERIALIZE, windowBackground.windowInformationList);

                                            // ... Update > (Window Background > Window Information List)
                                            if (windowBackgroundWindowInformationListSize == windowBackground.windowInformationListLength * sizeof(windowBackground.windowInformation))
                                            ::CopyMemory(&windowBackground.windowInformationList, &(allocation = ::HeapReAlloc(processHeap, HEAP_NO_SERIALIZE, windowBackground.windowInformationList, ((windowBackgroundWindowInformationListSize * 3u) / 2u) * sizeof(windowBackground.windowInformation))), sizeof(void*));

                                            // Update > (Window Background > Window Information List ...)
                                            windowBackground.windowInformationList[windowBackground.windowInformationListLength++] = {
                                                windowHandle, windowOpacity, windowRectangle
                                            };
                                        }
                                    }

                                    // Deletion
                                    ::ReleaseDC(windowHandle, windowDeviceContextHandle);
                                }
                            }
                        }

                        // Loop --- NOTE (Lapys) -> Iterate directly "underlapping" windows.
                        for (unsigned iterator = windowBackground.windowInformationListLength; iterator--; ) {
                            // Constant > ... Background Window (Window Handle, Opacity, Rectangle)
                            BOOL const windowIsPopup = 0 == (::GetWindowLongPtr(WINDOW.handle, GWL_STYLE) & WS_POPUP);

                            HWND const& windowBackgroundWindowHandle = (windowBackground.windowInformationList + iterator) -> handle;
                            RECT& windowBackgroundWindowRectangle = (windowBackground.windowInformationList + iterator) -> rectangle;
                            BYTE const& windowBackgroundWindowOpacity = (windowBackground.windowInformationList + iterator) -> opacity;

                            // Modification > ... Background Window Rectangle
                            windowBackgroundWindowRectangle.bottom -= windowBackgroundWindowRectangle.top;
                            windowBackgroundWindowRectangle.right -= windowBackgroundWindowRectangle.left;

                            windowBackgroundWindowRectangle.left -= WINDOW.rectangle.left;
                            windowBackgroundWindowRectangle.left -= windowIsPopup * ::GetSystemMetrics(SM_CXSIZEFRAME);

                            windowBackgroundWindowRectangle.top -= WINDOW.rectangle.top;
                            windowBackgroundWindowRectangle.top -= windowIsPopup * (::GetSystemMetrics(SM_CYCAPTION) + ::GetSystemMetrics(SM_CYSIZEFRAME));

                            (windowBackgroundWindowRectangle.bottom > WINDOW.style.height - windowBackgroundWindowRectangle.top) &&
                            (windowBackgroundWindowRectangle.bottom = WINDOW.style.height - windowBackgroundWindowRectangle.top);

                            (windowBackgroundWindowRectangle.right > WINDOW.style.width - windowBackgroundWindowRectangle.left) &&
                            (windowBackgroundWindowRectangle.right = WINDOW.style.width - windowBackgroundWindowRectangle.left);

                            // ...
                            ::PrintWindow(windowBackgroundWindowHandle, windowBackground.handles.deviceContext, PW_RENDERFULLCONTENT);
                            255u == windowBackgroundWindowOpacity ?
                                ::BitBlt(WINDOW.handles.memoryDeviceContext, windowBackgroundWindowRectangle.left, windowBackgroundWindowRectangle.top, windowBackgroundWindowRectangle.right, windowBackgroundWindowRectangle.bottom, windowBackground.handles.deviceContext, 0, 0, SRCCOPY) :
                                ::AlphaBlend(WINDOW.handles.memoryDeviceContext, windowBackgroundWindowRectangle.left, windowBackgroundWindowRectangle.top, windowBackgroundWindowRectangle.right, windowBackgroundWindowRectangle.bottom, windowBackground.handles.deviceContext, 0, 0, windowBackgroundWindowRectangle.right, windowBackgroundWindowRectangle.bottom, BLENDFUNCTION {AC_SRC_OVER, 0x0, windowBackgroundWindowOpacity, AC_SRC_ALPHA});
                        }
                    }

                    /* [Solid Brush Background] ... */
                    RECT windowRectangle = {0L, 0L, WINDOW.style.width, WINDOW.style.height};

                    ::FillRect(windowBackground.handles.deviceContext, &windowRectangle, WINDOW.classInformation.hbrBackground);
                    ::AlphaBlend(
                        WINDOW.handles.memoryDeviceContext,
                        0, 0, WINDOW.style.width, WINDOW.style.height,

                        windowBackground.handles.deviceContext,
                        0, 0, WINDOW.style.width, WINDOW.style.height,

                        BLENDFUNCTION {AC_SRC_OVER, 0x0, 255u, AC_SRC_ALPHA}
                    );

                    /* [Button] ... */
                    if (cursorPositionEvaluated) {
                        // Reset > Cursor Position Evaluated; ...
                        cursorPositionEvaluated = false;
                        BUTTON.procedure(message, (WPARAM) WINDOW.handles.memoryDeviceContext, (LPARAM) &cursorPosition);
                    }

                    /* [Text Guides] */ if (false) {
                        // Initialization > Window Text Content ...
                        RECT windowTextContentRectangle = {10L, 10L, 100L, 10L};
                        LONG const windowTextContentVerticalPadding = 2L;

                        // Loop
                        for (char const *const textGuides[] = {
                            "Exit Window: 'Alt + F4' hotkey, 'Esc' key", "Fullscreen: 'F11' key", "",
                            "Activate Button: 'Enter' key, 'Left-Click' button", "Select Button: 'Tab' key"
                        }, *const *iterator = textGuides, *const *const end = iterator + (sizeof(textGuides) / sizeof(char const*)); end != iterator; ++iterator) {
                            // Constant > Text Guide
                            char const *const &textGuide = *iterator;

                            // Modification > Window Text Content Rectangle > (Bottom, Top)
                            windowTextContentRectangle.top = windowTextContentRectangle.bottom + windowTextContentVerticalPadding;
                            windowTextContentRectangle.bottom = WINDOW.style.font.size + windowTextContentRectangle.top + windowTextContentVerticalPadding;

                            // ...
                            ::DrawText(WINDOW.handles.memoryDeviceContext, textGuide, -1, &windowTextContentRectangle, DT_LEFT | DT_NOCLIP | DT_SINGLELINE | DT_TOP);
                        }
                    }
                }

                // ...
                ::BitBlt(WINDOW.handles.deviceContext, 0, 0, WINDOW.style.width, WINDOW.style.height, WINDOW.handles.memoryDeviceContext, 0, 0, SRCCOPY);

                // Reset > Window ...
                ::SelectObject(WINDOW.handles.memoryDeviceContext, windowMemoryDeviceContextInformation.fontHandle);
                ::SetTextColor(WINDOW.handles.memoryDeviceContext, windowMemoryDeviceContextInformation.textColor);
                ::ValidateRect(WINDOW.handle, NULL);
            } return EXIT_SUCCESS;
        }

        // [Evaluate, Destroy] ...
        Evaluate: return ::DefWindowProc(WINDOW.handle, message, parameter, subparameter);
        Destroy: ::DestroyWindow(WINDOW.handle); goto Evaluate;
    }

/* Main */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const previousInstanceHandle, LPSTR const, int const appearance) {
    // Initialization > (Exit Code, Lock Handle)
    int exitCode = EXIT_SUCCESS;
    HANDLE lockHandle = NULL;

    // Update > Timestamp Frequency --- REDACT (Lapys)
    TIMESTAMP_FREQUENCY = 2000uL; {
        HKEY registryKeyHandle;
        if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0u, KEY_READ, &registryKeyHandle)) {
            ULONG registryKeyValueSize = 4uL;

            ::RegQueryValueEx(registryKeyHandle, "~MHz", NULL, NULL, (LPBYTE) &TIMESTAMP_FREQUENCY, &registryKeyValueSize);
            ::RegCloseKey(registryKeyHandle);
        }
    }

    // Modification > Window > (Appearance, Class Information)
    WINDOW.appearance = appearance;

    WINDOW.classInformation.cbClsExtra = 0;
    WINDOW.classInformation.cbSize = sizeof(WNDCLASSEX);
    WINDOW.classInformation.cbWndExtra = 0;
    WINDOW.classInformation.hIcon = (HICON) NULL;
    WINDOW.classInformation.hIconSm = (HICON) NULL;
    WINDOW.classInformation.hInstance = instanceHandle; // -> ::GetModuleHandle(NULL);
    WINDOW.classInformation.hCursor = (HCURSOR) ::LoadCursor(NULL, IDC_ARROW); // -> ::LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
    WINDOW.classInformation.hbrBackground = (HBRUSH) ::CreateSolidBrush(WINDOW.style.background.color) /* ?? ::GetSysColorBrush(COLOR_WINDOW) */;
    WINDOW.classInformation.lpfnWndProc = &WINDOW.procedure;
    WINDOW.classInformation.lpszClassName = "window";
    WINDOW.classInformation.lpszMenuName = (LPCSTR) NULL;
    WINDOW.classInformation.style = CS_GLOBALCLASS | CS_OWNDC;

    /* [Assert Previous (Program) Instance by ...]
        --- NOTE (Lapys) -> Terminate on previous running instance.
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

            // ... Update > Lock Handle
            if (0u == ::GetTempPath(MAX_PATH + 1u, lockFilePath)) goto AssertPreviousInstanceByMutex;
            if (0u == ::GetTempFileName(lockFilePath, "", 0000, lockFileName)) goto AssertPreviousInstanceByMutex;
            lockHandle = ::CreateFile(lockFileName, GENERIC_READ, 0u, NULL, CREATE_NEW, FILE_FLAG_DELETE_ON_CLOSE, NULL);

            // Logic > ...
            if (INVALID_HANDLE_VALUE == lockHandle) goto AssertPreviousInstanceByMutex;
            switch (::GetLastError()) {
                case ERROR_FILE_EXISTS: exitCode = EXIT_FAILURE; goto Terminate;
                case ERROR_SUCCESS: break;
                default: goto AssertPreviousInstanceByMutex;
            } goto EvaluatedPreviousInstance;
        }

        // [Mutex]
        goto AssertPreviousInstanceByMutex;
        AssertPreviousInstanceByMutex: {
            // ... Update > Lock Handle
            lockHandle = ::CreateMutex(NULL, TRUE, "PreviousInstanceAssertion");

            // Logic > ...
            if (NULL != lockHandle)
            switch (::GetLastError()) {
                case ERROR_ALREADY_EXISTS: exitCode = EXIT_FAILURE; goto Terminate;
                case ERROR_SUCCESS: break;
            } goto EvaluatedPreviousInstance;
        }

        // [...]
        EvaluatedPreviousInstance: {}
    }

    // Logic > ...
    if (0x0 == ::RegisterClassEx((WNDCLASSEX const*) &WINDOW.classInformation)) exitCode = EXIT_FAILURE;
    else {
        // Modification > Window > (Handle, Rectangle) ...
        ::SystemParametersInfo(SPI_GETWORKAREA, 0u, (PVOID) &WINDOW.rectangle, 0x0); {
            WINDOW.rectangle.left = ((WINDOW.rectangle.right - WINDOW.rectangle.left) - WINDOW.style.width) / 2L;
            WINDOW.rectangle.top = ((WINDOW.rectangle.bottom - WINDOW.rectangle.top) - WINDOW.style.height) / 2L;
            WINDOW.rectangle.bottom = WINDOW.rectangle.left + WINDOW.style.width;
            WINDOW.rectangle.right = WINDOW.rectangle.top + WINDOW.style.height;
        }

        WINDOW.handle = ::CreateWindowEx(
            0x0, WINDOW.classInformation.lpszClassName, WINDOW.title, WS_OVERLAPPEDWINDOW,
            WINDOW.rectangle.left, WINDOW.rectangle.top, WINDOW.style.width, WINDOW.style.height,
            HWND_DESKTOP, (HMENU) NULL, WINDOW.classInformation.hInstance, (LPVOID) /*(LPARAM) */NULL
        );

        // Logic > ...
        if (NULL == WINDOW.handle) exitCode = EXIT_FAILURE;
        else {
            // ...; Loop > Update ...
            MSG threadMessage = {};
            for (
                BOOL threadMessageAvailable = FALSE; FALSE == threadMessageAvailable || WM_QUIT != threadMessage.message;
                threadMessageAvailable = ::PeekMessage(&threadMessage, NULL, 0x0, 0x0, PM_REMOVE)
            ) ::DispatchMessage(&threadMessage);

            // Update > Exit Code
            exitCode = threadMessage.wParam;
        }

        goto TerminateWithCleanup;
    }

    // [Terminate ...] ...
    Terminate: return exitCode;
    TerminateWithCleanup: {
        ::DestroyCursor(WINDOW.classInformation.hCursor);
        ::UnregisterClass(WINDOW.classInformation.lpszClassName, WINDOW.classInformation.hInstance);

        if (INVALID_HANDLE_VALUE != lockHandle && NULL != lockHandle) ::CloseHandle(lockHandle);
    } goto Terminate;
}
