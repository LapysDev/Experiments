#include <stdio.h>

class Primitive { public:
    virtual void print(void) const { ::puts("Hello, [Primitive]"); }
    static void print(Primitive const& primitive) { primitive.print(); }
};
class Object : public Primitive { public: void print(void) const override { ::puts("Hello, [Object]"); } };

int main(void) {
    Object variable;
    Primitive::print(variable);
}
