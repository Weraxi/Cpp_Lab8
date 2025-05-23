#include "Apartment.h"

Apartment::Apartment(unsigned int worth, double square) : Property(worth), square(square) {}

double Apartment::getSquare() const { return square; }

double Apartment::calculateTax() const {
    if (square <= TAX_RATES::LIMIT_APARTMENT_SQUARE)
        return worth * TAX_RATES::APARTMENT_TAX;

    else return worth * TAX_RATES::APARTMENT_LUXURY_TAX;
}