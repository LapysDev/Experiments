/* WARN (Lapys) -> No (or primitive) buffering, formatting or memory management. */
/* Definition > ... */
struct print_line;
struct print_tab;

constexpr void print(void) noexcept;
void print(bool const) noexcept;
void print(char const) noexcept;
void print(char* const) noexcept;
void print(char const* const) noexcept;
void print(double const) noexcept;
void print(float const) noexcept;
void print(int const) noexcept;
void print(long const) noexcept;
void print(long double const) noexcept;
void print(short const) noexcept;
void print(signed char const) noexcept;
void print(unsigned char const) noexcept;
void print(unsigned int const) noexcept;
void print(unsigned long const) noexcept;
void print(unsigned short const) noexcept;
void print(wchar_t const) noexcept;
void print(wchar_t* const) noexcept;
void print(wchar_t const* const) noexcept;
void print(print_line const&) noexcept;
void print(print_tab const&) noexcept;
template <class type> void print(type&) noexcept;
template <class type> void print(type* const) noexcept;
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

/* Function > Print --- WARN (Lapys) -> Assumes pointers are 32-bit wide. */
constexpr inline void print(void) noexcept {}
inline void print(bool const argument) noexcept { print(argument ? "true" : "false"); }
inline void print(char const argument) noexcept { ::putchar(argument); }
inline void print(char* const argument) noexcept { print((char const*) argument); }
inline void print(char const* const argument) noexcept { if (NULL != argument) ::printf("%s", argument); }
inline void print(double const argument) noexcept { ::printf("%g", argument); }
inline void print(float const argument) noexcept { ::printf("%f", argument); }
inline void print(int const argument) noexcept { ::printf("%i", argument); }
inline void print(long const argument) noexcept { ::printf("%ld", argument); }
inline void print(long double const argument) noexcept { print((double) argument); }
inline void print(short const argument) noexcept { ::printf("%i", argument); }
inline void print(signed char const argument) noexcept { ::printf("%i", argument); }
inline void print(unsigned char const argument) noexcept { ::printf("%u", argument); }
inline void print(unsigned int const argument) noexcept { ::printf("%u", argument); }
inline void print(unsigned long const argument) noexcept { ::printf("%lu", argument); }
inline void print(unsigned short const argument) noexcept { ::printf("%u", argument); }
inline void print(wchar_t const argument) noexcept { ::printf("%c", argument); }
inline void print(wchar_t* const argument) noexcept { print((wchar_t const*) argument); }
inline void print(wchar_t const* const argument) noexcept { if (NULL != argument) ::printf("%ls", argument); }
inline void print(print_line& argument) noexcept { argument.operator()(); }
inline void print(print_tab& argument) noexcept { argument.operator()(); }
template <class type> inline void print(type&) noexcept { print("<object>"); }
template <class type> inline void print(type* const argument) noexcept { int pointer = *(int*) &argument; char string[9] {'0', '0', '0', '0', '0', '0', '0', '0', '\0'}; for (char *iterator = string + 8; iterator-- != string; pointer /= 10) *iterator = *("0123456789ABCDEF" + (pointer % 10)); print("0x", string); }
template <class type, class... types> inline void print(type argument, types... arguments) { print(argument); print(arguments...); }
