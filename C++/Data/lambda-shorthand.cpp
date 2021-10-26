#include <cstdio>
#include <type_traits>
#include <utility>

#define private public
/* ... */
union lambda {
  public:
    enum operation { multiply, nop };

    template <typename base, base, bool> union constant;
    template <bool, enum lambda::operation, class...> struct expression;
    template <unsigned char> union parameter;
    template <typename, bool> struct value;

  private:
};

// ...
template <typename base, base value, bool invocable>
union lambda::constant {};

// ...
template <bool determinable, class base, class... bases>
struct lambda::expression<determinable, lambda::nop, base, bases...> : protected lambda::expression<determinable, lambda::nop, bases...> {};

template <bool determinable>
struct lambda::expression<determinable, lambda::nop> {};

// ...
template <unsigned char index>
union lambda::parameter {};

// ...
template <typename base, bool invocable>
struct lambda::value final {
  template <bool, enum lambda::operation, class...>
  friend struct expression;

  private:
    base const evaluation;

    template <bool subinvocable>
    constexpr inline value(lambda::value<base, subinvocable> const& value) noexcept :
      evaluation(value.evaluation)
    {}

    // ...
    template <typename... types>
    constexpr typename std::enable_if<false == invocable, base>::type evaluate(types&&...) const noexcept {
      return this->evaluation;
    }

    template <typename... types>
    constexpr auto evaluate(types&&... arguments) const noexcept(noexcept(this->evaluation(std::forward<types>(arguments)...))) -> typename std::enable_if<invocable, decltype(this->evaluation(std::forward<types>(arguments)...))>::type {
      return this->evaluation(std::forward<types>(arguments)...);
    }

  public:
    template <typename type>
    constexpr inline value(type&& value) noexcept :
      evaluation(std::forward<type>(value))
    {}

    // ...
    constexpr friend lambda::value<typename std::remove_reference<base>::type, invocable> _c(lambda::value<base, invocable> const& value) noexcept {
      return {value.evaluation};
    }

    constexpr friend lambda::value<base, true> _f(lambda::value<base, invocable> const& value) noexcept {
      return {};
    }
};

/* ... */
constexpr lambda::parameter<0u> const _1;
constexpr lambda::parameter<1u> const _2;

// ...
template <typename type, type value>
constexpr lambda::constant<type, value, false> _t() noexcept {
  return {};
}

template <typename type>
constexpr lambda::value<type, false> _v(type&& argument) noexcept {
  return {std::forward<type>(argument)};
}

/* Main */
int function() { return 42; }
int variable = 42;

// ...
int main() {
  std::printf("[]: %i" "\r\n", _c(_v<int const&>(1)).evaluation);
  std::printf("[]: %i" "\r\n", _c(_v<int&&>(1)).evaluation);
  static_cast<void>(_1);
  static_cast<void>(_2);
  static_cast<void>(function);
  static_cast<void>(variable);
  // _1 * _2;
  // _1 * 42;
  // _1 * function;
  // _1 * variable;
  // _1 * (_1 * _2);
  // _1 * _t<int, 42>();
  // _1 * _t<int (&)(), function>();

  // _1 * _f(_2);
  // _1 * _f(42);
  // _1 * _f(function);
  // _1 * _f(variable);
  // _1 * _f(_1 * _2);
  // _1 * _f(_t<int, 42>());
  // _1 * _f(_t<int (), function>());
}
