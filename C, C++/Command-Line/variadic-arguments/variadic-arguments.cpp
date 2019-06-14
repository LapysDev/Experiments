/* Import */
    // C Standard Input-Output
    #include <cstdio>

    // Standard Argument
    #include <stdarg.h>

    // String
    #include <string.h>

/* Function */
    /* Print Lottery Numbers
            --- WARN ---
                #Lapys:
                    - Must have a counter or
                    - Must be sentinel-controlled (have a terminating value).
    */
    constexpr inline void printLotteryNumbers$fixed(int number) { std::printf("%i, ", number); }
    inline void printLotteryNumbers$variadic(va_list& arguments) { printLotteryNumbers$fixed(va_arg(arguments, int)); printLotteryNumbers$variadic(arguments); }
    inline void printLotteryNumbers(int number, ...) {
        // Print
        std::printf("%s", "The lottery numbers are: ");

        // Initialization > Arguments
        va_list arguments;

        // Update > Arguments
        va_start(arguments, number);

        // Print Lottery Numbers
        printLotteryNumbers$fixed(number);
        printLotteryNumbers$variadic(arguments);

        // Update > Arguments
        va_end(arguments);
    }

    // Print Lucky Numbers
    constexpr inline void printLuckyNumbers$fixed(int number) { std::printf("%i, ", number); }
    constexpr inline void printLuckyNumbers$variadic() {}
    template <typename... types, typename = int> constexpr void printLuckyNumbers$variadic(int number, types... numbers) { printLuckyNumbers$fixed(number); printLuckyNumbers$variadic(numbers...); }
    template <typename... types, typename = int> inline void printLuckyNumbers(types... arguments) { std::printf("%s", "The lucky numbers are: "); printLuckyNumbers$variadic(arguments...); }

    /* Main */
    int main(int argc, char* argv[]) {
        // Print (Lucky, Lottery) Numbers --- NOTE (Lapys) -> Fortune or Gamble?
        true ? printLuckyNumbers(1, 7, 9, 4, 3, 1, 0, 9, 2, 9) : printLotteryNumbers(1, 7, 9, 4, 3, 1, 0, 9, 2, 9);

        // Return
        return 0;
    }
