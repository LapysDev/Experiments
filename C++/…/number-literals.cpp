template <std::size_t capacity>
struct number final {
  char const value[capacity];

  // ... ->> Assume the `number` is completely representable by `type`
  template <typename type>
  constexpr operator type() const noexcept {
    enum : unsigned char { binary = 2u, decimal = 10u, hexadecimal = 16u, octal = 8u };

    type          characteristics = {static_cast<unsigned char>(0u)};          //
    signed char   exponential     = 0;                                         // ->> Determines if `number` uses scientific notation
    bool          fractional      = false;                                     // ->> Determines if `number` uses a decimal point
    type          exponent        = {static_cast<unsigned char>(0u)};          //
    type          mantissa        = {static_cast<unsigned char>(0u)};          //
    unsigned char radix           = *(this -> value) == '0' ? octal : decimal; // ->> Determines the numeral base of `number`

    // ... ->> Parse the `::value` into `characteristics`, `exponent`, and `mantissa`
    for (char const *iterator = this -> value; capacity != static_cast<std::size_t>(iterator - this -> value); ++iterator) {
      unsigned char digit = static_cast<unsigned char>(-1);

      // ... ->> Parse the current character
      switch (*iterator) {
        case '-':           exponential = -exponential;                            break;
        case '.':           fractional  = true;                                    break;
        case '0':           digit       = 0u;                                      break;
        case '1':           digit       = 1u;                                      break;
        case '2':           digit       = 2u;                                      break;
        case '3':           digit       = 3u;                                      break;
        case '4':           digit       = 4u;                                      break;
        case '5':           digit       = 5u;                                      break;
        case '6':           digit       = 6u;                                      break;
        case '7':           digit       = 7u;                                      break;
        case '8':           digit       = 8u;                                      break;
        case '9':           digit       = 9u;                                      break;
        case 'A': case 'a': digit       = 10u;                                     break;
        case 'B': case 'b': radix == hexadecimal ? digit = 11u : radix = binary;   break;
        case 'C': case 'c': digit = 12u;                                           break;
        case 'D': case 'd': digit = 13u;                                           break;
        case 'E': case 'e': radix == hexadecimal ? digit = 14u : exponential = 10; break;
        case 'F': case 'f': digit       = 15u;                                     break;
        case 'P': case 'p': exponential = 2;                                       break;
        case 'X': case 'x': radix       = hexadecimal;                             break;
      }

      // ... ->> Update `characteristics`, `exponent`, or `mantissa`
      if (digit != static_cast<unsigned char>(-1)) {
        type const subdigit = {static_cast<unsigned char>(digit)};
        type const subradix = {static_cast<unsigned char>(radix)};

        // ...
        if (exponential) { exponent = (exponent * subradix) + subdigit; continue; }
        if (fractional)  { mantissa = (mantissa + subdigit) / subradix; continue; }

        characteristics = (characteristics * subradix) + subdigit;
      }
    }

    // ... ->> Apply `exponent` and `mantissa` to `characteristics`
    characteristics = characteristics + mantissa;

    for (; exponent != type{static_cast<unsigned char>(0u)}; exponent = exponent - type{static_cast<unsigned char>(1u)}) {
      if (exponential > 0) characteristics = characteristics * exponential;
      if (exponential < 0) characteristics = characteristics / exponential;
    }

    return characteristics;
  }
};

/* ... */
template <char... numerics>
constexpr number<sizeof...(numerics)> operator ""_num() noexcept {
  return {numerics...};
}

static_cast<double>     (3.14_num);
static_cast<float>      (3.14_num);
static_cast<long double>(3.14_num);

constexpr char const* operator ""_str(char const string[]) noexcept {
  return string;
}

1337_str; // "1337"
3.14_str; // "3.14"
