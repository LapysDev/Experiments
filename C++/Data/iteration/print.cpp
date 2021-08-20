#include <cfloat>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <stdbool.h>

/* ... --- NOTE (Lapys) -> Feel free to adapt for other character formats: `char8_t`, `char16_t`, `char32_t`, `wchar_t` */
namespace {
  template <bool, typename> union assertion;
  template <typename base> union assertion<true, base> { typedef base type; };

  template <std::size_t count, std::size_t... indexes> struct index_sequence : index_sequence<count - 1u, count - 1u, indexes...> {};
  template <std::size_t... indexes> struct index_sequence<0u, indexes...> {};

  template <typename char_t, std::size_t length>
  struct string {
    template <typename subchar_t, std::size_t capacity>
    constexpr friend string<subchar_t, capacity> stringify(subchar_t const (&string)[capacity]);

    public:
      char_t const value[length];

      // ...
      constexpr string() :
        value{}
      {}

      constexpr string(string<char_t, 0u> const&) :
        value{}
      {}

      template <typename... types>
      constexpr string(char_t const character, types const... characters) :
        value{character, characters...}
      {}

      template <std::size_t capacity>
      constexpr string(char_t const (&string)[capacity]) :
        string<char_t, length>::string(string, index_sequence<(capacity < length ? capacity : length)>())
      {}

      template <std::size_t capacity>
      constexpr string(string<char_t, capacity> const& string) :
        string<char_t, length>::string(string.value)
      {}

      template <std::size_t capacity, std::size_t... indexes>
      constexpr string(char_t const (&string)[capacity], index_sequence<0u, indexes...> const) :
        value{string[indexes]...}
      {}
  };

  template <typename char_t>
  struct string<char_t, 0u> {
    public: template <typename, std::size_t> friend struct string;
    public: constexpr string(...) {}
  };

  // ... --> clamp(...)
  constexpr long double clamp(long double const number, long double const maximum) {
    return number < maximum ? number : maximum;
  }

  constexpr unsigned long long clamp(unsigned long long const integer, unsigned long long const maximum) {
    return integer < maximum ? integer : maximum;
  }

  // ... --> concatenate(...)
  template <typename char_t, std::size_t capacity>
  constexpr string<char_t, capacity> const& concatenate(::string<char_t, 0u> const&, string<char_t, capacity> const& string) {
    return string;
  }

  template <typename char_t, std::size_t capacity>
  constexpr string<char_t, capacity> const& concatenate(string<char_t, capacity> const& string, ::string<char_t, 0u> const&) {
    return string;
  }

  template <typename char_t, std::size_t capacityA, std::size_t capacityB, std::size_t... indexesA, std::size_t... indexesB>
  constexpr string<char_t, capacityA + capacityB> concatenate(string<char_t, capacityA> const& stringA, string<char_t, capacityB> const& stringB, index_sequence<0u, indexesA...> const, index_sequence<0u, indexesB...> const) {
    return {stringA.value[indexesA]..., stringB.value[indexesB]...};
  }

  template <typename char_t, std::size_t capacityA, std::size_t capacityB>
  constexpr string<char_t, capacityA + capacityB> concatenate(string<char_t, capacityA> const& stringA, string<char_t, capacityB> const& stringB) {
    return concatenate(stringA, stringB, index_sequence<capacityA>(), index_sequence<capacityB>());
  }

  // ... --> modulus(...)
  constexpr long double modulus(long double const dividend, long double const divisor) {
    return (
      0.00L > dividend ? -modulus(-dividend, divisor) :
      0.00L > divisor ? +modulus(dividend, -divisor) :
      dividend >= divisor ? modulus(dividend - divisor, divisor) : dividend
    );
  }

  constexpr unsigned long long modulus(unsigned long long const dividend, unsigned long long const divisor) {
    return dividend % divisor;
  }

  // ... --> repeat(...)
  template <std::size_t length, typename char_t, std::size_t capacity>
  constexpr typename assertion<0u == length, string<char_t, 0u> >::type repeat(string<char_t, capacity> const&) {
    return {};
  }

  template <std::size_t length, typename char_t, std::size_t capacity>
  constexpr typename assertion<1u == length, string<char_t, capacity> >::type repeat(string<char_t, capacity> const& string) {
    return string;
  }

  template <std::size_t length, typename char_t, std::size_t capacity>
  constexpr typename assertion<1u != length, string<char_t, capacity * length> >::type repeat(string<char_t, capacity> const& string) {
    return concatenate(string, repeat<length - 1u>(string));
  }

  // ... --> resize(...)
  template <std::size_t length, typename char_t, std::size_t capacity>
  constexpr string<char_t, length> resize(string<char_t, capacity> const& string) {
    return {string};
  }

  // ... --> reverse(...)
  template <typename char_t>
  constexpr string<char_t, 0u> const& reverse(string<char_t, 0u> const& string) {
    return string;
  }

  template <typename char_t, std::size_t capacity, std::size_t... indexes>
  constexpr string<char_t, capacity> reverse(string<char_t, capacity> const& string, index_sequence<0u, indexes...> const) {
    return {string.value[capacity - indexes - 1u]...};
  }

  template <typename char_t, std::size_t capacity>
  constexpr string<char_t, capacity> reverse(string<char_t, capacity> const& string) {
    return reverse(string, index_sequence<capacity>());
  }

  // ... --> stringify(...)
  template <typename char_t>
  constexpr string<char_t, 5u> stringify(bool const boolean) {
    return boolean ? string<char_t, 5u>('t', 'r', 'u', 'e', '\0') : string<char_t, 5u>('f', 'a', 'l', 's', 'e');
  }

  template <typename char_t>
  constexpr string<char_t, 1u> stringify(char_t const character) {
    return {character};
  }

  template <typename char_t, std::size_t capacity>
  constexpr string<char_t, capacity> stringify(char_t const (&string)[capacity]) {
    return {string};
  }

  template <typename char_t, typename... types>
  constexpr typename assertion<38u == sizeof...(types), string<char_t, 38u> >::type stringify(unsigned long long const, unsigned long long const, types const... digits) {
    return {digits...};
  }

  template <typename char_t, typename... types>
  constexpr typename assertion<38u != sizeof...(types), string<char_t, 38u> >::type stringify(unsigned long long const integer, unsigned long long const radix = 10uLL, types const... digits) {
    return stringify<char_t, char_t, types...>(integer / 10uLL, radix, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[clamp(modulus(integer, radix), 36uLL)], digits...);
  }

// 340282346638528859811704183484516925440
// 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368
// 1189731495357231765021263853030970205169063322294624200440323733891737005522970722616410290336528882853545697807495577314427443153670288434198125573853743678673593200706973263201915918282961524365529510646791086614311790632169778838896134786560600399148753433211454911160088679845154866512852340149773037600009125479393966223151383622417838542743917838138717805889487540575168226347659235576974805113725649020884855222494791399377585026011773549180099796226026859508558883608159846900235645132346594476384939859276456284579661772930407806609229102715046085388087959327781622986827547830768080040150694942303411728957777100335714010559775242124057347007386251660110828379119623008469277200965153500208474470792443848545912886723000619085126472111951361467527633519562927597957250278002980795904193139603021470997035276467445530922022679656280991498232083329641241038509239184734786121921697210543484287048353408113042573002216421348917347174234800714880751002064390517234247656004721768096486107994943415703476320643558624207443504424380566136017608837478165389027809576975977286860071487028287955567141404632615832623602762896316173978484254486860609948270867968048078702511858930838546584223040908805996294594586201903766048446790926002225410530775901065760671347200125846406957030257138960983757998926954553052368560758683179223113639519468850880771872104705203957587480013143131444254943919940175753169339392366881856189129931729104252921236835159922322050998001677102784035360140829296398115122877768135706045789343535451696539561254048846447169786893211671087229088082778350518228857646062218739702851655083720992349483334435228984751232753726636066213902281264706234075352071724058665079518217303463782631353393706774901950197841690441824738063162828586857741432581165364040218402724913393320949219498422442730427019873044536620350262386957804682003601447291997123095530057206141866974852846856186514832715974481203121946751686379343096189615107330065552421485195201762858595091051839472502863871632494167613804996319791441870254302706758495192008837915169401581740046711477877201459644461175204059453504764721807975761111720846273639279600339670470037613374509553184150073796412605047923251661354841291884211340823015473304754067072818763503617332908005951896325207071673904547777129682265206225651439919376804400292380903112437912614776255964694221981375146967079446870358004392507659451618379811859392049544036114915310782251072691486979809240946772142727012404377187409216756613634938900451232351668146089322400697993176017805338191849981933008410985993938760292601390911414526003720284872132411955424282101831204216104467404621635336900583664606591156298764745525068145003932941404131495400677602951005962253022823003631473824681059648442441324864573137437595096416168048024129351876204668135636877532814675538798871771836512893947195335061885003267607354388673368002074387849657014576090349857571243045102038730494854256702479339322809110526041538528994849203991091946129912491633289917998094380337879522093131466946149705939664152375949285890960489916121944989986384837022486672249148924678410206183364627416969576307632480235587975245253737035433882960862753427740016333434055083537048507374544819754722228975281083020898682633020285259923084168054539687911418297629988964576482765287504562854924265165217750799516259669229114977788962356670956627138482018191348321687995863652637620978285070099337294396784639879024914514222742527006363942327998483976739987154418554201562244154926653014515504685489258620276085761837129763358761215382565129633538141663949516556000264159186554850057052611431952919918807954522394649627635630178580896692226406235382898535867595990647008385687123810329591926494846250768992258419305480763620215089022149220528069842018350840586938493815498909445461977893029113576516775406232278298314033473276603952231603422824717528181818844304880921321933550869873395861276073670866652375555675803171490108477320096424318780070008797346032906278943553743564448851907191616455141155761939399690767415156402826543664026760095087523945507341556135867933066031744720924446513532366647649735400851967040771103640538150073486891798364049570606189535005089840913826869535090066783324472578712196604415284924840041850932811908963634175739897166596000759487800619164094854338758520657116541072260996288150123144377944008749301944744330784388995701842710004808305012177123560622895076269042856800047718893158089358515593863176652948089031267747029662545110861548958395087796755464137944895960527975209874813839762578592105756284401759349324162148339565350189196811389091843795734703269406342890087805846940352453479398080674273236297887100867175802531561302356064878709259865288416350972529537091114317204887747405539054009425375424119317944175137064689643861517718849867010341532542385911089624710885385808688837777258648564145934262121086647588489260031762345960769508849149662444156604419552086811989770240
//
  template <typename char_t, std::size_t capacity>
  string<char_t, LDBL_DIG + LDBL_MANT_DIG> stringify(long double const number, unsigned long long const radix, string<char_t, capacity> const& string) {
    std::puts("...");
    return (0.00L > number ? -number : number) > 41.00L/*static_cast<long double>(ULLONG_MAX)*/ ?
      (
        stringify<char_t, capacity + 1u>(
          number / static_cast<long double>(radix), radix,
          concatenate(stringify<char_t>("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ*"[static_cast<unsigned char>(clamp(modulus(number, static_cast<long double>(radix)), 36.00L))]), string)
        )
      ) :
      resize<LDBL_DIG + LDBL_MANT_DIG>(
        concatenate(
          repeat<38u - LDBL_DIG>(stringify<char_t>('0')),
          stringify<char_t>(static_cast<unsigned long long>(number), radix)
        )
      );
  }

  template <typename char_t>
  constexpr string<char_t, 39u> stringify(long long const integer, unsigned long long const radix = 10uLL) {
    return (0LL > integer
      ? concatenate(stringify<char_t>('-'), stringify<char_t>(static_cast<unsigned long long>(-integer) * 10uLL, radix))
      : concatenate(stringify<char_t>('0'), stringify<char_t>(static_cast<unsigned long long>(+integer) *  1uLL, radix))
    );
  }
}

/* Main */
int main() {
  // std::printf("%.38s", stringify<char>(1337420uLL, 10uLL).value);
  std::printf("%.*s", LDBL_DIG + LDBL_MANT_DIG, stringify<char>(1337420.69L, 10uLL, string<char, 0u>()).value);
}
