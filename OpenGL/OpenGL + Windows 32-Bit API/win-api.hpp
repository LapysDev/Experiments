// Logic
#ifndef WIN32_API
    /* Definition > ... */
    #define WIN32_API

    /* Import */
    #include "helper.hpp" // Helper
    #include <windows.h> // Windows
    #include <windowsx.h> // Windows X

    /* Namespace */
    namespace Win32 {
        /* Namespace > ... */
        namespace Event {}
        namespace Graphics {}
        namespace Style {}

        /* Namespace */
            /* Event --- NOTE (Lapys) -> Also known as messages. --- REDACT (Lapys) */
            namespace Event {
                namespace Device {
                    namespace Keyboard {
                        const WPARAM Activate = WM_ACTIVATE;
                        const WPARAM ApplicationCommand = WM_APPCOMMAND;
                        const WPARAM Character = WM_CHAR;
                        const WPARAM DeadCharacter = WM_DEADCHAR;
                        const WPARAM Hotkey = WM_HOTKEY;
                        const WPARAM Keydown = WM_KEYDOWN;
                        const WPARAM Keyup = WM_KEYUP;
                        const WPARAM KillFocus = WM_KILLFOCUS;
                        const WPARAM SetFocus = WM_SETFOCUS;
                        const WPARAM SystemDeadCharacter = WM_SYSDEADCHAR;
                        const WPARAM SystemKeydown = WM_SYSKEYDOWN;
                        const WPARAM SystemKeyup = WM_SYSKEYUP;

                        inline const bool ControlKeyIsActive(WPARAM MessageInformation) { return MessageInformation & MK_CONTROL; }
                        inline const bool ShiftKeyIsActive(WPARAM MessageInformation) { return MessageInformation & MK_SHIFT; }
                    }

                    namespace Mouse {
                        const unsigned int Activate = WM_MOUSEACTIVATE;
                        const LPARAM CaptureChange = WM_CAPTURECHANGED;
                        const LPARAM Hover = WM_MOUSEHOVER;
                        const LPARAM Leave = WM_MOUSELEAVE;
                        const LPARAM LeftButtonDoubleClick = WM_LBUTTONDBLCLK;
                        const LPARAM LeftButtonDown = WM_LBUTTONDOWN;
                        const LPARAM LeftButtonUp = WM_LBUTTONUP;
                        const LPARAM MiddleButtonDoubleClick = WM_MBUTTONDBLCLK;
                        const LPARAM MiddleButtonDown = WM_MBUTTONDOWN;
                        const LPARAM MiddleButtonUp = WM_MBUTTONUP;
                        const LPARAM Move = WM_MOUSEMOVE;
                        const LPARAM NonClientLeftButtonDoubleClick = WM_NCLBUTTONDBLCLK;
                        const LPARAM NonClientLeftButtonDown = WM_NCLBUTTONDOWN;
                        const LPARAM NonClientLeftButtonUp = WM_NCLBUTTONUP;
                        const LPARAM NonClientMiddleButtonDoubleClick = WM_NCMBUTTONDBLCLK;
                        const LPARAM NonClientMiddleButtonDown = WM_NCMBUTTONDOWN;
                        const LPARAM NonClientMiddleButtonUp = WM_NCMBUTTONUP;
                        const LPARAM NonClientMouseLeave = WM_NCMOUSELEAVE;
                        const LPARAM NonClientMouseMove = WM_NCMOUSEMOVE;
                        const LPARAM NonClientRightButtonDoubleClick = WM_NCRBUTTONDBLCLK;
                        const LPARAM NonClientRightButtonDown = WM_NCRBUTTONDOWN;
                        const LPARAM NonClientRightButtonUp = WM_NCRBUTTONUP;
                        const LPARAM NonClientXButtonDoubleClick = WM_NCXBUTTONDBLCLK;
                        const LPARAM NonClientXButtonDown = WM_NCXBUTTONDOWN;
                        const LPARAM NonClientXButtonUp = WM_NCXBUTTONUP;
                        const LPARAM NonClientHover = WM_NCMOUSEHOVER;
                        const LPARAM RightButtonDoubleClick = WM_RBUTTONDBLCLK;
                        const LPARAM RightButtonDown = WM_RBUTTONDOWN;
                        const LPARAM RightButtonUp = WM_RBUTTONUP;
                        const LPARAM Wheel = WM_MOUSEWHEEL;
                        const LPARAM XButtonDoubleClick = WM_XBUTTONDBLCLK;
                        const LPARAM XButtonDown = WM_XBUTTONDOWN;
                        const LPARAM XButtonUp = WM_XBUTTONUP;

                        inline const bool LeftButtonIsActive(WPARAM MessageInformation) { return MessageInformation & MK_LBUTTON; }
                        inline const bool MiddleButtonIsActive(WPARAM MessageInformation) { return MessageInformation & MK_MBUTTON; }
                        inline const bool RightButtonIsActive(WPARAM MessageInformation) { return MessageInformation & MK_RBUTTON; }
                    }
                }

                namespace Window {
                    const LRESULT ActivateApplication = WM_ACTIVATEAPP;
                    const LRESULT ActivateChild = WM_CHILDACTIVATE;
                    const LRESULT CancelMode = WM_CANCELMODE;
                    const LRESULT Close = WM_CLOSE;
                    const LRESULT Compact = WM_COMPACTING;
                    const LRESULT Create = WM_CREATE;
                    const LRESULT Destroy = WM_DESTROY;
                    const LRESULT Enable = WM_ENABLE;
                    const LRESULT EnterSizeMove = WM_ENTERSIZEMOVE;
                    const LRESULT ExitSizeMove = WM_EXITSIZEMOVE;
                    const LRESULT GetIcon = WM_GETICON;
                    const LRESULT GetMinimumMaximumInformation = WM_GETMINMAXINFO;
                    const LRESULT InputLanguageChange = WM_INPUTLANGCHANGE;
                    const LRESULT InputLanguageChangeRequest = WM_INPUTLANGCHANGEREQUEST;
                    const LRESULT Move = WM_MOVE;
                    const LRESULT Moving = WM_MOVING;
                    const LRESULT NonClientActivate = WM_NCACTIVATE;
                    const LRESULT NonClientCalculateSize = WM_NCCALCSIZE;
                    const LRESULT NonClientCreate = WM_NCCREATE;
                    const LRESULT NonClientDestroy = WM_NCDESTROY;
                    const LRESULT NonClientNull = WM_NULL;
                    const LRESULT PositionChanged = WM_WINDOWPOSCHANGED;
                    const LRESULT PositionChanging = WM_WINDOWPOSCHANGING;
                    const LRESULT QueryDragIcon = WM_QUERYDRAGICON;
                    const LRESULT QueryOpen = WM_QUERYOPEN;
                    const LRESULT Quit = WM_QUIT;
                    const LRESULT ShowWindow = WM_SHOWWINDOW;
                    const LRESULT Size = WM_SIZE;
                    const LRESULT Sizing = WM_SIZING;
                    const LRESULT StyleChanged = WM_STYLECHANGED;
                    const LRESULT StyleChanging = WM_STYLECHANGING;
                    const LRESULT ThemeChanged = WM_THEMECHANGED;
                    const LRESULT UserChanged = WM_USERCHANGED;
                }
            }

            /* Style --- REDACT (Lapys) */
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
                        const LPARAM Error = MB_ICONERROR;
                        const LPARAM Exclamation = MB_ICONEXCLAMATION;
                        const LPARAM Information = MB_ICONINFORMATION;
                    }
                    namespace PushButton {
                        const LPARAM Cancel_OK = MB_OKCANCEL;
                        const LPARAM Cancel_Retry = MB_RETRYCANCEL;
                        const LPARAM Cancel_Continue_Try = MB_CANCELTRYCONTINUE;
                        const LPARAM Cancel_No_Yes = MB_YESNOCANCEL;
                        const LPARAM No_Yes = MB_YESNO;
                        const LPARAM OK = MB_OK;
                    }
                    namespace SelectedButton {
                        const LPARAM Cancel = IDCANCEL;
                        const LPARAM Continue = IDCONTINUE;
                        const LPARAM No = IDNO;
                        const LPARAM OK = IDOK;
                        const LPARAM TryAgain = IDTRYAGAIN;
                        const LPARAM Yes = IDYES;
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
    }
#endif
