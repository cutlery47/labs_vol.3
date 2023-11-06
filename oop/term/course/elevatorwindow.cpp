#include "elevatorwindow.h"


ElevatorWindow::ElevatorWindow(QWidget *parent): QMainWindow(parent)
{
    setWindowTitle("Elevators");

    this->resize(width, height);

    // inititalizing elevator tables with elevators inside of them
    this->table_1 = new ElevatorTable;
    this->table_2 = new ElevatorTable;

    // initializing elevators. passing a pointer to the current thread
    // the purpose is allowing elevator to switch to the main thread independently
    // (basically a hack + antipattern but who cares lol)
    this->elevator_1 = new Elevator(this->thread());
    this->elevator_2 = new Elevator(this->thread());

    // layout for tables
    this->layout = new QHBoxLayout;
    this->layout->addWidget(this->table_1);
    this->layout->addWidget(this->table_2);

    // updating window layout
    this->main_widget = new QWidget;
    this->main_widget->setLayout(this->layout);
    setCentralWidget(this->main_widget);

    // initializing control panel
    this->panel = new PanelWindow;

    // connecting buttons
    connect(this->panel->add_btn_1, SIGNAL(clicked()), this, SLOT(retrievePassenger_1()));
    connect(this->panel->launch_btn_1, SIGNAL(clicked()), this, SLOT(startThread_1()));
    connect(this->panel->add_btn_2, SIGNAL(clicked()), this, SLOT(retrievePassenger_2()));
    connect(this->panel->launch_btn_2, SIGNAL(clicked()), this, SLOT(startThread_2()));

    // sending acquired data to an instance of Elevator
    connect(this, SIGNAL(sendPassenger_1(Passenger*)), this->elevator_1, SLOT(addPassenger(Passenger*)));
    connect(this, SIGNAL(sendPassenger_2(Passenger*)), this->elevator_2, SLOT(addPassenger(Passenger*)));

    // sending confirmed passenger back to gui
    connect(this->elevator_1, SIGNAL(passengerAdded(Passenger*)), this->table_1, SLOT(updateElevatorPass(Passenger*)));
    connect(this->elevator_2, SIGNAL(passengerAdded(Passenger*)), this->table_2, SLOT(updateElevatorPass(Passenger*)));

    // sending info about elevator transition to gui
    connect(this->elevator_1, SIGNAL(applyTransit(int)), this->table_1, SLOT(updateElevatorFloor(int)));
    connect(this->elevator_2, SIGNAL(applyTransit(int)), this->table_2, SLOT(updateElevatorFloor(int)));

    // condition for elevator thread to end
    connect(this->elevator_1, SIGNAL(stopElevator()), this, SLOT(finishThread_1()));
    connect(this->elevator_2, SIGNAL(stopElevator()), this, SLOT(finishThread_2()));

    // i hate niggers
    connect(&first_thread, SIGNAL(started()), this->elevator_1, SLOT(moveElevator()));
    connect(&second_thread, SIGNAL(started()), this->elevator_2, SLOT(moveElevator()));

    this->show();
    this->panel->show();

}

// YEP, SOME LEGIT ASS CODE RIGHT HERE
void ElevatorWindow::retrievePassenger_1() {
    // checking if "to" and "from" attributes of a passenger are different
    if (this->panel->from_box_1->text().toInt() != this->panel->to_box_1->text().toInt()) {
        Passenger* pass = new Passenger(this->panel->from_box_1->text().toInt(), this->panel->to_box_1->text().toInt(), 1);
        emit(sendPassenger_1(pass));
    }


}

void ElevatorWindow::retrievePassenger_2() {
    // checking if "to" and "from" attributes of a passenger are different
    if (this->panel->from_box_2->text().toInt() != this->panel->to_box_2->text().toInt()) {
        Passenger* pass = new Passenger(this->panel->from_box_2->text().toInt(), this->panel->to_box_2->text().toInt(), 2);
        emit(sendPassenger_2(pass));
    }

}

// return to the main thread
void ElevatorWindow::finishThread_1() {
    this->first_thread.quit();
}

// return to the main thread
void ElevatorWindow::finishThread_2() {
    this->second_thread.quit();
}

// once an elevator been launched - throw it over the fence
void ElevatorWindow::startThread_1() {
    this->elevator_1->moveToThread(&first_thread);
    this->first_thread.start();
}

// once an elevator been launched - throw it over the fence
void ElevatorWindow::startThread_2() {
    this->elevator_2->moveToThread(&second_thread);
    this->second_thread.start();
}

ElevatorWindow::~ElevatorWindow() {

    delete this->elevator_1;
    delete this->elevator_2;
    delete this->layout;
    delete this->main_widget;
    delete this->panel;

}




