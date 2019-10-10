/* Import */
#include <cstdio> // C Standard Input-Output --- NOTE (Lapys) -> For the `std::fflush` & `std::sprintf` function and `stdout` object. Unfortunately, the `stdio.h` library file does not suffice.
#include <iostream> // Input-Output Stream --- NOTE (Lapys) -> For the `std::basic_ostream<typename, typename>`, `std::ios_base`, `std::ios_base::fmtflags`, & `std::ostream` classes and `std::cout` & `std::ios::showbase` objects.
#include <math.h> // Mathematics --- NOTE (Lapys) -> For the `std::isnan` function.
#include <stdlib.h> // Standard Library --- NOTE (Lapys) -> For the `std::free` & `std::malloc` functions.
#include <unistd.h> // Unix Standard --- NOTE (Lapys) -> For the `::write` function. --- WARN (Lapys) -> Non standard to the C Standard Library.

/* Function */
    // Character String Length
    constexpr inline std::size_t characterStringLength(char characterString[]) { if (NULL == characterString) return 0; std::size_t length = 0; while (*(characterString + length) != '\0') length += 1; return length; }

    // Number Characteristics Length
    constexpr inline unsigned short numberCharacteristicsLength(unsigned long long number) { unsigned short length = 0; while (number) { length += 1; number /= 10; } return length; }

    // Number Mantissa Length
    constexpr inline unsigned short numberMantissaLength(long double number) {
        // Initialization > (Is (Safe, Signed), Integer, Length)
        bool isSafe = false; const bool isSigned = number < 0;
        long long integer = number; unsigned short length = 0;

        // Logic
        if (number != integer)
            // Loop > Update > (Number, Integer, Length) --- NOTE (Lapys) -> Alternatives to the 64-bit integer limits in hexadecimal.
            while (
                (isSafe = isSigned ? integer > -0x7FFFFFFFFFFFFFFF : integer < 0x8000000000000000) &&
                (isSigned ? number < integer : number > integer) &&
                (isSigned ? integer < 0 : integer > -1)
            ) { number *= 10; integer = number; length += 1; }

        // Return
        return length + isSafe;
    }

    // Signed Character String Length
    constexpr inline std::size_t signedCharacterStringLength(signed char signedCharacterString[]) { if (NULL == signedCharacterString) return 0; std::size_t length = 0; while (*(signedCharacterString + length) != '\0') length += 1; return length; }

    // Wide Character String Length
    constexpr inline std::size_t wideCharacterStringLength(wchar_t wideCharacterString[]) { if (NULL == wideCharacterString) return 0; std::size_t length = 0; while (*(wideCharacterString + length) != L'\0') length += 1; return length; }

    // To Character String
    constexpr inline char* toCharacterString(unsigned long long arg);
    constexpr inline char* toCharacterString(unsigned char arg) {switch(arg){case 0:return(char*)"0";case 1:return(char*)"1";case 2:return(char*)"2";case 3:return(char*)"3";case 4:return(char*)"4";case 5:return(char*)"5";case 6:return(char*)"6";case 7:return(char*)"7";case 8:return(char*)"8";case 9:return(char*)"9";case 10:return(char*)"10";case 11:return(char*)"11";case 12:return(char*)"12";case 13:return(char*)"13";case 14:return(char*)"14";case 15:return(char*)"15";case 16:return(char*)"16";case 17:return(char*)"17";case 18:return(char*)"18";case 19:return(char*)"19";case 20:return(char*)"20";case 21:return(char*)"21";case 22:return(char*)"22";case 23:return(char*)"23";case 24:return(char*)"24";case 25:return(char*)"25";case 26:return(char*)"26";case 27:return(char*)"27";case 28:return(char*)"28";case 29:return(char*)"29";case 30:return(char*)"30";case 31:return(char*)"31";case 32:return(char*)"32";case 33:return(char*)"33";case 34:return(char*)"34";case 35:return(char*)"35";case 36:return(char*)"36";case 37:return(char*)"37";case 38:return(char*)"38";case 39:return(char*)"39";case 40:return(char*)"40";case 41:return(char*)"41";case 42:return(char*)"42";case 43:return(char*)"43";case 44:return(char*)"44";case 45:return(char*)"45";case 46:return(char*)"46";case 47:return(char*)"47";case 48:return(char*)"48";case 49:return(char*)"49";case 50:return(char*)"50";case 51:return(char*)"51";case 52:return(char*)"52";case 53:return(char*)"53";case 54:return(char*)"54";case 55:return(char*)"55";case 56:return(char*)"56";case 57:return(char*)"57";case 58:return(char*)"58";case 59:return(char*)"59";case 60:return(char*)"60";case 61:return(char*)"61";case 62:return(char*)"62";case 63:return(char*)"63";case 64:return(char*)"64";case 65:return(char*)"65";case 66:return(char*)"66";case 67:return(char*)"67";case 68:return(char*)"68";case 69:return(char*)"69";case 70:return(char*)"70";case 71:return(char*)"71";case 72:return(char*)"72";case 73:return(char*)"73";case 74:return(char*)"74";case 75:return(char*)"75";case 76:return(char*)"76";case 77:return(char*)"77";case 78:return(char*)"78";case 79:return(char*)"79";case 80:return(char*)"80";case 81:return(char*)"81";case 82:return(char*)"82";case 83:return(char*)"83";case 84:return(char*)"84";case 85:return(char*)"85";case 86:return(char*)"86";case 87:return(char*)"87";case 88:return(char*)"88";case 89:return(char*)"89";case 90:return(char*)"90";case 91:return(char*)"91";case 92:return(char*)"92";case 93:return(char*)"93";case 94:return(char*)"94";case 95:return(char*)"95";case 96:return(char*)"96";case 97:return(char*)"97";case 98:return(char*)"98";case 99:return(char*)"99";case 100:return(char*)"100";case 101:return(char*)"101";case 102:return(char*)"102";case 103:return(char*)"103";case 104:return(char*)"104";case 105:return(char*)"105";case 106:return(char*)"106";case 107:return(char*)"107";case 108:return(char*)"108";case 109:return(char*)"109";case 110:return(char*)"110";case 111:return(char*)"111";case 112:return(char*)"112";case 113:return(char*)"113";case 114:return(char*)"114";case 115:return(char*)"115";case 116:return(char*)"116";case 117:return(char*)"117";case 118:return(char*)"118";case 119:return(char*)"119";case 120:return(char*)"120";case 121:return(char*)"121";case 122:return(char*)"122";case 123:return(char*)"123";case 124:return(char*)"124";case 125:return(char*)"125";case 126:return(char*)"126";case 127:return(char*)"127";case 128:return(char*)"128";case 129:return(char*)"129";case 130:return(char*)"130";case 131:return(char*)"131";case 132:return(char*)"132";case 133:return(char*)"133";case 134:return(char*)"134";case 135:return(char*)"135";case 136:return(char*)"136";case 137:return(char*)"137";case 138:return(char*)"138";case 139:return(char*)"139";case 140:return(char*)"140";case 141:return(char*)"141";case 142:return(char*)"142";case 143:return(char*)"143";case 144:return(char*)"144";case 145:return(char*)"145";case 146:return(char*)"146";case 147:return(char*)"147";case 148:return(char*)"148";case 149:return(char*)"149";case 150:return(char*)"150";case 151:return(char*)"151";case 152:return(char*)"152";case 153:return(char*)"153";case 154:return(char*)"154";case 155:return(char*)"155";case 156:return(char*)"156";case 157:return(char*)"157";case 158:return(char*)"158";case 159:return(char*)"159";case 160:return(char*)"160";case 161:return(char*)"161";case 162:return(char*)"162";case 163:return(char*)"163";case 164:return(char*)"164";case 165:return(char*)"165";case 166:return(char*)"166";case 167:return(char*)"167";case 168:return(char*)"168";case 169:return(char*)"169";case 170:return(char*)"170";case 171:return(char*)"171";case 172:return(char*)"172";case 173:return(char*)"173";case 174:return(char*)"174";case 175:return(char*)"175";case 176:return(char*)"176";case 177:return(char*)"177";case 178:return(char*)"178";case 179:return(char*)"179";case 180:return(char*)"180";case 181:return(char*)"181";case 182:return(char*)"182";case 183:return(char*)"183";case 184:return(char*)"184";case 185:return(char*)"185";case 186:return(char*)"186";case 187:return(char*)"187";case 188:return(char*)"188";case 189:return(char*)"189";case 190:return(char*)"190";case 191:return(char*)"191";case 192:return(char*)"192";case 193:return(char*)"193";case 194:return(char*)"194";case 195:return(char*)"195";case 196:return(char*)"196";case 197:return(char*)"197";case 198:return(char*)"198";case 199:return(char*)"199";case 200:return(char*)"200";case 201:return(char*)"201";case 202:return(char*)"202";case 203:return(char*)"203";case 204:return(char*)"204";case 205:return(char*)"205";case 206:return(char*)"206";case 207:return(char*)"207";case 208:return(char*)"208";case 209:return(char*)"209";case 210:return(char*)"210";case 211:return(char*)"211";case 212:return(char*)"212";case 213:return(char*)"213";case 214:return(char*)"214";case 215:return(char*)"215";case 216:return(char*)"216";case 217:return(char*)"217";case 218:return(char*)"218";case 219:return(char*)"219";case 220:return(char*)"220";case 221:return(char*)"221";case 222:return(char*)"222";case 223:return(char*)"223";case 224:return(char*)"224";case 225:return(char*)"225";case 226:return(char*)"226";case 227:return(char*)"227";case 228:return(char*)"228";case 229:return(char*)"229";case 230:return(char*)"230";case 231:return(char*)"231";case 232:return(char*)"232";case 233:return(char*)"233";case 234:return(char*)"234";case 235:return(char*)"235";case 236:return(char*)"236";case 237:return(char*)"237";case 238:return(char*)"238";case 239:return(char*)"239";case 240:return(char*)"240";case 241:return(char*)"241";case 242:return(char*)"242";case 243:return(char*)"243";case 244:return(char*)"244";case 245:return(char*)"245";case 246:return(char*)"246";case 247:return(char*)"247";case 248:return(char*)"248";case 249:return(char*)"249";case 250:return(char*)"250";case 251:return(char*)"251";case 252:return(char*)"252";case 253:return(char*)"253";case 254:return(char*)"254";case 255:return(char*)"255";default:return(char*)toCharacterString((unsigned long long)arg);}}
    constexpr inline char* toCharacterString(unsigned long long arg, bool isSigned) {
        // Logic > Return
        if (arg < 256) return toCharacterString((unsigned char) arg);

        // Initialization > (Iterator, Digits, Character String)
        unsigned short iterator = numberCharacteristicsLength(arg);
        constexpr const char digits[10] {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char* characterString = (char*) std::malloc(iterator);

        // (Loop > )Update > Character String
        isSigned && (*characterString = '-');
        *(characterString + isSigned + iterator) = '\0';
        while (arg > 0 && iterator) { *(characterString + isSigned + (iterator -= 1)) = *(digits + (arg % 10)); arg /= 10; }

        // Return
        return characterString;
    }
    constexpr inline char* toCharacterString(unsigned long long arg) { return toCharacterString(arg, false); }
    constexpr char* toCharacterString(long long arg) { const bool isSigned = arg < 0; return toCharacterString((unsigned long long) (isSigned ? -arg :arg), isSigned); }
    constexpr inline char* toCharacterString(long double arg) {
        // Initialization > (Argument Characteristics (Has Memory on Heap), Iterator, Length, Index, Character String)
        char* argCharacteristics = toCharacterString((long long) arg);
        const bool argCharacteristicsHasMemoryOnHeap = arg > 255;
        std::size_t iterator = characterStringLength(argCharacteristics);
        const std::size_t length = iterator + numberMantissaLength(arg);
        std::size_t index = length;
        char* characterString = (char*) std::malloc(length);

        /* Loop > Update > Character String
                --- NOTE (Lapys) -> Get all mantissa digits of the Argument.
                --- WARN (Lapys) -> Data can overflow past the Character String Length boundary here.
        */
        while (index) *(characterString + ((length - (index -= 1)) + iterator)) = *toCharacterString((unsigned long long) (arg *= 10) % 10);

        // Loop > Update > (Iterator, Character); Update > Character String
        *(characterString + iterator) = '.';
        while (iterator) { iterator -= 1; *(characterString + iterator) = *(argCharacteristics + iterator); }
        *(characterString + length) = '\0';

        // Logic > Deletion
        if (argCharacteristicsHasMemoryOnHeap) std::free(argCharacteristics);

        // Return
        return characterString;
    }
    inline char* toCharacterString(wchar_t* arg) {
        // Initialization > (Character String, Code Point, Iterator)
        char* characterString = (char*) std::malloc(wideCharacterStringLength(arg));
        unsigned codePoint = 0;
        std::size_t iterator = 0;

        // Loop
        while (*arg) {
            // Logic
            if (*arg > 0xD800 - 1 && *arg < 0xDBFF + 1)
                // Update > Code Point
                codePoint = ((*arg - 0xD800) << 10) + 0x10000;

            else {
                // Update > Code Point
                codePoint = *arg > 0xDC00 - 1 && *arg < 0xDFFF + 1 ? codePoint | *arg - 0xDC00 : *arg;

                // Logic > Update > (Code Point, Iterator) --- NOTE (Lapys) -> Append the newly transformed code points to the Character String.
                if (codePoint < 0x7F + 1) { *(characterString + iterator) = (char) codePoint; iterator += 1; }
                else if (codePoint < 0x7FF + 1) {
                    *(characterString + iterator) = (char) (0xC0 | ((codePoint >> 6) & 0x1F)); iterator += 1;
                    *(characterString + iterator) = (char) (0x80 | (codePoint & 0x3F)); iterator += 1;
                }
                else if (codePoint < 0xFFFF + 1) {
                    *(characterString + iterator) = (char) (0xE0 | ((codePoint >> 12) & 0x0F)); iterator += 1;
                    *(characterString + iterator) = (char) (0x80 | ((codePoint >> 6) & 0x3F)); iterator += 1;
                    *(characterString + iterator) = (char) (0x80 | (codePoint & 0x3F)); iterator += 1;
                }
                else {
                    *(characterString + iterator) = (char) (0xF0 | ((codePoint >> 18) & 0x07)); iterator += 1;
                    *(characterString + iterator) = (char) (0x80 | ((codePoint >> 12) & 0x3F)); iterator += 1;
                    *(characterString + iterator) = (char) (0x80 | ((codePoint >> 6) & 0x3F)); iterator += 1;
                    *(characterString + iterator) = (char) (0x80 | (codePoint & 0x3F)); iterator += 1;
                }

                // Update > Code Point
                codePoint = 0;
            }

            // Update > Argument
            arg += 1;
        }

        // Return
        return characterString;
    }

    // UTF-32 Character String Length
    constexpr inline std::size_t utf32CharacterStringLength(char32_t utf32CharacterString[]) { if (NULL == utf32CharacterString) return 0; std::size_t length = 0; while (*(utf32CharacterString + length) != U'\0') length += 1; return length; }

    // To Wide Character String --- MINIFY --- NOTE (Lapys) -> Convert each UTF-32 character to a wider format rather than statically cast the Argument.
    constexpr inline wchar_t* toWideCharacterString(char32_t arg[]) { std::size_t iterator = utf32CharacterStringLength(arg); wchar_t* string = (wchar_t*) std::malloc(iterator * sizeof(wchar_t)); while (iterator) { iterator -= 1; *(string + iterator) = (wchar_t) *(arg + iterator); } return string; }

    // Unsigned Character String Length
    constexpr inline std::size_t unsignedCharacterStringLength(unsigned char unsignedCharacterString[]) { if (NULL == unsignedCharacterString) return 0; std::size_t length = 0; while (*(unsignedCharacterString + length) != '\0') length += 1; return length; }

    // UTF-16 Character String Length
    constexpr inline std::size_t utf16CharacterStringLength(char16_t utf16CharacterString[]) { if (NULL == utf16CharacterString) return 0; std::size_t length = 0; while (*(utf16CharacterString + length) != u'\0') length += 1; return length; }

    /* Flush */
    inline static void flush() { std::fflush(stdout); }

    /* Print
            --- NOTE (Lapys) -> Will execute manipulators.
            --- WARN (Lapys) -> "Unpredictable" behavior of non-referenced pointers (i.e. in use-cases like `void ::print(NULL)` and `void ::print(std::string().c_str())`).
    */
        // []
        inline static void print() { flush(); }

        // [[Output Stream] Manipulators]
        constexpr inline void print(std::ios_base& (&argA)(std::ios_base&), std::ostream& argB = std::cout) { argA(argB); }
        constexpr inline void print(std::ostream& (&argA)(std::ostream&), std::ostream& argB = std::cout) { argA(argB); }
        template <typename type> constexpr inline void print(type (&argA)(int), std::ostream& argB = std::cout, int argC = int()) { argB << argA(argC); }
        template <typename type> constexpr inline void print(type (&argA)(std::ios_base::fmtflags), std::ostream& argB = std::cout, std::ios_base::fmtflags argC = std::ios::showbase) { argB << argA(argC); }
        template <typename characterType, typename traits> constexpr inline void print(std::basic_ostream<characterType, traits>& (&argA)(std::basic_ostream<characterType, traits>&), std::ostream& argB = std::cout) { argA(argB); }
        template <typename characterType, typename type> constexpr inline void print(type (&argA)(characterType), std::ostream& argB = std::cout, characterType argC = characterType()) { argB << argA(argC); }

        // [Pointers]
        inline void print(const void* arg) {
            if (NULL == arg)
                ::write(STDOUT_FILENO, "null", 4);

            else {
                bool isNullLike = true; char pointerString[8];
                std::sprintf(pointerString, "%p", arg);
                unsigned char iterator = 8;
                while (iterator) {
                    iterator -= 1;
                    if (*(pointerString + iterator) != '0') {
                        isNullLike = false;
                        iterator = 0;
                        break;
                    }
                }

                if (isNullLike)
                    ::write(STDOUT_FILENO, "null", 4);

                else {
                    ::write(STDOUT_FILENO, "0x", 2);
                    do {
                        iterator += 1;
                        switch (*pointerString) {
                            case '0': ::write(STDOUT_FILENO, "0", 1); break;
                            case '1': ::write(STDOUT_FILENO, "1", 1); break; case '2': ::write(STDOUT_FILENO, "2", 1); break; case '3': ::write(STDOUT_FILENO, "3", 1); break;
                            case '4': ::write(STDOUT_FILENO, "4", 1); break; case '5': ::write(STDOUT_FILENO, "5", 1); break; case '6': ::write(STDOUT_FILENO, "6", 1); break;
                            case '7': ::write(STDOUT_FILENO, "7", 1); break; case '8': ::write(STDOUT_FILENO, "8", 1); break; case '9': ::write(STDOUT_FILENO, "9", 1); break;
                            case 'a': case 'A': ::write(STDOUT_FILENO, "A", 1); break;
                            case 'b': case 'B': ::write(STDOUT_FILENO, "B", 1); break;
                            case 'c': case 'C': ::write(STDOUT_FILENO, "C", 1); break;
                            case 'd': case 'D': ::write(STDOUT_FILENO, "D", 1); break;
                            case 'e': case 'E': ::write(STDOUT_FILENO, "E", 1); break;
                            case 'f': case 'F': ::write(STDOUT_FILENO, "F", 1);
                        }
                    } while (*pointerString = *(pointerString + iterator));
                }
            }
        }

        // [Character String Literals]
        inline void print(char*& arg) { NULL == arg ? ::write(STDOUT_FILENO, "null", 4) : ::write(STDOUT_FILENO, (const char*) arg, characterStringLength(arg)); }
        inline void print(const char arg) { if (NULL == (void*) (int) arg) ::write(STDOUT_FILENO, "null", 4); else { if (arg == '\0') ::write(STDOUT_FILENO, "\\0", 2); else { if (arg == '\n') flush(); const char characterString[2] {arg, '\0'}; ::write(STDOUT_FILENO, characterString, 1); } } }
        inline void print(const char*& arg) { NULL == arg ? ::write(STDOUT_FILENO, "null", 4) : ::write(STDOUT_FILENO, arg, characterStringLength((char*) arg)); }

        void print(wchar_t*& arg) { if (NULL == arg) ::write(STDOUT_FILENO, "null", 4); else { char* characterString = toCharacterString(arg); print((char*&) characterString); std::free(characterString); } }
        void print(const wchar_t arg) { if (NULL == (void*) (int) arg) ::write(STDOUT_FILENO, "null", 4); else { wchar_t wideCharacterString[2] = {arg, L'\0'}; char* characterString = toCharacterString(wideCharacterString); print(*characterString); std::free(characterString); } }
        void print(const wchar_t*& arg) { if (NULL == arg) ::write(STDOUT_FILENO, "null", 4); else { char* characterString = toCharacterString((wchar_t*) arg); print((const char*&) characterString); std::free(characterString); } }

        void print(char16_t*& arg) { if (NULL == arg) ::write(STDOUT_FILENO, "null", 4); else print((wchar_t*&) arg); }
        void print(const char16_t arg) { if (NULL == (void*) (int) arg) ::write(STDOUT_FILENO, "null", 4); else print((const wchar_t) arg); }
        void print(const char16_t*& arg) { if (NULL == arg) ::write(STDOUT_FILENO, "null", 4); else print((const wchar_t*&) arg); }

        void print(char32_t*& arg) { if (NULL == arg) ::write(STDOUT_FILENO, "null", 4); else { wchar_t* wideCharacterString = toWideCharacterString(arg); print((wchar_t*&) wideCharacterString); std::free(wideCharacterString); } }
        void print(const char32_t arg) { if (NULL == (void*) arg) ::write(STDOUT_FILENO, "null", 4); else print((const wchar_t) arg); }
        void print(const char32_t*& arg) { if (NULL == arg) ::write(STDOUT_FILENO, "null", 4); else { wchar_t* wideCharacterString = toWideCharacterString((char32_t*) arg); print((const wchar_t*&) wideCharacterString); std::free(wideCharacterString); } }

        void print(signed char*& arg) { if (NULL == arg) ::write(STDOUT_FILENO, "null", 4); else print((char*&) arg); }
        void print(const signed char arg) { if (NULL == (void*) (int) arg) ::write(STDOUT_FILENO, "null", 4); else print((char) arg); }
        void print(const signed char*& arg) { if (NULL == arg) ::write(STDOUT_FILENO, "null", 4); else print((const char*&) arg); }

        void print(unsigned char*& arg) { if (NULL == arg) ::write(STDOUT_FILENO, "null", 4); else print((char*&) arg); }
        void print(const unsigned char arg) { if (NULL == (void*) (int) arg) ::write(STDOUT_FILENO, "null", 4); else print((char) arg); }
        void print(const unsigned char*& arg) { if (NULL == arg) ::write(STDOUT_FILENO, "null", 4); else print((const char*&) arg); }

        // [Plain-Old-Data] --- WARN (Lapys) -> Passing `NULL` as an argument calls `void ::print(const int)` and throws a compiler warning.
        inline void print(const bool arg) { arg ? ::write(STDOUT_FILENO, "true", 4) : ::write(STDOUT_FILENO, "false", 5); }
        inline void print(const double arg) { if (arg - 1 == arg + 1) ::write(STDOUT_FILENO, "Infinity", 8); else if (std::isnan(arg)) ::write(STDOUT_FILENO, "NaN", 3); else { char* characterString = toCharacterString((long double) arg); ::write(STDOUT_FILENO, characterString, characterStringLength(characterString)); characterString = NULL; } }
        inline void print(const float arg) { if (arg - 1 == arg + 1) ::write(STDOUT_FILENO, "Infinity", 8); else if (std::isnan(arg)) ::write(STDOUT_FILENO, "NaN", 3); else { char* characterString = toCharacterString((long double) arg); ::write(STDOUT_FILENO, characterString, characterStringLength(characterString)); std::free(characterString); } }
        inline void print(const int arg) { if (arg - 1 == arg + 1) ::write(STDOUT_FILENO, "Infinity", 8); else if (std::isnan(arg)) ::write(STDOUT_FILENO, "NaN", 3); else { char* characterString = toCharacterString((long long) arg); ::write(STDOUT_FILENO, characterString, characterStringLength(characterString)); std::free(characterString); } }
        inline void print(const long arg) { if (arg - 1 == arg + 1) ::write(STDOUT_FILENO, "Infinity", 8); else if (std::isnan(arg)) ::write(STDOUT_FILENO, "NaN", 3); else { char* characterString = toCharacterString((long long) arg); ::write(STDOUT_FILENO, characterString, characterStringLength(characterString)); std::free(characterString); } }
        inline void print(const long double arg) { if (arg - 1 == arg + 1) ::write(STDOUT_FILENO, "Infinity", 8); else if (std::isnan(arg)) ::write(STDOUT_FILENO, "NaN", 3); else { char* characterString = toCharacterString(arg); ::write(STDOUT_FILENO, characterString, characterStringLength(characterString)); characterString = NULL; } }
        inline void print(const long long arg) { if (arg - 1 == arg + 1) ::write(STDOUT_FILENO, "Infinity", 8); else if (std::isnan(arg)) ::write(STDOUT_FILENO, "NaN", 3); else { char* characterString = toCharacterString(arg); ::write(STDOUT_FILENO, characterString, characterStringLength(characterString)); std::free(characterString); } }
        inline void print(const short arg) { if (arg - 1 == arg + 1) ::write(STDOUT_FILENO, "Infinity", 8); else if (std::isnan(arg)) ::write(STDOUT_FILENO, "NaN", 3); else { char* characterString = toCharacterString((long long) arg); ::write(STDOUT_FILENO, characterString, characterStringLength(characterString)); std::free(characterString); } }
        inline void print(const unsigned int arg) { if (arg - 1 == arg + 1) ::write(STDOUT_FILENO, "Infinity", 8); else if (std::isnan(arg)) ::write(STDOUT_FILENO, "NaN", 3); else { char* characterString = toCharacterString((unsigned long long) arg); ::write(STDOUT_FILENO, characterString, characterStringLength(characterString)); std::free(characterString); } }
        inline void print(const unsigned long arg) { if (arg - 1 == arg + 1) ::write(STDOUT_FILENO, "Infinity", 8); else if (std::isnan(arg)) ::write(STDOUT_FILENO, "NaN", 3); else { char* characterString = toCharacterString((unsigned long long) arg); ::write(STDOUT_FILENO, characterString, characterStringLength(characterString)); std::free(characterString); } }
        inline void print(const unsigned long long arg) { if (arg - 1 == arg + 1) ::write(STDOUT_FILENO, "Infinity", 8); else if (std::isnan(arg)) ::write(STDOUT_FILENO, "NaN", 3); else { char* characterString = toCharacterString(arg); ::write(STDOUT_FILENO, characterString, characterStringLength(characterString)); std::free(characterString); } }
        inline void print(const unsigned short arg) { if (arg - 1 == arg + 1) ::write(STDOUT_FILENO, "Infinity", 8); else if (std::isnan(arg)) ::write(STDOUT_FILENO, "NaN", 3); else { char* characterString = toCharacterString((unsigned long long) arg); ::write(STDOUT_FILENO, characterString, characterStringLength(characterString)); std::free(characterString); } }

        /* [Aggregates, Classes, Structures & Unions]
                --- NOTE ---
                    #Lapys:
                        - For non-determinable values.
                        - Will detect empty arrays of unknown bounds.
        */
        inline void print(std::string arg) { ::write(STDOUT_FILENO, arg.c_str(), arg.length()); }
        void print(std::u16string arg) { const char16_t* characterString = arg.c_str(); print(characterString); }
        void print(std::u32string arg) { const char32_t* characterString = arg.c_str(); print(characterString); }
        void print(std::wstring arg) { const wchar_t* characterString = arg.c_str(); print(characterString); }
        template <typename type> inline void print(type&) { ::write(STDOUT_FILENO, "[object]", 8); }

        // [Pointers]
        void print(std::FILE* arg) { if (arg == stderr) ::write(STDOUT_FILENO, "[standard error file pointer]", 29); else if (arg == stdin) ::write(STDOUT_FILENO, "[standard input file pointer]", 29); else if (arg == stdout) ::write(STDOUT_FILENO, "[standard output file pointer]", 30); else print((const void*) arg); }
        template <typename type> void print(type*& arg) { print((const void*) arg); }

        // [Functions]
        inline void print(void (&arg)()) { if (arg == flush) flush(); else ::write(STDOUT_FILENO, "[function]", 10); }
        template <typename type> inline void print(type (&)()) { ::write(STDOUT_FILENO, "[function]", 10); }
        template <typename type> inline void print(type (&)(...)) { ::write(STDOUT_FILENO, "[function]", 10); }
        template <typename type, typename... types> inline void print(type (&)(types...)) { ::write(STDOUT_FILENO, "[function]", 10); }

        // [Function Pointers]
        inline void print(void (*&arg)()) { if (NULL == arg) ::write(STDOUT_FILENO, "null", 4); else if (*arg == flush) flush(); else ::write(STDOUT_FILENO, "[function pointer]", 18); }
        template <typename type> inline void print(type (*&arg)()) { NULL == arg ? ::write(STDOUT_FILENO, "null", 4) : ::write(STDOUT_FILENO, "[function pointer]", 18); }
        template <typename type> inline void print(type (*&arg)(...)) { NULL == arg ? ::write(STDOUT_FILENO, "null", 4) : ::write(STDOUT_FILENO, "[function pointer]", 18); }
        template <typename type, typename... types> inline void print(type (*&arg)(types...)) { NULL == arg ? ::write(STDOUT_FILENO, "null", 4) : ::write(STDOUT_FILENO, "[function pointer]", 18); }

        /* [Arrays]
            --- NOTE (Lapys) ->
                - Not allowed to distinguish between constant character arrays and constant expression character strings (e.g.: `const char[...] {...}` and `"Hello, World!"`).
                - Prints non-null-terminated character strings properly by identifying them as arrays with template `length` (i.e.: `template <std::size_t length> void ::print(const char (&)[length])`).

            --- UPDATE REQUIRED (Lapys) -> Can not detect empty multi-dimensional arrays (e.g.: `int array[0][0]`).
            --- WARN (Lapys) -> Can only print arrays with a depth less than the recursive function limit or template instantiation depth.
        */
        template <std::size_t length> constexpr inline void print(const char (&arg)[length]) { std::size_t iterator = length; while (iterator) { const char character = *(arg + (length - (iterator -= 1) - 1)); if (character == '\0') break; else print(character); } }
        template <std::size_t length> constexpr inline void print(const wchar_t (&arg)[length]) { std::size_t iterator = length; while (iterator) { const wchar_t character = *(arg + (length - (iterator -= 1) - 1)); if (character == L'\0') break; else print(character); } }
        template <std::size_t length> constexpr inline void print(const char16_t (&arg)[length]) { std::size_t iterator = length; while (iterator) { const char16_t character = *(arg + (length - (iterator -= 1) - 1)); if (character == u'\0') break; else print(character); } }
        template <std::size_t length> constexpr inline void print(const char32_t (&arg)[length]) { std::size_t iterator = length; while (iterator) { const char32_t character = *(arg + (length - (iterator -= 1) - 1)); if (character == U'\0') break; else print(character); } }
        template <std::size_t length> constexpr inline void print(const signed char (&arg)[length]) { std::size_t iterator = length; while (iterator) { const signed char character = *(arg + (length - (iterator -= 1) - 1)); if (character == '\0') break; else print(character); } }
        template <std::size_t length> constexpr inline void print(const unsigned char (&arg)[length]) { std::size_t iterator = length; while (iterator) { const unsigned char character = *(arg + (length - (iterator -= 1) - 1)); if (character) print(character); else break; } }
        template <typename type> constexpr inline void print(type (&)[0]) { ::write(STDOUT_FILENO, "[]", 2); }
        template <std::size_t length, typename type>
        constexpr inline void print(type (&arg)[length]) {
            std::size_t iterator = length;
             ::write(STDOUT_FILENO, "[", 1);
             while (iterator) {
                print(*(arg + (length - (iterator -= 1) - 1)));
                iterator && ::write(STDOUT_FILENO, ", ", 2);
             }
              ::write(STDOUT_FILENO, "]", 1);
        }

        // [...] --- NOTE (Lapys) -> May not pick up on other data structures, such as manipulators.
        template <typename type, typename... types> inline void print(type arg, types... args) { print(arg); print(args...); }

    /* Main */
    int main(int argc, char* argv[]) {
        // Print
        print("===== PROGRAM INITIATED =====\n");
        print(std::flush);

        // Print
        print("Output Stream: \"");
            print(
                '\n',
                "    This was the best all-purpose printer Lapys could make in C/ C++ at the time\n", flush,
                "    not to confused with a pretty-printer which makes printed data streams legible.\n\n", flush,

                "    The idea for this printer was to be able to distinguish all C/ C++ data types and output their respective valid information\n", flush,
                "    without the use of existing C/ C++ print functions such `write` or `std::printf`.",
                '\n'
            );
        print('"');

        // Print
        print(std::endl);
        print("===== PROGRAM TERMINATED =====");

        // Return
        return 0;
    }
