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
  static ::std::size_t const COUNT_LIMIT, MALFORMED, NO_SPACE, OVERLONG, UNSUPPORTED, NO_CHARACTER;

  struct /* final */ { ::std::size_t length, offset;  } source;         // ->> Zero byte length denotes NUL sentinel; Cursor index
  ::std::size_t                                         characters;     // ->> Number of characters (typically `0zu` for shift commands and `> 1zu` for UTF-7)
  enum policy                                           endianness : 3; //
  ::std::size_t                                         invalids;       // ->> Erroneous bytes to skip for recovery
  unsigned char                                         status : 5;     //

  // ->> unicode() keeps a UTF-7 Base64 run until its last Unicode scalar is returned.
  struct /* final */ {
    unsigned char const* text;
    ::std::size_t width, position, remaining;
    unsigned accumulator, bits, highSurrogate;
  } decoded;

  /* ... */
  void reset() /* noexcept */ {
    this -> characters    = 0u;
    this -> endianness    = static_cast<enum policy>(0x00u);
    this -> invalids      = 0u;
    this -> source.offset = 0u;
    this -> status        = 0x00u;
    this -> decoded.text          = static_cast<unsigned char const*>(NULL);
    this -> decoded.width         = 0u;
    this -> decoded.position      = 0u;
    this -> decoded.remaining     = 0u;
    this -> decoded.accumulator   = 0u;
    this -> decoded.bits          = 0u;
    this -> decoded.highSurrogate = 0u;
  }
};
  ::std::size_t const state::COUNT_LIMIT  = static_cast< ::std::size_t>(-1),
                      state::MALFORMED    = static_cast< ::std::size_t>(-2),
                      state::NO_CHARACTER = static_cast< ::std::size_t>(-3),
                      state::NO_SPACE     = static_cast< ::std::size_t>(-4),
                      state::OVERLONG     = static_cast< ::std::size_t>(-5),
                      state::UNSUPPORTED  = static_cast< ::std::size_t>(-6);

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

// Verified single-byte mappings generated from Python codec tables. 0xFFFF marks an undefined byte.
// No platform code-page APIs or third-party libraries are required at runtime.
// ->> HP_ROMAN8 (hp-roman8), 128 entries.
static unsigned short const unicode_HP_ROMAN8[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x00C0u, 0x00C2u, 0x00C8u, 0x00CAu, 0x00CBu, 0x00CEu, 0x00CFu,
  0x00B4u, 0x02CBu, 0x02C6u, 0x00A8u, 0x02DCu, 0x00D9u, 0x00DBu, 0x20A4u,
  0x00AFu, 0x00DDu, 0x00FDu, 0x00B0u, 0x00C7u, 0x00E7u, 0x00D1u, 0x00F1u,
  0x00A1u, 0x00BFu, 0x00A4u, 0x00A3u, 0x00A5u, 0x00A7u, 0x0192u, 0x00A2u,
  0x00E2u, 0x00EAu, 0x00F4u, 0x00FBu, 0x00E1u, 0x00E9u, 0x00F3u, 0x00FAu,
  0x00E0u, 0x00E8u, 0x00F2u, 0x00F9u, 0x00E4u, 0x00EBu, 0x00F6u, 0x00FCu,
  0x00C5u, 0x00EEu, 0x00D8u, 0x00C6u, 0x00E5u, 0x00EDu, 0x00F8u, 0x00E6u,
  0x00C4u, 0x00ECu, 0x00D6u, 0x00DCu, 0x00C9u, 0x00EFu, 0x00DFu, 0x00D4u,
  0x00C1u, 0x00C3u, 0x00E3u, 0x00D0u, 0x00F0u, 0x00CDu, 0x00CCu, 0x00D3u,
  0x00D2u, 0x00D5u, 0x00F5u, 0x0160u, 0x0161u, 0x00DAu, 0x0178u, 0x00FFu,
  0x00DEu, 0x00FEu, 0x00B7u, 0x00B5u, 0x00B6u, 0x00BEu, 0x2014u, 0x00BCu,
  0x00BDu, 0x00AAu, 0x00BAu, 0x00ABu, 0x25A0u, 0x00BBu, 0x00B1u, 0xFFFFu,
};

// ->> IBM037 (cp037), 256 entries.
static unsigned short const unicode_IBM037[] = {
  0x0000u, 0x0001u, 0x0002u, 0x0003u, 0x009Cu, 0x0009u, 0x0086u, 0x007Fu,
  0x0097u, 0x008Du, 0x008Eu, 0x000Bu, 0x000Cu, 0x000Du, 0x000Eu, 0x000Fu,
  0x0010u, 0x0011u, 0x0012u, 0x0013u, 0x009Du, 0x0085u, 0x0008u, 0x0087u,
  0x0018u, 0x0019u, 0x0092u, 0x008Fu, 0x001Cu, 0x001Du, 0x001Eu, 0x001Fu,
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x000Au, 0x0017u, 0x001Bu,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x0005u, 0x0006u, 0x0007u,
  0x0090u, 0x0091u, 0x0016u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0004u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x0014u, 0x0015u, 0x009Eu, 0x001Au,
  0x0020u, 0x00A0u, 0x00E2u, 0x00E4u, 0x00E0u, 0x00E1u, 0x00E3u, 0x00E5u,
  0x00E7u, 0x00F1u, 0x00A2u, 0x002Eu, 0x003Cu, 0x0028u, 0x002Bu, 0x007Cu,
  0x0026u, 0x00E9u, 0x00EAu, 0x00EBu, 0x00E8u, 0x00EDu, 0x00EEu, 0x00EFu,
  0x00ECu, 0x00DFu, 0x0021u, 0x0024u, 0x002Au, 0x0029u, 0x003Bu, 0x00ACu,
  0x002Du, 0x002Fu, 0x00C2u, 0x00C4u, 0x00C0u, 0x00C1u, 0x00C3u, 0x00C5u,
  0x00C7u, 0x00D1u, 0x00A6u, 0x002Cu, 0x0025u, 0x005Fu, 0x003Eu, 0x003Fu,
  0x00F8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x00C8u, 0x00CDu, 0x00CEu, 0x00CFu,
  0x00CCu, 0x0060u, 0x003Au, 0x0023u, 0x0040u, 0x0027u, 0x003Du, 0x0022u,
  0x00D8u, 0x0061u, 0x0062u, 0x0063u, 0x0064u, 0x0065u, 0x0066u, 0x0067u,
  0x0068u, 0x0069u, 0x00ABu, 0x00BBu, 0x00F0u, 0x00FDu, 0x00FEu, 0x00B1u,
  0x00B0u, 0x006Au, 0x006Bu, 0x006Cu, 0x006Du, 0x006Eu, 0x006Fu, 0x0070u,
  0x0071u, 0x0072u, 0x00AAu, 0x00BAu, 0x00E6u, 0x00B8u, 0x00C6u, 0x00A4u,
  0x00B5u, 0x007Eu, 0x0073u, 0x0074u, 0x0075u, 0x0076u, 0x0077u, 0x0078u,
  0x0079u, 0x007Au, 0x00A1u, 0x00BFu, 0x00D0u, 0x00DDu, 0x00DEu, 0x00AEu,
  0x005Eu, 0x00A3u, 0x00A5u, 0x00B7u, 0x00A9u, 0x00A7u, 0x00B6u, 0x00BCu,
  0x00BDu, 0x00BEu, 0x005Bu, 0x005Du, 0x00AFu, 0x00A8u, 0x00B4u, 0x00D7u,
  0x007Bu, 0x0041u, 0x0042u, 0x0043u, 0x0044u, 0x0045u, 0x0046u, 0x0047u,
  0x0048u, 0x0049u, 0x00ADu, 0x00F4u, 0x00F6u, 0x00F2u, 0x00F3u, 0x00F5u,
  0x007Du, 0x004Au, 0x004Bu, 0x004Cu, 0x004Du, 0x004Eu, 0x004Fu, 0x0050u,
  0x0051u, 0x0052u, 0x00B9u, 0x00FBu, 0x00FCu, 0x00F9u, 0x00FAu, 0x00FFu,
  0x005Cu, 0x00F7u, 0x0053u, 0x0054u, 0x0055u, 0x0056u, 0x0057u, 0x0058u,
  0x0059u, 0x005Au, 0x00B2u, 0x00D4u, 0x00D6u, 0x00D2u, 0x00D3u, 0x00D5u,
  0x0030u, 0x0031u, 0x0032u, 0x0033u, 0x0034u, 0x0035u, 0x0036u, 0x0037u,
  0x0038u, 0x0039u, 0x00B3u, 0x00DBu, 0x00DCu, 0x00D9u, 0x00DAu, 0x009Fu,
};

// ->> IBM273 (cp273), 256 entries.
static unsigned short const unicode_IBM273[] = {
  0x0000u, 0x0001u, 0x0002u, 0x0003u, 0x009Cu, 0x0009u, 0x0086u, 0x007Fu,
  0x0097u, 0x008Du, 0x008Eu, 0x000Bu, 0x000Cu, 0x000Du, 0x000Eu, 0x000Fu,
  0x0010u, 0x0011u, 0x0012u, 0x0013u, 0x009Du, 0x0085u, 0x0008u, 0x0087u,
  0x0018u, 0x0019u, 0x0092u, 0x008Fu, 0x001Cu, 0x001Du, 0x001Eu, 0x001Fu,
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x000Au, 0x0017u, 0x001Bu,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x0005u, 0x0006u, 0x0007u,
  0x0090u, 0x0091u, 0x0016u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0004u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x0014u, 0x0015u, 0x009Eu, 0x001Au,
  0x0020u, 0x00A0u, 0x00E2u, 0x007Bu, 0x00E0u, 0x00E1u, 0x00E3u, 0x00E5u,
  0x00E7u, 0x00F1u, 0x00C4u, 0x002Eu, 0x003Cu, 0x0028u, 0x002Bu, 0x0021u,
  0x0026u, 0x00E9u, 0x00EAu, 0x00EBu, 0x00E8u, 0x00EDu, 0x00EEu, 0x00EFu,
  0x00ECu, 0x007Eu, 0x00DCu, 0x0024u, 0x002Au, 0x0029u, 0x003Bu, 0x005Eu,
  0x002Du, 0x002Fu, 0x00C2u, 0x005Bu, 0x00C0u, 0x00C1u, 0x00C3u, 0x00C5u,
  0x00C7u, 0x00D1u, 0x00F6u, 0x002Cu, 0x0025u, 0x005Fu, 0x003Eu, 0x003Fu,
  0x00F8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x00C8u, 0x00CDu, 0x00CEu, 0x00CFu,
  0x00CCu, 0x0060u, 0x003Au, 0x0023u, 0x00A7u, 0x0027u, 0x003Du, 0x0022u,
  0x00D8u, 0x0061u, 0x0062u, 0x0063u, 0x0064u, 0x0065u, 0x0066u, 0x0067u,
  0x0068u, 0x0069u, 0x00ABu, 0x00BBu, 0x00F0u, 0x00FDu, 0x00FEu, 0x00B1u,
  0x00B0u, 0x006Au, 0x006Bu, 0x006Cu, 0x006Du, 0x006Eu, 0x006Fu, 0x0070u,
  0x0071u, 0x0072u, 0x00AAu, 0x00BAu, 0x00E6u, 0x00B8u, 0x00C6u, 0x00A4u,
  0x00B5u, 0x00DFu, 0x0073u, 0x0074u, 0x0075u, 0x0076u, 0x0077u, 0x0078u,
  0x0079u, 0x007Au, 0x00A1u, 0x00BFu, 0x00D0u, 0x00DDu, 0x00DEu, 0x00AEu,
  0x00A2u, 0x00A3u, 0x00A5u, 0x00B7u, 0x00A9u, 0x0040u, 0x00B6u, 0x00BCu,
  0x00BDu, 0x00BEu, 0x00ACu, 0x007Cu, 0x203Eu, 0x00A8u, 0x00B4u, 0x00D7u,
  0x00E4u, 0x0041u, 0x0042u, 0x0043u, 0x0044u, 0x0045u, 0x0046u, 0x0047u,
  0x0048u, 0x0049u, 0x00ADu, 0x00F4u, 0x00A6u, 0x00F2u, 0x00F3u, 0x00F5u,
  0x00FCu, 0x004Au, 0x004Bu, 0x004Cu, 0x004Du, 0x004Eu, 0x004Fu, 0x0050u,
  0x0051u, 0x0052u, 0x00B9u, 0x00FBu, 0x007Du, 0x00F9u, 0x00FAu, 0x00FFu,
  0x00D6u, 0x00F7u, 0x0053u, 0x0054u, 0x0055u, 0x0056u, 0x0057u, 0x0058u,
  0x0059u, 0x005Au, 0x00B2u, 0x00D4u, 0x005Cu, 0x00D2u, 0x00D3u, 0x00D5u,
  0x0030u, 0x0031u, 0x0032u, 0x0033u, 0x0034u, 0x0035u, 0x0036u, 0x0037u,
  0x0038u, 0x0039u, 0x00B3u, 0x00DBu, 0x005Du, 0x00D9u, 0x00DAu, 0x009Fu,
};

// ->> IBM424 (cp424), 256 entries.
static unsigned short const unicode_IBM424[] = {
  0x0000u, 0x0001u, 0x0002u, 0x0003u, 0x009Cu, 0x0009u, 0x0086u, 0x007Fu,
  0x0097u, 0x008Du, 0x008Eu, 0x000Bu, 0x000Cu, 0x000Du, 0x000Eu, 0x000Fu,
  0x0010u, 0x0011u, 0x0012u, 0x0013u, 0x009Du, 0x0085u, 0x0008u, 0x0087u,
  0x0018u, 0x0019u, 0x0092u, 0x008Fu, 0x001Cu, 0x001Du, 0x001Eu, 0x001Fu,
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x000Au, 0x0017u, 0x001Bu,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x0005u, 0x0006u, 0x0007u,
  0x0090u, 0x0091u, 0x0016u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0004u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x0014u, 0x0015u, 0x009Eu, 0x001Au,
  0x0020u, 0x05D0u, 0x05D1u, 0x05D2u, 0x05D3u, 0x05D4u, 0x05D5u, 0x05D6u,
  0x05D7u, 0x05D8u, 0x00A2u, 0x002Eu, 0x003Cu, 0x0028u, 0x002Bu, 0x007Cu,
  0x0026u, 0x05D9u, 0x05DAu, 0x05DBu, 0x05DCu, 0x05DDu, 0x05DEu, 0x05DFu,
  0x05E0u, 0x05E1u, 0x0021u, 0x0024u, 0x002Au, 0x0029u, 0x003Bu, 0x00ACu,
  0x002Du, 0x002Fu, 0x05E2u, 0x05E3u, 0x05E4u, 0x05E5u, 0x05E6u, 0x05E7u,
  0x05E8u, 0x05E9u, 0x00A6u, 0x002Cu, 0x0025u, 0x005Fu, 0x003Eu, 0x003Fu,
  0xFFFFu, 0x05EAu, 0xFFFFu, 0xFFFFu, 0x00A0u, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0x2017u, 0x0060u, 0x003Au, 0x0023u, 0x0040u, 0x0027u, 0x003Du, 0x0022u,
  0xFFFFu, 0x0061u, 0x0062u, 0x0063u, 0x0064u, 0x0065u, 0x0066u, 0x0067u,
  0x0068u, 0x0069u, 0x00ABu, 0x00BBu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x00B1u,
  0x00B0u, 0x006Au, 0x006Bu, 0x006Cu, 0x006Du, 0x006Eu, 0x006Fu, 0x0070u,
  0x0071u, 0x0072u, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x00B8u, 0xFFFFu, 0x00A4u,
  0x00B5u, 0x007Eu, 0x0073u, 0x0074u, 0x0075u, 0x0076u, 0x0077u, 0x0078u,
  0x0079u, 0x007Au, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x00AEu,
  0x005Eu, 0x00A3u, 0x00A5u, 0x00B7u, 0x00A9u, 0x00A7u, 0x00B6u, 0x00BCu,
  0x00BDu, 0x00BEu, 0x005Bu, 0x005Du, 0x00AFu, 0x00A8u, 0x00B4u, 0x00D7u,
  0x007Bu, 0x0041u, 0x0042u, 0x0043u, 0x0044u, 0x0045u, 0x0046u, 0x0047u,
  0x0048u, 0x0049u, 0x00ADu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0x007Du, 0x004Au, 0x004Bu, 0x004Cu, 0x004Du, 0x004Eu, 0x004Fu, 0x0050u,
  0x0051u, 0x0052u, 0x00B9u, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0x005Cu, 0x00F7u, 0x0053u, 0x0054u, 0x0055u, 0x0056u, 0x0057u, 0x0058u,
  0x0059u, 0x005Au, 0x00B2u, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0x0030u, 0x0031u, 0x0032u, 0x0033u, 0x0034u, 0x0035u, 0x0036u, 0x0037u,
  0x0038u, 0x0039u, 0x00B3u, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x009Fu,
};

// ->> IBM437 (cp437), 128 entries.
static unsigned short const unicode_IBM437[] = {
  0x00C7u, 0x00FCu, 0x00E9u, 0x00E2u, 0x00E4u, 0x00E0u, 0x00E5u, 0x00E7u,
  0x00EAu, 0x00EBu, 0x00E8u, 0x00EFu, 0x00EEu, 0x00ECu, 0x00C4u, 0x00C5u,
  0x00C9u, 0x00E6u, 0x00C6u, 0x00F4u, 0x00F6u, 0x00F2u, 0x00FBu, 0x00F9u,
  0x00FFu, 0x00D6u, 0x00DCu, 0x00A2u, 0x00A3u, 0x00A5u, 0x20A7u, 0x0192u,
  0x00E1u, 0x00EDu, 0x00F3u, 0x00FAu, 0x00F1u, 0x00D1u, 0x00AAu, 0x00BAu,
  0x00BFu, 0x2310u, 0x00ACu, 0x00BDu, 0x00BCu, 0x00A1u, 0x00ABu, 0x00BBu,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x2561u, 0x2562u, 0x2556u,
  0x2555u, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x255Cu, 0x255Bu, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x255Eu, 0x255Fu,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x2567u,
  0x2568u, 0x2564u, 0x2565u, 0x2559u, 0x2558u, 0x2552u, 0x2553u, 0x256Bu,
  0x256Au, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x258Cu, 0x2590u, 0x2580u,
  0x03B1u, 0x00DFu, 0x0393u, 0x03C0u, 0x03A3u, 0x03C3u, 0x00B5u, 0x03C4u,
  0x03A6u, 0x0398u, 0x03A9u, 0x03B4u, 0x221Eu, 0x03C6u, 0x03B5u, 0x2229u,
  0x2261u, 0x00B1u, 0x2265u, 0x2264u, 0x2320u, 0x2321u, 0x00F7u, 0x2248u,
  0x00B0u, 0x2219u, 0x00B7u, 0x221Au, 0x207Fu, 0x00B2u, 0x25A0u, 0x00A0u,
};

// ->> IBM500 (cp500), 256 entries.
static unsigned short const unicode_IBM500[] = {
  0x0000u, 0x0001u, 0x0002u, 0x0003u, 0x009Cu, 0x0009u, 0x0086u, 0x007Fu,
  0x0097u, 0x008Du, 0x008Eu, 0x000Bu, 0x000Cu, 0x000Du, 0x000Eu, 0x000Fu,
  0x0010u, 0x0011u, 0x0012u, 0x0013u, 0x009Du, 0x0085u, 0x0008u, 0x0087u,
  0x0018u, 0x0019u, 0x0092u, 0x008Fu, 0x001Cu, 0x001Du, 0x001Eu, 0x001Fu,
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x000Au, 0x0017u, 0x001Bu,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x0005u, 0x0006u, 0x0007u,
  0x0090u, 0x0091u, 0x0016u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0004u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x0014u, 0x0015u, 0x009Eu, 0x001Au,
  0x0020u, 0x00A0u, 0x00E2u, 0x00E4u, 0x00E0u, 0x00E1u, 0x00E3u, 0x00E5u,
  0x00E7u, 0x00F1u, 0x005Bu, 0x002Eu, 0x003Cu, 0x0028u, 0x002Bu, 0x0021u,
  0x0026u, 0x00E9u, 0x00EAu, 0x00EBu, 0x00E8u, 0x00EDu, 0x00EEu, 0x00EFu,
  0x00ECu, 0x00DFu, 0x005Du, 0x0024u, 0x002Au, 0x0029u, 0x003Bu, 0x005Eu,
  0x002Du, 0x002Fu, 0x00C2u, 0x00C4u, 0x00C0u, 0x00C1u, 0x00C3u, 0x00C5u,
  0x00C7u, 0x00D1u, 0x00A6u, 0x002Cu, 0x0025u, 0x005Fu, 0x003Eu, 0x003Fu,
  0x00F8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x00C8u, 0x00CDu, 0x00CEu, 0x00CFu,
  0x00CCu, 0x0060u, 0x003Au, 0x0023u, 0x0040u, 0x0027u, 0x003Du, 0x0022u,
  0x00D8u, 0x0061u, 0x0062u, 0x0063u, 0x0064u, 0x0065u, 0x0066u, 0x0067u,
  0x0068u, 0x0069u, 0x00ABu, 0x00BBu, 0x00F0u, 0x00FDu, 0x00FEu, 0x00B1u,
  0x00B0u, 0x006Au, 0x006Bu, 0x006Cu, 0x006Du, 0x006Eu, 0x006Fu, 0x0070u,
  0x0071u, 0x0072u, 0x00AAu, 0x00BAu, 0x00E6u, 0x00B8u, 0x00C6u, 0x00A4u,
  0x00B5u, 0x007Eu, 0x0073u, 0x0074u, 0x0075u, 0x0076u, 0x0077u, 0x0078u,
  0x0079u, 0x007Au, 0x00A1u, 0x00BFu, 0x00D0u, 0x00DDu, 0x00DEu, 0x00AEu,
  0x00A2u, 0x00A3u, 0x00A5u, 0x00B7u, 0x00A9u, 0x00A7u, 0x00B6u, 0x00BCu,
  0x00BDu, 0x00BEu, 0x00ACu, 0x007Cu, 0x00AFu, 0x00A8u, 0x00B4u, 0x00D7u,
  0x007Bu, 0x0041u, 0x0042u, 0x0043u, 0x0044u, 0x0045u, 0x0046u, 0x0047u,
  0x0048u, 0x0049u, 0x00ADu, 0x00F4u, 0x00F6u, 0x00F2u, 0x00F3u, 0x00F5u,
  0x007Du, 0x004Au, 0x004Bu, 0x004Cu, 0x004Du, 0x004Eu, 0x004Fu, 0x0050u,
  0x0051u, 0x0052u, 0x00B9u, 0x00FBu, 0x00FCu, 0x00F9u, 0x00FAu, 0x00FFu,
  0x005Cu, 0x00F7u, 0x0053u, 0x0054u, 0x0055u, 0x0056u, 0x0057u, 0x0058u,
  0x0059u, 0x005Au, 0x00B2u, 0x00D4u, 0x00D6u, 0x00D2u, 0x00D3u, 0x00D5u,
  0x0030u, 0x0031u, 0x0032u, 0x0033u, 0x0034u, 0x0035u, 0x0036u, 0x0037u,
  0x0038u, 0x0039u, 0x00B3u, 0x00DBu, 0x00DCu, 0x00D9u, 0x00DAu, 0x009Fu,
};

// ->> IBM775 (cp775), 128 entries.
static unsigned short const unicode_IBM775[] = {
  0x0106u, 0x00FCu, 0x00E9u, 0x0101u, 0x00E4u, 0x0123u, 0x00E5u, 0x0107u,
  0x0142u, 0x0113u, 0x0156u, 0x0157u, 0x012Bu, 0x0179u, 0x00C4u, 0x00C5u,
  0x00C9u, 0x00E6u, 0x00C6u, 0x014Du, 0x00F6u, 0x0122u, 0x00A2u, 0x015Au,
  0x015Bu, 0x00D6u, 0x00DCu, 0x00F8u, 0x00A3u, 0x00D8u, 0x00D7u, 0x00A4u,
  0x0100u, 0x012Au, 0x00F3u, 0x017Bu, 0x017Cu, 0x017Au, 0x201Du, 0x00A6u,
  0x00A9u, 0x00AEu, 0x00ACu, 0x00BDu, 0x00BCu, 0x0141u, 0x00ABu, 0x00BBu,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x0104u, 0x010Cu, 0x0118u,
  0x0116u, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x012Eu, 0x0160u, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x0172u, 0x016Au,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x017Du,
  0x0105u, 0x010Du, 0x0119u, 0x0117u, 0x012Fu, 0x0161u, 0x0173u, 0x016Bu,
  0x017Eu, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x258Cu, 0x2590u, 0x2580u,
  0x00D3u, 0x00DFu, 0x014Cu, 0x0143u, 0x00F5u, 0x00D5u, 0x00B5u, 0x0144u,
  0x0136u, 0x0137u, 0x013Bu, 0x013Cu, 0x0146u, 0x0112u, 0x0145u, 0x2019u,
  0x00ADu, 0x00B1u, 0x201Cu, 0x00BEu, 0x00B6u, 0x00A7u, 0x00F7u, 0x201Eu,
  0x00B0u, 0x2219u, 0x00B7u, 0x00B9u, 0x00B3u, 0x00B2u, 0x25A0u, 0x00A0u,
};

// ->> IBM850 (cp850), 128 entries.
static unsigned short const unicode_IBM850[] = {
  0x00C7u, 0x00FCu, 0x00E9u, 0x00E2u, 0x00E4u, 0x00E0u, 0x00E5u, 0x00E7u,
  0x00EAu, 0x00EBu, 0x00E8u, 0x00EFu, 0x00EEu, 0x00ECu, 0x00C4u, 0x00C5u,
  0x00C9u, 0x00E6u, 0x00C6u, 0x00F4u, 0x00F6u, 0x00F2u, 0x00FBu, 0x00F9u,
  0x00FFu, 0x00D6u, 0x00DCu, 0x00F8u, 0x00A3u, 0x00D8u, 0x00D7u, 0x0192u,
  0x00E1u, 0x00EDu, 0x00F3u, 0x00FAu, 0x00F1u, 0x00D1u, 0x00AAu, 0x00BAu,
  0x00BFu, 0x00AEu, 0x00ACu, 0x00BDu, 0x00BCu, 0x00A1u, 0x00ABu, 0x00BBu,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x00C1u, 0x00C2u, 0x00C0u,
  0x00A9u, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x00A2u, 0x00A5u, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x00E3u, 0x00C3u,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x00A4u,
  0x00F0u, 0x00D0u, 0x00CAu, 0x00CBu, 0x00C8u, 0x0131u, 0x00CDu, 0x00CEu,
  0x00CFu, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x00A6u, 0x00CCu, 0x2580u,
  0x00D3u, 0x00DFu, 0x00D4u, 0x00D2u, 0x00F5u, 0x00D5u, 0x00B5u, 0x00FEu,
  0x00DEu, 0x00DAu, 0x00DBu, 0x00D9u, 0x00FDu, 0x00DDu, 0x00AFu, 0x00B4u,
  0x00ADu, 0x00B1u, 0x2017u, 0x00BEu, 0x00B6u, 0x00A7u, 0x00F7u, 0x00B8u,
  0x00B0u, 0x00A8u, 0x00B7u, 0x00B9u, 0x00B3u, 0x00B2u, 0x25A0u, 0x00A0u,
};

// ->> IBM852 (cp852), 128 entries.
static unsigned short const unicode_IBM852[] = {
  0x00C7u, 0x00FCu, 0x00E9u, 0x00E2u, 0x00E4u, 0x016Fu, 0x0107u, 0x00E7u,
  0x0142u, 0x00EBu, 0x0150u, 0x0151u, 0x00EEu, 0x0179u, 0x00C4u, 0x0106u,
  0x00C9u, 0x0139u, 0x013Au, 0x00F4u, 0x00F6u, 0x013Du, 0x013Eu, 0x015Au,
  0x015Bu, 0x00D6u, 0x00DCu, 0x0164u, 0x0165u, 0x0141u, 0x00D7u, 0x010Du,
  0x00E1u, 0x00EDu, 0x00F3u, 0x00FAu, 0x0104u, 0x0105u, 0x017Du, 0x017Eu,
  0x0118u, 0x0119u, 0x00ACu, 0x017Au, 0x010Cu, 0x015Fu, 0x00ABu, 0x00BBu,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x00C1u, 0x00C2u, 0x011Au,
  0x015Eu, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x017Bu, 0x017Cu, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x0102u, 0x0103u,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x00A4u,
  0x0111u, 0x0110u, 0x010Eu, 0x00CBu, 0x010Fu, 0x0147u, 0x00CDu, 0x00CEu,
  0x011Bu, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x0162u, 0x016Eu, 0x2580u,
  0x00D3u, 0x00DFu, 0x00D4u, 0x0143u, 0x0144u, 0x0148u, 0x0160u, 0x0161u,
  0x0154u, 0x00DAu, 0x0155u, 0x0170u, 0x00FDu, 0x00DDu, 0x0163u, 0x00B4u,
  0x00ADu, 0x02DDu, 0x02DBu, 0x02C7u, 0x02D8u, 0x00A7u, 0x00F7u, 0x00B8u,
  0x00B0u, 0x00A8u, 0x02D9u, 0x0171u, 0x0158u, 0x0159u, 0x25A0u, 0x00A0u,
};

// ->> IBM855 (cp855), 128 entries.
static unsigned short const unicode_IBM855[] = {
  0x0452u, 0x0402u, 0x0453u, 0x0403u, 0x0451u, 0x0401u, 0x0454u, 0x0404u,
  0x0455u, 0x0405u, 0x0456u, 0x0406u, 0x0457u, 0x0407u, 0x0458u, 0x0408u,
  0x0459u, 0x0409u, 0x045Au, 0x040Au, 0x045Bu, 0x040Bu, 0x045Cu, 0x040Cu,
  0x045Eu, 0x040Eu, 0x045Fu, 0x040Fu, 0x044Eu, 0x042Eu, 0x044Au, 0x042Au,
  0x0430u, 0x0410u, 0x0431u, 0x0411u, 0x0446u, 0x0426u, 0x0434u, 0x0414u,
  0x0435u, 0x0415u, 0x0444u, 0x0424u, 0x0433u, 0x0413u, 0x00ABu, 0x00BBu,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x0445u, 0x0425u, 0x0438u,
  0x0418u, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x0439u, 0x0419u, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x043Au, 0x041Au,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x00A4u,
  0x043Bu, 0x041Bu, 0x043Cu, 0x041Cu, 0x043Du, 0x041Du, 0x043Eu, 0x041Eu,
  0x043Fu, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x041Fu, 0x044Fu, 0x2580u,
  0x042Fu, 0x0440u, 0x0420u, 0x0441u, 0x0421u, 0x0442u, 0x0422u, 0x0443u,
  0x0423u, 0x0436u, 0x0416u, 0x0432u, 0x0412u, 0x044Cu, 0x042Cu, 0x2116u,
  0x00ADu, 0x044Bu, 0x042Bu, 0x0437u, 0x0417u, 0x0448u, 0x0428u, 0x044Du,
  0x042Du, 0x0449u, 0x0429u, 0x0447u, 0x0427u, 0x00A7u, 0x25A0u, 0x00A0u,
};

// ->> IBM857 (cp857), 128 entries.
static unsigned short const unicode_IBM857[] = {
  0x00C7u, 0x00FCu, 0x00E9u, 0x00E2u, 0x00E4u, 0x00E0u, 0x00E5u, 0x00E7u,
  0x00EAu, 0x00EBu, 0x00E8u, 0x00EFu, 0x00EEu, 0x0131u, 0x00C4u, 0x00C5u,
  0x00C9u, 0x00E6u, 0x00C6u, 0x00F4u, 0x00F6u, 0x00F2u, 0x00FBu, 0x00F9u,
  0x0130u, 0x00D6u, 0x00DCu, 0x00F8u, 0x00A3u, 0x00D8u, 0x015Eu, 0x015Fu,
  0x00E1u, 0x00EDu, 0x00F3u, 0x00FAu, 0x00F1u, 0x00D1u, 0x011Eu, 0x011Fu,
  0x00BFu, 0x00AEu, 0x00ACu, 0x00BDu, 0x00BCu, 0x00A1u, 0x00ABu, 0x00BBu,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x00C1u, 0x00C2u, 0x00C0u,
  0x00A9u, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x00A2u, 0x00A5u, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x00E3u, 0x00C3u,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x00A4u,
  0x00BAu, 0x00AAu, 0x00CAu, 0x00CBu, 0x00C8u, 0xFFFFu, 0x00CDu, 0x00CEu,
  0x00CFu, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x00A6u, 0x00CCu, 0x2580u,
  0x00D3u, 0x00DFu, 0x00D4u, 0x00D2u, 0x00F5u, 0x00D5u, 0x00B5u, 0xFFFFu,
  0x00D7u, 0x00DAu, 0x00DBu, 0x00D9u, 0x00ECu, 0x00FFu, 0x00AFu, 0x00B4u,
  0x00ADu, 0x00B1u, 0xFFFFu, 0x00BEu, 0x00B6u, 0x00A7u, 0x00F7u, 0x00B8u,
  0x00B0u, 0x00A8u, 0x00B7u, 0x00B9u, 0x00B3u, 0x00B2u, 0x25A0u, 0x00A0u,
};

// ->> IBM00858 (cp858), 128 entries.
static unsigned short const unicode_IBM00858[] = {
  0x00C7u, 0x00FCu, 0x00E9u, 0x00E2u, 0x00E4u, 0x00E0u, 0x00E5u, 0x00E7u,
  0x00EAu, 0x00EBu, 0x00E8u, 0x00EFu, 0x00EEu, 0x00ECu, 0x00C4u, 0x00C5u,
  0x00C9u, 0x00E6u, 0x00C6u, 0x00F4u, 0x00F6u, 0x00F2u, 0x00FBu, 0x00F9u,
  0x00FFu, 0x00D6u, 0x00DCu, 0x00F8u, 0x00A3u, 0x00D8u, 0x00D7u, 0x0192u,
  0x00E1u, 0x00EDu, 0x00F3u, 0x00FAu, 0x00F1u, 0x00D1u, 0x00AAu, 0x00BAu,
  0x00BFu, 0x00AEu, 0x00ACu, 0x00BDu, 0x00BCu, 0x00A1u, 0x00ABu, 0x00BBu,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x00C1u, 0x00C2u, 0x00C0u,
  0x00A9u, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x00A2u, 0x00A5u, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x00E3u, 0x00C3u,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x00A4u,
  0x00F0u, 0x00D0u, 0x00CAu, 0x00CBu, 0x00C8u, 0x20ACu, 0x00CDu, 0x00CEu,
  0x00CFu, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x00A6u, 0x00CCu, 0x2580u,
  0x00D3u, 0x00DFu, 0x00D4u, 0x00D2u, 0x00F5u, 0x00D5u, 0x00B5u, 0x00FEu,
  0x00DEu, 0x00DAu, 0x00DBu, 0x00D9u, 0x00FDu, 0x00DDu, 0x00AFu, 0x00B4u,
  0x00ADu, 0x00B1u, 0x2017u, 0x00BEu, 0x00B6u, 0x00A7u, 0x00F7u, 0x00B8u,
  0x00B0u, 0x00A8u, 0x00B7u, 0x00B9u, 0x00B3u, 0x00B2u, 0x25A0u, 0x00A0u,
};

// ->> IBM860 (cp860), 128 entries.
static unsigned short const unicode_IBM860[] = {
  0x00C7u, 0x00FCu, 0x00E9u, 0x00E2u, 0x00E3u, 0x00E0u, 0x00C1u, 0x00E7u,
  0x00EAu, 0x00CAu, 0x00E8u, 0x00CDu, 0x00D4u, 0x00ECu, 0x00C3u, 0x00C2u,
  0x00C9u, 0x00C0u, 0x00C8u, 0x00F4u, 0x00F5u, 0x00F2u, 0x00DAu, 0x00F9u,
  0x00CCu, 0x00D5u, 0x00DCu, 0x00A2u, 0x00A3u, 0x00D9u, 0x20A7u, 0x00D3u,
  0x00E1u, 0x00EDu, 0x00F3u, 0x00FAu, 0x00F1u, 0x00D1u, 0x00AAu, 0x00BAu,
  0x00BFu, 0x00D2u, 0x00ACu, 0x00BDu, 0x00BCu, 0x00A1u, 0x00ABu, 0x00BBu,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x2561u, 0x2562u, 0x2556u,
  0x2555u, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x255Cu, 0x255Bu, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x255Eu, 0x255Fu,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x2567u,
  0x2568u, 0x2564u, 0x2565u, 0x2559u, 0x2558u, 0x2552u, 0x2553u, 0x256Bu,
  0x256Au, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x258Cu, 0x2590u, 0x2580u,
  0x03B1u, 0x00DFu, 0x0393u, 0x03C0u, 0x03A3u, 0x03C3u, 0x00B5u, 0x03C4u,
  0x03A6u, 0x0398u, 0x03A9u, 0x03B4u, 0x221Eu, 0x03C6u, 0x03B5u, 0x2229u,
  0x2261u, 0x00B1u, 0x2265u, 0x2264u, 0x2320u, 0x2321u, 0x00F7u, 0x2248u,
  0x00B0u, 0x2219u, 0x00B7u, 0x221Au, 0x207Fu, 0x00B2u, 0x25A0u, 0x00A0u,
};

// ->> IBM861 (cp861), 128 entries.
static unsigned short const unicode_IBM861[] = {
  0x00C7u, 0x00FCu, 0x00E9u, 0x00E2u, 0x00E4u, 0x00E0u, 0x00E5u, 0x00E7u,
  0x00EAu, 0x00EBu, 0x00E8u, 0x00D0u, 0x00F0u, 0x00DEu, 0x00C4u, 0x00C5u,
  0x00C9u, 0x00E6u, 0x00C6u, 0x00F4u, 0x00F6u, 0x00FEu, 0x00FBu, 0x00DDu,
  0x00FDu, 0x00D6u, 0x00DCu, 0x00F8u, 0x00A3u, 0x00D8u, 0x20A7u, 0x0192u,
  0x00E1u, 0x00EDu, 0x00F3u, 0x00FAu, 0x00C1u, 0x00CDu, 0x00D3u, 0x00DAu,
  0x00BFu, 0x2310u, 0x00ACu, 0x00BDu, 0x00BCu, 0x00A1u, 0x00ABu, 0x00BBu,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x2561u, 0x2562u, 0x2556u,
  0x2555u, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x255Cu, 0x255Bu, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x255Eu, 0x255Fu,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x2567u,
  0x2568u, 0x2564u, 0x2565u, 0x2559u, 0x2558u, 0x2552u, 0x2553u, 0x256Bu,
  0x256Au, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x258Cu, 0x2590u, 0x2580u,
  0x03B1u, 0x00DFu, 0x0393u, 0x03C0u, 0x03A3u, 0x03C3u, 0x00B5u, 0x03C4u,
  0x03A6u, 0x0398u, 0x03A9u, 0x03B4u, 0x221Eu, 0x03C6u, 0x03B5u, 0x2229u,
  0x2261u, 0x00B1u, 0x2265u, 0x2264u, 0x2320u, 0x2321u, 0x00F7u, 0x2248u,
  0x00B0u, 0x2219u, 0x00B7u, 0x221Au, 0x207Fu, 0x00B2u, 0x25A0u, 0x00A0u,
};

// ->> IBM862 (cp862), 128 entries.
static unsigned short const unicode_IBM862[] = {
  0x05D0u, 0x05D1u, 0x05D2u, 0x05D3u, 0x05D4u, 0x05D5u, 0x05D6u, 0x05D7u,
  0x05D8u, 0x05D9u, 0x05DAu, 0x05DBu, 0x05DCu, 0x05DDu, 0x05DEu, 0x05DFu,
  0x05E0u, 0x05E1u, 0x05E2u, 0x05E3u, 0x05E4u, 0x05E5u, 0x05E6u, 0x05E7u,
  0x05E8u, 0x05E9u, 0x05EAu, 0x00A2u, 0x00A3u, 0x00A5u, 0x20A7u, 0x0192u,
  0x00E1u, 0x00EDu, 0x00F3u, 0x00FAu, 0x00F1u, 0x00D1u, 0x00AAu, 0x00BAu,
  0x00BFu, 0x2310u, 0x00ACu, 0x00BDu, 0x00BCu, 0x00A1u, 0x00ABu, 0x00BBu,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x2561u, 0x2562u, 0x2556u,
  0x2555u, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x255Cu, 0x255Bu, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x255Eu, 0x255Fu,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x2567u,
  0x2568u, 0x2564u, 0x2565u, 0x2559u, 0x2558u, 0x2552u, 0x2553u, 0x256Bu,
  0x256Au, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x258Cu, 0x2590u, 0x2580u,
  0x03B1u, 0x00DFu, 0x0393u, 0x03C0u, 0x03A3u, 0x03C3u, 0x00B5u, 0x03C4u,
  0x03A6u, 0x0398u, 0x03A9u, 0x03B4u, 0x221Eu, 0x03C6u, 0x03B5u, 0x2229u,
  0x2261u, 0x00B1u, 0x2265u, 0x2264u, 0x2320u, 0x2321u, 0x00F7u, 0x2248u,
  0x00B0u, 0x2219u, 0x00B7u, 0x221Au, 0x207Fu, 0x00B2u, 0x25A0u, 0x00A0u,
};

// ->> IBM863 (cp863), 128 entries.
static unsigned short const unicode_IBM863[] = {
  0x00C7u, 0x00FCu, 0x00E9u, 0x00E2u, 0x00C2u, 0x00E0u, 0x00B6u, 0x00E7u,
  0x00EAu, 0x00EBu, 0x00E8u, 0x00EFu, 0x00EEu, 0x2017u, 0x00C0u, 0x00A7u,
  0x00C9u, 0x00C8u, 0x00CAu, 0x00F4u, 0x00CBu, 0x00CFu, 0x00FBu, 0x00F9u,
  0x00A4u, 0x00D4u, 0x00DCu, 0x00A2u, 0x00A3u, 0x00D9u, 0x00DBu, 0x0192u,
  0x00A6u, 0x00B4u, 0x00F3u, 0x00FAu, 0x00A8u, 0x00B8u, 0x00B3u, 0x00AFu,
  0x00CEu, 0x2310u, 0x00ACu, 0x00BDu, 0x00BCu, 0x00BEu, 0x00ABu, 0x00BBu,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x2561u, 0x2562u, 0x2556u,
  0x2555u, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x255Cu, 0x255Bu, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x255Eu, 0x255Fu,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x2567u,
  0x2568u, 0x2564u, 0x2565u, 0x2559u, 0x2558u, 0x2552u, 0x2553u, 0x256Bu,
  0x256Au, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x258Cu, 0x2590u, 0x2580u,
  0x03B1u, 0x00DFu, 0x0393u, 0x03C0u, 0x03A3u, 0x03C3u, 0x00B5u, 0x03C4u,
  0x03A6u, 0x0398u, 0x03A9u, 0x03B4u, 0x221Eu, 0x03C6u, 0x03B5u, 0x2229u,
  0x2261u, 0x00B1u, 0x2265u, 0x2264u, 0x2320u, 0x2321u, 0x00F7u, 0x2248u,
  0x00B0u, 0x2219u, 0x00B7u, 0x221Au, 0x207Fu, 0x00B2u, 0x25A0u, 0x00A0u,
};

// ->> IBM864 (cp864), 256 entries.
static unsigned short const unicode_IBM864[] = {
  0x0000u, 0x0001u, 0x0002u, 0x0003u, 0x0004u, 0x0005u, 0x0006u, 0x0007u,
  0x0008u, 0x0009u, 0x000Au, 0x000Bu, 0x000Cu, 0x000Du, 0x000Eu, 0x000Fu,
  0x0010u, 0x0011u, 0x0012u, 0x0013u, 0x0014u, 0x0015u, 0x0016u, 0x0017u,
  0x0018u, 0x0019u, 0x001Au, 0x001Bu, 0x001Cu, 0x001Du, 0x001Eu, 0x001Fu,
  0x0020u, 0x0021u, 0x0022u, 0x0023u, 0x0024u, 0x066Au, 0x0026u, 0x0027u,
  0x0028u, 0x0029u, 0x002Au, 0x002Bu, 0x002Cu, 0x002Du, 0x002Eu, 0x002Fu,
  0x0030u, 0x0031u, 0x0032u, 0x0033u, 0x0034u, 0x0035u, 0x0036u, 0x0037u,
  0x0038u, 0x0039u, 0x003Au, 0x003Bu, 0x003Cu, 0x003Du, 0x003Eu, 0x003Fu,
  0x0040u, 0x0041u, 0x0042u, 0x0043u, 0x0044u, 0x0045u, 0x0046u, 0x0047u,
  0x0048u, 0x0049u, 0x004Au, 0x004Bu, 0x004Cu, 0x004Du, 0x004Eu, 0x004Fu,
  0x0050u, 0x0051u, 0x0052u, 0x0053u, 0x0054u, 0x0055u, 0x0056u, 0x0057u,
  0x0058u, 0x0059u, 0x005Au, 0x005Bu, 0x005Cu, 0x005Du, 0x005Eu, 0x005Fu,
  0x0060u, 0x0061u, 0x0062u, 0x0063u, 0x0064u, 0x0065u, 0x0066u, 0x0067u,
  0x0068u, 0x0069u, 0x006Au, 0x006Bu, 0x006Cu, 0x006Du, 0x006Eu, 0x006Fu,
  0x0070u, 0x0071u, 0x0072u, 0x0073u, 0x0074u, 0x0075u, 0x0076u, 0x0077u,
  0x0078u, 0x0079u, 0x007Au, 0x007Bu, 0x007Cu, 0x007Du, 0x007Eu, 0x007Fu,
  0x00B0u, 0x00B7u, 0x2219u, 0x221Au, 0x2592u, 0x2500u, 0x2502u, 0x253Cu,
  0x2524u, 0x252Cu, 0x251Cu, 0x2534u, 0x2510u, 0x250Cu, 0x2514u, 0x2518u,
  0x03B2u, 0x221Eu, 0x03C6u, 0x00B1u, 0x00BDu, 0x00BCu, 0x2248u, 0x00ABu,
  0x00BBu, 0xFEF7u, 0xFEF8u, 0xFFFFu, 0xFFFFu, 0xFEFBu, 0xFEFCu, 0xFFFFu,
  0x00A0u, 0x00ADu, 0xFE82u, 0x00A3u, 0x00A4u, 0xFE84u, 0xFFFFu, 0xFFFFu,
  0xFE8Eu, 0xFE8Fu, 0xFE95u, 0xFE99u, 0x060Cu, 0xFE9Du, 0xFEA1u, 0xFEA5u,
  0x0660u, 0x0661u, 0x0662u, 0x0663u, 0x0664u, 0x0665u, 0x0666u, 0x0667u,
  0x0668u, 0x0669u, 0xFED1u, 0x061Bu, 0xFEB1u, 0xFEB5u, 0xFEB9u, 0x061Fu,
  0x00A2u, 0xFE80u, 0xFE81u, 0xFE83u, 0xFE85u, 0xFECAu, 0xFE8Bu, 0xFE8Du,
  0xFE91u, 0xFE93u, 0xFE97u, 0xFE9Bu, 0xFE9Fu, 0xFEA3u, 0xFEA7u, 0xFEA9u,
  0xFEABu, 0xFEADu, 0xFEAFu, 0xFEB3u, 0xFEB7u, 0xFEBBu, 0xFEBFu, 0xFEC1u,
  0xFEC5u, 0xFECBu, 0xFECFu, 0x00A6u, 0x00ACu, 0x00F7u, 0x00D7u, 0xFEC9u,
  0x0640u, 0xFED3u, 0xFED7u, 0xFEDBu, 0xFEDFu, 0xFEE3u, 0xFEE7u, 0xFEEBu,
  0xFEEDu, 0xFEEFu, 0xFEF3u, 0xFEBDu, 0xFECCu, 0xFECEu, 0xFECDu, 0xFEE1u,
  0xFE7Du, 0x0651u, 0xFEE5u, 0xFEE9u, 0xFEECu, 0xFEF0u, 0xFEF2u, 0xFED0u,
  0xFED5u, 0xFEF5u, 0xFEF6u, 0xFEDDu, 0xFED9u, 0xFEF1u, 0x25A0u, 0xFFFFu,
};

// ->> IBM865 (cp865), 128 entries.
static unsigned short const unicode_IBM865[] = {
  0x00C7u, 0x00FCu, 0x00E9u, 0x00E2u, 0x00E4u, 0x00E0u, 0x00E5u, 0x00E7u,
  0x00EAu, 0x00EBu, 0x00E8u, 0x00EFu, 0x00EEu, 0x00ECu, 0x00C4u, 0x00C5u,
  0x00C9u, 0x00E6u, 0x00C6u, 0x00F4u, 0x00F6u, 0x00F2u, 0x00FBu, 0x00F9u,
  0x00FFu, 0x00D6u, 0x00DCu, 0x00F8u, 0x00A3u, 0x00D8u, 0x20A7u, 0x0192u,
  0x00E1u, 0x00EDu, 0x00F3u, 0x00FAu, 0x00F1u, 0x00D1u, 0x00AAu, 0x00BAu,
  0x00BFu, 0x2310u, 0x00ACu, 0x00BDu, 0x00BCu, 0x00A1u, 0x00ABu, 0x00A4u,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x2561u, 0x2562u, 0x2556u,
  0x2555u, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x255Cu, 0x255Bu, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x255Eu, 0x255Fu,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x2567u,
  0x2568u, 0x2564u, 0x2565u, 0x2559u, 0x2558u, 0x2552u, 0x2553u, 0x256Bu,
  0x256Au, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x258Cu, 0x2590u, 0x2580u,
  0x03B1u, 0x00DFu, 0x0393u, 0x03C0u, 0x03A3u, 0x03C3u, 0x00B5u, 0x03C4u,
  0x03A6u, 0x0398u, 0x03A9u, 0x03B4u, 0x221Eu, 0x03C6u, 0x03B5u, 0x2229u,
  0x2261u, 0x00B1u, 0x2265u, 0x2264u, 0x2320u, 0x2321u, 0x00F7u, 0x2248u,
  0x00B0u, 0x2219u, 0x00B7u, 0x221Au, 0x207Fu, 0x00B2u, 0x25A0u, 0x00A0u,
};

// ->> IBM866 (cp866), 128 entries.
static unsigned short const unicode_IBM866[] = {
  0x0410u, 0x0411u, 0x0412u, 0x0413u, 0x0414u, 0x0415u, 0x0416u, 0x0417u,
  0x0418u, 0x0419u, 0x041Au, 0x041Bu, 0x041Cu, 0x041Du, 0x041Eu, 0x041Fu,
  0x0420u, 0x0421u, 0x0422u, 0x0423u, 0x0424u, 0x0425u, 0x0426u, 0x0427u,
  0x0428u, 0x0429u, 0x042Au, 0x042Bu, 0x042Cu, 0x042Du, 0x042Eu, 0x042Fu,
  0x0430u, 0x0431u, 0x0432u, 0x0433u, 0x0434u, 0x0435u, 0x0436u, 0x0437u,
  0x0438u, 0x0439u, 0x043Au, 0x043Bu, 0x043Cu, 0x043Du, 0x043Eu, 0x043Fu,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x2561u, 0x2562u, 0x2556u,
  0x2555u, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x255Cu, 0x255Bu, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x255Eu, 0x255Fu,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x2567u,
  0x2568u, 0x2564u, 0x2565u, 0x2559u, 0x2558u, 0x2552u, 0x2553u, 0x256Bu,
  0x256Au, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x258Cu, 0x2590u, 0x2580u,
  0x0440u, 0x0441u, 0x0442u, 0x0443u, 0x0444u, 0x0445u, 0x0446u, 0x0447u,
  0x0448u, 0x0449u, 0x044Au, 0x044Bu, 0x044Cu, 0x044Du, 0x044Eu, 0x044Fu,
  0x0401u, 0x0451u, 0x0404u, 0x0454u, 0x0407u, 0x0457u, 0x040Eu, 0x045Eu,
  0x00B0u, 0x2219u, 0x00B7u, 0x221Au, 0x2116u, 0x00A4u, 0x25A0u, 0x00A0u,
};

// ->> IBM869 (cp869), 128 entries.
static unsigned short const unicode_IBM869[] = {
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x0386u, 0xFFFFu,
  0x00B7u, 0x00ACu, 0x00A6u, 0x2018u, 0x2019u, 0x0388u, 0x2015u, 0x0389u,
  0x038Au, 0x03AAu, 0x038Cu, 0xFFFFu, 0xFFFFu, 0x038Eu, 0x03ABu, 0x00A9u,
  0x038Fu, 0x00B2u, 0x00B3u, 0x03ACu, 0x00A3u, 0x03ADu, 0x03AEu, 0x03AFu,
  0x03CAu, 0x0390u, 0x03CCu, 0x03CDu, 0x0391u, 0x0392u, 0x0393u, 0x0394u,
  0x0395u, 0x0396u, 0x0397u, 0x00BDu, 0x0398u, 0x0399u, 0x00ABu, 0x00BBu,
  0x2591u, 0x2592u, 0x2593u, 0x2502u, 0x2524u, 0x039Au, 0x039Bu, 0x039Cu,
  0x039Du, 0x2563u, 0x2551u, 0x2557u, 0x255Du, 0x039Eu, 0x039Fu, 0x2510u,
  0x2514u, 0x2534u, 0x252Cu, 0x251Cu, 0x2500u, 0x253Cu, 0x03A0u, 0x03A1u,
  0x255Au, 0x2554u, 0x2569u, 0x2566u, 0x2560u, 0x2550u, 0x256Cu, 0x03A3u,
  0x03A4u, 0x03A5u, 0x03A6u, 0x03A7u, 0x03A8u, 0x03A9u, 0x03B1u, 0x03B2u,
  0x03B3u, 0x2518u, 0x250Cu, 0x2588u, 0x2584u, 0x03B4u, 0x03B5u, 0x2580u,
  0x03B6u, 0x03B7u, 0x03B8u, 0x03B9u, 0x03BAu, 0x03BBu, 0x03BCu, 0x03BDu,
  0x03BEu, 0x03BFu, 0x03C0u, 0x03C1u, 0x03C3u, 0x03C2u, 0x03C4u, 0x0384u,
  0x00ADu, 0x00B1u, 0x03C5u, 0x03C6u, 0x03C7u, 0x00A7u, 0x03C8u, 0x0385u,
  0x00B0u, 0x00A8u, 0x03C9u, 0x03CBu, 0x03B0u, 0x03CEu, 0x25A0u, 0x00A0u,
};

// ->> IBM1026 (cp1026), 256 entries.
static unsigned short const unicode_IBM1026[] = {
  0x0000u, 0x0001u, 0x0002u, 0x0003u, 0x009Cu, 0x0009u, 0x0086u, 0x007Fu,
  0x0097u, 0x008Du, 0x008Eu, 0x000Bu, 0x000Cu, 0x000Du, 0x000Eu, 0x000Fu,
  0x0010u, 0x0011u, 0x0012u, 0x0013u, 0x009Du, 0x0085u, 0x0008u, 0x0087u,
  0x0018u, 0x0019u, 0x0092u, 0x008Fu, 0x001Cu, 0x001Du, 0x001Eu, 0x001Fu,
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x000Au, 0x0017u, 0x001Bu,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x0005u, 0x0006u, 0x0007u,
  0x0090u, 0x0091u, 0x0016u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0004u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x0014u, 0x0015u, 0x009Eu, 0x001Au,
  0x0020u, 0x00A0u, 0x00E2u, 0x00E4u, 0x00E0u, 0x00E1u, 0x00E3u, 0x00E5u,
  0x007Bu, 0x00F1u, 0x00C7u, 0x002Eu, 0x003Cu, 0x0028u, 0x002Bu, 0x0021u,
  0x0026u, 0x00E9u, 0x00EAu, 0x00EBu, 0x00E8u, 0x00EDu, 0x00EEu, 0x00EFu,
  0x00ECu, 0x00DFu, 0x011Eu, 0x0130u, 0x002Au, 0x0029u, 0x003Bu, 0x005Eu,
  0x002Du, 0x002Fu, 0x00C2u, 0x00C4u, 0x00C0u, 0x00C1u, 0x00C3u, 0x00C5u,
  0x005Bu, 0x00D1u, 0x015Fu, 0x002Cu, 0x0025u, 0x005Fu, 0x003Eu, 0x003Fu,
  0x00F8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x00C8u, 0x00CDu, 0x00CEu, 0x00CFu,
  0x00CCu, 0x0131u, 0x003Au, 0x00D6u, 0x015Eu, 0x0027u, 0x003Du, 0x00DCu,
  0x00D8u, 0x0061u, 0x0062u, 0x0063u, 0x0064u, 0x0065u, 0x0066u, 0x0067u,
  0x0068u, 0x0069u, 0x00ABu, 0x00BBu, 0x007Du, 0x0060u, 0x00A6u, 0x00B1u,
  0x00B0u, 0x006Au, 0x006Bu, 0x006Cu, 0x006Du, 0x006Eu, 0x006Fu, 0x0070u,
  0x0071u, 0x0072u, 0x00AAu, 0x00BAu, 0x00E6u, 0x00B8u, 0x00C6u, 0x00A4u,
  0x00B5u, 0x00F6u, 0x0073u, 0x0074u, 0x0075u, 0x0076u, 0x0077u, 0x0078u,
  0x0079u, 0x007Au, 0x00A1u, 0x00BFu, 0x005Du, 0x0024u, 0x0040u, 0x00AEu,
  0x00A2u, 0x00A3u, 0x00A5u, 0x00B7u, 0x00A9u, 0x00A7u, 0x00B6u, 0x00BCu,
  0x00BDu, 0x00BEu, 0x00ACu, 0x007Cu, 0x00AFu, 0x00A8u, 0x00B4u, 0x00D7u,
  0x00E7u, 0x0041u, 0x0042u, 0x0043u, 0x0044u, 0x0045u, 0x0046u, 0x0047u,
  0x0048u, 0x0049u, 0x00ADu, 0x00F4u, 0x007Eu, 0x00F2u, 0x00F3u, 0x00F5u,
  0x011Fu, 0x004Au, 0x004Bu, 0x004Cu, 0x004Du, 0x004Eu, 0x004Fu, 0x0050u,
  0x0051u, 0x0052u, 0x00B9u, 0x00FBu, 0x005Cu, 0x00F9u, 0x00FAu, 0x00FFu,
  0x00FCu, 0x00F7u, 0x0053u, 0x0054u, 0x0055u, 0x0056u, 0x0057u, 0x0058u,
  0x0059u, 0x005Au, 0x00B2u, 0x00D4u, 0x0023u, 0x00D2u, 0x00D3u, 0x00D5u,
  0x0030u, 0x0031u, 0x0032u, 0x0033u, 0x0034u, 0x0035u, 0x0036u, 0x0037u,
  0x0038u, 0x0039u, 0x00B3u, 0x00DBu, 0x0022u, 0x00D9u, 0x00DAu, 0x009Fu,
};

// ->> IBM01140 (cp1140), 256 entries.
static unsigned short const unicode_IBM01140[] = {
  0x0000u, 0x0001u, 0x0002u, 0x0003u, 0x009Cu, 0x0009u, 0x0086u, 0x007Fu,
  0x0097u, 0x008Du, 0x008Eu, 0x000Bu, 0x000Cu, 0x000Du, 0x000Eu, 0x000Fu,
  0x0010u, 0x0011u, 0x0012u, 0x0013u, 0x009Du, 0x0085u, 0x0008u, 0x0087u,
  0x0018u, 0x0019u, 0x0092u, 0x008Fu, 0x001Cu, 0x001Du, 0x001Eu, 0x001Fu,
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x000Au, 0x0017u, 0x001Bu,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x0005u, 0x0006u, 0x0007u,
  0x0090u, 0x0091u, 0x0016u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0004u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x0014u, 0x0015u, 0x009Eu, 0x001Au,
  0x0020u, 0x00A0u, 0x00E2u, 0x00E4u, 0x00E0u, 0x00E1u, 0x00E3u, 0x00E5u,
  0x00E7u, 0x00F1u, 0x00A2u, 0x002Eu, 0x003Cu, 0x0028u, 0x002Bu, 0x007Cu,
  0x0026u, 0x00E9u, 0x00EAu, 0x00EBu, 0x00E8u, 0x00EDu, 0x00EEu, 0x00EFu,
  0x00ECu, 0x00DFu, 0x0021u, 0x0024u, 0x002Au, 0x0029u, 0x003Bu, 0x00ACu,
  0x002Du, 0x002Fu, 0x00C2u, 0x00C4u, 0x00C0u, 0x00C1u, 0x00C3u, 0x00C5u,
  0x00C7u, 0x00D1u, 0x00A6u, 0x002Cu, 0x0025u, 0x005Fu, 0x003Eu, 0x003Fu,
  0x00F8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x00C8u, 0x00CDu, 0x00CEu, 0x00CFu,
  0x00CCu, 0x0060u, 0x003Au, 0x0023u, 0x0040u, 0x0027u, 0x003Du, 0x0022u,
  0x00D8u, 0x0061u, 0x0062u, 0x0063u, 0x0064u, 0x0065u, 0x0066u, 0x0067u,
  0x0068u, 0x0069u, 0x00ABu, 0x00BBu, 0x00F0u, 0x00FDu, 0x00FEu, 0x00B1u,
  0x00B0u, 0x006Au, 0x006Bu, 0x006Cu, 0x006Du, 0x006Eu, 0x006Fu, 0x0070u,
  0x0071u, 0x0072u, 0x00AAu, 0x00BAu, 0x00E6u, 0x00B8u, 0x00C6u, 0x20ACu,
  0x00B5u, 0x007Eu, 0x0073u, 0x0074u, 0x0075u, 0x0076u, 0x0077u, 0x0078u,
  0x0079u, 0x007Au, 0x00A1u, 0x00BFu, 0x00D0u, 0x00DDu, 0x00DEu, 0x00AEu,
  0x005Eu, 0x00A3u, 0x00A5u, 0x00B7u, 0x00A9u, 0x00A7u, 0x00B6u, 0x00BCu,
  0x00BDu, 0x00BEu, 0x005Bu, 0x005Du, 0x00AFu, 0x00A8u, 0x00B4u, 0x00D7u,
  0x007Bu, 0x0041u, 0x0042u, 0x0043u, 0x0044u, 0x0045u, 0x0046u, 0x0047u,
  0x0048u, 0x0049u, 0x00ADu, 0x00F4u, 0x00F6u, 0x00F2u, 0x00F3u, 0x00F5u,
  0x007Du, 0x004Au, 0x004Bu, 0x004Cu, 0x004Du, 0x004Eu, 0x004Fu, 0x0050u,
  0x0051u, 0x0052u, 0x00B9u, 0x00FBu, 0x00FCu, 0x00F9u, 0x00FAu, 0x00FFu,
  0x005Cu, 0x00F7u, 0x0053u, 0x0054u, 0x0055u, 0x0056u, 0x0057u, 0x0058u,
  0x0059u, 0x005Au, 0x00B2u, 0x00D4u, 0x00D6u, 0x00D2u, 0x00D3u, 0x00D5u,
  0x0030u, 0x0031u, 0x0032u, 0x0033u, 0x0034u, 0x0035u, 0x0036u, 0x0037u,
  0x0038u, 0x0039u, 0x00B3u, 0x00DBu, 0x00DCu, 0x00D9u, 0x00DAu, 0x009Fu,
};

// ->> ISO_8859_1_1987 (iso8859-1), 128 entries.
static unsigned short const unicode_ISO_8859_1_1987[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x00A1u, 0x00A2u, 0x00A3u, 0x00A4u, 0x00A5u, 0x00A6u, 0x00A7u,
  0x00A8u, 0x00A9u, 0x00AAu, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x00AFu,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x00B4u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x00B8u, 0x00B9u, 0x00BAu, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0x00BFu,
  0x00C0u, 0x00C1u, 0x00C2u, 0x00C3u, 0x00C4u, 0x00C5u, 0x00C6u, 0x00C7u,
  0x00C8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x00CCu, 0x00CDu, 0x00CEu, 0x00CFu,
  0x00D0u, 0x00D1u, 0x00D2u, 0x00D3u, 0x00D4u, 0x00D5u, 0x00D6u, 0x00D7u,
  0x00D8u, 0x00D9u, 0x00DAu, 0x00DBu, 0x00DCu, 0x00DDu, 0x00DEu, 0x00DFu,
  0x00E0u, 0x00E1u, 0x00E2u, 0x00E3u, 0x00E4u, 0x00E5u, 0x00E6u, 0x00E7u,
  0x00E8u, 0x00E9u, 0x00EAu, 0x00EBu, 0x00ECu, 0x00EDu, 0x00EEu, 0x00EFu,
  0x00F0u, 0x00F1u, 0x00F2u, 0x00F3u, 0x00F4u, 0x00F5u, 0x00F6u, 0x00F7u,
  0x00F8u, 0x00F9u, 0x00FAu, 0x00FBu, 0x00FCu, 0x00FDu, 0x00FEu, 0x00FFu,
};

// ->> ISO_8859_2_1987 (iso8859-2), 128 entries.
static unsigned short const unicode_ISO_8859_2_1987[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x0104u, 0x02D8u, 0x0141u, 0x00A4u, 0x013Du, 0x015Au, 0x00A7u,
  0x00A8u, 0x0160u, 0x015Eu, 0x0164u, 0x0179u, 0x00ADu, 0x017Du, 0x017Bu,
  0x00B0u, 0x0105u, 0x02DBu, 0x0142u, 0x00B4u, 0x013Eu, 0x015Bu, 0x02C7u,
  0x00B8u, 0x0161u, 0x015Fu, 0x0165u, 0x017Au, 0x02DDu, 0x017Eu, 0x017Cu,
  0x0154u, 0x00C1u, 0x00C2u, 0x0102u, 0x00C4u, 0x0139u, 0x0106u, 0x00C7u,
  0x010Cu, 0x00C9u, 0x0118u, 0x00CBu, 0x011Au, 0x00CDu, 0x00CEu, 0x010Eu,
  0x0110u, 0x0143u, 0x0147u, 0x00D3u, 0x00D4u, 0x0150u, 0x00D6u, 0x00D7u,
  0x0158u, 0x016Eu, 0x00DAu, 0x0170u, 0x00DCu, 0x00DDu, 0x0162u, 0x00DFu,
  0x0155u, 0x00E1u, 0x00E2u, 0x0103u, 0x00E4u, 0x013Au, 0x0107u, 0x00E7u,
  0x010Du, 0x00E9u, 0x0119u, 0x00EBu, 0x011Bu, 0x00EDu, 0x00EEu, 0x010Fu,
  0x0111u, 0x0144u, 0x0148u, 0x00F3u, 0x00F4u, 0x0151u, 0x00F6u, 0x00F7u,
  0x0159u, 0x016Fu, 0x00FAu, 0x0171u, 0x00FCu, 0x00FDu, 0x0163u, 0x02D9u,
};

// ->> ISO_8859_3_1988 (iso8859-3), 128 entries.
static unsigned short const unicode_ISO_8859_3_1988[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x0126u, 0x02D8u, 0x00A3u, 0x00A4u, 0xFFFFu, 0x0124u, 0x00A7u,
  0x00A8u, 0x0130u, 0x015Eu, 0x011Eu, 0x0134u, 0x00ADu, 0xFFFFu, 0x017Bu,
  0x00B0u, 0x0127u, 0x00B2u, 0x00B3u, 0x00B4u, 0x00B5u, 0x0125u, 0x00B7u,
  0x00B8u, 0x0131u, 0x015Fu, 0x011Fu, 0x0135u, 0x00BDu, 0xFFFFu, 0x017Cu,
  0x00C0u, 0x00C1u, 0x00C2u, 0xFFFFu, 0x00C4u, 0x010Au, 0x0108u, 0x00C7u,
  0x00C8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x00CCu, 0x00CDu, 0x00CEu, 0x00CFu,
  0xFFFFu, 0x00D1u, 0x00D2u, 0x00D3u, 0x00D4u, 0x0120u, 0x00D6u, 0x00D7u,
  0x011Cu, 0x00D9u, 0x00DAu, 0x00DBu, 0x00DCu, 0x016Cu, 0x015Cu, 0x00DFu,
  0x00E0u, 0x00E1u, 0x00E2u, 0xFFFFu, 0x00E4u, 0x010Bu, 0x0109u, 0x00E7u,
  0x00E8u, 0x00E9u, 0x00EAu, 0x00EBu, 0x00ECu, 0x00EDu, 0x00EEu, 0x00EFu,
  0xFFFFu, 0x00F1u, 0x00F2u, 0x00F3u, 0x00F4u, 0x0121u, 0x00F6u, 0x00F7u,
  0x011Du, 0x00F9u, 0x00FAu, 0x00FBu, 0x00FCu, 0x016Du, 0x015Du, 0x02D9u,
};

// ->> ISO_8859_4_1988 (iso8859-4), 128 entries.
static unsigned short const unicode_ISO_8859_4_1988[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x0104u, 0x0138u, 0x0156u, 0x00A4u, 0x0128u, 0x013Bu, 0x00A7u,
  0x00A8u, 0x0160u, 0x0112u, 0x0122u, 0x0166u, 0x00ADu, 0x017Du, 0x00AFu,
  0x00B0u, 0x0105u, 0x02DBu, 0x0157u, 0x00B4u, 0x0129u, 0x013Cu, 0x02C7u,
  0x00B8u, 0x0161u, 0x0113u, 0x0123u, 0x0167u, 0x014Au, 0x017Eu, 0x014Bu,
  0x0100u, 0x00C1u, 0x00C2u, 0x00C3u, 0x00C4u, 0x00C5u, 0x00C6u, 0x012Eu,
  0x010Cu, 0x00C9u, 0x0118u, 0x00CBu, 0x0116u, 0x00CDu, 0x00CEu, 0x012Au,
  0x0110u, 0x0145u, 0x014Cu, 0x0136u, 0x00D4u, 0x00D5u, 0x00D6u, 0x00D7u,
  0x00D8u, 0x0172u, 0x00DAu, 0x00DBu, 0x00DCu, 0x0168u, 0x016Au, 0x00DFu,
  0x0101u, 0x00E1u, 0x00E2u, 0x00E3u, 0x00E4u, 0x00E5u, 0x00E6u, 0x012Fu,
  0x010Du, 0x00E9u, 0x0119u, 0x00EBu, 0x0117u, 0x00EDu, 0x00EEu, 0x012Bu,
  0x0111u, 0x0146u, 0x014Du, 0x0137u, 0x00F4u, 0x00F5u, 0x00F6u, 0x00F7u,
  0x00F8u, 0x0173u, 0x00FAu, 0x00FBu, 0x00FCu, 0x0169u, 0x016Bu, 0x02D9u,
};

// ->> ISO_8859_5_1988 (iso8859-5), 128 entries.
static unsigned short const unicode_ISO_8859_5_1988[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x0401u, 0x0402u, 0x0403u, 0x0404u, 0x0405u, 0x0406u, 0x0407u,
  0x0408u, 0x0409u, 0x040Au, 0x040Bu, 0x040Cu, 0x00ADu, 0x040Eu, 0x040Fu,
  0x0410u, 0x0411u, 0x0412u, 0x0413u, 0x0414u, 0x0415u, 0x0416u, 0x0417u,
  0x0418u, 0x0419u, 0x041Au, 0x041Bu, 0x041Cu, 0x041Du, 0x041Eu, 0x041Fu,
  0x0420u, 0x0421u, 0x0422u, 0x0423u, 0x0424u, 0x0425u, 0x0426u, 0x0427u,
  0x0428u, 0x0429u, 0x042Au, 0x042Bu, 0x042Cu, 0x042Du, 0x042Eu, 0x042Fu,
  0x0430u, 0x0431u, 0x0432u, 0x0433u, 0x0434u, 0x0435u, 0x0436u, 0x0437u,
  0x0438u, 0x0439u, 0x043Au, 0x043Bu, 0x043Cu, 0x043Du, 0x043Eu, 0x043Fu,
  0x0440u, 0x0441u, 0x0442u, 0x0443u, 0x0444u, 0x0445u, 0x0446u, 0x0447u,
  0x0448u, 0x0449u, 0x044Au, 0x044Bu, 0x044Cu, 0x044Du, 0x044Eu, 0x044Fu,
  0x2116u, 0x0451u, 0x0452u, 0x0453u, 0x0454u, 0x0455u, 0x0456u, 0x0457u,
  0x0458u, 0x0459u, 0x045Au, 0x045Bu, 0x045Cu, 0x00A7u, 0x045Eu, 0x045Fu,
};

// ->> ISO_8859_6_1987 (iso8859-6), 128 entries.
static unsigned short const unicode_ISO_8859_6_1987[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x00A4u, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x060Cu, 0x00ADu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0x061Bu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x061Fu,
  0xFFFFu, 0x0621u, 0x0622u, 0x0623u, 0x0624u, 0x0625u, 0x0626u, 0x0627u,
  0x0628u, 0x0629u, 0x062Au, 0x062Bu, 0x062Cu, 0x062Du, 0x062Eu, 0x062Fu,
  0x0630u, 0x0631u, 0x0632u, 0x0633u, 0x0634u, 0x0635u, 0x0636u, 0x0637u,
  0x0638u, 0x0639u, 0x063Au, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0x0640u, 0x0641u, 0x0642u, 0x0643u, 0x0644u, 0x0645u, 0x0646u, 0x0647u,
  0x0648u, 0x0649u, 0x064Au, 0x064Bu, 0x064Cu, 0x064Du, 0x064Eu, 0x064Fu,
  0x0650u, 0x0651u, 0x0652u, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
};

// ->> ISO_8859_6_E (iso8859-6), 128 entries.
static unsigned short const unicode_ISO_8859_6_E[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x00A4u, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x060Cu, 0x00ADu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0x061Bu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x061Fu,
  0xFFFFu, 0x0621u, 0x0622u, 0x0623u, 0x0624u, 0x0625u, 0x0626u, 0x0627u,
  0x0628u, 0x0629u, 0x062Au, 0x062Bu, 0x062Cu, 0x062Du, 0x062Eu, 0x062Fu,
  0x0630u, 0x0631u, 0x0632u, 0x0633u, 0x0634u, 0x0635u, 0x0636u, 0x0637u,
  0x0638u, 0x0639u, 0x063Au, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0x0640u, 0x0641u, 0x0642u, 0x0643u, 0x0644u, 0x0645u, 0x0646u, 0x0647u,
  0x0648u, 0x0649u, 0x064Au, 0x064Bu, 0x064Cu, 0x064Du, 0x064Eu, 0x064Fu,
  0x0650u, 0x0651u, 0x0652u, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
};

// ->> ISO_8859_6_I (iso8859-6), 128 entries.
static unsigned short const unicode_ISO_8859_6_I[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x00A4u, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x060Cu, 0x00ADu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0x061Bu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x061Fu,
  0xFFFFu, 0x0621u, 0x0622u, 0x0623u, 0x0624u, 0x0625u, 0x0626u, 0x0627u,
  0x0628u, 0x0629u, 0x062Au, 0x062Bu, 0x062Cu, 0x062Du, 0x062Eu, 0x062Fu,
  0x0630u, 0x0631u, 0x0632u, 0x0633u, 0x0634u, 0x0635u, 0x0636u, 0x0637u,
  0x0638u, 0x0639u, 0x063Au, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0x0640u, 0x0641u, 0x0642u, 0x0643u, 0x0644u, 0x0645u, 0x0646u, 0x0647u,
  0x0648u, 0x0649u, 0x064Au, 0x064Bu, 0x064Cu, 0x064Du, 0x064Eu, 0x064Fu,
  0x0650u, 0x0651u, 0x0652u, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
};

// ->> ISO_8859_7_1987 (iso8859-7), 128 entries.
static unsigned short const unicode_ISO_8859_7_1987[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x2018u, 0x2019u, 0x00A3u, 0x20ACu, 0x20AFu, 0x00A6u, 0x00A7u,
  0x00A8u, 0x00A9u, 0x037Au, 0x00ABu, 0x00ACu, 0x00ADu, 0xFFFFu, 0x2015u,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x0384u, 0x0385u, 0x0386u, 0x00B7u,
  0x0388u, 0x0389u, 0x038Au, 0x00BBu, 0x038Cu, 0x00BDu, 0x038Eu, 0x038Fu,
  0x0390u, 0x0391u, 0x0392u, 0x0393u, 0x0394u, 0x0395u, 0x0396u, 0x0397u,
  0x0398u, 0x0399u, 0x039Au, 0x039Bu, 0x039Cu, 0x039Du, 0x039Eu, 0x039Fu,
  0x03A0u, 0x03A1u, 0xFFFFu, 0x03A3u, 0x03A4u, 0x03A5u, 0x03A6u, 0x03A7u,
  0x03A8u, 0x03A9u, 0x03AAu, 0x03ABu, 0x03ACu, 0x03ADu, 0x03AEu, 0x03AFu,
  0x03B0u, 0x03B1u, 0x03B2u, 0x03B3u, 0x03B4u, 0x03B5u, 0x03B6u, 0x03B7u,
  0x03B8u, 0x03B9u, 0x03BAu, 0x03BBu, 0x03BCu, 0x03BDu, 0x03BEu, 0x03BFu,
  0x03C0u, 0x03C1u, 0x03C2u, 0x03C3u, 0x03C4u, 0x03C5u, 0x03C6u, 0x03C7u,
  0x03C8u, 0x03C9u, 0x03CAu, 0x03CBu, 0x03CCu, 0x03CDu, 0x03CEu, 0xFFFFu,
};

// ->> ISO_8859_8_1988 (iso8859-8), 128 entries.
static unsigned short const unicode_ISO_8859_8_1988[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0xFFFFu, 0x00A2u, 0x00A3u, 0x00A4u, 0x00A5u, 0x00A6u, 0x00A7u,
  0x00A8u, 0x00A9u, 0x00D7u, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x00AFu,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x00B4u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x00B8u, 0x00B9u, 0x00F7u, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x2017u,
  0x05D0u, 0x05D1u, 0x05D2u, 0x05D3u, 0x05D4u, 0x05D5u, 0x05D6u, 0x05D7u,
  0x05D8u, 0x05D9u, 0x05DAu, 0x05DBu, 0x05DCu, 0x05DDu, 0x05DEu, 0x05DFu,
  0x05E0u, 0x05E1u, 0x05E2u, 0x05E3u, 0x05E4u, 0x05E5u, 0x05E6u, 0x05E7u,
  0x05E8u, 0x05E9u, 0x05EAu, 0xFFFFu, 0xFFFFu, 0x200Eu, 0x200Fu, 0xFFFFu,
};

// ->> ISO_8859_8_E (iso8859-8), 128 entries.
static unsigned short const unicode_ISO_8859_8_E[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0xFFFFu, 0x00A2u, 0x00A3u, 0x00A4u, 0x00A5u, 0x00A6u, 0x00A7u,
  0x00A8u, 0x00A9u, 0x00D7u, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x00AFu,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x00B4u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x00B8u, 0x00B9u, 0x00F7u, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x2017u,
  0x05D0u, 0x05D1u, 0x05D2u, 0x05D3u, 0x05D4u, 0x05D5u, 0x05D6u, 0x05D7u,
  0x05D8u, 0x05D9u, 0x05DAu, 0x05DBu, 0x05DCu, 0x05DDu, 0x05DEu, 0x05DFu,
  0x05E0u, 0x05E1u, 0x05E2u, 0x05E3u, 0x05E4u, 0x05E5u, 0x05E6u, 0x05E7u,
  0x05E8u, 0x05E9u, 0x05EAu, 0xFFFFu, 0xFFFFu, 0x200Eu, 0x200Fu, 0xFFFFu,
};

// ->> ISO_8859_8_I (iso8859-8), 128 entries.
static unsigned short const unicode_ISO_8859_8_I[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0xFFFFu, 0x00A2u, 0x00A3u, 0x00A4u, 0x00A5u, 0x00A6u, 0x00A7u,
  0x00A8u, 0x00A9u, 0x00D7u, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x00AFu,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x00B4u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x00B8u, 0x00B9u, 0x00F7u, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x2017u,
  0x05D0u, 0x05D1u, 0x05D2u, 0x05D3u, 0x05D4u, 0x05D5u, 0x05D6u, 0x05D7u,
  0x05D8u, 0x05D9u, 0x05DAu, 0x05DBu, 0x05DCu, 0x05DDu, 0x05DEu, 0x05DFu,
  0x05E0u, 0x05E1u, 0x05E2u, 0x05E3u, 0x05E4u, 0x05E5u, 0x05E6u, 0x05E7u,
  0x05E8u, 0x05E9u, 0x05EAu, 0xFFFFu, 0xFFFFu, 0x200Eu, 0x200Fu, 0xFFFFu,
};

// ->> ISO_8859_9_1989 (iso8859-9), 128 entries.
static unsigned short const unicode_ISO_8859_9_1989[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x00A1u, 0x00A2u, 0x00A3u, 0x00A4u, 0x00A5u, 0x00A6u, 0x00A7u,
  0x00A8u, 0x00A9u, 0x00AAu, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x00AFu,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x00B4u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x00B8u, 0x00B9u, 0x00BAu, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0x00BFu,
  0x00C0u, 0x00C1u, 0x00C2u, 0x00C3u, 0x00C4u, 0x00C5u, 0x00C6u, 0x00C7u,
  0x00C8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x00CCu, 0x00CDu, 0x00CEu, 0x00CFu,
  0x011Eu, 0x00D1u, 0x00D2u, 0x00D3u, 0x00D4u, 0x00D5u, 0x00D6u, 0x00D7u,
  0x00D8u, 0x00D9u, 0x00DAu, 0x00DBu, 0x00DCu, 0x0130u, 0x015Eu, 0x00DFu,
  0x00E0u, 0x00E1u, 0x00E2u, 0x00E3u, 0x00E4u, 0x00E5u, 0x00E6u, 0x00E7u,
  0x00E8u, 0x00E9u, 0x00EAu, 0x00EBu, 0x00ECu, 0x00EDu, 0x00EEu, 0x00EFu,
  0x011Fu, 0x00F1u, 0x00F2u, 0x00F3u, 0x00F4u, 0x00F5u, 0x00F6u, 0x00F7u,
  0x00F8u, 0x00F9u, 0x00FAu, 0x00FBu, 0x00FCu, 0x0131u, 0x015Fu, 0x00FFu,
};

// ->> ISO_8859_10 (iso8859-10), 128 entries.
static unsigned short const unicode_ISO_8859_10[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x0104u, 0x0112u, 0x0122u, 0x012Au, 0x0128u, 0x0136u, 0x00A7u,
  0x013Bu, 0x0110u, 0x0160u, 0x0166u, 0x017Du, 0x00ADu, 0x016Au, 0x014Au,
  0x00B0u, 0x0105u, 0x0113u, 0x0123u, 0x012Bu, 0x0129u, 0x0137u, 0x00B7u,
  0x013Cu, 0x0111u, 0x0161u, 0x0167u, 0x017Eu, 0x2015u, 0x016Bu, 0x014Bu,
  0x0100u, 0x00C1u, 0x00C2u, 0x00C3u, 0x00C4u, 0x00C5u, 0x00C6u, 0x012Eu,
  0x010Cu, 0x00C9u, 0x0118u, 0x00CBu, 0x0116u, 0x00CDu, 0x00CEu, 0x00CFu,
  0x00D0u, 0x0145u, 0x014Cu, 0x00D3u, 0x00D4u, 0x00D5u, 0x00D6u, 0x0168u,
  0x00D8u, 0x0172u, 0x00DAu, 0x00DBu, 0x00DCu, 0x00DDu, 0x00DEu, 0x00DFu,
  0x0101u, 0x00E1u, 0x00E2u, 0x00E3u, 0x00E4u, 0x00E5u, 0x00E6u, 0x012Fu,
  0x010Du, 0x00E9u, 0x0119u, 0x00EBu, 0x0117u, 0x00EDu, 0x00EEu, 0x00EFu,
  0x00F0u, 0x0146u, 0x014Du, 0x00F3u, 0x00F4u, 0x00F5u, 0x00F6u, 0x0169u,
  0x00F8u, 0x0173u, 0x00FAu, 0x00FBu, 0x00FCu, 0x00FDu, 0x00FEu, 0x0138u,
};

// ->> ISO_8859_11 (iso8859-11), 128 entries.
static unsigned short const unicode_ISO_8859_11[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x0E01u, 0x0E02u, 0x0E03u, 0x0E04u, 0x0E05u, 0x0E06u, 0x0E07u,
  0x0E08u, 0x0E09u, 0x0E0Au, 0x0E0Bu, 0x0E0Cu, 0x0E0Du, 0x0E0Eu, 0x0E0Fu,
  0x0E10u, 0x0E11u, 0x0E12u, 0x0E13u, 0x0E14u, 0x0E15u, 0x0E16u, 0x0E17u,
  0x0E18u, 0x0E19u, 0x0E1Au, 0x0E1Bu, 0x0E1Cu, 0x0E1Du, 0x0E1Eu, 0x0E1Fu,
  0x0E20u, 0x0E21u, 0x0E22u, 0x0E23u, 0x0E24u, 0x0E25u, 0x0E26u, 0x0E27u,
  0x0E28u, 0x0E29u, 0x0E2Au, 0x0E2Bu, 0x0E2Cu, 0x0E2Du, 0x0E2Eu, 0x0E2Fu,
  0x0E30u, 0x0E31u, 0x0E32u, 0x0E33u, 0x0E34u, 0x0E35u, 0x0E36u, 0x0E37u,
  0x0E38u, 0x0E39u, 0x0E3Au, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x0E3Fu,
  0x0E40u, 0x0E41u, 0x0E42u, 0x0E43u, 0x0E44u, 0x0E45u, 0x0E46u, 0x0E47u,
  0x0E48u, 0x0E49u, 0x0E4Au, 0x0E4Bu, 0x0E4Cu, 0x0E4Du, 0x0E4Eu, 0x0E4Fu,
  0x0E50u, 0x0E51u, 0x0E52u, 0x0E53u, 0x0E54u, 0x0E55u, 0x0E56u, 0x0E57u,
  0x0E58u, 0x0E59u, 0x0E5Au, 0x0E5Bu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
};

// ->> ISO_8859_13 (iso8859-13), 128 entries.
static unsigned short const unicode_ISO_8859_13[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x201Du, 0x00A2u, 0x00A3u, 0x00A4u, 0x201Eu, 0x00A6u, 0x00A7u,
  0x00D8u, 0x00A9u, 0x0156u, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x00C6u,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x201Cu, 0x00B5u, 0x00B6u, 0x00B7u,
  0x00F8u, 0x00B9u, 0x0157u, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0x00E6u,
  0x0104u, 0x012Eu, 0x0100u, 0x0106u, 0x00C4u, 0x00C5u, 0x0118u, 0x0112u,
  0x010Cu, 0x00C9u, 0x0179u, 0x0116u, 0x0122u, 0x0136u, 0x012Au, 0x013Bu,
  0x0160u, 0x0143u, 0x0145u, 0x00D3u, 0x014Cu, 0x00D5u, 0x00D6u, 0x00D7u,
  0x0172u, 0x0141u, 0x015Au, 0x016Au, 0x00DCu, 0x017Bu, 0x017Du, 0x00DFu,
  0x0105u, 0x012Fu, 0x0101u, 0x0107u, 0x00E4u, 0x00E5u, 0x0119u, 0x0113u,
  0x010Du, 0x00E9u, 0x017Au, 0x0117u, 0x0123u, 0x0137u, 0x012Bu, 0x013Cu,
  0x0161u, 0x0144u, 0x0146u, 0x00F3u, 0x014Du, 0x00F5u, 0x00F6u, 0x00F7u,
  0x0173u, 0x0142u, 0x015Bu, 0x016Bu, 0x00FCu, 0x017Cu, 0x017Eu, 0x2019u,
};

// ->> ISO_8859_14 (iso8859-14), 128 entries.
static unsigned short const unicode_ISO_8859_14[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x1E02u, 0x1E03u, 0x00A3u, 0x010Au, 0x010Bu, 0x1E0Au, 0x00A7u,
  0x1E80u, 0x00A9u, 0x1E82u, 0x1E0Bu, 0x1EF2u, 0x00ADu, 0x00AEu, 0x0178u,
  0x1E1Eu, 0x1E1Fu, 0x0120u, 0x0121u, 0x1E40u, 0x1E41u, 0x00B6u, 0x1E56u,
  0x1E81u, 0x1E57u, 0x1E83u, 0x1E60u, 0x1EF3u, 0x1E84u, 0x1E85u, 0x1E61u,
  0x00C0u, 0x00C1u, 0x00C2u, 0x00C3u, 0x00C4u, 0x00C5u, 0x00C6u, 0x00C7u,
  0x00C8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x00CCu, 0x00CDu, 0x00CEu, 0x00CFu,
  0x0174u, 0x00D1u, 0x00D2u, 0x00D3u, 0x00D4u, 0x00D5u, 0x00D6u, 0x1E6Au,
  0x00D8u, 0x00D9u, 0x00DAu, 0x00DBu, 0x00DCu, 0x00DDu, 0x0176u, 0x00DFu,
  0x00E0u, 0x00E1u, 0x00E2u, 0x00E3u, 0x00E4u, 0x00E5u, 0x00E6u, 0x00E7u,
  0x00E8u, 0x00E9u, 0x00EAu, 0x00EBu, 0x00ECu, 0x00EDu, 0x00EEu, 0x00EFu,
  0x0175u, 0x00F1u, 0x00F2u, 0x00F3u, 0x00F4u, 0x00F5u, 0x00F6u, 0x1E6Bu,
  0x00F8u, 0x00F9u, 0x00FAu, 0x00FBu, 0x00FCu, 0x00FDu, 0x0177u, 0x00FFu,
};

// ->> ISO_8859_15 (iso8859-15), 128 entries.
static unsigned short const unicode_ISO_8859_15[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x00A1u, 0x00A2u, 0x00A3u, 0x20ACu, 0x00A5u, 0x0160u, 0x00A7u,
  0x0161u, 0x00A9u, 0x00AAu, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x00AFu,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x017Du, 0x00B5u, 0x00B6u, 0x00B7u,
  0x017Eu, 0x00B9u, 0x00BAu, 0x00BBu, 0x0152u, 0x0153u, 0x0178u, 0x00BFu,
  0x00C0u, 0x00C1u, 0x00C2u, 0x00C3u, 0x00C4u, 0x00C5u, 0x00C6u, 0x00C7u,
  0x00C8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x00CCu, 0x00CDu, 0x00CEu, 0x00CFu,
  0x00D0u, 0x00D1u, 0x00D2u, 0x00D3u, 0x00D4u, 0x00D5u, 0x00D6u, 0x00D7u,
  0x00D8u, 0x00D9u, 0x00DAu, 0x00DBu, 0x00DCu, 0x00DDu, 0x00DEu, 0x00DFu,
  0x00E0u, 0x00E1u, 0x00E2u, 0x00E3u, 0x00E4u, 0x00E5u, 0x00E6u, 0x00E7u,
  0x00E8u, 0x00E9u, 0x00EAu, 0x00EBu, 0x00ECu, 0x00EDu, 0x00EEu, 0x00EFu,
  0x00F0u, 0x00F1u, 0x00F2u, 0x00F3u, 0x00F4u, 0x00F5u, 0x00F6u, 0x00F7u,
  0x00F8u, 0x00F9u, 0x00FAu, 0x00FBu, 0x00FCu, 0x00FDu, 0x00FEu, 0x00FFu,
};

// ->> ISO_8859_16 (iso8859-16), 128 entries.
static unsigned short const unicode_ISO_8859_16[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0x00A0u, 0x0104u, 0x0105u, 0x0141u, 0x20ACu, 0x201Eu, 0x0160u, 0x00A7u,
  0x0161u, 0x00A9u, 0x0218u, 0x00ABu, 0x0179u, 0x00ADu, 0x017Au, 0x017Bu,
  0x00B0u, 0x00B1u, 0x010Cu, 0x0142u, 0x017Du, 0x201Du, 0x00B6u, 0x00B7u,
  0x017Eu, 0x010Du, 0x0219u, 0x00BBu, 0x0152u, 0x0153u, 0x0178u, 0x017Cu,
  0x00C0u, 0x00C1u, 0x00C2u, 0x0102u, 0x00C4u, 0x0106u, 0x00C6u, 0x00C7u,
  0x00C8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x00CCu, 0x00CDu, 0x00CEu, 0x00CFu,
  0x0110u, 0x0143u, 0x00D2u, 0x00D3u, 0x00D4u, 0x0150u, 0x00D6u, 0x015Au,
  0x0170u, 0x00D9u, 0x00DAu, 0x00DBu, 0x00DCu, 0x0118u, 0x021Au, 0x00DFu,
  0x00E0u, 0x00E1u, 0x00E2u, 0x0103u, 0x00E4u, 0x0107u, 0x00E6u, 0x00E7u,
  0x00E8u, 0x00E9u, 0x00EAu, 0x00EBu, 0x00ECu, 0x00EDu, 0x00EEu, 0x00EFu,
  0x0111u, 0x0144u, 0x00F2u, 0x00F3u, 0x00F4u, 0x0151u, 0x00F6u, 0x015Bu,
  0x0171u, 0x00F9u, 0x00FAu, 0x00FBu, 0x00FCu, 0x0119u, 0x021Bu, 0x00FFu,
};

// ->> KOI8_R (koi8-r), 128 entries.
static unsigned short const unicode_KOI8_R[] = {
  0x2500u, 0x2502u, 0x250Cu, 0x2510u, 0x2514u, 0x2518u, 0x251Cu, 0x2524u,
  0x252Cu, 0x2534u, 0x253Cu, 0x2580u, 0x2584u, 0x2588u, 0x258Cu, 0x2590u,
  0x2591u, 0x2592u, 0x2593u, 0x2320u, 0x25A0u, 0x2219u, 0x221Au, 0x2248u,
  0x2264u, 0x2265u, 0x00A0u, 0x2321u, 0x00B0u, 0x00B2u, 0x00B7u, 0x00F7u,
  0x2550u, 0x2551u, 0x2552u, 0x0451u, 0x2553u, 0x2554u, 0x2555u, 0x2556u,
  0x2557u, 0x2558u, 0x2559u, 0x255Au, 0x255Bu, 0x255Cu, 0x255Du, 0x255Eu,
  0x255Fu, 0x2560u, 0x2561u, 0x0401u, 0x2562u, 0x2563u, 0x2564u, 0x2565u,
  0x2566u, 0x2567u, 0x2568u, 0x2569u, 0x256Au, 0x256Bu, 0x256Cu, 0x00A9u,
  0x044Eu, 0x0430u, 0x0431u, 0x0446u, 0x0434u, 0x0435u, 0x0444u, 0x0433u,
  0x0445u, 0x0438u, 0x0439u, 0x043Au, 0x043Bu, 0x043Cu, 0x043Du, 0x043Eu,
  0x043Fu, 0x044Fu, 0x0440u, 0x0441u, 0x0442u, 0x0443u, 0x0436u, 0x0432u,
  0x044Cu, 0x044Bu, 0x0437u, 0x0448u, 0x044Du, 0x0449u, 0x0447u, 0x044Au,
  0x042Eu, 0x0410u, 0x0411u, 0x0426u, 0x0414u, 0x0415u, 0x0424u, 0x0413u,
  0x0425u, 0x0418u, 0x0419u, 0x041Au, 0x041Bu, 0x041Cu, 0x041Du, 0x041Eu,
  0x041Fu, 0x042Fu, 0x0420u, 0x0421u, 0x0422u, 0x0423u, 0x0416u, 0x0412u,
  0x042Cu, 0x042Bu, 0x0417u, 0x0428u, 0x042Du, 0x0429u, 0x0427u, 0x042Au,
};

// ->> KOI8_U (koi8-u), 128 entries.
static unsigned short const unicode_KOI8_U[] = {
  0x2500u, 0x2502u, 0x250Cu, 0x2510u, 0x2514u, 0x2518u, 0x251Cu, 0x2524u,
  0x252Cu, 0x2534u, 0x253Cu, 0x2580u, 0x2584u, 0x2588u, 0x258Cu, 0x2590u,
  0x2591u, 0x2592u, 0x2593u, 0x2320u, 0x25A0u, 0x2219u, 0x221Au, 0x2248u,
  0x2264u, 0x2265u, 0x00A0u, 0x2321u, 0x00B0u, 0x00B2u, 0x00B7u, 0x00F7u,
  0x2550u, 0x2551u, 0x2552u, 0x0451u, 0x0454u, 0x2554u, 0x0456u, 0x0457u,
  0x2557u, 0x2558u, 0x2559u, 0x255Au, 0x255Bu, 0x0491u, 0x255Du, 0x255Eu,
  0x255Fu, 0x2560u, 0x2561u, 0x0401u, 0x0404u, 0x2563u, 0x0406u, 0x0407u,
  0x2566u, 0x2567u, 0x2568u, 0x2569u, 0x256Au, 0x0490u, 0x256Cu, 0x00A9u,
  0x044Eu, 0x0430u, 0x0431u, 0x0446u, 0x0434u, 0x0435u, 0x0444u, 0x0433u,
  0x0445u, 0x0438u, 0x0439u, 0x043Au, 0x043Bu, 0x043Cu, 0x043Du, 0x043Eu,
  0x043Fu, 0x044Fu, 0x0440u, 0x0441u, 0x0442u, 0x0443u, 0x0436u, 0x0432u,
  0x044Cu, 0x044Bu, 0x0437u, 0x0448u, 0x044Du, 0x0449u, 0x0447u, 0x044Au,
  0x042Eu, 0x0410u, 0x0411u, 0x0426u, 0x0414u, 0x0415u, 0x0424u, 0x0413u,
  0x0425u, 0x0418u, 0x0419u, 0x041Au, 0x041Bu, 0x041Cu, 0x041Du, 0x041Eu,
  0x041Fu, 0x042Fu, 0x0420u, 0x0421u, 0x0422u, 0x0423u, 0x0416u, 0x0412u,
  0x042Cu, 0x042Bu, 0x0417u, 0x0428u, 0x042Du, 0x0429u, 0x0427u, 0x042Au,
};

// ->> KZ_1048 (kz1048), 128 entries.
static unsigned short const unicode_KZ_1048[] = {
  0x0402u, 0x0403u, 0x201Au, 0x0453u, 0x201Eu, 0x2026u, 0x2020u, 0x2021u,
  0x20ACu, 0x2030u, 0x0409u, 0x2039u, 0x040Au, 0x049Au, 0x04BAu, 0x040Fu,
  0x0452u, 0x2018u, 0x2019u, 0x201Cu, 0x201Du, 0x2022u, 0x2013u, 0x2014u,
  0xFFFFu, 0x2122u, 0x0459u, 0x203Au, 0x045Au, 0x049Bu, 0x04BBu, 0x045Fu,
  0x00A0u, 0x04B0u, 0x04B1u, 0x04D8u, 0x00A4u, 0x04E8u, 0x00A6u, 0x00A7u,
  0x0401u, 0x00A9u, 0x0492u, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x04AEu,
  0x00B0u, 0x00B1u, 0x0406u, 0x0456u, 0x04E9u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x0451u, 0x2116u, 0x0493u, 0x00BBu, 0x04D9u, 0x04A2u, 0x04A3u, 0x04AFu,
  0x0410u, 0x0411u, 0x0412u, 0x0413u, 0x0414u, 0x0415u, 0x0416u, 0x0417u,
  0x0418u, 0x0419u, 0x041Au, 0x041Bu, 0x041Cu, 0x041Du, 0x041Eu, 0x041Fu,
  0x0420u, 0x0421u, 0x0422u, 0x0423u, 0x0424u, 0x0425u, 0x0426u, 0x0427u,
  0x0428u, 0x0429u, 0x042Au, 0x042Bu, 0x042Cu, 0x042Du, 0x042Eu, 0x042Fu,
  0x0430u, 0x0431u, 0x0432u, 0x0433u, 0x0434u, 0x0435u, 0x0436u, 0x0437u,
  0x0438u, 0x0439u, 0x043Au, 0x043Bu, 0x043Cu, 0x043Du, 0x043Eu, 0x043Fu,
  0x0440u, 0x0441u, 0x0442u, 0x0443u, 0x0444u, 0x0445u, 0x0446u, 0x0447u,
  0x0448u, 0x0449u, 0x044Au, 0x044Bu, 0x044Cu, 0x044Du, 0x044Eu, 0x044Fu,
};

// ->> MACINTOSH (mac-roman), 128 entries.
static unsigned short const unicode_MACINTOSH[] = {
  0x00C4u, 0x00C5u, 0x00C7u, 0x00C9u, 0x00D1u, 0x00D6u, 0x00DCu, 0x00E1u,
  0x00E0u, 0x00E2u, 0x00E4u, 0x00E3u, 0x00E5u, 0x00E7u, 0x00E9u, 0x00E8u,
  0x00EAu, 0x00EBu, 0x00EDu, 0x00ECu, 0x00EEu, 0x00EFu, 0x00F1u, 0x00F3u,
  0x00F2u, 0x00F4u, 0x00F6u, 0x00F5u, 0x00FAu, 0x00F9u, 0x00FBu, 0x00FCu,
  0x2020u, 0x00B0u, 0x00A2u, 0x00A3u, 0x00A7u, 0x2022u, 0x00B6u, 0x00DFu,
  0x00AEu, 0x00A9u, 0x2122u, 0x00B4u, 0x00A8u, 0x2260u, 0x00C6u, 0x00D8u,
  0x221Eu, 0x00B1u, 0x2264u, 0x2265u, 0x00A5u, 0x00B5u, 0x2202u, 0x2211u,
  0x220Fu, 0x03C0u, 0x222Bu, 0x00AAu, 0x00BAu, 0x03A9u, 0x00E6u, 0x00F8u,
  0x00BFu, 0x00A1u, 0x00ACu, 0x221Au, 0x0192u, 0x2248u, 0x2206u, 0x00ABu,
  0x00BBu, 0x2026u, 0x00A0u, 0x00C0u, 0x00C3u, 0x00D5u, 0x0152u, 0x0153u,
  0x2013u, 0x2014u, 0x201Cu, 0x201Du, 0x2018u, 0x2019u, 0x00F7u, 0x25CAu,
  0x00FFu, 0x0178u, 0x2044u, 0x20ACu, 0x2039u, 0x203Au, 0xFB01u, 0xFB02u,
  0x2021u, 0x00B7u, 0x201Au, 0x201Eu, 0x2030u, 0x00C2u, 0x00CAu, 0x00C1u,
  0x00CBu, 0x00C8u, 0x00CDu, 0x00CEu, 0x00CFu, 0x00CCu, 0x00D3u, 0x00D4u,
  0xF8FFu, 0x00D2u, 0x00DAu, 0x00DBu, 0x00D9u, 0x0131u, 0x02C6u, 0x02DCu,
  0x00AFu, 0x02D8u, 0x02D9u, 0x02DAu, 0x00B8u, 0x02DDu, 0x02DBu, 0x02C7u,
};

// ->> PTCP154 (ptcp154), 128 entries.
static unsigned short const unicode_PTCP154[] = {
  0x0496u, 0x0492u, 0x04EEu, 0x0493u, 0x201Eu, 0x2026u, 0x04B6u, 0x04AEu,
  0x04B2u, 0x04AFu, 0x04A0u, 0x04E2u, 0x04A2u, 0x049Au, 0x04BAu, 0x04B8u,
  0x0497u, 0x2018u, 0x2019u, 0x201Cu, 0x201Du, 0x2022u, 0x2013u, 0x2014u,
  0x04B3u, 0x04B7u, 0x04A1u, 0x04E3u, 0x04A3u, 0x049Bu, 0x04BBu, 0x04B9u,
  0x00A0u, 0x040Eu, 0x045Eu, 0x0408u, 0x04E8u, 0x0498u, 0x04B0u, 0x00A7u,
  0x0401u, 0x00A9u, 0x04D8u, 0x00ABu, 0x00ACu, 0x04EFu, 0x00AEu, 0x049Cu,
  0x00B0u, 0x04B1u, 0x0406u, 0x0456u, 0x0499u, 0x04E9u, 0x00B6u, 0x00B7u,
  0x0451u, 0x2116u, 0x04D9u, 0x00BBu, 0x0458u, 0x04AAu, 0x04ABu, 0x049Du,
  0x0410u, 0x0411u, 0x0412u, 0x0413u, 0x0414u, 0x0415u, 0x0416u, 0x0417u,
  0x0418u, 0x0419u, 0x041Au, 0x041Bu, 0x041Cu, 0x041Du, 0x041Eu, 0x041Fu,
  0x0420u, 0x0421u, 0x0422u, 0x0423u, 0x0424u, 0x0425u, 0x0426u, 0x0427u,
  0x0428u, 0x0429u, 0x042Au, 0x042Bu, 0x042Cu, 0x042Du, 0x042Eu, 0x042Fu,
  0x0430u, 0x0431u, 0x0432u, 0x0433u, 0x0434u, 0x0435u, 0x0436u, 0x0437u,
  0x0438u, 0x0439u, 0x043Au, 0x043Bu, 0x043Cu, 0x043Du, 0x043Eu, 0x043Fu,
  0x0440u, 0x0441u, 0x0442u, 0x0443u, 0x0444u, 0x0445u, 0x0446u, 0x0447u,
  0x0448u, 0x0449u, 0x044Au, 0x044Bu, 0x044Cu, 0x044Du, 0x044Eu, 0x044Fu,
};

// ->> TIS_620 (tis-620), 128 entries.
static unsigned short const unicode_TIS_620[] = {
  0x0080u, 0x0081u, 0x0082u, 0x0083u, 0x0084u, 0x0085u, 0x0086u, 0x0087u,
  0x0088u, 0x0089u, 0x008Au, 0x008Bu, 0x008Cu, 0x008Du, 0x008Eu, 0x008Fu,
  0x0090u, 0x0091u, 0x0092u, 0x0093u, 0x0094u, 0x0095u, 0x0096u, 0x0097u,
  0x0098u, 0x0099u, 0x009Au, 0x009Bu, 0x009Cu, 0x009Du, 0x009Eu, 0x009Fu,
  0xFFFFu, 0x0E01u, 0x0E02u, 0x0E03u, 0x0E04u, 0x0E05u, 0x0E06u, 0x0E07u,
  0x0E08u, 0x0E09u, 0x0E0Au, 0x0E0Bu, 0x0E0Cu, 0x0E0Du, 0x0E0Eu, 0x0E0Fu,
  0x0E10u, 0x0E11u, 0x0E12u, 0x0E13u, 0x0E14u, 0x0E15u, 0x0E16u, 0x0E17u,
  0x0E18u, 0x0E19u, 0x0E1Au, 0x0E1Bu, 0x0E1Cu, 0x0E1Du, 0x0E1Eu, 0x0E1Fu,
  0x0E20u, 0x0E21u, 0x0E22u, 0x0E23u, 0x0E24u, 0x0E25u, 0x0E26u, 0x0E27u,
  0x0E28u, 0x0E29u, 0x0E2Au, 0x0E2Bu, 0x0E2Cu, 0x0E2Du, 0x0E2Eu, 0x0E2Fu,
  0x0E30u, 0x0E31u, 0x0E32u, 0x0E33u, 0x0E34u, 0x0E35u, 0x0E36u, 0x0E37u,
  0x0E38u, 0x0E39u, 0x0E3Au, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x0E3Fu,
  0x0E40u, 0x0E41u, 0x0E42u, 0x0E43u, 0x0E44u, 0x0E45u, 0x0E46u, 0x0E47u,
  0x0E48u, 0x0E49u, 0x0E4Au, 0x0E4Bu, 0x0E4Cu, 0x0E4Du, 0x0E4Eu, 0x0E4Fu,
  0x0E50u, 0x0E51u, 0x0E52u, 0x0E53u, 0x0E54u, 0x0E55u, 0x0E56u, 0x0E57u,
  0x0E58u, 0x0E59u, 0x0E5Au, 0x0E5Bu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
};

// ->> WINDOWS_874 (cp874), 128 entries.
static unsigned short const unicode_WINDOWS_874[] = {
  0x20ACu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x2026u, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0x2018u, 0x2019u, 0x201Cu, 0x201Du, 0x2022u, 0x2013u, 0x2014u,
  0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0x00A0u, 0x0E01u, 0x0E02u, 0x0E03u, 0x0E04u, 0x0E05u, 0x0E06u, 0x0E07u,
  0x0E08u, 0x0E09u, 0x0E0Au, 0x0E0Bu, 0x0E0Cu, 0x0E0Du, 0x0E0Eu, 0x0E0Fu,
  0x0E10u, 0x0E11u, 0x0E12u, 0x0E13u, 0x0E14u, 0x0E15u, 0x0E16u, 0x0E17u,
  0x0E18u, 0x0E19u, 0x0E1Au, 0x0E1Bu, 0x0E1Cu, 0x0E1Du, 0x0E1Eu, 0x0E1Fu,
  0x0E20u, 0x0E21u, 0x0E22u, 0x0E23u, 0x0E24u, 0x0E25u, 0x0E26u, 0x0E27u,
  0x0E28u, 0x0E29u, 0x0E2Au, 0x0E2Bu, 0x0E2Cu, 0x0E2Du, 0x0E2Eu, 0x0E2Fu,
  0x0E30u, 0x0E31u, 0x0E32u, 0x0E33u, 0x0E34u, 0x0E35u, 0x0E36u, 0x0E37u,
  0x0E38u, 0x0E39u, 0x0E3Au, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0x0E3Fu,
  0x0E40u, 0x0E41u, 0x0E42u, 0x0E43u, 0x0E44u, 0x0E45u, 0x0E46u, 0x0E47u,
  0x0E48u, 0x0E49u, 0x0E4Au, 0x0E4Bu, 0x0E4Cu, 0x0E4Du, 0x0E4Eu, 0x0E4Fu,
  0x0E50u, 0x0E51u, 0x0E52u, 0x0E53u, 0x0E54u, 0x0E55u, 0x0E56u, 0x0E57u,
  0x0E58u, 0x0E59u, 0x0E5Au, 0x0E5Bu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
};

// ->> WINDOWS_1250 (cp1250), 128 entries.
static unsigned short const unicode_WINDOWS_1250[] = {
  0x20ACu, 0xFFFFu, 0x201Au, 0xFFFFu, 0x201Eu, 0x2026u, 0x2020u, 0x2021u,
  0xFFFFu, 0x2030u, 0x0160u, 0x2039u, 0x015Au, 0x0164u, 0x017Du, 0x0179u,
  0xFFFFu, 0x2018u, 0x2019u, 0x201Cu, 0x201Du, 0x2022u, 0x2013u, 0x2014u,
  0xFFFFu, 0x2122u, 0x0161u, 0x203Au, 0x015Bu, 0x0165u, 0x017Eu, 0x017Au,
  0x00A0u, 0x02C7u, 0x02D8u, 0x0141u, 0x00A4u, 0x0104u, 0x00A6u, 0x00A7u,
  0x00A8u, 0x00A9u, 0x015Eu, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x017Bu,
  0x00B0u, 0x00B1u, 0x02DBu, 0x0142u, 0x00B4u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x00B8u, 0x0105u, 0x015Fu, 0x00BBu, 0x013Du, 0x02DDu, 0x013Eu, 0x017Cu,
  0x0154u, 0x00C1u, 0x00C2u, 0x0102u, 0x00C4u, 0x0139u, 0x0106u, 0x00C7u,
  0x010Cu, 0x00C9u, 0x0118u, 0x00CBu, 0x011Au, 0x00CDu, 0x00CEu, 0x010Eu,
  0x0110u, 0x0143u, 0x0147u, 0x00D3u, 0x00D4u, 0x0150u, 0x00D6u, 0x00D7u,
  0x0158u, 0x016Eu, 0x00DAu, 0x0170u, 0x00DCu, 0x00DDu, 0x0162u, 0x00DFu,
  0x0155u, 0x00E1u, 0x00E2u, 0x0103u, 0x00E4u, 0x013Au, 0x0107u, 0x00E7u,
  0x010Du, 0x00E9u, 0x0119u, 0x00EBu, 0x011Bu, 0x00EDu, 0x00EEu, 0x010Fu,
  0x0111u, 0x0144u, 0x0148u, 0x00F3u, 0x00F4u, 0x0151u, 0x00F6u, 0x00F7u,
  0x0159u, 0x016Fu, 0x00FAu, 0x0171u, 0x00FCu, 0x00FDu, 0x0163u, 0x02D9u,
};

// ->> WINDOWS_1251 (cp1251), 128 entries.
static unsigned short const unicode_WINDOWS_1251[] = {
  0x0402u, 0x0403u, 0x201Au, 0x0453u, 0x201Eu, 0x2026u, 0x2020u, 0x2021u,
  0x20ACu, 0x2030u, 0x0409u, 0x2039u, 0x040Au, 0x040Cu, 0x040Bu, 0x040Fu,
  0x0452u, 0x2018u, 0x2019u, 0x201Cu, 0x201Du, 0x2022u, 0x2013u, 0x2014u,
  0xFFFFu, 0x2122u, 0x0459u, 0x203Au, 0x045Au, 0x045Cu, 0x045Bu, 0x045Fu,
  0x00A0u, 0x040Eu, 0x045Eu, 0x0408u, 0x00A4u, 0x0490u, 0x00A6u, 0x00A7u,
  0x0401u, 0x00A9u, 0x0404u, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x0407u,
  0x00B0u, 0x00B1u, 0x0406u, 0x0456u, 0x0491u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x0451u, 0x2116u, 0x0454u, 0x00BBu, 0x0458u, 0x0405u, 0x0455u, 0x0457u,
  0x0410u, 0x0411u, 0x0412u, 0x0413u, 0x0414u, 0x0415u, 0x0416u, 0x0417u,
  0x0418u, 0x0419u, 0x041Au, 0x041Bu, 0x041Cu, 0x041Du, 0x041Eu, 0x041Fu,
  0x0420u, 0x0421u, 0x0422u, 0x0423u, 0x0424u, 0x0425u, 0x0426u, 0x0427u,
  0x0428u, 0x0429u, 0x042Au, 0x042Bu, 0x042Cu, 0x042Du, 0x042Eu, 0x042Fu,
  0x0430u, 0x0431u, 0x0432u, 0x0433u, 0x0434u, 0x0435u, 0x0436u, 0x0437u,
  0x0438u, 0x0439u, 0x043Au, 0x043Bu, 0x043Cu, 0x043Du, 0x043Eu, 0x043Fu,
  0x0440u, 0x0441u, 0x0442u, 0x0443u, 0x0444u, 0x0445u, 0x0446u, 0x0447u,
  0x0448u, 0x0449u, 0x044Au, 0x044Bu, 0x044Cu, 0x044Du, 0x044Eu, 0x044Fu,
};

// ->> WINDOWS_1252 (cp1252), 128 entries.
static unsigned short const unicode_WINDOWS_1252[] = {
  0x20ACu, 0xFFFFu, 0x201Au, 0x0192u, 0x201Eu, 0x2026u, 0x2020u, 0x2021u,
  0x02C6u, 0x2030u, 0x0160u, 0x2039u, 0x0152u, 0xFFFFu, 0x017Du, 0xFFFFu,
  0xFFFFu, 0x2018u, 0x2019u, 0x201Cu, 0x201Du, 0x2022u, 0x2013u, 0x2014u,
  0x02DCu, 0x2122u, 0x0161u, 0x203Au, 0x0153u, 0xFFFFu, 0x017Eu, 0x0178u,
  0x00A0u, 0x00A1u, 0x00A2u, 0x00A3u, 0x00A4u, 0x00A5u, 0x00A6u, 0x00A7u,
  0x00A8u, 0x00A9u, 0x00AAu, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x00AFu,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x00B4u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x00B8u, 0x00B9u, 0x00BAu, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0x00BFu,
  0x00C0u, 0x00C1u, 0x00C2u, 0x00C3u, 0x00C4u, 0x00C5u, 0x00C6u, 0x00C7u,
  0x00C8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x00CCu, 0x00CDu, 0x00CEu, 0x00CFu,
  0x00D0u, 0x00D1u, 0x00D2u, 0x00D3u, 0x00D4u, 0x00D5u, 0x00D6u, 0x00D7u,
  0x00D8u, 0x00D9u, 0x00DAu, 0x00DBu, 0x00DCu, 0x00DDu, 0x00DEu, 0x00DFu,
  0x00E0u, 0x00E1u, 0x00E2u, 0x00E3u, 0x00E4u, 0x00E5u, 0x00E6u, 0x00E7u,
  0x00E8u, 0x00E9u, 0x00EAu, 0x00EBu, 0x00ECu, 0x00EDu, 0x00EEu, 0x00EFu,
  0x00F0u, 0x00F1u, 0x00F2u, 0x00F3u, 0x00F4u, 0x00F5u, 0x00F6u, 0x00F7u,
  0x00F8u, 0x00F9u, 0x00FAu, 0x00FBu, 0x00FCu, 0x00FDu, 0x00FEu, 0x00FFu,
};

// ->> WINDOWS_1253 (cp1253), 128 entries.
static unsigned short const unicode_WINDOWS_1253[] = {
  0x20ACu, 0xFFFFu, 0x201Au, 0x0192u, 0x201Eu, 0x2026u, 0x2020u, 0x2021u,
  0xFFFFu, 0x2030u, 0xFFFFu, 0x2039u, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0x2018u, 0x2019u, 0x201Cu, 0x201Du, 0x2022u, 0x2013u, 0x2014u,
  0xFFFFu, 0x2122u, 0xFFFFu, 0x203Au, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0x00A0u, 0x0385u, 0x0386u, 0x00A3u, 0x00A4u, 0x00A5u, 0x00A6u, 0x00A7u,
  0x00A8u, 0x00A9u, 0xFFFFu, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x2015u,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x0384u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x0388u, 0x0389u, 0x038Au, 0x00BBu, 0x038Cu, 0x00BDu, 0x038Eu, 0x038Fu,
  0x0390u, 0x0391u, 0x0392u, 0x0393u, 0x0394u, 0x0395u, 0x0396u, 0x0397u,
  0x0398u, 0x0399u, 0x039Au, 0x039Bu, 0x039Cu, 0x039Du, 0x039Eu, 0x039Fu,
  0x03A0u, 0x03A1u, 0xFFFFu, 0x03A3u, 0x03A4u, 0x03A5u, 0x03A6u, 0x03A7u,
  0x03A8u, 0x03A9u, 0x03AAu, 0x03ABu, 0x03ACu, 0x03ADu, 0x03AEu, 0x03AFu,
  0x03B0u, 0x03B1u, 0x03B2u, 0x03B3u, 0x03B4u, 0x03B5u, 0x03B6u, 0x03B7u,
  0x03B8u, 0x03B9u, 0x03BAu, 0x03BBu, 0x03BCu, 0x03BDu, 0x03BEu, 0x03BFu,
  0x03C0u, 0x03C1u, 0x03C2u, 0x03C3u, 0x03C4u, 0x03C5u, 0x03C6u, 0x03C7u,
  0x03C8u, 0x03C9u, 0x03CAu, 0x03CBu, 0x03CCu, 0x03CDu, 0x03CEu, 0xFFFFu,
};

// ->> WINDOWS_1254 (cp1254), 128 entries.
static unsigned short const unicode_WINDOWS_1254[] = {
  0x20ACu, 0xFFFFu, 0x201Au, 0x0192u, 0x201Eu, 0x2026u, 0x2020u, 0x2021u,
  0x02C6u, 0x2030u, 0x0160u, 0x2039u, 0x0152u, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0x2018u, 0x2019u, 0x201Cu, 0x201Du, 0x2022u, 0x2013u, 0x2014u,
  0x02DCu, 0x2122u, 0x0161u, 0x203Au, 0x0153u, 0xFFFFu, 0xFFFFu, 0x0178u,
  0x00A0u, 0x00A1u, 0x00A2u, 0x00A3u, 0x00A4u, 0x00A5u, 0x00A6u, 0x00A7u,
  0x00A8u, 0x00A9u, 0x00AAu, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x00AFu,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x00B4u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x00B8u, 0x00B9u, 0x00BAu, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0x00BFu,
  0x00C0u, 0x00C1u, 0x00C2u, 0x00C3u, 0x00C4u, 0x00C5u, 0x00C6u, 0x00C7u,
  0x00C8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x00CCu, 0x00CDu, 0x00CEu, 0x00CFu,
  0x011Eu, 0x00D1u, 0x00D2u, 0x00D3u, 0x00D4u, 0x00D5u, 0x00D6u, 0x00D7u,
  0x00D8u, 0x00D9u, 0x00DAu, 0x00DBu, 0x00DCu, 0x0130u, 0x015Eu, 0x00DFu,
  0x00E0u, 0x00E1u, 0x00E2u, 0x00E3u, 0x00E4u, 0x00E5u, 0x00E6u, 0x00E7u,
  0x00E8u, 0x00E9u, 0x00EAu, 0x00EBu, 0x00ECu, 0x00EDu, 0x00EEu, 0x00EFu,
  0x011Fu, 0x00F1u, 0x00F2u, 0x00F3u, 0x00F4u, 0x00F5u, 0x00F6u, 0x00F7u,
  0x00F8u, 0x00F9u, 0x00FAu, 0x00FBu, 0x00FCu, 0x0131u, 0x015Fu, 0x00FFu,
};

// ->> WINDOWS_1255 (cp1255), 128 entries.
static unsigned short const unicode_WINDOWS_1255[] = {
  0x20ACu, 0xFFFFu, 0x201Au, 0x0192u, 0x201Eu, 0x2026u, 0x2020u, 0x2021u,
  0x02C6u, 0x2030u, 0xFFFFu, 0x2039u, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0x2018u, 0x2019u, 0x201Cu, 0x201Du, 0x2022u, 0x2013u, 0x2014u,
  0x02DCu, 0x2122u, 0xFFFFu, 0x203Au, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0x00A0u, 0x00A1u, 0x00A2u, 0x00A3u, 0x20AAu, 0x00A5u, 0x00A6u, 0x00A7u,
  0x00A8u, 0x00A9u, 0x00D7u, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x00AFu,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x00B4u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x00B8u, 0x00B9u, 0x00F7u, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0x00BFu,
  0x05B0u, 0x05B1u, 0x05B2u, 0x05B3u, 0x05B4u, 0x05B5u, 0x05B6u, 0x05B7u,
  0x05B8u, 0x05B9u, 0xFFFFu, 0x05BBu, 0x05BCu, 0x05BDu, 0x05BEu, 0x05BFu,
  0x05C0u, 0x05C1u, 0x05C2u, 0x05C3u, 0x05F0u, 0x05F1u, 0x05F2u, 0x05F3u,
  0x05F4u, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0x05D0u, 0x05D1u, 0x05D2u, 0x05D3u, 0x05D4u, 0x05D5u, 0x05D6u, 0x05D7u,
  0x05D8u, 0x05D9u, 0x05DAu, 0x05DBu, 0x05DCu, 0x05DDu, 0x05DEu, 0x05DFu,
  0x05E0u, 0x05E1u, 0x05E2u, 0x05E3u, 0x05E4u, 0x05E5u, 0x05E6u, 0x05E7u,
  0x05E8u, 0x05E9u, 0x05EAu, 0xFFFFu, 0xFFFFu, 0x200Eu, 0x200Fu, 0xFFFFu,
};

// ->> WINDOWS_1256 (cp1256), 128 entries.
static unsigned short const unicode_WINDOWS_1256[] = {
  0x20ACu, 0x067Eu, 0x201Au, 0x0192u, 0x201Eu, 0x2026u, 0x2020u, 0x2021u,
  0x02C6u, 0x2030u, 0x0679u, 0x2039u, 0x0152u, 0x0686u, 0x0698u, 0x0688u,
  0x06AFu, 0x2018u, 0x2019u, 0x201Cu, 0x201Du, 0x2022u, 0x2013u, 0x2014u,
  0x06A9u, 0x2122u, 0x0691u, 0x203Au, 0x0153u, 0x200Cu, 0x200Du, 0x06BAu,
  0x00A0u, 0x060Cu, 0x00A2u, 0x00A3u, 0x00A4u, 0x00A5u, 0x00A6u, 0x00A7u,
  0x00A8u, 0x00A9u, 0x06BEu, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x00AFu,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x00B4u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x00B8u, 0x00B9u, 0x061Bu, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0x061Fu,
  0x06C1u, 0x0621u, 0x0622u, 0x0623u, 0x0624u, 0x0625u, 0x0626u, 0x0627u,
  0x0628u, 0x0629u, 0x062Au, 0x062Bu, 0x062Cu, 0x062Du, 0x062Eu, 0x062Fu,
  0x0630u, 0x0631u, 0x0632u, 0x0633u, 0x0634u, 0x0635u, 0x0636u, 0x00D7u,
  0x0637u, 0x0638u, 0x0639u, 0x063Au, 0x0640u, 0x0641u, 0x0642u, 0x0643u,
  0x00E0u, 0x0644u, 0x00E2u, 0x0645u, 0x0646u, 0x0647u, 0x0648u, 0x00E7u,
  0x00E8u, 0x00E9u, 0x00EAu, 0x00EBu, 0x0649u, 0x064Au, 0x00EEu, 0x00EFu,
  0x064Bu, 0x064Cu, 0x064Du, 0x064Eu, 0x00F4u, 0x064Fu, 0x0650u, 0x00F7u,
  0x0651u, 0x00F9u, 0x0652u, 0x00FBu, 0x00FCu, 0x200Eu, 0x200Fu, 0x06D2u,
};

// ->> WINDOWS_1257 (cp1257), 128 entries.
static unsigned short const unicode_WINDOWS_1257[] = {
  0x20ACu, 0xFFFFu, 0x201Au, 0xFFFFu, 0x201Eu, 0x2026u, 0x2020u, 0x2021u,
  0xFFFFu, 0x2030u, 0xFFFFu, 0x2039u, 0xFFFFu, 0x00A8u, 0x02C7u, 0x00B8u,
  0xFFFFu, 0x2018u, 0x2019u, 0x201Cu, 0x201Du, 0x2022u, 0x2013u, 0x2014u,
  0xFFFFu, 0x2122u, 0xFFFFu, 0x203Au, 0xFFFFu, 0x00AFu, 0x02DBu, 0xFFFFu,
  0x00A0u, 0xFFFFu, 0x00A2u, 0x00A3u, 0x00A4u, 0xFFFFu, 0x00A6u, 0x00A7u,
  0x00D8u, 0x00A9u, 0x0156u, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x00C6u,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x00B4u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x00F8u, 0x00B9u, 0x0157u, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0x00E6u,
  0x0104u, 0x012Eu, 0x0100u, 0x0106u, 0x00C4u, 0x00C5u, 0x0118u, 0x0112u,
  0x010Cu, 0x00C9u, 0x0179u, 0x0116u, 0x0122u, 0x0136u, 0x012Au, 0x013Bu,
  0x0160u, 0x0143u, 0x0145u, 0x00D3u, 0x014Cu, 0x00D5u, 0x00D6u, 0x00D7u,
  0x0172u, 0x0141u, 0x015Au, 0x016Au, 0x00DCu, 0x017Bu, 0x017Du, 0x00DFu,
  0x0105u, 0x012Fu, 0x0101u, 0x0107u, 0x00E4u, 0x00E5u, 0x0119u, 0x0113u,
  0x010Du, 0x00E9u, 0x017Au, 0x0117u, 0x0123u, 0x0137u, 0x012Bu, 0x013Cu,
  0x0161u, 0x0144u, 0x0146u, 0x00F3u, 0x014Du, 0x00F5u, 0x00F6u, 0x00F7u,
  0x0173u, 0x0142u, 0x015Bu, 0x016Bu, 0x00FCu, 0x017Cu, 0x017Eu, 0x02D9u,
};

// ->> WINDOWS_1258 (cp1258), 128 entries.
static unsigned short const unicode_WINDOWS_1258[] = {
  0x20ACu, 0xFFFFu, 0x201Au, 0x0192u, 0x201Eu, 0x2026u, 0x2020u, 0x2021u,
  0x02C6u, 0x2030u, 0xFFFFu, 0x2039u, 0x0152u, 0xFFFFu, 0xFFFFu, 0xFFFFu,
  0xFFFFu, 0x2018u, 0x2019u, 0x201Cu, 0x201Du, 0x2022u, 0x2013u, 0x2014u,
  0x02DCu, 0x2122u, 0xFFFFu, 0x203Au, 0x0153u, 0xFFFFu, 0xFFFFu, 0x0178u,
  0x00A0u, 0x00A1u, 0x00A2u, 0x00A3u, 0x00A4u, 0x00A5u, 0x00A6u, 0x00A7u,
  0x00A8u, 0x00A9u, 0x00AAu, 0x00ABu, 0x00ACu, 0x00ADu, 0x00AEu, 0x00AFu,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x00B4u, 0x00B5u, 0x00B6u, 0x00B7u,
  0x00B8u, 0x00B9u, 0x00BAu, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0x00BFu,
  0x00C0u, 0x00C1u, 0x00C2u, 0x0102u, 0x00C4u, 0x00C5u, 0x00C6u, 0x00C7u,
  0x00C8u, 0x00C9u, 0x00CAu, 0x00CBu, 0x0300u, 0x00CDu, 0x00CEu, 0x00CFu,
  0x0110u, 0x00D1u, 0x0309u, 0x00D3u, 0x00D4u, 0x01A0u, 0x00D6u, 0x00D7u,
  0x00D8u, 0x00D9u, 0x00DAu, 0x00DBu, 0x00DCu, 0x01AFu, 0x0303u, 0x00DFu,
  0x00E0u, 0x00E1u, 0x00E2u, 0x0103u, 0x00E4u, 0x00E5u, 0x00E6u, 0x00E7u,
  0x00E8u, 0x00E9u, 0x00EAu, 0x00EBu, 0x0301u, 0x00EDu, 0x00EEu, 0x00EFu,
  0x0111u, 0x00F1u, 0x0323u, 0x00F3u, 0x00F4u, 0x01A1u, 0x00F6u, 0x00F7u,
  0x00F8u, 0x00F9u, 0x00FAu, 0x00FBu, 0x00FCu, 0x01B0u, 0x20ABu, 0x00FFu,
};


// ->> A UTF-7 shifted run is validated by next(), then delivered one scalar per call.
// The caller must retain the input buffer while state::decoded.text refers to it.
static ::std::size_t unicode_shifted(struct state* const state, bool const imap) /* noexcept */ {
  for (; state->decoded.position < state->decoded.width; ) {
    unsigned const byte = state->decoded.text[state->decoded.position++];
    int const digit = byte >= 'A' and byte <= 'Z' ? static_cast<int>(byte - 'A') :
      byte >= 'a' and byte <= 'z' ? static_cast<int>(byte - 'a' + 26u) :
      byte >= '0' and byte <= '9' ? static_cast<int>(byte - '0' + 52u) :
      byte == '+' ? 62 : byte == (imap ? ',' : '/') ? 63 : -1;
    if (digit < 0) break; // ->> '-' or UTF-7's implicit run terminator
    state->decoded.accumulator = (state->decoded.accumulator << 6) | static_cast<unsigned>(digit);
    state->decoded.bits += 6u;
    if (state->decoded.bits < 16u) continue;
    state->decoded.bits -= 16u;
    unsigned const unit = (state->decoded.accumulator >> state->decoded.bits) & 0xFFFFu;
    state->decoded.accumulator &= (1u << state->decoded.bits) - 1u;
    if (unit >= 0xD800u and unit <= 0xDBFFu) { state->decoded.highSurrogate = unit; continue; }

    ::std::size_t const scalar = state->decoded.highSurrogate ?
      0x10000u + ((state->decoded.highSurrogate - 0xD800u) << 10) + (unit - 0xDC00u) : unit;
    state->decoded.highSurrogate = 0u;
    --state->decoded.remaining;
    state->characters = 1u;
    if (state->decoded.remaining == 0u) {
      state->source.offset += state->decoded.width;
      state->decoded.text = static_cast<unsigned char const*>(NULL);
    }
    return scalar;
  }
  return state::MALFORMED; // ->> Inconsistent UTF-7 parser state
}

// Return one Unicode scalar (U+0000..U+10FFFF), or state::* status.
// NO_CHARACTER denotes a BOM/shift command, not a Unicode scalar; retry at
// the updated offset. UTF-7 can yield multiple scalars while the offset stays
// at the run's beginning; use state until the run has been fully delivered.
// Unsupported legacy mappings are NOT treated as equal-numbered Unicode.
extern "C" ::std::size_t unicode(unsigned char const character[], enum format::encoding const encoding, struct state* const state = NULL) /* noexcept */ {
  if (character == NULL) return state::MALFORMED;
  bool const imap = encoding == format::UTF_7_IMAP;
  if (state != NULL and state->decoded.text != NULL) {
    if (encoding != format::UTF_7 and not imap) return state::UNSUPPORTED;
    return unicode_shifted(state, imap);
  }

  // Restrict byte-mapped encodings to explicitly supplied Unicode mappings.
  // For multibyte legacy formats, only unambiguous ASCII positions are mapped.
  unsigned short const* mapping = static_cast<unsigned short const*>(NULL);
  bool entire = false;
  switch (encoding) {
    case format::HP_ROMAN8: mapping = unicode_HP_ROMAN8; entire = false; break;
    case format::IBM00858: mapping = unicode_IBM00858; entire = false; break;
    case format::IBM01140: mapping = unicode_IBM01140; entire = true; break;
    case format::IBM037: mapping = unicode_IBM037; entire = true; break;
    case format::IBM1026: mapping = unicode_IBM1026; entire = true; break;
    case format::IBM273: mapping = unicode_IBM273; entire = true; break;
    case format::IBM424: mapping = unicode_IBM424; entire = true; break;
    case format::IBM437: mapping = unicode_IBM437; entire = false; break;
    case format::IBM500: mapping = unicode_IBM500; entire = true; break;
    case format::IBM775: mapping = unicode_IBM775; entire = false; break;
    case format::IBM850: mapping = unicode_IBM850; entire = false; break;
    case format::IBM852: mapping = unicode_IBM852; entire = false; break;
    case format::IBM855: mapping = unicode_IBM855; entire = false; break;
    case format::IBM857: mapping = unicode_IBM857; entire = false; break;
    case format::IBM860: mapping = unicode_IBM860; entire = false; break;
    case format::IBM861: mapping = unicode_IBM861; entire = false; break;
    case format::IBM862: mapping = unicode_IBM862; entire = false; break;
    case format::IBM863: mapping = unicode_IBM863; entire = false; break;
    case format::IBM864: mapping = unicode_IBM864; entire = true; break;
    case format::IBM865: mapping = unicode_IBM865; entire = false; break;
    case format::IBM866: mapping = unicode_IBM866; entire = false; break;
    case format::IBM869: mapping = unicode_IBM869; entire = false; break;
    case format::ISO_8859_10: mapping = unicode_ISO_8859_10; entire = false; break;
    case format::ISO_8859_11: mapping = unicode_ISO_8859_11; entire = false; break;
    case format::ISO_8859_13: mapping = unicode_ISO_8859_13; entire = false; break;
    case format::ISO_8859_14: mapping = unicode_ISO_8859_14; entire = false; break;
    case format::ISO_8859_15: mapping = unicode_ISO_8859_15; entire = false; break;
    case format::ISO_8859_16: mapping = unicode_ISO_8859_16; entire = false; break;
    case format::ISO_8859_1_1987: mapping = unicode_ISO_8859_1_1987; entire = false; break;
    case format::ISO_8859_2_1987: mapping = unicode_ISO_8859_2_1987; entire = false; break;
    case format::ISO_8859_3_1988: mapping = unicode_ISO_8859_3_1988; entire = false; break;
    case format::ISO_8859_4_1988: mapping = unicode_ISO_8859_4_1988; entire = false; break;
    case format::ISO_8859_5_1988: mapping = unicode_ISO_8859_5_1988; entire = false; break;
    case format::ISO_8859_6_1987: mapping = unicode_ISO_8859_6_1987; entire = false; break;
    case format::ISO_8859_6_E: mapping = unicode_ISO_8859_6_E; entire = false; break;
    case format::ISO_8859_6_I: mapping = unicode_ISO_8859_6_I; entire = false; break;
    case format::ISO_8859_7_1987: mapping = unicode_ISO_8859_7_1987; entire = false; break;
    case format::ISO_8859_8_1988: mapping = unicode_ISO_8859_8_1988; entire = false; break;
    case format::ISO_8859_8_E: mapping = unicode_ISO_8859_8_E; entire = false; break;
    case format::ISO_8859_8_I: mapping = unicode_ISO_8859_8_I; entire = false; break;
    case format::ISO_8859_9_1989: mapping = unicode_ISO_8859_9_1989; entire = false; break;
    case format::KOI8_R: mapping = unicode_KOI8_R; entire = false; break;
    case format::KOI8_U: mapping = unicode_KOI8_U; entire = false; break;
    case format::KZ_1048: mapping = unicode_KZ_1048; entire = false; break;
    case format::MACINTOSH: mapping = unicode_MACINTOSH; entire = false; break;
    case format::PTCP154: mapping = unicode_PTCP154; entire = false; break;
    case format::TIS_620: mapping = unicode_TIS_620; entire = false; break;
    case format::WINDOWS_1250: mapping = unicode_WINDOWS_1250; entire = false; break;
    case format::WINDOWS_1251: mapping = unicode_WINDOWS_1251; entire = false; break;
    case format::WINDOWS_1252: mapping = unicode_WINDOWS_1252; entire = false; break;
    case format::WINDOWS_1253: mapping = unicode_WINDOWS_1253; entire = false; break;
    case format::WINDOWS_1254: mapping = unicode_WINDOWS_1254; entire = false; break;
    case format::WINDOWS_1255: mapping = unicode_WINDOWS_1255; entire = false; break;
    case format::WINDOWS_1256: mapping = unicode_WINDOWS_1256; entire = false; break;
    case format::WINDOWS_1257: mapping = unicode_WINDOWS_1257; entire = false; break;
    case format::WINDOWS_1258: mapping = unicode_WINDOWS_1258; entire = false; break;
    case format::WINDOWS_874: mapping = unicode_WINDOWS_874; entire = false; break;
    default: break;
  }
  enum policy const mode = format::strategy(encoding);
  bool const unicodeFamily = mode == STRATEGY_FORMAT_UCS_2 or mode == STRATEGY_FORMAT_UCS_4 or
    mode == STRATEGY_FORMAT_UTF_8 or mode == STRATEGY_FORMAT_CESU_8 or
    mode == STRATEGY_FORMAT_UTF_16 or mode == STRATEGY_FORMAT_UTF_16BE or mode == STRATEGY_FORMAT_UTF_16LE or
    mode == STRATEGY_FORMAT_UTF_32 or mode == STRATEGY_FORMAT_UTF_32BE or mode == STRATEGY_FORMAT_UTF_32LE or
    mode == STRATEGY_FORMAT_UTF_7 or mode == STRATEGY_FORMAT_UTF_7_IMAP;
  bool const asciiCompatible = encoding == format::US_ASCII or
    encoding == format::BIG5 or encoding == format::BIG5_HKSCS or encoding == format::CP51932 or
    encoding == format::EUC_JP or encoding == format::EUC_KR or encoding == format::EUC_TW or
    encoding == format::GB18030 or encoding == format::GB2312 or encoding == format::GBK or
    encoding == format::JOHAB or encoding == format::SHIFT_JIS or encoding == format::WINDOWS_31J or
    encoding == format::WINDOWS_949;
  if (mapping == NULL and not unicodeFamily and not asciiCompatible) return state::UNSUPPORTED;
  if (mapping == NULL and asciiCompatible and encoding != format::US_ASCII and character[0] >= 0x80u) return state::UNSUPPORTED;
  if (state != NULL and state->source.length and state->source.offset >= state->source.length) return state::MALFORMED;

  struct state local = {};
  struct state* const cursor = state != NULL ? state : &local;
  ::std::size_t const position = cursor->source.offset;
  enum policy const endianBefore = cursor->endianness;
  ::std::size_t const width = next(character, encoding, cursor);
  if (width >= state::UNSUPPORTED) return width;
  if (cursor->characters == 0u) return state::NO_CHARACTER;
  if (mapping != NULL) {
    unsigned const byte = character[0];
    unsigned const scalar = not entire and byte < 128u ? byte : mapping[entire ? byte : byte - 128u];
    if (scalar == 0xFFFFu) {
      cursor->source.offset = position;
      cursor->characters = 0u;
      cursor->invalids = 1u;
      return state::MALFORMED;
    }
    cursor->characters = 1u;
    return scalar;
  }
  if (asciiCompatible) return character[0];

  switch (mode) {
    case STRATEGY_FORMAT_UCS_2:
    case STRATEGY_FORMAT_UTF_16:
    case STRATEGY_FORMAT_UTF_16BE:
    case STRATEGY_FORMAT_UTF_16LE: {
      bool const little = cursor->endianness != ENDIAN_BIG;
      unsigned const first = little ? static_cast<unsigned>(character[0]) | (static_cast<unsigned>(character[1]) << 8) :
        (static_cast<unsigned>(character[0]) << 8) | character[1];
      if (width == 2u) return first;
      unsigned const second = little ? static_cast<unsigned>(character[2]) | (static_cast<unsigned>(character[3]) << 8) :
        (static_cast<unsigned>(character[2]) << 8) | character[3];
      return 0x10000u + ((first - 0xD800u) << 10) + (second - 0xDC00u);
    }
    case STRATEGY_FORMAT_UCS_4:
    case STRATEGY_FORMAT_UTF_32:
    case STRATEGY_FORMAT_UTF_32BE:
    case STRATEGY_FORMAT_UTF_32LE:
      return cursor->endianness == ENDIAN_BIG ?
        (static_cast< ::std::size_t>(character[0]) << 24) | (static_cast< ::std::size_t>(character[1]) << 16) | (static_cast< ::std::size_t>(character[2]) << 8) | character[3] :
        static_cast< ::std::size_t>(character[0]) | (static_cast< ::std::size_t>(character[1]) << 8) | (static_cast< ::std::size_t>(character[2]) << 16) | (static_cast< ::std::size_t>(character[3]) << 24);
    case STRATEGY_FORMAT_UTF_8:
    case STRATEGY_FORMAT_CESU_8: {
      if (width == 1u) return character[0];
      if (width == 2u) return ((character[0] & 0x1Fu) << 6) | (character[1] & 0x3Fu);
      unsigned const first = ((character[0] & 0x0Fu) << 12) | ((character[1] & 0x3Fu) << 6) | (character[2] & 0x3Fu);
      if (width == 3u) return first;
      if (width == 4u) return ((character[0] & 0x07u) << 18) | ((character[1] & 0x3Fu) << 12) | ((character[2] & 0x3Fu) << 6) | (character[3] & 0x3Fu);
      unsigned const second = ((character[3] & 0x0Fu) << 12) | ((character[4] & 0x3Fu) << 6) | (character[5] & 0x3Fu);
      return 0x10000u + ((first - 0xD800u) << 10) + (second - 0xDC00u);
    }
    case STRATEGY_FORMAT_UTF_7:
    case STRATEGY_FORMAT_UTF_7_IMAP: {
      if (width == 1u) return character[0];
      if (width == 2u and character[1] == '-') return character[0];
      if (state == NULL and cursor->characters > 1u) return state::UNSUPPORTED;
      cursor->decoded.text = character;
      cursor->decoded.width = width;
      cursor->decoded.position = 1u;
      cursor->decoded.remaining = cursor->characters;
      cursor->decoded.accumulator = 0u;
      cursor->decoded.bits = 0u;
      cursor->decoded.highSurrogate = 0u;
      cursor->source.offset = position;
      return unicode_shifted(cursor, imap);
    }
    default: break;
  }
  cursor->endianness = endianBefore;
  return state::UNSUPPORTED;
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

  // Unicode code-point reconstruction, including scalar U+0000 when input is bounded.
  assert(unicode(utf8, format::UTF_8) == 'A');
  assert(unicode(&utf8[1], format::UTF_8) == 0x20ACu);
  unsigned char const utf8Supplementary[] = { 0xF0u, 0x9Fu, 0x98u, 0x80u, 0 };
  assert(unicode(utf8Supplementary, format::UTF_8) == 0x1F600u);
  unsigned char const utf16Supplementary[] = { 0x3Du, 0xD8u, 0x00u, 0xDEu, 0, 0 };
  assert(unicode(utf16Supplementary, format::UTF_16LE) == 0x1F600u);
  unsigned char const utf32Big[] = { 0, 0x01u, 0xF6u, 0, 0, 0, 0, 0 };
  assert(unicode(utf32Big, format::UTF_32BE) == 0x1F600u);
  assert(unicode(cesu8, format::CESU_8) == 0x1F600u);
  assert(unicode(utf8, format::US_ASCII) == 'A');
  assert(unicode(eucJP, format::EUC_JP) == 'A');
  assert(unicode(&eucJP[1], format::EUC_JP) == state::UNSUPPORTED);
  unsigned char const thaiScalar[] = { 0xA1u, 0 };
  assert(unicode(thaiScalar, format::ISO_8859_11) == 0x0E01u);
  unsigned char const euroWindows[] = { 0x80u, 0 };
  assert(unicode(euroWindows, format::WINDOWS_1252) == 0x20ACu);
  unsigned char const eAcuteLatin[] = { 0xE9u, 0 };
  assert(unicode(eAcuteLatin, format::ISO_8859_1_1987) == 0x00E9u);
  unsigned char const asciiNonAscii[] = { 0xE9u, 0 };
  assert(unicode(asciiNonAscii, format::US_ASCII) == state::MALFORMED);
  unsigned char const unknownMapping[] = { 0x80u, 0 };
  assert(unicode(unknownMapping, format::ADOBE_STANDARD_ENCODING) == state::UNSUPPORTED);
  unsigned char const invalidWindows1252[] = { 0x81u, 0 };
  assert(unicode(invalidWindows1252, format::WINDOWS_1252) == state::MALFORMED);
  unsigned char const ebcdicA[] = { 0xC1u, 0 };
  assert(unicode(ebcdicA, format::IBM037) == 'A');
  unsigned char const koi8A[] = { 0xE1u, 0 };
  assert(unicode(koi8A, format::KOI8_R) == 0x0410u);
  unsigned char const macEacute[] = { 0x8Eu, 0 };
  assert(unicode(macEacute, format::MACINTOSH) == 0x00E9u);
  struct state unicodeBom = {};
  unicodeBom.source.length = 8u;
  assert(unicode(withBom, format::UTF_16, &unicodeBom) == state::NO_CHARACTER);
  assert(unicode(&withBom[unicodeBom.source.offset], format::UTF_16, &unicodeBom) == 'A');
  assert(unicode(&withBom[unicodeBom.source.offset], format::UTF_16, &unicodeBom) == 0x1F600u);
  assert(unicodeBom.source.offset == 8u);
  struct state unicodeUnmappable = {};
  unicodeUnmappable.source.length = 1u;
  assert(unicode(invalidWindows1252, format::WINDOWS_1252, &unicodeUnmappable) == state::MALFORMED);
  assert(unicodeUnmappable.source.offset == 0u and unicodeUnmappable.invalids == 1u);
  unsigned char const zeroScalar[] = { 0u, 'A' };
  struct state zeroCursor = {};
  zeroCursor.source.length = 1u;
  assert(unicode(zeroScalar, format::UTF_8, &zeroCursor) == 0u);

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
    // UTF-7 Base64 can represent multiple scalars; don't lose their positions.
    struct state utf7Unicode = {};
    utf7Unicode.source.length = 8u;
    assert(unicode(utf7Pair, format::UTF_7, &utf7Unicode) == 'B');
    assert(utf7Unicode.source.offset == 0u and utf7Unicode.decoded.remaining == 1u);
    assert(unicode(&utf7Pair[utf7Unicode.source.offset], format::UTF_7, &utf7Unicode) == 'C');
    assert(utf7Unicode.source.offset == 8u and utf7Unicode.decoded.text == NULL);
    assert(unicode(utf7Pair, format::UTF_7) == state::UNSUPPORTED);
    assert(unicode(utf7Scalar, format::UTF_7) == 0x1F600u);
    assert(unicode(utf7, format::UTF_7) == 0x20ACu);
    struct state imapUnicode = {};
    imapUnicode.source.length = 13u;
    assert(unicode(imap, format::UTF_7_IMAP, &imapUnicode) == 'A');
    assert(unicode(&imap[imapUnicode.source.offset], format::UTF_7_IMAP, &imapUnicode) == '&');
    assert(unicode(&imap[imapUnicode.source.offset], format::UTF_7_IMAP, &imapUnicode) == 0x00E9u);
    assert(unicode(&imap[imapUnicode.source.offset], format::UTF_7_IMAP, &imapUnicode) == 0x03FFu);
    assert(imapUnicode.source.offset == 13u);
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
