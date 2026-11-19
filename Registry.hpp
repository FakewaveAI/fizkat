#pragma once
#include "Inventory.hpp"
#include <array>
#include <ostream>
#include <vector>
#include <stdexcept>

template<typename T, int MaxSize>
class Registry {
public:
    void add(const T& newR) {
        if (size_ == MaxSize) {
            storage_[start_] = newR;
            start_ = (start_ + 1) % MaxSize;
        } else {
            storage_[size_] = newR;
            ++size_;
        }
    }
    int size() const {
        return size_;
    }
    const T& operator[](int i) const {
        if (i < 0 || i >= size_) {
            throw std::out_of_range("Registry index out of range");
        }
        return storage_[(start_ + i) % MaxSize];
    }

private:
    std::array<T, MaxSize> storage_{};
    int size_ = 0;
    int start_ = 0;
};

template <typename T, int MaxSize>
std::ostream& operator<<(std::ostream& out, const Registry<T, MaxSize>& reg) {
    for (int i = 0; i < reg.size(); ++i) {
        out << reg[i] << '\n';
    }
    return out;
}

template <typename Container>
Report makeReport(const Container& vals) {
    Report ans;
    for (auto& val : vals) {
        ans += *val;
    }
    return ans;
}

template <typename Container, typename Condition>
std::vector<const InventoryItem*> conditionSelect(const Container& vals, Condition cnd) {
    std::vector<const InventoryItem*> ans;
    for (auto& val : vals) {
        if (cnd(*val)) {
            ans.push_back(&*val);
        }
    }
    return ans;
}