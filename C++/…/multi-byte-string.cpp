#include <clocale>
#include <cstdio>
#include <cwchar>

/* ... */
void print(char const* string) {
  char const    *end   = string;
  std::mbstate_t state = std::mbstate_t();

  // ...
  while ('\0' != *end)
    ++end;

  while (true) {
    wchar_t           character = L'\0';
    std::size_t const count     = std::mbrtowc(&character, string, end - string, &state);

    // ...    
    if (0u == count)
    break;

    if (count == static_cast<std::size_t>(-1) or count == static_cast<std::size_t>(-2))
    break;

    (void) std::printf("%lc", character);
    string += count;
  }
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  std::setlocale(LC_ALL, "en_US.utf8");
  print("z" "\u00Df" "\u6C34" "\U0001D10B"); // --> u8"zß水𝄋" --> "\x7A\xC3\x9F\xE6\xB0\xB4\xF0\x9D\x84\x8B"
}
