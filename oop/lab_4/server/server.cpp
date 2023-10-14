
#include "server.h"


Server::Server(QWidget *parent)
    : QWidget(parent)
{
    // устанавливаем параметры подключения сокетов
    CommProps props = {QHostAddress("127.0.0.1"), 1235, QHostAddress("127.0.0.1"), 1234};
    comm = new Communicator(props, this);

    matrix = new Matrix(3);

    connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(respondToRecieved(QByteArray)));
}

Server::~Server()
{
    delete comm;
    delete matrix;

}

void Server::respondToRecieved(QByteArray request_data) {
    QString response_data;
    struct request req_data;
    struct response res_data;
    req_data = decodeRequest(QString(request_data));

    // обновляем размер, только если он был изменен на клиенте
    matrix->applyChanges(req_data.matrix_size, req_data.matrix_values);

    // кроме первых трех, других оперций быть не может
    if (req_data.header == DETERMINANT_REQUEST) {
        res_data.data = numberToQString(matrix->det());
        res_data.header = DETERMINANT_RESPONSE;
    } else if (req_data.header == RANK_REQUEST) {
        res_data.data = QString::number(matrix->rank());
        res_data.header = RANK_RESPONSE;
    } else if (req_data.header == TRANSPOSE_REQUEST) {
        matrix->transpose();
        res_data.data = matrix->valuesToQString();
        res_data.header = TRANSPOSE_RESPONSE;
    }

    // слишком много дэйты...
    response_data = buildResponse(res_data);

    comm->send(QByteArray().append(response_data.toStdString()));
}




