/* Import */
    // [C Standard Library  ]
    #include <math.h> // Mathematics
    #include <stdlib.h> // Standard Library

    // [C++ Standard Library]
    #include <exception> // Exception
    #include <iostream> // Input-Output Stream

inline long double const* to_fraction(long double const number) {
    // Evaluation > Fraction
    static long double fraction[2] {};

    // Logic
    if (number < 0.00L)
        // Return
        return to_fraction(-number);

    else if (::isinf(number) || ::isnan(number) || false == ::isnormal(number))
        // Error
        throw std::invalid_argument("Number is non-convertible to rational fraction");

    else {
        // Evaluation > (Denominator, Numerator)
        long double& denominator = *(fraction + 1);
        long double& numerator = *fraction;

        // Initialization > (Characteristics, Mantissa)
        long double characteristics;
        long double mantissa = ::modf(number, &characteristics);

        // ... --- CHECKPOINT (Lapys)
        (void) characteristics;
        (void) denominator;
        (void) mantissa;
        (void) numerator;
    }

    // Return
    return fraction;
}

// 0.50 -> 1 / 2
// 0.30 -> 1 / 3
// 0.25 -> 1 / 4

/* Main */
int main(void) {
    // Return
    return EXIT_SUCCESS;
}
