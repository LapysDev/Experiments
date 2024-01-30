template <typename base>
struct nil final {
  private:
    template <typename subbase, typename = subbase>
    struct valueof final {
      friend struct nil;

      static_assert(0u != sizeof(subbase), "Incompatible type specified for trait `nil`");
      private: static base const value;
    };

    template <typename subbase>
    struct valueof<subbase, decltype(subbase(0))> final {
      friend struct nil;
      private: constexpr static base value = 0;
    };

  public:
    constexpr static base value = valueof<base>::value;
};

template <typename base>                    struct nil<base*>                                 final { constexpr static base *          value                 = NULL; };
template <typename base>                    struct nil<base* const>                           final { constexpr static base *          value                 = NULL; };
template <typename base>                    struct nil<base* const volatile>                  final { constexpr static base *volatile  value                 = NULL; };
template <typename base>                    struct nil<base*       volatile>                  final { constexpr static base *volatile  value                 = NULL; };
template <typename base, typename... bases> struct nil<base (*)              (bases...)>      final { constexpr static base (*         value)(bases...)      = nullptr; };
template <typename base, typename... bases> struct nil<base (*)              (bases..., ...)> final { constexpr static base (*         value)(bases..., ...) = nullptr; };
template <typename base, typename... bases> struct nil<base (*const)         (bases...)>      final { constexpr static base (*         value)(bases...)      = nullptr; };
template <typename base, typename... bases> struct nil<base (*const)         (bases..., ...)> final { constexpr static base (*         value)(bases..., ...) = nullptr; };
template <typename base, typename... bases> struct nil<base (*const volatile)(bases...)>      final { constexpr static base (*volatile value)(bases...)      = nullptr; };
template <typename base, typename... bases> struct nil<base (*const volatile)(bases..., ...)> final { constexpr static base (*volatile value)(bases..., ...) = nullptr; };
template <typename base, typename... bases> struct nil<base (*      volatile)(bases...)>      final { constexpr static base (*volatile value)(bases...)      = nullptr; };
template <typename base, typename... bases> struct nil<base (*      volatile)(bases..., ...)> final { constexpr static base (*volatile value)(bases..., ...) = nullptr; };
#ifdef __cpp_noexcept_function_type
  template <typename base, typename... bases> struct nil<base (*)              (bases...)      noexcept> final { constexpr static base (*         value)(bases...)      noexcept = nullptr; };
  template <typename base, typename... bases> struct nil<base (*)              (bases..., ...) noexcept> final { constexpr static base (*         value)(bases..., ...) noexcept = nullptr; };
  template <typename base, typename... bases> struct nil<base (*const)         (bases...)      noexcept> final { constexpr static base (*         value)(bases...)      noexcept = nullptr; };
  template <typename base, typename... bases> struct nil<base (*const)         (bases..., ...) noexcept> final { constexpr static base (*         value)(bases..., ...) noexcept = nullptr; };
  template <typename base, typename... bases> struct nil<base (*const volatile)(bases...)      noexcept> final { constexpr static base (*volatile value)(bases...)      noexcept = nullptr; };
  template <typename base, typename... bases> struct nil<base (*const volatile)(bases..., ...) noexcept> final { constexpr static base (*volatile value)(bases..., ...) noexcept = nullptr; };
  template <typename base, typename... bases> struct nil<base (*      volatile)(bases...)      noexcept> final { constexpr static base (*volatile value)(bases...)      noexcept = nullptr; };
  template <typename base, typename... bases> struct nil<base (*      volatile)(bases..., ...) noexcept> final { constexpr static base (*volatile value)(bases..., ...) noexcept = nullptr; };
#endif
template <class object, typename base> struct nil<base object::*>                final { constexpr static base object:: *         value = NULL; };
template <class object, typename base> struct nil<base object::* const>          final { constexpr static base object:: *         value = NULL; };
template <class object, typename base> struct nil<base object::* const volatile> final { constexpr static base object:: *volatile value = NULL; };
template <class object, typename base> struct nil<base object::*       volatile> final { constexpr static base object:: *volatile value = NULL; };
template <>                            struct nil<std::nullptr_t>                final { constexpr static std::nullptr_t          value = nullptr; };
