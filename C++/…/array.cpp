#include <ciso646> // → not
#include <climits> // → SIZE_MAX
#include <cstddef> // → NULL; std::byte, std::size_t
#include <cstdio>  //
#include <memory>  // → std::align(…)
#include <new>     // → delete, new

/* … → Assumed `T` is not implicit-lifetime or transparently replaceable: no optimizations */
template <typename T>
struct array {
  private:
    void       *value;    // Interface for accessing elements
    std::size_t capacity; // — followed by opaque storage for allocating elements
    std::size_t length;   //   `struct { T*[]; T[]; }`

  public:
    array() :
      value   (NULL),
      capacity(0u),
      length  (0u)
    {}

    ~array() {
      ::operator delete(this -> value);

      this -> capacity = 0u;
      this -> length   = 0u;
      this -> value    = NULL;
    }

    // …
    bool add(T const& object) {
      T *data;

      // …
      if (this -> capacity == this -> length) {
        std::size_t capacity = 1u;

        // …
        for (std::size_t rate = 1u; capacity < this -> capacity; ) {
          rate     *= (capacity > SIZE_MAX - (capacity / rate)) + 1u;
          capacity += capacity / rate;
        }

        if (not this -> reserve(capacity))
        return false;
      }

      data = this -> data();

      if (NULL == data)
      return false;

      static_cast<T**>(this -> value)[this -> length] = ::new (data + this -> length) T(object);
      this -> length                                 += 1u;

      return true;
    }

    T* data() const {
      std::size_t capacity = (this -> capacity * sizeof(T)) + (alignof(T) > sizeof(T) ? alignof(T) : sizeof(T));
      void       *value    = static_cast<T**>(this -> value) + this -> capacity;

      // Unusable as an array of `T`
      return static_cast<T*>(std::align(alignof(T), sizeof(T), value, capacity));
    }

    bool reserve(std::size_t count) {
      struct {
        union { std::size_t capacity, length; };
        union { void *value; T **elements; };
      } allocation, buffer, information = {{this -> length}, {this -> value}};

      // …
      if (count <= this -> capacity)
      return true;

      allocation.capacity = (count * sizeof(T)) + (alignof(T) > sizeof(T) ? alignof(T) : sizeof(T)) + (count * sizeof(T*));
      allocation.value    = ::operator new(allocation.capacity, static_cast<std::align_val_t>(alignof(T*)), std::nothrow);

      if (NULL == allocation.value) {
        ::operator delete(allocation.value);
        return false;
      }

      buffer.capacity = allocation.capacity                       - (count * sizeof(T*));
      buffer.value    = static_cast<std::byte*>(allocation.value) + (count * sizeof(T*));
      buffer.value    = std::align(alignof(T), sizeof(T), buffer.value, buffer.capacity);

      if (NULL == buffer.value) {
        ::operator delete(allocation.value);
        return false;
      }

      allocation.elements = ::new (allocation.value) T*[count];
      this -> capacity    = 0u;   // Prevent `array<T>` being observed (meaningfully)
      this -> length      = 0u;   // — as a side-effect of reconstructing its elements
      this -> value       = NULL; //

      if (NULL != information.value) {
        for (std::size_t index = 0u; index != information.length; ++index)
        allocation.elements[index] = ::new (static_cast<T*>(buffer.value) + index) T(
          *(static_cast<T**>(information.value)[index])
        );

        // Maintain LIFO order
        for (std::size_t index = information.length; index; )
        static_cast<T**>(information.value)[--index] -> ~T();
      }

      ::operator delete(information.value);
      this -> capacity = count;
      this -> length   = information.length;
      this -> value    = allocation .value;

      return true;
    }

    T& operator [](std::size_t index) const {
      return *(static_cast<T**>(index < this -> length ? this -> value : NULL)[index]);
    }
};

/* Main */
int main(int, char*[]) /* noexcept */ {}
