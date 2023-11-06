
#include "elevatortable.h"
#include <iostream>

ElevatorTable::ElevatorTable()
{
    // setting up the table
    this->table.setColumnCount(width);
    this->table.setRowCount(height);
    this->table.setHorizontalHeaderLabels({"Direction", "Passengers"});
    this->table.setVerticalHeaderLabels({"9", "8", "7", "6", "5", "4", "3", "2", "1"});

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            QTableWidgetItem* cell = new QTableWidgetItem;
            cell->setTextAlignment(Qt::AlignCenter);
            this->table.setItem(i, j, cell);

        }
    }

    // setting up the default cell
    this->table.item(height - 1, 0)->setBackground(Qt::green);
    this->table.item(height - 1, 0)->setText("↑");

    // something
    this->table.resizeColumnsToContents();
    this->table.horizontalHeader()->setStretchLastSection(true);
    this->table.verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->layout.addWidget(&(this->table));
    this->setLayout(&(this->layout));
}

// updating gui when a new passenger has been added
void ElevatorTable::updateElevatorPass(Passenger* pass) {
    int from = pass->from();
    int to = pass->to();

    QString text = "FROM: " + QString::number(from) + " TO: " + QString::number(to) + ";";

    if (this->table.item(height - from, 1)->text().length() != 0) {
        text = this->table.item(height - from, 1)->text() + text;
    }

    this->table.item(height - from, 1)->setText(text);

}

// erasing cell space
void ElevatorTable::clearCell(int height, int width) {
    this->table.item(height, width)->setText("");
    this->table.item(height, width)->setBackground(Qt::white);

}

// updating current cell gui
void ElevatorTable::updateElevatorFloor(int floor) {
    clearCell(height - cur_floor, 0);
    this->cur_floor = floor;

    this->table.item(height - cur_floor, 0)->setBackground(Qt::green);
    this->table.item(height - cur_floor, 0)->setText("↑");

}

ElevatorTable::~ElevatorTable() {

}

