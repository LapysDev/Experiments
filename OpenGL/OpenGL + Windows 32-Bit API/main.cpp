/* Import */
#include "main.hpp" // Main
#include <windows.h> // Windows

/* Main */
BOOL WINAPI DllMain(HINSTANCE DLLHandlerInstance, DWORD forwardingReason, LPVOID reserved) { if (MainState::IS_INVOKED) return 0; else { MainState::IS_INVOKED = true; return Main(DLLHandlerInstance, forwardingReason, reserved, NULL); } }
int main(int argumentCount, char* argumentVector[]) { if (MainState::IS_INVOKED) return 0; else { MainState::IS_INVOKED = true; return Main(argumentCount, argumentVector, NULL); } }
int wmain(int argumentCount, wchar_t* argumentVector[]) { if (MainState::IS_INVOKED) return 0; else { MainState::IS_INVOKED = true; return Main(argumentCount, argumentVector, NULL); } }
int WINAPI WinMain(HINSTANCE handlerInstance, HINSTANCE previousHandlerInstance, LPSTR programInitiationCommandLine, int windowAppearance) { if (MainState::IS_INVOKED) return 0; else { MainState::IS_INVOKED = true; return Main(handlerInstance, previousHandlerInstance, programInitiationCommandLine, windowAppearance, NULL); } }
