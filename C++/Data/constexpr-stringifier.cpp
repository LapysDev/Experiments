#include <cfloat>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <stdint.h>

#define private public

/* ... [Utilities] */
namespace {
  namespace { union void_t; }

  template <typename> union assess_array;
  template <typename> union assess_function;
  template <typename> union assess_pointer;
  template <typename> union assess_reference;
  template <typename> union baseof;
  template <typename type, type...> struct collection;
  template <bool, typename = void_t, typename = void_t> union conditional_t;
  template <unsigned long long, unsigned long long> union countof;
  template <std::size_t, std::size_t...> struct index_sequence;
  template <std::size_t...> struct integer_collection;
  template <typename> union is_array;
  template <typename> union is_character;
  template <typename> union is_function;
  template <typename> union is_function_pointer;
  template <typename> union is_object_pointer;
  template <typename> union is_pointer;
  template <typename> union is_reference;
  template <typename...> union is_same;
  template <typename> union remove_const;
  template <typename> union remove_cv;
  template <typename> union remove_volatile;

  // ...
  template <typename base> union assess_array { typedef base type; enum { size = 0u, value = false }; };
  template <typename base> union assess_array<base []> { typedef base type; enum { size = 0u, value = true }; };
  template <typename base, std::size_t capacity> union assess_array<base [capacity]> { typedef base type; enum { size = static_cast<unsigned int>(capacity), value = true }; };

  // ... ->> argument `types...`, and variadic state not assessed
  template <typename base> union assess_function { typedef base type; enum { value = false }; };
  template <typename base, typename... types> union assess_function<base (types...)>      { typedef base type; enum { value = true }; };
  template <typename base, typename... types> union assess_function<base (types..., ...)> { typedef base type; enum { value = true }; };
  #if __cplusplus >= 201703L
    template <typename base, typename... types> union assess_function<base (types...) noexcept>      { typedef base type; enum { value = true }; };
    template <typename base, typename... types> union assess_function<base (types..., ...) noexcept> { typedef base type; enum { value = true }; };
  #endif

  // ... ->> additional data (such as `class` scope) not assessed
  template <typename base> union assess_pointer { typedef base type; enum { has_base = false }; enum { value = false }; };
  template <typename base> union assess_pointer<base*>                { typedef base                type; enum { has_base = true }; enum { value = true }; };
  template <typename base> union assess_pointer<base const*>          { typedef base const          type; enum { has_base = true }; enum { value = true }; };
  template <typename base> union assess_pointer<base const volatile*> { typedef base const volatile type; enum { has_base = true }; enum { value = true }; };
  template <typename base> union assess_pointer<base volatile*>       { typedef base volatile       type; enum { has_base = true }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)>                     { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...)>                { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)      const>          { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) const>          { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)      const volatile> { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) const volatile> { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)      volatile>       { typedef base type; enum { has_base = false }; enum { value = true }; };
  template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) volatile>       { typedef base type; enum { has_base = false }; enum { value = true }; };
  #if __cplusplus >= 201703L
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...) noexcept>                     { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) noexcept>                { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)      const noexcept>          { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) const noexcept>          { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)      const volatile noexcept> { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) const volatile noexcept> { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types...)      volatile noexcept>       { typedef base type; enum { has_base = false }; enum { value = true }; };
    template <class object, typename base, typename... types> union assess_pointer<base (object::*)(types..., ...) volatile noexcept>       { typedef base type; enum { has_base = false }; enum { value = true }; };
  #endif

  // ...
  template <typename base> union assess_reference { typedef base type; enum { value = false }; };
  template <typename base> union assess_reference<base&>  { typedef base type; enum { value = true }; };
  template <typename base> union assess_reference<base&&> { typedef base type; enum { value = true }; };

  // ... ->> `enum`s, derived `class`es, and derived `struct`s are ignored
  template <typename base>
  union baseof {
    typedef
      typename conditional_t<
        is_array<base>::value, typename assess_array<base>::type,
      typename conditional_t<
        is_function<base>::value, typename assess_function<base>::type,
      typename conditional_t<
        is_pointer<base>::value, typename assess_pointer<base>::type,
      typename conditional_t<
        is_reference<base>::value, typename assess_reference<base>::type,
      base >::type >::type >::type >::type
    type;
  };

  // ...
  template <typename type, type...>
  struct collection {};
    template <>
    struct integer_collection<> : public collection<std::size_t> {
      enum { total = 0u };
    };

    template <std::size_t integer, std::size_t... integers>
    struct integer_collection<integer, integers...> : public collection<std::size_t, integer, integers...> {
      enum { total = integer + integer_collection<integers...>::total };
    };
      template <std::size_t count, std::size_t... indexes>
      struct index_sequence : public index_sequence<count - 1u, count - 1u, indexes...> {};

      template <std::size_t... indexes>
      struct index_sequence<0u, indexes...> : public integer_collection<0u, indexes...> {};

  // ...
  template <> union conditional_t<false> {};
  template <> union conditional_t<true > {};
  template <typename base> union conditional_t<false, base> {};
  template <typename base> union conditional_t<true , base> { typedef base type; };
  template <typename true_t, typename false_t> union conditional_t<false, true_t, false_t> { typedef false_t type; };
  template <typename true_t, typename false_t> union conditional_t<true , true_t, false_t> { typedef true_t  type; };

  // ...
  template <unsigned long long integer, unsigned long long radix>
  union countof {
    private:
      template <unsigned long long current, unsigned char total>
      union count {
        friend union countof<integer, radix>;
        private: enum { value = count<current / radix, 1u + total>::value };
      };

    public:
      enum { value = count<integer, 0u>::value };
  };
    template <unsigned long long integer, unsigned long long radix>
    template <unsigned char total>
    union countof<integer, radix>::count<0uLL, total> {
      friend union countof<integer, radix>;
      private: enum { value = total };
    };

  // ...
  template <typename type>
  union is_array {
    enum { value = assess_array<type>::value };
  };

  // ...
  template <typename> union is_character { enum { value = false }; };

  template <> union is_character<char>     { enum { value = true }; };
  template <> union is_character<char16_t> { enum { value = true }; };
  template <> union is_character<char32_t> { enum { value = true }; };
  template <> union is_character<wchar_t>  { enum { value = true }; };
  #if __cplusplus >= 202002L
    template <> union is_character<char8_t> { enum { value = true }; };
  #endif

  template <typename type> union is_character<type const>          { enum { value = is_character<type>::value }; };
  template <typename type> union is_character<type const volatile> { enum { value = is_character<type>::value }; };
  template <typename type> union is_character<type volatile>       { enum { value = is_character<type>::value }; };

  // ...
  template <typename type>
  union is_function {
    enum { value = assess_function<type>::value };
  };

  // ...
  template <typename type>
  union is_function_pointer {
    enum { value = assess_pointer<type>::value && (false == assess_pointer<type>::has_base || is_function<typename assess_pointer<type>::type>::value) };
  };

  // ...
  template <typename type>
  union is_object_pointer {
    enum { value = assess_pointer<type>::value && (assess_pointer<type>::has_base && false == is_function<typename assess_pointer<type>::type>::value) };
  };

  // ...
  template <typename type>
  union is_pointer {
    enum { value = assess_pointer<type>::value };
  };

  // ...
  template <typename type>
  union is_reference {
    enum { value = assess_reference<type>::value };
  };

  // ...
  template <typename...>
  union is_same {
    enum { value = false };
  };

  template <typename base>
  union is_same<base> {
    enum { value = true };
  };

  template <typename base, typename... types>
  union is_same<base, base, types...> {
    enum { value = is_same<base, types...>::value };
  };

  // ...
  template <typename base>
  union remove_const { typedef base type; };

  template <typename base>
  union remove_const<base const> { typedef base type; };

  // ...
  template <typename base>
  union remove_cv {
    typedef typename remove_const<typename remove_volatile<base>::type>::type type;
  };

  // ...
  template <typename base>
  union remove_volatile { typedef base type; };

  template <typename base>
  union remove_volatile<base volatile> { typedef base type; };
}

#include <iostream>
namespace {
  constexpr static long double clamp(long double const number, long double const maximum) noexcept {
    return number < maximum ? number : maximum;
  }

  constexpr static unsigned long long clamp(unsigned long long const integer, unsigned long long const maximum) noexcept {
    return integer < maximum ? integer : maximum;
  }

  // ...
  template <typename type>
  constexpr static type instanceof() noexcept;

  // ...
  constexpr static long double BRUH = 1090748135619415929403854669820128643832076401464198256741457059016023337455712704283293103825893418692963576760113404078870676361153328176337335791819453201293648567019545657769144328226729201351285269931196406270260336026480440969175457457972761371674685151986574543459574227180854216484829113510191433779904843906907429804595741823896486554618709041792897601116455079493369203465678175521696079684801558459855685733013566486039513197988373105835405796777612009301237854206866739825615928311027165234639450636848285846852170348270463209512509968067058410966085955092642305503999126249849448107494853836391673145057372360720424255193707930795994041642726134995908110235708792030968796978483320364347331379151776431779364689546781962532253830960478901235464552624735416170604229305704925798779937451183419917038882806949708127234296341630168457825311375190591938038532055263285376832051944705141594038168672584850105364137599906517090544246795943993047853382443557989750469086158380598290390817110977610708111281743815889676802983646880826277564443248867778999148099842770552937804045889869286932455986368097079801144943456484044501617914569752698799884748962448047381796626795915530385096762145649322993391853235732671223977435104048254563405033240765625678089482118619809316732015536399192001899986924279696482083825565538460312042194744384125777271713345334017008082499514551259345301937304531975956497587857813056357548743649252357662809902759268511245695220131755191191178754007743206136757995670389950808100623572398189635493648216795635229703365535937852132326697175361683729221025080424046084144493501461439616151571355283440633672450909832934735553367486392669531577251320558493971529522604761008028335623084242646494241138543741352686635888477730572942421530630919576116463519288087677879156380533208360801124706092572874115363993099695064769539416137905471954311106208397247690315470064624693670821849400811330458450488644556033372998959370992455415748897276576893134153834324225722747123365652717624767122587271223017720171358782071455476769419233276521819687142122867912819815905959535037583849140734279485726542341201739085687544185810789331401517726924334326432746195082356549679165353921485307479751097936588932037591464355435684099891485732748813779092562433055320292412558828857099539048519794851962881214192758407551927719426266389283037153538421489646205312387728364866753456450981869430743506800681796940942358371128706585427614331772236925501440.0L;

  template <std::size_t count>
  union divisor_t {
    long double const value[count];

    constexpr divisor_t() noexcept : value{} {}

    template <std::size_t... indexes, typename... types>
    constexpr divisor_t(index_sequence<0u, indexes...> const, long double const values[], types const... metavalues) noexcept : value{metavalues..., values[indexes]...} {}
  };

  template <>
  union divisor_t<0u> {
    constexpr divisor_t(...) noexcept {}
  };

  template <std::size_t limit>
  static long double modulus(
    long double const dividend, long double const divisor,
    long double const denominator, divisor_t<limit> const& denominators, std::size_t const count
  ) noexcept {
    std::cout << "[...]: " << dividend << ", " << divisor << " [";
      for (std::size_t iterator = 0u; count != iterator; ++iterator)
      std::cout << denominators.value[iterator] << ", ";
    std::cout << "]" "\r\n";

    return (
      0.0L == dividend ? 0.0L :
      0.0L > dividend ? -modulus<limit>(-dividend, divisor, denominator, denominators, count) :
      0.0L > divisor  ? +modulus<limit>(dividend, -divisor, denominator, denominators, count) :
      dividend < divisor ? (
        0u == count && denominator == divisor
        ? dividend :

        0u == count && denominator != divisor
        ? modulus<limit>(dividend, denominator, denominator, denominators, count)
        : modulus<limit>(dividend, denominators.value[0u], denominator, divisor_t<limit>(index_sequence<limit - 1u>(), denominators.value + 1), count - 1u)
      ) : (
        dividend > (divisor * divisor)
        ? modulus<limit>(dividend - (divisor * divisor), divisor * divisor, denominator, divisor_t<limit>(index_sequence<limit - 1u>(), denominators.value, divisor), count + (count != limit)) :

        dividend > (divisor *   10.0L)
        ? modulus<limit>(dividend - (divisor *   10.0L), divisor *   10.0L, denominator, divisor_t<limit>(index_sequence<limit - 1u>(), denominators.value, divisor), count + (count != limit)) :

        dividend > (divisor *    2.0L)
        ? modulus<limit>(dividend - (divisor *    2.0L), divisor *    2.0L, denominator, divisor_t<limit>(index_sequence<limit - 1u>(), denominators.value, divisor), count + (count != limit)) :

        modulus<limit>(dividend - divisor, divisor, denominator, denominators, count)
      )
    );
  }
}

/* Main */
int main() noexcept {
  std::fixed(std::cout);
  std::cout << "[]: " << ULONG_MAX << "\r\n";
  std::scientific(std::cout);

  long double modulo = modulus<256u>(ULONG_MAX, 10.0L, 10.0L, {}, 0u);
  std::printf("[]: %lf", static_cast<double>(modulo));
}
