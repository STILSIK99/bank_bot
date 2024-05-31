#pragma once

#include <QString>
#include <QDate>
#include <QDebug>
#include <QCryptographicHash>

#include <map>

#include "tools.h"
#include "dc_variables.h"

using Crypto = QCryptographicHash;

namespace RECORDS{

    const QString DATE_IN       = "ДатаПоступило";
    const QString DATE_OUT      = "ДатаСписано";
    const QString OPERATION_SUM = "Сумма";

    // std::vector<QString> FIELDS{};

    const std::vector<QString> HASH_1 = {
        "Дата", "ПлательщикБИК", "ПолучательБИК",
        "ПолучательРасчСчет", "Сумма"
    };

}


struct HashSum{
    unsigned long long firstPart, secondPart;

    HashSum(): firstPart(0), secondPart(0){};
    HashSum(const QString & str){
        // qDebug() << "HashSum::HashSum";
        if (str.length() != 32){
            qDebug() << "HashSum error.Length.";
        } else {
            bool res;
            firstPart = str.left(16).toULongLong(&res, 16);
            if (!res) qDebug() << "HashSum error.Value.";
            secondPart = str.right(16).toULongLong(&res, 16);
            if (!res) qDebug() << "HashSum error.Value.";
        }
    }
    HashSum(unsigned long long f, unsigned long long s):
        firstPart(f), secondPart(s)
    {}

    QString getFirst() const {
        return QString::number(firstPart);
    }

    QString getSecond() const {
        return QString::number(secondPart);
    }

};

class Record{
    /*

    Класс для работы с конкретной операцией из выписки.

     */
    std::map<QString, QString> *fields;
    bool direction; // true == + , false == -
    long long exctractSum () const;

    QString toHash(const std::vector<QString> &);
    void toHash_1();
    void toHash_2();

public:
    Record(std::map<QString, QString> *, bool); //fields, direction
    ~Record();
    HashSum hash_1, hash_2;
    QDate getOperationDate () const;
    long long getSum() const ;
    QString buildInsert(int) const;
    QString buildDelete(int) const;

};
