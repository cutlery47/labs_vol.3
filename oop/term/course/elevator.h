#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QDebug>

#include <passenger.h>


class Elevator: public QObject
{
    Q_OBJECT;

private:
    int max_passengers;
    int curr_floor;
    int passangers;
    Passenger* passengers;

public slots:
    void smth();

public:
    Elevator();
    ~Elevator();

};

#endif // ELEVATOR_H
