/* ... */
#include <cstdio>

// ...
inline char const*& put(void) noexcept;
inline void put(char const[]) noexcept;
inline void put(std::size_t const) noexcept;
template <typename... types> inline void put(char const[], types...) noexcept;
template <typename... types> inline void put(std::size_t const, types...) noexcept;
template <typename... types> inline void put(char const[], char const[], types...) noexcept;

// ...
inline char const*& put(void) noexcept { static char const *message; return message; }
inline void put(char const message[]) noexcept { std::printf("%s", message); }
template <typename... types> inline void put(char const message[], types... arguments) noexcept { put() = message; put(arguments...); }
template <typename... types> inline void put(std::size_t const length, types... arguments) noexcept { std::printf("%.*s", static_cast<int>(length), put()); put(arguments...); }
template <typename... types> inline void put(char const message[], char const argument[], types... arguments) noexcept { std::printf("%s", message); put(argument, arguments...); }

/* ... */
int main(void) {
  put("This is a sentence, isn't it?" "\r\n");
  put("This is a shorter sentence", 18u, "..." " ");
  put("sentence" "\r\n", 8u + 2u);
  put("Hello, World!", 6u, "\r\n", "D'ya know 'Lorem ipsum' is exactly 10 characters long?", 27u, "...");
}
