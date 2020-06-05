/* Logic > Definition > Lapys
        --- NOTE ---
            #Lapys:
                - For now, the core focus of this header file is to allow for consistency & simplicity along C++ development.
                - Also, to treat C++ like its easier-to-learn child: JavaScript.
*/
#ifndef LAPYS
#define LAPYS
    // Library Files
        /* C Math
                --- NOTE ---
                    #Lapys: Math methods & properties.
        */
        #ifndef _GLIBCXX_CMATH
            #include <cmath>
        #endif

        /* C Standard Integer
                --- NOTE ---
                    #Lapys: For integer-specific
        */
        #ifndef _GLIBCXX_CSTDINT
            #include <cstdint>
        #endif

        /* C Time
                --- NOTE ---
                    #Lapys: The C++ standard library's random number generator and date-time features.
        */
        #ifndef _GLIBCXX_CTIME
            #include <ctime>
        #endif

        /* Console Input-Output Header
                --- NOTE ---
                    #Lapys: More precise input methods.
        */
        #ifndef _CONIO_H_
            #include <conio.h>
        #endif

        /* File Stream
                --- NOTE ---
                    #Lapys: File access, creation, deletion & modification features.
        */
        #ifndef _GLIBCXX_FSTREAM
            #include <fstream>
        #endif

        /* Functional
                --- NOTE ---
                    #Lapys: For getter-setters, (custom) functions & lambdas.
        */
        #ifndef _GLIBCXX_FUNCTIONAL
            #include <functional>
        #endif

        /* Input-Output Stream
                --- NOTE ---
                    #Lapys: Input-output streaming methods.
        */
        #ifndef _GLIBCXX_IOSTREAM
            #include <iostream>
        #endif

        /* Standard Input-Output Header
                --- NOTE ---
                    #Lapys: Other input-output methods & properties.
        */
        #ifndef _STDIO_H
            #include <stdio.h>
        #endif

        /* String Stream
                --- NOTE ---
                    #Lapys: String stream methods & properties.
        */
        #ifndef _GLIBCXX_SSTREAM
            #include <sstream>
        #endif

        /* String Header
                --- NOTE ---
                    #Lapys: String methods & properties.
        */
        #ifndef _STRING_H
            #include <string.h>
        #endif

        /* Type Information
                --- NOTE ---
                    #Lapys: For data & information type features.
        */
        #ifndef _TYPEINFO
            #include <typeinfo>
        #endif

        /* Windows Header
                --- NOTE ---
                    #Lapys: Currently for console coloring...
        */
        #ifndef _WINDOWS_H
            #include <windows.h>
        #endif

    // Definition > (...)
    #ifndef FALSE
        #define FALSE !1
    #endif
    #ifndef TRUE
        #define TRUE !0
    #endif
    #define Infinity INFINITY
    #define ldouble long double
    #define lint long int
    #define llong long long
    #define luint long unsigned int
    #define NaN NAN
    #define sint short int
    #define suint short unsigned int
    #define uchar unsigned char
    #define uint unsigned int
    #define ulint unsigned long int
    #define usint unsigned short int

    #define xorswap(x, y) (x ^= y, y ^= x, x ^= y)

    // Namespace
        // Lapys C++ Development Kit
        namespace LapysCPPDevelopmentKit {
            // Class
                // Getter Setter
                template <typename data>
                class GetterSetter {
                    // [Private]
                    private:
                        // Initialization > (Current Value, Getter, Setter)
                        data currentValue;
                        std::function<const data()> getter;
                        std::function<void(data)> setter;

                        // [Operator]
                            // [>>]
                            template <typename GetterSetterData>
                            friend std::istream& operator >>(std::istream &inputStream, const GetterSetter<GetterSetterData>& getterSetter);

                            // [<<]
                            template <typename GetterSetterData>
                            friend std::ostream& operator <<(std::ostream &outputStream, const GetterSetter<GetterSetterData>& getterSetter);

                    // [Public]
                    public:
                        // [Constructor]
                        GetterSetter() :
                            getter([&]() -> data { return currentValue; }),
                            setter([&](data value) { currentValue = value; }),
                            currentValue()
                        {}

                        // [Operator]
                            // [()]
                            data operator()() { return getter(); }
                            void operator()(data value) { setter(value); }

                            // [=]
                            GetterSetter operator=(data value) {
                                // Setter > Value
                                setter(value);

                                // Return
                                return *this;
                            }
                            data operator=(GetterSetter value) { return value.getter(); }

                            // [[Data]]
                            operator data() { return getter(); }

                        // Function
                            // Initialize Getter
                            void initGetter(std::function<data()> func) { getter = func; }

                            // Initialize Setter
                            void initSetter(std::function<void(data)> func) { setter = func; }

                            // Get Value
                            data& getValue() { return currentValue; }
                };

            // Function
                // [Operator]
                    // [>>]
                        // {GetterSetter}
                        template <typename GetterSetterData>
                        std::istream& operator >>(std::istream &inputStream, const GetterSetter<GetterSetterData>& getterSetter) {
                            // Initialization > Value
                            GetterSetterData value;

                            // Update > Input Stream
                            inputStream >> value;

                            // Getter Setter > Setter > Value
                            getterSetter.setter(value);

                            // Return
                            return inputStream;
                        }

                    // [<<]
                        // {GetterSetter}
                        template <typename GetterSetterData>
                        std::ostream& operator <<(std::ostream &outputStream, const GetterSetter<GetterSetterData>& getterSetter) {
                            // Update > Output Stream
                            outputStream << getterSetter.getter();

                            // Return
                            return outputStream;
                        }

                // Number
                    // To Integer
                    template <typename data> int numberToInteger(data arg) { return std::floor(arg); }

                // Character
                    // To Lower Case
                    char charToLowerCase(char character) {
                        // Logic > Return
                        switch (character) {
                            case 'A': return 'a'; break;
                            case 'B': return 'b'; break;
                            case 'C': return 'c'; break;
                            case 'D': return 'd'; break;
                            case 'E': return 'e'; break;
                            case 'F': return 'f'; break;
                            case 'G': return 'g'; break;
                            case 'H': return 'h'; break;
                            case 'I': return 'i'; break;
                            case 'J': return 'j'; break;
                            case 'K': return 'k'; break;
                            case 'L': return 'l'; break;
                            case 'M': return 'm'; break;
                            case 'N': return 'n'; break;
                            case 'O': return 'o'; break;
                            case 'P': return 'p'; break;
                            case 'Q': return 'q'; break;
                            case 'R': return 'r'; break;
                            case 'S': return 's'; break;
                            case 'T': return 't'; break;
                            case 'U': return 'u'; break;
                            case 'V': return 'v'; break;
                            case 'W': return 'w'; break;
                            case 'X': return 'x'; break;
                            case 'Y': return 'y'; break;
                            case 'Z': return 'z'; break;
                            default: return character;
                        }
                    }

                    /* To Pointer
                            --- NOTE ---
                                #Lapys: For annoying `char` to `char*` conversions.
                    */
                    char* characterToPointer(char character) {
                        // Initialization > (Stream, String)
                        std::string stream = static_cast<std::ostringstream*>(&(std::ostringstream() << character)) -> str();
                        char* string = new char[stream.size() + 1];

                        // Update > String
                        strcpy(string, stream.c_str());

                        // Return
                        return string;
                    }

                    // To Upper Case
                    char charToUpperCase(char character) {
                        // Logic > Return
                        switch (character) {
                            case 'a': return 'A'; break;
                            case 'b': return 'B'; break;
                            case 'c': return 'C'; break;
                            case 'd': return 'D'; break;
                            case 'e': return 'E'; break;
                            case 'f': return 'F'; break;
                            case 'g': return 'G'; break;
                            case 'h': return 'H'; break;
                            case 'i': return 'I'; break;
                            case 'j': return 'J'; break;
                            case 'k': return 'K'; break;
                            case 'l': return 'L'; break;
                            case 'm': return 'M'; break;
                            case 'n': return 'N'; break;
                            case 'o': return 'O'; break;
                            case 'p': return 'P'; break;
                            case 'q': return 'Q'; break;
                            case 'r': return 'R'; break;
                            case 's': return 'S'; break;
                            case 't': return 'T'; break;
                            case 'u': return 'U'; break;
                            case 'v': return 'V'; break;
                            case 'w': return 'W'; break;
                            case 'x': return 'X'; break;
                            case 'y': return 'Y'; break;
                            case 'z': return 'Z'; break;
                            default: return character;
                        }
                    }

                // Number
                    // Maximum
                    template <class numberAData, class numberBData>
                    ldouble numberMax(numberAData numberA, numberBData numberB) { return static_cast<ldouble>(numberA > numberB ? numberA : numberB); }

                    // Minimum
                    template <class numberAData, class numberBData>
                    ldouble numberMin(numberAData numberA, numberBData numberB) { return static_cast<ldouble>(numberA < numberB ? numberA : numberB); }

                    // Modulus
                    template <class numberAData, class numberBData>
                    ldouble numberModulus(numberAData arg0, numberBData arg1) {
                        // Initialization > (Number (A, B), Division)
                        ldouble numberA = static_cast<ldouble>(arg0),
                            numberB = static_cast<ldouble>(arg1),
                            division = numberA / numberB;

                        // Return
                        return division == numberToInteger(division) ? 0 : numberA - (numberToInteger(division) * numberB);
                    }

                /* String
                        --- NOTE ---
                            #Lapys: Create a viable C-style string.
                */
                char* string() { return strdup(std::string("").c_str()); }
                char* string(char* copy) { return strdup(std::string(copy).c_str()); }
                    // Character At
                    char stringCharAt(char* string, uint index) { return *(string + index); }

                    // Is
                    bool stringIs(char stringA, char stringB) { return stringA == stringB; }
                    bool stringIs(char* stringA, char* stringB) { return !strcmp(stringA, stringB); }

                    // Is Empty
                    bool stringIsEmpty(char* string) { return !strcmp(string, ""); }

                    // Length
                    uint stringLength(char* string) { return strlen(string); }

                    // Concatenate
                    char* stringConcatenate(char* stringA, char* stringB) {
                        // Initialization > Value
                        char* value = (char*) malloc(1 + stringLength(stringA) + stringLength(stringB));

                        // Update > Value
                        strcpy(value, stringA);
                        strcat(value, stringB);

                        // Return
                        return value;
                    }

                    // Repeat
                    char* stringRepeat(char* string, uint count) {
                        // Initialization > Value
                        std::string value;

                        // Loop
                        while (count > 0) {
                            // Update > (Count, Value)
                            count -= 1;
                            value += string;
                        }

                        // Return
                        return strdup(value.c_str());
                    }

                    // Source Concatenate
                    char* stringSourceConcatenate(char*& stringA, char* stringB) {
                        // Update > String A
                        strcat(stringA, stringB);

                        // Return
                        return stringA;
                    }

                    /* Remove
                            --- NOTE ---
                                #Lapys: Remove a string from another.
                    */
                    char* stringRemove(char* string, char* match) {
                        // Initialization > (Complete, Iterator, Length, (Decremented) Match Length, Stream)
                        bool complete = FALSE;
                        uint iterator = 0, length = stringLength(string),
                            matchLength = stringLength(match),
                            decrementedMatchLength = matchLength - 1;
                        char* stream = LapysCPPDevelopmentKit::string();

                        /* Loop
                                Iterate through String.
                        */
                        for (iterator; iterator < length; iterator += 1) {
                            // Initialization > Match (Found, Iterator)
                            bool matchFound = FALSE;
                            uint matchIterator = 0;

                            // Logic
                            if (!complete)
                                /* Loop
                                        Iterate through Match.
                                */
                                for (matchIterator; matchIterator != matchLength; matchIterator += 1)
                                    /* Logic
                                            [if:else if statement]
                                    */
                                    if (!stringIs(stringCharAt(string, iterator + matchIterator), stringCharAt(match, matchIterator)))
                                        // Break
                                        break;

                                    else if (matchIterator == decrementedMatchLength) {
                                        // Update > (Complete, Iterator, Match Found)
                                        complete = TRUE;
                                        iterator += decrementedMatchLength;
                                        matchFound = TRUE;
                                    }

                            // Update > Stream
                            matchFound || stringSourceConcatenate(stream, characterToPointer(stringCharAt(string, iterator)));
                        }

                        // Return
                        return stream;
                    }

                    // Replace
                    char* stringReplace(char* string, char* match, char* replacement) {
                        // Initialization > (Complete, Replacement Is Empty, Iterator, Length, (Decremented) Match Length, Stream)
                        bool complete = FALSE, replacementIsEmpty = stringIsEmpty(replacement);
                        uint iterator = 0, length = stringLength(string),
                            matchLength = stringLength(match),
                            decrementedMatchLength = matchLength - 1;
                        char* stream = LapysCPPDevelopmentKit::string();

                        /* Loop
                                Iterate through String.
                        */
                        for (iterator; iterator < length; iterator += 1) {
                            // Initialization > Match (Found, Iterator)
                            bool matchFound = FALSE;
                            uint matchIterator = 0;

                            // Logic
                            if (!complete)
                                /* Loop
                                        Iterate through Match.
                                */
                                for (matchIterator; matchIterator != matchLength; matchIterator += 1)
                                    /* Logic
                                            [if:else if statement]
                                    */
                                    if (!stringIs(stringCharAt(string, iterator + matchIterator), stringCharAt(match, matchIterator)))
                                        // Break
                                        break;

                                    else if (matchIterator == decrementedMatchLength) {
                                        // Update > (Complete, Iterator, Match Found, Stream)
                                        complete = TRUE;
                                        iterator += decrementedMatchLength;
                                        matchFound = TRUE;
                                        replacementIsEmpty || stringSourceConcatenate(stream, replacement);
                                    }

                            // Update > Stream
                            matchFound || stringSourceConcatenate(stream, characterToPointer(stringCharAt(string, iterator)));
                        }

                        // Return
                        return stream;
                    }

                    // Remove Characters
                    char* stringRemoveCharacters(char* string, char* characters) {
                        // Initialization > (Iterator, Length, Stream)
                        uint iterator = 0, length = stringLength(characters);
                        char* stream = LapysCPPDevelopmentKit::string(string);

                        // Loop > Update > Stream
                        for (iterator; iterator != length; iterator += 1)
                            stream = stringRemove(stream, characterToPointer(stringCharAt(characters, iterator)));

                        // Return
                        return stream;
                    }

                    // Reverse
                    char* stringReverse(char* string) {
                        // Initialization > Buffer
                        char* buffer = string;

                        // Loop > Update > (Buffer, String)
                        while (buffer && *buffer) ++buffer;
                        for (--buffer; string < buffer; ++string, --buffer) xorswap(*string, *buffer);

                        // Return
                        return string;
                    }

                    // Reverse : UTF-8
                    char* stringReverse_UTF8(char* string) {
                        // Initialization > Buffer
                        char* buffer = string;

                        // Update > String
                        stringReverse(string);

                        // Loop > Update > Buffer
                        while (buffer && *buffer) ++buffer;

                        /* Loop
                                [while statement]
                        */
                        while (string < --buffer)
                            /* Logic
                                    [switch:case statement]

                                > (XOR Swap, Update > Buffer)
                            */
                            switch ((*buffer & 0xF0) >> 4) {
                                // {U+010000-U+10FFFF} Four Bytes
                                case 0xF:
                                    xorswap(*(buffer - 0), *(buffer - 3));
                                    xorswap(*(buffer - 1), *(buffer - 2));
                                    buffer -= 3;
                                    break;

                                // {U+000800-U+00FFFF} Three Bytes
                                case 0xE:
                                    xorswap(*(buffer - 0), *(buffer - 2));
                                    buffer -= 2;
                                    break;

                                // Fall Through
                                case 0xC:

                                // {U+000080-U+0007FF} Two Bytes
                                case 0xD:
                                    xorswap(*(buffer - 0), *(buffer - 1));
                                    buffer--;
                            }

                        // Return
                        return string;
                    }
        }

        // Lapys
        namespace Lapys {
            // Namespace
                // Data
                namespace Data {
                    // Namespace
                        // Convert
                        namespace Convert {
                            // Function
                                // To Character
                                template <typename data> char toCharacter(data arg) { return static_cast<char>(arg); }

                                // To Integer
                                template <typename data> int toInteger(data arg) { return static_cast<int>(arg); }

                                // To Long Double
                                template <typename data> ldouble toLongDouble(data arg) { return static_cast<ldouble>(arg); }

                                // To Numeral Data
                                template <typename data> ldouble toNumeralData(data arg) { return static_cast<ldouble>(arg); }

                                // To Output String Stream Pointer
                                template <typename data> std::ostringstream* toOutputStringStreamPointer(data arg) { return static_cast<std::ostringstream*>(arg); }

                                // To Unsigned Integer
                                template <typename data> uint toUnsignedInteger(data arg) { return static_cast<uint>(arg); }
                        }
                }

            // Function
                // Is Number
                template <typename data>
                bool isNumber(data arg) {
                    // Initialization > Argument Type
                    const std::type_info &argType(typeid(arg));

                    // Return
                    return argType == typeid(double) ||
                        argType == typeid(float) ||
                        argType == typeid(Infinity) || argType == typeid(int) ||
                        argType == typeid(ldouble) || argType == typeid(lint) || argType == typeid(llong) || argType == typeid(long) || argType == typeid(luint) ||
                        argType == typeid(NaN) ||
                        argType == typeid(sint) || argType == typeid(signed int) || argType == typeid(signed long int) || argType == typeid(signed short int) || argType == typeid(short) || argType == typeid(suint) ||
                        argType == typeid(uchar) || argType == typeid(uint) || argType == typeid(ulint) || argType == typeid(usint);
                }

                // Is Integer
                template <typename data>
                bool isInteger(data arg) { return isNumber(arg) && Data::Convert::toInteger(arg) == arg; }

                // Is Lower Case
                template <typename data>
                bool isLowerCase(data arg) { return !(arg == 'A' || arg == 'B' || arg == 'C' || arg == 'D' || arg == 'E' || arg == 'F' || arg == 'G' || arg == 'H' || arg == 'I' || arg == 'J' || arg == 'K' || arg == 'L' || arg == 'M' || arg == 'N' || arg == 'O' || arg == 'P' || arg == 'Q' || arg == 'R' || arg == 'S' || arg == 'T' || arg == 'U' || arg == 'V' || arg == 'W' || arg == 'X' || arg == 'Y' || arg == 'Z'); }

                // Is Negative Integer
                template <typename data>
                bool isNegativeInteger(data arg) { return isInteger(arg) && arg < 0; }

                // Is Negative Number
                template <typename data>
                bool isNegativeNumber(data arg) { return isNumber(arg) && arg < 0; }

                // Is Not a Number
                template <typename data>
                bool isNaN(data arg) { return isNumber(arg) && std::isnan(arg); }

                // Is Infinite
                template <typename data>
                bool isInfinite(data arg) { return isNumber(arg) && !isNaN(arg) && !std::isfinite(arg); }

                // Is Positive Integer
                template <typename data>
                bool isPositiveInteger(data arg) { return isInteger(arg) && (!arg || arg > 0); }

                // Is Positive Number
                template <typename data>
                bool isPositiveNumber(data arg) { return isNumber(arg) && (!arg || arg > 0); }

                // Is Upper Case
                template <typename data>
                bool isUpperCase(data arg) { return !(arg == 'a' || arg == 'b' || arg == 'c' || arg == 'd' || arg == 'e' || arg == 'f' || arg == 'g' || arg == 'h' || arg == 'i' || arg == 'j' || arg == 'k' || arg == 'l' || arg == 'm' || arg == 'n' || arg == 'o' || arg == 'p' || arg == 'q' || arg == 'r' || arg == 's' || arg == 't' || arg == 'u' || arg == 'v' || arg == 'w' || arg == 'x' || arg == 'y' || arg == 'z'); }

                // Numberfy
                ldouble numberfy() { return 0.00; }
                ldouble numberfy(char arg) {
                    // Initialization > Number
                    int number;

                    // Logic > Update > Number
                    switch (arg) {
                        case '0': number = 0; break;
                        case '1': number = 1; break;
                        case '2': number = 2; break;
                        case '3': number = 3; break;
                        case '4': number = 4; break;
                        case '5': number = 5; break;
                        case '6': number = 6; break;
                        case '7': number = 7; break;
                        case '8': number = 8; break;
                        case '9': number = 9;
                    }

                    // Return
                    return Data::Convert::toNumeralData(number);
                }
                ldouble numberfy(double arg) { return Data::Convert::toNumeralData(arg); }
                ldouble numberfy(int arg) { return Data::Convert::toNumeralData(arg); }
                ldouble numberfy(ldouble arg) { return Data::Convert::toNumeralData(arg); }
                ldouble numberfy(suint arg) { return Data::Convert::toNumeralData(arg); }
                ldouble numberfy(uint arg) { return Data::Convert::toNumeralData(arg); }

                template <typename data>
                ldouble numberfy(data arg) {
                    // Initialization > Number
                    ldouble number;

                    // Update > Number
                    (std::istringstream(arg) >> number) || (number = 0);

                    // Return
                    return number;
                }

                // Stringify
                char* stringify() { return LapysCPPDevelopmentKit::string(); }
                char* stringify(char* arg) { return LapysCPPDevelopmentKit::string(arg); }
                char* stringify(const char* arg) { return strdup(arg); }
                char* stringify(std::string arg) { return stringify(arg.c_str()); }
                char* stringify(std::stringstream arg) { return stringify(arg.str()); }
                char* stringify(char arg) { return LapysCPPDevelopmentKit::characterToPointer(arg); }
                template <typename data>
                char* stringify(data arg) {
                    // Initialization > (Stream, String)
                    std::string stream = Data::Convert::toOutputStringStreamPointer(&(std::ostringstream() << arg)) -> str();
                    char* string = new char[stream.size() + 1];

                    // Update > String
                    strcpy(string, stream.c_str());

                    // Return
                    return string;
                }

            // Class
                // Array, Boolean, Function, Number, Object, String
                class Array; class Boolean;
                class Function; class Number;
                class Object; class String;

                /* Array
                        --- CHECKPOINT ---
                */
                class Array {
                    // [Public]
                    public:
                        // Initialization > Length
                        LapysCPPDevelopmentKit::GetterSetter<uint> length;

                        // [Constructor]
                        Array() { constructor(); }

                        // [Operator]
                            // [bool]
                            operator bool() const { return TRUE; }

                            // [!]
                            Boolean operator !() const;

                            // [[]] --- CHECKPOINT ---
                            template <typename data> void operator [](uint index) {}

                        // Function
                            /* Constructor
                                    --- NOTE ---
                                        #Lapys: Handles default object construction.
                            */
                            inline void constructor() {
                                // Target > Length
                                    // Initialize Getter
                                    (this -> length).initGetter([&]() -> uint { return (this -> length).getValue(); });

                                    // Initialize Setter
                                    (this -> length).initSetter([&](uint value) -> uint { return ((this -> length).getValue() = value); });

                                // Modification > Target > Length
                                this -> length = 0;
                            }

                            // To String
                            String toString();

                            // Value Of --- CHECKPOINT ---
                            void valueOf() {}
                };

                // Boolean
                class Boolean {
                    // [Private]
                    private:
                        // Initialization > Value
                        bool value = FALSE;

                    // [Public]
                    public:
                        // [Constructor]
                        Boolean() {}
                        template <typename data> Boolean(data arg) { this -> value = !!arg; }

                        // [Operator]
                            // [bool]
                            operator bool() const { return !!(this -> value); }

                            // [+]
                            Number operator +();
                            Number operator +(Boolean arg);
                            template <typename data> Number operator +(data arg);

                            // [-]
                            Number operator -();
                            Number operator -(Boolean arg);
                            template <typename data> Number operator -(data arg);

                            // [*]
                            Number operator *(Boolean arg);
                            template <typename data> Number operator *(data arg);

                            // [/]
                            Number operator /(Boolean arg);
                            template <typename data> Number operator /(data arg);

                            // [%]
                            Number operator %(Boolean arg);
                            template <typename data> Number operator %(data arg);

                            // [>]
                            Boolean operator >(Boolean arg) { return Boolean((this -> value ? 1 : 0) > (arg.valueOf() ? 1 : 0)); }
                            template <typename data> Boolean operator >(data arg) { return Boolean((this -> value ? 1 : 0) > numberfy(arg)); }

                            // [<]
                            Boolean operator <(Boolean arg) { return Boolean((this -> value ? 1 : 0) < (arg.valueOf() ? 1 : 0)); }
                            template <typename data> Boolean operator <(data arg) { return Boolean((this -> value ? 1 : 0) < numberfy(arg)); }

                            // [!]
                            Boolean operator !() const;

                            // [=]
                            template <typename data> bool operator =(data arg) { return this -> value = !!arg; }

                            // [>=]
                            Boolean operator >=(Boolean arg) { return Boolean((this -> value ? 1 : 0) >= (arg.valueOf() ? 1 : 0)); }
                            template <typename data> Boolean operator >=(data arg) { return Boolean((this -> value ? 1 : 0) >= numberfy(arg)); }

                            // [<=]
                            Boolean operator <=(Boolean arg) { return Boolean((this -> value ? 1 : 0) <= (arg.valueOf() ? 1 : 0)); }
                            template <typename data> Boolean operator <=(data arg) { return Boolean((this -> value ? 1 : 0) <= numberfy(arg)); }

                            // [==]
                            template <typename data> Boolean operator ==(data arg) { return Boolean(this -> value == Boolean(arg).valueOf()); }

                            // [!=]
                            template <typename data> Boolean operator !=(data arg) { return Boolean(this -> value != Boolean(arg).valueOf()); }

                            // [<<]
                            friend std::ostream& operator <<(std::ostream& outputStream, const Boolean& boolean);

                        // To String
                        String toString();

                        // Value Of
                        bool valueOf() { return this -> value; }
                };

                /* Function
                        --- CHECKPOINT ---
                        --- NOTE ---
                            #Lapys: Not sure how feasible this is.
                */
                class Function {
                    // [Private] --- CHECKPOINT ---
                    private:

                    // [Public] --- CHECKPOINT ---
                    public:
                        // [Constructor]
                        Function() {}

                        // Function
                            // To String
                            String toString();

                            // Value Of
                            void valueOf();
                };

                // Number
                class Number {
                    // [Private]
                    private:
                        // Initialization > Value
                        ldouble value = 0;

                    // [Public]
                    public:
                        // [Constructor]
                        Number() {}
                        template <typename data> Number(data arg) { this -> value = numberfy(arg); }

                        // [Operator]
                            // [bool]
                            operator bool() const { return !!(this -> value); }

                            // [+]
                            Number operator +() { return Number(this -> value); }
                            Number operator +(const Number& number) { return Number(this -> value + numberfy(number.value)); }
                            template <typename data> Number operator +(data arg) { return Number(this -> value + numberfy(arg)); }
                            template <typename data> friend Number operator +(data arg, const Number& number);

                            // [-]
                            Number operator -() { return Number(-(this -> value)); }
                            Number operator -(const Number& number) { return Number(this -> value - numberfy(number.value)); }
                            template <typename data> Number operator -(data arg) { return Number(this -> value - numberfy(arg)); }
                            template <typename data> friend Number operator -(data arg, const Number& number);

                            // [*]
                            Number operator *(const Number& number) { return Number(this -> value * numberfy(number.value)); }
                            template <typename data> Number operator *(data number) { return Number(this -> value * numberfy(number)); }
                            template <typename data> friend Number operator *(data arg, const Number& number);

                            // [/]
                            Number operator /(const Number& number) { return Number(this -> value / numberfy(number.value)); }
                            template <typename data> Number operator /(data number) { return Number(this -> value / numberfy(number)); }
                            template <typename data> friend Number operator /(data arg, const Number& number);

                            // [%]
                            Number operator %(const Number& number) { return Number(LapysCPPDevelopmentKit::numberModulus(this -> value, number.value)); }
                            template <typename data> Number operator %(data number) { return Number(LapysCPPDevelopmentKit::numberModulus(this -> value, number)); }
                            template <typename data> friend Number operator %(data arg, const Number& number);

                            // [<]
                            template <typename data> Boolean operator <(data arg) { return Boolean(this -> value < numberfy(arg)); }

                            // [>]
                            template <typename data> Boolean operator >(data arg) { return Boolean(this -> value > numberfy(arg)); }

                            // [!]
                            Boolean operator !() const { return Boolean(!(this -> value)); }

                            // [=]
                            template <typename data> Number operator =(data arg) { return Number(this -> value = numberfy(arg)); }

                            // [+=]
                            Number operator +=(const Number& number) { return Number(this -> value += number.value); }

                            // [-=]
                            Number operator -=(const Number& number) { return Number(this -> value -= number.value); }

                            // [*=]
                            Number operator *=(const Number& number) { return Number(this -> value *= number.value); }

                            // [/=]
                            Number operator /=(const Number& number) { return Number(this -> value /= number.value); }

                            // [++]
                            Number operator ++() { return Number(++(this -> value)); }
                            Number operator ++(int) { return Number((this -> value)++); }

                            // [--]
                            Number operator --() { return Number(--(this -> value)); }
                            Number operator --(int) { return Number((this -> value)--); }

                            // [>=]
                            template <typename data> Boolean operator >=(data arg) { return Boolean(this -> value >= numberfy(arg)); }

                            // [<=]
                            template <typename data> Boolean operator <=(data arg) { return Boolean(this -> value <= numberfy(arg)); }

                            // [==]
                            template <typename data> Boolean operator ==(data arg) { return Boolean(this -> value == numberfy(arg)); }

                            // [!=]
                            template <typename data> Boolean operator !=(data arg) { return Boolean(this -> value != numberfy(arg)); }

                            // [<<]
                            friend std::ostream& operator <<(std::ostream& outputStream, const Number& number);

                        // To String
                        String toString();

                        // Value Of
                        ldouble valueOf() const {
                            // Return
                            return this -> value;
                        }
                };

                // Object
                class Object {
                    // [Private] --- CHECKPOINT ---
                    private:

                    // [Public] --- CHECKPOINT ---
                    public:
                        // To String
                        String toString();

                        // Value Of
                        void valueOf() {}
                };

                /* String
                        --- NOTE ---
                            #Lapys: Use C++ implementations of strings
                                rather than the `Array` class.
                */
                class String {
                    // [Private]
                    private:
                        // Initialization
                            // Value
                            char* value = LapysCPPDevelopmentKit::string();

                    // [Public]
                    public:
                        // Initialization > Length
                        LapysCPPDevelopmentKit::GetterSetter<uint> length;

                        // [Constructor]
                        String() { constructor(); }
                        template <typename data> String(data value) {
                            // Modification > Target > Value
                            this -> value = stringify(value);

                            // Constructor
                            constructor();
                        }

                        // [Operator]
                            // [bool]
                            operator bool() const { return !LapysCPPDevelopmentKit::stringIsEmpty(this -> value); }

                            // [+]
                            Number operator +() {
                                // Initialization > (Result, Value)
                                ldouble result;
                                char* value = this -> value;

                                // Logic > Update > Result
                                if (result = numberfy(value)) {}
                                else if (LapysCPPDevelopmentKit::stringIs(value, stringify('0')) || LapysCPPDevelopmentKit::stringIsEmpty(value))
                                    result = 0;

                                else
                                    result = NaN;

                                // Return
                                return Number(result);
                            }
                            String operator +(const String& string) { return String(LapysCPPDevelopmentKit::stringConcatenate(this -> value, string.value)); }
                            template <typename data> String operator +(data arg) { return String(LapysCPPDevelopmentKit::stringConcatenate(this -> value, stringify(arg))); }
                            template <typename data> friend String operator +(data arg, const String& string);

                            // [-]
                            Number operator -() {
                                // Initialization > (Result, Value)
                                ldouble result;
                                char* value = this -> value;

                                // Logic > Update > Result
                                if (result = numberfy(value)) {}
                                else if (LapysCPPDevelopmentKit::stringIs(value, stringify('0')) || LapysCPPDevelopmentKit::stringIsEmpty(value))
                                    result = -0;

                                else
                                    result = NaN;

                                // Return
                                return Number(result);
                            }
                            String operator -(const String& string) { return String(LapysCPPDevelopmentKit::stringRemoveCharacters(this -> value, string.value)); }
                            template <typename data> String operator -(data arg) { return String(LapysCPPDevelopmentKit::stringRemoveCharacters(this -> value, stringify(arg))); }
                            template <typename data> friend String operator -(data arg, const String& string);

                            // [*]
                            String operator *(int arg) { return String(LapysCPPDevelopmentKit::stringRepeat(this -> value, arg)); }
                            String operator *(uint arg) { return String(LapysCPPDevelopmentKit::stringRepeat(this -> value, arg)); }
                            String operator *(Number arg) { return String(LapysCPPDevelopmentKit::stringRepeat(this -> value, arg.valueOf())); }
                            template <typename data> friend String operator *(data arg, const String& string);

                            // [>]
                            Boolean operator >(String string) { return Boolean(LapysCPPDevelopmentKit::stringLength(this -> value) > LapysCPPDevelopmentKit::stringLength(string.valueOf())); }
                            template <typename data> Boolean operator >(data arg) { return Boolean(LapysCPPDevelopmentKit::stringLength(this -> value) > LapysCPPDevelopmentKit::stringLength(stringify(arg))); }

                            // [<]
                            Boolean operator <(String string) { return Boolean(LapysCPPDevelopmentKit::stringLength(this -> value) < LapysCPPDevelopmentKit::stringLength(string.valueOf())); }
                            template <typename data> Boolean operator <(data arg) { return Boolean(LapysCPPDevelopmentKit::stringLength(this -> value) < LapysCPPDevelopmentKit::stringLength(stringify(arg))); }

                            // [!]
                            Boolean operator !() const { return Boolean(LapysCPPDevelopmentKit::stringIsEmpty(this -> value)); }

                            // [=]
                            template <typename data> String operator =(data value) { return String(this -> value = stringify(value)); }

                            // [+=]
                            String operator +=(const String& string) { return String(this -> value = LapysCPPDevelopmentKit::stringConcatenate(this -> value, string.value)); }

                            // [>=]
                            Boolean operator >=(String string) { return Boolean(LapysCPPDevelopmentKit::stringLength(this -> value) >= LapysCPPDevelopmentKit::stringLength(string.valueOf())); }
                            template <typename data> Boolean operator >=(data arg) { return Boolean(LapysCPPDevelopmentKit::stringLength(this -> value) >= LapysCPPDevelopmentKit::stringLength(stringify(arg))); }

                            // [<=]
                            Boolean operator <=(String string) { return Boolean(LapysCPPDevelopmentKit::stringLength(this -> value) <= LapysCPPDevelopmentKit::stringLength(string.valueOf())); }
                            template <typename data> Boolean operator <=(data arg) { return Boolean(LapysCPPDevelopmentKit::stringLength(this -> value) <= LapysCPPDevelopmentKit::stringLength(stringify(arg))); }

                            // [==]
                            Boolean operator ==(const String& string) const { return Boolean(LapysCPPDevelopmentKit::stringIs(this -> value, string.value)); }
                            template <typename data> friend Boolean operator ==(data arg, const String& string);

                            // [!=]
                            Boolean operator !=(const String& string) const { return Boolean(!LapysCPPDevelopmentKit::stringIs(this -> value, string.value)); }
                            template <typename data> friend Boolean operator !=(data arg, const String& string);

                            // [<<]
                            friend std::ostream& operator <<(std::ostream& outputStream, const String& string);

                        // Function
                            /* Constructor
                                    --- NOTE ---
                                        #Lapys: Handles default object construction.
                            */
                            inline void constructor() {
                                // Modification > Target > Length > Initialize Getter
                                (this -> length).initGetter([&]() -> uint {
                                    // Return
                                    return LapysCPPDevelopmentKit::stringLength(this -> value);
                                });
                            }

                            // Character At
                            char charAt(uint index) { return isNegativeInteger(index) || index > this -> length ? 0 : LapysCPPDevelopmentKit::stringCharAt(this -> value, index); }

                            // Character Code At
                            Number charCodeAt(uint index) { return Number(Data::Convert::toInteger(charAt(index))); }

                            // Concatenate
                            template <typename data>
                            String concat(data string) { return String(LapysCPPDevelopmentKit::stringConcatenate(this -> value, stringify(string))); }

                            // Ends With
                            template <typename data>
                            Boolean endsWith(data string) {
                                // Initialization > (Match, (Match) Iterator)
                                char* match = stringify(string);
                                uint iterator = this -> length, matchIterator = LapysCPPDevelopmentKit::stringLength(match);

                                /* Loop
                                        [while statement]
                                */
                                while (iterator && matchIterator) {
                                    // Update > (Match) Iterator
                                    iterator -= 1;
                                    matchIterator -= 1;

                                    // Logic > Return
                                    if (!LapysCPPDevelopmentKit::stringIs(charAt(iterator), LapysCPPDevelopmentKit::stringCharAt(match, matchIterator)))
                                        return Boolean(FALSE);
                                }

                                // Return
                                return Boolean(TRUE);
                            }

                            // Includes
                            template <typename data>
                            Boolean includes(data string) {
                                // Initialization > (Match, Iterator, Length, (Decremented) Match Length)
                                char* match = stringify(string);
                                uint iterator = 0, length = this -> length,
                                    matchLength = LapysCPPDevelopmentKit::stringLength(match),
                                    decrementedMatchLength = matchLength - 1;

                                /* Loop
                                        Iterate through Target.
                                */
                                for (iterator; iterator != length; iterator += 1) {
                                    // Initialization > Match Iterator
                                    uint matchIterator = 0;

                                    /* Loop
                                            Iterate through Match.
                                    */
                                    for (matchIterator; matchIterator != matchLength; matchIterator += 1)
                                        /* Logic
                                                [if:else if statement]
                                        */
                                        if (!LapysCPPDevelopmentKit::stringIs(charAt(iterator + matchIterator), LapysCPPDevelopmentKit::stringCharAt(match, matchIterator)))
                                            // Break
                                            break;

                                        else if (matchIterator == decrementedMatchLength)
                                            // Return
                                            return Boolean(TRUE);
                                }

                                // Return
                                return Boolean(FALSE);
                            }

                            // Index Of
                            template <typename data>
                            Number indexOf(data string) {
                                // Initialization > (Match, Iterator, Length, (Decremented) Match Length)
                                char* match = stringify(string);
                                uint iterator = 0, length = this -> length,
                                    matchLength = LapysCPPDevelopmentKit::stringLength(match),
                                    decrementedMatchLength = matchLength - 1;

                                /* Loop
                                        Iterate through Target.
                                */
                                for (iterator; iterator != length; iterator += 1) {
                                    // Initialization > Match Iterator
                                    uint matchIterator = 0;

                                    /* Loop
                                            Iterate through Match.
                                    */
                                    for (matchIterator; matchIterator != matchLength; matchIterator += 1)
                                        /* Logic
                                                [if:else if statement]
                                        */
                                        if (!LapysCPPDevelopmentKit::stringIs(charAt(iterator + matchIterator), LapysCPPDevelopmentKit::stringCharAt(match, matchIterator)))
                                            // Break
                                            break;

                                        else if (matchIterator == decrementedMatchLength)
                                            // Return
                                            return Number(iterator);
                                }

                                // Return
                                return Number(-1);
                            }

                            // Last Index Of
                            template <typename data>
                            Number lastIndexOf(data string) {
                                // Initialization > (Match, Target, Iterator, Length, Index, (Decremented) Match Length)
                                char* match = LapysCPPDevelopmentKit::stringReverse_UTF8(stringify(string));
                                char* that = reverse().valueOf();
                                uint iterator = 0, length = this -> length,
                                    index = length,
                                    matchLength = LapysCPPDevelopmentKit::stringLength(match),
                                    decrementedMatchLength = matchLength - 1;

                                /* Loop
                                        Iterate through Target.
                                */
                                for (iterator; iterator != length; iterator += 1) {
                                    // Initialization > Match Iterator
                                    uint matchIterator = 0;

                                    // Update > Match Size
                                    index -= 1;

                                    /* Loop
                                            Iterate through Match.
                                    */
                                    for (matchIterator; matchIterator != matchLength; matchIterator += 1)
                                        /* Logic
                                                [if:else if statement]
                                        */
                                        if (!LapysCPPDevelopmentKit::stringIs(LapysCPPDevelopmentKit::stringCharAt(that, iterator + matchIterator), LapysCPPDevelopmentKit::stringCharAt(match, matchIterator)))
                                            // Break
                                            break;

                                        else if (matchIterator == decrementedMatchLength)
                                            // Return
                                            return Number(index);
                                }

                                // Return
                                return Number(-1);
                            }

                            // Match --- CHECKPOINT ---
                            Array match() {
                                // Return
                                return Array();
                            }

                            // Pad End
                            template <typename data>
                            String padEnd(uint maxLength, data fillString = " ") {
                                // Initialization > (Fill, String, Length)
                                char* fill = stringify(fillString);
                                char* string = stringify(this -> value);
                                uint length = this -> length;

                                /* Logic
                                        [if statement]
                                */
                                if (isPositiveInteger(maxLength) && maxLength > length) {
                                    // Update > Max Length
                                    maxLength -= length;

                                    /* Loop
                                            [while statement]
                                    */
                                    while (maxLength) {
                                        // Initialization > Fill (Iterator, Length)
                                        uint fillIterator = 0, fillLength = LapysCPPDevelopmentKit::stringLength(fill);

                                        // Loop > Update > (String, Maximum Length)
                                        for (fillIterator; maxLength && fillIterator != fillLength; fillIterator += 1) {
                                            string = LapysCPPDevelopmentKit::stringConcatenate(string, stringify(LapysCPPDevelopmentKit::stringCharAt(fill, fillIterator)));
                                            maxLength -= 1;
                                        }
                                    }
                                }

                                // Return
                                return String(string);
                            }

                            // Pad Start
                            template <typename data>
                            String padStart(uint maxLength, data fillString = " ") {
                                // Initialization > (Fill, String, Length)
                                char* fill = stringify(fillString);
                                char* string = stringify(this -> value);
                                uint length = this -> length;

                                /* Logic
                                        [if statement]
                                */
                                if (isPositiveInteger(maxLength) && maxLength > length) {
                                    // Initialization > Pad
                                    char* pad = LapysCPPDevelopmentKit::string();

                                    // Update > Max Length
                                    maxLength -= length;

                                    /* Loop
                                            [while statement]
                                    */
                                    while (maxLength) {
                                        // Initialization > Fill (Iterator, Length)
                                        uint fillIterator = 0, fillLength = LapysCPPDevelopmentKit::stringLength(fill);

                                        // Loop > Update > (Pad, Maximum Length)
                                        for (fillIterator; maxLength && fillIterator != fillLength; fillIterator += 1) {
                                            pad = LapysCPPDevelopmentKit::stringConcatenate(pad, stringify(LapysCPPDevelopmentKit::stringCharAt(fill, fillIterator)));
                                            maxLength -= 1;
                                        }
                                    }

                                    // Update > Pad
                                    pad = LapysCPPDevelopmentKit::stringConcatenate(pad, string);

                                    // Return
                                    return pad;
                                }

                                // Return
                                return String(string);
                            }

                            // Remove
                            template <typename data>
                            String remove(data match) { return String(LapysCPPDevelopmentKit::stringRemove(this -> value, stringify(match))); }

                            // Repeat
                            String repeat(uint count) { return String(LapysCPPDevelopmentKit::stringRepeat(stringify(this -> value), count)); }

                            // Replace
                            template <class matchData, class replacementData>
                            String replace(matchData match, replacementData replacement) { return String(LapysCPPDevelopmentKit::stringReplace(this -> value, stringify(match), stringify(replacement))); }

                            // Reverse
                            String reverse() { return String(LapysCPPDevelopmentKit::stringReverse_UTF8(stringify(this -> value))); }

                            // Slice --- CHECKPOINT ---
                            template <class startData, class endData>
                            String slice(startData start, endData end) {
                                return String();
                            }

                            // Split --- CHECKPOINT ---
                            Array split() {
                                // Return
                                return Array();
                            }

                            // Starts With
                            template <typename data>
                            Boolean startsWith(data string) {
                                // Initialization > (Match, Iterator, Length)
                                char* match = stringify(string);
                                uint iterator = 0, length = Data::Convert::toInteger(LapysCPPDevelopmentKit::numberMin(this -> length, LapysCPPDevelopmentKit::stringLength(match)));

                                // Loop > Logic > Return
                                for (iterator; iterator != length; iterator += 1)
                                    if (!LapysCPPDevelopmentKit::stringIs(charAt(iterator), LapysCPPDevelopmentKit::stringCharAt(match, iterator)))
                                        return Boolean(FALSE);

                                // Return
                                return Boolean(TRUE);
                            }

                            // To Lower Case
                            String toLowerCase() {
                                // Initialization > (Stream, Iterator, Length)
                                std::string stream;
                                uint iterator = 0, length = this -> length;

                                /* Loop
                                        Iterate through Target.
                                */
                                for (iterator; iterator != length; iterator += 1) {
                                    // Initialization > Character
                                    char character = charAt(iterator);

                                    // Update > Stream
                                    stream += isLowerCase(character) ? character : LapysCPPDevelopmentKit::charToLowerCase(character);
                                }

                                // Return
                                return String(stream);
                            }

                            // To Upper Case
                            String toUpperCase() {
                                // Initialization > (Stream, Iterator, Length)
                                std::string stream;
                                uint iterator = 0, length = this -> length;

                                /* Loop
                                        Iterate through Target.
                                */
                                for (iterator; iterator != length; iterator += 1) {
                                    // Initialization > Character
                                    char character = charAt(iterator);

                                    // Update > Stream
                                    stream += isUpperCase(character) ? character : LapysCPPDevelopmentKit::charToUpperCase(character);
                                }

                                // Return
                                return String(stream);
                            }

                            // Trim
                            String trim() { return String(trimLeft()).trimRight(); }

                            // Trim Left
                            String trimLeft() {
                                // Initialization > (Stream, Match)
                                char* stream = stringify(this -> value);
                                char match = charAt(0);

                                // Loop > Update > (Stream, Match)
                                while (
                                    !LapysCPPDevelopmentKit::stringIsEmpty(stream) &&
                                    (
                                        LapysCPPDevelopmentKit::stringIs(match, ' ') ||
                                        LapysCPPDevelopmentKit::stringIs(match, '\n')
                                    )
                                ) {
                                    stream = LapysCPPDevelopmentKit::stringRemove(stream, stringify(match));
                                    match = LapysCPPDevelopmentKit::stringCharAt(stream, 0);
                                }

                                // Return
                                return String(stream);
                            }

                            // Trim Right
                            String trimRight() {
                                // Initialization > (Stream, Match)
                                char* stream = reverse().valueOf();
                                char match = LapysCPPDevelopmentKit::stringCharAt(stream, 0);

                                // Loop > Update > (Stream, Match)
                                while (
                                    !LapysCPPDevelopmentKit::stringIsEmpty(stream) &&
                                    (
                                        LapysCPPDevelopmentKit::stringIs(match, ' ') ||
                                        LapysCPPDevelopmentKit::stringIs(match, '\n')
                                    )
                                ) {
                                    stream = LapysCPPDevelopmentKit::stringRemove(stream, stringify(match));
                                    match = LapysCPPDevelopmentKit::stringCharAt(stream, 0);
                                }

                                // Return
                                return String(LapysCPPDevelopmentKit::stringReverse_UTF8(stream));
                            }

                            // To String
                            String toString() { return String(this -> value); }

                            // Value Of
                            char* valueOf() const {
                                // Return
                                return this -> value;
                            }
                };

                // Array
                    // [!]
                    Boolean Array::operator !() const { return Boolean(FALSE); }

                // Boolean
                    // To String
                    String Boolean::toString() { return String(this -> value ? "true" : "false"); }

                    // [+]
                    Number Boolean::operator +() { return Number(this -> value ? 1 : 0); }
                    Number Boolean::operator +(Boolean arg) { return Number((this -> value ? 1 : 0) + (arg.valueOf() ? 1 : 0)); }
                    template <typename data> Number Boolean::operator +(data arg) { return Number((this -> value ? 1 : 0) + numberfy(arg)); }

                    // [-]
                    Number Boolean::operator -() { return -Number(this -> value ? 1 : 0); }
                    Number Boolean::operator -(Boolean arg) { return Number((this -> value ? 1 : 0) - (arg.valueOf() ? 1 : 0)); }
                    template <typename data> Number Boolean::operator -(data arg) { return Number((this -> value ? 1 : 0) - numberfy(arg)); }

                    // [*]
                    Number Boolean::operator *(Boolean arg) { return Number((this -> value ? 1 : 0) * (arg.valueOf() ? 1 : 0)); }
                    template <typename data> Number Boolean::operator *(data arg) { return Number((this -> value ? 1 : 0) * numberfy(arg)); }

                    // [/]
                    Number Boolean::operator /(Boolean arg) { return Number((this -> value ? 1 : 0) / (arg.valueOf() ? 1 : 0)); }
                    template <typename data> Number Boolean::operator /(data arg) { return Number((this -> value ? 1 : 0) / numberfy(arg)); }

                    // [%]
                    Number Boolean::operator %(Boolean arg) { return Number(LapysCPPDevelopmentKit::numberModulus(this -> value ? 1 : 0, arg.valueOf() ? 1 : 0)); }
                    template <typename data> Number Boolean::operator %(data arg) { return Number(LapysCPPDevelopmentKit::numberModulus(this -> value ? 1 : 0, numberfy(arg))); }

                    // [!]
                    Boolean Boolean::operator !() const { return Boolean(!(this -> value)); }

                    // [<<]
                    std::ostream& operator <<(std::ostream& outputStream, const Boolean& boolean) {
                        // Update > Output Stream
                        outputStream << (boolean.value ? "true" : "false");

                        // Return
                        return outputStream;
                    }

                // Number
                    // To String
                    String Number::toString() { return String(this -> value); }

                    // [+]
                    template <typename data> Number operator +(data arg, const Number& number) { return Number(numberfy(arg) + number.value); }

                    // [-]
                    template <typename data> Number operator -(data arg, const Number& number) { return Number(numberfy(arg) - number.value); }

                    // [*]
                    template <typename data> Number operator *(data arg, const Number& number) { return Number(numberfy(arg) * number.value); }

                    // [/]
                    template <typename data> Number operator /(data arg, const Number& number) { return Number(numberfy(arg) / number.value); }

                    // [%]
                    template <typename data> Number operator %(data arg, const Number& number) { return Number(LapysCPPDevelopmentKit::numberModulus(numberfy(arg), number.value)); }

                    // [<<]
                    std::ostream& operator <<(std::ostream& outputStream, const Number& number) {
                        // Update > Output Stream
                        outputStream << number.value;

                        // Return
                        return outputStream;
                    }

                    // [==]
                    template <typename data> Boolean operator ==(data arg, const Number& number) { return Boolean(numberfy(arg) == number.value); }

                // String
                    // [+]
                    template <typename data> String operator +(data arg, const String& string) { return String(LapysCPPDevelopmentKit::stringConcatenate(stringify(arg), string.value)); }

                    // [-]
                    template <typename data> String operator -(data arg, const String& string) { return String(LapysCPPDevelopmentKit::stringRemoveCharacters(stringify(arg), string.value)); }

                    // [*]
                    template <typename data> String operator *(data arg, const String& string) { return String(LapysCPPDevelopmentKit::stringRepeat(string.value, arg)); }

                    // [==]
                    template <typename data> Boolean operator ==(data arg, const String& string) { return Boolean(LapysCPPDevelopmentKit::stringIs(stringify(arg), string.valueOf())); }

                    // [!=]
                    template <typename data> Boolean operator !=(data arg, const String& string) { return Boolean(!LapysCPPDevelopmentKit::stringIs(stringify(arg), string.valueOf())); }

                    // [<<]
                    std::ostream& operator <<(std::ostream& outputStream, const String& string) {
                        // Update > Output Stream
                        outputStream << string.value;

                        // Return
                        return outputStream;
                    }

            // Function
                // Is Infinite
                bool isInfinite(char*& arg) { return FALSE; }
                bool isInfinite(const char*& arg) { return FALSE; }
                bool isInfinite(Lapys::Boolean arg) { return FALSE; }
                bool isInfinite(Lapys::Number arg) { return isInfinite(arg.valueOf()); }
                bool isInfinite(Lapys::String arg) { return FALSE; }
                bool isInfinite(Lapys::String* arg) { return FALSE; }
                bool isInfinite(LapysCPPDevelopmentKit::GetterSetter<uint> arg) { return isInfinite(arg.getValue()); }

                // Is Not a Number
                bool isNaN(char*& arg) { return FALSE; }
                bool isNaN(const char*& arg) { return FALSE; }
                bool isNaN(Lapys::Boolean arg) { return FALSE; }
                bool isNaN(Lapys::Number arg) { return isNaN(arg.valueOf()); }
                bool isNaN(Lapys::String arg) { return FALSE; }
                bool isNaN(Lapys::String* arg) { return FALSE; }
                bool isNaN(LapysCPPDevelopmentKit::GetterSetter<uint> arg) { return isNaN(arg.getValue()); }

                // Numberfy
                ldouble numberfy(const Lapys::Number& number) { return number.valueOf(); }

                // Print
                void print() {}
                template <typename data, typename... argumentsData>
                inline void print(data arg, argumentsData... args) {
                    // Initialization > Argument Type
                    const std::type_info &argType(typeid(arg));

                    /* Logic
                            [if:else if:else statement]

                        > Standard Library > C Output
                    */
                    if (argType == typeid(bool))
                        std::cout << (arg ? "true" : "false");

                    else if (isNumber(arg)) {
                        /* Logic
                                [if:else if:else statement]

                            > Standard Library > C Output
                        */
                        if (isNaN(arg))
                            std::cout << "NaN";

                        else if (isInfinite(arg))
                            std::cout << (isNegativeNumber(arg) ? "-Infinity" : "Infinity");

                        else
                            std::cout << arg;
                    }

                    else
                        std::cout << arg;

                    // Print
                    print(args...);
                }

                // Print Line
                inline void printl() {
                    // Standard Library > C Output
                    std::cout << std::endl;
                }

                template <typename... data>
                inline void printl(data... args) {
                    // Print
                    print(args...);
                    print('\n');
                }

                // Stringify
                char* stringify(const Lapys::String& string) { return string.valueOf(); }

            // Namespace
                /* Console
                        --- NOTE ---
                            #Lapys: Console-specific attributes & properties.
                */
                namespace Console {
                    // Function
                        // Clear
                        inline void clear() { system("cls"); }

                        // Get Color Scheme
                        Number getColorScheme() {
                            // Initialization > Information
                            CONSOLE_SCREEN_BUFFER_INFO info;

                            // Get Console Screen Buffer Information
                            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

                            // Return
                            return Number(info.wAttributes);
                        }

                        // Set Color Scheme
                        template <typename data>
                        Number setColorScheme(data attribute) {
                            // Set Console Text Attribute
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), numberfy(attribute));

                            // Return
                            return getColorScheme();
                        }

                        Number setColorScheme(const char* background, const char* foreground) {
                            // Initialization > (Color Scheme, Number of Schemes, (Background, Foreground) Iterator, Schemes)
                            int colorScheme = 255,
                                nSchemes = 16,
                                backgroundIterator = nSchemes,
                                foregroundIterator = nSchemes;
                            const char* schemes[nSchemes] = {"black", "darkblue", "darkgreen", "cyan", "darkred", "purple", "gold", "gray", "darkgray", "blue", "green", "lightblue", "red", "pink", "yellow", "white"};

                            /* Loop
                                    Index Schemes.
                            */
                            while (backgroundIterator) {
                                // Initialization > Background Scheme
                                const char* backgroundScheme = schemes[backgroundIterator -= 1];

                                /* Logic
                                        [if statement]
                                */
                                if (background == backgroundScheme) {
                                    /* Loop
                                            Index Schemes.
                                    */
                                    while (foregroundIterator) {
                                        // Initialization > Foreground Scheme
                                        const char* foregroundScheme = schemes[foregroundIterator -= 1];

                                        /* Logic
                                                [if statement]
                                        */
                                        if (
                                            !(
                                                (backgroundScheme == "black" && foregroundScheme == "black") ||
                                                (backgroundScheme == "white" && foregroundScheme == "white")
                                            )
                                        ) {
                                            /* Logic
                                                    [if statement]
                                            */
                                            if (foreground == foregroundScheme) {
                                                // Set Color Scheme
                                                setColorScheme(colorScheme - 1);

                                                // Break
                                                break;
                                            }

                                            // Update > Color Scheme
                                            colorScheme -= 1;
                                        }
                                    }

                                    // Break
                                    break;
                                }

                                /* Update > Color Scheme
                                        --- NOTE ---
                                            #Lapys: The first (black) and last (white) color scheme sets only have 15 variants, not 16.
                                */
                                colorScheme -= !backgroundIterator || backgroundIterator == nSchemes - 1 ? 15 : 16;
                            }

                            // Return
                            return getColorScheme();
                        }
                }

                // File --- CHECKPOINT ---
                namespace File {
                    // Function
                        // Read
                        template <typename data>
                        inline String read(data arg) {
                            // Initialization > (Content, Source, File)
                            String content;
                            const char* source = stringify(arg);
                            std::ifstream file(source);

                            /* Logic
                                    [if:else statement]
                            */
                            if (file.is_open()) {
                                // Initialization > Character
                                char character;

                                // Loop > Update > (Character, Content)
                                while (!file.eof()) {
                                    file.get(character);
                                    content += character;
                                }
                            }

                            else {}

                            // File > Close
                            file.close();

                            // Return
                            return content;
                        }
                }

                // Input
                namespace Input {
                    // Namespace
                        // Keyboard
                        namespace Keyboard {
                            /* Initialization
                                    --- UPDATE REQUIRED ---
                                        #Lapys: What do the character codes:
                                            -123, -122, -32, 0, 8
                                            represent?
                            */
                                // {Letter}
                                    // {Lowercase}
                                    int a = 97;
                                    int b = 98;
                                    int c = 99;
                                    int d = 100;
                                    int e = 101;
                                    int f = 102;
                                    int g = 103;
                                    int h = 104;
                                    int i = 105;
                                    int j = 106;
                                    int k = 107;
                                    int l = 108;
                                    int m = 109;
                                    int n = 110;
                                    int o = 111;
                                    int p = 112;
                                    int q = 113;
                                    int r = 114;
                                    int s = 115;
                                    int t = 116;
                                    int u = 117;
                                    int v = 118;
                                    int w = 119;
                                    int x = 120;
                                    int y = 121;
                                    int z = 122;

                                    // {Uppercase}
                                    int A = 65;
                                    int B = 66;
                                    int C = 67;
                                    int D = 68;
                                    int E = 69;
                                    int F = 70;
                                    int G = 71;
                                    int H = 72;
                                    int I = 73;
                                    int J = 74;
                                    int K = 75;
                                    int L = 76;
                                    int M = 77;
                                    int N = 78;
                                    int O = 79;
                                    int P = 80;
                                    int Q = 81;
                                    int R = 82;
                                    int S = 83;
                                    int T = 84;
                                    int U = 85;
                                    int V = 86;
                                    int W = 87;
                                    int X = 88;
                                    int Y = 89;
                                    int Z = 90;

                                // {Number}
                                int Zero = 48;
                                int One = 49;
                                int Two = 50;
                                int Three = 51;
                                int Four = 52;
                                int Five = 53;
                                int Six = 54;
                                int Seven = 55;
                                int Eight = 56;
                                int Nine = 57;

                                // {Special Characters}
                                int Add = 43;
                                int And = 38;
                                int Asterisk = 42;
                                int At = 64;
                                int Backslash = 92;
                                int Caret = 94;
                                int ClosedCurlyBrace = 125;
                                int ClosedParenthesis = 41;
                                int ClosedSquareBracket = 93;
                                int Colon = 58;
                                int Comma = 44;
                                int Dollar = 36;
                                int DoubleQuote = 34;
                                int Equal = 61;
                                int Exclamation = 33;
                                int Forwardslash = 47;
                                int GraveAccent = 96;
                                int GreaterThan = 62;
                                int Hash = 35;
                                int Hyphen = 45, Minus = 45;
                                int LesserThan = 60;
                                int OpenCurlyBrace = 123;
                                int OpenParenthesis = 40;
                                int OpenSquareBracket = 91;
                                int Percent = 37;
                                int Period = 46;
                                int Question = 63;
                                int Return = 3;
                                int SemiColon = 59;
                                int SingleQuote = 39;
                                int Space = 32;
                                int Tab = 9;
                                int Tilde = 126;
                                int Underscore = 95;
                                int VerticalBar = 124;

                            // Function
                                // Get Character
                                char getCharacter() {
                                    // Return
                                    return Data::Convert::toCharacter(std::getchar());
                                }

                                // Get Key
                                char getKey() {
                                    // Return
                                    return _getch();
                                }

                                // Get Line
                                Lapys::String getLine() {
                                    // Initialization > String
                                    std::string string;

                                    // Standard Library > Get Line
                                    std::getline(std::cin, string);

                                    // Return
                                    return Lapys::String(string);
                                }
                        }
                }

                // Math
                namespace Math {
                    // Initialization
                        // Euler`s Number
                        const Number E = 2.718281828459045,

                        // Pi
                        PI = 22.00 / 7.00;

                    // Function
                        // Absolute
                        template <typename data>
                        inline Number abs(data arg) {
                            // Initialization > Number
                            ldouble number = numberfy(arg);

                            // Return
                            return Number(isNegativeNumber(number) ? -number : number);
                        }

                        // Ackermann --- CHECKPOINT ---
                        template <typename data>
                        inline void ack(data arg) {}

                        // Arc Cosine
                        template <typename data>
                        inline Number acos(data arg) { return Number(std::acos(numberfy(arg))); }

                        // Arc Sine
                        template <typename data>
                        inline Number asin(data arg) { return Number(std::asin(numberfy(arg))); }

                        // Arc Tangent
                        template <typename data>
                        inline Number atan(data arg) { return Number(std::atan(numberfy(arg))); }

                        // Ceiling
                        template <typename data>
                        inline Number ceil(data arg) { return Number(std::ceil(numberfy(arg))); }

                        // Cosine
                        template <typename data>
                        inline Number cos(data arg) { return Number(std::cos(numberfy(arg))); }

                        // Cube Root
                        template <typename data>
                        inline Number cbrt(data arg) { return Number(std::cbrt(numberfy(arg))); }

                        // Exponent
                        template <typename data>
                        inline Number exp(data arg) { return Number(std::exp(numberfy(arg))); }

                        // Factorial --- CHECKPOINT ---
                        template <typename data>
                        inline void fact(data arg) {}

                        // Fibonacci --- CHECKPOINT ---
                        template <typename data>
                        inline void fibo(data arg) {}

                        // Floor
                        template <typename data>
                        inline Number floor(data arg) { return Number(std::floor(numberfy(arg))); }

                        // Is Finite
                        template <typename data>
                        inline Boolean isFinite(data arg) { return Boolean(std::isfinite(numberfy(arg))); }

                        // Is Integer
                        template <typename data>
                        inline Boolean isInteger(data arg) { return Boolean(Lapys::isInteger(numberfy(arg))); }

                        // Is Not a Number
                        template <typename data>
                        inline Boolean isNaN(data arg) { return Boolean(Lapys::isNaN(numberfy(arg))); }

                        // Is Non-Finite
                        template <typename data>
                        inline Boolean isNonFinite(data arg) { return !Math::isFinite(arg); }

                        // Is Non-Integer
                        template <typename data>
                        inline Boolean isNonInteger(data arg) { return !Math::isInteger(arg); }

                        // Is Safe Number
                        template <typename data>
                        inline Boolean isSafeNumber(data arg) { return Boolean(Math::isFinite(arg).valueOf() && !Math::isNaN(arg).valueOf()); }

                        // Is Safe Integer
                        template <typename data>
                        inline Boolean isSafeInteger(data arg) { return Boolean(Math::isSafeNumber(arg).valueOf() && Math::isInteger(arg).valueOf()); }

                        // Maximum --- CHECKPOINT ---
                        template <typename data>
                        inline void max(data arg) {}

                        // Minimum --- CHECKPOINT ---
                        template <typename data>
                        inline void min(data arg) {}

                        // Natural Logarithm
                        template <typename data>
                        inline Number log(data arg) { return Number(std::log(numberfy(arg))); }

                        // Natural Logarithm (Base 10) --- CHECKPOINT ---
                        template <typename data>
                        inline void log10(data arg) {}

                        /* Power
                                --- NOTE ---
                                    #Lapys: Favor integer-based results over rationals.
                        */
                        template <class baseData, class exponentData>
                        inline Number pow(baseData base, exponentData exponent) {
                            // Initialization > Results
                            ldouble results[2] = {exp(log(base).valueOf() * exponent).valueOf(), std::pow(base, exponent)};

                            // Return
                            return Number(LapysCPPDevelopmentKit::numberModulus(results[0], 1) > LapysCPPDevelopmentKit::numberModulus(results[1], 1) ? results[1] : results[0]);
                        }

                        // Random
                        inline Number random() {
                            // Standard Library > Seed Random
                            std::srand(std::time(NULL));

                            // Return
                            return Number(numberfy(std::rand() % 10) * .1);
                        }

                        // Root
                        template <class baseData, class exponentData>
                        inline Number root(baseData base, exponentData exponent) { return pow(base, 1.00 / exponent); }

                        // Round --- CHECKPOINT ---
                        template <typename data>
                        inline void round(data arg) {}

                        // Sine
                        template <typename data>
                        inline Number sin(data arg) { return Number(std::sin(numberfy(arg))); }

                        // Square Root
                        template <typename data>
                        inline Number sqrt(data arg) { return Number(std::sqrt(numberfy(arg))); }

                        // Tangent
                        template <typename data>
                        inline Number tan(data arg) { return Number(std::tan(numberfy(arg))); }
                }
        }

    // Modification > Lapys C++ Development Kit > Constants
    namespace LapysCPPDevelopmentKit::Constants {
        // Initialization
            // New Line
            Lapys::String NEWLINE = '\n';

            // Pi
            Lapys::Number PI = Lapys::Math::PI;

            // Tab Spacing
            Lapys::String TAB_SPACING = "    ";
    }

    // Utilization > Namespace > Lapys
    using namespace Lapys;
#endif
