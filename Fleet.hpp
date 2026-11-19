#pragma once
#include "Inventory.hpp"
#include "Transport.hpp"
#include "Things.hpp"
#include "ServiceCenter.hpp"
#include <memory>
#include <vector>
#include <string>

class Fleet {
public:
    void addTransport(std::unique_ptr<Transport> item, ServiceCenter& service);
    void addThing(std::unique_ptr<Thing> item);
    void removeId(const std::string& id);
    Report report() const;
    std::vector<const InventoryItem*> sortedItems() const;
    std::vector<const InventoryItem*> noviceItems() const;
    void setDisplay(const std::string& id);
    std::string printDisplay() const;
    std::string lastTransportDescription() const;
private:
    std::vector<std::shared_ptr<InventoryItem>> items_;
    std::weak_ptr<InventoryItem> display_;
    bool displayed_ = false;
    int findId(const std::string& id) const;
    void testFreeId(const std::string& id) const;
    std::weak_ptr<InventoryItem> lastTransport_;
    bool hasLast_ = false;
};