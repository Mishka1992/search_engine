#include "converterjson.h"
#include "anyError.h"
#include <QMutex>

QVector<QString> ConverterJSON::GetTextDocuments()
{
    QFile file("config.json");
    if(!file.exists()){
        throw NoFile();
    }
    QByteArray val;

    file.setFileName("config.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(val, &error);
    QVector<QString> files;
    if (doc.isObject())
    {

        QJsonArray array = doc["files"].toArray();

        QList <QVariant> ar = array.toVariantList();
        for( auto &i: ar) {
            QFile file(i.toString());

            if(file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                while(!file.atEnd())
                {
                    //читаем строку
                    QString str = file.readAll();

                    files.push_back(str);
                }

            }
            file.close();
        }

    }

    return files;
}

int ConverterJSON::GetResponsesLimit()
{
    QFile file("config.json");
    if(!file.exists()){
        throw NoFile();
    }
    QByteArray val;

    file.setFileName("config.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(val, &error);

    if (doc.isObject())
    {
        QJsonObject json = doc.object();
        QJsonValue test = json.value("config");

        if (test.isObject())
        {
            QJsonObject obj = test.toObject();
            int max_responses = obj["max_responses"].toInt();
            qDebug()<<obj["name"].toString();
            return max_responses;
        }
        return 0;
    }
    return 0;
}

QVector<QString> ConverterJSON::GetRequests()
{
    QFile file("requests.json");
    if(!file.exists()){
        throw NoFileRequests();
    }
    QByteArray val;

    file.setFileName("requests.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(val, &error);
    QVector<QString> files;
    if (doc.isObject())
    {
        QJsonArray array = doc["requests"].toArray();

        QList <QVariant> ar = array.toVariantList();
        for( auto &i : ar ) {
            files.push_back(i.toString());
        }
    }
    return files;
}

void ConverterJSON::putAnswers(QVector<QVector<pair<int, float>>> answers)
{
    QFile file("answer.json");
    if(!file.exists()){
        file.open(QIODevice::WriteOnly);
        file.close();
    }else{
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        file.close();
    }

}
