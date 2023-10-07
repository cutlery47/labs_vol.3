#ifndef ELEVATORWINDOW_H
#define ELEVATORWINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include <QDialog>
#include <QDebug>

#include "elevatortable.h"
#include "panelwindow.h"

namespace Ui { class ElevatorWindow; }

class ElevatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    ElevatorWindow(QWidget *parent = nullptr);
    ~ElevatorWindow();

    ElevatorTable* elevator_1;
    ElevatorTable* elevator_2;

private:
    int height = 600;
    int width = 800;

    QHBoxLayout layout;
    PanelWindow* panel;

};

#endif // ELEVATORWINDOW_H
