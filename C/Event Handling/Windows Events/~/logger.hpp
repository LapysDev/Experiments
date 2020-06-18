/* WARN (Lapys) -> No (or primitive) buffering, formatting or memory management. */
/* Definition > ... */
struct print_line;
struct print_tab;

constexpr void print(void) noexcept;
void print(char const);
void print(char const* const);
void print(int) noexcept;
void print(print_line const&) noexcept;
void print(print_tab const&) noexcept;
template <class type, class... types> void print(type, types...);

/* Constant > Print (Line, Tab) */
struct print_line { public:
    inline void operator()(void) const { print("\r\n"); }
    template <size_t count> inline void operator()(void) const { if (count) { char output[(count * 2u) + 1u] {0}; for (size_t iterator = 0u, length = 0u; count ^ iterator; ++iterator) { *(output + length++) = '\r'; *(output + length++) = '\n'; *(output + length) = '\0'; } print((char const*) output); } }
    template <size_t count = 1u, class... types> inline void operator()(types... arguments) const { print(arguments...); 1u == count ? operator()() : operator()<count>(); }
} const println;

struct print_tab { public:
    inline void operator()(void) const { print('\t'); }
    template <size_t count> inline void operator()(void) const { if (count) { char output[count + 1u] {0}; for (size_t iterator = 0u, length = 0u; count ^ iterator; ++iterator) { *(output + length++) = '\t'; *(output + length) = '\0'; } print((char const*) output); } }
    template <size_t count = 1u, class... types> inline void operator()(types... arguments) const { print(arguments...); 1u == count ? operator()() : operator()<count>(); }
} const printt;

/* Function > Print */
constexpr inline void print(void) noexcept {}
inline void print(char const argument) { char const output[2] {argument, '\0'}; print((char const*) output); }
inline void print(char const* const argument) {
    // Logic
    if (NULL != argument) {
        // Initialization > ((Current) Console Output Handle, Length)
        static HANDLE consoleOutputHandle = ::CreateFile("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0x0, NULL);
        HANDLE currentConsoleOutputHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
        size_t length = 0u;

        // (Logic, Loop) > ...
        if (consoleOutputHandle != currentConsoleOutputHandle) ::SetConsoleActiveScreenBuffer(consoleOutputHandle);
        for (char const *iterator = argument; '\0' ^ *iterator; ++iterator) ++length;

        // ...
        // std::cout << "\r\n[ARGUMENT]: \"" << argument << '"' << std::endl;
        ::WriteFile(consoleOutputHandle, argument, length, NULL, NULL);
    }
}
inline void print(int argument) noexcept { if (0 == argument) print("0x0"); else { if (argument < 0) { argument = -argument; print('-'); } print("0x"); for (char output[9] {'0', '0', '0', '0', '0', '0', '0', '0', '\0'}, *iterator = output; argument; ++iterator) { *iterator = *("0123456789ABCDEF" + (argument % 16)); if (0 == (argument /= 16)) { iterator = output + (sizeof(output) - 2u); for (char *subiterator = output; iterator > subiterator; (--iterator, ++subiterator)) { *iterator ^= *subiterator; *subiterator ^= *iterator; *iterator ^= *subiterator; } print((char const*) output); } } } }
inline void print(print_line const& argument) noexcept { argument.operator()(); }
inline void print(print_tab const& argument) noexcept { argument.operator()(); }
template <class type, class... types> inline void print(type argument, types... arguments) { print(argument); print(arguments...); }
