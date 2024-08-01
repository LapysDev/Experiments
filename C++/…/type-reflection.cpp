#include <ciso646>
#if defined _MSVC_LANG
# if _MSVC_LANG +0 >= 202002L
#   include <version>
# endif
#elif __cplusplus >= 202002L or defined __apple_build_version__ or defined __clang__ or defined __clang_major__ or defined __clang_minor__ or defined __clang_patchlevel__ or defined __clang_version__ or defined __CUDACC_VER_BUILD__ or defined __CUDACC_VER_MAJOR__ or defined __CUDACC_VER_MINOR__ or defined __ECC or defined __GNUC__ or defined __GNUC_MINOR__ or defined __GNUC_PATCHLEVEL__ or defined __ICC or defined __ICL or defined __INTEL_COMPILER or defined __INTEL_COMPILER_BUILD_DATE or defined __INTEL_LLVM_COMPILER or defined __NVCC__ or defined __NVCOMPILER or defined _MSC_BUILD or defined _MSC_FULL_VER or defined _MSC_VER
# include <version>
#endif

template <typename base>
union reflinfo {
  typedef base type;

  // → capture captured/ `void` types
  friend reflinfo<base> operator ,(reflinfo<base>, reflinfo<void>) {
    return reflinfo<base>();
  }
};

union refl {
  // → capture reference types (and copy-constructible non-reference types or `void`)
  // → support unary `(A) +B` over binary `(A) + B` expressions
  //   • `template <typename T> operator T();`
  friend refl operator +(refl) { return refl(); }

  template <typename type> operator type               &() { return static_cast<type               &>(*(type*) static_cast<void*>(this)); }
  template <typename type> operator type const         &() { return static_cast<type const         &>(*(type*) static_cast<void*>(this)); }
  template <typename type> operator type const volatile&() { return static_cast<type const volatile&>(*(type*) static_cast<void*>(this)); }
  template <typename type> operator type       volatile&() { return static_cast<type       volatile&>(*(type*) static_cast<void*>(this)); }
  #ifdef __cpp_rvalue_references // --> 200610L
    template <typename type> operator type               &&() { return static_cast<ype               &&>(*(type*) static_cast<void*>(this)); }
    template <typename type> operator type const         &&() { return static_cast<ype const         &&>(*(type*) static_cast<void*>(this)); }
    template <typename type> operator type const volatile&&() { return static_cast<ype const volatile&&>(*(type*) static_cast<void*>(this)); }
    template <typename type> operator type       volatile&&() { return static_cast<ype       volatile&&>(*(type*) static_cast<void*>(this)); }
  #endif

  #ifdef __cpp_rvalue_references // --> 200610L
    template <typename type>
    friend reflinfo<type&&> operator ,(refl, type&&) {
      return reflinfo<type&&>();
    }
  #else
    template <typename type> friend reflinfo<type               &> operator ,(refl, type               &) { return reflinfo<type               &>(); }
    template <typename type> friend reflinfo<type const         &> operator ,(refl, type const         &) { return reflinfo<type const         &>(); }
    template <typename type> friend reflinfo<type const volatile&> operator ,(refl, type const volatile&) { return reflinfo<type const volatile&>(); }
    template <typename type> friend reflinfo<type       volatile&> operator ,(refl, type       volatile&) { return reflinfo<type       volatile&>(); }
  #endif

  // → alias captured unary `(A) +B` expression type
  template <typename type>
  friend reflinfo<type> operator ,(refl, reflinfo<type>);

  // → capture non-`void` values
  // → support binary `(A) + B` over unary `(A) +B` expressions
  #ifdef __cpp_rvalue_references // --> 200610L
    template <typename type>
    friend reflinfo<type&&> operator +(type&&, refl);
  #else
    template <typename type> friend reflinfo<type               &> operator +(type               &, refl);
    template <typename type> friend reflinfo<type const         &> operator +(type const         &, refl);
    template <typename type> friend reflinfo<type const volatile&> operator +(type const volatile&, refl);
    template <typename type> friend reflinfo<type       volatile&> operator +(type       volatile&, refl);
  #endif
};

#define _
#define reflid(value) (refl _ (), (value) refl _ (), reflinfo<void>())
#if defined _MSC_VER or /* --> 200707L */ defined __cpp_decltype
# define refl(value)     decltype(refl(), (value) +refl(), reflinfo<void>())()
# define reflexpr(value) decltype(refl(), (value),         reflinfo<void>())()
#elif defined __GNUC__
# define refl(value)     __decltype(refl(), (value) +refl(), reflinfo<void>())()
# define reflexpr(value) __decltype(refl(), (value),         reflinfo<void>())()
#elif defined __clang__
# define refl(value)     typename reflinfo<__typeof__(refl(), (value) +refl(), reflinfo<void>())>::type()
# define reflexpr(value) typename reflinfo<__typeof__(refl(), (value),         reflinfo<void>())>::type()
#else
# define refl(value)     reflinfo<ERROR>()
# define reflexpr(value) reflinfo<ERROR>()
#endif

/* ================================= */
struct refl;
struct reflexpr;
struct reflproxy;
struct reflval;
struct reflvalexpr;

// …
struct reflproxy {
  template <class operation, typename base>
    struct can {
      template <typename type> static bool (&valueof(int, int))[sizeof operation::template value<type>(NULL, *(reflval*) NULL) + 1];
      template <typename>      static bool (&valueof(...))     [false                                                          + 1];

      // …
      static bool const value = sizeof(bool[false + 1]) != sizeof valueof<base>(0x0, 0x0);
    };
      template <bool = true, int = 0x0> struct assignof  { template <typename> static bool value(reflproxy const*, reflval, std::size_t) { return false; } };
      template <bool = true, int = 0x0> struct postincof { template <typename> static bool value(reflproxy const*, reflval, std::size_t) { return false; } };

      template <int sfinae>
      struct assignof<true, sfinae> {
        template <typename type>
        static bool value(reflproxy const* const proxy, reflval const value, std::size_t = sizeof(static_cast<void>(*static_cast<type*>(NULL) = *static_cast<type const*>(NULL)), 0)) {
          if (proxy -> reflection.id != value.reflection.id) return false;
          return proxy -> evaluate((reflvalexpr(), (*static_cast<type*>(proxy -> value) = *static_cast<type const*>(value.reflection.value)), reflexpr(), reflexpr())), true;
        }
      };

      template <int sfinae>
      struct postincof<true, sfinae> {
        template <typename type>
        static bool value(reflproxy const* const proxy, reflval const, std::size_t = sizeof(static_cast<void>((*static_cast<type*>(NULL))++), 0)) {
          return proxy -> evaluate((reflvalexpr(), (*static_cast<type*>(proxy -> value))++, reflexpr(), reflexpr())), true;
        }
      };
};

struct refl {
  template <typename T>
  static void* constructorof(void* const address, void const* const object, ...) {
    return NULL == object ? ::new (address) T() : ::new (address) T(static_cast<T const*>(object));
  }

  static void destructorof() {}

  public:
    void* (*const construct)(void*, void const*, ...);
};

struct reflexpr {
  #ifdef __cpp_rvalue_references
    template <typename type>
    friend refl operator ,(reflexpr const, type const&) {
      refl const reflection = {&refl::constructorof<type>};

      return reflection;
    }
  #endif
};

/* ============================================================================== */
struct refl {
  friend struct reflexpr;
  friend struct reflval;
  friend struct reflvalexpr;

  public:
    typedef void (*id_t)();

    // TODO -> std::less<id_t>
    void*     (*const construct)(void*, reflval, ...); // → Instanced copy constructor; TODO -> Figure if this can be template?
    void      (*const destruct) (void*,          ...); // → Instanced destructor
    reflproxy (*const proxy)    (void*, void*);        // → Instanced operator blah blah overload; should make out optional via hiding
    id_t        const id;                              //
    void             *value;                           //
    std::size_t const length;                          // → Number of elements in array type or parameters in function type, otherwise `1zu`
    std::size_t const size;                            // → Numbers of bytes occupied by type, otherwise `0zu`
    bool        const is_bounded;                      // → Bounded/ unbounded array type, otherwise `false`
    bool        const is_const;                        // → `const` type qualification
    bool        const is_lvalue;                       // → lvalue reference type qualification
    bool        const is_function;                     // → Function pointer/ reference type
    bool        const is_member;                       // → Member pointer type
    bool        const is_pointer;                      // → Function/ object pointer type
    bool        const is_rvalue;                       // → rvalue reference type qualification
    bool        const is_trivial;                      // → Trivial constructor, destructor, and layout of type
    bool        const is_union;                        // → `union` class type
    bool        const is_volatile;                     // → `volatile` type qualification

  private:
    template <typename> static void*     constructorof(void* const, reflval const, ...); //
    template <typename> static void      destructorof (void* const,                ...); //
    template <typename> static void      identityof   ();                                // → id_t
    template <typename> static reflproxy proxyof      (void* const, void* const);        //

    friend bool operator ==(refl const reflectionA, refl const reflectionB) {
      return reflectionA.id == reflectionB.id;
    }

    friend bool operator !=(refl const reflectionA, refl const reflectionB) {
      return reflectionA.id != reflectionB.id;
    }
};

struct reflexpr {
  friend refl operator ,(refl const reflection, reflexpr const) {
    return reflection;
  }

  friend refl operator ,(reflexpr const, refl const reflection) {
    return reflection;
  }

  friend refl operator ,(reflexpr const, reflexpr const) {
    refl const voidrefl = {NULL, NULL, NULL, &refl::identityof<void>, NULL};
    return voidrefl;
  }

  template <typename type>
  friend refl operator ,(reflexpr const, type const&) {
    refl const reflection = {
      &refl::constructorof<type>,
      &refl::destructorof <type>,
      &refl::proxyof      <type>,
      &refl::identityof   <type>,
      NULL
    };

    return reflection;
  }
};

struct reflvalexpr {
  template <typename type>
  friend refl operator ,(reflvalexpr const, type const& value) {
    refl const reflection = {
      &refl::constructorof<type>,
      &refl::destructorof <type>,
      &refl::proxyof      <type>,
      &refl::identityof   <type>,
      &const_cast<unsigned char&>(reinterpret_cast<unsigned char const volatile&>(value))
    };

    return reflection;
  }
};

struct reflval {
  friend struct reflproxy;

  public:
    refl const reflection;

    template <typename type>
    reflval(type const& value) : reflection((reflvalexpr(), value)) {}

  private:
    explicit reflval(refl        const reflection) : reflection(reflection) {}
    explicit reflval(reflexpr    const); // → = delete;
    explicit reflval(reflproxy   const); // → = delete;
    explicit reflval(reflvalexpr const); // → = delete;
};

struct reflproxy {
  friend struct refl;

  refl const reflection;
  struct {
    bool (*const assign) (reflproxy const*, reflval, std::size_t);
    bool (*const postinc)(reflproxy const*, reflval, std::size_t);
    // TODO → Other overload-able operators
  }        const operation;
  mutable void (*flush)(void*, ...);
  mutable void  *evaluated;
  void          *evaluation;
  void          *value;

  public:
    bool operator = (reflval const value) const { return this -> operation.assign (this, value,                       0x0u); }
    bool operator ++(int const)           const { return this -> operation.postinc(this, reflval(this -> reflection), 0x0u); }

  private:
    template <class operation, typename base>
    struct can {
      template <typename type> static bool (&valueof(int, int))[sizeof operation::template value<type>(NULL, *(reflval*) NULL) + 1];
      template <typename>      static bool (&valueof(...))     [false                                                          + 1];

      // …
      static bool const value = sizeof(bool[false + 1]) != sizeof valueof<base>(0x0, 0x0);
    };
      template <bool = true, int = 0x0> struct assignof  { template <typename> static bool value(reflproxy const*, reflval, std::size_t) { return false; } };
      template <bool = true, int = 0x0> struct postincof { template <typename> static bool value(reflproxy const*, reflval, std::size_t) { return false; } };

      template <int sfinae>
      struct assignof<true, sfinae> {
        template <typename type>
        static bool value(reflproxy const* const proxy, reflval const value, std::size_t = sizeof(static_cast<void>(*static_cast<type*>(NULL) = *static_cast<type const*>(NULL)), 0)) {
          if (proxy -> reflection.id != value.reflection.id) return false;
          return proxy -> evaluate((reflvalexpr(), (*static_cast<type*>(proxy -> value) = *static_cast<type const*>(value.reflection.value)), reflexpr(), reflexpr())), true;
        }
      };

      template <int sfinae>
      struct postincof<true, sfinae> {
        template <typename type>
        static bool value(reflproxy const* const proxy, reflval const, std::size_t = sizeof(static_cast<void>((*static_cast<type*>(NULL))++), 0)) {
          return proxy -> evaluate((reflvalexpr(), (*static_cast<type*>(proxy -> value))++, reflexpr(), reflexpr())), true;
        }
      };

    void evaluate(refl const evaluation) const {
      if (NULL != this -> evaluated && NULL != this -> flush)
        this -> flush(this -> evaluated);

      this -> evaluated = NULL != evaluation.construct && NULL != this -> evaluation ? evaluation.construct(this -> evaluation, reflval(evaluation)) : NULL;
      this -> flush     = evaluation.destruct;
    }
};
  template <typename type>
  void* refl::constructorof(void* const address, reflval const value, ...) {
    if (&identityof<type> == value.reflection.id)
      return ::new (address) type(*static_cast<type const*>(value.reflection.value));

    return NULL;
  }

  template <typename type>
  void refl::destructorof(void* const address, ...) {
    static_cast<type*>(address) -> ~type();
  }

  template <typename> // → The type template parameter should ideally not encode cv-qualifications
  void refl::identityof() {}

  template <typename type>
  reflproxy refl::proxyof(void* const source, void* const destination) {
    reflproxy const proxy = {{NULL, NULL, NULL, &refl::identityof<type>, NULL}, {
      &reflproxy::assignof <reflproxy::can<reflproxy::assignof <>, type>::value>::template value<type>,
      &reflproxy::postincof<reflproxy::can<reflproxy::postincof<>, type>::value>::template value<type>
    }, NULL, NULL, destination, source};

    return proxy;
  }

// …
#define reflof(expression) (::reflexpr(), (expression), ::reflexpr(), ::reflexpr())

/* Main */
int main(int, char*[]) {}
