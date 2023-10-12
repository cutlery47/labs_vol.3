#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>

class Rational
{
private:
    // числитель
    int numerator;

    // знаменатель
    int denominator;
public:
    Rational();
    Rational(const int&);

    // геттеры-сеттеры
    int getNumerator();
    int getDenominator();
    void setNumerator(int val);
    void setDenominator(int val);

    // получение НОД
    int getGCD(Rational val);

    //упрощение числа
    void simplify();

    //перегружаем операторы c++
    //операторы ввода-вывода
    friend std::ostream& operator << (std::ostream&,Rational);
    friend std::istream& operator >> (std::istream&, Rational&);

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
};

#endif // RATIONAL_H
