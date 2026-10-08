#include <iostream>

#include "calculator.h"

int main() {
    Operation add = [](int a, int b) {
        return a + b;
    };

    Operation multiply = [](int a, int b) {
        return a * b;
    };

    Calculator calculator(add);
    std::cout << "Addition: " << calculator.calculate(5, 3) << '\n';

    calculator.setOperation(multiply);
    std::cout << "Multiplication: " << calculator.calculate(5, 3) << '\n';
}
