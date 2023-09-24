#include "matrix.h"
#include <vector>


//конструктор класса Matrix
//при инициализации происходит заполнение матрицы
Matrix::Matrix(int size)
{
    this->matrix_size = size;

    matrix = new number* [matrix_size];
    for (int i = 0; i < matrix_size; ++i)
        matrix[i] = new number [matrix_size];

    //заполнение нулями
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            matrix[i][j] = 0;
        }
    }
}

number Matrix::retrieve(int i, int j) {
    return matrix[i][j];
}

void Matrix::insert(int i, int j, number val) {
    matrix[i][j] = val;
}

//удаление массива, выделенного в куче
void Matrix::wipe()
{
    for (int i = 0; i < matrix_size; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

//данный метод выводит матрицу на экран
void Matrix::print()
{
    for (int i = 0; i < matrix_size; ++i)
    {
        for (int j = 0; j < matrix_size; ++j)
        {
            std::cout << "   " << this->matrix[i][j];
        }
        std::cout << std::endl;
    }
}

//данный метод задает атрибут matrix_size
void Matrix::setSize()
{
    std::cout << "Please, set the matrix size... \n";

    do {
        std::cin >> matrix_size;
    } while(matrix_size < 1);
}

//геттер для размера матрицы
int Matrix::size()
{
    return matrix_size;
}

//ввод значений в матрицу
void Matrix::setValues()
{

    std::cout << "Please, enter the matrix values (from left to right)\n";
    for (int i = 0; i < matrix_size; ++i)
    {
        for (int j = 0; j < matrix_size; ++j)
        {
            std::cin >> this->matrix[i][j];
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

//получение матрицы без i столбца и j строки
Matrix Matrix::minor(int row, int column)
{
    Matrix minor(matrix_size - 1);

    int offset_i = 0;
    int offset_j = 0;
    for (int i = 0; i < matrix_size - 1; ++i)
    {
        if (i == row)
            offset_i = 1;
        for (int j = 0; j < matrix_size - 1; ++j)
        {
            if (j == column)
                offset_j = 1;
            minor.insert(i, j, matrix[i + offset_i][j + offset_j]);
        }
        offset_j = 0;
    }

    return minor;
}

//расчет определителя разложением по первому столбцу
number Matrix::det()
{
    //возвращаемое значение
    number d = 0;

    //знак
    number k = 1;

    if (matrix_size == 1)
    {
        d = matrix[0][0];
    }
    else if (matrix_size == 2)
    {
        d = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    else
    {
        for (int col = 0; col < matrix_size; ++col)
        {
            Matrix minor = this->minor(col, 0);
            d = d + k * matrix[col][0] * minor.det();
            k = -k;


            // "чистим минор"
            minor.wipe();

        }
    }

    return d;
}

int Matrix::rank() {
    int rnk = 0;

    //ранг матрицы - размер наибольшего ненулевого минора
    number d = this->det();

    if (d != 0) {
        return matrix_size;
    }

    //создаем массив для следующей итерации
    Matrix minor(matrix_size - 1);

    for (int row = 0; row < matrix_size; ++row) {
        for (int col = 0; col < matrix_size; ++col) {
            minor = this->minor(row, col);
            //находим максимальный ранг
            rnk = std::max(rnk, minor.rank());
        }
    }

    wipe();
    return rnk;
}
