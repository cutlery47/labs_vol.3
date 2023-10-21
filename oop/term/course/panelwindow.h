#ifndef PANELWINDOW_H
#define PANELWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>

namespace Ui { class PanelWindow; }

class PanelWindow : public QDialog
{
    Q_OBJECT

public:
    PanelWindow(QWidget *parent = nullptr);
    ~PanelWindow();

    QPushButton* launch_btn_1;
    QPushButton* launch_btn_2;

    QPushButton* add_btn_1;
    QPushButton* add_btn_2;

    QSpinBox* from_box_1;
    QSpinBox* from_box_2;

    QSpinBox* to_box_1;
    QSpinBox* to_box_2;

private:
    int height = 200;
    int width = 600;
    int expand = 100;

    QHBoxLayout* main_layout;
    QVBoxLayout* side_layout_1;
    QVBoxLayout* side_layout_2;
};

#endif // PANELWINDOW_H
