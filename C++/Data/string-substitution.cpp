/* Import > ... */
#include <cstdio>

/* ... */
static char const *matches[] = {NULL, NULL, NULL};
static unsigned char const matchesCount = sizeof(matches) / sizeof(char const*);

static char string[128];
static unsigned char stringLength = 0u;

static char const* replace(char const match[]) {
    // replace spaces with underscores, remove everything else
    return match[0] == ' ' && match[1] == '\0' ? "___" : "";
}

/* Main */
int main(void) {
    // your string value
    for (
        char const value[] = "  This is a really long sentence, y'know?", *iterator = value;
        iterator == value || '\0' != iterator[-1]; ++iterator
    ) string[stringLength++ /* --> iterator - value */] = *iterator;
    --stringLength; // from the NUL character added at the end

    // your intended matches
    for (
        char const
            *const values[] = {"really", " "},
            *const *iterator = values + (sizeof(values) / sizeof(char const*));
        iterator-- != values;
    ) matches[iterator - values] = *iterator;

    // ... print the input
    std::printf("[string] : \"%s\"" "\r\n", string);
    std::printf("%12s", "[matches]: {");
      for (unsigned iterator = 0u; iterator != matchesCount; ++iterator)
      std::printf("\"%s\"%.2s", matches[iterator], iterator == matchesCount - 1u ? "" : ", ");
    std::printf("%3s", "}" "\r\n");

    // --> "______This___is___a______long___sentence,___y'know?"
    /* start_process: */ {
        for (char *iterator = string; '\0' != *iterator; ++iterator) // go through the string
        for (char const *const *subiterator = matches + matchesCount; matches != subiterator--; ) { // go through every match
            char const *match = *subiterator;

            if (NULL == match || '\0' == *match) { /* different logic here */ }
            else {
                unsigned char matchLength;
                char const *substitute = NULL;

                // check for the match
                while (*iterator == *match) {
                    ++iterator;
                    ++match;

                    if ('\0' == *iterator) {
                        // use `return` instead if inside a function
                        goto end_process;
                    }

                    if ('\0' == *match) {
                        substitute = replace(*subiterator); // wary of side-effects
                        matchLength = match - *subiterator;
                        iterator -= matchLength;

                        break;
                    }
                }

                // the match has been found, so substitute it into the string
                if (NULL != substitute) {
                    char const *offset;
                    unsigned char substituteLength = 0u;

                    while ('\0' != substitute[substituteLength])
                    ++substituteLength;

                    // ...
                    if (matchLength < substituteLength) {
                        offset = string + stringLength;
                        stringLength += substituteLength - matchLength;

                        // expand the string (to accommodate for the substitution)
                        for (
                            char *fill = string + stringLength;
                            iterator != offset; --fill, --offset
                        ) *fill = *offset;

                        // replace the match with the substitution in the string
                        while ('\0' != *substitute)
                        *(iterator++) = *(substitute++);
                    }

                    else {
                        // replace the match with the substitution in the string
                        while ('\0' != *substitute)
                        *(iterator++) = *(substitute++);

                        // shrink the string (to fill the spaces left by the substitution)
                        offset = iterator + (matchLength - substituteLength);
                        if (iterator != offset) {
                            stringLength -= offset - iterator;
                              for (char *fill = iterator; '\0' != *offset; ++fill, ++offset)
                              *fill = *offset;
                            string[stringLength] = '\0';
                        }
                    }

                    --iterator; // correct the `iterator` position
                    break; // don't check for the other matches, move on to the next character instead
                }
            }
        }
    } end_process:

    // ... print the output
    std::printf("[string] : \"%s\"" "\r\n", string);
}
