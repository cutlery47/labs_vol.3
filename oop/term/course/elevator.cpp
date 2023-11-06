#include "elevator.h"

Elevator::Elevator(QThread* p_thread)
{
    this->max_passengers = 5;
    this->floor = 1;
    this->state = idle;
    this->parent_thread = p_thread;
}


Elevator::~Elevator() {
    for (int i = 0; i < passengers.length(); ++i) {
        delete passengers[i];
    }
}


void Elevator::moveElevator() {
    int i = 0;

    this->state = moving;

    while (i < 2) {
        if (this->state == idle) {
            QThread::msleep(500);
        }
        this->floor += 1;
        emit applyTransit(this->floor);
        QThread::msleep(250);
        ++i;
    }

    moveToThread(this->parent_thread);
    emit stopElevator();

}

void Elevator::addPassenger(Passenger* pass) {
    // just to make sure that the passenger has been added

    if (this->passengers.length() < 5) {
        passengers.append(pass);
        emit passengerAdded(pass);
    } else {
        qInfo() << "Elevator is full...";
    }

}

