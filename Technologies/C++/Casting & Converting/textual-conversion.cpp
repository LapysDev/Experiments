/* Import */
#include <cuchar> // C Unicode Characters
#include <fcntl.h> // File Control
#include <stdlib.h> // Standard Library
#include <string.h> // String
#include <wchar.h> // Wide Characters

#include <stdio.h>

/* Function
        --- NOTE (Lapys) -> `signed char` and `unsigned char` primitive types are not regarded as character types.
        --- WARN ---
            #Lapys:
                - Before C++ 2020`s `char8_t` primitive character type.
                - Evaluated (returned) strings are heap-allocated.
*/
    // [...]
    constexpr inline size_t string__length(char const* const string) { return NULL == string ? 0u : ::strlen(string); }
    constexpr inline size_t string__length(char* const string) { return string__length((char const*) string); }
    constexpr inline size_t string__length(wchar_t const* const string) { return NULL == string ? 0u : ::wcslen(string); }
    constexpr inline size_t string__length(wchar_t* const string) { return string__length((wchar_t const*) string); }
    template <typename type> inline size_t string__length(type* const string) { if (NULL == string) return 0u; else { size_t length = 0u; while (*(string + length)) ++length; return length; } }

    // [Character String]
    constexpr char const* character_string__to__character_string(char const* const characterString) noexcept { size_t const characterStringLength = string__length(characterString); char *evaluation = (char*) ::malloc((characterStringLength + 1u) * sizeof(char)); ::strncpy(evaluation, characterString, characterStringLength + 1u); return (char const*) evaluation; }
    inline char16_t const* character_string__to__UTF16_character_string(char* characterString) noexcept { char16_t *evaluation = (char16_t*) ::malloc((string__length(characterString) + 1u) * sizeof(char16_t)); for (char16_t *iterator = evaluation; (*iterator++ = *characterString++); ) continue; return (char16_t const*) evaluation; }
    inline char32_t const* character_string__to__UTF32_character_string(char* characterString) noexcept { char32_t *evaluation = (char32_t*) ::malloc((string__length(characterString) + 1u) * sizeof(char32_t)); for (char32_t *iterator = evaluation; (*iterator++ = *characterString++); ) continue; return (char32_t const*) evaluation; }
    inline wchar_t const* character_string__to__wide_character_string(char const* characterString) noexcept { size_t const characterStringLength = string__length(characterString); wchar_t *evaluation = (wchar_t*) ::malloc((characterStringLength + 1u) * sizeof(wchar_t)); mbstate_t multibyteState; ::mbrlen(NULL, 0u, &multibyteState); ::mbsrtowcs(evaluation, &characterString, characterStringLength + 1u, &multibyteState); return evaluation; }

    // [UTF-16 Character String]
    char const* UTF16_character_string__to__character_string(char16_t const* const UTF16CharacterString) noexcept;
    inline char16_t const* UTF16_character_string__to__UTF16_character_string(char16_t const* const UTF16CharacterString) noexcept { size_t const UTF16CharacterStringLength = string__length(UTF16CharacterString); char16_t *evaluation = (char16_t*) ::malloc((UTF16CharacterStringLength + 1u) * sizeof(char16_t)); ::memcpy(evaluation, UTF16CharacterString, (UTF16CharacterStringLength + 1u) * sizeof(char16_t)); return (char16_t const*) evaluation; }
    inline char32_t const* UTF16_character_string__to__UTF32_character_string(char16_t* UTF16CharacterString) noexcept { char32_t *evaluation = (char32_t*) ::malloc(string__length(UTF16CharacterString) * sizeof(char32_t)); for (char32_t *iterator = evaluation; (*iterator++ = *UTF16CharacterString++); ) continue; return (char32_t const*) evaluation; }
    wchar_t const* UTF16_character_string__to__wide_character_string(char16_t const* const UTF16CharacterString) noexcept;

    // [UTF-32 Character String]
    char const* UTF32_character_string__to__character_string(char32_t const* const UTF32CharacterString) noexcept;
    char16_t const* UTF32_character_string__to__UTF16_character_string(char32_t const* const UTF32CharacterString) noexcept;
    inline char32_t const* UTF32_character_string__to__UTF32_character_string(char32_t const* const UTF32CharacterString) noexcept { size_t const UTF32CharacterStringLength = string__length(UTF32CharacterString); char32_t *evaluation = (char32_t*) ::malloc((UTF32CharacterStringLength + 1u) * sizeof(char32_t)); ::memcpy(evaluation, UTF32CharacterString, (UTF32CharacterStringLength + 1u) * sizeof(char32_t)); return (char32_t const*) evaluation; }
    wchar_t const* UTF32_character_string__to__wide_character_string(char32_t const* const UTF32CharacterString) noexcept;

    // [Wide Character String]
    inline char const* wide_character_string__to__character_string(wchar_t const* wideCharacterString) noexcept { size_t const wideCharacterStringLength = string__length(wideCharacterString); char *evaluation = (char*) ::malloc((wideCharacterStringLength + 1u) * sizeof(char)); mbstate_t multibyteState; ::mbrlen(NULL, 0u, &multibyteState); ::wcsrtombs(evaluation, &wideCharacterString, wideCharacterStringLength + 1u, &multibyteState); return evaluation; }
    char16_t const* wide_character_string__to__UTF16_character_string(wchar_t const* const wideCharacterString) noexcept;
    char32_t const* wide_character_string__to__UTF32_character_string(wchar_t const* const wideCharacterString) noexcept;
    inline wchar_t const* wide_character_string__to__wide_character_string(wchar_t const* const wideCharacterString) noexcept { size_t const wideCharacterStringLength = string__length(wideCharacterString); wchar_t *evaluation = (wchar_t*) ::malloc((wideCharacterStringLength + 1u) * sizeof(wchar_t)); ::wcsncpy(evaluation, wideCharacterString, wideCharacterStringLength + 1u); return (wchar_t const*) evaluation; }

/* Main */
int main(void) {
    // Return
    return EXIT_SUCCESS;
}
