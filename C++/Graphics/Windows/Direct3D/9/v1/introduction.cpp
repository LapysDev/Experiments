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
LPDIRECT3D9 DIRECT_3D = NULL;
LPDIRECT3DDEVICE9 DIRECT_3D_DEVICE = NULL;

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
    }

    // [Evaluate, Destroy]
    Evaluate: return ::DefWindowProc(windowHandle, message, parameter, subparameter);
    Destroy: ::DestroyWindow(windowHandle); goto Evaluate;
}

/* Phase --- NOTE (Lapys) */
/* : Initiate -> Configure & initialize Direct3D */
void Initiate(HWND const windowHandle) {
    // Initialization > Direct 3D Present Parameters --- NOTE (Lapys) -> Store various device information.
    D3DPRESENT_PARAMETERS direct3DPresentParameters = {};

    // Update > Direct 3D ...
    DIRECT_3D = ::Direct3DCreate9(D3D_SDK_VERSION);

    direct3DPresentParameters.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
    direct3DPresentParameters.BackBufferCount = 0u;
    direct3DPresentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
    direct3DPresentParameters.BackBufferHeight = 0u;
    direct3DPresentParameters.BackBufferWidth = 0u;
    direct3DPresentParameters.EnableAutoDepthStencil = FALSE;
    direct3DPresentParameters.hDeviceWindow = windowHandle; // ...
    direct3DPresentParameters.Flags = 0x0;
    direct3DPresentParameters.FullScreen_RefreshRateInHz = 0u;
    direct3DPresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
    direct3DPresentParameters.MultiSampleQuality = 0u;
    direct3DPresentParameters.PresentationInterval = 0u;
    direct3DPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD; // NOTE (Lapys) -> Discard old frames.
    direct3DPresentParameters.Windowed = TRUE;

    // ... --- NOTE (Lapys) -> Create device class.
    DIRECT_3D -> CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &direct3DPresentParameters, &DIRECT_3D_DEVICE);
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
            0x0, windowClassInformation.lpszClassName, "Direct 3D | Introduction", WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
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
