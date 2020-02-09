/* Import */
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library
#include <time.h> // Time

/* Class > Date */
class Date {
    // [...]
    private:
        // Initialization > (Day, Month, Year)
        unsigned char day : 5;
        unsigned char month : 4;
        struct digit { friend Date;
            // [...]
            public:
                // Definition > Value --- NOTE (Lapys) -> Meant to hold only 10 values, but bit fields may only specify exponents of 2 values.
                unsigned char value : 4;

                // [Constructor] --- MINIFY (Lapys)
                constexpr inline digit(const unsigned char argument) : value{} { switch (argument) { case '0': case 0u: this -> value = 0u; break; case '1': case 1u: this -> value = 1u; break; case '2': case 2u: this -> value = 2u; break; case '3': case 3u: this -> value = 3u; break; case '4': case 4u: this -> value = 4u; break; case '5': case 5u: this -> value = 5u; break; case '6': case 6u: this -> value = 6u; break; case '7': case 7u: this -> value = 7u; break; case '8': case 8u: this -> value = 8u; break; case '9': case 9u: this -> value = 9u; break; } }
                constexpr inline digit(void) : value{} {}

                // [Operator] > ([=], [...]) --- MINIFY (Lapys)
                constexpr inline digit& operator =(const unsigned char argument) noexcept { switch (argument) { case '0': case 0u: this -> value = 0u; break; case '1': case 1u: this -> value = 1u; break; case '2': case 2u: this -> value = 2u; break; case '3': case 3u: this -> value = 3u; break; case '4': case 4u: this -> value = 4u; break; case '5': case 5u: this -> value = 5u; break; case '6': case 6u: this -> value = 6u; break; case '7': case 7u: this -> value = 7u; break; case '8': case 8u: this -> value = 8u; break; case '9': case 9u: this -> value = 9u; break; } return *this; }
                inline operator unsigned char(void) const noexcept { return this -> value; }
        } year[5]; // NOTE (Lapys) -> Store the year as a consecutive group of digits (to demonstrate an array of bit fields).

    // [...]
    public:
        // [Constructor]
        inline Date(void) : day{0u}, month{0u}, year{'\0', '\0', '\0', '\0', '\0'} {
            // Initialization > (Evaluation, Time)
            time_t evaluation;
            struct tm *time;

            // Update > (Evaluation, Time)
            ::time(&evaluation);
            time = ::gmtime(&evaluation);

            // (Loop > )Modification > Target > (Day, Month, Year)
            this -> day = time -> tm_mday - 1;
            this -> month = time -> tm_mon;

            for (int iterator = (5) - 1, year = time -> tm_year + 1900; ~iterator && year; (iterator--, year /= 10))
            *(this -> year + iterator) = year % 10;
        }

        // Function > ...
        inline unsigned char getDay(void) const noexcept { return this -> day + 1u; }
        inline unsigned char getMonth(void) const noexcept { return this -> month + 1u; }
        inline unsigned short getYear(void) const noexcept { return (*(this -> year) * 10000u) + (*(this -> year + 1) * 1000u) + (*(this -> year + 2) * 100u) + (*(this -> year + 3) * 10u) + *(this -> year + 4); }
};

/* Main */
int main(void) {
    /* Global > Date */
    Date date {};

    // Print
        // [Day]
        ::printf("%s", "[Date -> day]  : ");
        for (unsigned char iterator = date.getDay(); iterator; iterator /= 10u) ::putchar('\0');
        for (unsigned char iterator = date.getDay(); iterator; iterator /= 10u) { ::putchar('\b'); ::putchar((char) (iterator % 10u) + 48); ::putchar('\b'); }
        ::putchar('\n'); ::putchar('\r');

        // [Month]
        ::printf("%s", "[Date -> month]: ");
        for (unsigned char iterator = date.getMonth(); iterator; iterator /= 10u) ::putchar('\0');
        for (unsigned char iterator = date.getMonth(); iterator; iterator /= 10u) { ::putchar('\b'); ::putchar((char) (iterator % 10u) + 48); ::putchar('\b'); }
        ::putchar('\n'); ::putchar('\r');

        // [Year]
        ::printf("%s", "[Date -> year] : ");
        for (unsigned short iterator = date.getYear(); iterator; iterator /= 10u) ::putchar('\0');
        for (unsigned short iterator = date.getYear(); iterator; iterator /= 10u) { ::putchar('\b'); ::putchar((char) (iterator % 10u) + 48); ::putchar('\b'); }
            ::putchar('\n'); ::putchar('\r');

    // Print
        // [Format]
        ::printf("%s", "\n[Date]         : ");
        for (unsigned char iterator = 0u; iterator ^ 11u; iterator++) ::putchar('\0');

        // [Year]
        for (unsigned short iterator = date.getYear(); iterator; iterator /= 10u) { ::putchar('\b'); ::putchar((char) (iterator % 10u) + 48); ::putchar('\b'); }
        for (unsigned short iterator = 10000u, length = date.getYear(); iterator > length; iterator /= 10u) { ::putchar('\b'); ::putchar('0'); ::putchar('\b'); }
        ::putchar('\b'); ::putchar('|'); ::putchar('\b');

        // [Month]
        for (unsigned char iterator = date.getMonth(); iterator; iterator /= 10u) { ::putchar('\b'); ::putchar((char) (iterator % 10u) + 48); ::putchar('\b'); }
        if (date.getMonth() < 10u) { ::putchar('\b'); ::putchar('0'); ::putchar('\b'); }
        ::putchar('\b'); ::putchar('|'); ::putchar('\b');

        // [Day]
        for (unsigned char iterator = date.getDay(); iterator; iterator /= 10u) { ::putchar('\b'); ::putchar((char) (iterator % 10u) + 48); ::putchar('\b'); }
        if (date.getDay() < 10u) { ::putchar('\b'); ::putchar('0'); ::putchar('\b'); }

    // Return
    return EXIT_SUCCESS;
}
