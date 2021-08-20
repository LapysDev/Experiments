#include <cstddef>
#include <cstdio>

/* ... */
std::size_t split(char const string[], char const separator[], char const* splits[]) {
  std::size_t count = 0u;
  char const *split = string;
  
  // search the string
  for (char const *iterator = string; '\0' != *iterator; ++iterator)
  if (*iterator == *separator) {
    // check if substring and separator match
    for (char const *subiterator = separator; ; ++subiterator) {
      // match
      if ('\0' == *subiterator) {
        ++count;
        iterator += subiterator - separator;
        *(splits++) = split; // add to our splits
        split = iterator--; // onto the next split
        
        break;
      }
      
      // end of string
      if ('\0' == iterator[subiterator - separator]) {
        iterator += subiterator - separator; // break outer loop
        break;                               // break inner loop
      }
      
      // no match
      if (*subiterator != iterator[subiterator - separator]) break;
    }
  }
  
  // the final split
  *splits = split;
  
  // number of splits
  return count + 1u;
}

/* Main */
int main() {
  char const  separator[] = "!!";
  char const  string   [] = "!!A!!!!!B!!C!!";
  char const *splits   [] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}; // maximum of 10 splits
  
  unsigned long const count = split(string, separator, splits);
  
  // loop backwards until we find the splits
  std::printf("Splitting \"%s\" into %lu substrings:" "\r\n", string, count);
  
  for (char const **split = splits + sizeof(splits) / sizeof(*splits); split-- != splits; )
  if (NULL != *split) for (char const *iterator = *split; NULL != iterator; ++iterator) {
    // final split
    if ('\0' == *iterator) {
      std::printf("\"%s\", ", *split);
      break;
    }
      
    // mid-split
    if (*iterator == *separator) // check for separator
    for (char const *subiterator = separator; ; ++subiterator) {
      // separator confirms this is mid-split
      if ('\0' == *subiterator) {
        std::printf("\"%.*s\", ", static_cast<int>(iterator - *split), *split);
          
        iterator = static_cast<char const*>(NULL) - 1; // break outer loop
        break;                                         // break inner loop
      }

      // not a mid-split, just a fluke
      if (*subiterator != iterator[subiterator - separator]) break;
    }
  }
}
