template <typename... Ts>
struct overload : Ts... {
  overload(Ts const&... ts) :
    Ts(ts)...
  {}

  using Ts::operator +...;
};
