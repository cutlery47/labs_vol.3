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
            qDebug() << "   " << numberToQString(this->matrix[i][j]);
        }
        qDebug() << "";
    }
}

//данный метод задает атрибут matrix_size
void Matrix::setSize(int size)
{
    wipe();
    matrix_size = size;

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

    if (d != 0 || matrix_size == 1) {
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

    return rnk;
}

void Matrix::applyChanges(int size, QString values) {
    QStringList values_arr;
    number val;

    if (size != matrix_size) {
        setSize(size);
    }

    values_arr = values.split(',');

    for (int ind = 0; ind < values_arr.size(); ++ind) {
        val = QStringToNumber(values_arr[ind]);
        insert(ind / matrix_size, ind % matrix_size, val);
    }
}

QString Matrix::valuesToQString() {
    QString values;

    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
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
