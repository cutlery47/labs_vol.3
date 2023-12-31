
#ifndef REQUEST_H
#define REQUEST_H

#define header_sep "|"
#define body_sep ";"

#include <QString>
#include <QLineEdit>

// операции
enum headers {
    DETERMINANT_REQUEST = 0,
    TRANSPOSE_REQUEST = 1,
    RANK_REQUEST = 2,
    DETERMINANT_RESPONSE = 3,
    TRANSPOSE_RESPONSE = 4,
    RANK_RESPONSE = 5,
};

// каждый запрос содержит хэдер и данные матрицы
// хэдер нужен для определения операции
// значения матрицы, очевидно, нужны чтобы их изменять -_-
struct request {
    int header;
    int matrix_size;
    QString matrix_values;
};

// каждый ответ содержит хэдер и какие-то доп данные
// хэдер, как и в запросе, нужен для определения операции
// данные - просто значение(я), возвращаемые после операции
struct response {
    int header;
    QString data;
};

//создание запроса
QString buildRequest(request input);

//создание ответа
QString buildResponse(response output);

//преобразование запроса из строки в стракт
request decodeRequest(QString request_data);

//преобразование ответа из строки в стракт
response decodeResponse(QString response_data);

//преобразование из QLineEdit.text() в QString (возможно не нужно)
QString fromCellsToQString(QLineEdit** cells, int size);


#endif // REQUEST_H
