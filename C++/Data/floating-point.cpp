#include <cfloat>
#include <ciso646>
#include <climits>
#include <cmath>
#include <cstdio>

/* Main */
int main(int, char*[]) /* noexcept */ {
  long double       integer = LDBL_MAX; // --> x <= LDBL_MAX
  long double const radix   = 2.00L;
  long double       rank    = 1.00L;

  // ...
  while (rank <= integer / radix and rank <= LDBL_MAX / radix)
    rank *= radix;

  std::printf("[integer (10)]: %Lf" "\r\n", static_cast<long double>(integer));
  std::printf("[rank    (10)]: %Lf" "\r\n", static_cast<long double>(rank));
  
  std::printf("[integer  (2)]: ");
  for (unsigned char const *iterator = &reinterpret_cast<unsigned char const&>(integer) + sizeof integer; iterator != &reinterpret_cast<unsigned char const&>(integer); ) {
    // std::printf("0x%X" " ", *--iterator);
    for (unsigned char byte = *--iterator, index = CHAR_BIT; index; )
      std::printf((byte >> --index) & 1u ? "1" : "0");
    
    std::printf(" ");
  }
  std::printf("\r\n");
  
  std::printf("[rank     (2)]: ");
  for (unsigned char const *iterator = &reinterpret_cast<unsigned char const&>(rank) + sizeof rank; iterator != &reinterpret_cast<unsigned char const&>(rank); ) {
    // std::printf("0x%X" " ", *--iterator);
    for (unsigned char byte = *--iterator, index = CHAR_BIT; index; )
      std::printf((byte >> --index) & 1u ? "1" : "0");
    
    std::printf(" ");
  }
  std::printf("\r\n");
  
  std::printf("[]: ");
  for (; rank >= 1.00L; rank /= radix) {
    if                             (integer < rank * 1.00L) { integer -= rank * 0.00L; std::printf("0"); continue; }
    if (integer >= rank * 1.00L and integer < rank * 2.00L) { integer -= rank * 1.00L; std::printf("1"); continue; }
    if (integer >= rank * 2.00L and integer < rank * 3.00L) { integer -= rank * 2.00L; std::printf("2"); continue; }
    if (integer >= rank * 3.00L and integer < rank * 4.00L) { integer -= rank * 3.00L; std::printf("3"); continue; }
    if (integer >= rank * 4.00L and integer < rank * 5.00L) { integer -= rank * 4.00L; std::printf("4"); continue; }
    if (integer >= rank * 5.00L and integer < rank * 6.00L) { integer -= rank * 5.00L; std::printf("5"); continue; }
    if (integer >= rank * 6.00L and integer < rank * 7.00L) { integer -= rank * 6.00L; std::printf("6"); continue; }
    if (integer >= rank * 7.00L and integer < rank * 8.00L) { integer -= rank * 7.00L; std::printf("7"); continue; }
    if (integer >= rank * 8.00L and integer < rank * 9.00L) { integer -= rank * 8.00L; std::printf("8"); continue; }
    if (integer >= rank * 9.00L)                            { integer -= rank * 9.00L; std::printf("9"); continue; }
  }
}
