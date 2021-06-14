template <unsigned char index, typename type, typename... types>
struct typeindex : typeindex<index - 1u, types...> {};

template <typename type1, typename... types>
struct typeindex<0u, type1, types...> { typedef type1 type; };
