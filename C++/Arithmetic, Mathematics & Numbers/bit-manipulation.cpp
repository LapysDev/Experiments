/* Definition > ... */
typedef unsigned char size_t;

/* Function > ... */
constexpr inline int clear_bit(int const number, size_t const index) noexcept { return number & ~(1u << index); }
constexpr inline int get_bit(int const number, size_t const index) noexcept { return ((number >> index) & 1u) ? 1u : 0u; }
constexpr inline int get_high(int const number, size_t bitcount = sizeof(int) / 2u) noexcept { return number >> bitcount; }
constexpr inline int get_low(int const number, size_t bitcount = sizeof(int) / 2u) noexcept { return number & ~(~0u << bitcount); }
constexpr inline int set_bit(int const number, size_t const index) noexcept { return number | (1u << index); }
constexpr inline int toggle_bit(int const number, size_t const index) noexcept { return number ^ (1u << index); }

/* Main */
int main(void) { return EXIT_SUCCESS; }
