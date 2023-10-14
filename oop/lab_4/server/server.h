
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
    void respondToRecieved(QByteArray data);
};

QString numberToQString(number val);

number QStringToNumber(QString val);

#endif // SERVER_H
