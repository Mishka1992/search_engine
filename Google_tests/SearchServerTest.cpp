#include "gtest/gtest.h"
#include "searchserver.h"

TEST(TestCaseSearchServer, TestSimple) {
    const QVector<QString> docs = {
        "milk milk milk milk water water water",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino"
    };
    const QVector<QString> request = {"milk water", "sugar"};
    const QVector<QVector<RelativeIndex>> expected = {
        {
            {2, 1},
            {0, 0.7},
            {1, 0.3}
        },
        {
        }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    QVector<QVector<RelativeIndex>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}
TEST(TestCaseSearchServer, TestTop5) {
    const QVector<QString> docs = {
        "london is the capital of great britain",
        "paris is the capital of france",
        "berlin is the capital of germany",
        "rome is the capital of italy",
        "madrid is the capital of spain",
        "lisboa is the capital of portugal",
        "bern is the capital of switzerland",
        "moscow is the capital of russia",
        "kiev is the capital of ukraine",
        "minsk is the capital of belarus",
        "astana is the capital of kazakhstan",
        "beijing is the capital of china",
        "tokyo is the capital of japan",
        "bangkok is the capital of thailand",
        "welcome to moscow the capital of russia the third rome",
        "amsterdam is the capital of netherlands",
        "helsinki is the capital of finland",
        "oslo is the capital of norway",
        "stockholm is the capital of sweden",
        "riga is the capital of latvia",
        "tallinn is the capital of estonia",
        "warsaw is the capital of poland",
    };
    const QVector<QString> request = {"moscow is the capital of russia"};
    const QVector<QVector<RelativeIndex>> expected = {
        {

            {7, 1},
            {14, 1},
            { 0 , 0.667 },
            { 1 , 0.667  },
            { 2 , 0.667  },
            { 3 , 0.667  },
            { 4 , 0.667  },
            { 5 , 0.667  },
            { 6 , 0.667  },
            { 8 , 0.667  },
            { 9 , 0.667  },
            { 10 , 0.667  },
            { 11 , 0.667  },
            { 12 , 0.667  },
            { 13 , 0.667  },
            { 15 , 0.667  },
            { 16 , 0.667  },
            { 17 , 0.667  },
            { 18 , 0.667  },
            { 19 , 0.667  },
            { 20 , 0.667  },
            { 21 , 0.667  }
        }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    QVector<QVector<RelativeIndex>> result = srv.search(request);

    ASSERT_EQ(result, expected);
}
