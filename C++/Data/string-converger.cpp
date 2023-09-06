#include <ciso646>
#include <cstddef>
#include <cstdio>

/* … */
static bool const NUL_TERMINATED_STRINGS = true;

// …
template <std::size_t capacityA, std::size_t capacityB>
char const (&converge(char const (&stringA)[capacityA], char const (&stringB)[capacityB], bool const nulTerminated))[capacityA + capacityB /* - nulTerminated */] {
  static char convergence[capacityA + capacityB /* - nulTerminated */];
  char       *iterator = convergence;
  std::size_t lengthA  = 0u, lengthB  = 0u;
  std::size_t offsetA  = 0u, offsetB  = 0u;

  // …
  if (nulTerminated) {
    char const *subiterator;

    // …
    for (subiterator = stringA; ; ++subiterator)
    if ('\0' == *subiterator or subiterator == stringA + capacityA) {
      lengthA = subiterator - stringA;
      break;
    }

    for (subiterator = stringB; ; ++subiterator)
    if ('\0' == *subiterator or subiterator == stringB + capacityB) {
      lengthB = subiterator - stringB;
      break;
    }
  }

  else {
    lengthA = capacityA;
    lengthB = capacityB;
  }

  // … → Check if end of `stringA` and start of `stringB` overlap
  for (bool overlap = false; not overlap and offsetA != lengthA; )
  for (char const *iteratorA = stringA + offsetA, *iteratorB = stringB; ; ++iteratorA, ++iteratorB) {
    if      (iteratorA == stringA + lengthA)                             { overlap  = true; break; }
    else if (iteratorB == stringB + lengthB or *iteratorA != *iteratorB) { offsetA += 1u;   break; }
  }

  // … → Check if start of `stringA` and end of `stringB` overlap
  for (bool overlap = false; not overlap and offsetB != lengthB; )
  for (char const *iteratorA = stringA, *iteratorB = stringB + offsetB; ; ++iteratorA, ++iteratorB) {
    if      (iteratorB == stringB + lengthB)                             { overlap  = true; break; }
    else if (iteratorA == stringA + lengthA or *iteratorA != *iteratorB) { offsetB += 1u;   break; }
  }

  // … → End of `stringA` and start of `stringB` overlap
  if (offsetA != lengthA and (lengthA - offsetA != lengthB - offsetB ? lengthA - offsetA > lengthB - offsetB : *stringA < *stringB)) {
    for (char const *subiterator = stringA; offsetA != static_cast<std::size_t>(subiterator - stringA); ++iterator, ++subiterator)
    *iterator = *subiterator;

    for (char const *subiterator = stringB; lengthB != static_cast<std::size_t>(subiterator - stringB); ++iterator, ++subiterator)
    *iterator = *subiterator;
  }

  // … → Start of `stringA` and end of `stringB` overlap
  else if (offsetB != lengthB) {
    for (char const *subiterator = stringB; offsetB != static_cast<std::size_t>(subiterator - stringB); ++iterator, ++subiterator)
    *iterator = *subiterator;

    for (char const *subiterator = stringA; lengthA != static_cast<std::size_t>(subiterator - stringA); ++iterator, ++subiterator)
    *iterator = *subiterator;
  }

  // … → No overlaps found
  else {
    for (char const *subiterator = stringA; subiterator != stringA + lengthA; ++iterator, ++subiterator)
    *iterator = *subiterator;

    for (char const *subiterator = stringB; subiterator != stringB + lengthB; ++iterator, ++subiterator)
    *iterator = *subiterator;

    if (nulTerminated)
    *iterator = '\0';
  }

  return convergence;
}

template <std::size_t capacityA, std::size_t capacityB>
char const (&converge(char const (&stringA)[capacityA], char const (&stringB)[capacityB]))[capacityA + capacityB /* - true */] {
  return converge(stringA, stringB, NUL_TERMINATED_STRINGS);
}

#ifdef __cpp_variadic_templates // --> 200704L
  template <std::size_t capacity, std::size_t...>
  struct add {
    static std::size_t const value = capacity;
  };

  template <std::size_t capacityA, std::size_t capacityB, std::size_t... capacities>
  struct add<capacityA, capacityB, capacities...> {
    static std::size_t const value = capacityA + add<capacityB, capacities...>::value;
  };

  // …
  template <std::size_t capacityA, std::size_t capacityB, std::size_t... capacities>
  char const (&converge(char const (&stringA)[capacityA], char const (&stringB)[capacityB], char const (&...strings)[capacities]))[add<capacityA, capacityB, capacities...>::value] {
    return converge(converge(stringA, stringB), strings...);
  }
#endif

/* Main */
#include <cstdlib>
#include <csignal>

int main(int, char*[]) /* noexcept */ {
  struct program { static void bruh(int const) { std::fputs("\r\n" "SEGFAULT", stderr); std::exit(EXIT_FAILURE); } };
  std::signal(SIGSEGV, &program::bruh);

  std::puts(converge("apple", "leap"));
  std::puts(converge("leap", "apple"));
  std::puts(converge("apple", "soap"));
  std::puts(converge("soap", "apple"));

  std::puts(converge("apple", "clap", "pleasure", "rendered", "suren"));
  std::puts(converge("apple", "clap", "pleasure", "suren", "rendered"));
  std::puts(converge("apple", "clap", "rendered", "pleasure", "suren"));
  std::puts(converge("apple", "clap", "rendered", "suren", "pleasure"));
  std::puts(converge("apple", "clap", "suren", "pleasure", "rendered"));
  std::puts(converge("apple", "clap", "suren", "rendered", "pleasure"));
  std::puts(converge("apple", "pleasure", "clap", "rendered", "suren"));
  std::puts(converge("apple", "pleasure", "clap", "suren", "rendered"));
  std::puts(converge("apple", "pleasure", "rendered", "clap", "suren"));
  std::puts(converge("apple", "pleasure", "rendered", "suren", "clap"));
  std::puts(converge("apple", "pleasure", "suren", "clap", "rendered"));
  std::puts(converge("apple", "pleasure", "suren", "rendered", "clap"));
  std::puts(converge("apple", "rendered", "clap", "pleasure", "suren"));
  std::puts(converge("apple", "rendered", "clap", "suren", "pleasure"));
  std::puts(converge("apple", "rendered", "pleasure", "clap", "suren"));
  std::puts(converge("apple", "rendered", "pleasure", "suren", "clap"));
  std::puts(converge("apple", "rendered", "suren", "clap", "pleasure"));
  std::puts(converge("apple", "rendered", "suren", "pleasure", "clap"));
  std::puts(converge("apple", "suren", "clap", "pleasure", "rendered"));
  std::puts(converge("apple", "suren", "clap", "rendered", "pleasure"));
  std::puts(converge("apple", "suren", "pleasure", "clap", "rendered"));
  std::puts(converge("apple", "suren", "pleasure", "rendered", "clap"));
  std::puts(converge("apple", "suren", "rendered", "clap", "pleasure"));
  std::puts(converge("apple", "suren", "rendered", "pleasure", "clap"));
  std::puts(converge("clap", "apple", "pleasure", "rendered", "suren"));
  std::puts(converge("clap", "apple", "pleasure", "suren", "rendered"));
  std::puts(converge("clap", "apple", "rendered", "pleasure", "suren"));
  std::puts(converge("clap", "apple", "rendered", "suren", "pleasure"));
  std::puts(converge("clap", "apple", "suren", "pleasure", "rendered"));
  std::puts(converge("clap", "apple", "suren", "rendered", "pleasure"));
  std::puts(converge("clap", "pleasure", "apple", "rendered", "suren"));
  std::puts(converge("clap", "pleasure", "apple", "suren", "rendered"));
  std::puts(converge("clap", "pleasure", "rendered", "apple", "suren"));
  std::puts(converge("clap", "pleasure", "rendered", "suren", "apple"));
  std::puts(converge("clap", "pleasure", "suren", "apple", "rendered"));
  std::puts(converge("clap", "pleasure", "suren", "rendered", "apple"));
  std::puts(converge("clap", "rendered", "apple", "pleasure", "suren"));
  std::puts(converge("clap", "rendered", "apple", "suren", "pleasure"));
  std::puts(converge("clap", "rendered", "pleasure", "apple", "suren"));
  std::puts(converge("clap", "rendered", "pleasure", "suren", "apple"));
  std::puts(converge("clap", "rendered", "suren", "apple", "pleasure"));
  std::puts(converge("clap", "rendered", "suren", "pleasure", "apple"));
  std::puts(converge("clap", "suren", "apple", "pleasure", "rendered"));
  std::puts(converge("clap", "suren", "apple", "rendered", "pleasure"));
  std::puts(converge("clap", "suren", "pleasure", "apple", "rendered"));
  std::puts(converge("clap", "suren", "pleasure", "rendered", "apple"));
  std::puts(converge("clap", "suren", "rendered", "apple", "pleasure"));
  std::puts(converge("clap", "suren", "rendered", "pleasure", "apple"));
  std::puts(converge("pleasure", "apple", "clap", "rendered", "suren"));
  std::puts(converge("pleasure", "apple", "clap", "suren", "rendered"));
  std::puts(converge("pleasure", "apple", "rendered", "clap", "suren"));
  std::puts(converge("pleasure", "apple", "rendered", "suren", "clap"));
  std::puts(converge("pleasure", "apple", "suren", "clap", "rendered"));
  std::puts(converge("pleasure", "apple", "suren", "rendered", "clap"));
  std::puts(converge("pleasure", "clap", "apple", "rendered", "suren"));
  std::puts(converge("pleasure", "clap", "apple", "suren", "rendered"));
  std::puts(converge("pleasure", "clap", "rendered", "apple", "suren"));
  std::puts(converge("pleasure", "clap", "rendered", "suren", "apple"));
  std::puts(converge("pleasure", "clap", "suren", "apple", "rendered"));
  std::puts(converge("pleasure", "clap", "suren", "rendered", "apple"));
  std::puts(converge("pleasure", "rendered", "apple", "clap", "suren"));
  std::puts(converge("pleasure", "rendered", "apple", "suren", "clap"));
  std::puts(converge("pleasure", "rendered", "clap", "apple", "suren"));
  std::puts(converge("pleasure", "rendered", "clap", "suren", "apple"));
  std::puts(converge("pleasure", "rendered", "suren", "apple", "clap"));
  std::puts(converge("pleasure", "rendered", "suren", "clap", "apple"));
  std::puts(converge("pleasure", "suren", "apple", "clap", "rendered"));
  std::puts(converge("pleasure", "suren", "apple", "rendered", "clap"));
  std::puts(converge("pleasure", "suren", "clap", "apple", "rendered"));
  std::puts(converge("pleasure", "suren", "clap", "rendered", "apple"));
  std::puts(converge("pleasure", "suren", "rendered", "apple", "clap"));
  std::puts(converge("pleasure", "suren", "rendered", "clap", "apple"));
  std::puts(converge("rendered", "apple", "clap", "pleasure", "suren"));
  std::puts(converge("rendered", "apple", "clap", "suren", "pleasure"));
  std::puts(converge("rendered", "apple", "pleasure", "clap", "suren"));
  std::puts(converge("rendered", "apple", "pleasure", "suren", "clap"));
  std::puts(converge("rendered", "apple", "suren", "clap", "pleasure"));
  std::puts(converge("rendered", "apple", "suren", "pleasure", "clap"));
  std::puts(converge("rendered", "clap", "apple", "pleasure", "suren"));
  std::puts(converge("rendered", "clap", "apple", "suren", "pleasure"));
  std::puts(converge("rendered", "clap", "pleasure", "apple", "suren"));
  std::puts(converge("rendered", "clap", "pleasure", "suren", "apple"));
  std::puts(converge("rendered", "clap", "suren", "apple", "pleasure"));
  std::puts(converge("rendered", "clap", "suren", "pleasure", "apple"));
  std::puts(converge("rendered", "pleasure", "apple", "clap", "suren"));
  std::puts(converge("rendered", "pleasure", "apple", "suren", "clap"));
  std::puts(converge("rendered", "pleasure", "clap", "apple", "suren"));
  std::puts(converge("rendered", "pleasure", "clap", "suren", "apple"));
  std::puts(converge("rendered", "pleasure", "suren", "apple", "clap"));
  std::puts(converge("rendered", "pleasure", "suren", "clap", "apple"));
  std::puts(converge("rendered", "suren", "apple", "clap", "pleasure"));
  std::puts(converge("rendered", "suren", "apple", "pleasure", "clap"));
  std::puts(converge("rendered", "suren", "clap", "apple", "pleasure"));
  std::puts(converge("rendered", "suren", "clap", "pleasure", "apple"));
  std::puts(converge("rendered", "suren", "pleasure", "apple", "clap"));
  std::puts(converge("rendered", "suren", "pleasure", "clap", "apple"));
  std::puts(converge("suren", "apple", "clap", "pleasure", "rendered"));
  std::puts(converge("suren", "apple", "clap", "rendered", "pleasure"));
  std::puts(converge("suren", "apple", "pleasure", "clap", "rendered"));
  std::puts(converge("suren", "apple", "pleasure", "rendered", "clap"));
  std::puts(converge("suren", "apple", "rendered", "clap", "pleasure"));
  std::puts(converge("suren", "apple", "rendered", "pleasure", "clap"));
  std::puts(converge("suren", "clap", "apple", "pleasure", "rendered"));
  std::puts(converge("suren", "clap", "apple", "rendered", "pleasure"));
  std::puts(converge("suren", "clap", "pleasure", "apple", "rendered"));
  std::puts(converge("suren", "clap", "pleasure", "rendered", "apple"));
  std::puts(converge("suren", "clap", "rendered", "apple", "pleasure"));
  std::puts(converge("suren", "clap", "rendered", "pleasure", "apple"));
  std::puts(converge("suren", "pleasure", "apple", "clap", "rendered"));
  std::puts(converge("suren", "pleasure", "apple", "rendered", "clap"));
  std::puts(converge("suren", "pleasure", "clap", "apple", "rendered"));
  std::puts(converge("suren", "pleasure", "clap", "rendered", "apple"));
  std::puts(converge("suren", "pleasure", "rendered", "apple", "clap"));
  std::puts(converge("suren", "pleasure", "rendered", "clap", "apple"));
  std::puts(converge("suren", "rendered", "apple", "clap", "pleasure"));
  std::puts(converge("suren", "rendered", "apple", "pleasure", "clap"));
  std::puts(converge("suren", "rendered", "clap", "apple", "pleasure"));
  std::puts(converge("suren", "rendered", "clap", "pleasure", "apple"));
  std::puts(converge("suren", "rendered", "pleasure", "apple", "clap"));
  std::puts(converge("suren", "rendered", "pleasure", "clap", "apple"));
}
