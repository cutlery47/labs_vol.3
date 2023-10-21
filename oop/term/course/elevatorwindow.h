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

    ElevatorTable* elevator_1;
    ElevatorTable* elevator_2;

    int height = 600;
    int width = 800;

private:


    QHBoxLayout* layout;
    PanelWindow* panel;
    QWidget* main_widget;

private slots:
    void retrievePassenger_1();
    void retrievePassenger_2();



signals:
    void sendPassenger_1(Passenger* pass);
    void sendPassenger_2(Passenger* pass);

};

#endif // ELEVATORWINDOW_H
