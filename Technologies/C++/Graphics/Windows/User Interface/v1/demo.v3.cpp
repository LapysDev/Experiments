/* Library Files */
    // Their Character Header
    #include <tchar.h>

    // Windows
    #include <windows.h>

/* Global Data */
    // File Menu New
    #define FILE_MENU_NEW 1

    // File Menu Open
    #define FILE_MENU_OPEN 2

    // File Menu Exit
    #define FILE_MENU_EXIT 3

/* Functions */
    // Add Menus
    void AddMenus(HWND hWnd) {
        // Initialization > (...) Menu
        HMENU hMenu = CreateMenu();
        HMENU hFileMenu = CreateMenu();
        HMENU hSubMenu = CreateMenu();

        /* Append Menu > Handle Menu
                --- NOTE ---
                    #Lapys: Append items to the menus.
        */
            // File
            AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hFileMenu, "File");
                // New
                AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");

                // Open
                AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR) hSubMenu, "Open Submenu");
                    // Sub Menu Item
                    AppendMenu(hSubMenu, MF_STRING, NULL, "Submenu Item");

                // [Separator]
                AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);

                // Exit
                AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

            // Help
            AppendMenu(hMenu, MF_STRING, NULL, "Help");

        // Set Menu > Handle Window
        SetMenu(hWnd, hMenu);
    };

    // Window Procedure
    LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
        /* Logic
                [switch:case:default statement]
        */
        switch (msg) {
            /* Window Manager : Command
                    --- NOTE ---
                        #Lapys: Handles commands sent to menus or buttons and other GUI.
            */
            case WM_COMMAND:
                /* Logic
                        [switch]

                        --- NOTE ---
                            #Lapys: Determine which GUI was commanded.
                */
                switch (wp) {
                    // File Menu Exit
                    case FILE_MENU_EXIT: DestroyWindow(hWnd); break;

                    // File Menu New
                    case FILE_MENU_NEW: MessageBeep(MB_OK); break;
                }
                break;

            // Window Manager : Create > Add Menus
            case WM_CREATE: AddMenus(hWnd); break;

            // Window Manager : Destroy > Post Quit Message
            case WM_DESTROY: PostQuitMessage(!1); break;

            /* [Default] > Return
                    --- NOTE ---
                        #Lapys: Do the default action.
            */
            default: return DefWindowProcW(hWnd, msg, wp, lp);
        }
    };

    // Windows Main
    int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
        // Initialization > (Window Class, Class Name, Message)
        WNDCLASSW wc = {0};
        LPCWSTR className = L"Window";
        MSG msg = {0};

        // Modification > Window Class
            // Handle Brush Background
            wc.hbrBackground = (HBRUSH) COLOR_WINDOW;

            // Handle Cursor
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);

            // Handle Instance
            wc.hInstance = hInst;

            // Size of Long Pointer : Class Name
            wc.lpszClassName = className;

            // Long Pointer Function : Window Procedure
            wc.lpfnWndProc = WindowProcedure;

        // {Register Window Class > Window Class} Logic
        if (!RegisterClassW(&wc)) {
            // Message Box
            MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);

            // Return
            return -1;
        }

        // Create Window
        CreateWindowW(className, L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 500, 300, NULL, NULL, hInst, NULL);

        /* Loop
                The Event Loop.

            > (Translate, Dispatch) Message > Message
        */
        while (GetMessage(&msg, NULL, NULL, NULL) > 0) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Return
        return 0;
    }
