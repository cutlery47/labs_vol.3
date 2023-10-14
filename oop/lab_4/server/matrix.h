#ifndef MATRIX_H
#define MATRIX_H
#include <number.h>
#include <QString>
#include <QStringList>
#include <QDebug>

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

    //вывод матрицы
    void print();
    //транспонирование матрицы
    void transpose();
    //заполнение матрицы нулями
    void fill();
    //очистка матрицы
    void wipe();

    void applyChanges(int size, QString values);

    QString valuesToQString();

    //вычисление ранга
    int rank();
    //вычисление определителя
    number det();

    //вставка элемента матрицы
    void insert(int i, int j, number val);
    //получение элемента матрицы
    number retrieve(int i, int j);

    //сеттер для размера матрицы
    void setSize(int size);
    //сеттер для значений матрицы
    void setValues();

    //получение размера матрицы
    int size();
};

QString numberToQString(number val);

number QStringToNumber(QString val);

#endif // MATRIX_H
