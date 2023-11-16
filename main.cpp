#include <QCoreApplication>
#include "include/converterjson.h"
#include "include/invertedindex.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QMutex>
QMutex mtx2;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

   unique_ptr<ConverterJSON> json;
   unique_ptr<InvertedIndex> invIndex;
mtx2.lock();
  QVector<QString> doc=json->GetTextDocuments();
mtx2.unlock();
  invIndex->UpdateDocumentBase(doc);
  ///* QVector<Entry> vec=*/invIndex->GetWordCount("are");
//QVector<QString> vec1;
//  for(int i=0;i<docs.size();i++)
//{
//qDebug()<<i;
//    qDebug()<<docs[i];
//    qDebug()<<"=============================";
//    //vec1.push_back(i);
//   // qDebug()<<i.doc_id<<" "<<i.count;
//}
   //    qDebug()<<json->GetResponsesLimit();
//    qDebug()<<json->GetTextDocuments();
//    qDebug()<<json->GetRequests();
//    QVector<QVector<pair<int,float>>> answer;
//    json->putAnswers(answer);

    return 0;
}

