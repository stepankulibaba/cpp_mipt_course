#include <cstring>
#include <iomanip>
#include <iostream>

constexpr int kRows = 5;
constexpr int kColumns = 10;

bool fits(int column, int row, int length) {
  return row >= 0 && row < kRows && column >= 0 && column < kColumns &&
         length <= kColumns - column;
}

void clear(char board[kRows][kColumns]) {
  std::memset(board, ' ', kRows * kColumns);
}

bool put(char board[kRows][kColumns], int column, int row, char symbol) {
  if (!fits(column, row, 1)) {
    return false;
  }
  board[row][column] = symbol;
  return true;
}

bool text(char board[kRows][kColumns], int column, int row, const char* word) {
  int length = static_cast<int>(std::strlen(word));
  if (!fits(column, row, length)) {
    return false;
  }
  for (int offset = 0; word[offset] != '\0'; ++offset) {
    put(board, column + offset, row, word[offset]);
  }
  return true;
}

void print(const char board[kRows][kColumns]) {
  for (int row = 0; row < kRows; ++row) {
    for (int column = 0; column < kColumns; ++column) {
      std::cout << board[row][column];
    }
    std::cout << '\n';
  }
}

void finish_command() {
  std::cin.clear();
  char symbol = '\0';
  while (std::cin.get(symbol) && symbol != '\n') {
  }
}

int main() {
  char board[kRows][kColumns];
  clear(board);
  char command[8] = {};
  while (std::cin >> std::setw(sizeof(command)) >> command) {
    if (std::strcmp(command, "quit") == 0) {
      break;
    }

    bool success = true;
    if (std::strcmp(command, "clear") == 0) {
      clear(board);
    } else if (std::strcmp(command, "put") == 0) {
      int column = 0;
      int row = 0;
      char symbol = ' ';
      if (std::cin >> column >> row >> symbol) {
        success = put(board, column, row, symbol);
      } else {
        success = false;
      }
    } else if (std::strcmp(command, "text") == 0) {
      int column = 0;
      int row = 0;
      char word[kColumns + 2] = {};
      if (std::cin >> column >> row >> std::setw(sizeof(word)) >> word) {
        success = text(board, column, row, word);
      } else {
        success = false;
      }
    } else if (std::strcmp(command, "print") == 0) {
      print(board);
    } else {
      success = false;
    }
    if (!success) {
      std::cout << "error\n";
    }
    finish_command();
  }
}
