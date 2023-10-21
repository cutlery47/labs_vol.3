#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QDebug>
#include <QVector>

#include <passenger.h>


class Elevator: public QObject
{
    Q_OBJECT;

private:
    int max_passengers;
    int curr_floor;
    QVector<Passenger*> passengers;



public slots:
    void addPassenger(Passenger* pass);

signals:
    void passengerAdded(Passenger* pass);

public:
    Elevator(QObject* parent = nullptr);
    ~Elevator();

};

#endif // ELEVATOR_H
