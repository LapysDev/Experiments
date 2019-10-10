/* Import */
#include <exception> // Exception
#include <iostream> // Input-Output Stream
#include <stddef.h> // Standard Definition
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library
#include <unistd.h> // UNIX Standard

/* Class > Variant Array */
template <typename typeA, typename typeB>
class VariantArray {
    // Function > Print
    template <typename classTypeA, typename classTypeB> friend void print(VariantArray<classTypeA, classTypeB>& variantArray);

    // ...
    private:
        // Initialization > (Array, ...)
        void **array = NULL;
        unsigned length = 0u, size = 0u;
        const unsigned MAXIMUM_ELEMENT_BYTE_SIZE = sizeof(typeA) > sizeof(typeB) ? sizeof(typeA) : sizeof(typeB);

        // Function > ...
        const unsigned resize(const unsigned length) { signed long iterator = length - (this -> length); if (this -> length < length) { this -> array = (void**) std::realloc(this -> array, this -> size += MAXIMUM_ELEMENT_BYTE_SIZE * iterator); while (iterator) *(this -> array + (this -> length + (iterator -= 1))) = std::malloc(MAXIMUM_ELEMENT_BYTE_SIZE); } else if (this -> length > length) { iterator = -iterator; while (iterator) std::free(*(this -> array + (this -> length - (iterator -= 1)))); this -> array = (void**) std::realloc(this -> array, this -> size -= MAXIMUM_ELEMENT_BYTE_SIZE * iterator); } this -> length = length; return length; }
        void setIndex(const unsigned index, typeA element) { if (this -> length > index) *((typeA*) *(this -> array + index)) = element; else throw std::out_of_range(NULL); }
        void setIndex(const unsigned index, typeB element) { if (this -> length > index) *((typeB*) *(this -> array + index)) = element; else throw std::out_of_range(NULL); }

    // ...
    public:
        // Function > ...
        const unsigned push(typeA element) { this -> resize(this -> length + 1u); this -> setIndex(this -> length - 1u, element); }
        const unsigned push(typeB element) { this -> resize(this -> length + 1u); this -> setIndex(this -> length - 1u, element); }
        void pop() { this -> resize(this -> length - 1u); }
};

/* Function > Print */
inline void print() {}

void print(const char character) { const char string[1u] {character}; ::write(1u, string, 1u); }
void print(const char* string) { ::printf("%s", string); }
void print(const float number) { ::printf("%f", number); }
void print(const int number) { ::printf("%i", number); }
void print(const void* pointer) { ::printf("%p", pointer); }

template <typename typeA, typename typeB> void print(VariantArray<typeA, typeB>& variantArray) { unsigned iterator = variantArray.length; ::print('['); while (iterator) { ::print('*'); if (iterator -= 1u) ::print(", "); } ::print(']'); }

template <typename type, typename... types> void print(type argument, types... arguments) { ::print(argument); ::print(arguments...); }

/* Main */
int main(void) {
    // Initialization > Array
    VariantArray<float, int> array;

    // ...
    ::print("Array: ", array, '\n');

    array.push(1); array.push(1.5f); array.push(2); array.push(2.5f); array.push(3);
    ::print("Array: ", array, '\n');

    array.pop(); array.pop(); array.pop();
    ::print("Array: ", array, '\n');

    array.push(3.5f); array.push(4); array.push(4.5f);
    ::print("Array: ", array, '\n');

    // Return
    return 0;
}
