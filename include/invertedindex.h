#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H
#include <QVector>
#include <QMap>
#include <QRegExp>
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
    QVector<QString> docs; // ������ ����������� ����������
    QMap<QString, QVector<Entry>> freq_dictionary; // ��������� �������

};

#endif // INVERTEDINDEX_H
