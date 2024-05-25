/* Constant > Null Pointer */
const class {
  public:
    // [Operator] > [*] --- NOTE (Lapys) -> Convertible to types of non-null members or null member pointers.
    template <typename type> operator type*() const { return 0; }
    template <typename objectType, typename objectMethodType> operator objectMethodType objectType::*() const { return 0; }

  private:
    // [Operator] > [&] --- NOTE (Lapys) -> Non-reference-able address operation.
    void operator &() const;
} nullptr = {};
