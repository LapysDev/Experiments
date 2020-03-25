/* Import */
#include <iostream> // Input-Output Stream
#include <stdlib.h> // Standard Library

/* Class > Object */
class Object { public:
    // [Constructor]
    constexpr inline Object(void) {}
    constexpr inline Object(Object&) {}
    constexpr inline Object(Object&&) {}
    constexpr inline Object(Object const&) {}
    constexpr inline Object(Object const&&) {}

    // [Operator] > ...
    inline Object& operator =(Object&) noexcept { return *this; }
    inline Object& operator =(Object&&) noexcept { return *this; }
    inline Object& operator =(Object const&) noexcept { return *this; }
    inline Object& operator =(Object const&&) noexcept { return *this; }

    inline operator Object(void) noexcept { return *this; }
    inline operator const Object(void) noexcept { return *this; }

    /* Function > Parse */
    template <typename type> inline static void parse(type*) noexcept { std::cout << "Object [pass-by-address]" << std::endl; }
    template <typename type> inline static void parse(type const*) noexcept { std::cout << "Object [(constant) pass-by-address]" << std::endl; }
    template <typename type> inline static void parse(type&) noexcept { std::cout << "Object [pass-by-reference]" << std::endl; }
    template <typename type> inline static void parse(type&&) noexcept { std::cout << "Object [pass-by-value]" << std::endl; }
};

/* Function > Parse */
void parse(double const, double const) noexcept { std::cout << "double" << std::endl; }
void parse(float const, float const) noexcept { std::cout << "float" << std::endl; }
void parse(int const, int const) noexcept { std::cout << "int" << std::endl; }
void parse(long const, long const) noexcept { std::cout << "long" << std::endl; }
void parse(long double const, long double const) noexcept { std::cout << "long double" << std::endl; }
void parse(long long const, long long const) noexcept { std::cout << "long long" << std::endl; }
void parse(short const, short const) noexcept { std::cout << "short" << std::endl; }
void parse(unsigned int const, unsigned int const) noexcept { std::cout << "unsigned int" << std::endl; }
void parse(unsigned long const, unsigned long const) noexcept { std::cout << "unsigned long" << std::endl; }
void parse(unsigned long long const, unsigned long long const) noexcept { std::cout << "unsigned long long" << std::endl; }
void parse(unsigned short const, unsigned short const) noexcept { std::cout << "unsigned short" << std::endl; }

/* Main */
int main(void) {
    // Global > ...
    const Object constant {};
    Object object {};

    // ...
    Object::parse(object);
    Object::parse(Object());
    Object::parse(&constant);
    Object::parse(&object);

    ::parse(0.0, 0.0);
    ::parse(0.0f, 0.0f);
    ::parse(0, 0);
    ::parse(0L, 0L);
    ::parse(0LL, 0LL);
    ::parse(0.00, 0.00);
    ::parse(0u, 0u);
    ::parse(0uL, 0uL);
    ::parse(0uLL, 0uLL);

    // Return
    return EXIT_SUCCESS;
}
