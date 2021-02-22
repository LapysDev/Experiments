/* Import */
#include <windows.h> // Windows

/* Function > ... */
LRESULT CALLBACK windowProcedure(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
    // [Dispatch Message] Logic
    switch (message) {
        // [...]
        case WM_CLOSE: goto Destroy;
        case WM_KEYDOWN: if (VK_ESCAPE == parameter) goto Destroy; break;
        case WM_SYSCOMMAND: if (SC_CLOSE == parameter) goto Destroy; break;
        case WM_SYSKEYDOWN: if (VK_F4 == parameter) goto Destroy; break;

        // [Create, Destroy]
        case WM_CREATE: { ::ShowWindow(windowHandle, (long long int) (LPVOID) ((CREATESTRUCTA const*) subparameter) -> lpCreateParams); } break;
        case WM_DESTROY: { ::PostQuitMessage(EXIT_SUCCESS); } break;
    }

    // [Evaluate, Destroy]
    Evaluate: return ::DefWindowProc(windowHandle, message, parameter, subparameter);
    Destroy: ::DestroyWindow(windowHandle); goto Evaluate;
}

/* Main */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const, LPSTR const, int const appearance) {
    int exitCode = EXIT_SUCCESS;
    CHAR instanceFileName[MAX_PATH] = {0};
    WNDCLASSEX windowClassInformation = {};
    HWND windowHandle = NULL;

    ::GetModuleFileName(NULL, instanceFileName, MAX_PATH);

    windowClassInformation.cbClsExtra = 0;
    windowClassInformation.cbSize = sizeof(WNDCLASSEX);
    windowClassInformation.cbWndExtra = 0;
    windowClassInformation.hIcon = (HICON) ::ExtractIcon(instanceHandle, instanceFileName, 0u);
    windowClassInformation.hIconSm = (HICON) NULL;
    windowClassInformation.hInstance = instanceHandle;
    windowClassInformation.hCursor = ::LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
    windowClassInformation.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
    windowClassInformation.lpfnWndProc = &windowProcedure;
    windowClassInformation.lpszClassName = "window";
    windowClassInformation.lpszMenuName = (LPCSTR) NULL;
    windowClassInformation.style = CS_GLOBALCLASS | CS_OWNDC;

    if (0x0 == ::RegisterClassEx((WNDCLASSEX const*) &windowClassInformation)) exitCode = EXIT_FAILURE;
    else {
        windowHandle = ::CreateWindowEx(
            0x0, windowClassInformation.lpszClassName, "Direct 3D | Introduction", WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            HWND_DESKTOP, (HMENU) NULL, windowClassInformation.hInstance, (LPVOID) (LPARAM) appearance
        );

        if (NULL == windowHandle) exitCode = EXIT_FAILURE;
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

        ::UnregisterClass(windowClassInformation.lpszClassName, windowClassInformation.hInstance);
    }

    // Return
    return exitCode;
}
