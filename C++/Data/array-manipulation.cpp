/* Import > ... */
#include <iostream> // Input-Output Stream
#include <stdlib.h> // Standard Library
#include <string> // String
#include <string.h> // String

/* Definition > ... --- NOTE (Lapys) -> Use of references over value storage follows standard. */
#define PREFER_REFERENCE_OVER_VALUE true

/* Class */
    /* Object */
    class Object {
        // [...]
        private:
            // Definition > (Total, Value)
            static unsigned char total;
            std::string value;

        // [...]
        public:
            // [Constructor]
            inline Object(void) : value{} {
                // Initialization > ...
                char string[3];
                size_t value = ++total;

                // Update > ...
                *(string + 2) = (value % 10u) + 48u; value /= 10u;
                *(string + 1) = (value % 10u) + 48u; value /= 10u;
                *string = (value % 10u) + 48u;

                // Modification > Target > Value
                this -> value = string;
            }
            constexpr inline Object(Object&&) = delete;
            constexpr inline Object(const Object&) = delete;

            // [Operator] > ...
            inline Object& operator =(Object&&) const noexcept = delete;
            inline Object& operator =(const Object&) const noexcept = delete;

            friend inline std::ostream& operator <<(std::ostream& stream, Object& object) { stream << object.toString(); return stream; }

            // Function > To String
            inline const char* toString(void) noexcept { return this -> value.c_str(); }
    };

    /* Object Array */
    class ObjectArray {
        // [...]
        private:
            // Definition > (Length, Value)
            size_t length;
            #if PREFER_REFERENCE_OVER_VALUE
                Object **value;
            #else
                Object *value;
            #endif

            // Function > ... --- REDACT (Lapys)
            inline Object& at(const size_t index) const noexcept {
                #if PREFER_REFERENCE_OVER_VALUE
                    return **(this -> value + index);
                #else
                    return *(this -> value + index);
                #endif
            }
            inline void setIndex(const size_t index, Object* const object) const noexcept {
                #if PREFER_REFERENCE_OVER_VALUE
                    Object *& element = *(this -> value + index);

                    if (NULL == element) element = (Object*) ::malloc(sizeof(Object));
                    element = object;
                #else
                    ::memcpy(this -> value + index, object, sizeof(Object));
                #endif
            }

        // [...]
        public:
            // [Constructor]
            constexpr inline ObjectArray(void) : length{0u}, value{
                #if PREFER_REFERENCE_OVER_VALUE
                    (Object**) ::malloc(0u)
                #else
                    (Object*) ::malloc(0u)
                #endif
            } {}

            // [Destructor]
            inline ~ObjectArray(void) {
                ObjectArray::free();

                ::free((char*) ObjectArray::toString());
                ::free(this -> value);
            }

            // [Operator] > ...
            friend inline std::ostream& operator <<(std::ostream& stream, const ObjectArray& array) { stream << array.toString(); return stream; }
            inline Object& operator [](const size_t index) const noexcept { return ObjectArray::at(index); };
            template <typename type> operator type*(void) const noexcept { return (type*) ObjectArray::toString(); }

            // Function
                // ... --- REDACT (Lapys)
                inline void free(void) noexcept {
                    #if PREFER_REFERENCE_OVER_VALUE
                        for (size_t iterator = 0u; iterator ^ (this -> length); ++iterator) {
                            Object *& element = *(this -> value + iterator);
                            if (element) ::free(element);
                        }
                    #endif

                    ::free(this -> value);
                    this -> length = 0u;

                    #if PREFER_REFERENCE_OVER_VALUE
                        this -> value = (Object**) ::malloc(0u);
                    #else
                        this -> value = (Object*) ::malloc(0u);
                    #endif
                }
                inline void pop(void) noexcept { --(this -> length); }
                inline void push(Object& object) noexcept { ObjectArray::resize(this -> length + 1u); ObjectArray::setIndex(this -> length - 1u, &object); }
                inline void push(Object&& object) noexcept { ObjectArray::push((Object&) object); }
                inline void resize(const size_t length) noexcept {
                    if (length) {
                        #if PREFER_REFERENCE_OVER_VALUE
                            this -> value = (Object**) ::realloc(this -> value, length * sizeof(Object*));
                            if (length > this -> length) ::memset(this -> value + (this -> length), 0x0, length - (this -> length));
                        #else
                            this -> value = (Object*) ::realloc(this -> value, length * sizeof(Object));
                        #endif
                        this -> length = length;
                    } else ObjectArray::free();
                }

                // To String
                inline const char* toString(void) const noexcept {
                    // Initialization > (..., String)
                    size_t length = 0u;
                    static char *string = NULL;

                    // Deletion; Update > String
                    ::free(string);
                    string = (char*) ::malloc((((this -> length * 3u) + (this -> length * 2u) + (3u)) - (this -> length ? 2u : 0u)) * sizeof(char));

                    // Loop > Update > String
                    for (size_t iterator = 0u; iterator ^ (this -> length); ++iterator) {
                        // Constant > Element
                        #if PREFER_REFERENCE_OVER_VALUE
                            Object *& element = *(this -> value + iterator);
                        #else
                            Object *element = this -> value + iterator;
                        #endif

                        // Logic --- WARN (Lapys) -> Accessing un-initialized memory blocks as (now invalid) objects causes undefined behavior.
                        if (0x0 == element) {
                            // Update > String
                            *(string + ++length) = 'N';
                            *(string + ++length) = 'U';
                            *(string + ++length) = 'L';
                        }

                        else {
                            // Constant > ...
                            const char *substring = element -> toString();

                            // Update > String
                            *(string + ++length) = *substring;
                            *(string + ++length) = *(substring + 1);
                            *(string + ++length) = *(substring + 2);
                        }

                        // Logic > Update > String
                        if (iterator < this -> length - 1u) {
                            *(string + ++length) = ',';
                            *(string + ++length) = ' ';
                        }
                    }

                    // Update > String
                    *string = '[';
                    *(string + ++length) = ']';
                    *(string + ++length) = '\0';

                    // Return
                    return (const char*) string;
                }
    };

/* Modification > Object > Total */
unsigned char Object::total = 0u;

/* Main */
int main(void) {
    // Global > Array
    ObjectArray array;

    // ...
    std::cout << "[PROGRAM INITIATED]" << std::endl; {
        // ...
        Object object; (void) object;

        std::cout << array << std::endl;
        array.push(object); std::cout << array << std::endl;
        array.push(Object()); std::cout << array << std::endl;
        array.pop(); std::cout << array << std::endl;
        array.push(object); std::cout << array << std::endl;
        array.push(Object()); std::cout << array << std::endl;
        array.push(Object()); std::cout << array << std::endl;
        array.resize(7u); std::cout << array << std::endl;
        array.push(Object()); std::cout << array << std::endl;
        array.push(object); std::cout << array << std::endl;
    } std::cout << "[PROGRAM TERMINATED]" << std::flush;

    // Return
    return EXIT_SUCCESS;
}
