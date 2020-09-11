/* Import */
#include <exception> // Exception
#include <iostream> // Input-Output Stream
#include <unistd.h> // UNIX Standard

/* Class > Flexible Array */
template <typename type>
class FlexibleArray {
    // Function > Print
    template <typename classType> friend void print(FlexibleArray<classType>& flexibleArray);

    // ...
    private:
        // Class > Flexible Array
        struct flexible_array { public: inline flexible_array() : length(0u) {} unsigned length; type array[]; };

        // Initialization > Flexible Array (Size)
        flexible_array *flexibleArray = NULL;
        unsigned flexibleArraySize = 0u;

        // Function > ...
        type& elementAt(const unsigned index) { if (this -> flexibleArray -> length > index) return (this -> flexibleArray -> array)[index]; else throw std::out_of_range(NULL); }
        const unsigned resize(const unsigned length) { if (this -> flexibleArray -> length < length) this -> flexibleArray = (flexible_array*) std::realloc(this -> flexibleArray, flexibleArraySize += (sizeof(type) * (length - (this -> flexibleArray -> length)))); else if (this -> flexibleArray -> length > length) this -> flexibleArray = (flexible_array*) std::realloc(this -> flexibleArray, flexibleArraySize -= (sizeof(type) * (this -> flexibleArray -> length - length))); return (this -> flexibleArray -> length = length); }
        void setIndex(const unsigned index, type element) { if (this -> flexibleArray -> length > index) this -> flexibleArray -> array[index] = element; else throw std::out_of_range(NULL); }

    // ...
    public:
        // [Constructor]
        FlexibleArray() {
            // Update > (Target > (Flexible Array) ( > Length, Size))
            this -> flexibleArraySize = sizeof(flexible_array);
            this -> flexibleArray = (flexible_array*) std::malloc(flexibleArraySize);
            this -> flexibleArray -> length = 0u;
        }

        // Function > ...
        type& pop() { type& element = this -> elementAt(this -> flexibleArray -> length - 1u); this -> resize(this -> flexibleArray -> length - 1u); return element; }
        const unsigned push(type element) { this -> resize(this -> flexibleArray -> length + 1u); this -> setIndex(this -> flexibleArray -> length - 1u, element); }
};

/* Function > Print --- NOTE (Lapys) -> For printing the array. */
inline void print() {}

void print(const char character) { const char string[1u] {character}; ::write(1u, string, 1u); }
void print(const char* string) { ::printf("%s", string); }
void print(const float number) { ::printf("%f", number); }
void print(const int number) { ::printf("%i", number); }
void print(const void* pointer) { ::printf("%p", pointer); }

template <typename type> void print(FlexibleArray<type>& array) { unsigned iterator = array.flexibleArray -> length; ::print('['); while (iterator) { ::print(array.elementAt((array.flexibleArray -> length) - (iterator -= 1u) - 1u)); if (iterator) ::print(", "); } ::print(']'); }

template <typename type, typename... types> void print(type argument, types... arguments) { ::print(argument); ::print(arguments...); }

/* Main */
int main(void) {
    // Initialization > Array
    FlexibleArray<char> array;

    // ...
    ::print("Array: ", array, '\n');

    array.push('H'); array.push('e'); array.push('l'); array.push('l'); array.push('o');
    ::print("Array: ", array, '\n');

    array.pop(); array.pop(); array.pop();
    ::print("Array: ", array, '\n');

    array.push('`'); array.push('l'); array.push('l');
    ::print("Array: ", array, '\n');

    // Return
    return 0;
}
