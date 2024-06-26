template <typename... bases>
struct pack final {
  template <std::size_t index>
  struct at final {
    private:
      template <std::size_t, typename...>
      struct valueof;

      template <std::size_t subindex, typename subbase, typename... subbases>
      struct valueof<subindex, subbase, subbases...> final {
        friend struct at;
        private: typedef typename valueof<subindex - 1u, subbases...>::type type;
      };

      template <typename subbase, typename... subbases>
      struct valueof<0u, subbase, subbases...> final {
        friend struct at;
        private: typedef subbase type;
      };

    public:
      typedef typename valueof<index, bases...>::type type;
  };

  // ...
  template <typename type>
  struct has final {
    private:
      template <typename...>
      struct valueof final {
        friend struct has;
        private: static bool const value = false;
      };

      template <typename subbase, typename... subbases>
      struct valueof<subbase, subbases...> final {
        friend struct has;
        private: static bool const value = valueof<subbases...>::value;
      };

      template <typename... subbases>
      struct valueof<type, subbases...> final {
        friend struct has;
        private: static bool const value = true;
      };

    public:
      static bool const value = valueof<bases...>::value;
  };

  // ...
  template <std::size_t begin, std::size_t end>
  struct slice final {
    private:
      template <std::size_t, typename...>        struct beginof;
      template <std::size_t, class, typename...> struct endof;

      /* ... */
      template <std::size_t count, typename subbase, typename... subbases>
      struct beginof<count, subbase, subbases...> final {
        friend struct slice;
        private: typedef typename beginof<count - 1u, subbases...>::type type;
      };

      template <typename subbase, typename... subbases>
      struct beginof<0u, subbase, subbases...> final {
        friend struct slice;
        private: typedef typename endof<end - 1u, pack<subbase>, subbases...>::type type;
      };

      // ...
      template <std::size_t count, typename... sliced, typename subbase, typename... subbases>
      struct endof<count, pack<sliced...>, subbase, subbases...> final {
        friend struct slice;
        private: typedef typename endof<count - 1u, pack<sliced..., subbase>, subbases...>::type type;
      };

      template <typename... sliced, typename subbase, typename... subbases>
      struct endof<0u, pack<sliced...>, subbase, subbases...> final {
        friend struct slice;
        private: typedef pack<sliced...> type;
      };

    public:
      typedef typename beginof<begin, bases..., void>::type type;
  };

  template <std::size_t index>
  struct slice<index, index> final {
    typedef pack<> type;
  };

  // ...
  struct uniqueof final {
    private:
      template <class pack, typename...>
      struct valueof final {
        friend struct uniqueof;
        private: typedef pack type;
      };

      template <typename... packed, typename subbase, typename... subbases>
      struct valueof<pack<packed...>, subbase, subbases...> final {
        friend struct uniqueof;
        private: typedef typename std::conditional<
          pack<packed...>::template has<subbase>::value,
          typename valueof<pack<packed...>,          subbases...>::type,
          typename valueof<pack<packed..., subbase>, subbases...>::type
        >::type type;
      };

    public:
      typedef typename valueof<pack<>, bases...>::type type;
  };

  /* ... */
  static std::size_t const length = sizeof...(bases);
};
