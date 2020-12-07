/* Import */
    // [C Standard Library]
    #include <stdlib.h> // Standard Library
    #include <stdio.h> // Standard Input-Output
    #include <time.h> // Time

    // [Platform-Specific]
    #if defined(__ANDROID__) // Android
    #elif defined(__APPLE__ ) && defined(__MACH__) // Apple Macintosh
    #elif defined(__gnu_linux__) || defined(linux) || defined(__linux) || defined(__linux__) // Linux
    #  include <sys/mman.h> // Memory Manipulation
    #  include <unistd.h> // UNIX Standard
    #elif defined(__TOS_WIN__) || defined(_WIN16) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__) // Microsoft Windows
    #  include <windows.h> // Windows
    #endif

/* Class > Derived */
class Derived {
    // [...]
    protected:
        // Definition > Base
        void *Base;

    // [...]
    public:
        // [Constructor]
        // : [Operator] > [...]
        constexpr inline Derived(const void* base) : Base{(void*) base} {}
        constexpr inline Derived(void) : Base{0x0} {}

        inline operator void*(void) const noexcept { return this -> Base; }
};

/* Namespace > Memory Pool */
class MemoryPool { friend int main(void);
    // [...]
    private:
        // Definition
            // ... --- NOTE (Lapys) -> `unsigned char` is smaller than the `void*` type.
            typedef alignas(1) unsigned char MemoryBlock;

            // (Memory ..., ... Size)
            std::size_t evaluatedSize;
            MemoryBlock *memory;
            struct MemoryInformationList { friend MemoryPool; friend int main(void);
                // [...]
                protected:
                    // Definition > (Length, Value)
                    std::size_t length;
                    class MemoryInformation { friend MemoryPool; friend int main(void);
                        // [...]
                        private:
                            // Definition > (Index, Memory, Size)
                            std::size_t index;
                            void *memory;
                            std::size_t size;

                        // [...]
                        public:
                            // [Constructor]
                            constexpr inline MemoryInformation(const void* memory, const std::size_t index, const std::size_t size) : index{index}, memory{(void*) memory}, size{size} {}

                            // [Operator] > [=]
                            inline MemoryInformation& operator =(MemoryInformation&& memoryInformation) noexcept { this -> index = memoryInformation.index; this -> memory = memoryInformation.memory; this -> size = memoryInformation.size; return *this; }
                            inline MemoryInformation& operator =(const MemoryInformation& memoryInformation) noexcept { this -> index = memoryInformation.index; this -> memory = memoryInformation.memory; this -> size = memoryInformation.size; return *this; }
                    } *value;

                // [...]
                public:
                    // [Constructor]
                    constexpr inline MemoryInformationList(void) : length{0u}, value{(MemoryInformation*) std::malloc(1024u)} {}

                    // [Destructor]
                    inline ~MemoryInformationList(void) { std::free(this -> value); }

                    // Function
                        // Expand
                        void expand(void) noexcept {
                            // Initialization > (Length, ... Size)
                            std::size_t length = 1024u / sizeof(MemoryInformation);
                            std::size_t recentSize = 0u;
                            std::size_t size = 1u;

                            // Logic > Update > (Length, ... Size)
                            if (length < this -> length) length = this -> length;
                            for (std::size_t formerSize; size <= length; ) { formerSize = size; size += recentSize; recentSize = formerSize; }

                            // Logic > Modification > Target > Value
                            if (this -> length == recentSize) this -> value = (MemoryInformation*) std::realloc(this -> value, size * sizeof(MemoryInformation));
                        }

                        // Get By Memory
                        inline const MemoryInformation* getByMemory(const void* memory) const noexcept {
                            // Loop > Logic > Return
                            for (std::size_t iterator = 0u; iterator ^ this -> length; ++iterator)
                            if ((this -> value + iterator) -> memory == memory)
                                return this -> value + iterator;

                            // Return
                            return 0x0;
                        }

                        // Get By Unallocated Index --- NOTE (Lapys) -> Deceivingly straight-forward because the list is always sorted.
                        inline const MemoryInformation* getByUnallocatedIndex(void) const noexcept { return this -> value + (this -> length - 1u); }

                        // Remove [By Memory]
                        void remove(const void* memory) noexcept {
                            // Loop > Logic
                            for (std::size_t iterator = 0u; iterator ^ this -> length; ++iterator)
                            if ((this -> value + iterator) -> memory == memory) {
                                // (Loop > )Modification > Target > (Length, Value)
                                --(this -> length);
                                for (; iterator ^ this -> length; ++iterator) *(this -> value + iterator) = *(this -> value + (iterator + 1u));

                                // Terminate
                                iterator = this -> length - 1u;
                            }
                        }
            } memoryInformationList;
            std::size_t size;

            // ...
            typedef MemoryInformationList::MemoryInformation MemoryInformation;

        // Function
            // Get Allocation Size
            inline static std::size_t getAllocationSize(const std::size_t size) noexcept {
                /* Define > ... */
                #define ALLOCATION_TYPE
                #  define ALIGNED_ALLOCATION 1
                #  define PRECISE_ALLOCATION 2
                #  define EVEN_ALLOCATION 3
                #undef ALLOCATION_TYPE
                #define ALLOCATION_TYPE ALIGNED_ALLOCATION

                // Logic
                #if ALLOCATION_TYPE == ALIGNED_ALLOCATION
                    // Initialization > Allocation Size
                    std::size_t allocationSize = 2u;
                    std::size_t recentAllocationSize;

                    // Update > ... Allocation Size
                    while (allocationSize < size) {
                        recentAllocationSize = allocationSize;
                        allocationSize <<= 1u;
                    } allocationSize = recentAllocationSize;

                    // Logic
                    if (allocationSize < size) {
                        // Constant > Page Size
                        const std::size_t pageSize = MemoryPool::getPageSize();

                        // Logic > Loop > Update > Allocation Size
                        if (allocationSize < pageSize) while (allocationSize < size) allocationSize += sizeof(std::size_t);
                        else while (allocationSize < size) allocationSize += pageSize;
                    }

                    // (Loop > )Update > Allocation Size
                    if (allocationSize > sizeof(std::size_t)) { allocationSize -= sizeof(std::size_t); if (allocationSize < size) allocationSize += sizeof(std::size_t); }
                    while (allocationSize % sizeof(MemoryBlock)) ++allocationSize;

                    // Return
                    return allocationSize;
                #elif ALLOCATION_TYPE == EVEN_ALLOCATION
                    return size & 1u ? size + 1u : size;
                #elif ALLOCATION_TYPE == PRECISE_ALLOCATION
                    return size;
                #endif
            }

            // Get Memory
            inline const void* getMemory(std::size_t offset) const noexcept { return this -> memory + (offset / sizeof(MemoryBlock)); }

            // Get Page Size
            #if defined(__ANDROID__) // Android
                inline static long getPageSize(void) noexcept { return ::sysconf(_SC_PAGESIZE); }
            #elif defined(__APPLE__ ) && defined(__MACH__) // Apple Macintosh
            #elif defined(__gnu_linux__) || defined(linux) || defined(__linux) || defined(__linux__) // Linux
                inline static long getPageSize(void) noexcept { return ::sysconf(_SC_PAGESIZE); }
            #elif defined(__TOS_WIN__) || defined(_WIN16) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN32_WCE) || defined(_WIN64) || defined(__WINDOWS__) // Microsoft Windows
                inline static long getPageSize(void) noexcept { SYSTEM_INFO systemInformation; ::GetSystemInfo(&systemInformation); return systemInformation.dwPageSize; }
            #endif

    // [...]
    protected:
        // Function
            // Expand Memory
            void expandMemory(void);

            // Shrink Memory
            void shrinkMemory(void);

    // [...]
    public:
        // [Constructor]
        inline MemoryPool(void) : evaluatedSize{(std::size_t) MemoryPool::getPageSize()}, memory{0x0}, memoryInformationList{}, size{0u} { this -> memory = (MemoryBlock*) std::malloc(this -> evaluatedSize); }

        // [Destructor]
        ~MemoryPool(void) { std::free(this -> memory); }

        // Function
            // Allocate
            const void* allocate(std::size_t size) noexcept {
                // Initialization > Offset
                std::size_t offset = 0u;

                // Update > Size
                // Modification > Target > Size
                size = MemoryPool::getAllocationSize(size);
                this -> size += size;

                // Logic
                if (this -> size >= this -> evaluatedSize) {
                    // Modification > Target > (Evaluated Size, Memory)
                    this -> evaluatedSize <<= 1u;
                    this -> memory = (MemoryBlock*) std::realloc(this -> memory, this -> evaluatedSize);
                }

                // Logic > Loop
                if (this -> memoryInformationList.length)
                for (std::size_t memoryInformationListIterator = 0u; memoryInformationListIterator ^ this -> memoryInformationList.length; ++memoryInformationListIterator) {
                    // Initialization > Memory Information
                    MemoryInformation *memoryInformation = this -> memoryInformationList.value + memoryInformationListIterator;

                    // Logic
                    if (memoryInformation -> index == offset)
                        // Update > Offset
                        offset = memoryInformation -> index + memoryInformation -> size;

                    else if (memoryInformationListIterator + 1u == this -> memoryInformationList.length) {
                        // Update > Memory Information
                        memoryInformation = this -> memoryInformationList.value + (memoryInformationListIterator + 1u);

                        // Logic > Update > Offset
                        if (offset + size >= memoryInformation -> index)
                        offset = memoryInformation -> index + memoryInformation -> size;
                    }
                }

                // Declaration > Memory ...
                const void *memory = MemoryPool::getMemory(offset);
                bool memoryInformationListIsSorted = true;

                // Modification > Target > Memory Information List
                this -> memoryInformationList.expand();

                // Loop --- NOTE (Lapys) -> Record the information into the list (to preserve the order of the list).
                for (std::size_t memoryInformationListIterator = 0u; memoryInformationListIterator ^ this -> memoryInformationList.length; ++memoryInformationListIterator) {
                    // Initialization > Memory Information
                    MemoryInformation *memoryInformation = this -> memoryInformationList.value + memoryInformationListIterator;

                    // Logic
                    if (offset < memoryInformation -> index) {
                        // Initialization > Memory Information List Index
                        std::size_t memoryInformationListIndex = memoryInformationListIterator;

                        // Update > Memory Information List Iterator
                        memoryInformationListIterator = this -> memoryInformationList.length;

                        // Loop > Modification > (Target > Memory Information List) > Value
                        for (++memoryInformationListIndex; memoryInformationListIndex ^ memoryInformationListIterator--; ) *(this -> memoryInformationList.value + memoryInformationListIterator) = *(this -> memoryInformationList.value + memoryInformationListIterator - 1);

                        // Update > Memory Information ...
                        *memoryInformation = MemoryInformation(memory, offset, size);

                        memoryInformationListIsSorted = false;
                        memoryInformationListIterator = this -> memoryInformationList.length - 1u;
                    }
                }

                // Logic > Modification > (Target > Memory Information List) > Value --- NOTE (Lapys) -> Record the information at the end of the list.
                if (memoryInformationListIsSorted)
                *(this -> memoryInformationList.value + this -> memoryInformationList.length) = MemoryInformation(memory, offset, size);

                // Modification > (Target > Memory Information List) > Length
                ++(this -> memoryInformationList.length);

                // Return
                return memory;
            }

            // De-Allocate
            void deallocate(const void* pointer) noexcept {
                // Modification > Target > (Size, Memory Information List)
                this -> size -= this -> memoryInformationList.getByMemory(pointer) -> size;
                this -> memoryInformationList.remove(pointer);
            }

            // Re-Allocate
            const void* reallocate(const void* pointer, const std::size_t size);
} MemoryPool;

/* Main */
int main(void) {
    /* ... */
    ::printf("[PROGRAM INITIATED]\n\r"); {
        // Definition > ...
        #define BASIC_TEST true

        // Logic
        #if BASIC_TEST
            // Initialization > Names ...
            unsigned short namesLength = (unsigned short) -1;

            // ...
            ::srand(::time(0x0));

            // ...; Loop
            std::size_t total = 0u;
            for (unsigned short namesIterator = 0u; namesIterator ^ namesLength; ++namesIterator) {
                // Initialization > Name Length
                unsigned char nameLength;

                // (Loop > )Update > (Name Length, Total)
                while (0u == nameLength) nameLength = (unsigned char) (::rand() % (int) (unsigned char) -1);
                total += nameLength;

                // ...; Print
                MemoryPool.allocate(nameLength * sizeof(char));
                ::printf("[DEBUG #%i]: %i of %i bytes for %i bytes\n\r", namesIterator + 1u, MemoryPool.size, MemoryPool.evaluatedSize, total * sizeof(char));
            }

        #else
            // Global > (Names ..., Records) --- UPDATE (Lapys) -> Should be fetched from a record.
            unsigned short namesLength = (unsigned short) -1;
            char **names = (char**) std::malloc(namesLength * sizeof(char*));

            const char *record[354] {"Aaron", "Acton", "Ada", "Adel", "Aden", "Aeson", "Airgon", "Ajax", "Aldrich", "Alex", "Allen", "Alsop", "Amanra", "Amber", "Andromeda", "Angeal", "Anil", "Anorase", "Anthea", "Anthon", "Anthony", "Antoinette", "Arandi", "Arcas", "Arlie", "Asteria", "Asui", "August", "Aui", "Auspin", "Austin", "Ava", "Ave", "Avery", "Awais", "Bastian", "Bavor", "Bell", "Ben", "Benhart", "Bethel", "Bishop", "Blaise", "Bordy", "Brent", "Burkey", "Burn", "Byrne", "Byt", "B-Han", "Caius", "Calix", "Carmi", "Carola", "Carrion", "Carter", "Cassie", "Castle", "Castor", "Celeste", "Celestine", "Chandra", "Chaplin", "Chastain", "Chelise", "Chloe", "Chrystin", "Clair", "Claus", "Clay", "Cloud", "Clyde", "Cy", "Cygnus", "Cyrus", "Daemon", "Dan", "Dane", "Dante", "Darchin", "Darcy", "Darius", "Darkheim", "Dave", "Dawn", "Dax", "Daxter", "Day", "Deimos", "Dent", "Destain", "Destiny", "Deuce", "Devin", "Donovan", "Donquiote", "Dot", "Dwayne", "Edward", "Efosa", "Eldo", "Eli", "Elrik", "Elsevier", "Eoith", "Er", "Erd", "Esrever", "Esther", "Euross", "Eustace", "Eve", "Fabin", "Faust", "Fawkes", "Felix", "Ferra", "Figo", "Fiora", "Flora", "Forsyth", "Freydis", "Funto", "Gad", "Garneau", "Garreau", "Garth", "Giben", "Gilga", "Ginger", "Gladys", "Gold", "Gpher", "Griffin", "Guntr", "Halberd", "Haurvatat", "Havec", "Hazel", "Honey", "Ingrid", "Ingvar", "Ionna", "Iouis", "Irina", "Ishmael", "Iulia", "Jachial", "Jachin", "Jacquez", "Jaden", "Jadok", "Jamal", "Jamison", "Jan", "Janae", "Janis", "Janvi", "Jarchin", "Jason", "Javier", "Jeanne", "Jedial", "Jen", "Jenova", "Jenvi", "Jess", "Jinja", "Johann", "Joline", "Jordan", "Jorge", "Jorn", "Joshua", "Juan", "Judice", "Judin", "Julie", "June", "Keith", "Ken", "Kid", "Kidd", "Kim", "King", "Klein", "Ko", "Kofu", "Kon", "Kreuter", "Lance", "Larissa", "Lauda", "Leela", "Lentz", "Les", "Lex", "Leyvro", "Lin", "Linus", "Locke", "Lok", "Lotan", "Lotar", "Lothar", "Lucia", "Lycado", "Lynda", "Lynne", "Mac", "Mae", "Makarov", "Mako", "Marcin", "Marco", "Maric", "Marquez", "Maruez", "Marx", "Masato", "May", "Megan", "Meghari", "Merrick", "Milus", "Mina", "Mirza", "Morgan", "Mozhet", "Murdock", "Mycroft", "Naiad", "Naphtali", "Nathan", "Neil", "Nereid", "Nicole", "Night", "Nike", "Niko", "Nixon", "Nnoitra", "Noctor", "Nora", "Nwolise", "Oliver", "Orion", "Oslo", "Otite", "Otto", "Pearl", "Percival", "Percy", "Petriv", "Phine", "Piecke", "Pierce", "Pierre", "Pixis", "Pondy", "Price", "Quin", "Quinne", "Radul", "Rale", "Rayina", "Reginae", "Rei", "Reynold", "Rhen", "Richi", "Rick", "Rimisa", "Rin", "Rinta", "Rivald", "Robin", "Rodion", "Ronin", "Rook", "Rose", "Rostain", "Roy", "Royce", "Rule", "Rutledge", "Sacura", "Senna", "Sera", "Sethe", "Shaw", "Sheruib", "Shin", "Ra", "Shun", "Sigrid", "Silva", "Simon", "Sixto", "Slade", "Smough", "Sonya", "Sonna", "Stagner", "Stone", "Sue", "Sundar", "Sys", "Tagore", "Tanya", "Taylor", "Teresa", "Tesla", "Tiwa", "Tor", "Torvald", "Trace", "Tracy", "Tran", "Tristan", "Trubel", "Tsuna", "Tylor", "Vadal", "Valerie", "Vincent", "Virgil", "Vladmir", "Von", "Vos", "Vse", "Vyler", "Weah", "Wei", "Weiss", "Winston", "Wisteria", "Wordsworth", "Wunderweiss", "Xad", "Xavier", "Yitch", "Yoru", "Yu", "Yvette", "Ywach", "Yyvette", "Zadok", "Zeno", "Zeus", "Zidane", "Zora", "Zur", "Zuri"};

            // ...
            ::srand(::time(0x0));

            // Loop
            for (unsigned short iterator = 0u, length = 0u; length ^ namesLength; ) {
                // Initialization > (Names ..., ...)
                short namesIterator = 0u;

                const unsigned short recentLength = length;
                unsigned short total = 0u;

                // Loop
                for (; iterator ^ length; ++iterator) {
                    // Initialization > Name (Length)
                    const char *& name = record[::rand() % 354];
                    unsigned short nameLength = 0u;

                    // (Loop > )Update > (Name Length, ...)
                    for (char *nameIterator = (char*) name; *nameIterator; ++nameIterator) { ++nameLength; ++total; }
                    ++total;

                    // Update > Names (Iterator)
                    *(names + namesIterator) = (char*) MemoryPool.allocate((nameLength + 1u) * sizeof(char));
                    **(names + namesIterator) = **(names + namesIterator);

                    ++namesIterator;
                }

                // Logic > Print
                if (iterator) ::printf("[DEBUG]: %i of %i records\t(%i of %i bytes for %i bytes)\n\r", namesIterator, namesLength, MemoryPool.size, MemoryPool.evaluatedSize, total * sizeof(char));

                // Loop > Deletion
                while (namesIterator--) MemoryPool.deallocate(*(names + namesIterator));

                // Logic > Update > Length --- MINIFY (Lapys) --- NOTE (Lapys) -> Update the length randomly.
                if (length == namesLength - 1u) ++length; else { length += (unsigned short) (::rand() % (int) namesLength); if (length > namesLength || recentLength > length) length = namesLength - 1u; }
            }

            // Deletion
            std::free(names);
        #endif
    } ::printf("[PROGRAM TERMINATED]");

    // Return
    return EXIT_SUCCESS;
}
