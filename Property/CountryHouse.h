#pragma once
#include "Property.h"

class CountryHouse : public Property {
private:
    unsigned int distanceFromCity;

public:
    CountryHouse(unsigned int worth, unsigned int distance);

    unsigned int getDistanceFromCity() const;

    double calculateTax() const;
};

