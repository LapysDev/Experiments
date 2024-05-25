/* Import */
#include <algorithm> // Algorithm
#include <cstdarg> // C Standard Arguments
#include <cstddef> // C Standard Definition
#include <cstdint> // C Standard Integer
#include <cstdio> // C Standard Input/ Output
#include <cstring> // C String
#include <iostream> // Input/ Output Stream

/* Function > Terminate --- NOTE (Lapys) -> For testing. */
int Terminate(void) throw() { std::fflush(stdout); ::exit(EXIT_SUCCESS); return EXIT_SUCCESS; }
int Terminate(char const message[], ...) throw() { va_list arguments; std::fputs("\r\n", stderr); va_start(arguments, message); std::vfprintf(stderr, message, arguments); va_end(arguments); std::fputc('\0', stderr); std::fflush(stdout); ::exit(EXIT_FAILURE); return EXIT_FAILURE; }

/* ... Class > String */
constexpr unsigned char const STRING_STACK_LENGTH = std::max((size_t) 32u, sizeof(char*) + (sizeof(size_t) << 1u)) / sizeof(char);
class String {
    // [...]
    private:
        // Definition > Value
        char value[STRING_STACK_LENGTH];

        // Function > Allocate ...
        /* constexpr */ inline void allocateStack(size_t const) /* const */ noexcept {}
        inline void allocate(size_t const length) {
            // Logic > ...
            if (String::heapIsDefined()) String::allocateHeap(length);
            else if (length > String::stackSize()) String::moveStackToHeap((length - String::stackLength()) * sizeof(char));
        }
        inline void allocateHeap(size_t const length) {
            // Initialization > (Heap) Size
            size_t& heapSize = String::heapSize();
            size_t const size = (length * 1.618033988749895f) * sizeof(char);

            // Logic
            if (heapSize < size) {
                // Initialization > (Heap, ...)
                char *&heap = String::heap();
                void *const allocation = std::realloc(heap, size);

                // Logic > ...
                if (nullptr == allocation) Terminate("[Error]: More resources (%zu bytes) required for `String` instance", size);
                else { heap = (char*) allocation; heapSize = size; }
            }
        }

        // Function > (Heap ..., ... to Heap, Stack ...)
        inline char*& heap(void) const noexcept { return *(char**) (this -> value + 1); }
        constexpr inline bool heapIsDefined(void) const noexcept { return 0x1 == *(this -> value); }
        inline size_t& heapLength(void) const noexcept { return *(size_t*) (sizeof(char*) + (std::byte*) (this -> value + 1)); }
        inline size_t& heapSize(void) const noexcept { return *(size_t*) (sizeof(char*) + sizeof(size_t) + (std::byte*) (this -> value + 1)); }

        inline void moveStackToHeap(size_t const surplusSize) {
            // Constant > (... Size, ...) --- NOTE (Lapys) ->
            unsigned char const usedStackSize = String::stackLength() * sizeof(char);
            unsigned char const size = (((surplusSize + usedStackSize) >> 1u) << 1u) + 2u; // Additional space for NUL terminator.

            void *const allocation = std::malloc(size);

            // Logic > ...
            if (nullptr == allocation) Terminate("[Error]: More resources (%zu bytes) required for `String` instance", size);
            else {
                // Update > (Allocation, ...)
                std::memcpy(allocation, String::stack(), usedStackSize);

                String::heap() = (char*) allocation;
                String::heapLength() = usedStackSize / sizeof(char);
                String::heapSize() = size;

                String::promoteToHeap();
            }
        }
        constexpr inline void promoteToHeap(void) noexcept { *(this -> value) = 0x1; }

        constexpr inline char* stack(void) const noexcept { return (char*) this -> value + 1; }
        constexpr inline bool stackIsDefined(void) const noexcept { return 0x0 == *(this -> value); }
        constexpr inline unsigned char stackLength(void) const noexcept { char *iterator = (char*) this -> value; while ('\0' ^ *++iterator) continue; return iterator - String::stack(); }
        constexpr inline unsigned char stackSize(void) const noexcept { return sizeof(this -> value) - sizeof(char); }

    // [...]
    protected:
        // Phase > Initiate ...
        inline void initiate(char const string[], size_t const length) { length < STRING_STACK_LENGTH - 1u && String::stackIsDefined() ? String::initiateStack(string, length) : String::initiateHeap(string, length); }
        inline void initiateHeap(char const string[], size_t const length) { String::allocateHeap(length); std::strncpy(String::heap(), string, String::heapLength() = length); String::promoteToHeap(); }
        constexpr inline void initiateStack(char const string[], size_t const length) noexcept { char *const stack = String::stack(); *(stack + length) = '\0'; std::strncpy(stack, string, length); }

    // [...]
    public:
        // [Constructor]
        constexpr inline String(size_t const length) : value{0} { if (length >= STRING_STACK_LENGTH - 1u) String::allocateHeap(length); }
        constexpr inline String(char string[]) : value{0} { String::initiate(string, std::strlen(string)); }
        constexpr inline String(char const string[]) : value{0} { String::initiate(string, std::strlen(string)); }
        template <size_t length> constexpr inline String(char (&string)[length]) : value{0} { String::initiate(string, length); }
        template <size_t length> constexpr inline String(char const (&string)[length]) : value{0} { String::initiate(string, length); }
        constexpr inline String(char string[], size_t const length) : value{0} { String::initiate(string, length); }
        constexpr inline String(char const string[], size_t const length) : value{0} { String::initiate(string, length); }

        // [Destructor]
        inline ~String(void) { std::free((void*) (String::heapIsDefined() * (intptr_t) String::heap())); }

        // [Operator] > ...
        inline String& operator =(char string[]) { String::initiate(string, std::strlen(string)); return *this; }
        inline String& operator =(char const string[]) { String::initiate(string, std::strlen(string)); return *this; }
        template <size_t length> inline String& operator =(char (&string)[length]) { String::initiate(string, length); return *this; }
        template <size_t length> inline String& operator =(char const (&string)[length]) { String::initiate(string, length); return *this; }
        inline operator char*(void) const noexcept { return /* this -> value + 1 */ String::heapIsDefined() ? *(String::heap() + String::heapLength()) = '\0', String::heap() : String::stack(); }
};

int main(void) {
    String const string = "This message probably has to be greater than thirty-two (32) characters long.";
    std::cout << "[STRING]: \""; std::cout << string; std::cout << "\"\n";
}
