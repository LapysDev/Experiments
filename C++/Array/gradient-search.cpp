#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>

// Allocates memory unto stack (Risky to use)
#if defined(__WINDOWS__) // You get the idea
#  include <malloc.h>
#  define stack_allocate(size) _malloca(size)

#elif defined(__linux__)
#  include <alloca.h>
#  define stack_allocate(size) alloca(size)

#else
#  define stack_allocate(size) ::malloc(size)

#endif

// Declare stuff 📢
typedef unsigned array_t; // Array element type: Must be integral type with this setup! ✋
typedef long index_t;
typedef unsigned int length_t;
typedef length_t iterator_t; // For explicit semantics?
typedef struct statistic_t statistic_t; // Declare the `statistic_t` struct type.

namespace SEARCH {
    namespace linear {
        constexpr index_t forward(array_t*, array_t const, length_t const) noexcept;
        constexpr index_t reverse(array_t* const, array_t const, length_t const) noexcept;
    }

    namespace gradient {
        constexpr index_t binary(array_t* const, array_t const, length_t const) noexcept;
        constexpr index_t quaternary(array_t* const, array_t const, length_t const) noexcept;
        constexpr index_t octal(array_t* const, array_t const, length_t) noexcept;

        constexpr index_t variable(array_t* const, array_t const, length_t const, length_t) noexcept;
        constexpr index_t variable_binary(array_t* const, array_t const, length_t const) noexcept;
        constexpr index_t variable_quaternary(array_t* const, array_t const, length_t const) noexcept;
        constexpr index_t variable_octal(array_t* const, array_t const, length_t const) noexcept;
    }
}

// Setup stuff ⚙
array_t* ARRAY = NULL;
constexpr length_t const ARRAY_LENGTHS[8] {
    // Each length will be tested against each algorithm 🏃
    // (does `unsigned(...)` really have to be used here?)
    unsigned(1e1), unsigned(1e2), unsigned(1e3), unsigned(1e4), unsigned(1e5), unsigned(1e6), unsigned(1e7), unsigned(1e8)
};
constexpr iterator_t const TEST_COUNT = 100u;
struct statistic_t { // The stats. 📝
    index_t (&algorithm)(array_t* const, array_t const, length_t const);
    char const* const name;
    std::chrono::nanoseconds::rep time;

    constexpr inline statistic_t(char const* const name, index_t (&algorithm)(array_t* const, array_t const, length_t const)) :
    algorithm{algorithm}, name{name}, time{0u} {}
} STATISTICS[8] {
    {"Forward Linear", SEARCH::linear::forward},
    {"Reverse Linear", SEARCH::linear::reverse},

    {"Binary Gradient", SEARCH::gradient::binary},
    {"Quaternary Gradient", SEARCH::gradient::quaternary},
    {"Octal Gradient", SEARCH::gradient::octal},

    {"Variable Gradient (n = 2)", SEARCH::gradient::variable_binary},
    {"Variable Gradient (n = 4)", SEARCH::gradient::variable_quaternary},
    {"Variable Gradient (n = 8)", SEARCH::gradient::variable_octal}
};

// ...
inline array_t RANDOM(length_t const length) noexcept {
    static std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<array_t>(0u, length - 1u)(generator);
}

// Randomize the array 🎲
inline array_t* SHUFFLE(length_t const length) {
    ARRAY = (delete[] ARRAY, new array_t[length] {});

    for (array_t *iterator = ARRAY + length; ARRAY != iterator--; )
    *iterator = RANDOM(length);

    return ARRAY;
}

// Forward Linear [Search]
constexpr inline index_t SEARCH::linear::forward(array_t* array, array_t const value, length_t const length) noexcept {
    for (array_t *const end = array + length; array != end; ++array)
    if (value == *array) return array - (end - length);

    return -1;
}

// Reverse Linear [Search]
constexpr inline index_t SEARCH::linear::reverse(array_t* const array, array_t const value, length_t const length) noexcept {
    for (array_t *iterator = array + length; array != iterator--; )
    if (value == *iterator) return iterator - array;

    return -1;
}

// Doubly Gradient [Search]: Search the end & start of the array per iteration.
constexpr inline index_t SEARCH::gradient::binary(array_t* const array, array_t const value, length_t const length) noexcept {
    switch (length) { // No need to initialize variables on a length less than 3 🙅
        // (Though this amount of conditional branching code might be slower...)
        case 2u: if (value == *(array + 1)) return 1u;
        case 1u: if (value == *array) return 0u;
    } for (array_t *end = array + (length - 1u), *start = array; end > start; (--end, ++start)) {
        if (value == *end) return end - array;
        else if (value == *start) return start - array;
    }

    return -1;
}

// Quaternary Gradient [Search]: Search between the end & middle, and the middle & start of the array per iteration.
constexpr inline index_t SEARCH::gradient::quaternary(array_t* const array, array_t const value, length_t const length) noexcept {
    // Performs three (3) redundant checks with odd-length arrays.. 😭
    for (array_t
        *end = array + (length - 1u),
        *middleStart = array + (length >> 1u /* length / 2u */),
        *middleEnd = middleStart + (!(length & 1u) /* length % 2u */),
        *start = array;

        end >= middleEnd || start <= middleStart; // Actually necessary to check both... 😢
        (--end, ++middleEnd, --middleStart, ++start)
    ) {
        if (value == *end) return end - array;
        else if (value == *middleEnd) return middleEnd - array;
        else if (value == *middleStart) return middleStart - array;
        else if (value == *start) return start - array;
    }

    return -1;
}

// Octal Gradient [Search]: Search 8 parts of the array per iteration.
constexpr inline index_t SEARCH::gradient::octal(array_t* const array, array_t const value, length_t length) noexcept {
    /* Hard-coded approach to variable gradient search; Quite a bit ridiculous 😂 */

    // YES, an array could've been used instead... maybe 🤔
    // FAILS on array lengths lesser than 8 ⚠️
    array_t *start = NULL,
        *iterator2 = NULL, *iterator3 = NULL, *iterator4 = NULL, *iterator5 = NULL, *iterator6 = NULL,
        *preend = NULL, *end = array + (length - 1u);

    for (
        // Setup the iterators
        start = (length >>= 3u, array),
        iterator2 = start + length,
        iterator3 = iterator2 + length,
        iterator4 = iterator3 + length,
        iterator5 = iterator4 + length,
        iterator6 = iterator5 + length,
        preend = iterator6 + length;

        length ^ (length_t) (start - array);
        (++start, ++iterator2, ++iterator3, ++iterator4, ++iterator5, ++iterator6, ++preend, --end)
    ) {
        if (value == *start) return start - array;
        else if (value == *iterator2) return iterator2 - array;
        else if (value == *iterator3) return iterator3 - array;
        else if (value == *iterator4) return iterator4 - array;
        else if (value == *iterator5) return iterator5 - array;
        else if (value == *iterator6) return iterator6 - array;
        else if (value == *preend) return preend - array;
        else if (value == *end) return end - array;
    }

    // For array lengths not wholly divisible by 8 😕
    for (--preend; end != preend; --end)
    if (value == *end) return end - array;

    return -1;
}

/* [Variable] Gradient [Search] : `count` represents the number of gradient stops (which must be lesser than `length`)
    (Should this be called a distributed linear search?). */
constexpr inline index_t SEARCH::gradient::variable(array_t* const array, array_t const value, length_t const count, length_t length) noexcept {
    // Heap allocation is deathly slow for an algorithm, right? 🐢
    array_t **end = NULL;
    array_t **iterators = (array_t**) stack_allocate(count * sizeof(array_t*));
    array_t **preend = NULL;
    array_t *subend = NULL;

    // Setup the iterators
    *iterators = array; {
        end = iterators++ + (count - 1u);
        *end = array + (length - 1u);

        preend = end - 1;

        if (2u == count)
            --iterators;

        else {
            for (length /= count; end != iterators; ++iterators)
            *iterators = length + *(iterators - 1);

            iterators -= count - 1u;
        }
    }

    // Check the iterators concurrently
    for (subend = length + *preend; subend != *preend; iterators -= count - 1u) {
        if (value == *((*end)--))
        return (*end) - array + 1;

        while (iterators != end) if (value == *((*(iterators++))++))
        return (*(iterators - 1)) - array - 1;
    }

    // For unchecked indexes
    for (subend = *preend; subend <= *end; --*end)
    if (value == **end) return (*end) - array;

    return -1;
}

constexpr inline index_t SEARCH::gradient::variable_binary(array_t* const array, array_t const value, length_t const length) noexcept { return SEARCH::gradient::variable(array, value, 2u, length); }
constexpr inline index_t SEARCH::gradient::variable_quaternary(array_t* const array, array_t const value, length_t const length) noexcept { return SEARCH::gradient::variable(array, value, 4u, length); }
constexpr inline index_t SEARCH::gradient::variable_octal(array_t* const array, array_t const value, length_t const length) noexcept { return SEARCH::gradient::variable(array, value, 8u, length); }

/* Main */
int main(void) {
    // Go through each array length
    for (length_t const *ARRAY_LENGTH = ARRAY_LENGTHS, *end = ARRAY_LENGTHS + (sizeof(ARRAY_LENGTHS) / sizeof(length_t)); ARRAY_LENGTH != end; ++ARRAY_LENGTH) {
        // Get a random element to search; Not sure if this has to be re-rolled every function call
        array_t const TARGET = RANDOM((*ARRAY_LENGTH) - 1);

        // Print stuff
        std::cout << "LENGTH = " << std::setprecision(1) << std::scientific << (double) *ARRAY_LENGTH << std::endl;
        std::cout << "TIMES = [" << std::fixed << std::endl; {
            // Randomize the array per new length
            // Go through each statistic (and each algorithm)
            SHUFFLE(*ARRAY_LENGTH);
            for (statistic_t *STATISTIC = STATISTICS, *end = STATISTICS + (sizeof(STATISTICS) / sizeof(statistic_t)); STATISTIC != end; ++STATISTIC) {
                std::chrono::time_point<std::chrono::high_resolution_clock> const NOW = std::chrono::high_resolution_clock::now();

                // Batched performance benchmarking..
                for (iterator_t iterator = 0u; TEST_COUNT ^ iterator; ++iterator)
                STATISTIC -> algorithm(ARRAY, TARGET, *ARRAY_LENGTH);

                STATISTIC -> time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - NOW).count();
                std::cout << '\t' << STATISTIC -> name << " Search = " << STATISTIC -> time << " nanoseconds" << std::endl;
            }
        }

        // "Clean up" printing stuff
        std::cout << ']' << std::endl;
        std::endl(std::cout);
    }

    // ...; Return
    delete[] ARRAY;
    return EXIT_SUCCESS;
}
