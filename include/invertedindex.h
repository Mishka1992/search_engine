#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H
#include <QVector>
#include <QString>
#include <QMap>
#include <QRegExp>
#include <QFuture>
#include <QMutex>
#include <QtConcurrent/QtConcurrent>
using namespace std;
struct Entry {
    size_t doc_id, count;
    // ������ �������� ��������� ��� ���������� �������� ���������
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};
class InvertedIndex {
public:
    InvertedIndex() = default;
    /**
* �������� ��� ��������� ���� ����������, �� ������� ����� ���������
�����
* @param texts_input ���������� ����������
*/
    void UpdateDocumentBase(QVector<QString> input_docs);
    /**
* ����� ���������� ���������� ��������� ����� word � ����������� ����
����������
* @param word �����, ������� ��������� �������� ���������� ����������
* @return ���������� �������������� ������ � �������� ����
*/
    QVector<Entry> GetWordCount(const QString& word);
private:

    QMap<QString, QVector<Entry>> freq_dictionary; // ��������� �������
    QVector<QString> docs; // ������ ����������� ����������

};

#endif // INVERTEDINDEX_H
