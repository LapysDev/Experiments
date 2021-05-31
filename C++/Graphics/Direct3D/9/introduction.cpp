/* Import --> D3D9.dll, kernel32.dll, shell32.dll, user32.dll */
#include <stdint.h> // Standard Integers
#include <cstdio>
#include <cstdlib> // C Standard Library

#include <windef.h> // Windows Definitions
#include <winbase.h> // Windows Base
#include <wingdi.h> // Windows Graphics Device Interface
#include <winnt.h> // Windows New Technologies
#include <winuser.h> // Windows User
#   include <D3D9.h> // Direct 3D v9
#   include <shellapi.h> // Shell API

/* Definition > ... */
#undef UNICODE

static bool Initiate(void);
static void Update(void);

/* Global */
// : Direct 3D ...
static LPDIRECT3D9 direct3D = NULL;
static LPDIRECT3DDEVICE9 direct3DDevice = NULL;
static D3DPRESENT_PARAMETERS direct3DPresentationParameters = D3DPRESENT_PARAMETERS();

// : Window ...
static WNDCLASSEX windowClassInformation = WNDCLASSEX();
static HWND windowHandle = NULL;
static LRESULT CALLBACK windowProcedure(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
    switch (message) {
        /* ... */
        case WM_CLOSE: ::DestroyWindow(windowHandle); break;
        case WM_KEYDOWN: if (VK_ESCAPE == parameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSCOMMAND: if (SC_CLOSE == parameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSKEYDOWN: if (VK_F4 == parameter) ::DestroyWindow(windowHandle); break;

        /* ... */
        case WM_CREATE: ::ShowWindow(windowHandle, static_cast<long>(reinterpret_cast<intptr_t>(static_cast<LPVOID>(reinterpret_cast<CREATESTRUCTA const*>(subparameter) -> lpCreateParams)))); break;
        case WM_DESTROY: ::PostQuitMessage(EXIT_SUCCESS); break;
    }

    // ...
    return ::DefWindowProc(windowHandle, message, parameter, subparameter);
}

/* Phase */
// : Initiate
bool Initiate(void) {
    if (NULL == direct3D) direct3D = ::Direct3DCreate9(D3D_SDK_VERSION);
    if (NULL != direct3D) {
        direct3DPresentationParameters.AutoDepthStencilFormat = /* 0x0 */ D3DFMT_UNKNOWN;
        direct3DPresentationParameters.BackBufferCount = 0u;
        direct3DPresentationParameters.BackBufferFormat = /* 0x0 */ D3DFMT_UNKNOWN;
        direct3DPresentationParameters.BackBufferHeight = 0u;
        direct3DPresentationParameters.BackBufferWidth = 0u;
        direct3DPresentationParameters.EnableAutoDepthStencil = FALSE;
        direct3DPresentationParameters.Flags = 0x0u;
        direct3DPresentationParameters.FullScreen_RefreshRateInHz = 0u;
        direct3DPresentationParameters.hDeviceWindow = windowHandle;
        direct3DPresentationParameters.MultiSampleQuality = 0u;
        direct3DPresentationParameters.MultiSampleType = /* 0x0 */ D3DMULTISAMPLE_NONE;
        direct3DPresentationParameters.PresentationInterval = 0u;
        direct3DPresentationParameters.SwapEffect = D3DSWAPEFFECT_COPY;
        direct3DPresentationParameters.Windowed = TRUE;

        if (NULL == direct3DDevice && D3D_OK == direct3D -> CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &direct3DPresentationParameters, &direct3DDevice)) {
            D3DDISPLAYMODE direct3DDeviceDisplayMode;
            HRESULT const evaluation = direct3D -> GetAdapterDisplayMode(D3DADAPTER_DEFAULT , &direct3DDeviceDisplayMode);

            return D3D_OK == direct3D -> CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3D_OK == evaluation ? direct3DDeviceDisplayMode.Format : D3DFMT_X8R8G8B8, direct3DPresentationParameters.BackBufferFormat, direct3DPresentationParameters.Windowed);
        }
    }

    return false;
}

// : Update
void Update(void) {
    static HRESULT direct3DDevicePresentationEvaluation = D3D_OK;

    if (D3D_OK == direct3DDevicePresentationEvaluation) {
        direct3DDevice -> Clear(0u, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0u);

        if (D3D_OK == direct3DDevice -> BeginScene()) {
            /* Do something... */
            direct3DDevice -> EndScene();
        }

        direct3DDevicePresentationEvaluation = direct3DDevice -> Present(NULL, NULL, direct3DPresentationParameters.hDeviceWindow, NULL);
    }

    if (
        D3DERR_DEVICELOST == direct3DDevice -> TestCooperativeLevel() ||
        (D3DERR_DEVICELOST == direct3DDevicePresentationEvaluation && D3DERR_DEVICENOTRESET == direct3DDevice -> TestCooperativeLevel())
    ) {
        /* NOTE (Lapys) -> Before `Reset(...)`, release any explicit additional swap chains, D3DPOOL_DEFAULT, depth stencil surfaces, render targets, shaders, and state blocks resources */
        direct3DDevicePresentationEvaluation = direct3DDevice -> Reset(&direct3DPresentationParameters);
        Initiate();
    }
}

/* Main --- NOTE (Lapys) */
int WinMain(HINSTANCE const instanceHandle, HINSTANCE const /* previousInstanceHandle */, LPSTR const /* commandLineArguments */, int const appearance) {
    int exitCode = EXIT_SUCCESS;
    CHAR instanceFileName[MAX_PATH] = {0};

    // ...
    ::GetModuleFileName(NULL, instanceFileName, MAX_PATH);

    windowClassInformation.cbClsExtra = 0;
    windowClassInformation.cbSize = sizeof(WNDCLASSEX);
    windowClassInformation.cbWndExtra = 0;
    windowClassInformation.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
    windowClassInformation.hCursor = static_cast<HCURSOR>(::LoadCursor(instanceHandle, IDC_ARROW)) /* --> static_cast<HCURSOR>(::LoadImage(instanceHandle, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)) */;
    windowClassInformation.hIcon = static_cast<HICON>(::ExtractIcon(instanceHandle, instanceFileName, 0u));
    windowClassInformation.hIconSm = static_cast<HICON>(NULL);
    windowClassInformation.hInstance = instanceHandle;
    windowClassInformation.lpfnWndProc = &windowProcedure;
    windowClassInformation.lpszClassName = "window";
    windowClassInformation.lpszMenuName = static_cast<LPCSTR>(NULL);
    windowClassInformation.style = CS_GLOBALCLASS | CS_OWNDC;

    // ...
    if (0x0 == ::RegisterClassEx(static_cast<WNDCLASSEX const*>(&windowClassInformation))) exitCode = EXIT_FAILURE;
    else {
        windowHandle = ::CreateWindowEx(0x0, windowClassInformation.lpszClassName, "Windows Direct3D v9 Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, HWND_DESKTOP, static_cast<HMENU>(NULL), windowClassInformation.hInstance, reinterpret_cast<LPVOID>(static_cast<LPARAM>(appearance)));

        // ...
        if (NULL == windowHandle) exitCode = EXIT_FAILURE;
        else {
            if (false == Initiate()) exitCode = EXIT_FAILURE;
            else {
                MSG threadMessage = MSG();
                BOOL threadMessageAvailable = TRUE;

                while (true) {
                    ::DispatchMessage(&threadMessage);
                    threadMessageAvailable = ::PeekMessage(&threadMessage, NULL, 0x0, 0x0, PM_REMOVE);

                    if (false == (FALSE == threadMessageAvailable || WM_QUIT != threadMessage.message)) break;
                    Update();
                }

                exitCode = threadMessage.wParam;
            }
        }

        ::UnregisterClass(windowClassInformation.lpszClassName, windowClassInformation.hInstance);
    }

    ::DestroyCursor(windowClassInformation.hCursor);

    // ...
    return exitCode;
}
