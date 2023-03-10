/* ...
    --- CITE ---
      #Lapys:
        - Circle:                                             https://lapys.godbolt.org/z/G31KqznbW
        - Clang, GNU, Intel, Microsoft Visual Studio, NVIDIA: https://lapys.godbolt.org/z/rerq94nWo
*/
#include <cstddef>
#include <cstdio>
#include <type_traits>
#include <utility>
#if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 202002L || (defined(__circle_lang__) || defined(__clang__) || defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__GNUC__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER))
# include <version>
#endif

/* ... ->> Metafunction for evaluating operation validity without implicit rvalue-reference-qualification unlike `std::declval<...>()` */
template <typename type>
constexpr static type instanceof() noexcept;

// ...
struct $return final {
  struct nil;

  private:
    // ... ->> Matches any `$return` value(s)
    struct any final {
      template <typename type>
      constexpr operator type() const noexcept {
        return instanceof<type>();
      }
    };

    // ... ->> Metafunctions denoting C++ operators --- WARN (Lapys) -> Dependency on `decltype(...)` keyword prevents ISO C++98 support
    struct values_operation final {
      // ... ->> Metafunction asserting if specified `base` is a `values_operation`
      template <typename, std::nullptr_t = nullptr>
      struct is final {
        static bool const value = false;
      };

      template <typename base, std::nullptr_t specialization> struct is<base const,          specialization> final { static bool const value = is<base>::value; };
      template <typename base, std::nullptr_t specialization> struct is<base const volatile, specialization> final { static bool const value = is<base>::value; };
      template <typename base, std::nullptr_t specialization> struct is<base volatile,       specialization> final { static bool const value = is<base>::value; };

      // ...
      struct nop final {
        template <typename = void, typename = void, typename = void>
        struct evaluate {
          typedef void type;

          static bool const throwable = false;
          static bool const valid     = false;
        };
      };

      // ...
      #define values_operation(name, operator) name final {                                                       \
        template <typename base, typename = void>                                                                 \
        struct evaluate final : public nop::evaluate<base> {};                                                    \
                                                                                                                  \
        template <typename base>                                                                                  \
        struct evaluate<base, decltype(static_cast<void>(operator instanceof<base>()))> final {                   \
          typedef decltype(operator instanceof<base>()) type;                                                     \
                                                                                                                  \
          static bool const throwable = false == noexcept(operator instanceof<base>());                           \
          static bool const valid     = true;                                                                     \
        };                                                                                                        \
                                                                                                                  \
        template <typename type>                                                                                  \
        constexpr static typename evaluate<type>::type value(type&& value) noexcept(!evaluate<type>::throwable) { \
          return operator static_cast<type>(std::forward<type>(value));                                           \
        }                                                                                                         \
      }; template <std::nullptr_t specialization> struct is<name, specialization> final { static bool const value = true; }

      struct values_operation(plus,          +);
      struct values_operation(pre_increment, +);
      #undef values_operation

      // ...
      #define values_operation(name, operator) name final {                                                       \
        template <typename base, typename = void>                                                                 \
        struct evaluate final : public nop::evaluate<base> {};                                                    \
                                                                                                                  \
        template <typename base>                                                                                  \
        struct evaluate<base, decltype(static_cast<void>(instanceof<base>() operator))> final {                   \
          typedef decltype(instanceof<base>() operator) type;                                                     \
                                                                                                                  \
          static bool const throwable = false == noexcept(instanceof<base>() operator);                           \
          static bool const valid     = true;                                                                     \
        };                                                                                                        \
                                                                                                                  \
        template <typename type>                                                                                  \
        constexpr static typename evaluate<type>::type value(type&& value) noexcept(!evaluate<type>::throwable) { \
          return static_cast<type>(std::forward<type>(value)) operator;                                           \
        }                                                                                                         \
      }; template <std::nullptr_t specialization> struct is<name, specialization> final { static bool const value = true; }

      struct values_operation(post_decrement, --);
      struct values_operation(post_increment, ++);
      #undef values_operation

      // ...
      #define values_operation(name, operator) name final {                                                                                         \
        template <typename baseA, typename baseB, typename = void>                                                                                  \
        struct evaluate final : public nop::evaluate<baseA, baseB> {};                                                                              \
                                                                                                                                                    \
        template <typename baseA, typename baseB>                                                                                                   \
        struct evaluate<baseA, baseB, decltype(static_cast<void>(instanceof<baseA>() operator instanceof<baseB>()))> final {                        \
          typedef decltype(instanceof<baseA>() operator instanceof<baseB>()) type;                                                                  \
                                                                                                                                                    \
          static bool const throwable = false == noexcept(instanceof<baseA>() operator instanceof<baseB>());                                        \
          static bool const valid     = true;                                                                                                       \
        };                                                                                                                                          \
                                                                                                                                                    \
        template <typename typeA, typename typeB>                                                                                                   \
        constexpr static typename evaluate<typeA, typeB>::type value(typeA&& valueA, typeB&& valueB) noexcept(!evaluate<typeA, typeB>::throwable) { \
          return (static_cast<typeA>(std::forward<typeA>(valueA)) operator static_cast<typeB>(std::forward<typeB>(valueB)));                        \
        }                                                                                                                                           \
      }; template <std::nullptr_t specialization> struct is<name, specialization> final { static bool const value = true; }

      struct values_operation(add,                     +);
      struct values_operation(assign,                  =);
      struct values_operation(assign_add,              +);
      struct values_operation(assign_bitwise_and,     &=);
      struct values_operation(assign_bitwise_or,      |=);
      struct values_operation(assign_bitwise_xor,     ^=);
      struct values_operation(assign_divide,          /=);
      struct values_operation(assign_left_shift,     <<=);
      struct values_operation(assign_modulo,          %=);
      struct values_operation(assign_multiply,        *=);
      struct values_operation(assign_right_shift,    >>=);
      struct values_operation(assign_subtract,        -=);
      struct values_operation(bitwise_and,             &);
      struct values_operation(bitwise_or,              |);
      struct values_operation(bitwise_xor,             ^);
      struct values_operation(boolean_and,            &&);
      struct values_operation(boolean_or,             ||);
      struct values_operation(divide,                  /);
      struct values_operation(equals,                 ==);
      struct values_operation(equals_greater,         <=);
      struct values_operation(equals_lesser,          >=);
      struct values_operation(greater,                 >);
      struct values_operation(left_shift,             <<);
      struct values_operation(lesser,                  <);
      struct values_operation(member_pointer_access, ->*);
      struct values_operation(modulo,                  %);
      struct values_operation(multiply,                *);
      struct values_operation(right_shift,            >>);
      struct values_operation(subtract,                -);
      struct values_operation(unequals,               !=);
      #ifdef __cpp_impl_three_way_comparison
        struct values_operation(compare, <=>);
      #endif
      #undef values_operation

      // ...
      #define values_operation(name) name final {                                                                                                   \
        template <typename baseA, typename baseB, typename = void>                                                                                  \
        struct evaluate final : public nop::evaluate<baseA, baseB> {};                                                                              \
                                                                                                                                                    \
        template <typename baseA, typename baseB>                                                                                                   \
        struct evaluate<baseA, baseB, decltype(static_cast<void>(instanceof<baseA>()[instanceof<baseB>()]))> final {                                \
          typedef decltype(instanceof<baseA>()[instanceof<baseB>()]) type;                                                                          \
                                                                                                                                                    \
          static bool const throwable = false == noexcept(instanceof<baseA>()[instanceof<baseB>()]);                                                \
          static bool const valid     = true;                                                                                                       \
        };                                                                                                                                          \
                                                                                                                                                    \
        template <typename typeA, typename typeB>                                                                                                   \
        constexpr static typename evaluate<typeA, typeB>::type value(typeA&& valueA, typeB&& valueB) noexcept(!evaluate<typeA, typeB>::throwable) { \
          return static_cast<typeA>(std::forward<typeA>(valueA))[static_cast<typeB>(std::forward<typeB>(valueB))];                                  \
        }                                                                                                                                           \
      }; template <std::nullptr_t specialization> struct is<name, specialization> final { static bool const value = true; }

      struct values_operation(subscript);
      #undef values_operation

      // ...
      #define values_operation(name, operatorA, operatorB) name final {                                                                                                               \
        template <typename baseA, typename baseB, typename baseC, typename = void>                                                                                                    \
        struct evaluate final : public nop::evaluate<baseA, baseB, baseC> {};                                                                                                         \
                                                                                                                                                                                      \
        template <typename baseA, typename baseB, typename baseC>                                                                                                                     \
        struct evaluate<baseA, baseB, baseC, decltype(static_cast<void>(instanceof<baseA>() operatorA instanceof<baseB>() operatorB instanceof<baseC>()))> final {                    \
          typedef decltype(instanceof<baseA>() operatorA instanceof<baseB>() operatorB instanceof<baseC>()) type;                                                                     \
                                                                                                                                                                                      \
          static bool const throwable = false == noexcept(instanceof<baseA>() operatorA instanceof<baseB>() operatorB instanceof<baseC>());                                           \
          static bool const valid     = true;                                                                                                                                         \
        };                                                                                                                                                                            \
                                                                                                                                                                                      \
        template <typename typeA, typename typeB, typename typeC>                                                                                                                     \
        constexpr static typename evaluate<typeA, typeB, typeC>::type value(typeA&& valueA, typeB&& valueB, typeC&& valueC) noexcept(!evaluate<typeA, typeB, typeC>::throwable) {     \
          return static_cast<typeA>(std::forward<typeA>(valueA)) operatorA static_cast<typeB>(std::forward<typeB>(valueB)) operatorB static_cast<typeC>(std::forward<typeC>(valueC)); \
        }                                                                                                                                                                             \
      }; template <std::nullptr_t specialization> struct is<name, specialization> final { static bool const value = true; }

      struct values_operation(ternary, ?, :);
      #undef values_operation
    };

    // ... ->> Collection of requested types to sequentially cast an object to
    template <typename base = void, typename = void>
    struct values_cast final {
      template <typename type>
      constexpr static type&& value(type&& value) noexcept {
        return std::forward<type&&>(value);
      }
    };

    template <typename base>
    struct values_cast<base, values_cast<> > final {
      typedef base type;

      template <typename type>
      constexpr static base value(type&& value) noexcept(noexcept((base) std::declval<type>())) {
        return (base) std::forward<type>(value);
      }
    };

    template <typename base, typename subbase>
    struct values_cast<base, values_cast<subbase> > final {
      typedef typename values_cast<subbase>::type type;

      template <typename type>
      constexpr static typename values_cast<subbase>::type value(type&& value) noexcept(noexcept((base) std::declval<type>()) && noexcept(values_cast<subbase>::value(instanceof<base>()))) {
        return values_cast<subbase>::value((base) std::forward<type>(value));
      }
    };

    // ... ->> Collection of object (references)
    template <bool = false, typename = void, class = void, class = values_cast<>, std::nullptr_t = nullptr>
    struct values;

    template <std::nullptr_t specialization>
    struct values<false, void, void, values_cast<>, specialization> {
      friend struct $return;
      template <bool, typename, class, class, std::nullptr_t> friend struct values;

      typedef values_cast<> cast;
      typedef values     <> previous;
      typedef void          type;

      /* ... */
      private:
        static std::size_t const length = 0u;

        /* ... ->> Metafunction denoting `values` type when an object is added to the collection */
        template <typename base>
        struct addof final {
          typedef values<false, typename std::conditional<std::is_constructible<base, base>::value && (
            std::is_reference<base>                                     ::value ||
            std::is_same     <base, typename std::remove_cv<base>::type>::value
          ), base, base&&>::type, previous, cast> type;
        };

        // ... ->> Metafunction denoting `values` type with re-specified `allocated` flag
        template <bool suballocated>
        struct allocate final {
          typedef values<suballocated> type;
        };

        // ... ->> Metafunction denoting `values_cast` type used when referring to an object in `values`
        template <class, class = cast>
        struct castof;

        // ... ->> Metafunction denoting `values` type after concatenation with another `values`
        template <class>
        struct concatenationof;

        template <bool allocated>
        struct concatenationof<values<allocated> > final {
          typedef values<allocated> type;
        };

        template <bool allocated, typename base, class previous, class cast>
        struct concatenationof<values<allocated, base, previous, cast> > final {
          typedef values<true, base, typename concatenationof<previous>::type, cast> type;
        };

        // ... ->> Metafunction asserting if specified `base` is a `values` collection
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

        // ... ->> Metafunction generating `values` from a specified `base`
        template <typename base, class subvalues = values<true> >
        struct buildof final {
          typedef typename std::conditional<is<base>::value, typename std::remove_cv<typename std::remove_reference<base>::type>::type, subvalues>::type type;
        };

        // ... ->> Metafunction denoting `values` type when an operation is performed on its collection
        template <class, class subvalues, class = values, class = subvalues>
        struct operationof final {
          typedef values<> type;
        };

      public:
        static bool const allocated = false;

        /* ... ->> Metafunction denoting `values` type after a series of `struct values<>::addof`s and `struct values<>::concatenationof` */
        #ifdef __cpp_variadic_templates
          template <typename...>
          struct joinof final {
            typedef values<> type;
          };

          template <typename base, typename... bases>
          struct joinof<base, bases...> final {
            typedef typename std::conditional<
              is<base>::value,
              concatenationof<typename std::remove_cv<typename std::remove_reference<base>::type>::type>,
              addof<base>
            >::type::type::template joinof<bases...>::type type;
          };
        #endif

      /* ... */
      public:
        constexpr values()                noexcept {}
        constexpr values(values<> const&) noexcept {}

      /* ... */
      #if defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)
        public:
      #else
        private:
      #endif
        // ... ->> Concatenate two `values`
        template <class subvalues>
        constexpr static subvalues&& concatenate(values const&, subvalues&& valued) noexcept {
          return std::forward<subvalues>(valued);
        }

        // ... ->> Compute an operation resulting in a new `values` collection
        template <class, class subvalues, class /* = values */, class /* = subvalues */>
        constexpr values<> const& operate(subvalues const&) const noexcept {
          return *this;
        }

      /* ... */
      template <typename type>
      constexpr friend typename std::enable_if<false != is<type>::value, type&&>::type operator ,(values const& valuedA, type&& valuedB) noexcept {
        return concatenate(valuedA, std::forward<type>(valuedB));
      }

      template <typename type>
      constexpr friend typename std::enable_if<false == is<type>::value, typename addof<type>::type>::type operator ,(values const& valued, type&& value)
        #ifdef _MSC_VER
          noexcept(std::is_reference<type>::value)
        #else
          noexcept(noexcept(typename addof<type>::type(std::declval<type>(), instanceof<values const&>())))
        #endif
      { return {std::forward<type>(value), valued}; }
    };

    template <std::nullptr_t specialization>
    struct values<true, void, void, values_cast<>, specialization> : public values<false> {};

    template <typename base, class _previous, class _cast, std::nullptr_t specialization>
    struct values<false, base, _previous, _cast, specialization> : public values<false> {
      friend struct $return;
      template <bool, typename, class, class, std::nullptr_t> friend struct values;
      template <typename typeA, typename typeB, class previous, class cast> constexpr friend values<false, typeB&&, previous, values_cast<typeA, cast> > return_cast(values<false, typeB, previous, cast> const&) noexcept;

      typedef _cast     cast;
      typedef _previous previous;
      typedef  base     type;

      /* ... */
      public:
        static bool const allocated = false;

      private:
        typedef values_operation operations;
        static std::size_t const length = previous::length + 1u;

        // ... ->> See `struct values<>::allocate`
        template <bool suballocated>
        struct allocate final {
          typedef values<suballocated, base, previous, cast> type;
        };

        // ... ->> See `struct values<>::buildof`
        template <typename subbase, class subvalues = values<true> >
        struct buildof final {
          typedef typename std::conditional<
            is<subbase>::value,
            typename std::remove_cv<typename std::remove_reference<subbase>::type>::type,
            typename previous::template buildof<subbase, values<true, subbase&&, subvalues, values_cast<> > >::type
          >::type type;
        };

        // ... ->> See `struct values<>::castof`
        template <class subvalues, class subcast = cast>
        struct castof final {
          typedef typename previous::template castof<subvalues, typename castof<values, subcast>::type>::type type;
        };

        template <bool suballocated, class subcast>
        struct castof<values<suballocated, base, previous, cast>, subcast> final {
          typedef typename std::conditional<std::is_same<cast, values_cast<> >::value, subcast, cast>::type type;
        };

      public:
        // ... ->> See `struct values<>::add`
        template <typename subbase>
        struct addof final {
          typedef values<false, typename std::conditional<std::is_constructible<subbase, subbase>::value && (
            std::is_reference<subbase>                                        ::value ||
            std::is_same     <subbase, typename std::remove_cv<subbase>::type>::value
          ), subbase, subbase&&>::type, values<false, base, previous, cast>, values_cast<> > type;
        };

        // ... ->> See `struct values<>::concatenationof`
        template <class>
        struct concatenationof;

        template <bool suballocated, typename subbase, class subprevious, class subcast>
        struct concatenationof<values<suballocated, subbase, subprevious, subcast> > final {
          typedef values<true, subbase, typename subprevious::template concatenationof<values>::type, subcast> type;
        };

        // ... ->> See `struct values<>::joinof`
        #ifdef __cpp_variadic_templates
          template <typename...>
          struct joinof final {
            typedef values<false, base, previous, cast> type;
          };

          template <typename subbase, typename... subbases>
          struct joinof<subbase, subbases...> final {
            typedef typename std::conditional<
              is<subbase>::value,
              concatenationof<typename std::remove_cv<typename std::remove_reference<subbase>::type>::type>,
              addof<subbase>
            >::type::type::template joinof<subbases...>::type type;
          };
        #endif

        // ... ->> See `struct values<>::operationof` --- WARN (Lapys) -> Dependency on `decltype(...)` keyword prevents ISO C++98 support
        template <class, class subvalues, class = values, class = subvalues>
        struct operationof;

        template <class operation, bool suballocated, class valuesA, class valuesB>
        struct operationof<operation, values<suballocated>, valuesA, valuesB> final {
          typedef values<suballocated> type;
        };

        template <class operation, bool suballocated, typename subbase, class subprevious, class subcast, class valuesA, class valuesB>
        struct operationof<operation, values<suballocated, subbase, subprevious, subcast>, valuesA, valuesB> final {
          private:
            typedef typename valuesA::template castof<values<false,        base,    previous,    cast>    >::type castA;
            typedef typename valuesB::template castof<values<suballocated, subbase, subprevious, subcast> >::type castB;

            typedef typename operation::template evaluate<
              typename std::conditional<std::is_same<castA, values_cast<> >::value, base   &&, castA>::type,
              typename std::conditional<std::is_same<castB, values_cast<> >::value, subbase&&, castB>::type
            > evaluation;

          public:
            static bool const value = evaluation::valid;
            typedef typename std::conditional<value, values<true, typename evaluation::type, typename previous::template operationof<operation, subprevious, valuesA, valuesB>::type, cast>, values>::type type;
        };

      /* ... */
      private:
        base            value;
        previous const &prevalues;

      /* ... */
      public:
        constexpr values(base&& value, previous const& previous) noexcept(noexcept(base(instanceof<base&&>()))) :
          value    (static_cast<base>(static_cast<base&&>(value))),
          prevalues(previous)
        {}

        constexpr values(values<false, base, previous, cast> const& valued) noexcept(noexcept(values<false, base, previous, cast>(instanceof<base&&>(), instanceof<previous const&>()))) :
          values::values(static_cast<base&&>(const_cast<base&>(valued.value)), valued.prevalues)
        {}

      /* ... */
      public:
        // ... ->> Construct `values` from a specified `type`; See `struct values<>::buildof`
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
          return values::build(std::forward<type>(value), values<true, type&&, subvalues, values_cast<> >{static_cast<type&&>(value), valued});
        }

        template <typename type>
        constexpr static typename std::enable_if<false == is<type>::value, typename buildof<type>::type>::type build(type&& value) noexcept {
          return values::build(std::forward<type>(value), values<true, type&&, values<true>, values_cast<> >{static_cast<type&&>(value), {}});
        }

        // ... ->> See `values<>::concatenate(...)`
        constexpr static values<> concatenate(values<> const&, values<> const&) noexcept {
          return {};
        }

        template <class subvalues>
        constexpr static typename values<>::template concatenationof<subvalues>::type concatenate(subvalues const& valued, values<> const&) noexcept(noexcept(typename subvalues::type(instanceof<typename subvalues::type>()))) {
          return {static_cast<typename subvalues::type>(valued.value), concatenate(valued.prevalues, {})};
        }

        template <class subvaluesA, class subvaluesB>
        constexpr static typename subvaluesB::template concatenationof<subvaluesA>::type concatenate(subvaluesA const& valuedA, subvaluesB const& valuedB) noexcept(noexcept(typename subvaluesB::type(instanceof<typename subvaluesB::type>()))) {
          return {static_cast<typename subvaluesB::type>(valuedB.value), concatenate(valuedA, valuedB.prevalues)};
        }

        // ... ->> See `values<>::operate(...)`
        template <class operation, class subvalues, class, class>
        constexpr typename std::enable_if<false == operationof<operation, subvalues>::value || values::length != subvalues::length, any>::type operate(subvalues const&) const noexcept {
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
          static_assert(invalid_object_pack_operation::value, "Cannot perform binary operation on object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_right_shift::value, "Cannot shift object packs of incompatible types or unequal size");
          static_assert(invalid_object_pack_subtraction::value, "Cannot subtract object packs of incompatible types or unequal size");
          #ifdef __cpp_impl_three_way_comparison
            static_assert(invalid_object_pack_comparison::value, "Cannot compare object packs of incompatible types or unequal size");
          #endif

          // ...
          return {};
        }

        template <class operation, class subvalues, class valuesA, class valuesB>
        constexpr typename std::enable_if<false != operationof<operation, subvalues>::value && values::length == subvalues::length, typename operationof<operation, subvalues>::type>::type operate(subvalues const& valued) const noexcept(
          noexcept(operation::value(
            valuesA::template castof<values>   ::type::value(instanceof<typename values   ::type>()),
            valuesB::template castof<subvalues>::type::value(instanceof<typename subvalues::type>())
          ))
          #if defined(__clang__) || false == (defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER))
            && noexcept(typename operationof<operation, subvalues>::type(
              operation::value(valuesA::template castof<values>::type::value(instanceof<typename values::type>()), valuesB::template castof<subvalues>::type::value(instanceof<typename subvalues::type>())),
              instanceof<typename values::previous const&>().template operate<operation, typename subvalues::previous, valuesA, valuesB>(instanceof<typename subvalues::previous const&>())
            ))
          #endif
        ) {
          return {operation::value(
            valuesA::template castof<values>   ::type::value((typename values   ::type) this -> value),
            valuesB::template castof<subvalues>::type::value((typename subvalues::type) valued .value)
          ), this -> prevalues.template operate<operation, typename subvalues::previous, valuesA, valuesB>(valued.prevalues)};
        }

        // ... ->> Resolver for `friend` operator overloads
        template <class operation, typename type>
        constexpr typename operationof<operation, typename std::remove_cv<typename std::remove_reference<type>::type>::type>::type suboperate(type&& valued) const noexcept(noexcept(this -> template operate<operation, typename std::remove_cv<typename std::remove_reference<type>::type>::type, values, typename std::remove_cv<typename std::remove_reference<type>::type>::type>(valued))) {
          return this -> template operate<operation, typename std::remove_cv<typename std::remove_reference<type>::type>::type, values, typename std::remove_cv<typename std::remove_reference<type>::type>::type>(valued);
        }

      /* ... */
      template <typename type>
      constexpr typename operationof<operations::assign, typename buildof<type>::type>::type operator =(type&& value) const noexcept {
        return this -> template suboperate<operations::assign>(values::build(std::forward<type>(value)));
      }

      template <typename type>
      constexpr friend typename std::enable_if<false != is<type>::value, typename std::remove_reference<type>::type::template concatenationof<values>::type>::type operator ,(values const& valued, type&& value)
        #ifdef __circle_lang__
          noexcept(false)
        #else
          noexcept(noexcept(values::concatenate(valued, value)))
        #endif
      { return values::concatenate(valued, value); }

      template <typename type>
      constexpr friend typename std::enable_if<false == is<type>::value, typename addof<type>::type>::type operator ,(values const& valued, type&& value)
        #if defined(__circle_lang__) || defined(_MSC_VER)
          noexcept(std::is_reference<type>::value)
        #else
          noexcept(noexcept(typename addof<type>::type(std::declval<type>(), instanceof<values const&>())))
        #endif
      { return {std::forward<type>(value), valued}; }

      // ...
      template <typename type>
      constexpr friend typename buildof<type>::type::template operationof<operations::add, values>::type operator +(type&& value, values const& valued)
        #if defined(__circle_lang__) || defined(_MSC_VER)
          noexcept(false)
        #else
          noexcept(noexcept(values::build(std::declval<type>()).template suboperate<operations::add>(valued)))
        #endif
      { return values::build(std::forward<type>(value)).template suboperate<operations::add>(valued); }

      #if defined(__circle_lang__) || defined(_MSC_VER)
        template <typename type>
        constexpr typename std::enable_if<false == is<type>::value, typename values::template operationof<operations::add, typename buildof<type>::type>::type>::type operator +(type&& value) const noexcept(noexcept(*this + values::build(std::declval<type>()))) {
          return *this + values::build(std::forward<type>(value));
        }
      #else
        template <typename type>
        constexpr friend typename std::enable_if<false == is<type>::value, typename operationof<operations::add, typename buildof<type>::type>::type>::type operator +(values const& valued, type&& value) noexcept(noexcept(valued + values::build(std::declval<type>()))) {
          return valued + values::build(std::forward<type>(value));
        }
      #endif
    };

    template <typename base, class _previous, class _cast, std::nullptr_t specialization>
    struct values<true, base, _previous, _cast, specialization> final : public values<false, base, _previous, _cast> {
      friend struct $return;
      template <bool, typename, class, class, std::nullptr_t> friend struct values;

      typedef _cast     cast;
      typedef _previous previous;
      typedef  base     type;

      private:
        typedef values<false, base, previous, cast> subvalues;
        using subvalues::allocate;

        /* ... */
        previous prevalues;

      public:
        static bool const allocated = true;

        /* ... */
        constexpr values(base&& value, previous const& previous) noexcept(noexcept(subvalues(instanceof<base&&>(), instanceof<values::previous const&>())) && noexcept(values::previous(instanceof<values::previous const&>()))) :
          subvalues::values(static_cast<base&&>(value), this -> prevalues),
          prevalues{previous}
        {}

        constexpr values(values<true, base, previous, cast> const& valued) noexcept(noexcept(values<true, base, previous, cast>(instanceof<base&&>(), instanceof<previous const&>()))) :
          values::values(static_cast<base&&>(const_cast<base&>(valued.value)), valued.prevalues)
        {}
    };

  public:
    struct nil final : public values<> {};

    /* ... */
    template <typename typeA, typename typeB, class previous, class cast> constexpr friend values<false, typeB&&, previous, values_cast<typeA, cast> > return_cast(values<false, typeB, previous, cast> const&) noexcept;
    template <typename typeA, typename typeB, class previous, class cast> constexpr friend values<false, typeB&&, previous, values_cast<typeA, cast> > return_cast(values<true,  typeB, previous, cast> const&) noexcept;

    #ifdef __cpp_variadic_templates
      template <typename typeA, bool allocated, typename typeB, class previous, class cast, typename typeC, typename... types>
      constexpr friend values<
        values<allocated, typeB, previous, cast>::template joinof<typeC, types...>::type::allocated,
        typename values<allocated, typeB, previous, cast>::template joinof<typeC, types...>::type::type,
        typename values<allocated, typeB, previous, cast>::template joinof<typeC, types...>::type::previous,
        values_cast<typeA, typename values<allocated, typeB, previous, cast>::template joinof<typeC, types...>::type::cast>
      > return_cast(values<allocated, typeB, previous, cast> const&, typeC&&, types&&...) noexcept;
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
constexpr $return::values<false, typeB&&, previous, $return::values_cast<typeA, cast> > return_cast($return::values<false, typeB, previous, cast> const& valued) noexcept {
  return {static_cast<typeB&&>(const_cast<typeB&>(valued.value)), valued.prevalues};
}

template <typename typeA, typename typeB, class previous, class cast>
constexpr $return::values<false, typeB&&, previous, $return::values_cast<typeA, cast> > return_cast($return::values<true, typeB, previous, cast> const& valued) noexcept {
  return return_cast<typeA>(static_cast<$return::values<false, typeB, previous, cast> const&>(valued));
}

#ifdef __cpp_variadic_templates
  template <typename typeA, bool allocated, typename typeB, class previous, class cast, typename typeC, typename... types>
  constexpr $return::values<
    $return::values<allocated, typeB, previous, cast>::template joinof<typeC, types...>::type::allocated,
    typename $return::values<allocated, typeB, previous, cast>::template joinof<typeC, types...>::type::type,
    typename $return::values<allocated, typeB, previous, cast>::template joinof<typeC, types...>::type::previous,
    $return::values_cast<typeA, typename $return::values<allocated, typeB, previous, cast>::template joinof<typeC, types...>::type::cast>
  > return_cast($return::values<allocated, typeB, previous, cast> const& valued, typeC&& value, types&&... values) noexcept {
    return return_cast<typeA>((valued, std::forward<typeC>(value)), std::forward<types>(values)...);
  }
#endif

/* Main */
#include <cstdlib>
#include <csignal>

int main(int, char*[]) /* noexcept */ {
  std::signal(SIGSEGV, +[](int const) { std::puts("segfault"), std::exit(EXIT_FAILURE); });
  std::puts("[begin]");

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
  #elif (defined(__clang__) || ((defined(__GNUC__) || defined(_MSC_VER)) && false == (defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER))))
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
  #elif (defined(__clang__) || ((defined(__GNUC__) || defined(_MSC_VER)) && false == (defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER))))
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
  #elif (defined(__clang__) || ((defined(__GNUC__) || defined(_MSC_VER)) && false == (defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER))))
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

  double array[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  std::printf("%1.2s", "\r\n"); for (double element : array) std::printf("%f%c", element, ' ');
  ($, array[0], array[1], array[2], array[3], array[4], array[5]) = 0.0;
  std::printf("%1.2s", "\r\n"); for (double element : array) std::printf("%f%c", element, ' ');
  ($, array[0], array[1], array[2], array[3], array[4], array[5]) = (return_cast<signed char>($, -1.5), -2.5, -3.5, -4.5, -5.5, -6.5);

  std::puts("\r\n" "[end]");
}
