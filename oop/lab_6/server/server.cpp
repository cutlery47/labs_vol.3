#include "server.h"


Server::Server(QWidget *parent)
    : QWidget(parent)
{
    // устанавливаем параметры подключения сокетов
    CommProps props = {QHostAddress("127.0.0.1"), 1235, QHostAddress("127.0.0.1"), 1234};
    comm = new Communicator(props, this);

    connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(respondToRecieved(QByteArray)));
}

Server::~Server()
{
    delete comm;

}

void Server::respondToRecieved(QByteArray request_data) {
    QString response_data;
    struct request req_data;
    struct response res_data;
    req_data = decodeRequest(QString(request_data));

    int mat_size = req_data.matrix_size;

    if (req_data.type == RATIONAL_NUM) {
        SquareMatrix<Rational>* matrix = new SquareMatrix<Rational>(mat_size);
        matrix->applyChanges(mat_size, req_data.matrix_values);
        res_data.type = req_data.type;
        if (req_data.header == DETERMINANT_REQUEST) {
            res_data.data = matrix->det().simplify().toQString();
            res_data.header = DETERMINANT_RESPONSE;
        } else if (req_data.header == RANK_REQUEST) {
            res_data.data = QString::number(matrix->rank());
            res_data.header = RANK_RESPONSE;
        } else if (req_data.header == TRANSPOSE_REQUEST) {
            matrix->transpose();
            res_data.data = matrix->valuesToQString();
            res_data.header = TRANSPOSE_RESPONSE;
        }
        delete matrix;
    } else if (req_data.type == REAL_NUM) {
        SquareMatrix<Real>* matrix = new SquareMatrix<Real>(mat_size);
        matrix->applyChanges(mat_size, req_data.matrix_values);
        res_data.type = req_data.type;
        if (req_data.header == DETERMINANT_REQUEST) {
            res_data.data = matrix->det().toQString();
            res_data.header = DETERMINANT_RESPONSE;
        } else if (req_data.header == RANK_REQUEST) {
            res_data.data = QString::number(matrix->rank());
            res_data.header = RANK_RESPONSE;
        } else if (req_data.header == TRANSPOSE_REQUEST) {
            matrix->transpose();
            res_data.data = matrix->valuesToQString();
            res_data.header = TRANSPOSE_RESPONSE;
        }
        delete matrix;
    } else {
        SquareMatrix<Complex>* matrix = new SquareMatrix<Complex>(mat_size);
        matrix->applyChanges(mat_size, req_data.matrix_values);
        res_data.type = req_data.type;
        if (req_data.header == DETERMINANT_REQUEST) {
            res_data.data = matrix->det().toQString();
            res_data.header = DETERMINANT_RESPONSE;
        } else if (req_data.header == RANK_REQUEST) {
            res_data.data = QString::number(matrix->rank());
            res_data.header = RANK_RESPONSE;
        } else if (req_data.header == TRANSPOSE_REQUEST) {
            matrix->transpose();
            res_data.data = matrix->valuesToQString();
            res_data.header = TRANSPOSE_RESPONSE;
        }
        delete matrix;
    }

    response_data = buildResponse(res_data);
    comm->send(QByteArray().append(response_data.toStdString()));
}




