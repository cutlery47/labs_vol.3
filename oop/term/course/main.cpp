#include "elevatorwindow.h"
#include "panelwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ElevatorWindow w;
    return a.exec();
}
