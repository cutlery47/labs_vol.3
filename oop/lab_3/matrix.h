#ifndef MATRIX_H
#define MATRIX_H
#include <number.h>

//TODO:
// 1) динамический размер матрицы
// 2) убрать опр и ранг из атрибутов
// 3)

class Matrix
{
private:
    //сама матрица
    number** matrix;

    //размерность матрицы
    int matrix_size;

    //минор матрицы
    Matrix minor(int row, int column);

public:
    Matrix(int size);

    //утилиты матрицы
    void print();
    void transpose();
    void fill();
    void wipe();


    //расчеты
    int rank();
    number det();

    //добавление и удаление элементов
    void insert(int i, int j, number val);
    number retrieve(int i, int j);

    //сеттеры
    void setSize(int size);
    void setValues();

    //геттеры
    int size();
};

#endif // MATRIX_H
