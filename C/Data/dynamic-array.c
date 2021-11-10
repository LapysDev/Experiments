#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if __STDC_VERSION__ >= 201112L
# include <stdalign.h>
#endif

/* ... */
struct array;

void AlignArray   (struct array volatile* const, size_t const);
bool CopyArray    (struct array volatile* const, void const volatile* const, size_t const);
void DestroyArray (struct array volatile* const);
void EmptyArray   (struct array volatile* const);
bool GrowArray    (struct array volatile* const, size_t const);
void InitiateArray(struct array volatile* const, size_t const);
bool InsertArray  (struct array volatile* const, size_t const, ...);
void PopArray     (struct array volatile* const);
bool PushArray    (struct array volatile* const, ...);
void ReleaseArray (struct array volatile* const);
bool ReserveArray (struct array volatile* const, size_t const);
void SpliceArray  (struct array volatile* const, size_t const, size_t);

/* ... */
struct array {
  unsigned char *value; // public
  size_t capacity;      // private: full memory reserve of `value`
  size_t length;        // public : number of objects in `value`
  size_t size;          // private: size of each object in `value`
  #if __STDC_VERSION__ >= 201112L
    size_t alignment;   // private: alignment of each object in `value`
  #endif
};

// ...
void AlignArray(struct array volatile* const array, size_t const alignment) {
  #if __STDC_VERSION__ < 201112L
    (void) alignment;
    (void) array;
  #else
    array -> alignment = alignment;
  #endif
}

bool CopyArray(struct array volatile* const array, void const volatile* const copy, size_t const length) {
  EmptyArray(array);

  if (length > array -> capacity / array -> size)
  if (false == GrowArray(array, length)) return false;

  memcpy(array -> value, (void*) copy, array -> size * length);
  array -> length = length;

  return true;
}

void DestroyArray(struct array volatile* const array) {
  EmptyArray(array);
  ReleaseArray(array);

  array -> size = 0u;
  #if __STDC_VERSION__ >= 201112L
    array -> alignment = _Alignof(max_align_t);
  #endif
}

void EmptyArray(struct array volatile* const array) {
  array -> length = 0u;
}

bool GrowArray(struct array volatile* const array, size_t const count) {
  if (array -> size * count > array -> capacity - (array -> size * array -> length)) {
    void *allocation = NULL;
    size_t capacity = array -> capacity + (array -> size * count);

    // Grow the `array` geometrically, instead
    if (capacity < (array -> capacity * 5u) / 2u)
    capacity = (array -> capacity * 5u) / 2u;

    // ...
    while (capacity > array -> capacity) {
      allocation = NULL == array -> value ?
        #if __STDC_VERSION__ < 201112L
          malloc(capacity)
        #else
          aligned_alloc(array -> alignment, capacity)
        #endif
      : realloc(array -> value, capacity);

      // Allocation successful
      if (NULL != allocation) {
        array -> capacity = capacity;
        array -> value    = allocation;

        return true;
      }

      // Allocation failed
      if (array -> size * count > capacity - (array -> size * array -> length))
      break;

      // Request less sufficient memory
      capacity -= capacity / 2u;
    }

    return false;
  }

  return true;
}

void InitiateArray(struct array volatile* const array, size_t const size) {
  array -> capacity  = 0u;
  array -> length    = 0u;
  array -> size      = size;
  array -> value     = NULL;
  #if __STDC_VERSION__ >= 201112L
    array -> alignment = size < _Alignof(max_align_t) ? size : _Alignof(max_align_t);
  #endif
}

bool InsertArray(struct array volatile* const array, size_t const index, ...) {
  va_list arguments;
  size_t count = 0u;

  // ...
  va_start(arguments, index); {
    while (NULL != va_arg(arguments, void*))
    ++count;
  } va_end(arguments);

  if (0u == count || false == GrowArray(array, count))
  return false;

  // ...
  va_start(arguments, index); {
    unsigned char *uncommitted = array -> value + (array -> size * (array -> length - 1u));
    unsigned char *next        = uncommitted    + (array -> size * count);

    // Shift old `elements` forward to reserve space for new `elements`
    for (unsigned char counter = count + 1u; counter; --counter) {
      memcpy(next, uncommitted, array -> size);

      next        -= array -> size;
      uncommitted -= array -> size;
    }

    // Insert new `elements`
    for (unsigned char *value = array -> value + (array -> size * index); count--; value += array -> size) {
      memcpy(value, va_arg(arguments, void*), array -> size);
      ++(array -> length);
    }
  } va_end(arguments);

  return true;
}

void PopArray(struct array volatile* const array) {
  array -> length -= 0u != array -> length;
}

bool PushArray(struct array volatile* const array, ...) {
  va_list arguments;
  size_t count = 0u;

  // ...
  va_start(arguments, array); {
    while (NULL != va_arg(arguments, void*))
    ++count;
  } va_end(arguments);

  if (0u == count || false == GrowArray(array, count))
  return false;

  // ...
  va_start(arguments, array);
  for (unsigned char *value = array -> value + (array -> size * array -> length); count--; value += array -> size) {
    memcpy(value, va_arg(arguments, void*), array -> size);
    ++(array -> length);
  }
  va_end(arguments);

  return true;
}

void ReleaseArray(struct array volatile* const array) {
  free(array -> value);

  array -> capacity = 0u;
  array -> value    = NULL;
}

bool ReserveArray(struct array volatile* const array, size_t const count) {
  void *const allocation = NULL == array -> value ?
    #if __STDC_VERSION__ < 201112L
      malloc(array -> size * count)
    #else
      aligned_alloc(array -> alignment, array -> size * count)
    #endif
  : realloc(array -> value, array -> size * count);

  // Reservation failed
  if (NULL == allocation)
  return false;

  // Reservation succeeded
  array -> capacity = array -> size * count;
  array -> value    = allocation;

  return true;
}

void SpliceArray(struct array volatile* const array, size_t const index, size_t count) {
  unsigned char *uncommitted = array -> value + (array -> size * index);
  unsigned char *next        = uncommitted    + (array -> size * count);

  // use `memmove`, instead? 🤔
  array -> length -= count;
  while (count--) {
    memcpy(uncommitted, next, array -> size);

    next        += array -> size;
    uncommitted += array -> size;
  }
}

/* Main */
int main() {}
