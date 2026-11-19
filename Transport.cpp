#include "Transport.hpp"
#include "Errors.hpp"

Transport::Transport(const std::string& id, const std::string& name, int ease)
    : ItemBase(id, name), easeOfUse_(ease) {
    if (ease < 1 || ease > 10) {
        throw IncorrectArgument("ease of use of transport must be in [1, 10]");
    }
}

int Transport::getEaseOfUse() const {
    return easeOfUse_;
}

bool Transport::isForNovice() const {
    return easeOfUse_ >= cNoviceThreshold;
}

std::string Transport::description() const {
    return type() + " " + getID() + ": " + getName() + ", ease of use: "
        + std::to_string(getEaseOfUse());
}

Bike::Bike(const std::string& id, const std::string& name, int ease)
    : Transport(id, name, ease) {}

std::string Bike::type() const {
    return "bike";
}

ElectricTransport::ElectricTransport(const std::string& id, const std::string& name, double energy, int ease)
    : Transport(id, name, ease), energy_(checkedEnergy(energy)) {}

double ElectricTransport::dailyEnergy() const {
    return energy_;
}

const EnergyConsumer* ElectricTransport::energy() const {
    return this;
}

std::string ElectricTransport::description() const {
    return Transport::description() + ", daily energy: " + formatEnergy(dailyEnergy()) + " kWh/day";
}

std::string ElectricScooter::type() const {
    return "electric scooter";
}

std::string ElectricBike::type() const {
    return "electric bike";
}

std::string GolfCart::type() const {
    return "golf cart";
}

std::string GolfCart::description() const {
    return ElectricTransport::description() + ", license required";
}
