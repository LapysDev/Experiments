#include <cstdio>

/* ... */
template <typename base, bool immutability = false, bool lvalue = false, bool rvalue = false, bool volatility = false>
struct ctti /* final */ {
  private:
    template <bool = immutability, bool = lvalue, bool = rvalue, bool = volatility, int = 0>
    struct subqualifiersof;
  
    template <int specialization> struct subqualifiersof<false, false, false, false, specialization> { static char const (&valueof())[4]  { return "..." ""            "" "";   } };
    template <int specialization> struct subqualifiersof<false, true,  false, false, specialization> { static char const (&valueof())[2]  { return ""    ""            "" "&";  } };
    template <int specialization> struct subqualifiersof<false, false, true,  false, specialization> { static char const (&valueof())[3]  { return ""    ""            "" "&&"; } };
    template <int specialization> struct subqualifiersof<true,  false, false, false, specialization> { static char const (&valueof())[6]  { return ""    "const"       "" "";   } };
    template <int specialization> struct subqualifiersof<true,  true,  false, false, specialization> { static char const (&valueof())[7]  { return ""    "const"       "" "&";  } };
    template <int specialization> struct subqualifiersof<true,  false, true,  false, specialization> { static char const (&valueof())[8]  { return ""    "const"       "" "&&"; } };
    template <int specialization> struct subqualifiersof<true,  false, false, true,  specialization> { static char const (&valueof())[15] { return ""    "const volatile" "";   } };
    template <int specialization> struct subqualifiersof<true,  true,  false, true,  specialization> { static char const (&valueof())[16] { return ""    "const volatile" "&";  } };
    template <int specialization> struct subqualifiersof<true,  false, true,  true,  specialization> { static char const (&valueof())[17] { return ""    "const volatile" "&&"; } };
    template <int specialization> struct subqualifiersof<false, false, false, true,  specialization> { static char const (&valueof())[9]  { return ""    ""    "volatile" "";   } };
    template <int specialization> struct subqualifiersof<false, true,  false, true,  specialization> { static char const (&valueof())[10] { return ""    ""    "volatile" "&";  } };
    template <int specialization> struct subqualifiersof<false, false, true,  true,  specialization> { static char const (&valueof())[11] { return ""    ""    "volatile" "&&"; } };

  public:
    static char const (&qualifiersof())[sizeof(subqualifiersof<>::valueof()) / sizeof(char)] {
      return subqualifiersof<>::valueof();
    }
};

template <typename base, bool immutability, bool lvalue, bool rvalue, bool volatility>
struct ctti<base const, immutability, lvalue, rvalue, volatility> : ctti<base, true, lvalue, rvalue, volatility> {};

template <typename base, bool immutability, bool lvalue, bool rvalue, bool volatility>
struct ctti<base const volatile, immutability, lvalue, rvalue, volatility> : ctti<base, true, lvalue, rvalue, true> {};

template <typename base, bool immutability, bool lvalue, bool rvalue, bool volatility>
struct ctti<base volatile, immutability, lvalue, rvalue, volatility> : ctti<base, immutability, lvalue, rvalue, true> {};

template <typename base, bool immutability, bool lvalue, bool rvalue, bool volatility>
struct ctti<base&, immutability, lvalue, rvalue, volatility> : ctti<base, immutability, true, rvalue, volatility> {};

#if __cplusplus >= 201103L // --> __cpp_rvalue_reference
  template <typename base, bool immutability, bool lvalue, bool rvalue, bool volatility>
  struct ctti<base&&, immutability, lvalue, rvalue, volatility> : ctti<base, immutability, lvalue, true, volatility> {};
#endif

// ... ->> Perfect forwarding system used in Lapys C++
#if __cplusplus < 201103L // --> __cpp_rvalue_reference
  template <typename type>
  void function(type const&) {
    std::puts(ctti<type const&>::qualifiersof());
  }
#else
  template <typename type>
  void function(type&&) {
    std::puts(ctti<type&&>::qualifiersof());
  }
#endif

#if __cplusplus < 201103L // --> __cpp_rvalue_reference ->>
  // With    this, `function<T>()` always `volatile`-qualifies non-cv `T&`
  // Without this, `function<T>()` always `const`   -qualifies        `T`
  void function(int volatile&) {
    std::puts(ctti<int volatile&>::qualifiersof());
  }
#endif

/* Main */
int main(int, char*[]) /* noexcept */ {
  #if __cplusplus < 201103L // --> __cpp_rvalue_reference
    function(static_cast<int>(0));                                          // --> int const         & | int const         &
    function(const_cast <int               &>(static_cast<int const&>(0))); // --> int       volatile& | int const         &
    function(const_cast <int const         &>(static_cast<int const&>(0))); // --> int const         & | int const         &
    function(const_cast <int const volatile&>(static_cast<int const&>(0))); // --> int const volatile& | int const volatile&
    function(const_cast <int       volatile&>(static_cast<int const&>(0))); // --> int       volatile& | int const volatile&
  #else
    function(static_cast<int>(0));                                            // --> int               &&
    function(const_cast <int               &> (static_cast<int const&> (0))); // --> int               &
    function(const_cast <int const         &> (static_cast<int const&> (0))); // --> int const         &
    function(const_cast <int const volatile&> (static_cast<int const&> (0))); // --> int const volatile&
    function(const_cast <int       volatile&> (static_cast<int const&> (0))); // --> int       volatile&
    function(const_cast <int               &&>(static_cast<int      &&>(0))); // --> int               &&
    function(const_cast <int const         &&>(static_cast<int      &&>(0))); // --> int const         &&
    function(const_cast <int const volatile&&>(static_cast<int      &&>(0))); // --> int const volatile&&
    function(const_cast <int       volatile&&>(static_cast<int      &&>(0))); // --> int       volatile&&
  #endif
}
