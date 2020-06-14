/* Import */
#include <cuchar> // C Unicode Characters
#include <fcntl.h> // File Control
#include <stdlib.h> // Standard Library
#include <string.h> // String
#include <wchar.h> // Wide Characters

/* Function
        --- MINIFY (Lapys) ---
        --- NOTE (Lapys) -> `signed char` and `unsigned char` primitive types are not regarded as character types.
        --- WARN ---
            #Lapys:
                - Before C++ 2020`s `char8_t` primitive character type.
                - Evaluated (returned) strings are heap-allocated unless the string is null.
*/
    // [...]
    constexpr inline size_t string__length(char const* const string) { return NULL == string ? 0u : ::strlen(string); }
    constexpr inline size_t string__length(char* const string) { return string__length((char const*) string); }
    constexpr inline size_t string__length(wchar_t const* const string) { return NULL == string ? 0u : ::wcslen(string); }
    constexpr inline size_t string__length(wchar_t* const string) { return string__length((wchar_t const*) string); }
    template <typename type> inline size_t string__length(type* string) { if (NULL == string) return 0u; else { type *iterator = string; while (*iterator) ++iterator; return iterator - string; } }
    template <typename type> inline size_t string__length(type const* string) { if (NULL == string) return 0u; else { type *iterator = (type*) string; while (*iterator) ++iterator; return iterator - string; } }

    // [Character String]
    constexpr char const* character_string__to__character_string(char const* const string) noexcept { if (string) { char *evaluation = (char*) ::malloc((string__length(string) + 1u) * sizeof(char)); ::strcpy(evaluation, string); return (char const*) evaluation; } else return NULL; }
    constexpr inline char16_t const* character_string__to__UTF16_character_string(char* string) noexcept { if (string) { char16_t *evaluation = (char16_t*) ::malloc((string__length(string) + 1u) * sizeof(char16_t)); for (char16_t *iterator = evaluation; '\0' ^ (*iterator++ = *string++); ) continue; return (char16_t const*) evaluation; } else return NULL; }
    constexpr inline char32_t const* character_string__to__UTF32_character_string(char* string) noexcept { if (string) { char32_t *evaluation = (char32_t*) ::malloc((string__length(string) + 1u) * sizeof(char32_t)); for (char32_t *iterator = evaluation; '\0' ^ (*iterator++ = *string++); ) continue; return (char32_t const*) evaluation; } else return NULL; }
    inline wchar_t const* character_string__to__wide_character_string(char* string) noexcept {
        #if true
            if (string) { size_t const length = string__length(string) + 1u; wchar_t *evaluation = (wchar_t*) ::malloc(length * sizeof(wchar_t)); mbstate_t multibyteState; ::mbrlen(NULL, 0u, &multibyteState); ::mbsrtowcs(evaluation, (char const**) &string, length, &multibyteState); return evaluation; } else return NULL;
        #else
            unsigned int codepoint; wchar_t *evaluation = (wchar_t*) ::malloc((string__length(string) + 1u) * sizeof(wchar_t)); for (wchar_t *iterator = evaluation; '\0' ^ *string; ) { unsigned char const character = (unsigned char) *string; if (character <= 0x7F) codepoint = character; else if (character <= 0xBF) codepoint = (codepoint << 6u) | (character & 0x3F); else if (character <= 0xDF) codepoint = character & 0x1F; else if (character <= 0xEF) codepoint = character & 0x0F; else codepoint = character & 0x07; ++string; if (codepoint <= 0x10FFFF && (0x80 ^ (*string & 0xC0))) { if (sizeof(wchar_t) > 2u) *iterator++ = (wchar_t) codepoint; else if (codepoint > 0xFFFF) { *iterator++ = (wchar_t) (0xD800 + (codepoint >> 10u)); *iterator++ = (wchar_t) (0xDC00 + (codepoint & 0x03FF)); } else if (codepoint < 0xD800 || codepoint >= 0xE000) *iterator++ = (wchar_t) codepoint; } } return (wchar_t const*) evaluation;
        #endif
    }

    // [UTF-16 Character String]
    char const* UTF16_character_string__to__character_string(char16_t const* const string) noexcept; // CHECKPOINT (Lapys) -> `c16rtomb`?
    inline char16_t const* UTF16_character_string__to__UTF16_character_string(char16_t const* const string) noexcept { size_t const length = string__length(string) + 1u; char16_t *evaluation = (char16_t*) ::malloc(length * sizeof(char16_t)); ::memcpy(evaluation, string, length * sizeof(char16_t)); return (char16_t const*) evaluation; }
    inline char32_t const* UTF16_character_string__to__UTF32_character_string(char16_t* string) noexcept { char32_t *evaluation = (char32_t*) ::malloc((string__length(string) + 1u) * sizeof(char32_t)); for (char32_t *iterator = evaluation; (*iterator++ = *string++); ) continue; return (char32_t const*) evaluation; }
    wchar_t const* UTF16_character_string__to__wide_character_string(char16_t const* string) noexcept { wchar_t *evaluation = (wchar_t*) ::malloc((string__length(string) + 1u) * sizeof(wchar_t)); for (wchar_t *iterator = evaluation; (*iterator++ = *string++); ) continue; return (wchar_t const*) evaluation; }

    // [UTF-32 Character String]
    char const* UTF32_character_string__to__character_string(char32_t const* const string) noexcept; // CHECKPOINT (Lapys) -> `c32rtomb`?
    char16_t const* UTF32_character_string__to__UTF16_character_string(char32_t const* const string) noexcept; // CHECKPOINT (Lapys)
    inline char32_t const* UTF32_character_string__to__UTF32_character_string(char32_t const* const string) noexcept { size_t const length = string__length(string) + 1u; char32_t *evaluation = (char32_t*) ::malloc(length * sizeof(char32_t)); ::memcpy(evaluation, string, length * sizeof(char32_t)); return (char32_t const*) evaluation; }
    wchar_t const* UTF32_character_string__to__wide_character_string(char32_t const* string) noexcept { // CHECKPOINT (Lapys)
        wchar_t *evaluation = (wchar_t*) ::malloc((string__length(string) + 1u) * sizeof(wchar_t));
        if (sizeof(char32_t) == sizeof(wchar_t)) for (wchar_t *iterator = evaluation; (*iterator++ = *string++); ) continue;
        return (wchar_t const*) evaluation;
    }

    // [Wide Character String]
    inline char const* wide_character_string__to__character_string(wchar_t const* string) noexcept {
        #if true
            size_t const length = string__length(string) + 1u; char *evaluation = (char*) ::malloc(length * sizeof(char)); mbstate_t multibyteState; ::mbrlen(NULL, 0u, &multibyteState); ::wcsrtombs(evaluation, &string, length, &multibyteState); return evaluation;
        #else
            unsigned int codepoint = 0u; char *evaluation = (char*) ::malloc((string__length(string) + 1u) * sizeof(char)); for (char *iterator = evaluation; L'\0' ^ *string; ++string) { wchar_t const& character = *string; if (character >= 0xD800 && character <= 0xDBFF) codepoint = ((character - 0xD800) << 10u) + 0x10000; else { codepoint = character >= 0xDC00 && character <= 0xDFFF ? codepoint | (character - 0xDC00) : character; if (codepoint <= 0x7F) *iterator++ = (char) codepoint; else if (codepoint <= 0x7FF) { *iterator++ = (char) (0xC0 | ((codepoint >> 6u) & 0x1F)); *iterator++ = (char) (0x80 | (codepoint & 0x3F)); } else if (codepoint <= 0xFFFF) { *iterator++ = (char) (0xE0 | ((codepoint >> 12u) & 0x0F)); *iterator++ = (char) (0x80 | ((codepoint >> 6u) & 0x3F)); *iterator++ = (char) (0x80 | (codepoint & 0x3F)); } else { *iterator++ = (char) (0xF0 | ((codepoint >> 18u) & 0x07)); *iterator++ = (char) (0x80 | ((codepoint >> 12u) & 0x3F)); *iterator++ = (char) (0x80 | ((codepoint >> 6u) & 0x3F)); *iterator++ = (char) (0x80 | (codepoint & 0x3F)); } codepoint = 0u; } *(iterator + 1) = '\0'; } return evaluation;
        #endif
    }
    char16_t const* wide_character_string__to__UTF16_character_string(wchar_t const* string) noexcept { char16_t *evaluation = (char16_t*) ::malloc((string__length(string) + 1u) * sizeof(char16_t)); if (sizeof(char16_t) == sizeof(wchar_t)) for (char16_t *iterator = evaluation; (*iterator++ = *string++); ) continue; else for (char16_t *iterator = evaluation; L'\0' ^ *string; ++string) { long const character = *string; if (character < 0 || character > 0x10FFFF || (character >= 0xD800 && character <= 0xDFFF)) { ::memmove(iterator + 1, iterator, (iterator - evaluation) * sizeof(char16_t)); *iterator = u'\uFFFD'; } else if (((unsigned long) character) < 0x10000uL) { ::memmove(iterator + 1, iterator, (iterator - evaluation) * sizeof(char16_t)); *iterator = (char16_t) character; } else { *iterator++ = (char16_t) (((character - 0x10000uL) / 0x400u) + 0xD800u); *iterator++ = (char16_t) (((character - 0x10000uL) % 0x400u) + 0xDC00u); } } return (char16_t const*) evaluation; }
    char32_t const* wide_character_string__to__UTF32_character_string(wchar_t const* string) noexcept { char32_t *evaluation = (char32_t*) ::malloc((string__length(string) + 1u) * sizeof(char32_t)); for (char32_t *iterator = evaluation; (*iterator++ = *string++); ) continue; return (char32_t const*) evaluation; }
    inline wchar_t const* wide_character_string__to__wide_character_string(wchar_t const* const string) noexcept { wchar_t *evaluation = (wchar_t*) ::malloc((string__length(string) + 1u) * sizeof(wchar_t)); ::wcscpy(evaluation, string); return (wchar_t const*) evaluation; }

/* Main */
int main(void) {
    // Return
    return EXIT_SUCCESS;
}
