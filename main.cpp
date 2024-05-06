#include <QCoreApplication>
#include <QDebug>
#include "file_core.h"
#include "parser_core.h"
#include "test.h"
#include "statement.h"
#include "data_storage.h"
#include <QObject>
#include <QThread>
#include "bot_app.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // FileCore fc;
    // ParserCore pc;

    // QObject::connect(&fc, &FileCore::parseFile, [](QByteArray* arr){
    //     qDebug() << QString::fromUtf8(*arr).left(100);
    //     delete arr;
    // });
    // fc.readZip("E:/C++/QT/bank_bot/bank_bot/src/archive.zip");

    // qDebug() << "Working.";

    // if (TEST::testParseStatement()){
    //     qDebug() << "OK";
    // } else {
    //     qDebug() << "NO";
    // }

    // if (TEST::testDataBaseConnection()){
    //     qDebug() << "OK";
    // } else {
    //     qDebug() << "NO";
    // }

    // if (TEST::testConfig()){
    //     qDebug() << "OK";
    // } else {
    //     qDebug() << "NO";
    // }

    // QHash <QString, int> arr;

    // arr["123"] = 1;
    // arr["10"] = 2;
    // arr["6435"] = 3;

    // for(auto el : arr){
    //     qDebug() << el;
    // }

    // std::list<int> arr = {1,2,3}, arr_1 = {4, 5, 6};
    // arr.insert(arr.end(), arr_1.begin(), arr_1.end());
    // for(auto el : arr){
    //     qDebug() << el;
    // }

    // return 0;


    BotApp *app = new BotApp();
    if (!app->init()){
        return -1;
    }
    app->start();




    return a.exec();
}
