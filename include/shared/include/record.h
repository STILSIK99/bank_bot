#pragma once

#include <QString>
#include <QDate>
#include <QDebug>

#include <map>

#include "tools.h"

namespace RECORDS{

const QString DATE_IN       = "ДатаПоступило";
const QString DATE_OUT      = "ДатаСписано";
const QString OPERATION_SUM = "Сумма";

// std::vector<QString> FIELDS{};

}

class Record{
    /*

    Класс для работы с конкретной операцией из выписки.

     */
    std::map<QString, QString> *fields;
    bool direction; // true == + , false == -
    long long exctractSum () const;

public:
    Record(std::map<QString, QString> *, bool);
    ~Record();
    QString toHash_1();
    QString toHash_2();
    QDate getOperationDate () const;
    long long getSum() const ;

};
