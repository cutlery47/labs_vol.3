
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <number.h>

class Matrix
{
private:
    int matrix_size = 5;
    number matrix[10][10];


    void swapRows(number** tmp_matrix, int row_1, int row_2, int size);
    void getEditedMatrix(number** matrix, number** new_matrix, int row, int column, int size);

public:
    Matrix();

    void print();
    void setSize();
    void setValues();
    void transpose();
    void copy(number** tmp_matrix);

    number det(number** cur_matrix, int size);
    int getSize();
    int rank();
};

#endif // MATRIX_H
