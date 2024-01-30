struct Color {
  enum Enumeration { RED, GREEN, BLUE } value;

  Color(Enumeration const value) : value(value) {}
  operator Enumeration() const { return this -> value; }
};
