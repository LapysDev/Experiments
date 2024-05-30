#include <cstddef>
#include <functional>
#include <new>

/* … */
struct refl;
struct reflexpr;
struct reflproxy;
struct reflval;
struct reflvalexpr;

// …
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
