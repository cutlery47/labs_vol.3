#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
#include <QString>

class Rational
{
private:
    // числитель
    int numerator;
    // знаменатель
    int denominator;
public:
    //конструкторы класса
    Rational();
    Rational(const int&);
    Rational(QString str);

    // геттер для числителя
    int getNumerator();
    // геттер для знаменателя
    int getDenominator();
    // сеттер для числителя
    void setNumerator(int val);
    // сеттер для знаменателя
    void setDenominator(int val);

    // преобразует число в строку
    QString toQString();

    // получение НОД
    int getGCD(Rational val);

    //упрощение числа
    Rational simplify();

    //перегружаем операторы c++
    //операторы ввода-вывода
    friend std::ostream& operator << (std::ostream&,Rational);
    friend std::istream& operator >> (std::istream&, Rational&);

    //модуль числа
    Rational abs();

    //унарные операции
    Rational operator - ();

    //бинарные операции
    Rational operator * (Rational);
    Rational operator + (Rational);
    Rational operator - (Rational);
    Rational operator / (Rational);

    //операции сравнения
    bool operator == (Rational);
    bool operator != (Rational);
    bool operator > (Rational);
    bool operator < (Rational);
};

#endif // RATIONAL_H
