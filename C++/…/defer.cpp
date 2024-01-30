#include <csetjmp>
#include <cstdio>

#ifdef _MSC_VER
# pragma warning(disable: 4611)
# pragma warning(disable: 4702)
#endif

// #define defer defer__first_pass(_Deferral__, _Defererr__, __LINE__)
// # define defer__first_pass(className, objectName, identity) defer__second_pass(className, objectName, identity)
// # define defer__second_pass(className, objectName, identity) defer__parse(className ## identity, objectName ## identity)
// # define defer__parse(className, objectName) union className { void (*deferred)() /* throw(...) */; constexpr className(void (*const deferred)() /* throw(...) */) noexcept : deferred(deferred) {} inline ~className() noexcept { deferred(); } } const objectName = +[]() /* throw(...) */ -> void
// #define finally ;
#if __cplusplus < 201103L
# define defer__final
#else
# define defer__final final
#endif
#ifdef _MSC_VER
# define defer__inline __declspec(noinline)
#else
# define defer__inline inline
#endif
#ifdef __circle_lang__
# define defer__volatile volatile
#else
# define defer__volatile
#endif
# ifndef defer
#   define defer defer__first_pass(_Expression__, _Buffers__, _Status__, _Function__, __LINE__)
#     define defer__first_pass(interfaceName, jumpBuffersName, jumpStatusName, functionName, identity) defer__second_pass(interfaceName, jumpBuffersName, jumpStatusName, functionName, identity)
#     define defer__second_pass(interfaceName, jumpBuffersName, jumpStatusName, functionName, identity) defer__parse(interfaceName ## identity, jumpBuffersName ## identity, jumpStatusName ## identity, functionName ## identity)
#     define defer__parse(expression, buffers, status, function) static_cast<void>(0x00u); struct expression defer__final { public: std::jmp_buf buffers[2]; bool defer__volatile status; defer__inline ~expression() /* noexcept(expression::function()) */ { if (this -> status) return; this -> status = true; expression::function(); std::longjmp(this -> buffers[0], 0x1); } private: defer__inline static void function() /* throw(...) */ {
# endif
# ifndef finally
#   define finally(value) finally__first_pass(_Object__, __LINE__, (value))
#     define finally__first_pass(objectName, identity, value) finally__second_pass(objectName, identity, value)
#     define finally__second_pass(objectName, identity, value) finally__parse(objectName ## identity, value)
#     define finally__parse(object, value) } } object = {{}, false}; if (0x0 != setjmp(reinterpret_cast<std::jmp_buf (&)[2]>(object)[1])) return value; for (void (&longjmp)(std::jmp_buf, int) = std::longjmp; 0x0 != setjmp(reinterpret_cast<std::jmp_buf (&)[2]>(object)[0]); longjmp(reinterpret_cast<std::jmp_buf (&)[2]>(object)[1], 0x1))
# endif

/* Main */
int main(int, char*[]) /* noexcept */ {
  defer       std::puts("defer");
  finally(42) std::puts("finally");

  std::puts("main()");
}
