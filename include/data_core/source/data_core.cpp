#include "data_core.h"

//--------------------------------PUBLIC SLOTS---------------------------------

//-----------------------------------PUBLIC------------------------------------
DataCore::DataCore(){

}

void DataCore::processStatement(Statement * state){
	auto number = state->getAccountNumber();
    if (!storage.count(number)){
        storage[number] = std::map<QDate, DailyOperations *>();
    }

    auto [addList, delList] = DataStorage::dailyComparsion(
        state->dataByDate,
        storage[number],
        state->startDate,
        state->finishDate
    );

    DataStorage::deleteRecords(number, delList);
    DataStorage::insertRecords(number, addList);

    if (!DataStorage::needBefore(storage[number], state->dataByDate)){
        qDebug() << "Need statement for number " << number
                 << "before date " << state->startDate;
    }

    if (!DataStorage::needAfter(storage[number], state->dataByDate)){
        qDebug() << "Need statement for number " << number
                 << "after date " << state->finishDate;
    }

    //write new statement
    DataStorage::recalc(
        storage[number], state->dataByDate,
        state->startDate, state->finishDate);
	delete state;
}

void DataCore::processBinary(int id, QByteArray * data){
    Statement * state = new Statement;
    auto result = state->init(data);
    delete data;
    if (!result){
        qDebug() << "Statement not init";
        delete state;
        return;
    }
    processStatement(state);
}

void DataCore::loadDataFromDB(){
    DataStorage::loadAccounts();
    // loadData();
}


// void DataCore::processStatement(Statement *state){
//     if (!storage.count(state->getAccountNumber())){
//         storage[state->getAccountNumber()] = state->dataByDate;
//         return ;
//     }
//     for(auto &date : state->dataByDate){

//     }
// }

//-----------------------------------PUBLIC------------------------------------

void DataCore::init(const QString & _s,const QString & _u,const QString & _p){
    if (!DataBase::connect(_s, _u, _p)){
        qDebug() << "DataCore::init - not connected";
        emit(DataBase::errorConnection());
        return;
    }
    DataStorage::createTables();
    DataStorage::insertStartData();
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










































