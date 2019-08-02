/* Logic */
#ifndef DIRECT_X
    /* Definition */
    #define DIRECT_X

    /* Import */
    #include <stdio.h> // Standard Input-Output
    #include <string.h> // String
    #include <unistd.h> // Unix Standard
    #include <windows.h> // Windows
    #include <windowsx.h> // Windows X

    /* Global > Strict */
    struct FUNCTION_ARGUMENT_FLAG { public: template <typename type> inline type operator =(type argument) { return argument; } } _STRICT;

    /* Namespace > Lapys */
    namespace Lapys {
        /* Namespace > ... */
        namespace Console {}
        namespace Event {}
        namespace Data {}
        namespace Graphics {}
        namespace Settings {}
        namespace Style {}

        /* Namespace */
            /* Event > ... --- REDACT (Lapys) */
            namespace Event {
                namespace Device {
                    namespace Keyboard {
                        const unsigned int Activate = WM_ACTIVATE;
                        const unsigned int ApplicationCommand = WM_APPCOMMAND;
                        const unsigned int Character = WM_CHAR;
                        const unsigned int DeadCharacter = WM_DEADCHAR;
                        const unsigned int Hotkey = WM_HOTKEY;
                        const unsigned int Keydown = WM_KEYDOWN;
                        const unsigned int Keyup = WM_KEYUP;
                        const unsigned int KillFocus = WM_KILLFOCUS;
                        const unsigned int SetFocus = WM_SETFOCUS;
                        const unsigned int SystemDeadCharacter = WM_SYSDEADCHAR;
                        const unsigned int SystemKeydown = WM_SYSKEYDOWN;
                        const unsigned int SystemKeyup = WM_SYSKEYUP;
                    }

                    namespace Mouse {
                        const unsigned int Activate = WM_MOUSEACTIVATE;
                        const unsigned int CaptureChange = WM_CAPTURECHANGED;
                        const unsigned int Hover = WM_MOUSEHOVER;
                        const unsigned int Leave = WM_MOUSELEAVE;
                        const unsigned int LeftButtonDoubleClick = WM_LBUTTONDBLCLK;
                        const unsigned int LeftButtonDown = WM_LBUTTONDOWN;
                        const unsigned int LeftButtonUp = WM_LBUTTONUP;
                        const unsigned int MiddleButtonDoubleClick = WM_MBUTTONDBLCLK;
                        const unsigned int MiddleButtonDown = WM_MBUTTONDOWN;
                        const unsigned int MiddleButtonUp = WM_MBUTTONUP;
                        const unsigned int Move = WM_MOUSEMOVE;
                        const unsigned int NonClientLeftButtonDoubleClick = WM_NCLBUTTONDBLCLK;
                        const unsigned int NonClientLeftButtonDown = WM_NCLBUTTONDOWN;
                        const unsigned int NonClientLeftButtonUp = WM_NCLBUTTONUP;
                        const unsigned int NonClientMiddleButtonDoubleClick = WM_NCMBUTTONDBLCLK;
                        const unsigned int NonClientMiddleButtonDown = WM_NCMBUTTONDOWN;
                        const unsigned int NonClientMiddleButtonUp = WM_NCMBUTTONUP;
                        const unsigned int NonClientMouseLeave = WM_NCMOUSELEAVE;
                        const unsigned int NonClientMouseMove = WM_NCMOUSEMOVE;
                        const unsigned int NonClientRightButtonDoubleClick = WM_NCRBUTTONDBLCLK;
                        const unsigned int NonClientRightButtonDown = WM_NCRBUTTONDOWN;
                        const unsigned int NonClientRightButtonUp = WM_NCRBUTTONUP;
                        const unsigned int NonClientXButtonDoubleClick = WM_NCXBUTTONDBLCLK;
                        const unsigned int NonClientXButtonDown = WM_NCXBUTTONDOWN;
                        const unsigned int NonClientXButtonUp = WM_NCXBUTTONUP;
                        const unsigned int NonClientHover = WM_NCMOUSEHOVER;
                        const unsigned int RightButtonDoubleClick = WM_RBUTTONDBLCLK;
                        const unsigned int RightButtonDown = WM_RBUTTONDOWN;
                        const unsigned int RightButtonUp = WM_RBUTTONUP;
                        const unsigned int Wheel = WM_MOUSEWHEEL;
                        const unsigned int XButtonDoubleClick = WM_XBUTTONDBLCLK;
                        const unsigned int XButtonDown = WM_XBUTTONDOWN;
                        const unsigned int XButtonUp = WM_XBUTTONUP;

                        inline const bool ControlKeyIsActive(WPARAM MessageInformation) { return MessageInformation & MK_CONTROL; }
                        inline const bool LeftButtonIsActive(WPARAM MessageInformation) { return MessageInformation & MK_LBUTTON; }
                        inline const bool MiddleButtonIsActive(WPARAM MessageInformation) { return MessageInformation & MK_MBUTTON; }
                        inline const bool RightButtonIsActive(WPARAM MessageInformation) { return MessageInformation & MK_RBUTTON; }
                        inline const bool ShiftKeyIsActive(WPARAM MessageInformation) { return MessageInformation & MK_SHIFT; }
                    }
                }

                namespace Window {
                    const unsigned int ActivateApplication = WM_ACTIVATEAPP;
                    const unsigned int ActivateChild = WM_CHILDACTIVATE;
                    const unsigned int CancelMode = WM_CANCELMODE;
                    const unsigned int Close = WM_CLOSE;
                    const unsigned int Compact = WM_COMPACTING;
                    const unsigned int Create = WM_CREATE;
                    const unsigned int Destroy = WM_DESTROY;
                    const unsigned int Enable = WM_ENABLE;
                    const unsigned int EnterSizeMove = WM_ENTERSIZEMOVE;
                    const unsigned int ExitSizeMove = WM_EXITSIZEMOVE;
                    const unsigned int GetIcon = WM_GETICON;
                    const unsigned int GetMinimumMaximumInformation = WM_GETMINMAXINFO;
                    const unsigned int InputLanguageChange = WM_INPUTLANGCHANGE;
                    const unsigned int InputLanguageChangeRequest = WM_INPUTLANGCHANGEREQUEST;
                    const unsigned int Move = WM_MOVE;
                    const unsigned int Moving = WM_MOVING;
                    const unsigned int NonClientActivate = WM_NCACTIVATE;
                    const unsigned int NonClientCalculateSize = WM_NCCALCSIZE;
                    const unsigned int NonClientCreate = WM_NCCREATE;
                    const unsigned int NonClientDestroy = WM_NCDESTROY;
                    const unsigned int NonClientNull = WM_NULL;
                    const unsigned int PositionChanged = WM_WINDOWPOSCHANGED;
                    const unsigned int PositionChanging = WM_WINDOWPOSCHANGING;
                    const unsigned int QueryDragIcon = WM_QUERYDRAGICON;
                    const unsigned int QueryOpen = WM_QUERYOPEN;
                    const unsigned int Quit = WM_QUIT;
                    const unsigned int ShowWindow = WM_SHOWWINDOW;
                    const unsigned int Size = WM_SIZE;
                    const unsigned int Sizing = WM_SIZING;
                    const unsigned int StyleChanged = WM_STYLECHANGED;
                    const unsigned int StyleChanging = WM_STYLECHANGING;
                    const unsigned int ThemeChanged = WM_THEMECHANGED;
                    const unsigned int UserChanged = WM_USERCHANGED;
                }
            }

            /* Settings */
            namespace Settings {
                /* Global > ... */
                bool flushOutputBufferOnNewline = false;
            }

            /* Style > ... --- REDACT (Lapys) */
            namespace Style {
                namespace Brush {
                    const HBRUSH ActiveBorder = (HBRUSH) COLOR_ACTIVEBORDER;
                    const HBRUSH ActiveCaption = (HBRUSH) COLOR_ACTIVECAPTION;
                    const HBRUSH ApplicationWorkspace = (HBRUSH) COLOR_APPWORKSPACE;
                    const HBRUSH Background = (HBRUSH) COLOR_BACKGROUND;
                    const HBRUSH ButtonFace = (HBRUSH) COLOR_BTNFACE;
                    const HBRUSH ButtonShadow = (HBRUSH) COLOR_BTNSHADOW;
                    const HBRUSH ButtonText = (HBRUSH) COLOR_BTNTEXT;
                    const HBRUSH CaptionText = (HBRUSH) COLOR_CAPTIONTEXT;
                    const HBRUSH GrayText = (HBRUSH) COLOR_GRAYTEXT;
                    const HBRUSH Highlight = (HBRUSH) COLOR_HIGHLIGHT;
                    const HBRUSH HighlightText = (HBRUSH) COLOR_HIGHLIGHTTEXT;
                    const HBRUSH InactiveBorder = (HBRUSH) COLOR_INACTIVEBORDER;
                    const HBRUSH InactiveCaption = (HBRUSH) COLOR_INACTIVECAPTION;
                    const HBRUSH Menu = (HBRUSH) COLOR_MENU;
                    const HBRUSH MenuText = (HBRUSH) COLOR_MENUTEXT;
                    const HBRUSH Scrollbar = (HBRUSH) COLOR_SCROLLBAR;
                    const HBRUSH Window = (HBRUSH) COLOR_WINDOW;
                    const HBRUSH WindowFrame = (HBRUSH) COLOR_WINDOWFRAME;
                    const HBRUSH WindowText = (HBRUSH) COLOR_WINDOWTEXT;
                }

                namespace Cursor {
                    const LPCTSTR ApplicationStarting = IDC_APPSTARTING;
                    const LPCTSTR Arrow = IDC_ARROW;
                    const LPCTSTR CardinalAll = IDC_SIZE/* || IDC_SIZEALL*/;
                    const LPCTSTR CardinalNortheastSouthwest = IDC_SIZENESW;
                    const LPCTSTR CardinalNorthSouth = IDC_SIZENS;
                    const LPCTSTR CardinalWestEast = IDC_SIZEWE;
                    const LPCTSTR Crosshair = IDC_CROSS;
                    const LPCTSTR Hand = IDC_HAND;
                    const LPCTSTR Help = IDC_HELP;
                    const LPCTSTR Icon = IDC_ICON;
                    const LPCTSTR No = IDC_NO;
                    const LPCTSTR UpArrow = IDC_UPARROW;
                    const LPCTSTR Wait = IDC_WAIT;
                }

                namespace MessageBox {
                    namespace Icon {
                        const unsigned int Error = MB_ICONERROR;
                        const unsigned int Exclamation = MB_ICONEXCLAMATION;
                        const unsigned int Information = MB_ICONINFORMATION;
                    }
                    namespace PushButton {
                        const unsigned int Cancel_OK = MB_OKCANCEL;
                        const unsigned int Cancel_Retry = MB_RETRYCANCEL;
                        const unsigned int Cancel_Continue_Try = MB_CANCELTRYCONTINUE;
                        const unsigned int Cancel_No_Yes = MB_YESNOCANCEL;
                        const unsigned int No_Yes = MB_YESNO;
                        const unsigned int OK = MB_OK;
                    }
                    namespace SelectedButton {
                        const unsigned int Cancel = IDCANCEL;
                        const unsigned int Continue = IDCONTINUE;
                        const unsigned int No = IDNO;
                        const unsigned int OK = IDOK;
                        const unsigned int TryAgain = IDTRYAGAIN;
                        const unsigned int Yes = IDYES;
                    }
                }

                namespace Window {
                    namespace Appearance {
                        const unsigned int ClientEdge = WS_EX_CLIENTEDGE;
                        const unsigned int LeftAlign = WS_EX_LEFT;
                        const unsigned int LeftScrollbar = WS_EX_LEFTSCROLLBAR; // NOTE (Lapys) -> For specified languages only.
                        const unsigned int LeftToRightReading = WS_EX_LTRREADING;
                        const unsigned int Maximized = WS_MAXIMIZEBOX;
                        const unsigned int MDIChild = WS_EX_MDICHILD;
                        const unsigned int Minimized = WS_MINIMIZEBOX;
                        const unsigned int Overlapped = WS_OVERLAPPEDWINDOW/* || WS_EX_OVERLAPPEDWINDOW || (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)*/;
                        const unsigned int Palette = WS_EX_PALETTEWINDOW/* || (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)*/;
                        const unsigned int RaisedEdge = WS_EX_WINDOWEDGE;
                        const unsigned int RightAlign = WS_EX_RIGHT;
                        const unsigned int RightScrollbar = WS_EX_RIGHTSCROLLBAR;
                        const unsigned int RightToLeftLayout = WS_EX_LAYOUTRTL; // NOTE (Lapys) -> For specified languages only.
                        const unsigned int RightToLeftReading = WS_EX_RTLREADING; // NOTE (Lapys) -> For specified languages only.
                        const unsigned int StaticEdge = WS_EX_STATICEDGE;
                        const unsigned int TopMost = WS_EX_TOPMOST;
                        const unsigned int Transparent = WS_EX_TRANSPARENT;
                    }
                    namespace Function {
                        const unsigned int AcceptFiles = WS_EX_ACCEPTFILES;
                        const unsigned int AllowChildRedrawOSelf = CS_PARENTDC; // NOTE (Lapys) -> Improves performance.
                        const unsigned int ApplicationWindow = WS_EX_APPWINDOW;
                        const unsigned int ByteBoundaryAlign = CS_BYTEALIGNWINDOW;
                        const unsigned int ClassDeviceContext = CS_CLASSDC;
                        const unsigned int ClientByteBoundaryAlign = CS_BYTEALIGNCLIENT;
                        const unsigned int Composited = WS_EX_COMPOSITED; /* NOTE (Lapys) -> The window and its children are rendered with double-buffering.
                                                                                Incompatible with:
                                                                                    `Lapys::Style::Window::Function::ClassDeviceContext` or
                                                                                    `Lapys::Style::Window::Function::OwnDeviceContext`. */
                        const unsigned int ContextHelp = WS_EX_CONTEXTHELP; /* NOTE (Lapys) ->
                                                                                Incompatible with:
                                                                                    `Lapys::Style::Window::Appearance::Maximized` or
                                                                                    `Lapys::Style::Window::Appearance::Minimized` */
                        const unsigned int ControlParent = WS_EX_CONTROLPARENT;
                        const unsigned int DoubleClickable = CS_DBLCLKS;
                        const unsigned int DialogModalFrame = WS_EX_DLGMODALFRAME; // NOTE (Lapys) -> Double-bordered.
                        const unsigned int HorizontalRedraw = CS_HREDRAW;
                        const unsigned int Inactive = WS_EX_NOACTIVATE;
                        const unsigned int GlobalClass = CS_GLOBALCLASS;
                        const unsigned int Layered = WS_EX_LAYERED; /* NOTE (Lapys) ->
                                                                        Incompatible with:
                                                                            `Lapys::Style::Window::Function::ClassDeviceContext` or
                                                                            `Lapys::Style::Window::Function::OwnDeviceContext`. */
                        const unsigned int NoChildNotification = WS_EX_NOPARENTNOTIFY;
                        const unsigned int NonInherited = WS_EX_NOINHERITLAYOUT;
                        const unsigned int NoClose = CS_NOCLOSE;
                        const unsigned int OwnDeviceContext = CS_OWNDC;
                        const unsigned int SaveRenderAsBitmap = CS_SAVEBITS;
                        const unsigned int Tool = WS_EX_TOOLWINDOW;
                        const unsigned int VerticalRedraw = CS_VREDRAW;
                    }
                }
            }

        /* Namespace */
            /* Console */
            namespace Console {
                /* Functions */
                    // Flush Output Buffer
                    const int FlushOutputBuffer() { return ::fflush(stdout); }

                    // Write (Line)
                    void Write(const char* Message) { const unsigned MESSAGE_LENGTH = ::strlen(Message); if (Lapys::Settings::flushOutputBufferOnNewline) { unsigned messageIterator = MESSAGE_LENGTH; while (messageIterator) if (*(Message + (messageIterator -= 1)) == '\n') { messageIterator = 0; Lapys::Console::FlushOutputBuffer(); } } ::write(STDOUT_FILENO, Message, MESSAGE_LENGTH); }
                    void WriteLine(const char* Message) { ::puts(Message); Lapys::Settings::flushOutputBufferOnNewline && Lapys::Console::FlushOutputBuffer(); }
            }

            /* Data */
            namespace Data {
                /* Functions, Global */
                    // Default Window [Event Loop] Message Handler (Pointer)
                    LRESULT CALLBACK DefaultWindowMessageHandler(HWND HandlerWindow, const unsigned int Message, WPARAM MessageInformation, LPARAM AdditionalMessageInformatio) {
                        // Logic > ...
                        switch (Message) {
                            case Lapys::Event::Window::Destroy: { ::PostQuitMessage(0); return 0; } break;
                            default: return ::DefWindowProc(HandlerWindow, Message, MessageInformation, AdditionalMessageInformatio);
                        }
                    } LRESULT CALLBACK (*DefaultWindowMessageHandlerPointer)(HWND HandlerWindow, unsigned int Message, WPARAM MessageInformation, LPARAM AdditionalMessageInformatio) = &Lapys::Data::DefaultWindowMessageHandler;

                    // Create Window Class
                    const WNDCLASSEX& CreateWindowClass(
                        const char* ClassName,
                        HINSTANCE HandlerInstance,
                        LRESULT CALLBACK (*WindowMessageHandler)(HWND HandlerWindow, unsigned int Message, WPARAM MessageInformation, LPARAM AdditionalMessageInformatio) = Lapys::Data::DefaultWindowMessageHandlerPointer,
                        const unsigned int WindowStyle = Lapys::Style::Window::Function::DoubleClickable | Lapys::Style::Window::Function::HorizontalRedraw | Lapys::Style::Window::Function::VerticalRedraw,
                        const HBRUSH BackgroundColor = Lapys::Style::Brush::Window,
                        const LPCTSTR CursorStyle = Lapys::Style::Cursor::Arrow
                    ) {
                        // Constant > Window Class
                        static WNDCLASSEX WINDOW_CLASS;

                        // Deletion --- NOTE (Lapys) -> Clear out the Window Class for use.
                        ::ZeroMemory(&WINDOW_CLASS, sizeof(WINDOW_CLASS));

                        // Modification > Window Class > ... --- REDACT (Lapys)
                        WINDOW_CLASS.cbSize = sizeof(WNDCLASSEX); // NOTE (Lapys) -> Size up the Window Class to specify its measurements.
                        WINDOW_CLASS.hbrBackground = BackgroundColor;
                        WINDOW_CLASS.hCursor = ::LoadCursor(NULL, CursorStyle);
                        WINDOW_CLASS.hInstance = HandlerInstance;
                        WINDOW_CLASS.lpfnWndProc = *WindowMessageHandler; // NOTE (Lapys) -> The Event Loop.
                        WINDOW_CLASS.lpszClassName = ClassName;
                        WINDOW_CLASS.style = WindowStyle;

                        // Return
                        return WINDOW_CLASS;
                    }

                    // Register Window Class
                    WINUSERAPI ATOM WINAPI RegisterWindowClass(WNDCLASSEX& WindowClass) { return ::RegisterClassEx(&WindowClass); }

                    // Run Message Queue --- NOTE (Lapys) -> Or run an Event Loop.
                    MSG& RunMessageQueue(MSG& Message) {
                        // Loop
                        while (::GetMessage(&Message, NULL, 0, 0)) {
                            // (Translate, Dispatch) Message > Message
                            ::TranslateMessage(&Message);
                            ::DispatchMessage(&Message);
                        }

                        // Return
                        return Message;
                    }
            }

            /* Graphics */
            namespace Graphics {
                /* Functions */
                    // Spawn Message Box
                    const int SpawnMessageBox(
                        HWND HandlerWindow, const wchar_t* Title, const wchar_t* Content,
                        const unsigned int Style = Lapys::Style::MessageBox::PushButton::OK
                    ) { return ::MessageBoxW(HandlerWindow, Title, Content, Style); }

                    // Spawn Window
                    const HWND& SpawnWindow(
                        const char* Title,
                        WNDCLASSEX& Class, HINSTANCE HandlerInstance,
                        const signed int Height, const signed int Width, const signed int X = 0, const signed int Y = 0,
                        const unsigned int Style = Lapys::Style::Window::Appearance::Overlapped, const unsigned int ExtendedStyle = 0x00000000L,
                        HWND HandlerParentWindow = NULL, HMENU HandlerMenus = NULL,
                        LPVOID USED_WITH_MULTIPLE_WINDOWS = NULL
                    ) {
                        // Constant > Window Handler; Return
                        static HWND WINDOW_HANDLER;
                        return (WINDOW_HANDLER = ::CreateWindowEx(
                            ExtendedStyle,
                            Class.lpszClassName,
                            Title, Style,
                            X, Y, Width, Height,
                            HandlerParentWindow, HandlerMenus, HandlerInstance,
                            _STRICT = USED_WITH_MULTIPLE_WINDOWS
                        ));
                    }
            }
    }
#endif
