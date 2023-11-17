#include <QCoreApplication>
#include "converterjson.h"
#include "invertedindex.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QMutex>
QMutex mtx2;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConverterJSON json;
    InvertedIndex invIndex;
    QVector<QString> doc=json.GetTextDocuments();
//QVector<QString> doc;
//doc.push_back("milk milk milk milk water water water");
//doc.push_back("milk water water");
//doc.push_back("milk milk milk milk milk water water water water water");
//doc.push_back("americano cappuccino");
    invIndex.UpdateDocumentBase(doc);
//    QVector<QString> words{"milk","water","cappuccino"};

//    for(int i=0;i<words.size();i++){
//        qDebug()<<words[i];
//         qDebug()<<"=============================";
    QVector<Entry> vec=invIndex.GetWordCount("are");

    for(int i=0;i<vec.size();i++)
    {

        qDebug()<<"{"<<vec[i].doc_id<<","<<vec[i].count<<"}";

    }
//}

    return 0;
}

