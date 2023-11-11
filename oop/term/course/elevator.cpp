#include "elevator.h"

Elevator::Elevator(QThread* p_thread)
{
    this->max_passengers = 5;
    this->floor = 1;
    this->state = idle;
    this->parent_thread = p_thread;
}

void Elevator::addPassenger(Passenger* pass) {
    // добавляем пассажира в очередь и отправляем сигнал в UI
    if (this->awaiting.length() < this->max_passengers) {
        awaiting.append(pass);
        emit passengerAdded(pass);
    } else {
        qInfo() << "Elevator is full...";
    }

}

int Elevator::nearestPassenger() {
    // пробегаемся по всем ожидающим пассажирам и находим того, у которого
    // значение атрибута from отличается от текущего этажа лифта меньше всего
    // (ближайшее расстояние до пассажира)

    int min = 10;
    int dest = 0;

    for(int i = 0; i < awaiting.length(); ++i) {
        int diff = std::abs(this->floor - this->awaiting[i]->from());
        if (diff < min) {
            dest = this->awaiting[i]->from();
            min = diff;
        }
    }
    return dest;
}

int Elevator::nearestDestination() {
    // пробегаемся по всем пассажирам в лифте и находим того, у которого
    // значение атрибута to отличается от текущего этажа лифта меньше всего
    // (ближайшее расстояние до точки назначения)

    int min = 10;
    int dest = 0;

    for(int i = 0; i < onboard.length(); ++i) {
        int diff = std::abs(this->floor - this->onboard[i]->to());
        if (diff < min) {
            dest = this->onboard[i]->to();
            min = diff;
        }
    }
    return dest;
}

void Elevator::boardPassengers() {
    // берем элементы из awaiting и вставляем в onboard

    for (int i = 0; i < awaiting.length(); ++i) {
        if (this->floor == awaiting[i]->from()) {
            onboard.append(awaiting[i]);
            awaiting.removeAt(i);
        }
    }

    emit(applyBoarding(this->floor));
    emit(updateStatus(awaiting.length(), onboard.length()));
}

void Elevator::unboardPassengers() {
    // удаляем элементы из onboard

    for (int i = 0; i < onboard.length(); ++i) {
        if (this->floor == onboard[i]->to()) {
            onboard.removeAt(i);
        }
    }

    emit(updateStatus(awaiting.length(), onboard.length()));
}


void Elevator::moveElevator() {
    emit(updateStatus(awaiting.length(), onboard.length()));

    int mode = pickup;
    int destination = nearestPassenger();

    // двигаемся, пока очередь и лифт будут пусты
    while (!(awaiting.length() == 0 && onboard.length() == 0)) {
        if (destination > this->floor) {
            this->floor += 1;
        } else if (destination < this->floor) {
            this->floor -= 1;
        } else {
            //делаем вид что пассажиры заходят
            QThread::msleep(250);

            // в зависимости от назначения, производим соотв. операцию
            if (mode == pickup) {
                boardPassengers();
            } else if (mode == transit) {
                unboardPassengers();
            }

            int near_dest = nearestDestination();
            int near_pass = nearestPassenger();

            //определяем куда двигаться ближе
            if (near_pass == 0) {
                destination = near_dest;
                mode = transit;
            } else if (near_dest == 0) {
                destination = near_pass;
                mode = pickup;
            } else if (std::abs(this->floor - near_pass) <= std::abs(this->floor - near_dest)) {
                destination = near_pass;
                mode = pickup;
            } else if (std::abs(this->floor - near_pass) > std::abs(this->floor - near_dest)) {
                destination = near_dest;
                mode = transit;
            }
        }

        emit(applyTransit(this->floor));
        QThread::msleep(1000);
    }

    // выход в главный поток
    moveToThread(this->parent_thread);
    emit stopElevator();
}

Elevator::~Elevator() {
    for (int i = 0; i < awaiting.length(); ++i) {
        delete awaiting[i];
    }

    for (int i = 0; i < onboard.length(); ++i) {
        delete onboard[i];
    }

    delete parent_thread;
}



