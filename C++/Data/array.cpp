#include <cstddef>
#include <cstdio>
#if defined(__cplusplus) && __cplusplus == 199711L
# include <cstdarg>
#endif

#include <new>

/* ... */
namespace {
    namespace { union null_t {}; }

    template <std::size_t, typename = null_t, typename = null_t> union conditional_t;
    template <typename base> union conditional_t<false, base> {};
    template <typename base> union conditional_t<true , base> { typedef base type; };
    template <typename true_t, typename false_t> union conditional_t<false, true_t, false_t> { typedef false_t type; };
    template <typename true_t, typename false_t> union conditional_t<true , true_t, false_t> { typedef true_t  type; };

    template <typename base, typename = conditional_t<sizeof(base)> > struct has_default_constructor { static bool const value = false; };
    template <typename base> struct has_default_constructor<base, conditional_t<sizeof((base()))> >  { static bool const value = true ; };

    template <typename> struct is_scalar_t                                                             { static bool const value = false; };
    template <> struct is_scalar_t<bool>                                                               { static bool const value = true ; };
    template <> struct is_scalar_t<char>                                                               { static bool const value = true ; };
    template <> struct is_scalar_t<double>                                                             { static bool const value = true ; };
    template <> struct is_scalar_t<float>                                                              { static bool const value = true ; };
    template <> struct is_scalar_t<int>                                                                { static bool const value = true ; };
    template <> struct is_scalar_t<long>                                                               { static bool const value = true ; };
    template <> struct is_scalar_t<long double>                                                        { static bool const value = true ; };
    template <> struct is_scalar_t<short>                                                              { static bool const value = true ; };
    template <> struct is_scalar_t<signed char>                                                        { static bool const value = true ; };
    template <> struct is_scalar_t<unsigned char>                                                      { static bool const value = true ; };
    template <> struct is_scalar_t<unsigned int>                                                       { static bool const value = true ; };
    template <> struct is_scalar_t<unsigned long>                                                      { static bool const value = true ; };
    template <> struct is_scalar_t<unsigned short>                                                     { static bool const value = true ; };
    template <> struct is_scalar_t<wchar_t>                                                            { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base const>                                            { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base const volatile>                                   { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base volatile>                                         { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base*>                                                 { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base* const>                                           { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base* const volatile>                                  { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base* volatile>                                        { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base (*)[]>                                            { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base (*const)[]>                                       { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base (*const volatile)[]>                              { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base (*volatile)[]>                                    { static bool const value = true ; };
    template <typename base, std::size_t length> struct is_scalar_t<base (*)[length]>                  { static bool const value = true ; };
    template <typename base, std::size_t length> struct is_scalar_t<base (*const)[length]>             { static bool const value = true ; };
    template <typename base, std::size_t length> struct is_scalar_t<base (*const volatile)[length]>    { static bool const value = true ; };
    template <typename base, std::size_t length> struct is_scalar_t<base (*volatile)[length]>          { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base (*)(...)>                                         { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base (*const)(...)>                                    { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base (*const volatile)(...)>                           { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base (*volatile)(...)>                                 { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base (*)(void)>                                        { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base (*const)(void)>                                   { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base (*const volatile)(void)>                          { static bool const value = true ; };
    template <typename base> struct is_scalar_t<base (*volatile)(void)>                                { static bool const value = true ; };
    template <typename base, typename object> struct is_scalar_t<base (object::*)(...)>                { static bool const value = true ; };
    template <typename base, typename object> struct is_scalar_t<base (object::*const)(...)>           { static bool const value = true ; };
    template <typename base, typename object> struct is_scalar_t<base (object::*const volatile)(...)>  { static bool const value = true ; };
    template <typename base, typename object> struct is_scalar_t<base (object::*volatile)(...)>        { static bool const value = true ; };
    template <typename base, typename object> struct is_scalar_t<base (object::*)(void)>               { static bool const value = true ; };
    template <typename base, typename object> struct is_scalar_t<base (object::*const)(void)>          { static bool const value = true ; };
    template <typename base, typename object> struct is_scalar_t<base (object::*const volatile)(void)> { static bool const value = true ; };
    template <typename base, typename object> struct is_scalar_t<base (object::*volatile)(void)>       { static bool const value = true ; };
    #if defined(__cplusplus) && __cplusplus > 199711L
      template <> struct is_scalar_t<long long>                                                                                          { static bool const value = true; };
      template <> struct is_scalar_t<unsigned long long>                                                                                 { static bool const value = true; };
      template <typename base> struct is_scalar_t<base (*)(...) noexcept>                                                                { static bool const value = true; };
      template <typename base> struct is_scalar_t<base (*const)(...) noexcept>                                                           { static bool const value = true; };
      template <typename base> struct is_scalar_t<base (*const volatile)(...) noexcept>                                                  { static bool const value = true; };
      template <typename base> struct is_scalar_t<base (*volatile)(...) noexcept>                                                        { static bool const value = true; };
      template <typename base> struct is_scalar_t<base (*)(void) noexcept>                                                               { static bool const value = true; };
      template <typename base> struct is_scalar_t<base (*const)(void) noexcept>                                                          { static bool const value = true; };
      template <typename base> struct is_scalar_t<base (*const volatile)(void) noexcept>                                                 { static bool const value = true; };
      template <typename base> struct is_scalar_t<base (*volatile)(void) noexcept>                                                       { static bool const value = true; };
      template <typename base, typename object> struct is_scalar_t<base (object::*)(...) noexcept>                                       { static bool const value = true; };
      template <typename base, typename object> struct is_scalar_t<base (object::*const)(...) noexcept>                                  { static bool const value = true; };
      template <typename base, typename object> struct is_scalar_t<base (object::*const volatile)(...) noexcept>                         { static bool const value = true; };
      template <typename base, typename object> struct is_scalar_t<base (object::*volatile)(...) noexcept>                               { static bool const value = true; };
      template <typename base, typename object> struct is_scalar_t<base (object::*)(void) noexcept>                                      { static bool const value = true; };
      template <typename base, typename object> struct is_scalar_t<base (object::*const)(void) noexcept>                                 { static bool const value = true; };
      template <typename base, typename object> struct is_scalar_t<base (object::*const volatile)(void) noexcept>                        { static bool const value = true; };
      template <typename base, typename object> struct is_scalar_t<base (object::*volatile)(void) noexcept>                              { static bool const value = true; };
      template <typename base, typename... types> struct is_scalar_t<base (*)(types...)>                                                 { static bool const value = true; };
      template <typename base, typename... types> struct is_scalar_t<base (*)(types...) noexcept>                                        { static bool const value = true; };
      template <typename base, typename... types> struct is_scalar_t<base (*const)(types...)>                                            { static bool const value = true; };
      template <typename base, typename... types> struct is_scalar_t<base (*const)(types...) noexcept>                                   { static bool const value = true; };
      template <typename base, typename... types> struct is_scalar_t<base (*const volatile)(types...)>                                   { static bool const value = true; };
      template <typename base, typename... types> struct is_scalar_t<base (*const volatile)(types...) noexcept>                          { static bool const value = true; };
      template <typename base, typename... types> struct is_scalar_t<base (*volatile)(types...)>                                         { static bool const value = true; };
      template <typename base, typename... types> struct is_scalar_t<base (*volatile)(types...) noexcept>                                { static bool const value = true; };
      template <typename base, typename object, typename... types> struct is_scalar_t<base (object::*)(types...)>                        { static bool const value = true; };
      template <typename base, typename object, typename... types> struct is_scalar_t<base (object::*)(types...) noexcept>               { static bool const value = true; };
      template <typename base, typename object, typename... types> struct is_scalar_t<base (object::*const)(types...)>                   { static bool const value = true; };
      template <typename base, typename object, typename... types> struct is_scalar_t<base (object::*const)(types...) noexcept>          { static bool const value = true; };
      template <typename base, typename object, typename... types> struct is_scalar_t<base (object::*const volatile)(types...)>          { static bool const value = true; };
      template <typename base, typename object, typename... types> struct is_scalar_t<base (object::*const volatile)(types...) noexcept> { static bool const value = true; };
      template <typename base, typename object, typename... types> struct is_scalar_t<base (object::*volatile)(types...)>                { static bool const value = true; };
      template <typename base, typename object, typename... types> struct is_scalar_t<base (object::*volatile)(types...) noexcept>       { static bool const value = true; };
    #endif

    template <typename> struct lengthof;
    template <typename base, std::size_t length> struct lengthof<base [length]> { static std::size_t const value = length; };

    template <typename base> union to_mutable_t             { typedef base type; };
    template <typename base> union to_mutable_t<base const> { typedef base type; };
}

// ...
template <typename base, std::size_t capacity>
struct array {
    typedef typename conditional_t<
        is_scalar_t<base>::value,
        base [capacity], unsigned char [sizeof(base [capacity])]
    >::type array_t;

    private:
        array_t value;

        // ...
        template <std::size_t length>
        base (&cast(typename conditional_t<(capacity == length && true  == is_scalar_t<base>::value)>::type = typename conditional_t<true>::type()) const)[length] {
            return const_cast<base (&)[length]>(this -> value);
        }

        template <std::size_t length>
        base (&cast(typename conditional_t<(capacity == length && false == is_scalar_t<base>::value) || (capacity > length)>::type = typename conditional_t<true>::type()) const)[length] {
            base (*evaluation)[length];
            array_t *value = const_cast<array_t*>(&(this -> value));

            for (unsigned char *destination = static_cast<unsigned char*>(static_cast<void*>(&evaluation)) + sizeof(void*), *source = static_cast<unsigned char*>(static_cast<void*>(&value)) + sizeof(void*); source != static_cast<void*>(&value); )
            *--destination = *--source;

            return *evaluation;
        }

        // ...
        template <typename type>
        void destruct(typename conditional_t<false == is_scalar_t<type>::value>::type = typename conditional_t<true>::type()) {
            unsigned char *value = this -> value;

            for (std::size_t iterator = capacity; iterator--; value += sizeof(base))
            static_cast<base*>(static_cast<void*>(value)) -> ~base();
        }

        template <typename type>
        void destruct(typename conditional_t<true  == is_scalar_t<type>::value>::type = typename conditional_t<true>::type()) {}

        // ...
        template <typename type>
        void instantiate(type array[], typename conditional_t<false == is_scalar_t<type>::value, std::size_t>::type length) {
            for (unsigned char *value = this -> value; length--; ++array, value += sizeof(base))
            new (value) base(*array);
        }

        template <typename type>
        void instantiate(type array[], typename conditional_t<true  == is_scalar_t<type>::value, std::size_t>::type const length) {
            array += length;

            for (typename to_mutable_t<base>::type *value = const_cast<typename to_mutable_t<base>::type*>(this -> value + length); value != this -> value; )
            *--value = *--array;
        }

        #if defined(__cplusplus) && __cplusplus == 199711L
          template <typename type>
          void instantiate(std::va_list const array, typename conditional_t<false == is_scalar_t<type>::value, std::size_t>::type length) {
            for (unsigned char *value = this -> value; length--; value += sizeof(base)) {
                base *element;
                new (value) base(
                    *static_cast<base*>(static_cast<void*>(va_arg(array, unsigned char[sizeof(base)])))
                );
            }
          }

          template <typename type>
          void instantiate(std::va_list const array, typename conditional_t<true  == is_scalar_t<type>::value, std::size_t>::type length) {
            for (typename to_mutable_t<base>::type *value = const_cast<typename to_mutable_t<base>::type*>(this -> value); length--; ++value)
            *value = va_arg(array, base);
          }
        #endif

    public:
        array(void) : value() {}

        template <std::size_t length>
        array(typename conditional_t<(capacity >= length), base>::type (&array)[length]) : value() {
            this -> instantiate<base>(array, length);
        }

        #if defined(__cplusplus) && __cplusplus == 199711L
          array(std::size_t const count, ...) : value() {
            std::va_list elements;

            va_start(elements, count);
            this -> instantiate<base>(elements, count);
            va_end(elements);
          }
        #else
          template <typename... types>
          array(typename conditional_t<(capacity >= sizeof...(types)), std::size_t>::type const count, types&&... elements) : value{} {
            base array[sizeof...(types)] = {static_cast<base>(elements)...};
            this -> instantiate<base>(array, count);
          }
        #endif

        ~array(void) { this -> destruct<base>(); }

        // ...
        #if defined(__cplusplus) && __cplusplus > 199711L
          base* begin(void) const { return this -> cast<capacity>(); }
          base* end(void) const { return this -> cast<capacity>() + capacity; }
        #endif

        // ...
        base* operator ->(void) const { return this -> cast<capacity>(); }

        operator base*(void) const { return this -> cast<capacity>(); }
        template <typename type> operator type&(void) const { return this -> cast<lengthof<type>::value>(); }
};

/* Main */
#include <cstdio>
#include <string>

// ...
class String {
    private: char const *const value;
    public:
        String(char const value[]) : value(value) {}
        operator char const*(void) const { return this -> value; }
};

// ...
int main(void) {
    // : [Conversions]
    // std::printf("[char const*]    : \"%s\"" "\r\n", static_cast<char const*>(array<char const, 14u>("Hello, World!")));
    // std::printf("[char const [5]] : \"%s\"" "\r\n", static_cast<char const (&)[5]>(array<char const, 14u>("Hello, World!")));
    // std::printf("[char const [14]]: \"%s\"" "\r\n", static_cast<char const (&)[14]>(array<char const, 14u>("Hello, World!")));

    // std::printf("[String]         : \"%s\"" "\r\n", (*array<String, 1u>(1u, "Hello, World!")).operator char const*());
    // std::printf("[String]         : \"%s\"" "\r\n", array<String, 1u>(1u, "Hello, World!") -> operator char const*());
    // std::printf("[String]         : \"%s\"" "\r\n", array<String, 1u>(1u, "Hello, World!")[0].operator char const*());

    array<std::string, 1u>(1u, "Hello, World!");
    // std::printf("[std::string]    : \"%s\"" "\r\n", (*array<std::string, 1u>(1u, "Hello, World!")).c_str());
    // std::printf("[std::string]    : \"%s\"" "\r\n", array<std::string, 1u>(1u, "Hello, World!") -> c_str());
    // std::printf("[std::string]    : \"%s\"" "\r\n", array<std::string, 1u>(1u, "Hello, World!")[0].c_str());

    // : [Iteration] ->> The `iterable` is immutable, but its `const`-ness doesn't apply to its elements/ members (it respects the cv-qualification of its specified type)
    array<int, 10> const iterable = array<int, 10>(10u, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

    std::printf("%13s", "[int [10]]: {");
      for (std::size_t iterator = 0u; iterator != 10u; ++iterator) iterable[iterator] += 1;
      for (std::size_t iterator = 0u; iterator != 10u; ++iterator) std::printf("%i%.2s", iterable[iterator], iterator == 10u - 1u ? "" : ", ");
    std::printf("%3s", "}" "\r\n");

    std::printf("%13s", "[int [10]]: {");
      for (int *iterator = iterable; iterator - iterable != 10L; ++iterator) *iterator += 1;
      for (int *iterator = iterable; iterator - iterable != 10L; ++iterator) std::printf("%i%.2s", *iterator, iterator - iterable == 10L - 1L ? "" : ", ");
    std::printf("%3s", "}" "\r\n");

    #if defined(__cplusplus) && __cplusplus > 199711L
      std::printf("%13s", "[int [10]]: {");
        for (int& element : iterable) element += 1;
        for (int  element : iterable) std::printf("%i, ", element);
      std::printf("%3s", "}" "\r\n");
    #endif
}
