#include "../include/invertedindex.h"
#include <QDebug>
#include <sstream>
#include <QtConcurrent/QtConcurrent>

void InvertedIndex::UpdateDocumentBase(QVector<QString> input_docs)
{

    if(input_docs.empty())
    {
        qDebug()<<"size = 0";
        return;
    }

    //  QVector<QString> vec;
    for(auto &i:input_docs)
    {

        qDebug()<<"====================================";
        //qDebug()<<input_docs[i];

        docs.push_back(i);

    }


}

QVector<Entry> InvertedIndex::GetWordCount(const QString &word)
{
    QRegExp reg(" ");
    QVector<Entry> entry;

    for(int i=0;0<docs.size();i++)
    {
        Entry ent;
        ent.doc_id=i;
        ent.count=0;
        QStringList text=docs[i].split(reg);
        for (int index = 0; index < text.length(); index++)
        {

            if(text.at(index).toStdString()==word.toStdString());
            {
                ent.count++;
            }

        }

        entry.push_back(ent);
    }
    return entry;
}

//void InvertedIndex::FreqDictionary(QVector<QString> docs)
//{

//}
