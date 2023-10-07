
#include "elevatortable.h"
#include <iostream>

ElevatorTable::ElevatorTable(Elevator* elevator)
{
    this->elevator = elevator;

    this->table.setColumnCount(2);
    this->table.setRowCount(9);

    this->table.setHorizontalHeaderLabels({"Direction", "Passengers"});
    this->table.setVerticalHeaderLabels({"9", "8", "7", "6", "5", "4", "3", "2", "1"});

    this->cell.setText("↑");
    this->cell.setBackground(Qt::green);
    this->cell.setTextAlignment(Qt::AlignCenter);

    this->table.setItem(8, 0, &(this->cell));

    this->table.resizeColumnsToContents();
    this->table.horizontalHeader()->setStretchLastSection(true);
    this->table.verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->layout.addWidget(&(this->table));
    this->setLayout(&(this->layout));
}

ElevatorTable::~ElevatorTable() {
    delete elevator;
}

