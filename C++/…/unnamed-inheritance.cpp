#include <iostream>
using namespace std;

struct Base {virtual int process(int a, int b) = 0;};
static struct : Base {
    int process(int a, int b) { return a+b;}
} add;
static struct : Base {
    int process(int a, int b) { return a-b;}
} subtract;
static struct : Base {
    int process(int a, int b) { return a*b;}
} multiply;
static struct : Base {
    int process(int a, int b) { return a/b;}
} divide;

void perform(Base& op, int a, int b) {
    cout << "input: " << a << ", " << b << "; output: " << op.process(a, b) << endl;
}

int main() {
    perform(add, 2, 3);
    perform(subtract, 6, 1);
    perform(multiply, 6, 7);
    perform(divide, 72, 8);
    return 0;
}
