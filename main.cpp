#include <QCoreApplication>
#include <QDebug>
#include "file_core.h"
#include "parser_core.h"
#include "test.h"
#include "statement.h"
#include "data_storage.h"
#include <QObject>


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

    if (TEST::testConfig()){
        qDebug() << "OK";
    } else {
        qDebug() << "NO";
    }


    return a.exec();
}
