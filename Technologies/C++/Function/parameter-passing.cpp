/* Import */
#include <iostream> // Input-Output Stream
#include <stdlib.h> // Standard Library

/* Class > Object */
class Object { public:
    // [Constructor]
    constexpr inline Object(void) {}
    constexpr inline Object(Object&) {}
    constexpr inline Object(Object&&) {}
    constexpr inline Object(const Object&) {}
    constexpr inline Object(const Object&&) {}

    // [Operator] > ...
    inline Object& operator =(Object&) noexcept { return *this; }
    inline Object& operator =(Object&&) noexcept { return *this; }
    inline Object& operator =(const Object&) noexcept { return *this; }
    inline Object& operator =(const Object&&) noexcept { return *this; }

    inline operator Object(void) noexcept { return *this; }
    inline operator const Object(void) noexcept { return *this; }

    /* Function > Parse */
    template <typename type> inline static void parse(type*) noexcept { std::cout << "Object [pass-by-address]" << std::endl; }
    template <typename type> inline static void parse(const type*) noexcept { std::cout << "Object [(constant) pass-by-address]" << std::endl; }
    template <typename type> inline static void parse(type&) noexcept { std::cout << "Object [pass-by-reference]" << std::endl; }
    template <typename type> inline static void parse(type&&) noexcept { std::cout << "Object [pass-by-value]" << std::endl; }
};

/* Main */
int main(void) {
    // Global > ...
    char *array;
    const Object constant {};
    Object object {};

    // ...
    Object::parse(object);
    Object::parse(Object());
    Object::parse(&constant);
    Object::parse(&object);

    // Return
    return EXIT_SUCCESS;
}
