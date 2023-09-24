#include <cstdio>

/* … */
template <typename base>
struct handle final {
  base value;

  private:
    struct handle_proxy final {
      handle_proxy(...) noexcept;
    };

    template <typename type = void>
    friend inline void handle_defer(handle_proxy const) noexcept {
      enum : bool { missing_handle_defer = 0u == sizeof(type*) };
      static_assert(missing_handle_defer, "Expected defined `handle_defer(...)` function");
    }

  public:
    constexpr auto defer() const
      noexcept(noexcept(handle_defer(*this))) ->
      decltype         (handle_defer(*this))
    { return handle_defer(*this); }
};

// void handle_defer(handle<int> const& handle) noexcept {
//   (void) std::printf("%1.9s%i%1.33s", "Deferred ", handle.value, " from `struct handle<int>` object");
// }

/* Main */
int main(int, char*[]) /* noexcept */ {
  typedef handle<int> int_handle;
  int_handle{42}.defer();
}
