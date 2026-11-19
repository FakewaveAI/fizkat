#include "Things.hpp"

std::string Thing::description() const {
    return type() + " " + getID() + ": " + getName();
}

std::string Helmet::type() const {
    return "helmet";
}

Dock::Dock(const std::string& id, const std::string& name, double energy)
    : Thing(id, name), energy_(checkedEnergy(energy)) {}

std::string Dock::type() const {
    return "dock";
}

double Dock::dailyEnergy() const {
    return energy_;
}

const EnergyConsumer* Dock::energy() const {
    return this;
}

std::string Dock::description() const {
    return Thing::description() + ", daily energy: " + formatEnergy(dailyEnergy()) + " kWh/day";
}
