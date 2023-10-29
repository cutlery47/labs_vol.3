#include "matrix.h"
#include <vector>


//конструктор класса Matrix
//при инициализации происходит заполнение матрицы
Matrix::Matrix(int height, int width)
{
    this->height = height;
    this->width = width;

    matrix = new number* [width];
    for (int i = 0; i < width; ++i)
        matrix[i] = new number [height];

    //заполнение нулями
    for (int i = 0; i < this->width; ++i) {
        for (int j = 0; j < this->height; ++j) {
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
    for (int i = 0; i < this->height; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

//данный метод выводит матрицу на экран
void Matrix::print()
{
    for (int i = 0; i < this->height; ++i)
    {
        for (int j = 0; j < this->width; ++j)
        {
            qInfo() << "   " << numberToQString(this->matrix[i][j]);
        }
        qDebug() << "";
    }
}

//данный метод задает атрибут matrix_size
void Matrix::setSize(int height, int width)
{
    wipe();
    this->height = height;
    this->width = width;

    matrix = new number* [width];
    for (int i = 0; i < width; ++i)
        matrix[i] = new number [height];

    //заполнение нулями
    for (int i = 0; i < this->width; ++i) {
        for (int j = 0; j < this->height; ++j) {
            matrix[i][j] = 0;
        }
    }
}

//геттер для высоты матрицы
int Matrix::getHeight()
{
    return this->height;
}

//геттер для ширины матрицы
int Matrix::getWidth()
{
    return this->width;
}

//ввод значений в матрицу
void Matrix::setValues()
{

    std::cout << "Please, enter the matrix values (from left to right)\n";
    for (int i = 0; i < this->width; ++i)
    {
        for (int j = 0; j < this->height; ++j)
        {
            std::cin >> this->matrix[i][j];
        }

    }
}

//копирование значений матрицы
void Matrix::copy(Matrix* mat) {
    if (!(this->width == mat->width && this->height == mat->height)) {
        qInfo() << "Matrix can't be copied";
        return;
    }

    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            this->matrix[i][j] = mat->matrix[i][j];
        }
    }
}


//транспонирование матрицы
void Matrix::transpose()
{
    Matrix *tmp = new Matrix(this->width, this->height);
    tmp->copy(this);

    for (int i = 0; i < this->height; ++i)
    {
        for (int j = 0; j < this->width; ++j)
        {
            this->matrix[i][j] = tmp->matrix[j][i];
        }
    }

    delete tmp;
}

//приведение матрицы к диагональному виду
void Matrix::gauss() {
    int i = 0;
    int j = 0;
    int k = 0;

    for (i = 0; i < this->height; ++i) {
        int row_max = i;

        for (j = i + 1; j < this->height; ++j) {
            if (matrix[j][i].abs() > matrix[row_max][i].abs()) {
                row_max = j;
            }
        }

        for (k = 0; k < this->width; ++k) {
            number tmp = this->matrix[i][k];
            this->matrix[i][k] = this->matrix[row_max][k];
            this->matrix[row_max][k] = tmp;
        }

        for (j = i + 1; j < this->height; ++j) {
            number q = - matrix[j][i] / matrix[i][i];
            for (k = this->width - 1; k >= i; -- k)
                this->matrix[j][k] = this->matrix[j][k] + q * this->matrix[i][k];
        }
    }
}

//подсчет ранга матрицы (считаем кол-ва ненулевых строк в ступенчатом виде)
int Matrix::rank() {
    int rnk = 0;

    Matrix *tmp = new Matrix{this->height, this->width};
    tmp->copy(this);
    tmp->gauss();

    for (int i = 0; i < tmp->height; ++i) {
        number row_sum = 0;

        for (int j = 0; j < tmp->width; ++j) {
            row_sum = row_sum + tmp->matrix[i][j];
        }

        if (row_sum != 0) {
            rnk += 1;
        }
    }

    tmp->wipe();

    return rnk;
}

void Matrix::applyChanges(int size, QString values) {
    QStringList values_arr;
    number val;

    if (size * size != this->width * this->height) {
        setSize(size, size);
    }

    values_arr = values.split(',');

    for (int ind = 0; ind < values_arr.size(); ++ind) {
        val = QStringToNumber(values_arr[ind]);
        insert(ind / this->width, ind % this->width, val);
    }
}

QString Matrix::valuesToQString() {
    QString values;

    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            values.append(numberToQString(retrieve(i, j)));
            values.append(',');
        }
    }

    values.chop(1);
    return values;
}

QString numberToQString(number val) {
    QString res = QString::number(val.getNumerator()) + "/" + QString::number(val.getDenominator());
    return res;
}

number QStringToNumber(QString val) {
    number tmp;
    QString str_num;
    QString str_den;
    int flag = 0;

    for (int i = 0; i < val.size(); ++i) {
        if (val[i] == '/') {
            flag = 1;
        } else {
            if (flag == 0) {
                str_num.append(val[i]);
            } else {
                str_den.append(val[i]);
            }
        }
    }

    // если знаменателя не было при вводе - добавляем единицу
    if (str_den.size() == 0) {
        str_den.append('1');
    }

    tmp.setDenominator(str_den.toInt());
    tmp.setNumerator(str_num.toInt());
    return tmp;
}
