
#include "request.h"

QString buildRequest(request input) {
    QString body = "";
    QString header = "";
    QString type = "";

    // хэдер запроса - тип операции
    header.append(QString::number(input.header));
    header.append(header_sep);

    // тип данных
    type.append(QString::number(input.type));
    type.append(header_sep);

    // тело запроса - замерность матрицы и ее элементы
    body.append(QString::number(input.matrix_size));
    body.append(body_sep);
    body.append(input.matrix_values);

    return header + type + body;
}

QString buildResponse(response output) {
    QString body = "";
    QString header = "";
    QString type = "";

    // тут все так же пока что
    header.append(QString::number(output.header));
    header.append(header_sep);

    // тип данных
    type.append(QString::number(output.type));
    type.append(header_sep);

    // тело запроса
    body.append(output.data);

    return header + type + body;
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
    QString str_type;
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
                    str_type.append(response_data[index]);
                    break;
                case(2):
                    str_data.append(response_data[index]);
                    break;
            }
        }
        ++index;
    }

    res.header = str_header.toInt();
    res.type = str_type.toInt();
    res.data = str_data;

    return res;
}

request decodeRequest(QString request_data) {
    struct request req;
    QString str_header;
    QString str_type;
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
                    str_type.append(request_data[index]);
                    break;
                case(2):
                    str_size.append(request_data[index]);
                    break;
                case(3):
                    str_values.append(request_data[index]);
                    break;
                }
        }
        ++index;
    }

    req.header = QString(str_header).toInt();
    req.type = QString(str_header).toInt();
    req.matrix_size = QString(str_size).toInt();
    req.matrix_values = str_values;

    return req;
}

