#pragma once
#include "Property.h"

class Car : public Property {
private:
    double horsepower;

public:
    Car(unsigned int worth, double horsepower);

    double getHorsepower() const;

    double calculateTax() const;
};

