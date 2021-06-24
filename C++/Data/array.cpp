#include <cstddef>
#include <cstdio>
#include <new>

/* ... */
template <typename base, std::size_t capacity>
struct array {
    private:
        typedef base (&array_t)[capacity];
        template <std::size_t> union assertion;

        template <bool, typename> union conditional_t;
        template <typename alias> union conditional_t<true, alias> { typedef alias type; };

        template <typename, typename = assertion<sizeof(bool)> > struct has_default_constructor { static bool const value = false; };
        template <typename alias> struct has_default_constructor<alias, assertion<sizeof(alias(), false)> > { static bool const value = true; };

        template <typename, typename = assertion<sizeof(bool)> > struct has_destructor { static bool const value = false; };
        template <typename alias> struct has_destructor<alias, assertion<sizeof(static_cast<alias*>(NULL) -> ~alias(), false)> > { static bool const value = true; };

        template <typename alias> union mutable_cast              { typedef alias type; };
        template <typename alias> union mutable_cast<alias const> { typedef alias type; };

        template <std::size_t, typename = assertion<true> > union subbase;
        template <std::size_t length> union subbase<length, assertion<(capacity > length)> > { typedef base type; };

        // ...
        base value[capacity];

        template <typename type> static typename conditional_t<false == has_destructor<type>::value, void>::type destruct(typename mutable_cast<type>::type&) {}
        template <typename type> static typename conditional_t<true  == has_destructor<type>::value, void>::type destruct(typename mutable_cast<type>::type& element) { element.~base(); }

    public:
        array(base (&array)[capacity]) : value(array) {}

        template <std::size_t length>
        array(typename conditional_t<true  == has_default_constructor<base>::value, typename subbase<length>::type >::type (&)[length]) : value() {
            std::puts("[default-initialized]");
        }

        template <std::size_t length>
        array(typename conditional_t<false == has_default_constructor<base>::value, typename subbase<length>::type >::type (&)[length]) : value(*static_cast<base (*)[capacity]>(&value)) {
            std::puts("[self-initialized]");
            // typename subbase<length>   ::type *iterator = array + length;
            // typename mutable_cast<base>::type *value    = const_cast<typename mutable_cast<base>::type*>(this -> value) + length;

            // for (--value; array != iterator; --value) {
            //     array::destruct<base>(*value);
            //     new (value) base(*--iterator);
            // }

            /* ... */
            // for (base *iterator = array + length; iterator-- != array; )
            // new (const_cast<typename mutable_cast<base>::type*>(this -> value + (iterator - array))) base(*iterator);
        }

        // ...
        operator array_t(void) const { return const_cast<array_t>(this -> value); }
};

/* Main */
struct Object {
    Object(int) {}
};

#include <string>
int main(void) {
    char const characters[1] = "";
    Object        objects[1] = {Object(0x45)};
    std::string   strings[1] = {std::string()};

    array<char const , 5u> a(characters);
    array<Object     , 5u> b   (objects);
    array<std::string, 5u> c   (strings);

    static_cast<void>(a);
    static_cast<void>(b);
    static_cast<void>(c);

    // array<char const, 14u>("Lorem ipsum");
    // array<char const, 14u>("Hello, World!");
    // array<char const, 14u>("This is a long sentence");

    // std::string objectsA[3] = {std::string(), std::string(), std::string()};
    // std::string objectsB[2] = {std::string(), std::string()};

    // array<std::string, 3u> arrayA = array<std::string, 3u>(objectsA);
    // std::puts("BEFORE...");
    // array<std::string, 3u> arrayB = array<std::string, 3u>(objectsB);
    // std::puts("...AFTER");

    // std::string& object = arrayA[0];

    // static_cast<void>(arrayA);
    // static_cast<void>(arrayB);
    // static_cast<void>(object);

    // std::printf("[]: \"%s\"" "\r\n", static_cast<char const (&)[14]>(array<char const, 14u>("Lorem ipsum")));
    // std::printf("[]: \"%s\"" "\r\n", static_cast<char const (&)[14]>(array<char const, 14u>("Hello, World!")));
}
