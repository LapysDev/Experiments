#include <ciso646>
#include <climits>
#include <cstddef>
#include <stdint.h>

/* ... */
#include <cstdio>
#include <typeinfo>
#define private public

template <std::size_t width>
struct float_t /* final */ {
  // CITE (Lapys) -> https://en.wikipedia.org/wiki/Single-precision_floating-point_format
  static std::size_t const radix = 2u;

  uintmax_t exponent   : 8;
  uintmax_t mantissa   : 23;
  bool      signedness : 1;
};

template <std::size_t width>
struct uint_t /* final */ {
  private:
    // ... --> widthinfo<…> ->> Diagnostics information on `width`
    template <std::size_t subwidth, unsigned char =
      // ... ->> Determine what leading "byte segment" type to use for `subwidth`
      #if __cplusplus >= 201103L or defined _MSVC_LANG
        (subwidth >= CHAR_BIT * sizeof(unsigned long long)) ? 0x5u :
      #endif
      (subwidth >= CHAR_BIT * sizeof(unsigned long))  ? 0x4u :
      (subwidth >= CHAR_BIT * sizeof(unsigned int))   ? 0x3u :
      (subwidth >= CHAR_BIT * sizeof(unsigned short)) ? 0x2u :
      (subwidth >= CHAR_BIT * sizeof(unsigned char))  ? 0x1u :
      0x1u
    >
    struct widthinfo /* final */ {
      // ... ->> Represents a linear contiguous type able to completely store a `uint_t<…>`
      template <typename base>
      struct flatten /* final */ {
        static std::size_t const length = (subwidth / (CHAR_BIT * sizeof(base))) + (subwidth % (CHAR_BIT * sizeof(base)) ? 1u : 0u) + (0u == subwidth);
      };

      // ... ->> Determines how much `subwidth` remains after accounting for the leading "byte segment" type
      static std::size_t const next =
        #if __cplusplus >= 201103L or defined _MSVC_LANG
          subwidth >= CHAR_BIT * sizeof(unsigned long long) ? subwidth - (CHAR_BIT * sizeof(unsigned long long)) :
        #endif
        subwidth >= CHAR_BIT * sizeof(unsigned long)  ? subwidth - (CHAR_BIT * sizeof(unsigned long))  :
        subwidth >= CHAR_BIT * sizeof(unsigned int)   ? subwidth - (CHAR_BIT * sizeof(unsigned int))   :
        subwidth >= CHAR_BIT * sizeof(unsigned short) ? subwidth - (CHAR_BIT * sizeof(unsigned short)) :
        subwidth >= CHAR_BIT * sizeof(unsigned char)  ? subwidth - (CHAR_BIT * sizeof(unsigned char))  :
      0u;

      // ->> `widthinfo<…>::byte`    connotes the                       "byte segment" type
      // ->> `widthinfo<…>::trivial` connotes the maximum representable "byte segment" type
    };

    template <std::size_t subwidth> struct widthinfo<subwidth, 0x1u> : public widthinfo<subwidth, 0x0u> { typedef unsigned char  byte; typedef unsigned short trivial; };
    template <std::size_t subwidth> struct widthinfo<subwidth, 0x2u> : public widthinfo<subwidth, 0x0u> { typedef unsigned short byte; typedef unsigned int   trivial; };
    template <std::size_t subwidth> struct widthinfo<subwidth, 0x3u> : public widthinfo<subwidth, 0x0u> { typedef unsigned int   byte; typedef unsigned long  trivial; };

    #if __cplusplus < 201103L or not defined _MSVC_LANG
      template <std::size_t subwidth>
      struct widthinfo<subwidth, 0x4u> : public widthinfo<subwidth, 0x0u> {
        typedef unsigned long byte;
        typedef uintmax_t     trivial;
      };
    #else
      template <std::size_t subwidth>
      struct widthinfo<subwidth, 0x4u> : public widthinfo<subwidth, 0x0u> {
        typedef unsigned long      byte;
        typedef unsigned long long trivial;
      };

      template <std::size_t subwidth>
      struct widthinfo<subwidth, 0x5u> : public widthinfo<subwidth, 0x0u> {
        typedef unsigned long long byte;
        typedef uintmax_t          trivial;
      };
    #endif

    // ... --> value_t<…> ->> Little-endian sequenced `uint_t` value representation
    template <std::size_t subwidth, std::size_t = widthinfo<subwidth>::next>
    struct value_t /* : public value_t<widthinfo<subwidth>::next> */ {
      static std::size_t const           length = CHAR_BIT * sizeof(typename widthinfo<subwidth>::byte);
      typename widthinfo<subwidth>::byte value;
      value_t<widthinfo<subwidth>::next> _; // ->> Allow accurate `reinterpret_cast` evaluation for little-endian environments

      /* constexpr */ inline value_t<widthinfo<subwidth>::next>& next() const /* noexcept */ {
        return const_cast<value_t<widthinfo<subwidth>::next>&>(this -> _);
      }
    };

    template <std::size_t subwidth>
    struct value_t<subwidth, 0u> : public value_t<0u> {
      static std::size_t const           length = subwidth;
      typename widthinfo<subwidth>::byte value  : subwidth;

      /* constexpr */ inline value_t<0u>& next() const /* noexcept */ {
        return const_cast<value_t<0u>&>(static_cast<value_t<0u> const&>(*this));
      }
    };

    template <>
    struct value_t<0u, 0u> /* final */ {
      static std::size_t const length = 0u;

      /* constexpr */ inline value_t<0u>& next() const /* noexcept */ {
        return const_cast<value_t<0u>&>(*this);
      }
    };

    // ... --> cast<T> ->> Convert trivial C++ integer types to `base`
    template <typename base>
    struct cast /* final */ {
      base const value;

      /* constexpr */ inline cast(base const value) /* noexcept */ : value(value) {}
      /* constexpr */ inline operator base() const /* noexcept */ { return this -> value; }
    };

    template <std::size_t subwidth>
    struct cast<uint_t<subwidth> > /* final */ {
      uint_t<subwidth> value;

      inline cast(uintmax_t const value) /* noexcept */ : value() { this -> value.operator =(value); }
      /* constexpr */ inline operator uint_t<subwidth>() const /* noexcept */ { return this -> value; }
    };

    /* ... --> assign(…, …) */
    /* constexpr */ inline static void assign(value_t<0u>&, uintmax_t const) /* noexcept */ { /* Do nothing… */ }

    template <std::size_t subwidth>
    inline static void assign(value_t<subwidth>& integer, uintmax_t value) /* noexcept */ {
      for (uintmax_t const maximum = (((static_cast<uintmax_t>(1u) << (width - 1u)) - 1u) << 1u) + 1u; value > maximum; --value)
        value -= maximum; // ->> Truncate `value` due to possible overflow (faster algorithm unknown)

      integer.value = value & ((((static_cast<uintmax_t>(1u) << (integer.length - 1u)) - 1u) << 1u) + 1u);
      uint_t::assign(integer.next(), value >> integer.length);
    }

    // ... --- TODO (Lapys)
    inline static void diagnose(value_t<0u> const&) {}

    template <std::size_t subwidth>
    inline static void diagnose(value_t<subwidth> const& integer) {
      char string[value_t<subwidth>::length];
      char *iterator = string + (sizeof string / sizeof(char));

      // ...
      for (uintmax_t value = integer.value; value; value >>= 1u)
        *--iterator = value & 1u ? '1' : '0';

      while (iterator != string)
        *--iterator = '0';

      std::printf("{%zu} %0.*s" " ", static_cast<std::size_t>(integer.value), static_cast<int>(sizeof string / sizeof(char)), string);
      uint_t::diagnose(integer.next());
    }

    // ... --> flatten(…, …) ->> Little-endian sequenced
    /* constexpr */ inline static void flatten(value_t<0u> const&, uintmax_t[], std::size_t, std::size_t) /* noexcept */ {
      return 0u;
    }

    /* constexpr */ inline static void flatten(value_t<width> const& integer, uintmax_t (&value)[widthinfo<width>::flatten<uintmax_t>::length]) /* noexcept */ {
      for (uintmax_t *iterator = value + (sizeof value / sizeof(uintmax_t)); iterator != value; )
      *--iterator = 0u;

      uint_t::flatten(integer, value, integer.length, CHAR_BIT * sizeof(uintmax_t));
    }

    template <std::size_t subwidth>
    /* constexpr */ inline static void flatten(value_t<subwidth> const& integer, uintmax_t value[], std::size_t integerLength, std::size_t valueLength) /* noexcept */ {
      if (integerLength > valueLength) {
        integerLength -= valueLength;
        *value       <<= valueLength;
        *value        |= integer.value >> integerLength;

        uint_t::flatten(integer, value + 1, integerLength, CHAR_BIT * sizeof(uintmax_t)) + 1u;
      }

      else {
        *value     <<= integerLength;
        *value      |= integer.value & ((((1u << (integerLength - 1u)) - 1u) << 1u) + 1u);
        valueLength -= integerLength;

        uint_t::flatten(integer.next(), value + (0u == valueLength), integer.next().length, 0u == valueLength ? CHAR_BIT * sizeof(uintmax_t) : valueLength) + (0u == valueLength);
      }
    }

    // ... --> maximize(…)
    /* constexpr */ inline static void maximize(value_t<0u>&) /* noexcept */ { /* Do nothing… */ }

    template <std::size_t subwidth>
    inline static void maximize(value_t<subwidth>& integer) /* noexcept */ {
      integer.value = (((static_cast<uintmax_t>(1u) << (integer.length - 1u)) - 1u) << 1u) + 1u;
      uint_t::maximize(integer.next());
    }

    // ... --> promote(…)
    template <typename type>
    /* constexpr */ inline static type promote(value_t<0u>&, std::size_t const = 0u) /* noexcept */ {
      return cast<type>(0u);
    }

    template <typename type, std::size_t subwidth>
    /* constexpr */ inline static type promote(value_t<subwidth>& integer, std::size_t const length = 0u) /* noexcept */ {
      return uint_t::promote<type>(integer.next(), integer.length + length) | (cast<type>(integer.value) << length);
    }

    // ... --> shift(…, …)
    /* constexpr */ inline static void shift(value_t<width>& integer, uintmax_t shift) /* noexcept */ {
      std::size_t const length = widthinfo<width>::flatten<uintmax_t>::length;
      uintmax_t         shifted[length];

      // ...
      if (shift >= width or shift >= CHAR_BIT * length * sizeof(uintmax_t))
        uint_t::zero(integer);

      else {
        uint_t::flatten(integer, shifted);
        // (void) shifted; print this really

        for (uintmax_t *iteratorA = shifted, iteratorB = shifted + (shift / CHAR_BIT * sizeof(uintmax_t)); ; ++iteratorA, ++iteratorB) {
          if (iteratorB == shifted + length) {
            while (iteratorA != shifted + length)
            *(iteratorA++) = 0u;

            break;
          }

          *iteratorA = *iteratorB;
        }

        shift %= CHAR_BIT * sizeof(uintmax_t);

        for (uintmax_t *iterator = shifted; ; ++iterator) {
          *iterator <<= shift;

          if (iterator == shifted + (length - 1u)) break;
          iterator[0] |= iterator[1] >> ((CHAR_BIT * sizeof(uintmax_t)) - shift);
        }

        (void) shifted;
      }
    }

    // ... --> zero(…)
    /* constexpr */ inline static void zero(value_t<0u>&) /* noexcept */ { /* Do nothing… */ }

    template <std::size_t subwidth>
    /* constexpr */ inline static void zero(value_t<subwidth>& integer) /* noexcept */ {
      integer.value = 0u;
      uint_t::zero(integer.next());
    }

    /* ... */
    #define uint_t uint_t_1u(__LINE__)
    # define uint_t_1u(hash) uint_t_2u(hash)
    # define uint_t_2u(hash)                                                                                              \
      public : value_t<width> value ## hash; /* ->> Obfuscate the public member for aggregate-/ default-initialization */ \
      private: /* constexpr */ inline value_t<width>& valueof() const /* noexcept */ { return const_cast<value_t<width>&>(this -> value ## hash); }

      uint_t;
    #undef uint_t
    # undef uint_t_1u
    # undef uint_t_2u

  public: // ->> No non-trivial constructor for `union` support pre-C++11
    // ...
    inline uint_t<width>& operator =(uintmax_t const value) /* noexcept */ {
      uint_t::assign(this -> valueof(), value);
      return *this;
    }

    // ...
    /* constexpr */ inline operator typename widthinfo<width>::trivial() const /* noexcept */ {
      return uint_t::promote<typename widthinfo<width>::trivial>(this -> valueof());
    }

    template <std::size_t subwidth>
    /* constexpr */ inline operator uint_t<subwidth>() const /* noexcept */ {
      return uint_t::promote<uint_t<subwidth> >(this -> valueof());
    }
};
  template <std::size_t width>
  /* constexpr */ inline uint_t<width> operator +(uint_t<width> const& integer) /* noexcept */ {
    return integer;
  }

  // template <std::size_t width>
  // /* constexpr */ inline uint_t<width> operator -(uint_t<width>) /* noexcept */ {
  //   uint_t<width> maximum = {};

  //   uint_t<width>::maximize(maximum.valueof());
  //   return maximum - *this;
  // }

  // template <std::size_t widthA, std::size_t widthB>
  // inline uint_t<(widthA > widthB ? widthA : widthB)> operator -(uint_t<widthA> const& integerA, uint_t<widthB> const& integerB) {
  //   uint_t<(widthA > widthB ? widthA : widthB)>::subtract(integerA.valueof(), integerB.valueof());
  // }

  // template <std::size_t width>
  // /* constexpr */ inline uint_t<width> operator <<(uint_t<width> integerA, uintmax_t const integerB) /* noexcept */ {
  //   uint_t<width>::shift(integerA.valueof(), integerB);
  //   return integerA;
  // }

  // template <std::size_t widthA, std::size_t widthB>
  // /* constexpr */ inline uint_t<(widthA > widthB ? widthA : widthB)> operator <<(uint_t<widthA> const& integerA, uint_t<widthB> const& integerB) /* noexcept */ {
  //   integerA.valueof()
  // }

/* Main */
int main(int, char*[]) /* noexcept */ {
  std::size_t const width = 16u + 8u + 1u;
  union { uint_t<width> integer; };

  // ...
  integer = 1u;
  std::printf("[integer]: %zu" "\r\n", static_cast<std::size_t>(integer));
  uint_t<width>::shift(integer.valueof(), 1u);
  std::printf("[integer]: %zu" "\r\n", static_cast<std::size_t>(integer));

  // integer = 16777216u | 23412u; // 16800628u
  // std::size_t const length = uint_t<width>::flatten(integer.valueof(), bytes);
  //
  // std::printf("[integer]: (%zu)" " ", static_cast<std::size_t>(integer)); uint_t<width>::diagnose(integer.valueof()); std::printf("\r\n");
  // std::printf("[bytes]: ");
  //   for (uintmax_t *iterator = bytes, *const end = bytes + length; iterator != end; ++iterator) {
  //     char string[CHAR_BIT * sizeof(uintmax_t)];
  //     char *subiterator = string + (sizeof string / sizeof(char));
  //
  //     for (uintmax_t value = *iterator; value; value >>= 1u)
  //       *--subiterator = value & 1u ? '1' : '0';
  //
  //     while (subiterator != string)
  //       *--subiterator = '0';
  //
  //     std::printf("(%zu:%u)" " " "%0.*s" " ", static_cast<std::size_t>(*iterator), static_cast<unsigned>(length), static_cast<int>(sizeof string / sizeof(char)), string);
  //   }
  // std::printf("\r\n");

  // std::printf("[integer]: %lu" "\r\n", static_cast<unsigned long>(static_cast<uint_t<8u> >(integer)));
}
