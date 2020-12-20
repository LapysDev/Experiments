/* C++ Detection Idiom.
     - Inspired by Yakk's `can_apply` implementation (https://stackoverflow.com/a/29521342/2069064)
     - Reference http://open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4502.pdf
*/
#include <cstddef>
#include <iostream>

/* ... */
namespace {
  template <typename> struct dummy {};
  enum void_t {}; template <std::size_t> struct to_void_t { typedef void_t type; };

  template <class, typename = void_t>
  struct disambiguate final
  { public: static bool const value = false; };

  template <class object>
  struct disambiguate<dummy<object>, typename to_void_t<sizeof(object::member)>::type> final
  { public: static bool const value = true; };
}

template <class object>
struct has_member {
  private:
    // Summon nasal demons, here..
    struct member_object { public: int member; };
    class subobject : public object, public member_object {};

  public:
    // If the `object` type uses the `final` base clause/ is a `union`,
    // then defer to the `disambiguate<dummy<object>>::value`, instead
    // [*] Note that the fallback doesn't work for `private`/ `protected` members..
    static bool const value = false == disambiguate<dummy<subobject>>::value;
};

// Tests
class A { public: int member; };
class B { private: int member; };
class C { private: int member[2]; };
class D { private: void member(void); };
class E { private: void member(void); void member(int); };
class F { private: template <typename type> void member(type); };
class G { private: typedef int member; };
class H { private: using member = int; };
class I { private: template <typename type> using member = type; };
class J { private: class member {}; };
class K { private: template <typename> class member {}; };
class L { private: enum member {}; };
class M {};

int main(void) {
  std::boolalpha(std::cout);

  std::cout << has_member<A>::value << std::endl;
  std::cout << has_member<B>::value << std::endl;
  std::cout << has_member<C>::value << std::endl;
  std::cout << has_member<D>::value << std::endl;
  std::cout << has_member<E>::value << std::endl;
  std::cout << has_member<F>::value << std::endl;
  std::cout << has_member<G>::value << std::endl;
  std::cout << has_member<H>::value << std::endl;
  std::cout << has_member<I>::value << std::endl;
  std::cout << has_member<J>::value << std::endl;
  std::cout << has_member<K>::value << std::endl;
  std::cout << has_member<L>::value << std::endl;
  std::cout << has_member<M>::value << std::endl;
}
