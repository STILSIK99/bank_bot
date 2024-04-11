#include "daily_operations.h"


//-----------------------------------PUBLIC------------------------------------

DailyOperations::DailyOperations(const QDate & d){
    date = d;
    start_sum = finish_sum = changes = all_add = all_minus = 0;
}


void DailyOperations::addRecord(const Record * record){
    data.emplace_back(record);
    auto sum = record->getSum();
    changes += record->getSum();
    if (sum > 0) all_add += sum;
    else all_minus += sum;
}

DailyOperations::~DailyOperations(){
    for(auto el : data){
        delete el;
    }
}
