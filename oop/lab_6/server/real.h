#ifndef REAL_H
#define REAL_H

#include <QString>

class Real {

    double val;

public:
    Real();
    Real(const double&);
    Real(const Real&);
    Real(QString str);

    // модуль
    Real abs();

    // бинарыные операции
    Real operator+(Real num);
    Real operator-(Real num);
    Real operator*(Real num);
    Real operator/(Real num);

    double value();

    QString toQString();

    // опреации сравнения
    bool operator==(Real num);
    bool operator!=(Real num);
    bool operator>(Real num);
    bool operator<(Real num);

    // операция присваивания + смены знака
    void operator=(Real num);
    Real operator-();

};

#endif // REAL_H
