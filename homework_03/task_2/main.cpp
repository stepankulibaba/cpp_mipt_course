#include <climits>
#include <cstring>
#include <iomanip>
#include <iostream>

bool deposit(int& savings) {
  int amount = 0;
  if (!(std::cin >> amount) || amount <= 0 || amount > INT_MAX - savings) {
    return false;
  }
  savings += amount;
  return true;
}

bool withdraw(int& savings) {
  int amount = 0;
  if (!(std::cin >> amount) || amount <= 0 || amount > savings) {
    return false;
  }
  savings -= amount;
  return true;
}

bool balance(int& savings) {
  std::cout << savings << '\n';
  return true;
}

bool reset(int& savings) {
  savings = 0;
  return true;
}

bool inc(int& savings) {
  if (savings == INT_MAX) {
    return false;
  }
  ++savings;
  return true;
}

struct Command {
  const char* name;
  bool (*operation)(int&);
};

void finish_command() {
  std::cin.clear();
  char symbol = '\0';
  while (std::cin.get(symbol) && symbol != '\n') {
  }
}

int main() {
  const Command commands[] = {{"deposit", deposit},
                              {"withdraw", withdraw},
                              {"balance", balance},
                              {"reset", reset},
                              {"inc", inc}};
  int savings = 0;
  char command[16] = {};
  while (std::cin >> std::setw(sizeof(command)) >> command) {
    if (std::strcmp(command, "stop") == 0) {
      break;
    }

    bool success = false;
    for (const Command& entry : commands) {
      if (std::strcmp(command, entry.name) == 0) {
        success = entry.operation(savings);
        break;
      }
    }
    if (!success) {
      std::cout << "error\n";
    }
    finish_command();
  }
}
