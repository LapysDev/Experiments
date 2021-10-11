#include <cstdio>
#include <type_traits>
#include <utility>

/* ... */
enum operation {
  minus,
  multiply
};

template <operation, typename...> struct expression;
template <typename> class operand;
template <unsigned char> struct parameter;
template <typename> struct value;

/* ... */
template <typename type>
struct expression<operation::minus, operand<type> > final {
  private:
    operand<type> const operand;

  public:
    constexpr expression(type const& operand) noexcept :
      operand(operand)
    {}

    template <typename... types>
    constexpr auto operator ()(types&&... arguments) const noexcept ->
      decltype(-(this -> operand.evaluate().operator ()(std::forward<types>(arguments)...)))
    { return -(this -> operand.evaluate().operator ()(std::forward<types>(arguments)...)); }
};

template <typename typeA, typename typeB>
struct expression<operation::multiply, operand<typeA>, operand<typeB> > final {
  private:
    operand<typeA> const operandA;
    operand<typeB> const operandB;

  public:
    constexpr expression(typeA const& operandA, typeB const& operandB) noexcept :
      operandA(operandA), operandB(operandB)
    {}

    template <typename... types>
    constexpr auto operator ()(types&&... arguments) const noexcept ->
      decltype(
        this -> operandA.evaluate().operator ()(std::forward<types>(arguments)...) *
        this -> operandB.evaluate().operator ()(std::forward<types>(arguments)...)
      )
    {
      return (
        this -> operandA.evaluate().operator ()(std::forward<types>(arguments)...) *
        this -> operandB.evaluate().operator ()(std::forward<types>(arguments)...)
      );
    }
};

// ...
template <typename>
class operand;

template <operation operation, typename... types>
class operand<expression<operation, types...> > final {
  template <enum operation, typename...>
  friend struct expression;

  expression<operation, types...> const &value;

  // ...
  constexpr operand(expression<operation, types...> const& expression) noexcept : value(expression) {}
  constexpr expression<operation, types...> const& evaluate() const noexcept { return this -> value; }
};

template <unsigned char index>
class operand<parameter<index> > final {
  template <enum operation, typename...>
  friend struct expression;

  // ...
  constexpr operand(parameter<index> const) noexcept {}
  constexpr parameter<index> evaluate() const noexcept { return {}; }
};

template <typename type>
class operand<value<type> > final {
  template <enum operation, typename...>
  friend struct expression;

  ::value<type> const value;

  // ...
  constexpr operand(::value<type> const value) noexcept :
    value(value)
  {}

  constexpr ::value<type> evaluate() const noexcept {
    return this -> value;
  }
};

// ...
template <unsigned char index>
struct parameter final {
  private:
    template <typename>
    class to_function;

    template <typename type, typename... types>
    class to_function<type (types...)> final {
      friend struct parameter<index>;
      constexpr static type value(types... arguments) noexcept {
        return parameter<index>{}.operator ()(arguments...);
      }
    };

    #if __cplusplus >= 201703L
      template <typename type, typename... types>
      class to_function<type (types...) noexcept> final {
        friend struct parameter<index>;
        constexpr static type value(types... arguments) noexcept {
          return parameter<index>{}.operator ()(arguments...);
        }
      };
    #endif

    // ...
    template <unsigned char count, typename type, typename... types>
    constexpr typename std::enable_if<0u == count, type&&>::type operator ()(type&& argument, types&&...) const noexcept {
      return std::forward<type>(argument);
    }

    template <unsigned char count, typename type, typename... types>
    constexpr auto operator ()(type&&, types&&... arguments) const noexcept ->
      decltype(this -> template operator ()<count - 1u>(std::forward<types>(arguments)...))
    { return this -> template operator ()<count - 1u>(std::forward<types>(arguments)...); }

  public:
    template <typename... types>
    constexpr auto operator ()(types&&... arguments) const noexcept ->
      decltype(this -> operator ()<index>(std::forward<types>(arguments)...))
    { return this -> operator ()<index>(std::forward<types>(arguments)...); }

    template <typename type>
    constexpr operator type() const noexcept {
      return &parameter<index>::to_function<typename std::remove_reference<typename std::remove_pointer<type>::type>::type>::value;
    }
};

// ...
template <typename type>
struct value final {
  private:
    type const reference;

  public:
    constexpr value(type const value) noexcept :
      reference(value)
    {}

    template <typename... types>
    constexpr type operator ()(types&&...) const noexcept {
      return this -> reference;
    }
};

/* ... */
// [-x]
template <operation operation, typename... types>
constexpr expression<operation::minus, operand<expression<operation, types...>> > operator -(expression<operation, types...> const& expression) noexcept {
  return {expression};
}

template <unsigned char index>
constexpr expression<operation::minus, operand<parameter<index> > > operator -(parameter<index> const parameter) noexcept {
  return {parameter};
}

// [x * y]
template <operation operationA, operation operationB, typename... typesA, typename... typesB>
constexpr expression<operation::multiply, operand<expression<operationA, typesA...> >, operand<expression<operationB, typesB...> > > operator *(expression<operationA, typesA...> const& expressionA, expression<operationB, typesB...> const& expressionB) noexcept {
  return {expressionA, expressionB};
}

template <operation operation, unsigned char index, typename... types>
constexpr expression<operation::multiply, operand<expression<operation, types...> >, operand<parameter<index> > > operator *(expression<operation, types...> const& expression, parameter<index> const parameter) noexcept {
  return {expression, parameter};
}

template <operation operation, typename type, typename... types>
constexpr expression<operation::multiply, operand<expression<operation, types...> >, operand<value<type> > > operator *(expression<operation, types...> const& expression, type&& value) noexcept {
  return {expression, {std::forward<type>(value)}};
}

template <operation operation, unsigned char index, typename... types>
constexpr expression<operation::multiply, operand<parameter<index> >, operand<expression<operation, types...> > > operator *(parameter<index> const parameter, expression<operation, types...> const& expression) noexcept {
  return {parameter, expression};
}

template <unsigned char indexA, unsigned char indexB>
constexpr expression<operation::multiply, operand<parameter<indexA> >, operand<parameter<indexB> > > operator *(parameter<indexA> const parameterA, parameter<indexB> const parameterB) noexcept {
  return {parameterA, parameterB};
}

template <unsigned char index, typename type>
constexpr expression<operation::multiply, operand<parameter<index> >, operand<value<type> > > operator *(parameter<index> const parameter, type&& value) noexcept {
  return {parameter, {std::forward<type>(value)}};
}

template <operation operation, typename type, typename... types>
constexpr expression<operation::multiply, operand<value<type> >, operand<expression<operation, types...> > > operator *(type&& value, expression<operation, types...> const& expression) noexcept {
  return {{std::forward<type>(value)}, expression};
}

template <unsigned char index, typename type>
constexpr expression<operation::multiply, operand<value<type> >, operand<parameter<index> > > operator *(type&& value, parameter<index> const parameter) noexcept {
  return {{std::forward<type>(value)}, parameter};
}

/* ... */
constexpr parameter<0u> _1 {};
constexpr parameter<1u> _2 {};

/* Main */
int main() {
  int x = 2;

  std::printf("[]: %i" "\r\n", _1(1));
  std::printf("[]: %i" "\r\n", (_1 * x)(1));
  std::printf("[]: %i" "\r\n", ((-_1) * x)(1));
  std::printf("[]: %i" "\r\n", ((_1 * x) * x)(1));
}
