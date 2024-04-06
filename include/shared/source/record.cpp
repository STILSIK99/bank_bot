#include "record.h"


//-----------------------------------PUBLIC------------------------------------

Record::Record(std::map<QString, QString> * _data){
    fields = _data;
}

Record::~Record(){
    delete fields;
}

QDate Record::getOperationDate(){
    if (fields->count(RECORDS::DATE_IN)){
        return TOOLS::extractDateFromRecord(fields->at(RECORDS::DATE_IN));
    } else if (fields->count(RECORDS::DATE_OUT)){
        return TOOLS::extractDateFromRecord(fields->at(RECORDS::DATE_OUT));
    }
    return QDate(1900, 1, 1);
}

//----------------------------------PRIVATE------------------------------------

