/* Import */
#include <cstdarg> // C Standard Arguments
#include <cstdbool> // C Standard Boolean
#include <cstdlib> // C Standard Library
#include <cstdio> // C Standard Input-Output
#include <cuchar> // C Universal Characters
#include <exception> // Exception
#include <iostream> // Input-Output Stream

/* Definition */
    // Arguments To Pointer [Source]
    #define argumentsToPointer_Source(type) \
        va_list arguments; \
        type* pointer = (type*) std::malloc(LENGTH * sizeof(type)); *pointer = (type) argument; \
        \
        va_start(arguments, argument); \
        for (unsigned char iterator = 1; iterator ^ LENGTH; iterator += 1) *(pointer + iterator) = va_arg(arguments, type); \
        va_end(arguments); \
        \
        return pointer;

    // Get Arguments Length( [Expanded])
    #define getArgumentsLength_Expanded(argument0, argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9, argument10, argument11, argument12, argument13, argument14, argument15, argument16, argument17, argument18, argument19, argument20, argument21, argument22, argument23, argument24, argument25, argument26, argument27, argument28, argument29, argument30, argument31, argument32, argument33, argument34, argument35, argument36, argument37, argument38, argument39, argument40, argument41, argument42, argument43, argument44, argument45, argument46, argument47, argument48, argument49, argument50, argument51, argument52, argument53, argument54, argument55, argument56, argument57, argument58, argument59, argument60, argument61, argument62, argument63, argument64, argument65, argument66, argument67, argument68, argument69, argument70, argument71, argument72, argument73, argument74, argument75, argument76, argument77, argument78, argument79, argument80, argument81, argument82, argument83, argument84, argument85, argument86, argument87, argument88, argument89, argument90, argument91, argument92, argument93, argument94, argument95, argument96, argument97, argument98, argument99, argument100, argument101, argument102, argument103, argument104, argument105, argument106, argument107, argument108, argument109, argument110, argument111, argument112, argument113, argument114, argument115, argument116, argument117, argument118, argument119, argument120, argument121, argument122, argument123, argument124, argument125, argument126, argument127, argument128, argument129, argument130, argument131, argument132, argument133, argument134, argument135, argument136, argument137, argument138, argument139, argument140, argument141, argument142, argument143, argument144, argument145, argument146, argument147, argument148, argument149, argument150, argument151, argument152, argument153, argument154, argument155, argument156, argument157, argument158, argument159, argument160, argument161, argument162, argument163, argument164, argument165, argument166, argument167, argument168, argument169, argument170, argument171, argument172, argument173, argument174, argument175, argument176, argument177, argument178, argument179, argument180, argument181, argument182, argument183, argument184, argument185, argument186, argument187, argument188, argument189, argument190, argument191, argument192, argument193, argument194, argument195, argument196, argument197, argument198, argument199, argument200, argument201, argument202, argument203, argument204, argument205, argument206, argument207, argument208, argument209, argument210, argument211, argument212, argument213, argument214, argument215, argument216, argument217, argument218, argument219, argument220, argument221, argument222, argument223, argument224, argument225, argument226, argument227, argument228, argument229, argument230, argument231, argument232, argument233, argument234, argument235, argument236, argument237, argument238, argument239, argument240, argument241, argument242, argument243, argument244, argument245, argument246, argument247, argument248, argument249, argument250, argument251, argument252, argument253, argument254, argument255, argumentsLength, ...) argumentsLength
    #define getArgumentsLength(...) getArgumentsLength_Expanded(argument0, ##__VA_ARGS__, 255u, 254u, 253u, 252u, 251u, 250u, 249u, 248u, 247u, 246u, 245u, 244u, 243u, 242u, 241u, 240u, 239u, 238u, 237u, 236u, 235u, 234u, 233u, 232u, 231u, 230u, 229u, 228u, 227u, 226u, 225u, 224u, 223u, 222u, 221u, 220u, 219u, 218u, 217u, 216u, 215u, 214u, 213u, 212u, 211u, 210u, 209u, 208u, 207u, 206u, 205u, 204u, 203u, 202u, 201u, 200u, 199u, 198u, 197u, 196u, 195u, 194u, 193u, 192u, 191u, 190u, 189u, 188u, 187u, 186u, 185u, 184u, 183u, 182u, 181u, 180u, 179u, 178u, 177u, 176u, 175u, 174u, 173u, 172u, 171u, 170u, 169u, 168u, 167u, 166u, 165u, 164u, 163u, 162u, 161u, 160u, 159u, 158u, 157u, 156u, 155u, 154u, 153u, 152u, 151u, 150u, 149u, 148u, 147u, 146u, 145u, 144u, 143u, 142u, 141u, 140u, 139u, 138u, 137u, 136u, 135u, 134u, 133u, 132u, 131u, 130u, 129u, 128u, 127u, 126u, 125u, 124u, 123u, 122u, 121u, 120u, 119u, 118u, 117u, 116u, 115u, 114u, 113u, 112u, 111u, 110u, 109u, 108u, 107u, 106u, 105u, 104u, 103u, 102u, 101u, 100u, 99u, 98u, 97u, 96u, 95u, 94u, 93u, 92u, 91u, 90u, 89u, 88u, 87u, 86u, 85u, 84u, 83u, 82u, 81u, 80u, 79u, 78u, 77u, 76u, 75u, 74u, 73u, 72u, 71u, 70u, 69u, 68u, 67u, 66u, 65u, 64u, 63u, 62u, 61u, 60u, 59u, 58u, 57u, 56u, 55u, 54u, 53u, 52u, 51u, 50u, 49u, 48u, 47u, 46u, 45u, 44u, 43u, 42u, 41u, 40u, 39u, 38u, 37u, 36u, 35u, 34u, 33u, 32u, 31u, 30u, 29u, 28u, 27u, 26u, 25u, 24u, 23u, 22u, 21u, 20u, 19u, 18u, 17u, 16u, 15u, 14u, 13u, 12u, 11u, 10u, 9u, 8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u)

    // Get Arguments
    #define getArguments(...) ::argumentsToPointer(getArgumentsLength(__VA_ARGS__), __VA_ARGS__)

/* Global > (False, True) */
static const unsigned char False = 0, True = 1;

/* Function */
    // Arguments To Pointer --- MINIFY --- WARN (Lapys) -> Defer to the `getArguments` macro instead.
    static void* argumentsToPointer(const unsigned char LENGTH) { return NULL; }
    static int* argumentsToPointer(const unsigned char LENGTH, int argument, ...) { argumentsToPointer_Source(int); }
    static long double* argumentsToPointer(const unsigned char LENGTH, long double argument, ...) { argumentsToPointer_Source(long double); }
    static long long* argumentsToPointer(const unsigned char LENGTH, long long argument, ...) { argumentsToPointer_Source(long long); }
    static unsigned long long* argumentsToPointer(const unsigned char LENGTH, unsigned long long argument, ...) { argumentsToPointer_Source(unsigned long long); }
    static void** argumentsToPointer(const unsigned char LENGTH, void* argument, ...) { argumentsToPointer_Source(void*); }
    static void** argumentsToPointer(const unsigned char LENGTH, const void* argument, ...) { argumentsToPointer_Source(void*); }

    // Stringify --- WARN (Lapys) -> For pointer conversion, convert the pointer to an integral instead.
    static char* str(char arg) { char* string = (char*) std::malloc(2); *string = arg; *(string + 1) = '\0'; return string; }
    static char* str(double arg) { char* string = (char*) std::malloc(20); std::sprintf(string, "%lf", arg); return string; }
    static char* str(long double arg) { return ::str((double) arg); }
    static char* str(int arg) { char* string = (char*) std::malloc(20); std::sprintf(string, "%d", arg); return string; }
    static char* str(long long arg) { return ::str((int) arg); }
    static char* str(unsigned int arg) { char* string = (char*) std::malloc(20); std::sprintf(string, "%u", arg); return string; }
    static char* str(unsigned long long arg) { return ::str((unsigned int) arg); }
    static char* str(void* arg) { char* string = (char*) std::malloc(10); std::sprintf(string, "%p", arg); return string; }
    static char* str(const void* arg) { return ::str((void*) arg); }

/* Class > ... */
    // Boolean
    struct boolean {
        // [Private]
        private:
            // Initialization > Value
            unsigned char value = 0;

        // [Public]
        public:
            // [Constructor]
            boolean() {}
            boolean(const boolean& argument) {}
    };

    // Array
    struct array {};

    // Number
    struct number {};

    // Object
    struct object {};

    // String
    struct string {};

    // Symbol
    struct symbol {};

/* Main */
int main(int argc, char* argv[]) {
    // Return
    return 0;
}

