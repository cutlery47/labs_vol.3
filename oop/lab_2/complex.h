#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>

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

    double getReal();
    double getImag();

    void setReal();
    void setImag();

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
};

#endif // COMPLEX_H
