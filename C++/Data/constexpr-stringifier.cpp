#include <cstdio>

/* ... */
#define concatenate(argument1, argument2) argument1 ## argument2
#define defer(macro, ...) macro(__VA_ARGS__)
#define first(argument, ...) argument
#define second(argument1, argument2, ...) argument2

#define empty() pass
#define select(argument, ...) defer(concatenate, select_, defer(second, select_check_ ## argument, fail, ~))(argument)
# define select_fail(argument) empty
# define select_pass(argument) repeat_niladic_check
#   define select_check_until ~, pass

#define repeat(...) repeat_parse(repeat_begin(__VA_ARGS__, until, ~))
# define repeat_arity_fail(...)
# define repeat_arity_pass(...) __VA_ARGS__
# define repeat_begin(function, condition, separator, argument, ...) \
  "(continue" ":" #argument ")" " " \
  repeat_check(repeat_arity_, condition(argument, __VA_ARGS__)())(repeat_stall(repeat_recurse)()(function, condition, separator, __VA_ARGS__, ~))
# define repeat_check(prefix, suffix) defer(concatenate, prefix, defer(second, concatenate(repeat_check_, suffix), pass, ~))
#   define repeat_check_fail ~, fail
#   define repeat_check_pass
# define repeat_niladic_check() fail
# define repeat_parse(...) repeat_parse_12(__VA_ARGS__)
#   define repeat_parse_1(...) __VA_ARGS__
#   define repeat_parse_2(...) repeat_parse_1(repeat_parse_1(__VA_ARGS__))
#   define repeat_parse_3(...) repeat_parse_2(repeat_parse_2(__VA_ARGS__))
#   define repeat_parse_4(...) repeat_parse_3(repeat_parse_3(__VA_ARGS__))
#   define repeat_parse_5(...) repeat_parse_4(repeat_parse_4(__VA_ARGS__))
#   define repeat_parse_6(...) repeat_parse_5(repeat_parse_5(__VA_ARGS__))
#   define repeat_parse_7(...) repeat_parse_6(repeat_parse_6(__VA_ARGS__))
#   define repeat_parse_8(...) repeat_parse_7(repeat_parse_7(__VA_ARGS__))
#   define repeat_parse_9(...) repeat_parse_8(repeat_parse_8(__VA_ARGS__))
#   define repeat_parse_10(...) repeat_parse_9(repeat_parse_9(__VA_ARGS__))
#   define repeat_parse_11(...) repeat_parse_10(repeat_parse_10(__VA_ARGS__))
#   define repeat_parse_12(...) repeat_parse_11(repeat_parse_11(__VA_ARGS__))
# define repeat_stall(argument) repeat_stall_12(argument)
# define repeat_stall_null()
#   define repeat_stall_1(argument) argument repeat_stall_null()
#   define repeat_stall_2(argument) argument repeat_stall_null repeat_stall_null()()
#   define repeat_stall_3(argument) argument repeat_stall_null repeat_stall_null repeat_stall_null()()()
#   define repeat_stall_4(argument) argument repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null()()()()
#   define repeat_stall_5(argument) argument repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null()()()()()
#   define repeat_stall_6(argument) argument repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null()()()()()()
#   define repeat_stall_7(argument) argument repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null()()()()()()()
#   define repeat_stall_8(argument) argument repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null()()()()()()()()
#   define repeat_stall_9(argument) argument repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null()()()()()()()()()
#   define repeat_stall_10(argument) argument repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null()()()()()()()()()()
#   define repeat_stall_11(argument) argument repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null()()()()()()()()()()()
#   define repeat_stall_12(argument) argument repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null repeat_stall_null()()()()()()()()()()()()
# define repeat_recurse() repeat_begin

#define arity(count) defer(concatenate, arity_, defer(second, arity_check_ ## count, invalid, ~))(count)
# define arity_invalid(count)
# define arity_valid(count) concatenate(arity_, count)
#   define arity_0
#   define arity_1 1
#   define arity_2 2, arity_1
#   define arity_3 3, arity_2
#   define arity_4 4, arity_3
#   define arity_5 5, arity_4
#   define arity_6 6, arity_5
#   define arity_7 7, arity_6
#   define arity_8 8, arity_7
#   define arity_9 9, arity_8
#   define arity_10 10, arity_9
#   define arity_11 11, arity_10
#   define arity_12 12, arity_11
#   define arity_13 13, arity_12
#   define arity_14 14, arity_13
#   define arity_15 15, arity_14
#   define arity_16 16, arity_15
#   define arity_17 17, arity_16
#   define arity_18 18, arity_17
#   define arity_19 19, arity_18
#   define arity_20 20, arity_19
#   define arity_21 21, arity_20
#   define arity_22 22, arity_21
#   define arity_23 23, arity_22
#   define arity_24 24, arity_23
#   define arity_25 25, arity_24
#   define arity_26 26, arity_25
#   define arity_27 27, arity_26
#   define arity_28 28, arity_27
#   define arity_29 29, arity_28
#   define arity_30 30, arity_29
#   define arity_31 31, arity_30
#   define arity_32 32, arity_31
#   define arity_33 33, arity_32
#   define arity_34 34, arity_33
#   define arity_35 35, arity_34
#   define arity_36 36, arity_35
#   define arity_37 37, arity_36
#   define arity_38 38, arity_37
#   define arity_39 39, arity_38
#   define arity_40 40, arity_39
#   define arity_41 41, arity_40
#   define arity_42 42, arity_41
#   define arity_43 43, arity_42
#   define arity_44 44, arity_43
#   define arity_45 45, arity_44
#   define arity_46 46, arity_45
#   define arity_47 47, arity_46
#   define arity_48 48, arity_47
#   define arity_49 49, arity_48
#   define arity_50 50, arity_49
#   define arity_51 51, arity_50
#   define arity_52 52, arity_51
#   define arity_53 53, arity_52
#   define arity_54 54, arity_53
#   define arity_55 55, arity_54
#   define arity_56 56, arity_55
#   define arity_57 57, arity_56
#   define arity_58 58, arity_57
#   define arity_59 59, arity_58
#   define arity_60 60, arity_59
#   define arity_61 61, arity_60
#   define arity_62 62, arity_61
#   define arity_63 63, arity_62
#   define arity_64 64, arity_63
#   define arity_65 65, arity_64
#   define arity_66 66, arity_65
#   define arity_67 67, arity_66
#   define arity_68 68, arity_67
#   define arity_69 69, arity_68
#   define arity_70 70, arity_69
#   define arity_71 71, arity_70
#   define arity_72 72, arity_71
#   define arity_73 73, arity_72
#   define arity_74 74, arity_73
#   define arity_75 75, arity_74
#   define arity_76 76, arity_75
#   define arity_77 77, arity_76
#   define arity_78 78, arity_77
#   define arity_79 79, arity_78
#   define arity_80 80, arity_79
#   define arity_81 81, arity_80
#   define arity_82 82, arity_81
#   define arity_83 83, arity_82
#   define arity_84 84, arity_83
#   define arity_85 85, arity_84
#   define arity_86 86, arity_85
#   define arity_87 87, arity_86
#   define arity_88 88, arity_87
#   define arity_89 89, arity_88
#   define arity_90 90, arity_89
#   define arity_91 91, arity_90
#   define arity_92 92, arity_91
#   define arity_93 93, arity_92
#   define arity_94 94, arity_93
#   define arity_95 95, arity_94
#   define arity_96 96, arity_95
#   define arity_97 97, arity_96
#   define arity_98 98, arity_97
#   define arity_99 99, arity_98
#   define arity_100 100, arity_99
#   define arity_101 101, arity_100
#   define arity_102 102, arity_101
#   define arity_103 103, arity_102
#   define arity_104 104, arity_103
#   define arity_105 105, arity_104
#   define arity_106 106, arity_105
#   define arity_107 107, arity_106
#   define arity_108 108, arity_107
#   define arity_109 109, arity_108
#   define arity_110 110, arity_109
#   define arity_111 111, arity_110
#   define arity_112 112, arity_111
#   define arity_113 113, arity_112
#   define arity_114 114, arity_113
#   define arity_115 115, arity_114
#   define arity_116 116, arity_115
#   define arity_117 117, arity_116
#   define arity_118 118, arity_117
#   define arity_119 119, arity_118
#   define arity_120 120, arity_119
#   define arity_121 121, arity_120
#   define arity_122 122, arity_121
#   define arity_123 123, arity_122
#   define arity_124 124, arity_123
#   define arity_125 125, arity_124
#   define arity_126 126, arity_125
#   define arity_127 127, arity_126
#   define arity_128 128, arity_127
#   define arity_129 129, arity_128
#   define arity_130 130, arity_129
#   define arity_131 131, arity_130
#   define arity_132 132, arity_131
#   define arity_133 133, arity_132
#   define arity_134 134, arity_133
#   define arity_135 135, arity_134
#   define arity_136 136, arity_135
#   define arity_137 137, arity_136
#   define arity_138 138, arity_137
#   define arity_139 139, arity_138
#   define arity_140 140, arity_139
#   define arity_141 141, arity_140
#   define arity_142 142, arity_141
#   define arity_143 143, arity_142
#   define arity_144 144, arity_143
#   define arity_145 145, arity_144
#   define arity_146 146, arity_145
#   define arity_147 147, arity_146
#   define arity_148 148, arity_147
#   define arity_149 149, arity_148
#   define arity_150 150, arity_149
#   define arity_151 151, arity_150
#   define arity_152 152, arity_151
#   define arity_153 153, arity_152
#   define arity_154 154, arity_153
#   define arity_155 155, arity_154
#   define arity_156 156, arity_155
#   define arity_157 157, arity_156
#   define arity_158 158, arity_157
#   define arity_159 159, arity_158
#   define arity_160 160, arity_159
#   define arity_161 161, arity_160
#   define arity_162 162, arity_161
#   define arity_163 163, arity_162
#   define arity_164 164, arity_163
#   define arity_165 165, arity_164
#   define arity_166 166, arity_165
#   define arity_167 167, arity_166
#   define arity_168 168, arity_167
#   define arity_169 169, arity_168
#   define arity_170 170, arity_169
#   define arity_171 171, arity_170
#   define arity_172 172, arity_171
#   define arity_173 173, arity_172
#   define arity_174 174, arity_173
#   define arity_175 175, arity_174
#   define arity_176 176, arity_175
#   define arity_177 177, arity_176
#   define arity_178 178, arity_177
#   define arity_179 179, arity_178
#   define arity_180 180, arity_179
#   define arity_181 181, arity_180
#   define arity_182 182, arity_181
#   define arity_183 183, arity_182
#   define arity_184 184, arity_183
#   define arity_185 185, arity_184
#   define arity_186 186, arity_185
#   define arity_187 187, arity_186
#   define arity_188 188, arity_187
#   define arity_189 189, arity_188
#   define arity_190 190, arity_189
#   define arity_191 191, arity_190
#   define arity_192 192, arity_191
#   define arity_193 193, arity_192
#   define arity_194 194, arity_193
#   define arity_195 195, arity_194
#   define arity_196 196, arity_195
#   define arity_197 197, arity_196
#   define arity_198 198, arity_197
#   define arity_199 199, arity_198
#   define arity_200 200, arity_199
#   define arity_201 201, arity_200
#   define arity_202 202, arity_201
#   define arity_203 203, arity_202
#   define arity_204 204, arity_203
#   define arity_205 205, arity_204
#   define arity_206 206, arity_205
#   define arity_207 207, arity_206
#   define arity_208 208, arity_207
#   define arity_209 209, arity_208
#   define arity_210 210, arity_209
#   define arity_211 211, arity_210
#   define arity_212 212, arity_211
#   define arity_213 213, arity_212
#   define arity_214 214, arity_213
#   define arity_215 215, arity_214
#   define arity_216 216, arity_215
#   define arity_217 217, arity_216
#   define arity_218 218, arity_217
#   define arity_219 219, arity_218
#   define arity_220 220, arity_219
#   define arity_221 221, arity_220
#   define arity_222 222, arity_221
#   define arity_223 223, arity_222
#   define arity_224 224, arity_223
#   define arity_225 225, arity_224
#   define arity_226 226, arity_225
#   define arity_227 227, arity_226
#   define arity_228 228, arity_227
#   define arity_229 229, arity_228
#   define arity_230 230, arity_229
#   define arity_231 231, arity_230
#   define arity_232 232, arity_231
#   define arity_233 233, arity_232
#   define arity_234 234, arity_233
#   define arity_235 235, arity_234
#   define arity_236 236, arity_235
#   define arity_237 237, arity_236
#   define arity_238 238, arity_237
#   define arity_239 239, arity_238
#   define arity_240 240, arity_239
#   define arity_241 241, arity_240
#   define arity_242 242, arity_241
#   define arity_243 243, arity_242
#   define arity_244 244, arity_243
#   define arity_245 245, arity_244
#   define arity_246 246, arity_245
#   define arity_247 247, arity_246
#   define arity_248 248, arity_247
#   define arity_249 249, arity_248
#   define arity_250 250, arity_249
#   define arity_251 251, arity_250
#   define arity_252 252, arity_251
#   define arity_253 253, arity_252
#   define arity_254 254, arity_253
#   define arity_255 255, arity_254

#   define arity_check_1 ~, valid
#   define arity_check_2 ~, valid
#   define arity_check_3 ~, valid
#   define arity_check_4 ~, valid
#   define arity_check_5 ~, valid
#   define arity_check_6 ~, valid
#   define arity_check_7 ~, valid
#   define arity_check_8 ~, valid
#   define arity_check_9 ~, valid
#   define arity_check_10 ~, valid
#   define arity_check_11 ~, valid
#   define arity_check_12 ~, valid
#   define arity_check_13 ~, valid
#   define arity_check_14 ~, valid
#   define arity_check_15 ~, valid
#   define arity_check_16 ~, valid
#   define arity_check_17 ~, valid
#   define arity_check_18 ~, valid
#   define arity_check_19 ~, valid
#   define arity_check_20 ~, valid
#   define arity_check_21 ~, valid
#   define arity_check_22 ~, valid
#   define arity_check_23 ~, valid
#   define arity_check_24 ~, valid
#   define arity_check_25 ~, valid
#   define arity_check_26 ~, valid
#   define arity_check_27 ~, valid
#   define arity_check_28 ~, valid
#   define arity_check_29 ~, valid
#   define arity_check_30 ~, valid
#   define arity_check_31 ~, valid
#   define arity_check_32 ~, valid
#   define arity_check_33 ~, valid
#   define arity_check_34 ~, valid
#   define arity_check_35 ~, valid
#   define arity_check_36 ~, valid
#   define arity_check_37 ~, valid
#   define arity_check_38 ~, valid
#   define arity_check_39 ~, valid
#   define arity_check_40 ~, valid
#   define arity_check_41 ~, valid
#   define arity_check_42 ~, valid
#   define arity_check_43 ~, valid
#   define arity_check_44 ~, valid
#   define arity_check_45 ~, valid
#   define arity_check_46 ~, valid
#   define arity_check_47 ~, valid
#   define arity_check_48 ~, valid
#   define arity_check_49 ~, valid
#   define arity_check_50 ~, valid
#   define arity_check_51 ~, valid
#   define arity_check_52 ~, valid
#   define arity_check_53 ~, valid
#   define arity_check_54 ~, valid
#   define arity_check_55 ~, valid
#   define arity_check_56 ~, valid
#   define arity_check_57 ~, valid
#   define arity_check_58 ~, valid
#   define arity_check_59 ~, valid
#   define arity_check_60 ~, valid
#   define arity_check_61 ~, valid
#   define arity_check_62 ~, valid
#   define arity_check_63 ~, valid
#   define arity_check_64 ~, valid
#   define arity_check_65 ~, valid
#   define arity_check_66 ~, valid
#   define arity_check_67 ~, valid
#   define arity_check_68 ~, valid
#   define arity_check_69 ~, valid
#   define arity_check_70 ~, valid
#   define arity_check_71 ~, valid
#   define arity_check_72 ~, valid
#   define arity_check_73 ~, valid
#   define arity_check_74 ~, valid
#   define arity_check_75 ~, valid
#   define arity_check_76 ~, valid
#   define arity_check_77 ~, valid
#   define arity_check_78 ~, valid
#   define arity_check_79 ~, valid
#   define arity_check_80 ~, valid
#   define arity_check_81 ~, valid
#   define arity_check_82 ~, valid
#   define arity_check_83 ~, valid
#   define arity_check_84 ~, valid
#   define arity_check_85 ~, valid
#   define arity_check_86 ~, valid
#   define arity_check_87 ~, valid
#   define arity_check_88 ~, valid
#   define arity_check_89 ~, valid
#   define arity_check_90 ~, valid
#   define arity_check_91 ~, valid
#   define arity_check_92 ~, valid
#   define arity_check_93 ~, valid
#   define arity_check_94 ~, valid
#   define arity_check_95 ~, valid
#   define arity_check_96 ~, valid
#   define arity_check_97 ~, valid
#   define arity_check_98 ~, valid
#   define arity_check_99 ~, valid
#   define arity_check_100 ~, valid
#   define arity_check_101 ~, valid
#   define arity_check_102 ~, valid
#   define arity_check_103 ~, valid
#   define arity_check_104 ~, valid
#   define arity_check_105 ~, valid
#   define arity_check_106 ~, valid
#   define arity_check_107 ~, valid
#   define arity_check_108 ~, valid
#   define arity_check_109 ~, valid
#   define arity_check_110 ~, valid
#   define arity_check_111 ~, valid
#   define arity_check_112 ~, valid
#   define arity_check_113 ~, valid
#   define arity_check_114 ~, valid
#   define arity_check_115 ~, valid
#   define arity_check_116 ~, valid
#   define arity_check_117 ~, valid
#   define arity_check_118 ~, valid
#   define arity_check_119 ~, valid
#   define arity_check_120 ~, valid
#   define arity_check_121 ~, valid
#   define arity_check_122 ~, valid
#   define arity_check_123 ~, valid
#   define arity_check_124 ~, valid
#   define arity_check_125 ~, valid
#   define arity_check_126 ~, valid
#   define arity_check_127 ~, valid
#   define arity_check_128 ~, valid
#   define arity_check_129 ~, valid
#   define arity_check_130 ~, valid
#   define arity_check_131 ~, valid
#   define arity_check_132 ~, valid
#   define arity_check_133 ~, valid
#   define arity_check_134 ~, valid
#   define arity_check_135 ~, valid
#   define arity_check_136 ~, valid
#   define arity_check_137 ~, valid
#   define arity_check_138 ~, valid
#   define arity_check_139 ~, valid
#   define arity_check_140 ~, valid
#   define arity_check_141 ~, valid
#   define arity_check_142 ~, valid
#   define arity_check_143 ~, valid
#   define arity_check_144 ~, valid
#   define arity_check_145 ~, valid
#   define arity_check_146 ~, valid
#   define arity_check_147 ~, valid
#   define arity_check_148 ~, valid
#   define arity_check_149 ~, valid
#   define arity_check_150 ~, valid
#   define arity_check_151 ~, valid
#   define arity_check_152 ~, valid
#   define arity_check_153 ~, valid
#   define arity_check_154 ~, valid
#   define arity_check_155 ~, valid
#   define arity_check_156 ~, valid
#   define arity_check_157 ~, valid
#   define arity_check_158 ~, valid
#   define arity_check_159 ~, valid
#   define arity_check_160 ~, valid
#   define arity_check_161 ~, valid
#   define arity_check_162 ~, valid
#   define arity_check_163 ~, valid
#   define arity_check_164 ~, valid
#   define arity_check_165 ~, valid
#   define arity_check_166 ~, valid
#   define arity_check_167 ~, valid
#   define arity_check_168 ~, valid
#   define arity_check_169 ~, valid
#   define arity_check_170 ~, valid
#   define arity_check_171 ~, valid
#   define arity_check_172 ~, valid
#   define arity_check_173 ~, valid
#   define arity_check_174 ~, valid
#   define arity_check_175 ~, valid
#   define arity_check_176 ~, valid
#   define arity_check_177 ~, valid
#   define arity_check_178 ~, valid
#   define arity_check_179 ~, valid
#   define arity_check_180 ~, valid
#   define arity_check_181 ~, valid
#   define arity_check_182 ~, valid
#   define arity_check_183 ~, valid
#   define arity_check_184 ~, valid
#   define arity_check_185 ~, valid
#   define arity_check_186 ~, valid
#   define arity_check_187 ~, valid
#   define arity_check_188 ~, valid
#   define arity_check_189 ~, valid
#   define arity_check_190 ~, valid
#   define arity_check_191 ~, valid
#   define arity_check_192 ~, valid
#   define arity_check_193 ~, valid
#   define arity_check_194 ~, valid
#   define arity_check_195 ~, valid
#   define arity_check_196 ~, valid
#   define arity_check_197 ~, valid
#   define arity_check_198 ~, valid
#   define arity_check_199 ~, valid
#   define arity_check_200 ~, valid
#   define arity_check_201 ~, valid
#   define arity_check_202 ~, valid
#   define arity_check_203 ~, valid
#   define arity_check_204 ~, valid
#   define arity_check_205 ~, valid
#   define arity_check_206 ~, valid
#   define arity_check_207 ~, valid
#   define arity_check_208 ~, valid
#   define arity_check_209 ~, valid
#   define arity_check_210 ~, valid
#   define arity_check_211 ~, valid
#   define arity_check_212 ~, valid
#   define arity_check_213 ~, valid
#   define arity_check_214 ~, valid
#   define arity_check_215 ~, valid
#   define arity_check_216 ~, valid
#   define arity_check_217 ~, valid
#   define arity_check_218 ~, valid
#   define arity_check_219 ~, valid
#   define arity_check_220 ~, valid
#   define arity_check_221 ~, valid
#   define arity_check_222 ~, valid
#   define arity_check_223 ~, valid
#   define arity_check_224 ~, valid
#   define arity_check_225 ~, valid
#   define arity_check_226 ~, valid
#   define arity_check_227 ~, valid
#   define arity_check_228 ~, valid
#   define arity_check_229 ~, valid
#   define arity_check_230 ~, valid
#   define arity_check_231 ~, valid
#   define arity_check_232 ~, valid
#   define arity_check_233 ~, valid
#   define arity_check_234 ~, valid
#   define arity_check_235 ~, valid
#   define arity_check_236 ~, valid
#   define arity_check_237 ~, valid
#   define arity_check_238 ~, valid
#   define arity_check_239 ~, valid
#   define arity_check_240 ~, valid
#   define arity_check_241 ~, valid
#   define arity_check_242 ~, valid
#   define arity_check_243 ~, valid
#   define arity_check_244 ~, valid
#   define arity_check_245 ~, valid
#   define arity_check_246 ~, valid
#   define arity_check_247 ~, valid
#   define arity_check_248 ~, valid
#   define arity_check_249 ~, valid
#   define arity_check_250 ~, valid
#   define arity_check_251 ~, valid
#   define arity_check_252 ~, valid
#   define arity_check_253 ~, valid
#   define arity_check_254 ~, valid
#   define arity_check_255 ~, valid

/* Main */
#define pass(sus) "continue" " "
#define add(...)

int main() {
  std::puts(repeat(pass, select, add));
  std::puts(repeat(pass, select, add, arity(1)));
  std::puts(repeat(pass, select, add, arity(2)));
  std::puts(repeat(pass, select, add, arity(3)));
  std::puts(repeat(pass, select, add, arity(4)));
  std::puts(repeat(pass, select, add, arity(255)));
}
