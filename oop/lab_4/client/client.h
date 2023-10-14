
#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QUdpSocket>
#include <QDebug>

#include <interface.h>
#include <../communicator/communicator.h>
#include <../communicator/request.h>

class Client : public QWidget
{
    Q_OBJECT

private:
    // объект интерфейса
    Interface* interface;

    // объект коммуникатора (UDP-сокет)
    Communicator* comm;

public:
    Client(QWidget *parent = nullptr);
    ~Client();

public slots:
    // слот для получения данных из коммуникатора
    void fromCommunicator(QByteArray data);

    // слот для отправки данных через коммуникатор
    void toCommunicator(QString data);
};

#endif // CLIENT_H
