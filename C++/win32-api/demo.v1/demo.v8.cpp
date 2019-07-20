/* Library Files */
    // Standard Library Header
    #include <stdlib.h>

    // Their Character Header
    #include <tchar.h>

    // Windows
    #include <windows.h>

/* Global Data */
    // (Age, Name) Input, Logo, (Update) Message, Window
    HWND ageInput, logo, message, nameInput, updateMessage, window;

    // Dialog Class Name
    LPCWSTR dialogClassName = L"Dialog";

    // (Icon, Update Message) Image
    HBITMAP iconImg, updateMessageImg;

    // Author
    #define AUTHOR "Lapys"

    // Description
    #define DESCRIPTION "First GUI program made by the Lapys Dev Team."

    // Close Dialog
    #define CLOSE_DIALOG 1

    // Exit
    #define EXIT 2

    // New
    #define NEW 3

    // Show Help
    #define SHOW_HELP 4

    // Test Sound
    #define TEST_SOUND 5

    // Update Message
    #define UPDATE_MESSAGE 6

/* Functions */
    // Dialog Procedure
    LRESULT CALLBACK DialogProcedure(HWND dialog, UINT msg, WPARAM wp, LPARAM lp) {
        /* Logic
                [switch:case:default statement]
        */
        switch (msg) {
            // Window Manager : Command
            case WM_COMMAND:
                /* Logic
                        [switch:case statement]
                */
                switch (wp) {
                    // Close Dialog > (Destroy, Enable) Window
                    case CLOSE_DIALOG:
                        DestroyWindow(dialog);
                        EnableWindow(window, !0);
                        break;
                }
                break;

            // Window Manager : Destroy > (Destroy, Enable) Window
            case WM_DESTROY:
                DestroyWindow(dialog);
                EnableWindow(window, !0);
                break;

            // [Default] > Return
            default: return DefWindowProcW(dialog, msg, wp, lp);
        }
    };

    // Handle Controls
    void handleControls(HWND window) {
        // Create Window
            // Logo
            logo = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 207.5, 0, 60, 60, window, NULL, NULL, NULL);
                // Send Message > Logo
                ::SendMessage(logo, STM_SETIMAGE, (WPARAM) IMAGE_BITMAP, (LPARAM) iconImg);

            // Name
            CreateWindowW(L"static", L"Name", WS_VISIBLE | WS_CHILD, 70, 70, 150, 27.5, window, NULL, NULL, NULL);
            nameInput = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 250, 70, 175, 27.5, window, NULL, NULL, NULL);

            // Age
            CreateWindowW(L"static", L"Age", WS_VISIBLE | WS_CHILD, 70, 120, 150, 27.5, window, NULL, NULL, NULL);
            ageInput = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 250, 120, 175, 27.5, window, NULL, NULL, NULL);

            // Update Message
            updateMessage = CreateWindowW(L"button" , L"Update Message", WS_VISIBLE | WS_CHILD | BS_BITMAP, 175, 165, 150, 65, window, (HMENU) UPDATE_MESSAGE, NULL, NULL);
                // Send Message > Update Message
                ::SendMessage(updateMessage, BM_SETIMAGE, (WPARAM) IMAGE_BITMAP, (LPARAM) updateMessageImg);

            // Message
            message = CreateWindowW(L"static", L"Please enter your valid name and age", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 90, 245, 300, 300, window, NULL, NULL, NULL);
    };

    // Handle Dialog Controls
    void handleDialogControls(HWND dialog) {
        // Create Window
            // Close
            CreateWindowW(L"button", L"Close New Window", WS_VISIBLE | WS_CHILD, 100, 50, 200, 30, dialog, (HMENU) CLOSE_DIALOG, NULL, NULL);
    };

    // Handle Menus
    void handleMenus(HWND window) {
        // Initialization > (Menu, File, Options)
        HMENU menu = CreateMenu(),
            file = CreateMenu(),
            options = CreateMenu();

        // Append Menu > Menu
            // File
            AppendMenu(menu, MF_POPUP, (UINT_PTR) file, "File");
                // New
                AppendMenu(file, MF_STRING, NEW, "New");

                // [Separator]
                AppendMenu(file, MF_SEPARATOR, 0, NULL);

                // Exit
                AppendMenu(file, MF_STRING, EXIT, "Exit");

            // Options
            AppendMenu(menu, MF_POPUP, (UINT_PTR) options, "Options");
                // Test Sounds
                AppendMenu(options, MF_STRING, TEST_SOUND, "Test Sounds");

            // Help
            AppendMenu(menu, MF_STRING, SHOW_HELP, "Help");

        // Set Menu
        SetMenu(window, menu);
    };

    // Load Images
    void loadImages() {
        // Update > (Icon Image, Update Message Image)
        iconImg = (HBITMAP)::LoadImageW(NULL, L"icon.bmp", IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE | LR_DEFAULTSIZE);
            (iconImg == NULL) && (iconImg = (HBITMAP)::LoadImageW(NULL, L"no-img.bmp", IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE | LR_DEFAULTSIZE));
        updateMessageImg = (HBITMAP)::LoadImageW(NULL, L"update-message.bmp", IMAGE_BITMAP, 150, 65, LR_LOADFROMFILE | LR_DEFAULTSIZE);
            (updateMessageImg == NULL) && (updateMessageImg = (HBITMAP)::LoadImageW(NULL, L"no-img.bmp", IMAGE_BITMAP, 150, 65, LR_LOADFROMFILE | LR_DEFAULTSIZE));
    };

    // Register Dialog
    void registerDialog(HWND window) {
        // Initialization > Dialog
        HWND dialog = CreateWindowW(dialogClassName, L"New Window", WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 425, 250, window, NULL, NULL, NULL);

        // Handle Dialog Controls
        handleDialogControls(dialog);
    };

    // Register Dialog Class
    void registerDialogClass(HINSTANCE hInst) {
        // Initialization > (Window Class, Message)
        WNDCLASSW dialogClass = {0};

        // Modification > Window Class
            // Handle Brush Background
            dialogClass.hbrBackground = (HBRUSH) COLOR_WINDOW + 4;

            // Handle Cursor
            dialogClass.hCursor = LoadCursor(NULL, IDC_ARROW);

            // Handle Instance
            dialogClass.hInstance = hInst;

            // Size of Long Pointer : Class Name
            dialogClass.lpszClassName = dialogClassName;

            // Long Pointer Function : Window Procedure
            dialogClass.lpfnWndProc = DialogProcedure;

        // {Register Window Class > Dialog Class}
        RegisterClassW(&dialogClass);
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
                    // Exit > (Destroy Window > Window)
                    case EXIT: (MessageBox(window, "Are you sure?", "Wait!", MB_ICONEXCLAMATION | MB_YESNO) == IDYES) && DestroyWindow(window); break;

                    // New
                    case NEW: {
                        // Register Dialog > Window
                        registerDialog(window);

                        /* Enable Window > Window
                                --- NOTE ---
                                    #Lapys: The window's state depends on the second argument.
                        */
                        EnableWindow(window, !1);
                    } break;

                    // Show Help
                    case SHOW_HELP: {
                        // Initialization > (File Path, Message, Instance)
                        char filepath[MAX_PATH],
                            message[MAX_PATH];
                        HINSTANCE hInstance = GetModuleHandle(NULL);

                        // Get Module File Name > Handle Instance
                        GetModuleFileName(hInstance, filepath, MAX_PATH);

                        // Update > Message
                        strcpy(message, "Demo Application\n\n");
                        strcat(message, "Author: "); strcat(message, AUTHOR); strcat(message, "\n");
                        strcat(message, "Description: "); strcat(message, DESCRIPTION); strcat(message, "\n");
                        strcat(message, "File Path: "); strcat(message, filepath);

                        // Message Box
                        MessageBox(window, message, "About", MB_ICONQUESTION | MB_OK);
                    } break;

                    // Test Sound > (Message Beep > OK)
                    case TEST_SOUND: MessageBeep(MB_OK); break;

                    // Update Message
                    case UPDATE_MESSAGE: {
                        // Initialization > (Age, Name), Message Text
                        char age[150], name[150], messageText[339];

                        // Get Window Text > (Age, Name) Input
                        GetWindowText(ageInput, age, 150);
                        GetWindowText(nameInput, name, 150);

                        /* Logic
                                [if:else statement]

                            > Update > Message Text
                        */
                        if (strcmp(age, "") && strcmp(name, "")) {
                            strcpy(messageText, "Hello ");
                            strcat(messageText, name);
                            strcat(messageText, ". You are ");
                            strcat(messageText, age);
                            strcat(messageText, " years of age, correct?");
                        }

                        else
                            strcpy(messageText, "Please state your age and name");

                        // Set Window Text > Message
                        SetWindowText(message, messageText);
                    } break;
                }
                break;

            // Window Manager : Create > (...)
            case WM_CREATE:
                loadImages();
                handleControls(window);
                handleMenus(window);
                break;

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
            wc.hbrBackground = (HBRUSH) COLOR_WINDOW + 4;

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
            MessageBox(NULL, "The window you tried to register failed! :-(", "Window Registration Error", MB_ICONEXCLAMATION | MB_OK);

            // Return
            return -1;
        }

        else
            // Register Dialog Class
            registerDialogClass(hInst);

        // Update > Window
        window = CreateWindowW(className, L"Demo Application", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 500, 600, NULL, NULL, hInst, NULL);

        /* Loop
                The Event Loop.

            > (Translate, Dispatch) Message > Message
        */
        while (GetMessage(&msg, NULL, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Return
        return 0;
    }
