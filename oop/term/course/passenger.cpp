
#include "passenger.h"

Passenger::Passenger(int from, int to)
{
    this->from_floor = from;
    this->to_floor = to;
}

Passenger::Passenger() {

}

int Passenger::to() {
    return this->to_floor;
}

int Passenger::from() {
    return this->from_floor;
}


