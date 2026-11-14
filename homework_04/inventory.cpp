#include "inventory.h"

#include <cctype>
#include <cmath>
#include <ostream>
#include <utility>

std::ostream& operator<<(std::ostream& out, const InventoryItem& item) {
  return out << item.describe();
}

bool operator<(const InventoryItem& left, const InventoryItem& right) {
  return left.id() < right.id();
}

Item::Item(std::string id, std::string name)
    : id_(std::move(id)), name_(std::move(name)) {
  if (id_.empty() || name_.empty()) {
    throw InputError("empty id or name");
  }
}

std::string Item::describe() const { return id() + " " + name(); }

EnergyConsumer::EnergyConsumer(double energy) : energy_(energy) {
  if (!std::isfinite(energy) || energy < 0) {
    throw InputError("invalid energy");
  }
}

Transport::Transport(std::string id, std::string name, int score)
    : Item(std::move(id), std::move(name)), score_(score) {
  if (score < 1 || score > 10) {
    throw InputError("score must be between 1 and 10");
  }
}

void Transport::inspect() const {
  std::string lower_name = name();
  for (char& symbol : lower_name) {
    symbol =
        static_cast<char>(std::tolower(static_cast<unsigned char>(symbol)));
  }
  if (lower_name.find("broken") != std::string::npos) {
    throw InspectionError("inspection rejected");
  }
}

Bike::Bike(std::string id, std::string name, int score)
    : Transport(std::move(id), std::move(name), score) {}

ElectricTransport::ElectricTransport(std::string id, std::string name,
                                     double energy, int score)
    : Transport(std::move(id), std::move(name), score),
      EnergyConsumer(energy) {}

Scooter::Scooter(std::string id, std::string name, double energy, int score)
    : ElectricTransport(std::move(id), std::move(name), energy, score) {}

ElectricBike::ElectricBike(std::string id, std::string name, double energy,
                           int score)
    : ElectricTransport(std::move(id), std::move(name), energy, score) {}

Helmet::Helmet(std::string id, std::string name)
    : Item(std::move(id), std::move(name)) {}

Dock::Dock(std::string id, std::string name, double energy)
    : Item(std::move(id), std::move(name)), EnergyConsumer(energy) {}

Pump::Pump(std::string id, std::string name)
    : Item(std::move(id), std::move(name)), EnergyConsumer(0.5) {}
