#include "Fleet.hpp"
#include "Errors.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <string>
#include <cctype>

std::vector<std::string> splitWords(const std::string& line) {
    bool flag = true;
    std::vector<std::string> ans;
    ans.push_back("");
    for (auto& x : line) {
        if (isspace(x)) {
            if (flag == false) {
                ans.push_back("");
            }
            flag = true;
        } else {
            ans.back() += x;
            flag = false;
        }
    }
    if (ans.back().empty()) {
        ans.pop_back();
    }
    return ans;
}

void exceptSz(const std::vector<std::string>& words, int size, const std::string& hint) {
    if ((int)words.size() != size) {
        throw ParseError(hint);
    }
}

double toDouble(const std::string& word) {
    std::size_t ansSize = 0;
    try {
        double ans = std::stod(word, &ansSize);
        if (ansSize != word.size()) {
            throw ParseError("not a number: " + word);
        }
        return ans;
    } catch (const std::exception&) {
        throw ParseError("not a number: " + word);
    }
}

int toInt(const std::string& word) {
    std::size_t ansSize = 0;
    try {
        double ans = std::stoi(word, &ansSize);
        if (ansSize != word.size()) {
            throw ParseError("not a integer: " + word);
        }
        return ans;
    } catch (const std::exception&) {
        throw ParseError("not a integer: " + word);
    }
}

void doAdd(const std::vector<std::string>& words, Fleet& fleet, ServiceCenter& service) {
    std::string hint = "hint: add TYPE ...";
    if ((int)words.size() == 1) {
        throw ParseError(hint);
    }
    std::string type = words[1];
    if (type == "scooter") {
        hint = "hint: add scooter id name energy ease";
        exceptSz(words, 6, hint);
        fleet.addTransport(std::make_unique<ElectricScooter>
            (words[2], words[3], toDouble(words[4]), toInt(words[5])), service);
        return;
    }
    if (type == "bike") {
        hint = "hint: add bike id name ease";
        exceptSz(words, 5, hint);
        fleet.addTransport(std::make_unique<Bike>
            (words[2], words[3], toInt(words[4])), service);
        return;
    }
    if (type == "ebike") {
        hint = "hint: add ebike id name energy ease";
        exceptSz(words, 6, hint);
        fleet.addTransport(std::make_unique<ElectricBike>
            (words[2], words[3], toDouble(words[4]), toInt(words[5])), service);
        return;
    }
    if (type == "golf_cart") {
        hint = "hint: add golf_cart id name energy ease";
        exceptSz(words, 6, hint);
        fleet.addTransport(std::make_unique<GolfCart>
            (words[2], words[3], toDouble(words[4]), toInt(words[5])), service);
        return;
    }
    if (type == "helmet") {
        hint = "hint: add helmet id name";
        exceptSz(words, 4, hint);
        fleet.addThing(std::make_unique<Helmet>(words[2], words[3]));
        return;
    }
    if (type == "dock") {
        hint = "hint: add dock id name energy";
        exceptSz(words, 5, hint);
        fleet.addThing(std::make_unique<Dock>(words[2], words[3], toDouble(words[4])));
        return;
    }
    throw ParseError("unknown item type: " + type);
}

bool doCommand(const std::vector<std::string>& words, Fleet& fleet, ServiceCenter& service) {
    if (words[0] == "quit") {
        return false;
    }
    if (words[0] == "add") {
        doAdd(words, fleet, service);
        return true;
    }
    std::string hint = "";
    if (words[0] == "energy") {
        hint = "hint: energy";
        exceptSz(words, 1, hint);
        std::cout << std::fixed << std::setprecision(1) << fleet.report().eng << '\n';
        return true;
    }
    if (words[0] == "novice") {
        hint = "hint: novice";
        exceptSz(words, 1, hint);
        for (const InventoryItem* item : fleet.noviceItems()) {
            std::cout << *item << '\n';
        }
        return true;
    }
    if (words[0] == "list") {
        hint = "hint: list";
        exceptSz(words, 1, hint);
        for (const InventoryItem* item : fleet.sortedItems()) {
            std::cout << *item << '\n';
        }
        return true;
    }
    if (words[0] == "focus") {
        hint = "hint: focus id";
        exceptSz(words, 2, hint);
        fleet.setDisplay(words[1]);
        return true;
    }
    if (words[0] == "show_focus") {
        hint = "hint: show_focus";
        exceptSz(words, 1, hint);
        std::cout << fleet.printDisplay() << '\n';
        return true;
    }
    if (words[0] == "remove") {
        hint = "hint: remove id";
        exceptSz(words, 2, hint);
        fleet.removeId(words[1]);
        return true;
    }
    if (words[0] == "last") {
        hint = "hint: last";
        exceptSz(words, 1, hint);
        std::cout << fleet.lastTransportDescription() << '\n';
        return true;
    }
    throw ParseError("unknown command: " + words[0]);
}

int main() {
    Fleet fleet;
    ServiceCenter service;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<std::string> words = splitWords(line);
        if (words.empty()) {
            continue;
        }
        try {
            if (doCommand(words, fleet, service) == false) {
                break;
            }
        } catch (const FleetError& er) {
            std::cout << "error: " << er.what() << '\n';
        }
    }
    return 0;
}