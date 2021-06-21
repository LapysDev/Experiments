#include <cstdio>

/* ... */
struct Color {
    unsigned char const value : 2;
    static Color const RED, GREEN, BLUE;

    Color(unsigned char const value) : value(value) {}
    operator unsigned char(void) const { return this -> value; }
} const Color::RED = 0u, Color::GREEN = 1u, Color::BLUE = 2u;

/* Main */
int main(void) {
    Color const color = Color::BLUE;

    std::printf("[sizeof(Color)]: %lu" "\r\n", static_cast<unsigned long>(sizeof(Color)));
    if (Color::RED   == color) std::puts("RED"  );
    if (Color::GREEN == color) std::puts("GREEN");
    if (Color::BLUE  == color) std::puts("BLUE" );
}
