
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <number.h>

class Matrix
{
private:
    number matrix[10][10];

    //стандартные атрибуты объектов
    int matrix_size = 5;
    int rank = -1;
    number det = 228;

    //приватные утилиты матрицы
    number** getMinor(number** matrix, number** mat, int row, int column, int size);

public:
    Matrix();

    //утилиты матрицы
    void print();
    void transpose();
    void copy(number** mat);
    void clear(number** mat, int size);
    number** allocate(int size);

    //расчеты
    int calcRank(number** mat, int size);
    number calcDet(number** mat, int size);

    //сеттеры
    void setSize();
    void setValues();
    void setRank(number**mat, int size);
    void setDet(number**mat, int size);

    //геттеры
    int getSize();
    int getRank();
    number getDet();
};

#endif // MATRIX_H
