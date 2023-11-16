#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>
#include <QString>

class Complex
{
private:
    //вещественная часть числа
    double real;
    //мнимая часть числа
    double imag;
public:
    Complex();
    Complex(const double&);
    Complex(QString str);

    double getReal();
    double getImag();

    int abs();

    void setReal();
    void setImag();

    QString toQString();

    //перегружаем операторы c++
    //операторы ввода-вывода
    friend std::ostream& operator << (std::ostream&, Complex);
    friend std::istream& operator >> (std::istream&, Complex&);

    //унарные операции
    Complex operator - ();

    //бинарные операции
    Complex operator * (Complex);
    Complex operator + (Complex);
    Complex operator - (Complex);
    Complex operator / (Complex);

    //операции сравнения
    bool operator == (Complex);
    bool operator != (Complex);

    void operator = (QString);
    void operator = (int);
};

#endif // COMPLEX_H
