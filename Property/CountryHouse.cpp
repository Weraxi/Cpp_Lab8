#include "CountryHouse.h"

CountryHouse::CountryHouse(unsigned int worth, unsigned int distance) : Property(worth), distanceFromCity(distance) {}

unsigned int CountryHouse::getDistanceFromCity() const { return distanceFromCity; }

double CountryHouse::calculateTax() const {
    if (distanceFromCity <= TAX_RATES::LIMIT_DISTANCE_FROM_CITY)
        return worth * TAX_RATES::APARTMENT_TAX;

    else return worth * TAX_RATES::COUNTRY_HOUSE_TAX;
}
