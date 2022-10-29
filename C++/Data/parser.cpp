#include <climits>
#include <cstddef>
#include <cstdio>
#include <stdint.h>
#if defined(_MSVC_LANG) ? _MSVC_LANG >= 202002L : __cplusplus >= 202002L
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
struct parse_t /* final */ {
  enum encoding /* : uint16_t */ {
    _default = 0x000u,

    adobe_standard_encoding, adobe_symbol_encoding, amiga_1251, ansi_x3_110_1983, ansi_x3_4_1968, ansi_x3_4_1986, arabic, arabic7, asmo_449, asmo_708,
    big5, big5_hkscs, bocu_1, brf, bs_4730, bs_viewdata,
    ca, ccsid00858, ccsid00924, ccsid01140, ccsid01141, ccsid01142, ccsid01143, ccsid01144, ccsid01145, ccsid01146, ccsid01147, ccsid01148, ccsid01149, cesu_8, chinese, cn, cp00858, cp00924, cp01140, cp01141, cp01142, cp01143, cp01144, cp01145, cp01146, cp01147, cp01148, cp01149, cp037, cp038, cp1026, cp154, cp273, cp274, cp275, cp278, cp280, cp281, cp284, cp285, cp290, cp297, cp367, cp420, cp423, cp424, cp437, cp500, cp50220, cp51932, cp775, cp819, cp850, cp851, cp852, cp855, cp857, cp860, cp861, cp862, cp863, cp864, cp865, cp866, cp868, cp869, cp870, cp871, cp880, cp891, cp903, cp904, cp905, cp918, cp936, cp_ar, cp_gr, cp_is, csa71, csa72, csa7_1, csa7_2, csa_t500_1983, csa_z243_4_1985_1, csa_z243_4_1985_2, csa_z243_4_1985_gr, csadobestandardencoding, csascii, csbig5, csbig5hkscs, csbocu1, csbocu_1, csbrf, cscesu8, cscesu_8, cscp51932, csdecmcs, csdkus, csebcdicatdea, csebcdiccafr, csebcdicdkno, csebcdicdknoa, csebcdices, csebcdicesa, csebcdicess, csebcdicfise, csebcdicfisea, csebcdicfr, csebcdicit, csebcdicpt, csebcdicuk, csebcdicus, cseucfixwidjapanese, cseuckr, cseucpkdfmtjapanese, csgb18030, csgb2312, csgbk, cshalfwidthkatakana, cshpdesktop, cshplegal, cshpmath8, cshppifont, cshppsmath, cshproman8, csibbm904, csibm00858, csibm00924, csibm01140, csibm01141, csibm01142, csibm01143, csibm01144, csibm01145, csibm01146, csibm01147, csibm01148, csibm01149, csibm037, csibm038, csibm1026, csibm1047, csibm273, csibm274, csibm275, csibm277, csibm278, csibm280, csibm281, csibm284, csibm285, csibm290, csibm297, csibm420, csibm423, csibm424, csibm500, csibm851, csibm855, csibm857, csibm860, csibm861, csibm863, csibm864, csibm865, csibm866, csibm868, csibm869, csibm870, csibm871, csibm880, csibm891, csibm903, csibm905, csibm918, csibmebcdicatde, csibmsymbols, csibmthai, csinvariant, csiso102t617bit, csiso10367box, csiso103t618bit, csiso10646utf1, csiso10swedish, csiso111ecmacyrillic, csiso115481, csiso11swedishfornames, csiso121canadian1, csiso122canadian2, csiso123csaz24341985gr, csiso128t101g2, csiso139csn369103, csiso13jisc6220jp, csiso141jusib1002, csiso143iecp271, csiso146serbian, csiso147macedonian, csiso14jisc6220ro, csiso150, csiso150greekccitt, csiso151cuba, csiso153gost1976874, csiso158lap, csiso159jisx02121990, csiso15italian, csiso16portuguese, csiso17spanish, csiso18greek7old, csiso19latingreek, csiso2022cn, csiso2022cnext, csiso2022jp, csiso2022jp2, csiso2022kr, csiso2033, csiso21german, csiso25french, csiso27latingreek1, csiso2intlrefversion, csiso42jisc62261978, csiso47bsviewdata, csiso49inis, csiso4unitedkingdom, csiso50inis8, csiso51iniscyrillic, csiso54271981, csiso5427cyrillic, csiso5428greek, csiso57gb1988, csiso58gb231280, csiso60danishnorwegian, csiso60norwegian, csiso61norwegian2, csiso646basic1983, csiso646danish, csiso6937add, csiso69french, csiso70videotexsupp1, csiso84portuguese2, csiso85spanish2, csiso86hungarian, csiso87jisx0208, csiso885913, csiso885914, csiso885915, csiso885916, csiso88596e, csiso88596i, csiso88598e, csiso88598i, csiso8859supp, csiso88greek7, csiso89asmo449, csiso90, csiso91jisc62291984a, csiso92jisc62991984b, csiso93jis62291984badd, csiso94jis62291984hand, csiso95jis62291984handadd, csiso96jisc62291984kana, csiso99naplps, csisolatin1, csisolatin2, csisolatin3, csisolatin4, csisolatin5, csisolatin6, csisolatinarabic, csisolatincyrillic, csisolatingreek, csisolatinhebrew, csisotextcomm, csjisencoding, cskoi7switched, cskoi8r, cskoi8u, csksc56011987, csksc5636, cskz1048, csmacintosh, csmicrosoftpublishing, csmnem, csmnemonic, csn_369103, csnatsdano, csnatsdanoadd, csnatssefi, csnatssefiadd, csosdebcdicdf03irv, csosdebcdicdf041, csosdebcdicdf0415, cspc775baltic, cspc850multilingual, cspc862latinhebrew, cspc8codepage437, cspc8danishnorwegian, cspc8turkish, cspcp852, csptcp154, csscsu, csshiftjis, cstis620, cstscii, csucs4, csunicode, csunicode11, csunicode11utf7, csunicodeascii, csunicodeibm1261, csunicodeibm1264, csunicodeibm1265, csunicodeibm1268, csunicodeibm1276, csunicodejapanese, csunicodelatin1, csunknown8bit, csusdk, csutf16, csutf16be, csutf16le, csutf32, csutf32be, csutf32le, csutf7, csutf8, csventurainternational, csventuramath, csventuraus, csviqr, csviscii, cswindows1250, cswindows1251, cswindows1252, cswindows1253, cswindows1254, cswindows1255, cswindows1256, cswindows1257, cswindows1258, cswindows30latin1, cswindows31j, cswindows31latin1, cswindows31latin2, cswindows31latin5, cswindows874, cuba, cyrillic, cyrillic_asian,
    de, dec, dec_mcs, din_66003, dk, dk_us, ds2089, ds_2089, e13b, ebcdic_at_de, ebcdic_at_de_a, ebcdic_be, ebcdic_br, ebcdic_ca_fr, ebcdic_cp_ar1, ebcdic_cp_ar2, ebcdic_cp_be, ebcdic_cp_ca, ebcdic_cp_ch, ebcdic_cp_dk, ebcdic_cp_es, ebcdic_cp_fi, ebcdic_cp_fr, ebcdic_cp_gb, ebcdic_cp_gr, ebcdic_cp_he, ebcdic_cp_is, ebcdic_cp_it, ebcdic_cp_nl, ebcdic_cp_no, ebcdic_cp_roece, ebcdic_cp_se, ebcdic_cp_tr, ebcdic_cp_us, ebcdic_cp_wt, ebcdic_cp_yu, ebcdic_cyrillic, ebcdic_de_273_euro, ebcdic_dk_277_euro, ebcdic_dk_no, ebcdic_dk_no_a, ebcdic_es, ebcdic_es_284_euro, ebcdic_es_a, ebcdic_es_s, ebcdic_fi_278_euro, ebcdic_fi_se, ebcdic_fi_se_a, ebcdic_fr, ebcdic_fr_297_euro, ebcdic_gb_285_euro, ebcdic_int, ebcdic_international_500_euro, ebcdic_is_871_euro, ebcdic_it, ebcdic_it_280_euro, ebcdic_jp_e, ebcdic_jp_kana, ebcdic_latin9__euro, ebcdic_no_277_euro, ebcdic_pt, ebcdic_se_278_euro, ebcdic_uk, ebcdic_us, ebcdic_us_37_euro, ecma_114, ecma_118, ecma_cyrillic, elot_928, es, es2, euc_jp, euc_kr, extended_unix_code_fixed_width_for_japanese, extended_unix_code_packed_format_for_japanese,
    fi, fr,
    gb, gb18030, gb2312, gb_1988_80, gb_2312_80, gbk, gost_19768_74, greek, greek7, greek7_old, greek8, greek_ccitt,
    hebrew, hp_desktop, hp_legal, hp_math8, hp_pi_font, hp_roman8, hu, hz_gb_2312,
    ibm00858, ibm00924, ibm01140, ibm01141, ibm01142, ibm01143, ibm01144, ibm01145, ibm01146, ibm01147, ibm01148, ibm01149, ibm037, ibm038, ibm1026, ibm1047, ibm273, ibm274, ibm275, ibm277, ibm278, ibm280, ibm281, ibm284, ibm285, ibm290, ibm297, ibm367, ibm420, ibm423, ibm424, ibm437, ibm500, ibm775, ibm819, ibm850, ibm851, ibm852, ibm855, ibm857, ibm860, ibm861, ibm862, ibm863, ibm864, ibm865, ibm866, ibm868, ibm869, ibm870, ibm871, ibm880, ibm891, ibm903, ibm904, ibm905, ibm918, ibm_1047, ibm_symbols, ibm_thai, iec_p27_1, inis, inis_8, inis_cyrillic, invariant, irv, iso5427cyrillic1981, iso646_ca, iso646_ca2, iso646_cn, iso646_cu, iso646_de, iso646_dk, iso646_es, iso646_es2, iso646_fi, iso646_fr, iso646_fr1, iso646_gb, iso646_hu, iso646_it, iso646_jp, iso646_jp_ocr_b, iso646_kr, iso646_no, iso646_no2, iso646_pt, iso646_pt2, iso646_se, iso646_se2, iso646_us, iso646_yu, iso_10367_box, iso_10646, iso_10646_j_1, iso_10646_ucs_2, iso_10646_ucs_4, iso_10646_ucs_basic, iso_10646_unicode_latin1, iso_10646_utf_1, iso_11548_1, iso_2022_cn, iso_2022_cn_ext, iso_2022_jp, iso_2022_jp_2, iso_2022_kr, iso_2033_1983, iso_5427, iso_5427_1981, iso_5428_1980, iso_646_basic_1983, iso_646_irv_1983, iso_646_irv_1991, iso_6937_2_25, iso_6937_2_add, iso_8859_1, iso_8859_10, iso_8859_10_1992, iso_8859_11, iso_8859_13, iso_8859_14, iso_8859_14_1998, iso_8859_15, iso_8859_16, iso_8859_16_2001, iso_8859_1_1987, iso_8859_1_windows_3_0_latin_1, iso_8859_1_windows_3_1_latin_1, iso_8859_2, iso_8859_2_1987, iso_8859_2_windows_latin_2, iso_8859_3, iso_8859_3_1988, iso_8859_4, iso_8859_4_1988, iso_8859_5, iso_8859_5_1988, iso_8859_6, iso_8859_6_1987, iso_8859_6_e, iso_8859_6_i, iso_8859_7, iso_8859_7_1987, iso_8859_8, iso_8859_8_1988, iso_8859_8_e, iso_8859_8_i, iso_8859_9, iso_8859_9_1989, iso_8859_9_windows_latin_5, iso_8859_supp, iso_9036, iso_celtic, iso_ir_10, iso_ir_100, iso_ir_101, iso_ir_102, iso_ir_103, iso_ir_109, iso_ir_11, iso_ir_110, iso_ir_111, iso_ir_121, iso_ir_122, iso_ir_123, iso_ir_126, iso_ir_127, iso_ir_128, iso_ir_13, iso_ir_138, iso_ir_139, iso_ir_14, iso_ir_141, iso_ir_142, iso_ir_143, iso_ir_144, iso_ir_146, iso_ir_147, iso_ir_148, iso_ir_149, iso_ir_15, iso_ir_150, iso_ir_151, iso_ir_152, iso_ir_153, iso_ir_154, iso_ir_155, iso_ir_157, iso_ir_158, iso_ir_159, iso_ir_16, iso_ir_17, iso_ir_18, iso_ir_19, iso_ir_199, iso_ir_2, iso_ir_21, iso_ir_226, iso_ir_25, iso_ir_27, iso_ir_37, iso_ir_4, iso_ir_42, iso_ir_47, iso_ir_49, iso_ir_50, iso_ir_51, iso_ir_54, iso_ir_55, iso_ir_57, iso_ir_58, iso_ir_6, iso_ir_60, iso_ir_61, iso_ir_69, iso_ir_70, iso_ir_84, iso_ir_85, iso_ir_86, iso_ir_87, iso_ir_88, iso_ir_89, iso_ir_8_1, iso_ir_8_2, iso_ir_90, iso_ir_91, iso_ir_92, iso_ir_93, iso_ir_94, iso_ir_95, iso_ir_96, iso_ir_98, iso_ir_99, iso_ir_9_1, iso_ir_9_2, iso_tr_11548_1, iso_unicode_ibm_1261, iso_unicode_ibm_1264, iso_unicode_ibm_1265, iso_unicode_ibm_1268, iso_unicode_ibm_1276, it,
    jis_c6220_1969, jis_c6220_1969_jp, jis_c6220_1969_ro, jis_c6226_1978, jis_c6226_1983, jis_c6229_1984_a, jis_c6229_1984_b, jis_c6229_1984_b_add, jis_c6229_1984_hand, jis_c6229_1984_hand_add, jis_c6229_1984_kana, jis_encoding, jis_x0201, jis_x0208_1983, jis_x0212_1990, jp, jp_ocr_a, jp_ocr_b, jp_ocr_b_add, jp_ocr_hand, jp_ocr_hand_add, js, jus_i_b1_002, jus_i_b1_003_mac, jus_i_b1_003_serb,
    katakana, koi7_switched, koi8_e, koi8_r, koi8_u, korean, ks_c_5601_1987, ks_c_5601_1989, ksc5636, ksc_5601, kz_1048,
    l1, l10, l2, l3, l4, l5, l6, l8, lap, latin1, latin10, latin1_2_5, latin2, latin3, latin4, latin5, latin6, latin8, latin_9, latin_greek, latin_greek_1, latin_lap,
    mac, macedonian, macintosh, microsoft_publishing, mnem, mnemonic, ms936, ms_kanji, msz_7795_3,
    naplps, nats_dano, nats_dano_add, nats_sefi, nats_sefi_add, nc_nc00_10_81, nf_z_62_010, nf_z_62_010_1973, no, no2, ns_4551_1, ns_4551_2,
    osd_ebcdic_df03_irv, osd_ebcdic_df04_1, osd_ebcdic_df04_15,
    pc8_danish_norwegian, pc8_turkish, pc_multilingual_850_euro, pt, pt154, pt2, ptcp154,
    r8, ref, rk1048, roman8,
    scsu, se, se2, sen_850200_b, sen_850200_c, serbian, shift_jis, st_sev_358_88, strk1048_2002,
    t_101_g2, t_61, t_61_7bit, t_61_8bit, tis_620, tscii,
    uk, unicode_1_1, unicode_1_1_utf_7, unknown_8bit, us, us_ascii, us_dk, utf_16, utf_16be, utf_16le, utf_32, utf_32be, utf_32le, utf_7, utf_8,
    ventura_international, ventura_math, ventura_us, videotex_suppl, viqr, viscii,
    windows_1250, windows_1251, windows_1252, windows_1253, windows_1254, windows_1255, windows_1256, windows_1257, windows_1258, windows_31j, windows_874, windows_936,
    x0201, x0201_7, x0208, x0212, x_adobe_zapf_dingbats_encoding, x_din_66303,
    yu,

    _automatic = 0x400u
  };

  std::size_t begin;
  std::size_t end;
};

template <typename sourceType, typename targetType>
/* constexpr */ std::size_t parse(sourceType const source[], std::size_t const sourceLength, targetType* target, std::size_t const targetLength, parse_t::encoding encoding = parse_t::_default) /* noexcept */ {
  enum endianness /* : unsigned char */ {
    big_endian,
    little_endian
  };

  struct parser /* final */ {
    /* constexpr */ inline static endianness endianof() /* noexcept */ {
      #ifdef __cpp_lib_endian
        return std::endian::native == std::endian::little ? little_endian : big_endian;
      #endif

      #if (                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
        (defined(__GLIBC__) && ((defined(_BYTE_ORDER) && ((defined(_LITTLE_ENDIAN) && _BYTE_ORDER == _LITTLE_ENDIAN) || (defined(_PDP_ENDIAN) && _BYTE_ORDER == _PDP_ENDIAN))) || (defined(__BYTE_ORDER) && ((defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN) || (defined(__PDP_ENDIAN) && __BYTE_ORDER == __PDP_ENDIAN))))) ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
        (defined(__GNUC__) && (defined(__BYTE_ORDER__) && ((defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || (defined(__ORDER_PDP_ENDIAN__) && __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__))))                                                                                                                ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
        (defined(__LITTLE_ENDIAN__) && false == defined(__BIG_ENDIAN__)) || (defined(_LITTLE_ENDIAN) && false == defined(_BIG_ENDIAN))                                                                                                                                                                                                    ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
        defined(__AARCH64EL__) || defined(__ARMEL__) || defined(__MIPSEL) || defined(__MIPSEL__) || defined(__THUMBEL__) || defined(_MIPSEL)                                                                                                                                                                                              ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
        defined(__alpha__) || defined(__amd64) || defined(__amd64) || defined(__amd64__) || defined(__amd64__) || defined(__bfin__) || defined(__BFIN__) || defined(__i386) || defined(__i386__) || defined(__i486__) || defined(__i486__) || defined(__i586__) || defined(__i586__) || defined(__i686__) || defined(__I86__) || defined(__ia64) || defined(__ia64__) || defined(__IA64__) || defined(__INTEL__) || defined(__itanium__) || defined(__THW_INTEL__) || defined(__x86_64) || defined(__x86_64__) || defined(_IA64) || defined(_M_ALPHA) || defined(_M_AMD64) || defined(_M_IA64) || defined(_M_IX86) || defined(_M_X64) || defined(_X86_) || defined(bfin) || defined(BFIN) || defined(i386) || ((CPP_VENDOR & CPP_MICROSOFT_WINDOWS_VENDOR) && (defined(__arm64) || defined(__arm__) || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB) || defined(__thumb__) || defined(_M_ARM))) \
      )
        return little_endian;
      #endif

      #if (                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                \
        (defined(__GLIBC__) && ((defined(_BYTE_ORDER) && (defined(_BIG_ENDIAN) && _BYTE_ORDER == _BIG_ENDIAN)) || (defined(__BYTE_ORDER) && (defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN)))) ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
        (defined(__GNUC__) && (defined(__BYTE_ORDER__) && (defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)))                                                                  ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
        (defined(__BIG_ENDIAN__) && false == defined(__LITTLE_ENDIAN__)) || (defined(_BIG_ENDIAN) && false == defined(_LITTLE_ENDIAN))                                                                 ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
        defined(__AARCH64EB__) || defined(__ARMEB__) || defined(__MIPSEB) || defined(__MIPSEB__) || defined(__THUMBEB__) || defined(_MIPSEB)                                                           ||                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
        defined(__370__) || defined(__hppa) || defined(__hpux) || defined(__m68k__) || defined(__mc68000) || defined(__mc68000__) || defined(__mc68010) || defined(__mc68010__) || defined(__mc68020) || defined(__mc68020__) || defined(__mc68030) || defined(__mc68030__) || defined(__mc68040) || defined(__mc68040__) || defined(__mc68060) || defined(__mc68060__) || defined(__powerpc__) || defined(__ppc__) || defined(__s390__) || defined(__s390__) || defined(__s390x__) || defined(__sparc) || defined(__sparc__) || defined(__sparcv8) || defined(__sparcv9) || defined(__SYSC_ZARCH__) || defined(__THW_370__) || defined(_POWER) || defined(M68000) || defined(mc68000) || defined(mc68010) || defined(mc68020) || defined(mc68030) || defined(mc68040) || defined(mc68060) \
      )
        return big_endian;
      #endif

      return sizeof(unsigned char) == sizeof(uintmax_t) || 1u == reinterpret_cast<unsigned char const&>(static_cast<uintmax_t const&>(1u)) ? little_endian : big_endian;
    }

    /* constexpr */ inline static unsigned char indexof(char          const          source[], std::size_t const index) /* noexcept */ { return static_cast<unsigned char>(source[index] - '\0'); }
    /* constexpr */ inline static unsigned char indexof(char          const volatile source[], std::size_t const index) /* noexcept */ { return static_cast<unsigned char>(source[index] - '\0'); }
    /* constexpr */ inline static unsigned char indexof(unsigned char const          source[], std::size_t const index) /* noexcept */ { return source[index]; }
    /* constexpr */ inline static unsigned char indexof(unsigned char const volatile source[], std::size_t const index) /* noexcept */ { return source[index]; }
    /* constexpr */ inline static unsigned char indexof(wchar_t       const          source[], std::size_t const index) /* noexcept */ { return 0u == MB_LEN_MAX % 16u ? (static_cast<unsigned char>(source[index / (MB_LEN_MAX / 8u)]) >> 8u * (index % (MB_LEN_MAX / 8u))) & 0xFFu : indexof(reinterpret_cast<unsigned char const*>         (source), index); }
    /* constexpr */ inline static unsigned char indexof(wchar_t       const volatile source[], std::size_t const index) /* noexcept */ { return 0u == MB_LEN_MAX % 16u ? (static_cast<unsigned char>(source[index / (MB_LEN_MAX / 8u)]) >> 8u * (index % (MB_LEN_MAX / 8u))) & 0xFFu : indexof(reinterpret_cast<unsigned char const volatile*>(source), index); }
    /* constexpr */ inline static unsigned char indexof(void const*          const   source,   std::size_t const index) /* noexcept */ { return indexof(static_cast<unsigned char const*>         (source), index); }
    /* constexpr */ inline static unsigned char indexof(void const volatile* const   source,   std::size_t const index) /* noexcept */ { return indexof(static_cast<unsigned char const volatile*>(source), index); }
    #ifdef __cpp_unicode_characters
      /* constexpr */ inline static unsigned char indexof(char16_t const          source[], std::size_t const index) /* noexcept */ { return CHAR_BIT * sizeof(char16_t) == 16u ? (static_cast<unsigned char>(source[index / 2u]) >> 8u * (index % 2u)) & 0xFFu : indexof(reinterpret_cast<unsigned char const*>         (source), index); }
      /* constexpr */ inline static unsigned char indexof(char16_t const volatile source[], std::size_t const index) /* noexcept */ { return CHAR_BIT * sizeof(char16_t) == 16u ? (static_cast<unsigned char>(source[index / 2u]) >> 8u * (index % 2u)) & 0xFFu : indexof(reinterpret_cast<unsigned char const volatile*>(source), index); }
      /* constexpr */ inline static unsigned char indexof(char32_t const          source[], std::size_t const index) /* noexcept */ { return CHAR_BIT * sizeof(char32_t) == 32u ? (static_cast<unsigned char>(source[index / 4u]) >> 8u * (index % 4u)) & 0xFFu : indexof(reinterpret_cast<unsigned char const*>         (source), index); }
      /* constexpr */ inline static unsigned char indexof(char32_t const volatile source[], std::size_t const index) /* noexcept */ { return CHAR_BIT * sizeof(char32_t) == 32u ? (static_cast<unsigned char>(source[index / 4u]) >> 8u * (index % 4u)) & 0xFFu : indexof(reinterpret_cast<unsigned char const volatile*>(source), index); }
    #endif

    /* constexpr */ inline static unsigned char lengthof(sourceType const source[], parse_t::encoding const encoding) /* noexcept */ {
      switch (encoding) {
        case parse_t::ansi_x3_4_1968: case parse_t::ansi_x3_4_1986:
        case parse_t::cp367: case parse_t::csascii:
        case parse_t::ibm367: case parse_t::iso646_us: case parse_t::iso_646_irv_1991: case parse_t::iso_ir_6:
        case parse_t::us: case parse_t::us_ascii:
          return 1u;

        case parse_t::csutf32: case parse_t::csutf32be: case parse_t::csutf32le:
        case parse_t::utf_32 : case parse_t::utf_32be : case parse_t::utf_32le :
          return 4u;

        case parse_t::csutf16: case parse_t::utf_16: return (
          static_cast<unsigned>((indexof(source, big_endian    == endianof() ? 2u : 0u) << 0u) | (indexof(source, big_endian    == endianof() ? 3u : 1u) << 8u)) > 0xD7FFu &&
          static_cast<unsigned>((indexof(source, little_endian == endianof() ? 2u : 0u) << 0u) | (indexof(source, little_endian == endianof() ? 3u : 1u) << 8u)) < 0xE000u
        ) + 1u;
        case parse_t::csutf16be: case parse_t::utf_16be: return 1u + (static_cast<unsigned>((indexof(source, 2u) << 0u) | (indexof(source, 3u) << 8u)) > 0xD7FFu && static_cast<unsigned>((indexof(source, 2u) << 0u) | (indexof(source, 3u) << 8u)) < 0xE000u);
        case parse_t::csutf16le: case parse_t::utf_16le: return 1u + (static_cast<unsigned>((indexof(source, 0u) << 0u) | (indexof(source, 1u) << 8u)) > 0xD7FFu && static_cast<unsigned>((indexof(source, 0u) << 0u) | (indexof(source, 1u) << 8u)) < 0xE000u);


        case parse_t::csutf8:
        case parse_t::utf_8: {
          unsigned char const value = indexof(source, 0u);

          // ...
          if (/* value >= 0x00u && */ value <= 0x7Fu) return 1u;
          else if  (value >= 0xC0u && value <= 0xDFu) return 2u;
          else if  (value >= 0xE0u && value <= 0xEFu) return 3u;
          else if  (value >= 0xF0u && value <= 0xF7u) return 4u;
        } return static_cast<unsigned char>(-1);

        default: break;
      }

      return static_cast<unsigned char>(-1);
    }

    /* constexpr */ inline static char const*          nextof(char          const volatile source[], std::size_t const count) /* noexcept */ { return const_cast<char const*>         (source + count / sizeof(char)); }
    /* constexpr */ inline static unsigned char const* nextof(unsigned char const volatile source[], std::size_t const count) /* noexcept */ { return const_cast<unsigned char const*>(source + count / sizeof(unsigned char)); }
    /* constexpr */ inline static wchar_t const*       nextof(wchar_t       const volatile source[], std::size_t const count) /* noexcept */ { return const_cast<wchar_t const*>      (source + count / sizeof(wchar_t)); }
    /* constexpr */ inline static void const*          nextof(void const volatile* const   source,   std::size_t const count) /* noexcept */ { return nextof(static_cast<unsigned char const volatile*>(source), count); }
    #ifdef __cpp_unicode_characters
      /* constexpr */ inline static char16_t const* nextof(char16_t const volatile source[], std::size_t const count) /* noexcept */ { return const_cast<char16_t const*>(source + count / sizeof(char16_t)); }
      /* constexpr */ inline static char32_t const* nextof(char32_t const volatile source[], std::size_t const count) /* noexcept */ { return const_cast<char32_t const*>(source + count / sizeof(char32_t)); }
    #endif

    /* constexpr */ static uint_least32_t valueof(sourceType const source[], parse_t::encoding const encoding, unsigned char length = 0u) /* noexcept */ {
      uint_fast32_t value = static_cast<uint_fast32_t>(-1);

      // ...
      length = 0u == length ? lengthof(source, encoding) : length;

      if (length != static_cast<unsigned char>(-1)) {
        enum endianness endian;

        // ...
        switch (encoding) {
          case parse_t::csutf16be: case parse_t::csutf32be: case parse_t::utf_16be: case parse_t::utf_32be: endian = big_endian;    break;
          case parse_t::csutf16le: case parse_t::csutf32le: case parse_t::utf_16le: case parse_t::utf_32le: endian = little_endian; break;
          default: endian = endianof(); break;
        }

        switch (encoding) {
          case parse_t::ansi_x3_4_1968: case parse_t::ansi_x3_4_1986:
          case parse_t::cp367: case parse_t::csascii:
          case parse_t::ibm367: case parse_t::iso646_us: case parse_t::iso_646_irv_1991: case parse_t::iso_ir_6:
          case parse_t::us: case parse_t::us_ascii: {
            value = indexof(source, 0u);
          } break;

          case parse_t::csutf32: case parse_t::csutf32be: case parse_t::csutf32le:
          case parse_t::utf_32:  case parse_t::utf_32be:  case parse_t::utf_32le: {
            switch (endian) {
              case big_endian   : value = (indexof(source, 3) << 8u * 0u) | (indexof(source, 2) << 8u * 1u) | (indexof(source, 1) << 8u * 2u) | (indexof(source, 0) << 8u * 3u); break;
              case little_endian: value = (indexof(source, 0) << 8u * 0u) | (indexof(source, 1) << 8u * 1u) | (indexof(source, 2) << 8u * 2u) | (indexof(source, 3) << 8u * 3u); break;
            }
          } break;

          case parse_t::csutf16: case parse_t::csutf16be: case parse_t::csutf16le:
          case parse_t::utf_16:  case parse_t::utf_16be:  case parse_t::utf_16le: {
            value = length != 1u ? 0x10000uL + (
              ((((indexof(source, 2u + (endian == big_endian)) << 0u) | (indexof(source, 2u + (endian == little_endian)) << 8u)) - 0xDC00u)) +
              ((((indexof(source, 0u + (endian == big_endian)) << 0u) | (indexof(source, 0u + (endian == little_endian)) << 8u)) - 0xD800u) * 0x400u)
            ) :  (indexof(source, 0u + (endian == big_endian)) << 0u) | (indexof(source, 0u + (endian == little_endian)) << 8u);


            if (value > 0x10FFFFuL)
            return static_cast<uint_least32_t>(-1);
          } break;

          case parse_t::csutf8:
          case parse_t::utf_8: {
            switch (length) {
              case 1u: value = indexof(source, 0u) & 0x7Fu; break;
              case 2u: if ((indexof(source, 0u) & 0xE0u) != 0xC0u) return static_cast<uint_least32_t>(-1); else value = indexof(source, 0u) & 0x1Fu; break;
              case 3u: if ((indexof(source, 0u) & 0xF0u) != 0xE0u) return static_cast<uint_least32_t>(-1); else value = indexof(source, 0u) & 0x0Fu; break;
              case 4u: if ((indexof(source, 0u) & 0xF8u) != 0xF0u) return static_cast<uint_least32_t>(-1); else value = indexof(source, 0u) & 0x07u; break;
            }

            while (--length) {
              if ((indexof(source, 4u - length) & 0xC0u) != 0x80u)
              return static_cast<uint_least32_t>(-1);

              value <<= 6u;
              value  |= indexof(source, 4u - length) & 0x3Fu;
            }

            if (
              value < 0x0800uL ?
                indexof(source, 0u) != (0xC0u | ((value & 0x7C0uL) >> 6u * 1u)) ||
                indexof(source, 1u) != (0x80u | ((value & 0x03FuL) >> 6u * 0u)) :
              value < 0x10000uL ?
                indexof(source, 0u) != (0xE0u | ((value & 0xF000uL) >> 6u * 2u)) ||
                indexof(source, 1u) != (0x80u | ((value & 0x0FC0uL) >> 6u * 1u)) ||
                indexof(source, 2u) != (0x80u | ((value & 0x003FuL) >> 6u * 0u)) :
              value < 0x110000uL ?
                indexof(source, 0u) != (0xF0u | ((value & 0x1C0000uL) >> 6u * 3u)) ||
                indexof(source, 1u) != (0x80u | ((value & 0x03F000uL) >> 6u * 2u)) ||
                indexof(source, 2u) != (0x80u | ((value & 0x000FC0uL) >> 6u * 1u)) ||
                indexof(source, 3u) != (0x80u | ((value & 0x00003FuL) >> 6u * 0u)) :
              true
            ) return static_cast<uint_least32_t>(-1);
          } break;

          default: break;
        }
      }

      return value;
    }
  };

  enum precedence /* : unsigned char */ {
    nop = 0x0u,
    complement, minus, negate, plus,
    expr_begin, expr_end, multiply, divide, modulo, add, subtract, left_shift, right_shift, compare, lesser, lesser_equals, greater, greater_equals, equals, unequals, bitwise_and, bitwise_xor, bitwise_or, boolean_and, boolean_or, ternary_check
  };

  /* ... */
  if (NULL == static_cast<void const volatile*>(source)) {
    /* constexpr */ char const value[] = "amogus";

    // ...
    if (0u != targetLength && targetLength < sizeof(value) / sizeof(char))
    return 0u;

    if (NULL != (char*) target) {
      for (char const *iterator = value; '\0' != *iterator; ++iterator, target = 1 + (char*) target)
      *(char*) target = *iterator;
    }

    return sizeof(value) / sizeof(char);
  }

  // ...
  if (encoding == parse_t::_default)
    encoding = parse_t::us_ascii;

  else if (encoding & parse_t::_automatic) {
    parse_t::encoding const subencoding = static_cast<parse_t::encoding>(static_cast<unsigned /* --> uint16_t */>(encoding) & 0x3FFu);
    parse_t::encoding       encodings[] = {parse_t::_default, parse_t::utf_8, parser::endianof() == little_endian ? parse_t::utf_16le : parse_t::utf_16be, subencoding == parse_t::_default ? parse_t::us_ascii : subencoding};

    // ...
    if (targetLength > 3u) *encodings =
      0xFFu == parser::indexof(source, 0u) && 0xFEu == parser::indexof(source, 1u) && 0x00u == parser::indexof(source, 2u) && 0x00u == parser::indexof(source, 3u) ? parse_t::utf_32le :
      0x00u == parser::indexof(source, 0u) && 0x00u == parser::indexof(source, 1u) && 0xFEu == parser::indexof(source, 2u) && 0xFFu == parser::indexof(source, 3u) ? parse_t::utf_32be :
    parse_t::_default;

    if (parse_t::_default == *encodings) *encodings =
      0xFEu == parser::indexof(source, 0u) && 0xFFu == parser::indexof(source, 1u)                                         ? parse_t::utf_16be :
      0xFFu == parser::indexof(source, 0u) && 0xFEu == parser::indexof(source, 1u)                                         ? parse_t::utf_16le :
      0xEFu == parser::indexof(source, 0u) && 0xBBu == parser::indexof(source, 1u) && 0xBFu == parser::indexof(source, 2u) ? parse_t::utf_8 :
    parse_t::_default;

    // ...
    for (std::size_t index = 0u; ; ++index) {
      sourceType const *iterator  = source;
      std::size_t       length    = sourceLength;
      bool              validated = false;

      // ...
      while (true) {
        std::size_t const sublength = parser::lengthof(iterator, encodings[index]);
        if (0u != sourceLength && sublength > length) break;

        uint_fast32_t const value = parser::valueof(iterator, encodings[index], sublength);
        if (value == static_cast<uint_least32_t>(-1)) break;
        if (value == 0x00000000uL) { validated = true; break; }

        // ...
        iterator = static_cast<sourceType const*>(parser::nextof(iterator, sublength));
        length  -= sublength;
        if (0u == length) { validated = true; break; }
      }

      if (validated) { encoding = encodings[index]; break; }
      if (index == (sizeof(encodings) / sizeof(parse_t::encoding)) - 1u) return 0u;
    }
  }

  /* ... */
  // {" ", "!", "%", "&", "(", ")", "*", "+", "-", "/", ":", "<", "=", ">", "?", "\\", "\f", "\n", "\r", "\t", "\v", "^", "function", "mod", "rem", "var", "{", "|", "}", "~", "«", "»", "×", "÷", "≠", "≤", "≥"};

  static_cast<void>(encoding);
  static_cast<void>(sourceLength);
  static_cast<void>(target);
  static_cast<void>(targetLength);

  // ...
  return 0u;
}

// ... ->> basic extensions to allow for all object pointer types (missing optimized support however for specific cases)
template <typename sourceType, typename targetType>
/* constexpr */ std::size_t parse(sourceType source, targetType target) /* noexcept */ {
  return parse((void const volatile*) source, 0u, (void volatile*) target, 0u);
}

template <typename sourceType, std::size_t sourceCapacity, typename targetType>
/* constexpr */ std::size_t parse(sourceType (&source)[sourceCapacity], targetType target) /* noexcept */ {
  return parse(static_cast<sourceType*>(source), sourceCapacity * sizeof(sourceType), (void volatile*) target, 0u);
}

template <typename sourceType, typename targetType, std::size_t targetCapacity>
/* constexpr */ std::size_t parse(sourceType source, targetType (&target)[targetCapacity]) /* noexcept */ {
  return parse((void const volatile*) source, 0u, static_cast<targetType*>(target), targetCapacity * sizeof(targetType));
}

template <typename sourceType, std::size_t sourceCapacity, typename targetType, std::size_t targetCapacity>
/* constexpr */ std::size_t parse(sourceType (&source)[sourceCapacity], targetType (&target)[targetCapacity]) /* noexcept */ {
  return parse(static_cast<sourceType*>(source), sourceCapacity * sizeof(sourceType), static_cast<targetType*>(target), targetCapacity * sizeof(targetType));
}

/* Main */
int main(int, char*[]) /* noexcept */ {
  std::size_t const parsed = parse("(-((1 + 5) * 2 % 3 - 2)) ^ 5 - 1", NULL);
  std::printf("%lu", static_cast<unsigned long>(parsed));
}
