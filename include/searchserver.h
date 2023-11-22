#ifndef SEARCHSERVER_H
#define SEARCHSERVER_H
#include <QVector>
#include "invertedindex.h"

struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};
class SearchServer {
public:
    /**
* @param idx � ����������� ������ ��������� ������ �� �����
InvertedIndex,
* ����� SearchServer ��� ������ ������� ���� ����������� �
�������
*/
    SearchServer(InvertedIndex& idx): _index(idx){ };
    /**
* ����� ��������� ��������� ��������
* @param queries_input ��������� ������� ������ �� �����
requests.json
* @return ���������� ��������������� ������ ����������� ������� ���
�������� ��������
*/
    QVector<QVector<RelativeIndex>> search(const QVector<QString>& queries_input);
    QVector<pair<int,QVector<pair<size_t, float>>>> answers;
private:
    QVector<RelativeIndex> getRelativeIndex(const QString& word);
    QVector<QString> getWordRequest(const QString& word);

    InvertedIndex _index;
};

#endif // SEARCHSERVER_H
