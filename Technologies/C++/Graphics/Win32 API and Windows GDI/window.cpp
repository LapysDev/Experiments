/* Definition --- NOTE (Lapys) -> Hopefully these are accurate. */
#define CHAR_MAX 255
#define NULL ((void*) 0)
#define STDOUT_FILENO 1

/* Import */
#include <math.h> // Mathematics --- NOTE (Lapys) -> For drawing the sine wave.
#include <unistd.h> // UNIX Standard --- NOTE (Lapys) -> For printing to the standard output file stream.
#include <windows.h> // Windows --- NOTE (Lapys) -> For creating the window (the data & graphical components are unnecessary).

/* Global > Count */
unsigned long COUNT = 0uL;

/* Function > Window ... */
LRESULT CALLBACK windowProcedure(HWND window, unsigned message, unsigned messageParameter, long additionalMessageParameter) {
    // Logic
    switch (message) {
        case WM_CLOSE: ::DestroyWindow(window); ::PostQuitMessage(0); break;
        case WM_DESTROY: ::PostQuitMessage(0); break;
        case WM_PAINT: {
            // Initialization > (Paint Information, Graphics Device Context)
            PAINTSTRUCT paintInformation;
            HDC graphicsDeviceContext = ::BeginPaint(window, &paintInformation);

            // ...
            {
                // Initialization > (..., Buffer)
                const char string[25] {0};
                char *buffer = (char*) string;

                // [Update > Buffer] ...
                {
                    // Update > Buffer
                    *buffer = '['; *(buffer + 1) = 'P'; *(buffer + 2) = 'A'; *(buffer + 3) = 'I'; *(buffer + 4) = 'N'; *(buffer + 5) = 'T'; *(buffer + 6) = 'I'; *(buffer + 7) = 'N'; *(buffer + 8) = 'G'; *(buffer + 9) = ']'; *(buffer + 10) = ' '; *(buffer + 11) = '(';

                    // Logic
                    if (COUNT) {
                        // Initialization > Count
                        unsigned long count;

                        // (Loop > )Update > Buffer --- NOTE (Lapys) -> Convert the digits of the count into characters and add them to the buffer.
                        buffer = buffer + (11 + 1);
                        for (count = COUNT; count; count /= 10uL) buffer += 1;
                        *buffer = ')';
                        for (count = COUNT; count; count /= 10uL) *(buffer -= 1) = unsigned(count % 10uL) + 48u;
                        buffer = buffer - (11 + 1);
                    } else { *(buffer + 12) = '0'; *(buffer + 13) = ')'; }
                }

                // [Draw] ...
                {
                    // Initialization > Window Bounding Rectangle --- NOTE (Lapys) -> Can also use the `GetClientRect` function.
                    RECT windowBoundingRectangle; ::GetWindowRect(window, &windowBoundingRectangle);

                    // Constant > Window (Height, Width)
                    const long windowHeight = windowBoundingRectangle.bottom - windowBoundingRectangle.top;
                    const long windowWidth = windowBoundingRectangle.right - windowBoundingRectangle.left;

                    // [Background] ...
                    {
                        // Initialization > Count
                        const unsigned long maxima = 255uL;
                        const unsigned long threshold = 85uL;
                        unsigned long count = COUNT; while (count > (threshold * 2)) count /= (threshold * 2);

                        // ... --- NOTE (Lapys) -> Fill a rectangular region the size of the window with a dynamically changing color based on the `COUNT` (number of times the window has been painted) variable.
                        ::FillRect(graphicsDeviceContext, &paintInformation.rcPaint /* -> const RECT */, (HBRUSH) ::CreateSolidBrush(RGB(0, 0, (count > threshold ? (threshold * 2) - count : count) * (maxima / threshold))));
                    }

                    /* [Sine Wave] ...
                            --- PARAMETER ---
                                angle -> In radians: Variable coordinate at which the sine wave should accept.
                                x -> Frequency of the sine wave.
                                y -> Plot-point of the sine wave.
                    */
                    for (double angle = 0.0, x = 0.0, y = 0.0; x < windowWidth; (angle += 5.0, x += 3.0)) {
                        // Constant > Color
                        const COLORREF color = RGB(255, 255, 255);

                        // Update > ...
                        y = 50.0 * ::sin(angle * (M_PI / 180.0 /* --- NOTE (Lapys) -> Degrees to radians. */));
                        y = (windowHeight / 2L) - y; // NOTE (Lapys) -> Center the plot point.

                        // ... --- NOTE (Lapys) -> Pad the pixel to be .5 unit(s) wider.
                        ::SetPixel(graphicsDeviceContext, x, y, color);
                        ::SetPixel(graphicsDeviceContext, x, y + 1.0, color);
                        ::SetPixel(graphicsDeviceContext, x + 1.0, y, color);
                        ::SetPixel(graphicsDeviceContext, x + 1.0, y + 1.0, color);
                    }

                    // [Data] ...
                    {
                        // Initialization > (Text Width, Window Font Size)
                        unsigned textWidth = 0u;
                        SIZE windowFontSize;

                        // : ... --- NOTE (Lapys) -> Erase the former textual data via carriage returns.
                        // : Loop --- NOTE (Lapys) -> Draw the buffer character-by-character since the length is unknown.
                        ::write(STDOUT_FILENO, "\r                    \r", 22u);
                        for (; *buffer; buffer += 1) {
                            // Update > Window Font Size
                            ::GetTextExtentPoint32(graphicsDeviceContext, buffer, 1, &windowFontSize);

                            // : ... --- NOTE (Lapys) -> Output the textual data to the standard output file stream.
                            // : ... --- NOTE (Lapys) -> Draw the textual onto the graphics device context.
                            ::write(STDOUT_FILENO, buffer, 1u);
                            ::TextOut(graphicsDeviceContext, 15 + (int) textWidth, 10, buffer, 1);

                            // Update > Text Width
                            textWidth += windowFontSize.cx;
                        }
                    }
                }

                // Update > Count
                COUNT += 1uL;
            }

            // [End] ...
            ::EndPaint(window, &paintInformation);
        } break;
        default: return ::DefWindowProc(window, message, messageParameter, additionalMessageParameter);
    }

    // Return
    return 0;
}

/* Main */
int WinMain(HINSTANCE handlerInstance, HINSTANCE previousHandlerInstance, LPSTR programInitiationCommandLine, int windowAppearance) {
    // [Begin] ...
    ::write(STDOUT_FILENO, "[PROGRAM INITIATED]\n", 20u);

    // Declaration > Window Class ...
    WNDCLASS windowClass {};

    const char windowClassName[] = "Window Class Name"; // WARN (Lapys) -> Must not be empty.
    HINSTANCE& windowHandlerInstance = handlerInstance;

    // Deletion
    ::ZeroMemory(&windowClass, sizeof(windowClass));

    // Modification > Window Class > ...
    windowClass.cbClsExtra = 0; // NOTE (Lapys) -> Extra bytes to allocate following the window class structure.
    windowClass.cbWndExtra = 0; // NOTE (Lapys) -> Extra bytes to allocate following the window instance.
    windowClass.hbrBackground = (HBRUSH) COLOR_WINDOW; // NOTE (Lapys) -> Window background color.
    windowClass.hCursor = (HCURSOR) ::LoadCursor(NULL, IDC_ARROW); // NOTE (Lapys) -> Window cursor.
    windowClass.hIcon = NULL; // NOTE (Lapys) -> Window favorite icon.
    windowClass.hInstance = windowHandlerInstance;
    windowClass.lpszClassName = windowClassName;
    windowClass.lpszMenuName = NULL; // NOTE (Lapys) -> Resource name of the window class menu.
    windowClass.lpfnWndProc = &windowProcedure; // NOTE (Lapys) -> Event loop or Message queue.
    windowClass.style = CS_HREDRAW | CS_VREDRAW; // NOTE (Lapys) -> Pre-defined look of window instances of the class.

    // Logic
    if (::RegisterClass(&windowClass)) {
        // Declaration > Window
        HWND window = ::CreateWindowEx(
            0, // NOTE (Lapys) -> Optional window styles.
            windowClassName,
            "Window Title", // NOTE (Lapys) -> Title of the window.
            WS_OVERLAPPEDWINDOW | WS_VISIBLE, // NOTE (Lapys) -> Non-optional window style.

            CW_USEDEFAULT, CW_USEDEFAULT, // NOTE (Lapys) -> Window width and height.
            CW_USEDEFAULT, CW_USEDEFAULT, // NOTE (Lapys) -> Window X and Y coordinate.

            NULL, // NOTE (Lapys) -> Parent window.
            NULL, // NOTE (Lapys) -> Window menu.
            handlerInstance,
            NULL // NOTE (Lapys) -> Additional application data.
        );

        // Logic
        if (window) {
            // Initialization > Window ...
            MSG windowProcedureMessage {};

            // ...
            ::ShowWindow(window, windowAppearance);
            ::UpdateWindow(window);

            // Loop --- NOTE (Lapys) -> Event loop.
            while (true) {
                // Logic --- WARN (Lapys) -> Using the `PeekMessage` function utilizes an entire core of CPU to asynchronously read messages faster than the `GetMessage` function.
                if (::GetMessage(&windowProcedureMessage, NULL, 0, 0/*, PM_REMOVE*/)) { // NOTE (Lapys) -> This value is only `-1` in exceptions.
                    // Logic
                    if (windowProcedureMessage.message == WM_QUIT) break;
                    else {
                        // ...
                        ::TranslateMessage(&windowProcedureMessage);
                        ::DispatchMessage(&windowProcedureMessage);

                        // ::sleep(1); // NOTE (Lapys) -> If the `PeekMessage` function is to be used, utilize a manual slowdown to allow other background processes to share CPU resources.
                    }
                }

                else
                    // ...
                    break;
            }
        }

        // Deletion
        ::UnregisterClass(windowClassName, windowHandlerInstance);
    }

    // [End] ...
    ::write(STDOUT_FILENO, "\n[PROGRAM TERMINATED]", 21u);

    // Return
    return 0;
}
