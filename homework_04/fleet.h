#pragma once

#include <cstddef>
#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

#include "inventory.h"

class Fleet {
 public:
  void add(std::unique_ptr<InventoryItem> item);
  void remove(const std::string& id);
  void focus(const std::string& id);
  void show_focus(std::ostream& out) const;

  std::size_t size() const { return items_.size(); }
  double energy() const;
  std::size_t count_novice() const;
  void print(std::ostream& out, bool novice_only) const;

 private:
  using Items = std::vector<std::shared_ptr<InventoryItem>>;

  Items::iterator find(const std::string& id);

  Items items_;
  std::weak_ptr<InventoryItem> focus_;
};
