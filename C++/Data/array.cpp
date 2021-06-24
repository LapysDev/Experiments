#if defined(__cplusplus) && __cplusplus > 199711L
#else
#   include <cstdarg>
#endif
#include <cstddef>
#include <cstdio>
#include <new>

/* ... */
namespace {
    template <std::size_t> union assertion;

    template <bool, typename> union enable_t;
    template <typename base > union enable_t<true, base> { typedef base type; };

    template <typename, typename = assertion<sizeof(true)> > struct has_default_constructor         { static bool const value = false; };
    template <typename base> struct has_default_constructor<base, assertion<sizeof(base(), true)> > { static bool const value = true ; };

    template <typename, typename = assertion<sizeof(true)> > struct has_destructor                                      { static bool const value = false; };
    template <typename base> struct has_destructor<base, assertion<sizeof(static_cast<base*>(NULL) -> ~base(), true)> > { static bool const value = true ; };

    template <typename> struct is_trivial                                           { static bool const value = false; };
    template <> struct is_trivial<bool>                                             { static bool const value = true; };
    template <> struct is_trivial<char>                                             { static bool const value = true; };
    template <> struct is_trivial<double>                                           { static bool const value = true; };
    template <> struct is_trivial<float>                                            { static bool const value = true; };
    template <> struct is_trivial<int>                                              { static bool const value = true; };
    template <> struct is_trivial<long>                                             { static bool const value = true; };
    template <> struct is_trivial<long double>                                      { static bool const value = true; };
    template <> struct is_trivial<short>                                            { static bool const value = true; };
    template <> struct is_trivial<signed char>                                      { static bool const value = true; };
    template <> struct is_trivial<unsigned char>                                    { static bool const value = true; };
    template <> struct is_trivial<unsigned int>                                     { static bool const value = true; };
    template <> struct is_trivial<unsigned long>                                    { static bool const value = true; };
    template <> struct is_trivial<unsigned short>                                   { static bool const value = true; };
    template <> struct is_trivial<wchar_t>                                          { static bool const value = true; };
    template <typename type> struct is_trivial<type const>                          { static bool const value = is_trivial<type>::value; };
    template <typename type> struct is_trivial<type const volatile>                 { static bool const value = is_trivial<type>::value; };
    template <typename type> struct is_trivial<type volatile>                       { static bool const value = is_trivial<type>::value; };
    template <typename type> struct is_trivial<type*>                               { static bool const value = true; };
    template <typename type> struct is_trivial<type* const>                         { static bool const value = is_trivial<type*>::value; };
    template <typename type> struct is_trivial<type* const volatile>                { static bool const value = is_trivial<type*>::value; };
    template <typename type> struct is_trivial<type* volatile>                      { static bool const value = is_trivial<type*>::value; };
    template <typename type> struct is_trivial<type []>                             { static bool const value = true; };
    template <typename type, std::size_t length> struct is_trivial<type [length]>   { static bool const value = true; };
    template <typename type> struct is_trivial<type (*)(...)>                       { static bool const value = true; };
    template <typename type, class object> struct is_trivial<type (object::*)(...)> { static bool const value = true; };
    #if defined(__cplusplus) && __cplusplus > 199711L
      template <> struct is_trivial<long long>          { static bool const value = true; };
      template <> struct is_trivial<unsigned long long> { static bool const value = true; };
    #endif

    template <typename base> union to_mutable_t             { typedef base type; };
    template <typename base> union to_mutable_t<base const> { typedef base type; };

    // ...
    template <typename type> static typename enable_t<false == has_destructor<type>::value, void>::type destruct(type&) { /* do nothing... */ }
    template <typename type> static typename enable_t<true  == has_destructor<type>::value, void>::type destruct(typename to_mutable_t<type>::type& object) { object.~type(); }
}

template <typename base, std::size_t capacity>
class array {
    typedef base (&array_t)[capacity];
    typedef typename to_mutable_t<base>::type mutable_t;

    private:
        base value[capacity];

        // ...
        template <typename type>
        typename enable_t<false == is_trivial<type>::value, void>::type initiate(base array[], std::size_t const length, bool const restruct) {
            for (mutable_t
                *iterator = const_cast<mutable_t*>(array) + length,
                *value = const_cast<mutable_t*>(this -> value) + length
            ; array != iterator; ) {
                if (restruct) destruct<base>(*--value);
                new (value -= !restruct) base(*--iterator);
            }
        }

        template <typename type>
        typename enable_t<true == is_trivial<type>::value, void>::type initiate(base array[], std::size_t const length, bool const) {
            for (mutable_t
                *iterator = const_cast<mutable_t*>(array) + length,
                *value = const_cast<mutable_t*>(this -> value) + length
            ; array != iterator; ) *--value = *--iterator;
        }

    public:
        template <std::size_t length> array(typename enable_t<(capacity == length) && false == is_trivial<base>::value, base>::type (&)[length]);
        template <std::size_t length> array(typename enable_t<(capacity == length) && true  == is_trivial<base>::value, base>::type (&)[length]);
        template <std::size_t length> array(typename enable_t<(capacity > length) && false == has_default_constructor<base>::value, base>::type (&)[length]);
        template <std::size_t length> array(typename enable_t<(capacity > length) && true  == has_default_constructor<base>::value, base>::type (&)[length]);
        #if defined(__cplusplus) && __cplusplus > 199711L
            template <typename... types> array(std::size_t const, types&&...);
        #else
            array(std::size_t, ...); // undefined with non-trivial `base`s
        #endif

        // ...
        #if defined(__cplusplus) && __cplusplus > 199711L
            base* begin(void) { return this -> value; }
            base* begin(void) const { return this -> value; }

            base* end(void) { return this -> value + capacity; }
            base* end(void) const { return this -> value + capacity; }
        #endif

        // ...
        operator array_t(void) { return this -> value; }
        operator array_t(void) const { return this -> value; }
};

// ... ->> has to be defined separately
#if defined(__cplusplus) && __cplusplus > 199711L
  template <typename base, std::size_t capacity>
  template <typename... types>
  array<base, capacity>::array(std::size_t const, types&&... arguments) : value{static_cast<base>(static_cast<types&&>(arguments))...} {}
#else
  template <typename base, std::size_t capacity>
  array<base, capacity>::array(std::size_t count, ...) : value() {
    std::va_list arguments;
    va_start(arguments, count);
      for (mutable_t *value = const_cast<mutable_t*>(this -> value); count--; ++value) {
        destruct<base>(*value);
        new (value) base(va_arg(arguments, base));
      }
    va_end(arguments);
  }
#endif

template <typename base, std::size_t capacity>
template <std::size_t length>
    array<base, capacity>::array(typename enable_t<(capacity == length) && false == is_trivial<base>::value, base>::type (&array)[length]) : value(*static_cast<base (*)[capacity]>(&array)) {
    std::puts("[array: assignment initialized (=)]");
}

template <typename base, std::size_t capacity>
template <std::size_t length>
array<base, capacity>::array(typename enable_t<(capacity == length) && true  == is_trivial<base>::value, base>::type (&array)[length]) : value() {
    std::puts("[array: default initialized    (=)]");
    this -> initiate<base>(array, capacity, true);
}

template <typename base, std::size_t capacity>
template <std::size_t length>
array<base, capacity>::array(typename enable_t<(capacity > length) && false == has_default_constructor<base>::value, base>::type (&array)[length]) : value(*static_cast<base (*)[capacity]>(&(this -> value))) {
    std::puts("[array: self initialized       (<)]");
    this -> initiate<base>(array, length, false);
}

template <typename base, std::size_t capacity>
template <std::size_t length>
array<base, capacity>::array(typename enable_t<(capacity > length) && true  == has_default_constructor<base>::value, base>::type (&array)[length]) : value() {
    std::puts("[array: default initialized    (<)]");
    this -> initiate<base>(array, length, true);
}

/* Main */
#include <string>
#include <typeinfo>

struct Integer { Integer(int const value) { std::printf(" {Integer(%i)} ", value); } };
struct Object  { Object (void)            { std::printf(" {Object ( )} ")        ; } };

namespace std { // undefined
    struct type_info_ref {
        private: std::type_info const &value;
        public:
            type_info_ref(std::type_info const& information) : value(information) {}
            operator std::type_info const&(void) const { return this -> value; }
    };
}

int main(void) {
    char const         characters [ ] = "Hello";
    std::type_info_ref information[1] = {typeid(int)};
    Integer            integers   [1] = {Integer(2)};
    Object             objects    [1] = {Object ( )};
    std::string        strings    [1] = {};

    // ...
    std::puts("\r\n");
    array<char const        , 6u> const A1 ((std::printf("char const        : "), characters));
    array<char const        , 7u> const A2 ((std::printf("char const        : "), characters));

    array<Integer           , 1u> const B1 ((std::printf("Integer           : "), integers));
    array<Integer           , 2u> const B2 ((std::printf("Integer           : "), integers));

    array<Object            , 1u> const C1 ((std::printf("Object            : "), objects));
    array<Object            , 2u> const C2 ((std::printf("Object            : "), objects));

    array<std::type_info_ref, 1u> const D1 ((std::printf("std::type_info_ref: "), information));
    array<std::type_info_ref, 2u> const D2 ((std::printf("std::type_info_ref: "), information));

    array<std::string       , 1u> const E1 ((std::printf("std::string       : "), strings));
    array<std::string       , 2u> const E2 ((std::printf("std::string       : "), strings));

    // ...
    std::puts("\r\n");
    static_cast<void>(A1); static_cast<void>(A2);
    static_cast<void>(B1); static_cast<void>(B2);
    static_cast<void>(C1); static_cast<void>(C2);
    static_cast<void>(D1); static_cast<void>(D2);
    static_cast<void>(E1); static_cast<void>(E2);

    /* ... */
    array<int, 10u> progressionA = array<int, 10u>(10u, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    array<int, 10u> progressionB = array<int, 10u>(10u, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    array<int, 10u> progressionC = array<int, 10u>(10u, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

    std::printf("%56s", "[array<int, 10> : iteration via range-based for loop]: {");
    #if defined(__cplusplus) && __cplusplus > 199711L
      for (int& element : progressionA) element *= 2;
      for (int  element : progressionA) std::printf("%i%2s", element, ", ");
    #else
      static_cast<void>(progressionA);
    #endif
    std::printf("%3s", "}" "\r\n");

    std::printf("%56s", "[array<int, 10> : iteration via indexes]             : {");
      for (std::size_t index = 0u; index != 10u; ++index) progressionB[index] *= 2;
      for (std::size_t index = 0u; index != 10u; ++index) std::printf("%i%.2s", progressionB[index], index == 9u ? "" : ", ");
    std::printf("%3s", "}" "\r\n");

    std::printf("%56s", "[array<int, 10> : iteration via pointers]            : {");
      for (int *iterator = progressionC; 10 != (iterator - progressionC); ++iterator) *iterator *= 2;
      for (int *iterator = progressionC; 10 != (iterator - progressionC); ++iterator) std::printf("%i%.2s", *iterator, 9L == iterator - progressionC ? "" : ", ");
    std::printf("%3s", "}" "\r\n");
}
