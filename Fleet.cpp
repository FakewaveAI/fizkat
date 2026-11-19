#include "Fleet.hpp"
#include "Errors.hpp"
#include <algorithm>

int Fleet::findId(const std::string &id) const {
    for (int i = 0; i < (int)items_.size(); ++i) {
        if (items_[i]->getID() == id) {
            return i;
        }
    }
    return -1;
}

void Fleet::testFreeId(const std::string &id) const {
    if (findId(id) != -1) {
        throw DuplicateID(id);
    }
}

void Fleet::addTransport(std::unique_ptr<Transport> item, ServiceCenter& service) {
    testFreeId(item->getID());
    service.inspect(*item);
    items_.push_back(std::move(item));
    lastTransport_ = items_.back();
    hasLast_ = true;
}

void Fleet::addThing(std::unique_ptr<Thing> item) {
    testFreeId(item->getID());
    items_.push_back(std::move(item));
}

void Fleet::removeId(const std::string &id) {
    int i = findId(id);
    if (i == -1) {
        throw UnknownID(id);
    }
    items_.erase(items_.begin() + i);
}

Report Fleet::report() const {
    return makeReport(items_);
}

std::vector<const InventoryItem*> Fleet::sortedItems() const {
    std::vector<const InventoryItem*> ans =
        conditionSelect(items_, [](const InventoryItem&){ return true; });
    std::sort(ans.begin(), ans.end(),
        [](const InventoryItem* a, const InventoryItem* b){ return *a < *b; });
    return ans;
}

std::vector<const InventoryItem*> Fleet::noviceItems() const {
    std::vector<const InventoryItem*> ans = sortedItems();
    ans = conditionSelect(ans, [](const InventoryItem& x) { return x.isForNovice(); });
    return ans;
}

void Fleet::setDisplay(const std::string &id) {
    int i = findId(id);
    if (i == -1) {
        throw UnknownID(id);
    }
    display_ = items_[i];
    displayed_ = true;
}

std::string Fleet::printDisplay() const {
    if (!displayed_) {
        return "empty";
    }
    std::shared_ptr<InventoryItem> item = display_.lock();
    if (item == nullptr) {
        return "removed";
    }
    return item->description();
}

std::string Fleet::lastTransportDescription() const {
    if (!hasLast_) {
        return "empty";
    }
    std::shared_ptr<InventoryItem> item = lastTransport_.lock();
    if (item == nullptr) {
        return "removed";
    }
    return item->description();
}
