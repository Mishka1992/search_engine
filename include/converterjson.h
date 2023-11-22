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
* ����� ��������� ����������� ������
* @return ���������� ������ � ���������� ������ �������������
* � config.json
*/
    QVector<QString> GetTextDocuments();
    /**
* ����� ��������� ���� max_responses ��� ����������� �����������
* ���������� ������� �� ���� ������
* @return
*/
    int GetResponsesLimit();
    /**
* ����� ��������� �������� �� ����� requests.json
* @return ���������� ������ �������� �� ����� requests.json
*/
    QVector<QString> GetRequests();
    /**
* �������� � ���� answers.json ���������� ��������� ��������
*/
    void putAnswers(QVector<pair<int,QVector<pair<size_t, float>>>> answers);

};

#endif // CONVERTERJSON_H
