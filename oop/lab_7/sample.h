#ifndef SAMPLE_H
#define SAMPLE_H

#include <QPainter>
#include "graph.h"

class Sample {
    // граф
    Graph graph;

public:
    // конструктор для семпла
    Sample(Graph);
    Sample();

    // отрисовка семпла
    void paint(QPainter*,QRect);
    // отрисовка линий
    void paintLines(QPointF*, QPainter*, int i, int j, qreal);
    // проверка на наличие ребра между двумя нодами
    bool isConnected(int i, int j);

};

#endif
