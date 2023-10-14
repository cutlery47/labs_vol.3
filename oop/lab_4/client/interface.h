
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
#include <QStringList>

#include <../communicator/request.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Interface; }
QT_END_NAMESPACE

class Interface : public QWidget

{
    Q_OBJECT

    int matrix_size;

    // поля ввода значений
    QLineEdit** cells;

    // главный лэйаут
    QVBoxLayout* main_layout;
    // верхний лэйаут
    QHBoxLayout* upper_layout;
    // матричный лэйаут
    QGridLayout* grid_layout;
    // нижний лэйаут
    QHBoxLayout* lower_layout;

    // кнопка транспонирования
    QPushButton* trans_btn;
    // кнопка определителя
    QPushButton* det_btn;
    // кнопка ранга
    QPushButton* rank_btn;
    // текст с результатом операции
    QLabel* result;
    // переключатель размерности матрицы
    QSpinBox* size_box;

    // обновление внутренней матрицы
    void updateMatrix();
    // обновление грида
    void updateGrid();
    // конвертатор number -> QStirng
//    QString numberToQString(number val);
//    // конвертатор QString -> number
//    number QStringToNumber(QString val);
    // проверка на правильность ввода
    bool inputIsValid();



public:
    Interface(QWidget *parent = nullptr);
    ~Interface();

    void applyTranspose(QString values);

    void applyDeterminant(QString value);

    void applyRank(QString value);

signals:
    void request(QString);


public slots:
    // изменение размерности матрицы
    void changeSize();
    // расчет определителя
    void calcDet();
    // расчет ранга
    void calcRank();
    // транспонироавние
    void transpose();
};

#endif // INTERFACE_H
