#include <iomanip>
#include <iostream>

struct TemperatureRange {
  int minimum;
  int maximum;
};

double average_temperature(const int* temperatures, int day_count) {
  long long sum = 0;
  for (int day = 0; day < day_count; ++day) {
    sum += temperatures[day];
  }
  return static_cast<double>(sum) / day_count;
}

TemperatureRange temperature_range(const int* temperatures, int day_count) {
  TemperatureRange range{temperatures[0], temperatures[0]};
  for (int day = 1; day < day_count; ++day) {
    if (temperatures[day] < range.minimum) {
      range.minimum = temperatures[day];
    }
    if (temperatures[day] > range.maximum) {
      range.maximum = temperatures[day];
    }
  }
  return range;
}

int freezing_days(const int* temperatures, int day_count) {
  int count = 0;
  for (int day = 0; day < day_count; ++day) {
    if (temperatures[day] < 0) {
      ++count;
    }
  }
  return count;
}

int main() {
  int day_count = 0;
  if (!(std::cin >> day_count) || day_count <= 0) {
    return 1;
  }

  int* temperatures = new int[day_count];
  for (int day = 0; day < day_count; ++day) {
    if (!(std::cin >> temperatures[day])) {
      delete[] temperatures;
      return 1;
    }
  }

  TemperatureRange range = temperature_range(temperatures, day_count);
  std::cout << std::fixed << std::setprecision(1)
            << average_temperature(temperatures, day_count) << '\n';
  std::cout << range.minimum << ' ' << range.maximum << '\n';
  std::cout << freezing_days(temperatures, day_count) << '\n';
  delete[] temperatures;
}
