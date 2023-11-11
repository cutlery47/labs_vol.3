#include "elevatorwindow.h"


ElevatorWindow::ElevatorWindow(QWidget *parent): QMainWindow(parent)
{
    setWindowTitle("Elevators");

    this->resize(width, height);

    // создание таблиц
    this->table_1 = new ElevatorTable;
    this->table_2 = new ElevatorTable;

    // создание лифтов + передача указателя на главный поток
    this->elevator_1 = new Elevator(this->thread());
    this->elevator_2 = new Elevator(this->thread());

    //GUI
    this->status_bar = new QHBoxLayout;
    this->status_1 = new QVBoxLayout;
    this->status_2 = new QVBoxLayout;

    this->awaiting_status_1 = new QLabel("Awaiting passengers: 0");
    this->boarded_status_1 = new QLabel("Boarded passengers: 0");
    this->status_1->addWidget(awaiting_status_1);
    this->status_1->addWidget(boarded_status_1);

    this->awaiting_status_2 = new QLabel("Awaiting passengers: 0");
    this->boarded_status_2 = new QLabel("Boarded passengers: 0");
    this->status_2->addWidget(awaiting_status_2);
    this->status_2->addWidget(boarded_status_2);

    this->status_bar->addLayout(status_1);
    this->status_bar->addLayout(status_2);

    this->tables = new QHBoxLayout;
    this->tables->addWidget(this->table_1);
    this->tables->addWidget(this->table_2);

    this->main_layout = new QVBoxLayout;
    this->main_layout->addLayout(tables);
    this->main_layout->addLayout(status_bar);

    // обновляем layout
    this->main_widget = new QWidget;
    this->main_widget->setLayout(this->main_layout);
    setCentralWidget(this->main_widget);

    // создаем панель управления
    this->panel = new PanelWindow;

    // коннект кнопок
    connect(this->panel->add_btn_1, SIGNAL(clicked()), this, SLOT(retrievePassenger_1()));
    connect(this->panel->launch_btn_1, SIGNAL(clicked()), this, SLOT(startThread_1()));
    connect(this->panel->add_btn_2, SIGNAL(clicked()), this, SLOT(retrievePassenger_2()));
    connect(this->panel->launch_btn_2, SIGNAL(clicked()), this, SLOT(startThread_2()));

    // перелача данных из панели в лифт
    connect(this, SIGNAL(sendPassenger_1(Passenger*)), this->elevator_1, SLOT(addPassenger(Passenger*)));
    connect(this, SIGNAL(sendPassenger_2(Passenger*)), this->elevator_2, SLOT(addPassenger(Passenger*)));

    // отправка подтвержденных данных обратно в GUI
    connect(this->elevator_1, SIGNAL(passengerAdded(Passenger*)), this->table_1, SLOT(updateElevatorPass(Passenger*)));
    connect(this->elevator_2, SIGNAL(passengerAdded(Passenger*)), this->table_2, SLOT(updateElevatorPass(Passenger*)));

    // обновление GUI
    connect(this->elevator_1, SIGNAL(applyTransit(int)), this->table_1, SLOT(updateElevatorFloor(int)));
    connect(this->elevator_2, SIGNAL(applyTransit(int)), this->table_2, SLOT(updateElevatorFloor(int)));
    connect(this->elevator_1, SIGNAL(applyBoarding(int)), this->table_1, SLOT(updateBoardedPass(int)));
    connect(this->elevator_2, SIGNAL(applyBoarding(int)), this->table_2, SLOT(updateBoardedPass(int)));

    // остановка доп потоков
    connect(this->elevator_1, SIGNAL(stopElevator()), this, SLOT(finishThread_1()));
    connect(this->elevator_2, SIGNAL(stopElevator()), this, SLOT(finishThread_2()));

    // обновление панели статуса
    connect(this->elevator_1, SIGNAL(updateStatus(int,int)), this, SLOT(updateElevatorStatus_1(int,int)));
    connect(this->elevator_2, SIGNAL(updateStatus(int,int)), this, SLOT(updateElevatorStatus_2(int,int)));

    // магия вне хогвартса
    connect(&first_thread, SIGNAL(started()), this->elevator_1, SLOT(moveElevator()));
    connect(&second_thread, SIGNAL(started()), this->elevator_2, SLOT(moveElevator()));

    this->show();
    this->panel->show();

}

void ElevatorWindow::retrievePassenger_1() {
    if (this->panel->from_box_1->text().toInt() != this->panel->to_box_1->text().toInt()) {
        Passenger* pass = new Passenger(this->panel->from_box_1->text().toInt(), this->panel->to_box_1->text().toInt());
        emit(sendPassenger_1(pass));
    }


}

void ElevatorWindow::retrievePassenger_2() {
    if (this->panel->from_box_2->text().toInt() != this->panel->to_box_2->text().toInt()) {
        Passenger* pass = new Passenger(this->panel->from_box_2->text().toInt(), this->panel->to_box_2->text().toInt());
        emit(sendPassenger_2(pass));
    }

}

void ElevatorWindow::updateElevatorStatus_1(int awaiting, int boarded) {
    QString status_1 = "Awaiting passengers: " + QString::number(awaiting);
    QString status_2 = "Boarded passengers: " + QString::number(boarded);

    this->awaiting_status_1->setText(status_1);
    this->boarded_status_1->setText(status_2);
}

void ElevatorWindow::updateElevatorStatus_2(int awaiting, int boarded) {
    QString status_1 = "Awaiting passengers: " + QString::number(awaiting);
    QString status_2 = "Boarded passengers: " + QString::number(boarded);

    this->awaiting_status_2->setText(status_1);
    this->boarded_status_2->setText(status_2);
}

// возвращаемся в главный поток
void ElevatorWindow::finishThread_1() {
    this->first_thread.quit();
}

// возвращаемся в главный поток
void ElevatorWindow::finishThread_2() {
    this->second_thread.quit();
}

void ElevatorWindow::startThread_1() {
    this->elevator_1->moveToThread(&first_thread);
    this->first_thread.start();
}

void ElevatorWindow::startThread_2() {
    this->elevator_2->moveToThread(&second_thread);
    this->second_thread.start();
}

ElevatorWindow::~ElevatorWindow() {

    delete this->elevator_1;
    delete this->elevator_2;
    delete this->main_layout;
    delete this->main_widget;
    delete this->panel;

}




