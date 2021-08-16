#include <climits>
#include <cstdlib>

#include "linked-list.hh" // Structure to iterate over
#include "print.hh"       // Compile-time "logging"
#include "timer.hh"       // Benchmarking

/* ... */
static unsigned char length = 1u + (std::rand() % UCHAR_MAX);
static LinkedList list = LinkedList();

// ... ->> `flush(stdout, print(...))` to log the values to the `stdout` `FILE` stream
void linear(LinkedList* const list) {
  for (LinkedList *iterator = list; NULL != iterator; iterator = iterator -> next)
  print(iterator -> value, ", ");
}

void recurse(LinkedList* const list) {
  if (NULL == list) return;

  print(list -> value, ", ");
  recurse(list -> next);
}

/* Main */
int main() {
  // Setup
  std::printf("List of %hu nodes" "\r\n" "====================" "\r\n", static_cast<unsigned short>(length));
  for (LinkedList *iterator = &list; length; --length) {
    LinkedList *const tail = static_cast<LinkedList*>(std::malloc(sizeof(LinkedList)));

    iterator -> next = tail;
    iterator = tail;

    tail -> next = NULL;
    tail -> value = length;
  }

  // ...
  timerstart timer;

  std::puts("Linear Iteration");
  // timerstart(&timer);
  linear(&list);
  // std::printf("%llu", static_cast<unsigned long long>(timerend(&timer)));
  std::puts("\r\n");

  // std::puts("Recursive Iteration");
  // timerstart(); { recurse(&list); } timerend();
  // std::puts("\r\n");
}
