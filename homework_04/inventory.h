#pragma once

#include <iosfwd>
#include <stdexcept>
#include <string>

class FleetError : public std::runtime_error {
 public:
  using std::runtime_error::runtime_error;
};

class InputError : public FleetError {
 public:
  using FleetError::FleetError;
};

class InspectionError : public FleetError {
 public:
  using FleetError::FleetError;
};

class InventoryItem {
 public:
  virtual ~InventoryItem() = default;

  virtual const std::string& id() const = 0;
  virtual const std::string& name() const = 0;
  virtual std::string describe() const = 0;
  virtual double daily_energy() const { return 0; }
  virtual bool is_for_novice() const { return false; }
  virtual void inspect() const {}
};

std::ostream& operator<<(std::ostream& out, const InventoryItem& item);
bool operator<(const InventoryItem& left, const InventoryItem& right);

class Item : public InventoryItem {
 public:
  const std::string& id() const override { return id_; }
  const std::string& name() const override { return name_; }
  std::string describe() const override;

 protected:
  Item(std::string id, std::string name);

 private:
  std::string id_;
  std::string name_;
};

class EnergyConsumer {
 public:
  virtual ~EnergyConsumer() = default;

  virtual double daily_energy() const = 0;

 protected:
  explicit EnergyConsumer(double energy);

  double energy_;
};

class Transport : public Item {
 public:
  bool is_for_novice() const override { return score_ >= 6; }
  void inspect() const override;

 protected:
  Transport(std::string id, std::string name, int score);

 private:
  int score_;
};

class Bike : public Transport {
 public:
  Bike(std::string id, std::string name, int score);
};

class ElectricTransport : public Transport, public EnergyConsumer {
 public:
  double daily_energy() const override { return energy_; }

 protected:
  ElectricTransport(std::string id, std::string name, double energy, int score);
};

class Scooter : public ElectricTransport {
 public:
  Scooter(std::string id, std::string name, double energy, int score);
};

class ElectricBike : public ElectricTransport {
 public:
  ElectricBike(std::string id, std::string name, double energy, int score);
};

class Helmet : public Item {
 public:
  Helmet(std::string id, std::string name);
};

class Dock : public Item, public EnergyConsumer {
 public:
  Dock(std::string id, std::string name, double energy);

  double daily_energy() const override { return energy_; }
};

class Pump : public Item, public EnergyConsumer {
 public:
  Pump(std::string id, std::string name);

  double daily_energy() const override { return energy_; }
};
