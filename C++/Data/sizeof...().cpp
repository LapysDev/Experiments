template<std::size_t N>
struct any_counter
{
    any_counter() {}

    template<typename T>
    any_counter<N + 1> operator,(const T&)
    {
        return any_counter<N + 1>();
    }

    char array[N + 1];
};

#define arg_count(...) (sizeof(any_counter<0>(),##__VA_ARGS__)-1)
