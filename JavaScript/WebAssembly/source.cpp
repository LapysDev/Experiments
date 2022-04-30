/* CITE (Lapys) -> https://mbebenita.github.io/WasmExplorer/ */
/* CODE (Lapys) ->  em++ source.cpp -s WASM=1 -s SIDE_MODULE=1 -o source.wasm */
#include <cstddef>
#include <ctime>
#include <stdint.h>

/* ... */
extern "C" uintmax_t benchmark(std::time_t const milliseconds) {
  std::size_t       operations      = 0u;
  std::time_t const recentTimestamp = std::time(static_cast<std::time_t*>(NULL));

  // ...
  if (recentTimestamp != static_cast<std::time_t>(-1))
  while (true) {
    std::time_t const currentTimestamp = std::time(static_cast<std::time_t*>(NULL));

    // ...
    if (currentTimestamp == static_cast<std::time_t>(-1)) break;
    if (milliseconds < currentTimestamp - recentTimestamp) return operations;

    ++operations;
  }

  return 0u;
}
