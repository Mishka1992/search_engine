#include "gtest/gtest.h"
#include "invertedindex.h"

using namespace std;
void TestInvertedIndexFunctionality(
        const QVector<QString>& docs,
        const QVector<QString>& requests,
        const QVector<QVector<Entry>>& expected
        ) {
    QVector<QVector<Entry>> result;
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    for(auto& request : requests) {
        QVector<Entry> word_count = idx.GetWordCount(request);
        result.push_back(word_count);
    }
    ASSERT_EQ(result, expected);
}
TEST(TestCaseInvertedIndex, TestBasic) {
    const QVector<QString> docs = {
        "london is the capital of great britain",
        "big ben is the nickname for the Great bell of the striking clock"
    };
    const QVector<QString> requests = {"london", "the"};
    const QVector<QVector<Entry>> expected = {
        {
            {0, 1}
        }, {
            {0, 1}, {1, 3}
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestBasic2) {
    const QVector<QString> docs = {
        "milk milk milk milk water water water",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino"
    };
    const QVector<QString> requests = {"milk", "water", "cappuccino"};
    const QVector<QVector<Entry>> expected = {
        {
            {0, 4}, {1, 1}, {2, 5}
        }, {
            {0, 3}, {1, 2}, {2, 5}
        }, {
            {3, 1}
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
    const QVector<QString> docs = {
        "a b c d e f g h i j k l",
        "statement"
    };
    const QVector<QString> requests = {"m", "statement"};
    const QVector<QVector<Entry>> expected = {
        {
        }, {
            {1, 1}
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
