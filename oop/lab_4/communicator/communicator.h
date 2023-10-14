
#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QtGlobal>
#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include <QtNetwork/qabstractsocket.h>

struct CommProps {
    QHostAddress selfIp;
    quint16 selfPort;
    QHostAddress recipientIp;
    quint16 recipientPort;
};


class Communicator : public QUdpSocket
{
    Q_OBJECT;

public:
    Communicator(CommProps& comm, QObject* parent = nullptr);

    bool ready;
    CommProps props;

    bool isReady();

signals:
    void recieved(QByteArray);

public slots:
    void send(QByteArray);

private slots:
    void recieve();
};

#endif // COMMUNICATOR_H
