#include <ciso646>
#include <cstddef>
#include <cstdio>
#include <cwchar>

/* Main */
int main(int, char*[]) /* noexcept */ {
  unsigned char encoded[] = {
    '\0', 'H',  '\0', '\0', '\0',
    '\0', 'e',  '\0', '-',  '\0',
    '\0', 'l',  '\0', '\0', '\0',
    '\0', 'l',  '\0', '-', '\0',
    '\0', 'o',  '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0',
  };
  // wchar_t     const encoded[]       = L"Set up internal clock via the Task Scheduler ⏱️";
  std::size_t const stride          = 5u;
  char              unencoded[2048] = "";

  // ...
  for (std::size_t index = 0u, length = 0u; ; index += stride) {
    unsigned char const *const character      = reinterpret_cast<unsigned char const*>(encoded) + index;
    bool                       characterIsNUL = true;
    std::size_t                currentIndex   = 0u;
    std::size_t                nextIndex      = 0u;

    // ... ->> Ignores `character` endianness, leading bytes, and trailing bytes (assumes it is a distinct set of `stride` code units)
    for (; currentIndex != stride; ++currentIndex)
    if (0x00u != character[currentIndex]) {
      characterIsNUL = false;
      break;
    }

    if (characterIsNUL)
    break;

    for (bool redundant = false; currentIndex != stride and not redundant; ++currentIndex) {
      nextIndex           = currentIndex + 1u;
      unencoded[length++] = static_cast<char>(character[currentIndex]);

      for (redundant = true; nextIndex != stride; ++nextIndex)
      if (0x00u != character[nextIndex]) {
        redundant = false;
        break;
      }

      if (not redundant and 0x00u == character[currentIndex]) {
        length           -= currentIndex;
        unencoded[length++] = '?';

        break;
      }
    }
  }
  
  // ...
  // std::fprintf(stderr, "[encoded]  : ");
  //   for (unsigned char const *iterator = reinterpret_cast<unsigned char const*>(encoded); iterator != reinterpret_cast<unsigned char const*>(encoded) + sizeof encoded; ++iterator)
  //   std::fprintf(stderr, "%02X" " ", (unsigned) *iterator);
  // std::fprintf(stderr, "\r\n");
  // std::fwprintf(stderr, L"[encoded]  : \"%ls\"" "\r\n", encoded);
  
  // std::fprintf(stdout, "[unencoded]: ");
  //   for (unsigned char const *iterator = reinterpret_cast<unsigned char const*>(unencoded); iterator != reinterpret_cast<unsigned char const*>(unencoded) + sizeof encoded; ++iterator)
  //   std::fprintf(stdout, "%02X" " ", (unsigned) *iterator);
  // std::fprintf(stdout, "\r\n");
  std::fprintf(stdout,  "[unencoded]: \"%s\"" "\r\n", unencoded);
}
