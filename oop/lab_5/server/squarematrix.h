
#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "matrix.h"


class SquareMatrix: public Matrix
{


public:
    SquareMatrix(int size);

    //определитель квадратной матрицы
    number det();
};

#endif // SQUAREMATRIX_H
