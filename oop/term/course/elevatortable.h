
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

private slots:
    void updateElevatorUI(Passenger* pass);

public:
    Elevator* elevator;
    ElevatorTable(QObject *parent = nullptr);
    ~ElevatorTable();

};

#endif // ELEVATORTABLE_H
