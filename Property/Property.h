#pragma once
#include "tax_rates.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <iomanip>
#include <limits>

using namespace std;

class Property {
protected:
    unsigned int worth;

public:
    Property(unsigned int worth);

    virtual double calculateTax() const = 0;

    double calculateIncomeTax() const;

    unsigned int getWorth() const;

    void setWorth(unsigned int newWorth);

    virtual ~Property();
};

