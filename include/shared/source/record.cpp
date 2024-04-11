#include "record.h"


//-----------------------------------PUBLIC------------------------------------

Record::Record(std::map<QString, QString> * _data, bool _direct){
    fields = _data;
    direction = _direct;
}

Record::~Record(){
    delete fields;
}

QDate Record::getOperationDate() const {
    if (direction){
        return TOOLS::extractDateFromRecord(fields->at(RECORDS::DATE_IN));
    } else {
        return TOOLS::extractDateFromRecord(fields->at(RECORDS::DATE_OUT));
    }
}

long long Record::getSum() const {
    auto sum = exctractSum();
    if (!direction){
        sum *= -1;
    }
    return sum;
}
//----------------------------------PRIVATE------------------------------------

long long Record::exctractSum() const {
    qDebug() << "Record::exctractSum";
    if (!fields->count(RECORDS::OPERATION_SUM)) {
        qDebug() << "Not found sum.";
        return 0;
    }
    return TOOLS::exctractSum(fields->at(RECORDS::OPERATION_SUM));
}
