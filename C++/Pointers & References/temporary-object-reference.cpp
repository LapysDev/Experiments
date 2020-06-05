/* Import */
#include <iostream> // Input-Output Stream

/* Function > ... */
inline int create(void) noexcept { int const value = int(); return value ? value : 42; }
template <typename type> constexpr inline type* parse(type&& value) noexcept { return (type*) &value; }

/* Main */
int main(void) {
    // Constant > ...
    int const value = ::create();
    int * const pointer = ::parse(int(value));

    std::cout << "Address: " << pointer << std::endl;
    for (size_t iterator = 0u, length = -1; iterator ^ length; ++iterator) ::parse(int()); // NOTE (Lapys) -> Try corrupting the temporary object address.

    std::cout << "Address Value: " << *pointer << std::endl;
    std::cout << "Value: " << value << std::endl;
}
