/* Import */
    // [C Standard Library]
    #include <float.h>
    #include <math.h>
    #include <stdlib.h>

    // [C++ Standard Library]
    #include <iostream>

/* Function */
    // Number > Greatest Common Divisor --- NOTE (Lapys) -> Expects safe number arguments. -> #include <numeric> \ template <..., ...> std::gcd(..., ...)
    constexpr inline long double number__greatest_common_divisor(long double const numberA, long double const numberB) noexcept {
        // Logic > Return
        if (0.00L == numberA) return numberB;
        else if (0.00L == numberB) return numberA;
        else if (numberA == numberB) return numberA;
        else if (numberA < numberB) return number__greatest_common_divisor(numberA, ::fmodl(numberB, numberA) /* -> numberB % numberA */);
        else return number__greatest_common_divisor(numberB, ::fmodl(numberA, numberB) /* -> numberA % numberB */);
    }

    // To Fraction
    inline long double* to_fraction(long double const number) {
        static long double evaluation[3] {0.00L}; // -> Whole, Numerator, Denominator
        constexpr static long double precision = ::powl(10.00L, (long double) LDBL_MAX_10_EXP);

        long double characteristics, mantissa = ::modfl(number, &characteristics);
        long double greatestCommonDivisor = number__greatest_common_divisor(::roundl(mantissa * precision), precision);

        *evaluation = characteristics;
        *(evaluation + 1) = ::truncl(::roundl(mantissa * precision) / greatestCommonDivisor);
        *(evaluation + 2) = ::truncl(precision / greatestCommonDivisor);

        return evaluation;
    }

/* Main */
int main(void) { return EXIT_SUCCESS; }
