#include <stdio.h> // For testing.
#include <string.h> // Does not use memory manipulation utilities.

namespace Memory {
    // The copying utility
    static void* copy(void* const destination, void const* const source, size_t size) {
        typedef unsigned char byte;

        byte *destinationIterator = (byte*) destination;
        byte *sourceIterator = (byte*) source;

        while (size--) *(destinationIterator++) = *(sourceIterator++);

        return destination;
    }
}

class Object { // Spawn an object with a incrementing id and a name.
    private: unsigned id; char *name;
    protected: static unsigned total;
    public:
        Object(char *const name) : id{++Object::total}, name{name} {}
        Object(char const *const name) : id{++Object::total}, name{(char*) name} {}
        Object(void) : id{++Object::total}, name{NULL} {}

        char* toString(void) const {
            // We won't bother with memory allocation failure or leaking, here... -_-
            char *const evaluation = new char[14u + (10u + (NULL == this -> name ? 3u : ::strlen(this -> name))) + 1u] {0};
            char *indexer = (char*) evaluation;

            ::strcpy(indexer, "Object ("); indexer += 8u;
            { char *end = NULL, *start = NULL;
                start = indexer;
                for (unsigned iterator = this -> id; iterator; iterator /= 10u) *(indexer++) = *("0123456789" + (iterator % 10u));

                end = indexer - 1;
                for (; start < end; (--end, ++start)) { *end ^= *start; *start ^= *end; *end ^= *start; }
            }
            ::strcpy(indexer, ") {\""); indexer += 4u;

            if (NULL == this -> name) { ::strcpy(indexer, "..."); indexer += 3u; }
            else { ::strcpy(indexer, this -> name); indexer += ::strlen(this -> name); }

            ::strcpy(indexer, "\"}");

            return &*evaluation;
        }
}; unsigned Object::total = 0u;
typedef float Primitive;

/* TEST */
int main(void) {
    Object objectA {}, objectB {"Lapys"};
    Primitive primitiveA = 0.00, primitiveB = 3.141592653589793f /* -> M_PI ? */;

    ::printf("[A]: {%f, %s}\r\n", primitiveA, objectA.toString());
    ::printf("[B]: {%f, %s}\r\n", primitiveB, objectB.toString());

    // Copy the memory region of `second`.
    Memory::copy(&objectA, &objectB, sizeof(Object) /* -> sizeof(objectA) */);
    ::putchar('\n');
    Memory::copy(&primitiveA, &primitiveB, sizeof(Primitive) /* -> sizeof(primitiveA) */);

    ::printf("[A]: {%f, %s}\r\n", primitiveA, objectA.toString());
    ::printf("[B]: {%f, %s}\r\n", primitiveB, objectB.toString());
}
