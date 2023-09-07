#include "matrix.h"
#include <vector>

typedef double number;

//конструктор класса Matrix
//при инициализации происходит заполнение матрицы
Matrix::Matrix()
{
    for (int i = 0; i < matrix_size; ++i)
    {
        for (int j = 0; j < matrix_size; ++j)
        {
            matrix[i][j] = 0;
        }
    }
}

//удаление массива, выделенного в куче
void Matrix::clear(number** mat, int size)
{
    for (int i = 0; i < size; ++i) {
        delete[] mat[i];
    }

    delete[] mat;
}

//данный метод выводит матрицу на экран
void Matrix::print()
{
    for (int i = 0; i < matrix_size; ++i)
    {
        for (int j = 0; j < matrix_size; ++j)
        {
            std::cout << "   " << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

//данный метод задает атрибут matrix_size
void Matrix::setSize()
{
    std::cout << "Please, set the matrix size... (max = 10)\n";

    do {
        std::cin >> matrix_size;
    } while(matrix_size > 10 or matrix_size < 1);
}

//геттер для размера матрицы
int Matrix::getSize()
{
    return matrix_size;
}

//ввод значений в матрицу
void Matrix::setValues()
{
    //матрица обновилась - сбросились значения ранга и определителя
    det = 228;
    rank = -1;

    std::cout << "Please, enter the matrix values (from left to right)\n";
    for (int i = 0; i < matrix_size; ++i)
    {
        for (int j = 0; j < matrix_size; ++j)
        {
            std::cin >> matrix[i][j];
        }

    }
}

//транспонирование матрицы
void Matrix::transpose()
{
    number temp = 0;

    for (int i = 0; i < matrix_size; ++i)
    {
        for (int j = i; j < matrix_size; ++j)
        {
            temp = matrix[j][i];
            matrix[j][i] = matrix[i][j];
            matrix[i][j] = temp;
        }
    }
}

//копирование значений одной матрицы в другую
void Matrix::copy(number** mat)
{
    for (int i = 0; i < matrix_size; ++i)
    {
        for (int j = 0; j < matrix_size; ++j)
        {
            mat[i][j] = matrix[i][j];
        }
    }
}

number** Matrix::allocate(int size)
{
    number** mat = new number* [size];
    for (int i = 0; i < size; ++i)
        mat[i] = new number[size];

    return mat;
}

//получение матрицы без i столбца и j строки
number** Matrix::getMinor(number** og_mat, number** mat, int row, int column, int size)
{
    int offset_i = 0;
    int offset_j = 0;
    for (int i = 0; i < size; ++i)
    {
        if (i == row)
            offset_i = 1;
        for (int j = 0; j < size; ++j)
        {
            if (j == column)
                offset_j = 1;
            mat[i][j] = og_mat[i + offset_i][j + offset_j];
        }
        offset_j = 0;
    }

    return mat;
}

number Matrix::getDet() {
    return det;
}

int Matrix::getRank() {
    return rank;
}

void Matrix::setDet(number**mat, int size) {
    det = calcDet(mat, size);
}

void Matrix::setRank(number**mat, int size) {
    rank = calcRank(mat, size);
}

//расчет определителя разложением по первому столбцу
number Matrix::calcDet(number** mat, int size)
{
    //возвращаемое значение
    number d = 0;

    //знак
    int k = 1;

    //создаем массив для следующей итерации
    number** minor = allocate(size - 1);

    if (size == 1)
    {
        d = mat[0][0];
    }
    else if (size == 2)
    {
        d = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }
    else
    {
        for (int col = 0; col < size; ++col)
        {
            minor = getMinor(mat, minor, col, 0, size - 1);
            d += k * mat[col][0] * calcDet(minor, size - 1);
            k = -k;

        }
    }

    //очищаем память после минора
    clear(minor, size - 1);

    return d;
}

int Matrix::calcRank(number** mat, int size) {
    int rnk = 0;

    //ранг матрицы - размер наибольшего ненулевого минора
    number d = calcDet(mat, size);
    if (d != 0) {
        return size;
    }

    //создаем массив для следующей итерации
    number** minor = allocate(size - 1);

    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            minor = getMinor(mat, minor, row, col, size - 1);
            //находим максимальный ранг
            rnk = std::max(rnk, calcRank(minor, size - 1));
        }
    }

    clear(minor, size - 1);
    return rnk;
}
