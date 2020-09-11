#include <iostream>

void foo(int) {}
void bar(int...) {}
void baz(int, ...) {}
void quez(int = 0) {}

int main(void) {
    std::cout.write("[PROGRAM INITIATED]", 20u);
    std::endl(std::cout);

    void (*function)(void) = NULL; { std::boolalpha(std::cout);
        function = (void (*)(void)) foo;
        std::cout << "[function == foo]: " << (function == (void (*)(void)) foo) << std::endl;
        std::cout << "[function == bar]: " << (function == (void (*)(void)) bar) << std::endl;
        std::cout << "[function == baz]: " << (function == (void (*)(void)) baz) << std::endl;
        std::cout << "[function == quez]: " << (function == (void (*)(void)) quez) << std::endl;
        std::endl(std::cout);

        function = (void (*)(void)) bar;
        std::cout << "[function == foo]: " << (function == (void (*)(void)) foo) << std::endl;
        std::cout << "[function == bar]: " << (function == (void (*)(void)) bar) << std::endl;
        std::cout << "[function == baz]: " << (function == (void (*)(void)) baz) << std::endl;
        std::cout << "[function == quez]: " << (function == (void (*)(void)) quez) << std::endl;
        std::endl(std::cout);

        function = (void (*)(void)) baz;
        std::cout << "[function == foo]: " << (function == (void (*)(void)) foo) << std::endl;
        std::cout << "[function == bar]: " << (function == (void (*)(void)) bar) << std::endl;
        std::cout << "[function == baz]: " << (function == (void (*)(void)) baz) << std::endl;
        std::cout << "[function == quez]: " << (function == (void (*)(void)) quez) << std::endl;
        std::endl(std::cout);

        function = (void (*)(void)) quez;
        std::cout << "[function == foo]: " << (function == (void (*)(void)) foo) << std::endl;
        std::cout << "[function == bar]: " << (function == (void (*)(void)) bar) << std::endl;
        std::cout << "[function == baz]: " << (function == (void (*)(void)) baz) << std::endl;
        std::cout << "[function == quez]: " << (function == (void (*)(void)) quez) << std::endl;
    }

    std::cout.write("[PROGRAM TERMINATED]", 20u);
    std::flush(std::cout);
}
