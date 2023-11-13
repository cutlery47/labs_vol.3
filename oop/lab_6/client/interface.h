
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
#include <QRadioButton>

#include <../communicator/request.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Interface; }
QT_END_NAMESPACE

class Interface : public QWidget

{
    Q_OBJECT

    // размер матрицы
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
    QVBoxLayout* lower_layout;
    // лэйаут для кнопок операций
    QHBoxLayout* operations_panel;
    // лэйаут для кнопок переключения между режиами
    QHBoxLayout* modes_panel;



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

    QRadioButton* check_real;

    QRadioButton* check_rational;

    QRadioButton* check_complex;



    // обновление внутренней матрицы
    void updateMatrix();
    // обновление грида
    void updateGrid();
    // проверка на правильность ввода
    bool inputIsValid();
    // проверка на тип данных
    int getDatatype();



public:
    Interface(QWidget *parent = nullptr);
    ~Interface();

    // применение полученного от сервера ответа (все три метода)
    void applyTranspose(QString values);
    void applyDeterminant(QString value);
    void applyRank(QString value);

signals:
    // сигнал для отправки данных в сокет
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
