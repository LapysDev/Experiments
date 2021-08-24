template <typename type>
type* aligned_alloc(std::size_t const alignment = alignof(type)) {
    void *allocation = std::malloc(69u * sizeof(type));
    return static_cast<type*>(
        // could be `NULL`
        std::align(alignment, sizeof(type), allocation, 69u * sizeof(type))
    );
}

aligned_alloc<int>();
