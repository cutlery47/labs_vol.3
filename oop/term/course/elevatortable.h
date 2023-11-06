
#ifndef ELEVATORTABLE_H
#define ELEVATORTABLE_H

#include "elevator.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QDebug>

class ElevatorTable : public QWidget
{
    Q_OBJECT;

private:
    QTableWidget table;
    QHBoxLayout layout;
    int height = 9;
    int width = 2;
    int cur_floor = 1;


    void clearCell(int height, int width);

private slots:
    void updateElevatorPass(Passenger* pass);
    void updateElevatorFloor(int floor);




public:
    ElevatorTable();
    ~ElevatorTable();

};

#endif // ELEVATORTABLE_H
