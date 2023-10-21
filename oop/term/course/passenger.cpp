
#include "passenger.h"

Passenger::Passenger(int from, int to, int num)
{
    this->from_floor = from;
    this->to_floor = to;
    this->elevator_num = num;
}

Passenger::Passenger() {

}

int Passenger::to() {
    return this->to_floor;
}

int Passenger::from() {
    return this->from_floor;
}

int Passenger::elevator() {
    return this->elevator_num;
}

