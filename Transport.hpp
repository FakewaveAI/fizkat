#pragma once
#include "Inventory.hpp"
#include <string>

class Transport : public ItemBase {
public:
    static constexpr int cNoviceThreshold = 6;
    Transport(const std::string& id, const std::string& name, int ease);
    int getEaseOfUse() const;
    bool isForNovice() const override;
    std::string description() const override;
private:
    int easeOfUse_;
};

class Bike final : public Transport {
public:
    Bike(const std::string& id, const std::string& name, int ease);
    std::string type() const override;
};

class ElectricTransport : public Transport, public EnergyConsumer {
public:
    ElectricTransport(const std::string& id, const std::string& name, double energy, int ease);
    double dailyEnergy() const override;
    const EnergyConsumer* energy() const override;
    std::string description() const override;
private:
    double energy_;
};

class ElectricScooter final : public ElectricTransport {
public:
    using ElectricTransport::ElectricTransport;
    std::string type() const override;
};

class ElectricBike final : public ElectricTransport {
public:
    using ElectricTransport::ElectricTransport;
    std::string type() const override;
};

class GolfCart final : public ElectricTransport {
public:
    using ElectricTransport::ElectricTransport;
    bool isForNovice() const override { return false; }
    std::string type() const override;
    std::string description() const override;
};