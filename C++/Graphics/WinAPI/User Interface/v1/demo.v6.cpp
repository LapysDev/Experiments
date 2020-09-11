/* Library Files */
    // Standard Library Header
    #include <stdlib.h>

    // Their Character Header
    #include <tchar.h>

    // Windows
    #include <windows.h>

/* Global Data */
    // (Age, Name) Input, Message
    HWND ageInput, message, nameInput;

    // Exit
    #define EXIT 1

    // Update Message
    #define UPDATE_MESSAGE 2

/* Functions */
    // Handle Controls
    void handleControls(HWND window) {
        // Create Window
            // Name
            CreateWindowW(L"static", L"Name", WS_VISIBLE | WS_CHILD, 70, 50, 150, 27.5, window, NULL, NULL, NULL);
            nameInput = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 250, 50, 175, 27.5, window, NULL, NULL, NULL);

            // Age
            CreateWindowW(L"static", L"Age", WS_VISIBLE | WS_CHILD, 70, 100, 150, 27.5, window, NULL, NULL, NULL);
            ageInput = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 250, 100, 175, 27.5, window, NULL, NULL, NULL);

            // Update Message
            CreateWindowW(L"button" , L"Update Message", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 162.5, 200, 40, window, (HMENU) UPDATE_MESSAGE, NULL, NULL);

            // Message
            message = CreateWindowW(L"static", L"Please enter your valid name and age", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 90, 225, 300, 300, window, NULL, NULL, NULL);
    };

    // Window Procedure
    LRESULT CALLBACK WindowProcedure(HWND window, UINT msg, WPARAM wp, LPARAM lp) {
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
                    // Exit > Destroy Window
                    case EXIT: DestroyWindow(window);

                    // Update Message
                    case UPDATE_MESSAGE:
                        // Initialization > (Age, Name), Message Text
                        char age[150], name[150], messageText[339];

                        // Get Window Text > (Age, Name) Input
                        GetWindowText(ageInput, age, 150);
                        GetWindowText(nameInput, name, 150);

                        // Update > Message Text
                        strcpy(messageText, "Hello ");
                        strcat(messageText, name);
                        strcat(messageText, ". You are ");
                        strcat(messageText, age);
                        strcat(messageText, " years of age, correct?");

                        // Set Window Text > Message
                        SetWindowText(message, messageText);
                        break;
                }
                break;

            // Window Manager : Create > Handle Controls
            case WM_CREATE: handleControls(window); break;

            // Window Manager : Destroy > Post Quit Message
            case WM_DESTROY: PostQuitMessage(!1); break;

            /* [Default] > Return
                    --- NOTE ---
                        #Lapys: Do the default action.
            */
            default: return DefWindowProcW(window, msg, wp, lp);
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
        CreateWindowW(className, L"Demo Application", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 500, 600, NULL, NULL, hInst, NULL);

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
