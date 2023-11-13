
#include "client.h"


Client::Client(QWidget *parent)
    : QWidget(parent)
{
    // задаем параметры сокетов
    CommProps props = {QHostAddress("127.0.0.1"), 1234, QHostAddress("127.0.0.1"), 1235};
    comm = new Communicator(props, this);

    interface = new Interface();
    interface->show();

    connect(interface, SIGNAL(request(QString)), this, SLOT(toCommunicator(QString)));
    connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(fromCommunicator(QByteArray)));
}

Client::~Client()
{
    delete interface;
    delete comm;

}

void Client::fromCommunicator(QByteArray data) {
    QString str_data = QString(data);

    struct response res = decodeResponse(str_data);

    if (res.header == TRANSPOSE_RESPONSE) {
        interface->applyTranspose(res.data);
    } else if (res.header == DETERMINANT_RESPONSE) {
        interface->applyDeterminant(res.data);
    } else if (res.header == RANK_RESPONSE) {
        interface->applyRank(res.data);
    }
}

void Client::toCommunicator(QString data) {
    comm->send(QByteArray().append(data.toStdString()));
    return;
}


