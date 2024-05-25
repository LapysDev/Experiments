#include <cstddef>
#include <cstdio>

/* ... --> search<𝓍>(…) */
template <std::size_t count, typename type>
bool search(type const& key, type const array[], std::size_t length) {
  union {
    type const *stop; // ->> for elements missed via `0u != count % length`
    type const *stops[count];
  };

  // ...
  stop = array + (count * (length / count));

  for (type const *const end = array + length; stop != end; ++stop)
  if (key == *stop) return true;

  // ...
  length /= count;

  for (type const **stop = stops + count; stop != stops; array += length)
  *--stop = array;

  while (length--) {
    for (type const **stop = stops + count; stop != stops; )
    if (key == *((*--stop)++)) return true;
  }

  return false;
}

/* Main */
int main() {}
