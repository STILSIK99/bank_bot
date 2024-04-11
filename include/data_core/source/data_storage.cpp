#include "data_storage.h"

//--------------------------------PUBLIC SLOTS---------------------------------

void DataStorage::processStatement(Statement *state){

}

//-----------------------------------PUBLIC------------------------------------

bool DataStorage::init(){
    // if (DataBase::)
}

DataStorage::~DataStorage(){
    if (DataBase::isConnected()) DataBase::close();
}

//----------------------------------PRIVATE------------------------------------
