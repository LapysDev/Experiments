/* Import */
#include <stdio.h> // Standard Input-Output
#include <windows.h> // Windows

/* ... --- NOTE (Lapys) -> Fix console output on Windows operating system environments. */
#if _WINDOWS
if (::AttachConsole(ATTACH_PARENT_PROCESS)) { ::freopen("CONOUT$", "wb", stdout); ::freopen("CONOUT$", "wb", stderr); }
#endif

/* Main --- NOTE (Lapys) -> Works even if the standard streams are closed. */
int main(void) {
    // ... --- NOTE (Lapys) -> Close all the pre-defined C standard file streams (which are commonly used for console interactivity with a user).
    ::fclose(stderr); ::fclose(stdin); ::fclose(stdout);

    // Global > Console ...
    HANDLE consoleActiveScreenBuffer = ::CreateFile("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, NULL);
    HANDLE consoleInputBuffer = ::CreateFile("CONIN$", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);

    // Declaration > Console ...
    DWORD consoleInputBufferEventsReadCount;
    INPUT_RECORD consoleInputBufferInformation[1];

    // ... --- NOTE (Lapys) -> Just in case...
    ::SetConsoleActiveScreenBuffer(consoleActiveScreenBuffer);
    ::SetConsoleTitle("Interaction"); // NOTE (Lapys) -> Changes the console title temporarily.

    // ...
    {
        // Global > (Buffer, Character)
        char *buffer = (char*) std::malloc(1u); *buffer = '\0';
        char character;

        // Declaration > Buffer ...
        const unsigned bufferInputChunkSize = 20u; // NOTE (Lapys) -> Better to implement this multiplicatively, though.
        unsigned bufferLength = 0u, bufferSize = 1u;

        // Print; Loop; Print
        ::WriteFile(consoleActiveScreenBuffer, "Type anything: \"", 16uL, NULL, NULL);
        do {
            // Logic > Update > Buffer ... --- NOTE (Lapys) -> Allocate more space for the input buffer string.
            if (bufferLength == bufferSize) { bufferSize += bufferInputChunkSize; buffer = (char*) std::realloc(buffer, bufferSize * sizeof(char)); }

            // Logic --- NOTE (Lapys) -> Would have opted for the `ReadFile` function but it unilaterally echoes its output to the active console screen buffer.
            if (::ReadConsoleInput(consoleInputBuffer, consoleInputBufferInformation, 1uL, &consoleInputBufferEventsReadCount)) {
                // Constant > Console Input Buffer Data
                const INPUT_RECORD& consoleInputBufferData = *consoleInputBufferInformation;

                // Logic
                if (consoleInputBufferData.EventType == KEY_EVENT) {
                    // Constant > Console Input Buffer Key Event Record
                    const KEY_EVENT_RECORD& consoleInputBufferKeyEventRecord = consoleInputBufferData.Event.KeyEvent;

                    // Logic
                    if (consoleInputBufferKeyEventRecord.bKeyDown) {
                        // Update > Character
                        character = consoleInputBufferKeyEventRecord.uChar.AsciiChar;

                        // Logic > ... --- NOTE (Lapys) -> Manually echo the event record data.
                        switch (character) {
                            case '\b': bufferLength -= 1u; ::WriteFile(consoleActiveScreenBuffer, "\b \b", 3uL, NULL, NULL); break;
                            case '\0': break;
                            default: *(buffer + bufferLength) = character; bufferLength += 1u; ::WriteFile(consoleActiveScreenBuffer, "*", 1uL, NULL, NULL);
                        }
                    }
                }
            }
        } while (!(character == '\n' || character == '\r' || character == EOF));
        ::WriteFile(consoleActiveScreenBuffer, "\b\"\n", 3uL, NULL, NULL);

        // Print; Update > Buffer ...; Print
        ::WriteFile(consoleActiveScreenBuffer, "Received: \"", 11uL, NULL, NULL);
        buffer = (char*) std::realloc(buffer, bufferLength * sizeof(char)); *(buffer + (bufferLength - 1u)) = '\0';
        ::WriteFile(consoleActiveScreenBuffer, buffer, bufferLength - 1u, NULL, NULL);
        ::WriteFile(consoleActiveScreenBuffer, "\"", 1uL, NULL, NULL);
    }

    // Deletion
    ::CloseHandle(consoleActiveScreenBuffer);
    ::CloseHandle(consoleInputBuffer);

    // Return
    return 0;
}
