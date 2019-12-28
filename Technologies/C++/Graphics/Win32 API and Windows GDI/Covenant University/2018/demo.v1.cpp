/* Library Files */
    // Windows
    #include <windows.h>

    // Their Character Header
    #include <tchar.h>

/* Functions */
    // Windows Main
    int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
        // Message Box
        MessageBox(NULL, "Hello, World!", "Message Box", MB_OK);

        // Return
        return 0;
    }
