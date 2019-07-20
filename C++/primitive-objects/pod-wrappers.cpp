/* Import */
#include <iostream> // Input-Output Stream
#include <math.h> // Mathematics
#include <stdbool.h> // Standard Boolean
#include <stdlib.h> // Standard Library
#include <cuchar> // Universal Characters

/* Function */
    // String
    constexpr inline static char* str(char character) { char* characterPointer = NULL; if (character == '\0') characterPointer = (char*) std::malloc(1 * sizeof(char)); else { characterPointer = (char*) std::malloc(2 * sizeof(char)); *(characterPointer + 1) = '\0'; } *characterPointer = character; return characterPointer; }
    constexpr inline static char16_t* str(char16_t character) { char16_t* characterPointer = NULL; if (character == '\0') characterPointer = (char16_t*) std::malloc(1 * sizeof(char16_t)); else { characterPointer = (char16_t*) std::malloc(2 * sizeof(char16_t)); *(characterPointer + 1) = u'\0'; } *characterPointer = character; return characterPointer; }
    constexpr inline static char32_t* str(char32_t character) { char32_t* characterPointer = NULL; if (character == '\0') characterPointer = (char32_t*) std::malloc(1 * sizeof(char32_t)); else { characterPointer = (char32_t*) std::malloc(2 * sizeof(char32_t)); *(characterPointer + 1) = U'\0'; } *characterPointer = character; return characterPointer; }
    constexpr inline static signed char* str(signed char character) { signed char* characterPointer = NULL; if (character == '\0') characterPointer = (signed char*) std::malloc(1 * sizeof(signed char)); else { characterPointer = (signed char*) std::malloc(2 * sizeof(signed char)); *(characterPointer + 1) = '\0'; } *characterPointer = character; return characterPointer; }
    constexpr inline static unsigned char* str(unsigned char character) { unsigned char* characterPointer = NULL; if (character == '\0') characterPointer = (unsigned char*) std::malloc(1 * sizeof(unsigned char)); else { characterPointer = (unsigned char*) std::malloc(2 * sizeof(unsigned char)); *(characterPointer + 1) = '\0'; } *characterPointer = character; return characterPointer; }
    constexpr inline static wchar_t* str(wchar_t character) { wchar_t* characterPointer = NULL; if (character == '\0') characterPointer = (wchar_t*) std::malloc(1 * sizeof(wchar_t)); else { characterPointer = (wchar_t*) std::malloc(2 * sizeof(wchar_t)); *(characterPointer + 1) = L'\0'; } *characterPointer = character; return characterPointer; }
        // Length
        constexpr inline static unsigned strlen(char* characterArray) { if (NULL == characterArray) return 0; else { unsigned length = 0; while (*(characterArray + length) != '\0') length += 1; return length; } }
        constexpr inline static unsigned strlen(char16_t* characterArray) { if (NULL == characterArray) return 0; else { unsigned length = 0; while (*(characterArray + length) != u'\0') length += 1; return length; } }
        constexpr inline static unsigned strlen(char32_t* characterArray) { if (NULL == characterArray) return 0; else { unsigned length = 0; while (*(characterArray + length) != U'\0') length += 1; return length; } }
        constexpr inline static unsigned strlen(signed char* characterArray) { if (NULL == characterArray) return 0; else { unsigned length = 0; while (*(characterArray + length) != '\0') length += 1; return length; } }
        constexpr inline static unsigned strlen(unsigned char* characterArray) { if (NULL == characterArray) return 0; else { unsigned length = 0; while (*(characterArray + length) != '\0') length += 1; return length; } }
        constexpr inline static unsigned strlen(wchar_t* characterArray) { if (NULL == characterArray) return 0; else { unsigned length = 0; while (*(characterArray + length) != L'\0') length += 1; return length; } }

/* Class */
    /* Number */
    class Number {
        // [Private]
        private:
            // [Constructor]
            inline Number(void*) { this -> type = this -> NaN; }
            inline Number(const void*) { this -> type = this -> NaN; }

            // Function > Modulus
            inline long double modulus(long double decimalA, long double decimalB) {
                // Initialization > Decimal Modulus
                double decimalModulus = decimalA < 0 ? -decimalA : decimalA;

                // (Loop > )Update > (...)
                (decimalB < 0) && (decimalB = -decimalB);
                while (decimalModulus >= decimalB) decimalModulus -= decimalB;

                // Return
                return decimalA < 0 ? -decimalModulus : decimalModulus;
            }

        // [Protected]
        protected:
            // Initialization > (Type, Value)
            enum {decimal, integer, NaN, signedInteger} type;
            union { long double decimal; unsigned long long integer; long long signedInteger; } value;

            // Phase > Update
            inline void update(const Number& number) {
                // Modification > Target > Type
                this -> type = number.type;

                // Logic > Update > (Target > Value)
                if (this -> type == this -> decimal) (this -> value).decimal = number.value.decimal;
                else if (this -> type == this -> integer) (this -> value).integer = number.value.integer;
                else if (this -> type == this -> signedInteger) (this -> value).signedInteger = number.value.signedInteger;
            }

        // [Public]
        public:
            // [Constructor]
            Number() { this -> type = integer; (this -> value).integer = 0; }
            Number(double number) { this -> type = this -> decimal; (this -> value).decimal = number; }
            Number(float number) { this -> type = this -> decimal; (this -> value).decimal = number; }
            Number(int number) { this -> type = this -> signedInteger; (this -> value).signedInteger = number; }
            Number(long number) { this -> type = this -> signedInteger; (this -> value).signedInteger = number; }
            Number(long double number) { this -> type = this -> decimal; (this -> value).decimal = number; }
            Number(long long number) { this -> type = this -> signedInteger; (this -> value).signedInteger = number; }
            Number(short number) { this -> type = this -> signedInteger; (this -> value).signedInteger = number; }
            Number(unsigned int number) { this -> type = this -> integer; (this -> value).integer = number; }
            Number(unsigned long number) { this -> type = this -> integer; (this -> value).integer = number; }
            Number(unsigned long long number) { this -> type = this -> integer; (this -> value).integer = number; }
            Number(unsigned short number) { this -> type = this -> integer; (this -> value).integer = number; }
            Number(const Number& number) { this -> update(number); }

            // [Operator]
                // [+]
                inline Number& operator +() { return *this; }
                Number operator +(Number number) {
                    // Logic > Return
                    if (this -> type == this -> decimal && number.type == number.decimal) return Number((this -> value).decimal + number.value.decimal);
                    else if (this -> type == this -> decimal && number.type == number.integer) return Number((this -> value).decimal + number.value.integer);
                    else if (this -> type == this -> decimal && number.type == number.signedInteger) return Number((this -> value).decimal + number.value.signedInteger);

                    else if (this -> type == this -> integer && number.type == number.decimal) return Number((this -> value).integer + number.value.decimal);
                    else if (this -> type == this -> integer && number.type == number.integer) return Number((this -> value).integer + number.value.integer);
                    else if (this -> type == this -> integer && number.type == number.signedInteger) return Number((this -> value).integer + number.value.signedInteger);

                    else if (this -> type == this -> signedInteger && number.type == number.decimal) return Number((this -> value).signedInteger + number.value.decimal);
                    else if (this -> type == this -> signedInteger && number.type == number.integer) return Number((this -> value).signedInteger + number.value.integer);
                    else if (this -> type == this -> signedInteger && number.type == number.signedInteger) return Number((this -> value).signedInteger + number.value.signedInteger);

                    // Return
                    return Number("NaN");
                }

                // [-]
                Number operator -() { if (this -> type == this -> decimal) return Number(-(this -> value).decimal); else if (this -> type == this -> integer) return Number(-(this -> value).integer); else if (this -> type == this -> signedInteger) return Number(-(this -> value).signedInteger); return Number("NaN"); }
                Number operator -(Number number) {
                    // Logic > Return
                    if (this -> type == this -> decimal && number.type == number.decimal) return Number((this -> value).decimal - number.value.decimal);
                    else if (this -> type == this -> decimal && number.type == number.integer) return Number((this -> value).decimal - number.value.integer);
                    else if (this -> type == this -> decimal && number.type == number.signedInteger) return Number((this -> value).decimal - number.value.signedInteger);

                    else if (this -> type == this -> integer && number.type == number.decimal) return Number((this -> value).integer - number.value.decimal);
                    else if (this -> type == this -> integer && number.type == number.integer) return Number((this -> value).integer - number.value.integer);
                    else if (this -> type == this -> integer && number.type == number.signedInteger) return Number((this -> value).integer - number.value.signedInteger);

                    else if (this -> type == this -> signedInteger && number.type == number.decimal) return Number((this -> value).signedInteger - number.value.decimal);
                    else if (this -> type == this -> signedInteger && number.type == number.integer) return Number((this -> value).signedInteger - number.value.integer);
                    else if (this -> type == this -> signedInteger && number.type == number.signedInteger) return Number((this -> value).signedInteger - number.value.signedInteger);

                    // Return
                    return Number("NaN");
                }

                // [*]
                Number operator *(Number number) {
                    // Logic > Return
                    if (this -> type == this -> decimal && number.type == number.decimal) return Number((this -> value).decimal * number.value.decimal);
                    else if (this -> type == this -> decimal && number.type == number.integer) return Number((this -> value).decimal * number.value.integer);
                    else if (this -> type == this -> decimal && number.type == number.signedInteger) return Number((this -> value).decimal * number.value.signedInteger);

                    else if (this -> type == this -> integer && number.type == number.decimal) return Number((this -> value).integer * number.value.decimal);
                    else if (this -> type == this -> integer && number.type == number.integer) return Number((this -> value).integer * number.value.integer);
                    else if (this -> type == this -> integer && number.type == number.signedInteger) return Number((this -> value).integer * number.value.signedInteger);

                    else if (this -> type == this -> signedInteger && number.type == number.decimal) return Number((this -> value).signedInteger * number.value.decimal);
                    else if (this -> type == this -> signedInteger && number.type == number.integer) return Number((this -> value).signedInteger * number.value.integer);
                    else if (this -> type == this -> signedInteger && number.type == number.signedInteger) return Number((this -> value).signedInteger * number.value.signedInteger);

                    // Return
                    return Number("NaN");
                }

                // [/]
                Number operator /(Number number) { return this -> toDecimal() / number.toDecimal(); }

                // [%]
                Number operator %(Number number) {
                    // Logic > Return
                    if (this -> type == this -> decimal && number.type == number.decimal) return Number(this -> modulus((this -> value).decimal, number.value.decimal));
                    else if (this -> type == this -> decimal && number.type == number.integer) return Number(this -> modulus((this -> value).decimal, number.value.integer));
                    else if (this -> type == this -> decimal && number.type == number.signedInteger) return Number(this -> modulus((this -> value).decimal, number.value.signedInteger));

                    else if (this -> type == this -> integer && number.type == number.decimal) return Number(this -> modulus((this -> value).integer, number.value.decimal));
                    else if (this -> type == this -> integer && number.type == number.integer) return Number((this -> value).integer % number.value.integer);
                    else if (this -> type == this -> integer && number.type == number.signedInteger) return Number((this -> value).integer % number.value.signedInteger);

                    else if (this -> type == this -> signedInteger && number.type == number.decimal) return Number(this -> modulus((this -> value).signedInteger, number.value.decimal));
                    else if (this -> type == this -> signedInteger && number.type == number.integer) return Number((this -> value).signedInteger % number.value.integer);
                    else if (this -> type == this -> signedInteger && number.type == number.signedInteger) return Number((this -> value).signedInteger % number.value.signedInteger);

                    // Return
                    return Number("NaN");
                }

                // [^]
                Number operator ^(Number number) {
                    // Logic > Return
                    if (this -> type == this -> decimal && number.type == number.decimal) return Number(this -> toSigned() ^ number.toSigned());
                    else if (this -> type == this -> decimal && number.type == number.integer) return Number(this -> toSigned() ^ number.value.integer);
                    else if (this -> type == this -> decimal && number.type == number.signedInteger) return Number(this -> toSigned() ^ number.value.signedInteger);

                    else if (this -> type == this -> integer && number.type == number.decimal) return Number((this -> value).integer ^ number.toSigned());
                    else if (this -> type == this -> integer && number.type == number.integer) return Number((this -> value).integer ^ number.value.integer);
                    else if (this -> type == this -> integer && number.type == number.signedInteger) return Number((this -> value).integer ^ number.value.signedInteger);

                    else if (this -> type == this -> signedInteger && number.type == number.decimal) return Number((this -> value).signedInteger ^ number.toSigned());
                    else if (this -> type == this -> signedInteger && number.type == number.integer) return Number((this -> value).signedInteger ^ number.value.integer);
                    else if (this -> type == this -> signedInteger && number.type == number.signedInteger) return Number((this -> value).signedInteger ^ number.value.signedInteger);

                    // Return
                    return Number("NaN");
                }

                // [&]
                Number operator &(Number number) {
                    // Logic > Return
                    if (this -> type == this -> decimal && number.type == number.decimal) return Number(this -> toSigned() & number.toSigned());
                    else if (this -> type == this -> decimal && number.type == number.integer) return Number(this -> toSigned() & number.value.integer);
                    else if (this -> type == this -> decimal && number.type == number.signedInteger) return Number(this -> toSigned() & number.value.signedInteger);

                    else if (this -> type == this -> integer && number.type == number.decimal) return Number((this -> value).integer & number.toSigned());
                    else if (this -> type == this -> integer && number.type == number.integer) return Number((this -> value).integer & number.value.integer);
                    else if (this -> type == this -> integer && number.type == number.signedInteger) return Number((this -> value).integer & number.value.signedInteger);

                    else if (this -> type == this -> signedInteger && number.type == number.decimal) return Number((this -> value).signedInteger & number.toSigned());
                    else if (this -> type == this -> signedInteger && number.type == number.integer) return Number((this -> value).signedInteger & number.value.integer);
                    else if (this -> type == this -> signedInteger && number.type == number.signedInteger) return Number((this -> value).signedInteger & number.value.signedInteger);

                    // Return
                    return Number("NaN");
                }

                // [|]
                Number operator |(Number number) {
                    // Logic > Return
                    if (this -> type == this -> decimal && number.type == number.decimal) return Number(this -> toSigned() & number.toSigned());
                    else if (this -> type == this -> decimal && number.type == number.integer) return Number(this -> toSigned() & number.value.integer);
                    else if (this -> type == this -> decimal && number.type == number.signedInteger) return Number(this -> toSigned() & number.value.signedInteger);

                    else if (this -> type == this -> integer && number.type == number.decimal) return Number((this -> value).integer & number.toSigned());
                    else if (this -> type == this -> integer && number.type == number.integer) return Number((this -> value).integer & number.value.integer);
                    else if (this -> type == this -> integer && number.type == number.signedInteger) return Number((this -> value).integer & number.value.signedInteger);

                    else if (this -> type == this -> signedInteger && number.type == number.decimal) return Number((this -> value).signedInteger & number.toSigned());
                    else if (this -> type == this -> signedInteger && number.type == number.integer) return Number((this -> value).signedInteger & number.value.integer);
                    else if (this -> type == this -> signedInteger && number.type == number.signedInteger) return Number((this -> value).signedInteger & number.value.signedInteger);

                    // Return
                    return Number("NaN");
                }

                // [~]
                Number operator ~() { return ~(this -> toSigned()); }

                // [!]
                bool operator !() const {
                    // Logic > Return
                    if (this -> type == this -> decimal) return (this -> value).decimal;
                    else if (this -> type == this -> integer) return (this -> value).integer;
                    else if (this -> type == this -> signedInteger) return (this -> value).signedInteger;

                    // Return
                    return false;
                }

                // [=]
                Number& operator =(Number number) { this -> update(number); return *this; }

                // [<]
                bool operator <(Number number) const {
                    // Logic > Return
                    if (this -> type == this -> decimal && number.type == number.decimal) return Number((this -> value).decimal < number.value.decimal);
                    else if (this -> type == this -> decimal && number.type == number.integer) return Number((this -> value).decimal < number.value.integer);
                    else if (this -> type == this -> decimal && number.type == number.signedInteger) return Number((this -> value).decimal < number.value.signedInteger);

                    else if (this -> type == this -> integer && number.type == number.decimal) return Number((this -> value).integer < number.value.decimal);
                    else if (this -> type == this -> integer && number.type == number.integer) return Number((this -> value).integer < number.value.integer);
                    else if (this -> type == this -> integer && number.type == number.signedInteger) return Number(this -> toSigned() < number.value.signedInteger);

                    else if (this -> type == this -> signedInteger && number.type == number.decimal) return Number((this -> value).signedInteger < number.value.decimal);
                    else if (this -> type == this -> signedInteger && number.type == number.integer) return Number((this -> value).signedInteger < number.toSigned());
                    else if (this -> type == this -> signedInteger && number.type == number.signedInteger) return Number((this -> value).signedInteger < number.value.signedInteger);

                    // Return
                    return false;
                }

                // [>]
                bool operator >(Number number) const {
                    // Logic > Return
                    if (this -> type == this -> decimal && number.type == number.decimal) return Number((this -> value).decimal > number.value.decimal);
                    else if (this -> type == this -> decimal && number.type == number.integer) return Number((this -> value).decimal > number.value.integer);
                    else if (this -> type == this -> decimal && number.type == number.signedInteger) return Number((this -> value).decimal > number.value.signedInteger);

                    else if (this -> type == this -> integer && number.type == number.decimal) return Number((this -> value).integer > number.value.decimal);
                    else if (this -> type == this -> integer && number.type == number.integer) return Number((this -> value).integer > number.value.integer);
                    else if (this -> type == this -> integer && number.type == number.signedInteger) return Number(this -> toSigned() > number.value.signedInteger);

                    else if (this -> type == this -> signedInteger && number.type == number.decimal) return Number((this -> value).signedInteger > number.value.decimal);
                    else if (this -> type == this -> signedInteger && number.type == number.integer) return Number((this -> value).signedInteger > number.toSigned());
                    else if (this -> type == this -> signedInteger && number.type == number.signedInteger) return Number((this -> value).signedInteger > number.value.signedInteger);

                    // Return
                    return false;
                }

                // [<=]
                Number& operator <=(Number number) { this -> update(*this < number); return *this; }

                // [>=]
                Number& operator >=(Number number) { this -> update(*this > number); return *this; }

                // [++]
                Number& operator ++() { *this += 1; return *this; }
                Number operator ++(signed) { Number number(*this); ++*this; return number; }

                // [--]
                Number operator --() { *this -= 1; return *this; }
                Number operator --(signed) { Number number(*this); --*this; return number; }

                // [<<]
                friend std::ostream& operator <<(std::ostream& outputStream, const Number& number) { outputStream << number.toDecimal(); return outputStream; }
                friend std::basic_ostream<wchar_t>& operator <<(std::basic_ostream<wchar_t>& wideOutputStream, const Number& number) { wideOutputStream << number.toDecimal(); return wideOutputStream; }

                // [>>]
                friend std::istream& operator >>(std::istream& inputStream, Number& number) { inputStream >> number.value.decimal; number.type = number.decimal; return inputStream; }

                // [==]
                bool operator ==(Number number) const {
                    // Logic > Return
                    if (this -> type == this -> decimal && number.type == number.decimal) return (this -> value).decimal == number.value.decimal;
                    else if (this -> type == this -> decimal && number.type == number.integer) return (this -> value).decimal == number.value.integer;
                    else if (this -> type == this -> decimal && number.type == number.signedInteger) return (this -> value).decimal == number.value.signedInteger;

                    else if (this -> type == this -> integer && number.type == number.decimal) return (this -> value).integer == number.value.decimal;
                    else if (this -> type == this -> integer && number.type == number.integer) return (this -> value).integer == number.value.integer;
                    else if (this -> type == this -> integer && number.type == number.signedInteger) return this -> toSigned() == number.value.signedInteger;

                    else if (this -> type == this -> signedInteger && number.type == number.decimal) return (this -> value).signedInteger == number.value.decimal;
                    else if (this -> type == this -> signedInteger && number.type == number.integer) return (this -> value).signedInteger == number.toSigned();
                    else if (this -> type == this -> signedInteger && number.type == number.signedInteger) return (this -> value).signedInteger == number.value.signedInteger;

                    // Return
                    return Number("NaN");
                }

                // [!=]
                bool operator !=(Number number) const { return !(*this == number); }

                // [&&]
                bool operator &&(Number number) const { return !!*this && !!number; }

                // [||]
                bool operator ||(Number number) const { return !!*this || !!number; }

                // [+=]
                Number operator +=(Number number) { *this = *this + number; return *this; }

                // [-=]
                Number operator -=(Number number) { *this = *this - number; return *this; }

                // [/=]
                Number operator /=(Number number) { *this = *this / number; return *this; }

                // [%=]
                Number operator %=(Number number) { *this = *this % number; return *this; }

                // [^=]
                Number operator ^=(Number number) { *this = *this ^ number; return *this; }

                // [&=]
                Number operator &=(Number number) { *this = *this & number; return *this; }

                // [|=]
                Number operator |=(Number number) { *this = *this | number; return *this; }

                // [*=]
                Number operator *=(Number number) { *this = *this * number; return *this; }

                // [Plain Old-Data]
                operator bool() { if (this -> type == this -> decimal) return (this -> value).decimal; else if (this -> type == this -> integer) return (this -> value).integer; else if (this -> type == this -> signedInteger) return (this -> value).signedInteger; return false; }
                operator double() { return this -> toDecimal(); }
                operator float() { return this -> toDecimal(); }
                operator int() { return this -> toSigned(); }
                operator long() { return this -> toSigned(); }
                operator long double() { return this -> toDecimal(); }
                operator long long() { return this -> toSigned(); }
                operator short() { return this -> toSigned(); }
                operator unsigned int() { return this -> toInteger(); }
                operator unsigned long() { return this -> toInteger(); }
                operator unsigned long long() { return this -> toInteger(); }
                operator unsigned short() { return this -> toInteger(); }

            // Function > To (Decimal, Integer, Signed)
            long double toDecimal() const { if (this -> type == this -> decimal) return (this -> value).decimal; else if (this -> type == this -> integer) return (this -> value).integer; else if (this -> type == this -> signedInteger) return (this -> value).signedInteger; return NAN; }
            unsigned long long toInteger() const { if (this -> type == this -> decimal) return (this -> value).decimal; else if (this -> type == this -> integer) return (this -> value).integer; else if (this -> type == this -> signedInteger) return (this -> value).signedInteger; return (unsigned long long) NAN; }
            long long toSigned() const { if (this -> type == this -> decimal) return (this -> value).decimal; else if (this -> type == this -> integer) return (this -> value).integer; else if (this -> type == this -> signedInteger) return (this -> value).signedInteger; return (unsigned long long) NAN; }
    };

    /* String */
    class String {
        // [Private]
        private:
            // Class > Character
            class Character {
                // [Protected]
                protected:
                    // Initialization > (Type, Value)
                    enum {native, signedNative, unsignedNative, utf16, utf32, wide} type;
                    union { char native; signed char signedNative; unsigned char unsignedNative; char16_t utf16; char32_t utf32; wchar_t wide; } value;

                    // Phase > Update
                    void update(const Character& character) {
                        this -> type = character.type;

                        if (this -> type == this -> native) (this -> value).native = character.value.native;
                        else if (this -> type == this -> signedNative) (this -> value).signedNative = character.value.signedNative;
                        else if (this -> type == this -> unsignedNative) (this -> value).unsignedNative = character.value.unsignedNative;
                        else if (this -> type == this -> utf16) (this -> value).utf16 = character.value.utf16;
                        else if (this -> type == this -> utf32) (this -> value).utf32 = character.value.utf32;
                        else if (this -> type == this -> wide) (this -> value).wide = character.value.wide;
                    }

                // [Public]
                public:
                    // [Constructor]
                    Character() { this -> type = this -> native; (this -> value).native = '\0'; }
                    Character(const char character) { this -> type = this -> native; (this -> value).native = character; }
                    Character(const char16_t character) { this -> type = this -> utf16; (this -> value).utf16 = character; }
                    Character(const char32_t character) { this -> type = this -> utf32; (this -> value).utf32 = character; }
                    Character(const signed char character) { this -> type = this -> signedNative; (this -> value).signedNative = character; }
                    Character(const unsigned char character) { this -> type = this -> unsignedNative; (this -> value).unsignedNative = character; }
                    Character(const wchar_t character) { this -> type = this -> wide; (this -> value).wide = character; }
                    Character(const Character& character) { this -> update(character); }

                    // [Operator]
                        // [=]
                        Character& operator =(Character character) { this -> update(character); return *this; }

                        // [Plain Old-Data]
                        operator char() { return this -> toCharacter(); }
                        operator signed char() { return this -> toSignedCharacter(); }
                        operator unsigned char() { return this -> toUnsignedCharacter(); }
                        operator char16_t() { return this -> toUTF16Character(); }
                        operator char32_t() { return this -> toUTF32Character(); }
                        operator wchar_t() { return this -> toWideCharacter(); }

                    // Function > To (...)
                    char toCharacter() const {
                        if (this -> type == this -> native) return (this -> value).native;
                        else if (this -> type == this -> signedNative) return (this -> value).signedNative;
                        else if (this -> type == this -> unsignedNative) return (this -> value).unsignedNative;
                        else if (this -> type == this -> utf16) return (this -> value).utf16;
                        else if (this -> type == this -> utf32) return (this -> value).utf32;
                        else if (this -> type == this -> wide) return (this -> value).wide;
                        return '\0';
                    }
                    signed char toSignedCharacter() const { return (signed char) this -> toCharacter(); }
                    signed char toUnsignedCharacter() const { return (unsigned char) this -> toCharacter(); }
                    char16_t toUTF16Character() const {
                        if (this -> type == this -> native) return (this -> value).native;
                        else if (this -> type == this -> signedNative) return (this -> value).signedNative;
                        else if (this -> type == this -> unsignedNative) return (this -> value).unsignedNative;
                        else if (this -> type == this -> utf16) return (this -> value).utf16;
                        else if (this -> type == this -> utf32) return (this -> value).utf32;
                        else if (this -> type == this -> wide) return (this -> value).wide;
                        return u'\0';
                    }
                    char32_t toUTF32Character() const {
                        if (this -> type == this -> native) return (this -> value).native;
                        else if (this -> type == this -> signedNative) return (this -> value).signedNative;
                        else if (this -> type == this -> unsignedNative) return (this -> value).unsignedNative;
                        else if (this -> type == this -> utf16) return (this -> value).utf16;
                        else if (this -> type == this -> utf32) return (this -> value).utf32;
                        else if (this -> type == this -> wide) return (this -> value).wide;
                        return U'\0';
                    }
                    wchar_t toWideCharacter() const {
                        if (this -> type == this -> native) return (this -> value).native;
                        else if (this -> type == this -> signedNative) return (this -> value).signedNative;
                        else if (this -> type == this -> unsignedNative) return (this -> value).unsignedNative;
                        else if (this -> type == this -> utf16) return (this -> value).utf16;
                        else if (this -> type == this -> utf32) return (this -> value).utf32;
                        else if (this -> type == this -> wide) return (this -> value).wide;
                        return L'\0';
                    }
            };

            // Function > Resize --- WARN (Lapys) -> Clears the content of the String.
            void resize(unsigned length) {
                std::free(this -> value);

                if (length) {
                    this -> length = length;
                    this -> value = (Character*) std::malloc(length * sizeof(Character));
                }
            }

        // [Protected]
        protected:
            // Initialization > (Type, Value)
            Character* value = NULL;

            // Phase
                // Initiate
                void initiate(char character) { this -> initiate(::str(character)); }
                void initiate(char* characterPointer) { this -> resize(::strlen(characterPointer)); this -> update(characterPointer); }

                void initiate(char16_t character) { this -> initiate(::str(character)); }
                void initiate(char16_t* characterPointer) { this -> resize(::strlen(characterPointer)); this -> update(characterPointer); }

                void initiate(char32_t character) { this -> initiate(::str(character)); }
                void initiate(char32_t* characterPointer) { this -> resize(::strlen(characterPointer)); this -> update(characterPointer); }

                void initiate(signed char character) { this -> initiate(::str(character)); }
                void initiate(signed char* characterPointer) { this -> resize(::strlen(characterPointer)); this -> update(characterPointer); }

                void initiate(unsigned char character) { this -> initiate(::str(character)); }
                void initiate(unsigned char* characterPointer) { this -> resize(::strlen(characterPointer)); this -> update(characterPointer); }

                void initiate(wchar_t character) { this -> initiate(::str(character)); }
                void initiate(wchar_t* characterPointer) { this -> resize(::strlen(characterPointer)); this -> update(characterPointer); }

                void initiate(const String& string) { this -> resize(string.length); this -> update(string); }

                // Update
                void update(char* characterPointer) { unsigned iterator = this -> length; *(this -> value + iterator) = '\0'; while (iterator) { iterator -= 1; *(this -> value + iterator) = *(characterPointer + iterator); } }
                void update(char16_t* characterPointer) { unsigned iterator = this -> length; while (iterator) { iterator -= 1; *(this -> value + iterator) = *(characterPointer + iterator); } }
                void update(char32_t* characterPointer) { unsigned iterator = this -> length; while (iterator) { iterator -= 1; *(this -> value + iterator) = *(characterPointer + iterator); } }
                void update(signed char* characterPointer) { unsigned iterator = this -> length; while (iterator) { iterator -= 1; *(this -> value + iterator) = *(characterPointer + iterator); } }
                void update(unsigned char* characterPointer) { unsigned iterator = this -> length; while (iterator) { iterator -= 1; *(this -> value + iterator) = *(characterPointer + iterator); } }
                void update(wchar_t* characterPointer) { unsigned iterator = this -> length; while (iterator) { iterator -= 1; *(this -> value + iterator) = *(characterPointer + iterator); } }
                void update(const String& string) { unsigned iterator = this -> length; while (iterator) { iterator -= 1; *(this -> value + iterator) = string[iterator]; } }

        // [Public]
        public:
            // Initialization > Length
            unsigned length = 0;

            // [Constructor]
            String() { this -> initiate('\0'); }

            String(const char character) { this -> initiate(character); }
            String(char characterArray[]) { this -> initiate(characterArray); }
            String(const char characterArray[]) { this -> initiate((char*) characterArray); }

            String(const char16_t character) { this -> initiate(character); }
            String(char16_t characterArray[]) { this -> initiate(characterArray); }
            String(const char16_t characterArray[]) { this -> initiate((char16_t*) characterArray); }

            String(const char32_t character) { this -> initiate(character); }
            String(char32_t characterArray[]) { this -> initiate(characterArray); }
            String(const char32_t characterArray[]) { this -> initiate((char32_t*) characterArray); }

            String(const signed char character) { this -> initiate(character); }
            String(signed char characterArray[]) { this -> initiate(characterArray); }
            String(const signed char characterArray[]) { this -> initiate((signed char*) characterArray); }

            String(const unsigned char character) { this -> initiate(character); }
            String(unsigned char characterArray[]) { this -> initiate(characterArray); }
            String(const unsigned char characterArray[]) { this -> initiate((unsigned char*) characterArray); }

            String(const wchar_t character) { this -> initiate(character); }
            String(wchar_t characterArray[]) { this -> initiate(characterArray); }
            String(const wchar_t characterArray[]) { this -> initiate((wchar_t*) characterArray); }

            String(const String& string) { this -> initiate(string); }

            // [Operator]
                // [+]
                String operator +(String string) const {
                    const unsigned length = this -> length + string.length;
                    unsigned iterator = length;

                    String concatenation;
                    concatenation.resize(iterator);

                    std::cout << "[WORKING]" << std::endl;

                    while (iterator != this -> length) { iterator -= 1; concatenation[iterator] = string[string.length - (length - iterator)]; }
                    while (iterator) { iterator -= 1; concatenation[iterator] = (*this)[iterator]; }

                    return concatenation;
                }

                // [-]
                // [*]
                // [/]
                // [%]
                // [^]
                // [&]
                // [|]
                // [~]
                // [!]
                // [,]
                // [=]
                // [<]
                // [>]
                // [<=]
                // [>=]
                // [++]
                // [--]
                // [<<]
                // [>>]
                // [==]
                // [!=]
                // [&&]
                // [||]
                // [+=]
                // [-=]
                // [/=]
                // [%=]
                // [^=]
                // [&=]
                // [|=]
                // [*=]
                // [<<=]
                // [>>=]

                // [=]
                String& operator =(String string) { this -> initiate(string); return *this; }

                // [<<]
                friend std::ostream& operator <<(std::ostream& outputStream, const String& string) { outputStream << string.toCharacterPointer(); return outputStream; }
                friend std::basic_ostream<wchar_t>& operator <<(std::basic_ostream<wchar_t>& wideOutputStream, const String& string) { wideOutputStream << string.toWideCharacterPointer(); return wideOutputStream; }

                // [[]]
                Character& operator [](unsigned index) const {
                    // Logic > Return
                    if (index >= this -> length) { static Character character; return character; }
                    else return *(this -> value + index);
                }
                Character& operator[](signed index) const { return (*this)[(unsigned) index]; }

                // [Plain-Old Data]
                operator char() { return *(this -> toCharacterPointer()); }
                operator char*() { return this -> toCharacterPointer(); }
                operator const char*() { return (char*) *this; }

                operator char16_t() { return *(this -> toUTF16CharacterPointer()); }
                operator char16_t*() { return this -> toUTF16CharacterPointer(); }
                operator const char16_t*() { return (char16_t*) *this; }

                operator char32_t() { return *(this -> toUTF32CharacterPointer()); }
                operator char32_t*() { return this -> toUTF32CharacterPointer(); }
                operator const char32_t*() { return (char32_t*) *this; }

                operator signed char() { return *(this -> toSignedCharacterPointer()); }
                operator signed char*() { return this -> toSignedCharacterPointer(); }
                operator const signed char*() { return (signed char*) *this; }

/                operator unsigned char() { return *(this -> toUnsignedCharacterPointer()); }
                operator unsigned char*() { return this -> toUnsignedCharacterPointer(); }
                operator const unsigned char*() { return (unsigned char*) *this; }

                operator wchar_t() { return *(this -> toWideCharacterPointer()); }
                operator wchar_t*() { return this -> toWideCharacterPointer(); }
                operator const wchar_t*() { return (wchar_t*) *this; }

            // Function > To (...)
            char* toCharacterPointer() const { unsigned iterator = this -> length; char* characterPointer = (char*) std::malloc(iterator + 1); *(characterPointer + iterator + 1) = '\0'; while (iterator) { iterator -= 1; *(characterPointer + iterator) = (*this)[iterator]; } return characterPointer; }
            signed char* toSignedCharacterPointer() const { return (signed char*) this -> toCharacterPointer(); }
            unsigned char* toUnsignedCharacterPointer() const { return (unsigned char*) this -> toCharacterPointer(); }
            char16_t* toUTF16CharacterPointer() const { unsigned iterator = this -> length; char16_t* utf16CharacterPointer = (char16_t*) std::malloc(iterator); *(utf16CharacterPointer + iterator + 1) = u'\0'; while (iterator) { iterator -= 1; *(utf16CharacterPointer + iterator) = (*this)[iterator]; } return utf16CharacterPointer; }
            char32_t* toUTF32CharacterPointer() const { unsigned iterator = this -> length; char32_t* utf32CharacterPointer = (char32_t*) std::malloc(iterator); *(utf32CharacterPointer + iterator + 1) = U'\0'; while (iterator) { iterator -= 1; *(utf32CharacterPointer + iterator) = (*this)[iterator]; } return utf32CharacterPointer; }
            wchar_t* toWideCharacterPointer() const { unsigned iterator = this -> length; wchar_t* wideCharacterPointer = (wchar_t*) std::malloc(iterator); *(wideCharacterPointer + iterator + 1) = L'\0'; while (iterator) { iterator -= 1; *(wideCharacterPointer + iterator) = (*this)[iterator]; } return wideCharacterPointer; }
    };

/* Function */
    // Add, Divide, Modulus, Multiply, Subtract
    inline Number add(Number numberA, Number numberB) { return numberA + numberB; }
    inline Number divide(Number numberA, Number numberB) { return numberA / numberB; }
    inline Number modulus(Number numberA, Number numberB) { return numberA % numberB; }
    inline Number multiply(Number numberA, Number numberB) { return numberA * numberB; }
    inline Number subtract(Number numberA, Number numberB) { return numberA - numberB; }

    // Concatenate, Includes, Remove, Repeat
    String concat(String stringA, String stringB) { return stringA + stringB; }
    // bool includes(String stringA, String stringB) const { return stringA.includes(stringB); }
    // String remove(String stringA, String stringB) { return stringA - stringB; }
    // String repeat(String string, Number count) { String repitition; while (count) { count -= 1; repitition += string; } return repitition; }

    /* Main */
    int main(int argc, char* argv[]) {
        // Print
        std::cout << "Add [2.5, 3]: " << add(2.5, 3) << std::endl;
        std::cout << "Divide [2.5, 3]: " << divide(2.5, 3) << std::endl;
        std::cout << "Modulus [2.5, 3]: " << modulus(2.5, 3) << std::endl;
        std::cout << "Multiply [2.5, 3]: " << multiply(2.5, 3) << std::endl;
        std::cout << "Subtract [2.5, 3]: " << subtract(2.5, 3) << std::endl;

        // Print
        std::cout << std::endl;

        // std::cout << String("Hello, World!") << std::endl;

        // Return
        return 0;
    }
