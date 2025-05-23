#pragma once
#include "Property.h"

class Apartment : public Property {
    double square;

public:
    Apartment(unsigned int worth, double square);

    double getSquare() const;

    double calculateTax() const;
};

