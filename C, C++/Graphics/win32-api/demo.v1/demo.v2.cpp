/* Library Files */
    // Windows
    #include <windows.h>

    // Their Character Header
    #include <tchar.h>

/* Functions */
    // Window Procedure
    LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
        /* Logic
                [switch:case:default statement]
        */
        switch (msg) {
            // Window Manager : Destroy
            case WM_DESTROY: PostQuitMessage(false); break;

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

        // {Register Window Class > Window Class} Logic > Return
        if (!RegisterClassW(&wc))
            return -1;

        // Create Window
        CreateWindowW(className, L"My Window", WS_OVERLAPPED | WS_VISIBLE, 0, 0, 500, 300, NULL, NULL, hInst, NULL);

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
