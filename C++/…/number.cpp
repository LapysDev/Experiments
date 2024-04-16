#include <ciso646>
#include <climits>
#include <cstddef>
#include <stdint.h>

/* ... */
#include <cstdio>
#include <typeinfo>
#define private public

/* constexpr */ inline static uintmax_t widthmaxof(unsigned char const width) /* noexcept */ {
  return width ? (((static_cast<uintmax_t>(1u) << (width - 1u)) - 1u) << 1u) + 1u : 0u;
}

// ...
struct bigfloat;
struct bigint;
struct biguint;

struct endian /* final */ {
  enum type /* : bool */ {
    big,
    little
  };
};

template <std::size_t width, enum endian::type endianness = endian::little>
struct uintwidth /* final */ {
  private:
    // ... --> widthinfo<…> ->> Diagnostics information on `width`
    template <std::size_t subwidth, unsigned char =
      // ... ->> Determine what leading "byte segment" type to use for `subwidth`
      #if defined __clang__
        (subwidth >= CHAR_BIT * sizeof(__uint128_t)) ? 0x8u :
      #elif defined __GNUC__ ? defined __SIZEOF_INT128__ : false
      # pragma GCC diagnostic push
      # pragma GCC diagnostic ignored "-Wpedantic"
        (subwidth >= CHAR_BIT * sizeof(unsigned __int128)) ? 0x8u :
      # pragma GCC diagnostic pop
      #elif defined __cpp_lib_ranges // --> 201911L
      # if __cplusplus >= 201103L or defined _MSVC_LANG
          (subwidth >= CHAR_BIT * sizeof(std::ranges::range_difference_t<std::ranges::iota_view<unsigned long long, unsigned long long> >)) ? 0x8u :
      # else
          (subwidth >= CHAR_BIT * sizeof(std::ranges::range_difference_t<std::ranges::iota_view<unsigned long, unsigned long> >)) ? 0x8u :
      # endif
      #endif
      (subwidth >= CHAR_BIT * sizeof(std::size_t)) ? 0x7u :
      (subwidth >= CHAR_BIT * sizeof(uintmax_t))   ? 0x6u :
      #if __cplusplus >= 201103L or defined _MSVC_LANG
        (subwidth >= CHAR_BIT * sizeof(unsigned long long)) ? 0x5u :
      #endif
      (subwidth >= CHAR_BIT * sizeof(unsigned long))  ? 0x4u :
      (subwidth >= CHAR_BIT * sizeof(unsigned int))   ? 0x3u :
      (subwidth >= CHAR_BIT * sizeof(unsigned short)) ? 0x2u :
      (subwidth >= CHAR_BIT * sizeof(unsigned char))  ? 0x1u :
      0x1u
    >
    struct widthinfo {
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
    template <std::size_t subwidth> struct widthinfo<subwidth, 0x6u> : public widthinfo<subwidth, 0x0u> { typedef uintmax_t      byte; typedef uintmax_t      trivial; };
    template <std::size_t subwidth> struct widthinfo<subwidth, 0x7u> : public widthinfo<subwidth, 0x0u> { typedef std::size_t    byte; typedef std::size_t    trivial; };

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

    #if defined __clang__
      template <std::size_t subwidth>
      struct widthinfo<subwidth, 0x8u> : public widthinfo<subwidth, 0x0u> {
        typedef __uint128_t byte;
        typedef __uint128_t trivial;
      };
    #elif defined __GNUC__ ? defined __SIZEOF_INT128__ : false
      template <std::size_t subwidth>
      struct widthinfo<subwidth, 0x8u> : public widthinfo<subwidth, 0x0u> {
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wpedantic"

        typedef unsigned __int128 byte;
        typedef unsigned __int128 trivial;

        #pragma GCC diagnostic pop
      };
    #elif defined __cpp_lib_ranges // --> 201911L
      template <std::size_t subwidth>
      struct widthinfo<subwidth, 0x8u> : public widthinfo<subwidth, 0x0u> {
        #if __cplusplus >= 201103L or defined _MSVC_LANG
          typedef std::ranges::range_difference_t<std::ranges::iota_view<unsigned long long, unsigned long long> > byte;
          typedef std::ranges::range_difference_t<std::ranges::iota_view<unsigned long long, unsigned long long> > trivial;
        #else
          typedef std::ranges::range_difference_t<std::ranges::iota_view<unsigned long, unsigned long> > byte;
          typedef std::ranges::range_difference_t<std::ranges::iota_view<unsigned long, unsigned long> > trivial;
        #endif
      };
    #endif

    // ... --> segment<…> ->> `uintwidth` value representation — layout order defers to the environment's `reinterpret_cast` endian perspective
    template <std::size_t subwidth, std::size_t = widthinfo<subwidth>::next, enum endian::type = endianness>
    struct segment;

    template <>
    struct segment<0u, 0u, endianness> /* final */ {
      static std::size_t const extent = 0u;
      static std::size_t const length = 0u;

      /* constexpr */ inline segment<0u>& next() const /* noexcept */ {
        return const_cast<segment<0u>&>(*this);
      }
    };

    template <std::size_t subwidth>
    struct segment<subwidth, 0u, endianness> /* final */ {
      static std::size_t const           extent = 1u;
      typename widthinfo<subwidth>::byte value  : subwidth;
      static std::size_t const           length = subwidth;

      /* constexpr */ inline segment<0u>& next(segment<0u> const& _ = segment<0u>()) const /* noexcept */ {
        return const_cast<segment<0u>&>(_); // ->> Ensure this temporary is never accessed
      }
    };

    template <std::size_t subwidth, std::size_t subnext>
    struct segment<subwidth, subnext, endian::big> /* final */ {
      segment<subnext>                   _;
      typename widthinfo<subwidth>::byte value;
      static std::size_t const           length = CHAR_BIT * sizeof(typename widthinfo<subwidth>::byte);
      static std::size_t const           extent = segment<subnext>::extent + 1u;

      /* constexpr */ inline segment<subnext>& next() const /* noexcept */ {
        return const_cast<segment<subnext>&>(_);
      }
    };

    template <std::size_t subwidth, std::size_t subnext>
    struct segment<subwidth, subnext, endian::little> /* final */ {
      static std::size_t const           extent = segment<subnext>::extent + 1u;
      static std::size_t const           length = CHAR_BIT * sizeof(typename widthinfo<subwidth>::byte);
      typename widthinfo<subwidth>::byte value;
      segment<subnext>                   _;

      /* constexpr */ inline segment<subnext>& next() const /* noexcept */ {
        return const_cast<segment<subnext>&>(_);
      }
    };

    // ... --> lengthof<T> ->> Length of `base` array able to completely store a `uintwidth<width>`
    template <typename base>
    struct lengthof /* final */ {
      static std::size_t const value = (width / (CHAR_BIT * sizeof(base))) + (width % (CHAR_BIT * sizeof(base)) ? 1u : 0u) + (0u == width);

      struct bits /* final */ {
        static std::size_t const size    = CHAR_BIT * sizeof(base[value]);
        static std::size_t const padding = size - width;
      };
    };

    // ... --> cast<T>(…) ->> Convert trivial C++ integer types to `base`
    template <typename base>
    struct cast /* final */ {
      base const value;

      /* constexpr */ inline cast(base const value) /* noexcept */ : value(value) {}
      /* constexpr */ inline operator base() const /* noexcept */ { return this -> value; }
    };

    template <std::size_t subwidth>
    struct cast<uintwidth<subwidth> > /* final */ {
      uintwidth<subwidth> /* const */ value;

      inline cast(uintmax_t const value) /* noexcept */ : value() { this -> value.operator =(value); }
      /* constexpr */ inline operator uintwidth<subwidth>() const /* noexcept */ { return this -> value; }
    };

    /* ... --> assign(…, T) */
    /* constexpr */ inline static void assign(segment<0u>&, uintmax_t const, std::size_t const = 0u) /* noexcept */ { /* Do nothing… */ }

    template <std::size_t subwidth>
    inline static void assign(segment<subwidth>& segment, uintmax_t value, std::size_t const length = (CHAR_BIT * sizeof(uintmax_t) < width ? CHAR_BIT * sizeof(uintmax_t) : width)) /* noexcept */ {
      for (uintmax_t const maximum = widthmaxof(CHAR_BIT * sizeof(uintmax_t) < width ? CHAR_BIT * sizeof(uintmax_t) : width); maximum < value; --value)
        value -= maximum; // ->> Truncate `value` due to possible overflow (faster algorithm unknown)

      segment.value = (value >> (endian::big == endianness ? length - segment.length : 0u)) & widthmaxof(segment.length);
      uintwidth::assign(segment.next(), value >> (endian::little == endianness ? segment.length : 0u), length - segment.length);
    }

    // ... --> compose(…, T[])
    // /* constexpr */ inline static void compose(segment<0u>&, uintmax_t const (&)[lengthof<uintmax_t>::value], std::size_t const = 0u) /* noexcept */ { /* Do nothing… */ }

    // template <std::size_t subwidth>
    // /* constexpr */ inline static void compose(segment<subwidth>& segment, uintmax_t const (&value)[lengthof<uintmax_t>::value], std::size_t const length = 0u) /* noexcept */ {
    //   TODO (Lapys)
    // }

    // ... --- TODO (Lapys) -> Not part of the final product
    inline static void debug(segment<0u> const&) {}

    template <std::size_t subwidth>
    inline static void debug(segment<subwidth> const& segment) {
      char string[uintwidth::segment<subwidth>::length];
      char *iterator = string + (sizeof string / sizeof(char));

      // ...
      for (uintmax_t value = segment.value; value; value >>= 1u)
        *--iterator = value & 1u ? '1' : '0';

      while (iterator != string)
        *--iterator = '0';

      std::printf("{%zu} %0.*s" " ", static_cast<std::size_t>(segment.value), static_cast<int>(sizeof string / sizeof(char)), string);
      uintwidth::debug(segment.next());
    }

    // ... --> decompose(…, T[]) --- TODO (Lapys) -> Use `uintmax_t[]`
    template <typename S>
    /* constexpr */ inline static void decompose(segment<0u> const&, S[], std::size_t, std::size_t) /* noexcept */ { /* Do nothing… */ }

    template <typename S>
    /* constexpr */ inline static void decompose(segment<width> const& segment, S (&value)[lengthof<S>::value]) /* noexcept */ {
      for (S *iterator = value + (sizeof value / sizeof(S)); iterator != value; )
      *--iterator = 0u; // ->> Zero out `S value[]`

      uintwidth::decompose(segment, value, segment.length, CHAR_BIT * sizeof(S));
    }

    template <typename S, std::size_t subwidth>
    /* constexpr */ inline static void decompose(segment<subwidth> const& segment, S value[], std::size_t segmentLength, std::size_t valueLength) /* noexcept */ {
      if (segmentLength > valueLength) {
        segmentLength -= valueLength;
        *value       <<= valueLength;
        *value        |= segment.value >> segmentLength;

        uintwidth::decompose(segment, value + 1, segmentLength, CHAR_BIT * sizeof(S));
      }

      else {
        *value     <<= segmentLength;
        *value      |= segment.value & widthmaxof(segmentLength);
        valueLength -= segmentLength;

        uintwidth::decompose(segment.next(), value + (0u == valueLength), segment.next().length, 0u == valueLength ? CHAR_BIT * sizeof(S) : valueLength);
      }
    }

    // ... --> diagnose(…, …)
    template <std::size_t capacity>
    /* constexpr */ inline static void diagnose(segment<0u> const&, std::size_t (&)[capacity]) /* noexcept */ { /* Do nothing… */ }

    template <std::size_t subwidth, std::size_t capacity>
    /* constexpr */ inline static void diagnose(segment<subwidth> const& segment, std::size_t (&lengths)[capacity]) /* noexcept */ {
      lengths[capacity - segment.extent] = segment.length;
      uintwidth::diagnose(segment.next(), lengths);
    }

    // ... --> maximize(…)
    /* constexpr */ inline static void maximize(segment<0u>&) /* noexcept */ { /* Do nothing… */ }

    template <std::size_t subwidth>
    inline static void maximize(segment<subwidth>& segment) /* noexcept */ {
      segment.value = widthmaxof(segment.length);
      uintwidth::maximize(segment.next());
    }

    // ... --> promote<T>(…)
    template <typename type>
    /* constexpr */ inline static type promote(segment<0u>&, std::size_t const = 0u) /* noexcept */ {
      return cast<type>(0u);
    }

    template <typename type, std::size_t subwidth>
    /* constexpr */ inline static type promote(segment<subwidth>& segment, std::size_t const length = 0u) /* noexcept */ {
      return (
        uintwidth::promote<type>(segment.next(), segment.length + length) |
        (cast<type>(segment.value) << (endian::big == endianness ? width - (segment.length + length) : length))
      );
    }

    // ... --> shift(…, T) --- TODO (Lapys) -> Make breakage-proof e.g.: `32, 8, 8` v. `32, 16` and what's the deal with `uintwidth<64>`?
    /* constexpr */ inline static void shift(segment<width>& segment, uintmax_t shift) /* noexcept */ {
      typedef uint8_t S;
      // typedef uint16_t S;
      // typedef uint32_t S;
      // typedef uint64_t S;
      // typedef uintmax_t S;

      if (shift >= width or shift >= CHAR_BIT * sizeof(S[lengthof<S>::value]))
      return uintwidth::zero(segment);

      S           composition[uintwidth::lengthof<S>    ::value]; // go with `struct segment { T prev; T next; }` approach, instead
      std::size_t lengths    [uintwidth::segment <width>::extent];
      std::size_t minimumLength = segment.length;

      // ...
      uintwidth::decompose(segment, composition);
      uintwidth::diagnose (segment, lengths);

      for (std::size_t *iterator = lengths + segment.extent; iterator != lengths; ) {
        if (*--iterator < minimumLength)
        minimumLength = *iterator;
      }

      // ... ->> Shift entire "byte sequence"s at a time
      for (; shift; shift = shift > minimumLength ? shift - minimumLength : 0u)
      for (std::size_t compositionIndex = 0u, *iterator = lengths + segment.extent; iterator != lengths; ) {
        struct shifty /* final */ {
          /* constexpr */ inline static void diagnose(S (&composition)[uintwidth::lengthof<S>::value], std::size_t index, std::size_t const length, S** const begin, std::size_t* const beginOffset, S** const end, std::size_t* const endOffset) /* noexcept */ {
            std::size_t const compositionElementWidth = CHAR_BIT * sizeof(S);
            S          *const compositionEnd          = composition + (lengthof<S>::value - 1u);

            // ...
            *begin     = compositionEnd;
            *end       = compositionEnd;
            *endOffset = index;

            // ...
            if (0u == lengthof<S>::bits::padding) {
              *end   -= (index - 0u) / compositionElementWidth;
              index  += length;
              *begin -= (index - 1u) / compositionElementWidth;
            }

            else {
              *endOffset -= index >= compositionElementWidth - lengthof<S>::bits::padding ? compositionElementWidth - lengthof<S>::bits::padding : 0u;

              *end   -= index >= compositionElementWidth - lengthof<S>::bits::padding ? ((index - (compositionElementWidth - lengthof<S>::bits::padding) - 0u) / compositionElementWidth) + 1u : 0u;
              index  += length;
              *begin -= index >  compositionElementWidth - lengthof<S>::bits::padding ? ((index - (compositionElementWidth - lengthof<S>::bits::padding) - 1u) / compositionElementWidth) + 1u : 0u;
            }

            *endOffset  %= compositionElementWidth;
            *beginOffset = *begin == *end ? length + *endOffset : ((compositionElementWidth - (compositionEnd == *end ? lengthof<S>::bits::padding : 0u)) - *endOffset);
          }

          /* constexpr */ inline static uintmax_t read(S (&composition)[uintwidth::lengthof<S>::value], S begin[], std::size_t const beginOffset, S end[], std::size_t const endOffset) /* noexcept */ {
            std::size_t const compositionElementWidth = CHAR_BIT * sizeof(S);
            S          *const compositionEnd          = composition + (lengthof<S>::value - 1u);

            // ...
            if (begin != end) {
              uintmax_t value = 0u;

              // ... ->> `value` inclusively straddles the segments between `begin` and `end`
              for (S *iterator = begin; ; ++iterator) {
                if (end == iterator)
                return value | ((lengthof<S>::bits::padding and compositionEnd == end ? *end & widthmaxof(compositionElementWidth - lengthof<S>::bits::padding) : *end) >> endOffset);

                value  |= begin == iterator ? *begin & widthmaxof(beginOffset) : *iterator;
                value <<= compositionElementWidth - (end == iterator + 1 ? endOffset + (compositionEnd == end ? lengthof<S>::bits::padding : 0u) : 0u);
              }
            }

            return ((lengthof<S>::bits::padding and compositionEnd == end ? *begin & widthmaxof(compositionElementWidth - lengthof<S>::bits::padding) : *begin) & widthmaxof(beginOffset)) >> endOffset;
          }

          /* constexpr */ inline static void write(S (&composition)[uintwidth::lengthof<S>::value], S begin[], std::size_t const beginOffset, S end[], std::size_t const endOffset, uintmax_t value) /* noexcept */ {
            std::size_t const compositionElementWidth = CHAR_BIT * sizeof(S);
            S          *const compositionEnd          = composition + (lengthof<S>::value - 1u);
            std::size_t const length                  = begin != end ? ((CHAR_BIT * ((compositionEnd - 1) - begin) * sizeof(S)) + (compositionElementWidth - lengthof<S>::bits::padding) + beginOffset) - (compositionEnd != end ? ((CHAR_BIT * ((compositionEnd - 1) - end) * sizeof(S)) + (compositionElementWidth - lengthof<S>::bits::padding)) - endOffset : endOffset) : (beginOffset - endOffset);

            // ...
            for (uintmax_t const maximum = widthmaxof(length); maximum < value; --value)
              value -= maximum; // ->> Truncate `value` due to possible overflow (faster algorithm unknown)

            if (begin != end)
            for (S *iterator = end + 1; ; ) {
              if (begin == --iterator) {
                *begin  = (*begin >> beginOffset) << beginOffset;
                *begin |= value & widthmaxof(beginOffset);

                return; // --> value >>= beginOffset;
              }

              if (end == iterator) {
                *end   &= widthmaxof(endOffset);
                *end   |= (value & widthmaxof(compositionElementWidth - (compositionEnd == end ? lengthof<S>::bits::padding : 0u) - endOffset)) << endOffset;
                value >>= compositionElementWidth - (compositionEnd == end ? lengthof<S>::bits::padding : 0u) - endOffset;

                continue;
              }

              *iterator = value & widthmaxof(compositionElementWidth);
              value   >>= compositionElementWidth;
            }

            *begin  = ((*begin >> beginOffset) << beginOffset) | (*begin & widthmaxof(endOffset));
            *begin |= value << endOffset;
          }
        };

        std::size_t const currentSegmentLength = *--iterator;
        uintmax_t         currentSegmentValue  = 0u;
        std::size_t const nextSegmentLength    = iterator != lengths ? iterator[-1] : 0u;
        uintmax_t         nextSegmentValue     = 0u;
        S                *subcomposition,      *subcompositionEnd;       // ->> Range  in `composition` where the "byte segment" is stored
        std::size_t       subcompositionOffset, subcompositionEndOffset; // ->> Offset in `composition` where the "byte segment" begins and ends

        // ...
        if (iterator != lengths) {
          shifty::diagnose(composition, compositionIndex + currentSegmentLength, nextSegmentLength, &subcomposition, &subcompositionOffset, &subcompositionEnd, &subcompositionEndOffset);
          nextSegmentValue = shifty::read(composition, subcomposition, subcompositionOffset, subcompositionEnd, subcompositionEndOffset);
        }

        shifty::diagnose(composition, compositionIndex, currentSegmentLength, &subcomposition, &subcompositionOffset, &subcompositionEnd, &subcompositionEndOffset);
        currentSegmentValue = shifty::read(composition, subcomposition, subcompositionOffset, subcompositionEnd, subcompositionEndOffset);

        shifty::write(composition, subcomposition, subcompositionOffset, subcompositionEnd, subcompositionEndOffset, (currentSegmentValue << minimumLength) | (nextSegmentValue >> (nextSegmentLength - minimumLength)));
        compositionIndex += currentSegmentLength;
      }
    }

    // ... --> zero(…)
    /* constexpr */ inline static void zero(segment<0u>&) /* noexcept */ { /* Do nothing… */ }

    template <std::size_t subwidth>
    /* constexpr */ inline static void zero(segment<subwidth>& segment) /* noexcept */ {
      segment.value = 0u;
      uintwidth::zero(segment.next());
    }

    /* ... */
    #define uintwidth uint_t_1u(__LINE__)
    # define uint_t_1u(hash) uint_t_2u(hash)
    # define uint_t_2u(hash)                                                                                              \
      public : segment<width> value ## hash; /* ->> Obfuscate the public member for aggregate-/ default-initialization */ \
      private: /* constexpr */ inline segment<width>& valueof() const /* noexcept */ { return const_cast<segment<width>&>(this -> value ## hash); }

      uintwidth;
    #undef uintwidth
    # undef uint_t_1u
    # undef uint_t_2u

  public: // ->> No non-trivial constructor for `union` support pre-C++11
    // ...
    inline uintwidth<width, endianness>& operator =(uintmax_t const value) /* noexcept */ {
      uintwidth::assign(this -> valueof(), value);
      return *this;
    }

    // ...
    /* constexpr */ inline operator typename widthinfo<width>::trivial() const /* noexcept */ {
      return uintwidth::promote<typename widthinfo<width>::trivial>(this -> valueof());
    }

    template <std::size_t subwidth>
    /* constexpr */ inline operator uintwidth<subwidth>() const /* noexcept */ {
      return uintwidth::promote<uintwidth<subwidth> >(this -> valueof());
    }
};
  template <std::size_t width, enum endian::type subendianness>
  /* constexpr */ inline uintwidth<width, subendianness> operator +(uintwidth<width, subendianness> const& segment) /* noexcept */ {
    return segment;
  }

  // template <std::size_t width>
  // /* constexpr */ inline uintwidth<width> operator -(uintwidth<width>) /* noexcept */ {
  //   uintwidth<width> maximum = {};

  //   uintwidth<width>::maximize(maximum.valueof());
  //   return maximum - *this;
  // }

  // template <std::size_t widthA, std::size_t widthB>
  // inline uintwidth<(widthA > widthB ? widthA : widthB)> operator -(uintwidth<widthA> const& integerA, uintwidth<widthB> const& integerB) {
  //   uintwidth<(widthA > widthB ? widthA : widthB)>::subtract(integerA.valueof(), integerB.valueof());
  // }

  // template <std::size_t width>
  // /* constexpr */ inline uintwidth<width> operator <<(uintwidth<width> integerA, uintmax_t const integerB) /* noexcept */ {
  //   uintwidth<width>::shift(integerA.valueof(), integerB);
  //   return integerA;
  // }

  // template <std::size_t widthA, std::size_t widthB>
  // /* constexpr */ inline uintwidth<(widthA > widthB ? widthA : widthB)> operator <<(uintwidth<widthA> const& integerA, uintwidth<widthB> const& integerB) /* noexcept */ {
  //   integerA.valueof()
  // }

template <std::size_t>
struct literal;

template <std::size_t>
struct intwidth;

template <std::size_t>
struct fixedwidth;

template <std::size_t significance, std::size_t place>
struct floatwidth /* final */ {
  // CITE (Lapys) -> https://en.wikipedia.org/wiki/Single-precision_floating-point_format
  static std::size_t const radix = 2u;

  uintmax_t exponent   : significance;
  uintmax_t mantissa   : place;
  bool      signedness : 1;
};

struct real;

// ...
typedef floatwidth<4u,  3u>   float8,   f8;
typedef floatwidth<5u,  10u>  float16,  f16;
typedef floatwidth<8u,  23u>  float32,  f32;
typedef floatwidth<11u, 52u>  float64,  f64;
typedef floatwidth<15u, 64u>  float80,  f80;
typedef floatwidth<15u, 112u> float128, f128;
typedef floatwidth<19u, 236u> float256, f256;
typedef intwidth  <8u>        int8,     i8;
typedef intwidth  <16u>       int16,    i16;
typedef intwidth  <32u>       int32,    i32;
typedef intwidth  <64u>       int64,    i64;
typedef intwidth  <128u>      int128,   i128;
typedef intwidth  <256u>      int256,   i256;
typedef uintwidth <8u>        uint8,    u8;
typedef uintwidth <16u>       uint16,   u16;
typedef uintwidth <32u>       uint32,   u32;
typedef uintwidth <64u>       uint64,   u64;
typedef uintwidth <128u>      uint128,  u128;
typedef uintwidth <256u>      uint256,  u256;

/* Main */
int main(int, char*[]) /* noexcept */ {
  std::size_t const width = 16u + 8u + 5u;
  union { uintwidth<width> integer; };

  // ...
  // integer = 1u;
  // integer = 65536u;
  // integer = 1u | 65536u | 16777216u; // 16842753u
  integer = 42069u | 71337u | 17344212u;

  std::printf("[integer]: %zu" "\r\n", static_cast<std::size_t>(integer));
  uintwidth<width>::shift(integer.valueof(), CHAR_BIT);

  // std::puts("");

  // integer = (42069u | 71337u | 17344212u) << CHAR_BIT;
  // std::printf("[integer]: %zu" "\r\n", static_cast<std::size_t>(integer));
  // uintwidth<width>::shift(integer.valueof(), CHAR_BIT);

  // std::printf("[integer]: %lu" "\r\n", static_cast<unsigned long>(static_cast<uintwidth<8u> >(integer)));
}
