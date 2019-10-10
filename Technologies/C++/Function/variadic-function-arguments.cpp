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
    constexpr inline void print_lottery_numbers$fixed(int number) { std::printf("%i, ", number); }
    inline void print_lottery_numbers$variadic(va_list& arguments) { print_lottery_numbers$fixed(va_arg(arguments, int)); print_lottery_numbers$variadic(arguments); }
    inline void print_lottery_numbers(int number, ...) {
        // Print
        std::printf("%s", "The lottery numbers are: ");

        // Initialization > Arguments
        va_list arguments;

        // Update > Arguments
        va_start(arguments, number);

        // Print Lottery Numbers
        print_lottery_numbers$fixed(number);
        print_lottery_numbers$variadic(arguments);

        // Update > Arguments
        va_end(arguments);
    }

    // Print Lucky Numbers
    constexpr inline void print_lucky_numbers$fixed(int number) { std::printf("%i, ", number); }
    constexpr inline void print_lucky_numbers$variadic() {}
    template <typename... types, typename = int> constexpr void print_lucky_numbers$variadic(int number, types... numbers) { print_lucky_numbers$fixed(number); print_lucky_numbers$variadic(numbers...); }
    template <typename... types, typename = int> inline void print_lucky_numbers(types... arguments) { std::printf("%s", "The lucky numbers are: "); print_lucky_numbers$variadic(arguments...); }

    /* Main */
    int main(int argc, char* argv[]) {
        // Print (Lucky, Lottery) Numbers --- NOTE (Lapys) -> Fortune or Gamble?
        true ? print_lucky_numbers(1, 7, 9, 4, 3, 1, 0, 9, 2, 9) : print_lottery_numbers(1, 7, 9, 4, 3, 1, 0, 9, 2, 9);

        // Return
        return 0;
    }
