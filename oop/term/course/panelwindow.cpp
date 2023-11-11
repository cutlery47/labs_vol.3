#include "panelwindow.h"

PanelWindow::PanelWindow(QWidget *parent) :QDialog(parent)
{

    QLabel* from_label_1 = new QLabel("From floor:");
    QLabel* from_label_2 = new QLabel("From floor:");

    QLabel* to_label_1 = new QLabel("To floor:");
    QLabel* to_label_2 = new QLabel("To floor:");

    setWindowTitle("Panel");

    this->resize(width, height);

    this->launch_btn_1 = new QPushButton;
    this->launch_btn_2 = new QPushButton;
    this->launch_btn_1->setText("Launch elevator 1");
    this->launch_btn_2->setText("Launch elevator 2");

    this->add_btn_1 = new QPushButton;
    this->add_btn_2 = new QPushButton;
    this->add_btn_1->setText("Add elevator 1 passenger");
    this->add_btn_2->setText("Add elevator 2 passenger");

    this->from_box_1 = new QSpinBox;
    this->from_box_2 = new QSpinBox;
    this->from_box_1->setMaximum(9);
    this->from_box_1->setMinimum(1);
    this->from_box_2->setMaximum(9);
    this->from_box_2->setMinimum(1);

    this->to_box_1 = new QSpinBox;
    this->to_box_2 = new QSpinBox;
    this->to_box_1->setMaximum(9);
    this->to_box_1->setMinimum(1);
    this->to_box_2->setMaximum(9);
    this->to_box_2->setMinimum(1);

    this->side_layout_1 = new QVBoxLayout;
    this->side_layout_2 = new QVBoxLayout;
    this->side_layout_1->addWidget(add_btn_1);
    this->side_layout_2->addWidget(add_btn_2);

    this->side_layout_1->addWidget(from_label_1);
    this->side_layout_2->addWidget(from_label_2);

    this->side_layout_1->addWidget(from_box_1);
    this->side_layout_2->addWidget(from_box_2);

    this->side_layout_1->addWidget(to_label_1);
    this->side_layout_2->addWidget(to_label_2);

    this->side_layout_1->addWidget(to_box_1);
    this->side_layout_2->addWidget(to_box_2);

    this->side_layout_1->addWidget(launch_btn_1);
    this->side_layout_2->addWidget(launch_btn_2);

    this->main_layout = new QHBoxLayout;
    this->main_layout->addLayout(side_layout_1);
    this->main_layout->addLayout(side_layout_2);

    this->setLayout(this->main_layout);
}

PanelWindow::~PanelWindow()
{
    delete this->launch_btn_1;
    delete this->launch_btn_2;
    delete this->add_btn_1;
    delete this->add_btn_2;
    delete this->main_layout;
    delete this->side_layout_1;
    delete this->side_layout_2;
    delete this->from_box_1;
    delete this->from_box_2;
    delete this->to_box_1;
    delete this->to_box_2;

}
