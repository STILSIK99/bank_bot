#include "record.h"


//-----------------------------------PUBLIC------------------------------------

Record::Record(std::map<QString, QString> * _data, bool _direct) {
    fields = _data;
    direction = _direct;
    toHash_1();
    toHash_2();
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

void Record::toHash_1(){
    hash_1 = HashSum(toHash(RECORDS::HASH_1));
}

void Record::toHash_2(){
    hash_2 =  HashSum(toHash(DATABASE::FIELDS));
}

QString Record::buildInsert(int accountId) const {
    QString request = "(";
    request += QString::number(accountId) + ",";
    request += hash_1.getFirst() + ",";
    request += hash_1.getSecond() + ",";
    request += hash_2.getFirst() + ",";
    request += hash_2.getSecond() + ",";
    for(int i = 0; i < DATABASE::FIELDS.size(); ++i){
        auto &field = DATABASE::FIELDS[i];
        if (!fields->count(field)) {
            request += "null";
        } else if (fields->at(field) == ""){
            request += "null";
        } else if (DATABASE::IS_DIGIT_FIELD[i]){
            request += fields->at(field) + "";
        } else if (DATABASE::IS_DATE_FIELD[i]) {
            if (fields->at(field).length() == 10){
                request += "'";
                request += TOOLS::extractDateFromRecord(
                               fields->at(field)).toString("yyyy-MM-dd");
                request += "'";
            } else {
                request += "null";
            }
        } else {
            int column = i + 1;
            if (DATABASE::LENGTH_CONSTRAINT.count(column)){
                if (fields->at(field).length() > DATABASE::LENGTH_CONSTRAINT.at(column)){
                    qDebug() << "Field_" << column << " has length " <<
                        fields->at(field).length() << " that more than " <<
                        DATABASE::LENGTH_CONSTRAINT.at(column);
                    request += QString("'%1'").arg(
                        fields->at(field).left(DATABASE::LENGTH_CONSTRAINT.at(column)));
                } else {
                    request += QString("'%1'").arg(fields->at(field));
                }
            } else {
                request += QString("'%1'").arg(fields->at(field));
            }
        }
        request += ",";
    }
    request[request.length() - 1] = ')';
    request += ";";
    return DATABASE::REQUESTS::INSERT_RECORD.arg(request);
}

QString Record::buildDelete(int accountId) const {
    return DATABASE::REQUESTS::DELETE_RECORD.arg(
        hash_1.getFirst(), hash_1.getSecond(),
        hash_2.getFirst(), hash_2.getSecond(), QString::number(accountId));
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

QString Record::toHash(const std::vector<QString> &arr){
    QString record = "";
    if (fields){
        for(auto &el : arr){
            if (fields->count(el)){
                record += el + "=" + fields->at(el) + "\r\n";
            }
        }
    }

    return Crypto::hash(record.toUtf8(), Crypto::Md5).toHex();
}
