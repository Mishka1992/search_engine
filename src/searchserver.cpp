#include "searchserver.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
QMutex mtServer;


QVector<QVector<RelativeIndex> > SearchServer::search(const QVector<QString> &queries_input)
{
    QVector<QVector<RelativeIndex>> relatInd;
    if(queries_input.empty())
    {
        return {};
    }
    for(auto &query:queries_input)
    {
        QFuture<QVector<RelativeIndex>> relInd=QtConcurrent::run(this,&SearchServer::getRelativeIndex,query);

        relatInd.push_back(relInd);
    }


    return relatInd;
}

QVector<RelativeIndex> SearchServer::getRelativeIndex(const QString& query)
{
 mtServer.lock();
    QVector<RelativeIndex> relativeIndex;
    auto request=getWordRequest(query);

    QVector<Entry> vec;
    QMap<size_t,float> mapEntry;
    int maxRequest=0;

    for(auto &words:request){

        auto entry=_index.GetWordCount(words);

        for(auto &en:entry)
        {

            vec.push_back({en.doc_id,en.count});
        }

    }

    for(auto &i:vec)
    {

        if (mapEntry.find(i.doc_id) != mapEntry.end()) {
            mapEntry[i.doc_id]+=i.count;
        } else {
            mapEntry.insert(i.doc_id,i.count);
        }

    }

    foreach (size_t key, mapEntry.keys())
    {
        if(mapEntry.value(key)>maxRequest)
        {
            maxRequest=mapEntry.value(key);
        }

    }

    foreach (size_t key, mapEntry.keys())
    {
        float m=round(mapEntry.value(key)/maxRequest * 1000) / 1000;

        relativeIndex.push_back({key,m});
    }
    std::sort(relativeIndex.begin(), relativeIndex.end(), [] (RelativeIndex lh, RelativeIndex rh)
    {
        if(lh.rank == rh.rank){
            return lh.doc_id < rh.doc_id;
        }
        return lh.rank > rh.rank;

    });
    mtServer.unlock();
    return relativeIndex;
}


QVector<QString> SearchServer::getWordRequest(const QString &word)
{
    QVector<QString> request;
    QRegExp reg("\\s+");
    QStringList text=word.split(reg);
    for (int index = 0; index < text.length(); index++)
    {
        request.push_back(text[index]);
    }
    if(request.empty())
    {
        return {};
    }
    return request;
}


