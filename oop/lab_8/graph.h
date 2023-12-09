#ifndef GRAPH_H
#define GRAPH_H
#include "matrix.h"
#include <QFile>
#include <QTextStream>


class Graph
{
private:
    // матрица смежности
    Matrix<int>* adj;

    // размерность матрицы смежности
    int graph_size = 4;

public:
    // конструктор
    Graph();
    // обработка нового графа
    void set(QString);
    // геттер для размерности матрицы
    int size();
    // получение элемента из матрицы смежности
    int retrieve(int, int);
};

#endif
