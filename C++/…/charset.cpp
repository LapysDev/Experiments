#include <cassert>
#include <climits>
#include <cstddef>
#include <cstring>
#include <iso646.h>

/* ... */
enum policy {
  ENDIAN_BIG     = 0x01u, ENDIAN_LITTLE     = 0x02u, ENDIAN_MIXED = 0x04u,
  INVALID_IGNORE = 0x20u, INVALID_TERMINATE = 0x40u,

  // ->> Strategies denote character boundaries
  STRATEGY_ACCENT_PREFIX = 0x80u,  // ->> Byte code unit plus accent sequence
  STRATEGY_BYTE,                   // ->> Native byte (typically an octet)
  STRATEGY_BYTE_SEPTET,            // ->> 7-bit byte
  STRATEGY_DOUBLE_94,              // ->> Two bytes between 0x21–0x7E for 94×94 graphics
  STRATEGY_FORMAT_BIG5,            // ->> Big5 lead/ trail rules
  STRATEGY_FORMAT_BOCU_1,          // ->> BOCU-1 delta prefix length without code-point mapping
  STRATEGY_FORMAT_CESU_8,          // ->> UTF-16 code units represented by UTF-8 triplets
  STRATEGY_FORMAT_EUC_JP,          // ->> EUC-JP including SS2 and SS3 prefixes
  STRATEGY_FORMAT_EUC_TW,          // ->> EUC-TW ASCII, CNS plane 1, and SS2 plane selectors
  STRATEGY_FORMAT_EUC_KR,          // ->> EUC-KR ASCII or double-byte column/ row
  STRATEGY_FORMAT_GB2312,          // ->> GB2312 EUC byte pair
  STRATEGY_FORMAT_GB18030,         // ->> GB18030 one-/ two-/ four-byte syntax
  STRATEGY_FORMAT_GBK,             // ->> GBK one-/ two-byte syntax
  STRATEGY_FORMAT_HZ_GB_2312,      // ->> HZ ASCII/ GB2312 tilde-switch escape grammar
  STRATEGY_FORMAT_ISO_2022_CN,     // ->> ISO-2022-CN G1/ G2 designations and shift controls
  STRATEGY_FORMAT_ISO_2022_CN_EXT, // ->> ISO-2022-CN-EXT including G3
  STRATEGY_FORMAT_ISO_2022_JP,     // ->> ISO-2022-JP G0 escape-designated sets
  STRATEGY_FORMAT_ISO_2022_JP_2,   // ->> ISO-2022-JP-2 with extended G0/ SS2
  STRATEGY_FORMAT_ISO_2022_KR,     // ->> ISO-2022-KR designation and SI/ SO
  STRATEGY_FORMAT_JOHAB,           // ->> Johab two-byte Hangul and Hanja/ symbol sequences
  STRATEGY_FORMAT_KOI7_SWITCHED,   // ->> KOI7 7-bit code unit SI–SO switching
  STRATEGY_FORMAT_SCSU,            // ->> SCSU single-byte and Unicode modes
  STRATEGY_FORMAT_SJIS,            // ->> Shift_JIS single-/ double-byte syntax
  STRATEGY_FORMAT_UCS_2,           // ->> Fixed two-octet scalar without surrogates
  STRATEGY_FORMAT_UCS_4,           // ->> Fixed four-octet scalar
  STRATEGY_FORMAT_UTF_7,           // ->> UTF-7 modified Base64 shifted runs
  STRATEGY_FORMAT_UTF_7_IMAP,      // ->> IMAP modified UTF-7: &- shift, comma Base64, explicit -
  STRATEGY_FORMAT_UTF_8,           // ->> UTF-8 scalars
  STRATEGY_FORMAT_UTF_16,          // ->> UTF-16 BOM-selectable endian
  STRATEGY_FORMAT_UTF_16BE,        // ->> UTF-16 big            endian
  STRATEGY_FORMAT_UTF_16LE,        // ->> UTF-16 little         endian
  STRATEGY_FORMAT_UTF_32,          // ->> UTF-32 BOM-selectable endian
  STRATEGY_FORMAT_UTF_32BE,        // ->> UTF-32 big            endian
  STRATEGY_FORMAT_UTF_32LE,        // ->> UTF-32 little         endian
  STRATEGY_FORMAT_WINDOWS_949      // ->> Unified Hangul Code (UHC) extended two-byte rows
};

struct format /* final */ {
  enum encoding /* : unsigned char:8 */ {
    ADOBE_STANDARD_ENCODING,        // ->> Adobe-Standard-Encoding;        8 bits             per 1                                                (8-bit or greater) byte(s)
    ADOBE_SYMBOL_ENCODING,          // ->> Adobe-Symbol-Encoding;          8 bits             per 1                                                (8-bit or greater) byte(s)
    AMIGA_1251,                     // ->> Amiga-1251;                     8 bits             per 1                                                (8-bit or greater) byte(s)
    ANSI_X3_110_1983,               // ->> ANSI_X3.110-1983;               8 bits             per 1–2                                              (8-bit or greater) byte(s)
    ASMO_449,                       // ->> ASMO_449;                       7 bits             per 1                                                (8-bit or greater) byte(s)
    BIG5,                           // ->> Big5;                           8 bits             per 1–2                                              (8-bit or greater) byte(s)
    BIG5_HKSCS,                     // ->> Big5-HKSCS;                     8 bits             per 1–2                                              (8-bit or greater) byte(s)
    BOCU_1,                         // ->> BOCU-1;                         8 bits             per 1–4                                              (8-bit exactly)    byte(s)
    BRF,                            // ->> BRF;                            8 bits             per 1                                                (8-bit or greater) byte(s)
    BS_4730,                        // ->> BS_4730;                        7 bits             per 1                                                (8-bit or greater) byte(s)
    BS_VIEWDATA,                    // ->> BS_viewdata;                    7 bits             per 1                                                (8-bit or greater) byte(s)
    CESU_8,                         // ->> CESU-8;                         8 bits             per 1–3 or 6                                         (8-bit or greater) byte(s)
    CP50220,                        // ->> CP50220;                        7 bits (in 8 bits) per variable (1–2 per character + escapes)           (8-bit exactly)    byte(s)
    CP51932,                        // ->> CP51932;                        8 bits             per 1–3                                              (8-bit or greater) byte(s)
    CSA_Z243_4_1985_1,              // ->> CSA_Z243.4-1985-1;              7 bits             per 1                                                (8-bit or greater) byte(s)
    CSA_Z243_4_1985_2,              // ->> CSA_Z243.4-1985-2;              7 bits             per 1                                                (8-bit or greater) byte(s)
    CSA_Z243_4_1985_GR,             // ->> CSA_Z243.4-1985-gr;             8 bits             per 1                                                (8-bit or greater) byte(s)
    CSN_369103,                     // ->> CSN_369103;                     7 bits             per 1                                                (8-bit or greater) byte(s)
    DEC_MCS,                        // ->> DEC-MCS;                        8 bits             per 1                                                (8-bit or greater) byte(s)
    DIN_66003,                      // ->> DIN_66003;                      7 bits             per 1                                                (8-bit or greater) byte(s)
    DK_US,                          // ->> dk-us;                          7 bits             per 1                                                (8-bit or greater) byte(s)
    DS_2089,                        // ->> DS_2089;                        7 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_AT_DE,                   // ->> EBCDIC-AT-DE;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_AT_DE_A,                 // ->> EBCDIC-AT-DE-A;                 8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_CA_FR,                   // ->> EBCDIC-CA-FR;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_DK_NO,                   // ->> EBCDIC-DK-NO;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_DK_NO_A,                 // ->> EBCDIC-DK-NO-A;                 8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_ES,                      // ->> EBCDIC-ES;                      8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_ES_A,                    // ->> EBCDIC-ES-A;                    8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_ES_S,                    // ->> EBCDIC-ES-S;                    8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_FI_SE,                   // ->> EBCDIC-FI-SE;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_FI_SE_A,                 // ->> EBCDIC-FI-SE-A;                 8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_FR,                      // ->> EBCDIC-FR;                      8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_IT,                      // ->> EBCDIC-IT;                      8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_PT,                      // ->> EBCDIC-PT;                      8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_UK,                      // ->> EBCDIC-UK;                      8 bits             per 1                                                (8-bit or greater) byte(s)
    EBCDIC_US,                      // ->> EBCDIC-US;                      8 bits             per 1                                                (8-bit or greater) byte(s)
    ECMA_CYRILLIC,                  // ->> ECMA-cyrillic;                  8 bits             per 1                                                (8-bit or greater) byte(s)
    ES,                             // ->> ES;                             7 bits             per 1                                                (8-bit or greater) byte(s)
    ES2,                            // ->> ES2;                            7 bits             per 1                                                (8-bit or greater) byte(s)
    EUC_JP,                         // ->> EUC-JP;                         8 bits             per 1–3                                              (8-bit or greater) byte(s)
    EUC_KR,                         // ->> EUC-KR;                         8 bits             per 1–2                                              (8-bit or greater) byte(s)
    EUC_TW,                         // ->> EUC-TW;                         8 bits             per 1, 2 or 4                                        (8-bit or greater) byte(s)
    GB2312,                         // ->> GB2312;                         8 bits             per 1–2                                              (8-bit or greater) byte(s)
    GB18030,                        // ->> GB18030;                        8 bits             per 1–2 or 4                                         (8-bit or greater) byte(s)
    GB_1988_80,                     // ->> GB_1988-80;                     7 bits             per 1                                                (8-bit or greater) byte(s)
    GB_2312_80,                     // ->> GB_2312-80;                     7 bits             per 2                                                (8-bit or greater) byte(s)
    GBK,                            // ->> GBK;                            8 bits             per 1–2                                              (8-bit or greater) byte(s)
    GOST_19768_74,                  // ->> GOST_19768-74;                  8 bits             per 1                                                (8-bit or greater) byte(s)
    GREEK7,                         // ->> greek7;                         7 bits             per 1                                                (8-bit or greater) byte(s)
    GREEK7_OLD,                     // ->> greek7-old;                     7 bits             per 1                                                (8-bit or greater) byte(s)
    GREEK_CCITT,                    // ->> greek-ccitt;                    7 bits             per 1                                                (8-bit or greater) byte(s)
    HP_DESKTOP,                     // ->> HP-DeskTop;                     8 bits             per 1                                                (8-bit or greater) byte(s)
    HP_LEGAL,                       // ->> HP-Legal;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    HP_MATH8,                       // ->> HP-Math8;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    HP_PI_FONT,                     // ->> HP-Pi-font;                     8 bits             per 1                                                (8-bit or greater) byte(s)
    HP_ROMAN8,                      // ->> hp-roman8;                      8 bits             per 1                                                (8-bit or greater) byte(s)
    HZ_GB_2312,                     // ->> HZ-GB-2312;                     7 bits (in 8 bits) per variable (1–2 per graphic + shifts)              (8-bit exactly)    byte(s)
    IBM037,                         // ->> IBM037;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM038,                         // ->> IBM038;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM273,                         // ->> IBM273;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM274,                         // ->> IBM274;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM275,                         // ->> IBM275;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM277,                         // ->> IBM277;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM278,                         // ->> IBM278;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM280,                         // ->> IBM280;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM281,                         // ->> IBM281;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM284,                         // ->> IBM284;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM285,                         // ->> IBM285;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM290,                         // ->> IBM290;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM297,                         // ->> IBM297;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM420,                         // ->> IBM420;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM423,                         // ->> IBM423;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM424,                         // ->> IBM424;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM437,                         // ->> IBM437;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM500,                         // ->> IBM500;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM775,                         // ->> IBM775;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM850,                         // ->> IBM850;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM851,                         // ->> IBM851;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM852,                         // ->> IBM852;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM855,                         // ->> IBM855;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM857,                         // ->> IBM857;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM00858,                       // ->> IBM00858;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM860,                         // ->> IBM860;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM861,                         // ->> IBM861;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM862,                         // ->> IBM862;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM863,                         // ->> IBM863;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM864,                         // ->> IBM864;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM865,                         // ->> IBM865;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM866,                         // ->> IBM866;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM868,                         // ->> IBM868;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM869,                         // ->> IBM869;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM870,                         // ->> IBM870;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM871,                         // ->> IBM871;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM880,                         // ->> IBM880;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM891,                         // ->> IBM891;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM903,                         // ->> IBM903;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM904,                         // ->> IBM904;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM905,                         // ->> IBM905;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM918,                         // ->> IBM918;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM00924,                       // ->> IBM00924;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM1026,                        // ->> IBM1026;                        8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM1047,                        // ->> IBM1047;                        8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM01140,                       // ->> IBM01140;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM01141,                       // ->> IBM01141;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM01142,                       // ->> IBM01142;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM01143,                       // ->> IBM01143;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM01144,                       // ->> IBM01144;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM01145,                       // ->> IBM01145;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM01146,                       // ->> IBM01146;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM01147,                       // ->> IBM01147;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM01148,                       // ->> IBM01148;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM01149,                       // ->> IBM01149;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM_SYMBOLS,                    // ->> IBM-Symbols;                    8 bits             per 1                                                (8-bit or greater) byte(s)
    IBM_THAI,                       // ->> IBM-Thai;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    IEC_P27_1,                      // ->> IEC_P27-1;                      7 bits             per 1                                                (8-bit or greater) byte(s)
    INIS,                           // ->> INIS;                           7 bits             per 1                                                (8-bit or greater) byte(s)
    INIS_8,                         // ->> INIS-8;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    INIS_CYRILLIC,                  // ->> INIS-cyrillic;                  7 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_646_BASIC_1983,             // ->> ISO_646.basic:1983;             7 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_646_IRV_1983,               // ->> ISO_646.irv:1983;               7 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_2022_CN,                    // ->> ISO-2022-CN;                    7 bits (in 8 bits) per variable (1–2 per character + escapes)           (8-bit exactly)    byte(s)
    ISO_2022_CN_EXT,                // ->> ISO-2022-CN-EXT;                7 bits (in 8 bits) per variable (1–2 per character + escapes)           (8-bit exactly)    byte(s)
    ISO_2022_JP,                    // ->> ISO-2022-JP;                    7 bits (in 8 bits) per variable (1–2 per character + escapes)           (8-bit exactly)    byte(s)
    ISO_2022_JP_2,                  // ->> ISO-2022-JP-2;                  7 bits (in 8 bits) per variable (1–2 per character + escapes)           (8-bit exactly)    byte(s)
    ISO_2022_KR,                    // ->> ISO-2022-KR;                    7 bits (in 8 bits) per variable (1–2 per character + escapes)           (8-bit exactly)    byte(s)
    ISO_2033_1983,                  // ->> ISO_2033-1983;                  7 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_5427,                       // ->> ISO_5427;                       7 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_5427_1981,                  // ->> ISO_5427:1981;                  7 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_5428_1980,                  // ->> ISO_5428:1980;                  7 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_1_1987,                // ->> ISO_8859-1:1987;                8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_1_WINDOWS_3_0_LATIN_1, // ->> ISO-8859-1-Windows-3.0-Latin-1; 8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_1_WINDOWS_3_1_LATIN_1, // ->> ISO-8859-1-Windows-3.1-Latin-1; 8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_2_1987,                // ->> ISO_8859-2:1987;                8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_2_WINDOWS_LATIN_2,     // ->> ISO-8859-2-Windows-Latin-2;     8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_3_1988,                // ->> ISO_8859-3:1988;                8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_4_1988,                // ->> ISO_8859-4:1988;                8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_5_1988,                // ->> ISO_8859-5:1988;                8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_6_1987,                // ->> ISO_8859-6:1987;                8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_6_E,                   // ->> ISO_8859-6-E;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_6_I,                   // ->> ISO_8859-6-I;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_7_1987,                // ->> ISO_8859-7:1987;                8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_8_1988,                // ->> ISO_8859-8:1988;                8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_8_E,                   // ->> ISO_8859-8-E;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_8_I,                   // ->> ISO_8859-8-I;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_9_1989,                // ->> ISO_8859-9:1989;                8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_9_WINDOWS_LATIN_5,     // ->> ISO-8859-9-Windows-Latin-5;     8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_10,                    // ->> ISO-8859-10;                    8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_11,                    // ->> ISO-8859-11 (Thai);             8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_13,                    // ->> ISO-8859-13;                    8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_14,                    // ->> ISO-8859-14;                    8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_15,                    // ->> ISO-8859-15;                    8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_16,                    // ->> ISO-8859-16;                    8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_8859_SUPP,                  // ->> ISO_8859-supp;                  8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_10367_BOX,                  // ->> ISO_10367-box;                  8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_10646_J_1,                  // ->> ISO-10646-J-1;                  16-bit code units  per 2                                                (8-bit or greater) byte(s)
    ISO_10646_UCS_2,                // ->> ISO-10646-UCS-2;                16-bit code units  per 2                                                (8-bit or greater) byte(s)
    ISO_10646_UCS_4,                // ->> ISO-10646-UCS-4;                32-bit code units  per 4                                                (8-bit or greater) byte(s)
    ISO_10646_UCS_BASIC,            // ->> ISO-10646-UCS-Basic;            16-bit code units  per 2                                                (8-bit or greater) byte(s)
    ISO_10646_UNICODE_LATIN1,       // ->> ISO-10646-Unicode-Latin1;       16-bit code units  per 2                                                (8-bit or greater) byte(s)
    ISO_11548_1,                    // ->> ISO-11548-1;                    8 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_IR_90,                      // ->> iso-ir-90;                      7 bits             per 1                                                (8-bit or greater) byte(s)
    ISO_UNICODE_IBM_1261,           // ->> ISO-Unicode-IBM-1261;           16-bit code units  per 2                                                (8-bit or greater) byte(s)
    ISO_UNICODE_IBM_1264,           // ->> ISO-Unicode-IBM-1264;           16-bit code units  per 2                                                (8-bit or greater) byte(s)
    ISO_UNICODE_IBM_1265,           // ->> ISO-Unicode-IBM-1265;           16-bit code units  per 2                                                (8-bit or greater) byte(s)
    ISO_UNICODE_IBM_1268,           // ->> ISO-Unicode-IBM-1268;           16-bit code units  per 2                                                (8-bit or greater) byte(s)
    ISO_UNICODE_IBM_1276,           // ->> ISO-Unicode-IBM-1276;           16-bit code units  per 2                                                (8-bit or greater) byte(s)
    IT,                             // ->> IT;                             7 bits             per 1                                                (8-bit or greater) byte(s)
    JIS_C6220_1969_JP,              // ->> JIS_C6220-1969-jp;              7 bits             per 1                                                (8-bit or greater) byte(s)
    JIS_C6220_1969_RO,              // ->> JIS_C6220-1969-ro;              7 bits             per 1                                                (8-bit or greater) byte(s)
    JIS_C6226_1978,                 // ->> JIS_C6226-1978;                 7 bits             per 2                                                (8-bit or greater) byte(s)
    JIS_C6226_1983,                 // ->> JIS_C6226-1983;                 7 bits             per 2                                                (8-bit or greater) byte(s)
    JIS_C6229_1984_A,               // ->> JIS_C6229-1984-a;               7 bits             per 1                                                (8-bit or greater) byte(s)
    JIS_C6229_1984_B,               // ->> JIS_C6229-1984-b;               7 bits             per 1                                                (8-bit or greater) byte(s)
    JIS_C6229_1984_B_ADD,           // ->> JIS_C6229-1984-b-add;           7 bits             per 1                                                (8-bit or greater) byte(s)
    JIS_C6229_1984_HAND,            // ->> JIS_C6229-1984-hand;            7 bits             per 1                                                (8-bit or greater) byte(s)
    JIS_C6229_1984_HAND_ADD,        // ->> JIS_C6229-1984-hand-add;        7 bits             per 1                                                (8-bit or greater) byte(s)
    JIS_C6229_1984_KANA,            // ->> JIS_C6229-1984-kana;            7 bits             per 1                                                (8-bit or greater) byte(s)
    JIS_ENCODING,                   // ->> JIS_Encoding;                   7 bits (in 8 bits) per variable (1–2 per character + escapes)           (8-bit exactly)    byte(s)
    JIS_X0201,                      // ->> JIS_X0201;                      8 bits             per 1                                                (8-bit or greater) byte(s)
    JIS_X0212_1990,                 // ->> JIS_X0212-1990;                 7 bits             per 2                                                (8-bit or greater) byte(s)
    JOHAB,                          // ->> Johab (CP1361);                 8 bits             per 1–2                                              (8-bit or greater) byte(s)
    JUS_I_B1_002,                   // ->> JUS_I.B1.002;                   7 bits             per 1                                                (8-bit or greater) byte(s)
    JUS_I_B1_003_MAC,               // ->> JUS_I.B1.003-mac;               7 bits             per 1                                                (8-bit or greater) byte(s)
    JUS_I_B1_003_SERB,              // ->> JUS_I.B1.003-serb;              7 bits             per 1                                                (8-bit or greater) byte(s)
    KOI7_SWITCHED,                  // ->> KOI7-switched;                  7 bits (in 8 bits) per 1                                                (8-bit exactly)    byte(s)
    KOI8_R,                         // ->> KOI8-R;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    KOI8_U,                         // ->> KOI8-U;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    KS_C_5601_1987,                 // ->> KS_C_5601-1987;                 7 bits             per 2                                                (8-bit or greater) byte(s)
    KSC5636,                        // ->> KSC5636;                        7 bits             per 1                                                (8-bit or greater) byte(s)
    KZ_1048,                        // ->> KZ-1048;                        8 bits             per 1                                                (8-bit or greater) byte(s)
    LATIN_GREEK,                    // ->> latin-greek;                    8 bits             per 1                                                (8-bit or greater) byte(s)
    LATIN_GREEK_1,                  // ->> Latin-greek-1;                  8 bits             per 1                                                (8-bit or greater) byte(s)
    LATIN_LAP,                      // ->> latin-lap;                      8 bits             per 1                                                (8-bit or greater) byte(s)
    MACINTOSH,                      // ->> macintosh;                      8 bits             per 1                                                (8-bit or greater) byte(s)
    MICROSOFT_PUBLISHING,           // ->> Microsoft-Publishing;           8 bits             per 1                                                (8-bit or greater) byte(s)
    MSZ_7795_3,                     // ->> MSZ_7795.3;                     7 bits             per 1                                                (8-bit or greater) byte(s)
    NATS_DANO,                      // ->> NATS-DANO;                      7 bits             per 1                                                (8-bit or greater) byte(s)
    NATS_DANO_ADD,                  // ->> NATS-DANO-ADD;                  7 bits             per 1                                                (8-bit or greater) byte(s)
    NATS_SEFI,                      // ->> NATS-SEFI;                      7 bits             per 1                                                (8-bit or greater) byte(s)
    NATS_SEFI_ADD,                  // ->> NATS-SEFI-ADD;                  7 bits             per 1                                                (8-bit or greater) byte(s)
    NC_NC00_10_81,                  // ->> NC_NC00-10:81;                  7 bits             per 1                                                (8-bit or greater) byte(s)
    NF_Z_62_010,                    // ->> NF_Z_62-010;                    7 bits             per 1                                                (8-bit or greater) byte(s)
    NF_Z_62_010__1973,              // ->> NF_Z_62-010_(1973);             8 bits             per 1                                                (8-bit or greater) byte(s)
    NS_4551_1,                      // ->> NS_4551-1;                      7 bits             per 1                                                (8-bit or greater) byte(s)
    NS_4551_2,                      // ->> NS_4551-2;                      7 bits             per 1                                                (8-bit or greater) byte(s)
    OSD_EBCDIC_DF03_IRV,            // ->> OSD_EBCDIC_DF03_IRV;            8 bits             per 1                                                (8-bit or greater) byte(s)
    OSD_EBCDIC_DF04_1,              // ->> OSD_EBCDIC_DF04_1;              8 bits             per 1                                                (8-bit or greater) byte(s)
    OSD_EBCDIC_DF04_15,             // ->> OSD_EBCDIC_DF04_15;             8 bits             per 1                                                (8-bit or greater) byte(s)
    PC8_DANISH_NORWEGIAN,           // ->> PC8-Danish-Norwegian;           8 bits             per 1                                                (8-bit or greater) byte(s)
    PC8_TURKISH,                    // ->> PC8-Turkish;                    8 bits             per 1                                                (8-bit or greater) byte(s)
    PT2,                            // ->> PT2;                            7 bits             per 1                                                (8-bit or greater) byte(s)
    PT,                             // ->> PT;                             7 bits             per 1                                                (8-bit or greater) byte(s)
    PTCP154,                        // ->> PTCP154;                        8 bits             per 1                                                (8-bit or greater) byte(s)
    SCSU,                           // ->> SCSU;                           8 bits             per variable (commonly 1–4 + commands)               (8-bit exactly)    byte(s)
    SEN_850200_B,                   // ->> SEN_850200_B;                   7 bits             per 1                                                (8-bit or greater) byte(s)
    SEN_850200_C,                   // ->> SEN_850200_C;                   7 bits             per 1                                                (8-bit or greater) byte(s)
    SHIFT_JIS,                      // ->> Shift_JIS;                      8 bits             per 1–2                                              (8-bit or greater) byte(s)
    T_61_7BIT,                      // ->> T.61-7bit;                      7 bits             per 1                                                (8-bit or greater) byte(s)
    T_61_8BIT,                      // ->> T.61-8bit;                      8 bits             per 1–2                                              (8-bit or greater) byte(s)
    T_101_G2,                       // ->> T.101-G2;                       8 bits             per 1                                                (8-bit or greater) byte(s)
    TIS_620,                        // ->> TIS-620;                        8 bits             per 1                                                (8-bit or greater) byte(s)
    TSCII,                          // ->> TSCII;                          8 bits             per 1                                                (8-bit or greater) byte(s)
    UNICODE_1_1,                    // ->> UNICODE-1-1;                    16-bit code units  per 2                                                (8-bit or greater) byte(s)
    US_ASCII,                       // ->> US-ASCII;                       7 bits             per 1                                                (8-bit or greater) byte(s)
    US_DK,                          // ->> us-dk;                          7 bits             per 1                                                (8-bit or greater) byte(s)
    UTF_7,                          // ->> UTF-7;                          7 bits (in 8 bits) per variable (1 ASCII or multiple Base64 characters) (8-bit exactly)    byte(s)
    UTF_7_IMAP,                     // ->> IMAP modified UTF-7;            7 bits (in 8 bits) per variable (&- or &Base64- or printable ASCII)     (8-bit exactly)    byte(s)
    UTF_8,                          // ->> UTF-8;                          8 bits             per 1–4                                              (8-bit or greater) byte(s)
    UTF_16,                         // ->> UTF-16;                         16-bit code units  per 2 or 4 (+ optional 2 BOM)                        (8-bit or greater) byte(s)
    UTF_16BE,                       // ->> UTF-16BE;                       16-bit code units  per 2 or 4                                           (8-bit or greater) byte(s)
    UTF_16LE,                       // ->> UTF-16LE;                       16-bit code units  per 2 or 4                                           (8-bit or greater) byte(s)
    UTF_32,                         // ->> UTF-32;                         32-bit code units  per 4 (+ optional 4 BOM)                             (8-bit or greater) byte(s)
    UTF_32BE,                       // ->> UTF-32BE;                       32-bit code units  per 4                                                (8-bit or greater) byte(s)
    UTF_32LE,                       // ->> UTF-32LE;                       32-bit code units  per 4                                                (8-bit or greater) byte(s)
    VENTURA_INTERNATIONAL,          // ->> Ventura-International;          8 bits             per 1                                                (8-bit or greater) byte(s)
    VENTURA_MATH,                   // ->> Ventura-Math;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    VENTURA_US,                     // ->> Ventura-US;                     8 bits             per 1                                                (8-bit or greater) byte(s)
    VIDEOTEX_SUPPL,                 // ->> videotex-suppl;                 8 bits             per 1                                                (8-bit or greater) byte(s)
    VISCII,                         // ->> VISCII;                         8 bits             per 1                                                (8-bit or greater) byte(s)
    WINDOWS_31J,                    // ->> Windows-31J;                    8 bits             per 1–2                                              (8-bit or greater) byte(s)
    WINDOWS_874,                    // ->> windows-874;                    8 bits             per 1                                                (8-bit or greater) byte(s)
    WINDOWS_949,                    // ->> Windows-949 (UHC);              8 bits             per 1–2                                              (8-bit or greater) byte(s)
    WINDOWS_1250,                   // ->> windows-1250;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    WINDOWS_1251,                   // ->> windows-1251;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    WINDOWS_1252,                   // ->> windows-1252;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    WINDOWS_1253,                   // ->> windows-1253;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    WINDOWS_1254,                   // ->> windows-1254;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    WINDOWS_1255,                   // ->> windows-1255;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    WINDOWS_1256,                   // ->> windows-1256;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    WINDOWS_1257,                   // ->> windows-1257;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    WINDOWS_1258,                   // ->> windows-1258;                   8 bits             per 1                                                (8-bit or greater) byte(s)
    X_ADOBE_ZAPF_DINGBATS_ENCODING, // ->> x-Adobe-Zapf-Dingbats-Encoding; 8 bits             per 1                                                (8-bit or greater) byte(s)
    X_DIN_66303                     // ->> x-DIN_66303;                    7 bits             per 1                                                (8-bit or greater) byte(s)
  };

  template <enum format::encoding format>
  struct maximum /* final */ {
    enum /* : ::std::size_t */ { value = (
      format::CESU_8           == format                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         ? 6u :
      format::BOCU_1           == format or format::EUC_TW     == format or format::GB18030 == format or format::ISO_10646_UCS_4 == format or format::SCSU == format or format::UTF_8 == format or format::UTF_16 == format or format::UTF_16BE == format or format::UTF_16LE == format or format::UTF_32 == format or format::UTF_32BE == format or format::UTF_32LE == format                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  ? 4u :
      format::CP51932          == format or format::EUC_JP     == format                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         ? 3u :
      format::ANSI_X3_110_1983 == format or format::BIG5       == format or format::BIG5_HKSCS  == format or format::EUC_KR          == format or format::GB2312      == format or format::GB_2312_80    == format or format::GBK         == format or format::ISO_10646_J_1 == format or format::ISO_10646_UCS_2 == format or format::ISO_10646_UCS_BASIC == format or format::ISO_10646_UNICODE_LATIN1 == format or format::ISO_UNICODE_IBM_1261 == format or format::ISO_UNICODE_IBM_1264 == format or format::ISO_UNICODE_IBM_1265 == format or format::ISO_UNICODE_IBM_1268 == format or format::ISO_UNICODE_IBM_1276 == format or format::JIS_C6226_1978 == format or format::JIS_C6226_1983 == format or format::JOHAB == format or format::JIS_X0212_1990 == format or format::KS_C_5601_1987 == format or format::SHIFT_JIS == format or format::T_61_8BIT == format or format::UNICODE_1_1 == format or format::WINDOWS_31J == format or format::WINDOWS_949 == format ? 2u :
      format::CP50220          == format or format::HZ_GB_2312 == format or format::ISO_2022_CN == format or format::ISO_2022_CN_EXT == format or format::ISO_2022_JP == format or format::ISO_2022_JP_2 == format or format::ISO_2022_KR == format or format::JIS_ENCODING  == format or format::KOI7_SWITCHED   == format or format::UTF_7               == format or format::UTF_7_IMAP               == format                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               ? 0u :
      1u
    ) };
  };

  /* ... */
  static enum policy strategy(enum format::encoding format) /* noexcept */ {
    switch (format) {
      case format::ASMO_449:
      case format::BS_4730:           case format::BS_VIEWDATA:
      case format::CSA_Z243_4_1985_1: case format::CSA_Z243_4_1985_2: case format::CSN_369103:
      case format::DIN_66003:         case format::DK_US:             case format::DS_2089:
      case format::ES:                case format::ES2:
      case format::GB_1988_80:        case format::GREEK7:            case format::GREEK7_OLD:       case format::GREEK_CCITT:
      case format::IEC_P27_1:         case format::INIS:              case format::INIS_CYRILLIC:    case format::ISO_646_BASIC_1983: case format::ISO_646_IRV_1983:     case format::ISO_2033_1983:       case format::ISO_5427:                case format::ISO_5427_1981:       case format::ISO_5428_1980: case format::ISO_IR_90:        case format::IT:
      case format::JIS_C6220_1969_JP: case format::JIS_C6220_1969_RO: case format::JIS_C6229_1984_A: case format::JIS_C6229_1984_B:   case format::JIS_C6229_1984_B_ADD: case format::JIS_C6229_1984_HAND: case format::JIS_C6229_1984_HAND_ADD: case format::JIS_C6229_1984_KANA: case format::JUS_I_B1_002:  case format::JUS_I_B1_003_MAC: case format::JUS_I_B1_003_SERB:
      case format::KSC5636:
      case format::MSZ_7795_3:
      case format::NATS_DANO:    case format::NATS_DANO_ADD: case format::NATS_SEFI: case format::NATS_SEFI_ADD: case format::NC_NC00_10_81: case format::NF_Z_62_010: case format::NS_4551_1: case format::NS_4551_2:
      case format::PT2:          case format::PT:
      case format::SEN_850200_B: case format::SEN_850200_C:
      case format::T_61_7BIT:
      case format::US_ASCII: case format::US_DK:
      case format::X_DIN_66303:
        return STRATEGY_BYTE_SEPTET;

      case format::BIG5: case format::BIG5_HKSCS: return STRATEGY_FORMAT_BIG5;
      case format::CESU_8:                        return STRATEGY_FORMAT_CESU_8;
      case format::CP51932: case format::EUC_JP:  return STRATEGY_FORMAT_EUC_JP;
      case format::EUC_TW:                        return STRATEGY_FORMAT_EUC_TW;
      case format::EUC_KR:                        return STRATEGY_FORMAT_EUC_KR;

      case format::GB_2312_80:
      case format::JIS_C6226_1978: case format::JIS_C6226_1983: case format::JIS_X0212_1990:
      case format::KS_C_5601_1987:
        return STRATEGY_DOUBLE_94;

      case format::GB18030: return STRATEGY_FORMAT_GB18030;
      case format::GB2312:  return STRATEGY_FORMAT_GB2312;
      case format::GBK:     return STRATEGY_FORMAT_GBK;

      case format::ISO_10646_J_1:        case format::ISO_10646_UCS_2:      case format::ISO_10646_UCS_BASIC:  case format::ISO_10646_UNICODE_LATIN1: case format::ISO_UNICODE_IBM_1261: case format::ISO_UNICODE_IBM_1264:
      case format::ISO_UNICODE_IBM_1265: case format::ISO_UNICODE_IBM_1268: case format::ISO_UNICODE_IBM_1276: case format::UNICODE_1_1:
        return STRATEGY_FORMAT_UCS_2;

      case format::ISO_10646_UCS_4:                     return STRATEGY_FORMAT_UCS_4;
      case format::ISO_8859_11:                         return STRATEGY_BYTE; // Thai 8-bit code positions; no mapping table
      case format::JOHAB:                               return STRATEGY_FORMAT_JOHAB;
      case format::SHIFT_JIS: case format::WINDOWS_31J: return STRATEGY_FORMAT_SJIS;
      case format::UTF_16:                              return STRATEGY_FORMAT_UTF_16;
      case format::UTF_16BE:                            return STRATEGY_FORMAT_UTF_16BE;
      case format::UTF_16LE:                            return STRATEGY_FORMAT_UTF_16LE;
      case format::UTF_32:                              return STRATEGY_FORMAT_UTF_32;
      case format::UTF_32BE:                            return STRATEGY_FORMAT_UTF_32BE;
      case format::UTF_32LE:                            return STRATEGY_FORMAT_UTF_32LE;
      case format::UTF_8:                               return STRATEGY_FORMAT_UTF_8;
      case format::WINDOWS_949:                         return STRATEGY_FORMAT_WINDOWS_949;

      #if CHAR_BIT == 8 // ->> Native ICU-agnostic
        case format::ANSI_X3_110_1983: return STRATEGY_ACCENT_PREFIX;
        case format::BOCU_1:           return STRATEGY_FORMAT_BOCU_1;
        case format::CP50220:          return STRATEGY_FORMAT_ISO_2022_JP;
        case format::HZ_GB_2312:       return STRATEGY_FORMAT_HZ_GB_2312;
        case format::ISO_2022_CN:      return STRATEGY_FORMAT_ISO_2022_CN;
        case format::ISO_2022_CN_EXT:  return STRATEGY_FORMAT_ISO_2022_CN_EXT;
        case format::ISO_2022_JP:      return STRATEGY_FORMAT_ISO_2022_JP;
        case format::ISO_2022_JP_2:    return STRATEGY_FORMAT_ISO_2022_JP_2;
        case format::ISO_2022_KR:      return STRATEGY_FORMAT_ISO_2022_KR;
        case format::JIS_ENCODING:     return STRATEGY_FORMAT_ISO_2022_JP_2;
        case format::KOI7_SWITCHED:    return STRATEGY_FORMAT_KOI7_SWITCHED;
        case format::SCSU:             return STRATEGY_FORMAT_SCSU;
        case format::T_61_8BIT:        return STRATEGY_ACCENT_PREFIX;
        case format::UTF_7:            return STRATEGY_FORMAT_UTF_7;
        case format::UTF_7_IMAP:       return STRATEGY_FORMAT_UTF_7_IMAP;
      #endif

      default:
        return STRATEGY_BYTE;
    }
  }
};

struct state /* final */ {
  enum /* : unsigned char:5 */ { ISO_2022_G1_DESIGNATED = 0x01u, ISO_2022_G2_DESIGNATED = 0x02u, ISO_2022_G3_DESIGNATED = 0x04u, ISO_2022_SHIFTED = 0x08u, SCSU_UNICODE = 0x10u }; // ->> ISO-2022 G1–G3, ISO-2022/ HZ alternative, and SCSU’s two-byte Unicode
  static ::std::size_t const COUNT_LIMIT, MALFORMED, NO_SPACE, OVERLONG, UNSUPPORTED;

  struct /* final */ { ::std::size_t length, offset;  } source;         // ->> Zero byte length denotes NUL sentinel; Cursor index
  ::std::size_t                                         characters;     // ->> Number of characters (typically `0zu` for shift commands and `> 1zu` for UTF-7)
  enum policy                                           endianness : 3; //
  ::std::size_t                                         invalids;       // ->> Erroneous bytes to skip for recovery
  unsigned char                                         status : 5;     //

  /* ... */
  void reset() /* noexcept */ {
    this -> characters    = 0u;
    this -> endianness    = static_cast<enum policy>(0x00u);
    this -> invalids      = 0u;
    this -> source.offset = 0u;
    this -> status        = 0x00u;
  }
};
  ::std::size_t const state::COUNT_LIMIT = static_cast< ::std::size_t>(-1),
                      state::MALFORMED   = static_cast< ::std::size_t>(-2),
                      state::NO_SPACE    = static_cast< ::std::size_t>(-3),
                      state::OVERLONG    = static_cast< ::std::size_t>(-4),
                      state::UNSUPPORTED = static_cast< ::std::size_t>(-5);

/* ... ->> Characters are accordingly either Unicode scalars or legacy code units */
extern "C" ::std::size_t nul(enum format::encoding const encoding, unsigned char nul[], ::std::size_t const capacity = 0u) /* noexcept */ {
  switch (format::strategy(encoding)) {
    case STRATEGY_DOUBLE_94:                                                                                               return state::UNSUPPORTED;
    case STRATEGY_FORMAT_UCS_2: case STRATEGY_FORMAT_UTF_16: case STRATEGY_FORMAT_UTF_16BE: case STRATEGY_FORMAT_UTF_16LE: return not capacity or capacity >= 2u ? (void) ::std::memset (nul, 0x00u, 2u),            2u : state::NO_SPACE;
    case STRATEGY_FORMAT_UCS_4: case STRATEGY_FORMAT_UTF_32: case STRATEGY_FORMAT_UTF_32BE: case STRATEGY_FORMAT_UTF_32LE: return not capacity or capacity >= 4u ? (void) ::std::memset (nul, 0x00u, 4u),            4u : state::NO_SPACE;
    case STRATEGY_FORMAT_UTF_7:      { unsigned char const shift[] = {'+', 'A', 'A', 'A', '-'};                            return not capacity or capacity >= 5u ? (void) ::std::memmove(nul, shift, sizeof(shift)), 5u : state::NO_SPACE; } break;
    case STRATEGY_FORMAT_UTF_7_IMAP: { unsigned char const shift[] = {'&', 'A', 'A', 'A', '-'};                            return not capacity or capacity >= 5u ? (void) ::std::memmove(nul, shift, sizeof(shift)), 5u : state::NO_SPACE; } break;
    default: *nul = 0x00u;                                                                                                 return 1u;
  }
}

// Return the positive width, in native CHAR_BIT bytes, of the next character (or state-changing command).
//   A shift/designation command has width > 0 but produces zero characters.
//   UTF-7’s Base64 run may contain several characters in one returned width.
// The number produced is `state::characters`; there is no extra width output parameter.
//
// On each successful call, state->source.offset advances by the returned
// width, while state->status retains stateful charset transitions. Pass a
// pointer to the CURRENT byte, not the start of the entire source buffer:
//   next(&text[state.source.offset], encoding, &state)
// The optional status pointer overrides state->status (useful when sharing
// shift state without sharing other state); NULL is the default sentinel.
extern "C" ::std::size_t next(unsigned char const text[], enum format::encoding const encoding, struct state* const state = NULL, unsigned* const status = NULL) /* noexcept */ {
  if (text == NULL) return state::MALFORMED;

  enum policy const mode = format::strategy(encoding);
  ::std::size_t length = state != NULL and state->source.length != 0 ? state->source.length - state->source.offset : 0;

  // When no explicit source length is supplied, locate the complete NUL code
  // unit (1, 2 or 4 native bytes). This convention cannot describe embedded
  // NUL characters; supply state->source.length for binary source instead.
  if (length == 0 and (state == NULL or state->source.length == 0)) {
    unsigned unitBytes = 1;
    // NUL code-unit width is determined by the encoding strategy.
    switch (mode) {
      case STRATEGY_FORMAT_UCS_2:
      case STRATEGY_FORMAT_UTF_16:
      case STRATEGY_FORMAT_UTF_16BE:
      case STRATEGY_FORMAT_UTF_16LE: unitBytes = 2u; break;
      case STRATEGY_FORMAT_UCS_4:
      case STRATEGY_FORMAT_UTF_32:
      case STRATEGY_FORMAT_UTF_32BE:
      case STRATEGY_FORMAT_UTF_32LE: unitBytes = 4u; break;
      default: break;
    }
    for (;;) {
      bool terminated = true;
      for (unsigned index = 0; index < unitBytes; ++index)
        if (text[length + index] != 0) terminated = false;
      if (terminated) break;
      if (length >= state::UNSUPPORTED - unitBytes) return state::COUNT_LIMIT;
      length += unitBytes;
    }
  }
  if (length == 0) return state::MALFORMED;

  enum policy endianness = state != NULL ? state->endianness : ENDIAN_LITTLE;
  if (endianness != ENDIAN_BIG and endianness != ENDIAN_LITTLE) endianness = ENDIAN_LITTLE;
  switch (mode) {
    case STRATEGY_FORMAT_UTF_16BE:
    case STRATEGY_FORMAT_UTF_32BE: endianness = ENDIAN_BIG; break;
    case STRATEGY_FORMAT_UTF_16LE:
    case STRATEGY_FORMAT_UTF_32LE: endianness = ENDIAN_LITTLE; break;
    default: break;
  }

  // A standalone next() starts with an optional BOM. The higher-level
  // operations already handle BOMs before calling next(), so they start
  // after the BOM, keeping its bytes outside their character count.
  if (state == NULL or state->source.offset == 0) {
    if (mode == STRATEGY_FORMAT_UTF_16 and length >= 2 and
        ((text[0] == 0xFEu and text[1] == 0xFFu) or (text[0] == 0xFFu and text[1] == 0xFEu))) {
      endianness = text[0] == 0xFEu ? ENDIAN_BIG : ENDIAN_LITTLE;
      if (state != NULL) {
        state->endianness = endianness;
        state->characters = 0;
        state->invalids = 0;
        state->source.offset += 2;
      }
      return 2;
    }
    if (mode == STRATEGY_FORMAT_UTF_32 and length >= 4 and
        ((text[0] == 0 and text[1] == 0 and text[2] == 0xFEu and text[3] == 0xFFu) or
         (text[0] == 0xFFu and text[1] == 0xFEu and text[2] == 0 and text[3] == 0))) {
      endianness = text[0] == 0xFFu ? ENDIAN_LITTLE : ENDIAN_BIG;
      if (state != NULL) {
        state->endianness = endianness;
        state->characters = 0;
        state->invalids = 0;
        state->source.offset += 4;
      }
      return 4;
    }
  }
  bool const little = endianness != ENDIAN_BIG;
  unsigned shiftFlags = status != NULL ? *status : (state != NULL ? state->status : 0u);
  // Native code units carry one wire octet each for the following formats.
  if ((mode == STRATEGY_FORMAT_BOCU_1 or mode == STRATEGY_FORMAT_HZ_GB_2312 or
       mode == STRATEGY_FORMAT_ISO_2022_CN or mode == STRATEGY_FORMAT_ISO_2022_CN_EXT or
       mode == STRATEGY_FORMAT_ISO_2022_JP or mode == STRATEGY_FORMAT_ISO_2022_JP_2 or
       mode == STRATEGY_FORMAT_ISO_2022_KR or mode == STRATEGY_FORMAT_KOI7_SWITCHED or
       mode == STRATEGY_FORMAT_SCSU or mode == STRATEGY_FORMAT_UTF_7 or
       mode == STRATEGY_FORMAT_UTF_7_IMAP) and CHAR_BIT != 8) return state::UNSUPPORTED;

  // These booleans are local views of the stream's compact shift status.
  bool shifted = (shiftFlags & state::ISO_2022_SHIFTED) != 0;
  bool designation = (shiftFlags & state::ISO_2022_G1_DESIGNATED) != 0;
  bool g2Designated = (shiftFlags & state::ISO_2022_G2_DESIGNATED) != 0;
  bool g3Designated = (shiftFlags & state::ISO_2022_G3_DESIGNATED) != 0;
  bool unicodeMode = (shiftFlags & state::SCSU_UNICODE) != 0;
  ::std::size_t width = 1;
  ::std::size_t produced = 1;
  ::std::size_t failure = 0;

  unsigned first = text[0];
  unsigned second = length >= 2 ? text[1] : 0;
  unsigned third = length >= 3 ? text[2] : 0;
  unsigned fourth = length >= 4 ? text[3] : 0;

  if (first > 0xFFu) { failure = state::MALFORMED; goto finished; }

  if (mode == STRATEGY_ACCENT_PREFIX) {
    // ANSI X3.110-1983 and T.61 use a nonspacing accent byte (C1..CF)
    // optionally followed by a base-letter byte. These are 1- or 2-byte
    // character units; exact repertoire/mapping is not validated here.
    if (first >= 0xC1u and first <= 0xCFu and length >= 2 and
        ((second >= 'A' and second <= 'Z') or (second >= 'a' and second <= 'z') or second == ' ')) width = 2;
    goto finished;
  }

  if (mode == STRATEGY_FORMAT_HZ_GB_2312) {
    // RFC 1843: "~~" literal tilde; "~{" enter GB; "~}" leave GB;
    // tilde-newline is a continuation with no decoded character.
    if (first == '~') {
      if (length < 2 or second > 0x7Fu) { failure = state::MALFORMED; goto finished; }
      width = 2;
      if (second == '~') { /* literal tilde */ }
      else if (second == '{' and not shifted) { shifted = true; produced = 0; }
      else if (second == '}' and shifted) { shifted = false; produced = 0; }
      else if (second == '\n') produced = 0;
      else failure = state::MALFORMED;
    } else if (shifted) {
      if (length < 2 or first < 0x21u or first > 0x77u or second < 0x21u or second > 0x7Eu) failure = state::MALFORMED;
      else width = 2;
    } else if (first > 0x7Fu) failure = state::MALFORMED;
    goto finished;
  }

  if (mode == STRATEGY_FORMAT_ISO_2022_JP or mode == STRATEGY_FORMAT_ISO_2022_JP_2 or
      mode == STRATEGY_FORMAT_ISO_2022_KR or mode == STRATEGY_FORMAT_ISO_2022_CN or
      mode == STRATEGY_FORMAT_ISO_2022_CN_EXT or mode == STRATEGY_FORMAT_KOI7_SWITCHED) {
    // ISO 2022 uses ESC for charset designations and SO/SI for switching.
    // Designations and shifts consume bytes but are NOT characters.
    bool japanese = mode == STRATEGY_FORMAT_ISO_2022_JP or mode == STRATEGY_FORMAT_ISO_2022_JP_2;
    bool extendedJP = mode == STRATEGY_FORMAT_ISO_2022_JP_2;
    bool chinese = mode == STRATEGY_FORMAT_ISO_2022_CN or mode == STRATEGY_FORMAT_ISO_2022_CN_EXT;
    if (first == 0x1Bu and mode != STRATEGY_FORMAT_KOI7_SWITCHED) {
      produced = 0;
      if (length < 3) { failure = state::MALFORMED; goto finished; }
      if (japanese) {
        if (second == '(' and (third == 'B' or third == 'J' or
            (third == 'I' and (mode == STRATEGY_FORMAT_ISO_2022_JP or encoding == format::CP50220)))) {
          shifted = false; width = 3;
        } else if (second == '$' and (third == '@' or third == 'B' or (third == 'A' and extendedJP))) {
          shifted = true; width = 3;
        } else if (extendedJP and second == '$' and third == '(' and length >= 4 and (fourth == 'C' or fourth == 'D')) {
          shifted = true; width = 4;
        } else if (extendedJP and second == '.' and (third == 'A' or third == 'F')) {
          g2Designated = true; width = 3;
        } else if (extendedJP and second == 'N' and g2Designated and length >= 3 and third >= 0x20u and third <= 0x7Fu) {
          width = 3; produced = 1;
        } else failure = state::MALFORMED;
      } else if (mode == STRATEGY_FORMAT_ISO_2022_KR) {
        if (length >= 4 and second == '$' and third == ')' and fourth == 'C') { designation = true; width = 4; }
        else failure = state::MALFORMED;
      } else if (chinese) {
        if (length >= 4 and second == '$' and third == ')' and
            (fourth == 'A' or fourth == 'G' or (mode == STRATEGY_FORMAT_ISO_2022_CN_EXT and fourth == 'E'))) {
          designation = true; width = 4;
        } else if (length >= 4 and second == '$' and third == '*' and fourth == 'H') {
          g2Designated = true; width = 4;
        } else if (length >= 4 and mode == STRATEGY_FORMAT_ISO_2022_CN_EXT and second == '$' and third == '+' and fourth >= 'I' and fourth <= 'M') {
          g3Designated = true; width = 4;
        } else if (second == 'N' and g2Designated and length >= 4 and third >= 0x21u and third <= 0x7Eu and fourth >= 0x21u and fourth <= 0x7Eu) {
          width = 4; produced = 1;
        } else if (second == 'O' and g3Designated and length >= 4 and third >= 0x21u and third <= 0x7Eu and fourth >= 0x21u and fourth <= 0x7Eu) {
          width = 4; produced = 1;
        } else failure = state::MALFORMED;
      }
      goto finished;
    }
    if (first == 0x0Eu or first == 0x0Fu) {
      if (japanese) { failure = state::MALFORMED; goto finished; }
      if (first == 0x0Eu and not designation and mode != STRATEGY_FORMAT_KOI7_SWITCHED) failure = state::MALFORMED;
      shifted = (first == 0x0Eu);
      produced = 0;
      goto finished;
    }
    if (first > 0x7Fu) { failure = state::MALFORMED; goto finished; }
    if (shifted) {
      if (length < 2 or first < 0x21u or first > 0x7Eu or second < 0x21u or second > 0x7Eu) {
        // KOI7 still represents a single 7-bit character after a shift.
        if (mode == STRATEGY_FORMAT_KOI7_SWITCHED) width = 1;
        else failure = state::MALFORMED;
      } else if (mode != STRATEGY_FORMAT_KOI7_SWITCHED) width = 2;
    }
    goto finished;
  }

  if (mode == STRATEGY_FORMAT_BOCU_1) {
    // ICU BOCU-1 lead-byte range rule: 0x50..0xCF => 1,
    // 0x25..0x4F or 0xD0..0xFA => 2, 0x22..0x24 or 0xFB..0xFD => 3,
    // otherwise (0x21 or 0xFE) => 4. 0xFF is a reset byte.
    // Without reconstructing the delta this is STRUCTURAL validation only.
    if (first == 0xFFu) { produced = 0; goto finished; }
    if (first <= 0x20u) goto finished;
    if (first >= 0x50u and first < 0xD0u) width = 1;
    else if ((first >= 0x25u and first < 0x50u) or (first >= 0xD0u and first <= 0xFAu)) width = 2;
    else if ((first >= 0x22u and first < 0x25u) or (first >= 0xFBu and first <= 0xFDu)) width = 3;
    else width = 4;
    if (length < width) failure = state::MALFORMED;
    else for (::std::size_t index = 1; index < width; ++index)
      if (text[index] == 0u) failure = state::MALFORMED;
    goto finished;
  }

  if (mode == STRATEGY_FORMAT_SCSU) {
    // UTR #6 / ICU SCSU: command bytes may change the active mode
    // without producing a character. Unicode mode stores UCS-2 big-endianness.
    if (not unicodeMode) {
      if (first >= 0x01u and first <= 0x08u) width = 2; // SQ0..SQ7
      else if (first == 0x0Bu) width = 3; // SDX
      else if (first == 0x0Eu) width = 3; // SQU, quoted UCS-2 unit
      else if (first == 0x0Fu) { unicodeMode = true; produced = 0; }
      else if (first >= 0x10u and first <= 0x17u) produced = 0; // SC0..SC7
      else if (first >= 0x18u and first <= 0x1Fu) { width = 2; produced = 0; } // SD0..SD7
      else if (first == 0x0Cu or (first >= 0x01u and first < 0x20u and first != 0x09u and first != 0x0Au and first != 0x0Du)) failure = state::MALFORMED;
    } else {
      if (first >= 0xE0u and first <= 0xE7u) { unicodeMode = false; produced = 0; }
      else if (first >= 0xE8u and first <= 0xEFu) { width = 2; unicodeMode = false; produced = 0; }
      else if (first == 0xF0u) width = 3; // UQU, quote a Unicode code unit
      else if (first == 0xF1u) { width = 3; unicodeMode = false; produced = 0; }
      else if (first >= 0xF2u) failure = state::MALFORMED;
      else {
        // In Unicode mode two big-endianness units making a surrogate pair
        // represent one scalar (four source bytes), not two characters.
        width = 2;
        if (length >= 2 and first >= 0xD8u and first <= 0xDBu) {
          if (second > 0xFFu or length < 4 or third < 0xDCu or third > 0xDFu) failure = state::MALFORMED;
          else width = 4;
        } else if (first >= 0xDCu and first <= 0xDFu) failure = state::MALFORMED;
      }
    }
    if (length < width) failure = state::MALFORMED;
    goto finished;
  }

  if (mode == STRATEGY_FORMAT_UTF_7 or mode == STRATEGY_FORMAT_UTF_7_IMAP) {
    // RFC 2152 UTF-7 and RFC 3501 IMAP modified UTF-7 pack UTF-16 code
    // units in Base64 without byte-aligned character boundaries. Parse each RUN
    // and count scalars; one run may yield multiple characters.
    bool const imap = mode == STRATEGY_FORMAT_UTF_7_IMAP;
    if (first > 0x7Fu or (imap and (first < 0x20u or first > 0x7Eu))) { failure = state::MALFORMED; goto finished; }
    if (first != (imap ? '&' : '+')) goto finished;
    if (length >= 2 and second == '-') { width = 2; goto finished; } // literal + or &
    unsigned accumulator = 0u;
    unsigned bits = 0u;
    unsigned pendingHigh = 0u;
    produced = 0;
    width = 1;
    while (width < length) {
      unsigned nextByte = text[width];
      int digit = nextByte >= 'A' and nextByte <= 'Z' ? static_cast<int>(nextByte - 'A') :
        nextByte >= 'a' and nextByte <= 'z' ? static_cast<int>(nextByte - 'a' + 26) :
        nextByte >= '0' and nextByte <= '9' ? static_cast<int>(nextByte - '0' + 52) :
        nextByte == '+' ? 62 : nextByte == (imap ? ',' : '/') ? 63 : -1;
      if (digit < 0) break;
      accumulator = (accumulator << 6) | static_cast<unsigned>(digit);
      bits += 6;
      ++width;
      if (bits >= 16) {
        bits -= 16;
        unsigned unit = (accumulator >> bits) & 0xFFFFu;
        accumulator &= (1u << bits) - 1u;
        if (pendingHigh) {
          if (unit < 0xDC00u or unit > 0xDFFFu) { failure = state::MALFORMED; break; }
          pendingHigh = 0;
          ++produced;
        } else if (unit >= 0xD800u and unit <= 0xDBFFu) pendingHigh = unit;
        else if (unit >= 0xDC00u and unit <= 0xDFFFu) { failure = state::MALFORMED; break; }
        else if (imap and unit >= 0x20u and unit <= 0x7Eu) { failure = state::MALFORMED; break; } // must be direct ASCII, or &-
        else ++produced;
      }
    }
    if (width == 1 or produced == 0 or pendingHigh or (bits != 0 and accumulator != 0)) failure = state::MALFORMED;
    if (imap and (width >= length or text[width] != '-')) failure = state::MALFORMED; // no implicit shift termination
    if (width < length and text[width] == '-') ++width;
    goto finished;
  }

  // Non-stateful strategies: inspect the lead byte and enough lookahead
  // to determine how many native bytes belong to the encoded character.
  // For 94x94 character sets, '94' means the 94 graphic byte positions
  // 0x21..0x7E in each of two code-set dimensions (row and column).
if (mode == STRATEGY_BYTE) goto finished;
if (mode == STRATEGY_BYTE_SEPTET) { failure = first <= 0x7Fu ? 0 : state::MALFORMED; goto finished; }

// Only validate lookahead bytes after determining they belong to this character.

if (mode == STRATEGY_DOUBLE_94) {
  // ISO 2022 94-character graphic sets use byte positions 0x21..0x7E.
  width = length < 2 ? length : 2;
  { failure = length >= 2 and (first >= 0x21u and first <= 0x7Eu) and (second >= 0x21u and second <= 0x7Eu) ? 0 : state::MALFORMED; goto finished; }
}

if (mode == STRATEGY_FORMAT_UCS_2 or mode == STRATEGY_FORMAT_UTF_16 or mode == STRATEGY_FORMAT_UTF_16BE or mode == STRATEGY_FORMAT_UTF_16LE) {
  width = length < 2 ? length : 2;
  if (length < 2 or second > 0xFFu) { failure = state::MALFORMED; goto finished; }

  unsigned unit = little ? first | (second << 8) : (first << 8) | second;
  if (mode == STRATEGY_FORMAT_UCS_2) { failure = unit >= 0xD800u and unit <= 0xDFFFu ? state::MALFORMED : 0; goto finished; }
  if (unit >= 0xDC00u and unit <= 0xDFFFu) { failure = state::MALFORMED; goto finished; }
  if (unit >= 0xD800u and unit <= 0xDBFFu) {
    if (length < 4) { width = length; { failure = state::MALFORMED; goto finished; } }
    if (third > 0xFFu or fourth > 0xFFu) { failure = state::MALFORMED; goto finished; }
    unsigned low = little ? third | (fourth << 8) : (third << 8) | fourth;
    if (low < 0xDC00u or low > 0xDFFFu) { failure = state::MALFORMED; goto finished; }
    width = 4;
  }
  goto finished;
}

if (mode == STRATEGY_FORMAT_UCS_4 or mode == STRATEGY_FORMAT_UTF_32 or mode == STRATEGY_FORMAT_UTF_32BE or mode == STRATEGY_FORMAT_UTF_32LE) {
  width = length < 4 ? length : 4;
  if (length < 4 or second > 0xFFu or third > 0xFFu or fourth > 0xFFu) { failure = state::MALFORMED; goto finished; }
  unsigned long value = little ?
    static_cast<unsigned long>(first) | (static_cast<unsigned long>(second) << 8) |
      (static_cast<unsigned long>(third) << 16) | (static_cast<unsigned long>(fourth) << 24) :
    (static_cast<unsigned long>(first) << 24) | (static_cast<unsigned long>(second) << 16) |
      (static_cast<unsigned long>(third) << 8) | static_cast<unsigned long>(fourth);
  if (value > 0x10FFFFul or (value >= 0xD800ul and value <= 0xDFFFul)) { failure = state::MALFORMED; goto finished; }
  goto finished;
}

if (mode == STRATEGY_FORMAT_UTF_8 or mode == STRATEGY_FORMAT_CESU_8) {
  if (first < 0x80u) goto finished;
  if (first < 0xC2u or first > 0xF4u) { failure = first == 0xC0u or first == 0xC1u ? state::OVERLONG : state::MALFORMED; goto finished; }
  if (first <= 0xDFu) width = 2;
  else if (first <= 0xEFu) width = 3;
  else if (mode == STRATEGY_FORMAT_UTF_8) width = 4;
  else { failure = state::MALFORMED; goto finished; }

  if (length < width) { width = length; { failure = state::MALFORMED; goto finished; } }
  if ((width >= 2 and second > 0xFFu) or (width >= 3 and third > 0xFFu) or
      (width == 4 and fourth > 0xFFu)) { failure = state::MALFORMED; goto finished; }
  if (not ((second & 0xC0u) == 0x80u) or (width >= 3 and not ((third & 0xC0u) == 0x80u)) or
      (width == 4 and not ((fourth & 0xC0u) == 0x80u))) { width = 1; { failure = state::MALFORMED; goto finished; } }
  if ((first == 0xE0u and second < 0xA0u) or (first == 0xF0u and second < 0x90u)) { failure = state::OVERLONG; goto finished; }
  if (first == 0xF4u and second > 0x8Fu) { failure = state::MALFORMED; goto finished; }

  if (first == 0xEDu and second >= 0xA0u) {
    if (mode == STRATEGY_FORMAT_UTF_8) { failure = state::MALFORMED; goto finished; }
    if (second >= 0xB0u) { failure = state::MALFORMED; goto finished; } // isolated low surrogate
    // CESU-8's surrogate pair encodes one supplementary character in 6 bytes.
    if (length < 6) { width = length; { failure = state::MALFORMED; goto finished; } }
    unsigned sixth = text[5];
    if (text[3] != 0xEDu or text[4] < 0xB0u or text[4] > 0xBFu or
        sixth > 0xFFu or (sixth & 0xC0u) != 0x80u) { failure = state::MALFORMED; goto finished; }
    width = 6;
  }
  goto finished;
}

if (mode == STRATEGY_FORMAT_BIG5) {
  if (first < 0x80u) goto finished;
  if (length < 2) { failure = state::MALFORMED; goto finished; }
  if (first < 0x81u or first > 0xFEu or not ((second >= 0x40u and second <= 0x7Eu) or
      (second >= 0xA1u and second <= 0xFEu))) { failure = state::MALFORMED; goto finished; }
  width = 2;
  goto finished;
}

if (mode == STRATEGY_FORMAT_SJIS) {
  if (first <= 0x7Fu or (first >= 0xA1u and first <= 0xDFu)) goto finished;
  if (not ((first >= 0x81u and first <= 0x9Fu) or (first >= 0xE0u and first <= 0xFCu)) or
      length < 2 or not ((second >= 0x40u and second <= 0x7Eu) or (second >= 0x80u and second <= 0xFCu))) { failure = state::MALFORMED; goto finished; }
  width = 2;
  goto finished;
}

if (mode == STRATEGY_FORMAT_EUC_KR or mode == STRATEGY_FORMAT_GB2312) {
  // EUC 94-character rows/columns use 0xA1..0xFE.
  if (first < 0x80u) goto finished;
  if (length < 2 or not (first >= 0xA1u and first <= 0xFEu) or not (second >= 0xA1u and second <= 0xFEu)) { failure = state::MALFORMED; goto finished; }
  width = 2;
  goto finished;
}

if (mode == STRATEGY_FORMAT_EUC_TW) {
  // EUC-TW: ASCII (1), CNS plane 1 (2), or SS2 8E A1..B0 with a CNS pair (4).
  // A1..B0 covers planes 1..16; this validates syntax, not assigned repertoire.
  if (first < 0x80u) goto finished;
  if (first == 0x8Eu) {
    width = length < 4 ? length : 4;
    if (length < 4 or second < 0xA1u or second > 0xB0u or
        third < 0xA1u or third > 0xFEu or fourth < 0xA1u or fourth > 0xFEu) failure = state::MALFORMED;
    goto finished;
  }
  width = length < 2 ? length : 2;
  if (length < 2 or first < 0xA1u or first > 0xFEu or second < 0xA1u or second > 0xFEu) failure = state::MALFORMED;
  goto finished;
}

if (mode == STRATEGY_FORMAT_EUC_JP) {
  if (first < 0x80u) goto finished;
  if (first == 0x8Eu) {
    if (length < 2 or second < 0xA1u or second > 0xDFu) { failure = state::MALFORMED; goto finished; }
    width = 2;
    goto finished;
  }
  if (first == 0x8Fu) {
    if (length < 3 or not (second >= 0xA1u and second <= 0xFEu) or not (third >= 0xA1u and third <= 0xFEu)) { failure = state::MALFORMED; goto finished; }
    width = 3;
    goto finished;
  }
  if (length < 2 or not (first >= 0xA1u and first <= 0xFEu) or not (second >= 0xA1u and second <= 0xFEu)) { failure = state::MALFORMED; goto finished; }
  width = 2;
  goto finished;
}

if (mode == STRATEGY_FORMAT_JOHAB) {
  // Johab/CP1361: ASCII, Hangul 84..D3 with 41..7E/81..FE trails,
  // or Hanja and symbols D9..DE/E0..F9 with 31..7E/91..FE trails.
  // Validate byte geometry, not which Hangul combinations are assigned.
  if (first < 0x80u) goto finished;
  width = length < 2 ? length : 2;
  if (length < 2) { failure = state::MALFORMED; goto finished; }
  if (first >= 0x84u and first <= 0xD3u) {
    if (not ((second >= 0x41u and second <= 0x7Eu) or (second >= 0x81u and second <= 0xFEu))) failure = state::MALFORMED;
  } else if ((first >= 0xD9u and first <= 0xDEu) or (first >= 0xE0u and first <= 0xF9u)) {
    if (not ((second >= 0x31u and second <= 0x7Eu) or (second >= 0x91u and second <= 0xFEu))) failure = state::MALFORMED;
  } else failure = state::MALFORMED;
  goto finished;
}

if (mode == STRATEGY_FORMAT_WINDOWS_949) {
  // Unified Hangul Code extends EUC-KR: lead 81..FE; ASCII-letter and
  // high-byte trails (41..5A, 61..7A, 81..FE) allow additional Hangul.
  if (first < 0x80u) goto finished;
  width = length < 2 ? length : 2;
  if (length < 2 or first < 0x81u or first > 0xFEu or
      not ((second >= 0x41u and second <= 0x5Au) or (second >= 0x61u and second <= 0x7Au) or
           (second >= 0x81u and second <= 0xFEu))) failure = state::MALFORMED;
  goto finished;
}

if (mode == STRATEGY_FORMAT_GBK or mode == STRATEGY_FORMAT_GB18030) {
  if (first < 0x80u) goto finished;
  if (first < 0x81u or first > 0xFEu or length < 2) { failure = state::MALFORMED; goto finished; }
  if (second >= 0x40u and second <= 0xFEu and second != 0x7Fu) { width = 2; goto finished; }
  if (mode == STRATEGY_FORMAT_GB18030 and second >= 0x30u and second <= 0x39u) {
    if (length < 4) { width = length; { failure = state::MALFORMED; goto finished; } }
    if (third >= 0x81u and third <= 0xFEu and fourth >= 0x30u and fourth <= 0x39u) {
      width = 4;
      goto finished;
    }
  }
  { failure = state::MALFORMED; goto finished; }
}

{ failure = state::UNSUPPORTED; goto finished; }

  finished:
    // Only commit shift-state changes when the source operation is valid.
    if (state != NULL) {
      state->endianness = endianness;
      state->characters = failure ? 0 : produced;
      state->invalids = failure ? width : 0;
      if (not failure) state->source.offset += width;
    }
    if (not failure) {
      unsigned const updatedFlags = (shifted ? static_cast<unsigned>(state::ISO_2022_SHIFTED) : 0u) |
        (designation ? static_cast<unsigned>(state::ISO_2022_G1_DESIGNATED) : 0u) |
        (g2Designated ? static_cast<unsigned>(state::ISO_2022_G2_DESIGNATED) : 0u) |
        (g3Designated ? static_cast<unsigned>(state::ISO_2022_G3_DESIGNATED) : 0u) |
        (unicodeMode ? static_cast<unsigned>(state::SCSU_UNICODE) : 0u);
      if (state != NULL) state->status = updatedFlags;
      if (status != NULL) *status = updatedFlags;
      return width;
    }
    return failure;
}

// Count encoded characters without allocating or constructing output bytes.
// Invalid text still follows the requested ignore/terminate/fallback policy.
extern "C" ::std::size_t length(unsigned char const text[], enum format::encoding const encoding, enum policy const policy = static_cast<enum policy>(ENDIAN_LITTLE | (INVALID_IGNORE ^ INVALID_TERMINATE)), struct state* const state = NULL) /* noexcept */ {
  /* TODO */
  if (NULL != state) state->reset();
  enum policy mode = format::strategy(encoding);
  // Without an explicit byte bound, locate the encoded NUL terminator.
  // UCS-2/UTF-16 require two aligned zero bytes; UCS-4/UTF-32 require four.
  // Stateful formats and inputs with embedded NUL must supply state->source.length.
  ::std::size_t length = state != NULL ? state->source.length : 0;
  if (not length) {
    unsigned unitBytes = 1u;
    // NUL code-unit width is determined by the encoding strategy.
    switch (mode) {
      case STRATEGY_FORMAT_UCS_2:
      case STRATEGY_FORMAT_UTF_16:
      case STRATEGY_FORMAT_UTF_16BE:
      case STRATEGY_FORMAT_UTF_16LE: unitBytes = 2u; break;
      case STRATEGY_FORMAT_UCS_4:
      case STRATEGY_FORMAT_UTF_32:
      case STRATEGY_FORMAT_UTF_32BE:
      case STRATEGY_FORMAT_UTF_32LE: unitBytes = 4u; break;
      default: break;
    }

    for (;;) {
      bool ended = true;
      for (unsigned index = 0; index < unitBytes; ++index)
        if (text[length + index]) ended = false;
      if (ended) break;
      if (length >= state::UNSUPPORTED - unitBytes) return state::COUNT_LIMIT;
      length += unitBytes;
    }
  }
  if (length >= state::UNSUPPORTED) return state::COUNT_LIMIT;

  // Determine byte order for fixed-width encodings, overriding the policy
  // for formats with explicit BE/LE suffixes. A leading UTF-16/UTF-32 BOM
  // selects byte order, consumes source bytes, but does not count as a character.
  bool little = (policy & ENDIAN_BIG) == 0;
  switch (mode) {
    case STRATEGY_FORMAT_UTF_16BE:
    case STRATEGY_FORMAT_UTF_32BE: little = false; break;
    case STRATEGY_FORMAT_UTF_16LE:
    case STRATEGY_FORMAT_UTF_32LE: little = true; break;
    default: break;
  }
  ::std::size_t bomBytes = 0;
  if (mode == STRATEGY_FORMAT_UTF_16 and length >= 2) {
    if (text[0] == 0xFEu and text[1] == 0xFFu) { little = false; bomBytes = 2; }
    else if (text[0] == 0xFFu and text[1] == 0xFEu) { little = true; bomBytes = 2; }
  }
  if (mode == STRATEGY_FORMAT_UTF_32 and length >= 4) {
    if (text[0] == 0 and text[1] == 0 and text[2] == 0xFEu and text[3] == 0xFFu) { little = false; bomBytes = 4; }
    else if (text[0] == 0xFFu and text[1] == 0xFEu and text[2] == 0 and text[3] == 0) { little = true; bomBytes = 4; }
  }
  ::std::size_t position = bomBytes;
  ::std::size_t count = 0;
  ::std::size_t status = 0;
  struct state iterator = {};
  iterator.endianness = little ? ENDIAN_LITTLE : ENDIAN_BIG;
  iterator.source.length = length;
  iterator.source.offset = position;
  while (position < length) {
    // next() returns the consumed byte width or one of state::* errors.
    ::std::size_t const result = next(&text[iterator.source.offset], encoding, &iterator);
    ::std::size_t const width = result >= state::UNSUPPORTED ? iterator.invalids : result;
    ::std::size_t const produced = iterator.characters;
    ::std::size_t const failure = result >= state::UNSUPPORTED ? result : 0;
    if (failure == 0) {
      if (width == 0 or width > length - position or count > state::UNSUPPORTED - produced) {
        status = state::COUNT_LIMIT;
        break;
      }
      position = iterator.source.offset;
      count += produced;
    } else {
      if (failure == state::UNSUPPORTED) { status = failure; break; }
      if (not (policy & INVALID_IGNORE)) { status = failure; break; }
      position += width ? width : 1;
      iterator.source.offset = position;
    }
  }
  // HZ and ISO-2022 use in-band shift commands (not characters); a stream
  // ending in its shifted set without the required reset is incomplete.
  if (not status and (iterator.status & state::ISO_2022_SHIFTED) and (mode == STRATEGY_FORMAT_HZ_GB_2312 or mode == STRATEGY_FORMAT_ISO_2022_JP or mode == STRATEGY_FORMAT_ISO_2022_JP_2 or mode == STRATEGY_FORMAT_ISO_2022_CN or mode == STRATEGY_FORMAT_ISO_2022_CN_EXT or mode == STRATEGY_FORMAT_ISO_2022_KR)) status = state::MALFORMED;
  if (state != NULL) { state->source.offset = position; state->status = iterator.status; state->endianness = iterator.endianness; }
  return status ? status : count;
}

/* Main */
int main(int, char*[]) {
  unsigned char const utf8[] = { 'A', 0xE2u, 0x82u, 0xACu, 0 };
  assert(length(utf8, format::UTF_8) == 2);
  assert(length(utf8, format::UTF_8, INVALID_TERMINATE) == 2);

  // next() returns character widths directly; its state retains source offset.
  struct state cursor = {};
  cursor.source.length = 4;
  assert(next(utf8, format::UTF_8, &cursor) == 1);
  assert(cursor.source.offset == 1 and cursor.characters == 1);
  assert(next(&utf8[cursor.source.offset], format::UTF_8, &cursor) == 3);
  assert(cursor.source.offset == 4 and cursor.characters == 1);
  cursor.status = state::ISO_2022_SHIFTED;
  cursor.invalids = 5;
  cursor.reset();
  assert(cursor.source.length == 4);
  assert(cursor.source.offset == 0);
  assert(cursor.status == 0 and cursor.invalids == 0 and cursor.characters == 0);

  unsigned char const overlong[] = { 0xC0u, 0xAFu, 0 };
  assert(length(overlong, format::UTF_8, INVALID_TERMINATE) == state::OVERLONG);
  struct state ignored = {};
  assert(length(overlong, format::UTF_8, INVALID_IGNORE, &ignored) == 0);
  assert(ignored.source.offset == 2);

  unsigned char const accented[] = { 0xC1u, 'A', 0 };
  assert(length(accented, format::ANSI_X3_110_1983, INVALID_TERMINATE) == 1);
  assert(length(accented, format::T_61_8BIT, INVALID_TERMINATE) == 1);

  unsigned char const utf16be[] = { 0, 0x41u, 0xD8u, 0x3Du, 0xDEu, 0, 0, 0 };
  struct state utf16BEBounded = {};
  utf16BEBounded.source.length = 6;
  assert(length(utf16be, format::UTF_16BE, INVALID_TERMINATE, &utf16BEBounded) == 2);
  assert(utf16BEBounded.source.offset == 6);

  unsigned char const gb18030[] = { 0x81u, 0x30u, 0x81u, 0x30u, 0 };
  assert(length(gb18030, format::GB18030) == 1);
  unsigned char const cesu8[] = { 0xEDu, 0xA0u, 0xBDu, 0xEDu, 0xB8u, 0x80u, 0 };
  assert(length(cesu8, format::CESU_8, INVALID_TERMINATE) == 1);
  assert(format::maximum<format::UTF_8>::value == 4 and format::maximum<format::CESU_8>::value == 6);

  // The public next() supports bounded iteration without output parameters.
  struct state malformedCursor = {};
  malformedCursor.source.length = 2;
  unsigned char const invalidUtf8[] = { 0xC0u, 0xAFu };
  assert(next(invalidUtf8, format::UTF_8, &malformedCursor) == state::OVERLONG);
  assert(malformedCursor.source.offset == 0 and malformedCursor.invalids == 1);
  assert(next(utf8, format::UTF_8) == 1);

  // Byte order is retained after a standalone BOM; BOMs produce no characters.
  struct state utf16Cursor = {};
  utf16Cursor.source.length = 8;
  unsigned char const withBom[] = { 0xFEu, 0xFFu, 0, 'A', 0xD8u, 0x3Du, 0xDEu, 0, 0, 0 };
  assert(next(withBom, format::UTF_16, &utf16Cursor) == 2);
  assert(utf16Cursor.characters == 0 and utf16Cursor.endianness == ENDIAN_BIG);
  assert(next(&withBom[utf16Cursor.source.offset], format::UTF_16, &utf16Cursor) == 2);
  assert(next(&withBom[utf16Cursor.source.offset], format::UTF_16, &utf16Cursor) == 4);
  assert(utf16Cursor.source.offset == 8 and utf16Cursor.characters == 1);

  // Newly supported legacy and IMAP encodings: structural widths and errors.
  assert(format::maximum<format::EUC_JP>::value == 3);
  assert(format::maximum<format::EUC_TW>::value == 4);
  assert(format::maximum<format::ISO_8859_11>::value == 1);
  assert(format::maximum<format::JOHAB>::value == 2);
  assert(format::maximum<format::WINDOWS_949>::value == 2);
  assert(format::maximum<format::UTF_7_IMAP>::value == 0);
  unsigned char const thai[] = { 'A', 0xA1u, 0xFBu, 0 };
  assert(length(thai, format::ISO_8859_11, INVALID_TERMINATE) == 3);

  unsigned char const eucJP[] = { 'A', 0xA4u, 0xA2u, 0x8Eu, 0xA6u, 0x8Fu, 0xA2u, 0xAFu, 0 };
  assert(length(eucJP, format::EUC_JP, INVALID_TERMINATE) == 4);
  assert(length(eucJP, format::CP51932, INVALID_TERMINATE) == 4);
  unsigned char const eucTW[] = { 'A', 0xA4u, 0xA1u, 0x8Eu, 0xA2u, 0xA1u, 0xA1u, 0x8Eu, 0xB0u, 0xA1u, 0xA1u, 0 };
  assert(length(eucTW, format::EUC_TW, INVALID_TERMINATE) == 4);
  unsigned char const johab[] = { 'A', 0x84u, 0x41u, 0xD9u, 0x31u, 0xE0u, 0x91u, 0 };
  assert(length(johab, format::JOHAB, INVALID_TERMINATE) == 4);
  unsigned char const uhc[] = { 'A', 0x81u, 0x41u, 0x81u, 0x61u, 0xA1u, 0xA1u, 0 };
  assert(length(uhc, format::WINDOWS_949, INVALID_TERMINATE) == 4);

  struct state multibyteCursor = {};
  multibyteCursor.source.length = 3;
  unsigned char const eucTWTruncated[] = { 0x8Eu, 0xA2u, 0xA1u };
  assert(next(eucTWTruncated, format::EUC_TW, &multibyteCursor) == state::MALFORMED);
  assert(multibyteCursor.invalids == 3 and multibyteCursor.source.offset == 0);
  unsigned char const eucTWBadPlane[] = { 0x8Eu, 0xB1u, 0xA1u, 0xA1u, 0 };
  assert(length(eucTWBadPlane, format::EUC_TW, INVALID_TERMINATE) == state::MALFORMED);
  unsigned char const eucJPBadTrail[] = { 0x8Eu, 0x80u, 0 };
  assert(length(eucJPBadTrail, format::EUC_JP, INVALID_TERMINATE) == state::MALFORMED);
  unsigned char const johabBadLead[] = { 0xD8u, 0x91u, 0 };
  assert(length(johabBadLead, format::JOHAB, INVALID_TERMINATE) == state::MALFORMED);
  unsigned char const johabBadTrail[] = { 0x84u, 0x40u, 0 };
  assert(length(johabBadTrail, format::JOHAB, INVALID_TERMINATE) == state::MALFORMED);
  unsigned char const uhcBadTrail[] = { 0x81u, 0x5Bu, 0 };
  assert(length(uhcBadTrail, format::WINDOWS_949, INVALID_TERMINATE) == state::MALFORMED);
  unsigned char const uhcTruncated[] = { 0x81u, 0 };
  assert(length(uhcTruncated, format::WINDOWS_949, INVALID_TERMINATE) == state::MALFORMED);

  #if CHAR_BIT == 8
    // IMAP modified UTF-7 uses &- for a literal ampersand and comma instead of slash.
    unsigned char const imap[] = { 'A', '&', '-', '&', 'A', 'O', 'k', '-', '&', 'A', ',', '8', '-', 0 };
    assert(length(imap, format::UTF_7_IMAP, INVALID_TERMINATE) == 4);
    unsigned char const imapNotClosed[] = { '&', 'A', 'O', 'k', 0 };
    assert(length(imapNotClosed, format::UTF_7_IMAP, INVALID_TERMINATE) == state::MALFORMED);
    unsigned char const imapWrongAlphabet[] = { '&', 'A', '/', '8', '-', 0 };
    assert(length(imapWrongAlphabet, format::UTF_7_IMAP, INVALID_TERMINATE) == state::MALFORMED);
    unsigned char const imapRedundantEncoding[] = { '&', 'A', 'E', 'E', '-', 0 }; // ASCII 'A' must be direct
    assert(length(imapRedundantEncoding, format::UTF_7_IMAP, INVALID_TERMINATE) == state::MALFORMED);
    unsigned char const imapBadDirect[] = { 0x1Fu, 0 };
    assert(length(imapBadDirect, format::UTF_7_IMAP, INVALID_TERMINATE) == state::MALFORMED);
    unsigned char imapNul[5] = {};
    assert(nul(format::UTF_7_IMAP, imapNul, sizeof(imapNul)) == 5);
    assert(imapNul[0] == '&' and imapNul[1] == 'A' and imapNul[4] == '-');

    unsigned char const hz[] = { 'A', '~', '{', 0x3Du, 0x3Bu, '~', '}', 'B', 0 };
    struct state hzLength = {};
    assert(length(hz, format::HZ_GB_2312, INVALID_TERMINATE, &hzLength) == 3);
    assert(hzLength.source.offset == 8);
    struct state hzCursor = {};
    hzCursor.source.length = 8;
    assert(next(hz, format::HZ_GB_2312, &hzCursor) == 1);
    assert(next(&hz[hzCursor.source.offset], format::HZ_GB_2312, &hzCursor) == 2);
    assert(hzCursor.characters == 0 and (hzCursor.status & state::ISO_2022_SHIFTED));
    assert(next(&hz[hzCursor.source.offset], format::HZ_GB_2312, &hzCursor) == 2);
    assert(hzCursor.characters == 1);
    assert(next(&hz[hzCursor.source.offset], format::HZ_GB_2312, &hzCursor) == 2);
    assert(hzCursor.characters == 0 and not (hzCursor.status & state::ISO_2022_SHIFTED));
    assert(next(&hz[hzCursor.source.offset], format::HZ_GB_2312, &hzCursor) == 1);
    assert(hzCursor.source.offset == 8);

    unsigned char const jp[] = { 0x1Bu, '$', 'B', 0x24u, 0x22u, 0x24u, 0x24u, 0x1Bu, '(', 'B', 0 };
    struct state jpLength = {};
    assert(length(jp, format::ISO_2022_JP, INVALID_TERMINATE, &jpLength) == 2);
    assert(jpLength.source.offset == 10);
    assert(length(jp, format::CP50220, INVALID_TERMINATE) == 2);
    unsigned char const korean[] = { 0x1Bu, '$', ')', 'C', 0x0Eu, 0x30u, 0x21u, 0x0Fu, 0 };
    assert(length(korean, format::ISO_2022_KR, INVALID_TERMINATE) == 1);
    unsigned char const chinese[] = { 0x1Bu, '$', ')', 'A', 0x0Eu, 0x3Du, 0x3Bu, 0x0Fu, 0 };
    assert(length(chinese, format::ISO_2022_CN, INVALID_TERMINATE) == 1);
    unsigned char const utf7[] = { '+', 'I', 'K', 'w', '-', 0 }; // U+20AC
    assert(length(utf7, format::UTF_7, INVALID_TERMINATE) == 1);
    unsigned char const utf7plus[] = { '+', '-', 0 };
    assert(length(utf7plus, format::UTF_7, INVALID_TERMINATE) == 1);
    unsigned char const bocu[] = { 0x90u, 0xD0u, 0x21u, 0 };
    assert(length(bocu, format::BOCU_1, INVALID_TERMINATE) == 2);
    unsigned char const scsu[] = { 0x0Fu, 0x20u, 0xACu, 0 };
    assert(length(scsu, format::SCSU, INVALID_TERMINATE) == 1);

    unsigned char const jp2[] = { 0x1Bu, '.', 'A', 0x1Bu, 'N', 0x41u, 0 };
    assert(length(jp2, format::ISO_2022_JP_2, INVALID_TERMINATE) == 1);
    unsigned char const cnExt[] = { 0x1Bu, '$', '+', 'I', 0x1Bu, 'O', 0x21u, 0x21u, 0 };
    assert(length(cnExt, format::ISO_2022_CN_EXT, INVALID_TERMINATE) == 1);
    unsigned char const utf7Scalar[] = { '+', '2', 'D', '3', 'e', 'A', 'A', '-', 0 }; // U+1F600
    assert(length(utf7Scalar, format::UTF_7, INVALID_TERMINATE) == 1);
    // A UTF-7 Base64 run may produce several characters per next() call.
    unsigned char const utf7Pair[] = { '+', 'A', 'E', 'I', 'A', 'Q', 'w', '-', 0 }; // U+0042, U+0043
    struct state utf7Length = {};
    assert(length(utf7Pair, format::UTF_7, INVALID_TERMINATE, &utf7Length) == 2);
    assert(utf7Length.source.offset == 8);
    struct state utf7Cursor = {};
    utf7Cursor.source.length = 8;
    assert(next(utf7Pair, format::UTF_7, &utf7Cursor) == 8);
    assert(utf7Cursor.characters == 2 and utf7Cursor.source.offset == 8);
    unsigned char const brokenHZ[] = { '~', '{', 0x3Du, 0x3Bu, 0 }; // missing ~}
    assert(length(brokenHZ, format::HZ_GB_2312, INVALID_TERMINATE) == state::MALFORMED);
    unsigned char const scsuSupplementary[] = { 0x0Fu, 0xD8u, 0x3Du, 0xDEu, 0x00u, 0 };
    // For embedded zero octets, use an explicit byte bound instead of C-string scanning.
    struct state bounded = {};
    bounded.source.length = 5;
    assert(length(scsuSupplementary, format::SCSU, INVALID_TERMINATE, &bounded) == 1);
    assert(bounded.source.offset == 5);
  #endif
}
