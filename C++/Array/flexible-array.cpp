/* Import */
    // C Standard Input-Output
    #include <cstdio>

    // Standard Library
    #include <stdlib.h>

/* Function > (To) Character String (Length) --- MINIFY */
constexpr static std::size_t characterStringLength(char characterString[]) { if (NULL == characterString) return 0; else { std::size_t length = 0; while (*(characterString + length) != '\0') length += 1; return length; } }
constexpr inline static char* toCharacterString(int arg) { char* characterString = (char*) std::malloc(255); std::sprintf(characterString, "%i", arg); characterString = (char*) std::realloc(characterString, characterStringLength(characterString)); return characterString; }

/* Class */
    // Flexible Array
    template <typename structType>
    struct flexible_array {
        // [Private]
        private:
            // Definition > Structure Type Size
            #define STRUCT_TYPE_SIZE sizeof(structType)

            // Initialization > (Array, Batched, Length, Size)
            structType* array = NULL;
            bool batched = false; // NOTE (Lapys) -> Is allocating memory in batch?
            std::size_t length = 0, size = 0;

            // Phase > (Initiate, Terminate)
            constexpr inline void init() { this -> array = (structType*) std::malloc(STRUCT_TYPE_SIZE); }
            constexpr inline void terminate() { std::free(this -> array); this -> batched = this -> length = this -> size = 0; }

        // [Protected]
        protected:
            // Function > (Allocate, Request) Size
            constexpr inline void allocateSize(std::size_t size) { if (this -> size < size) this -> array = (structType*) std::realloc(this -> array, sizeof(&(this -> array)) + ((this -> size = size) * STRUCT_TYPE_SIZE)); }
            constexpr inline std::size_t requestSize(structType element) { return sizeof element; }
            template <typename... types, typename = structType> constexpr std::size_t requestSize(structType element, types... elements) { return this -> requestSize(element) + this -> requestSize(elements...); }

        // [Public]
        public:
            // [Constructor]
            explicit flexible_array(structType element) { this -> init(); this -> add(element); }
            template <typename... types, typename = structType> explicit flexible_array(types... elements) { this -> init(); this -> batched = true; this -> allocateSize(this -> requestSize(elements...)); this -> add(elements...); this -> batched = false; }

            // [Destructor]
            ~flexible_array() {
                // Target > Terminate
                this -> terminate();

                // Deletion
                #undef STRUCT_TYPE_SIZE
            }

            // [Operator] > [[]]
            constexpr inline structType operator [](std::size_t index) { return *(this -> array + index); }

            // Function
                // Add --- MINIFY
                constexpr inline void add(structType element) { if (!(this -> batched)) this -> allocateSize(this -> size + this -> requestSize(element)); *(this -> array + this -> length) = element; this -> length += 1; }
                template <typename... types> constexpr void add(structType element, types... elements) { this -> add(element); this -> add(elements...); }

                // Free --- NOTE (Lapys) -> Remove all elements.
                constexpr inline void free() { this -> terminate(); this -> init(); }

                // Index --- NOTE (Lapys) -> Forward indexing.
                constexpr inline int index(structType element) { std::size_t iterator = this -> length; while (iterator) if (*(this -> array + (this -> length - (iterator -= 1) - 1)) == element) return this -> length - iterator - 1; return -1; }

                // Remove
                constexpr inline void remove(structType element) {
                    // Initialization > Index
                    int index = this -> index(element);

                    // Logic
                    if (~index) {
                        // Initialization > Length
                        const std::size_t length = this -> length;

                        // Logic
                        if (length == 1)
                            // Target > Free --- NOTE (Lapys) -> Faster processing...
                            this -> free();

                        else {
                            // Initialization > (Element Is Removed, Former Array, Iterator, Size)
                            bool elementIsRemoved = false;
                            structType formerArray[length - 1] {0}; // NOTE (Lapys) -> Cache...
                            std::size_t iterator = length, size = 0;

                            // Loop
                            while (iterator) {
                                // Update > Index --- NOTE (Lapys) -> Re-purpose the Index variable.
                                index = length - (iterator -= 1) - 1;

                                // Initialization > Former Element
                                structType formerElement = *(this -> array + index);

                                // Logic > Update > (...)
                                if (element == formerElement && !elementIsRemoved) elementIsRemoved = true;
                                else size += this -> requestSize(*(formerArray + index - elementIsRemoved) = formerElement);
                            }

                            // Target > (Free, Allocate Size)
                            this -> free();
                            this -> allocateSize(size);

                            // Modification > Target > Length
                            this -> length = index;

                            // Loop > Update > (Index, Target > Array)
                            while (index) { index -= 1; *(this -> array + index) = *(formerArray + index); }
                        }
                    }
                }
                template <typename... types> constexpr void remove(structType element, types... elements) { this -> remove(element); this -> remove(elements...); }

                // To String
                constexpr inline const char* toString() {
                    // Initialization > (Character String (Length), Array String (Length))
                    const std::size_t length = this -> length;
                    std::size_t characterStringLength = 2, iterator = length;
                    char* arrayString[length];
                    std::size_t arrayStringLength[length];

                    /* Loop
                            --- NOTE (Lapys) -> Populate the Array String & Array String Length arrays whilst
                                determining the string length required to print all the Array's elements.
                    */
                    while (iterator) {
                        // Update > Character String Length
                        (iterator -= 1) && (characterStringLength += 2);
                        characterStringLength += *(arrayStringLength + iterator) = ::characterStringLength(*(arrayString + iterator) = toCharacterString(*(this -> array + iterator)));
                    }

                    // Initialization > Character String
                    char* characterString = (char*) std::malloc(characterStringLength);

                    // Update > Character String (Length)
                    *characterString = '[';
                    *(characterString + (characterStringLength - 1)) = ']';
                    *(characterString + characterStringLength) = '\0';
                    characterStringLength = 1;

                    // Loop --- NOTE (Lapys) -> Use the recently populated Array String & Array String Length (cache) to write data into the Character String.
                    while (iterator != length) {
                        // Initialization > (Array String Element) (Length, Iterator)
                        char* arrayStringElement = *(arrayString + iterator);
                        const std::size_t arrayStringElementLength = *(arrayStringLength + iterator);
                        std::size_t arrayStringElementIterator = arrayStringElementLength;

                        // Loop
                        while (arrayStringElementIterator) {
                            // Update > (Array String Element Iterator, Character String)
                            arrayStringElementIterator -= 1;
                            *(characterString + (characterStringLength + arrayStringElementIterator)) = *(arrayStringElement + arrayStringElementIterator);
                        }

                        // Update > Character String Length
                        characterStringLength += arrayStringElementLength;

                        // Logic
                        if ((iterator += 1) != length) {
                            // Update > Character String (Length)
                            *(characterString + characterStringLength) = ',';
                            *(characterString + characterStringLength + 1) = ' ';
                            characterStringLength += 2;
                        }
                    }

                    // Return
                    return characterString;
                }
    };

/* Function */
    /* Main */
    int main(int argc, char* argv[]) {
        // Initialization > Array
        flexible_array<int> array(1, 0, 1);

        // Print; Update > Array
        std::printf("Array: %s\n", array.toString()); array.add(2, 3, 5);
        std::printf("Array: %s\n", array.toString()); array.remove(1, 3, 5);
        std::printf("Array: %s\n", array.toString());

        // Return
        return 0;
    }
