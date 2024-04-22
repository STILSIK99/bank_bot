#include "data_core.h"

//--------------------------------PUBLIC SLOTS---------------------------------

//-----------------------------------PUBLIC------------------------------------

void DataCore::processStatement(Statement *state){
    if (!storage.count(state->getAccountNumber())){
        storage[state->getAccountNumber()] = state->dataByDate;
        return ;
    }
    for(auto &date : state->dataByDate){

    }
}

//-----------------------------------PUBLIC------------------------------------

bool DataCore::init(const QString & _s,const QString & _u,const QString & _p){
    if (!DataBase::connect(_s, _u, _p)){
        qDebug() << "DataCore::init - not connected";
        return false;
    }
    if (!DataStorage::createTables()) return false;
    DataStorage::insertStartData();

    return true;
}

DataCore::~DataCore(){
    if (DataBase::isConnected()) DataBase::close();
}

void DataCore:: test(){
    QString request = "Select * from accounts;";
    std::vector<std::vector<QString>> data;
    DataBase::query(request, 2, data);
    for (auto row : data){
        qDebug() << TOOLS::toString(row);
    }

}
//----------------------------------PRIVATE------------------------------------

