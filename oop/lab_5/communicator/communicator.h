
#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QtGlobal>
#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include <QtNetwork/qabstractsocket.h>

struct CommProps {
    // адрес и порт владельца сокета
    QHostAddress selfIp;
    quint16 selfPort;
    // адрес и порт приемник
    QHostAddress recipientIp;
    quint16 recipientPort;
};


class Communicator : public QUdpSocket
{
    Q_OBJECT;

public:
    Communicator(CommProps& comm, QObject* parent = nullptr);

    // переменная для проеверки создания сокета
    bool ready;

    // параметры сокета
    CommProps props;

    // проверка значения ready
    bool isReady();

signals:
    // сигнал, испускаемый при получении новых данных
    void recieved(QByteArray);

public slots:
    // слот, записывающий данные в принимающий сокет
    void send(QByteArray);

private slots:
    // слот, обрабатывающий новые данные
    void recieve();
};

#endif // COMMUNICATOR_H
