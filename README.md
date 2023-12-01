# search_engine
Поисковый движок представлякт из себя консольное приложение
(исполняемый файл, запускаемый на любом сервере или компьютере),
осуществляющее поиск и имеющее возможность настройки через файлы формата
JSON. Применённые в нём решения можно впоследствии встроить в поисковый
движок работающий на веб.
Принципы работы поискового движка:
1. В конфигурационном файле перед запуском приложения задаются названия
файлов, по которым движок будет осуществлять поиск.
2. Поисковый движок самостоятельно обходит все файлы и
индексирует их так, чтобы потом по любому поисковому запросу находит наиболее
релевантные документы.
3. Пользователь задаёт запрос через JSON-файл requests.json. Запрос — это
набор слов, по которым нужно найти документы.
4. Запрос трансформируется в список слов.
5. В индексе ищутся те документы, на которых встречаются все эти слова.
6. Результаты поиска ранжируются, сортируются и отдаются пользователю,
максимальное количество возможных документов в ответе задаётся в
конфигурационном файле.
7. В конце программа формирует файл answers.json, в который записывает
результаты поиска

Сборка приложения:
1. Установить на Ваш ПК  Qt Creator 5.15.2
2. Собрать приложение под MiNGW64

Пример файла JSON указан в директории bin/

Пример описания файла config.json:
{
"config": {
"name": "Example name",
"version": "0.1",
"max_responses": 5
},
"files": [
"../resources/file001.txt",
"../resources/file002.txt",
"../resources/file003.txt",
"../resources/file004.txt",
…
]
}

● config — общая информация, без которой приложение не запускается. Если это
поле отсутствует, то при старте программа должна выбросить исключение и
вывести в текстовую консоль ошибку config file is empty. Если отсутствует сам
файл config.json, то выбросит исключение и выведет ошибку config
file is missing.
● name — поле с названием поискового движка. Оно может быть любым.
● version — поле с номером версии поискового движка.
● max_responses — поле, определяющее максимальное количество ответов на
один запрос.
● files содержит пути к файлам, по которым необходимо осуществлять поиск.
Внутри списка files лежат пути к файлам.
● <путь к файлу>(“../resorces/file001.txt”) — это путь к файлу. Впоследствии по его
содержимому программа совершит поиск. Если по этому пути файл не
существует, то на экран выводится соответствующая ошибка, но выполнение
программы не прекращается. При этом каждый документ содержит не более
1000 слов с максимальной длиной каждого в 100 символов. Слова
состоят из строчных латинских букв и разделены одним или несколькими
пробелами.

Файл с запросами requests.json.
Он содержит запросы, которые необходимо обработать поисковому движку.
Пример описания файла requests.json:
{
"requests": [
"some words..",
"some words..",
"some words..",
"some words..",
…
]
}

● requests состоит из списка запросов, которые необходимо обработать
поисковым движком. Поле содержит не более 1000 запросов, каждый из
которых включает от одного до десяти слов.
● <содержимое запроса>(“some words”) — поисковый запрос, набор слов,
разделённых одним или несколькими пробелами.Все слова состоят из строчных латинских букв.

Файл с ответами на запросы answers.json.

Пример описания файла answers.json:
{
"answers": {
"request001": {
"result": "true",
"relevance": {
"docid": 0, “rank” : 0.989,
"docid": 1, “rank” : 0.897,
"docid": 2, “rank” : 0.750,
"docid": 3, “rank” : 0.670,
"docid": 4, “rank” : 0.561
}
},
"request002": {
"result": "true",
"docid": 0, “rank” : 0.769
},
"request003": {
"result": "false"
}
}
}
Рассмотрим каждого поле файла answers.json:
● answers — базовое поле в этом файле, которое содержит ответы на запросы.
● request001 … 003 — идентификатор запроса, по которому сформирован ответ.
Идентификатор запроса формируется автоматически по порядку, в котором
находятся запросы в поле requests файла requests.json. Например:
"requests": [
"some words..", для данной строки id запроса будет равен “request001”
"some words..", для данной строки id запроса будет равен “request002”
"some words..", для данной строки id запроса будет равен “request003”
"some words..", для данной строки id запроса будет равен “request004”
…
]
● result – результат поиска запроса. Если он принимает значение true, значит по
данному запросу найден хотя бы один документ. Если результат имеет значение
false, значит ни одного документа не найдено. Тогда других полей в ответе на
этот запрос нет.
● relevance включается в файл answers.json, если на этот запрос удалось найти
более одного документа.
Далее идут соответствия рейтинга ответа и названия id документа, в котором
осуществлялся поиск:
● <Идентификатор документа>("docid") — идентификатор документа, в котором
найден ответ на запрос. Он формируется автоматически при индексации всех
документов исходя из порядка, в котором документы расположены в поле files в
файле config.json. Например, если в поле config.json поле files содержит:
"files": [
"../resources/file001.txt", для данного файла docid будет равен 0
"../resources/file002.txt", для данного файла docid будет равен 1
"../resources/file003.txt", для данного файла docid будет равен 2
"../resources/file004.txt", для данного файла docid будет равен 3
…
]
● <ранг ответа>(“rank”) — ранг или поисковый рейтинг. Это число показывает,
насколько документ подходит для заданного запроса. В ответе id документов
располагаются в порядке уменьшения поискового рейтинга

Модульные тесты.
Модульные тесты проверяют работу отдельных модулей в ПО.
При успешном проведении тестов на экран должно вывести сообщение:

[==========] Running 5 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from TestCaseSearchServer
[ RUN      ] TestCaseSearchServer.TestSimple
[       OK ] TestCaseSearchServer.TestSimple (0 ms)
[ RUN      ] TestCaseSearchServer.TestTop5
[       OK ] TestCaseSearchServer.TestTop5 (0 ms)
[----------] 2 tests from TestCaseSearchServer (7 ms total)

[----------] 3 tests from TestCaseInvertedIndex
[ RUN      ] TestCaseInvertedIndex.TestBasic
[       OK ] TestCaseInvertedIndex.TestBasic (0 ms)
[ RUN      ] TestCaseInvertedIndex.TestBasic2
[       OK ] TestCaseInvertedIndex.TestBasic2 (0 ms)
[ RUN      ] TestCaseInvertedIndex.TestInvertedIndexMissingWord
[       OK ] TestCaseInvertedIndex.TestInvertedIndexMissingWord (0 ms)
[----------] 3 tests from TestCaseInvertedIndex (8 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 2 test suites ran. (26 ms total)
[  PASSED  ] 5 tests.

