/* Import */
    // C Mathematics
    #include <cmath>

    // Convert Code-Set Facet
    #include <codecvt>

    // Input-Output Stream
    #include <iostream>

    // Locale
    #include <locale>

/* Function */
    // Characteristics Length
    inline const unsigned short characteristicsLength(unsigned long long number) { unsigned short length = 0; while (number) { length += 1; number /= 10; } return length; }
    inline const unsigned short characteristicsLength(long long number) { if (number < 0 || number == -0.0) return characteristicsLength((unsigned long long) -number); else return characteristicsLength((unsigned long long) number); }
    const unsigned short characteristicsLength(long double number) { return characteristicsLength((long long) number); }
    const unsigned short characteristicsLength(double number) { return characteristicsLength((long double) number); }
    const unsigned short characteristicsLength(float number) { return characteristicsLength((long double) number); }
    const unsigned short characteristicsLength(int number) { return characteristicsLength((long long) number); }
    const unsigned short characteristicsLength(long number) { return characteristicsLength((long long) number); }
    const unsigned short characteristicsLength(short number) { return characteristicsLength((long long) number); }
    const unsigned short characteristicsLength(unsigned int number) { return characteristicsLength((unsigned long long) number); }
    const unsigned short characteristicsLength(unsigned long number) { return characteristicsLength((unsigned long long) number); }
    const unsigned short characteristicsLength(unsigned short number) { return characteristicsLength((unsigned long long) number); }

    // String Length
    template <typename type> inline unsigned long strlen(type string) { unsigned long iterator = 0; while (*(string + iterator) != '\0') iterator += 1; return iterator; }

    // Mantissa Length --- CHECKPOINT ---
    const unsigned short mantissaLength(long double arg) {
        // Initialization > (Integer, Length)
        unsigned long long integer = arg;
        unsigned short length = 0;

        // Loop > Update > (...)
        while (arg > integer && integer) { arg *= 10; integer = arg; length += 1; }

        // Return
        return length;
    }
    const unsigned short mantissaLength(double arg) { return mantissaLength((long double) arg); }
    const unsigned short mantissaLength(float arg) { return mantissaLength((long double) arg);}
    inline const unsigned short mantissaLength(int) { return 0; }
    inline const unsigned short mantissaLength(long) { return 0; }
    inline const unsigned short mantissaLength(long long) { return 0; }
    inline const unsigned short mantissaLength(short) { return 0; }
    inline const unsigned short mantissaLength(unsigned int) { return 0; }
    inline const unsigned short mantissaLength(unsigned long) { return 0; }
    inline const unsigned short mantissaLength(unsigned long long) { return 0; }
    inline const unsigned short mantissaLength(unsigned short) { return 0; }

    // To
        // Boolean --- CHECKPOINT ---
        bool toBoolean(void) {}

        // Character String --- CHECKPOINT ---
        char* toCharacterString(const char16_t* arg) { std::string string = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t>().to_bytes(arg); return (char*) string.c_str(); }
        char* toCharacterString(const char32_t* arg) { std::string string = std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(arg); return (char*) string.c_str(); }
        char* toCharacterString(unsigned long long arg) {
            // Initialization > (Length, Iterator, Digits, String)
            const unsigned short length = characteristicsLength(arg);
            unsigned short iterator = length;
            static constexpr const char digits[10] {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
            char* string = (char*) std::malloc(length * sizeof(char));

            // Loop > Update > (String, Argument)
            while (arg > 0 && iterator) { *(string + (iterator -= 1)) = *(digits + (arg % 10)); arg /= 10; }

            // Update > String
            *(string + length) = '\0';

            // Return
            return string;
        }
        char* toCharacterString(long double arg) {}
        char* toCharacterString(long long arg) {
            // Logic
            if (arg < 0 || arg == -0.0) {
                // Initialization > (Stream, Length, Iterator, String)
                char* stream = toCharacterString((unsigned long long) -arg);
                const unsigned long length = strlen(stream);
                unsigned long iterator = length;
                char* string = (char*) std::malloc((length + 1) * sizeof(char));

                // Loop > Update > String
                while (iterator) *(string + ((iterator -= 1) + 1)) = *(stream + iterator);

                // Deletion
                std::free(stream);

                // Update > String
                *string = '-';

                // Return
                return string;
            }

            else
                // Return
                return toCharacterString((unsigned long long) arg);
        }
        char* toCharacterString(double arg) { return toCharacterString((long double) arg); }
        char* toCharacterString(float arg) { return toCharacterString((long double) arg); }
        char* toCharacterString(int arg) { return toCharacterString((long long) arg); }
        char* toCharacterString(nullptr_t) { return char*(""); }
        char* toCharacterString(long arg) { return toCharacterString((long long) arg); }
        char* toCharacterString(short arg) { return toCharacterString((long long) arg); }
        char* toCharacterString(unsigned int arg) { return toCharacterString((unsigned long long) arg); }
        char* toCharacterString(unsigned long arg) { return toCharacterString((unsigned long long) arg); }
        char* toCharacterString(unsigned short arg) { return toCharacterString((unsigned long long) arg); }
        char* toCharacterString(const wchar_t* arg) {
            // Initialization > (Length, Iterator, String, Code Point)
            const unsigned long length = strlen(arg);
            unsigned long iterator = 0;
            char* string = (char*) std::malloc(length * sizeof(char));
            unsigned int codepoint = 0;

            // Loop
            while (*arg != L'\0') {
                // Logic
                if (*arg >= 0xD800 && *arg <= 0xDBFF)
                    // Update > Code Point
                    codepoint = ((*arg - 0xD800) << 10) + 0x10000;

                else {
                    // Logic > Update > Code Point
                    if (*arg >= 0xDC00 && *arg <= 0xDFFF) codepoint |= *arg - 0xDC00;
                    else codepoint = *arg;

                    if (codepoint <= 0x7F)
                        // Update > String
                        *(string + ((iterator += 1) - 1)) = (char) codepoint;

                    else if (codepoint <= 0x7FF) {
                        // Update > String
                        *(string + ((iterator += 1) - 1)) = (char) 0xC0 | ((codepoint >> 6) & 0x1F);
                        *(string + ((iterator += 1) - 1)) = (char) 0x80 | (codepoint & 0x3F);
                    }

                    else if (codepoint <= 0xFFFF) {
                        // Update > String
                        *(string + ((iterator += 1) - 1)) = (char) 0xE0 | ((codepoint >> 12) & 0x0F);
                        *(string + ((iterator += 1) - 1)) = (char) 0x80 | ((codepoint >> 6) & 0x3F);
                        *(string + ((iterator += 1) - 1)) = (char) 0x80 | (codepoint & 0x3F);
                    }

                    else {
                        // Update > String
                        *(string + ((iterator += 1) - 1)) = (char) 0xF0 | ((codepoint >> 18) & 0x07);
                        *(string + ((iterator += 1) - 1)) = (char) 0x80 | ((codepoint >> 12) & 0x3F);
                        *(string + ((iterator += 1) - 1)) = (char) 0x80 | ((codepoint >> 6) & 0x3F);
                        *(string + ((iterator += 1) - 1)) = (char) 0x80 | (codepoint & 0x3F);
                    }

                    // Update > Code Point
                    codepoint = 0;
                }

                // Update > Argument
                arg += 1;
            }

            // Update > String
            *(string + length) = '\0';

            // Return
            return string;
        }

        // Double --- CHECKPOINT ---
        double toDouble(void) {}

        // Float --- CHECKPOINT ---
        float toFloat(void) {}

        // Integer --- CHECKPOINT ---
        int toInteger(void) {}

        // Null Pointer Type --- CHECKPOINT ---
        nullptr_t toNullPointerType(void) {}

        // Long --- CHECKPOINT ---
        long toLong(void) {}

        // Long Double --- CHECKPOINT ---
        long double toLongDouble(void) {}

        // Long Long --- CHECKPOINT ---
        long long toLongLong(void) {}

        // Short --- CHECKPOINT ---
        short toShort(void) {}

        // Unsigned Integer --- CHECKPOINT ---
        unsigned int toUnsignedInteger(void) {}

        // Unsigned Long --- CHECKPOINT ---
        unsigned long toUnsignedLong(void) {}

        // Unsigned Long Long --- CHECKPOINT ---
        unsigned long long toUnsignedLongLong(void) {}

        // Unsigned Short --- CHECKPOINT ---
        unsigned short toUnsignedShort(void) {}

        // UTF-16 Character String --- CHECKPOINT ---
        char16_t* toUTF16CharacterString(const char* arg) {}
        char16_t* toUTF16CharacterString(const char32_t* arg) {}
        char16_t* toUTF16CharacterString(const wchar_t* arg) {}

        // UTF-32 Character String --- CHECKPOINT ---
        char32_t* toUTF32CharacterString(const char* arg) {}
        char32_t* toUTF32CharacterString(const char16_t* arg) {}
        char32_t* toUTF32CharacterString(const wchar_t* arg) {}

        // Void
        void toVoid(void) {}

        // Wide Character String --- CHECKPOINT ---
        wchar_t* toWideCharacterString(const char* arg) {
            // Initialization > (Length, Iterator, String, Code Point)
            const unsigned long length = strlen(arg);
            unsigned long iterator = 0, wchar_tLength = sizeof(wchar_t);
            wchar_t* string = (wchar_t*) std::malloc(length * wchar_tLength);
            unsigned int codepoint = 0;

            // Loop
            while (*arg != '\0') {
                // Initialization > Character
                unsigned char character = (unsigned char) *arg;

                // Logic > Update > Code Point
                if (character <= 0x7F) codepoint = character;
                else if (character <= 0xBF) codepoint = (codepoint << 6) | (character & 0x3F);
                else if (character <= 0xDF) codepoint = character & 0x1F;
                else if (character <= 0xEF) codepoint = character & 0x0F;
                else codepoint = character & 0x07;

                // Update > Argument
                arg += 1;

                // Logic
                if (((*arg & 0xC0) != 0x80) && (codepoint <= 0x10FFFF)) {
                    // Logic
                    if (wchar_tLength > 2)
                        // Update > String
                        *(string + ((iterator += 1) - 1)) = (wchar_t) codepoint;

                    else if (codepoint > 0xFFFF) {
                        // Update > String
                        *(string + ((iterator += 1) - 1)) = (wchar_t) 0xD800 + (codepoint >> 10);
                        *(string + ((iterator += 1) - 1)) = (wchar_t) 0xDC00 + (codepoint & 0x03FF);
                    }

                    else if (codepoint < 0xD800 || codepoint >= 0xE000)
                        // Update > String
                        *(string + ((iterator += 1) - 1)) = (wchar_t) codepoint;
                }
            }

            // Return
            return string;
        }
        wchar_t* toWideCharacterString(const char16_t* arg) {}
        wchar_t* toWideCharacterString(const char32_t* arg) {}

    /* Main */
    int main(int argc, char* argv[]) {
        // Initialization > Argument
        long double arg = 2.11;

        // Update > (C Standard Library > C Output)
        std::cout << "String: \"";
        std::wcout << mantissaLength(arg);
        std::cout << '"';

        // Return
        return 0;
    }
