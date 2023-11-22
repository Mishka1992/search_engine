#ifndef CONVERTERJSON_H
#define CONVERTERJSON_H

#include <QByteArray>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

using namespace std;

class ConverterJSON
{
public:
    ConverterJSON() = default;
    /**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/
    QVector<QString> GetTextDocuments();
    /**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/
    int GetResponsesLimit();
    /**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
    QVector<QString> GetRequests();
    /**
* Положить в файл answers.json результаты поисковых запросов
*/
    void putAnswers(QVector<pair<int,QVector<pair<size_t, float>>>> answers);

};

#endif // CONVERTERJSON_H
