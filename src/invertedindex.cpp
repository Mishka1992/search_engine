#include "invertedindex.h"
#include <QDebug>

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
    QRegExp reg("\\s+");
    QVector<Entry> entry;
    if(docs.empty())
    {
        return {};
    }

    for(int i=0;i<docs.size();i++)
    {
        Entry ent;
        ent.doc_id=i;
        ent.count=0;
        QStringList text=docs[i].split(reg);
        for (int index = 0; index < text.length(); index++)
        {
            if(text.at(index)==word)
            {
                ent.count++;
            }
        }
        if(ent.count!=0){
            entry.push_back(ent);
        }
    }
    return entry;
}


