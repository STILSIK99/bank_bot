#include "data_core.h"

//--------------------------------PUBLIC SLOTS---------------------------------
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

//-----------------------------------PUBLIC------------------------------------
DataCore::DataCore(){

}

void DataCore::processStatement(Statement * state){
    QString number = state->getAccountNumber();
    int accountId = DataStorage::getAccount(number);
    if (!storage.count(accountId)){
        storage[accountId] = std::map<QDate, DailyOperations *>();
    }

    QString startSum = "0.00", startDate = "9999-12-31";
    exctractStartProperties(state, startSum, startDate);
    DataStorage::updateStartSum(accountId, startSum, startDate);

    auto [addList, delList] = DataStorage::dailyComparsion(
        state->dataByDate,
        storage[accountId],
        state->startDate,
        state->finishDate
    );


    DataStorage::deleteRecords(accountId, delList);
    DataStorage::insertRecords(accountId, addList);

    if (!DataStorage::needBefore(storage[accountId], state->dataByDate)){
        qDebug() << "Need statement for number " << number
                 << "before date " << state->startDate;
    }

    if (!DataStorage::needAfter(storage[accountId], state->dataByDate)){
        qDebug() << "Need statement for number " << number
                 << "after date " << state->finishDate;
    }

    //write new statement
    DataStorage::recalc(
        state->dataByDate, storage[accountId],
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
    DataStorage::loadStartSums();
    DataStorage::loadDailyOperations();
}

//----------------------------------PRIVATE------------------------------------

void DataCore::exctractStartProperties(Statement * state,
        QString & sum, QString & date)
{
    if (!state) return;
    sum = state->getStartSum();
    date = state->getStartDate();
}







































