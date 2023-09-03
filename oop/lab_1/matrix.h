
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <number.h>

class Matrix
{
private:
    int matrix_size = 5;
    number matrix[10][10];
public:
    void printMatrix();
    void setSize();
    int getSize();
    void setMatrixValues();
    void transposeMatrix();
    void swapRows(number** tmp_matrix, int row_1, int row_2, int size);
    void getEditedMatrix(number** matrix, number** new_matrix, int row, int column, int size);
    number calculateDet(number** cur_matrix, int size);
    void copyMatrix(number** tmp_matrix);
    int calculateRank();
    Matrix();
};

#endif // MATRIX_H
