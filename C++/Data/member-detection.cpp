#include <iostream>
#include <type_traits>  //std::true_type / std::false_type

#define CREATE_HAS_METHOD_NAME(name, method)                                                    \
namespace                                                                                       \
{                                                                                               \
    template<size_t...>                                                                         \
    using void_t = void;                                                                        \
                                                                                                \
    struct X##name {bool method(); };                                                           \
                                                                                                \
    template <class Object>                                                                     \
    struct Xor##name : public Object, public X##name {};                                        \
                                                                                                \
    template<class, class = void_t<>>                                                           \
    struct has_##name : std::true_type {};                                                      \
                                                                                                \
    template<class Object>                                                                      \
    struct has_##name<Object, void_t<sizeof(&Xor##name<Object>::method)>> : std::false_type {}; \
}                                                                                               \

//first parameter is name and usage is has_##name
//second parameter is method for example operator+

CREATE_HAS_METHOD_NAME(member, member);
CREATE_HAS_METHOD_NAME(plus, operator+);


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

class N { public: void operator +(void); };
class O { public: void operator +(A const&); };
class P { protected: void operator +(A const&); };
class Q { private: void operator +(A const&); };
//class R { private: template<class...> void operator +(X const&); };
class S { private: int& operator +(void); void operator +(A const&); };
class T { private: friend void operator +(G const&); };
class U {};

int main()
{
    std::cout << std::boolalpha;
    std::cout << "member:\n";
    std::cout << has_member<A>::value << '\n';
    std::cout << has_member<B>::value << '\n';
    std::cout << has_member<C>::value << '\n';
    std::cout << has_member<D>::value << '\n';
    std::cout << has_member<E>::value << '\n';
    std::cout << has_member<F>::value << '\n';
    std::cout << has_member<G>::value << '\n';
    std::cout << has_member<H>::value << '\n';
    std::cout << has_member<I>::value << '\n';
    std::cout << has_member<J>::value << '\n';
    std::cout << has_member<K>::value << '\n';
    std::cout << has_member<L>::value << '\n';
    std::cout << has_member<M>::value << '\n';

    std::cout << "operator+:\n";
    std::cout << has_plus<N>::value << '\n';
    std::cout << has_plus<O>::value << '\n';
    std::cout << has_plus<P>::value << '\n';
    std::cout << has_plus<Q>::value << '\n';
    //std::cout << has_member<R>::value << '\n';
    std::cout << has_plus<S>::value << '\n';
    std::cout << has_plus<T>::value << '\n';
    std::cout << has_plus<U>::value << '\n';
}
