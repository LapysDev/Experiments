/* Import */
#include <cstdio> // Standard Input-Output
#include <unistd.h> // Unix Standard

/* Definition */
    // Print Character --- NOTE (Lapys) -> Maximum Argument Count: 3, Minimum Argument Count: 2.
    #define print_character_with_custom_terminator_character(characterType, character, terminatingCharacter) \
        if (character != terminatingCharacter) { \
            (character == '\n') && std::fflush(stdout); \
            characterType characterString[2] {character, terminatingCharacter}; \
            ::write(STDOUT_FILENO, characterString, 1); \
        } \
        else ::write(STDOUT_FILENO, "\\0", 2)
    #define print_character_with_terminator_character(characterType, character) print_character_with_custom_terminator_character(characterType, character, '\0')

    #define print_character_macro_function_selector(arg1, arg2, arg3, print_characterMacroFunction, ...) printCharacterMacroFunction
    #define print_character_macro_function_expander(...) print_character_macro_function_selector(__VA_ARGS__, print_character_with_custom_terminator_character, print_character_with_terminator_character)
    #define print_character(...) print_character_macro_function_expander(__VA_ARGS__)(__VA_ARGS__)

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Print Character
        print_character(char, 'A', '\0');

        // Return
        return 0;
    }
