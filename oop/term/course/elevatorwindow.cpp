#include "elevatorwindow.h"


ElevatorWindow::ElevatorWindow(QWidget *parent): QMainWindow(parent)
{
    setWindowTitle("Elevators");

    this->resize(width, height);

    //inititalizing elevator tables with elevators inside of them
    this->elevator_1 = new ElevatorTable(this);
    this->elevator_2 = new ElevatorTable(this);

    this->layout = new QHBoxLayout;
    this->layout->addWidget(this->elevator_1);
    this->layout->addWidget(this->elevator_2);

    //updating window layout
    this->main_widget = new QWidget;
    this->main_widget->setLayout(this->layout);
    setCentralWidget(this->main_widget);

    // creating a panel
    this->panel = new PanelWindow;

    // retrieving data from panel to window
    connect(this->panel->add_btn_1, SIGNAL(clicked()), this, SLOT(retrievePassenger_1()));
    connect(this->panel->add_btn_2, SIGNAL(clicked()), this, SLOT(retrievePassenger_2()));

    // sending acquired data to an instance of Elevator
    connect(this, SIGNAL(sendPassenger_1(Passenger*)), this->elevator_1->elevator, SLOT(addPassenger(Passenger*)));
    connect(this, SIGNAL(sendPassenger_2(Passenger*)), this->elevator_2->elevator, SLOT(addPassenger(Passenger*)));

    connect(this->elevator_1->elevator, SIGNAL(passengerAdded(Passenger*)), this->elevator_1, SLOT(updateElevatorUI(Passenger*)));
    connect(this->elevator_2->elevator, SIGNAL(passengerAdded(Passenger*)), this->elevator_2, SLOT(updateElevatorUI(Passenger*)));


    this->show();
    this->panel->show();
}

// YEP, SOME LEGIT ASS CODE RIGHT HERE
void ElevatorWindow::retrievePassenger_1() {
    Passenger* pass = new Passenger(this->panel->from_box_1->text().toInt(), this->panel->to_box_1->text().toInt(), 1);
    emit(sendPassenger_1(pass));

}

void ElevatorWindow::retrievePassenger_2() {
    Passenger* pass = new Passenger(this->panel->from_box_2->text().toInt(), this->panel->to_box_2->text().toInt(), 2);
    emit(sendPassenger_2(pass));

}

ElevatorWindow::~ElevatorWindow()
{
    delete this->elevator_1;
    delete this->elevator_2;
    delete this->layout;
    delete this->main_widget;
    delete this->panel;
}




