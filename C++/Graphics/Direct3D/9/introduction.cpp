/* ... --> d3d9.lib, gdi32.lib, kernel32.lib, shell32.lib, user32.lib */
/* Definition > ... */
#undef UNICODE

/* Import */
// : [C Standard Library]
#include <stdbool.h> // Standard Boolean
#include <stdint.h>  // Standard Integers

// : [C++ Standard Library]
#include <cstdio>  // C Standard Input/ Output
#include <cstdlib> // C Standard Library

// : [Windows API]
#include <windows.h> // Windows
# include <d3d9.h>   // Direct 3D v9

/* Phase > ... */
static void INITIATE ();
       void RESET    ();
       void TERMINATE();
       void UPDATE   ();

LRESULT CALLBACK UPDATE(HWND const, UINT const, WPARAM const, LPARAM const);

/* Namespace */
// : Graphics
namespace Graphics {
    static struct Direct3D {
      private: LPDIRECT3D9 value;
      public:
        Direct3D() : value() {}
        Direct3D(LPDIRECT3D9 const value) : value(value) {}

        // ...
        LPDIRECT3DDEVICE9     DEVICE = NULL;
        D3DPRESENT_PARAMETERS PRESENTATION_PARAMETERS;

        // ...
        LPDIRECT3D9 operator ->() const { return this -> value; }
        operator LPDIRECT3D9&() { return const_cast<LPDIRECT3D9&>(this -> value); }
    } Direct3D = NULL;
}

// : Program
namespace Program {
    static int       EXIT_CODE           = EXIT_SUCCESS;
    static CHAR      FILE_NAME[MAX_PATH] = {'\0'};
    static HINSTANCE HANDLE              = NULL;
    static MSG       THREAD_MESSAGE      = MSG();
}

// : Window
namespace Window {
    static int     APPEARANCE      = SW_SHOW;
    static HBRUSH  BACKGROUND      = NULL;
    static LPCSTR  CLASS_NAME      = "window";
    static UINT    CLASS_STYLE     = CS_GLOBALCLASS | CS_OWNDC;
    static HCURSOR CURSOR          = NULL;
    static HICON   FAVICON         = NULL;
    static HWND    HANDLE          = NULL;
    static int     HEIGHT          = -1;
    static HICON   ICON            = NULL;
    static int     LEFT            = -1;
    static LRESULT CALLBACK (*PROCEDURE)(HWND const, UINT const, WPARAM const, LPARAM const) = &::DefWindowProc;
    static DWORD   STYLE           = WS_OVERLAPPEDWINDOW;
    static DWORD   STYLE_EXTENSION = 0x00000000L;
    static LPCSTR  TITLE           = "";
    static int     TOP             = -1;
    static int     WIDTH           = -1;
}

/* Main */
int WinMain(HINSTANCE const programHandle, HINSTANCE const, LPSTR const, int const appearance) {
    Program::HANDLE = programHandle;
    Window::APPEARANCE = appearance;

    // ...
    INITIATE();
    return Program::EXIT_CODE;
}

/* Phase */
/* : Initiate */
void INITIATE() {
    bool const pollThreadMessages = NULL == Window::HANDLE;

    /* ... */
    if (NULL == Window::HANDLE) {
        WNDCLASSEX classInformation;

        // ...
        ::GetModuleFileName(static_cast<HMODULE>(NULL), Program::FILE_NAME, MAX_PATH);

        Window::BACKGROUND = ::GetSysColorBrush(COLOR_WINDOW);
        Window::CURSOR     = ::LoadCursor(NULL, IDC_ARROW); // --> static_cast<HCURSOR>(::LoadImage(NULL, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_SHARED))
        Window::ICON       = ::ExtractIcon(static_cast<HINSTANCE>(::GetCurrentProcess()), Program::FILE_NAME, 0u);
        Window::PROCEDURE  = static_cast<LRESULT CALLBACK (*)(HWND const, UINT const, WPARAM const, LPARAM const)>(&UPDATE);
        Window::TITLE      = "Direct3D v9";

        // ...
        classInformation.cbClsExtra    = 0;
        classInformation.cbSize        = sizeof(WNDCLASSEX);
        classInformation.cbWndExtra    = 0;
        classInformation.hbrBackground = Window::BACKGROUND;
        classInformation.hCursor       = Window::CURSOR;
        classInformation.hIcon         = Window::ICON;
        classInformation.hIconSm       = Window::FAVICON;
        classInformation.hInstance     = Program::HANDLE;
        classInformation.lpfnWndProc   = Window::PROCEDURE;
        classInformation.lpszClassName = Window::CLASS_NAME;
        classInformation.lpszMenuName  = static_cast<LPCSTR>(NULL);
        classInformation.style         = Window::CLASS_STYLE;

        // ...
        if (0x0 == ::RegisterClassEx(const_cast<WNDCLASSEX const*>(&classInformation))) TERMINATE();
        if (Window::HEIGHT == -1 || Window::LEFT == -1 || Window::TOP == -1 || Window::WIDTH == -1) {
            RECT workareaBounds;
            ::SystemParametersInfo(SPI_GETWORKAREA, 0x0000u, static_cast<PVOID>(&workareaBounds), 0x0u);

            // ...
            if (Window::HEIGHT == -1) Window::HEIGHT = ((workareaBounds.bottom - workareaBounds.top) * 3) / 4;
            if (Window::WIDTH  == -1) Window::WIDTH  = ((workareaBounds.right - workareaBounds.left) * 3) / 4;

            if (Window::LEFT   == -1) Window::LEFT   = (((workareaBounds.right - workareaBounds.left) - Window::WIDTH ) * 1) / 2;
            if (Window::TOP    == -1) Window::TOP    = (((workareaBounds.bottom - workareaBounds.top) - Window::HEIGHT) * 1) / 2;
        }

        // ...
        Window::HANDLE = ::CreateWindowEx(Window::STYLE_EXTENSION, Window::CLASS_NAME, Window::TITLE, Window::STYLE, Window::LEFT, Window::TOP, Window::WIDTH, Window::HEIGHT, NULL /* --> HWND_DESKTOP */, static_cast<HMENU>(NULL), Program::HANDLE, reinterpret_cast<LPVOID>(static_cast<LPARAM>(Window::APPEARANCE)));
        if (NULL == Window::HANDLE) TERMINATE();
    }

    // ...
    {
        if (NULL == Graphics::Direct3D) Graphics::Direct3D = ::Direct3DCreate9(D3D_SDK_VERSION);

        Graphics::Direct3D.PRESENTATION_PARAMETERS.AutoDepthStencilFormat     = /* 0x0 */ D3DFMT_UNKNOWN;
        Graphics::Direct3D.PRESENTATION_PARAMETERS.BackBufferCount            = 0u;
        Graphics::Direct3D.PRESENTATION_PARAMETERS.BackBufferFormat           = /* 0x0 */ D3DFMT_UNKNOWN;
        Graphics::Direct3D.PRESENTATION_PARAMETERS.BackBufferHeight           = 0u;
        Graphics::Direct3D.PRESENTATION_PARAMETERS.BackBufferWidth            = 0u;
        Graphics::Direct3D.PRESENTATION_PARAMETERS.EnableAutoDepthStencil     = FALSE;
        Graphics::Direct3D.PRESENTATION_PARAMETERS.Flags                      = 0x0u;
        Graphics::Direct3D.PRESENTATION_PARAMETERS.FullScreen_RefreshRateInHz = 0u;
        Graphics::Direct3D.PRESENTATION_PARAMETERS.hDeviceWindow              = Window::HANDLE;
        Graphics::Direct3D.PRESENTATION_PARAMETERS.MultiSampleQuality         = 0u;
        Graphics::Direct3D.PRESENTATION_PARAMETERS.MultiSampleType            = /* 0x0 */ D3DMULTISAMPLE_NONE;
        Graphics::Direct3D.PRESENTATION_PARAMETERS.PresentationInterval       = 0u;
        Graphics::Direct3D.PRESENTATION_PARAMETERS.SwapEffect                 = D3DSWAPEFFECT_COPY;
        Graphics::Direct3D.PRESENTATION_PARAMETERS.Windowed                   = TRUE;

        // ...
        if (D3D_OK == Graphics::Direct3D -> CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window::HANDLE, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &Graphics::Direct3D.PRESENTATION_PARAMETERS, &Graphics::Direct3D.DEVICE)) {
            D3DDISPLAYMODE displayMode;

            Graphics::Direct3D -> GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);
            if (D3D_OK != Graphics::Direct3D -> CheckDeviceType(
                D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, /* --> D3DFMT_X8R8G8B8 */ displayMode.Format,
                Graphics::Direct3D.PRESENTATION_PARAMETERS.BackBufferFormat, Graphics::Direct3D.PRESENTATION_PARAMETERS.Windowed
            )) TERMINATE();
        }
    }

    /* ... */
    if (false == pollThreadMessages) return;

    for (bool available = false; WM_QUIT != Program::THREAD_MESSAGE.message; UPDATE()) {
        available = ::PeekMessage(&Program::THREAD_MESSAGE, NULL, 0x0u, 0x0u, PM_REMOVE);
        if (FALSE != available) ::DispatchMessage(&Program::THREAD_MESSAGE);

        Program::EXIT_CODE = Program::THREAD_MESSAGE.wParam;
    }
}

/* : Update */
void UPDATE() {
    static HRESULT presentation = D3D_OK;

    // ...
    if (D3D_OK == presentation) {
        Graphics::Direct3D.DEVICE -> Clear(0u, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0u);
        if (D3D_OK == Graphics::Direct3D.DEVICE -> BeginScene()) {
            /* ... */
            Graphics::Direct3D.DEVICE -> EndScene();
        }

        presentation = Graphics::Direct3D.DEVICE -> Present(NULL, NULL, Graphics::Direct3D.PRESENTATION_PARAMETERS.hDeviceWindow, NULL);
    }

    // ... ->> Before `Reset(...)`, release any explicit additional swap chains, D3DPOOL_DEFAULT, depth stencil surfaces, render targets, shaders, and state blocks resources.
    if (D3DERR_DEVICELOST == Graphics::Direct3D.DEVICE -> TestCooperativeLevel() || (D3DERR_DEVICELOST == presentation && D3DERR_DEVICENOTRESET == Graphics::Direct3D.DEVICE -> TestCooperativeLevel())) {
        presentation = Graphics::Direct3D.DEVICE -> Reset(&Graphics::Direct3D.PRESENTATION_PARAMETERS);
        return RESET();
    }
}

LRESULT CALLBACK UPDATE(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
    switch (message) {
        /* ... */
        case WM_CLOSE     :                             ::DestroyWindow(windowHandle); break;
        case WM_KEYDOWN   : if (VK_ESCAPE == parameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSCOMMAND: if (SC_CLOSE  == parameter) ::DestroyWindow(windowHandle); break;
        case WM_SYSKEYDOWN: if (VK_F4     == parameter) ::DestroyWindow(windowHandle); break;

        /* ... */
        case WM_CREATE: {
            LPVOID const creationParameter = reinterpret_cast<CREATESTRUCTA const*>(subparameter) -> lpCreateParams;

            // ...
            ::FreeConsole();
            ::ShowWindow(windowHandle, /* --> SW_SHOWDEFAULT */ static_cast<long>(static_cast<int>(reinterpret_cast<intptr_t>(creationParameter))));
        } break;

        // ...
        case WM_DESTROY: { Window::HANDLE = NULL; ::PostQuitMessage(EXIT_SUCCESS); } break;
        case WM_PAINT: return 0x0L; // ->> No GDI painting.
    }

    // ...
    return ::DefWindowProc(windowHandle, message, parameter, subparameter);
}

/* : Reset */
void RESET() { return INITIATE(); }

/* : Terminate */
void TERMINATE() {
    if (NULL != Window::HANDLE) ::DestroyWindow(Window::HANDLE);
    ::UnregisterClass(Window::CLASS_NAME, Program::HANDLE);

    std::exit(Program::EXIT_CODE);
}
