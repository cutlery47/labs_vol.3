
#include "request.h"

QString buildRequest(request input) {
    QString body = "";
    QString header = "";

    // хэдер запроса - тип операции
    header.append(QString::number(input.header));
    header.append(header_sep);

    // тело запроса - замерность матрицы и ее элементы
    body.append(QString::number(input.matrix_size));
    body.append(body_sep);
    body.append(input.matrix_values);

    return header + body;
}

QString buildResponse(response output) {
    QString body = "";
    QString header = "";

    // тут все так же пока что
    header.append(QString::number(output.header));
    header.append(header_sep);

    // тело запроса
    body.append(output.data);

    return header + body;
}

QString fromCellsToQString(QLineEdit** cells, int size) {
    QString values;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (cells[i][j].text() == "") {
                values.append("0");
            } else {
                values.append(cells[i][j].text());
            }

            values.append(",");
        }
    }

    values.chop(1);
    return values;
}

response decodeResponse(QString response_data) {
    struct response res;
    QString str_header;
    QString str_data;
    int index = 0;
    int flag = 0;

    while (index < response_data.size()) {
        if (response_data[index] == '|') {
            flag += 1;
        } else {
            switch (flag){
                case(0):
                    str_header.append(response_data[index]);
                    break;
                case(1):
                    str_data.append(response_data[index]);
                    break;
            }
        }
        ++index;
    }

    res.header = str_header.toInt();
    res.data = str_data;

    return res;
}

request decodeRequest(QString request_data) {
    struct request req;
    QString str_header;
    QString str_size;
    QString str_values;
    int index = 0;
    int flag = 0;


    while (index < request_data.size()) {
        if (request_data[index] == '|' || request_data[index] == ';') {
            ++flag;
        } else {
            switch (flag){
                case(0):
                    str_header.append(request_data[index]);
                    break;
                case(1):
                    str_size.append(request_data[index]);
                    break;
                case(2):
                    str_values.append(request_data[index]);
                    break;
                }
        }
        ++index;
    }

    req.header = QString(str_header).toInt();
    req.matrix_size = QString(str_size).toInt();
    req.matrix_values = str_values;

    return req;
}

