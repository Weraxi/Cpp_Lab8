#include "Owner.h"

bool Owner::isValidINN(const string& inn) const {
    if (inn.length() != 12) return false;

    return all_of(inn.begin(), inn.end(), ::isdigit);
}

Owner::Owner(const string& fullname, const string& inn) {
    this->fullname = fullname;

    if (!isValidINN(inn))
        throw invalid_argument("ИНН должен содержать ровно 12 цифр");

    this->inn = inn;
}

void Owner::addProperty(Property* property) {
    if (property == nullptr)
        throw invalid_argument("Нельзя добавить NULL в качестве имущества");

    properties.push_back(property);
}

bool Owner::removeProperty(Property* property) {
    auto it = remove_if(properties.begin(), properties.end(),
        [property](Property* p) { return p == property; });

    if (it != properties.end()) {
        properties.erase(it, properties.end());
        return true;
    }

    return false;
}

double Owner::calculateTotalPropertyTax() const {
    double totalTax = 0.0;

    for (const auto& property : properties)
        totalTax += property->calculateTax();

    return totalTax;
}

double Owner::calculateTotalIncomeTax() const {
    double totalWorth = 0.0;

    for (const auto& property : properties)
        totalWorth += property->getWorth();

    return totalWorth * 0.13;
}

string Owner::getFullname() const { return fullname; }

string Owner::getINN() const { return inn; }

const vector<Property*>& Owner::getProperties() const { return properties; }

Owner::~Owner() {
    for (auto& property : properties)
        delete property;
}