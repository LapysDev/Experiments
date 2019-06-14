/* Import */
#include <iostream> // Input-Output Stream
#include <windows.h> // Windows

/* Definition > ... --- NOTE (Lapys) -> Abstract all Windows 32 classes, structures & types. */
#define Callback __stdcall
#define WinAPI __stdcall
    #define APIEntry WinAPI

typedef unsigned char byte;
typedef unsigned long double_word;
    typedef double_word languageGroupIdentifier;
    typedef double_word localeIdentifier;
    typedef double_word localeInformationType;
typedef unsigned int double_word32_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
typedef unsigned long long long_double_word;
typedef unsigned short word;
    typedef word atom;
    typedef word languageID;
typedef unsigned long ColorReference;
typedef HANDLE Handle;
    typedef HACCEL AcceleratorTableHandle;
    typedef HBITMAP BitmapHandle;
    typedef HBRUSH BrushHandle;
    typedef HCOLORSPACE ColorSpaceHandle;
    typedef HCURSOR CursorHandle;
    typedef HDWP DeferredWindowPositionHandle;
    typedef HDC DeviceContextHandle;
    typedef HDESK DesktopHandle;
    typedef HCONV DynamicDataExchangeConversationHandle;
    typedef HCONVLIST DynamicDataExchangeConversationListHandle;
    typedef HDDEDATA DynamicDataExchangeHandle;
    typedef HSZ DynamicDataExchangeStringHandle;
    typedef HENHMETAFILE EnhancedMetaFileHandle;
    typedef int FileHandle;
    typedef HFONT FontHandle;
    typedef HGDIOBJ GDIObjectHandle;
    typedef HGLOBAL GlobalMemoryBlockHandle;
    typedef HHOOK HookHandle;
    typedef HICON IconHandle;
    typedef HKL InputLocaleIdentifierHandle;
    typedef HDROP InternalDropHandle;
    typedef HINSTANCE InstanceHandle;
    typedef HLOCAL LocalMemoryBlockHandle;
    typedef HMENU MenuHandle;
    typedef HMETAFILE MetaFileHandle;
    typedef HMODULE ModuleInstance;
    typedef HMONITOR MonitorHandle;
    typedef HPALETTE PaletteHandle;
    typedef HPEN PenHandle;
    typedef HRGN RegionHandle;
    typedef HKEY RegistryKeyHandle;
    typedef HRSRC ResourceHandle;
    typedef long ResultHandle;
    typedef SC_HANDLE ServiceControlManagerDatabaseHandle;
    typedef SERVICE_STATUS_HANDLE ServiceStatusHandle;
    typedef HWND WindowHandle;
    typedef HWINSTA WindowStationHandle;
typedef MSG Message;
typedef long MessageParameter;
typedef unsigned int UnsignedMessageParameter;
typedef void* ServiceControlManagerDatabaseLock;
typedef WNDCLASS WindowClass;

/* Global > Window */
WindowHandle window;

/* Phase > Update */
long Callback Update(WindowHandle window, const unsigned int message, UnsignedMessageParameter primaryParameters, MessageParameter secondaryParameters) {
    // Logic
    switch (message) {}
}

/* Main --- NOTE (Lapys) -> Can also be the default `main` function. */
int WinAPI WinMain(InstanceHandle instance, InstanceHandle previousInstance, char* arguments, const int) {
    // Constant > Status --- NOTE (Lapys) -> Status of the program.
    int STATUS = 0;

    // Initialization > (Message, Window Class)
    Message message = {0};
    WindowClass windowClass = {0};

    // Modification > Window Class
        // Class Name
        windowClass.lpszClassName = (LPCSTR) L"Window";

        /* Handle Brush Background
                --- NOTE ---
                    #Lapys:
                        Other available colors are:
                        - COLOR_ACTIVEBORDER, COLOR_ACTIVECAPTION, COLOR_APPWORKSPACE
                        - COLOR_BACKGROUND, COLOR_BTNFACE, COLOR_BTNSHADOW, COLOR_BTNTEXT
                        - COLOR_CAPTIONTEXT
                        - COLOR_GRAYTEXT
                        - COLOR_HIGHLIGHT, COLOR_HIGHLIGHTTEXT
                        - COLOR_INACTIVEBORDER, COLOR_INACTIVECAPTION
                        - COLOR_MENU, COLOR_MENUTEXT
                        - COLOR_SCROLLBAR
                        - COLOR_WINDOW, COLOR_WINDOWFRAME, COLOR_WINDOWTEXT
        */
        windowClass.hbrBackground = (BrushHandle) (COLOR_WINDOW + 4);

        // Handler Cursor
        windowClass.hCursor = ::LoadCursor(NULL, IDC_ARROW);

        // Handle Instance
        windowClass.hInstance = instance;

        // Window Procedure
        windowClass.lpfnWndProc = Update;

    // Logic
    if (::RegisterClass(&windowClass)) {}
        // Register Dialog Class > Instance --- UPDATE REQUIRED (Lapys)
        ::registerDialogClass(instance);

    else {
        // Message Box
        ::MessageBox(NULL, "Failure in registering window class.", "Window Registration Error", MB_ICONEXCLAMATION | MB_OK);

        // Update > Status
        STATUS = -1;
    }

    // Logic
    if (~STATUS) {
        // Update > Window --- UPDATE REQUIRED (Lapys)
        window = ::CreateWindow(windowClass.lpszClassName, L"Lapys C++ | Testing Room", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 800, 500, NULL, NULL, instance, NULL);

        // Loop > ... --- NOTE (Lapys) -> The main event loop.
        while (::GetMessage(&message, NULL, 0, 0) > 0) {
            ::TranslateMessage(&message);
            ::DispatchMessage(&message);
        }
    }

    // Return
    return STATUS;
}
