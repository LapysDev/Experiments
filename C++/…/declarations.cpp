#include <cstdio>

/* ... */
class Object {
  static int member;
  static int member_array[1];
};

int
  Object::member,
  Object::member_array[1],
  array[1],
  function(),
  object,
  Object::*member_pointer,
    (Object::*member_bounded_array_pointer)[1],
    (Object::*member_function_pointer)(),
    (Object::*member_unbounded_array_pointer)[],
  *pointer,
    (*bounded_array_pointer)[1],
    (*function_pointer)(),
    (*unbounded_array_pointer)[],
  &reference = object,
    (&bounded_array_reference)[1]  = array,
    (&function_reference)()        = function,
    (&unbounded_array_reference)[] = array, // since C++20
  &&rvalue_reference = (int&&) object, // since C++11
    (&&rvalue_bounded_array_reference)[1]  = (int (&&)[1]) array, // since C++11
    (&&rvalue_function_reference)()        = function,            // since C++11
    (&&rvalue_unbounded_array_reference)[] = (int (&&)[]) array;  // since C++20

/* Main */
int main(int, char*[]) /* noexcept */ {}
