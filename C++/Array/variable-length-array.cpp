/* Import */
#include <exception> // Exception
#include <iostream> // Input-Output Stream
#include <stddef.h> // Standard Definition
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library
#include <unistd.h> // UNIX Standard

/* Class > Variable Length Array */
template <typename type>
class VariableLengthArray {
    // Function > Print
    template <typename classType> friend void print(VariableLengthArray<classType>& variableLengthArray);

    // ...
    private:
        // Initialization > (Array, ...)
        void **array = NULL;
        unsigned length = 0u, size = 0u;

        // Function > ...
        type& elementAt(const unsigned index) { if (this -> length > index) return *((type*) *(this -> array + index)); else throw std::out_of_range(NULL); }
        const unsigned resize(const unsigned length) { signed long iterator = length - (this -> length); if (this -> length < length) { this -> array = (void**) std::realloc(this -> array, this -> size += sizeof(type) * iterator); while (iterator) *(this -> array + (this -> length + (iterator -= 1))) = std::malloc(sizeof(type)); } else if (this -> length > length) { iterator = -iterator; while (iterator) std::free(*(this -> array + (this -> length - (iterator -= 1)))); this -> array = (void**) std::realloc(this -> array, this -> size -= sizeof(type) * iterator); } this -> length = length; return length; }
        void setIndex(const unsigned index, type element) { if (this -> length > index) *((type*) *(this -> array + index)) = element; else throw std::out_of_range(NULL); }

    // ...
    public:
        // Function > ...
        const unsigned push(type element) { this -> resize(this -> length + 1u); this -> setIndex(this -> length - 1u, element); }
        void pop() { this -> resize(this -> length - 1u); }
};

/* Function > Print */
inline void print() {}

void print(const char character) { const char string[1u] {character}; ::write(1u, string, 1u); }
void print(const char* string) { ::printf("%s", string); }
void print(const float number) { ::printf("%f", number); }
void print(const int number) { ::printf("%i", number); }
void print(const void* pointer) { ::printf("%p", pointer); }

template <typename type> void print(VariableLengthArray<type>& variableLengthArray) { unsigned iterator = variableLengthArray.length; ::print('['); while (iterator) { ::print(variableLengthArray.elementAt(variableLengthArray.length - (iterator -= 1u) - 1u)); if (iterator) ::print(", "); } ::print(']'); }

template <typename type, typename... types> void print(type argument, types... arguments) { ::print(argument); ::print(arguments...); }

/* Main */
int main(void) {
    // Initialization > Array
    VariableLengthArray<char> array;

    // ...
    ::print("Array: ", array, '\n');

    array.push('L'); array.push('a'); array.push('p'); array.push('y'); array.push('s');
    ::print("Array: ", array, '\n');

    array.pop(); array.pop(); array.pop();
    ::print("Array: ", array, '\n');

    array.push('z'); array.push('u'); array.push('l'); array.push('i');
    ::print("Array: ", array, '\n');

    // Return
    return 0;
}
