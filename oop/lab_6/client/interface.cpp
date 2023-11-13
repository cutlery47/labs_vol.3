
#include "interface.h"


Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
    //значение по умолчанию
    matrix_size = 3;

    main_layout = new QVBoxLayout;
    upper_layout = new QHBoxLayout;
    grid_layout = new QGridLayout;
    lower_layout = new QVBoxLayout;
    operations_panel = new QHBoxLayout;
    modes_panel = new QHBoxLayout;


    result = new QLabel("Result: ");
    size_box = new QSpinBox(this);
    size_box->setValue(matrix_size);
    size_box->setMaximum(10);
    size_box->setMinimum(1);

    upper_layout->addWidget(size_box);
    upper_layout->addWidget(result);

    updateGrid();

    // приколы
    trans_btn = new QPushButton("Transpose", this);
    det_btn = new QPushButton("Determinant", this);
    rank_btn = new QPushButton("Rank", this);

    check_complex = new QRadioButton("Complex", this);
    check_real = new QRadioButton("Real", this);
    check_rational = new QRadioButton("Rational", this);
    check_rational->setChecked(true);

    operations_panel->addWidget(trans_btn);
    operations_panel->addWidget(det_btn);
    operations_panel->addWidget(rank_btn);

    modes_panel->addWidget(check_complex);
    modes_panel->addWidget(check_real);
    modes_panel->addWidget(check_rational);

    lower_layout->addLayout(operations_panel);
    lower_layout->addLayout(modes_panel);

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
    for (int i = 0; i < matrix_size; ++i) {
        delete cells[i];
    }

    delete []cells;
    delete trans_btn;
    delete det_btn;
    delete result;
    delete size_box;
    delete rank_btn;
}

void Interface::updateGrid() {

    // регулярное выражение для валидации ввода
//    QRegularExpression exp("-?[0-9]*\\/[1-9]+[0-9]*");
//    QRegularExpressionValidator* valid = new QRegularExpressionValidator(exp);

    cells = new QLineEdit*[matrix_size];
    for (int i = 0; i < matrix_size; ++i) {
        cells[i] = new QLineEdit[matrix_size];
    }

    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            cells[i][j].setPlaceholderText("0");
            //cells[i][j].setValidator(valid);
            grid_layout->addWidget(&cells[i][j], i , j);
        }
    }

}

int Interface::getDatatype() {
    if (check_complex->isChecked()) {
        return COMPLEX_NUM;
    } else if (check_rational->isChecked()) {
        return RATIONAL_NUM;
    } else {
        return REAL_NUM;
    }
}

void Interface::changeSize() {
    for (int i = 0; i < matrix_size; ++i) {
        delete[] cells[i];
    }
    delete cells;

    matrix_size = size_box->value();
    updateGrid();

    setLayout(main_layout);
}

void Interface::calcDet() {
//    if (!inputIsValid()) {
//        return;
//    }

    struct request input;

    input.header = DETERMINANT_REQUEST;
    input.type = getDatatype();
    input.matrix_size = matrix_size;
    input.matrix_values = fromCellsToQString(cells, matrix_size);

    QString request_data = buildRequest(input);
    emit request(request_data);
}

void Interface::calcRank() {
//    if (!inputIsValid()) {
//        return;
//    }

    struct request input;

    input.header = RANK_REQUEST;
    input.type = getDatatype();
    input.matrix_size = matrix_size;
    input.matrix_values = fromCellsToQString(cells, matrix_size);

    QString request_data = buildRequest(input);
    emit request(request_data);
}

void Interface::transpose() {
//    if (!inputIsValid()) {
//        return;
//    }

    struct request input;

    input.header = TRANSPOSE_REQUEST;
    input.type = getDatatype();
    input.matrix_size = matrix_size;
    input.matrix_values = fromCellsToQString(cells, matrix_size);

    QString request_data = buildRequest(input);
    emit request(request_data);;
}

void Interface::applyTranspose(QString values) {
    QStringList matrix_values;
    matrix_values = values.split(',');

    for (int i = 0; i < matrix_values.size(); ++i) {
        cells[i / matrix_size][i % matrix_size].setText(matrix_values[i]);
    }
}

void Interface::applyDeterminant(QString value) {
    result->setText("Result: " + value);
}

void Interface::applyRank(QString value) {
    result->setText("Result: " + value);
}

bool Interface::inputIsValid() {
    // проверка на совпадение заданной маски ввода
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            if (!cells[i][j].hasAcceptableInput()) {
                return false;
            }
        }
    }
    return true;
}




