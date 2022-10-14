#include <climits>
#include <cstdio>
#include <stdint.h>
#if __cplusplus >= 202002L || _MSVC_LANG >= 202002L
# include <version>
#endif
#if defined(__cpp_lib_endian)
# include <bit>
#elif defined(__GLIBC__)
# include <endian.h>
#elif defined(__APPLE__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__MACH__) || defined(__OpenBSD__) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9)
# include <machine/endian.h>
#elif defined(__bsdi__) || defined(__DragonFly__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(__OpenBSD__) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9)
# include <sys/endian.h>
#endif

/* ... */
uint_least8_t get_utf8_codepoint_length(char const unit[]) {
  unsigned char const value = static_cast<unsigned char>(*unit);

  // ...
  if (/* value >= 0x00u && */ value <= 0x7Fu) return 1u;
  else if  (value >= 0xC0u && value <= 0xDFu) return 2u;
  else if  (value >= 0xE0u && value <= 0xEFu) return 3u;
  else if  (value >= 0xF0u && value <= 0xF7u) return 4u;

  return -1;
}

uint_least32_t get_utf8_codepoint_value(char const unit[]) {
  enum { big_endian, little_endian, pdp_endian } const
  #ifdef __cpp_lib_endian
    endian = std::endian::native == std::endian::little ? little_endian : big_endian;
  #elif (                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                \
    (defined(__GLIBC__) && ((defined(_BYTE_ORDER) && (defined(_LITTLE_ENDIAN) && _BYTE_ORDER == _LITTLE_ENDIAN)) || (defined(__BYTE_ORDER) && (defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN)))) ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        \
    (defined(__GNUC__) && (defined(__BYTE_ORDER__) && (defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)))                                                                        ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        \
    (defined(__LITTLE_ENDIAN__) && false == defined(__BIG_ENDIAN__)) || (defined(_LITTLE_ENDIAN) && false == defined(_BIG_ENDIAN))                                                                             ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        \
    defined(__AARCH64EL__) || defined(__ARMEL__) || defined(__MIPSEL) || defined(__MIPSEL__) || defined(__THUMBEL__) || defined(_MIPSEL)                                                                       ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        \
    defined(__alpha__) || defined(__amd64) || defined(__amd64) || defined(__amd64__) || defined(__amd64__) || defined(__bfin__) || defined(__BFIN__) || defined(__i386) || defined(__i386__) || defined(__i486__) || defined(__i486__) || defined(__i586__) || defined(__i586__) || defined(__i686__) || defined(__I86__) || defined(__ia64) || defined(__ia64__) || defined(__IA64__) || defined(__INTEL__) || defined(__itanium__) || defined(__THW_INTEL__) || defined(__x86_64) || defined(__x86_64__) || defined(_IA64) || defined(_M_ALPHA) || defined(_M_AMD64) || defined(_M_IA64) || defined(_M_IX86) || defined(_M_X64) || defined(_X86_) || defined(bfin) || defined(BFIN) || defined(i386) || ((CPP_VENDOR & CPP_MICROSOFT_WINDOWS_VENDOR) && (defined(__arm64) || defined(__arm__) || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB) || defined(__thumb__) || defined(_M_ARM))) \
  )
    endian = little_endian;
  #elif (                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
    (defined(__GLIBC__) && ((defined(_BYTE_ORDER) && (defined(_BIG_ENDIAN) && _BYTE_ORDER == _BIG_ENDIAN)) || (defined(__BYTE_ORDER) && (defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN)))) ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
    (defined(__GNUC__) && (defined(__BYTE_ORDER__) && (defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)))                                                                  ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
    (defined(__BIG_ENDIAN__) && false == defined(__LITTLE_ENDIAN__)) || (defined(_BIG_ENDIAN) && false == defined(_LITTLE_ENDIAN))                                                                 ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
    defined(__AARCH64EB__) || defined(__ARMEB__) || defined(__MIPSEB) || defined(__MIPSEB__) || defined(__THUMBEB__) || defined(_MIPSEB)                                                           ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
    defined(__370__) || defined(__hppa) || defined(__hpux) || defined(__m68k__) || defined(__mc68000) || defined(__mc68000__) || defined(__mc68010) || defined(__mc68010__) || defined(__mc68020) || defined(__mc68020__) || defined(__mc68030) || defined(__mc68030__) || defined(__mc68040) || defined(__mc68040__) || defined(__mc68060) || defined(__mc68060__) || defined(__powerpc__) || defined(__ppc__) || defined(__s390__) || defined(__s390__) || defined(__s390x__) || defined(__sparc) || defined(__sparc__) || defined(__sparcv8) || defined(__sparcv9) || defined(__SYSC_ZARCH__) || defined(__THW_370__) || defined(_POWER) || defined(M68000) || defined(mc68000) || defined(mc68010) || defined(mc68020) || defined(mc68030) || defined(mc68040) || defined(mc68060) \
  )
    endian = big_endian;
  #elif (                                                                                                                                                                                             \
    (defined(__GLIBC__) && ((defined(_BYTE_ORDER) && (defined(_PDP_ENDIAN) && _BYTE_ORDER == _PDP_ENDIAN)) || (defined(__BYTE_ORDER) && (defined(__PDP_ENDIAN) && __BYTE_ORDER == __PDP_ENDIAN)))) || \
    (defined(__GNUC__) && (defined(__BYTE_ORDER__) && (defined(__ORDER_PDP_ENDIAN__) && __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__)))                                                                     \
  )
    endian = pdp_endian;
  #else
    endian = 1u == reinterpret_cast<unsigned char const&>(static_cast<uintmax_t const&>(1u)) ? little_endian : big_endian;
  #endif

  switch (get_utf8_codepoint_length(unit)) {
    case 1u:
      return static_cast<unsigned char>(*unit) & 0x7Fu;

    case 2u: switch (endian) {
      case big_endian                    : return ((static_cast<unsigned char>(unit[0]) & 0x1Fu) << 0u) | ((static_cast<unsigned char>(unit[1]) & 0x3Fu) << 6u);
      case little_endian: case pdp_endian: return ((static_cast<unsigned char>(unit[1]) & 0x3Fu) << 0u) | ((static_cast<unsigned char>(unit[0]) & 0x1Fu) << 6u);
    } break;

    case 3u: switch (endian) {
      case big_endian   : return (((static_cast<unsigned char>(unit[0]) & 0x0Fu) << 0u)) | (((static_cast<unsigned char>(unit[1]) & 0x3Fu) << 6u)) | (((static_cast<unsigned char>(unit[2]) & 0x3Fu) << 12u));
      case little_endian: return (((static_cast<unsigned char>(unit[2]) & 0x3Fu) << 0u)) | (((static_cast<unsigned char>(unit[1]) & 0x3Fu) << 6u)) | (((static_cast<unsigned char>(unit[0]) & 0x0Fu) << 12u));
      case pdp_endian   : return (((static_cast<unsigned char>(unit[1]) & 0x3Fu) << 0u)) | (((static_cast<unsigned char>(unit[0]) & 0x0Fu) << 6u)) | (((static_cast<unsigned char>(unit[2]) & 0x3Fu) << 12u));
    } break;

    case 4u: switch (endian) {
      case big_endian   : return (((static_cast<unsigned char>(unit[0]) & 0x07u) << 0u)) | (((static_cast<unsigned char>(unit[1]) & 0x3Fu) << 6u)) | (((static_cast<unsigned char>(unit[2]) & 0x3Fu) << 12u)) | (((static_cast<unsigned char>(unit[3]) & 0x3Fu) << 18u));
      case little_endian: return (((static_cast<unsigned char>(unit[3]) & 0x3Fu) << 0u)) | (((static_cast<unsigned char>(unit[2]) & 0x3Fu) << 6u)) | (((static_cast<unsigned char>(unit[1]) & 0x3Fu) << 12u)) | (((static_cast<unsigned char>(unit[0]) & 0x07u) << 18u));
      case pdp_endian   : return (((static_cast<unsigned char>(unit[2]) & 0x3Fu) << 0u)) | (((static_cast<unsigned char>(unit[3]) & 0x3Fu) << 6u)) | (((static_cast<unsigned char>(unit[0]) & 0x07u) << 12u)) | (((static_cast<unsigned char>(unit[1]) & 0x3Fu) << 18u));
    }
  }

  return -1;
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  char const unit[] = "$"; // --> U+0024
  // char const unit[] = "£"; // --> U+00A3
  // char const unit[] = "€"; // --> U+20AC
  // char const unit[] = "𐍈"; // --> U+10348
  // char const unit[] = "💙";

  // ...
  for (char const *byte = unit; byte != unit + (sizeof(unit) / sizeof(char)); ++byte)
  std::printf("0x%.2X" " ", static_cast<unsigned char>(*byte));

  std::printf("(%hu)" "\r\n", get_utf8_codepoint_length(unit));
  std::printf("0x%lX" "\r\n", static_cast<unsigned long>(get_utf8_codepoint_value(unit)));
}
