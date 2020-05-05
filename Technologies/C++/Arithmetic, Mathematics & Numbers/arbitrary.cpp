/*
        UPDATE (Lapys) -> Check for primitive integer overflows in every method.
        UPDATE (Lapys) -> Each class has the same methods.
        UPDATE (Lapys) -> Each class is compatible.
        UPDATE (Lapys) -> Intermix differing radices for each class method.
        UPDATE (Lapys) -> Try to `constexpr` everything.
*/
/* Import */
    // [C Standard Library] --- NOTE (Lapys) -> The essential features.
    #include <float.h> // Floating-Point
    #include <limits.h> // Limits
    #include <math.h> // Mathematics
    #include <stdlib.h> // Standard Library
    #include <string.h> // String

    // [C++ Standard Library] --- NOTE (Lapys) ->  The feature testers.
    #include <cctype> // C Character Type
    #include <chrono> // Chronology
    #include <exception> // Exception
    #include <iostream> // Input-Output Stream
    #include <random> // Random
    #include <string> // String
    #include <sstream> // String Stream
    #include <type_traits> // Type Traits

/* Definition > ... */
template <size_t = 10u> class BigSignedInteger;
template <size_t = 10u> class BigFloat;
template <size_t = 10u> class BigUnsignedInteger;

typedef BigUnsignedInteger<10u> count_t;
typedef BigFloat<10u> BigNumber;
typedef BigSignedInteger<10u> BigInteger;

/* Polyfill > ... */
#ifndef INFINITY
#  define INFINITY HUGE_VAL
#endif

#ifndef NANL
#  define NANL NAN
#endif

/* Function > ... --- MINIFY (Lapys) --- NOTE (Lapys) -> Development & testing functions. */
constexpr inline void print(void) noexcept {}
inline void print(bool const argument) noexcept { argument ? std::cout.write("true", 4u) : std::cout.write("false", 5u); }
template <class type> constexpr inline void print(type argument) noexcept { std::cout << argument; }
template <size_t length, class type> inline typename std::enable_if<std::is_same<type, char>::value || std::is_same<type, char const>::value, void>::type print(type* const argument) noexcept { if (NULL == argument) print<6u>("[null]"); else std::cout.write(argument, length); }
template <size_t length, class type> inline typename std::enable_if<std::is_same<type, wchar_t>::value || std::is_same<type, wchar_t const>::value, void>::type print(type* const argument) noexcept { if (NULL == argument) print<6u>("[null]"); else std::wcout.write(argument, length); }
template <class type> inline void print(type* const argument) noexcept { if (NULL == argument) print<6u>("[null]"); else if (std::is_same<type, char>::value || std::is_same<type, char const>::value) std::cout << argument; else if (std::is_same<type, wchar_t>::value || std::is_same<type, wchar_t const>::value) std::wcout << argument; else { std::stringstream stream; stream << argument; char *string = (char*) stream.str().c_str(), *iterator = string; while ('\0' ^ *iterator) { if ('x' ^ *iterator) *iterator = std::toupper(*iterator); ++iterator; } print(string); } }
template <class type, class... types> inline void print(type argument, types... arguments) noexcept { print(argument); print(arguments...); }
inline void printfl(void) noexcept { std::flush(std::cout); }
template <size_t length, class type> inline void printfl(type argument) noexcept { print<length>(argument); printfl(); }
template <class... types> inline void printfl(types... arguments) noexcept { print(arguments...); printfl(); }
inline void println(void) noexcept { std::endl(std::cout); }
template <size_t count = 1u> inline void println(void) noexcept { if (count) { char const buffer[count + 1u] {'\n'}; print<count - 1u>(buffer); println(); } }
template <size_t count = 1u, size_t length, class type> inline void println(type argument) noexcept { print<length>(argument); println<count>(); }
template <size_t count = 1u, class... types> inline void println(types... arguments) noexcept { print(arguments...); println<count>(); }
constexpr inline void printp(void) noexcept {}
template <class type> constexpr inline void printp(type argument) noexcept { if ((std::is_same<type, char>::value || std::is_same<type, char const>::value) || (std::is_same<type, signed char>::value || std::is_same<type, signed char const>::value)) { print('\''); print(argument); print('\''); } else if ((std::is_same<type, bool>::value || std::is_same<type, bool const>::value) || (std::is_same<type, double>::value || std::is_same<type, double const>::value) || (std::is_same<type, int>::value || std::is_same<type, int const>::value) || (std::is_same<type, short>::value || std::is_same<type, short const>::value)) print(argument); else if (std::is_same<type, float>::value || std::is_same<type, float const>::value) { print(argument); print('f'); } else if ((std::is_same<type, long>::value || std::is_same<type, long const>::value) || (std::is_same<type, long double>::value || std::is_same<type, long double const>::value)) { print(argument); print('L'); } else if (std::is_same<type, unsigned char>::value || std::is_same<type, unsigned char const>::value) { print('\''); print(argument); print<2u>("'u"); } else if ((std::is_same<type, unsigned int>::value || std::is_same<type, unsigned int const>::value) || (std::is_same<type, unsigned short>::value || std::is_same<type, unsigned short const>::value)) { print(argument); print('u'); } else if (std::is_same<type, unsigned long>::value || std::is_same<type, unsigned long const>::value) { print(argument); print<2u>("uL"); } else if (std::is_same<type, wchar_t>::value || std::is_same<type, wchar_t const>::value) { print<2u>("L'"); print(argument); print('\''); } else print<8u>("[object]"); }
template <bool obfuscate = false, size_t length, class type> inline typename std::enable_if<std::is_same<type, char>::value || std::is_same<type, char const>::value, void>::type printp(type* const argument) noexcept { if (obfuscate) print<8u>("[string]"); else { print('"'); print(argument); print('"'); } }
template <bool obfuscate = false, size_t length, class type> inline typename std::enable_if<std::is_same<type, wchar_t>::value || std::is_same<type, wchar_t const>::value, void>::type printp(type* const argument) noexcept { if (obfuscate) print<8u>("[string]"); else { print<2u>("\"L"); print(argument); print('"'); } }
template <bool obfuscate = false, class type> inline void printp(type* const argument) noexcept { if (std::is_same<type, char>::value || std::is_same<type, char const>::value) { if (obfuscate) print<8u>("[string]"); else { print('"'); print(argument); print('"'); } } else if (std::is_same<type, wchar_t>::value || std::is_same<type, wchar_t const>::value) { if (obfuscate) print<8u>("[string]"); else { print<2u>("\"L"); print(argument); print('"'); } } else print(argument); }
template <bool obfuscate = false, size_t length, size_t size, class type> inline typename std::enable_if<true == ((std::is_same<type, char>::value || std::is_same<type, char const>::value) || (std::is_same<type, wchar_t>::value || std::is_same<type, wchar_t const>::value)), void>::type printp(type (&argument)[size]) noexcept { obfuscate ? print<8u>("[string]") : printp<length>(argument); }
template <class type> inline void printp(type (&)(...)) noexcept { print<10u>("[function]"); }
template <class type, class... types> inline void printp(type (&)(types...)) noexcept { print<10u>("[function]"); }
template <class type, class... types> inline void printp(type (&)(types..., ...)) noexcept { print<10u>("[function]"); }
template <class type, class... types> inline void printp(type argument, types... arguments) noexcept { printp(argument); printp(arguments...); }
inline void printflp(void) noexcept { printfl(); }
template <size_t length, class type> inline void printflp(type argument) noexcept { printp<length>(argument); printflp(); }
template <class... types> inline void printflp(types... arguments) noexcept { printp(arguments...); printflp(); }
inline void printlnp(void) noexcept { println(); }
template <size_t count = 1u> inline void printlnp(void) noexcept { if (count) { char const buffer[count + 1u] {'\n'}; print<count - 1u>(buffer); printlnp(); } }
template <size_t count = 1u, size_t length, class type> inline void printlnp(type argument) noexcept { printp<length>(argument); printlnp<count>(); }
template <size_t count = 1u, class... types> inline void printlnp(types... arguments) noexcept { printp(arguments...); printlnp<count>(); }


inline bool randbool(void) noexcept { static std::uniform_int_distribution<std::mt19937::result_type> distribution {0, 1}; static std::mt19937 randomizer {(unsigned long) std::chrono::system_clock::now().time_since_epoch().count()}; return distribution(randomizer); }
inline long double random(long double const minimum, long double const maximum) noexcept { std::uniform_real_distribution<> distribution {(double) minimum, (double) maximum}; static std::mt19937 randomizer {(unsigned long) std::chrono::system_clock::now().time_since_epoch().count()}; return distribution(randomizer); }
inline long double random(long double const range) noexcept { return random(0.00L, range); }
inline long double random(void) noexcept { return random(0.00L, 1.00L); }
inline unsigned int randint(unsigned int const minimum, unsigned int const maximum) noexcept { std::uniform_int_distribution<std::mt19937::result_type> distribution {minimum, maximum}; static std::mt19937 randomizer {(unsigned long) std::chrono::system_clock::now().time_since_epoch().count()}; return distribution(randomizer); }
inline unsigned int randint(unsigned int const range) noexcept { return randint(0u, range); }
inline int randint(int const range) noexcept { return (range < 0 ? -1L : 1L) * (long) randint((unsigned int) (range < 0 ? -range : range)); }
inline int randint(int const minimum, int const maximum) noexcept { return maximum < 0 ? (long) randint((unsigned int) -maximum, (unsigned int) (minimum < 0 ? -minimum : minimum)) : (((long) randint(0u, (unsigned int) (maximum + (minimum < 0 ? -minimum : minimum)))) - (minimum < 0 ? -minimum : minimum)); }
inline unsigned int randint(void) noexcept { return randint(0u, 10u); }
template <class typeA, class typeB> inline typename std::enable_if<(std::is_same<typeA, int>::value || std::is_same<typeA, long>::value || std::is_same<typeA, short>::value) && (std::is_same<typeB, int>::value || std::is_same<typeB, long>::value || std::is_same<typeB, short>::value), int>::type randint(typeA const minimum, typeB const maximum) noexcept { return randint((int) minimum, (int) maximum); }
template <class typeA, class typeB> inline typename std::enable_if<(std::is_same<typeA, unsigned int>::value || std::is_same<typeA, unsigned long>::value || std::is_same<typeA, unsigned short>::value) && (std::is_same<typeB, unsigned int>::value || std::is_same<typeB, unsigned long>::value || std::is_same<typeB, unsigned short>::value), unsigned int>::type randint(typeA const minimum, typeB const maximum) noexcept { return randint((unsigned int) minimum, (unsigned int) maximum); }
template <class typeA, class typeB> inline typename std::enable_if<(std::is_same<typeA, int>::value || std::is_same<typeA, long>::value || std::is_same<typeA, short>::value) && (std::is_same<typeB, unsigned int>::value || std::is_same<typeB, unsigned long>::value || std::is_same<typeB, unsigned short>::value), long long>::type randint(typeA const minimum, typeB const maximum) noexcept { if (minimum < 0) return randint((long) minimum, (long) (((long) maximum) < 0L ? -((long) maximum) : maximum)); else return randint((unsigned long) minimum, (unsigned long) maximum); }
template <class typeA, class typeB> inline typename std::enable_if<(std::is_same<typeA, unsigned int>::value || std::is_same<typeA, unsigned long>::value || std::is_same<typeA, unsigned short>::value) && (std::is_same<typeB, int>::value || std::is_same<typeB, long>::value || std::is_same<typeB, short>::value), long long>::type randint(typeA const minimum, typeB const maximum) noexcept { if (maximum < 0) return randint((long) (((long) minimum) < 0L ? -((long) minimum) : minimum), (long) maximum); else return randint((unsigned long) minimum, (unsigned long) maximum); }

/* Class > Digit --- NOTE (Lapys) -> Black-box to a single atomic value. */
class Digit { template <size_t> friend class BigFloat; template <size_t> friend class BigSignedInteger; template <size_t> friend class BigUnsignedInteger; friend int main(void);
    /* ... */
    public: typedef size_t digit_t; // NOTE (Lapys) -> Same type as the `radix` non-type template.

    // [...]
    private:
        // Definition > Value
        digit_t value;

    // [...]
    protected:
        // Function > (From, To) --- NOTE (Lapys) -> Parse values such as `'1'`, `'A'` or `'\0'` into valid numeric representatives.
        constexpr static digit_t from(char const) noexcept;
        constexpr static char to(digit_t const) noexcept;

    // [...]
    public:
        // [Constructor]
        constexpr inline Digit(void) : value{} {}
        constexpr inline Digit(digit_t const value) : value{value} {}
        constexpr inline Digit(Digit const& digit) : value{digit.value} {}
        constexpr inline Digit(Digit&& digit) : value{digit.value} {}

        // Function > ... --- MINIFY (Lapys)
            // [Conditional]
            constexpr static bool isEqual(Digit const, Digit const) noexcept;
            constexpr static bool isGreater(Digit const, Digit const) noexcept;
            constexpr static bool isLesser(Digit const, Digit const) noexcept;

            template <size_t> constexpr static bool isHighestRank(Digit const) noexcept;
            template <size_t> constexpr static bool isLowerRank(Digit const) noexcept;
            template <size_t> constexpr static bool isLowestRank(Digit const) noexcept;
            template <size_t> constexpr static bool isMeanRank(Digit const) noexcept;
            template <size_t> constexpr static bool isUpperRank(Digit const) noexcept;

            // [Operational] --- NOTE (Lapys) -> Atomic digit-by-digit arithmetic. If the radix is a fixed & static value, utilize a lookup table.
            template <size_t> static Digit const* add(Digit const, Digit const) noexcept;
            template <size_t> static Digit const* decrement(Digit const) noexcept;
            template <size_t> static Digit const* increment(Digit const) noexcept;
            template <size_t> static Digit const* multiply(Digit const, Digit const) noexcept;
            template <size_t> static Digit const* subtract(Digit const, Digit const) noexcept;

            // [Miscellaneous]
            constexpr static digit_t toNumber(Digit const) noexcept;
            char const* toString(void) const noexcept;

        // [Operator] > ...
        inline Digit& operator =(Digit const digit) noexcept { this -> value = digit.value; return *this; }
        inline Digit& operator +=(Digit const digit) noexcept { return Digit::operator =(this -> value + digit.value); }
        inline Digit& operator -=(Digit const digit) noexcept { return Digit::operator =(this -> value - digit.value); }
        inline Digit const operator ++(int const) noexcept { Digit const evaluation {this -> value}; Digit::operator ++(); return evaluation; }
        inline Digit& operator ++(void) noexcept { ++(this -> value); return *this; }
        inline Digit const operator --(int const) noexcept { Digit const evaluation {this -> value}; Digit::operator --(); return evaluation; }
        inline Digit& operator --(void) noexcept { --(this -> value); return *this; }

        inline operator digit_t(void) const noexcept { return Digit::toNumber(*this); }
};

/* Class
        --- NOTE ---
            #Lapys:
                - Maximum "decimal" places of `SIZE_MAX - ...`
                - Ironically, radices are of denary (decimal) value.
                - Utilizes positional notation to represent the numbers.

        --- WARN ---
            #Lapys:
                - POD/ primitive type numbers are mostly incompatible with these arbitrary-precision numbers in boolean arithmetic/ expressions (this excludes explicit/ implicit assignment, construction, or type casting).
                - The radix of a number may not be `0` or `1`.
*/
    /* Big Unsigned Integer --- NOTE (Lapys) -> Does not overflow beyond `0` into negatives. */
    template <size_t radix>
    class BigUnsignedInteger { template <size_t> friend class BigFloat; template <size_t> friend class BigSignedInteger; template <size_t> friend class BigUnsignedInteger; friend int main(void);
        /* ... */
        typedef typename Digit::digit_t digit_t;
        typedef unsigned long primitive;

        // [...]
        protected:
            // Definition > ...
            constexpr static primitive const PRIMITIVE_MAX = ULONG_MAX;

            // Definition > (Allocate, Copy) --- MINIFY (Lapys)
            constexpr inline void allocate(size_t const size) noexcept { this -> value = (Digit*) (NULL == this -> value ? ::malloc(size * sizeof(Digit)) : ::realloc(this -> value, size * sizeof(Digit))); }

            constexpr void copy(BigFloat<radix> const&);
            constexpr void copy(BigFloat<radix>&&);
            constexpr void copy(BigSignedInteger<radix> const&) noexcept;
            constexpr void copy(BigSignedInteger<radix>&&) noexcept;

            constexpr inline void copy(BigUnsignedInteger<radix> const& number) noexcept { if (&number != this) { BigUnsignedInteger::allocate((this -> length = number.length)); ::memcpy(this -> value, number.value, number.length * sizeof(Digit)); } }
            constexpr inline void copy(BigUnsignedInteger<radix>&& number) noexcept { this -> length = number.length; number.length = 0u; ::free(this -> value); this -> value = number.value; }

            template <size_t base> constexpr inline void copy(BigUnsignedInteger<base> const& number) noexcept { base == radix ? BigUnsignedInteger::copy(number) : BigUnsignedInteger::copy(BigUnsignedInteger::toBase<radix>(number)); }
            template <size_t base> constexpr inline void copy(BigUnsignedInteger<base>&& number) noexcept { base == radix ? BigUnsignedInteger::copy((BigUnsignedInteger<radix>&&) number) : BigUnsignedInteger::copy(BigUnsignedInteger::toBase<radix>(number)); }

        // [...]
        private:
            // Definition > (Length, Value)
            size_t length; // NOTE (Lapys) -> `0` must be represented without a significant `length` value.
            Digit *value; // WARN (Lapys) -> The amount of digits allowed must not be lesser than the `length` data member field.

        // [...]
        public:
            // [Constructor]
            constexpr inline BigUnsignedInteger(void) : length{0u}, value{NULL} {}
            constexpr inline BigUnsignedInteger(unsigned int const number) : length{0u}, value{NULL} { BigUnsignedInteger::copy(BigUnsignedInteger::fromInteger(number)); }
            constexpr inline BigUnsignedInteger(unsigned long const number) : length{0u}, value{NULL} { BigUnsignedInteger::copy(BigUnsignedInteger::fromInteger(number)); }
            constexpr inline BigUnsignedInteger(unsigned short const number) : length{0u}, value{NULL} { BigUnsignedInteger::copy(BigUnsignedInteger::fromInteger(number)); }
            constexpr inline BigUnsignedInteger(BigFloat<radix> const&);
            constexpr inline BigUnsignedInteger(BigFloat<radix>&&);
            constexpr inline BigUnsignedInteger(BigSignedInteger<radix> const&);
            constexpr inline BigUnsignedInteger(BigSignedInteger<radix>&&);
            template <size_t base> constexpr inline BigUnsignedInteger(BigUnsignedInteger<base> const& number) : length{0u}, value{NULL} { BigUnsignedInteger::copy((BigUnsignedInteger<base> const&) number); }
            template <size_t base> constexpr inline BigUnsignedInteger(BigUnsignedInteger<base>&& number) : length{0u}, value{NULL} { BigUnsignedInteger::copy((BigUnsignedInteger<base>&&) number); }

            // [Destructor]
            inline ~BigUnsignedInteger(void) { BigUnsignedInteger::zero(); }

            // Definition > ...
                // [Conditional]
                bool isBaseFactor(void) const noexcept;
                inline static bool isBaseFactor(BigUnsignedInteger<radix> const& number) noexcept { return number.isBaseFactor(); }

                bool isBig(void) const noexcept;
                inline static bool isBig(BigUnsignedInteger<radix> const& number) noexcept { return number.isBig(); }

                inline bool isEqual(unsigned int const number) const noexcept { return BigUnsignedInteger::isEqual(*this, (unsigned long) number); }
                inline bool isEqual(unsigned long const number) const noexcept { return BigUnsignedInteger::isEqual(*this, number); }
                inline bool isEqual(unsigned short const number) const noexcept { return BigUnsignedInteger::isEqual(*this, (unsigned long) number); }
                inline bool isEqual(BigUnsignedInteger<radix> const& number) const noexcept { return BigUnsignedInteger::isEqual(*this, number); }
                inline static bool isEqual(BigUnsignedInteger<radix> const& numberA, unsigned int numberB) noexcept { return BigUnsignedInteger::isEqual(numberA, (unsigned long) numberB); }
                static bool isEqual(BigUnsignedInteger<radix> const&, unsigned long) noexcept;
                inline static bool isEqual(BigUnsignedInteger<radix> const& numberA, unsigned short numberB) noexcept { return BigUnsignedInteger::isEqual(numberA, (unsigned long) numberB); }
                static bool isEqual(BigUnsignedInteger<radix> const&, BigUnsignedInteger<radix> const&) noexcept;

                inline bool isGreater(BigUnsignedInteger<radix> const& number) const noexcept { return BigUnsignedInteger::isGreater(*this, number); }
                static bool isGreater(BigUnsignedInteger<radix> const&, BigUnsignedInteger<radix> const&) noexcept;

                inline bool isLesser(BigUnsignedInteger<radix> const& number) const noexcept { return BigUnsignedInteger::isLesser(*this, number); }
                static bool isLesser(BigUnsignedInteger<radix> const&, BigUnsignedInteger<radix> const&) noexcept;

                bool isSignificant(void) const noexcept;
                inline static bool isSignificant(BigUnsignedInteger<radix> const& number) noexcept { return number.isSignificant(); }

                bool isZero(void) const noexcept;
                inline static bool isZero(BigUnsignedInteger<radix> const& number) noexcept { return number.isZero(); }

                // [Operational]
                BigUnsignedInteger<radix>& add(unsigned int const number) noexcept { BigUnsignedInteger::add((unsigned long) number); }
                BigUnsignedInteger<radix>& add(unsigned long const number) noexcept { if (number == 1uL) BigUnsignedInteger::increment(); else BigUnsignedInteger::add(BigUnsignedInteger<radix> {number}); return *this; }
                BigUnsignedInteger<radix>& add(unsigned short const number) noexcept { BigUnsignedInteger::add((unsigned long) number); }
                BigUnsignedInteger<radix>& add(BigUnsignedInteger<radix> const&) noexcept;
                inline static BigUnsignedInteger<radix> const add(BigUnsignedInteger<radix> const& numberA, unsigned int const numberB) noexcept { return BigUnsignedInteger::add(numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix> const add(BigUnsignedInteger<radix> const& numberA, unsigned long const numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.add(numberB); return evaluation; }
                inline static BigUnsignedInteger<radix> const add(BigUnsignedInteger<radix> const& numberA, unsigned short const numberB) noexcept { return BigUnsignedInteger::add(numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix> const add(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.add(numberB); return evaluation; }
                inline static BigUnsignedInteger<radix>& add(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix>&& numberB) noexcept { numberB.add(numberA); return numberB; }
                inline static BigUnsignedInteger<radix>& add(BigUnsignedInteger<radix>&& numberA, unsigned int const numberB) noexcept { return BigUnsignedInteger::add((BigUnsignedInteger<radix>&&) numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix>& add(BigUnsignedInteger<radix>&& numberA, unsigned long const numberB) noexcept { numberA.add(numberB); return numberA; }
                inline static BigUnsignedInteger<radix>& add(BigUnsignedInteger<radix>&& numberA, unsigned short const numberB) noexcept { return BigUnsignedInteger::add((BigUnsignedInteger<radix>&&) numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix>& add(BigUnsignedInteger<radix>&& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { numberA.add(numberB); return numberA; }

                BigUnsignedInteger<radix>& decrement(void) noexcept;
                inline static BigUnsignedInteger<radix>& decrement(BigUnsignedInteger<radix>& number) noexcept { number.decrement(); return number; }

                void divide(...) const;

                inline BigUnsignedInteger<radix>& exponentiate(unsigned int const number) noexcept { return BigUnsignedInteger::exponentiate((unsigned long) number); }
                inline BigUnsignedInteger<radix>& exponentiate(unsigned long const number) noexcept { if (number ^ 1uL) { if (number) BigUnsignedInteger::exponentiate(BigUnsignedInteger<radix> {number}); else { this -> length = 1u; *(this -> value) = 1u; } } return *this; }
                inline BigUnsignedInteger<radix>& exponentiate(unsigned short const number) noexcept { return BigUnsignedInteger::exponentiate((unsigned long) number); }
                BigUnsignedInteger<radix>& exponentiate(BigUnsignedInteger<radix> const&) noexcept;
                inline static BigUnsignedInteger<radix> const exponentiate(BigUnsignedInteger<radix> const& numberA, unsigned int const numberB) noexcept { return BigUnsignedInteger::exponentiate(numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix> const exponentiate(BigUnsignedInteger<radix> const& numberA, unsigned long const numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.exponentiate(numberB); return evaluation; }
                inline static BigUnsignedInteger<radix> const exponentiate(BigUnsignedInteger<radix> const& numberA, unsigned short const numberB) noexcept { return BigUnsignedInteger::exponentiate(numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix> const exponentiate(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.exponentiate(numberB); return evaluation; }
                inline static BigUnsignedInteger<radix>& exponentiate(BigUnsignedInteger<radix>&& numberA, unsigned int const numberB) noexcept { return BigUnsignedInteger::exponentiate((BigUnsignedInteger<radix>&&) numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix>& exponentiate(BigUnsignedInteger<radix>&& numberA, unsigned long const numberB) noexcept { numberA.exponentiate(numberB); return numberA; }
                inline static BigUnsignedInteger<radix>& exponentiate(BigUnsignedInteger<radix>&& numberA, unsigned short const numberB) noexcept { return BigUnsignedInteger::exponentiate((BigUnsignedInteger<radix>&&) numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix>& exponentiate(BigUnsignedInteger<radix>&& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { numberA.exponentiate(numberB); return numberA; }

                constexpr inline static BigUnsignedInteger<radix> const fromInteger(unsigned int const number) noexcept { return BigUnsignedInteger::fromInteger((unsigned long) number); }
                constexpr static BigUnsignedInteger<radix> const fromInteger(unsigned long const) noexcept;
                constexpr inline static BigUnsignedInteger<radix> const fromInteger(unsigned short const number) noexcept { return BigUnsignedInteger::fromInteger((unsigned long) number); }

                BigUnsignedInteger<radix>& increment(void) noexcept;
                inline static BigUnsignedInteger<radix>& increment(BigUnsignedInteger<radix>& number) noexcept { number.increment(); return number; }

                void logarithmize(...) const noexcept;

                inline BigUnsignedInteger<radix>& modulo(unsigned int const number) { return BigUnsignedInteger::modulo(number); }
                BigUnsignedInteger<radix>& modulo(unsigned long const);
                inline BigUnsignedInteger<radix>& modulo(unsigned short const number) { return BigUnsignedInteger::modulo(number); }
                void modulo(...) const noexcept;
                inline static BigUnsignedInteger<radix> const modulo(BigUnsignedInteger<radix> const& numberA, unsigned int const numberB) { return BigUnsignedInteger::modulo(numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix> const modulo(BigUnsignedInteger<radix> const& numberA, unsigned long const numberB) { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.modulo(numberB); return evaluation; }
                inline static BigUnsignedInteger<radix> const modulo(BigUnsignedInteger<radix> const& numberA, unsigned short const numberB) { return BigUnsignedInteger::modulo(numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix>& modulo(BigUnsignedInteger<radix>&& numberA, unsigned int const numberB) { return BigUnsignedInteger::modulo((BigUnsignedInteger<radix>&&) numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix>& modulo(BigUnsignedInteger<radix>&& numberA, unsigned long const numberB) { numberA.modulo(numberB); return numberA; }
                inline static BigUnsignedInteger<radix>& modulo(BigUnsignedInteger<radix>&& numberA, unsigned short const numberB) { return BigUnsignedInteger::modulo((BigUnsignedInteger<radix>&&) numberA, (unsigned long) numberB); }

                BigUnsignedInteger<radix>& multiply(unsigned int const number) noexcept { return BigUnsignedInteger::multiply((unsigned long) number); }
                BigUnsignedInteger<radix>& multiply(unsigned long const number) noexcept { if (number) { if (number ^ 1uL) BigUnsignedInteger::multiply(BigUnsignedInteger<radix> {number}); } else BigUnsignedInteger::zero(); return *this; }
                BigUnsignedInteger<radix>& multiply(unsigned short const number) noexcept { return BigUnsignedInteger::multiply((unsigned long) number); }
                BigUnsignedInteger<radix>& multiply(BigUnsignedInteger<radix> const&) noexcept;
                inline static BigUnsignedInteger<radix> const multiply(BigUnsignedInteger<radix> const& numberA, unsigned int const numberB) noexcept { return BigUnsignedInteger::multiply(numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix> const multiply(BigUnsignedInteger<radix> const& numberA, unsigned long const numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.multiply(numberB); return evaluation; }
                inline static BigUnsignedInteger<radix> const multiply(BigUnsignedInteger<radix> const& numberA, unsigned short const numberB) noexcept { return BigUnsignedInteger::multiply(numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix> const multiply(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.multiply(numberB); return evaluation; }
                inline static BigUnsignedInteger<radix>& multiply(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix>&& numberB) noexcept { numberB.multiply(numberA); return numberB; }
                inline static BigUnsignedInteger<radix>& multiply(BigUnsignedInteger<radix>&& numberA, unsigned int const numberB) noexcept { return BigUnsignedInteger::multiply((BigUnsignedInteger<radix>&&) numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix>& multiply(BigUnsignedInteger<radix>&& numberA, unsigned long const numberB) noexcept { numberA.multiply(numberB); return numberA; }
                inline static BigUnsignedInteger<radix>& multiply(BigUnsignedInteger<radix>&& numberA, unsigned short const numberB) noexcept { return BigUnsignedInteger::multiply((BigUnsignedInteger<radix>&&) numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix>& multiply(BigUnsignedInteger<radix>&& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { numberA.multiply(numberB); return numberA; }

                BigUnsignedInteger<radix>& shiftLeft(void) noexcept;
                BigUnsignedInteger<radix>& shiftLeft(unsigned int const number) noexcept { return BigUnsignedInteger::shiftLeft((unsigned long) number); }
                BigUnsignedInteger<radix>& shiftLeft(unsigned long) noexcept;
                BigUnsignedInteger<radix>& shiftLeft(unsigned short const number) noexcept { return BigUnsignedInteger::shiftLeft((unsigned long) number); }
                BigUnsignedInteger<radix>& shiftLeft(BigUnsignedInteger<radix> const&) noexcept;
                inline static BigUnsignedInteger<radix>& shiftLeft(BigUnsignedInteger<radix>& number) noexcept { return number.shiftLeft(); }
                inline static BigUnsignedInteger<radix> const shiftLeft(BigUnsignedInteger<radix> const& numberA, unsigned int const numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.shiftLeft((unsigned long) numberB); return evaluation; }
                inline static BigUnsignedInteger<radix> const shiftLeft(BigUnsignedInteger<radix> const& numberA, unsigned long const numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.shiftLeft(numberB); return evaluation; }
                inline static BigUnsignedInteger<radix> const shiftLeft(BigUnsignedInteger<radix> const& numberA, unsigned short const numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.shiftLeft((unsigned long) numberB); return evaluation; }
                inline static BigUnsignedInteger<radix> const shiftLeft(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.shiftLeft(numberB); return evaluation; }
                inline static BigUnsignedInteger<radix>& shiftLeft(BigUnsignedInteger<radix>&& numberA, unsigned int const numberB) noexcept { numberA.shiftLeft((unsigned long) numberB); return numberA; }
                inline static BigUnsignedInteger<radix>& shiftLeft(BigUnsignedInteger<radix>&& numberA, unsigned long const numberB) noexcept { numberA.shiftLeft(numberB); return numberA; }
                inline static BigUnsignedInteger<radix>& shiftLeft(BigUnsignedInteger<radix>&& numberA, unsigned short const numberB) noexcept { numberA.shiftLeft((unsigned long) numberB); return numberA; }
                inline static BigUnsignedInteger<radix>& shiftLeft(BigUnsignedInteger<radix>&& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { numberA.shiftLeft(numberB); return numberA; }

                BigUnsignedInteger<radix>& shiftRight(void) noexcept;
                BigUnsignedInteger<radix>& shiftRight(unsigned int const number) noexcept { return BigUnsignedInteger::shiftRight((unsigned long) number); }
                BigUnsignedInteger<radix>& shiftRight(unsigned long const) noexcept;
                BigUnsignedInteger<radix>& shiftRight(unsigned short const number) noexcept { return BigUnsignedInteger::shiftRight((unsigned long) number); }
                BigUnsignedInteger<radix>& shiftRight(BigUnsignedInteger<radix> const&) noexcept;
                inline static BigUnsignedInteger<radix>& shiftRight(BigUnsignedInteger<radix>& number) noexcept { return number.shiftRight(); }
                inline static BigUnsignedInteger<radix> const shiftRight(BigUnsignedInteger<radix> const& numberA, unsigned int const numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.shiftRight((unsigned long) numberB); return evaluation; }
                inline static BigUnsignedInteger<radix> const shiftRight(BigUnsignedInteger<radix> const& numberA, unsigned long const numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.shiftRight(numberB); return evaluation; }
                inline static BigUnsignedInteger<radix> const shiftRight(BigUnsignedInteger<radix> const& numberA, unsigned short const numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.shiftRight((unsigned long) numberB); return evaluation; }
                inline static BigUnsignedInteger<radix> const shiftRight(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.shiftRight(numberB); return evaluation; }
                inline static BigUnsignedInteger<radix>& shiftRight(BigUnsignedInteger<radix>&& numberA, unsigned int const numberB) noexcept { numberA.shiftRight((unsigned long) numberB); return numberA; }
                inline static BigUnsignedInteger<radix>& shiftRight(BigUnsignedInteger<radix>&& numberA, unsigned long const numberB) noexcept { numberA.shiftRight(numberB); return numberA; }
                inline static BigUnsignedInteger<radix>& shiftRight(BigUnsignedInteger<radix>&& numberA, unsigned short const numberB) noexcept { numberA.shiftRight((unsigned long) numberB); return numberA; }
                inline static BigUnsignedInteger<radix>& shiftRight(BigUnsignedInteger<radix>&& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { numberA.shiftRight(numberB); return numberA; }

                inline BigUnsignedInteger<radix>& subtract(unsigned int const number) noexcept { return BigUnsignedInteger::subtract((unsigned long) number); }
                inline BigUnsignedInteger<radix>& subtract(unsigned long const number) noexcept { if (number == 1uL) BigUnsignedInteger::decrement(); else BigUnsignedInteger::subtract(BigUnsignedInteger<radix> {number}); return *this; }
                inline BigUnsignedInteger<radix>& subtract(unsigned short const number) noexcept { return BigUnsignedInteger::subtract((unsigned long) number); }
                BigUnsignedInteger<radix>& subtract(BigUnsignedInteger<radix> const&) noexcept;
                inline static BigUnsignedInteger<radix> const subtract(BigUnsignedInteger<radix> const& numberA, unsigned int const numberB) noexcept { return BigUnsignedInteger::subtract(numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix> const subtract(BigUnsignedInteger<radix> const& numberA, unsigned long const numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.subtract(numberB); return evaluation; }
                inline static BigUnsignedInteger<radix> const subtract(BigUnsignedInteger<radix> const& numberA, unsigned short const numberB) noexcept { return BigUnsignedInteger::subtract(numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix> const subtract(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { BigUnsignedInteger<radix> evaluation {numberA}; evaluation.subtract(numberB); return evaluation; }
                inline static BigUnsignedInteger<radix>& subtract(BigUnsignedInteger<radix>&& numberA, unsigned int const numberB) noexcept { return BigUnsignedInteger::subtract((BigUnsignedInteger<radix>&&) numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix>& subtract(BigUnsignedInteger<radix>&& numberA, unsigned long const numberB) noexcept { numberA.subtract(numberB); return numberA; }
                inline static BigUnsignedInteger<radix>& subtract(BigUnsignedInteger<radix>&& numberA, unsigned short const numberB) noexcept { return BigUnsignedInteger::subtract((BigUnsignedInteger<radix>&&) numberA, (unsigned long) numberB); }
                inline static BigUnsignedInteger<radix>& subtract(BigUnsignedInteger<radix>&& numberA, BigUnsignedInteger<radix> const& numberB) noexcept { numberA.subtract(numberB); return numberA; }

                template <size_t base> constexpr static BigUnsignedInteger<base> const toBase(BigUnsignedInteger<radix> const&) noexcept;
                constexpr static primitive toInteger(BigUnsignedInteger<radix> const&);
                char const* toString(void) const noexcept;

                constexpr inline void zero(void) noexcept { if (this -> length) { this -> length = 0u; ::free(this -> value); this -> value = NULL; } }

            // [Operator] > ...
            inline BigUnsignedInteger<radix> const operator +(void) const& noexcept { return BigUnsignedInteger<radix> {*this}; }
            inline BigUnsignedInteger<radix>& operator +(void) const&& noexcept { return *this; }
            inline BigUnsignedInteger<radix> const operator +(BigUnsignedInteger<radix> const& number) const& noexcept { return BigUnsignedInteger::add(*this, number); }
            inline BigUnsignedInteger<radix>& operator +(BigUnsignedInteger<radix> const& number)&& noexcept { return BigUnsignedInteger::add(number); }
            inline BigSignedInteger<radix> const operator -(void) const noexcept;
            inline BigUnsignedInteger<radix> const operator -(unsigned int const number) const& noexcept { return BigUnsignedInteger::operator -((unsigned long) number); }
            inline BigUnsignedInteger<radix> const operator -(unsigned long const number) const& noexcept { return BigUnsignedInteger::subtract(*this, number); }
            inline BigUnsignedInteger<radix> const operator -(unsigned short const number) const& noexcept { return BigUnsignedInteger::operator -((unsigned long) number); }
            inline BigUnsignedInteger<radix> const operator -(unsigned int const number)&& noexcept { return BigUnsignedInteger::subtract((unsigned long) number); }
            inline BigUnsignedInteger<radix> const operator -(unsigned long const number)&& noexcept { return BigUnsignedInteger::subtract(number); }
            inline BigUnsignedInteger<radix> const operator -(unsigned short const number)&& noexcept { return BigUnsignedInteger::subtract((unsigned long) number); }
            inline BigUnsignedInteger<radix> const operator -(BigUnsignedInteger<radix> const& number) const& noexcept { return BigUnsignedInteger::subtract(*this, number); }
            inline BigUnsignedInteger<radix>& operator -(BigUnsignedInteger<radix> const& number)&& noexcept { return BigUnsignedInteger::subtract(number); }
            inline BigUnsignedInteger<radix> const operator *(BigUnsignedInteger<radix> const& number) const& noexcept { return BigUnsignedInteger::multiply(*this, number); }
            inline BigUnsignedInteger<radix>& operator *(BigUnsignedInteger<radix> const& number)&& noexcept { return BigUnsignedInteger::multiply(number); }
            inline BigUnsignedInteger<radix> const operator /(BigUnsignedInteger<radix> const&) const&;
            inline BigUnsignedInteger<radix>& operator /(BigUnsignedInteger<radix> const&)&&;
            inline BigUnsignedInteger<radix> const operator %(unsigned int const number) const& { return BigUnsignedInteger::operator %((unsigned long) number); }
            inline BigUnsignedInteger<radix> const operator %(unsigned long const number) const& { return BigUnsignedInteger::modulo(*this, number); }
            inline BigUnsignedInteger<radix> const operator %(unsigned short const number) const& { return BigUnsignedInteger::operator %((unsigned long) number); }
            inline BigUnsignedInteger<radix> const operator %(BigUnsignedInteger<radix> const&) const&;
            inline BigUnsignedInteger<radix>& operator %(unsigned int const number)&& { return BigUnsignedInteger::operator %((unsigned long) number); }
            inline BigUnsignedInteger<radix>& operator %(unsigned long const number)&& { return BigUnsignedInteger::modulo(number); }
            inline BigUnsignedInteger<radix>& operator %(unsigned short const number)&& { return BigUnsignedInteger::operator %((unsigned long) number); }
            inline BigUnsignedInteger<radix>& operator %(BigUnsignedInteger<radix> const&)&&;
            inline BigUnsignedInteger<radix> const operator <<(BigUnsignedInteger<radix> const& number) const& noexcept { return BigUnsignedInteger::shiftLeft(*this, number); }
            inline BigUnsignedInteger<radix>& operator <<(BigUnsignedInteger<radix> const& number)&& noexcept { return BigUnsignedInteger::shiftLeft(number); }
            inline BigUnsignedInteger<radix> const operator >>(BigUnsignedInteger<radix> const& number) const& noexcept { return BigUnsignedInteger::shiftRight(*this, number); }
            inline BigUnsignedInteger<radix>& operator >>(BigUnsignedInteger<radix> const& number)&& noexcept { return BigUnsignedInteger::shiftRight(number); }
            inline BigUnsignedInteger<radix>& operator =(BigFloat<radix> const& number) noexcept { BigUnsignedInteger::copy((BigFloat<radix> const&) number); return *this; }
            inline BigUnsignedInteger<radix>& operator =(BigFloat<radix>&& number) noexcept { BigUnsignedInteger::copy((BigFloat<radix>&&) number); return *this; }
            inline BigUnsignedInteger<radix>& operator =(BigSignedInteger<radix> const& number) noexcept { BigUnsignedInteger::copy((BigSignedInteger<radix> const&) number); return *this; }
            inline BigUnsignedInteger<radix>& operator =(BigSignedInteger<radix>&& number) noexcept { BigUnsignedInteger::copy((BigSignedInteger<radix>&&) number); return *this; }
            template <size_t base> inline BigUnsignedInteger<radix>& operator =(BigUnsignedInteger<base> const& number) noexcept { BigUnsignedInteger::copy((BigUnsignedInteger<base> const&) number); return *this; }
            template <size_t base> inline BigUnsignedInteger<radix>& operator =(BigUnsignedInteger<base>&& number) noexcept { BigUnsignedInteger::copy((BigUnsignedInteger<base>&&) number); return *this; }
            inline BigUnsignedInteger<radix>& operator +=(BigUnsignedInteger<radix> const& number) noexcept { return BigUnsignedInteger::add(number); }
            inline BigUnsignedInteger<radix>& operator -=(BigUnsignedInteger<radix> const& number) noexcept { return BigUnsignedInteger::subtract(number); }
            inline BigUnsignedInteger<radix>& operator *=(BigUnsignedInteger<radix> const&) noexcept;
            inline BigUnsignedInteger<radix>& operator /=(BigUnsignedInteger<radix> const&);
            inline BigUnsignedInteger<radix>& operator %=(unsigned int const number) { return BigUnsignedInteger::operator %=((unsigned long) number); }
            inline BigUnsignedInteger<radix>& operator %=(unsigned long const number) { return BigUnsignedInteger::modulo(number); }
            inline BigUnsignedInteger<radix>& operator %=(unsigned short const number) { return BigUnsignedInteger::operator %=((unsigned long) number); }
            inline BigUnsignedInteger<radix>& operator %=(BigUnsignedInteger<radix> const&);
            inline BigUnsignedInteger<radix>& operator <<=(BigUnsignedInteger<radix> const& number) noexcept { return BigUnsignedInteger::shiftLeft(number); }
            inline BigUnsignedInteger<radix>& operator >>=(BigUnsignedInteger<radix> const& number) noexcept { return BigUnsignedInteger::shiftRight(number); }
            inline bool operator ==(unsigned int const number) const noexcept { return BigUnsignedInteger::operator ==((unsigned long) number); }
            inline bool operator ==(unsigned long const number) const noexcept { return BigUnsignedInteger::isEqual(*this, number); }
            inline bool operator ==(unsigned short const number) const noexcept { return BigUnsignedInteger::operator ==((unsigned long) number); }
            inline bool operator ==(BigUnsignedInteger<radix> const& number) const noexcept { return BigUnsignedInteger::isEqual(*this, number); }
            inline bool operator !=(unsigned int const number) const noexcept { return BigUnsignedInteger::operator !=((unsigned long) number); }
            inline bool operator !=(unsigned long const number) const noexcept { return false == BigUnsignedInteger::operator ==(number); }
            inline bool operator !=(unsigned short const number) const noexcept { return BigUnsignedInteger::operator !=((unsigned long) number); }
            inline bool operator !=(BigUnsignedInteger<radix> const& number) const noexcept { return false == BigUnsignedInteger::operator ==(number); }
            inline bool operator <(BigUnsignedInteger<radix> const& number) const noexcept { return BigUnsignedInteger::isLesser(*this, number); }
            inline bool operator >(BigUnsignedInteger<radix> const& number) const noexcept { return BigUnsignedInteger::isGreater(*this, number); }
            inline bool operator <=(unsigned int const number) const noexcept { return BigUnsignedInteger::operator <=((unsigned long) number); }
            inline bool operator <=(unsigned long const number) const noexcept { return BigUnsignedInteger::operator ==(number) || BigUnsignedInteger::operator <(number); }
            inline bool operator <=(unsigned short const number) const noexcept { return BigUnsignedInteger::operator <=((unsigned long) number); }
            inline bool operator <=(BigUnsignedInteger<radix> const& number) const noexcept { return BigUnsignedInteger::operator ==(number) || BigUnsignedInteger::operator <(number); }
            inline bool operator >=(unsigned int const number) const noexcept { return BigUnsignedInteger::operator >=((unsigned long) number); }
            inline bool operator >=(unsigned long const number) const noexcept { return BigUnsignedInteger::operator ==(number) || BigUnsignedInteger::operator >(number); }
            inline bool operator >=(unsigned short const number) const noexcept { return BigUnsignedInteger::operator >=((unsigned long) number); }
            inline bool operator >=(BigUnsignedInteger<radix> const& number) const noexcept { return BigUnsignedInteger::operator ==(number) || BigUnsignedInteger::operator >(number); }
            inline BigUnsignedInteger<radix> const operator ++(int const)& noexcept { BigUnsignedInteger<radix> const evaluation {*this}; BigUnsignedInteger::operator ++(); return evaluation; }
            inline BigUnsignedInteger<radix>& operator ++(int const)&& noexcept { return BigUnsignedInteger::operator ++(); }
            inline BigUnsignedInteger<radix>& operator ++(void) noexcept { BigUnsignedInteger::increment(); return *this; }
            inline BigUnsignedInteger<radix> const operator --(int const)& noexcept { BigUnsignedInteger<radix> const evaluation {*this}; BigUnsignedInteger::operator --(); return evaluation; }
            inline BigUnsignedInteger<radix>& operator --(int const)&& noexcept { return BigUnsignedInteger::operator --(); }
            inline BigUnsignedInteger<radix>& operator --(void) noexcept { BigUnsignedInteger::decrement(); return *this; }
    };

    /* Big Signed Integer */
    template <size_t radix>
    class BigSignedInteger : BigUnsignedInteger<radix> { template <size_t> friend class BigFloat; template <size_t> friend class BigSignedInteger; template <size_t> friend class BigUnsignedInteger; friend int main(void);
        /* ... */
        typedef typename Digit::digit_t digit_t;
        typedef signed long primitive;

        // [...]
        private:
            // Definition > Signedness
            bool signedness;

        // [...]
        protected:
            // Definition > ...
            constexpr static primitive const PRIMITIVE_MAX = LONG_MAX;

            // Definition > Copy
            constexpr inline void copy(BigFloat<radix> const&);
            constexpr inline void copy(BigFloat<radix>&&);
            constexpr inline void copy(BigSignedInteger<radix> const& number) noexcept { BigUnsignedInteger<radix>::copy((BigSignedInteger<radix> const&) number); this -> signedness = number.signedness; }
            constexpr inline void copy(BigSignedInteger<radix>&& number) noexcept { BigUnsignedInteger<radix>::copy((BigSignedInteger<radix>&&) number); this -> signedness = number.signedness; }
            constexpr inline void copy(BigUnsignedInteger<radix> const&) noexcept;
            constexpr inline void copy(BigUnsignedInteger<radix>&&) noexcept;

        // [...]
        public:
            // [Constructor]
            constexpr inline BigSignedInteger(void) : BigUnsignedInteger<radix>(), signedness{false} {}
            constexpr inline BigSignedInteger(int const number) : BigUnsignedInteger<radix>(), signedness{false} { BigSignedInteger::copy(BigSignedInteger::fromInteger(number)); }
            constexpr inline BigSignedInteger(long const number) : BigUnsignedInteger<radix>(), signedness{false} {  BigSignedInteger::copy(BigSignedInteger::fromInteger(number)); }
            constexpr inline BigSignedInteger(short const number) : BigUnsignedInteger<radix>(), signedness{false} { BigSignedInteger::copy(BigSignedInteger::fromInteger(number)); }
            constexpr inline BigSignedInteger(BigFloat<radix> const&);
            constexpr inline BigSignedInteger(BigFloat<radix>&&);
            constexpr inline BigSignedInteger(BigSignedInteger<radix> const& number) : BigUnsignedInteger<radix>(), signedness{number.signedness} { BigSignedInteger::copy((BigSignedInteger<radix> const&) number); }
            constexpr inline BigSignedInteger(BigSignedInteger<radix>&& number) : BigUnsignedInteger<radix>(), signedness{number.signedness} { BigSignedInteger::copy((BigSignedInteger<radix>&&) number); }
            constexpr inline BigSignedInteger(BigUnsignedInteger<radix> const&);
            constexpr inline BigSignedInteger(BigUnsignedInteger<radix>&&);

            // Definition > ...
                // [Conditional]
                void isEqual(...) const noexcept;
                void isLesser(...) const noexcept;
                void isGreater(...) const noexcept;

                bool isNegative(void) const noexcept;
                inline static bool isNegative(BigSignedInteger<radix> const& number) noexcept { return number.isNegative(); }
                inline static bool isNegative(BigSignedInteger<radix>&& number) noexcept { return BigSignedInteger::isNegative(number); }

                bool isPositive(void) const noexcept;
                inline static bool isPositive(BigSignedInteger<radix> const& number) noexcept { return number.isPositive(); }
                inline static bool isPositive(BigSignedInteger<radix>&& number) noexcept { return BigSignedInteger::isPositive(number); }

                // [Operational]
                void add(...) const noexcept;
                void decrement(...) const noexcept;
                void divide(...) const noexcept;
                void exponentiate(...) const noexcept;

                constexpr inline static BigSignedInteger<radix> const fromInteger(int const number) noexcept { return BigSignedInteger::fromInteger((long) number); }
                constexpr static BigSignedInteger<radix> const fromInteger(long const) noexcept;
                constexpr inline static BigSignedInteger<radix> const fromInteger(short const number) noexcept { return BigSignedInteger::fromInteger((long) number); }

                void increment(...) const noexcept;
                void logarithmize(...) const noexcept;
                void multiply(...) const noexcept;

                BigSignedInteger<radix>& sign(void) noexcept;
                inline static BigSignedInteger<radix>& sign(BigSignedInteger<radix>& number) noexcept { return number.sign(); }
                inline static BigSignedInteger<radix>& sign(BigSignedInteger<radix>&& number) noexcept { return BigSignedInteger::sign(number); }

                void subtract(...) const noexcept;
                static void toInteger(...) noexcept;

                char const* toString(void) const noexcept;

                BigSignedInteger<radix>& unsign(void) noexcept;
                inline static BigSignedInteger<radix>& unsign(BigSignedInteger<radix>& number) noexcept { return number.unsign(); }
                inline static BigSignedInteger<radix>& unsign(BigSignedInteger<radix>&& number) noexcept { return BigSignedInteger::unsign(number); }

                constexpr inline void zero(void) noexcept { BigUnsignedInteger<radix>::zero(); BigSignedInteger::unsign(); }

            // [Operator] > ...
            inline BigSignedInteger<radix> const operator -(void) const noexcept { BigSignedInteger<radix> evaluation {*this}; BigSignedInteger::sign(evaluation); return evaluation; }
    };

    /* Big Float */
    template <size_t radix>
    class BigFloat : BigSignedInteger<radix> { template <size_t> friend class BigFloat; template <size_t> friend class BigSignedInteger; template <size_t> friend class BigUnsignedInteger; friend int main(void);
        /* ... */
        typedef typename Digit::digit_t digit_t;
        typedef long double primitive;

        // [...]
        private:
            // Definition > [(Characteristics, Mantissa) (Length), ]State
            size_t mantissaLength;
            enum BigFloatState {DENORMALIZED, INFINITE, SAFE, UNCOMPUTABLE} state;

        // [...]
        protected:
            // Definition > (Infinity, Not-A-Number, ...)
            static BigFloat<radix> const Infinity;
            static BigFloat<radix> const NaN;

            constexpr static primitive const PRIMITIVE_MAX = LDBL_MAX;

            // [Constructor]
            constexpr inline BigFloat(BigFloatState const state) : BigSignedInteger<radix>(), state{state} {}

            // Definition > Copy
            constexpr inline void copy(BigFloat<radix> const& number) noexcept { if (&number != this && BigFloat::SAFE == (this -> state = number.state)) { BigFloat::allocate(this -> setCharacteristicsLength(number.getCharacteristicsLength()) + this -> setMantissaLength(number.getMantissaLength())); this -> signedness = number.signedness; ::memcpy(this -> value, number.value, (this -> getCharacteristicsLength() + this -> getMantissaLength()) * sizeof(Digit)); } }
            constexpr inline void copy(BigFloat<radix>&& number) noexcept { if (BigFloat::SAFE == (this -> state = number.state)) { this -> setCharacteristicsLength(number.getCharacteristicsLength()); this -> setMantissaLength(number.getMantissaLength()); number.setCharacteristicsLength(0u); number.setMantissaLength(0u); this -> signedness = number.signedness; ::free(this -> value); this -> value = number.value; } }
            constexpr inline void copy(BigSignedInteger<radix> const&) noexcept;
            constexpr inline void copy(BigSignedInteger<radix>&&) noexcept;
            constexpr inline void copy(BigUnsignedInteger<radix> const&) noexcept;
            constexpr inline void copy(BigUnsignedInteger<radix>&&) noexcept;

            // Function > ... (Characteristics, Mantissa) ...
            void characteristicsIsEqual(...) const noexcept;
            void mantissaIsEqual(...) const noexcept;

            constexpr inline size_t& decrementCharacteristicsLength(void) noexcept { return --((size_t&) BigFloat::getCharacteristicsLength()); }
            constexpr inline size_t& decrementMantissaLength(void) noexcept { return --((size_t&) BigFloat::getMantissaLength()); }

            constexpr inline Digit* const& getCharacteristics(void) const noexcept { return this -> value; }
            constexpr inline size_t const& getCharacteristicsLength(void) const noexcept { return this -> length; }
            constexpr inline Digit* getMantissa(void) const noexcept { return NULL == this -> value ? NULL : BigFloat::getCharacteristicsLength() + this -> value; }
            constexpr inline size_t const& getMantissaLength(void) const noexcept { return this -> mantissaLength; }

            constexpr inline bool hasSignificantCharacteristics(void) const noexcept { return this -> getCharacteristicsLength(); }
            constexpr inline bool hasSignificantMantissa(void) const noexcept { return this -> getMantissaLength(); }

            constexpr inline size_t& incrementCharacteristicsLength(void) noexcept { return ++((size_t&) BigFloat::getCharacteristicsLength()); }
            constexpr inline size_t& incrementMantissaLength(void) noexcept { return ++((size_t&) BigFloat::getMantissaLength()); }

            constexpr inline Digit*& setCharacteristics(Digit* const characteristics) noexcept { return (((Digit*&) BigFloat::getCharacteristics()) = characteristics); }
            constexpr inline size_t& setCharacteristicsLength(size_t const characteristicsLength) noexcept { return (((size_t&) BigFloat::getCharacteristicsLength()) = characteristicsLength); }
            constexpr inline Digit*& setMantissa(Digit* const mantissa) noexcept { return (BigFloat::getMantissa() = mantissa); }
            constexpr inline size_t& setMantissaLength(size_t const mantissaLength) noexcept { return (((size_t&) BigFloat::getMantissaLength()) = mantissaLength); }

        // [...]
        public:
            // [Constructor]
            constexpr inline BigFloat(void) : BigSignedInteger<radix>(), mantissaLength{0u}, state{BigFloat::SAFE} {}
            constexpr inline BigFloat(double const number) : BigSignedInteger<radix>(), mantissaLength{0u}, state{BigFloat::SAFE} { BigFloat::copy(BigFloat::fromNumber(number)); }
            constexpr inline BigFloat(float const number) : BigSignedInteger<radix>(), mantissaLength{0u}, state{BigFloat::SAFE} { BigFloat::copy(BigFloat::fromNumber(number)); }
            constexpr inline BigFloat(long double const number) : BigSignedInteger<radix>(), mantissaLength{0u}, state{BigFloat::SAFE} { BigFloat::copy(BigFloat::fromNumber(number)); }
            constexpr inline BigFloat(BigFloat<radix> const& number) : BigSignedInteger<radix>(), mantissaLength{0u}, state{BigFloat::SAFE} { BigFloat::copy((BigFloat<radix> const&) number); }
            constexpr inline BigFloat(BigFloat<radix>&& number) : BigSignedInteger<radix>(), mantissaLength{0u}, state{BigFloat::SAFE} { BigFloat::copy((BigFloat<radix>&&) number); }
            constexpr inline BigFloat(BigSignedInteger<radix> const&);
            constexpr inline BigFloat(BigSignedInteger<radix>&&);
            constexpr inline BigFloat(BigUnsignedInteger<radix> const&);
            constexpr inline BigFloat(BigUnsignedInteger<radix>&&);

            // Definition > ...
                // [Conditional]
                void isBaseFactor(...) const noexcept;

                bool isComputable(void) const noexcept;
                inline static bool isComputable(BigUnsignedInteger<radix> const& number) noexcept { return number.isComputable(); }

                void isEqual(...) const noexcept;

                bool isFinite(void) const noexcept;
                inline static bool isFinite(BigUnsignedInteger<radix> const& number) noexcept { return number.isFinite(); }

                bool isInfinite(void) const noexcept;
                inline static bool isInfinite(BigUnsignedInteger<radix> const& number) noexcept { return number.isInfinite(); }

                bool isInteger(void) const noexcept;
                inline static bool isInteger(BigUnsignedInteger<radix> const& number) noexcept { return number.isInteger(); }

                void isLesser(...) const noexcept;
                void isGreater(...) const noexcept;

                bool isNaN(void) const noexcept;
                inline static bool isNaN(BigUnsignedInteger<radix> const& number) noexcept { return number.isNaN(); }

                bool isNormal(void) const noexcept;
                inline static bool isNormal(BigUnsignedInteger<radix> const& number) noexcept { return number.isNormal(); }

                bool isSafe(void) const noexcept;
                inline static bool isSafe(BigUnsignedInteger<radix> const& number) noexcept { return number.isSafe(); }

                bool isSignificant(void) const noexcept;
                inline static bool isSignificant(BigUnsignedInteger<radix> const& number) noexcept { return number.isSignificant(); }

                bool isZero(void) const noexcept;
                inline static bool isZero(BigUnsignedInteger<radix> const& number) noexcept { return number.isZero(); }

                // [Operational]
                void add(...) const noexcept;
                void decrement(...) const noexcept;
                void divide(...) const noexcept;
                void exponentiate(...) const noexcept;
                inline static BigFloat<radix> const fromNumber(double const number) noexcept { return BigFloat::fromNumber((long double) number); }
                inline static BigFloat<radix> const fromNumber(float const number) noexcept { return BigFloat::fromNumber((long double) number); }
                static BigFloat<radix> const fromNumber(long double const) noexcept;
                void increment(...) const noexcept;
                void logarithmize(...) const noexcept;
                void modulo(...) const noexcept;
                void multiply(...) const noexcept;
                void shftLeft(...) const noexcept;
                void shiftRight(...) const noexcept;

                inline BigFloat<radix>& sign(void) noexcept { BigSignedInteger<radix>::sign(); return *this; }
                inline static BigFloat<radix>& sign(BigFloat<radix>& number) noexcept { return number.sign(); }
                inline static BigFloat<radix>& sign(BigFloat<radix>&& number) noexcept { return BigFloat::sign(number); }

                void subtract(...) const noexcept;
                static void toNumber(...) noexcept;

                char const* toString(void) const noexcept;

                constexpr inline BigFloat<radix>& truncate(void) noexcept;
                inline static BigFloat<radix>& truncate(BigFloat<radix>& number) noexcept { return number.truncate(); }
                inline static BigFloat<radix>& truncate(BigFloat<radix>&& number) noexcept { return BigFloat::truncate(number); }

                inline BigFloat<radix>& unsign(void) noexcept { BigSignedInteger<radix>::unsign(); return *this; }
                inline static BigFloat<radix>& unsign(BigFloat<radix>& number) noexcept { return number.unsign(); }
                inline static BigFloat<radix>& unsign(BigFloat<radix>&& number) noexcept { return BigFloat::unsign(number); }

                constexpr inline void zero(void) noexcept { if (this -> getCharacteristicsLength() || this -> getMantissaLength()) { BigFloat::unsign(); this -> setCharacteristicsLength(0u); this -> setMantissaLength(0u); this -> state = BigFloat::SAFE; std::free(this -> value); this -> value = NULL; } }
    };

/* Modification > ... */
template <size_t radix> BigFloat<radix> const BigFloat<radix>::Infinity {BigFloatState::INFINITE};
template <size_t radix> BigFloat<radix> const BigFloat<radix>::NaN {BigFloatState::UNCOMPUTABLE};

/* Modification > Digit --- MINIFY (Lapys) */
    // Is ... --- MINIFY (Lapys)
    constexpr inline bool Digit::isEqual(Digit const digitA, Digit const digitB) noexcept { return digitA.value == digitB.value; }
    constexpr inline bool Digit::isGreater(Digit const digitA, Digit const digitB) noexcept { return digitA.value > digitB.value; }
    template <size_t radix> constexpr inline bool Digit::isHighestRank(Digit const digit) noexcept { return digit.value == radix - 1u; }
    constexpr inline bool Digit::isLesser(Digit const digitA, Digit const digitB) noexcept { return digitA.value < digitB.value; }
    template <size_t radix> constexpr inline bool Digit::isLowerRank(Digit const digit) noexcept { return digit.value < (radix / 2u); }
    template <size_t radix> constexpr inline bool Digit::isLowestRank(Digit const digit) noexcept { return 0u == digit.value; }
    template <size_t radix> constexpr inline bool Digit::isMeanRank(Digit const digit) noexcept { return digit.value == radix / 2u || ((radix & 1u) && (digit.value == (radix / 2u) + 1u)); }
    template <size_t radix> constexpr inline bool Digit::isUpperRank(Digit const digit) noexcept { return digit.value > (radix / 2u) + (radix & 1u); }

    // ... --- MINIFY (Lapys)
    constexpr inline Digit::digit_t Digit::from(char const value) noexcept { switch (value) { case '0': return 0u; case '1': return 1u; case '2': return 2u; case '3': return 3u; case '4': return 4u; case '5': return 5u; case '6': return 6u; case '7': return 7u; case '8': return 8u; case '9': return 9u; case 'A': case 'a': return 10u; case 'B': case 'b': return 11u; case 'C': case 'c': return 12u; case 'D': case 'd': return 13u; case 'E': case 'e': return 14u; case 'F': case 'f': return 15u; case 'G': case 'g': return 16u; case 'H': case 'h': return 17u; case 'I': case 'i': return 18u; case 'J': case 'j': return 19u; case 'K': case 'k': return 20u; case 'L': case 'l': return 21u; case 'M': case 'm': return 22u; case 'N': case 'n': return 23u; case 'O': case 'o': return 24u; case 'P': case 'p': return 25u; case 'Q': case 'q': return 26u; case 'R': case 'r': return 27u; case 'S': case 's': return 28u; case 'T': case 't': return 29u; case 'U': case 'u': return 30u; case 'V': case 'v': return 31u; case 'W': case 'w': return 32u; case 'X': case 'x': return 33u; case 'Y': case 'y': return 34u; case 'Z': case 'z': return 35u; } return digit_t(); }
    constexpr inline char Digit::to(digit_t const value) noexcept { switch (value) { case 0u: return '0'; break; case 1u: return '1'; break; case 2u: return '2'; break; case 3u: return '3'; break; case 4u: return '4'; break; case 5u: return '5'; break; case 6u: return '6'; break; case 7u: return '7'; break; case 8u: return '8'; break; case 9u: return '9'; break; case 10u: return 'A'; break; case 11u: return 'B'; break; case 12u: return 'C'; break; case 13u: return 'D'; break; case 14u: return 'E'; break; case 15u: return 'F'; break; case 16u: return 'G'; break; case 17u: return 'H'; break; case 18u: return 'I'; break; case 19u: return 'J'; break; case 20u: return 'K'; break; case 21u: return 'L'; break; case 22u: return 'M'; break; case 23u: return 'N'; break; case 24u: return 'O'; break; case 25u: return 'P'; break; case 26u: return 'Q'; break; case 27u: return 'R'; break; case 28u: return 'S'; break; case 29u: return 'T'; break; case 30u: return 'U'; break; case 31u: return 'V'; break; case 32u: return 'W'; break; case 33u: return 'X'; break; case 34u: return 'Y'; break; case 35u: return 'Z'; break; } return '\0'; }

    template <size_t radix> inline Digit const* Digit::add(Digit const digitA, Digit const digitB) noexcept { static Digit evaluation[2] {0}; if (Digit::isLowestRank<radix>(digitA)) { *evaluation = 0u; *(evaluation + 1) = digitB; } else if (Digit::isLowestRank<radix>(digitB)) { *evaluation = 0u; *(evaluation + 1) = digitA; } else if (Digit::isMeanRank<radix>(digitA) && Digit::isMeanRank<radix>(digitB)) { *evaluation = 1u; *(evaluation + 1) = 0u; } else if (Digit::isUpperRank<radix>(digitA)) { if (radix - digitA > digitB) { *evaluation = 0u; *(evaluation + 1) = digitA + digitB; } else { *evaluation = 1u; *(evaluation + 1) = digitB - (radix - digitA); } } else if (Digit::isUpperRank<radix>(digitB)) { if (radix - digitB > digitA) { *evaluation = 0u; *(evaluation + 1) = digitA + digitB; } else { *evaluation = 1u; *(evaluation + 1) = digitA - (radix - digitB); } } else { *evaluation = 0u; *(evaluation + 1) = digitA + digitB; } return &*evaluation; }
    template <size_t radix> inline Digit const* Digit::decrement(Digit const digit) noexcept { static Digit evaluation[2] {0}; if (Digit::isLowestRank<radix>(digit)) { *evaluation = 1u; *(evaluation + 1) = 1u; } else { *evaluation = 0u; *(evaluation + 1) = digit - 1u; } return &*evaluation; }
    template <size_t radix> inline Digit const* Digit::increment(Digit const digit) noexcept { static Digit evaluation[2] {0}; if (Digit::isHighestRank<radix>(digit)) { *evaluation = 1u; *(evaluation + 1) = 0u; } else { *evaluation = 0u; *(evaluation + 1) = digit + 1u; } return &*evaluation; }
    template <size_t radix> inline Digit const* Digit::multiply(Digit const digitA, Digit const digitB) noexcept { static Digit evaluation[2] {0}; ::memset(evaluation, 0u, sizeof(evaluation)); for (digit_t iterator = digitB.value; false == Digit::isLowestRank<radix>(iterator); --iterator) for (digit_t subiterator = digitA.value; false == Digit::isLowestRank<radix>(subiterator); --subiterator) { if (Digit::isHighestRank<radix>(*(evaluation + 1))) { ++*evaluation; *(evaluation + 1) = 0u; } else ++*(evaluation + 1); } return &*evaluation; }
    template <size_t radix> inline Digit const* Digit::subtract(Digit const digitA, Digit const digitB) noexcept { static Digit evaluation[2] {0}; if (digitA == digitB) { *evaluation = 0u; *(evaluation + 1) = 0u; } else if (digitA < digitB) { *evaluation = 1u; *(evaluation + 1) = digitB - digitA; } else { *evaluation = 0u; *(evaluation + 1) = digitA - digitB; } return &*evaluation; }

    // To ...
    constexpr inline Digit::digit_t Digit::toNumber(Digit const digit) noexcept { return digit.value; }
    inline char const* Digit::toString(void) const noexcept { static char evaluation[20] {0}; if (this -> value) { char *iterator = evaluation, *subiterator = evaluation - 1; for (digit_t value = this -> value; value; value /= 10u) *iterator++ = *("0123456789" + (value % 10u)); *iterator = '\0'; while (--iterator > ++subiterator) { *iterator ^= *subiterator; *subiterator ^= *iterator; *iterator ^= *subiterator; } } else { *evaluation = '0'; *(evaluation + 1) = '\0'; } return &*evaluation; }

/* Modification */
    /* Big Float */
        // [Constructor] --- MINIFY (Lapys)
        template <size_t radix> constexpr inline BigFloat<radix>::BigFloat(BigSignedInteger<radix> const& number) : BigSignedInteger<radix>(), state{BigFloat::SAFE} { BigFloat::copy((BigSignedInteger<radix> const&) number); }
        template <size_t radix> constexpr inline BigFloat<radix>::BigFloat(BigSignedInteger<radix>&& number) : BigSignedInteger<radix>(), state{BigFloat::SAFE} { BigFloat::copy((BigSignedInteger<radix>&&) number); }
        template <size_t radix> constexpr inline BigFloat<radix>::BigFloat(BigUnsignedInteger<radix> const& number) : BigSignedInteger<radix>(), state{BigFloat::SAFE} { BigFloat::copy((BigUnsignedInteger<radix> const&) number); }
        template <size_t radix> constexpr inline BigFloat<radix>::BigFloat(BigUnsignedInteger<radix>&& number) : BigSignedInteger<radix>(), state{BigFloat::SAFE} { BigFloat::copy((BigUnsignedInteger<radix>&&) number); }

        // Copy --- MINIFY (Lapys)
        template <size_t radix> constexpr inline void BigFloat<radix>::copy(BigSignedInteger<radix> const& number) noexcept { BigSignedInteger<radix>::copy((BigSignedInteger<radix> const&) number); BigFloat::truncate(); this -> state = BigFloat::SAFE; }
        template <size_t radix> constexpr inline void BigFloat<radix>::copy(BigSignedInteger<radix>&& number) noexcept { BigSignedInteger<radix>::copy((BigSignedInteger<radix>&&) number); BigFloat::truncate(); this -> state = BigFloat::SAFE; }
        template <size_t radix> constexpr inline void BigFloat<radix>::copy(BigUnsignedInteger<radix> const& number) noexcept { BigUnsignedInteger<radix>::copy((BigUnsignedInteger<radix> const&) number); BigFloat::truncate(); BigFloat::unsign(); this -> state = BigFloat::SAFE; }
        template <size_t radix> constexpr inline void BigFloat<radix>::copy(BigUnsignedInteger<radix>&& number) noexcept { BigUnsignedInteger<radix>::copy((BigUnsignedInteger<radix>&&) number); BigFloat::truncate(); BigFloat::unsign(); this -> state = BigFloat::SAFE; }

        // From Number
        template <size_t radix>
        inline BigFloat<radix> const BigFloat<radix>::fromNumber(long double const number) noexcept {
            // Evaluation > Evaluation
            BigFloat<radix> evaluation;

            // Logic
            if (::isinf(number)) {
                // Update > Evaluation; Modification > Evaluation > State
                if (number < 0.00L) BigFloat::sign(evaluation);
                evaluation.state = BigFloat::INFINITE;
            }

            else if (::isnan(number))
                // Modification > Evaluation > State
                evaluation.state = BigFloat::DENORMALIZED;

            else if (number && false == ::isnormal(number))
                // Modification > Evaluation > State
                evaluation.state = BigFloat::DENORMALIZED;

            else if (number) {
                // Initialization > (Characteristics, Mantissa)
                long double characteristics, mantissa = ::modf(number < 0.00L ? -number : number, &characteristics);

                // ...; Logic > Update > Evaluation
                evaluation.allocate((characteristics ? LDBL_DIG : 0u) + (mantissa ? LDBL_MANT_DIG : 0u));
                if (number < 0.00L) BigFloat::sign(evaluation);

                // Logic
                if (characteristics) {
                    // Initialization > Iterator
                    Digit *iterator = evaluation.getCharacteristics();

                    // Loop
                    for (long double digit; characteristics && (evaluation.getCharacteristicsLength() ^ LDBL_DIG); *iterator++ = (digit_t) ::round(digit)) {
                        // Update > (Evaluation, ...)
                        digit = ::modf((characteristics /= 10.00L), &characteristics) * 10.00L;
                        evaluation.incrementCharacteristicsLength();
                    }

                    // Update > Iterator; Loop > ...
                    --iterator;
                    for (Digit *subiterator = evaluation.getCharacteristics(); iterator > subiterator; (--iterator, ++subiterator)) {
                        iterator -> value ^= subiterator -> value;
                        subiterator -> value ^= iterator -> value;
                        iterator -> value ^= subiterator -> value;
                    }
                }

                // Logic
                if (mantissa) {
                    // Initialization > Iterator
                    Digit *iterator = evaluation.getMantissa();

                    // Loop
                    for (long double digit; mantissa >= LDBL_EPSILON && (evaluation.getMantissaLength() ^ LDBL_MANT_DIG); *iterator++ = (digit_t) ::round(digit)) {
                        // Update > (Evaluation, ...)
                        evaluation.incrementMantissaLength();
                        mantissa = ::modf((mantissa *= 10.00L), &digit);
                    }
                }
            }

            // Return
            return evaluation;
        }

        // Is Computable
        template <size_t radix>
        inline bool BigFloat<radix>::isComputable(void) const noexcept { return BigFloat::UNCOMPUTABLE != this -> state; }

        // Is Finite
        template <size_t radix>
        inline bool BigFloat<radix>::isFinite(void) const noexcept { return BigFloat::INFINITE != this -> state; }

        // Is Infinite
        template <size_t radix>
        inline bool BigFloat<radix>::isInfinite(void) const noexcept { return BigFloat::INFINITE == this -> state; }

        // Is Integer
        template <size_t radix>
        inline bool BigFloat<radix>::isInteger(void) const noexcept { return 0u == this -> getMantissaLength(); }

        // Is Not-A-Number
        template <size_t radix>
        inline bool BigFloat<radix>::isNaN(void) const noexcept { return BigFloat::UNCOMPUTABLE == this -> state; }

        // Is Normal
        template <size_t radix>
        inline bool BigFloat<radix>::isNormal(void) const noexcept { return BigFloat::DENORMALIZED != this -> state; }

        // Is Safe
        template <size_t radix>
        inline bool BigFloat<radix>::isSafe(void) const noexcept { return BigFloat::SAFE == this -> state; }

        // Is Significant
        template <size_t radix>
        inline bool BigFloat<radix>::isSignificant(void) const noexcept { return this -> getCharacteristicsLength() || this -> getMantissaLength(); }

        // Is Zero
        template <size_t radix>
        inline bool BigFloat<radix>::isZero(void) const noexcept { return false == BigFloat::isSignificant(); }

        // To String
        template <size_t radix>
        inline char const* BigFloat<radix>::toString(void) const noexcept {
            // Evaluation > Evaluation
            char *evaluation;

            // Logic
            if (BigFloat::isInfinite()) {
                // Update > Evaluation
                evaluation = (char*) ::malloc(10u * sizeof(char));
                ::strncpy(evaluation, "-Infinity" + BigFloat::isPositive(), 9u + BigFloat::isNegative());
            }

            else if (BigFloat::isNaN()) {
                // Update > Evaluation
                evaluation = (char*) ::malloc(4u * sizeof(char));
                ::strncpy(evaluation, "NaN", 4u);
            }

            else if (false == BigFloat::isNormal()) {
                // Update > Evaluation
                evaluation = (char*) ::malloc(13u * sizeof(char));
                ::strncpy(evaluation, "Denormalized", 13u);
            }

            else {
                // Update > Evaluation
                evaluation = (char*) (BigFloat::isNegative() && (BigFloat::hasSignificantCharacteristics() || BigFloat::hasSignificantMantissa()) ? BigSignedInteger<radix>::toString() : BigUnsignedInteger<radix>::toString());

                // Logic
                if (BigFloat::hasSignificantMantissa()) {
                    // Initialization > (Length, Mantissa, Sub-Evaluation)
                    size_t length = ::strlen(evaluation);
                    BigUnsignedInteger<radix> mantissa;
                    char const *subevaluation;

                    // Modification > Mantissa > Length
                    mantissa.length = this -> getMantissaLength();
                    mantissa.value = this -> getMantissa();

                    // Update > (Evaluation, ...)
                    *(evaluation + length) = '.';
                    subevaluation = mantissa.toString();
                    evaluation = (char*) ::realloc(evaluation, (length + ::strlen(subevaluation) + 2u) * sizeof(char));
                    while ((*(evaluation + ++length) = *subevaluation++)) continue;
                    *(evaluation + length) = '\0';

                    // Deletion; ...
                    mantissa.value = NULL;
                    ::free((char*) subevaluation);
                }
            }

            // Return
            return &*evaluation;
        }

        // Truncate
        template <size_t radix>
        constexpr inline BigFloat<radix>& BigFloat<radix>::truncate(void) noexcept { this -> setMantissaLength(0u); return *this; }

    /* Big Signed Integer */
        // [Constructor] --- MINIFY (Lapys)
        template <size_t radix> constexpr inline BigSignedInteger<radix>::BigSignedInteger(BigFloat<radix> const& number) : BigUnsignedInteger<radix>(), signedness{false} { BigSignedInteger::copy((BigFloat<radix> const&) number); }
        template <size_t radix> constexpr inline BigSignedInteger<radix>::BigSignedInteger(BigFloat<radix>&& number) : BigUnsignedInteger<radix>(), signedness{false} { BigSignedInteger::copy((BigFloat<radix>&&) number); }
        template <size_t radix> constexpr inline BigSignedInteger<radix>::BigSignedInteger(BigUnsignedInteger<radix> const& number) : BigUnsignedInteger<radix>(), signedness{false} { BigSignedInteger::copy((BigUnsignedInteger<radix> const&) number); }
        template <size_t radix> constexpr inline BigSignedInteger<radix>::BigSignedInteger(BigUnsignedInteger<radix>&& number) : BigUnsignedInteger<radix>(), signedness{false} { BigSignedInteger::copy((BigUnsignedInteger<radix>&&) number); }

        // Copy --- MINIFY (Lapys)
        template <size_t radix> constexpr inline void BigSignedInteger<radix>::copy(BigFloat<radix> const& number) { if (BigFloat<radix>::isSafe(number)) BigSignedInteger::copy((BigSignedInteger<radix> const&) number); else throw std::invalid_argument("Invalid value for signed integer"); }
        template <size_t radix> constexpr inline void BigSignedInteger<radix>::copy(BigFloat<radix>&& number) { if (BigFloat<radix>::isSafe(number)) BigSignedInteger::copy((BigSignedInteger<radix>&&) number); else throw std::invalid_argument("Invalid value for signed integer"); }
        template <size_t radix> constexpr inline void BigSignedInteger<radix>::copy(BigUnsignedInteger<radix> const& number) noexcept { BigUnsignedInteger<radix>::copy((BigUnsignedInteger<radix> const&) number); BigSignedInteger::unsign(); }
        template <size_t radix> constexpr inline void BigSignedInteger<radix>::copy(BigUnsignedInteger<radix>&& number) noexcept { BigUnsignedInteger<radix>::copy((BigUnsignedInteger<radix>&&) number); BigSignedInteger::unsign(); }

        // From Integer
        template <size_t radix>
        constexpr inline BigSignedInteger<radix> const BigSignedInteger<radix>::fromInteger(long const number) noexcept {
            // Return
            return number < 0L ?
                -BigSignedInteger<radix>{BigUnsignedInteger<radix>::fromInteger((unsigned long) -number)} :
                BigSignedInteger<radix>{BigUnsignedInteger<radix>::fromInteger((unsigned long) number)};
        }

        // Is Negative
        template <size_t radix>
        inline bool BigSignedInteger<radix>::isNegative(void) const noexcept { return this -> signedness; }

        // Is Positive
        template <size_t radix>
        inline bool BigSignedInteger<radix>::isPositive(void) const noexcept { return false == this -> signedness; }

        // Sign
        template <size_t radix>
        inline BigSignedInteger<radix>& BigSignedInteger<radix>::sign(void) noexcept { this -> signedness = !(this -> signedness); return *this; }

        // To String
        template <size_t radix>
        inline char const* BigSignedInteger<radix>::toString(void) const noexcept {
            // Evaluation > Evaluation
            char *evaluation = (char*) BigUnsignedInteger<radix>::toString();

            // Logic
            if (BigSignedInteger::isNegative()) {
                // Constant > Length
                size_t const length = ::strlen(evaluation);

                // Update > Evaluation
                evaluation = (char*) ::realloc(evaluation, (length + 2u) * sizeof(char));
                ::memmove(evaluation + 1, evaluation, (length + 1u) * sizeof(char));
                *evaluation = '-';
            }

            // Return
            return &*evaluation;
        }

        // Unsign
        template <size_t radix>
        inline BigSignedInteger<radix>& BigSignedInteger<radix>::unsign(void) noexcept { this -> signedness = false; return *this; }

    /* Big Unsigned Integer */
        // [Constructor] --- MINIFY (Lapys)
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>::BigUnsignedInteger(BigFloat<radix> const& number) : length{0u}, value{NULL} { BigUnsignedInteger::copy(number); }
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>::BigUnsignedInteger(BigFloat<radix>&& number) : length{0u}, value{NULL} { BigUnsignedInteger::copy((BigFloat<radix>&&) number); }
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>::BigUnsignedInteger(BigSignedInteger<radix> const& number) : length{0u}, value{NULL} { BigUnsignedInteger::copy(number); }
        template <size_t radix> constexpr inline BigUnsignedInteger<radix>::BigUnsignedInteger(BigSignedInteger<radix>&& number) : length{0u}, value{NULL} { BigUnsignedInteger::copy((BigSignedInteger<radix>&&) number); }

        // Add
        template <size_t radix>
        inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::add(BigUnsignedInteger<radix> const& number) noexcept {
            // Logic
            if (BigUnsignedInteger::isZero())
                // ...
                BigUnsignedInteger::copy(number);

            else if (BigUnsignedInteger::isEqual(1uL)) {
                // ...
                BigUnsignedInteger::copy(number);
                BigUnsignedInteger::increment();
            }

            else if (BigUnsignedInteger::isEqual(number, 1uL))
                // ...
                BigUnsignedInteger::increment();

            else if (BigUnsignedInteger::isSignificant(number)) {
                // Initialization > Carry
                bool carry = false;

                // Logic
                if (this -> length < number.length) {
                    // ...
                    BigUnsignedInteger::allocate(number.length);

                    // Modification > Target > (Length, Value)
                    ::memmove(this -> value + (number.length - this -> length), this -> value, this -> length * sizeof(Digit));
                    ::memset(this -> value, 0u, (number.length - this -> length) * sizeof(Digit));
                    this -> length = number.length;
                }

                // Loop
                for (size_t iterator = 0u, length = this -> length; iterator ^ length; ++iterator) {
                    // Initialization > (Digit, Evaluation)
                    Digit *digit = this -> value + (this -> length - iterator - 1u);
                    Digit *evaluation = (Digit*) Digit::add<radix>(digit -> value, iterator < number.length ? (number.value + (number.length - iterator - 1u)) -> value : 0u);

                    // Logic --- NOTE (Lapys) -> Update the digit-by-digit addition result with the carry.
                    if (carry) {
                        // Logic
                        if (Digit::isEqual(*evaluation, 0u)) {
                            // Constant > Sub-Evaluation
                            Digit const * const subevaluation = Digit::increment<radix>(*(evaluation + 1));

                            // Logic > Update > Evaluation
                            if (0u == *subevaluation) evaluation = (Digit*) subevaluation;
                            else ::memcpy(evaluation, subevaluation, 2u * sizeof(Digit));
                        }

                        else
                            // Update > Evaluation
                            *(evaluation + 1) = *(Digit::increment<radix>(*(evaluation + 1)) + 1);

                        // Update > Carry
                        carry = false;
                    }

                    // (Logic >)Update > ...
                    if (Digit::isEqual(*evaluation, 1u)) carry = true;
                    *digit = *(evaluation + 1);
                }

                // Logic
                if (carry) {
                    // ...; Modification > Target > (Length, Value)
                    BigUnsignedInteger::allocate(++(this -> length));

                    ::memmove(this -> value + 1, this -> value, (this -> length - 1u) * sizeof(Digit));
                    *(this -> value) = 1u;
                }
            }

            // Return
            return *this;
        }

        // Copy --- MINIFY (Lapys)
        template <size_t radix> constexpr inline void BigUnsignedInteger<radix>::copy(BigFloat<radix> const& number) { if (BigFloat<radix>::isSafe(number)) BigUnsignedInteger::copy((BigUnsignedInteger<radix> const&) number); else throw std::invalid_argument("Invalid value for unsigned integer"); }
        template <size_t radix> constexpr inline void BigUnsignedInteger<radix>::copy(BigFloat<radix>&& number) { if (BigFloat<radix>::isSafe(number)) BigUnsignedInteger::copy((BigUnsignedInteger<radix>&&) number); else throw std::invalid_argument("Invalid value for unsigned integer"); }
        template <size_t radix> constexpr inline void BigUnsignedInteger<radix>::copy(BigSignedInteger<radix> const& number) noexcept { BigUnsignedInteger::copy((BigUnsignedInteger<radix> const&) number); }
        template <size_t radix> constexpr inline void BigUnsignedInteger<radix>::copy(BigSignedInteger<radix>&& number) noexcept { BigUnsignedInteger::copy((BigUnsignedInteger<radix>&&) number); }

        // Decrement
        template <size_t radix>
        inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::decrement(void) noexcept {
            // Logic
            if (BigUnsignedInteger::isSignificant()) {
                // Initialization > Iterator
                Digit *iterator;

                // Loop > Update > Iterator
                for (iterator = this -> value + (this -> length - 1u); Digit::isLowestRank<radix>(*iterator); --iterator)
                *iterator = radix - 1u;

                // Logic
                if (Digit::isEqual(*iterator, 1u)) {
                    // Logic > ...
                    if (iterator == this -> value) ::memmove(this -> value, this -> value + 1, --(this -> length) * sizeof(char));
                    else BigUnsignedInteger::zero();
                }

                else
                    // ...
                    --*iterator;
            }

            // Return
            return *this;
        }

        // Exponentiate --- CHECKPOINT (Lapys)
        template <size_t radix>
        BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::exponentiate(BigUnsignedInteger<radix> const& number) noexcept {
            // ...
            (void) number;
            // function decompose(number) {
            //     var iterator = 1;
            //     var precision = 1e7;
            //     var sum = 0;
            //     var summand;

            //     number = Math.abs(number);
            //     number = number - Number.parseInt(number);

            //     console.clear();
            //     console.group("[number]:", number);

            //     while (sum < number) {
            //         summand = iterator;
            //         while (
            //             summand < precision &&
            //             (1 / summand > number || sum + (1 / summand) > number)
            //         ) ++summand;
            //         if (iterator == summand) break;
            //         iterator = summand;
            //         sum += 1 / summand;

            //         console.log("[summand]:", iterator);
            //     }

            //     console.groupEnd();
            //     console.log("[sum]:", sum)
            // }

            // function pow(base, exponent) {
            //     var evaluation;

            //     if (exponent < 0)
            //         evaluation = 1 / pow(base, -exponent);

            //     else if (Math.abs(exponent) != exponent) {
            //         var exponentCharacteristics = Number.parseInt(exponent);
            //         var exponentMantissa = exponent - exponentCharacteristics;

            //         evaluation = pow(base, exponentCharacteristics);

            //         for (var rootExponent in decompose(exponentMantissa))
            //         evaluation *= root(base, rootExponent);
            //     }

            //     else {
            //         evaluation = base;

            //         for (var iterator = exponent; iterator ? --iterator : 0; )
            //         evaluation *= base
            //     }

            //     return evaluation
            // }

            // function root(base, exponent) {
            //     var baseFunction = function(number) { return pow(number, exponent) - base };
            //     var baseFunctionDerivative = function(number) { return exponent * pow(number, exponent - 1) };
            //     var evaluation = 1;
            //     var limit = 0.00000000000001;
            //     var precision = 0.0000001;
            //     var solutionFound = false;

            //     for (var iterator = 1, length = 20; iterator ^ length; ++iterator) {
            //         var approximation;
            //         var denominator = baseFunction(evaluation);
            //         var derivativeDenominator = baseFunctionDerivative(evaluation);

            //         if (Math.abs(derivativeDenominator) < limit) iterator = length - 1;
            //         else {
            //             approximation = evaluation - (denominator / derivativeDenominator);
            //             if (Math.abs(approximation - evaluation) <= precision) solutionFound = true;
            //             evaluation = approximation
            //         }
            //     }

            //     if (solutionFound) return evaluation;
            //     else return null
            // }


            // x0 = 1  # The initial guess
            // f(x) = x^2 - 2  # The function whose root we are trying to find
            // fprime(x) = 2 * x  # The derivative of the function
            // tolerance = 10^(-7)  # 7 digit accuracy is desired
            // epsilon = 10^(-14)  # Do not divide by a number smaller than this
            // maxIterations = 20  # Do not allow the iterations to continue indefinitely
            // solutionFound = false  # Have not converged to a solution yet

            // for i = 1:maxIterations
            //   y = f(x0)
            //   yprime = fprime(x0)

            //   if abs(yprime) < epsilon  # Stop if the denominator is too small
            //     break
            //   end

            //   global x1 = x0 - y/yprime  # Do Newton's computation

            //   if abs(x1 - x0) <= tolerance  # Stop when the result is within the desired tolerance
            //     global solutionFound = true
            //     break
            //   end

            //   global x0 = x1  # Update x0 to start the process again
            // end

            // if solutionFound
            //   println("Solution: ", x1)  # x1 is a solution within tolerance and maximum number of iterations
            // else
            //   println("Did not converge")  # Newton's method did not converge
            // end

            // Return
            return *this;
        }

        // From Integer
        template <size_t radix>
        constexpr inline BigUnsignedInteger<radix> const BigUnsignedInteger<radix>::fromInteger(unsigned long const number) noexcept {
            // Evaluation > Evaluation
            BigUnsignedInteger evaluation {};

            // Logic
            if (number) {
                // ...; Loop
                evaluation.allocate(64u + 1u);
                for (unsigned long index = 0uL, iterator = number; iterator; iterator /= radix) {
                    // Modification > Evaluation > Value
                    *(evaluation.value + index++) = iterator % radix;

                    // Logic
                    if (iterator < radix) {
                        // Modification > Evaluation > Length; ...
                        evaluation.length = index;
                        evaluation.allocate(evaluation.length);

                        // Loop > ... --- NOTE (Lapys) -> Reverse the value set.
                        for ((--index, iterator = 0uL); iterator < index; (--index, ++iterator)) {
                            (evaluation.value + index) -> value ^= (evaluation.value + iterator) -> value;
                            (evaluation.value + iterator) -> value ^= (evaluation.value + index) -> value;
                            (evaluation.value + index) -> value ^= (evaluation.value + iterator) -> value;
                        }

                        // Update > Iterator
                        iterator = 0uL;
                    }
                }
            }

            // Return
            return evaluation;
        }

        // Increment
        template <size_t radix>
        inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::increment(void) noexcept {
            // Logic
            if (BigUnsignedInteger::isZero()) {
                // Modification > Target > (Length, Value)
                BigUnsignedInteger::allocate((this -> length = 1u));
                *(this -> value) = 1u;
            }

            else {
                // Initialization > Iterator
                Digit *iterator;

                // Loop > Update > Iterator
                for (iterator = this -> value + (this -> length - 1u); iterator >= this -> value && Digit::isHighestRank<radix>(*iterator); --iterator)
                *iterator = 0u;

                // Logic
                if (iterator == this -> value - 1) {
                    // Modification > Target > (Length, Value)
                    BigUnsignedInteger::allocate(++(this -> length));

                    ::memmove(this -> value + 1, this -> value, (this -> length - 1u) * sizeof(Digit));
                    *(this -> value) = 1u;
                }

                else
                    // ...
                    ++*iterator;
            }

            // Return
            return *this;
        }

        // Is Base Factor --- NOTE (Lapys) -> Not multiplicative factors, but rather exponential factors (of the radix).
        template <size_t radix>
        inline bool BigUnsignedInteger<radix>::isBaseFactor(void) const noexcept {
            // Evaluation > Evaluation
            bool evaluation = true;

            // Update > Evaluation
            evaluation = this -> length > 1u && 1u == *(this -> value);

            // Logic > ...
            if (evaluation) {
                for (size_t iterator = 1u; evaluation && (iterator ^ (this -> length)); ++iterator)
                if (false == Digit::isLowestRank<radix>(*(this -> value + iterator))) evaluation = false;
            }

            // Return
            return evaluation;
        }

        // Is Big
        template <size_t radix>
        inline bool BigUnsignedInteger<radix>::isBig(void) const noexcept { static BigUnsignedInteger<radix> const maximum {PRIMITIVE_MAX}; return BigUnsignedInteger::isGreater(maximum); }

        // Is Equal
        template <size_t radix>
        inline bool BigUnsignedInteger<radix>::isEqual(BigUnsignedInteger<radix> const& numberA, unsigned long numberB) noexcept {
            // Evaluation > Evaluation
            bool evaluation = true;

            // Logic
            if (numberB && BigUnsignedInteger::isSignificant(numberA)) {
                // Logic
                if (numberB < 10u)
                    // Update > Evaluation
                    evaluation = numberA.length == 1u && evaluation == *numberA.value;

                else {
                    // Loop > Logic > Update > Evaluation
                    for (size_t iterator = 0u; evaluation && (iterator ^ numberA.length); (++iterator, numberB /= radix))
                    if (0u == numberB || false == Digit::isEqual(*(numberA.value + (numberA.length - iterator - 1u)), numberB % radix)) evaluation = false;

                    // Logic > Update > Evaluation
                    if (numberB) evaluation = false;
                }
            }

            else
                // Update > Evaluation
                evaluation = BigUnsignedInteger::isZero(numberA) && 0u == numberB;

            // Return
            return evaluation;
        }

        template <size_t radix>
        inline bool BigUnsignedInteger<radix>::isEqual(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept {
            // Evaluation > Evaluation
            bool evaluation = true;

            // Logic
            if (numberA.length == numberB.length) {
                // Logic
                if (numberA.length) {
                    // Loop > Logic > Update > Evaluation
                    for (size_t iterator = 0u; evaluation && (iterator ^ numberA.length); ++iterator)
                    if (false == Digit::isEqual(*(numberA.value + iterator), *(numberB.value + iterator)))
                    evaluation = false;
                }
            }

            else
                // Update > Evaluation
                evaluation = false;

            // Return
            return evaluation;
        }

        // Is Greater
        template <size_t radix>
        inline bool BigUnsignedInteger<radix>::isGreater(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept {
            // Evaluation > Evaluation
            bool evaluation = true;

            // Logic
            if (BigUnsignedInteger::isZero(numberA))
                // Update > Evaluation
                evaluation = false;

            else if (numberA.length < numberB.length)
                // Update > Evaluation
                evaluation = false;

            else if (numberA.length == numberB.length) {
                // Initialization > Pending
                bool pending = true;

                // Loop
                for (size_t iterator = 0u; pending && (iterator ^ numberA.length); ++iterator) {
                    // Logic > Update > ...
                    if (Digit::isGreater(*(numberA.value + iterator), *(numberB.value + iterator))) pending = false;
                    else if (Digit::isLesser(*(numberA.value + iterator), *(numberB.value + iterator))) { evaluation = false; pending = false; }
                }

                // Logic > Update > Evaluation
                if (pending) evaluation = false;
            }

            // Return
            return evaluation;
        }

        // Is Lesser
        template <size_t radix>
        inline bool BigUnsignedInteger<radix>::isLesser(BigUnsignedInteger<radix> const& numberA, BigUnsignedInteger<radix> const& numberB) noexcept {
            // Evaluation > Evaluation
            bool evaluation = true;

            // Logic
            if (BigUnsignedInteger::isZero(numberA))
                // Update > Evaluation
                evaluation = BigUnsignedInteger::isSignificant(numberB);

            else if (numberA.length > numberB.length)
                // Update > Evaluation
                evaluation = false;

            else if (numberA.length == numberB.length) {
                // Initialization > Pending
                bool pending = true;

                // Loop
                for (size_t iterator = 0u; pending && (iterator ^ numberA.length); ++iterator) {
                    // Logic > Update > ...
                    if (Digit::isLesser(*(numberA.value + iterator), *(numberB.value + iterator))) pending = false;
                    else if (Digit::isGreater(*(numberA.value + iterator), *(numberB.value + iterator))) { evaluation = false; pending = false; }
                }

                // Logic > Update > Evaluation
                if (pending) evaluation = false;
            }

            // Return
            return evaluation;
        }

        // Is Significant
        template <size_t radix>
        inline bool BigUnsignedInteger<radix>::isSignificant(void) const noexcept { return false == BigUnsignedInteger::isZero(); }

        // Is Zero
        template <size_t radix>
        inline bool BigUnsignedInteger<radix>::isZero(void) const noexcept { return 0u == this -> length; }

        // Modulo
        template <size_t radix>
        inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::modulo(unsigned long const number) {
            // Logic
            if (number) {
                // Initialization > Evaluation
                unsigned long evaluation = 0u;

                // Loop > Update > Evaluation
                for (size_t iterator = 0u; iterator ^ (this -> length); ++iterator)
                evaluation = ((evaluation * radix) + *(this -> value + iterator)) % number;

                // ...
                BigUnsignedInteger::copy(BigUnsignedInteger::fromInteger(evaluation));
            }

            else
                // Error
                throw std::domain_error("Division by zero");

            // Return
            return *this;
        }

        // Multiply
        template <size_t radix>
        BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::multiply(BigUnsignedInteger<radix> const& number) noexcept {
            // Logic
            if (BigUnsignedInteger::isSignificant() && false == BigUnsignedInteger::isEqual(number, 1uL)) {
                // Logic
                if (BigUnsignedInteger::isZero(number))
                    // ...
                    BigUnsignedInteger::zero();

                else if (BigUnsignedInteger::isEqual(1uL))
                    // ...
                    BigUnsignedInteger::copy(number);

                else if (BigUnsignedInteger::isBaseFactor()) {
                    // Constant > Length
                    size_t const length = this -> length;

                    // ...; Loop > ...
                    BigUnsignedInteger::copy(number);
                    BigUnsignedInteger::shiftLeft(length - 1u);
                }

                else if (BigUnsignedInteger::isBaseFactor(number))
                    // ...
                    BigUnsignedInteger::shiftLeft(number.length - 1u);

                else {
                    // Initialization > (Product ..., Sum)
                    BigUnsignedInteger<radix> product; Digit* productValue; // NOTE (Lapys) -> For proper de-allocation afterwards.
                    BigUnsignedInteger<radix> sum;

                    // Modification > Product > (Length, Value); ...
                    product.length = number.length + (this -> length > number.length ? this -> length : number.length) + 1u;
                    product.allocate(product.length);
                    productValue = product.value;
                    product.value += product.length;

                    // Loop > Logic --- NOTE (Lapys) -> Ignore multiplying by zeroes.
                    for (size_t iterator = 0u; iterator ^ number.length; ++iterator)
                    if (*(number.value + (number.length - iterator - 1u))) {
                        // Initialization > Carry
                        Digit carry = 0u;

                        // Loop --- NOTE (Lapys) -> There are potential redundancies in multiplying digits with `0` value.
                        for (size_t subiterator = 0u; subiterator ^ (this -> length); ++subiterator) {
                            // Initialization > Evaluation
                            Digit *evaluation = (Digit*) Digit::multiply<radix>(*(number.value + (number.length - iterator - 1u)), *(this -> value + (this -> length - subiterator - 1u)));

                            // Logic --- NOTE (Lapys) -> Add to the carry
                            if (carry) {
                                // Initialization > Sub-Evaluation
                                Digit const *subevaluation = Digit::add<radix>(carry, *(evaluation + 1));

                                // Update > (Evaluation, ...)
                                *(evaluation + 1) = *(subevaluation + 1);
                                if (Digit::isEqual(*subevaluation, 1u)) ++*evaluation;

                                carry = 0u;
                            }

                            // Modification > Product > Value; ...
                            *product.value-- = *(evaluation + 1);
                            if (false == Digit::isEqual(*evaluation, 0u)) carry = *evaluation;
                        }

                        // Logic
                        if (carry) {
                            // Modification > Product > (Length, Value)
                            product.length = this -> length + 1u;
                            *product.value-- = carry;
                        }

                        else
                            // Modification > Product > Length
                            product.length = this -> length;

                        // Modification > Product > (Length, Value)
                        ++product.value;
                        ::memmove(product.value - iterator, product.value, product.length * sizeof(Digit)); product.value -= iterator;
                        ::memset(product.value + (product.length), 0u, iterator * sizeof(Digit)); product.length += iterator;

                        // Update > Sum; Modification > Product > Value
                        sum.add(product);
                        product.value += product.length - 1u;
                    }

                    // Modification > Product > Value; ...
                    product.value = productValue;
                    BigUnsignedInteger::copy(sum);
                }
            }

            // Return
            return *this;
        }

        // Shift Left
        template <size_t radix>
        inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::shiftLeft(void) noexcept {
            // Logic
            if (BigUnsignedInteger::isSignificant()) {
                // Modification > Target > (Length, Value)
                BigUnsignedInteger::allocate(++(this -> length));
                *(this -> value + (this -> length - 1u)) = 0u;
            }

            // Return
            return *this;
        }

        template <size_t radix>
        inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::shiftLeft(unsigned long number) noexcept {
            // Logic
            if (number && BigUnsignedInteger::isSignificant()) {
                // Modification > Target > (Length, Value)
                BigUnsignedInteger::allocate(this -> length + number);
                ::memset(this -> value + (this -> length), 0u, number * sizeof(Digit));
                this -> length += number;
            }

            // Return
            return *this;
        }

        template <size_t radix>
        inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::shiftLeft(BigUnsignedInteger<radix> const& number) noexcept {
            // Logic
            if (BigUnsignedInteger::isSignificant() && BigUnsignedInteger::isSignificant(number)) {
                // Logic
                if (BigUnsignedInteger::isBig(number)) {
                    // Initialization > Iterator
                    BigUnsignedInteger<radix> iterator {number};

                    // (Loop, Logic) > ...
                    while (BigUnsignedInteger::isBig(iterator)) { BigUnsignedInteger::shiftLeft((unsigned long) PRIMITIVE_MAX); iterator.subtract(PRIMITIVE_MAX); }
                    if (BigUnsignedInteger::isSignificant(iterator)) BigUnsignedInteger::shiftLeft(BigUnsignedInteger::toInteger(iterator));
                }

                else
                    // ...
                    BigUnsignedInteger::shiftLeft(BigUnsignedInteger::toInteger(number));
            }

            // Return
            return *this;
        }

        // Shift Right
        template <size_t radix>
        inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::shiftRight(void) noexcept { if (BigUnsignedInteger::isSignificant()) --(this -> length); return *this; }

        template <size_t radix>
        inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::shiftRight(unsigned long const number) noexcept {
            // Logic
            if (number && BigUnsignedInteger::isSignificant()) {
                // Logic > ...
                if (this -> length > number) this -> length -= number;
                else BigUnsignedInteger::zero();
            }

            // Return
            return *this;
        }

        template <size_t radix>
        inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::shiftRight(BigUnsignedInteger<radix> const& number) noexcept {
            // Logic
            if (BigUnsignedInteger::isSignificant() && BigUnsignedInteger::isSignificant(number)) {
                // Constant > Maximum Digit Count
                static BigUnsignedInteger<radix> const MAXIMUM_DIGIT_COUNT {SIZE_MAX};

                // Logic > ...
                if (BigUnsignedInteger::isGreater(number, MAXIMUM_DIGIT_COUNT)) BigUnsignedInteger::zero();
                else BigUnsignedInteger::shiftRight(BigUnsignedInteger::toInteger(number));
            }

            // Return
            return *this;
        }

        // Subtract
        template <size_t radix>
        inline BigUnsignedInteger<radix>& BigUnsignedInteger<radix>::subtract(BigUnsignedInteger<radix> const& number) noexcept {
            // Logic
            if (BigUnsignedInteger::isGreater(number)) {
                // Logic
                if (BigUnsignedInteger::isEqual(number, 1uL))
                    // ...
                    BigUnsignedInteger::decrement();

                else {
                    // Loop
                    for (size_t iterator = 0u; iterator ^ this -> length; ++iterator) {
                        // Initialization > (Digit (A, B), Evaluation)
                        Digit *digitA = this -> value + (this -> length - iterator - 1u);
                        Digit *digitB = iterator < number.length ? number.value + (number.length - iterator - 1u) : NULL;
                        Digit const *const evaluation = Digit::subtract<radix>(digitA -> value, NULL == digitB ? 0u : digitB -> value);

                        // Logic
                        if (Digit::isEqual(*evaluation, 1u)) {
                            // Update > Digit
                            *digitA = *(Digit::add<radix>(digitA -> value, *(Digit::increment<radix>(*(Digit::subtract<radix>(radix - 1u, NULL == digitB ? 0u : digitB -> value) + 1)) + 1)) + 1);

                            // Loop
                            for (size_t subiterator = iterator + 1u; subiterator ^ this -> length; ++subiterator) {
                                // Initialization > Sub-Evaluation
                                Digit const *subevaluation;

                                // Update > (Digit (A, B), Sub-Evaluation)
                                --digitA;
                                digitB = digitB < number.value ? NULL : digitB - 1;
                                subevaluation = Digit::decrement<radix>(*digitA);

                                // Logic > Update > (Digit A, ...)
                                if (Digit::isEqual(*subevaluation, 1u)) { ++iterator; *digitA = *(Digit::increment<radix>(*(Digit::subtract<radix>(radix - 1u, NULL == digitB ? 0u : digitB -> value) + 1)) + 1); } // Continue
                                else { *digitA = *(subevaluation + 1); subiterator = this -> length - 1u; } // Terminate
                            }
                        }

                        else
                            // Update > Digit A
                            *digitA = *(evaluation + 1);
                    }

                    // Logic > Modification > Target > Value
                    if (Digit::isLowestRank<radix>(*(this -> value)))
                    ::memmove(this -> value, this -> value + 1, --(this -> length) * sizeof(Digit));
                }
            }

            else
                // Deletion
                BigUnsignedInteger::zero();

            // Return
            return *this;
        }

        // To Base --- CHECKPOINT (Lapys)
        template <size_t radix>
        template <size_t base>
        constexpr inline BigUnsignedInteger<base> const BigUnsignedInteger<radix>::toBase(BigUnsignedInteger<radix> const& number) noexcept {
            // Evaluation > Evaluation
            BigUnsignedInteger<base> evaluation;

            // Logic
            if (BigUnsignedInteger::isSignificant(number)) {
                // Logic
                if (base == radix)
                    // Update > Evaluation
                    evaluation = number;

                else if (base > radix) {

                }

                else {
                    size_t count = 0u;
                    BigUnsignedInteger<radix> exponent {base};

                    while (BigUnsignedInteger::isLesser(exponent, number)) {
                        ++count;
                        exponent.multiply(base);
                    }

                    if (BigUnsignedInteger::isEqual(exponent, number)) {
                        evaluation.length = 1u;
                        *evaluation.value = 1u;

                        for (size_t iterator = 0u; count ^ iterator; ++iterator) evaluation.shiftLeft();
                    }

                    // 64, 78, 127 with ADD, MULTIPLY & SUBTRACT

                    // EXP
                    // 2 * 2 * 2 * 2 * 2 * 2 -> 64
                    // 2 * 2 * 2 * 2 * 2 * 2 * 2 -> 128

                    // MUL
                    // 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 -> 126
                    // 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 + 2 -> 128

                    // ADD
                    // 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 -> 127
                    // 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 -> 128
                }
            }

            // Return
            return evaluation;
        }

        // To Integer
        template <size_t radix>
        constexpr inline typename BigUnsignedInteger<radix>::primitive BigUnsignedInteger<radix>::toInteger(BigUnsignedInteger<radix> const& number) {
            // Initialization > (Evaluation, ...)
            BigUnsignedInteger<radix>::primitive evaluation = 0uL;
            BigUnsignedInteger<radix>::primitive exponent = 1uL;

            // Loop > Update > (Evaluation, ...)
            for (size_t iterator = 0u; iterator ^ number.length; ++iterator) {
                evaluation += exponent * Digit::toNumber(*(number.value + (number.length - iterator - 1u)));
                exponent *= radix;
            }

            // Return
            return evaluation;
        }

        // To String
        template <size_t radix>
        inline char const* BigUnsignedInteger<radix>::toString(void) const noexcept {
            // Evaluation > Evaluation
            char *evaluation;

            // Logic
            if (BigUnsignedInteger::isZero()) {
                // Update > Evaluation
                evaluation = (char*) ::malloc(2u * sizeof(char));
                *evaluation = '0'; *(evaluation + 1) = '\0';
            }

            else {
                // Initialization > (Delimit, Digit Length, Iterator)
                bool delimit = false; // NOTE (Lapys) -> Represent each digit not as hexadecimal/ decimal numeral symbols, but rather as their intrinsic value delimited by `[]` brackets.
                unsigned char digitLength = 1u;
                char *iterator;

                // Update > (Evaluation, Iterator)
                evaluation = (char*) ::malloc((this -> length + 1u) * sizeof(char));
                iterator = evaluation;

                // Loop
                for (size_t index = 0u; index ^ (this -> length); ) {
                    // Initialization > Sub-Evaluation
                    char *subevaluation;

                    // Logic
                    if (delimit) {
                        // Initialization > Sub-Iterator
                        char *subiterator;

                        // Update > (Sub-Evaluation, Sub-Iterator)
                        subevaluation = (char*) (this -> value + index) -> toString();
                        subiterator = subevaluation;

                        // Loop > Update > Sub-Iterator
                        while (*subiterator) ++subiterator;

                        // Logic
                        if ('\0' == subevaluation && ((unsigned char) (subiterator - subevaluation)) > digitLength) {
                            // Update > (..., Evaluation, ...)
                            digitLength = subiterator - subevaluation;
                            evaluation = (char*) ::realloc(evaluation, ((this -> length + 1u) * (digitLength + 2u)) * sizeof(char));
                            index = 0u;
                            iterator = evaluation;
                        }

                        else {
                            // (Loop > )Update > ...
                            ++index;
                            *iterator++ = '['; while (subevaluation != subiterator) *iterator++ = *subevaluation++; *iterator++ = ']';
                        }
                    }

                    else {
                        // Constant > Character
                        char const character = Digit::to((this -> value + index) -> value);

                        // Update > Sub-Evaluation
                        subevaluation = (char*) &character;

                        // Logic
                        if ('\0' == *subevaluation) {
                            // Initialization > Sub-Iterator
                            char *subiterator;

                            // Update > (Sub-Evaluation, Sub-Iterator)
                            subevaluation = (char*) (this -> value + index) -> toString();
                            subiterator = subevaluation;

                            // Loop > Update > Digit Length
                            while (*(digitLength + subiterator)) ++digitLength;

                            // Update > (..., Evaluation, ...)
                            delimit = true;
                            evaluation = (char*) ::realloc(evaluation, ((this -> length + 1u) * (digitLength + 2u)) * sizeof(char));
                            index = 0u;
                            iterator = evaluation;
                        }

                        else {
                            // Update > ...
                            ++index;
                            *iterator++ = *subevaluation;
                        }
                    }
                }

                // Update > ...
                *iterator = '\0';
            }

            // Return
            return &*evaluation;
        }

        // [Operator] > ... --- MINIFY (Lapys)
        template <size_t radix> inline BigSignedInteger<radix> const BigUnsignedInteger<radix>::operator -(void) const noexcept { BigSignedInteger<radix> evaluation {*this}; evaluation.sign(); return evaluation; }

/* Constant > (Infinity, Not-A-Number) */
template <size_t radix> BigFloat<radix> const& Infinity = BigFloat<radix>::Infinity;
template <size_t radix> BigFloat<radix> const& NaN = BigFloat<radix>::NaN;

/* Utilization > ... */
typedef Digit::digit_t digit_t;

/* Main */
int main(void) {
    /* [Initiate] ... */
    ::println("[PROGRAM INITIATED]");

    /* [Update] ... */ {
        ::println("[EVAL]: ", BigUnsignedInteger<10u>::toBase<2u>(BigUnsignedInteger<10u> {127u}).toString());
    }

    /* [Terminate] ... */
    ::printfl("[PROGRAM TERMINATED]");

    // Return
    return EXIT_SUCCESS;
}
