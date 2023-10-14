
#ifndef SERVER_H
#define SERVER_H

#include <QDebug>
#include <QWidget>

#include <matrix.h>
#include <number.h>
#include <../communicator/communicator.h>
#include <../communicator/request.h>

class Server : public QWidget

{
    Q_OBJECT

    //сама матрица
    Matrix* matrix;

    //коммуникатор
    Communicator* comm;

public:
    Server(QWidget *parent = nullptr);
    ~Server();

public slots:
    // слот, который срабатывает при приходе запроса
    void respondToRecieved(QByteArray data);
};

#endif // SERVER_H
