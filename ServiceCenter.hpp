#pragma once
#include "Registry.hpp"
#include "Transport.hpp"
#include <ostream>

struct CheckUpRecord {
    std::string id;
    std::string name;
    bool okay = false;
};

std::ostream& operator<<(std::ostream& out, const CheckUpRecord& record);

class ServiceCenter {
public:
    static constexpr int cLogbookSize = 16;
    using Logbook = Registry<CheckUpRecord, cLogbookSize>;
    void inspect(const Transport& t);
    const Logbook& getLogbook() const;
private:
    static bool isBroken(const std::string& s);
    Logbook logbook_;
};