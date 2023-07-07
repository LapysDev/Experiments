#include <ciso646>
#include <cstddef>
#include <cstdio>
#include <stdint.h>

/* ... */
template <std::size_t capacity, std::size_t count>
constexpr char* min_expression(char (*const computation)[capacity], std::size_t const value, std::size_t const (&values)[count], std::size_t rank = 0u, std::size_t const limit = static_cast<std::size_t>(-1)) noexcept {
  union min /* namespace */ {
    enum operation_t : unsigned char {
      concatenate         = 0xCu,
      parse               = 0x0u,

      add                 = 0x7u,
      bitwise_and         = 0x3u,
      bitwise_or          = 0x1u,
      bitwise_shift_left  = 0x5u,
      bitwise_shift_right = 0x4u,
      bitwise_xor         = 0x2u,
      divide              = 0x9u,
      exponentiate        = 0xBu,
      modulo              = 0x8u,
      multiply            = 0xAu,
      subtract            = 0x6u // ->> Overflow not accounted
    };
  
    // …
    enum : std::size_t {
      arity   = ((5u) * 2u) + 1u, // ->> Number of tokens allowed in the final `computation`
      eager   = true,             // ->> ..? (see usage for description)
      maximum = 20u,              // --> min::lengthof(SIZE_MAX)
      radix   = 10u               // ->> Base number representation of `computation`; `0zu` and beyond `36zu` is unsupported
    };

    /* … */
    constexpr static std::size_t digitof(char const token) noexcept {
      return (
        token >= '0' and token <= '9' ? static_cast<unsigned char>(token - '0') < static_cast<std::size_t>(min::radix) ? static_cast<unsigned char>(token - '0') : static_cast<std::size_t>(min::radix) :
        token >= 'a' and token <= 'z' ? static_cast<unsigned char>(token - 'a') < static_cast<std::size_t>(min::radix) ? static_cast<unsigned char>(token - 'a') : static_cast<std::size_t>(min::radix) :
        min::radix
      );
    }

    constexpr static unsigned char lengthof(std::size_t value) noexcept {
      unsigned char length = 0u == value ? 1u : 0u;

      // …
      for (; value; value /= min::radix)
        ++length;

      return length;
    }

    constexpr static char* nullify(char (*const computation)[capacity]) noexcept {
      for (char *iterator = *computation + capacity; *computation != iterator; )
      *--iterator = '\0';

      return nullptr;
    }

    constexpr static std::size_t operandsof(std::size_t const index, char const expression[], char const* token, std::size_t const length) noexcept {
      std::size_t operand = 0u;

      // …
      switch (index) {
        case 0u: {
          std::size_t rank = 1u;

          // …
          for (--token; min::radix != min::digitof(*token); --token, rank *= min::radix) {
            operand += min::digitof(*token) * rank;
            if (expression == token) break;
          }
        } break;

        case 1u: {
          for (token += length; min::radix != min::digitof(*token) and '\0' != *token; ++token)
          operand = min::digitof(*token) + (operand * min::radix);
        } break;
      }

      return operand;
    }

    constexpr static char* operate(char (*const computation)[min::maximum + 1u], operation_t const operation, std::size_t const (&operands)[2]) noexcept {
      char       *iterator = *computation;
      std::size_t value    = operands[0];

      // …
      switch (operation) {
        case min::add                : value +=  operands[1]; break;
        case min::bitwise_and        : value &=  operands[1]; break;
        case min::bitwise_or         : value |=  operands[1]; break;
        case min::bitwise_shift_left : value <<= operands[1]; break;
        case min::bitwise_shift_right: value >>= operands[1]; break;
        case min::bitwise_xor        : value ^=  operands[1]; break;
        case min::multiply           : value *=  operands[1]; break;
        case min::subtract           : value -=  operands[1]; break;

        case min::divide: value = 0u != operands[1] ? value / operands[1] : 0u; break;
        case min::modulo: value = 0u != operands[1] ? value % operands[1] : 0u; break;

        case min::exponentiate: {
          if (0u == operands[1])                                      value =  1u;
          else for (std::size_t exponent = operands[1]; --exponent; ) value *= operands[0];
        } break;

        default:
          return nullptr;
      }

      *iterator = '0';
      iterator += min::lengthof(value);
      *iterator = '\0';

      for (; value; value /= min::radix)
      *--iterator = "0123456789abcdefghijklmnopqrstuvwxyz"[value % min::radix];

      // …
      return *computation;
    }

    constexpr static char* resultof(char (*const computation)[(SIZE_MAX / min::maximum >= capacity / 2u ? (capacity >= 2u ? capacity / 2u : 1u) * min::maximum : capacity) + 1u], char const (&expression)[capacity]) noexcept {
      std::size_t length                            = capacity;
      char        subcomputation[min::maximum + 1u] = {};

      // --> *computation = expression
      for (std::size_t index = capacity; index--; )
      (*computation)[index] = expression[index];

      // … ->> Run through each operation to compute `expression`
      for (operation_t operation = min::exponentiate; min::parse != operation; operation = static_cast<operation_t>(static_cast<unsigned char>(operation) - 1u)) {
        char             *iterator = *computation + length;
        char const *const token    = min::tokenof(operation);

        // …
        if (nullptr == token)
        continue;

        // … ->> Run through the current `computation` with the given `operation`
        while (*computation != iterator--)
        for (std::size_t index = 0u; ; ++index) {
          if ('\0' == token[index]) /* --> token in *computation */ {
            std::size_t sublength = index;

            // … --> subcomputation = operate(…, multiply, size_t[2] {a, b})
            if (nullptr != min::operate(&subcomputation, operation, {
              min::operandsof(0u, *computation, iterator, sublength),
              min::operandsof(1u, *computation, iterator, sublength)
            })) {
              char const *iterators[2] = {iterator - 1, iterator + sublength};
              std::size_t offset       = 0u;

              // … --> computation -> replace(iterator, subcomputation)
              for (sublength = 0u; '\0' != subcomputation[sublength]; )
                ++sublength;

              while (min::radix != min::digitof(*iterators[0]) and *computation != iterators[0]) --iterators[0];
              while (min::radix != min::digitof(*iterators[1]))                                  ++iterators[1];

              iterators[0] += *computation != iterators[0];
              offset        = iterators[1] - iterators[0];

              if (offset < sublength) {
                if (length + (sublength - offset) > sizeof(*computation) / sizeof(char))
                return nullptr;

                for (index = length; index-- != static_cast<std::size_t>(iterators[1] - *computation); )
                  (*computation)[index + (sublength - offset)] = (*computation)[index];

                iterators[1] += sublength - offset;
                length       += sublength - offset;
              }

              iterator = const_cast<char*>(iterators[0]);

              for (index = 0u; index != sublength; ++index)
              iterator[index] = subcomputation[index];

              for (index = 0u; ; ++index) {
                iterator[index + sublength] = iterators[1][index];
                if ('\0' == iterators[1][index]) break;
              }
            }

            break;
          }

          if ('\0' == iterator[index] or iterator[index] != token[index])
          break;
        }
      }

      // …
      return *computation;
    }

    constexpr static char const* tokenof(operation_t const operation) noexcept {
      switch (operation) {
        case min::add                : return "+";
        case min::bitwise_and        : return "&";
        case min::bitwise_or         : return "|";
        case min::bitwise_shift_left : return "<<";
        case min::bitwise_shift_right: return ">>";
        case min::bitwise_xor        : return "^";
        case min::divide             : return "/";
        case min::exponentiate       : return "**";
        case min::modulo             : return "%";
        case min::multiply           : return "*";
        case min::subtract           : return "-";

        default:
          return nullptr;
      }
    }
  };

  /* … */
  typedef typename min::operation_t operation_t;

  bool                assertion                                                            = true;                                        // ->> "Can `computation` derive `value` from `values` using `operations`?"
  bool                concatenable                                                         = false;                                       // --> min::concatenate in operations
  char                expression        [min::lengthof(SIZE_MAX /* -->    value  */) + 1u] = {'0', '\0'};                                 // ->> `value`  representation
  char                expressions[count][min::lengthof(SIZE_MAX /* --> ...values */) + 1u] = {};                                          // ->> `values` representations
  unsigned char const length                                                               = min::lengthof(value);                        //
  std::size_t         sublength                                                            = 0u;                                          // ->> Minimum length of `computation`, or length of `min_expression`
  bool                operable                                                             = false;                                       // --> only min::concatenate in operations
  operation_t const   operations[]                                                         = {min::concatenate, min::add, min::multiply}; //

  struct {
    std::size_t                                                             length;
    struct { char const *value[min::maximum + 1u]; operation_t operation; } value[0u == min::arity ? 1u : static_cast<std::size_t>(min::arity)];
  } sequence = {1u, {
    {{*expressions, nullptr}, min::concatenate}
  }};

  char subcomputation[(SIZE_MAX / min::maximum >= capacity / 2u ? (capacity >= 2u ? capacity / 2u : 1u) * min::maximum : capacity) + 1u] = {};

  // … ->> Assert pre-conditions
  assertion = 0u != min::arity;

  if (assertion) {
    assertion = false;

    for (operation_t const *operation = operations; operation != operations + (sizeof(operations) / sizeof(operation_t)); ++operation)
    if (min::concatenate == *operation or nullptr != min::tokenof(*operation)) { assertion = true; break; }
  }

  if (assertion) {
    assertion = false;

    for (std::size_t index = count; index--; )
    if (0u != values[index] and value >= values[index]) { assertion = true; break; }
  }

  if (not assertion)
  return min::nullify(computation);

  // … --> concatenable | operable = …
  for (operation_t const *operation = operations + (sizeof(operations) / sizeof(operation_t)); operation != operations; ) {
    --operation;

    if (min::concatenate == *operation)      concatenable = true;
    if (nullptr != min::tokenof(*operation)) operable     = true;
  }

  // … --> expression = …
  expression[length] = '\0';
  
  for (std::size_t divisor = 1u, sublength = length; sublength--; divisor *= min::radix)
  expression[sublength] = "0123456789abcdefghijklmnopqrstuvwxyz"[(value / divisor) % min::radix];
    
  // … --> expressions = …
  for (std::size_t index = count; index--; ) {
    char       *expression = expressions[index];
    std::size_t value      = values     [index];

    // …
    *expression = '0';
    expression += min::lengthof(value);
    *expression = '\0';
    
    for (; value; value /= min::radix)
    *--expression = "0123456789abcdefghijklmnopqrstuvwxyz"[value % min::radix];
  }

  // … ->> Permute through a combination of allowed `operations` until the estimated result exceeds/ matches the target `value` (range) or until the `sequence` of `operations` is fully explored
  for (std::size_t step = 0u; limit == static_cast<std::size_t>(-1) or limit != step; ++step) {
    bool permuted = false;

    /* … --> computation = sequence */ {
      std::size_t index    = 0u;
      char       *iterator = *computation;

      for (*iterator = '\0'; index != sequence.length; ++index, *iterator = '\0')
      switch (sequence.value[index].operation) {
        case min::concatenate: {
          for (char const *const *value = sequence.value[index].value; nullptr != *value; ++value)
          for (char const *expression = *value; '\0' != *expression; ++expression)
            *(iterator++) = *expression;
        } break;

        case min::add        : *(iterator++) = '+'; break;
        case min::bitwise_and: *(iterator++) = '&'; break;
        case min::bitwise_or : *(iterator++) = '|'; break;
        case min::bitwise_xor: *(iterator++) = '^'; break;
        case min::divide     : *(iterator++) = '/'; break;
        case min::modulo     : *(iterator++) = '%'; break;
        case min::multiply   : *(iterator++) = '*'; break;
        case min::subtract   : *(iterator++) = '-'; break;

        case min::bitwise_shift_left : iterator[0] = iterator[1] = '<'; iterator += 2; break;
        case min::bitwise_shift_right: iterator[0] = iterator[1] = '>'; iterator += 2; break;
        case min::exponentiate       : iterator[0] = iterator[1] = '*'; iterator += 2; break;

        default:
          return min::nullify(computation);
      }
    }

    // … --> subcomputation = resultof(…, computation)
    if (nullptr == min::resultof(&subcomputation, *computation))
    return min::nullify(computation);

    // … --> expression == subcomputation
    for (std::size_t index = 0u; expression[index] == subcomputation[index]; ++index)
    if ('\0' == expression[index] and '\0' == subcomputation[index]) {
      if (min::eager) {
        for (index = 0u; '\0' != (*computation)[index]; ) ++index;
        if (0u != sublength and index > sublength) return min::nullify(computation);

        sublength = index;
      }

      if (rank--) break;
      return *computation;
    }

    // … ->> Next `sequence`
    for (std::size_t index = sequence.length - 1u; ; index -= 2u) {
      operation_t const *operation = operations;
      std::size_t        subcount  = 0u;
      char const       **subvalue  = sequence.value[index].value;

      // …
      for (; operation != operations + (sizeof(operations) / sizeof(operation_t)); ++operation) {
        if (nullptr != min::tokenof(*operation))
        break;
      }

      for (; nullptr != *subvalue; ++subcount)                                                             ++subvalue;
      for (--subvalue; *subvalue == expressions[count - 1u] and subvalue != sequence.value[index].value; ) --subvalue;

      // …
      if (*subvalue != expressions[count - 1u]) {
        for (char const (*expression)[min::lengthof(SIZE_MAX /* --> ...values */) + 1u] = expressions; ; ++expression)
        if (*subvalue == expression[0]) {
          *subvalue = expression[1];
          break;
        }

        for (++subvalue; nullptr != *subvalue; ++subvalue)
        *subvalue = *expressions;

        permuted = true;
      }

      if (concatenable and not permuted) {
        unsigned char sublength = min::lengthof(*values);

        // … ->> `sublength` is the smallest-sized expression of all `expressions`
        for (char const (*expression)[min::lengthof(SIZE_MAX /* --> ...values */) + 1u] = expressions + count; expression != expressions; ) {
          unsigned char length = 0u;

          // …
          --expression;

          while ('\0' != (*expression)[length]) length   += 1u;
          if (length < sublength)               sublength = length;
        }

        // … ->> Concatenate
        if (subcount * sublength < length and subcount * sublength < min::maximum) {
          for (std::size_t index = 0u; count != index; ++index)
          if (0u != values[index]) {
            *subvalue = expressions[index];
            break;
          }

          for (++subvalue; nullptr != *subvalue; ++subvalue)
            *subvalue = *expressions;

          permuted    = true;
          subvalue[0] = *expressions;
          subvalue[1] = nullptr;
        }
      }

      if (operable and not permuted) {
        if (0u == index) {
          permuted                   = true;
          sequence.length           += 2u;
          sequence.value -> value[0] = *expressions;
          sequence.value -> value[1] = nullptr;

          if (min::arity < sequence.length)
          return min::nullify(computation);
        }

        else {
          operation_t const *suboperation = operation;

          // …
          while (*suboperation != sequence.value[index - 1u].operation)
            ++suboperation;

          for (++suboperation; suboperation != operations + (sizeof(operations) / sizeof(operation_t)); ++suboperation) {
            if (nullptr != min::tokenof(*suboperation))
            break;
          }

          if (suboperation != operations + (sizeof(operations) / sizeof(operation_t))) {
            permuted                             = true;
            sequence.value[index - 0u].value[0]  = *expressions;
            sequence.value[index - 0u].value[1]  = nullptr;
            sequence.value[index - 1u].operation = *suboperation;
          }
        }
      }

      // …
      if (permuted) {
        for (++index; index != sequence.length; ++index) {
          sequence.value[index].operation = 0u == index % 2u ? min::concatenate : *operation;
          sequence.value[index].value[0]  = *expressions;
          sequence.value[index].value[1]  = nullptr;
        }

        break;
      }

      if (0u == index)
      return min::nullify(computation);
    }
  }

  // …
  return min::nullify(computation);
}


/* Main */
int main(int, char*[]) /* noexcept */ {
  char              expression    [512] = {'\0'};
  std::size_t const initial_values[]    = {2u, 3u};
  std::size_t const target              = 6u;

  // … ->> Minimal uses
  (void) std::fprintf(stdout, "%zu = %s" "\r\n", target, ::min_expression(&expression, 100002u, {0u, 1u}));
  (void) std::fprintf(stdout, "%zu = %s" "\r\n", target, ::min_expression(&expression, 100002u, {0u, 1u}, 0u));
  (void) std::fprintf(stdout, "%zu = %s" "\r\n", target, ::min_expression(&expression, 100002u, {0u, 1u}, 1u));
  (void) std::fprintf(stdout, "%zu = %s" "\r\n", target, ::min_expression(&expression, 100002u, {0u, 1u}, 1u, 4290u - 1u));
  (void) std::fputc('\n', stdout);

  // … ->> Extended use
  for (std::size_t count = 0u; ; ++count) {
    if (nullptr == ::min_expression(&expression, target, initial_values, count)) {
      if (0u == count)
      (void) std::fputs("no expression found", stderr);

      break;
    }

    (void) std::fprintf(stdout, "%zu = %s" "\r\n", target, expression);
  }
}
