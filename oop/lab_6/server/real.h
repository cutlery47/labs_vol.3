
#ifndef REAL_H
#define REAL_H


class Real {

    double val;

public:
    Real();
    Real(double val);

    // модуль
    Real abs();

    // бинарыные операции
    Real operator+(Real num);
    Real operator-(Real num);
    Real operator*(Real num);
    Real operator/(Real num);

    // опреации сравнения
    bool operator==(Real num);
    bool operator!=(Real num);
    bool operator>(Real num);
    bool operator<(Real num);

    // операция присваивания + смены знака
    Real operator=(Real num);
    Real operator-();

};

#endif // REAL_H
