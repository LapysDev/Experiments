#include <climits>
#include <cstddef>
#include <cstdio>
#include <new>
#include <stdint.h>

/* ... */
template <typename base, std::size_t size>
struct bigarray /* final */ {
  union {
    base elements[size];
    base value   [size];
  };

  private:
    std::size_t capacity;
    std::size_t length;
    base       *subvalue;

  public:
    void add() /* noexcept */ {}
    void find() /* noexcept */ {}
    void pop() /* noexcept */ {}
    void remove() /* noexcept */ {}

    /* ... --> std::malloc(), std::realloc() */
    void operator [](std::size_t const) /* noexcept */;
};

/* ... */
struct biguint /* final */ {
  private:
    bigarray<unsigned char, CHAR_BIT * sizeof(uintmax_t)> value;

  public:
    biguint(uintmax_t const = 0u) /* noexcept */ {}

    /* ... */
    operator uintmax_t() const /* noexcept */;
};

struct bigint /* final */ {
  private:
    biguint value;
    bool    signedness;

  public:
    bigint(intmax_t const = 0) /* noexcept */ {}
    bigint(biguint const) /* noexcept */ {}

    /* ... */
    operator intmax_t() const /* noexcept */;

    operator biguint() const /* noexcept */ {
      return this -> value;
    }
};

// ...
struct bignum /* final */ {
  private:
    struct operation /* final */ {
      operation  *next;
      std::size_t stepCount;

      // ...
    };

    /* ... */
    union {
      unsigned char initializer;
      bignum        exponent;

      ~() /* noexcept */ {}
    };

    bigint                  numerator;
    biguint                 denominator; // infinity has this as zero
    bigarray<operation, 1u> operations; // tree
    struct {
      bool e;
      bool ln;
      bool pi;
    } transcendental; // built up with `operation`s

  public:
    bignum(bigint const) /* noexcept */ {}
    bignum(biguint const) /* noexcept */ {}
    bignum(long double const) /* noexcept */ {}

    /* ... */
    operator long double() const /* noexcept */;

    operator bigint() const /* noexcept */;
    operator biguint() const /* noexcept */;
};

/* Main */
int main(int, char*[]) /* noexcept */ {}
