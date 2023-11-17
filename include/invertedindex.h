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
    // ƒанный оператор необходим дл€ проведени€ тестовых сценариев
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};
class InvertedIndex {
public:
    InvertedIndex() = default;
    /**
* ќбновить или заполнить базу документов, по которой будем совершать
поиск
* @param texts_input содержимое документов
*/
    void UpdateDocumentBase(QVector<QString> input_docs);
    /**
* ћетод определ€ет количество вхождений слова word в загруженной базе
документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
*/
    QVector<Entry> GetWordCount(const QString& word);
private:

    QMap<QString, QVector<Entry>> freq_dictionary; // частотный словарь
    QVector<QString> docs; // список содержимого документов

};

#endif // INVERTEDINDEX_H
