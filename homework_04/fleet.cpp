#include "fleet.h"

#include <algorithm>
#include <ostream>
#include <utility>

template <typename T>
class Total {
 public:
  Total& operator+=(T value) {
    value_ += value;
    return *this;
  }
  T value() const { return value_; }

 private:
  T value_{};
};

Fleet::Items::iterator Fleet::find(const std::string& id) {
  return std::find_if(items_.begin(), items_.end(),
                      [&id](const auto& item) { return item->id() == id; });
}

void Fleet::add(std::unique_ptr<InventoryItem> item) {
  if (find(item->id()) != items_.end()) {
    throw InputError("duplicate id");
  }

  item->inspect();
  items_.emplace_back(std::move(item));
}

void Fleet::remove(const std::string& id) {
  auto item = find(id);
  if (item == items_.end()) {
    throw InputError("unknown id");
  }
  items_.erase(item);
}

void Fleet::focus(const std::string& id) {
  auto item = find(id);
  if (item == items_.end()) {
    throw InputError("unknown id");
  }
  focus_ = *item;
}

void Fleet::show_focus(std::ostream& out) const {
  if (auto item = focus_.lock()) {
    out << *item << '\n';
  } else {
    out << "expired\n";
  }
}

double Fleet::energy() const {
  Total<double> total;
  for (const auto& item : items_) {
    total += item->daily_energy();
  }
  return total.value();
}

std::size_t Fleet::count_novice() const {
  Total<std::size_t> total;
  for (const auto& item : items_) {
    total += item->is_for_novice() ? 1 : 0;
  }
  return total.value();
}

void Fleet::print(std::ostream& out, bool novice_only) const {
  Items sorted = items_;
  std::sort(sorted.begin(), sorted.end(),
            [](const auto& left, const auto& right) { return *left < *right; });

  for (const auto& item : sorted) {
    if (!novice_only || item->is_for_novice()) {
      out << *item << '\n';
    }
  }
}
