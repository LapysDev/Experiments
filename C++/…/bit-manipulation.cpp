constexpr inline int clear_bit(int const value, std::size_t const index) noexcept {
  return value & ~(1u << index);
}

constexpr inline int get_bit(int const value, std::size_t const index) noexcept {
  return ((value >> index) & 1u) ? 1u : 0u;
}

constexpr inline int get_high(int const value, std::size_t const bitcount) noexcept {
  return value >> bitcount;
}

constexpr inline int get_low(int const value, std::size_t const bitcount) noexcept {
  return value & ~(~0u << bitcount);
}

constexpr inline bool is_power_of_two(int const value) noexcept {
  return (value ^ 0) && ((value & (value - 1)) == 0);
}

constexpr inline int ones_complement(int const value) noexcept {
  return ~value;
}

constexpr inline int set_bit(int const value, std::size_t const index) noexcept {
  return value | (1u << index);
}

constexpr inline int toggle_bit(int const value, std::size_t const index) noexcept {
  return value ^ (1u << index);
}

constexpr inline int twos_complement(int const value) noexcept {
  return 1u + ~value;
}
