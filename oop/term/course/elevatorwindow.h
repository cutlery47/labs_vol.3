#ifndef ELEVATORWINDOW_H
#define ELEVATORWINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QTextEdit>

#include "elevatortable.h"
#include "panelwindow.h"

class ElevatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    ElevatorWindow(QWidget *parent = nullptr);
    ~ElevatorWindow();

    // GUI для лифтов
    ElevatorTable* table_1;
    ElevatorTable* table_2;

    // лифты
    Elevator* elevator_1;
    Elevator* elevator_2;

    // параметры окна
    int height = 600;
    int width = 800;

private:
    QHBoxLayout* tables;
    QHBoxLayout* status_bar;
    QVBoxLayout* main_layout;

    QVBoxLayout* status_1;
    QLabel* awaiting_status_1;
    QLabel* boarded_status_1;

    QVBoxLayout* status_2;
    QLabel* awaiting_status_2;
    QLabel* boarded_status_2;

    QWidget* main_widget;

    // потоки первого и второго лифтов соответственно
    QThread first_thread;
    QThread second_thread;

    // панель управления
    PanelWindow* panel;

private slots:
    void retrievePassenger_1();
    void retrievePassenger_2();
    void startThread_1();
    void startThread_2();
    void finishThread_1();
    void finishThread_2();
    void updateElevatorStatus_1(int awaiting, int boarded);
    void updateElevatorStatus_2(int awaiting, int boarded);



signals:
    void sendPassenger_1(Passenger* pass);
    void sendPassenger_2(Passenger* pass);

};

#endif // ELEVATORWINDOW_H
