#include <cstdio>
#include <new>
#include <version>
#if __cplusplus >= 201103L
# include <type_traits>
# include <utility>
#endif

/* ... */
#ifndef __cpp_lib_launder
  template <typename type>
  inline type* launder(type* const address) {
    return address;
  }
#endif

/* Class */
template <typename base, std::size_t capacity = 0u>
#if defined(__cpp_rvalue_references) && defined(__cpp_variadic_templates)
  class Array {
    private:
      template <int, std::size_t subcapacity>
      union fixed { base value[subcapacity]; };

      template <int dummy>
      union fixed<dummy, 0u> {};

      fixed<>

    public:
      template <typename... types>
      inline Array(types&&... elements) {}
  };
#else
  class Array {};
#endif

template <typename base, std::size_t capacity = 0u>
class Array {
  private:
    template <typename, std::size_t length>
    struct data_t {
      private: typedef base type[length];
      public:
        type data;
        inline operator type&() const volatile { return const_cast<type&>(this -> data); }
    };

    template <typename dummy>
    struct data_t<dummy, 0u> {
      private: typedef base type[];
      public: inline operator type*() const volatile { return NULL; }
    };

    /* ... */
    void push() const volatile {}

    #if defined(__cpp_rvalue_references) && defined(__cpp_variadic_templates)
      template <typename type, typename... types>
      void push(type&& element, types&&... elements) const volatile {
        static_cast<void>(element);
        this -> push(std::forward<types>(elements)...);
      }
    #endif

  public:
    union {
      data_t<base, capacity> automatic, value;
      base                  *deferred;
    };

    /* ... ->> allow construction with more arbitrary `elements` than `capacity` */
    #if defined(__cpp_rvalue_references) && defined(__cpp_variadic_templates)
      private:
        template <typename... types>
        inline Array(bool (*const)[false + 1], types&&... elements) :
          automatic{std::forward<types>(elements)...}
        {}

        template <typename... types>
        inline Array(bool (*const)[true + 1], types&&... elements) :
          deferred(NULL)
        { this -> add(static_cast<types>(elements)...); }

      public:
        template <typename... types>
        inline Array(types&&... elements) :
          Array<base, capacity>::Array(static_cast<bool (*)[(capacity < sizeof...(elements)) + 1]>(NULL), std::forward<types>(elements)...)
        {}
    #endif

    /* ... */
    void add(base const& element) const volatile {
      this -> push(element);
    }

    template <std::size_t count>
    void add(base const (&elements)[count]) const volatile {
      for (base const *element = elements + count; element != elements; )
      this -> push(*--element);
    }

    /* ... */
    template <std::size_t length>
    Array& operator =(base const volatile (&)[length]) volatile {
      return *const_cast<Array*>(this);
    }
};

/* Main */
int main(int, char*[]) /* noexcept */ {
  Array<int, 3u> const array = {1, 2, 3};

  std::puts(NULL == array.value        ? "true" : "false");
  std::puts(NULL == Array<int>().value ? "true" : "false");
}
