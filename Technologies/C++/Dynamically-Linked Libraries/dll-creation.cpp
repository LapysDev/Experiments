__declspec( dllexport ) int add2(int num){
   return num + 2;
}
gcc -shared -o mylib.dll funcs.c

/* Import */
    // [C Standard Library]
    #include <conio.h> // Console Input-Output
    #include <float.h> // Floating-Point --- NOTE (Lapys) -> Number-to-string conversion.
    #include <math.h> // Mathematics
    #include <wchar.h> // Wide Character --- NOTE (Lapys) -> `wchar_t` primitive character type.

    // [C++ Standard Library]
    #include <type_traits> // Type Traits --- WARN (Lapys) -> Only works with C++ 2011, ISO/IEC 14882:2011.

    // [Platform-Dependent]
    #include <unistd.h> // UNIX Standard Library

    #include <windows.h> // Windows

    // [...]
    #include <iostream>
    #include <stdlib.h>

/* Global > ... */
size_t value = 0u;

/* Declaration > ... */
template <size_t count = 1u, typename... types> void println(types...) noexcept;
template <size_t count = 1u, typename... types> void printlnp(types...) noexcept;

/* Function > ... */
    // [Arithmetic]
    template <typename type> inline typename std::enable_if<std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long double>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value || std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value, type>::type add(type numberA, type numberB) noexcept { return numberA + numberB; }
    template <typename type> inline typename std::enable_if<std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long double>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value || std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value, type>::type divide(type numberA, type numberB) noexcept { return numberA / numberB; }
    template <typename type> inline typename std::enable_if<std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long double>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value || std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value, type>::type modulo(type numberA, type numberB) noexcept { return numberA % numberB; }
    template <typename type> inline typename std::enable_if<std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long double>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value || std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value, type>::type multiply(type numberA, type numberB) noexcept { return numberA * numberB; }
    template <typename type> inline typename std::enable_if<std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long double>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value || std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value, type>::type subtract(type numberA, type numberB) noexcept { return numberA - numberB; }

    // [Console Input & Output]
    struct console {
        private:
        public:
            // [Constructor]
            console() {}

            /* Function */
                // Clear
                inline void clear(void) noexcept {
                    // Logic
                    #if defined(__ANDROID__) || defined(__gnu_linux__) || defined(linux) || defined(__linux) || defined(__linux__) // [Android/ Linux]
                        // ...
                        ::clrscr();

                    #elif defined(__TOS_WIN__) || defined(_WIN16) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__) // [Microsoft Windows]
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

                    #else
                        // (Loop > )...
                        for (unsigned char iterator = 0u; iterator ^ 100u; ++iterator) ::putchar('\n');
                        ::putchar('\r');
                    #endif
                }
    } console;
    using console::print;
    constexpr inline void print(void) noexcept {}
    template <typename type> // [Character]
    inline typename std::enable_if<(
        std::is_same<type, char>::value || std::is_same<type, signed char>::value || std::is_same<type, unsigned char>::value || std::is_same<type, wchar_t>::value
    ), void>::type print(type message) noexcept {
        // Logic
        #if defined(__ANDROID__) || defined(__gnu_linux__) || defined(linux) || defined(__linux) || defined(__linux__) // [Android/ Linux]
            // ...
            ::write(STDOUT_FILENO, &message, 1u);

        #elif defined(__TOS_WIN__) || defined(_WIN16) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__) // [Microsoft Windows]
            // Initialization > Screen Console Buffer ...
            HANDLE screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (INVALID_HANDLE_VALUE == screenConsoleBufferHandle) return;

            CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation {};
            ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);

            // ...
            put(message, screenConsoleBufferHandle, &screenConsoleBufferInformation.dwCursorPosition);

        #else
            // ...
            ::putchar(message);
        #endif
    }
    template <typename type> // [String]
    inline typename std::enable_if<std::is_pointer<type>::value && (
        (std::is_same<type, char*>::value || std::is_same<type, const char*>::value) ||
        (std::is_same<type, signed char*>::value || std::is_same<type, const signed char*>::value) ||
        (std::is_same<type, unsigned char*>::value || std::is_same<type, const unsigned char*>::value) ||
        (std::is_same<type, wchar_t*>::value || std::is_same<type, const wchar_t*>::value)
    ), void>::type print(type message) noexcept {
        // Logic
        if (message) {
            // Initialization > Screen Console Buffer ...
            HANDLE screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (INVALID_HANDLE_VALUE == screenConsoleBufferHandle) return;

            CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation {};
            ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);

            // Loop > ...
            while (*message && put(*(message++), screenConsoleBufferHandle, &screenConsoleBufferInformation.dwCursorPosition)) continue;
        }
    }
    // template <typename type> // [Pointer]
    // inline typename std::enable_if<!std::is_array<type>::value && std::is_pointer<type>::value && !(
    //     (std::is_same<type, char*>::value || std::is_same<type, const char*>::value) ||
    //     (std::is_same<type, signed char*>::value || std::is_same<type, const signed char*>::value) ||
    //     (std::is_same<type, unsigned char*>::value || std::is_same<type, const unsigned char*>::value) ||
    //     (std::is_same<type, wchar_t*>::value || std::is_same<type, const wchar_t*>::value)
    // ), void>::type print(type message) noexcept {
    //     // Logic
    //     if (message) {
    //         // Initialization > String ...
    //         char string[2 + 64 + 1] {0}, stringDigit;
    //         unsigned char stringLength = 0u;

    //         // Update > String
    //         *string = '0';
    //         *(string + 1) = 'x';

    //         // Loop
    //         for (int iterator = (int) message; iterator; iterator /= 16) {
    //             // (Logic > )Update > String ...
    //             switch (iterator % 16) { case 0: stringDigit = '0'; break; case 1: stringDigit = '1'; break; case 2: stringDigit = '2'; break; case 3: stringDigit = '3'; break; case 4: stringDigit = '4'; break; case 5: stringDigit = '5'; break; case 6: stringDigit = '6'; break; case 7: stringDigit = '7'; break; case 8: stringDigit = '8'; break; case 9: stringDigit = '9'; break; case 10: stringDigit = 'A'; break; case 11: stringDigit = 'B'; break; case 12: stringDigit = 'C'; break; case 13: stringDigit = 'D'; break; case 14: stringDigit = 'E'; break; case 15: stringDigit = 'F'; break; }
    //             *(string + (2u + stringLength++)) = stringDigit;
    //         }

    //         // ... Update > String (Length)
    //         if (stringLength) while (stringLength % 8u) *(string + (2u + stringLength++)) = '0';
    //         else { *(string + 2) = '0'; *(string + 3) = '0'; *(string + 4) = '0'; *(string + 5) = '0'; *(string + 6) = '0'; *(string + 7) = '0'; *(string + 8) = '0'; *(string + 9) = '0'; }
    //         ++stringLength;

    //         // Loop
    //         for (char *stringIterator = string + 2; (string + stringLength) > stringIterator; (++stringIterator, --stringLength)) {
    //             // Update > String (Iterator)
    //             *stringIterator ^= *(string + stringLength);
    //             *(string + stringLength) ^= *stringIterator;
    //             *stringIterator ^= *(string + stringLength);
    //         }

    //         // ...
    //         print(string);
    //     }

    //     else
    //         // ...
    //         print("null");
    // }
    template <typename type> // [Rational]
    inline typename std::enable_if<(
        std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, long double>::value
    ), void>::type print(type message) noexcept {
        // Logic
        if (message) {
            // Initialization > (Characteristics, Mantissa, String ...)
            type characteristics;
            type mantissa;
            char string[(std::is_same<type, double>::value ? DBL_DIG : (std::is_same<type, float>::value ? FLT_DIG : (std::is_same<type, long double>::value ? LDBL_DIG : 20))) + 1 + 1] {0}, stringDigit, *stringIterator = string;

            // Logic
            if (message != ::abs(message)) {
                // Update > (Message, String Iterator)
                message = -message;
                *(stringIterator++) = '-';
            }

            // Logic; Update > Mantissa
            #if defined(__cplusplus) && __cplusplus <= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
                // Logic > Update > Characteristics
                if (std::is_same<type, double>::value) characteristics = ::floor(message);
                else if (std::is_same<type, float>::value) characteristics = ::floorf(message);
                else if (std::is_same<type, long double>::value) characteristics = ::floorl(message);
            #else
                // Update > Characteristics
                characteristics = ::floor(message);
            #endif
            mantissa = message - characteristics;

            // Logic --- NOTE (Lapys) -> Parse the integer exponent of the message.
            if (characteristics) {
                // Update > Mantissa; Loop
                while (characteristics >= 1.0) {
                    // Logic > Update > Digit
                    if (std::is_same<type, double>::value) switch (((long) characteristics) % 10L) { case 0L: stringDigit = '0'; break; case 1L: stringDigit = '1'; break; case 2L: stringDigit = '2'; break; case 3L: stringDigit = '3'; break; case 4L: stringDigit = '4'; break; case 5L: stringDigit = '5'; break; case 6L: stringDigit = '6'; break; case 7L: stringDigit = '7'; break; case 8L: stringDigit = '8'; break; case 9L: stringDigit = '9'; break; }
                    else if (std::is_same<type, float>::value) switch (((int) characteristics) % 10) { case 0: stringDigit = '0'; break; case 1: stringDigit = '1'; break; case 2: stringDigit = '2'; break; case 3: stringDigit = '3'; break; case 4: stringDigit = '4'; break; case 5: stringDigit = '5'; break; case 6: stringDigit = '6'; break; case 7: stringDigit = '7'; break; case 8: stringDigit = '8'; break; case 9: stringDigit = '9'; break; }
                    else if (std::is_same<type, long double>::value) switch (((long long) characteristics) % 10LL) { case 0LL: stringDigit = '0'; break; case 1LL: stringDigit = '1'; break; case 2LL: stringDigit = '2'; break; case 3LL: stringDigit = '3'; break; case 4LL: stringDigit = '4'; break; case 5LL: stringDigit = '5'; break; case 6LL: stringDigit = '6'; break; case 7LL: stringDigit = '7'; break; case 8LL: stringDigit = '8'; break; case 9LL: stringDigit = '9'; break; }

                    // Update > (Characteristics, String Iterator)
                    characteristics /= 10.0;
                    *(stringIterator++) = stringDigit;
                }

                // Update > String Iterator; Loop --- NOTE (Lapys) -> Reverse the valid string content.
                --stringIterator;
                for (char *stringSubiterator = string + ('-' == *string); stringIterator > stringSubiterator; (--stringIterator, ++stringSubiterator)) {
                    // Update > String (Sub)Iterator --- NOTE (Lapys) -> Swap the end & start digits.
                    *stringSubiterator ^= *stringIterator;
                    *stringIterator ^= *stringSubiterator;
                    *stringSubiterator ^= *stringIterator;
                }
            }

            else {
                // Update > String ...
                *(0.0 == mantissa && '-' == *string ? string : stringIterator++) = '0';
            }

            // Logic --- NOTE (Lapys) -> Parse the fractional mantissa of the message.
            if (mantissa) {
                // (Loop > )Update > (Mantissa, String Iterator)
                mantissa *= 10.0;
                while (*stringIterator) { ++stringIterator; } *(stringIterator++) = '.';

                // Loop
                for (unsigned char mantissaHasValue = true, mantissaIterator = 0u, mantissaLength = (std::is_same<type, double>::value ? DBL_MANT_DIG : (std::is_same<type, float>::value ? FLT_MANT_DIG : (std::is_same<type, long double>::value ? LDBL_MANT_DIG : 20u))); mantissaHasValue && (mantissaIterator ^ mantissaLength); (mantissa *= 10.0, ++mantissaIterator)) {
                    // Logic
                    #if defined(__cplusplus) && __cplusplus <= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
                        // Logic > Update > Mantissa Has Value
                        if (std::is_same<type, double>::value) mantissaHasValue = mantissa != ::floor(mantissa);
                        else if (std::is_same<type, float>::value) mantissaHasValue = mantissa != ::floorf(mantissa);
                        else if (std::is_same<type, long double>::value) mantissaHasValue = mantissa != ::floorl(mantissa);
                    #else
                        // Update > Mantissa Has Value
                        mantissaHasValue = mantissa != ::floor(mantissa);
                    #endif

                    // Logic > Update > String Digit
                    // : Update > String Iterator
                    if (std::is_same<type, double>::value) switch (((long) mantissa) % 10L) { case 0L: stringDigit = '0'; break; case 1L: stringDigit = '1'; break; case 2L: stringDigit = '2'; break; case 3L: stringDigit = '3'; break; case 4L: stringDigit = '4'; break; case 5L: stringDigit = '5'; break; case 6L: stringDigit = '6'; break; case 7L: stringDigit = '7'; break; case 8L: stringDigit = '8'; break; case 9L: stringDigit = '9'; break; }
                    else if (std::is_same<type, float>::value) switch (((int) mantissa) % 10) { case 0: stringDigit = '0'; break; case 1: stringDigit = '1'; break; case 2: stringDigit = '2'; break; case 3: stringDigit = '3'; break; case 4: stringDigit = '4'; break; case 5: stringDigit = '5'; break; case 6: stringDigit = '6'; break; case 7: stringDigit = '7'; break; case 8: stringDigit = '8'; break; case 9: stringDigit = '9'; break; }
                    else if (std::is_same<type, long double>::value) switch (((long long) mantissa) % 10LL) { case 0LL: stringDigit = '0'; break; case 1LL: stringDigit = '1'; break; case 2LL: stringDigit = '2'; break; case 3LL: stringDigit = '3'; break; case 4LL: stringDigit = '4'; break; case 5LL: stringDigit = '5'; break; case 6LL: stringDigit = '6'; break; case 7LL: stringDigit = '7'; break; case 8LL: stringDigit = '8'; break; case 9LL: stringDigit = '9'; break; }

                    *(stringIterator++) = stringDigit;
                }
            }

            // ...
            print(string);
        }

        else
            // ...
            print('0');
    }
    template <typename type> // [Integral]
    inline typename std::enable_if<(
        (std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value) ||
        (std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value)
    ), void>::type print(type message) noexcept {
        // Logic
        if (message) {
            // Initialization > String ...
            char string[20 + 1] {0}, stringDigit, *stringIterator = string;

            // Logic
            if (message != ::abs(message)) {
                // Update > (Message, String Iterator)
                message = -message;
                *(stringIterator++) = '-';
            }

            // Loop
            for (; message; message /= 10) {
                // (Logic > )Update > String ...
                switch (message % 10) { case 0: stringDigit = '0'; break; case 1: stringDigit = '1'; break; case 2: stringDigit = '2'; break; case 3: stringDigit = '3'; break; case 4: stringDigit = '4'; break; case 5: stringDigit = '5'; break; case 6: stringDigit = '6'; break; case 7: stringDigit = '7'; break; case 8: stringDigit = '8'; break; case 9: stringDigit = '9'; break; }
                *(stringIterator++) = stringDigit;
            }

            // Update > String Iterator; Loop --- NOTE (Lapys) -> Reverse the valid string content.
            --stringIterator;
            for (char *stringSubiterator = string + ('-' == *string); stringIterator > stringSubiterator; (--stringIterator, ++stringSubiterator)) {
                // Update > String (Sub)Iterator --- NOTE (Lapys) -> Swap the end & start digits.
                *stringSubiterator ^= *stringIterator;
                *stringIterator ^= *stringSubiterator;
                *stringSubiterator ^= *stringIterator;
            }

            // ...
            print(string);
        }

        else
            // ...
            print('0');
    }
    template <size_t length, typename type> // [String Array]
    inline typename std::enable_if<(
        (std::is_same<type, char>::value || std::is_same<type, const char>::value) ||
        (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) ||
        (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) ||
        (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value)
    ), void>::type print(type (&message)[length]) noexcept { print((type*) message); }
    template <size_t length, typename type> // [Primitive Array]
    inline typename std::enable_if<(
        (std::is_same<type, double>::value || std::is_same<type, const double>::value) ||
        (std::is_same<type, float>::value || std::is_same<type, const float>::value) ||
        (std::is_same<type, int>::value || std::is_same<type, const int>::value) ||
        (std::is_same<type, long>::value || std::is_same<type, const long>::value) ||
        (std::is_same<type, long double>::value || std::is_same<type, const long double>::value) ||
        (std::is_same<type, long long>::value || std::is_same<type, const long long>::value) ||
        (std::is_same<type, short>::value || std::is_same<type, const short>::value) ||
        (std::is_same<type, unsigned int>::value || std::is_same<type, const unsigned int>::value) ||
        (std::is_same<type, unsigned long>::value || std::is_same<type, const unsigned long>::value) ||
        (std::is_same<type, unsigned long long>::value || std::is_same<type, const unsigned long long>::value) ||
        (std::is_same<type, unsigned short>::value || std::is_same<type, const unsigned short>::value)
    ), void>::type print(type (&message)[length]) noexcept { print('['); for (size_t iterator = 0u; iterator ^ length; ++iterator) { print(*(message + iterator)); } print(']'); }
    template <size_t length, typename type> // [Object Array]
    inline typename std::enable_if<!(
        (std::is_same<type, char>::value || std::is_same<type, const char>::value) ||
        (std::is_same<type, double>::value || std::is_same<type, const double>::value) ||
        (std::is_same<type, float>::value || std::is_same<type, const float>::value) ||
        (std::is_same<type, int>::value || std::is_same<type, const int>::value) ||
        (std::is_same<type, long>::value || std::is_same<type, const long>::value) ||
        (std::is_same<type, long double>::value || std::is_same<type, const long double>::value) ||
        (std::is_same<type, long long>::value || std::is_same<type, const long long>::value) ||
        (std::is_same<type, short>::value || std::is_same<type, const short>::value) ||
        (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) ||
        (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) ||
        (std::is_same<type, unsigned int>::value || std::is_same<type, const unsigned int>::value) ||
        (std::is_same<type, unsigned long>::value || std::is_same<type, const unsigned long>::value) ||
        (std::is_same<type, unsigned long long>::value || std::is_same<type, const unsigned long long>::value) ||
        (std::is_same<type, unsigned short>::value || std::is_same<type, const unsigned short>::value) ||
        (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value)
    ), void>::type print(type (&)[length]) noexcept { print("[array]"); }
    template <typename type, typename... types> // [Function Pointer/ Manipulator]
    inline void print(type (*message)(types...)) noexcept {
        // Logic
        if (message == (type (*)(types...)) println || message == (type (*)(types...)) printlnp) {
            // Logic
            #if defined(__ANDROID__) || defined(__gnu_linux__) || defined(linux) || defined(__linux) || defined(__linux__) // [Android/ Linux]
                // ...
                ::write(STDOUT_FILENO, "\n", 1u);

            #elif defined(__TOS_WIN__) || defined(_WIN16) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__) // [Microsoft Windows]
                // Initialization > Screen Console Buffer ...
                HANDLE screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                if (INVALID_HANDLE_VALUE == screenConsoleBufferHandle) return;

                CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation {};

                ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);
                ::SetConsoleCursorPosition(screenConsoleBufferHandle, {0, ++screenConsoleBufferInformation.dwCursorPosition.Y});

            #else
                // ...
                ::puts("");

            #endif
        }

        else
            // ...
            print("[function pointer]");
    }
    template <typename type, typename... types> inline void print(type message, types... messages) noexcept { print(message); print(messages...); }
    template <size_t count, typename... types> inline void println(types... messages) noexcept { print(messages...); for (size_t iterator = 0u; count ^ iterator; ++iterator) print(println<>); }

    template <size_t count, typename... types> void printlnp(types...) noexcept {}

    template <typename type> // WARN (Lapys) -> Ignores the output and return values of the `WriteConsoleOutputCharacter` procedure.
    inline typename std::enable_if<(std::is_same<type, char>::value || std::is_same<type, const char>::value) || (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) || (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) || (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value), bool>::type put(type message, HANDLE consoleBufferHandle, COORD *coordinates) noexcept {
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

        // ...; Return
        ::SetConsoleCursorPosition(consoleBufferHandle, *coordinates);
        return true;
    }

    // [Miscellaneous]
    inline size_t count(void) noexcept { static size_t value = 0u; return value++; }
    inline size_t increment(void) noexcept { return value++; }

class A  {};
/* Main */
int main(void) {
    A /*a, */b[3];
    // ::println("A: ", &a);
    ::print("B: ", b);
    // ::println("C: ", new A);
    // ::print("Hello, World!");
    // ::printlnp<2u>("Hello, World!", ::println<>, "Lorem ipsum");
    // ::println("Pointer: ", NULL);
    // ::print("Number: ", -M_PI);

    // Return
    return 0;
}

// BOOL WINAPI DllMain(HINSTANCE DLLHandlerInstance, DWORD forwardingReason, LPVOID reserved) {
//     // Return
//     return true;
// }
