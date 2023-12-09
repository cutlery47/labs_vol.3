#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QFileDialog>
#include <QToolButton>
#include <QMouseEvent>
#include "stategraph.h"


class Canvas : public QWidget {
    Q_OBJECT
    // семпл канваса
    StateGraph sample;

public:
    //конструктор канваса
    Canvas(StateGraph,QWidget *parent = 0);

public slots:
    // поиск документа с графом
    void browse();

protected:
    // нажатие кнопки мыши
    void mousePressEvent(QMouseEvent* event);
    // встроенный метод отрисовки канваса
    void paintEvent(QPaintEvent*);
    // виджет для канваса
    QWidget canvas;


};

#endif
