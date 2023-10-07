#include "elevator.h"

Elevator::Elevator()
{
    this->max_passengers = 5;
    this->curr_floor = 1;
    this->passangers = 0;

    passengers = new Passenger[max_passengers];
}

Elevator::~Elevator() {
    delete[] passengers;
}

void Elevator::smth() {
    qInfo("123123");
}

