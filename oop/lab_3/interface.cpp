
#include "interface.h"


Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
    // creating an instance of matrix
    matrix = new Matrix(size);

    // creating a layout for matrix + resizing
    layout = new QGridLayout;
    resize(height + (expand * size * 2), height + (expand * size));


    // allocating for matrix representaion
    cells = new QLineEdit*[size];
    for (int i = 0; i < size; ++i) {
        cells[i] = new QLineEdit[size * 2];
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < 2 * size; ++j) {
            layout->addWidget(&cells[i][j], i , j);
        }
    }

    this->setLayout(layout);

    //buttons and stuff
    trans_btn = new QPushButton(this);
    trans_btn->setGeometry(10, height + (expand * size) - 40, 100, 25);
    trans_btn->setText("Transpose");

    det_btn = new QPushButton(this);
    det_btn->setGeometry(110, height + (expand * size) - 40, 100, 25);
    det_btn->setText("Determinant");

    rank_btn = new QPushButton(this);
    rank_btn->setGeometry(210, height + (expand * size) - 40, 100, 25);
    rank_btn->setText("Rank");

    size_box = new QSpinBox(this);
    size_box->setGeometry(10, 10, 50, 25);
    size_box->setValue(size);
    size_box->setMaximum(10);
    size_box->setMinimum(1);

    result = new QLabel("1223", this);
    result->setGeometry(75, 10, 25, 25);

    //signals
    connect(size_box, SIGNAL(valueChanged(int)), this, SLOT(change_size()));
}

Interface::~Interface()
{
    for (int i = 0; i < size; ++i) {
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

void Interface::change_size() { 

    // deleting current representation to create a new one
    for (int i = 0; i < size; ++i) {
        delete[] cells[i];
    }
    delete cells;

    // updating size
    size = size_box->value();
    matrix->setSize(size);
    resize(height + (expand * size * 2), height + (expand * size));

    // updating representation
    update_layout();
}



void Interface::update_layout() {

    // allocating for updated representation
    cells = new QLineEdit*[size];

    for (int i = 0; i < size; ++i) {
        cells[i] = new QLineEdit[size * 2];
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < 2 * size; ++j) {
            layout->addWidget(&cells[i][j], i , j);
        }
    }

    this->setLayout(layout);

    trans_btn->setGeometry(10, height + (expand * size) - 40, 100, 25);
    det_btn->setGeometry(110, height + (expand * size) - 40, 100, 25);
    rank_btn->setGeometry(210, height + (expand * size) - 40, 100, 25);
    result->setGeometry(75, 10, 25, 25);
}




