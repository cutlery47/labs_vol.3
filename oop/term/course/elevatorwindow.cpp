#include "elevatorwindow.h"


ElevatorWindow::ElevatorWindow(QWidget *parent): QMainWindow(parent)
{
    setWindowTitle("Elevators");

    this->resize(width, height);

    //inititalizing elevator tables with elevators inside of them
    this->elevator_1 = new ElevatorTable(new Elevator);
    this->elevator_2 = new ElevatorTable(new Elevator);

    this->layout.addWidget(this->elevator_1);
    this->layout.addWidget(this->elevator_2);

    //updating window layout
    QWidget *widget = new QWidget;
    widget->setLayout(&(this->layout));
    setCentralWidget(widget);

    // creating a panel
    panel = new PanelWindow;

    // connecting signals
    connect(&panel->add_btn_1, SIGNAL(clicked()), elevator_1->elevator, SLOT(smth()));
    connect(&panel->add_btn_2, SIGNAL(clicked()), elevator_2->elevator, SLOT(smth()));


    this->show();
    panel->show();
}

ElevatorWindow::~ElevatorWindow()
{
    delete elevator_1;
    delete elevator_2;
}




