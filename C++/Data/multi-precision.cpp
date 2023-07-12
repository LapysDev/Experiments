#include <cfloat>  // --> LDBL_MAX
#include <ciso646> //
#include <climits> // --> ULONG_MAX
#include <cstddef> // --> std::size_t
#include <cstdio>  //
#include <cstdlib> // --> std::calloc(...), std::free(...), std::malloc(...), std::realloc(...)
#include <new>     // --> new

/* ... */
struct bignum {
  /* ... */
  private: template <typename base, std::size_t precapacity = 1u> struct array;
  public:  struct operation;

  /* ... */
  private:
    static unsigned char const radix = 10u; // ->> Must not be above the maximum representable value (`UCHAR_MAX`) per digit; Higher values are space efficient

  public:
    static bignum const EULER;
    static bignum const INFINITY;
    static bignum const ONE;
    static bignum const PI;
    static bignum const TAU;
    static bignum const ZERO;

  /* ... */
  private:
    template <typename base, std::size_t precapacity>
    struct array {
      friend struct operation;

      #if defined(__clang__)
      # pragma clang diagnostic ignored "-Wmissing-braces"
      # pragma clang diagnostic ignored "-Wmissing-field-initializers"
      #elif defined(__ICC) or defined(__INTEL_COMPILER) or defined(__INTEL_LLVM_COMPILER)
      # pragma warning (disable:3280)
      #elif defined(__GNUC__)
      # pragma GCC diagnostic ignored "-Wmissing-field-initializers"
      #elif defined(_MSC_VER)
      #endif

      private:
        struct allocation {
          template <typename subbase = void>
          struct storage {
            subbase    *value;
            std::size_t capacity; // ->> Maximum byte size of `subbase` elements altogether
          };

          // ...
          struct value {
            storage<>  *allocations;
            std::size_t capacity; // ->> Maximum byte size of `allocations`
            std::size_t size;     // ->> Number            of `allocations`

            /* ... */
            inline ~value() {
              for (this -> allocations += this -> size; this -> size; --(this -> size)) {
                storage<> *const allocation = /* --> std::launder(...) */ --(this -> allocations);

                // ...
                std::free(allocation -> value); // ->> `NULL` or otherwise

                allocation -> capacity = 0u;
                allocation -> value    = NULL;
              }

              std::free(this -> allocations); // ->> `NULL` or otherwise
              this -> allocations = NULL;
            }
          };

          /* ... */
          static value table; // ->> Static zero-initialized members
        };

        // ...
        template <typename subbase>
        struct baseof {
          typedef subbase type;
        };

        template <typename subbase> struct baseof<subbase const>          { typedef subbase type; };
        template <typename subbase> struct baseof<subbase const volatile> { typedef subbase type; };
        template <typename subbase> struct baseof<subbase       volatile> { typedef subbase type; };
        template <typename subbase> struct baseof<subbase&>               { typedef subbase type; };

        #ifdef __cpp_rvalue_references // --> 200610L
          template <typename subbase>
          struct baseof<subbase&&> {
            typedef subbase type;
          };
        #endif

        // ...
        struct length {
          private:
            mutable std::size_t value; // ->> Allow pointer inter-convertibility between `struct array::length` and `std::size_t`

            /* ... */
            inline std::size_t valueof() const {
              struct layout /* ->> Plain-Old Data/ Standard layout representation of `struct array` */ {
                /* alignas(sizeof array().elements) */ unsigned char value [sizeof array().elements];
                /* alignas(sizeof array().length)   */ unsigned char length[sizeof array().length];
              };

              return /* --> std::launder(...) */ reinterpret_cast<array const*>(reinterpret_cast<unsigned char const*>(this) - offsetof(layout, length)) -> lengthof();
            }

          public:
            inline length() :
              value(this -> valueof())
            {}

            /* ... */
            inline operator std::size_t() const {
              this -> value = this -> valueof();
              return this -> value;
            }
        };

        // ...
        template <typename subbase>
        struct storage : public allocation::template storage<subbase> {
          std::size_t length; // ->> Number of `subbase` elements
        };

        // ...
        template <typename subbase, std::size_t capacity = precapacity>
        struct value {
          struct element {
            union {
              /* alignas(base) */ unsigned char automatic[sizeof(base)];
              storage<subbase>                  dynamic;
            };
            subbase *value;

            /* ... */
            inline element() :
              dynamic(),
              value  (NULL)
            {
              this -> dynamic.capacity = 0u;
              this -> dynamic.length   = 0u;
              this -> dynamic.value    = NULL;
            }

            template <typename type>
            inline element(type const& value) :
              automatic(),
              value    (::new (this -> automatic) subbase(value))
            {}
          } value[capacity + 1u];
        };

        template <typename subbase>
        struct value<subbase, 0u> {
          struct element {
            union {
              storage<subbase> dynamic;
              unsigned char   *automatic;
            };
            subbase *value;

            /* ... */
            inline element() :
              dynamic(),
              value  (NULL)
            {
              this -> dynamic.capacity = 0u;
              this -> dynamic.length   = 0u;
              this -> dynamic.value    = NULL;
            }

            template <typename type>
            element(type const&) /* = delete */;
          } value[1u];
        };

        /* ... */
        typedef typename baseof<base>::type subbase;

        /* ... */
        bool allocate(std::size_t count) {
          typedef typename allocation::template storage<> storage;
          typename array::template storage<subbase> &dynamic = this -> elements.value[precapacity].dynamic;

          // ...
          if (count <= precapacity) {
            storage *allocation = NULL;

            // ... ->> Destruct `::dynamic` and excess `::automatic` elements in order
            for (subbase *iterator = dynamic.value + dynamic.length; iterator != dynamic.value; )
            (/* --> std::launder(...) */ --iterator) -> ~subbase();

            for (std::size_t index = precapacity; count != index; ) {
              if (NULL != this -> elements.value[--index].value)
              this -> elements.value[index].value -> ~subbase();
            }

            for (std::size_t index = precapacity; count != index; ) {
              unsigned char *const automatic = this -> elements.value[--index].automatic;

              // ...
              this -> elements.value[index].value = NULL;

              for (unsigned char *iterator = automatic + sizeof(subbase); automatic != iterator; )
              *--iterator = 0x00u; // --> std::memset(automatic, 0x00, sizeof(subbase));
            }

            // ... ->> Cache `::dynamic` `storage` into the `allocation::table`
            if (0u != dynamic.capacity) {
              std::size_t next = allocation::table.capacity;

              // ...
              for (unsigned char *iterator = reinterpret_cast<unsigned char*>(dynamic.value) + dynamic.capacity; iterator != reinterpret_cast<unsigned char*>(dynamic.value); )
              *--iterator = 0x00u; // --> std::memset(dynamic.value, 0x00, dynamic.capacity);

              for (std::size_t rate = 1u; ; ++next) // --> next >= allocation::table.capacity
              for (; 0u == next % sizeof(storage); rate *= 2u) {
                if (0u == allocation::table.capacity / rate) {
                  next += next > ULONG_MAX - sizeof(storage) ? 0u : sizeof(storage);
                  break;
                }

                if (next <= ULONG_MAX - (allocation::table.capacity / rate)) {
                  next += allocation::table.capacity / rate;
                  break;
                }
              }

              // ... ->> Find unused `storage` (ie: `NULL == ::value`) to cache into
              for (storage *iterator = allocation::table.allocations + allocation::table.size; iterator != allocation::table.allocations; ) {
                storage *const suballocation = /* --> std::launder(...) */ --iterator;

                // ...
                if (NULL == suballocation -> value) {
                  suballocation -> capacity = dynamic.capacity;
                  suballocation -> value    = dynamic.value;

                  dynamic.capacity = 0u;
                  dynamic.length   = 0u;
                  dynamic.value    = NULL;

                  // ...
                  return true; // ->> (Non-)allocation went well
                }

                if (next != allocation::table.capacity and suballocation -> capacity >= allocation::table.capacity + sizeof(storage))
                allocation = NULL == allocation or (
                  // ->> Well-fitted: `next == ::capacity`
                  (next < allocation    -> capacity ? (allocation    -> capacity - next) : (next - allocation    -> capacity)) >
                  (next < suballocation -> capacity ? (suballocation -> capacity - next) : (next - suballocation -> capacity))
                ) ? suballocation : allocation;
              }

              /* ... ->> Attempt to add `::dynamic` `storage` to the `allocation::table` */ {
                // ... ->> Add `::dynamic` `storage` to the sufficiently-sized `allocation::table`
                if (allocation::table.capacity >= (allocation::table.size + 1u) * sizeof(storage))
                  allocation = allocation::table.allocations + allocation::table.size++;

                // ... ->> Re-purpose the nearest well-fitted `allocation` to expand the `allocation::table`
                else if (NULL != allocation) {
                  std::size_t const capacity = allocation -> capacity;
                  std::size_t const offset   = allocation - allocation::table.allocations;
                  storage    *const value    = reinterpret_cast<storage*>(allocation -> value);

                  // ...
                  for (std::size_t index = allocation::table.size; index; ) {
                    if (--index == offset) {
                      allocation             = ::new (value + index) storage();
                      allocation -> capacity = allocation::table.capacity;
                      allocation -> value    = reinterpret_cast<subbase*>(allocation::table.allocations);

                      continue;
                    }

                    (void) ::new (value + index) storage(allocation::table.allocations[index]);
                  }

                  for (unsigned char *iterator = reinterpret_cast<unsigned char*>(allocation -> value) + allocation -> capacity; iterator != reinterpret_cast<unsigned char*>(allocation -> value); )
                    *--iterator = 0x00u; // --> std::memset(allocation -> value, 0x00, allocation -> capacity);

                  allocation::table.allocations = value;
                  allocation::table.capacity    = capacity;
                  allocation                    = allocation::table.allocations + allocation::table.size++;
                }

                // ... ->> Re-purpose the `::dynamic` `storage` as the `allocation::table` instead
                else if (dynamic.capacity >= (allocation::table.size + 1u) + sizeof(storage)) {
                  std::size_t const capacity = dynamic.capacity;
                  storage    *const value    = reinterpret_cast<storage*>(dynamic.value);

                  // ...
                  for (std::size_t index = allocation::table.size; index--; )
                    (void) ::new (value + index) storage(allocation::table.allocations[index]);

                  for (unsigned char *iterator = reinterpret_cast<unsigned char*>(allocation::table.allocations) + allocation::table.capacity; iterator != reinterpret_cast<unsigned char*>(allocation::table.allocations); )
                    *--iterator = 0x00u; // --> std::memset(allocation::table.allocations, 0x00, allocation::table.capacity);

                  dynamic.capacity = allocation::table.capacity;
                  dynamic.value    = reinterpret_cast<subbase*>(allocation::table.allocations);

                  allocation::table.allocations = value;
                  allocation::table.capacity    = capacity;
                  allocation                    = allocation::table.allocations + allocation::table.size++;
                }

                else if (0u == allocation::table.capacity and 0u == allocation::table.size) {
                  allocation::table.allocations = reinterpret_cast<storage*>(dynamic.value);
                  allocation::table.capacity    = dynamic.capacity;
                  allocation                    = NULL;

                  dynamic.value = NULL; // ->> passed to `std::free(...)` due to `NULL == allocation`
                }

                // ... ->> Grow the `allocation::table` to add `::dynamic` `storage` to it
                else if (next != allocation::table.capacity) {
                  void *const suballocation = NULL == allocation::table.allocations ? std::malloc(next) : std::realloc(allocation::table.allocations, next);

                  // ...
                  if (NULL == suballocation)
                    allocation = NULL;

                  else {
                    allocation::table.allocations = static_cast<storage*>(suballocation);
                    allocation::table.capacity    = next;
                    allocation                    = allocation::table.allocations + allocation::table.size++;
                  }
                }

                // ... ->> Otherwise just release the `::dynamic` `storage`
                if (NULL == allocation)
                  std::free(dynamic.value); // ->> `NULL` or otherwise

                else {
                  allocation             = ::new (allocation) storage();
                  allocation -> capacity = dynamic.capacity;
                  allocation -> value    = dynamic.value;
                }

                dynamic.capacity = 0u;
                dynamic.length   = 0u;
                dynamic.value    = NULL;

                // ...
                return true; // ->> (De-/ Non-)allocation went well
              }
            }

            return true; // ->> (Non-)allocation went well
          }

          count -= precapacity;

          // ... ->> Destruct excess `::dynamic` elements in order
          for (std::size_t index = dynamic.length; count < index; )
            (/* --> std::launder(...) */ dynamic.value + --index) -> ~subbase();

          // ... ->> Attempt to grow the `::dynamic` `storage` to match the `count`
          if (dynamic.capacity < count * sizeof(subbase)) {
            // ... ->> Find unused `storage` (ie: `NULL == ::value`) to grow the `::dynamic` `storage`
            for (storage *iterator = allocation::table.allocations + allocation::table.size; iterator != allocation::table.allocations; ) {
              storage *const allocation = /* --> std::launder(...) */ --iterator;

              // ...
              if (allocation -> capacity >= count * sizeof(subbase)) {
                std::size_t const capacity = dynamic.capacity;
                subbase    *const value    = dynamic.value;

                // ... ->> Re-initialize `::dynamic` elements into unused `storage`
                for (std::size_t index = 0u, end = count < dynamic.length ? count : dynamic.length; index != end; ++index)
                  (void) ::new (static_cast<subbase*>(allocation -> value) + index) subbase(*(/* --> std::launder(...) */ dynamic.value + index));

                for (subbase *subiterator = dynamic.value + (count < dynamic.length ? count : dynamic.length); subiterator != dynamic.value; )
                  (/* --> std::launder(...) */ --subiterator) -> ~subbase();

                // ...
                dynamic.capacity = allocation -> capacity;
                dynamic.value    = static_cast<subbase*>(allocation -> value);

                allocation -> capacity = capacity;
                allocation -> value    = value;

                for (unsigned char *subiterator = reinterpret_cast<unsigned char*>(dynamic.value + dynamic.capacity), *const end = reinterpret_cast<unsigned char*>(dynamic.value + capacity); subiterator != end; )
                  *--subiterator = 0x00u; // --> std::memset(dynamic.value + capacity, 0x00, dynamic.capacity - capacity);

                // ...
                return true; // ->> (Non-)allocation went well
              }
            }

            // ... ->> Re-purpose the `allocation::table` as `::dynamic` `storage`
            if (allocation::table.capacity >= count * sizeof(subbase) and 0u == allocation::table.size) {
              std::size_t const capacity = dynamic.capacity;
              storage    *const value    = reinterpret_cast<storage*>(dynamic.value);

              // ... ->> Re-initialize `::dynamic` elements into unused `storage`
              for (std::size_t index = 0u, end = count < dynamic.length ? count : dynamic.length; index != end; ++index)
                (void) ::new (reinterpret_cast<subbase*>(allocation::table.allocations) + index) subbase(*(/* --> std::launder(...) */ dynamic.value + index));

              for (subbase *subiterator = dynamic.value + (count < dynamic.length ? count : dynamic.length); subiterator != dynamic.value; )
                (/* --> std::launder(...) */ --subiterator) -> ~subbase();

              // ...
              dynamic.capacity = allocation::table.capacity;
              dynamic.value    = reinterpret_cast<subbase*>(allocation::table.allocations);

              allocation::table.allocations = value;
              allocation::table.capacity    = capacity;

              for (unsigned char *subiterator = reinterpret_cast<unsigned char*>(dynamic.value + dynamic.capacity), *const end = reinterpret_cast<unsigned char*>(dynamic.value + capacity); subiterator != end; )
                *--subiterator = 0x00u; // --> std::memset(dynamic.value + capacity, 0x00, dynamic.capacity - capacity);

              // ...
              return true; // ->> (Non-)allocation went well
            }

            /* ... ->> (Re-)allocate memory then zero out extra memory */ {
              void       *allocation = NULL;
              std::size_t capacity   = dynamic.capacity;
              std::size_t next       = 0u == capacity ? sizeof(subbase) * 2u : capacity;

              // ...
              for (; capacity > next; next = (next * 3u) / 2u) // --> next >= dynamic.capacity
              if (next > (ULONG_MAX / 3u) * 2u) {
                next += next > ULONG_MAX - sizeof(subbase) ? 0u : sizeof(subbase); // ->> Fallback growth `rate` could be improved
                break;
              }

              allocation = NULL == dynamic.value ? std::calloc(next / sizeof(subbase), sizeof(subbase)) : /* --> -Wclass-memaccess */ std::realloc(static_cast<void*>(dynamic.value), next);

              if (NULL != allocation) {
                if (NULL != dynamic.value) {
                  for (unsigned char *iterator = static_cast<unsigned char*>(allocation) + next, *const end = static_cast<unsigned char*>(allocation) + capacity; iterator != end; )
                  *--iterator = 0x00u; // --> std::memset(allocation + capacity, 0x00, next - capacity);
                }

                dynamic.capacity = next;
                dynamic.value    = static_cast<subbase*>(allocation);

                // ...
                return true; // ->> Allocation went well
              }
            }
          }

          return false;
        }

        // ...
        inline subbase* at(std::size_t const index) const {
          if (index < precapacity) return this -> elements.value[index].value;
          return /* --> std::launder(...) */ this -> elements.value[precapacity].dynamic.value + (index - precapacity);
        }

        // ...
        inline std::size_t lengthof() const {
          std::size_t length = this -> elements.value[precapacity].dynamic.length;

          // ...
          for (std::size_t index = precapacity; index; )
          length += NULL != this -> elements.value[--index].value;

          return length;
        }

      public:
        value<subbase, precapacity> elements;
        length                      length; // ->> Strictly a front-facing feature ie: not required by `array` implementation

        /* ... */
        inline ~array() {
          (void) this -> allocate(0u);
        }

        /* ... */
        template <typename type>
        bool add(type const& element) {
          std::size_t const length = this -> lengthof();

          // ...
          if (this -> allocate(length + 1u)) {
            if (length < precapacity)
              this -> elements.value[length].value = ::new (this -> elements.value[length].automatic) subbase(element);

            else {
              (void) ::new (this -> elements.value[precapacity].dynamic.value + this -> elements.value[precapacity].dynamic.length) subbase(element);
              ++(this -> elements.value[precapacity].dynamic.length);
            }

            // ...
            return true;
          }

          return false;
        }

        // ...
        void pop() {
          if (0u == this -> elements.value[precapacity].dynamic.length) {
            std::size_t const length = this -> lengthof();

            // ...
            if (0u != length) {
              this -> elements.value[length - 1u].value -> ~subbase();
              this -> elements.value[length - 1u].value = NULL;
            }

            return;
          }

          (/* --> std::launder(...) */ this -> elements.value[precapacity].dynamic + (this -> elements.value[precapacity].dynamic.length - 1u)) -> ~subbase();
          --(this -> elements.value[precapacity].dynamic.length);
        }

        // ...
        template <typename type, std::size_t capacity>
        array& operator =(array<type, capacity> const& array) {
          std::size_t const end    = array.lengthof();
          std::size_t const length = this -> lengthof();

          // ...
          if (this -> allocate(end))
          for (std::size_t index = 0u; index != end; ++index) {
            type &element = *array.at(index);

            // ...
            if (index < precapacity) {
              if (NULL != this -> elements.value[index].value) {
                this -> elements.value[index].value -> ~subbase();
                this -> elements.value[index].value = ::new (this -> elements.value[index].automatic) subbase(element);
              }

              continue;
            }

            if (index < length)
              (/* --> std::launder(...) */ this -> elements.value[precapacity].dynamic + (index - precapacity)) -> ~subbase();

            (void) ::new (this -> elements.value[precapacity].dynamic + (index - precapacity)) subbase(element);
          }

          return *this;
        }

        // ...
        inline base& operator [](std::size_t const index) const {
          return *(this -> at(index));
        }
    };

  public:
    struct operation {
      typedef std::size_t state_t;

      /* ... */
      bool         (*function)(bignum&, state_t[]);
      array<state_t> state;

      /* ... */
      operation(bool (&function)(bignum&, state_t[]), std::size_t arity) :
        function(&function),
        state   ()
      { (void) this -> state.allocate(arity); }
    };

  /* ... */
  private:
    array<unsigned char, 20u> denominator;
    array<unsigned char, 20u> numerator;
    array<operation>          operations;
    bool                      signedness;

    /* ... */
    bool add(bignum const& number) {
      static_cast<void>(number);
      return false;
    }

    // ...
    bool decrement() {
      return false;
    }

    // ...
    bool exponentiate(bignum const& number) {
      static_cast<void>(number);
      return false;
    }

    // ...
    bool increment() {
      return false;
    }

    // ...
    bool multiply(bignum const& number) {
      static_cast<void>(number);
      static_cast<void>(this -> signedness);

      return false;
    }

  /* ... */
  public:
    inline bignum() :
      denominator(),
      numerator  (),
      operations (),
      signedness (false)
    {
      (void) this -> denominator.add(1u);
      (void) this -> numerator  .add(0u);

      /* ... */
      if (reinterpret_cast<unsigned char*>(this) == &reinterpret_cast<unsigned char const&>(bignum::EULER)) {
        struct euler {
          static bool function(bignum&, operation::state_t[]) {
            return false;
          }
        };

        (void) this -> operations.add(operation(euler::function, 0u));
        return;
      }

      // ...
      if (reinterpret_cast<unsigned char*>(this) == &reinterpret_cast<unsigned char const&>(bignum::INFINITY)) {
        this -> denominator[0] = 0u;
        return;
      }

      // ...
      if (reinterpret_cast<unsigned char*>(this) == &reinterpret_cast<unsigned char const&>(bignum::ONE)) {
        this -> numerator[0] = 1u;
        return;
      }

      // ...
      if (reinterpret_cast<unsigned char*>(this) == &reinterpret_cast<unsigned char const&>(bignum::PI)) {
        // this -> denominator[0] = 78256779;
        // this -> numerator[0] = 245850922;

        return;
      }

      // ...
      if (reinterpret_cast<unsigned char*>(this) == &reinterpret_cast<unsigned char const&>(bignum::TAU)) {
        this -> numerator[0] = 2u;
        (void) this -> multiply(bignum::PI);

        return;
      }

      // ...
      if (reinterpret_cast<unsigned char*>(this) == &reinterpret_cast<unsigned char const&>(bignum::ZERO))
      return;
    }

    // ...
    bignum(long double const number) :
      denominator(),
      numerator  (),
      operations (),
      signedness (number < +0.00L)
    {
      long double characteristics = 1.00L;

      // ...
      number = this -> signedness ? -number : +number;

      (void) this -> denominator.add(1u);
      (void) this -> numerator  .add(0u);

      if (number < 1.00L)
        characteristics = 0.00L;
      else for (long double rate = 1.00L; characteristics < number; )
        if (characteristics > 10.00L - (characteristics / rate)) {
          rate *= 2u;
          if (characteristics / rate < 1.00L)
          continue;
        }
        characteristics += characteristics / rate;
    }
};
  template <typename base, std::size_t precapacity>
  typename bignum::template array<base, precapacity>::allocation::value bignum::array<base, precapacity>::allocation::table = {};

  bignum const bignum::EULER    = bignum();
  bignum const bignum::INFINITY = bignum();
  bignum const bignum::ONE      = bignum();
  bignum const bignum::PI       = bignum();
  bignum const bignum::TAU      = bignum();
  bignum const bignum::ZERO     = bignum();

/* Main */
int main(int, char*[]) /* noexcept */ {
}
