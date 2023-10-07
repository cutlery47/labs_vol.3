
#include "interface.h"

#include <QApplication>
#include <QLocale>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Interface w;
    w.show();
    return a.exec();
}
