#pragma once

#pragma once

#include <QTextCodec>
#include <QString>
#include <QJsonObject>
#include <QDate>
#include <map>


namespace TOOLS{

//convert 1c file from CP1251 coding to UTF-8
QString convertFile(QByteArray inputText);

//compare begin of 2 strings
bool comparePrefix(const QString &, const QString &);

//for check available fields in json-object
bool compareObjects(const QJsonObject &, const std::vector<QString> &);

QString getLastLine(const QString &, int = 2);

QDate extractDateFromRecord(const QString &);

}

