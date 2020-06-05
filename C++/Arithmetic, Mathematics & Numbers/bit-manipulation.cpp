/* Function > ... */
constexpr inline int clear_bit(int const number, size_t const index) noexcept { return number & ~(1uLL << index); }
constexpr inline int get_bit(int const number, size_t const index) noexcept { return ((number >> index) & 1uLL) ? 1 : 0; }
constexpr inline int set_bit(int const number, size_t const index) noexcept { return number | (1uLL << index); }
constexpr inline int toggle_bit(int const number, size_t const index) noexcept { return number ^ (1uLL << index); }

/* Main */
int main(void) { return 0; }
