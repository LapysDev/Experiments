#include <cstddef> // → std::byte
#include <ciso646> // → and, not, or
#include <new>     // → ::new, std::align_val_t, std::nothrow

/* TODO → should defer to `std::align(…)` for alignment preferably */
template <typename T>
struct nonvector {
  union element {
    alignas(T) std::byte value[sizeof(T)];
    T                   *reference;
  };

  struct iterator final {
    nonvector const *that;
    std::size_t      index;

    T& operator *() const { return that -> operator [](index); }
    void operator ++() { ++index; }
    bool operator !=(struct iterator const iterator) const { return index != iterator.index; }
  };

  enum type : signed char {
    collection = -1,
    reference  = +1,
    value      = 0
  };

  /* … */
  type       *buffer;
  std::size_t capacity;
  std::size_t length;

  /* → stuff you might expect in a `std::vector` (except the `bool` return values) */
  nonvector() :
    buffer  (NULL),
    capacity(0u),
    length  (0u)
  {}

  ~nonvector() {
    std::byte        *iterator  = reinterpret_cast<std::byte*>(buffer + capacity);
    bool        const collected = NULL != buffer and *buffer == nonvector::collection;
    std::size_t const alignment = collected ? alignof(T) : alignof(element);

    // …
    while (static_cast<std::size_t>(iterator - reinterpret_cast<std::byte*>(buffer)) % alignment)
      ++iterator;

    if (collected) {
      for (T *subiterator = reinterpret_cast<T*>(iterator) + length; subiterator != reinterpret_cast<T*>(iterator); )
      std::launder(--subiterator) -> ~T();
    }

    else for (element *subiterator = reinterpret_cast<element*>(iterator) + length; subiterator != reinterpret_cast<element*>(iterator); ) {
      if (nonvector::value == buffer[--subiterator - reinterpret_cast<element*>(iterator)])
      std::launder(reinterpret_cast<T*>(std::launder(subiterator) -> value)) -> ~T();
    }
    
    ::delete[] buffer; // ???
  }

  // …
  template <typename... Ts>
  bool emplace_back(Ts&&... arguments) {
    if (capacity == length ? not reserve(capacity ? capacity * 2u : 1u) : false)
      return false; // → doubled growth rate

    std::byte        *iterator  = reinterpret_cast<std::byte*>(buffer + capacity);
    bool        const collected = NULL != buffer and *buffer == nonvector::collection;
    std::size_t const alignment = collected ? alignof(T) : alignof(element);

    // …
    while (static_cast<std::size_t>(iterator - reinterpret_cast<std::byte*>(buffer)) % alignment)
      ++iterator;

    (void) ::new (collected ? iterator + (length * sizeof(T)) : (::new (iterator + (length * sizeof(element))) element) -> value) T(static_cast<Ts&&>(arguments)...);
    buffer[length++] = nonvector::value;

    return true;
  }

  bool push_back(T const& value) { return emplace_back(value); }
  bool push_back(T&&      value) { return emplace_back(static_cast<T&&>(value)); }

  bool reserve(std::size_t const count) {
    if (capacity < count) {
      std::size_t       size       = count * sizeof(type);
      bool        const collected  = NULL != buffer and *buffer == nonvector::collection;
      type             *allocation = NULL;
      std::size_t const alignment  = collected ? alignof(T) : alignof(element);

      // → non-optimized: always copy onto new buffer
      while (size % alignof(element))
        ++size;

      size      += count * sizeof(element);
      size       = (size / sizeof(type)) + (size != (size / sizeof(type)) * sizeof(type));
      allocation = ::new (static_cast<std::align_val_t>(alignof(type)), std::nothrow) type[size];

      if (NULL == allocation)
        return false;
      
      for (type *destinationA = allocation, *sourceA = buffer, *const end = buffer + length; ; ++destinationA, ++sourceA) {
        if (end != sourceA) { *destinationA = *sourceA; continue; }

        std::byte *destinationB = reinterpret_cast<std::byte*>(destinationA + (count    - length));
        std::byte *sourceB      = reinterpret_cast<std::byte*>(sourceA      + (capacity - length));

        // …
        size = collected ? sizeof(T) : sizeof(element);

        for (type *const end = allocation + count; destinationA != end; ++destinationA)
          *destinationA = nonvector::value;

        while (static_cast<std::size_t>(destinationB - reinterpret_cast<std::byte*>(allocation)) % alignment) ++destinationB;
        while (static_cast<std::size_t>(sourceB      - reinterpret_cast<std::byte*>(buffer))     % alignment) ++sourceB;

        for (std::byte *const end = sourceB + (length * size); end != sourceB; (destinationB += size), (sourceB += size)) {
          switch (collected ? nonvector::collection : buffer[length - (reinterpret_cast<element*>(end) - reinterpret_cast<element*>(sourceB))]) {
            case nonvector::collection: {
              T *const element = std::launder(reinterpret_cast<T*>(sourceB));

              (void) ::new (destinationB) T(*element);
              element -> ~T();
            } break;

            case nonvector::reference:
              (::new (destinationB) element) -> reference = std::launder(reinterpret_cast<element*>(sourceB)) -> reference;
              break;

            case nonvector::value: {
              T *const element = std::launder(reinterpret_cast<T*>(std::launder(reinterpret_cast<nonvector::element*>(sourceB)) -> value));

              (void) ::new ((::new (destinationB) nonvector::element) -> value) T(*element);
              element -> ~T();
            } break;
          }
        }

        break;
      }

      buffer   = allocation;
      capacity = count;
    }

    return true;
  }

  T& operator [](std::size_t const index) const {
    if (index < length) {
      std::byte        *iterator  = reinterpret_cast<std::byte*>(buffer + capacity);
      bool        const collected = NULL != buffer and *buffer == nonvector::collection;
      std::size_t const alignment = collected ? alignof(T) : alignof(element);

      // …
      while (static_cast<std::size_t>(iterator - reinterpret_cast<std::byte*>(buffer)) % alignment)
      ++iterator;

      switch (collected ? nonvector::collection : buffer[index]) {
        case nonvector::collection: return *std::launder(reinterpret_cast<T*>(iterator) + index);
        case nonvector::reference : return *(std::launder(reinterpret_cast<element*>(iterator) + index) -> reference);
        case nonvector::value     : return *std::launder(reinterpret_cast<T*>(std::launder(reinterpret_cast<element*>(iterator) + index) -> value));
      }
    }

    T *const element = NULL;
    return *element;
  }

  // → how I would implement `emplace_back(…)` and `push_back(…)` instead
  bool add_reference(T& reference) {
    if (capacity == length ? not reserve(capacity ? capacity * 2u : 1u) : false)
      return false; // → doubled growth rate

    std::byte        *iterator  = reinterpret_cast<std::byte*>(buffer + capacity);
    bool        const collected = NULL != buffer and *buffer == nonvector::collection;
    std::size_t const alignment = collected ? alignof(T) : alignof(element);

    // …
    while (static_cast<std::size_t>(iterator - reinterpret_cast<std::byte*>(buffer)) % alignment)
      ++iterator;

    if (collected) {
      std::byte *subiterator = reinterpret_cast<std::byte*>(buffer + capacity);

      // …
      while (static_cast<std::size_t>(subiterator - reinterpret_cast<std::byte*>(buffer)) % alignof(element))
        ++subiterator;

      iterator    += length * sizeof(T);
      subiterator += length * sizeof(element);

      for (std::byte *const end = subiterator - (length * sizeof(element)); end != subiterator; ) {
        T *const element = std::launder(reinterpret_cast<T*>(iterator - sizeof(T)));

        // …
        iterator    -= sizeof(T);
        subiterator -= sizeof(nonvector::element);

        if (subiterator > iterator + sizeof(T)) {
          T const copy = *element;

          element -> ~T();
          (void) ::new ((::new (subiterator) nonvector::element) -> value) T(copy);
        }

        else {
          (void) ::new ((::new (subiterator) nonvector::element) -> value) T(*element);
          element -> ~T();
        }
      }

      *buffer  = nonvector::value;
      iterator = subiterator;
    }

    (::new (iterator + (length * sizeof(element))) element) -> reference = const_cast<T*>(reinterpret_cast<T const volatile*>(&reinterpret_cast<std::byte const volatile&>(reference)));
    buffer[length++]                                                     = nonvector::reference;

    return true;
  }

  bool add_value(T const& value) {
    return emplace_back(value);
  }

  // → looking for contiguous data?
  iterator begin() const {
    return {this, 0u};
  }

  T* data() const {
    std::byte        *iterator  = reinterpret_cast<std::byte*>(buffer + capacity);
    bool        const collected = NULL != buffer and *buffer == nonvector::collection;
    std::size_t const alignment = collected ? alignof(T) : alignof(element);

    // …
    while (static_cast<std::size_t>(iterator - reinterpret_cast<std::byte*>(buffer)) % alignment)
    ++iterator;

    if (not collected) {
      if (sizeof(T) < sizeof(element)) {
        if (alignof(T) > alignof(element)) return NULL;
        std::byte *subiterator = reinterpret_cast<std::byte*>(buffer + capacity);

        // …
        while (static_cast<std::size_t>(subiterator - reinterpret_cast<std::byte*>(buffer)) % alignof(T))
          ++subiterator;

        for (std::byte *const end = subiterator + (length * sizeof(T)); end != subiterator; ) {
          type &type = buffer[length - (reinterpret_cast<T*>(end) - reinterpret_cast<T*>(subiterator))];

          // …
          switch (type) {
            case nonvector::reference:
              (void) ::new (subiterator) T(*(std::launder(reinterpret_cast<element*>(iterator)) -> reference));
              break;

            case nonvector::value: {
              T *const element = std::launder(reinterpret_cast<T*>(std::launder(reinterpret_cast<nonvector::element*>(iterator)) -> value));

              // …
              if (iterator > subiterator + sizeof(T)) {
                (void) ::new (subiterator) T(*element);
                element -> ~T();
              }

              else {
                T const copy = *element;

                element -> ~T();
                (void) ::new (subiterator) T(copy);
              }
            } break;

            default:
              return NULL;
          }

          iterator    += sizeof(element);
          subiterator += sizeof(T);
          type         = buffer == &type ? nonvector::collection : nonvector::value;
        }

        iterator = subiterator - (length * sizeof(T));
      }

      else {
        for (element *subiterator = reinterpret_cast<element*>(iterator), *const end = subiterator + length; end != subiterator; ++subiterator)
        if (nonvector::reference == buffer[length - (end - subiterator)]) {
          element *const element   = std::launder(subiterator);
          T       *const reference = element -> reference;

          // …
          buffer[length - (end - subiterator)] = nonvector::value;
          (void) ::new (element -> value) T(*reference);
        }
      }
    }

    return std::launder(reinterpret_cast<T*>(iterator)); // → Undefined Behavior because no array of `T` was laundered to exist
  }

  iterator end() const {
    return {this, length};
  }
};

/* … */
#include <iostream>
#include <string>

/* Main */
int main(int, char*[]) /* noexcept */ {
  nonvector<std::string> strings {};
  std::string            text    {"..."};

  // …
  strings.emplace_back("Hello, World!", 5u); // → std::string("Hello, World!", 5u)
  strings.push_back("Lorem ipsum");
  strings.add_value("Lapis philosophorum");

  strings.add_reference(text); // → take note of this element's address
  std::cout << "[ ]: " << &text << " {\"" << text << "\"}" << std::endl;

  std::endl(std::cout);

  // → contiguous behavior
  for (std::string &string : strings) // → works with ranged-based `for …`
  std::cout << "[A]: " << &string << " {\"" << string << "\"}" << std::endl;

  std::endl(std::cout);

  for (std::size_t i = 0u; i != strings.length; ++i) // → works with regular `for …` and subscript indexing
  std::cout << "[B]: " << &strings[i] << " {\"" << strings[i] << "\"}" << std::endl;

  std::endl(std::cout);

  // → contiguous layout
  ([](std::string* string, std::size_t length) {
    for (; length--; ++string) // → works with regular `for …` and pointer (C-style "array") shenanigans
    std::cout << "[C]: " << string << " {\"" << *string << "\"}" << std::endl;
  })(strings.data(), strings.length);

  std::endl(std::cout);

  for (std::string &string : strings) // → did you take of that element's address?
  std::cout << "[D]: " << &string << " {\"" << string << "\"}" << std::endl;
}
