#include "Inventory.hpp"
#include "Errors.hpp"

ItemBase::ItemBase(const std::string& id, const std::string& name) : id_(id), name_(name) {
    if (id.empty()) {
        throw IncorrectArgument("empty id");
    }
    if (name.empty()) {
        throw IncorrectArgument("empty name");
    }
}

double checkedEnergy(double e) {
    if (e >= 0) {
        return e;
    }
    throw IncorrectArgument("invalid energy value");
}

std::string formatEnergy(double e) {
    std::string energyText = std::to_string(e);
    while (energyText.back() == '0') {
        energyText.pop_back();
    }
    if (energyText.back() == '.') {
        energyText.pop_back();
    }
    return energyText;
}

std::ostream& operator<<(std::ostream& out, const InventoryItem& a) {
    out << a.getID() << " " << a.getName();
    return out;
}

bool operator<(const InventoryItem& a, const InventoryItem& b) {
    return a.getID() < b.getID();
}

Report& Report::operator+=(const InventoryItem& b) {
    cnt++;
    if (b.energy() != nullptr) {
        eng += b.energy()->dailyEnergy();
    }
    return *this;
}
