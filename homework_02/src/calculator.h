#pragma once

#include <functional>

using Operation = std::function<int(int, int)>;

class Calculator {
public:
    explicit Calculator(Operation operation);

    void setOperation(Operation operation);
    int calculate(int a, int b) const;

private:
    Operation operation_;
};
