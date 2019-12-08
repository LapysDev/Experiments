/* Import */
#include <iostream> // Input-Output Stream

/* Global */
unsigned char total = 'A';

/* Class > Number */
class Number {
    // [...]
    public:
        // [Constructor]
        Number(Number& value) { std::cout << '[' << total << "]: Copy constructor" << std::endl; total += 1u; }
        Number(Number&& value) { std::cout << '[' << total << "]: Move constructor" << std::endl; total += 1u; }

        Number(const int value) { std::cout << '[' << total << "]: Build constructor" << std::endl; total += 1u; }

        Number(const Number& value) { std::cout << '[' << total << "]: Copy (constant) constructor" << std::endl; total += 1u; }
        Number(const Number&& value) { std::cout << '[' << total << "]: Move (constant) constructor" << std::endl; total += 1u; }
};

/* Main */
int main(void) {
    // ...
    Number numberA(1);
    Number numberB {2};
    Number numberC(Number(3));
    Number numberD {Number(4)};
    Number numberE = 5;
    Number numberF = Number(6);

    const Number numberG(1);
    const Number numberH {2};
    const Number numberI(Number(3));
    const Number numberJ {Number(4)};
    const Number numberK = 5;
    const Number numberL = Number(6);

    Number numberM = numberA;
    Number numberN = numberG;

    const Number numberO = numberA;
    const Number numberP = numberG;

    // Return
    return 0;
}
