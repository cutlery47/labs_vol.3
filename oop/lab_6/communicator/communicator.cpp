#include "communicator.h"


Communicator::Communicator(CommProps& comm, QObject* parent)
{
    // устанавливаем параметры сокета клиента и сокета сервера
    props = comm;
    // открываем сокеты
    ready = bind(props.selfIp, props.selfPort, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);

    // когда на сокет приходят новые данные - обрабатываем их
    connect(this, SIGNAL(readyRead()), this, SLOT(recieve()));
}

bool Communicator::isReady() {
    return ready;
}

void Communicator::send(QByteArray msg)
{
    // если сокет клиента открыт - можем отправляеть данные
    if (ready)
    {
        // отправка получателю
        writeDatagram(msg, props.recipientIp, props.recipientPort);
        qDebug() << "Sent by: " << props.selfIp.toString() << ":" << props.selfPort << "; data: " << msg;
    }
}

void Communicator::recieve()
{
    // если пришли новые данные - считываем их
    if (hasPendingDatagrams())
    {
        // выделение памяти для получения датаграммы
        quint64 size = pendingDatagramSize();
        QByteArray msg(size,'\0');

        // запись полученных данных
        readDatagram(msg.data(), size);

        qDebug() << "Recieved by: " << props.selfIp.toString() << ":" << props.selfPort << "; data: " << msg;

        //qDebug()<<"recieved"<<msg;
        emit recieved(msg);
    }
}
