#pragma once
#include <exception>
#include <string>

class FleetError : public std::exception {
public:
    explicit FleetError(const std::string& msg) : msg_(msg) {}
    const char* what() const noexcept override { return msg_.c_str(); }
private:
    std::string msg_;
};

class InspectionRejected : public FleetError {
public:
    InspectionRejected() : FleetError("inspection rejected") {}
};

class ParseError : public FleetError {
public:
    using FleetError::FleetError;
};

class IncorrectArgument : public FleetError {
public:
    explicit IncorrectArgument(const std::string& c) : FleetError("incorrect argument: " + c) {}
};

class UnknownID : public FleetError {
public:
    explicit UnknownID(const std::string& c) : FleetError("unknown id: " + c) {}
};

class DuplicateID : public FleetError {
public:
    explicit DuplicateID(const std::string& c) : FleetError("id " + c + " already exists") {}
};

