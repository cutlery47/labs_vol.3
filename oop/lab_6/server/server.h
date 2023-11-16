#ifndef SERVER_H
#define SERVER_H

#include <QDebug>
#include <QWidget>

#include <squarematrix.h>
#include <rational.h>
#include <real.h>
#include <complex.h>



class Server : public QWidget

{
    Q_OBJECT

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
