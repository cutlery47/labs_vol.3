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

//данный метод выводит матрицу на экран
void Matrix::printMatrix()
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

    do
    {
        std::cin >> matrix_size;
    } while(matrix_size > 10 or matrix_size < 1);
}

//геттер для размера матрицы
int Matrix::getSize()
{
    return matrix_size;
}

//ввод значений в матрицу
void Matrix::setMatrixValues() {
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
void Matrix::transposeMatrix()
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
void Matrix::copyMatrix(number** tmp_matrix)
{
    for (int i = 0; i < matrix_size; ++i)
    {
        for (int j = 0; j < matrix_size; ++j)
        {
            tmp_matrix[i][j] = matrix[i][j];
        }
    }
}

//получение матрицы без i столбца и j строки
void Matrix::getEditedMatrix(number** matrix, number** new_matrix, int row, int column, int size)
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
            new_matrix[i][j] = matrix[i + offset_i][j + offset_j];
        }
    }
}

//расчет определителя разложением по первому столбцу
number Matrix::calculateDet(number** cur_matrix, int size)
{
    //возвращаемое значение
    number det = 0;
    int k = 1;

    //создаем массив для следующей итерации
    number** edited_matrix = new number* [size - 1];
    for (int i = 0; i < size - 1; ++i)
        edited_matrix[i] = new number[size - 1];

    if (size == 1)
    {
        det = cur_matrix[0][0];
        return det;
    }
    else if (size == 2)
    {
        det = cur_matrix[0][0] * cur_matrix[1][1] - cur_matrix[0][1] * cur_matrix[1][0];
        return det;
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            getEditedMatrix(cur_matrix, edited_matrix, i, 0, size - 1);
            det += k * cur_matrix[i][0] * calculateDet(edited_matrix, size - 1);
            k = -k;
        }
    }

    return det;
}

number** vectorToArray(std::vector<std::vector<number>> vect) {
    int size = vect.size();

    number** mat = new number* [size];
    for (int i = 0; i < size; ++i) {
        mat[i] = new number[size];
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            mat[i][j] = vect[i][j];
        }
    }

    return mat;
}

int Matrix::calculateRank() {
    int rank = 1;
    int q = 1;

    while (q < matrix_size) {
        std::vector<number> standart(1,1);
        std::vector<std::vector<number>> smth;

        standart.resize(q);
        for (int w = 0; w < q; ++w) {
            smth.push_back(standart);
        }

        for(int a = 0; a < (matrix_size - (q - 1)); a++){
            for(int b = 0; b < (matrix_size - (q - 1)); b++){
                for(int c = 0; c < q; c++){
                    for(int d = 0; d < q; d++){
                        smth[c][d] = matrix[a+c][b+d];
                    }
                }

                int arr_sz = smth.size();
                number** smth_arr = vectorToArray(smth);

                if (calculateDet(smth_arr, arr_sz) != 0) {
                    rank = q;
                }

            }
        }

        ++q;
    }

    return rank;

}


