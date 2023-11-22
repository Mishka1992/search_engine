#include <QCoreApplication>
#include "converterjson.h"
#include "invertedindex.h"
#include "searchserver.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QMutex>
#include <algorithm>
QMutex mtx2;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConverterJSON json;
    InvertedIndex invIndex;

    QVector<QString> doc=json.GetTextDocuments();

    invIndex.UpdateDocumentBase(doc);

    SearchServer searchServer(invIndex);

    QVector<QVector<RelativeIndex> > rel=searchServer.search(json.GetRequests());
    json.putAnswers(searchServer.answers);
//QtConcurrent::run(t,&ConverterJSON::putAnswers,searchServer.answers);
    return 0;
}

