#include "daily_operations.h"


//-----------------------------------PUBLIC------------------------------------

DailyOperations::DailyOperations(const QDate & d){
    date = d;
}


void DailyOperations::addRecord(const Record * record){
    data.emplace_back(record);
}

DailyOperations::~DailyOperations(){
    for(auto el : data){
        delete el;
    }
}
