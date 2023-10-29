#include "squarematrix.h"

// ипользуем конструктор произвольной матрицы
SquareMatrix::SquareMatrix(int size): Matrix(size, size)
{

}

//считаем определитель
number SquareMatrix::det() {
    number det = 1;

    int i = 0;
    int j = 0;

    //квадратная матрица => размер = высоте или ширине
    SquareMatrix* tmp = new SquareMatrix(this->getWidth());
    tmp->copy(this);
    tmp->gauss();

    tmp->print();

    while(i < this->getHeight() and j < this->getWidth()) {
        det = det * tmp->retrieve(i, j);
        i += 1;
        j += 1;
    }

    det.simplify();

    delete tmp;
    return det;
}
