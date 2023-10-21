#include "elevator.h"

Elevator::Elevator(QObject* parent) : QObject(parent)
{
    this->max_passengers = 5;
    this->curr_floor = 1;
}

Elevator::~Elevator() {
    for (int i = 0; i < passengers.length(); ++i) {
        delete passengers[i];
    }
}



void Elevator::addPassenger(Passenger* pass) {
    // just to make sure that the passenger has been added

    if (this->passengers.length() < 5) {
        passengers.append(pass);
    } else {
        qInfo() << "Elevator is full...";
    }

    emit(passengerAdded(pass));

}

