#include <cfloat>  // --> LDBL_MAX
#include <ciso646> //
#include <climits> // --> UINTMAX_MAX
#include <cstddef> // --> std::size_t
#include <cstdio>  //
#include <cstdlib> // --> std::calloc(...), std::free(...), std::malloc(...), std::realloc(...)
#include <new>     // --> new
#if __cplusplus >= 201103L or defined _MSVC_LANG // --> +201402L
# include <type_traits> // --> std::is_trivial
#endif

/* ... */
struct bignum /* final */ {
  public:
    typedef unsigned char    digit;     // ->> Component part of `::denominator` and `::numerator`; Must be an integer type
    typedef struct operation operation; // ->> Sequence of iterable continuous functions that more precisely compute `bignum`

  private:
    // ... ->> Removes qualifiers from specified type
    template <typename base>
    struct baseof /* final */ {
      typedef base type;
    };

    template <typename base> struct baseof<base&>               /* final */ { typedef typename baseof<base>::type type; };
    template <typename base> struct baseof<base const>          /* final */ { typedef typename baseof<base>::type type; };
    template <typename base> struct baseof<base const volatile> /* final */ { typedef typename baseof<base>::type type; };
    template <typename base> struct baseof<base       volatile> /* final */ { typedef typename baseof<base>::type type; };

    #ifdef __cpp_rvalue_references // --> 200610L
      template <typename base>
      struct baseof<base&&> /* final */ {
        typedef typename baseof<base>::type type;
      };
    #endif

    // ... ->> Determines the object address provenance of the specified type
    template <typename base>
    struct is_blessed /* final */ {
      private:
        template <typename, unsigned char = 0x00u>
        struct valueof /* final */ {
          static bool const value = false;
        };

        template <unsigned char sfinae> struct valueof<char,          sfinae> /* final */ { static bool const value = true; };
        template <unsigned char sfinae> struct valueof<unsigned char, sfinae> /* final */ { static bool const value = true; };

        #ifdef __cpp_lib_byte // --> 201811L
          template <unsigned char sfinae>
          struct valueof<std::byte, sfinae> /* final */ {
            static bool const value = true;
          };
        #endif

      public:
        static bool const value = valueof<typename baseof<base>::value>::value;
    };

    // ... ->> Determines the triviality of constructing/ destructing the specified type
    template <typename base>
    struct is_trivial /* final */ {
      #if __cplusplus >= 201103L or defined _MSVC_LANG // --> +201402L
        static bool const value = std::is_trivially_constructible<base>::value and std::is_trivially_destructible<base>::value;
      #elif defined __clang__ or defined __GNUC__ or defined _MSC_VER
        #undef __has_trivial_copy
        #undef __has_trivial_destructor
        #ifdef __clang__
        # pragma clang diagnostic push
        # pragma clang diagnostic ignored "-Wdeprecated-builtins"
        #endif

        static bool const value = __has_trivial_constructor(base) and __has_trivial_destructor(base); // ->> Subject to `-Wclass-memaccess`

        #ifdef __clang__
        # pragma clang diagnostic pop
        #endif
      #else
        private:
          // ... ->> Compiler-extended integer types explicitly not acknowledged; See `is_enum` internals
          template <typename subbase, unsigned char sfinae = 0x00u>
          struct valueof /* final */  {
            private:
              template <typename subsubbase>
              struct is_enum /* final */  {
                private:
                  template <typename type>
                  static bool const (&valueof(unsigned char const, bool const (*const)[static_cast<type>(1u)] = NULL) /* noexcept */)[true + 1u];

                  template <typename>
                  static bool const (&valueof(...) /* noexcept */)[false + 1u];

                public:
                  static bool const value = sizeof(valueof(sfinae)) == sizeof(bool const (&)[true + 1u]);
              };

              // ...
              template <typename subsubbase, typename = subsubbase const>
              struct is_function /* final */  {
                static bool const value = false;
              };

              template <typename subsubbase>
              struct is_function<subsubbase, subsubbase> /* final */ {
                static bool const value = true;
              };

            public:
              static bool const value = is_enum<subbase>::value or is_function<subbase>::value;
          };

          template <unsigned char sfinae> struct valueof<bool,           sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<char,           sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<double,         sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<float,          sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<long double,    sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<signed char,    sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<signed int,     sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<signed long,    sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<signed short,   sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<unsigned char,  sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<unsigned int,   sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<unsigned long,  sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<unsigned short, sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<wchar_t,        sfinae> /* final */ { static bool const value = true; };

          template <typename subbase, unsigned char sfinae>
          struct valueof<subbase*, sfinae> /* final */ {
            static bool const value = true;
          };

          #ifdef __cpp_char8_t // --> 201811L
            template <unsigned char sfinae>
            struct valueof<char8_t, sfinae> /* final */ {
              static bool const value = true;
            };
          #endif

          #ifdef __cpp_lib_byte // --> 201811L
            template <unsigned char sfinae>
            struct valueof<std::byte, sfinae> /* final */ {
              static bool const value = true;
            };
          #endif

          #ifdef __cpp_unicode_characters // --> 200704L
            template <unsigned char sfinae> struct valueof<char16_t, sfinae> /* final */ { static bool const value = true; };
            template <unsigned char sfinae> struct valueof<char32_t, sfinae> /* final */ { static bool const value = true; };
          #endif

        public:
          static bool const value = valueof<typename baseof<base>::type>::value;
      #endif
    };

    template <typename base>
    struct is_trivial<base&> /* final */ {
      static bool const value = true;
    };

    #ifdef __cpp_rvalue_references // --> 200610L
      template <typename base>
      struct is_trivial<base&&> /* final */ {
        static bool const value = true;
      };
    #endif

    /* ... */
    struct allocation;                                                         // ->> Dynamically-allocated memory management interface for `array::dynamic` elements
                                                                               //
    template <typename, std::size_t = 1u>                      struct array;   // ->> Variable-length collection of contiguous `base` objects (such as `digit`s or `operation::state`s)
    template <std::size_t = 128u / (CHAR_BIT * sizeof(digit))> struct biguint; // ->> `::denominator` and `::numerator` types

  /* ... */
  private:
    static digit const radix = 10u; // ->> Must not be zero; Higher numeral systems are more computation and memory efficient

  public:
    static bignum const EULER;
    static bignum const INFINITY;
    static bignum const ONE;
    static bignum const PI;
    static bignum const TAU;
    static bignum const ZERO;

    /* ... */
    template <typename type>
    /* constexpr */ inline static type* bless(type* const address) /* noexcept */ {
      #ifdef __cpp_lib_launder // --> 201606L
        return std::launder(address);
      #else
        return address; // ->> Pretend :)
      #endif
    }

    // ...
    /* constexpr */ inline static char*                bytesof(char*                const address) /* noexcept */ { return address; }
    /* constexpr */ inline static char const*          bytesof(char const*          const address) /* noexcept */ { return address; }
    /* constexpr */ inline static char const volatile* bytesof(char const volatile* const address) /* noexcept */ { return address; }
    /* constexpr */ inline static char       volatile* bytesof(char       volatile* const address) /* noexcept */ { return address; }

    /* constexpr */ inline static unsigned char*                bytesof(unsigned char*                const address) /* noexcept */ { return address; }
    /* constexpr */ inline static unsigned char const*          bytesof(unsigned char const*          const address) /* noexcept */ { return address; }
    /* constexpr */ inline static unsigned char const volatile* bytesof(unsigned char const volatile* const address) /* noexcept */ { return address; }
    /* constexpr */ inline static unsigned char       volatile* bytesof(unsigned char       volatile* const address) /* noexcept */ { return address; }

    template <typename type> inline static unsigned char*                bytesof(type*                const address) /* noexcept */ { return reinterpret_cast<unsigned char*>               (address); }
    template <typename type> inline static unsigned char const*          bytesof(type const*          const address) /* noexcept */ { return reinterpret_cast<unsigned char const*>         (address); }
    template <typename type> inline static unsigned char const volatile* bytesof(type const volatile* const address) /* noexcept */ { return reinterpret_cast<unsigned char const volatile*>(address); }
    template <typename type> inline static unsigned char       volatile* bytesof(type       volatile* const address) /* noexcept */ { return reinterpret_cast<unsigned char       volatile*>(address); }

    #ifdef __cpp_lib_byte // --> 201603L
      /* constexpr */ inline static std::byte*                bytesof(std::byte*                const address) /* noexcept */ { return address; }
      /* constexpr */ inline static std::byte const*          bytesof(std::byte const*          const address) /* noexcept */ { return address; }
      /* constexpr */ inline static std::byte const volatile* bytesof(std::byte const volatile* const address) /* noexcept */ { return address; }
      /* constexpr */ inline static std::byte       volatile* bytesof(std::byte       volatile* const address) /* noexcept */ { return address; }
    #endif

    // ...
    template <typename typeA, typename typeB, typename typeC>
    /* constexpr */ inline static typeB* instantiate(typeB* const address, typeC const& value, bool const (*const)[is_blessed<typeA>::value] = NULL) /* noexcept(...) */ {
      return static_cast<void>(*(typeA*) address = value), address;
    }

    template <typename typeA, typename typeB, typename typeC>
    inline static typeB* instantiate(typeB* const address, typeC const& value, bool const (*const)[not is_blessed<typeA>::value] = NULL) /* noexcept(...) */ {
      return ::new (address) typeA(value);
    }

  /* ... */
  private:
    struct allocation {
      template <typename base>
      struct storage {
        union { subbase *value, *allocations; };
        std::size_t capacity;                // ->> Maximum byte size of storage referenced by `value` (or `allocations`)
        union { std::size_t length, size; }; // ->> Number of existing `subbase` objects contiguously referenced by `allocations` (or `value`)
      };

      /* ... */
      static struct value /* final */ : public storage<storage<void> > {
        static std::size_t const rate = 2u; // ->> Growth rate of `::capacity` --> rate != 0u

        /* ... */
        /* constexpr */ inline value() /* noexcept */ :
          allocations(NULL),
          size       (0u)
        {}

        // ...
        inline ~value() /* noexcept */ {
          for (storage<void> *iterator = this -> allocations + this -> size; iterator != this -> allocations; ) {
            storage<void> *const storage = bless(--iterator);

            // ...
            std::free(storage -> value);

            storage -> length = 0u;
            storage -> value  = NULL;
          }

          this -> allocations = NULL;
          this -> size        = 0u;
        }
      } table;
    };

    // ...
    template <typename base, std::size_t prelength>
    struct array : public allocation /* --> using allocation::storage */ {
      friend struct operation;
      static std::size_t const precapacity = prelength; // ->> Amount of reserve automatic storage measured in elements

      /* ... */
      private:
        // ... ->> Aliases base `element` type
        template <typename subbase = base>
        struct elementof /* final */ {
          typedef typename baseof<subbase>::type type;
        };

        template <typename subbase>
        struct elementof<subbase&> /* final */ {
          typedef struct element /* final */ {
            private:
              subbase &value;

            public:
              template <typename type>
              /* constexpr */ inline element(type& reference) /* noexcept */ :
                reference(static_cast<subbase&>(reference))
              {}

              // ...
              /* constexpr */ inline operator subbase&() const /* noexcept */ {
                return this -> value;
              }
          } type;
        };

        #ifdef __cpp_rvalue_references // --> 200610L
          template <typename subbase>
          struct elementof<subbase&&> /* final */ {
            typedef struct element /* final */ {
              private:
                subbase &&value;

              public:
                template <typename type>
                /* constexpr */ inline element(type&& reference) /* noexcept */ :
                  value((subbase&&) static_cast<type&&>(reference))
                {}

                // ...
                /* constexpr */ inline operator subbase&&() const /* noexcept */ {
                  return static_cast<subbase&&>(this -> value);
                }
            } type;
          };
        #endif

      protected: using allocation::storage;
      public: typedef typename elementof<base>::type element;

      /* ... ->> C++11 and forward explicitly separate `::automatic` and `::dynamic` `elements` as different members */
      public:
        struct elements /* final */ {
          private:
            union {
              /* alignas(subbase) */ unsigned char automatic[sizeof(element)];
              storage<element>                     dynamic;
            };

            element *value;

          public:
            /* constexpr */ inline elements() /* noexcept */ :
              automatic(),
              value    (NULL)
            {}

            template <typename type>
            /* constexpr */ inline elements(type const& element) /* noexcept(...) */ :
              automatic(),
              value    (instantiate<element>(this -> automatic, element))
            {}
        } elements[prelength + 1u];

      /* ... */
      public:
        inline ~array() /* noexcept(...) */ {
          (void) this -> reserve(0u);
        }

      /* ... */
      protected:
        /* constexpr */ inline element* at(std::size_t const index) const /* noexcept */ {
          return index >= this -> precapacity ? index >= this -> elements[this -> precapacity].dynamic.capacity / sizeof(element) ? NULL : bless(this -> elements[this -> precapacity].dynamic + (index - this -> precapacity)) : this -> elements[index].value;
        }

      public:
        template <typename type>
        /* constexpr */ bool add(type const& value) /* noexcept(...) */ {
          std::size_t const capacity = this -> capacityof();
          std::size_t const length   = this -> lengthof();

          // ...
          if (capacity <= length) {
            if (not this -> reserve(length + 1u))
            return false;
          }

          (void) instantiate<element>(this -> at(length), value);
          this -> resize(length + 1u);

          // ...
          return true;
        }

        // ...
        /* constexpr */ inline std::size_t capacityof() const /* noexcept */ {
          return this -> precapacity + (this -> elements[this -> precapacity].dynamic.capacity / sizeof(element));
        }

        // ...
        /* constexpr */ inline std::size_t lengthof() const /* noexcept */ {
          std::size_t length = this -> elements[this -> precapacity].dynamic.length;

          // ... ->> Not simply `::dynamic.length + ::precapacity`
          for (struct elements const *iterator = this -> elements + this -> precapacity; iterator != this -> elements; ) {
            if (NULL != (--iterator) -> value)
            return length + (iterator - this -> elements);
          }

          return length;
        }

        // ...
        /* constexpr */ inline void empty() /* noexcept(...) */ {
          if (this -> lengthof())
            (void) this -> reserve(0u);

          this -> resize(0u);
        }

        // ...
        /* constexpr */ inline void pop() /* noexcept(...) */ {
          std::size_t const length = this -> lengthof();

          // ...
          if (0u != length) {
            if (length <= this -> precapacity) {
              this -> elements[length - 1u].value -> ~element();

              // ... ->> Scrub reusable storage
              for (unsigned char *iterator = this -> elements[length - 1u].automatic + sizeof(element); iterator != this -> elements[length - 1u].automatic; )
                *--iterator = 0x00u; // --> std::memset(this -> elements[length - 1u].automatic, 0x00, sizeof element);

              // ... ->> Keep side-effects consistent with `::dynamic` elements
              for (struct elements *iterator = this -> elements + (length - 1u); iterator != this -> elements + this -> precapacity; ++iterator)
                iterator -> value = NULL;
            }

            else {
              storage<element> &dynamic = this -> elements[this -> precapacity].dynamic;

              // ...
              dynamic.value += length - this -> precapacity - 1u;
              bless(dynamic.value) -> ~element();

              // ... ->> Scrub reusable storage
              for (unsigned char *iterator = bytesof(dynamic.value + 1); iterator != bytesof(dynamic.value); )
                *--iterator = 0x00u; // --> std::memset(dynamic.value + ..., 0x00, sizeof element);

              dynamic.value -= length - this -> precapacity - 1u;
            }

            this -> resize(length - 1u);
          }
        }

        // ...
        bool reserve(std::size_t count) /* noexcept(...) */ {
          struct table /* final */ {
            /* [[nodiscard]] constexpr */ inline static storage<void> swap(void* const allocations, std::size_t const capacity) /* noexcept */ {
              storage<void>  evaluation = {};
              storage<void> *value      = 0u != capacity ? ::new (allocations) storage<void>[allocation::table.size] + allocation::table.size : NULL;

              // ... ->> Copy old `allocation::table` `storage` into new `allocation::table` `storage` (or `allocations`)
              if (NULL != value) {
                for (storage<void> *iterator = allocation::table.allocations + allocation::table.size; iterator != allocation::table.allocations; )
                *--value = *bless(--iterator);
              }

              // ... ->> Scrub reusable `storage`
              for (unsigned char *iterator = bytesof(allocation::table.allocations) + allocation::table.capacity; iterator != bytesof(allocation::table.allocations); )
                *--iterator = 0x00u; // --> std::memset(allocation::table.allocations, 0x00, allocation::table.capacity);

              // ...
              evaluation.capacity           = allocation::table.capacity;
              evaluation.value              = static_cast<void*>(allocation::table.allocations);
              allocation::table.allocations = NULL == allocations ? NULL : allocations != value ? static_cast<storage<void>*>(allocations) : /* ->> `bless(...)` becomes redundant */ value;
              allocation::table.capacity    = capacity;

              return evaluation;
            }
          };

          /* ... */
          storage<element> &dynamic = this -> elements[this -> precapacity].dynamic;

          // ...
          if (count <= this -> precapacity) {
            // ... ->> Destruct `::dynamic` elements
            for (element *iterator = dynamic.value + dynamic.length; iterator != dynamic.value; )
              bless(--iterator) -> ~element();

            // ... ->> Destruct excess `::automatic` elements
            for (struct elements *iterator = this -> elements + this -> precapacity, *const end = this -> elements + count; iterator != end; ) {
              if (NULL != --iterator -> value)
              iterator -> value -> ~element();
            }

            // ... ->> Scrub reusable `storage`
            for (unsigned char *iterator = bytesof(dynamic.value + dynamic.length); dynamic.length--; )
              *--iterator = 0x00u; // --> std::memset(dynamic.value, 0x00, dynamic.length * sizeof element);

            for (struct elements *iterator = this -> elements + this -> precapacity, *const end = this -> elements + count; iterator != end; ) {
              (--iterator) -> value = NULL;

              for (unsigned char *subiterator = iterator -> automatic + sizeof(element); subiterator != iterator -> automatic; )
              *--subiterator = 0x00u; // --> std::memset(iterator -> automatic, 0x00, sizeof element);
            }

            // ... ->> Release `::dynamic` `storage`
            if (0u != dynamic.capacity) {
              // ... ->> Swap `allocation::table` `storage` for sufficiently larger `::dynamic` `storage`
              if (allocation::table.capacity <= dynamic.capacity / allocation::table.rate) {
                storage<void> const allocation = table::swap(dynamic.value, dynamic.capacity);

                // ...
                dynamic.capacity = allocation.capacity;
                dynamic.value    = allocation.value;
              }

              // ... ->> Enlarge `allocation::table` `storage` to store `::dynamic` `storage`
              if (allocation::table.capacity < sizeof(storage<void>) + (allocation::table.size * sizeof(storage<void>))) {
                storage<void> *dynamic = NULL;

                // ... ->> Enlarge `allocation::table` `storage` by external memory management features
                if (allocation::table.capacity <= UINTMAX_MAX /* --> SIZE_MAX */ / allocation::table.rate) // ->> Do not aggressively enlarge `allocation::table` `storage`
                for (std::size_t next = allocation::table.capacity >= sizeof(storage<void>) ? allocation::table.capacity * allocation::table.rate : sizeof(storage<void>); allocation::table.capacity != next and next > sizeof(storage<void>) + (allocation::table.size * sizeof(storage<void>)); next = (allocation::table.capacity + next) / 2u) {
                  void *const allocation = NULL == allocation::table.allocations ? std::malloc(next) : std::realloc(allocation::table.allocations, next);

                  // ...
                  if (NULL != allocation) {
                    allocation::table.allocations = static_cast<storage<void>*>(allocation);
                    allocation::table.capacity    = next;

                    goto allocated;
                  }
                }

                // ... ->> Enlarge `allocation::table` `storage` by swapping with sufficiently large `::dynamic` `storage`
                for (storage<void> *iterator = allocation::table.allocations + allocation::table.size; iterator != allocation::table.allocations; ) {
                  storage<void> *const allocation = bless(--iterator);
                  dynamic = NULL == dynamic or allocation -> capacity > dynamic -> capacity ? allocation : dynamic;
                }

                if (NULL != dynamic and dynamic -> capacity >= sizeof(storage<void>) + (allocation::table.size * sizeof(storage<void>))) {
                  storage<void> const allocation = table::swap(dynamic -> value, dynamic -> capacity);

                  // ...
                  dynamic -> capacity = allocation.capacity;
                  dynamic -> value    = allocation.value;
                }

                // ...
                allocated:
              }

              // ... ->> Store `::dynamic` `storage` in `allocation::table`
              if (allocation::table.capacity >= sizeof(storage<void>) + (allocation::table.size * sizeof(storage<void>))) {
                storage<void> *allocation = NULL;

                // ... ->> See use of external memory management features (ie: `std::malloc(...)` and `std::realloc(...)`) in the previous code block
                if (allocation::table.capacity == sizeof(storage<void>) and 0u == allocation::table.size) {
                  allocation                    = ::new (allocation::table.allocations) storage<void>[1];
                  allocation::table.allocations = allocation == allocation::table.allocations ? /* ->> `bless(...)` becomes redundant */ allocation : allocation::table.allocations;
                  allocation::table.size        = 1u;
                }

                else
                  allocation = ::new (allocation::table.allocations + allocation::table.size++) storage<void>;

                // ...
                allocation -> capacity = dynamic.capacity;
                allocation -> length   = 0u;
                allocation -> value    = dynamic.value;

                dynamic.value = NULL; // ->> Do not release `::dynamic` `storage` since it is stored within `allocation::table`
              }

              // ... ->> Release `::dynamic` `storage`
              std::free(dynamic.value);

              dynamic.capacity = 0u;
              dynamic.value    = NULL;
            }
          }

          else {
            count -= this -> precapacity;

            // ... ->> Allocate additional `storage` for `::dynamic`
            if (dynamic.capacity < count * sizeof(element)) {
              std::size_t next = dynamic.capacity;

              // ...
              while (0u != next % /* --> alignof ... */ sizeof(element))
                ++next;

              for (std::size_t rate = 2u; ; ++rate) {
                if (next <= (UINTMAX_MAX / (rate + 1u)) * rate) { next  = (next * (rate + 1u)) / rate; break; }
                if (dynamic.length <= rate)                     { next += sizeof(element);             break; }
              }

              next = next < sizeof(element) * 2u ? sizeof(element) * 2u : next;

              // ... ->> Swap `::dynamic` `storage` without forcing user-side side-effects like constructor calls
              if (is_trivial<element>::value or 0u == dynamic.length) {
                storage<void> *allocation = NULL;

                // ... ->> Allocate `storage` from best-fitting `::dynamic` within `allocation::table`
                for (storage<void> *iterator = allocation::table.allocations + allocation::table.size; iterator != allocation::table.allocations; ) {
                  storage<void> *const suballocation = bless(--iterator);

                  // ...
                  if (suballocation -> capacity >= count * sizeof(element))
                  allocation = NULL == allocation or (
                    // ->> Best-fit: `::capacity == next`
                    (allocation    -> capacity < next ? next - allocation    -> capacity : allocation    -> capacity - next) >
                    (suballocation -> capacity < next ? next - suballocation -> capacity : suballocation -> capacity - next)
                  ) ? suballocation : allocation;
                }

                if (NULL != allocation) /* --> dynamic.swap(allocation) */ {
                  std::size_t const capacity = allocation -> capacity;
                  element          *value    = ::new (allocation -> value) element[dynamic.length] + dynamic.length;

                  // ... ->> Copy old `::dynamic` `storage` into new `::dynamic` `storage` (or best-fitting `allocation::table` `::dynamic`)
                  for (element *iterator = dynamic.value + dynamic.length; iterator != dynamic.value; )
                    *--value = *bless(--iterator);

                  // ... ->> Scrub reusable `storage`
                  for (unsigned char *iterator = bytesof(dynamic.value + dynamic.length); iterator != bytesof(dynamic.value); )
                    *--iterator = 0x00u; // --> std::memset(dynamic.value, 0x00, dynamic.length * sizeof element);

                  // ...
                  value = allocation -> value != value ? allocation -> value : /* ->> `bless(...)` becomes redundant */ value;

                  allocation -> capacity = dynamic.capacity;
                  allocation -> value    = dynamic.value;

                  dynamic.capacity = capacity;
                  dynamic.value    = value;
                }

                // ... ->> Swap `::dynamic` `storage` for sufficiently larger `allocation::table` `storage`
                else if (0u == allocation::table.size and allocation::table.capacity >= count * sizeof(element)) {
                  storage<void> const allocation = table::swap(dynamic.value, dynamic.capacity);

                  // ...
                  dynamic.capacity = allocation.capacity;
                  dynamic.value    = allocation.value;
                }
              }

              // ... ->> Enlarge `::dynamic` `storage` by external memory management features
              if (dynamic.capacity < count * sizeof(element))
              for (; next >= dynamic.capacity + sizeof(element); next = (dynamic.capacity + next + sizeof(element)) / 2u) {
                void *const allocation = NULL == dynamic.value ? std::calloc(next, sizeof(unsigned char)) : std::realloc(dynamic.value, next);

                // ...
                if (NULL != allocation) {
                  dynamic.capacity = next;
                  dynamic.value    = static_cast<element*>(allocation);

                  break;
                }
              }

              // ...
              if (dynamic.capacity < count * sizeof(element))
                return false;
            }

            else {
              // ... ->> Destruct excess `::dynamic` elements
              for (element *iterator = dynamic.value + dynamic.length, *const end = dynamic.value + count; iterator != end; )
              bless(--iterator) -> ~element();

              // ... ->> Scrub reusable `storage`
              for (unsigned char *iterator = bytesof(dynamic.value + dynamic.length), *const end = bytesof(dynamic.value + count); iterator != end; )
              *--iterator = 0x00u; // --> std::memset(dynamic.value + count, 0x00, (dynamic.length - count) * sizeof element);

              // ->> Risk of `::dynamic.length` miscounting (greater than) the number of elements within its `storage`
            }
          }

          // ...
          return true;
        }

        // ...
        /* constexpr */ inline void resize(std::size_t const count) /* noexcept */ {
          // ... ->> Resize `::automatic` "length" and `::dynamic` `length`
          if (count > this -> precapacity)
            this -> elements[this -> precapacity].dynamic.length = count - this -> precapacity;

          else {
            this -> elements[this -> precapacity].dynamic.length = 0u;

            for (struct elements *iterator = this -> elements + this -> precapacity, *const end = this -> elements + count; iterator != end; )
            (--iterator) -> value = NULL;
          }

          // ... ->> Grow `::automatic` "length" by falsely instantiating uninitialized `::automatic` elements
          for (struct elements *iterator = this -> elements + this -> precapacity + (count <= this -> precapacity ? count : this -> precapacity); iterator != this -> elements; ) {
            if (NULL == (--iterator) -> value)
            iterator -> value = bless(reinterpret_cast<element*>(iterator -> automatic));
          }
        }

        // ...
        template <typename type, std::size_t capacity>
        array& operator =(array<type, capacity> const& array) /* noexcept(...) */ {
          storage<element> &dynamic = this -> elements[this -> precapacity].dynamic;
          std::size_t const length  = array.lengthof();

          // ...
          if (length > this -> capacityof() or this -> reserve(length)) {
            // ... ->> Destruct all `::automatic` and `::dynamic` elements
            for (element *iterator = dynamic.value + dynamic.length; iterator != dynamic.value; )
              bless(--iterator) -> ~element();

            for (struct elements *iterator = this -> elements + this -> precapacity; iterator != this -> elements; ) {
              if (NULL != --iterator -> value)
              iterator -> value -> ~element();
            }

            // ... ->> Scrub pending storage
            dynamic.length = length > this -> precapacity ? length - this -> precapacity : 0u;

            for (unsigned char *iterator = bytesof(dynamic.value + dynamic.length); iterator != bytesof(dynamic.value); )
              *--iterator = 0x00u; // --> std::memset(dynamic.value, 0x00, dynamic.length * sizeof element);

            for (struct elements *iterator = this -> elements + this -> precapacity; iterator != this -> elements; ) {
              (--iterator) -> value = NULL;

              for (unsigned char *subiterator = iterator -> automatic + sizeof(element); subiterator != iterator -> automatic; )
              *--subiterator = 0x00u; // --> std::memset(iterator -> automatic, 0x00, sizeof element);
            }

            // ... ->> Value-initialize all elements using `array`
            for (std::size_t index = 0u; index != length; ++index) {
              if (index < this -> precapacity) {
                this -> elements[index].value = instantiate<element>(this -> elements[index].automatic, *array.at(index));
                continue;
              }

              (void) instantiate<element>(this -> elements[this -> precapacity].dynamic.value + (index - this -> precapacity), *array.at(index));
            }
          }

          return *this;
        }

        /* constexpr */ inline base& operator [](std::size_t const index) const /* noexcept */ {
          return *(index < this -> capacityof() and index < this -> lengthof() ? this -> at(index) : NULL);
        }
    };

    // ...
    template <std::size_t precapacity>
    struct biguint /* final */ : public array<digit, precapacity> {
      /* constexpr */ inline biguint(uintmax_t integer) /* noexcept */ :
        array<digit, precapacity>::array()
      {
        if (radix != 1u) {
          std::size_t rank = 0u == integer;

          // ...
          for (uintmax_t value = integer; value; value /= radix)
            ++rank;

          if (this -> reserve(rank))
          for (this -> resize(rank); rank--; integer /= radix) {
            if (rank < this -> precapacity) {
              this -> elements[rank].value = instantiate<element>(this -> elements[rank].automatic, integer % radix);
              continue;
            }

            (void) instantiate<element>(this -> elements[this -> precapacity].dynamic.value + (rank - this -> precapacity), integer % radix);
          }
        }

        else if (this -> reserve(integer)) {
          this -> resize(integer);

          while (integer--) {
            if (integer < this -> precapacity) {
              this -> elements[integer].value = instantiate<element>(this -> elements[integer].automatic, 0u);
              continue;
            }

            (void) instantiate<element>(this -> elements[this -> precapacity].dynamic.value + (integer - this -> precapacity), 0u);
          }
        }
      }

      // ...
      template <std::size_t capacity>
      /* constexpr */ inline biguint(biguint<capacity> const& integer) /* noexcept */ :
        array<digit, precapacity>::array()
      { (void) this -> template array<digit, precapacity>::operator =(integer); }

      /* ... */
      template <std::size_t capacity>
      bool add(biguint<capacity> const& integer) /* noexcept */ {
        bool        carry   = false;
        std::size_t rank    = this -> lengthof();
        std::size_t subrank = integer.lengthof();

        // ...
        if (rank < subrank) {
          std::size_t index = subrank;

          // ...
          if (not this -> shift(subrank))
            return false;

          while (rank)  this -> operator [](--index) = this -> operator [](--rank);
          while (index) this -> operator [](--index) = 0u;

          rank = subrank;
        }

        while (subrank) {
          digit const subdigit = integer[--subrank];

          // ...
          if (this -> operator [](--rank) > radix - subdigit - 1u) {
            this -> operator [](rank) -= radix - subdigit - carry;
            carry                      = true;
          }

          else {
            this -> operator [](rank) += subdigit;
            carry                      = false;
          }
        }

        if (carry) {
          if (0u == rank) {
            if (not this -> shift(1u))
              return false;

            for (rank = this -> lengthof(); --rank; )
              this -> operator [](rank - 0u) = this -> operator [](rank - 1u);

            this -> operator [](0u) = 0u;
          }

          while (rank and this -> operator [](rank) == radix - 1u)
            this -> operator [](rank--) = 0u;

          // if (0u == rank) {}
        }

        // ...
        return true;
      }

      // ...
      /* constexpr */ inline signed char compare(biguint const& integer) const /* noexcept */ {
        return this -> greater(integer) ? +1 : this -> lesser(integer) ? : -1 : 0;
      }

      // ...
      /* constexpr */ inline void decrement() /* noexcept */ {
        if (radix != 1u) {
          std::size_t const length = this -> lengthof();
          std::size_t       rank   = length;

          // ...
          while (0u == this -> operator [](--rank))
            continue;

          --(this -> operator [](rank));

          while (length != rank++)
            this -> operator [](rank) = radix - 1u;

          if (0u == this -> operator [](0u)) {
            for (rank = 0u; rank != length - 1u; ++rank)
              this -> operator [](rank + 0u) = this -> operator [](rank + 1u);

            this -> pop();
          }

          // ...
          return;
        }

        this -> pop();
      }

      // ...
      void divide();

      // ...
      /* constexpr */ inline bool equals(biguint const& integer) const /* noexcept */ {
        std::size_t rank = this -> lengthof();

        // ...
        if (rank != integer.lengthof())
        return false;

        while (rank--) {
          if (this -> operator [](rank) != integer[rank])
          return false;
        }

        // ...
        return true;
      }

      // ...
      bool exponentiate();

      // ...
      /* constexpr */ inline bool greater(biguint const& integer) const /* noexcept */ {
        std::size_t const rank    = this -> lengthof();
        std::size_t const subrank = integer.lengthof();

        // ...
        if (rank == subrank)
        for (std::size_t index = 0u; index != rank; ++index) {
          if (this -> operator [](index) > integer[index])
          return true;
        }

        return rank > subrank;
      }

      // ...
      /* constexpr */ inline bool increment() /* noexcept */ {
        if (radix != 1u) {
          std::size_t const length = this -> lengthof();
          std::size_t       rank   = length;

          // ...
          while (rank and this -> operator [](--rank) == radix - 1u)
          continue;

          if (rank or this -> operator [](0u) != radix - 1u)
            ++(this -> operator [](rank));

          else {
            if (not this -> add(0u))
              return false;

            this -> operator [](0u) = radix != 1u;
          }

          while (length != ++rank)
          this -> operator [](rank) = 0u;

          // ...
          return true;
        }

        return this -> add(0u);
      }

      // ...
      /* constexpr */ inline bool lesser(biguint const& integer) const /* noexcept */ {
        std::size_t const rank    = this -> lengthof();
        std::size_t const subrank = integer.lengthof();

        // ...
        if (rank == subrank)
        for (std::size_t index = 0u; index != rank; ++index) {
          if (this -> operator [](index) < integer[index])
          return true;
        }

        return rank < subrank;
      }

      // ...
      bool modulo();

      // ...
      template <std::size_t capacity>
      bool multiply(biguint<capacity> const&);

      // ...
      inline bool shift(std::size_t const count) /* noexcept */ {
        std::size_t const rank = this -> lengthof();

        // ...
        if (not this -> reserve(count + rank))
          return false;

        this -> resize(count + rank);

        for (std::size_t index = count + rank; index-- != rank; ) {
          if (index < this -> precapacity) {
            this -> elements[index].value = instantiate<element>(this -> elements[index].automatic, 0u);
            continue;
          }

          (void) instantiate<element>(this -> elements[this -> precapacity].dynamic + (index - this -> precapacity), 0u);
        }

        return true;
      }

      // ...
      void subtract();

      // ...
      /* constexpr */ inline void unshift(std::size_t const count) /* noexcept */ {
        std::size_t const rank = this -> lengthof();

        // ...
        if (count >= rank)
          this -> zero();

        else {
          (void) this -> reserve(rank - count);
          this -> resize(rank - count);
        }
      }

      // ...
      /* constexpr */ inline void zero() /* noexcept */ {
        this -> empty();
      }
    };

  public:
    struct operation /* final */ {
      typedef std::size_t state;

      /* ... */
      bool                              (&function)(bignum&, state[]);
      struct : public array<state, 0u> {} states;

      /* ... */
      inline operation(bool (&function)(bignum&, state[]), std::size_t const arity) /* noexcept */ :
        function(function),
        states  ()
      { (void) this -> states.grow(arity, 0u); }
    };

  /* ... */
  private:
    biguint<>        denominator;
    biguint<>        numerator;
    array<operation> operations;
    bool             signedness;

    /* ... */
    bool add(bignum const&) /* noexcept */;

    // ...
    template <std::size_t precapacity>
    bool assign(array<digit, precapacity> bignum::* const digits, long double const integer) /* noexcept */ {
      static_cast<void>(digits);
      static_cast<void>(integer);
      // std::size_t  length = 0u;
      // bignum       radix  = bignum();
      // long double  rank   = 1.00L;

      // // ... --> radix = 2;
      // if (bignum::radix > 1u)
      //   radix.numerator[0] = 2u;

      // else {
      //   radix.numerator[0] = 1u;
      //   (void) radix.numerator.add(0u);
      // }

      // // ... --> length = std::log10l(integer); rank = std::powl(10.00L, length);
      // for (long double const end = integer / 2.00L; rank <= end and rank <= LDBL_MAX / 2.00L; ) {
      //   length += 1u;
      //   rank   *= 2.00L;
      // }

      // // ...
      // bignum::zero(this ->* digits);

      // for (length = 0u; rank >= 1.00L; ++length, rank /= 2.00L) {
      //   unsigned char const bit = integer >= /* --> rank * 1.00L */ rank ? 1u : 0u;

      //   // ... --> (void) bits.add(bit);
      //   integer -= rank * bit;

      //   bignum::multiply(this ->* digits, radix);
      //   bignum::multiply(digits, );

      //   if (length < precapacity) bits.elements.value[length].value = ::new (bits.elements.value[length].automatic) typename bit(bit);
      //   else (void) ::new (bits.elements.value[precapacity].dynamic.value + (length - precapacity)) typename bit(bit);
      // }

      // if (length > precapacity)
      // bits.elements.value[precapacity].dynamic.length = length - precapacity;

      // // ...
      // return true;
    }

    // ...
    bool decrement() /* noexcept */;

    // ...
    bool doubly() /* noexcept */;

    // ...
    bool exponentiate(bignum const&) /* noexcept */;

    // ...
    bool increment() /* noexcept */;

    // ...
    bool multiply(bignum const&) /* noexcept */;

    // ...
    static void nan() /* noexcept(...) ->> Depends if `NaN` is signaling or not */;

    // ...
    /* constexpr */ inline static long double truncate(long double const number) /* noexcept */ {
      if (UINTMAX_MAX < number) {
        long double truncation = 1.00L;

        // ... ->> Count up to `number` in multiples of `truncation`
        for (long double rate = 1.00L; number > truncation; ) {
          long double const increment = truncation / rate;

          // ...
          if (increment < 1.00L or increment != bignum::truncate(increment))
            break;

          if (truncation <= LDBL_MAX - increment) {
            if (number < truncation + increment)
              break;

            truncation += increment;
            continue;
          }

          rate *= 2.00L;
        }

        // ... ->> Count up to `number` in multiples of two where `rate >= 1.00L`
        for (long double rate = 1.00L; number != truncation; ) {
          while (truncation == truncation + rate or (number > truncation + rate and rate <= LDBL_MAX / 2.00L))
            rate *= 2.00L;

          while (number < truncation + rate and rate > 1.00L)
            rate /= 2.00L;

          if (number < truncation + rate)
            break;

          truncation += rate;
        }

        // ...
        return truncation;
      }

      return static_cast<uintmax_t>(number);
    }

  public:
    inline bignum() :
      denominator(1u),
      numerator  (0u),
      operations (),
      signedness (false)
    {
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
        this -> denominator = 0u;
        return;
      }

      // ...
      if (reinterpret_cast<unsigned char*>(this) == &reinterpret_cast<unsigned char const&>(bignum::ONE)) {
        this -> numerator = 1u;
        return;
      }

      // ...
      if (reinterpret_cast<unsigned char*>(this) == &reinterpret_cast<unsigned char const&>(bignum::PI)) {
        this -> denominator = 78256779u;
        this -> numerator   = 245850922u;

        return;
      }

      // ...
      if (reinterpret_cast<unsigned char*>(this) == &reinterpret_cast<unsigned char const&>(bignum::TAU)) {
        this -> denominator = 78256779u;
        this -> numerator   = 491701844u;

        return;
      }

      // ...
      if (reinterpret_cast<unsigned char*>(this) == &reinterpret_cast<unsigned char const&>(bignum::ZERO))
      return;
    }

    // ...
    /* constexpr */ inline bignum(long double number) /* noexcept */ :
      denominator(),
      numerator  (),
      operations (),
      signedness (number < +0.00L)
    {
      // ... ->> Not-a-Number representation
      if (number != number) {
        bignum::nan();
        return;
      }

      number = this -> signedness ? -number : +number;

      // ... ->> Infinity representation
      if (number == 1.00L / 0.00L) {
        this -> denominator = 0u;
        this -> numerator   = 0u;

        return;
      }

      /* ... ->> Normalized representation */ {
        long double const characteristics = bignum::truncate(number);

        // ...
        if (characteristics == number) {
          this -> denominator = 1u;
          (void) this -> assign(&bignum::numerator, characteristics);
        }

        else {
          // long double       denominator = 0.00L;
          // long double       divisor     = 0.00L;
          // long double const mantissa    = number - characteristics;
          // long double       numerator   = 0.00L;
          // long double       whole       = 0.00L;

          // // ...
          // denominator = 1.00L;
          // numerator   = mantissa;
          // whole       = characteristics;

          // // ...
          // while (not bignum::truncate(numerator) and numerator <= LDBL_MAX / 10.00L) {
          //   denominator *= 10.00L;
          //   numerator   *= 10.00L;
          // }

          // divisor = denominator;

          // for (var number = numerator, remainder; ; ) {
          //   remainder = number % divisor;
          //   if (0 == remainder) break;

          //   number = divisor;
          //   divisor = remainder;
          // }

          // denominator /= divisor;
          // numerator   /= divisor;
        }
      }
    }

    // ...
    /* constexpr */ inline bignum(bignum const& number) /* noexcept */ :
      denominator(number.denominator),
      numerator  (number.numerator),
      operations (),
      signedness (number.signedness)
    { this -> operations = number.operations; }
};
  bignum::allocation::value bignum::allocation::table = {};

  bignum const bignum::EULER    = bignum();
  bignum const bignum::INFINITY = bignum();
  bignum const bignum::ONE      = bignum();
  bignum const bignum::PI       = bignum();
  bignum const bignum::TAU      = bignum();
  bignum const bignum::ZERO     = bignum();

/* Main */
int main(int, char*[]) /* noexcept */ {
}
