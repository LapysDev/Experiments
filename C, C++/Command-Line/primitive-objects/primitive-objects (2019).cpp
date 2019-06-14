/* Import */
#include <exception> // Exception
#include <iostream> // Input-Output Stream
#include <math.h> // Mathematics
#include <stdbool.h> // Standard Boolean
#include <stdlib.h> // Standard Library
#include <string.h> // String
#include <cuchar> // Universal Characters

/* Global */
    // False, True
    constexpr static const unsigned char False = 0, True = 1;

/* Function */
    // Add To Arguments
    template <typename type> constexpr static void addToArgumentsList(const unsigned argumentsListLength, type*& argumentsList, type argument) { *(argumentsList + argumentsListLength) = argument; }
    template <typename type, typename... types> constexpr static void addToArgumentsList(const unsigned argumentsListLength, type*& argumentsList, type argument, types... arguments) { ::addToArgumentsList(argumentsListLength, argumentsList, argument); ::addToArgumentsList(argumentsListLength + 1, argumentsList, arguments...); }

    // Get Arguments Length
    constexpr inline static unsigned getArgumentsLength() { return 0; }
    template <typename type> constexpr inline unsigned getArgumentsLength(type argument) { return 1; }
    template <typename type, typename... types> constexpr unsigned getArgumentsLength(type argument, types... arguments) { return ::getArgumentsLength(argument) + ::getArgumentsLength(arguments...); }

    // Get Arguments List --- NOTE (Lapys) -> Convert a collection of arguments into an array.
    template <typename type, typename... types>
    constexpr type* getArgumentsList(type argument, types... arguments) {
        // Initialization > Arguments List
        type* argumentsList = (type*) std::malloc(::getArgumentsLength(argument, arguments...) * sizeof(type));

        // Update > Arguments List
        ::addToArgumentsList(0, argumentsList, argument, arguments...);

        // Return
        return argumentsList;
    }

    // Parse Integer
    long parseInt(const double number) { return number; }
    int parseInt(const float number) { return number; }
    int parseInt(const int number) { return number; }
    long parseInt(const long number) { return number; }
    long long parseInt(const long double number) { return number; }
    long long parseInt(const long long number) { return number; }
    short parseInt(const short number) { return number; }
    unsigned parseInt(const unsigned int number) { return number; }
    unsigned long parseInt(const unsigned long number) { return number; }
    unsigned long long parseInt(const unsigned long long number) { return number; }
    unsigned short parseInt(const unsigned short number) { return number; }

    // String --- NOTE (Lapys) -> Convert plain-old-data to string.
    constexpr inline static char* str(const char character) { char* string = (char*) std::malloc(2); *string = character; *(string + 1) = '\0'; return string; }
    constexpr static char* str(const double number) { char* string = (char*) std::malloc(20); std::sprintf(string, "%lf", number); return string; }
    constexpr static char* str(const float number) { return ::str((double) number); }
    constexpr static char* str(const long double number) { return ::str((double) number); }
    constexpr static char* str(const int number) { char* string = (char*) std::malloc(20); std::sprintf(string, "%d", number); return string; }
    constexpr static char* str(const long long number) { return ::str((int) number); }
    constexpr static char* str(const long number) { return ::str((long long) number); }
    constexpr static char* str(const short number) { return ::str((long long) number); }
    constexpr static char* str(const unsigned int number) { char* string = (char*) std::malloc(20); std::sprintf(string, "%u", number); return string; }
    constexpr static char* str(const unsigned long long number) { return ::str((unsigned int) number); }
    constexpr static char* str(const unsigned long number) { return ::str((unsigned long long) number); }
    constexpr static char* str(const unsigned short number) { return ::str((unsigned long long) number); }

/* Class */
    /* Boolean
            --- NOTE (Lapys) -> Represents state.
            --- WARN (Lapys) -> Uses the `unsigned char` type to represent binary.
    */
    struct boolean {
        // [Private]
        private:
            // Initialization > Value
            enum {False, True} value;

        // [Protected]
        protected:
            // Phase
                // Initiate
                void initiate() { this -> reset(); }
                inline void initiate(const unsigned char argument) { this -> value = argument ? this -> True : this -> False; }
                void initiate(const int argument) { this -> initiate((unsigned char) argument); }
                inline void initiate(const boolean& argument) { this -> value = argument.valueOf() ? this -> True : this -> False; }

                // Reset
                inline void reset() { this -> value = False; }

                // Terminate
                void terminate() { this -> reset(); }

        // [Public]
        public:
            // [Constructor]
            boolean() { this -> initiate(); }
            boolean(char argument) { this -> initiate(argument == '\0'); }
            boolean(char16_t argument) { this -> initiate(argument == u'\0'); }
            boolean(char32_t argument) { this -> initiate(argument == U'\0'); }
            boolean(double argument) { this -> initiate(!!argument); }
            boolean(float argument) { this -> initiate(!!argument); }
            boolean(int argument) { this -> initiate(!!argument); }
            boolean(long argument) { this -> initiate(!!argument); }
            boolean(long double argument) { this -> initiate(!!argument); }
            boolean(long long argument) { this -> initiate(!!argument); }
            boolean(short argument) { this -> initiate(!!argument); }
            boolean(signed char argument) { this -> initiate(argument == '\0'); }
            boolean(unsigned char argument) { this -> initiate(argument); }
            boolean(unsigned int argument) { this -> initiate(!!argument); }
            boolean(unsigned long argument) { this -> initiate(!!argument); }
            boolean(unsigned long long argument) { this -> initiate(!!argument); }
            boolean(unsigned short argument) { this -> initiate(!!argument); }
            boolean(wchar_t argument) { this -> initiate(argument == L'\0'); }
            boolean(const boolean& argument) { this -> initiate(argument); }

            // [Destructor]
            ~boolean() { this -> terminate(); }

            // [Operator]
                // [=]
                boolean& operator =(boolean argument) { this -> initiate(argument); return *this; }

                // [<<]
                friend inline std::ostream& operator <<(std::ostream& outputStream, const boolean& variable) { outputStream << variable.toString(); return outputStream; }

                // [==]
                unsigned char operator ==(const boolean& argument) { return this -> valueOf() == argument.valueOf(); }

                // [!=]
                unsigned char operator !=(const boolean& argument) { return this -> valueOf() != argument.valueOf(); }

                // [int]
                operator int() const { return this -> valueOf(); }

            // Function
                // To String
                char* toString() const {
                    // Initialization > String
                    char* string = NULL;

                    // Logic > Update > String
                    if (this -> valueOf()) { string = (char*) std::malloc(5); *string = 'T'; *(string + 1) = 'r'; *(string + 2) = 'u'; *(string + 3) = 'e'; *(string + 4) = '\0'; }
                    else { string = (char*) std::malloc(6); *string = 'F'; *(string + 1) = 'a'; *(string + 2) = 'l'; *(string + 3) = 's'; *(string + 4) = 'e'; *(string + 5) = '\0'; }

                    // Return
                    return string;
                }

                // Value Of
                unsigned char valueOf() const { return this -> value == this -> True; }
    };

    // Array --- NOTE (Lapys) -> Not a primitive JavaScript object type, but it will do.
    template <typename structType>
    struct array {
        // [Private]
        private:
            // Definition > Maximum Length
            #define MAXIMUM_LENGTH 0xFFFFFFFF

            // Initialization
                // Is Allocated On Heap Memory
                boolean isAllocatedOnHeapMemory = False,

                /* Is Batch Processing
                        --- NOTE (Lapys) -> Allows control of the Length data member and prevents redundant system calls for memory storage (or removal).
                        --- WARN (Lapys) ->
                            - Allocate the correct amount of memory before manipulating storage data using the Resize member function.
                            - Do not forget to reset this value to `false` when its use-context is fulfilled.
                */
                isBatchProcessing = False;

                // Value
                structType* value = NULL;

            // Function > Allocate
            constexpr void allocate(const unsigned size) { if (this -> length < size) this -> resize(size); }

        // [Protected]
        protected:
            // Initialization > Length
            unsigned length = 0;

            // Phase
                // Initiate
                constexpr void initiate(structType* pointer, const unsigned length) {
                    // Target > Reset
                    this -> reset();

                    // Logic
                    if (length) {
                        // Logic
                        if (length < MAXIMUM_LENGTH) {
                            // Initialization > Iterator
                            unsigned iterator = length;

                            // Logic
                            if (length == 1)
                                // Update > (Target > Value)
                                this -> add(*pointer);

                            else {
                                // Modification > Target > Is Batch Processing
                                this -> isBatchProcessing = True;

                                /* Update > (Target > ...)
                                        --- NOTE (Lapys) -> We do not consider additional memory for the array to store new members
                                            because it is being initiated with overriding elements.
                                */
                                this -> resize(length);

                                // Loop > Update > (Target > Value)
                                while (iterator) this -> add(*(pointer + (length - (iterator -= 1) - 1)));

                                // Modification > Target > Is Batch Processing
                                this -> isBatchProcessing = False;
                            }
                        }

                        else
                            // Error
                            throw std::length_error("Invalid array length");
                    }

                    else
                        // Target > Reset --- NOTE (Lapys) -> Initiating an array with a length of 0 should reset it.
                        this -> reset();
                }
                constexpr void initiate(const array& argument) {
                    // Initialization > (Length, Iterator)
                    const unsigned length = argument.length;
                    unsigned iterator = length;

                    // Target > Reset
                    this -> reset();

                    // Update > (Target > ...)
                    this -> resize(length);

                    // Loop > Update > (Iterator, Target > Value)
                    while (iterator) { iterator -= 1; *(this -> value + iterator) = argument[iterator]; }
                }
                template <typename... types> void initiate(structType element, types... elements) { this -> initiate(::getArgumentsList(element, elements...), ::getArgumentsLength(element, elements...)); }

                // Reset
                void reset() { this -> free(); }

                // Terminate
                void terminate() { this -> reset(); }

        // [Public]
        public:
            // [Constructor]
            array() {}
            array(structType (&)[0]) { this -> reset(); }
            template <unsigned length> array(structType (&array)[length]) { this -> initiate(array, length); }
            template <typename... types> array(types... elements) { this -> initiate(elements...); }
            array(const array& argument) { this -> initiate(argument); }

            // [Destructor]
            ~array() { this -> terminate(); }

            // [Operator]
                // [+]
                unsigned operator +() { return this -> length; }

                // [=]
                array& operator =(array argument) { this -> initiate(argument); return *this; }

                // [<<]
                constexpr friend inline std::ostream& operator <<(std::ostream& outputStream, const array& variable) { outputStream << variable.toString(); return outputStream; }

                // [[]]
                inline structType& operator [](unsigned index) const { if (index < this -> length) return *(this -> value + index); else { static structType undefined; return undefined; } }

            // Function
                // Add
                constexpr inline void add() { this -> isBatchProcessing = False; }
                constexpr inline void add(structType element) {
                    // Update > (Target > Value)
                    *(this -> value + this -> length) = element;

                    // Logic > (...)
                    if (this -> isBatchProcessing) this -> length += 1;
                    else this -> allocate(this -> length + 1); // NOTE (Lapys) -> Length is implicitly incremented here.
                }

                template <typename... types>
                constexpr void add(structType element, types... elements) {
                    // Modification > Target > Is Batch Processing
                    this -> isBatchProcessing = True;

                    // Update > (Target > ...)
                    this -> allocate(this -> length + ::getArgumentsLength(element, elements...));
                    this -> add(element); this -> add(elements...);

                    // Modification > Target > Is Batch Processing
                    this -> isBatchProcessing = False;
                }

                // Concatenate
                constexpr void concatenate(structType* pointer, const unsigned length) {
                    // Initialization > Iterator
                    unsigned iterator = length;

                    // Modification > Target > Is Batch Processing
                    this -> isBatchProcessing = True;

                    // Update > (Target > ...)
                    this -> allocate(this -> length + length);

                    // Loop > Target > Add
                    while (iterator) this -> add(*(pointer + (length - (iterator -= 1) - 1)));

                    // Modification > Target > Is Batch Processing
                    this -> isBatchProcessing = False;
                }
                constexpr inline static void concatenate(structType (&)[0]) {}
                template <unsigned length> void concatenate(structType (&array)[length]) { this -> concatenate(array, length); }

                // Cut At
                constexpr void cutAt(unsigned index) {
                    // Logic > Loop > Update > (...)
                    if (index < this -> length) while (index != this -> length) { *(this -> value + index) = *(this -> value + index + 1); index += 1; }

                    // Logic > Update > (Target > ...)
                    this -> length -= 1;
                    if (!(this -> isBatchProcessing)) this -> resize(this -> length);
                }

                // Free
                constexpr void free() { if (this -> isAllocatedOnHeapMemory) { this -> isAllocatedOnHeapMemory = False; std::free(this -> value); } this -> length = 0; this -> value = NULL; }

                // Includes
                constexpr boolean includes(structType element) const {
                    // Logic
                    if (this -> length == 1)
                        // Return
                        return *(this -> value) == element;

                    else if (this -> length) {
                        // Initialization > (Iterator, (Half, (Third) Quarter) Length)
                        signed iterator = this -> length;
                        const signed halfLength = ::parseInt(this -> length / 2),
                            quarterLength = ::parseInt(halfLength / 2),
                            thirdQuarterLength = halfLength + quarterLength;

                        // Loop
                        while (iterator != thirdQuarterLength) {
                            // Update > Iterator
                            iterator -= 1;

                            // Logic > Return
                            if (
                                *(this -> value + (this -> length - iterator - 1)) == element ||
                                ((iterator - halfLength) > -1 && *(this -> value + (iterator - halfLength)) == element) ||
                                (halfLength + (this -> length - iterator - 1) < this -> length && *(this -> value + (halfLength + (this -> length - iterator - 1))) == element) ||
                                *(this -> value + iterator) == element
                            ) return True;
                        }

                        // Return
                        return False;
                    }

                    else
                        // Return
                        return False;
                }

                // Index
                constexpr long index(structType element) const {
                    // Logic
                    if (this -> length) {
                        // Logic
                        if (this -> length == 1)
                            // Return
                            return *(this -> value) == element ? 0 : -1;

                        else {
                            // Initialization
                                // Index(es), Iterator
                                signed index = -1, indexes[4] {0}, iterator = this -> length;

                                // (Half, (Third) Quarter) Length
                                const signed halfLength = ::parseInt(this -> length / 2),
                                    quarterLength = ::parseInt(halfLength / 2),
                                    thirdQuarterLength = halfLength + quarterLength;

                            // Loop
                            while (iterator != thirdQuarterLength) {
                                // Update > (Iterator, Indexes)
                                iterator -= 1;

                                *indexes = (signed) this -> length - iterator - 1;
                                *(indexes + 1) = iterator - halfLength;
                                *(indexes + 2) = halfLength - *indexes;
                                *(indexes + 3) = iterator;

                                // Logic > Return
                                if (
                                    ((*(this -> value + *indexes) == element) && (index = 1)) ||
                                    (*(indexes + 1) > -1 && ((*(this -> value + *(indexes + 1)) == element) && (index = 2))) ||
                                    ((*(indexes + 2) < (signed) this -> length) && ((*(this -> value + *(indexes + 2)) == element) && (index = 3))) ||
                                    ((*(this -> value + *(indexes + 3)) == element) && (index = 4))
                                ) return *(indexes + (index - 1));
                            }

                            // Return
                            return index;
                        }
                    }

                    else
                        // Return
                        return -1;
                }

                // Remove
                constexpr inline void remove() { this -> isBatchProcessing = False; }
                constexpr void remove(structType element) { signed index = this -> index(element); if (this -> length && ~index) this -> cutAt(index); }

                template <typename... types>
                constexpr void remove(structType element, types... elements) {
                    // Modification > Target > Is Batch Processing
                    this -> isBatchProcessing = True;

                    // Target > Remove
                    this -> remove(element); this -> remove(elements...);

                    // Logic
                    if (this -> isBatchProcessing && ::getArgumentsLength(elements...) == 1) {
                        // Modification > Target > Is Batch Processing
                        this -> isBatchProcessing = False;

                        // Update > (Target > ...)
                        this -> resize(this -> length);
                    }
                }

                // Resize --- NOTE (Lapys) -> Manipulates the Length data member and allocates size for the array to store its values.
                constexpr void resize(const unsigned length, boolean VOID_UNUSED_ELEMENTS = False) {
                    // Logic
                    if (this -> length != length) {
                        // Logic
                        if (length && length < MAXIMUM_LENGTH) {
                            // Initialization > Size
                            const unsigned size = length * sizeof(structType);

                            // Logic
                            if (this -> isAllocatedOnHeapMemory) {
                                // Logic
                                if (length > this -> length)
                                    // Modification > Target > Value
                                    this -> value = (structType*) std::realloc(this -> value, size);

                                else {
                                    // Initialization > (Iterator, Value Cache)
                                    unsigned iterator;
                                    structType* valueCache = (structType*) std::malloc(size);

                                    // Logic
                                    if (VOID_UNUSED_ELEMENTS) {
                                        // (Loop > )Update > (...)
                                        iterator = this -> length;
                                        while (iterator != length) { *(this -> value + (iterator -= 1)) = structType(); }
                                    }

                                    // (Loop > )Update > (...)
                                    iterator = length;
                                    while (iterator) { iterator -= 1; *(valueCache + iterator) = *(this -> value + iterator); }

                                    // Deletion
                                    std::free(this -> value);

                                    // Modification > Target > Value
                                    this -> value = (structType*) std::malloc(length * sizeof(size));

                                    // (Loop > )Update > (...)
                                    iterator = length;
                                    while (iterator) { iterator -= 1; *(this -> value + iterator) = *(valueCache + iterator); }

                                    // Deletion
                                    std::free(valueCache);
                                }
                            }

                            else
                                // Modification > Target > Value
                                this -> value = (structType*) std::malloc(size);

                            // Modification > Target > Is (Allocated On Heap Memory, Batch Processing)
                            this -> isAllocatedOnHeapMemory || (this -> isAllocatedOnHeapMemory = True);
                            this -> isBatchProcessing || (this -> length = length);
                        }

                        else if (!length)
                            // Target > Free --- NOTE (Lapys) -> Resizing the array to zero clears all its contents.
                            this -> free();
                    }
                }

                // To String
                constexpr char* toString() const {
                    // Logic
                    if (this -> length) {
                        // Initialization
                            // Iterator, Length
                            unsigned iterator = this -> length, length = 0;

                            // Array String (Length) --- NOTE (Lapys) -> Store the string data of the array's contents within other arrays.
                            char* arrayString[iterator]; unsigned arrayStringLength[iterator];

                            // Separator (Length) --- NOTE (Lapys) -> Delimit each element.
                            const char* separator = ", "; const unsigned separatorLength = 2;

                        // (Loop > )Update > (...) --- NOTE (Lapys) -> Inquire all necessary string data.
                        while (iterator) { iterator -= 1; length += (*(arrayStringLength + iterator) = ::strlen(*(arrayString + iterator) = ::str(*(this -> value + iterator)))) + (iterator ? separatorLength : 0); }
                        length += 2;

                        // Initialization > String
                        char* string = (char*) std::malloc(length);

                        // Update > (String, Length)
                        *string = '['; *(string + (length - 1)) = ']'; *(string + length) = '\0';
                        length = 0;

                        // Loop
                        while (iterator != this -> length) {
                            // Initialization > (Array String Element) (Length, Iterator)
                            char* arrayStringElement = *(arrayString + iterator);
                            const unsigned arrayStringElementLength = *(arrayStringLength + iterator);
                            unsigned arrayStringElementIterator = arrayStringElementLength;

                            // Loop > Update > String
                            while (arrayStringElementIterator)
                                *(string + (length += 1)) = *(arrayStringElement + (arrayStringElementLength - (arrayStringElementIterator -= 1) - 1));

                            // Logic --- NOTE (Lapys) -> Delimit the stringified element?
                            if ((iterator += 1) != this -> length) {
                                // Initialization > Separator Iterator
                                unsigned separatorIterator = separatorLength;

                                // Loop > Update > String
                                while (separatorIterator)
                                    *(string + (length += 1)) = *(separator + (separatorLength - (separatorIterator -= 1) - 1));
                            }
                        }

                        // Return
                        return string;
                    }

                    else {
                        // Initialization > String
                        char* string = (char*) std::malloc(3);

                        // Update > String
                        *string = '['; *(string + 1) = ']'; *(string + 2) = '\0';

                        // Return
                        return string;
                    }
                }

                // Value Of
                constexpr structType*& valueOf() const { return this -> value; }
    };

    // Function
    // struct function {
    //     protected:
    //         template <typename type, typename... types>
    //         void initiate(type (&argument)(types... parameters)) {}

    //     public:
    //         function() {}
    //         template <typename type, typename... types>
    //         function(type (&argument)(types... parameters)) {}
    // };

    // Number
    struct number {
        // [Private]
        private:
            // Initialization > (Is (Not-A-Number, Signed), Type)
            boolean isNaN = false, isSigned = false;
            enum {whole, decimal} type;
    };

    // String
    struct string {
        // [Private]
        private:
            // Class > Character
            struct character {};

            // Initialization > Value
            array<character> value;
    };

    // Symbol
    struct symbol {};

    // Variable
    struct var;

    // Object
    struct object {
        // [Private]
        private:
            // Initialization > Property
            struct property {
                // [Private]
                private:
                    // Class
                        // Property Name
                        struct property_name {
                            // [Private]
                            private:
                                // Initialization > Value
                                struct { public: string _string = ""; symbol* _symbol; } value;
                        };

                        // Property Value
                        struct property_value {};
            };

            // Initialization > Properties
            array<property> properties;
    };

    // Accessor
    struct accessor {};

    // Mutator
    struct mutator {};

    // Variable
    struct var {
        // Initialization > Reference
        struct { public: array<var>* _array; boolean* _boolean; function* _function; number* _number; object* _object; string* _string; symbol* _symbol; } reference;
    };

/* Namespace > Standard Library */
namespace std { constexpr static const char *longline = "============================================================", *tab = "    "; }

/* Function */
    /* Main */
    int main(int argc, char* argv[]) {
        /* Logic --- REDACT (Lapys) */
            // [Array]
            if (true) {
                array<int> variable(0, 1, 2);

                std::cout << "ARRAYS" << std::endl << std::longline << std::endl;

                std::cout << std::tab << "[INIT.] : " << variable << std::endl;

                std::cout << std::endl;

                std::cout << std::tab << "[ADD] : "; variable.add(3); std::cout << variable << std::endl;
                std::cout << std::tab << "[ADD] : "; variable.add(4, 5, 6); std::cout << variable << std::endl;
                std::cout << std::tab << "[ADD] : "; variable.add(7); std::cout << variable << std::endl;
                std::cout << std::tab << "[ADD] : "; variable.add(8, 9); std::cout << variable << std::endl;

                std::cout << std::endl;

                std::cout << std::tab << "[RESIZE] : "; variable.resize(5); std::cout << variable << std::endl;

                std::cout << std::endl;

                std::cout << std::tab << "[REMOVE] : "; variable.remove(2); std::cout << variable << std::endl;
                std::cout << std::tab << "[REMOVE] : "; variable.remove(1, 4, 3); std::cout << variable << std::endl;
                std::cout << std::tab << "[REMOVE] : "; variable.remove(0); std::cout << variable << std::endl;

                std::cout << std::endl;

                std::cout << std::tab << "[RESIZE] : "; variable.resize(2); std::cout << variable << std::endl;

                std::cout << std::endl;

                std::cout << std::tab << "[EDIT] : "; variable[0] = 7; variable[1] = 0; variable[2] = 7; std::cout << variable << std::endl;
                std::cout << std::tab << "[EDIT] : "; variable[0] = 1; variable[1] = 0; variable[2] = 1; std::cout << variable << std::endl;

                std::cout << std::endl;

                std::cout << std::tab << "[CONCAT.] : ";
                    int concatenationArray[4] {1, 2, 3, 5};
                    variable.concatenate(concatenationArray);
                std::cout << variable << std::endl;

                std::cout << std::endl;

                std::cout << std::tab << "[FREE x2] : "; variable.free(); variable.free(); std::cout << variable << std::endl;

                std::cout << std::endl;

                std::cout << std::tab << "[COPY] : "; variable = array<int>(7, 0, 7); std::cout << variable << std::endl;

                std::cout << std::endl;
            }

            // [Boolean]
            if (true) {
                boolean variable;

                std::cout << "BOOLEAN" << std::endl << std::longline << std::endl;

                std::cout << std::tab << "[INIT.] : " << variable << std::endl;

                std::cout << std::endl;

                std::cout << std::tab << "[EDIT] : " << (variable = true) << std::endl;

                std::cout << std::endl;
            }

            // [Function]
            if (true) {
                // function variable = main;

                // std::cout << "FUNCTION" << std::endl << std::longline << std::endl;

                // std::cout << std::endl;
            }

        // Return
        return 0;
    }

