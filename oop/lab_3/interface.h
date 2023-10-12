
#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QDebug>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QValidator>

#include <matrix.h>
#include <number.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Interface; }
QT_END_NAMESPACE

class Interface : public QWidget

{
    Q_OBJECT

    // поля ввода значений
    QLineEdit** cells;

    // лэйауты
    QVBoxLayout* main_layout;
    QHBoxLayout* upper_layout;
    QGridLayout* grid_layout;
    QHBoxLayout* lower_layout;

    // виджеты
    QPushButton* trans_btn;
    QPushButton* det_btn;
    QPushButton* rank_btn;
    QLabel* result;
    QSpinBox* size_box;

    // объект матрицы
    Matrix* matrix;

    // функции-помощники
    void updateMatrix();
    void updateGrid();
    QString numberToQString(number val);
    number QStringToNumber(QString val);
    bool inputIsValid();

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();


public slots:
    void changeSize();
    void calcDet();
    void calcRank();
    void transpose();
};

#endif // INTERFACE_H
