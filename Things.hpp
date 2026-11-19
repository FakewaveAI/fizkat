#pragma once
#include "Inventory.hpp"

class Thing : public ItemBase {
public:
    using ItemBase::ItemBase;
    std::string description() const override;
};

class Helmet final : public Thing {
public:
    using Thing::Thing;
    std::string type() const override;
};

class Dock final : public Thing, public EnergyConsumer {
public:
    Dock(const std::string& id, const std::string& name, double energy);
    std::string type() const override;
    double dailyEnergy() const override;
    const EnergyConsumer* energy() const override;
    std::string description() const override;
private:
    double energy_;
};