/* Import */
#include <time.h> // Time

/* Definition > ... */
bool randbool(void) noexcept;
int randint(int const = 100) noexcept;
float random(float = 100.0f) noexcept;
void randseed(void) noexcept;
void randseed(unsigned const) noexcept;

/* Function */
    // Random Boolean
    inline bool randbool(void) noexcept { randseed(); return 1 == ::rand() % 2; }

    // Random Integer
    inline int randint(int const range) noexcept { randseed(); return (::rand() % range) * (range < 0 ? -1 : 1); }

    // Random
    inline float random(float range) noexcept {
        // Initialization > (Evaluation, Precision)
        float evaluation = 0.0f;
        unsigned char precision = 0u;

        // Logic > Loop
        if (::isfinite(range) && false == ::isnan(range))
        while (0 != ::modf(range, &evaluation) && (FLT_MAX_10_EXP ^ precision)) {
            // Update > (Precision, Range)
            ++precision;
            range *= 10.0f;
        }

        // (Loop > )Update > Evaluation
        randseed();
        evaluation = randint(::trunc(evaluation));
        while (precision--) evaluation /= 10.0f;

        // Return
        return evaluation;
    }

    // Random Seed --- WARN (Lapys) -> Seeds only once.
    inline void randseed(void) noexcept { randseed(::time(0x0)); }
    inline void randseed(unsigned const seed) noexcept { static bool once = false; if (false == once) { ::srand(seed); once = true; } }
