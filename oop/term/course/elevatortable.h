
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
    QTableWidgetItem cell;
    QHBoxLayout layout;
    int cur_floor = 1;

public:
    Elevator* elevator;
    ElevatorTable(Elevator* elevator);
    ~ElevatorTable();

};

#endif // ELEVATORTABLE_H
