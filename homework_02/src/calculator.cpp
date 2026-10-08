#include "calculator.h"

#include <iostream>

Operation withLogging(Operation operation) {
    return [operation](int a, int b) {
        std::cout << "Arguments: " << a << ", " << b << '\n';
        int result = operation(a, b);
        std::cout << "Result: " << result << '\n';
        return result;
    };
}

Calculator::Calculator(Operation operation) : operation_(operation) {}

void Calculator::setOperation(Operation operation) {
    operation_ = operation;
}

int Calculator::calculate(int a, int b) const {
    return operation_(a, b);
}
