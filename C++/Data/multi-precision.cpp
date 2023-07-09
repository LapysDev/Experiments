#include <ciso646> //
#include <climits> // --> ULONG_MAX
#include <cstddef> // --> std::size_t
#include <cstdio>  //
#include <cstdlib> // --> std::free(...), std::malloc(...)
#include <new>     // --> new

/* ... */
struct bignum {
  /* ... */
  private:
    static unsigned char const radix = 10u; // ->> Must not be above the maximum representable value per digit; Higher values are space efficient

  public:
    static bignum const EULER;
    static bignum const INFINITY;
    static bignum const PI;
    static bignum const TAU;

  /* ... */
  private:
  public:
    // ...
    template <typename base, std::size_t precapacity = 1u>
    struct array {
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
        template <typename subbase>
        struct allocation {
          struct storage {
            subbase    *value;
            std::size_t capacity; // ->> Maximum byte size of `subbase` elements altogether
          };

          // ...
          struct valueof {
            storage    *allocations;
            std::size_t capacity; // ->> Maximum byte size of `allocations`
            std::size_t size;     // ->> Number            of `allocations`

            /* ... */
            ~valueof() {
              for (this -> allocations += this -> size; this -> size; --(this -> size)) {
                std::free((--(this -> allocations)) -> value); // ->> `NULL` or otherwise

                this -> allocations -> capacity = 0u;
                this -> allocations -> value    = NULL;
              }

              std::free(this -> allocations); // ->> `NULL` or otherwise
              this -> allocations = NULL;
            }
          };

          /* ... */
          static valueof table; // Static zero-initialized members
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
            std::size_t valueof() const {
              struct layout /* ->> Plain-Old Data/ Standard layout representation of `struct array` */ {
                /* alignas(sizeof array().elements) */ unsigned char value [sizeof array().elements];
                /* alignas(sizeof array().length)   */ unsigned char length[sizeof array().length];
              };

              return /* --> std::launder(...) */ reinterpret_cast<array const*>(reinterpret_cast<unsigned char const*>(this) - offsetof(layout, length)) -> lengthof();
            }

          public:
            length() :
              value(this -> valueof())
            {}

            /* ... */
            operator std::size_t() const {
              this -> value = this -> valueof();
              return this -> value;
            }
        };

        // ...
        template <typename subbase>
        struct storage : public allocation<subbase>::storage {
          std::size_t length; // ->> Number of `subbase` elements
        };

        // ...
        template <typename subbase, std::size_t capacity>
        struct valueof {
          struct any {
            union {
              /* alignas(base) */ unsigned char automatic[sizeof(base)];
              storage<subbase>                  dynamic;
            };
            subbase *value;

            /* ... */
            any() :
              dynamic(),
              value  (NULL)
            {
              this -> dynamic.capacity = 0u;
              this -> dynamic.length   = 0u;
              this -> dynamic.value    = NULL;
            }

            template <typename type>
            any(type const& value) :
              automatic(),
              value    (::new (this -> automatic) subbase(value))
            {}

            // ...
            ~any() {
              if (NULL != this -> value)
              this -> value -> ~subbase();
            }
          } value[capacity + 1u];
        };

        template <typename subbase>
        struct valueof<subbase, 0u> {
          struct nul {
            union {
              storage<subbase> dynamic;
              unsigned char   *automatic;
            };
            subbase *value;

            /* ... */
            nul() :
              dynamic(),
              value  (NULL)
            {
              this -> dynamic.capacity = 0u;
              this -> dynamic.length   = 0u;
              this -> dynamic.value    = NULL;
            }

            template <typename type>
            nul(type const&) /* = delete */;
          } value[1u];
        };

        /* ... */
        typedef typename baseof<base>::type subbase;

        /* ... */
        bool allocate(std::size_t count) {
          typedef allocation<subbase> allocation;

          storage<subbase> const       &dynamic    = this -> elements.value[precapacity].dynamic;
          typename allocation::storage *allocation = NULL;

          // ...
          if (count <= precapacity) {
            // ... ->> Destruct `::dynamic` and excess `::automatic` elements in order
            for (subbase *iterator = dynamic.value + dynamic.length; iterator != dynamic.value; )
            (/* --> std::launder(...) */ --iterator) -> ~subbase();

            for (std::size_t index = precapacity; count != index; )
            if (NULL != this -> elements.value[--index].value) {
              this -> elements.value[index].value -> ~subbase();
              this -> elements.value[index].value = NULL;
            }

            for (std::size_t index = precapacity; count != index; ) {
              unsigned char *const automatic = this -> elements.value[--index].automatic;

              // ...
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
              for (; 0u == next % sizeof(typename allocation::storage); rate *= 2u) {
                if (0u == allocation::table.capacity / rate) {
                  next += next <= ULONG_MAX - sizeof(typename allocation::storage) ? sizeof(typename allocation::storage) : 0u;
                  break;
                }

                if (next <= ULONG_MAX - (allocation::table.capacity / rate)) {
                  next += allocation::table.capacity / rate;
                  break;
                }
              }

              // ... ->> Find unused `storage` (ie: `NULL == ::value`) to cache into
              for (typename allocation::storage *iterator = allocation::table.allocations + allocation::table.size; iterator != allocation::table.allocations; ) {
                typename allocation::storage *const suballocation = /* --> std::launder(...) */ --iterator;

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

                if (next != allocation::table.capacity and suballocation -> capacity >= allocation::table.capacity + sizeof(typename allocation::storage))
                allocation = NULL == allocation or (
                  // ->> Well-fitted: `next == ::capacity`
                  (next < allocation    -> capacity ? (allocation    -> capacity - next) : (next - allocation    -> capacity)) >
                  (next < suballocation -> capacity ? (suballocation -> capacity - next) : (next - suballocation -> capacity))
                ) ? suballocation : allocation;
              }

              /* ... ->> Attempt to add `::dynamic` `storage` to the `allocation::table` */ {
                // ... ->> Add `::dynamic` `storage` to the sufficiently-sized `allocation::table`
                if (allocation::table.capacity >= (allocation::table.size + 1u) * sizeof(typename allocation::storage))
                  allocation = allocation::table.allocations + allocation::table.size++;

                // ... ->> Re-purpose the nearest well-fitted `allocation` to expand the `allocation::table`
                else if (NULL != allocation) {
                  std::size_t                   const capacity = allocation -> capacity;
                  std::size_t                   const offset   = allocation - allocation::table.allocations;
                  typename allocation::storage *const value    = reinterpret_cast<typename allocation::storage*>(allocation -> value);

                  // ...
                  for (std::size_t index = allocation::table.size; index; ) {
                    if (--index == offset) {
                      allocation             = ::new (value + index) typename allocation::storage();
                      allocation -> capacity = allocation::table.capacity;
                      allocation -> value    = reinterpret_cast<subbase*>(allocation::table.allocations);

                      continue;
                    }

                    (void) ::new (value + index) typename allocation::storage(allocation::table.allocations[index]);
                  }

                  for (unsigned char *iterator = reinterpret_cast<unsigned char*>(allocation -> value) + allocation -> capacity; iterator != reinterpret_cast<unsigned char*>(allocation -> value); )
                    *--iterator = 0x00u; // --> std::memset(allocation -> value, 0x00, allocation -> capacity);

                  allocation::table.allocations = value;
                  allocation::table.capacity    = capacity;
                  allocation                    = allocation::table.allocations + allocation::table.size++;
                }

                // ... ->> Re-purpose the `::dynamic` `storage` as the `allocation::table` instead
                else if (0u == allocation::table.capacity and 0u == allocation::table.size) {
                  allocation                    = NULL;
                  allocation::table.allocations = reinterpret_cast<typename table::storage*>(dynamic.value);
                  allocation::table.capacity    = dynamic.capacity;

                  dynamic.value = NULL; // ->> passed to `std::free(...)` due to `NULL == allocation`
                }

                // ... ->> Grow the `allocation::table` to add `::dynamic` `storage` to it
                else if (next != allocation::table.capacity) {
                  void *const suballocation = NULL == allocation::table.allocations ? std::malloc(next) : std::realloc(allocation::table.allocations, next);

                  // ...
                  if (NULL == suballocation)
                    allocation = NULL;

                  else {
                    allocation::table.allocations = static_cast<typename table::storage*>(suballocation);
                    allocation::table.capacity    = next;
                    allocation                    = allocation::table.allocations + allocation::table.size++;
                  }
                }

                // ... ->> Otherwise just release the `::dynamic` `storage`
                if (NULL == allocation)
                  std::free(dynamic.value); // ->> `NULL` or otherwise

                else {
                  allocation             = ::new (allocation) typename allocation::storage();
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
            for (typename allocation::storage const *iterator = allocation::table.allocations + allocation::table.size; iterator != allocation::table.allocations; ) {
              typename allocation::storage *const suballocation = /* --> std::launder(...) */ --iterator;

              // ...
              if (suballocation -> capacity >= count * sizeof(subbase)) {
                std::size_t const capacity = dynamic.capacity;
                subbase    *const value    = dynamic.value;

                // ... ->> Re-initialize `::dynamic` elements into unused `storage`
                for (std::size_t index = 0u; index != dynamic.length; ++index)
                  (void) ::new (suballocation -> value + index) subbase(*(/* --> std::launder(...) */ dynamic.value + index));

                for (subbase *subiterator = dynamic.value + dynamic.length; subiterator != dynamic.value; )
                  (/* --> std::launder(...) */ --subiterator) -> ~subbase();

                // ...
                dynamic.capacity = suballocation -> capacity;
                dynamic.value    = suballocation -> value;

                suballocation -> capacity = capacity;
                suballocation -> value    = value;

                // ...
                return true; // (Non-)allocation went well
              }
            }

            // Re-purpose the `allocation::table` as `::dynamic` `storage`
            if (allocation::table.capacity > count * sizeof(subbase) and 0u == allocation::table.size) {
              std::size_t capacity = allocation::table.capacity;

              // ... ->> PENDING/ TOOD
              for ()

              dynamic.capacity = allocation::table.capacity;
              dynamic.value    = reinterpret_cast<subbase*>(allocation::table.allocations);

              allocation = allocation::table.allocations;
            }

            // (Re-)allocate memory then zero out extra memory
          }

          // ->> TODO: Zero-out sus excess `::dynamic` elements

          // this -> elements.value[precapacity].dynamic.capacity
          // this -> elements.value[precapacity].dynamic.value
          // this -> elements.value[precapacity].dynamic.length

          return false;
        }

        // ...
        subbase* at(std::size_t const index) const {
          if (index < precapacity) return this -> elements.value[index].value;
          return /* --> std::launder(...) */ this -> elements.value[precapacity].dynamic.value + (index - precapacity);
        }

        // ...
        std::size_t lengthof() const {
          std::size_t length = this -> elements.value[precapacity].dynamic.length;

          // ...
          for (std::size_t index = precapacity; index; )
          length += NULL != this -> elements.value[--index].value;

          return length;
        }

      public:
        valueof<subbase, precapacity> elements;
        length                        length; // ->> Strictly a front-facing feature ie: not required by `array` implementation

        /* ... */
        ~array() {
          storage<subbase> const &dynamic = this -> elements.value[precapacity].dynamic;

          // ...
          for (subbase *iterator = dynamic.value + dynamic.length; iterator != dynamic.value; )
          (--iterator) -> ~subbase();

          for (std::size_t index = precapacity; index; ) {
            if (NULL != this -> elements.value[--index].value)
            this -> elements.value[index].value -> ~subbase();
          }
        }

        /* ... */
        template <typename type>
        bool add(type const&) {
          return false;
        }

        // ...
        base& operator [](std::size_t const index) const {
          return *(this -> at(index));
        }
    };

  public:
    struct operation {
      operation *next;
      bool       continuous;
    };

  /* ... */
  private:
    // array<unsigned char, 20u> denominator;
    // array<unsigned char, 20u> numerator;
    // array<operation>          operation;
    bool                      signedness;

  /* ... */
  public:
    bignum() :
      // denominator(),
      // numerator  (),
      // operation  (),
      signedness (false)
    {
      // this -> denominator.add(1u);
      // this -> numerator  .add(0u);
      static_cast<void>(this -> signedness);
    }
};
  template <typename base, std::size_t precapacity>
  template <typename subbase>
  typename bignum::template array<base, precapacity>::template allocation<subbase>::valueof bignum::array<base, precapacity>::allocation<subbase>::table = {};

/* Main */
#include <csignal>
#include <cstdlib>

struct object {
  static std::size_t count;
  std::size_t const id;

  // ...
  object() : id(++object::count) { std::fprintf(stdout, "[construct]: %lu" "\r\n", static_cast<unsigned long>(this -> id)); }
  object(object const& object) : id(++object::count) { std::fprintf(stdout, "[copy construct (%lu)]: %lu" "\r\n", static_cast<unsigned long>(object.id), static_cast<unsigned long>(this -> id)); }

  ~object() { std::fprintf(stdout, "[destruct]: %lu" "\r\n", static_cast<unsigned long>(this -> id)); }
};
  std::size_t object::count = 0u;

int main(int, char*[]) /* noexcept */ {
  struct program { static void exit(int const) { std::fprintf(stderr, "\r\n" "... SEGMENTATION FAULT ..." "\r\n"); std::exit(EXIT_SUCCESS); } };
  std::signal(SIGSEGV, &program::exit);

  bignum::array<object, 1u> array = {};
  static_cast<void>(array);
}
