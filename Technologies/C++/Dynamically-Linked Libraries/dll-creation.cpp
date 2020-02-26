/* Import */
#include <float.h> // Floating-Point --- NOTE (Lapys) -> Number-to-string conversion.
#include <math.h> // Mathematics
#include <wchar.h> // Wide Character --- NOTE (Lapys) -> `wchar_t` primitive character type.
#include <windows.h> // Windows
#include <type_traits> // Type Traits --- NOTE (Lapys) -> Standard template library type detection.

#include <iostream>

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
    template <typename type> // [Character]
    inline typename std::enable_if<(std::is_same<type, char>::value || std::is_same<type, const char>::value) || (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) || (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) || (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value), void>::type print(type message) noexcept {
        // Initialization > Screen Console Buffer ...
        HANDLE screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (INVALID_HANDLE_VALUE == screenConsoleBufferHandle) return;

        CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation {};
        ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);

        // ...
        put(message, screenConsoleBufferHandle, &screenConsoleBufferInformation.dwCursorPosition);
    }
    template <typename type> // [String]
    inline typename std::enable_if<(std::is_same<type, char>::value || std::is_same<type, const char>::value) || (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) || (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) || (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value), void>::type print(type message[]) noexcept {
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
    template <typename type> // [Pointer]
    inline typename std::enable_if<!((std::is_same<type, char>::value || std::is_same<type, const char>::value) || (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) || (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) || (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value)), void>::type
    print(type* message) noexcept {
        // Logic
        if (message) {
            // Initialization > String ...
            char string[2 + 64 + 1] {0}, stringDigit;
            unsigned char stringLength = 0u;

            // Update > String
            *string = '0';
            *(string + 1) = 'x';

            // Loop
            for (int iterator = (int) message; iterator; iterator /= 16) {
                // (Logic > )Update > String ...
                switch (iterator % 16) { case 0: stringDigit = '0'; break; case 1: stringDigit = '1'; break; case 2: stringDigit = '2'; break; case 3: stringDigit = '3'; break; case 4: stringDigit = '4'; break; case 5: stringDigit = '5'; break; case 6: stringDigit = '6'; break; case 7: stringDigit = '7'; break; case 8: stringDigit = '8'; break; case 9: stringDigit = '9'; break; case 10: stringDigit = 'A'; break; case 11: stringDigit = 'B'; break; case 12: stringDigit = 'C'; break; case 13: stringDigit = 'D'; break; case 14: stringDigit = 'E'; break; case 15: stringDigit = 'F'; break; }
                *(string + (2u + stringLength++)) = stringDigit;
            }

            // ... Update > String (Length)
            if (stringLength) while (stringLength % 8u) *(string + (2u + stringLength++)) = '0';
            else { *(string + 2) = '0'; *(string + 3) = '0'; *(string + 4) = '0'; *(string + 5) = '0'; *(string + 6) = '0'; *(string + 7) = '0'; *(string + 8) = '0'; *(string + 9) = '0'; }
            ++stringLength;

            // Loop
            for (char *stringIterator = string + 2; (string + stringLength) > stringIterator; (++stringIterator, --stringLength)) {
                // Update > String (Iterator)
                *stringIterator ^= *(string + stringLength);
                *(string + stringLength) ^= *stringIterator;
                *stringIterator ^= *(string + stringLength);
            }

            // ...
            print(string);
        }

        else
            // ...
            print("null");
    }
    template <typename type> // [Rational]
    inline typename std::enable_if<std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, long double>::value, void>::type print(type message) noexcept {
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
    template <typename type> // [Integer]
    inline typename std::enable_if<std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value || std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value, void>::type print(type message) noexcept {
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
    template <typename type, typename... types> // [Function Pointer/ Manipulator]
    inline void print(type (*message)(types...)) noexcept {
        // Logic
        if (message == (type (*)(types...)) println || message == (type (*)(types...)) printlnp) {
            // Initialization > Screen Console Buffer ...
            HANDLE screenConsoleBufferHandle = ::CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (INVALID_HANDLE_VALUE == screenConsoleBufferHandle) return;

            CONSOLE_SCREEN_BUFFER_INFO screenConsoleBufferInformation {};

            ::GetConsoleScreenBufferInfo(screenConsoleBufferHandle, &screenConsoleBufferInformation);
            ::SetConsoleCursorPosition(screenConsoleBufferHandle, {0, ++screenConsoleBufferInformation.dwCursorPosition.Y});
        }

        else
            // ...
            print("[function pointer]");
    }
    // template <size_t length, typename type>
    // inline typename std::enable_if<(std::is_same<type, char>::value || std::is_same<type, const char>::value) || (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) || (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) || (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value), void>::type
    // print(type (&)[length]) noexcept {/* print("[DEBUG]"); */}
    template <typename type> // [Array]
    inline typename std::enable_if<!((std::is_same<type, char>::value || std::is_same<type, const char>::value) || (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) || (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) || (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value)), void>::type
    print(type (&)[3]) noexcept {/* print("[array]"); */}

    template <typename type, typename... types> inline void print(type (*)(types..., ...)) noexcept { print("[function pointer]"); }
    template <typename type, typename... types> inline void print(type (&)(types...)) noexcept { print("[function]"); }
    template <typename type, typename... types> inline void print(type (&)(types..., ...)) noexcept { print("[function]"); }
    // template <typename type, typename... types> inline void print(type message, types... messages) noexcept { print(message); print(messages...); }
    // template <size_t count, typename... types> inline void println(types... messages) noexcept { print(messages...); for (size_t iterator = 0u; count ^ iterator; ++iterator) print(println<>); }
    // constexpr inline void printp(void) noexcept {}
    // template <typename type> inline typename std::enable_if<(std::is_same<type, char>::value || std::is_same<type, const char>::value) || (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) || (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) || (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value), void>::type printp(type message) noexcept {
    //     // Logic > ... --- MINIFY (Lapys)
    //     switch (message) {
    //         case '\0': print("'\\0'"); break; case '\1': print("'\\1'"); break; case '\2': print("'\\2'"); break; case '\3': print("'\\3'"); break; case '\4': print("'\\4'"); break; case '\5': print("'\\5'"); break; case '\6': print("'\\6'"); break; case '\16': print("'\\16'"); break; case '\17': print("'\\17'"); break; case '\20': print("'\\20'"); break; case '\21': print("'\\21'"); break; case '\22': print("'\\22'"); break; case '\23': print("'\\23'"); break; case '\24': print("'\\24'"); break; case '\25': print("'\\25'"); break; case '\26': print("'\\26'"); break; case '\27': print("'\\27'"); break;
    //         case '\a': print("'\\a'"); break; case '\b': print("'\\b'"); break; case '\f': print("'\\f'"); break; case '\n': print("'\\n'"); break; case '\r': print("'\\r'"); break; case '\t': print("'\\t'"); break; case '\v': print("'\\v'"); break;
    //         case '\u0018': print("'\\u0018'"); break; case '\u0019': print("'\\u0019'"); break; case '\u001A': print("'\\u001A'"); break; case '\u001B': print("'\\e'"); break; case '\u001C': print("'\\u001C'"); break; case '\u001D': print("'\\u001D'"); break; case '\u001E': print("'\\u001E'"); break; case '\u001F': print("'\\u001F'"); break; case '\u007F': print("'\\u007F'"); break;
    //         case '\'': print("'\\''"); break; case '\\': print("'\\\\'"); break;
    //         default: type string[4] {'\'', message, '\'', 0}; print(string); break;
    //     }
    // }
    // template <typename type> inline typename std::enable_if<(std::is_same<type, char>::value || std::is_same<type, const char>::value) || (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) || (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) || (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value), void>::type printp(type message[]) noexcept { print('"'); print(message); print('"'); }
    // template <typename type> inline typename std::enable_if<!((std::is_same<type, char>::value || std::is_same<type, const char>::value) || (std::is_same<type, signed char>::value || std::is_same<type, const signed char>::value) || (std::is_same<type, unsigned char>::value || std::is_same<type, const unsigned char>::value) || (std::is_same<type, wchar_t>::value || std::is_same<type, const wchar_t>::value)), void>::type printp(type* message) noexcept { print(message); }
    // template <typename type> inline typename std::enable_if<std::is_same<type, double>::value || std::is_same<type, float>::value || std::is_same<type, long double>::value, void>::type printp(type message) noexcept { print(message); }
    // template <typename type> inline typename std::enable_if<std::is_same<type, int>::value || std::is_same<type, long>::value || std::is_same<type, long long>::value || std::is_same<type, short>::value || std::is_same<type, unsigned int>::value || std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long long>::value || std::is_same<type, unsigned short>::value, void>::type printp(type message) noexcept { print(message); }
    // template <typename type, typename... types> inline void printp(type message, types... messages) noexcept { printp(message); printp(messages...); }
    // template <size_t count, typename... types> inline void printlnp(types... messages) noexcept { printp(messages...); for (size_t iterator = 0u; count ^ iterator; ++iterator) printp(printlnp<>); }

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
    // ::print(&a); std::endl(std::cout);
    ::print(b);
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
