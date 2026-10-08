#include "calculator.h"

Calculator::Calculator(Operation operation) : operation_(operation) {}

void Calculator::setOperation(Operation operation) {
    operation_ = operation;
}

int Calculator::calculate(int a, int b) const {
    return operation_(a, b);
}
