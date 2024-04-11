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

//exctract date value, str only '\d\d\.\d\d\.\d\d\d\d' format
QDate extractDateFromRecord(const QString &);

//exctract digit value, str only '[\d\.]+' format
long long exctractSum(const QString &);

// const std::map<QString, QString> extractVars(Config *, const QString &);

}

