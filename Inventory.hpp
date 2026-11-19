#pragma once
#include <string>
#include <ostream>

class EnergyConsumer {
public:
    virtual ~EnergyConsumer() = default;
    virtual double dailyEnergy() const = 0;
};

class InventoryItem {
public:
    virtual ~InventoryItem() = default;
    virtual const std::string& getID() const = 0;
    virtual const std::string& getName() const = 0;
    virtual std::string type() const = 0;
    virtual std::string description() const = 0;
    virtual const EnergyConsumer* energy() const { return nullptr; }
    virtual bool isForNovice() const { return false; }
};

class ItemBase : public InventoryItem{
public:
    ItemBase(const std::string& id, const std::string& name);
    const std::string& getID() const override {
        return id_;
    }
    const std::string& getName() const override {
        return name_;
    }
private:
    const std::string id_;
    const std::string name_;
};

double checkedEnergy(double e);

std::string formatEnergy(double e);

std::ostream& operator<<(std::ostream& out, const InventoryItem& a);

bool operator<(const InventoryItem& a, const InventoryItem& b);

struct Report {
    int cnt = 0;
    double eng = 0;
    Report& operator+=(const InventoryItem& b);
};
