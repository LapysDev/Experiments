/* ... -> All features used can be user-defined. */
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <type_traits>

/* ... -> Allow addition to `std` namespace for this demo. */
#ifdef __cplusplus
namespace std {
    #if __cplusplus < 201703L
      // [https://en.cppreference.com/w/cpp/types/result_of#Notes]
      // `std::result_of<...>` seems limited... so a minimal alternative will be applied for now.
      template <typename> struct returnof {};
      template <typename return_t, typename... args_t> struct returnof<return_t (args_t...)> { public: using type = return_t; };
      template <typename return_t, typename... args_t> struct returnof<return_t (&)(args_t...)> { public: using type = return_t; };
      template <typename return_t, typename... args_t> struct returnof<return_t (*)(args_t...)> { public: using type = return_t; };
    #else
      template <typename type>
      using returnof = std::invoke_result<type>;
    #endif
}
#endif

/* ... -> Memory region for directly casted objects (size should be based on type being casted, not fixed). */
static unsigned char BUFFER[1u << 16u];

/* ... */
// : Main implementation.
template <typename return_t, typename cast_t, std::size_t = sizeof(cast_t)>
constexpr return_t direct_cast(cast_t const& value) noexcept {
    typename std::remove_reference<return_t>::type* evaluation = NULL; // -> *(return_t*) ...
    unsigned char *evaluationIterator = static_cast<unsigned char*>(static_cast<void*>(&evaluation));
    unsigned char const *valueIterator = static_cast<unsigned char const*>(static_cast<void const*>(&value));

    for ( // -> Update the `BUFFER` with the memory layout of `value` (on the precision level of bytes).
        unsigned char *bufferIterator = BUFFER;
        static_cast<std::size_t>(bufferIterator - BUFFER) ^ sizeof(value); ++bufferIterator
    ) *bufferIterator = *valueIterator++;

    for ( // -> Set `evaluation` to the updated `BUFFER` (necessary because array & function pointers are different from data pointers).
        std::ptrdiff_t bufferIterator = static_cast<unsigned char*>(static_cast<void*>(BUFFER)) - static_cast<unsigned char*>(NULL);
        bufferIterator; bufferIterator >>= CHAR_BIT * sizeof(unsigned char)
    ) *evaluationIterator++ = bufferIterator & UCHAR_MAX;

    return *evaluation;
}

// : Array-type specific overload.
template <typename return_t, typename cast_t, typename = typename std::enable_if<std::is_array<return_t>::value || std::is_array<typename std::remove_reference<return_t>::type>::value, void>::type>
constexpr typename std::remove_extent<return_t>::type (&direct_cast(cast_t const& value) noexcept)[std::extent<return_t>::value] {
    cast_t const *const address = &value;
    return *direct_cast<typename std::remove_reference<return_t>::type*>(address);
}

// : Function-type specific overload.
template <typename return_t, typename cast_t, typename = typename std::enable_if<std::is_function<return_t>::value || std::is_function<typename std::remove_reference<return_t>::type>::value, void>::type, typename... types>
constexpr typename std::returnof<return_t>::type (&direct_cast(cast_t const& value) noexcept)(types...) {
    cast_t const *const address = &value;
    return *direct_cast<typename std::remove_reference<return_t>::type*>(address);
}

/* ... -> Evaluate the byte layout of `object` as a hexadecimal string sequence. */
template <typename type>
inline char const* layoutof(type const& object) noexcept {
    unsigned char const *const layout = reinterpret_cast<unsigned char const*>(reinterpret_cast<void const*>(&object)), *layoutIterator = layout;
    static char string[3u * sizeof(type)]; char *const stringEnd = string + (sizeof(string) / sizeof(char)), *stringIterator = stringEnd;

    *--stringIterator = '\0';
    while (static_cast<std::size_t>(layoutIterator - layout) < sizeof(object)) {
        if (stringEnd != stringIterator + 1) { *--stringIterator = ' '; }
        *--stringIterator = "0123456789ABCDEF"[*layoutIterator % 0x10u];
        *--stringIterator = "0123456789ABCDEF"[*layoutIterator / 0x10u];

        ++layoutIterator;
    }

    return const_cast<char const*>(string);
}

/* ... -> Objects to --test-- toy around with. */
class Object final { public:
    static bool OBSERVE_OBJECTS;
    char const *name; int time;

    inline Object(char const name[], int const time) noexcept : name{name}, time{time} { OBSERVE_OBJECTS && std::puts("<Object instantiated>"); }
    inline Object(Object const& object) noexcept : name{object.name}, time{object.time} { OBSERVE_OBJECTS && std::puts("<Object reference-instantiated>"); }
    inline Object(Object&& object) noexcept : name{object.name}, time{object.time} { OBSERVE_OBJECTS && std::puts("<Object move-instantiated>"); }

    inline Object& operator =(Object const& object) noexcept { OBSERVE_OBJECTS && std::puts("<Object reference-assigned>"); return this -> name = object.name, this -> time = object.time, *this; }
    inline Object& operator =(Object&& object) noexcept { OBSERVE_OBJECTS && std::puts("<Object move-assigned>"); return this -> name = object.name, this -> time = object.time, *this; }
};

bool Object::OBSERVE_OBJECTS = false;

static std::intmax_t bigInteger;
static int integer = 1337u;
static Object object = Object {"@Lapys", 20u};
static constexpr char const* put(void) { return "<function call>"; }

/* Test */
constexpr inline void TestCompileTime(void) noexcept {
    /* -> Assume it `direct_cast<...>` is compile-time able for now... */
}

inline void TestRunTime(void) noexcept {
    /* [Plain-Old Types] -> Check for fitting & narrowing conversions. */ std::puts("\r");
    bigInteger = direct_cast<std::intmax_t>(static_cast<int>(integer));
    std::printf("[intmax_t          <- int                            ]: (%zi : %i)                    {%s : ", bigInteger, integer, layoutof(bigInteger)), std::printf("%s}" "\r\n", layoutof(integer));

    integer = direct_cast<int>(static_cast<std::intmax_t>(bigInteger));
    std::printf("[int               <- intmax_t                       ]: (%i : %zi)                    {%s : ", integer, bigInteger, layoutof(integer)), std::printf("%s}" "\r\n", layoutof(bigInteger));

    void *const pointer = direct_cast<void*>(static_cast<std::intmax_t>(bigInteger));
    std::printf("[void*             <- intmax_t                       ]: (%p : %zi)        {%s : ", pointer, bigInteger, layoutof(pointer)), std::printf("%s}" "\r\n", layoutof(bigInteger));

    /* [Incompatible Types] -> The "real" test of `direct_cast<...>`. */ std::puts("\r");
    integer = direct_cast<int>(object); {
        Object::OBSERVE_OBJECTS = false;
        std::printf("[int               <- Object&                        ]: (%i : {\"%s\", %i})    {%s : ", integer, object.name, object.time, layoutof(integer)), std::printf("%s}" "\r\n", layoutof(object));
        Object::OBSERVE_OBJECTS = true;
    }

    object = direct_cast<Object>(++integer); {
        Object::OBSERVE_OBJECTS = false;
        std::printf("[Object            <- int& (+ 1)                     ]: ({\"%s\", %i} : %i)     {%s : ", object.name, object.time, integer, layoutof(object)), std::printf("%s}" "\r\n", layoutof(integer));
        Object::OBSERVE_OBJECTS = true;
    }

    /* [Reference Types] -> Are references preserved? */ std::puts("\r");
    int &integerReference = direct_cast<int&>(static_cast<std::intmax_t>(bigInteger));
    std::printf("[int&              <- intmax_t                       ]: (%i : %zi)                    {%s : ", integerReference, bigInteger, layoutof(integerReference)), std::printf("%s}" "\r\n", layoutof(bigInteger));

    Object &objectReference = direct_cast<Object&>((bigInteger = static_cast<std::intmax_t>(reinterpret_cast<std::intptr_t>("Jyrsper"))));
    std::printf("[Object&           <- intmax_t& (= char const[])     ]: ({\"%s\", %i} : %zi)   {%s : ", objectReference.name, objectReference.time, bigInteger, layoutof(objectReference)), std::printf("%s}" "\r\n", layoutof(bigInteger));

    /* [Array Types] -> Edge cases for array types. */ std::puts("\r");
    int (&array)[2] = direct_cast<int[2]>((bigInteger = 420L | (std::intmax_t {69L} << ((CHAR_BIT * sizeof(std::intmax_t) / 2L)))));
    std::printf("[int [2]           <- intmax_t& (= intmax_t)         ]: ([%i, %i] : %zi)       {%s : ", array[0], array[1], bigInteger, layoutof(array)), std::printf("%s}" "\r\n", layoutof(bigInteger));

    int (&arrayReference)[2] = direct_cast<int (&)[2]>(array);
    std::printf("[int (&)[2]        <- int (&)[2]                     ]: ([%i, %i] : [%i, %i])          {%s : ", arrayReference[0], arrayReference[1], array[0], array[1], layoutof(arrayReference)), std::printf("%s}" "\r\n", layoutof(array));

    int (*arrayPointer)[2] = direct_cast<int (*)[2]>(&array);
    std::printf("[int (*)[2]        <- int (*)[2]                     ]: ([%i, %i] : [%i, %i])          {%s : ", (*arrayPointer)[0], (*arrayPointer)[1], array[0], array[1], layoutof(arrayPointer)), std::printf("%s}" "\r\n", layoutof(&array));

    /* [Function Types] -> Edge cases for function types (minimal testing). */ std::puts("\r");
    char const* (*functionPointer)(void) = direct_cast<char const* (*)(void)>((bigInteger = reinterpret_cast<std::intptr_t>(&::put)));
    std::printf("[char const* (*)() <- intmax_t& (= char const* (*)())]: (`%s` : %zi) {%s : ", (*functionPointer)(), bigInteger, layoutof(functionPointer)), std::printf("%s}" "\r\n", layoutof(bigInteger));

    char const* (&functionReference)(void) = direct_cast<char const* (&)(void)>(::put);
    std::printf("[char const* (&)() <- char const* ()                 ]: (`%s`)" "\r\n", functionReference());

    char const* (&function)(void) = direct_cast<char const* (void)>(::put);
    std::printf("[char const* ()    <- char const* ()                 ]: (`%s`)" "\r\n", function());
}

/* Main */
int main(void) {
    Object::OBSERVE_OBJECTS = true, TestRunTime();
    Object::OBSERVE_OBJECTS = true, TestCompileTime();
}
