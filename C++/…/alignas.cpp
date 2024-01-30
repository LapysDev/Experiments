#include <cstdio>

/* ... */
#if defined(__cplusplus) && __cplusplus >= 201103L
# define alignby(size) alignas(size)
# define alignis(size) alignof(size)
#else
# if defined(_MSC_VER) && _MSC_VER >= 1800
#  define __alignof_is_defined true
# elif false == defined(__clang__)
#  include <stdalign.h>
# endif

# if defined(__alignas_is_defined)
#  if defined(_Alignas)
#   define alignby(size) _Alignas(size)
#  else
#   define alignby(size) alignas(size)
#  endif
# else
#  if defined(__GNUG__)
#   define alignby(size) __attribute__((aligned(size)))
#  elif defined(_MSC_VER)
#   define alignby(size) __declspec(align(size))
#  else
#   define alignby(size)
#  endif
# endif

# if defined(__alignof_is_defined)
#  if defined(_Alignof)
#   define alignis(size) _Alignof(size)
#  else
#   define alignis(size) alignof(size)
#  endif
# else
#  if defined(__GNUG__)
#   define alignis(size) __alignof__(size)
#  elif defined(_MSC_VER)
#   define alignis(size) __alignof(size)
#  else
#   define alignis(size) sizeof(size)
#  endif
# endif
#endif

/* Main */
int main() {
  struct alignby(32u) Object {};
  std::printf("%li", alignis(struct Object));
}
