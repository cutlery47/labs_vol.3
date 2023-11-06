#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QTimer>
#include <QThread>

#include <passenger.h>

enum elevator_state {
    idle = 0,
    moving = 1
};

class Elevator: public QObject
{
    Q_OBJECT;

    // elevator can quit current thread if needed
    QThread* parent_thread;

    // attributes
    int max_passengers;
    int floor;
    QVector<Passenger*> passengers;


public slots:
    void addPassenger(Passenger* pass);
    void moveElevator();

signals:
    void passengerAdded(Passenger* pass);
    void applyTransit(int floor);
    void stopElevator();

public:
    Elevator(QThread* parent_thread);
    ~Elevator();

    int state = idle;

};

#endif // ELEVATOR_H
