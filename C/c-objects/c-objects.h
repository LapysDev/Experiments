/* Logic */
#ifndef C_OBJECTS
    /* Definition */
    #define C_OBJECTS

    /* Global */
        // Heap (Maximum Size)
        const int HEAP_MAXIMUM_SIZE = 10;
        static int HEAP[10];

    /* Functions */
        // Delete, New
        void delete(void*);
        void* new(void* Type, ...) {
            int* POINTER = HEAP + 1;
            while (POINTER != HEAP) { if (!*POINTER) break; POINTER += 1; }
            *POINTER = HEAP_MAXIMUM_SIZE;
            return POINTER;
        }

    typedef void* Set;
    typedef void* SetItem;

    void add(Set, SetItem);
    void contains(Set, SetItem);
    void drop(Set, SetItem);
    void isEqualTo(SetItem, SetItem);
#endif
