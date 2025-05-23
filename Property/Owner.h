#pragma once
#include "Property.h"

class Owner {
    string fullname;
    string inn;
    vector<Property*> properties;

    bool isValidINN(const string& inn) const;

public:
    Owner(const string& fullname, const string& inn);

    void addProperty(Property* property);

    bool removeProperty(Property* property);

    double calculateTotalPropertyTax() const;

    double calculateTotalIncomeTax() const;

    string getFullname() const;

    string getINN() const;

    const vector<Property*>& getProperties() const;

    ~Owner();
};


