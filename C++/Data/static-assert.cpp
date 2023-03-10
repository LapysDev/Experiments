#include <cstddef>

/* ... ->> May raise a C++11 compatibility warning for the class name used here */
template <bool>
union static_assert {
  inline static_assert(char const[]) throw() {}
};

template <> // ... ->> or just undefine the falsy definition
union static_assert<false> {
  private:
    template <typename, unsigned char = 0x0u>
    union literal_assert;

    template <unsigned char specialization>
    union literal_assert<char const, specialization> {};

  public:
    template <typename type, std::size_t capacity>
    inline static_assert(type (&)[capacity]) throw(static_assert<false>) {
      // ... ->> In case for some reason the `static_assert(...)` macro was `#undef`
      literal_assert<type>();

      // ... ->> Something along the lines of `std::exit(...)` and such would do,
      //         not sure how freestanding environments may handle this
      throw static_assert<false>(*this);
    }
};

#define static_assert__(id, condition, message) static_assert<(condition)> _ ## id = static_assert<(condition)>("" message "");
#define static_assert_(id, condition, message)  static_assert__(id, condition, message)
#define static_assert(condition, message)       static_assert_(__LINE__, condition, message)

/* Main */
int main(int, char*[]) /* noexcept */ {
  static_assert(true,  "TRUE");
  static_assert(false, "FALSE");
}
