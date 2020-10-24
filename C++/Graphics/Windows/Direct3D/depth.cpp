/* ...
    --- CODE (Lapys) -> C++11
        d3d9.lib, d3dx9.lib, kernel32.lib, shell32.lib, user32.lib
*/
/* Definitions > ... */
#define NO_STRICT
#define WIN32_LEAN_AND_MEAN

#undef STRICT
#undef UNICODE

/* Import */
#include <d3d9.h> // Direct 3D v9
#include <d3dx9.h> // Direct 3D Extensions v9
#   include <d3d9types.h> // Direct 3D v9 Types
#   include <d3dx9math.h> // Direct 3D Extensions v9 Mathematics
#include <windows.h> // Windows
#include <windowsx.h> // Windows Extensions
#   include <basetsd.h> // Basic Types Definition
#   include <shellapi.h> // Shell API
#   include <winbase.h> // Windows Base
#   include <windef.h> // Windows Definitions
#   ifndef NOGDI // Windows GDI (Graphics Device Interface)
#       include <wingdi.h>
#   endif
#   include <winuser.h> // Windows User

/* Definition */
void Initiate(HWND const);
void Update(void);
void Terminate(void);

/* Class */
// : Vertex --- NOTE (lapys) -> Transformed: Modified via World, View, Projection matrices into screen-space; Untransformed: Maps directly to 2D coordinates.
struct vertex_t final { public:
    FLOAT x, y, z; DWORD color;
    constexpr vertex_t(FLOAT const x, FLOAT const y, FLOAT const z, DWORD const color) noexcept : x{x}, y{y}, z{z}, color{color} {}
};

/* Global */
// : Direct 3D ...
static LPDIRECT3D9 DIRECT_3D = NULL;
static LPDIRECT3DDEVICE9 DIRECT_3D_DEVICE = NULL;
static D3DPRESENT_PARAMETERS DIRECT_3D_PRESENT_PARAMETERS = {};

// : Matrix Transformations
static struct {
    D3DXMATRIX projection = {};

    D3DXMATRIX view = {};
    D3DXVECTOR3 viewCameraTranslation = {};
    D3DXVECTOR3 viewFocalTranslation = {};
    D3DXVECTOR3 viewUpDirection = {};

    D3DXMATRIX worldScale = {};
    D3DXMATRIX worldTranslation = {};
    D3DXMATRIX worldXRotation = {}, worldYRotation = {}, worldZRotation = {};
} MATRIX_TRANSFORMATIONS = {};

// : Render (Height, Width)
enum { RENDER_HEIGHT = 600u, RENDER_WIDTH = 800u };

// : Triangle ...
constexpr vertex_t TRIANGLE[3] = {
    {0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(0x00u, 0x00u, 0xFFu)},
    {1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(0x00u, 0xFFu, 0x00u)},
    {-1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(0xFFu, 0x00u, 0x00u)}
};

// : Vertex Buffer
static LPDIRECT3DVERTEXBUFFER9 VERTEX_BUFFER = NULL;

/* Function > Handle Events */
LRESULT CALLBACK HandleEvents(HWND const windowHandle, UINT const message, WPARAM const parameter, LPARAM const subparameter) {
    // [Dispatch Message] Logic
    switch (message) {
        // [...]
        case WM_CLOSE: goto Destroy;
        case WM_SYSCOMMAND: if (SC_CLOSE == parameter) goto Destroy; break;
        case WM_SYSKEYDOWN: if (VK_F4 == parameter) goto Destroy; break;

        // [Create, Destroy]
        case WM_CREATE: { ::ShowWindow(windowHandle, (long long int) (LPVOID) ((CREATESTRUCTA const*) subparameter) -> lpCreateParams); } break;
        case WM_DESTROY: { ::PostQuitMessage(EXIT_SUCCESS); } break;

        // [Key Up]
        case WM_KEYDOWN: if (VK_ESCAPE == parameter) goto Destroy;
        case WM_KEYUP: switch (parameter) {
            // [Render Transformations]
            // case VK_DOWN: ::D3DXMatrixScaling(&MATRIX_TRANSFORMATIONS.worldYRotation, 0.5f, 0.5f, 0.5f); break;
            // case VK_LEFT: ::D3DXMatrixRotationY(&MATRIX_TRANSFORMATIONS.worldYRotation, angle -= 0.0174533f); break;
            // case VK_RIGHT: ::D3DXMatrixRotationY(&MATRIX_TRANSFORMATIONS.worldYRotation, angle += 0.0174533f); break;
            // case VK_UP: ::D3DXMatrixScaling(&MATRIX_TRANSFORMATIONS.worldYRotation, 2.0f, 2.0f, 2.0f); break;

            // [Toggle Fullscreen]
            case VK_F11: {
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
        } break;
    }

    // [Evaluate, Destroy]
    Evaluate: return ::DefWindowProc(windowHandle, message, parameter, subparameter);
    Destroy: ::DestroyWindow(windowHandle); goto Evaluate;
}

/* Phase --- NOTE (Lapys) */
/* : Initiate -> Configure & initialize Direct3D */
void Initiate(HWND const windowHandle, vertex_t const vertices[], unsigned char const count) {
    // Initialization > ...
    VOID *vertexBufferMemory = NULL;

    /* Update --- NOTE (Lapys) -> */ {
        // Direct 3D ...
        DIRECT_3D = ::Direct3DCreate9(D3D_SDK_VERSION);

        DIRECT_3D_PRESENT_PARAMETERS.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
        DIRECT_3D_PRESENT_PARAMETERS.BackBufferCount = 0u;
        DIRECT_3D_PRESENT_PARAMETERS.BackBufferFormat = D3DFMT_X8R8G8B8; // Set the back buffer color format to 32-bit.
        DIRECT_3D_PRESENT_PARAMETERS.BackBufferHeight = RENDER_HEIGHT;
        DIRECT_3D_PRESENT_PARAMETERS.BackBufferWidth = RENDER_WIDTH;
        DIRECT_3D_PRESENT_PARAMETERS.EnableAutoDepthStencil = FALSE;
        DIRECT_3D_PRESENT_PARAMETERS.hDeviceWindow = windowHandle; // ...
        DIRECT_3D_PRESENT_PARAMETERS.Flags = 0x0;
        DIRECT_3D_PRESENT_PARAMETERS.FullScreen_RefreshRateInHz = 0u;
        DIRECT_3D_PRESENT_PARAMETERS.MultiSampleType = D3DMULTISAMPLE_NONE;
        DIRECT_3D_PRESENT_PARAMETERS.MultiSampleQuality = 0u;
        DIRECT_3D_PRESENT_PARAMETERS.PresentationInterval = 0u;
        DIRECT_3D_PRESENT_PARAMETERS.SwapEffect = D3DSWAPEFFECT_DISCARD; // Discard old frames.
        DIRECT_3D_PRESENT_PARAMETERS.Windowed = TRUE;

        // Matrix Transformations ...
        ::D3DXMatrixIdentity(&MATRIX_TRANSFORMATIONS.projection);
        ::D3DXMatrixIdentity(&MATRIX_TRANSFORMATIONS.view);
        ::D3DXMatrixIdentity(&MATRIX_TRANSFORMATIONS.worldScale);
        ::D3DXMatrixIdentity(&MATRIX_TRANSFORMATIONS.worldTranslation);
        ::D3DXMatrixIdentity(&MATRIX_TRANSFORMATIONS.worldXRotation);
        ::D3DXMatrixIdentity(&MATRIX_TRANSFORMATIONS.worldYRotation);
        ::D3DXMatrixIdentity(&MATRIX_TRANSFORMATIONS.worldZRotation);
    }

    // Direct 3D > ... --- NOTE (Lapys) -> Create device class & vertex buffer.
    DIRECT_3D -> CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &DIRECT_3D_PRESENT_PARAMETERS, &DIRECT_3D_DEVICE);
    DIRECT_3D_DEVICE -> CreateVertexBuffer(
        count * sizeof(vertex_t), // -> Byte size of the buffer.
        0x0, // -> Specify the usage of the buffer (can be null).
        D3DFVF_DIFFUSE | D3DFVF_XYZ, // -> Flexible Vertex Format (FVF) information of the vertices stored in the buffer.
        D3DPOOL_MANAGED, // -> Store the buffer within video RAM.
        &VERTEX_BUFFER, NULL
    );
    DIRECT_3D_DEVICE -> SetRenderState(D3DRS_LIGHTING, FALSE); // -> Disable 3D (advanced) lighting.

    // Vertex Buffer > ...
    VERTEX_BUFFER -> Lock(0u, 0u, &vertexBufferMemory, 0x0);
      ::CopyMemory(vertexBufferMemory, vertices, count * sizeof(vertex_t));
    VERTEX_BUFFER -> Unlock();
}

/* : Update -> Render a single frame.  */
void Update(void) { // NOTE (Lapys) ->
    // [Initiate]
    DIRECT_3D_DEVICE -> Clear(0u, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00u, 0x0Fu, 0x33u), 1.0f, 0u); // Clear the window to a Deep Blue color fill.
    DIRECT_3D_DEVICE -> BeginScene(); // Begin the 3D scene.

    /* [Update] Render to the back buffer. */ {
        // [Configuration]
        DIRECT_3D_DEVICE -> SetFVF(D3DFVF_DIFFUSE | D3DFVF_XYZ);
        DIRECT_3D_DEVICE -> SetStreamSource(0u, VERTEX_BUFFER, 0u, sizeof(vertex_t));

        // [World Transform]
        D3DXQUATERNION worldRotation = {};
        D3DXVECTOR3 worldScale = {};
        D3DMATRIX worldTransformation = {};
        D3DXVECTOR3 worldTranslation = {};

        DIRECT_3D_DEVICE -> GetTransform(D3DTS_WORLD, (D3DMATRIX*) &worldTransformation);
        ::D3DXMatrixDecompose(&worldScale, &worldRotation, &worldTranslation, (D3DMATRIX*) &worldTransformation);

        ::D3DXMatrixRotationX(&MATRIX_TRANSFORMATIONS.worldXRotation, worldRotation.x);
        ::D3DXMatrixRotationY(&MATRIX_TRANSFORMATIONS.worldYRotation, worldRotation.y);
        ::D3DXMatrixRotationZ(&MATRIX_TRANSFORMATIONS.worldZRotation, worldRotation.z);

        DIRECT_3D_DEVICE -> SetTransform(D3DTS_WORLD, &MATRIX_TRANSFORMATIONS.worldXRotation);
        DIRECT_3D_DEVICE -> SetTransform(D3DTS_WORLD, &MATRIX_TRANSFORMATIONS.worldYRotation);
        DIRECT_3D_DEVICE -> SetTransform(D3DTS_WORLD, &MATRIX_TRANSFORMATIONS.worldZRotation);
        DIRECT_3D_DEVICE -> SetTransform(D3DTS_WORLD, &MATRIX_TRANSFORMATIONS.worldTranslation);
        DIRECT_3D_DEVICE -> SetTransform(D3DTS_WORLD, &MATRIX_TRANSFORMATIONS.worldScale);

        // [View Transform]
        MATRIX_TRANSFORMATIONS.viewCameraTranslation = {0.0f, 0.0f, 10.0f};
        MATRIX_TRANSFORMATIONS.viewFocalTranslation = {0.0f, 0.0f, 0.0f};
        MATRIX_TRANSFORMATIONS.viewUpDirection = {0.0f, 1.0f, 0.0f};
        ::D3DXMatrixLookAtLH(&MATRIX_TRANSFORMATIONS.view,
            &MATRIX_TRANSFORMATIONS.viewCameraTranslation, // Camera position.
            &MATRIX_TRANSFORMATIONS.viewFocalTranslation, // Look-at position.
            &MATRIX_TRANSFORMATIONS.viewUpDirection // Top of the view frustum.
        );
        DIRECT_3D_DEVICE -> SetTransform(D3DTS_VIEW, &MATRIX_TRANSFORMATIONS.view);

        // [Projection Transform]
        ::D3DXMatrixPerspectiveFovLH(&MATRIX_TRANSFORMATIONS.projection,
            D3DXToRadian(45.0f), // Horizontal FoV (Field-of-View).
            (FLOAT) RENDER_WIDTH / (FLOAT) RENDER_HEIGHT, // Aspect ratio.
            1.0f, // Near-view plane; not render relatively close objects.
            100.0f // Far-view plane; not render relatively far objects.
        );
        DIRECT_3D_DEVICE -> SetTransform(D3DTS_PROJECTION, &MATRIX_TRANSFORMATIONS.projection);

        // [Draw]
        DIRECT_3D_DEVICE -> DrawPrimitive(D3DPT_TRIANGLELIST, 0u, 1u /* Single triangle in the list. */);
    }

    // [Terminate]
    DIRECT_3D_DEVICE -> EndScene(); // End the 3D scene.
    DIRECT_3D_DEVICE -> Present(NULL, NULL, NULL, NULL); // Display the created frame.
}

/* : Terminate -> Release & terminate Direct3D. */
void Terminate(void) {
    // Deletion
    VERTEX_BUFFER -> Release();
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
            0x0, windowClassInformation.lpszClassName, "Direct 3D | Depth", WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, RENDER_WIDTH, RENDER_HEIGHT,
            HWND_DESKTOP, (HMENU) NULL, windowClassInformation.hInstance, (LPVOID) (LPARAM) appearance
        );

        // Logic > ...
        if (NULL == windowHandle) exitCode = EXIT_FAILURE;
        else {
            // Initialization > Thread Message
            MSG threadMessage = {};

            /* Initiate ... */
            Initiate(windowHandle, TRIANGLE, 3u);
            for (BOOL threadMessageAvailable = FALSE; WM_QUIT != threadMessage.message; threadMessageAvailable = ::PeekMessage(&threadMessage, NULL, 0x0, 0x0, PM_REMOVE)) {
                /* ... Update */
                if (threadMessageAvailable) ::DispatchMessage(&threadMessage);
                else { Update(); }
            }

            /* Terminate ... */
            Terminate();
            exitCode = threadMessage.wParam;
        }

        // Deletion
        ::UnregisterClass(windowClassInformation.lpszClassName, windowClassInformation.hInstance);
    }

    // Return
    return exitCode;
}
