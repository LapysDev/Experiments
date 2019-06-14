#include <iostream>

class Generic {
    private:
        float value = 0;
    public:
        Generic(float number) { this -> value = number; }

        float add(float number) { return 2019; }
        float operator +(float number) { return 2019; }
};

float add(Generic generic, float number) { return 2019; }

int main(int argc, char* argv[]) {
    Generic generic = Generic(2);

    std::cout << add(generic, 4) << std::endl;
    std::cout << generic.add(4) << std::endl;
    std::cout << generic + 4 << std::endl;

    return 0;
}
