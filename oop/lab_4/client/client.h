
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
    Interface* interface;
    Communicator* comm;

public:
    Client(QWidget *parent = nullptr);
    ~Client();

public slots:
    void fromCommunicator(QByteArray data);
    void toCommunicator(QString data);
};

#endif // CLIENT_H
