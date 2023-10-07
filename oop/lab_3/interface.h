
#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QDebug>
#include <matrix.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Interface; }
QT_END_NAMESPACE

class Interface : public QWidget

{
    Q_OBJECT

    QLineEdit** cells;
    QPushButton* trans_btn;
    QPushButton* det_btn;
    QPushButton* rank_btn;
    QLabel* result;
    QGridLayout* layout;
    QSpinBox* size_box;

    int height = 300;
    int width = 200;
    int expand = 25;
    int size = 3;

    Matrix* matrix;

    QLineEdit** copy_representation(QLineEdit** repr, int new_size, int old_size);

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();





public slots:
    void change_size();
    void update_layout();

};

#endif // INTERFACE_H
