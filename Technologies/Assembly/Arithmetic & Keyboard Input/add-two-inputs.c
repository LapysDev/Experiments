#include <stdio.h>

int add(int argumentA, int argumentB) { return argumentA + argumentB; }

int main(void) {
    int evaluation;

    const int numberA = 2;
    const int numberB = 3;

    evaluation = add(numberA, numberB);

    return 0;
}
