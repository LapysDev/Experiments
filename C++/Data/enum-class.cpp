struct Color {
    enum Value { RED, GREEN, BLUE } value;

    Color(Value const value) : value(value) {}
    operator Value() const { return this -> value; }
};
