#include <QCoreApplication>
#include "converterjson.h"
#include "invertedindex.h"
#include "searchserver.h"

QMutex mtx2;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConverterJSON json;
    InvertedIndex invIndex;

    QVector<QString> doc=json.GetTextDocuments();

    invIndex.UpdateDocumentBase(doc);

    SearchServer searchServer(invIndex);

    searchServer.search(json.GetRequests());
    json.putAnswers(searchServer.answers);

    return 0;
}

