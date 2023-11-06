#ifndef ELEVATORWINDOW_H
#define ELEVATORWINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include <QDialog>
#include <QDebug>

#include "elevatortable.h"
#include "panelwindow.h"

class ElevatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    ElevatorWindow(QWidget *parent = nullptr);
    ~ElevatorWindow();

    //GUI for elevators
    ElevatorTable* table_1;
    ElevatorTable* table_2;

    //Elevators themselves
    Elevator* elevator_1;
    Elevator* elevator_2;

    int height = 600;
    int width = 800;

private:
    int t;

    QHBoxLayout* layout;
    PanelWindow* panel;
    QWidget* main_widget;

    QThread first_thread;
    QThread second_thread;

private slots:
    void retrievePassenger_1();
    void retrievePassenger_2();
    void startThread_1();
    void startThread_2();
    void finishThread_1();
    void finishThread_2();



signals:
    void sendPassenger_1(Passenger* pass);
    void sendPassenger_2(Passenger* pass);

};

#endif // ELEVATORWINDOW_H
