#include <cfloat>   // --> LDBL_MAX
#include <ciso646>  //
#include <climits>  // --> CHAR_BIT, UINTMAX_MAX
#include <cstddef>  // --> std::size_t
#include <cstdio>   //
#include <cstdlib>  // --> std::calloc(...), std::free(...), std::malloc(...), std::realloc(...)
#include <new>      // --> new
#include <stdint.h> // --> uintmax_t
#ifdef __cpp_lib_endian // --> 201907L
# include <bit> // --> std::endian
#endif
#if __cplusplus >= 201103L or defined _MSVC_LANG // --> +201402L
# include <type_traits> // --> std::is_enum, std::is_function, std::is_trivial
#endif

/* ... */
struct bignum /* final */ {
  public:
    typedef unsigned char digit; // ->> Component part of `::denominator` and `::numerator` `array`s; must be an integer type
    struct operation;            // ->> Sequence of iterable continuous functions that more precisely compute `bignum`

  private:
    struct allocation;                // ->> Dynamically-allocated memory management interface for `array::dynamic` elements
    struct byte_iterator;             // ->> Common interface for object address converted to byte addresses (allows for optimal byte traversal); see `bytesof(...)`
    enum   sfinaeptr_t { sfinaeptr }; // ->> Dummy/ extension type used for selective overloading/ specialization for evaluating possible compile-time constraints and expressions

    template <typename, std::size_t = 1u>                      struct array;                  // ->> Variable-length collection of contiguous `base` objects (such as `digit`s or `operation::state`s)
    template <typename>                                        struct baseof;                 // ->> Removes qualifiers from specified type -- to allow `array`s handle their `elements` generically
    template <std::size_t = 128u / (CHAR_BIT * sizeof(digit))> struct biguint;                // ->> `::denominator` and `::numerator` types
    template <typename>                                        struct is_bless_constructible; // ->> Evaluates if type can be completely and correctly constructed using a "blessed" type; see `struct is_blessed<>` definition
    template <typename>                                        struct is_bless_decomposable;  // ->> Evaluates if type can be correctly decomposed (via bitwise manipulation for integers or other means) by a "blessed" type; see `struct is_blessed<>` definition
    template <typename>                                        struct is_blessed;             // ->> Determines the object address provenance of the specified type
    template <typename>                                        struct is_byte;                // ->> Evaluates if type is a byte type -- to help determine its "blessedness"; see `struct is_blessed<>` definition
    template <typename>                                        struct is_enum;                // ->> Evaluates if type is an enumeration type -- to help determine its triviality; see `struct is_trivial<>` definition
    template <typename>                                        struct is_function;            // ->> Evaluates if type is a function type
    template <typename>                                        struct is_integer;             // ->> Evaluates if type is (based on) an integer type -- to help determine its "blessedness"; see `struct is_bless_constructible<>` or `struct is_bless_decomposable<>` definitions
    template <typename>                                        struct is_trivial;             // ->> Determines the triviality of constructing/ destructing the specified type -- to allow `array`s optimally read/ write their `elements`

  /* ... */
  private:
    template <typename base> struct baseof                      /* final */ { typedef base type; };
    template <typename base> struct baseof<base&>               /* final */ { typedef typename baseof<base>::type type; };
    template <typename base> struct baseof<base const>          /* final */ { typedef typename baseof<base>::type type; };
    template <typename base> struct baseof<base const volatile> /* final */ { typedef typename baseof<base>::type type; };
    template <typename base> struct baseof<base       volatile> /* final */ { typedef typename baseof<base>::type type; };
    #ifdef __cpp_rvalue_references // --> 200610L
      template <typename base> struct baseof<base&&> /* final */ { typedef typename baseof<base>::type type; };
    #endif

    // ...
    struct byte_iterator {
      protected:
        struct byte_proxy /* final */ : public byte_iterator {
          constexpr inline byte_proxy&   operator ++()          /* noexcept */ { switch (this -> type) { case 0x1u: ++*(this -> valueB); break; case 0x2u: ++*(this -> valueC); break; default: ++*(this -> valueA); break; } return *this; }
          constexpr inline byte_proxy&   operator --()          /* noexcept */ { switch (this -> type) { case 0x1u: --*(this -> valueB); break; case 0x2u: --*(this -> valueC); break; default: --*(this -> valueA); break; } return *this; }
          constexpr inline unsigned char operator ++(int const) /* noexcept */ { switch (this -> type) { case 0x1u: return (*(this -> valueB))++; case 0x2u: return (*(this -> valueC))++; } return (*(this -> valueA))++; }
          constexpr inline unsigned char operator --(int const) /* noexcept */ { switch (this -> type) { case 0x1u: return (*(this -> valueB))--; case 0x2u: return (*(this -> valueC))--; } return (*(this -> valueA))--; }

          constexpr inline byte_proxy& operator =  (unsigned char const value) /* noexcept */ { switch (this -> type) { case 0x1u: *(this -> valueB) =   value; break; case 0x2u: *(this -> valueC) =  value; break; default: *(this -> valueA) =   value; break; } return *this; }
          constexpr inline byte_proxy& operator += (unsigned char const value) /* noexcept */ { switch (this -> type) { case 0x1u: *(this -> valueB) +=  value; break; case 0x2u: *(this -> valueC) += value; break; default: *(this -> valueA) +=  value; break; } return *this; }
          constexpr inline byte_proxy& operator -= (unsigned char const value) /* noexcept */ { switch (this -> type) { case 0x1u: *(this -> valueB) -=  value; break; case 0x2u: *(this -> valueC) -= value; break; default: *(this -> valueA) -=  value; break; } return *this; }
          constexpr inline byte_proxy& operator *= (unsigned char const value) /* noexcept */ { switch (this -> type) { case 0x1u: *(this -> valueB) *=  value; break; case 0x2u: *(this -> valueC) *= value; break; default: *(this -> valueA) *=  value; break; } return *this; }
          constexpr inline byte_proxy& operator /= (unsigned char const value) /* noexcept */ { switch (this -> type) { case 0x1u: *(this -> valueB) /=  value; break; case 0x2u: *(this -> valueC) /= value; break; default: *(this -> valueA) /=  value; break; } return *this; }
          constexpr inline byte_proxy& operator &= (unsigned char const value) /* noexcept */ { switch (this -> type) { case 0x1u: *(this -> valueB) &=  value; break; case 0x2u: *(this -> valueC) &= value; break; default: *(this -> valueA) &=  value; break; } return *this; }
          constexpr inline byte_proxy& operator |= (unsigned char const value) /* noexcept */ { switch (this -> type) { case 0x1u: *(this -> valueB) |=  value; break; case 0x2u: *(this -> valueC) |= value; break; default: *(this -> valueA) |=  value; break; } return *this; }
          constexpr inline byte_proxy& operator ^= (unsigned char const value) /* noexcept */ { switch (this -> type) { case 0x1u: *(this -> valueB) ^=  value; break; case 0x2u: *(this -> valueC) ^= value; break; default: *(this -> valueA) ^=  value; break; } return *this; }
          constexpr inline byte_proxy& operator <<=(unsigned char const value) /* noexcept */ { switch (this -> type) { case 0x1u: *(this -> valueB) <<= value; break; case 0x2u: *(this -> valueC) <<=value; break; default: *(this -> valueA) <<= value; break; } return *this; }
          constexpr inline byte_proxy& operator >>=(unsigned char const value) /* noexcept */ { switch (this -> type) { case 0x1u: *(this -> valueB) >>= value; break; case 0x2u: *(this -> valueC) >>=value; break; default: *(this -> valueA) >>= value; break; } return *this; }

          constexpr inline operator unsigned char() const /* noexcept */ { switch (this -> type) { case 0x1u: return *(this -> valueB); case 0x2u: return *(this -> valueC); } return *(this -> valueA); }
        };

        /* ... */
        union {
          unsigned char *valueA;
          char          *valueB;
          #ifdef __cpp_lib_byte // --> 201603L
            std::byte *valueC;
          #else
            unsigned char *valueC;
          #endif
        };
        unsigned char const type;

      public:
        constexpr inline byte_iterator(char          const volatile value[]) /* noexcept */ : valueB                            (const_cast<char*>         (value)),  type(0x1u) {}
        constexpr inline byte_iterator(unsigned char const volatile value[]) /* noexcept */ : valueA                            (const_cast<unsigned char*>(value)),  type(0x0u) {}
        constexpr inline byte_iterator(void const volatile* const   value)   /* noexcept */ : valueA(static_cast<unsigned char*>(const_cast<void*>         (value))), type(0x0u) {}
        #ifdef __cpp_lib_byte // --> 201603L
          constexpr inline byte_iterator(std::byte const volatile value[]) /* noexcept */ : valueC(const_cast<std::byte*>(value)), type(0x2u) {}
        #endif

        /* ... */
        constexpr inline byte_proxy     operator * () const    /*   noexcept */ { switch (this -> type) { case 0x1u: return this -> valueB; case 0x2u: return this -> valueC; } return this -> valueA; }
        constexpr inline byte_iterator& operator ++()          /* & noexcept */ { switch (this -> type) { case 0x1u: ++(this -> valueB); break; case 0x2u: ++(this -> valueC); break; default: ++(this -> valueA); break; } return *this; }
        constexpr inline byte_iterator& operator --()          /* & noexcept */ { switch (this -> type) { case 0x1u: --(this -> valueB); break; case 0x2u: --(this -> valueC); break; default: --(this -> valueA); break; } return *this; }
        constexpr inline byte_iterator  operator ++(int const) /* & noexcept */ { return byte_iterator(this -> operator ++()).operator --(); }
        constexpr inline byte_iterator  operator --(int const) /* & noexcept */ { return byte_iterator(this -> operator --()).operator ++(); }
    };

    // ...
    template <typename base>
    struct is_bless_constructible /* final */ {
      static bool const value = is_integer<base>::value;
    };

    // ...
    template <typename base>
    struct is_bless_decomposable /* final */ {
      static bool const value = is_integer<base>::value;
    };

    // ...
    template <typename base>
    struct is_blessed /* final */ {
      static bool const value = is_byte<base>::value;
    };

    // ...
    template <typename base>
    struct is_byte /* final */ {
      private:
        template <typename base, sfinaeptr_t = sfinaeptr> struct valueof                                       /* final */ { static bool const value = false; };
        template <sfinaeptr_t sfinae>                     struct valueof<char          const volatile, sfinae> /* final */ { static bool const value = true;  };
        template <sfinaeptr_t sfinae>                     struct valueof<unsigned char const volatile, sfinae> /* final */ { static bool const value = true;  };
        #ifdef __cpp_lib_byte // --> 201603L
          template <sfinaeptr_t sfinae> struct valueof<std::byte const volatile, sfinae> /* final */ { static bool const value = true; };
        #endif

      public:
        static bool const value = valueof<base const volatile>::value;
    };

    // ...
    template <typename base>
    struct is_enum /* final */  {
      #if __cplusplus >= 201402L or defined _MSVC_LANG // --> +201402L
        static bool const value = std::is_enum<base>::value;
      #else
        private:
          template <class type> static bool const (&is_class(sfinaeptr_t const, bool const (*const)[sizeof static_cast<int type::*>(NULL)] = NULL) /* noexcept */)[true  + 1u];
          template <class>      static bool const (&is_class(...)                                                                                  /* noexcept */)[false + 1u];

          template <typename type> static bool const (&is_integer_constant(sfinaeptr_t const, bool const (*const)[static_cast<type>(1u)] = NULL) /* noexcept */)[true  + 1u];
          template <typename>      static bool const (&is_integer_constant(...)                                                                  /* noexcept */)[false + 1u];

        public:
          static bool const value = sizeof(bool const[false + 1u]) == sizeof is_class<base>(sfinaeptr) and sizeof(bool const[true + 1u]) == sizeof is_integer_constant<base>(sfinaeptr);
      #endif
    };

    // ...
    #if __cplusplus >= 201103L or defined _MSVC_LANG // --> +201402L
      template <typename base>
      struct is_function /* final */ {
        static bool const value = std::is_function<base>::value;
      };
    #else
      template <typename base>
      struct is_function /* final */ {
        private:
          template <typename, typename>
          struct valueof /* final */ {
            template <typename> static bool const (&valueof(...) /* noexcept */)[false + 1u];
          };

          template <typename subbase>
          struct valueof<subbase, subbase> /* final */ {
            template <typename type> static bool const (&valueof(sfinaeptr_t const, type) /* noexcept */)[false + 1u];
            template <typename>      static bool const (&valueof(...)                     /* noexcept */)[true  + 1u];
          };

        public:
          static bool const value = sizeof(bool const[true + 1u]) == sizeof valueof<base, base const volatile>::template value<base>(sfinaeptr);
      };
    #endif

    // ...
    #if __cplusplus >= 201103L or defined _MSVC_LANG // --> +201402L
      template <typename base>
      struct is_integer /* final */ {
        static bool const value = is_enum<base>::value or std::is_integer<base>::value;
      };
    #else
      template <typename base>
      struct is_integer /* final */ {
        private:
          template <typename subbase, sfinaeptr_t = sfinaeptr> struct valueof                                        /* final */ { static bool const value = is_enum<subbase>::value; };
          template <sfinaeptr_t sfinae>                        struct valueof<bool           const volatile, sfinae> /* final */ { static bool const value = true;                    };
          template <sfinaeptr_t sfinae>                        struct valueof<char           const volatile, sfinae> /* final */ { static bool const value = true;                    };
          template <sfinaeptr_t sfinae>                        struct valueof<int            const volatile, sfinae> /* final */ { static bool const value = true;                    };
          template <sfinaeptr_t sfinae>                        struct valueof<long           const volatile, sfinae> /* final */ { static bool const value = true;                    };
          template <sfinaeptr_t sfinae>                        struct valueof<short          const volatile, sfinae> /* final */ { static bool const value = true;                    };
          template <sfinaeptr_t sfinae>                        struct valueof<signed char    const volatile, sfinae> /* final */ { static bool const value = true;                    };
          template <sfinaeptr_t sfinae>                        struct valueof<unsigned char  const volatile, sfinae> /* final */ { static bool const value = true;                    };
          template <sfinaeptr_t sfinae>                        struct valueof<unsigned int   const volatile, sfinae> /* final */ { static bool const value = true;                    };
          template <sfinaeptr_t sfinae>                        struct valueof<unsigned long  const volatile, sfinae> /* final */ { static bool const value = true;                    };
          template <sfinaeptr_t sfinae>                        struct valueof<unsigned short const volatile, sfinae> /* final */ { static bool const value = true;                    };
          template <sfinaeptr_t sfinae>                        struct valueof<wchar_t        const volatile, sfinae> /* final */ { static bool const value = true;                    };
          #ifdef __cpp_char8_t // --> 201811L
            template <sfinaeptr_t sfinae> struct valueof<char8_t const volatile, sfinae> /* final */ { static bool const value = true; };
          #endif
          #ifdef __cpp_lib_byte // --> 201603L
            template <sfinaeptr_t sfinae> struct valueof<std::byte const volatile, sfinae> /* final */ { static bool const value = true; };
          #endif
          #ifdef __cpp_unicode_characters // --> 200704L
            template <sfinaeptr_t sfinae> struct valueof<char16_t const volatile, sfinae> /* final */ { static bool const value = true; };
            template <sfinaeptr_t sfinae> struct valueof<char32_t const volatile, sfinae> /* final */ { static bool const value = true; };
          #endif

        public:
          static bool const value = valueof<base const volatile>::value;
      };
    #endif

    // ...
    template <typename base>
    struct is_trivial /* final */ {
      #if __cplusplus >= 201103L or defined _MSVC_LANG // --> +201402L
        static bool const value = std::is_trivially_constructible<base>::value and std::is_trivially_destructible<base>::value;
      #elif defined __clang__ or defined __GNUC__ or defined _MSC_VER
        #ifdef __clang__
        # pragma clang diagnostic push
        # pragma clang diagnostic ignored "-Wdeprecated-builtins"
        #endif
        #undef __has_trivial_copy
        #undef __has_trivial_destructor

        static bool const value = __has_trivial_copy(base) and __has_trivial_destructor(base);

        #ifdef __clang__
        # pragma clang diagnostic pop
        #endif
      #else
        private:
          template <typename subbase, unsigned char = 0x00u>
          struct valueof /* final */  {
            static bool const value = is_bless_constructible<subbase>::value or is_function<subbase>::value;
          };

          template <unsigned char sfinae> struct valueof<double,      sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<float,       sfinae> /* final */ { static bool const value = true; };
          template <unsigned char sfinae> struct valueof<long double, sfinae> /* final */ { static bool const value = true; };

          template <typename subbase, unsigned char sfinae>
          struct valueof<subbase*, sfinae> /* final */ {
            static bool const value = true;
          };

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
  private:
    static digit const radix = 10u; // ->> Higher numeral systems are more computation and memory efficient; Must not be zero

  public:
    static bignum const EULER;
    static bignum const INFINITY;
    static bignum const ONE;
    static bignum const PI;
    static bignum const TAU;
    static bignum const ZERO;

    /* ... */
    // ... ->> Constant-optimized value-assignment (or value-initialization) intended for `array` `::dynamic` `elements`
    template <typename typeA, typename typeB, typename typeC>
    constexpr inline static typeB* assign(typeB address[], typeC const& value, bool const (*const)[
      is_blessed<typeA>::value and
      is_blessed<typeB>::value and
      sizeof(typeA) == sizeof(typeB)
    ] = NULL) /* noexcept(...) */ {
      *address = value;
      return address;
    }

    template <typename typeA, typename typeB, typename typeC>
    constexpr inline static typeB* assign(typeB address[], typeC const& value, bool const (*const)[
      is_bless_constructible<typeA>::value and not is_blessed<typeA>::value and
      is_blessed            <typeB>::value and
      is_bless_decomposable <typeC>::value and
      0u == sizeof(typeA) % sizeof(typeB)
    ] = NULL) /* noexcept(...) */ {
      std::size_t const width = CHAR_BIT * sizeof(typeB);                 // --> 8zu
      std::size_t const all   = (((1u << (width - 1u)) - 1u) << 1u) + 1u; // --> UCHAR_MAX

      // ... ->> Copy every `sizeof typeB` byte segment from `value` into `address` little-endian-wise
      if (
        #ifdef __cpp_lib_endian // --> 201907L
          std::endian::native == std::endian::little
        #elif defined __alpha or defined __alpha__ or defined __alpha_ev4__ or defined __alpha_ev5__ or defined __alpha_ev6__ or defined __amd64 or defined __amd64__ or defined __ARMEL__ or defined __bfin__ or defined __BFIN__ or defined __i386 or defined __i386__ or defined __i386__ or defined __i486__ or defined __i486__ or defined __i586__ or defined __i586__ or defined __i686__ or defined __i686__ or defined __I86__ or defined __I86__ or defined __ia64 or defined __ia64__ or defined __IA64__ or defined __INTEL__ or defined __itanium__ or defined __MIPSEL or defined __MIPSEL__ or defined __THUMBEL__ or defined __THW_INTEL__ or defined __x86_64 or defined __x86_64__ or defined _IA64 or defined _M_ALPHA or defined _M_AMD64 or defined _M_IA64 or defined _M_IX86 or defined _M_IX86 or defined _M_X64 or defined _MIPSEL or defined _X86_ or defined bfin or defined BFIN or defined i386 or ((defined __aarch64__ or defined __AARCH64EL__ or defined __arm64 or defined __arm__ or defined __ARM_ARCH or defined __ARM_ARCH_4__ or defined __ARM_ARCH_4T__ or defined __ARM_ARCH_5TE__ or defined __ARM_ARCH_5TEJ__ or defined __ARM_ARCH_6K__ or defined __ARM_ARCH_6KZ__ or defined __ARM_ARCH_6T2__ or defined __ARM_ARCH_6Z__ or defined __ARM_ARCH_7__ or defined __ARM_ARCH_7A__ or defined __ARM_ARCH_7M__ or defined __ARM_ARCH_7R__ or defined __TARGET_ARCH_ARM or defined __TARGET_ARCH_THUMB or defined __thumb__ or defined _M_ARM or defined _M_ARM64) and (defined __NT__ or defined __TOS_WIN__ or defined __WIN32__ or defined __WINDOWS__ or defined _WIN16 or defined _WIN32 or defined _WIN32_WCE or defined _WIN64 or defined WIN32))
          true
        #else
          false
        #endif
      ) {
        for (std::size_t index = sizeof(typeA); index--; )
        address[index] = (value >> (width * index)) & all;
      }

      // ... ->> Copy every `sizeof typeB` byte segment from `value` into `address` big-endian-wise
      else if (
        #ifdef __cpp_lib_endian // --> 201907L
          std::endian::native == std::endian::big
        #elif defined __370__ or defined __AARCH64EB__ or defined __ARMEB__ or defined __hppa or defined __HPPA11__ or defined __HPPA20__ or defined __hppa__ or defined __HPPA__ or defined __hpux or defined __m68k__ or defined __mc68000 or defined __mc68000__ or defined __mc68010 or defined __mc68010__ or defined __mc68020 or defined __mc68020__ or defined __mc68030 or defined __mc68030__ or defined __mc68040 or defined __mc68040__ or defined __mc68060 or defined __mc68060__ or defined __MIPSEB or defined __MIPSEB__ or defined __PA7100__ or defined __PA8000__ or defined __powerpc or defined __powerpc64__ or defined __powerpc__ or defined __POWERPC__ or defined __ppc or defined __ppc601__ or defined __ppc603__ or defined __ppc604__ or defined __ppc604__ or defined __ppc64__ or defined __PPC64__ or defined __ppc__ or defined __PPC__ or defined __PPCBROADWAY__ or defined __PPCGECKO__ or defined __RISC2_0__ or defined __s390__ or defined __s390x__ or defined __sparc or defined __sparc__ or defined __sparc_v8__ or defined __sparc_v9__ or defined __sparcv8 or defined __sparcv9 or defined __SYSC_ZARCH__ or defined __THUMBEB__ or defined __THW_370__ or defined __THW_RS6000 or defined _ARCH_601 or defined _ARCH_603 or defined _ARCH_PPC or defined _ARCH_PPC64 or defined _ARCH_PWR or defined _ARCH_PWR2 or defined _IBMR2 or defined _M_PPC or defined _MIPSEB defined _PA_RISC1_0 or defined _PA_RISC1_1 or defined _PA_RISC2_0 or defined _POWER or defined _XENON or defined M68000 or defined mc68000 or defined mc68010 or defined mc68020 or defined mc68030 or defined mc68040 or defined mc68060
          true
        #else
          false
        #endif
      ) {
        for (std::size_t index = sizeof(typeA); index--; )
        address[index] = (value >> (width * (sizeof(typeA) - index - 1u))) & all;
      }

      // ... --> std::memcpy(address, &value, sizeof value);
      else
        *(typeA*) address = value;

      // ...
      return address;
    }

    template <typename typeA, typename typeB, typename typeC>
    constexpr inline static typeB* assign(typeB address[], typeC const& value, bool const (*const)[not is_bless_constructible<typeA>::value] = NULL) /* noexcept(...) */ {
      *(typeA*) address = value;
      return address;
    }

    // ... ->> Prove existing valid object at `address`
    template <typename type>
    constexpr inline static type* bless(type* const address) /* noexcept */ {
      #ifdef __cpp_lib_launder // --> 201606L
        return std::launder(address);
      #else
        return address; // ->> Pretend :)
      #endif
    }

    // ... Decomposes `address` to a byte address
    constexpr inline static char*                         bytesof(char                         address[]) /* noexcept */ { return address; }
    constexpr inline static char const*                   bytesof(char const                   address[]) /* noexcept */ { return address; }
    constexpr inline static char const volatile*          bytesof(char const volatile          address[]) /* noexcept */ { return address; }
    constexpr inline static char       volatile*          bytesof(char       volatile          address[]) /* noexcept */ { return address; }
    constexpr inline static unsigned char*                bytesof(unsigned char                address[]) /* noexcept */ { return address; }
    constexpr inline static unsigned char const*          bytesof(unsigned char const          address[]) /* noexcept */ { return address; }
    constexpr inline static unsigned char const volatile* bytesof(unsigned char const volatile address[]) /* noexcept */ { return address; }
    constexpr inline static unsigned char       volatile* bytesof(unsigned char       volatile address[]) /* noexcept */ { return address; }

    inline static unsigned char*                bytesof(void*                const address) /* noexcept */ { return static_cast<unsigned char*>               (address); }
    inline static unsigned char const*          bytesof(void const*          const address) /* noexcept */ { return static_cast<unsigned char const*>         (address); }
    inline static unsigned char const volatile* bytesof(void const volatile* const address) /* noexcept */ { return static_cast<unsigned char const volatile*>(address); }
    inline static unsigned char       volatile* bytesof(void       volatile* const address) /* noexcept */ { return static_cast<unsigned char       volatile*>(address); }

    #ifdef __cpp_lib_byte // --> 201603L
      constexpr inline static std::byte*                bytesof(std::byte                address[]) /* noexcept */ { return address; }
      constexpr inline static std::byte const*          bytesof(std::byte const          address[]) /* noexcept */ { return address; }
      constexpr inline static std::byte const volatile* bytesof(std::byte const volatile address[]) /* noexcept */ { return address; }
      constexpr inline static std::byte       volatile* bytesof(std::byte       volatile address[]) /* noexcept */ { return address; }
    #endif

    // ... ->> Constant-optimized value-initialization intended for `array` `::dynamic` `elements`
    template <typename typeA, typename typeB, typename typeC>
    constexpr inline static typeB* instantiate(typeB* const address, typeC const& value, bool const (*const)[is_bless_constructible<typeA>::value] = NULL) /* noexcept(...) */ {
      return assign<typeA>(address, value);
    }

    template <typename typeA, typename typeB, typename typeC>
    inline static typeB* instantiate(typeB* const address, typeC const& value, bool const (*const)[not is_bless_constructible<typeA>::value] = NULL) /* noexcept(...) */ {
      return ::new (address) typeA(value);
    }

  /* ... */
  private:
    struct allocation {
      template <typename base>
      struct storage /* final */ {
        union { base *value, *allocations; };
        std::size_t capacity;                // ->> Maximum byte size of storage referenced by `value` (or `allocations`)
        union { std::size_t length, size; }; // ->> Number of existing `subbase` objects contiguously referenced by `allocations` (or `value`)
      };

      /* ... ->> Caches unused allocations */
      static struct value /* final */ : public storage<storage<void> > {
        static std::size_t const rate = 2u; // ->> Growth rate of `::capacity`; Must not be zero (and ideally not one, either)

        /* ... */
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
        template <typename> struct addressof  /* final */ {}; // ->> Flag for accessing the storage address of `elements`
        template <typename> struct iteratorof /* final */ {}; // ->> Flag for accessing the objects of `elements`
        template <typename> struct valueof    /* final */ {}; // ->> Flag for accessing the containers of `elements`

        // ... ->> Aliases `::automatic` `element` type
        template <typename subbase, bool = is_bless_constructible<subbase>::value or is_trivial<subbase>::value>
        struct automaticof /* final */ {
          typedef subbase type[1];
        };

        template <typename subbase>
        struct automaticof<subbase, true> /* final */ {
          typedef unsigned char type[sizeof(subbase)];
        };

        // ... ->> Aliases `::dynamic` `element` type
        template <typename subbase, bool = is_bless_constructible<subbase>::value>
        struct dynamicof /* final */ {
          typedef subbase type;
        };

        template <typename subbase>
        struct dynamicof<subbase, true> /* final */ {
          typedef unsigned char type; // --> unsigned char[sizeof subbase]
        };

        // ... ->> Aliases base `element` type
        template <typename subbase>
        struct elementof /* final */ {
          typedef typename baseof<subbase>::type type;
        };

        template <typename subbase>
        struct elementof<subbase&> /* final */ {
          typedef struct element /* final */ {
            subbase &value;
            constexpr inline operator subbase&() const /* noexcept */ { return this -> value; }
          } type;
        };

        #ifdef __cpp_rvalue_references // --> 200610L
          template <typename subbase>
          struct elementof<subbase&&> /* final */ {
            typedef struct element /* final */ {
              subbase &&value;
              constexpr inline operator subbase&&() const /* noexcept */ { return static_cast<subbase&&>(this -> value); }
            } type;
          };
        #endif

      protected:
        using allocation::storage;

      public:
        typedef typename elementof<base>::type element;

        typedef typename automaticof<element>::type automatic;
        typedef typename dynamicof  <element>::type dynamic;

      /* ... */
      #if __cplusplus >= 201103L or defined _MSVC_LANG // --> +201402L
        public:
          struct elements /* final */ {
            private:
              template <bool boolean, bool... booleans> struct boolean_and          final { static bool const value = boolean and boolean_and<booleans...>::value; };
              template <bool boolean>                   struct boolean_and<boolean> final { static bool const value = boolean; };

              // ...
              template <std::size_t...>                            struct index_sequence                    final { typedef index_sequence<>                                             type; };
              template <std::size_t index, std::size_t... indexes> struct index_sequence<index, indexes...> final { typedef typename index_sequence<index - 1u, index, indexes...>::type type; };
              template <std::size_t... indexes>                    struct index_sequence<0u,    indexes...> final { typedef index_sequence<0u, indexes...>                               type; };

              /* ... */
              struct automatic final { alignas(array::element) array::automatic automatic; } automatic   [prelength];
              struct element   final { array::element                          *value;     } subautomatic[prelength];
              storage<array::dynamic>                                                        dynamic;

              /* ... */
              template <std::size_t... indexesA, std::size_t... indexesB, typename... types>
              constexpr elements(index_sequence<indexesA...> const, index_sequence<0u, indexesB...> const, bool const (*const)[is_trivial<typename array::element>::value], types&&... values) noexcept(boolean_and<true, noexcept(array::element(static_cast<types&&>(values)))...>::value) :
                automatic   {static_cast<types&&>(values)...},
                subautomatic{this -> automatic[indexesA].automatic..., (static_cast<void>(indexesB), static_cast<typename array::element*>(NULL))...},
                dynamic     {NULL, 0u, 0u}
              {}

              template <std::size_t... indexesA, std::size_t... indexesB, typename... types>
              constexpr elements(index_sequence<indexesA...> const, index_sequence<0u, indexesB...> const, bool const (*const)[not is_trivial<typename array::element>::value], types&&... values) noexcept(boolean_and<true, noexcept(array::element(static_cast<types&&>(values)))...>::value) :
                automatic   {},
                subautomatic{instantiate<typename array::element>(this -> automatic[indexesA].automatic, static_cast<types&&>(values))..., (static_cast<void>(indexesB), static_cast<typename array::element*>(NULL))...},
                dynamic     {NULL, 0u, 0u}
              {}

            public:
              template <typename... types>
              constexpr elements(types&&... values) noexcept(boolean_and<true, noexcept(array::element(static_cast<types&&>(values)))...>::value) :
                elements::elements(
                  index_sequence<sizeof...(types)>::type{},
                  index_sequence<(prelength >= sizeof...(types)) ? (prelength - sizeof...(types)) + 1u : 0u>::type{},
                  static_cast<bool const (*)[true]>(NULL),
                  static_cast<types&&>(values)...
                )
              { static_assert(prelength >= sizeof...(values), "Too many elements to automatically initialize `array` with"); }
          } elements;

        private:
          typedef typename elements::automatic *automatic_address;  // ->> Pointer inter-convertible with `array::automatic`
          typedef typename elements::element   *automatic_iterator; // ->> Pointer inter-convertible with `array::element*`
          typedef dynamic                      *dynamic_address, *dynamic_iterator;

          /* ... */
          constexpr friend elements::automatic (&operator ->*(array const* const array, addressof <automatic> const) noexcept)[prelength] { return array -> elements.automatic; }
          constexpr friend elements::element   (&operator ->*(array const* const array, iteratorof<automatic> const) noexcept)[prelength] { return array -> elements.subautomatic; }
          constexpr friend storage<dynamic>&     operator ->*(array const* const array, valueof   <dynamic>   const) noexcept             { return const_cast<storage<dynamic>&>(array -> elements.dynamic); }
      #else
        private:
          union elements {
            private:
              union {
                /* alignas(element) */ array::automatic automatic;
                storage<array::dynamic>                 dynamic;
              };

              array::element *value;

            public:
              inline elements() throw() : automatic(), value(NULL) {}

              template <typename type> inline elements(type&       value, bool const (*const)[    is_trivial<type>::value] = NULL) throw()          : automatic(), value(instantiate<typename array::element>(this -> automatic, value)) {}
              template <typename type> inline elements(type const& value, bool const (*const)[    is_trivial<type>::value] = NULL) throw()          : automatic(), value(instantiate<typename array::element>(this -> automatic, value)) {}
              template <typename type> inline elements(type&       value, bool const (*const)[not is_trivial<type>::value] = NULL) /* throw(...) */ : automatic(), value(instantiate<typename array::element>(this -> automatic, value)) {}
              template <typename type> inline elements(type const& value, bool const (*const)[not is_trivial<type>::value] = NULL) /* throw(...) */ : automatic(), value(instantiate<typename array::element>(this -> automatic, value)) {}
          };

        public:
          elements elements[prelength];

        /* ... */
        private:
          typedef union elements *automatic_address, *automatic_iterator;
          typedef dynamic        *dynamic_address,   *dynamic_iterator;

          /* ... */
          friend inline union elements  (&operator ->*(array const* const array, addressof <automatic> const) throw())[prelength] { return array -> elements; }
          friend inline union elements  (&operator ->*(array const* const array, iteratorof<automatic> const) throw())[prelength] { return array -> elements; }
          friend inline storage<dynamic>& operator ->*(array const* const array, valueof   <dynamic>   const) throw()             { return const_cast<storage<dynamic>&>(array -> elements[array -> precapacity].dynamic); }
      #endif
      private:
        constexpr inline friend dynamic_address  operator ->*(array const* const array, addressof <dynamic>   const)  /* noexcept */ { return array ->* valueof<dynamic>().value; }
        constexpr inline friend dynamic_iterator operator ->*(array const* const array, iteratorof<dynamic>   const)  /* noexcept */ { return array ->* valueof<dynamic>().value; }
        constexpr inline friend void             operator ->*(array const* const,       valueof   <automatic> const); /* noexcept */

      /* ... */
      public:
        // ... --- WARN (Lapys) ->> If destructor is not defined, then `::reserve(0u)` should be called at least once immediately before destruction
        #if defined _MSVC_LANG
        # if _MSVC_LANG >= 202002L
            constexpr ~array() noexcept(noexcept(this -> reserve(0u))) { (void) this -> reserve(0u); }
        # endif
        #elif __cplusplus >= 202002L
          constexpr ~array() noexcept(noexcept(this -> reserve(0u))) { (void) this -> reserve(0u); }
        #elif not defined __cpp_constexpr // --> 200704L
          inline ~array() /* noexcept(...) */ { (void) this -> reserve(0u); }
        #endif

      /* ... */
      protected:
        constexpr inline element* at(std::size_t const index) const /* noexcept */ {
          return index < this -> precapacity ? this ->* iteratorof<automatic>()[index].value : index - this -> precapacity < this ->* valueof<dynamic>().capacity / sizeof(element) ? bless(this ->* iteratorof<dynamic>() + (index - this -> precapacity)) : NULL;
        }

        // ... --- TODO (Lapys)
        static? destruct();

        // ...
        template <typename type>
        constexpr inline element* set(std::size_t const index, type& value) /* noexcept */ {
          if (index < this -> precapacity) {
            this ->* iteratorof<automatic>()[index].value = instantiate<element>(this ->* addressof<automatic>()[index].automatic, value);
            return this ->* iteratorof<automatic>()[index].value;
          }

          if (index - this -> precapacity < this ->* valueof<dynamic>().capacity / sizeof(element))
          return instantiate<element>(this ->* iteratorof<dynamic>() + (index - this -> precapacity), value);

          return NULL;
        }

        template <typename type>
        constexpr inline element* set(std::size_t const index, type const& value) /* noexcept */ {
          if (index < this -> precapacity) {
            this ->* iteratorof<automatic>()[index].value = instantiate<element>(this ->* addressof<automatic>()[index].automatic, value);
            return this ->* iteratorof<automatic>()[index].value;
          }

          if (index - this -> precapacity < this ->* valueof<dynamic>().capacity / sizeof(element))
          return instantiate<element>(this ->* iteratorof<dynamic>() + (index - this -> precapacity), value);

          return NULL;
        }

      public:
        template <typename type>
        constexpr inline bool add(type& value) /* noexcept(...) */ {
          std::size_t const length = this -> lengthof();

          // ...
          if (length >= this -> capacityof()) {
            if (not this -> reserve(length + 1u))
            return false;
          }

          (void) instantiate<element>(this -> at(length), value);
          this -> resize(length + 1u);

          // ...
          return true;
        }

        template <typename type>
        constexpr inline bool add(type const& value) /* noexcept(...) */ {
          std::size_t const length = this -> lengthof();

          // ...
          if (length >= this -> capacityof()) {
            if (not this -> reserve(length + 1u))
            return false;
          }

          (void) instantiate<element>(this -> at(length), value);
          this -> resize(length + 1u);

          // ...
          return true;
        }

        // ...
        constexpr inline std::size_t capacityof() const /* noexcept */ {
          return this -> precapacity + (this ->* valueof<dynamicof>().capacity / sizeof(element));
        }

        // ...
        constexpr inline void empty() /* noexcept(...) */ {
          if (this -> lengthof())
            (void) this -> reserve(0u);

          this -> resize(0u);
        }
    };
};

struct bignum /* final */ {
  private:
    template <typename base, std::size_t prelength>
    struct array : public allocation /* --> using allocation::storage */ {
      /* ... */
      public:
        // ...
        constexpr inline std::size_t lengthof() const /* noexcept */ {
          std::size_t length = this -> elements[this -> precapacity].dynamic.length;

          // ... ->> Not simply `::dynamic.length + ::precapacity`
          for (struct elements const *iterator = this -> elements + this -> precapacity; iterator != this -> elements; ) {
            if (NULL != (--iterator) -> value)
            return length + (iterator - this -> elements);
          }

          return length;
        }

        // ...
        constexpr inline void pop() /* noexcept(...) */ {
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
                allocated:;
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
        constexpr inline std::size_t resize(std::size_t const count) /* noexcept */ {
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

          // ...
          return count;
        }

        // ...
        template <typename type, std::size_t capacity>
        array& operator =(array<type, capacity> const& array) /* noexcept(...) */ {
          if (reinterpret_cast<unsigned char const*>(this) != &reinterpret_cast<unsigned char const&>(array)) {
            storage<element> &dynamic = this -> elements[this -> precapacity].dynamic;
            std::size_t const length  = array.lengthof();

            // ... ->> Copy-assign/ value-initialize all elements using `array`
            if (length <= this -> capacityof() or this -> reserve(length)) {
              for (std::size_t index = 0u, subindex = this -> lengthof(); index != length; ++index)
                index < subindex ? (void) *(this -> at(index)) = *array.at(index) : this -> set(index, *array.at(index));

              this -> resize(length);
            }
          }

          return *this;
        }

        constexpr inline base& operator [](std::size_t const index) const /* noexcept */ {
          return *(this -> at(index));
        }
    };

    // ...
    template <std::size_t precapacity>
    struct biguint /* final */ : public array<digit, precapacity> {
      constexpr inline biguint(uintmax_t integer = 0u) /* noexcept */ :
        array<digit, precapacity>::array()
      {
        if (0u == integer)
        return;

        if (radix != 1u) {
          std::size_t rank = 0u == integer;

          // ...
          for (uintmax_t value = integer; value; value /= radix)
          ++rank;

          if (this -> reserve(rank)) {
            for (this -> resize(rank); rank--; integer /= radix)
            this -> set(rank, integer % radix);
          }
        }

        else if (this -> reserve(integer)) {
          this -> resize(integer);

          while (integer--)
            this -> set(integer, 0u);
        }
      }

      // ...
      template <std::size_t capacity>
      constexpr inline biguint(biguint<capacity> const& integer) /* noexcept */ :
        array<digit, precapacity>::array()
      { (void) this -> template array<digit, precapacity>::operator =(integer); }

      /* ... */
      template <std::size_t capacity>
      bool add(biguint<capacity> const& integer) /* noexcept */ {
        bool        carry   = false;
        std::size_t rank    = this -> lengthof();
        std::size_t subrank = integer.lengthof();

        // ...
        if (reinterpret_cast<unsigned char const*>(this) == &reinterpret_cast<unsigned char const&>(integer))
          return this -> doubly();

        if (rank < subrank) {
          std::size_t index = subrank;

          // ...
          if (not this -> shift(subrank))
            return false;

          while (rank)  this -> operator [](--index) = this -> operator [](--rank);
          while (index) this -> operator [](--index) = 0u;

          rank = subrank;
        }

        while (rank) {
          digit const subdigit = subrank ? integer[--subrank] : 0u;

          // ...
          if (carry + this -> operator [](--rank) > radix - subdigit - 1u) {
            this -> operator [](rank) -= radix - subdigit - carry;
            carry                      = true;
          }

          else {
            this -> operator [](rank) += subdigit + carry;
            carry                      = false;
          }
        }

        if (carry) {
          if (not this -> shift(1u))
            return false;

          for (rank = this -> lengthof(); --rank; )
            this -> operator [](rank - 0u) = this -> operator [](rank - 1u);

          this -> operator [](0u) = 1u;
        }

        // ...
        return true;
      }

      // ...
      constexpr inline signed char compare(biguint const& integer) const /* noexcept */ {
        return this -> greater(integer) ? +1 : this -> lesser(integer) ? -1 : 0;
      }

      // ...
      constexpr inline void decrement() /* noexcept */ {
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

      // ... --- TODO (Lapys)
      void divide() /* noexcept */;

      // ...
      bool doubly() /* noexcept */ {
        std::size_t rank = this -> lengthof();

        // ...
        if (radix != 1u) {
          bool carry = false;

          // ...
          while (rank) {
            digit const digit = this -> operator [](--rank);

            // ...
            if (carry + digit > radix - digit - 1u) {
              this -> operator [](rank) -= radix - digit - carry;
              carry                      = true;
            }

            else {
              this -> operator [](rank) += digit + carry;
              carry                      = false;
            }
          }

          if (carry) {
            if (not this -> shift(1u))
              return false;

            for (rank = this -> lengthof(); --rank; )
              this -> operator [](rank - 0u) = this -> operator [](rank - 1u);

            this -> operator [](0u) = 1u;
          }
        }

        else {
          if (not this -> reserve(rank * 2u))
            return false;

          this -> resize(rank * 2u);

          for (std::size_t count = rank; count--; )
            this -> set(count + rank, 0u);
        }
      }

      // ...
      constexpr inline bool equals(biguint const& integer) const /* noexcept */ {
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

      // ... --- TODO (Lapys)
      bool exponentiate() /* noexcept */;

      // ...
      constexpr inline bool greater(biguint const& integer) const /* noexcept */ {
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
      constexpr inline bool increment() /* noexcept */ {
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
      constexpr inline bool lesser(biguint const& integer) const /* noexcept */ {
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

      // ... --- TODO (Lapys)
      bool modulo() /* noexcept */;

      // ...
      template <std::size_t capacity>
      bool multiply(biguint<capacity> const& integer) /* noexcept */ {
        std::size_t rank    = this -> lengthof();
        std::size_t subrank = integer.lengthof();

        // ... ->> Commutate `integer` and `this` to simplify the algorithm
        if (rank < subrank) {
          biguint<capacity> value = 0u;

          // ...
          if (not value.reserve(subrank))
            return false;

          value.resize(subrank);

          while (subrank--)
            value.set(subrank, integer.at(subrank));

          if (not value.multiply(*this))
            return false;

          subrank = value.lengthof();

          if (not this -> reserve(subrank))
            return false;

          this -> resize(subrank);

          while (subrank--)
            this -> set(subrank, integer.at(subrank));
        }

        // ...
        // while (subrank) {
        //   std::size_t length     = rank;
        //   digit const multiplier = integer[--subrank];

        //   // ...
        //   while (length)
        //     UINTMAX_MAX * UINTMAX_MAX
        //     this -> operator [](--length)
        // }

        return true;
      }

      // ...
      inline bool shift(std::size_t const count) /* noexcept */ {
        std::size_t const rank = this -> lengthof();

        // ...
        if (not this -> reserve(count + rank))
          return false;

        this -> resize(count + rank);

        for (std::size_t index = count + rank; index-- != rank; )
          this -> set(index, 0u);

        return true;
      }

      // ...
      void subtract() /* noexcept */;

      // ...
      constexpr inline void unshift(std::size_t const count) /* noexcept */ {
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
      constexpr inline void zero() /* noexcept */ {
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
      constexpr inline operation(bool (&function)(bignum&, state[]), std::size_t const arity) /* noexcept */ :
        function(function),
        states  ()
      {
        if (not this -> states.reserve(arity))
        return;

        for (std::size_t index = this -> states.resize(arity); index; )
        this -> states.set(--index, 0u);
      }
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
    constexpr inline static long double truncate(long double const number) /* noexcept */ {
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
        // atan2f(1, 1) * 4
        // this -> denominator = 78256779u;
        // this -> numerator   = 245850922u;

        return;
      }

      // ...
      if (reinterpret_cast<unsigned char*>(this) == &reinterpret_cast<unsigned char const&>(bignum::TAU)) {
        // PI * 2
        // this -> denominator = 78256779u;
        // this -> numerator   = 491701844u;

        return;
      }

      // ...
      if (reinterpret_cast<unsigned char*>(this) == &reinterpret_cast<unsigned char const&>(bignum::ZERO))
      return;
    }

    // ...
    constexpr inline bignum(long double number) /* noexcept */ :
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
    constexpr inline bignum(bignum const& number) /* noexcept */ :
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
