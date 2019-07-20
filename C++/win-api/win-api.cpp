/* Import */
#include "win-api.hpp" // Windows API

/* Utilization */
using namespace Lapys;

/* Functions > Main Event Loop */
LRESULT CALLBACK MainEventLoop(HWND HandlerWindow, unsigned int Message, WPARAM MessageInformation, LPARAM AdditionalMessageInformatio) {
    // Logic > ...
    switch (Message) {
        case Event::Window::Destroy: ::PostQuitMessage(0); return 0;
        default: return ::DefWindowProc(HandlerWindow, Message, MessageInformation, AdditionalMessageInformatio);
    }
}

/* Modification > Settings > Flush Output Buffer On Newline */
namespace Settings { bool flushOutputBufferOnNewline = true; }

/* Main */
int WINAPI WinMain(HINSTANCE HandlerInstance, HINSTANCE PreviousHandlerInstance, LPSTR ProgramInitiationCommandLine, int WindowAppearance) {
    // Print; ...
    Console::WriteLine("[PROGRAM INITIATED]");

    // Initialization > (Window) (Class, Message)
    HWND WINDOW;
    WNDCLASSEX WINDOW_CLASS = Data::CreateWindowClass("Generic Window Class", HandlerInstance, _STRICT = &MainEventLoop);
    MSG WINDOW_MESSAGE;

    // Update > (Window) (Class, Message)
    Data::RegisterWindowClass(WINDOW_CLASS);

    WINDOW = Graphics::SpawnWindow("Window", WINDOW_CLASS, HandlerInstance, 400, 500, 300, 300);
    ::ShowWindow(WINDOW, WindowAppearance);

    Data::RunMessageQueue(WINDOW_MESSAGE);

    // Print; Return --- NOTE (Lapys) -> The program executed successfully.
    Console::Write("[PROGRAM TERMINATED]");
    return 0;
}
