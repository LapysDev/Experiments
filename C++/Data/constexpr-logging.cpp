#include <cstddef>
#include <cstdio>

/* ... */
struct print {
  friend void flush(FILE* const stream, print const& data) noexcept(noexcept(std::fprintf(stdout, " "))) {
    std::fprintf(stream, "%s", data.buffer);
  }

  private:
    #if __cplusplus >= 2011uL
      typedef signed   long long intmax_t;
      typedef unsigned long long uintmax_t;
    #else
      typedef signed   long intmax_t;
      typedef unsigned long uintmax_t;
    #endif

    char buffer[2048 - 1], dummy;

  protected:
    // : Buffer operations
    constexpr char const* bufend  ()                                        const { return this -> bufend(this -> buffer); }
    constexpr char const* bufend  (char const buffer[])                     const { return '\0' != *buffer ? this -> bufend(buffer + 1) : buffer; }
    constexpr std::size_t buflen  ()                                        const { return this -> bufend(this -> buffer) - (this -> buffer); }
    constexpr char        bufread (std::size_t const index)                 const { return (this -> buffer[index]); }
    constexpr int         bufwrite(std::size_t const index, char const character) { return (const_cast<char*>(this -> buffer)[index] = character); }

    constexpr int bufrev(std::size_t const begin, std::size_t const end) {
      return begin < end ? (
        this -> bufwrite(begin, this -> bufread(begin) ^ this -> bufread(end)  ),
        this -> bufwrite(end  , this -> bufread(end)   ^ this -> bufread(begin)),
        this -> bufwrite(begin, this -> bufread(begin) ^ this -> bufread(end)  )
      ), this -> bufrev(begin + 1u, end - 1u) : 0x0;
    }

    // : Number operations
    constexpr unsigned char numdig(uintmax_t   const number, unsigned char const nil) const { return number > nil ? nil : number; }
    constexpr unsigned char numdig(long double const number, unsigned char const nil) const { return number < 01.0L ? 0u : number < 02.0L ? 1u : number < 03.0L ? 2u : number < 04.0L ? 3u : number < 05.0L ? 4u : number < 06.0L ? 5u : number < 07.0L ? 6u : number < 08.0L ? 7u : number < 09.0L ? 8u : number < 10.0L ? 9u : nil; }

    constexpr unsigned char numcharsize(long double const number, long double const radix) const { return 1.0L <= number ? 1u + this -> numcharsize(number / radix, radix) : 0u; }
    constexpr unsigned char nummantsize(long double const,        long double const)       const { return 15u; }
    constexpr unsigned char numsize(uintmax_t const number, uintmax_t const radix) const { return 0u != number ? 1u + this -> numsize(number / radix, radix) : 0u; }

    template <typename type>
    constexpr type numunit(type const number, unsigned char const exponent, type const radix) const {
      return 0u != exponent ? radix * this -> numunit(number, exponent - 1u, radix) : number;
    }

    // : Pointer operations
    constexpr uintmax_t ptrval(void* const pointer) const {
      return static_cast<unsigned char*>(pointer) - static_cast<unsigned char*>(NULL);
    }

    // : Print (disambiguous) operations ->> Main implementations
    constexpr int putc(char const character) {
      return this -> bufwrite(this -> buflen() + 1u, '\0'), this -> bufwrite(this -> buflen() + 0u, character);
    }

    constexpr int putd(long double const number, unsigned char const characteristicsLength, unsigned char const mantissaLength, long double const radix) {
      return 0u == characteristicsLength ? (
        0u != mantissaLength && 0.0L != number ? (
          this -> putc('.'),
          this -> putd(number * this -> numunit(1.0L, mantissaLength, radix), mantissaLength, 0u, radix)
        ) : 0x0
      ) : (
        this -> putc("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[this -> numdig(number / this -> numunit(1.0L, characteristicsLength - 1u, radix), 37u)]),
        this -> putd(number - (
          this -> numunit(1.0L, characteristicsLength - 1u, radix) *
          this -> numdig(number / this -> numunit(1.0L, characteristicsLength - 1u, radix), 37u)
        ), characteristicsLength - 1u, mantissaLength, radix)
      );
    }

    constexpr int putp(void* const pointer) {
      return this -> puts("0x"), this -> putu(this -> ptrval(pointer), 16u);
    }

    constexpr int puts(char const string[]) {
      return '\0' != *string ? this -> putc(*string), this -> puts(string + 1) : 0x0;
    }

    constexpr int putu(uintmax_t const number, uintmax_t const radix) {
      return 0u != number ? (
        this -> putc("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[this -> numdig(number % radix, 37u)]),
        this -> putu(number / radix, radix)
      ) : 0x0;
    }

    // : Print (overloaded) operations ->> Atomic overloads
    constexpr int put(bool const boolean) {
      return this -> puts(boolean ? "true" : "false");
    }

    constexpr int put(char const character) {
      return this -> putc(character);
    }

    constexpr int put(char const string[]) {
      return this -> puts(string);
    }

    constexpr int put(long double const number) {
      return 0.0L != number ?
        this -> putd(number, number < 1.0L ? 1u : this -> numcharsize(number, 10.0L), this -> nummantsize(number, 10.0L), 10.0L) :
        this -> puts("0.0");
    }

    constexpr int put(intmax_t const number) {
      return 0 > number ?
        this -> putc('-'), this -> put(static_cast<unsigned long long>(-number)) :
        this -> put(static_cast<unsigned long long>(number));
    }

    constexpr int put(uintmax_t const number) {
      return 0u != number ? (
        this -> putu(number, 10u),
        this -> bufrev(this -> buflen() - this -> numsize(number, 10u), this -> buflen() - 1u)
      ) : this -> putc('0');
    }

    template <typename type>
    constexpr int put(type* const pointer) {
      return this -> putp(static_cast<void*>(pointer)), this -> bufrev(
        this -> buflen() - this -> numsize(this -> ptrval(static_cast<void*>(pointer)), 16u),
        this -> buflen() - 1u
      );
    }

    // : Print (ambiguous) operations ->> Ambiguous overloads
    constexpr int put() { return 0x0; }
    constexpr int put(char string[]) { return this -> put(const_cast<char const*>(string)); }
    constexpr int put(double const number) { return this -> put(static_cast<long double>(number)); }
    constexpr int put(float  const number) { return this -> put(static_cast<long double>(number)); }
    constexpr int put(signed   char  const number) { return this -> put(static_cast<intmax_t>(number)); }
    constexpr int put(signed   int   const number) { return this -> put(static_cast<intmax_t>(number)); }
    constexpr int put(signed   short const number) { return this -> put(static_cast<intmax_t>(number)); }
    constexpr int put(unsigned char  const number) { return this -> put(static_cast<uintmax_t>(number)); }
    constexpr int put(unsigned int   const number) { return this -> put(static_cast<uintmax_t>(number)); }
    constexpr int put(unsigned short const number) { return this -> put(static_cast<uintmax_t>(number)); }
    #if __cplusplus >= 2011uL
     constexpr int put(signed   long const number) { return this -> put(static_cast<intmax_t>(number)); }
     constexpr int put(unsigned long const number) { return this -> put(static_cast<uintmax_t>(number)); }
    #endif
    template <typename type> constexpr int put(type const* const pointer) { return this -> put(const_cast<type*>(pointer)); }
    template <typename type, typename... types> constexpr int put(type const argument, types const... arguments) { return this -> put(argument), this -> put(arguments...); }

  public:
    template <typename... types>
    constexpr explicit print(types const... arguments) :
      buffer{0}, dummy(static_cast<char>(this -> put(arguments...)))
    {}

    constexpr operator int() const { return this -> buflen(); }
};
