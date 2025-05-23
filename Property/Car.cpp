#include "Car.h"

Car::Car(unsigned int worth, double horsepower) : Property(worth), horsepower(horsepower) {}

double Car::getHorsepower() const { return horsepower; }

double Car::calculateTax() const {
    if (horsepower < TAX_RATES::LOW_HORSEPOWER)
        return worth * TAX_RATES::CAR_TAX;

    else if (horsepower > TAX_RATES::HIGH_HORSEPOWER)
        return worth * TAX_RATES::CAR_LUXURY_TAX;

    else return worth * TAX_RATES::CAR_TRUCK_TAX;
}