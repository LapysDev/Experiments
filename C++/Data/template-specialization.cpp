#include <iostream>

template<bool B, class T = void> struct enable_if {};
template<class T> struct enable_if<true, T> { typedef T type; };

template <int value, typename enable_if<0 == value, bool>::type = 0> void put(void) { ::puts("[false]"); }
template <int value, typename enable_if<1 == value, char>::type = 0> void put(void) { ::puts("[true]"); }

template <class> struct is_primitive { inline operator bool(void) const { return false; } };
template <> struct is_primitive<bool> { inline operator bool(void) const { return true; } };
template <> struct is_primitive<char> { inline operator bool(void) const { return true; } };
template <> struct is_primitive<double> { inline operator bool(void) const { return true; } };
template <> struct is_primitive<float> { inline operator bool(void) const { return true; } };
template <> struct is_primitive<int> { inline operator bool(void) const { return true; } };
template <> struct is_primitive<long> { inline operator bool(void) const { return true; } };
template <> struct is_primitive<long double> { inline operator bool(void) const { return true; } };
template <> struct is_primitive<signed char> { inline operator bool(void) const { return true; } };
template <> struct is_primitive<unsigned char> { inline operator bool(void) const { return true; } };
template <> struct is_primitive<unsigned int> { inline operator bool(void) const { return true; } };
template <> struct is_primitive<unsigned long> { inline operator bool(void) const { return true; } };
template <> struct is_primitive<unsigned short> { inline operator bool(void) const { return true; } };
template <> struct is_primitive<wchar_t> { inline operator bool(void) const { return true; } };
template <> struct is_primitive<void> { inline operator bool(void) const { return true; } };
template <> template <class type> struct is_primitive<type*> { inline operator bool(void) const { return true; } };

struct object {};

int main(void) {
    std::boolalpha(std::cout);

    std::cout << "[bool]: " << is_primitive<bool>() << std::endl;
    std::cout << "[char]: " << is_primitive<char>() << std::endl;
    std::cout << "[double]: " << is_primitive<double>() << std::endl;
    std::cout << "[float]: " << is_primitive<float>() << std::endl;
    std::cout << "[int]: " << is_primitive<int>() << std::endl;
    std::cout << "[long]: " << is_primitive<long>() << std::endl;
    std::cout << "[long double]: " << is_primitive<long double>() << std::endl;
    std::cout << "[signed char]: " << is_primitive<signed char>() << std::endl;
    std::cout << "[unsigned char]: " << is_primitive<unsigned char>() << std::endl;
    std::cout << "[unsigned int]: " << is_primitive<unsigned int>() << std::endl;
    std::cout << "[unsigned long]: " << is_primitive<unsigned long>() << std::endl;
    std::cout << "[unsigned short]: " << is_primitive<unsigned short>() << std::endl;
    std::cout << "[wchar_t]: " << is_primitive<wchar_t>() << std::endl;
    std::cout << "[void]: " << is_primitive<void>() << std::endl;
    std::cout << "[void*]: " << is_primitive<void*>() << std::endl;
    std::cout << "[object]: " << is_primitive<object>() << std::endl;
}
