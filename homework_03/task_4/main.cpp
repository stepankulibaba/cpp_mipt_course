#include <cstring>
#include <iomanip>
#include <iostream>

int main() {
  // int*** хранит трёхмерную сетку измерений: слой, строка, столбец.
  // void* позволяет держать целые суммы и вещественные средние в одной таблице.
  // Команда выбирает отчёт и определяет тип данных перед чтением буфера.
  int layer_count = 0;
  int row_count = 0;
  int column_count = 0;
  if (!(std::cin >> layer_count >> row_count >> column_count) ||
      layer_count <= 0 || row_count <= 0 || column_count <= 0) {
    return 1;
  }

  int*** measurements = new int**[layer_count];
  for (int layer = 0; layer < layer_count; ++layer) {
    measurements[layer] = new int*[row_count];
    for (int row = 0; row < row_count; ++row) {
      measurements[layer][row] = new int[column_count]{};
      for (int column = 0; column < column_count; ++column) {
        std::cin >> measurements[layer][row][column];
      }
    }
  }
  bool is_input_valid = !std::cin.fail();

  long long* sums = new long long[layer_count];
  double* averages = new double[layer_count];
  void* reports[] = {sums, averages};
  for (int layer = 0; layer < layer_count; ++layer) {
    long long sum = 0;
    for (int row = 0; row < row_count; ++row) {
      for (int column = 0; column < column_count; ++column) {
        sum += measurements[layer][row][column];
      }
    }
    sums[layer] = sum;
    averages[layer] = static_cast<double>(sum) / row_count / column_count;
  }

  char command[16] = {};
  std::cout << std::fixed << std::setprecision(1);
  while (std::cin >> std::setw(sizeof(command)) >> command) {
    if (std::strcmp(command, "stop") == 0) {
      break;
    }
    if (std::strcmp(command, "cell") == 0) {
      int layer = 0;
      int row = 0;
      int column = 0;
      if (!(std::cin >> layer >> row >> column) || layer < 0 ||
          layer >= layer_count || row < 0 || row >= row_count || column < 0 ||
          column >= column_count) {
        std::cout << "error\n";
      } else {
        std::cout << measurements[layer][row][column] << '\n';
      }
    } else {
      int report_index = -1;
      if (std::strcmp(command, "sum") == 0) {
        report_index = 0;
      } else if (std::strcmp(command, "average") == 0) {
        report_index = 1;
      }
      if (report_index == -1) {
        std::cout << "error\n";
      } else {
        void* data = reports[report_index];
        for (int layer = 0; layer < layer_count; ++layer) {
          if (layer > 0) {
            std::cout << ' ';
          }
          if (report_index == 1) {
            std::cout << static_cast<double*>(data)[layer];
          } else {
            std::cout << static_cast<long long*>(data)[layer];
          }
        }
        std::cout << '\n';
      }
    }
    std::cin.clear();
    char symbol = '\0';
    while (std::cin.get(symbol) && symbol != '\n') {
    }
  }

  delete[] sums;
  delete[] averages;
  for (int layer = 0; layer < layer_count; ++layer) {
    for (int row = 0; row < row_count; ++row) {
      delete[] measurements[layer][row];
    }
    delete[] measurements[layer];
  }
  delete[] measurements;
  return is_input_valid ? 0 : 1;
}
