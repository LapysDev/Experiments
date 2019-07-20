/* Import */
#include "direct-x.hpp" // Direct X

/* Utilization */
using namespace Lapys;

/* Global */
    // Direct 3D
    LPDIRECT3D9 DIRECT_3D;
    LPDIRECT3DDEVICE9 DIRECT_3D_DEVICE;

    // (Window) (Class, Message)
    HWND WINDOW;
    WNDCLASSEX WINDOW_CLASS;
    MSG WINDOW_MESSAGE;

/* Functions */
    /* Graphics > Render Frame */
    namespace Lapys { namespace Graphics { void RenderFrame() {
        // Direct 3D Device > ...
        DIRECT_3D_DEVICE -> Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0); // NOTE (Lapys) -> Clear the window to a deep blue.

        DIRECT_3D_DEVICE -> BeginScene(); // NOTE (Lapys) -> Lock memory for video processing; Ready to start rendering.
        DIRECT_3D_DEVICE -> EndScene(); // NOTE (Lapys) -> Unlock memory for video processing.

        DIRECT_3D_DEVICE -> Present(NULL, NULL, NULL, NULL); // NOTE (Lapys) -> Display the created frame.
    } } }

    /* Main Event Loop */
    LRESULT CALLBACK MainEventLoop(HWND HandlerWindow, unsigned int Message, WPARAM MessageInformation, LPARAM AdditionalMessageInformatio) {
        // Logic > ...
        switch (Message) {
            // [Destroy]
            case Event::Window::Destroy: ::PostQuitMessage(0); return 0;
            // default: Graphics::RenderFrame(); break;
        }

        // Return
        return ::DefWindowProc(HandlerWindow, Message, MessageInformation, AdditionalMessageInformatio);
    }

/* Phase */
    /* Initiate */
    const unsigned int Initiate(HINSTANCE HandlerInstance, HINSTANCE PreviousHandlerInstance, LPSTR ProgramInitiationCommandLine, int WindowAppearance) {
        // Update > Window (Class)
        WINDOW_CLASS = Data::CreateWindowClass("Generic Window Class", HandlerInstance, _STRICT = &MainEventLoop);
        Data::RegisterWindowClass(WINDOW_CLASS);

        WINDOW = Graphics::SpawnWindow("Window", WINDOW_CLASS, HandlerInstance, 400, 500, 300, 300);
        ::ShowWindow(WINDOW, WindowAppearance);

        // ...
        // Data::InitiateDirect3D(DIRECT_3D, DIRECT_3D_DEVICE, WINDOW);

        // Return
        return 0;
    }

    /* Reset */
    const unsigned int Reset(HINSTANCE HandlerInstance, HINSTANCE PreviousHandlerInstance, LPSTR ProgramInitiationCommandLine, int WindowAppearance) { return 0; }

    /* Update */
    const unsigned int Update(HINSTANCE HandlerInstance, HINSTANCE PreviousHandlerInstance, LPSTR ProgramInitiationCommandLine, int WindowAppearance) {
        // Loop
        Data::RunMessageQueue(WINDOW_MESSAGE);

        // Return
        return 0;
    }

    /* Terminate */
    const unsigned int Terminate(HINSTANCE HandlerInstance, HINSTANCE PreviousHandlerInstance, LPSTR ProgramInitiationCommandLine, int WindowAppearance) {
        // ...
        // Data::TerminateDirect3D(DIRECT_3D, DIRECT_3D_DEVICE);

        // Return
        return 0;
    }

/* Main */
int WINAPI WinMain(HINSTANCE HandlerInstance, HINSTANCE PreviousHandlerInstance, LPSTR ProgramInitiationCommandLine, int WindowAppearance) {
    // Print, ...
    Console::WriteLine("[PROGRAM INITIATED]");
        Initiate(HandlerInstance, PreviousHandlerInstance, ProgramInitiationCommandLine, WindowAppearance);
        Update(HandlerInstance, PreviousHandlerInstance, ProgramInitiationCommandLine, WindowAppearance);
        Terminate(HandlerInstance, PreviousHandlerInstance, ProgramInitiationCommandLine, WindowAppearance);
    Console::Write("[PROGRAM TERMINATED]");

    // Return
    return WINDOW_MESSAGE.wParam;
}
