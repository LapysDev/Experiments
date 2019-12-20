/* Import */
#include <fcntl.h> // Functional
#include <limits.h> // Limits
#include <math.h> // Mathematics
#include <stdlib.h> // Standard Library
#include <windows.h> // Windows

#include <iostream>

/* Global > (Application ..., ...) */
HANDLE applicationConsoleActiveScreenBufferHandle = NULL;
char *applicationName = NULL;
int applicationStatus = 0;

unsigned long windowPaintMessageInvocationCount = 0uL;

/* Function > Window Procedure */
LRESULT CALLBACK windowProcedure(HWND windowHandle, UINT message, WPARAM messageParameter, LPARAM additionalMessageParameter) {
    // Logic
    switch (message) {
        // [Window Manager ...]
        case WM_CLOSE: ::DestroyWindow(windowHandle); break;
        case WM_DESTROY: ::PostQuitMessage(0);break;
        case WM_PAINT: {
            // Update > Window Paint Message Invocation Count
            windowPaintMessageInvocationCount += 1uL;

            // ...
            {
                // Initialization > (Graphics Device Context, Paint Information)
                HDC graphicsDeviceContext;
                PAINTSTRUCT paintInformation;

                // Update > Graphics Device Context
                graphicsDeviceContext = ::BeginPaint(windowHandle, &paintInformation);

                // ...
                {
                    // Declaration
                        // Monitor (Handle, Information, ...)
                        HMONITOR monitorHandle;
                        MONITORINFO monitorInformation;
                        long /*monitorHeight, */monitorWidth;

                        // Output String, ...
                        const char outputString[33] {0}; // NOTE (Lapys) -> Allocated on the stack.
                        char *buffer = (char*) outputString;

                        // Window (Bounding Rectangle, ...)
                        RECT windowBoundingRectangle;
                        long windowHeight, windowWidth;

                    // Update
                        // Buffer
                        *buffer = '['; *(buffer + 1) = 'P'; *(buffer + 2) = 'A'; *(buffer + 3) = 'I'; *(buffer + 4) = 'N'; *(buffer + 5) = 'T'; *(buffer + 6) = 'I'; *(buffer + 7) = 'N'; *(buffer + 8) = 'G'; *(buffer + 9) = ']'; *(buffer + 10) = ' '; *(buffer + 11) = '(';

                        // Monitor ...
                        monitorHandle = ::MonitorFromWindow(windowHandle, MONITOR_DEFAULTTOPRIMARY);

                        monitorInformation.cbSize = sizeof(MONITORINFO);
                        ::GetMonitorInfo(monitorHandle, &monitorInformation);

                        /* monitorHeight = monitorInformation.rcMonitor.bottom - monitorInformation.rcMonitor.top; */
                        monitorWidth = monitorInformation.rcMonitor.right - monitorInformation.rcMonitor.left;

                        // Window ... --- NOTE (Lapys) -> Can also use the `GetClientRect` function to update the Window Bounding Rectangle.
                        ::GetWindowRect(windowHandle, &windowBoundingRectangle);
                        windowHeight = windowBoundingRectangle.bottom - windowBoundingRectangle.top;
                        windowWidth = windowBoundingRectangle.right - windowBoundingRectangle.left;

                    // Logic --- NOTE (Lapys) -> Emplace the numeric representation of Count into the Buffer as a string.
                    if (windowPaintMessageInvocationCount) {
                        // Initialization > Count
                        unsigned long count;

                        // (Loop > )Update > Buffer
                        buffer = buffer + (11 + 1);
                        for (count = windowPaintMessageInvocationCount; count; count /= 10uL) buffer += 1;

                        *buffer = ')';

                        for (count = windowPaintMessageInvocationCount; count; count /= 10uL) *(buffer -= 1) = ((char) (count % 10uL)) + 48;
                        buffer = buffer - (11 + 1);
                    } else { *(buffer + 12) = '0'; *(buffer + 13) = ')'; }

                    // ...
                    ::FillRect(graphicsDeviceContext, &paintInformation.rcPaint /* -> const RECT& -> windowBoundingRectangle */, (HBRUSH) ::CreateSolidBrush(RGB(0, 0, 33)));

                    /* [Sine Wave] ...
                            --- PARAMETER ---
                                angle -> In radians: Variable coordinate at which the sine wave should accept.
                                x -> Frequency of the sine wave.
                                y -> Plot-point of the sine wave.
                    */
                    for (double angle = 0.0, x = 0.0, y = 0.0; x < windowWidth; (angle += 5.0, x += (double) (3L * windowWidth) / monitorWidth /* --- NOTE (Lapys) -> Wave Frequency Length. */)) {
                        // Update > ...
                        y = (windowHeight / 10L /* --- NOTE (Lapys) -> Wave Height. */) * ::sin(angle * (M_PI / 180.0 /* --- NOTE (Lapys) -> Degrees to radians. */));
                        y = (windowHeight / 2L) - y; // NOTE (Lapys) -> Center the plot point.

                        // ... --- NOTE (Lapys) -> Pad the pixel to be .5 unit(s) wider.
                        ::SetPixel(graphicsDeviceContext, x, y, RGB(255, 255, 255));
                        ::SetPixel(graphicsDeviceContext, x, y + 1.0, RGB(127, 127, 127));
                        ::SetPixel(graphicsDeviceContext, x + 1.0, y, RGB(127, 127, 127));
                        ::SetPixel(graphicsDeviceContext, x + 1.0, y + 1.0, RGB(0, 0, 0));
                    }

                    // [Data] ...
                    {
                        // Initialization > Output String ...
                        char outputStringCharacter;
                        SIZE outputStringCharacterFontSize;
                        unsigned outputStringWidth = 0u;

                        // : ... --- NOTE (Lapys) -> Erase the former textual data via carriage returns.
                        // : Loop --- NOTE (Lapys) -> Draw the buffer character-by-character since the length is unknown.
                        ::WriteFile(applicationConsoleActiveScreenBufferHandle, "\r                    \r", 22u, NULL, NULL);
                        do {
                            // Update > Output String (Character, Character Font Size)
                            outputStringCharacter = *buffer;
                            ::GetTextExtentPoint32(graphicsDeviceContext, buffer, 1, &outputStringCharacterFontSize);

                            // : ... --- NOTE (Lapys) -> Draw the textual data onto the graphics device context.
                            // : ... --- NOTE (Lapys) -> Output the textual data to the standard output file stream.
                            ::TextOut(graphicsDeviceContext, 15 + (int) outputStringWidth, 10, &outputStringCharacter, 1);
                            ::WriteFile(applicationConsoleActiveScreenBufferHandle, &outputStringCharacter, 1u, NULL, NULL);

                            // Update > (Buffer, Output String Width)
                            buffer += 1;
                            outputStringWidth += outputStringCharacterFontSize.cx;
                        } while (*buffer ^ 0);
                    }
                }

                // Deletion
                ::EndPaint(windowHandle, &paintInformation);
            }
        } break;

        // [...]
        default: return ::DefWindowProc(windowHandle, message, messageParameter, additionalMessageParameter);
    }

    // Return
    return 0;
}

/* Main */
int WinMain(HINSTANCE handlerInstance, HINSTANCE /*previousHandlerInstance*/, LPSTR /*programInitiationCommandLine*/, int windowAppearance) {
    /* Update > Application ... */
    applicationConsoleActiveScreenBufferHandle = ::CreateFile("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, NULL);
    applicationName = (char*) "Introduction";
    applicationStatus = EXIT_SUCCESS; // NOTE (Lapys) -> No errors; Successful exit.

    // Declaration
        // Console Active Screen Buffer Handle
        const HANDLE consoleActiveScreenBufferHandle = applicationConsoleActiveScreenBufferHandle;

        // Window Class ...
        WNDCLASS windowClass {};
        const HINSTANCE& windowClassHandlerInstance = handlerInstance;
        const char windowClassName[] = "DEFAULT"; // WARN (Lapys) -> Must not be empty.

    // Update > (Console Active Screen Buffer Handle, ...)
    ::SetConsoleActiveScreenBuffer(consoleActiveScreenBufferHandle);
    ::SetConsoleTitle(applicationName);

    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);

    // Deletion
    ::ZeroMemory(&windowClass, sizeof(windowClass));

    // Modification > Window Class > ...
    windowClass.cbClsExtra = 0; // NOTE (Lapys) -> Extra bytes to allocate following the window class structure.
    windowClass.cbWndExtra = 0; // NOTE (Lapys) -> Extra bytes to allocate following the window instance.
    windowClass.hbrBackground = (HBRUSH) COLOR_WINDOW; // NOTE (Lapys) -> Window background color.
    windowClass.hCursor = (HCURSOR) ::LoadCursor(NULL, IDC_ARROW); // NOTE (Lapys) -> Window cursor.
    windowClass.hIcon = NULL; // NOTE (Lapys) -> Window favorite icon.
    windowClass.hInstance = windowClassHandlerInstance;
    windowClass.lpszClassName = windowClassName;
    windowClass.lpszMenuName = NULL; // NOTE (Lapys) -> Resource name of the window class menu.
    windowClass.lpfnWndProc = &windowProcedure; // NOTE (Lapys) -> Event loop or Message queue.
    windowClass.style = CS_HREDRAW | CS_VREDRAW; // NOTE (Lapys) -> Pre-defined look of window instances of the class.

    // [Initiate]
    {
        // [Begin] ...
        ::WriteFile(consoleActiveScreenBufferHandle, "[PROGRAM INITIATED]\n\r", 21uL, NULL, NULL);

        // Logic
        if (::RegisterClass(&windowClass)) {
            // Constant > Window Handle
            const HWND windowHandle = ::CreateWindowEx(0, windowClassName, applicationName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, handlerInstance, NULL);

            // Logic
            if (windowHandle) {
                // Initialization > Window Procedure Message
                MSG windowProcedureMessage {};

                // Update > Window Handle
                ::ShowWindow(windowHandle, windowAppearance);
                ::UpdateWindow(windowHandle);

                // Loop > Logic
                while (true)
                if (::GetMessage(&windowProcedureMessage, NULL, 0, 0)) {
                    // Logic > ...
                    if (windowProcedureMessage.message == WM_QUIT) break;
                    else {
                        // Update > Window Procedure Message
                        ::TranslateMessage(&windowProcedureMessage);
                        ::DispatchMessage(&windowProcedureMessage);
                    }
                } else break;

                // ...; Update > Application Status
                ::WriteFile(applicationConsoleActiveScreenBufferHandle, "\n", 1u, NULL, NULL);
                applicationStatus = windowProcedureMessage.wParam;
            } else { applicationStatus = EXIT_FAILURE; }

            // Deletion
            ::UnregisterClass(windowClassName, windowClassHandlerInstance);
        } else { applicationStatus = EXIT_FAILURE; }

        // [End] ...
        ::WriteFile(consoleActiveScreenBufferHandle, "[PROGRAM TERMINATED]\0", 21uL, NULL, NULL);
    }

    // [Terminate]
    {
        // Deletion
        ::CloseHandle(applicationConsoleActiveScreenBufferHandle);
    }

    // Return
    return applicationStatus;
}
