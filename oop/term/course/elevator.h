#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QTimer>
#include <QThread>

#include <passenger.h>


// энум для определения движения лифта
enum elevator_state {
    idle = 0,
    moving = 1
};

// энум для определения назначения движения лифта
enum elevator_dest {
    pickup = 0,
    transit = 1
};

class Elevator: public QObject
{
    Q_OBJECT;

    // поток родителя, чтобы объект лифта мог самостоятельно входить в главный поток
    QThread* parent_thread;
    // максимальное количество пассажиров
    int max_passengers;
    // текущий этаж лифта
    int floor;

    // пассажиры, ожидающие посадки
    QVector<Passenger*> awaiting;
    // пассажиры, находящиеся в лифте
    QVector<Passenger*> onboard;

    // определение ближайшего этажа, на котором ожидает пасадки пассажир
    int nearestPassenger();
    // определение ближайшего этажа, на который можно доставить пассажира
    int nearestDestination();

    // посадка пассажиров
    void boardPassengers();
    // выход пассажиров
    void unboardPassengers();

    //изначально лифт не двигается
    int state = idle;


public slots:
    // слот для добавления нового пассажира в очередь ожидающих
    void addPassenger(Passenger* pass);
    // передвижение лифта (главный цикл лифта)
    void moveElevator();

signals:
    // пассажир добавлен
    void passengerAdded(Passenger* pass);
    // обновление UI
    void applyTransit(int floor);
    void applyBoarding(int floor);
    void updateStatus(int awaiting, int boarded);
    // остановка цикла
    void stopElevator();


public:
    Elevator(QThread* parent_thread);
    ~Elevator();



};

#endif // ELEVATOR_H
