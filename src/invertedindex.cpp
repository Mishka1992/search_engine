#include "invertedindex.h"
#include <QDebug>
QMutex mtx;
Entry IndexFile(const QString& content,size_t index,const QString& word)
{
    mtx.lock();
    QRegExp reg("\\s+");
    Entry entry;

    entry.doc_id=index;
    entry.count=0;
    QStringList text=content.split(reg);
    for (int index = 0; index < text.length(); index++)
    {
        if(text.at(index)==word)
        {
            entry.count++;
        }
    }

    mtx.unlock();
    return entry;
}

void InvertedIndex::UpdateDocumentBase(QVector<QString> input_docs)
{

    if(input_docs.empty())
    {
        return;
    }

    for(auto &i: input_docs)
    {
        docs.push_back(i);
    }


}

QVector<Entry> InvertedIndex::GetWordCount(const QString &word)
{
    QVector<Entry> entry;
    if(docs.empty())
    {
        return {};
    }

    for(int i=0;i<docs.size();i++)
    {
        QFuture<Entry> entFind=QtConcurrent::run(IndexFile,docs[i],i,word);
        Entry entr1=entFind;
        if(entr1.count!=0)
        {
            entry.push_back(entFind);
        }
    }

    return entry;
}


