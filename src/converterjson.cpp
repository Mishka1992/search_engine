#include "converterjson.h"
#include "anyError.h"

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
    QFile fAnswer("answer.json");
    if(!fAnswer.exists()){
        fAnswer.open(QIODevice::WriteOnly);
        fAnswer.close();
    }else{
        fAnswer.open(QIODevice::WriteOnly | QIODevice::Truncate);
        fAnswer.close();
    }
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
            qDebug()<<"name: "<<obj["name"].toString();
            qDebug()<<"max_responses: "<<max_responses;
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
    QVector<QString> requests;
    if (doc.isObject())
    {
        QJsonArray array = doc["requests"].toArray();
        QJsonObject recordObject;
        QJsonObject objObject;
        QList <QVariant> ar = array.toVariantList();
        for( auto &i : ar ) {
            requests.push_back(i.toString());
        }
    }
    return requests;
}

void ConverterJSON::putAnswers(QVector<pair<int,QVector<pair<size_t, float>>>> answers)
{
    QJsonObject recordObject;
    QJsonObject objObject;
    QJsonObject obj2Object;
    QJsonObject obj3Object;
    QJsonObject obj4Object;
    int limit=GetResponsesLimit();
    for(int i=0;i<answers.size();i++)
    {
        if(i==limit){
            break;
        }
        if(answers[i].second.empty())
        {
            obj2Object.insert("result", QJsonValue::fromVariant(false));
            objObject.insert("request" + QString::number(answers[i].first), obj2Object);
        }else{

            if(answers[i].second.size()==1){

                for(auto &n:answers[i].second)
                {

                    obj2Object.insert("docid", QJsonValue::fromVariant(n.first));
                    obj2Object.insert("rank", n.second);

                }
                obj2Object.insert("result", QJsonValue::fromVariant(true));
                objObject.insert("request" + QString::number(answers[i].first), obj2Object);
            }else{
                QJsonArray JsonTextArray;
                for(auto &n:answers[i].second)
                {
                    QJsonObject obj;
                    obj.insert("docid", QJsonValue::fromVariant(n.first));
                    obj.insert("rank", n.second);
                    JsonTextArray.push_back(obj);
                }
                obj4Object.insert("result", QJsonValue::fromVariant(true));
                obj4Object.insert("relevance", JsonTextArray);
                objObject.insert("request" + QString::number(answers[i].first), obj4Object);
            }
        }


    }
    recordObject.insert("answer", objObject);


    QJsonDocument doc(recordObject);
    QString jsonString = doc.toJson(QJsonDocument::Indented);

    QFile fAnswer("answer.json");

    fAnswer.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream( &fAnswer );
    stream << jsonString;
    fAnswer.close();

}
