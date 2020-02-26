/* Import */
#include <wchar.h> // Wide Character
#include <windows.h> // Windows

#include <stdio.h>
#include <iostream>
#include <type_traits> // Type Traits

/* Global > ... */
size_t value = 0u;

/* Function > ... */
    // [Arithmetic]
    template <typename type> inline typename std::enable_if<std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long double>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value || std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value, type>::type add(type numberA, type numberB) noexcept { return numberA + numberB; }
    template <typename type> inline typename std::enable_if<std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long double>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value || std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value, type>::type divide(type numberA, type numberB) noexcept { return numberA / numberB; }
    template <typename type> inline typename std::enable_if<std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long double>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value || std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value, type>::type modulo(type numberA, type numberB) noexcept { return numberA % numberB; }
    template <typename type> inline typename std::enable_if<std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long double>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value || std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value, type>::type multiply(type numberA, type numberB) noexcept { return numberA * numberB; }
    template <typename type> inline typename std::enable_if<std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long double>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value || std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value, type>::type subtract(type numberA, type numberB) noexcept { return numberA - numberB; }

    // [Console Input & Output]
    inline void clear(void) noexcept {
        // Initialization > Screen Console Buffer Handle
        HANDLE screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        // Logic
        if (INVALID_HANDLE_VALUE != screenConsoleBufferHandle) {
            // Initialization > Screen Console Buffer (Bytes Written, Handle, Information)
            DWORD screenConsoleBufferBytesWritten;
            CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation {};

            // ...
            ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);
            ::FillConsoleOutputCharacter(screenConsoleBufferHandle, ' ', screenConsoleBufferInformation.dwSize.X * screenConsoleBufferInformation.dwSize.Y, {0L, 0L}, &screenConsoleBufferBytesWritten);
            ::SetConsoleCursorPosition(screenConsoleBufferHandle, {0, 0});
        }
    }

    constexpr inline void print(void) noexcept {}
    template <typename type> inline typename std::enable_if<(std::is_same<type, char>::value || std::is_same<type, const char>::value) || (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) || (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) || (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value), void>::type print(type message) noexcept {
        // Initialization > Screen Console Buffer ...; ...
        HANDLE screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (INVALID_HANDLE_VALUE == screenConsoleBufferHandle) return;

        CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation {};

        // ...
        ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
        ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);

        put(message, screenConsoleBufferHandle, &screenConsoleBufferInformation.dwCursorPosition);

        ::SetConsoleCursorPosition(screenConsoleBufferHandle, screenConsoleBufferInformation.dwCursorPosition);
    }
    template <typename type> inline typename std::enable_if<(std::is_same<type, char>::value || std::is_same<type, const char>::value) || (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) || (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) || (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value), void>::type print(type message[]) noexcept {
        // Initialization > Screen Console Buffer ...; ...
        HANDLE screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (INVALID_HANDLE_VALUE == screenConsoleBufferHandle) return;

        CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation {};

        // (Loop > )...
        ::SetConsoleActiveScreenBuffer(screenConsoleBufferHandle);
        ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);

        while (*message && put(*(message++), screenConsoleBufferHandle, &screenConsoleBufferInformation.dwCursorPosition)) continue;

        ::SetConsoleCursorPosition(screenConsoleBufferHandle, screenConsoleBufferInformation.dwCursorPosition);
    }
    template <typename type> inline typename std::enable_if<std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, long double>::value, void>::type
    print(type message) noexcept { /* RATIONAL */ }
    template <typename type> inline typename std::enable_if<std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value || std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value, void>::type
    print(type message) noexcept { /* INTEGER */ }
    template <typename type, typename... types> inline void print(type message, types... messages) noexcept { print(message); print(messages...); }

    template <typename type> inline typename std::enable_if<(std::is_same<type, char>::value || std::is_same<type, const char>::value) || (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) || (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) || (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value), bool>::type
    put(type message, HANDLE consoleBufferHandle, COORD *coordinates) noexcept { // WARN (Lapys) -> Ignores the output and return values of the `WriteConsoleOutputCharacter` procedure.
        // Initialization > Console Buffer Bytes Written
        static DWORD consoleBufferBytesWritten;

        // Logic > ...
        switch (message) {
            case '\a': break;
            case '\b': --(coordinates -> X); break;
            case '\f': break;
            case '\n': ++(coordinates -> Y); break;
            case '\r': coordinates -> X = 0; break;
            case '\t': while (coordinates -> X % 4) ++(coordinates -> X); break;
            case '\v': while (coordinates -> Y % 4) ++(coordinates -> Y); break;
            default: {
                // Initialization > Console Buffer Write Procedure Evaluation
                // : Logic > Return
                BOOL consoleBufferWriteProcedureEvaluation = ::WriteConsoleOutputCharacter(consoleBufferHandle, &message, 1uL, *coordinates, &consoleBufferBytesWritten);
                if (1 != consoleBufferBytesWritten || false == consoleBufferWriteProcedureEvaluation) return false;
                else ++(coordinates -> X);
            } break;
        }

        // Return
        return true;
    }

    // [Miscellaneous]
    inline size_t count(void) noexcept { static size_t value = 0u; return value++; }
    inline size_t increment(void) noexcept { return value++; }

/* Main */
int main(void) {
    ::print("Hello, World!", '\n', "Lorem ipsum");

    // Return
    return 0;
}

// BOOL WINAPI DllMain(HINSTANCE DLLHandlerInstance, DWORD forwardingReason, LPVOID reserved) {
//     // Return
//     return true;
// }
