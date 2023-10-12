
#include "interface.h"


Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
    // создание объекта матрицы, 3 - размер по умолчанию
    matrix = new Matrix(3);

    main_layout = new QVBoxLayout;
    upper_layout = new QHBoxLayout;
    grid_layout = new QGridLayout;
    lower_layout = new QHBoxLayout;

    result = new QLabel("Result: ");
    size_box = new QSpinBox(this);
    size_box->setValue(matrix->size());
    size_box->setMaximum(10);
    size_box->setMinimum(1);

    upper_layout->addWidget(size_box);
    upper_layout->addWidget(result);

    updateGrid();

    // приколы
    trans_btn = new QPushButton("Transpose", this);
    det_btn = new QPushButton("Determinant", this);
    rank_btn = new QPushButton("Rank", this);

    lower_layout->addWidget(trans_btn);
    lower_layout->addWidget(det_btn);
    lower_layout->addWidget(rank_btn);

    main_layout->addLayout(upper_layout);
    main_layout->addLayout(grid_layout);
    main_layout->addLayout(lower_layout);

    this->setLayout(main_layout);

    connect(size_box, SIGNAL(valueChanged(int)), this, SLOT(changeSize()));
    connect(det_btn, SIGNAL(clicked()), this, SLOT(calcDet()));
    connect(rank_btn, SIGNAL(clicked()), this, SLOT(calcRank()));
    connect(trans_btn, SIGNAL(clicked()), this, SLOT(transpose()));
}

Interface::~Interface() {
    for (int i = 0; i < matrix->size(); ++i) {
        delete cells[i];
    }

    delete []cells;
    delete trans_btn;
    delete det_btn;
    delete result;
    delete size_box;
    delete rank_btn;
    delete matrix;
}

void Interface::updateGrid() {

    // регулярное выражение для валидации ввода
    QRegularExpression exp("-?[0-9]*\\/[1-9]+[0-9]*");
    QRegularExpressionValidator* valid = new QRegularExpressionValidator(exp);

    cells = new QLineEdit*[matrix->size()];
    for (int i = 0; i < matrix->size(); ++i) {
        cells[i] = new QLineEdit[matrix->size()];
    }

    for (int i = 0; i < matrix->size(); ++i) {
        for (int j = 0; j < matrix->size(); ++j) {
            cells[i][j].setPlaceholderText("0");
            cells[i][j].setValidator(valid);
            grid_layout->addWidget(&cells[i][j], i , j);
        }
    }

}

void Interface::changeSize() {
    for (int i = 0; i < matrix->size(); ++i) {
        delete[] cells[i];
    }
    delete cells;

    matrix->setSize(size_box->value());
    updateGrid();

    setLayout(main_layout);
}

QString Interface::numberToQString(number val) {
    QString res = QString::number(val.getNumerator()) + "/" + QString::number(val.getDenominator());
    return res;
}

number Interface::QStringToNumber(QString val) {
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

    //если знаменателя не было при вводе - добавляем единицу
    if (str_den.size() == 0) {
        str_den.append('1');
    }

    tmp.setDenominator(str_den.toInt());
    tmp.setNumerator(str_num.toInt());
    return tmp;
}

void Interface::calcDet() {
    if (!inputIsValid()) {
        return;
    }
    updateMatrix();

    number det = this->matrix->det();
    det.simplify();

    QString res = numberToQString(det);
    this->result->setText("Result: Determinant = " + res);
}

void Interface::calcRank() {
    if (!inputIsValid()) {
        return;
    }
    updateMatrix();

    int rank = this->matrix->rank();
    this->result->setText("Result: Rank = " + QString::number(rank));
}

void Interface::transpose() {
    if (!inputIsValid()) {
        return;
    }

    updateMatrix();
    matrix->transpose();

    for (int i = 0; i < matrix->size(); ++i) {
        for (int j = i; j < matrix->size(); ++j) {
            cells[i][j].setText(numberToQString(matrix->retrieve(i, j)));
            cells[j][i].setText(numberToQString(matrix->retrieve(j, i)));
        }
    }

    this->setLayout(main_layout);
}

bool Interface::inputIsValid() {
    // проверка на совпадение заданной маски ввода
    for (int i = 0; i < matrix->size(); ++i) {
        for (int j = 0; j < matrix->size(); ++j) {
            if (!cells[i][j].hasAcceptableInput()) {
                return false;
            }
        }
    }
    return true;
}

void Interface::updateMatrix() {
    // обновление внутренней матрицы новыми значениями
    for (int i = 0; i < matrix->size(); ++i) {
        for (int j = 0; j < matrix->size(); ++j) {
            matrix->insert(i, j, QStringToNumber(cells[i][j].text()));
        }
    }
}




