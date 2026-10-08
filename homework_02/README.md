# Домашка 2 – стратегия и декоратор

Небольшой калькулятор с двумя операциями: сложение и умножение.

- `calculator.h` — объявления калькулятора и декоратора.
- `calculator.cpp` — реализация стратегии и декоратора.
- `main.cpp` — пример использования обоих паттернов.

## Запуск

Из корня репозитория, в PowerShell с установленным `g++` (я проверял у себя на винде):

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic -static homework_02/src/main.cpp homework_02/src/calculator.cpp -o "$env:TEMP\cpp_mipt_calculator.exe"
& "$env:TEMP\cpp_mipt_calculator.exe"
```

Можно также собрать через CMake, если установлены `g++`, CMake и Ninja:

```powershell
cmake -S homework_02 -B "$env:TEMP\cpp_mipt_homework_02_build" -G Ninja -DCMAKE_CXX_COMPILER=g++
cmake --build "$env:TEMP\cpp_mipt_homework_02_build"
& "$env:TEMP\cpp_mipt_homework_02_build\calculator_demo.exe"
```


Ожидаемый вывод:

```text
Addition: 8
Multiplication: 15
Addition with logging:
Arguments: 5, 3
Result: 8
Multiplication with logging:
Arguments: 5, 3
Result: 15
```