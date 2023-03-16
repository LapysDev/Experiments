/* ...
    --- CITE ---
      #Lapys:
        - Circle:                                             https://lapys.godbolt.org/z/94fWTzdP3
        - Clang, GNU, Intel, Microsoft Visual Studio, NVIDIA: https://lapys.godbolt.org/z/WbMaKcP7c
*/
#include <cstddef>
#include <cstdio>
#include <type_traits>
#include <utility>
#if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 202002L || (defined(__circle_lang__) || defined(__clang__) || defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__GNUC__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER))
# include <version>
#endif

/* ... ->> Over-engineered operative tuple */
struct $return final {
  public:
    struct nil;

  private:
    struct operation;
    template <bool, typename = void, class = nil /* --> values<> */, class = nil /* --> values_cast<> */, std::nullptr_t = nullptr> struct values;
    template <typename = void, class = nil /* --> values_cast<> */>                                                                 struct values_cast;

    /* ... ->> Metafunction for evaluating operation validity without implicit rvalue-reference-qualification (unlike `std::declval<...>()`) */
    template <typename type>
    constexpr static type instanceof() noexcept;

  /* ... */
  private:
    // ... ->> Metafunctions denoting C++ operators
    struct operation final {
      // ... ->> Metafunction asserting if specified `base` is a `operation`
      template <typename, std::nullptr_t = nullptr>
      struct is final {
        static bool const value = false;
      };

      template <typename base, std::nullptr_t specialization> struct is<base const,          specialization> final { static bool const value = is<base>::value; };
      template <typename base, std::nullptr_t specialization> struct is<base const volatile, specialization> final { static bool const value = is<base>::value; };
      template <typename base, std::nullptr_t specialization> struct is<base volatile,       specialization> final { static bool const value = is<base>::value; };

      // ... --- TODO (Lapys) -> There has got to be a neater way to do this --- WARN (Lapys) -> Dependency on `decltype(...)` keyword prevents ISO C++98 support
      struct nop final {
        struct evaluate {
          typedef void type;

          static bool const throwable = false;
          static bool const valid     = false;
        };
      };

      // ...
      #define _return(name, operation) name final {                                                               \
        template <typename, typename = void>                                                                      \
        struct evaluate final : nop::evaluate {};                                                                 \
                                                                                                                  \
        template <typename base>                                                                                  \
        struct evaluate<base, decltype((void) operation instanceof<base>())> final {                              \
          typedef decltype(operation instanceof<base>()) type;                                                    \
          static bool const throwable = !noexcept(operation instanceof<base>()), valid = true;                    \
        };                                                                                                        \
                                                                                                                  \
        template <typename type>                                                                                  \
        constexpr static typename evaluate<type>::type value(type&& value) noexcept(!evaluate<type>::throwable) { \
          return operation static_cast<type>(std::forward<type>(value));                                          \
        }                                                                                                         \
      }; template <std::nullptr_t specialization> struct is<name, specialization> final { static bool const value = true; }

      struct _return(address,        &);
      struct _return(complement,     ~);
      struct _return(dereference,    *);
      struct _return(minus,          -);
      struct _return(negate,         !);
      struct _return(plus,           +);
      struct _return(pre_decrement, --);
      struct _return(pre_increment, ++);
      #undef _return

      // ...
      #define _return(name, operation) name final {                                                               \
        template <typename, typename = void>                                                                      \
        struct evaluate final : nop::evaluate {};                                                                 \
                                                                                                                  \
        template <typename base>                                                                                  \
        struct evaluate<base, decltype((void) instanceof<base>() operation)> final {                              \
          typedef decltype(instanceof<base>() operation) type;                                                    \
                                                                                                                  \
          static bool const throwable = !noexcept(instanceof<base>() operation), valid = true;                    \
        };                                                                                                        \
                                                                                                                  \
        template <typename type>                                                                                  \
        constexpr static typename evaluate<type>::type value(type&& value) noexcept(!evaluate<type>::throwable) { \
          return static_cast<type>(std::forward<type>(value)) operation;                                          \
        }                                                                                                         \
      }; template <std::nullptr_t specialization> struct is<name, specialization> final { static bool const value = true; }

      struct _return(member_access,  .operator ->());
      struct _return(post_decrement, --);
      struct _return(post_increment, ++);
      #undef _return

      // ... ->> Additional parameters purely for syntax-highlighting cleanup while developing
      #define _return(name, operation, ...) name final {                                                                                            \
        template <typename, typename, typename = void>                                                                                              \
        struct evaluate final : nop::evaluate {};                                                                                                   \
                                                                                                                                                    \
        template <typename baseA, typename baseB>                                                                                                   \
        struct evaluate<baseA, baseB, decltype((void) (instanceof<baseA>() operation instanceof<baseB>()))> final {                                 \
          typedef decltype((instanceof<baseA>() operation instanceof<baseB>())) type;                                                               \
          static bool const throwable = !noexcept(instanceof<baseA>() operation instanceof<baseB>()), valid = true;                                 \
        };                                                                                                                                          \
                                                                                                                                                    \
        template <typename typeA, typename typeB>                                                                                                   \
        constexpr static typename evaluate<typeA, typeB>::type value(typeA&& valueA, typeB&& valueB) noexcept(!evaluate<typeA, typeB>::throwable) { \
          return (static_cast<typeA>(std::forward<typeA>(valueA)) operation static_cast<typeB>(std::forward<typeB>(valueB)));                       \
        }                                                                                                                                           \
      }; template <std::nullptr_t specialization> struct is<name, specialization> final { static bool const value = true; }

      struct _return(add,                     +, ~);
      struct _return(assign,                  =, ~);
      struct _return(assign_add,             +=, ~);
      struct _return(assign_bitwise_and,     &=, ~);
      struct _return(assign_bitwise_or,      |=, ~);
      struct _return(assign_bitwise_xor,     ^=, ~);
      struct _return(assign_divide,          /=, ~);
      struct _return(assign_left_shift,     <<=, =>>);
      struct _return(assign_modulo,          %=, ~);
      struct _return(assign_multiply,        *=, ~);
      struct _return(assign_right_shift,    >>=, ~);
      struct _return(assign_subtract,        -=, ~);
      struct _return(bitwise_and,             &, ~);
      struct _return(bitwise_or,              |, ~);
      struct _return(bitwise_xor,             ^, ~);
      struct _return(boolean_and,            &&, ~);
      struct _return(boolean_or,             ||, ~);
      struct _return(divide,                  /, ~);
      struct _return(equals,                 ==, ~);
      struct _return(equals_greater,         <=, =>);
      struct _return(equals_lesser,          >=, ~);
      struct _return(greater,                 >, ~);
      struct _return(left_shift,             <<, >>);
      struct _return(lesser,                  <, >);
      struct _return(member_pointer_access, ->*, ~);
      struct _return(modulo,                  %, ~);
      struct _return(multiply,                *, ~);
      struct _return(right_shift,            >>, ~);
      struct _return(subtract,                -, ~);
      struct _return(unequals,               !=, ~);
      #ifdef __cpp_impl_three_way_comparison
        struct _return(compare, <=>);
      #endif
      #undef _return

      // ...
      #define _return(name) name final {                                                                                                            \
        template <typename, typename, typename = void>                                                                                              \
        struct evaluate final : nop::evaluate {};                                                                                                   \
                                                                                                                                                    \
        template <typename baseA, typename baseB>                                                                                                   \
        struct evaluate<baseA, baseB, decltype((void) instanceof<baseA>()[instanceof<baseB>()])> final {                                            \
          typedef decltype(instanceof<baseA>()[instanceof<baseB>()]) type;                                                                          \
          static bool const throwable = !noexcept(instanceof<baseA>()[instanceof<baseB>()]), valid = true;                                          \
        };                                                                                                                                          \
                                                                                                                                                    \
        template <typename typeA, typename typeB>                                                                                                   \
        constexpr static typename evaluate<typeA, typeB>::type value(typeA&& valueA, typeB&& valueB) noexcept(!evaluate<typeA, typeB>::throwable) { \
          return static_cast<typeA>(std::forward<typeA>(valueA))[static_cast<typeB>(std::forward<typeB>(valueB))];                                  \
        }                                                                                                                                           \
      }; template <std::nullptr_t specialization> struct is<name, specialization> final { static bool const value = true; }

      struct _return(subscript);
      #undef _return

      // ...
      #ifdef __cpp_variadic_templates
      # define _return(name) name final {                                                                                                                  \
          template <typename base, typename... bases>                                                                                                      \
          struct evaluate final {                                                                                                                          \
            private:                                                                                                                                       \
              template <typename, typename = void>                                                                                                         \
              struct valueof : nop::evaluate {};                                                                                                           \
                                                                                                                                                           \
              template <typename subbase>                                                                                                                  \
              struct valueof<subbase, decltype((void) instanceof<subbase>()(instanceof<bases>()...))> {                                                    \
                typedef decltype(instanceof<subbase>()(instanceof<bases>()...)) type;                                                                      \
                static bool const throwable = !noexcept(instanceof<subbase>()(instanceof<bases>()...)), valid = true;                                      \
              };                                                                                                                                           \
                                                                                                                                                           \
            public:                                                                                                                                        \
              typedef typename valueof<base>::type type;                                                                                                   \
              static bool const throwable = valueof<base>::throwable, valid = valueof<base>::valid;                                                        \
          };                                                                                                                                               \
                                                                                                                                                           \
          template <typename type, typename... types>                                                                                                      \
          constexpr static typename evaluate<type, types...>::type value(type&& value, types&&... values) noexcept(!evaluate<type, types...>::throwable) { \
            return static_cast<type>(std::forward<type>(value))(static_cast<types>(std::forward<types>(values))...);                                       \
          }                                                                                                                                                \
        }; template <std::nullptr_t specialization> struct is<name, specialization> final { static bool const value = true; }

        struct _return(call);
      # undef _return
      #endif
    };

    // ... ->> Recursive collection of (requested) types to sequentially cast an object through
    template <typename, class>
    struct values_cast final {
      template <typename subbase>
      struct valueof final {
        typedef subbase type;
      };

      template <typename type>
      constexpr static typename valueof<type&&>::type value(type&& value) noexcept {
        return std::forward<type>(value);
      }
    };

    template <typename base>
    struct values_cast<base, values_cast<> > final {
      template <typename>
      struct valueof final {
        typedef base type;
      };

      template <typename type>
      constexpr static typename valueof<type&&>::type value(type&& value) noexcept(noexcept(static_cast<base>(std::declval<type>()))) {
        return static_cast<base>(std::forward<type>(value));
      }
    };

    template <typename base, typename subbase, class subcast>
    struct values_cast<base, values_cast<subbase, subcast> > final {
      template <typename subsubbase>
      struct valueof final {
        typedef typename values_cast<subbase, subcast>::template valueof<subsubbase>::type type;
      };

      template <typename type>
      constexpr static typename valueof<type&&>::type value(type&& value) noexcept(
        noexcept(static_cast<base>(std::declval<type>())) &&
        noexcept(values_cast<subbase, subcast>::value(instanceof<base>()))
      ) { return values_cast<subbase, subcast>::value(static_cast<base>(std::forward<type>(value))); }
    };

    // ... ->> Recursive collection of objects (or references)
    template <std::nullptr_t specialization>
    struct values<false, void, nil, nil, specialization> {
      friend struct $return;
      template <bool, typename, class, class, std::nullptr_t> friend struct values;

      /* ... */
      private:
        typedef values_cast<> cast;
        typedef values<false> previous;
        typedef void          type;

        /* ... */
        static std::size_t const length = 0u;

        /* ... ->> Metafunction asserting if specified `base` is a `values` collection */
        template <typename base>
        struct is final {
          static bool const value = std::is_same<base, nil>::value;
        };

        template <typename base> struct is<base&>               final { static bool const value = is<base>::value; };
        template <typename base> struct is<base&&>              final { static bool const value = is<base>::value; };
        template <typename base> struct is<base const>          final { static bool const value = is<base>::value; };
        template <typename base> struct is<base const volatile> final { static bool const value = is<base>::value; };
        template <typename base> struct is<base volatile>       final { static bool const value = is<base>::value; };

        template <bool allocated, typename base, class previous, class cast>
        struct is<values<allocated, base, previous, cast> > final {
          static bool const value = true;
        };

        // ... ->> Metafunction denoting `values` when an object is added to the collection or another `values` is concatenated
        template <typename base, bool = true>
        struct addof final {
          typedef values<false, typename std::conditional<std::is_constructible<base, base>::value && (
            std::is_reference<base>                                     ::value ||
            std::is_same     <base, typename std::remove_cv<base>::type>::value
          ), base, base&&>::type, previous, cast> type;
        };

        template <bool allocated>
        struct addof<values<allocated>, false> final {
          typedef values<allocated> type;
        };

        template <bool allocated, typename base, class previous, class cast>
        struct addof<values<allocated, base, previous, cast>, true> final {
          typedef values<true, base, typename addof<
            typename values<allocated, base, previous, cast>::previous,
            0u != values<allocated, base, previous, cast>::previous::length
          >::type, cast> type;
        };

        // ... ->> Metafunction generating `values` from a specified `base` object
        template <typename base, class subvalues = values<false> >
        struct buildof final {
          typedef typename std::conditional<is<base>::value, typename std::remove_cv<typename std::remove_reference<base>::type>::type, subvalues>::type type;
        };

        // ... ->> Metafunction denoting `values_cast` used when referring to an object in `values`
        template <class, class subcast = cast>
        struct castof final {
          typedef subcast type;
        };

        // ... ->> Metafunction denoting `values` type when an operation is performed on its collection
        template <
          class, class subvalues, class = values, class = subvalues
          #ifdef __cpp_variadic_templates
            , typename...
          #endif
        > struct operationof final {
          typedef values<false> type;

          static bool const nil   = false;
          static bool const value = true;
        };

        // ... ->> Metafunction denoting `values` after a requested cast from `return_cast<>(...)`
        template <typename base>
        struct return_cast final {
          typedef values<false, void, previous, values_cast<base, cast> > type;
        };

      public:
        // ... ->> Metafunction denoting `values` after a series of additions or concatenations
        #ifdef __cpp_variadic_templates
          template <typename...>
          struct joinof final {
            typedef values<false> type;
          };

          template <typename base, typename... bases>
          struct joinof<base, bases...> final {
            typedef typename addof<typename std::conditional<is<base>::value, typename std::remove_cv<typename std::remove_reference<base>::type>::type, base>::type>::type::template joinof<bases...>::type type;
          };
        #endif

      /* ... */
      private:
        // ... ->> Concatenate `values`
        template <class subvalues>
        constexpr static subvalues&& add(values<false> const&, subvalues&& valued) noexcept {
          return std::forward<subvalues>(valued);
        }

        // ... ->> Compute operation resulting in new `values`
        template <class, class /* = values */>
        constexpr values<false> const& operate() const noexcept {
          return *this;
        }

        template <class, class subvalues, class /* = values */, class /* = subvalues */, std::size_t /* = values::length */, std::size_t /* = subvalues::length */>
        constexpr values<false> const& operate(subvalues const&) const noexcept {
          return *this;
        }

        #ifdef __cpp_variadic_templates
          template <class, std::size_t, class /* = values */, typename... types>
          constexpr values<false> const& operate(types&&...) const noexcept {
            return *this;
          }
        #endif

      /* ... */
      template <typename type>
      constexpr friend typename std::enable_if<false != is<type>::value, type&&>::type operator ,(values const& valuedA, type&& valuedB) noexcept {
        return values::add(valuedA, std::forward<type>(valuedB));
      }

      template <typename type>
      constexpr friend typename std::enable_if<false == is<type>::value, typename addof<type>::type>::type operator ,(values const& valued, type&& value)
        #ifdef _MSC_VER
          noexcept(std::is_reference<type>::value)
        #else
          noexcept(noexcept(typename addof<type>::type(valued, std::declval<type>())))
        #endif
      { return {valued, std::forward<type>(value)}; }
    };

    template <std::nullptr_t specialization>
    struct values<true, void, nil, nil, specialization> : public values<false> {};

    template <typename base, class _previous, class _cast, std::nullptr_t specialization>
    struct values<false, base, _previous, _cast, specialization> : public values<false> {
      friend struct $return;
      template <bool, typename, class, class, std::nullptr_t> friend struct values;
      template <typename typeA, typename typeB, class previous, class cast> constexpr friend typename values<false, typeB, previous, cast>::template return_cast<typeA>::type return_cast(values<false, typeB, previous, cast> const&) noexcept(noexcept(typeB(std::declval<typeB>())) && noexcept(previous(std::declval<previous const&>())));

      /* ... */
      private:
        typedef typename std::conditional<std::is_same<nil, _cast>    ::value, values_cast<>, _cast>    ::type cast;
        typedef typename std::conditional<std::is_same<nil, _previous>::value, values<false>, _previous>::type previous;
        typedef operation operations;
        typedef base      type;

        /* ... */
        static std::size_t const length = previous::length + 1u;

        /* ... */
        template <typename subbase>
        struct addof final {
          typedef values<false, typename std::conditional<std::is_constructible<subbase, subbase>::value && (
            std::is_reference<subbase>                                        ::value ||
            std::is_same     <subbase, typename std::remove_cv<subbase>::type>::value
          ), subbase, subbase&&>::type, values<false, base, previous, cast>, values_cast<> > type;
        };

        template <bool suballocated, typename subbase, class subprevious, class subcast>
        struct addof<values<suballocated, subbase, subprevious, subcast> > final {
          typedef values<true, subbase, typename values<suballocated, subbase, subprevious, subcast>::previous::template addof<values>::type, subcast> type;
        };

        // ...
        template <typename subbase, class subvalues = values<true> >
        struct buildof final {
          typedef typename std::conditional<
            is<subbase>::value,
            typename std::remove_cv<typename std::remove_reference<subbase>::type>::type,
            typename previous::template buildof<subbase, values<true, subbase&&, subvalues, values_cast<> > >::type
          >::type type;
        };

        // ...
        template <class subvalues, class subcast = cast>
        struct castof final {
          typedef typename previous::template castof<subvalues, typename castof<values, subcast>::type>::type type;
        };

        template <class subcast>
        struct castof<values, subcast> final {
          typedef typename std::conditional<std::is_same<cast, values_cast<> >::value, subcast, cast>::type type;
        };

      public:
        // ...
        #ifdef __cpp_variadic_templates
          template <typename...>
          struct joinof final {
            typedef values<false, base, previous, cast> type;
          };

          template <typename subbase, typename... subbases>
          struct joinof<subbase, subbases...> final {
            typedef typename addof<typename std::conditional<is<subbase>::value, typename std::remove_cv<typename std::remove_reference<subbase>::type>::type, subbase>::type>::type::template joinof<subbases...>::type type;
          };
        #endif

        // ...
        template <
          class, class subvalues = nil, class = values, class = subvalues
          #ifdef __cpp_variadic_templates
            , typename...
          #endif
        > struct operationof;

        template <
          class operation, class subvalues
          #ifdef __cpp_variadic_templates
            , typename... bases
          #endif
        > struct operationof<
          operation, nil, subvalues, nil
          #ifdef __cpp_variadic_templates
            , bases...
          #endif
        > final {
          typedef typename operation::template evaluate<
            typename subvalues::template castof<values<false, base, previous, cast> >::type::template valueof<base>::type
          > evaluation;

          public:
            static bool const nil   = std::is_void<typename evaluation::type>::value || previous::template operationof<operation, $return::nil, subvalues, $return::nil>::nil;
            static bool const value = evaluation::valid;

            typedef typename std::conditional<false == nil && value, values<
              true,
              typename std::conditional<nil, $return::nil, typename evaluation::type>::type,
              typename previous::template operationof<operation, $return::nil, subvalues, $return::nil>::type,
              cast
            >, void>::type type;
        };

        template <class operation, bool suballocated, class valuesA, class valuesB>
        struct operationof<operation, values<suballocated>, valuesA, valuesB> final {
          typedef values<suballocated> type;

          static bool const nil   = false;
          static bool const value = true;
        };

        template <class operation, bool suballocated, typename subbase, class subprevious, class subcast, class valuesA, class valuesB>
        struct operationof<operation, values<suballocated, subbase, subprevious, subcast>, valuesA, valuesB> final {
          typedef typename operation::template evaluate<
            typename valuesA::template castof<values<false,        base,    previous,    cast>    >::type::template valueof<base>   ::type,
            typename valuesB::template castof<values<suballocated, subbase, subprevious, subcast> >::type::template valueof<subbase>::type
          > evaluation;

          public:
            static bool const nil   = std::is_void<typename evaluation::type>::value || previous::template operationof<operation, typename values<suballocated, subbase, subprevious, subcast>::previous, valuesA, valuesB>::nil;
            static bool const value = evaluation::valid;

            typedef typename std::conditional<false == nil && value, values<
              true,
              typename std::conditional<nil, $return::nil, typename evaluation::type>::type,
              typename previous::template operationof<operation, typename values<suballocated, subbase, subprevious, subcast>::previous, valuesA, valuesB>::type,
              cast
            >, void>::type type;
        };

        #ifdef __cpp_variadic_templates
          template <class subvalues, typename... bases>
          struct operationof<operations::call, nil, subvalues, nil, bases...> final {
            typedef typename operations::call::template evaluate<
              typename subvalues::template castof<values<false, base, previous, cast> >::type::template valueof<base>::type,
              bases...
            > evaluation;

            public:
              static bool const nil   = std::is_void<typename evaluation::type>::value || previous::template operationof<operations::call, $return::nil, subvalues, $return::nil, bases...>::nil;
              static bool const value = evaluation::valid;

              typedef typename std::conditional<false == nil && value, values<
                true,
                typename std::conditional<nil, $return::nil, typename evaluation::type>::type,
                typename previous::template operationof<operations::call, $return::nil, subvalues, $return::nil, bases...>::type,
                cast
              >, void>::type type;
          };
        #endif

        // ...
        template <typename subbase>
        struct return_cast final {
          typedef values<false, base, previous, values_cast<subbase, cast> > type;
        };

      /* ... */
      private:
        previous const &prevalues;
        base            value;

      /* ... */
      public:
        constexpr values(previous const& previous, base&& value) noexcept(noexcept(base(instanceof<base>()))) :
          prevalues(previous),
          value    (static_cast<base>(static_cast<base&&>(value)))
        {}

        constexpr values(values const& valued) noexcept(noexcept(values(instanceof<previous>(), instanceof<base&&>()))) :
          values::values(valued.prevalues, static_cast<base&&>(const_cast<base&>(valued.value)))
        {}

      /* ... */
      private:
        constexpr static values<false> add(values<false> const&, values<false> const&) noexcept {
          return {};
        }

        template <class subvalues>
        constexpr static typename values<false>::template addof<subvalues>::type add(subvalues const& valued, values<false> const&) noexcept(noexcept(typename values<false>::template addof<subvalues>::type(values::add(instanceof<typename subvalues::previous>(), {}), instanceof<typename subvalues::type&&>()))) {
          return {values::add(valued.prevalues, {}), static_cast<typename subvalues::type&&>(const_cast<typename subvalues::type&>(valued.value))};
        }

        template <class subvaluesA, class subvaluesB>
        constexpr static typename subvaluesB::template addof<subvaluesA>::type add(subvaluesA const& valuedA, subvaluesB const& valuedB) noexcept(noexcept(typename subvaluesB::template addof<subvaluesA>::type(values::add(instanceof<subvaluesA>(), instanceof<typename subvaluesB::previous>()), instanceof<typename subvaluesB::type&&>()))) {
          return {values::add(valuedA, valuedB.prevalues), static_cast<typename subvaluesB::type&&>(const_cast<typename subvaluesB::type&>(valuedB.value))};
        }

        // ...
        template <bool suballocated, typename type, class subprevious, class subcast>
        constexpr static values<suballocated, type, subprevious, subcast> const& build(values<suballocated, type, subprevious, subcast> const& valued) noexcept {
          return valued;
        }

        template <typename type>
        constexpr static typename buildof<type>::type build(type&&, typename buildof<type>::type const valued) noexcept {
          return valued;
        }

        template <typename type, class subvalues>
        constexpr static typename std::enable_if<false == std::is_same<subvalues, typename buildof<type>::type>::value, typename buildof<type>::type>::type build(type&& value, subvalues const valued) noexcept {
          return values::build(std::forward<type>(value), values<true, type&&, subvalues, values_cast<> >{valued, static_cast<type&&>(value)});
        }

        template <typename type>
        constexpr static typename std::enable_if<false == is<type>::value, typename buildof<type>::type>::type build(type&& value) noexcept {
          return values::build(std::forward<type>(value), values<true, type&&, values<true>, values_cast<> >{{}, static_cast<type&&>(value)});
        }

        // ...
        template <class operation, class subvalues>
        #if __cpp_constexpr >= 201304L
          constexpr
        #endif
        inline typename std::enable_if<false != operationof<operation>::nil && false != operationof<operation>::value, void>::type operate() const noexcept(
          noexcept(instanceof<previous>().template operate<operation, subvalues>())     &&
          noexcept(subvalues::template castof<values>::type::value(instanceof<base>())) &&
          noexcept(operation::value(subvalues::template castof<values>::type::value(instanceof<base>())))
        ) {
          return static_cast<void>(
            static_cast<void>(this -> prevalues.template operate<operation, subvalues>()),
            operation::value(subvalues::template castof<values>::type::value((base) this -> value))
          );
        }

        template <class operation, class subvalues>
        constexpr typename std::enable_if<false == operationof<operation>::nil && false != operationof<operation>::value, typename operationof<operation>::type>::type operate() const noexcept(
          noexcept(instanceof<previous>().template operate<operation, subvalues>())     &&
          noexcept(subvalues::template castof<values>::type::value(instanceof<base>())) &&
          noexcept(operation::value(subvalues::template castof<values>::type::value(instanceof<base>())))
          #if defined(__clang__) || false == (defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER))
            && noexcept(typename operationof<operation>::type(
              instanceof<previous>().template operate<operation, subvalues>(),
              operation::value(subvalues::template castof<values>::type::value(instanceof<base>()))
            ))
          #endif
        ) {
          return {
            this -> prevalues.template operate<operation, subvalues>(),
            operation::value(subvalues::template castof<values>::type::value((base) this -> value))
          };
        }

        template <class operation, class subvalues>
        typename std::enable_if<false == operationof<operation>::value, void>::type operate() const noexcept(false) {
          typedef std::integral_constant<bool, 0u == sizeof(subvalues)>                            invalid;
          typedef std::integral_constant<bool, invalid::value || operations::is<operation>::value> invalid_object_pack_operation;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::address>       ::value> invalid_object_pack_address;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::complement>    ::value> invalid_object_pack_bitwise_complement;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::dereference>   ::value> invalid_object_pack_dereference;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::member_access> ::value> invalid_object_pack_member_access;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::minus>         ::value> invalid_object_pack_additive_negation;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::negate>        ::value> invalid_object_pack_boolean_negation;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::plus>          ::value> invalid_object_pack_additive_identity;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::post_decrement>::value> invalid_object_pack_postfix_decrement;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::post_increment>::value> invalid_object_pack_postfix_increment;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::pre_decrement> ::value> invalid_object_pack_decrement;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::pre_increment> ::value> invalid_object_pack_increment;

          static_assert(invalid_object_pack_operation::value, "Cannot perform operation on object pack of incompatible type(s)");
          static_assert(invalid_object_pack_additive_identity::value, "Cannot additively identity an object pack of incompatible type(s)");
          static_assert(invalid_object_pack_additive_negation::value, "Cannot additively negate an object pack of incompatible type(s)");
          static_assert(invalid_object_pack_address::value, "Cannot address an object pack of incompatible type(s)");
          static_assert(invalid_object_pack_bitwise_complement::value, "Cannot bitwise-negate an object pack of incompatible type(s)");
          static_assert(invalid_object_pack_boolean_negation::value, "Cannot negate an object pack of incompatible type(s)");
          static_assert(invalid_object_pack_decrement::value, "Cannot decrement an object pack of incompatible type(s)");
          static_assert(invalid_object_pack_dereference::value, "Cannot dereference an object pack of incompatible type(s)");
          static_assert(invalid_object_pack_increment::value, "Cannot increment an object pack of incompatible type(s)");
          static_assert(invalid_object_pack_member_access::value, "Cannot access object pack members of incompatible type(s)");
          static_assert(invalid_object_pack_postfix_decrement::value, "Cannot post-decrement an object pack of incompatible type(s)");
          static_assert(invalid_object_pack_postfix_increment::value, "Cannot post-increment an object pack of incompatible type(s)");
        }

        template <class operation, class subvalues, class valuesA, class valuesB, std::size_t length, std::size_t sublength>
        #if __cpp_constexpr >= 201304L
          constexpr
        #endif
        inline typename std::enable_if<false != operationof<operation, subvalues>::nil && false != operationof<operation, subvalues>::value && length == sublength, void>::type operate(subvalues const& valued) const noexcept(
          noexcept(instanceof<typename values::previous>().template operate<operation, typename subvalues::previous, valuesA, valuesB, values::previous::length, subvalues::previous::length>(instanceof<typename subvalues::previous>())) &&
          noexcept(valuesA::template castof<values>   ::type::value(instanceof<typename values   ::type>()))                                                                                                                               &&
          noexcept(valuesB::template castof<subvalues>::type::value(instanceof<typename subvalues::type>()))                                                                                                                               &&
          noexcept(operation::value(valuesA::template castof<values>::type::value(instanceof<typename values::type>()), valuesB::template castof<subvalues>::type::value(instanceof<typename subvalues::type>())))
        ) {
          return static_cast<void>(
            static_cast<void>(this -> prevalues.template operate<operation, typename subvalues::previous, valuesA, valuesB, values::previous::length, subvalues::previous::length>(valued.prevalues)),
            operation::value(valuesA::template castof<values>::type::value((typename values::type) this -> value), valuesB::template castof<subvalues>::type::value((typename subvalues::type) valued.value))
          );
        }

        template <class operation, class subvalues, class valuesA, class valuesB, std::size_t length, std::size_t sublength>
        constexpr typename std::enable_if<false == operationof<operation, subvalues>::nil && false != operationof<operation, subvalues>::value && length == sublength, typename operationof<operation, subvalues>::type>::type operate(subvalues const& valued) const noexcept(
          noexcept(instanceof<typename values::previous>().template operate<operation, typename subvalues::previous, valuesA, valuesB, values::previous::length, subvalues::previous::length>(instanceof<typename subvalues::previous>())) &&
          noexcept(valuesA::template castof<values>   ::type::value(instanceof<typename values   ::type>()))                                                                                                                               &&
          noexcept(valuesB::template castof<subvalues>::type::value(instanceof<typename subvalues::type>()))                                                                                                                               &&
          noexcept(operation::value(valuesA::template castof<values>::type::value(instanceof<typename values::type>()), valuesB::template castof<subvalues>::type::value(instanceof<typename subvalues::type>())))
          #if defined(__clang__) || false == (defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER))
            && noexcept(typename operationof<operation, subvalues>::type(
              instanceof<typename values::previous>().template operate<operation, typename subvalues::previous, valuesA, valuesB, values::previous::length, subvalues::previous::length>(instanceof<typename subvalues::previous>()),
              operation::value(valuesA::template castof<values>::type::value(instanceof<typename values::type>()), valuesB::template castof<subvalues>::type::value(instanceof<typename subvalues::type>()))
            ))
          #endif
        ) {
          return {
            this -> prevalues.template operate<operation, typename subvalues::previous, valuesA, valuesB, values::previous::length, subvalues::previous::length>(valued.prevalues),
            operation::value(valuesA::template castof<values>::type::value((typename values::type) this -> value), valuesB::template castof<subvalues>::type::value((typename subvalues::type) valued.value))
          };
        }

        template <class operation, class subvalues, class, class, std::size_t length, std::size_t sublength>
        typename std::enable_if<false == operationof<operation, subvalues>::value || length != sublength, void>::type operate(subvalues const&) const noexcept(false) {
          typedef std::integral_constant<bool, 0u == sizeof(subvalues)>                            invalid;
          typedef std::integral_constant<bool, invalid::value || operations::is<operation>::value> invalid_object_pack_operation;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::add>                  ::value> invalid_object_pack_addition;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::assign>               ::value> invalid_object_pack_assignment;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::assign_add>           ::value> invalid_object_pack_compound_add_assignment;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::assign_left_shift>    ::value> invalid_object_pack_compound_left_shift_assignment;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::assign_right_shift>   ::value> invalid_object_pack_compound_right_shift_assignment;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::assign_subtract>      ::value> invalid_object_pack_compound_subtract_assignment;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::bitwise_and>          ::value> invalid_object_pack_bitwise_and;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::bitwise_and>          ::value> invalid_object_pack_compound_bitwise_and_assignment;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::bitwise_or>           ::value> invalid_object_pack_bitwise_or;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::bitwise_or>           ::value> invalid_object_pack_compound_bitwise_or_assignment;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::bitwise_xor>          ::value> invalid_object_pack_bitwise_xor;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::bitwise_xor>          ::value> invalid_object_pack_compound_bitwise_xor_assignment;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::boolean_and>          ::value> invalid_object_pack_boolean_and;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::boolean_or>           ::value> invalid_object_pack_boolean_or;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::divide>               ::value> invalid_object_pack_compound_divide_assignment;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::divide>               ::value> invalid_object_pack_division;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::equals>               ::value> invalid_object_pack_equality;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::equals_greater>       ::value> invalid_object_pack_greater_equality;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::equals_lesser>        ::value> invalid_object_pack_lesser_equality;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::greater>              ::value> invalid_object_pack_greater_comparison;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::left_shift>           ::value> invalid_object_pack_left_shift;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::lesser>               ::value> invalid_object_pack_lesser_comparison;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::member_pointer_access>::value> invalid_object_pack_member_access;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::modulo>               ::value> invalid_object_pack_compound_modulo_assignment;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::modulo>               ::value> invalid_object_pack_modulation;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::multiply>             ::value> invalid_object_pack_compound_multiply_assignment;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::multiply>             ::value> invalid_object_pack_multiplication;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::right_shift>          ::value> invalid_object_pack_right_shift;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::subscript>            ::value> invalid_object_pack_index;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::subtract>             ::value> invalid_object_pack_subtraction;
          typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::unequals>             ::value> invalid_object_pack_inequality;
          #ifdef __cpp_impl_three_way_comparison
            typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::compare>::value> invalid_object_pack_comparison;
          #endif

          static_assert(invalid_object_pack_operation::value, "Cannot perform binary operation on object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_addition::value, "Cannot add object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_assignment::value, "Cannot assign object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_bitwise_and::value, "Cannot AND object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_bitwise_or::value, "Cannot OR object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_bitwise_xor::value, "Cannot XOR object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_boolean_and::value, "Cannot conjunct object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_boolean_or::value, "Cannot disjunct object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_compound_add_assignment::value, "Cannot compound-add assign object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_compound_bitwise_and_assignment::value, "Cannot compound-AND assign object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_compound_bitwise_or_assignment::value, "Cannot compound-OR assign object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_compound_bitwise_xor_assignment::value, "Cannot compound-XOR assign object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_compound_divide_assignment::value, "Cannot compound-divide assign object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_compound_left_shift_assignment::value, "Cannot compound-shift assign object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_compound_modulo_assignment::value, "Cannot compound-modulate assign object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_compound_multiply_assignment::value, "Cannot compound-multiply assign object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_compound_right_shift_assignment::value, "Cannot compound-shift assign object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_compound_subtract_assignment::value, "Cannot compound-subtract assign object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_division::value, "Cannot divide object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_equality::value, "Cannot compare object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_greater_comparison::value, "Cannot compare object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_greater_equality::value, "Cannot compare object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_index::value, "Cannot index object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_inequality::value, "Cannot compare object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_left_shift::value, "Cannot shift object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_lesser_comparison::value, "Cannot compare object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_lesser_equality::value, "Cannot compare object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_member_access::value, "Cannot access members of object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_modulation::value, "Cannot modulate object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_multiplication::value, "Cannot multiply object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_right_shift::value, "Cannot shift object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_subtraction::value, "Cannot subtract object packs of incompatible types or unequal size");
          #ifdef __cpp_impl_three_way_comparison
            static_assert(invalid_object_pack_comparison::value, "Cannot compare object packs of incompatible types or unequal size");
          #endif
        }

        #ifdef __cpp_variadic_templates
          template <class operation, std::size_t count, class subvalues, typename... types>
          #if __cpp_constexpr >= 201304L
            constexpr
          #endif
          inline typename std::enable_if<false != operationof<operation, nil, values, nil, types...>::nil && false != operationof<operation, nil, values, nil, types...>::value, void>::type operate(types&&... values) const noexcept(
            noexcept(instanceof<previous>().template operate<operation, count, subvalues>(std::declval<types>()...))               &&
            noexcept(subvalues::template castof<$return::values<false, base, _previous, _cast> >::type::value(instanceof<base>())) &&
            noexcept(operation::value(subvalues::template castof<$return::values<false, base, _previous, _cast> >::type::value(instanceof<base>()), std::declval<types>()...))
          ) {
            return static_cast<void>(
              static_cast<void>(this -> prevalues.template operate<operation, count, subvalues>(std::forward<types>(values)...)),
              operation::value(subvalues::template castof<$return::values<false, base, _previous, _cast> >::type::value((base) this -> value), std::forward<types>(values)...)
            );
          }

          template <class operation, std::size_t count, class subvalues, typename... types>
          constexpr typename std::enable_if<false == operationof<operation, nil, values, nil, types...>::nil && false != operationof<operation, nil, values, nil, types...>::value, typename operationof<operation, nil, values, nil, types...>::type>::type operate(types&&... values) const noexcept(
            noexcept(instanceof<previous>().template operate<operation, count, subvalues>(std::declval<types>()...))               &&
            noexcept(subvalues::template castof<$return::values<false, base, _previous, _cast> >::type::value(instanceof<base>())) &&
            noexcept(operation::value(subvalues::template castof<$return::values<false, base, _previous, _cast> >::type::value(instanceof<base>()), std::declval<types>()...))
            #if defined(__clang__) || false == (defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER))
              && noexcept(typename operationof<operation, nil, $return::values<false, base, _previous, _cast>, nil, types...>::type(
                instanceof<previous>().template operate<operation, count, subvalues>(std::declval<types>()...),
                operation::value(subvalues::template castof<$return::values<false, base, _previous, _cast> >::type::value(instanceof<base>()), std::declval<types>()...)
              ))
            #endif
          ) {
            return {
              this -> prevalues.template operate<operation, count, subvalues>(std::forward<types>(values)...),
              operation::value(subvalues::template castof<$return::values<false, base, _previous, _cast> >::type::value((base) this -> value), std::forward<types>(values)...)
            };
          }

          template <class operation, std::size_t, class subvalues, typename... types>
          typename std::enable_if<false == operationof<operation, nil, values, nil, types...>::value, void>::type operate(types&&...) const noexcept(false) {
            typedef std::integral_constant<bool, 0u == sizeof(subvalues)>                            invalid;
            typedef std::integral_constant<bool, invalid::value || operations::is<operation>::value> invalid_object_pack_operation;
            typedef std::integral_constant<bool, invalid::value || false == std::is_same<operation, operations::call>::value> invalid_object_pack_function_call;

            static_assert(invalid_object_pack_operation::value, "Cannot perform operation on object pack of incompatible type(s)");
            static_assert(invalid_object_pack_function_call::value, "Cannot call an object pack of incompatible type(s) like a function");
          }
        #endif

      #ifdef __clang__
        private:
      #else
        public:
      #endif
        template <class operation>
        constexpr typename operationof<operation>::type suboperate() const noexcept(noexcept(this -> template operate<operation, values>())) {
          return this -> template operate<operation, values>();
        }

        template <class operation, class subvalues>
        constexpr typename operationof<operation, subvalues>::type suboperate(subvalues const& valued) const noexcept(
          #if defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__NVCC__) || defined(__NVCOMPILER)
            false
          #else
            noexcept(this -> template operate<operation, subvalues, values, subvalues, length, subvalues::length>(instanceof<subvalues>()))
          #endif
        ) { return this -> template operate<operation, subvalues, values, subvalues, values::length, subvalues::length>(valued); }

        #ifdef __cpp_variadic_templates
          template <class operation, std::size_t count, typename... types>
          constexpr typename operationof<operation, nil, values, nil, types...>::type suboperate(types&&... values) const noexcept(noexcept(this -> template operate<operation, count, $return::values<false, base, _previous, _cast> >(std::declval<types>()...))) {
            return this -> template operate<operation, count, $return::values<false, base, _previous, _cast> >(std::forward<types>(values)...);
          }
        #endif

      /* ... */
      public:
        constexpr typename operationof<operations::member_access>::type operator ->() const noexcept(noexcept(this -> template suboperate<operation::member_access>())) {
          return this -> template suboperate<operations::member_access>();
        }

        constexpr typename operationof<operations::assign, values>::type operator =(values const& valued) const noexcept(
          #if defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__NVCC__) || defined(__NVCOMPILER)
            false
          #else
            noexcept(this -> template suboperate<operations::assign>(instanceof<values>()))
          #endif
        ) {
          return this -> template suboperate<operations::assign>(valued);
        }

        template <typename type>
        constexpr typename operationof<operations::assign, typename buildof<type>::type>::type operator =(type&& value) const noexcept(noexcept(this -> template suboperate<operation::assign>(values::build(std::declval<type>())))) {
          return this -> template suboperate<operations::assign>(values::build(std::forward<type>(value)));
        }

        template <typename type>
        constexpr typename operationof<operations::subscript, typename buildof<type>::type>::type operator [](type&& value) const noexcept(noexcept(this -> template suboperate<operation::subscript>(values::build(std::declval<type>())))) {
          return this -> template suboperate<operations::subscript>(values::build(std::forward<type>(value)));
        }

        #ifdef __cpp_variadic_templates
          template <typename... types>
          constexpr typename operationof<operations::call, nil, values, nil, types...>::type operator ()(types&&... values) const noexcept(noexcept(this -> template suboperate<operations::call, sizeof...(types)>(std::declval<types>()...))) {
            return this -> template suboperate<operations::call, sizeof...(types)>(std::forward<types>(values)...);
          }
        #endif

      /* ... */
      #if defined(_MSC_VER)
        template <typename type>
        constexpr typename std::enable_if<false != is<type>::value, typename std::remove_reference<type>::type::template addof<values>::type>::type operator ,(type&& value) const noexcept(noexcept(values::add(instanceof<values>(), std::declval<type>()))) {
          return values::add(*this, value);
        }

        template <typename type>
        constexpr typename std::enable_if<false == is<type>::value, typename addof<type>::type>::type operator ,(type&& value) const noexcept(std::is_reference<type>::value) {
          return {*this, std::forward<type>(value)};
        }
      #else
        template <typename type>
        constexpr friend typename std::enable_if<false != is<type>::value, typename std::remove_reference<type>::type::template addof<values>::type>::type operator ,(values const& valued, type&& value)
          #ifdef __circle_lang__
            noexcept(false)
          #else
            noexcept(noexcept(values::add(valued, std::declval<type>())))
          #endif
        { return values::add(valued, value); }

        template <typename type>
        constexpr friend typename std::enable_if<false == is<type>::value, typename addof<type>::type>::type operator ,(values const& valued, type&& value)
          #ifdef __circle_lang__
            noexcept(std::is_reference<type>::value)
          #else
            noexcept(noexcept(typename addof<type>::type(valued, std::declval<type>())))
          #endif
        { return {valued, std::forward<type>(value)}; }
      #endif

      // ...
      #define _return_ _return_
      #define _return_false
      #if defined(__circle_lang__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
      # define _return_true int const
      # define _return(name, operation, postfix)                                                           \
        constexpr typename operationof<name>::type operator operation(_return_ ## postfix) const noexcept( \
          noexcept(this -> template suboperate<name>())                                                    \
        ) { return this -> template suboperate<name>(); }
      #else
      # define _return_true , int const
      # define _return(name, operation, postfix)                                                                                 \
        constexpr friend typename operationof<name>::type operator operation(values const& valued _return_ ## postfix) noexcept( \
          noexcept(valued.template suboperate<name>())                                                                           \
        ) { return valued.template suboperate<name>(); }                                                                         \
                                                                                                                                 \
        unsigned char : 0
      #endif

      _return(operations::address,         &, false);
      _return(operations::complement,      ~, false);
      _return(operations::dereference,     *, false);
      _return(operations::minus,           -, false);
      _return(operations::negate,          !, false);
      _return(operations::plus,            +, false);
      _return(operations::post_decrement, --, true);
      _return(operations::post_increment, ++, true);
      _return(operations::pre_decrement,  --, false);
      _return(operations::pre_increment,  ++, false);
      #undef _return
      #undef _return_
      #undef _return_false
      #undef _return_true

      // ... ->> Additional parameters purely for syntax-highlighting cleanup while developing
      #if defined(__circle_lang__) || defined(_MSC_VER)
      # define _return(name, operation, ...)                                                                                                                                                                      \
        template <typename type>                                                                                                                                                                                  \
        constexpr friend typename buildof<type>::type::template operationof<name, values>::type operator operation(type&& value, values const& valued) noexcept(                                                  \
          false                                                                                                                                                                                                   \
        ) { return values::build(std::forward<type>(value)).template suboperate<name>(valued); }                                                                                                                  \
                                                                                                                                                                                                                  \
        template <typename type>                                                                                                                                                                                  \
        constexpr typename std::enable_if<false == is<type>::value, typename values::template operationof<name, typename buildof<type>::type>::type>::type operator operation(type&& value) const noexcept(       \
          noexcept(instanceof<values>() operation values::build(std::declval<type>()))                                                                                                                     \
        ) { return *this operation values::build(std::forward<type>(value)); }
      #else
      # define _return(name, operation, ...)                                                                                                                                                                      \
        template <typename type>                                                                                                                                                                                  \
        constexpr friend typename buildof<type>::type::template operationof<name, values>::type operator operation(type&& value, values const& valued) noexcept(                                                  \
          noexcept(values::build(std::declval<type>()).template suboperate<name>(valued))                                                                                                                         \
        ) { return values::build(std::forward<type>(value)).template suboperate<name>(valued); }                                                                                                                  \
                                                                                                                                                                                                                  \
        template <typename type>                                                                                                                                                                                  \
        constexpr friend typename std::enable_if<false == is<type>::value, typename operationof<name, typename buildof<type>::type>::type>::type operator operation(values const& valued, type&& value) noexcept( \
          noexcept(valued operation values::build(std::declval<type>()))                                                                                                                                          \
        ) { return valued operation values::build(std::forward<type>(value)); }                                                                                                                                   \
                                                                                                                                                                                                                  \
        unsigned char : 0
      #endif

      _return(operations::add,                     +, ~);
      _return(operations::assign_add,             +=, ~);
      _return(operations::assign_bitwise_and,     &=, ~);
      _return(operations::assign_bitwise_or,      |=, ~);
      _return(operations::assign_bitwise_xor,     ^=, ~);
      _return(operations::assign_divide,          /=, ~);
      _return(operations::assign_left_shift,     <<=, =>>);
      _return(operations::assign_modulo,          %=, ~);
      _return(operations::assign_multiply,        *=, ~);
      _return(operations::assign_right_shift,    >>=, ~);
      _return(operations::assign_subtract,        -=, ~);
      _return(operations::bitwise_and,             &, ~);
      _return(operations::bitwise_or,              |, ~);
      _return(operations::bitwise_xor,             ^, ~);
      _return(operations::boolean_and,            &&, ~);
      _return(operations::boolean_or,             ||, ~);
      _return(operations::divide,                  /, ~);
      _return(operations::equals,                 ==, ~);
      _return(operations::equals_greater,         <=, =>);
      _return(operations::equals_lesser,          >=, ~);
      _return(operations::greater,                 >, ~);
      _return(operations::left_shift,             <<, >>);
      _return(operations::lesser,                  <, >);
      _return(operations::member_pointer_access, ->*, ~);
      _return(operations::modulo,                  %, ~);
      _return(operations::multiply,                *, ~);
      _return(operations::right_shift,            >>, ~);
      _return(operations::subtract,                -, ~);
      _return(operations::unequals,               !=, ~);
      #ifdef __cpp_impl_three_way_comparison
        _return(compare, <=>, ~);
      #endif
      #undef _return
    };

    template <typename base, class _previous, class _cast, std::nullptr_t specialization>
    struct values<true, base, _previous, _cast, specialization> final : public values<false, base, _previous, _cast> {
      friend struct $return;
      template <bool, typename, class, class, std::nullptr_t> friend struct values;

      private:
        typedef values<false, base, _previous, _cast> subvalues;

        typedef typename subvalues::cast     cast;
        typedef typename subvalues::previous previous;
        typedef typename subvalues::type     type;

        /* ... */
        previous prevalues;

      public:
        constexpr values(previous const& previous, base&& value) noexcept(noexcept(subvalues(instanceof<values::previous>(), instanceof<base&&>())) && noexcept(values::previous(instanceof<values::previous const&>()))) :
          subvalues::values(this -> prevalues, static_cast<base&&>(value)),
          prevalues{previous}
        {}

        constexpr values(values const& valued) noexcept(noexcept(values(instanceof<previous>(), instanceof<base&&>()))) :
          values::values(valued.prevalues, static_cast<base&&>(const_cast<base&>(valued.value)))
        {}
    };

  public:
    struct nil final : public values<false> {
      template <bool, typename, class, class, std::nullptr_t> friend struct values;

      private:
        template <typename typeA, typename typeB>
        constexpr nil(typeA&&, typeB&&) noexcept {}

      public:
        constexpr nil() noexcept {}
    };

    /* ... */
    template <typename typeA, typename typeB, class previous, class cast> constexpr friend typename values<false, typeB, previous, cast>::template return_cast<typeA>::type return_cast(values<false, typeB, previous, cast> const&) noexcept(noexcept(typeB(std::declval<typeB>())) && noexcept(previous(std::declval<previous const&>())));
    #ifdef __cpp_variadic_templates
      template <typename typeA, typename typeB, class previous, class cast, typename typeC, typename... types>
      constexpr friend typename values<false, typeB, previous, cast>::template joinof<typeC, types...>::type::template return_cast<typeA>::type return_cast(values<false, typeB, previous, cast> const& valued, typeC&&, types&&...) noexcept(
        noexcept((valued, std::declval<typeC>()))
        #if defined(_MSC_VER) || (defined(__clang__) && __cplusplus >= 202002L)
          && noexcept(return_cast<typeA>((valued, std::declval<typeC>()), std::declval<types>()...))
        #endif
      );
    #endif
};

// ...
constexpr static $return::nil const $ = {};

// ...
template <typename>
constexpr $return::nil return_cast($return::nil const&) noexcept {
  return {};
}

template <typename typeA, typename typeB, class previous, class cast>
constexpr typename $return::values<false, typeB, previous, cast>::template return_cast<typeA>::type return_cast($return::values<false, typeB, previous, cast> const& valued) noexcept(
  noexcept(typeB(std::declval<typeB>())) &&
  noexcept(previous(std::declval<previous const&>()))
) { return {valued.prevalues, static_cast<typeB&&>(const_cast<typeB&>(valued.value))}; }

#ifdef __cpp_variadic_templates
  template <typename typeA, typename typeB, class previous, class cast, typename typeC, typename... types>
  constexpr typename $return::values<false, typeB, previous, cast>::template joinof<typeC, types...>::type::template return_cast<typeA>::type return_cast($return::values<false, typeB, previous, cast> const& valued, typeC&& value, types&&... values) noexcept(
    noexcept((valued, std::declval<typeC>()))
    #if defined(_MSC_VER) || (defined(__clang__) && __cplusplus >= 202002L)
      && noexcept(return_cast<typeA>((valued, std::declval<typeC>()), std::declval<types>()...))
    #endif
  ) { return return_cast<typeA>((valued, std::forward<typeC>(value)), std::forward<types>(values)...); }
#endif

/* Main */
int main(int, char*[]) /* noexcept */ {
  constexpr static auto a1 = ($,  1); static_cast<void>(a1);
  constexpr static auto a2 = (a1, 2); static_cast<void>(a2);
  constexpr static auto a3 = (a2, 3); static_cast<void>(a3);

  constexpr static auto b1 = ($,  4); static_cast<void>(b1);
  constexpr static auto b2 = (b1, 5); static_cast<void>(b2);
  constexpr static auto b3 = (b2, 6); static_cast<void>(b3);

  constexpr static auto c = ($, $); static_cast<void>(c);
  #ifdef __circle_lang__
    constexpr        auto d = (($, 1),       ($, 2));
    constexpr        auto e = (($, 1, 2, 3), ($, 4, 5, 6));
    constexpr        auto f = (a1,           b1);
    constexpr        auto g = (a3,           b3);
  #elif defined(__clang__) || ((defined(__GNUC__) || defined(_MSC_VER)) && false == (defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER)))
    constexpr static auto d = (($, 1),       ($, 2));
    constexpr static auto e = (($, 1, 2, 3), ($, 4, 5, 6));
    constexpr static auto f = (a1,           b1);
    constexpr static auto g = (a3,           b3);
  #else
    const            auto d = (($, 1),       ($, 2));
    const            auto e = (($, 1, 2, 3), ($, 4, 5, 6));
    const            auto f = (a1,           b1);
    const            auto g = (a3,           b3);
  #endif
  static_cast<void>(d), static_cast<void>(e), static_cast<void>(f), static_cast<void>(g);

  #ifdef __circle_lang__
    constexpr        auto h = ($, 1) + 1;
    constexpr        auto i = 1 + ($, 1);
    constexpr        auto j = ($, 1, 2, 3) + 1;
    constexpr        auto k = 1 + ($, 1, 2, 3);
  #elif defined(__clang__) || ((defined(__GNUC__) || defined(_MSC_VER)) && false == (defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER)))
    constexpr static auto h = ($, 1) + 1;
    constexpr static auto i = 1 + ($, 1);
    constexpr static auto j = ($, 1, 2, 3) + 1;
    constexpr static auto k = 1 + ($, 1, 2, 3);
  #else
    const     static auto h = ($, 1) + 1;
    const     static auto i = 1 + ($, 1);
    const     static auto j = ($, 1, 2, 3) + 1;
    const     static auto k = 1 + ($, 1, 2, 3);
  #endif
  static_cast<void>(h), static_cast<void>(i), static_cast<void>(j), static_cast<void>(k);

  #ifdef __circle_lang__
    constexpr        auto l = ($, 1)       + ($, 2);
    constexpr        auto m = ($, 1, 2, 3) + ($, 4, 5, 6);
    constexpr        auto n = a1           + b1;
    constexpr        auto o = a3           + b3;
  #elif defined(__clang__) || ((defined(__GNUC__) || defined(_MSC_VER)) && false == (defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER)))
    constexpr static auto l = ($, 1)       + ($, 2);
    constexpr static auto m = ($, 1, 2, 3) + ($, 4, 5, 6);
    constexpr static auto n = a1           + b1;
    constexpr static auto o = a3           + b3;
  #else
    const     static auto l = ($, 1)       + ($, 2);
    const     static auto m = ($, 1, 2, 3) + ($, 4, 5, 6);
    const     static auto n = a1           + b1;
    const     static auto o = a3           + b3;
  #endif
  static_cast<void>(l), static_cast<void>(m), static_cast<void>(n), static_cast<void>(o);

  // ...
  double array[] = {1.0, 2.0, 3.0, 4.0, 5.0};

  std::printf("%1.2s", "\r\n"); for (double element : array) std::printf("%f%c", element, ' ');
  ($, array[0], array[1], array[2], array[3], array[4]) = ($, array[0], array[1], array[2], array[3], array[4]);
  std::printf("%1.2s", "\r\n"); for (double element : array) std::printf("%f%c", element, ' ');
  ($, array[0], array[1], array[2], array[3], array[4]) = 0.0;
  std::printf("%1.2s", "\r\n"); for (double element : array) std::printf("%f%c", element, ' ');
  ($, array[0], array[1], array[2], array[3], array[4]) = (return_cast<signed char>((return_cast<unsigned char>($, -1.5, -2.5), -3.5, -4.5)), -5.5f);
  std::printf("%1.2s", "\r\n"); for (double element : array) std::printf("%f%c", element, ' ');
  ($, array[0], array[1], array[2], array[3], array[4]) = -($, 1.5, 2.5, array[2], array[3], array[4]);
  std::printf("%1.2s", "\r\n"); for (double element : array) std::printf("%f%c", element, ' ');
  ($, array[0], array[1]) = ([]() noexcept { return ($, 1), ($, 2) + ($, 4); })();
  std::printf("%1.2s", "\r\n"); for (double element : array) std::printf("%f%c", element, ' ');

  // ...
  #ifdef __cpp_variadic_templates
    ($, [](char const message[]) noexcept { std::puts(message); })("\r\n" "Hello, World!");
  #endif
}
