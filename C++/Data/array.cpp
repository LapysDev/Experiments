#include <cstddef>
#include <cstdio>

/* ... */
template <typename base, std::size_t capacity>
union array {
    private:
        template <typename alias> union mutable_cast              { typedef alias type; };
        template <typename alias> union mutable_cast<alias const> { typedef alias type; };

        template <std::size_t, typename = array<base, true> > union subbase_t;
        template <std::size_t length> union subbase_t<length, array<base, (capacity >= length)> > { typedef base type; };

        typedef base (&base_t)[capacity];

        // ...
        base value[capacity];

        static void destruct(base&) {}
        static void destruct(base& element) { element.~base(); }

    public:
        template <std::size_t length>
        array(typename subbase_t<length>::type (&array)[length]) {
            for (base *iterator = array + length; iterator-- != array; )
            const_cast<typename mutable_cast<base>::type (&)[capacity]>(value)[iterator - array] = *iterator;
        }

        operator base_t(void) const { return this -> value; }
};

/* Main */
int main(void) {
    // array<char const, 14u>("Lorem ipsum");
    // array<char const, 14u>("Hello, World!");
    // array<char const, 14u>("This is a long sentence");
}
