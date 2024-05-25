#include <ciso646>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <new>
#include <utility>

/* ... */
template <typename base>
struct array final {
  template <typename>
  friend struct array;

  private:
    alignas(base) static unsigned char root[sizeof(base)];

    std::FILE  *value;
    std::size_t length;

  public:
    array() :
      value (std::tmpfile()),
      length(0u)
    {}

    template <typename type>
    array(array<type> const& array) /* throw(...) */ :
      array::array()
    {
      for (std::size_t index = 0u; index != array.length; ++index) {
        type *const element = array.at(index);
        if (NULL == element or not this -> add(*element)) break; // --> throw ...;
      }
    }

    array(array<base>&& array) :
      value (array.value),
      length(array.length)
    {}

    // ...
    ~array() {
      if (NULL != this -> value) {
        (void) this -> empty();            // ->> Leaked destructors if `false`
        (void) std::fclose(this -> value); // ->> "Leaked" file stream if `EOF`
        
        this -> length = 0u;
        this -> value  = NULL;
      }
    }

    /* ... */
    template <typename type>
    bool add(type&& value) {
      if (
        LONG_MAX >  this -> length * sizeof(base) and
        NULL     != this -> value                 and
        (0u == this -> length or 0 == std::fseek(this -> value, this -> length * sizeof(base), SEEK_SET))
      ) {
        if (std::fwrite(::new (this -> root) base(std::forward<type>(value)), sizeof(base), 1u, this -> value) == 1u)
        return ++(this -> length), true;
      }

      return false;
    }

    base* at(std::size_t const index) const {
      if (
        index <  this -> length and
        0u    != this -> length and
        NULL  != this -> value  and
        (0u == index ? std::rewind(this -> value), true : 0 == std::fseek(this -> value, index * sizeof(base), SEEK_SET))
      ) {
        if (std::fread(this -> root, sizeof(base), 1u, this -> value) == 1u)
        return std::launder((base*) this -> root);
      }

      return NULL;
    }

    bool empty() {
      while (this -> length) {
        if (not this -> pop())
        return false;
      }

      return true;
    }

    std::size_t lengthof() const {
      return this -> length;
    }

    bool pop() {
      if (0u != this -> length and NULL != this -> value) {
        base *const element = this -> at(this -> length - 1u);

        // ...
        if (NULL == element)
          return false;

        element -> ~base();
        --(this -> length);
      }

      return true;
    }

    // ...
    template <typename type>
    array& operator =(array<type> const& array)& /* throw(...) */ {
      for (std::size_t index = 0u, length = this -> length; index != array.length; ++index) {
        type *const element = array.at(index);

        // ...
        if (NULL == element)
        break; // --> throw ...;

        // ...
        if (index < length) {
          base *const subelement = this -> at(index);

          // ...
          if (NULL == subelement)
            break; // --> throw ...;
          
          *subelement = *element;
        }

        else if (not this -> add(*element))
          break; // --> throw ...;
      }

      return *this;
    }

    base& operator [](std::size_t const index) const {
      return *(this -> at(index));
    }
};
  template <typename base>
  alignas(base) unsigned char array<base>::root[sizeof(base)] = {};

/* Main */
struct int_echo_t final {
  int value;

  int_echo_t(int const value = 0) : value(value) { std::printf("[...]: new {%i}" "\r\n", value); }
  ~int_echo_t() { std::printf("[...]: delete int {%i}" "\r\n", this -> value); }

  operator int&() /* const */ { return this -> value; }
};

int main(int, char*[]) /* noexcept */ {
  array<int_echo_t> integers = {};

  // ...
  integers.add(1);
  integers.add(2);
  integers.add(3);

  std::printf("[]: (%zu)" " ", integers.lengthof());
  for (std::size_t index = 0u; index != integers.lengthof(); ++index)
    std::printf("%i" " ", (int) integers[index]);
  std::printf("\r\n");

  integers.pop();

  std::printf("[]: (%zu)" " ", integers.lengthof());
  for (std::size_t index = 0u; index != integers.lengthof(); ++index)
    std::printf("%i" " ", (int) integers[index]);
  std::printf("\r\n");

  integers.empty();

  std::printf("[]: (%zu)", integers.lengthof());
}
