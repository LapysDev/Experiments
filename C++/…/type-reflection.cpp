#include <ciso646>
#if defined _MSVC_LANG
# if _MSVC_LANG +0 >= 202002L
#   include <version>
# endif
#elif __cplusplus >= 202002L or defined __apple_build_version__ or defined __clang__ or defined __clang_major__ or defined __clang_minor__ or defined __clang_patchlevel__ or defined __clang_version__ or defined __CUDACC_VER_BUILD__ or defined __CUDACC_VER_MAJOR__ or defined __CUDACC_VER_MINOR__ or defined __ECC or defined __GNUC__ or defined __GNUC_MINOR__ or defined __GNUC_PATCHLEVEL__ or defined __ICC or defined __ICL or defined __INTEL_COMPILER or defined __INTEL_COMPILER_BUILD_DATE or defined __INTEL_LLVM_COMPILER or defined __NVCC__ or defined __NVCOMPILER or defined _MSC_BUILD or defined _MSC_FULL_VER or defined _MSC_VER
# include <version>
#endif

/* ... */
struct reflect /* final */ {
  enum /* : unsigned char */ { const  = 0x1u, volatile = 0x2u                 }; // --> reflinfo::cv
  enum /* : unsigned char */ { copy   = 0x1u, create   = 0x2u, destroy = 0x4u }; // --> reflinfo::trivial
  enum /* : unsigned char */ { lvalue = 0x1u, rvalue   = 0x2u                 }; // --> reflinfo::reference

  // ...
  void* (*const constructor)(void*, reflparams); // FIGURE OUT COPY-/ ZERO-CONSTRUCTOR
  void  (*const destructor) (void*, ...); // ALSO CARRY PARAMETERS LIKE CONSTRUCTORS
  struct proxy {}; // -> add, assign, increment, plus

  reflproxy proxy = refl(int).proxy;
  bool proxy::add(&2, &2, &result);
  B operator +(A, A) == reflexpr(*(A*) … + *(A const [volatile]*) …).constructor(&result, copy)

  constructor(&…, 2, 3.5)
  constructor(&…, reflparams(2, 3.5))

  std::size_t   alignment; // --> alignof base
  bool          array;     // ->> Falsy for pointer-/ reference-to-arrays
  unsigned char cv;        //
  bool          except;    //
  bool          function;  // ->> Falsy for pointer-/ reference-to-functions
  void        (*id)();     //
  std::size_t   length;    // ->> Zero for unbounded arrays, non-zero for bounded arrays
  bool          member;    //
  bool          pointer;   //
  unsigned char reference; //
  std::size_t   size;      // --> sizeof base
  unsigned char trivial;   //

  // ->> `refl(…)` for non-`void` types (2nd step)
  template <typename type> operator type               &() { return static_cast<type               &>(*(type*) static_cast<void*>(this)); }
  template <typename type> operator type const         &() { return static_cast<type const         &>(*(type*) static_cast<void*>(this)); }
  template <typename type> operator type const volatile&() { return static_cast<type const volatile&>(*(type*) static_cast<void*>(this)); }
  template <typename type> operator type       volatile&() { return static_cast<type       volatile&>(*(type*) static_cast<void*>(this)); }
  #ifdef __cpp_rvalue_references // --> 200610L
    template <typename type> operator type               &&() { return static_cast<type               &&>(*(type*) static_cast<void*>(this)); }
    template <typename type> operator type const         &&() { return static_cast<type const         &&>(*(type*) static_cast<void*>(this)); }
    template <typename type> operator type const volatile&&() { return static_cast<type const volatile&&>(*(type*) static_cast<void*>(this)); }
    template <typename type> operator type       volatile&&() { return static_cast<type       volatile&&>(*(type*) static_cast<void*>(this)); }
  #endif
};

template <typename base, bool = true>
struct reflinfo /* final */ : public reflect {
  typedef ...  base; // int* -> int
  typedef base type;

  private:
  public:
    #ifdef __cpp_constexpr // --> 200704L
      constexpr
    #endif
    operator reflect() const {
      reflect reflection = {
      };
      return reflection;
    }
};

template <typename base>
struct reflinfo<base, false> /* final */ {
  operator reflect() const {
    reflect reflection = {};
    return reflection;
  }
};

typedef struct reflect::proxy reflproxy;
  // ->> `refl(…)` for non-`void` types (1st step)
  reflect operator +(reflect);

  // ->> `refl(…)` for non-`void` types (3rd step)
  #ifdef __cpp_rvalue_references // --> 200610L
    template <typename type>
    friend reflinfo<type&&> operator ,(reflect, type&&) {
      return reflinfo<type&&>();
    }
  #else
    template <typename type> friend reflinfo<type               &> operator ,(reflect, type               &) { return reflinfo<type               &>(); }
    template <typename type> friend reflinfo<type const         &> operator ,(reflect, type const         &) { return reflinfo<type const         &>(); }
    template <typename type> friend reflinfo<type const volatile&> operator ,(reflect, type const volatile&) { return reflinfo<type const volatile&>(); }
    template <typename type> friend reflinfo<type       volatile&> operator ,(reflect, type       volatile&) { return reflinfo<type       volatile&>(); }
  #endif

  // ->> `refl(…)` for non-`void` types (4th step)
  template <typename type>
  reflinfo<type> operator ,(reflinfo<type>, reflinfo<void>) {
    return reflinfo<type>();
  }

  // ->> `refl(…)` for expressions (1st step)
  #ifdef __cpp_rvalue_references // --> 200610L
    template <typename type>
    reflinfo<type&&> operator +(type&&, reflect);
  #else
    template <typename type> reflinfo<type               &> operator +(type               &, reflect);
    template <typename type> reflinfo<type const         &> operator +(type const         &, reflect);
    template <typename type> reflinfo<type const volatile&> operator +(type const volatile&, reflect);
    template <typename type> reflinfo<type       volatile&> operator +(type       volatile&, reflect);
  #endif

  // ->> `refl(…)` for expressions (2nd step)
  template <typename type>
  reflinfo<type> operator ,(reflect, reflinfo<type>);

#if defined _MSC_VER or /* --> 200707L */ defined __cpp_decltype
# define refl(value)     (reflect) decltype(reflect(), (value) +reflect(), reflinfo<void>())()
# define reflexpr(value) (reflect) decltype(reflect(), (value),            reflinfo<void>())()
# define reflid(value)   (reflect) decltype(reflect(), (value)  reflect(), reflinfo<void>())()
#elif defined __GNUC__
# define refl(value)     (reflect) __decltype(reflect(), (value) +reflect(), reflinfo<void>())()
# define reflexpr(value) (reflect) __decltype(reflect(), (value),            reflinfo<void>())()
# define reflid(value)   (reflect) __decltype(reflect(), (value)  reflect(), reflinfo<void>())()
#elif defined __clang__
# define refl(value)     (reflect) typename reflinfo<__typeof__(reflect(), (value) +reflect(), reflinfo<void>())>::type()
# define reflexpr(value) (reflect) typename reflinfo<__typeof__(reflect(), (value),            reflinfo<void>())>::type()
# define reflid(value)   (reflect) typename reflinfo<__typeof__(reflect(), (value)  reflect(), reflinfo<void>())>::type()
#else
# define refl(value)     (reflect) reflinfo<void, false>()
# define reflexpr(value) (reflect) reflinfo<void, false>()
# define reflid(value)   (reflect) (reflect(), (value) reflect(), reflinfo<void>())
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
