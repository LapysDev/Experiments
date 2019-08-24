/* Import */
    // C Standard Input-Output
    #include <cstdio>

    // Unix Standard
    #include <unistd.h>

/* Definition */
    // Print Character --- NOTE (Lapys) -> Maximum Argument Count: 3, Minimum Argument Count: 2.
    #define printCharacterWithCustomTermination(characterType, character, terminatingCharacter) \
        if (character != terminatingCharacter) { \
            (character == '\n') && std::fflush(stdout); \
            characterType characterString[2] {character, terminatingCharacter}; \
            ::write(STDOUT_FILENO, characterString, 1); \
        } \
        else ::write(STDOUT_FILENO, "\\0", 2)
    #define printCharacterWithTermination(characterType, character) printCharacterWithCustomTermination(characterType, character, '\0')

    #define printCharacterMacroFunctionSelector(arg1, arg2, arg3, printCharacterMacroFunction, ...) printCharacterMacroFunction
    #define printCharacterMacroFunctionExpander(...) printCharacterMacroFunctionSelector(__VA_ARGS__, printCharacterWithCustomTermination, printCharacterWithTermination)
    #define printCharacter(...) printCharacterMacroFunctionExpander(__VA_ARGS__)(__VA_ARGS__)

/* Function */
    // Main
    int main(int argc, char* argv[]) {
        // Print Character
        printCharacter(char, 'A', '\0');

        // Return
        return 0;
    }
