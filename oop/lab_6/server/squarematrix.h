
#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "matrix.h"


template <class number>
class SquareMatrix: public Matrix<number>
{


public:
    SquareMatrix(int size);

    //определитель квадратной матрицы
    number det();
};

template <class number>
SquareMatrix<number>::SquareMatrix(int size): Matrix<number>(size, size)
{

}

//считаем определитель
template <class number>
number SquareMatrix<number>::det() {
    number det = 1;

    int i = 0;
    int j = 0;

    //квадратная матрица => размер = высоте или ширине
    SquareMatrix* tmp = new SquareMatrix(this->getWidth());
    tmp->copy(this);
    tmp->gauss();

    while(i < this->getHeight() and j < this->getWidth()) {
        det = det * tmp->retrieve(i, j);
        i += 1;
        j += 1;
    }

    delete tmp;
    return det;
}

#endif // SQUAREMATRIX_H
