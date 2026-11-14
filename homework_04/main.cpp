#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include "fleet.h"

template <typename T>
T read(std::istream& input) {
  T value{};
  if (!(input >> value)) {
    throw InputError("invalid arguments");
  }
  return value;
}

void require_end(std::istream& input) {
  std::string extra;
  if (input >> extra) {
    throw InputError("extra arguments");
  }
}

std::unique_ptr<InventoryItem> read_item(std::istream& input) {
  auto type = read<std::string>(input);
  auto id = read<std::string>(input);
  auto name = read<std::string>(input);

  if (type == "bike") {
    return std::make_unique<Bike>(id, name, read<int>(input));
  }
  if (type == "helmet") {
    return std::make_unique<Helmet>(id, name);
  }
  if (type == "pump") {
    return std::make_unique<Pump>(id, name);
  }
  if (type == "dock") {
    return std::make_unique<Dock>(id, name, read<double>(input));
  }
  if (type == "scooter" || type == "ebike") {
    double energy = read<double>(input);
    int score = read<int>(input);
    if (type == "scooter") {
      return std::make_unique<Scooter>(id, name, energy, score);
    }
    return std::make_unique<ElectricBike>(id, name, energy, score);
  }
  throw InputError("unknown item type");
}

bool run_command(Fleet& fleet, const std::string& line) {
  std::istringstream input(line);
  std::string command;
  if (!(input >> command)) {
    return true;
  }

  if (command == "add") {
    auto item = read_item(input);
    require_end(input);
    fleet.add(std::move(item));
    return true;
  }

  if (command == "focus" || command == "remove") {
    auto id = read<std::string>(input);
    require_end(input);
    if (command == "focus") {
      fleet.focus(id);
    } else {
      fleet.remove(id);
    }
    return true;
  }

  require_end(input);
  if (command == "quit") {
    return false;
  }
  if (command == "energy") {
    std::cout << std::fixed << std::setprecision(1) << fleet.energy() << '\n';
  } else if (command == "list" || command == "novice") {
    fleet.print(std::cout, command == "novice");
  } else if (command == "show_focus") {
    fleet.show_focus(std::cout);
  } else if (command == "count") {
    std::cout << fleet.size() << '\n';
  } else if (command == "count_novice") {
    std::cout << fleet.count_novice() << '\n';
  } else {
    throw InputError("unknown command");
  }
  return true;
}

int main() {
  Fleet fleet;
  std::string line;
  while (std::getline(std::cin, line)) {
    try {
      if (!run_command(fleet, line)) {
        break;
      }
    } catch (const FleetError& error) {
      std::cout << "error: " << error.what() << '\n';
    }
  }
}
