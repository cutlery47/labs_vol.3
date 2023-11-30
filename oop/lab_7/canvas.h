#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QFileDialog>
#include <QToolButton>
#include "sample.h"


class Canvas : public QWidget {
    Q_OBJECT
    // семпл канваса
    Sample sample;

public:
    //конструктор канваса
    Canvas(Sample,QWidget *parent = 0);

public slots:
    // поиск документа с графом
    void browse();

protected:
    // встроенный метод отрисовки канваса
    void paintEvent(QPaintEvent*);
    // виджет для канваса
    QWidget canvas;


};

#endif
