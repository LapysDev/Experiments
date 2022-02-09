/* ... */
#include <stdint.h>

#define LITTLE_ENDIAN 0
#define BIG_ENDIAN    1
#define WORDS_LITTLE_ENDIAN 2

#if defined(__cplusplus) && __cplusplus >= 202002L
# include <bit>
# define ENDIANNESS (std::endian::native == std::endian::little ? LITTLE_ENDIAN : BIG_ENDIAN)
#else
# undef ENDIAN_DETECTED

# if !defined(ENDIAN_DETECTED) && defined(__GLIBC__)
#  include <endian.h>

#  if defined(__BYTE_ORDER)
#   if   defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN
#    define ENDIAN_DETECTED
#    define ENDIANNESS LITTLE_ENDIAN
#   elif defined(__BIG_ENDIAN   ) && __BYTE_ORDER == __BIG_ENDIAN
#    define ENDIAN_DETECTED
#    define ENDIANNESS BIG_ENDIAN
#   endif
#  endif
# endif

# if !defined(ENDIAN_DETECTED) && defined(__GNUC__)
#  if defined(__BYTE_ORDER__)
#   if   defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#    define ENDIAN_DETECTED
#    define ENDIANNESS LITTLE_ENDIAN
#   elif defined(__ORDER_BIG_ENDIAN__   ) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#    define ENDIAN_DETECTED
#    define ENDIANNESS BIG_ENDIAN
#   endif
#  endif
# endif

# if !defined(ENDIAN_DETECTED)
#  if   defined(_LITTLE_ENDIAN) && false == defined(_BIG_ENDIAN)
#   define ENDIAN_DETECTED
#   define ENDIANNESS LITTLE_ENDIAN
#  elif defined(_BIG_ENDIAN) && false == defined(_LITTLE_ENDIAN)
#   define ENDIAN_DETECTED
#   define ENDIANNESS BIG_ENDIAN
#  endif
# endif

# if !defined(ENDIAN_DETECTED)
#  if defined(__hppa) || defined(__hpux) || defined(_MIPSEB) || defined(_POWER) || defined(__powerpc__) || defined(__ppc__) || defined(_POWER) || defined(__s390__) || defined(__sparc) || defined(__sparc__)
#   define ENDIAN_DETECTED
#   define ENDIANNESS BIG_ENDIAN
#  elif (defined(_MSC_VER) && (defined(_M_ARM) || defined(_M_ARM64))) || (defined(__amd64) || defined(__amd64__) || defined(__bfin__) || defined(__i386__) || defined(__alpha__) || defined(__ia64) || defined(__ia64__) || defined(_M_ALPHA) || defined(_M_AMD64) || defined(_M_IA64) || defined(_M_IX86) || defined(_M_X64) || defined(__x86_64) || defined(__x86_64__))
#   define ENDIAN_DETECTED
#   define ENDIANNESS LITTLE_ENDIAN
#  endif
# endif

# if !defined(ENDIAN_DETECTED)
#  include <stdint.h>

   static uint16_t const ENDIANNESS = 1u;
#  define ENDIANNESS (1u == *static_cast<uint8_t const*>(static_cast<void const*>(&ENDIANNESS)) ? LITTLE_ENDIAN : BIG_ENDIAN)
# endif

# undef ENDIAN_DETECTED
#endif

/* Main */
#include <cstdio>

int main() {
  std::printf("%12s", "Endianness: ");
  switch (ENDIANNESS) {
    case BIG_ENDIAN         : std::puts("BIG");    break;
    case LITTLE_ENDIAN      : std::puts("LITTLE"); break;
    case WORDS_LITTLE_ENDIAN: std::puts("MIXED");  break;
  }
}
