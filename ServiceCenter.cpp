#include "ServiceCenter.hpp"
#include "Errors.hpp"
#include <cctype>

std::ostream& operator<<(std::ostream& out, const CheckUpRecord& record) {
    out << record.id << " " << record.name << ": " << (record.okay ? "accepted" : "rejected");
    return out;
}

bool ServiceCenter::isBroken(const std::string &s) {
    for (int i = 0; i + 6 <= (int)s.size(); ++i) {
        std::string t = "";
        for (int j = i; j < i + 6; ++j) {
            t += std::tolower(s[j]);
        }
        if (t == "broken") {
            return true;
        }
    }
    return false;
}

void ServiceCenter::inspect(const Transport& t) {
    bool okay = !isBroken(t.getName());
    logbook_.add({t.getID(), t.getName(), okay});
    if (!okay) {
        throw InspectionRejected();
    }
}

const ServiceCenter::Logbook& ServiceCenter::getLogbook() const {
    return logbook_;
}
