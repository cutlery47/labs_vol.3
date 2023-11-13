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
    int height;
    int width;

    //минор матрицы
    Matrix minor(int row, int column);

public:
    Matrix(int height, int width);

    //вывод матрицы
    void print();
    //транспонирование матрицы
    void transpose();
    //заполнение матрицы нулями
    void fill();
    //очистка матрицы
    void wipe();
    //приведение к треугольному виду методом Гаусса
    void gauss();
    //копирование значений матрицы
    void copy(Matrix* mat);

    // обновление значениями, полученными из ответа
    void applyChanges(int size, QString values);
    // получение значений матрицы в виде QString
    QString valuesToQString();

    //вычисление ранга
    int rank();
    //вставка элемента матрицы
    void insert(int i, int j, number val);
    //получение элемента матрицы
    number retrieve(int i, int j);

    //сеттер для размеров матрицы
    void setSize(int height, int width);
    //сеттер для значений матрицы
    void setValues();
    //получение высоту матрицы
    int getHeight();
    //получение ширины матрицы
    int getWidth();
};

// преобразование из number в QString
QString numberToQString(number val);

// преобразование из QString в number
number QStringToNumber(QString val);

#endif // MATRIX_H
