/* Import > ... */
#include <inttypes.h> // Integer Types
#include <stdint.h> // Standard Integer

#include <cstddef> // C Standard Definition
#include <cstdio> // C Standard Input/ Output
#include <cstdlib> // C Standard Library

/* Global > States --- WARN (Lapys) -> Requires at least two states. */
static char const *const STATES[] = {
    // "STATE A", "STATE B", "STATE C"
    "0", "1", "2", "3", "4", "5", "6", "7"//, "8", "9"
};

static std::size_t const STATES_COUNT = sizeof(STATES) / sizeof(char const*);

/* Function > Filter */
static bool FILTER(char const* const permutation[]) {
    // ... ->> Modify at will to change what entries are outputted.
    // : Denary counting
    if (STATES[0] == permutation[0] && NULL != permutation[1]) return false;

    // : Distinct states
    for (char const *const *state = permutation + STATES_COUNT; permutation != state--; )
    for (char const *const *substate = permutation + STATES_COUNT; permutation != substate--; ) {
        if (state != substate) {
            char const *iterator = *state;
            char const *subiterator = *substate;

            if (NULL != iterator && NULL != subiterator)
            while (*iterator == *subiterator) {
                if ('\0' == *(iterator++)) return '\0' != *subiterator;
                if ('\0' == *(subiterator++)) return '\0' != *iterator;
            }
        }
    }

    // ... ->> Default
    return true;
}

/* Main */
int main(void) {
    uintmax_t PERMUTATIONS_COUNT = 0u;
    char const **PERMUTATIONS = NULL;

    std::size_t PERMUTATION_LENGTH = 1u;
    std::size_t PERMUTATION_INDEX = 0u;
    char const *PERMUTATION[STATES_COUNT] = { STATES[0], /* ... */ 0 };

    std::size_t OUTPUT_LENGTH = 0u;
    char *OUTPUT_BUFFER = NULL;

    // ... ->> Calculate total permutation count.
    for (std::size_t base = STATES_COUNT, iterator = STATES_COUNT; iterator; --iterator) {
        std::size_t permutationsCount = 1u;

        for (std::size_t subiterator = iterator; subiterator; --subiterator) permutationsCount *= base;
        PERMUTATIONS_COUNT += permutationsCount;

        if (/* ->> Overflow */ PERMUTATIONS_COUNT < base) {
            std::fputs("[Error]: Too many states to permute" "\r\n", stderr);
            std::exit(EXIT_FAILURE);
        }
    }

    // ... ->> Output loading message.
    std::fprintf(stdout, "Processing %lu possible permutations ..." "\r\n", static_cast<unsigned long>(PERMUTATIONS_COUNT));

    // ... ->> Calculate output stream buffer size.
    for (std::size_t iterator = PERMUTATIONS_COUNT; iterator; --iterator) {
        for (char const *const *state = STATES + STATES_COUNT; STATES != state--; ) {
            std::size_t length = 0u;

            for (char const *subiterator = *state; '\0' != *subiterator; ++subiterator) ++length;
            if (length < /* --> "(null)" */ 6u) length = 6u;

            OUTPUT_LENGTH += length;
        }

        OUTPUT_LENGTH += /* --> '[', ']' '\n' */ 3u + /* --> ", " */ (2u * (STATES_COUNT - 1u));
    }

    // ...
    PERMUTATIONS = static_cast<char const**>(std::malloc((PERMUTATIONS_COUNT * STATES_COUNT) * sizeof(char const*)));
    if (NULL == PERMUTATIONS) {
        std::fputs("[Error]: Unable to permute all states" "\r\n", stderr);
        std::exit(EXIT_FAILURE);
    }

    // ... ->> Generate the permutations.
    PERMUTATIONS_COUNT = 0u;
    while (PERMUTATION_LENGTH != STATES_COUNT + 1u) {
        char const **permutationState = PERMUTATION + (PERMUTATION_LENGTH - 1u);

        for (char const *const *state = STATES + STATES_COUNT; STATES != state--; )
        if (*permutationState == *state) {
            bool const filter = FILTER(PERMUTATION);
            std::size_t iterator = 0u;

            // ... ->> record the current permutation
            if (filter) {
                while (PERMUTATION_LENGTH != iterator)
                PERMUTATIONS[PERMUTATIONS_COUNT++] = PERMUTATION[iterator++];
            }

            for (iterator = STATES_COUNT - (filter * PERMUTATION_LENGTH); iterator--; )
            PERMUTATIONS[PERMUTATIONS_COUNT++] = NULL;

            // ... ->> change the permutation
            if (STATES_COUNT != ++state - STATES) *permutationState = *state;
            else {
                --state;
                while (*permutationState == *state) {
                    *permutationState = *STATES;
                    if (PERMUTATION == permutationState--) break;
                }

                // ...
                if (PERMUTATION == ++permutationState) {
                    *permutationState = *STATES;
                    PERMUTATION[PERMUTATION_LENGTH++] = *STATES;
                }

                else {
                    --permutationState;
                    state = STATES;

                    while (*permutationState != *state) ++state;
                    *permutationState = *++state;
                }
            }

            // ...
            break;
        }
    }

    // ... ->> Output the permutations.
    OUTPUT_BUFFER = static_cast<char*>(std::malloc(OUTPUT_LENGTH * sizeof(char)));
    std::setbuf(stdout, OUTPUT_BUFFER);

    for (uintmax_t iterator = 0u; PERMUTATIONS_COUNT != iterator; ) {
        std::size_t count = 0u; // ... ->> null count

        for (std::size_t subiterator = STATES_COUNT; subiterator--; )
        count += NULL == PERMUTATIONS[iterator++];

        if (STATES_COUNT != count) {
            std::fprintf(stdout, "#%lu\t[", static_cast<unsigned long>(++PERMUTATION_INDEX));

            iterator -= STATES_COUNT;

            for (std::size_t subiterator = STATES_COUNT; subiterator--; )
            std::fprintf(stdout, "%s%.2s", PERMUTATIONS[iterator++], subiterator ? ", " : "");

            std::fprintf(stdout, "%c%.2s", ']', PERMUTATIONS_COUNT == iterator ? "" : "\r\n");
        }
    }

    std::fflush(stdout);

    // ... ->> Clean-up
    std::free(OUTPUT_BUFFER);
    std::free(PERMUTATIONS);

    // ...
    return EXIT_SUCCESS;
}
