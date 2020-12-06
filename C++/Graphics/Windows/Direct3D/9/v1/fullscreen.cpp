/* ...
    --- CODE (Lapys) -> C++11
        d3d9.lib, shell32.lib, user32.lib
*/
/* Definitions > ... */
#define NO_STRICT
#define WIN32_LEAN_AND_MEAN

#undef STRICT
#undef UNICODE

/* Import */
#include <d3d9.h> // Direct 3D v9
#   include <d3d9types.h> // Direct 3D v9 Types
#include <windows.h> // Windows
#include <windowsx.h> // Windows Extensions
#   include <basetsd.h> // Basic Types Definition
#   include <shellapi.h> // Shell API
#   include <windef.h> // Windows Definitions
#   ifndef NOGDI // Windows GDI (Graphics Device Interface)
#       include <wingdi.h>
#   endif
#   include <winuser.h> // Windows User

/* Definition */
void Initiate(HWND const);
void Update(void);
void Terminate(void);

/* Global > ... */
static LPDIRECT3D9 DIRECT_3D = NULL;
static LPDIRECT3DDEVICE9 DIRECT_3D_DEVICE = NULL;
static D3DPRESENT_PARAMETERS DIRECT_3D_PRESENT_PARAMETERS = {};
enum { SCREEN_HEIGHT = 600u, SCREEN_WIDTH = 800u };

/* Function > Handle Events */
LRESULT CALLBACK HandleEvents(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
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

        // [Key Up]
        case WM_KEYUP: if (VK_F11 == parameter) {
            // Initialization > Window ...
            RECT windowRectangle = {};

            static struct {
                LONG_PTR extendedStyle = 0x0;
                D3DPRESENT_PARAMETERS presentParameters = {};
                LONG_PTR style = 0x0;
            } windowResolutionInformation = {};
            static BOOL windowResolutionUnchanged = TRUE;

            // Logic --- NOTE (Lapys) -> Change the style; Previously this was done by destroying & re-creating the window.
            if (windowResolutionUnchanged) {
                // Initialization > Present Parameters
                D3DPRESENT_PARAMETERS presentParameters = {};

                // Update > Present Parameters --- NOTE (Lapys) ->
                presentParameters = DIRECT_3D_PRESENT_PARAMETERS;
                presentParameters.Windowed = FALSE;

                // ... > Window Resolution ...
                windowResolutionInformation.presentParameters = DIRECT_3D_PRESENT_PARAMETERS;
                windowResolutionInformation.extendedStyle = ::GetWindowLongPtr(windowHandle, GWL_EXSTYLE);
                windowResolutionInformation.style = ::GetWindowLongPtr(windowHandle, GWL_STYLE);

                // ...
                ::SetWindowLongPtr(windowHandle, GWL_EXSTYLE, WS_EX_TOPMOST);
                ::SetWindowLongPtr(windowHandle, GWL_STYLE, WS_POPUP);
                DIRECT_3D_DEVICE -> Reset(&presentParameters);

                windowResolutionUnchanged = FALSE;
            }

            else {
                // ... > Window Resolution ...
                ::SetWindowLongPtr(windowHandle, GWL_STYLE, windowResolutionInformation.extendedStyle);
                ::SetWindowLongPtr(windowHandle, GWL_STYLE, windowResolutionInformation.style);
                DIRECT_3D_DEVICE -> Reset(&windowResolutionInformation.presentParameters);

                windowResolutionUnchanged = TRUE;
            }

            // ... --- NOTE (Lapys) -> The style may be cached and require repositioning to visually update.
            ::GetWindowRect(windowHandle, &windowRectangle);
            ::SetWindowPos(windowHandle, HWND_TOPMOST, windowRectangle.left, windowRectangle.top, windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top, SWP_DEFERERASE | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOREDRAW | SWP_NOSENDCHANGING | SWP_NOSIZE | SWP_SHOWWINDOW);
        } break;
    }

    // [Evaluate, Destroy]
    Evaluate: return ::DefWindowProc(windowHandle, message, parameter, subparameter);
    Destroy: ::DestroyWindow(windowHandle); goto Evaluate;
}

/* Phase --- NOTE (Lapys) */
/* : Initiate -> Configure & initialize Direct3D */
void Initiate(HWND const windowHandle) {
    // Update > Direct 3D ... --- NOTE (Lapys) ->
    DIRECT_3D = ::Direct3DCreate9(D3D_SDK_VERSION);

    DIRECT_3D_PRESENT_PARAMETERS.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
    DIRECT_3D_PRESENT_PARAMETERS.BackBufferCount = 0u;
    DIRECT_3D_PRESENT_PARAMETERS.BackBufferFormat = D3DFMT_X8R8G8B8; // Set the back buffer color format to 32-bit.
    DIRECT_3D_PRESENT_PARAMETERS.BackBufferHeight = SCREEN_HEIGHT;
    DIRECT_3D_PRESENT_PARAMETERS.BackBufferWidth = SCREEN_WIDTH;
    DIRECT_3D_PRESENT_PARAMETERS.EnableAutoDepthStencil = FALSE;
    DIRECT_3D_PRESENT_PARAMETERS.hDeviceWindow = windowHandle; // ...
    DIRECT_3D_PRESENT_PARAMETERS.Flags = 0x0;
    DIRECT_3D_PRESENT_PARAMETERS.FullScreen_RefreshRateInHz = 0u;
    DIRECT_3D_PRESENT_PARAMETERS.MultiSampleType = D3DMULTISAMPLE_NONE;
    DIRECT_3D_PRESENT_PARAMETERS.MultiSampleQuality = 0u;
    DIRECT_3D_PRESENT_PARAMETERS.PresentationInterval = 0u;
    DIRECT_3D_PRESENT_PARAMETERS.SwapEffect = D3DSWAPEFFECT_DISCARD; // Discard old frames.
    DIRECT_3D_PRESENT_PARAMETERS.Windowed = TRUE;

    // ... --- NOTE (Lapys) -> Create device class.
    DIRECT_3D -> CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &DIRECT_3D_PRESENT_PARAMETERS, &DIRECT_3D_DEVICE);
}

/* : Update -> Render a single frame. */
void Update(void) {
    // ... --- NOTE (Lapys) ->
    DIRECT_3D_DEVICE -> Clear(0u, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00u, 0x28u, 0x64u), 1.0f, 0u); // Clear the window to a Deep Blue color fill.
    DIRECT_3D_DEVICE -> BeginScene(); // Begin the 3D scene.
    /* Render to the back buffer. */ {
        /* Some code here... */
    }
    DIRECT_3D_DEVICE -> EndScene(); // End the 3D scene.
    DIRECT_3D_DEVICE -> Present(NULL, NULL, NULL, NULL); // Display the created frame.
}

/* : Terminate -> Release & terminate Direct3D. */
void Terminate(void) {
    DIRECT_3D_DEVICE -> Release();
    DIRECT_3D -> Release();
}

/* Main */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const, LPSTR const, int const appearance) {
    // Initialization > (Exit Code, Instance File Name, Window ...)
    int exitCode = EXIT_SUCCESS;
    CHAR instanceFileName[MAX_PATH] = {0};
    WNDCLASSEX windowClassInformation = {};
    HWND windowHandle = NULL;

    // Update > (Instance File Name, Window Class Information)
    ::GetModuleFileName(NULL, instanceFileName, MAX_PATH);

    windowClassInformation.cbClsExtra = 0;
    windowClassInformation.cbSize = sizeof(WNDCLASSEX);
    windowClassInformation.cbWndExtra = 0;
    windowClassInformation.hIcon = (HICON) ::ExtractIcon(instanceHandle, instanceFileName, 0u);
    windowClassInformation.hIconSm = (HICON) NULL;
    windowClassInformation.hInstance = instanceHandle;
    windowClassInformation.hCursor = ::LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
    windowClassInformation.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
    windowClassInformation.lpfnWndProc = &HandleEvents;
    windowClassInformation.lpszClassName = "window";
    windowClassInformation.lpszMenuName = (LPCSTR) NULL;
    windowClassInformation.style = CS_GLOBALCLASS | CS_OWNDC;

    // Logic > ...
    if (0x0 == ::RegisterClassEx((WNDCLASSEX const*) &windowClassInformation)) exitCode = EXIT_FAILURE;
    else {
        // Update > Window Handle
        windowHandle = ::CreateWindowEx(
            0x0, windowClassInformation.lpszClassName, "Direct 3D | Fullscreen", WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH, SCREEN_HEIGHT,
            HWND_DESKTOP, (HMENU) NULL, windowClassInformation.hInstance, (LPVOID) (LPARAM) appearance
        );

        // Logic > ...
        if (NULL == windowHandle) exitCode = EXIT_FAILURE;
        else {
            // Initialization > Thread Message
            MSG threadMessage = {};

            // ...; Loop
            Initiate(windowHandle);
            for (
                BOOL threadMessageAvailable = FALSE; WM_QUIT != threadMessage.message;
                threadMessageAvailable = ::PeekMessage(&threadMessage, NULL, 0x0, 0x0, PM_REMOVE)
            ) {
                // Logic > ...
                if (threadMessageAvailable) ::DispatchMessage(&threadMessage);
                else { Update(); }
            }

            // ...; Update > Exit Code
            Terminate();
            exitCode = threadMessage.wParam;
        }

        // Deletion
        ::UnregisterClass(windowClassInformation.lpszClassName, windowClassInformation.hInstance);
    }

    // Return
    return exitCode;
}
