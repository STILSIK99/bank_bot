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

std::pair<
    std::list<const Record *>,
    std::list<const Record *>
> DailyOperations::getChanges(const std::list<const Record *> & old){
    //merge records
    //this->data - master data
    //old - slave data
    QHash<std::pair<QString, QString>, std::list<const Record *>> buffer;
    for(auto record : this->data){
        auto p = std::make_pair(
            record->hash_1.getFirst() + record->hash_1.getSecond(),
            record->hash_2.getFirst() + record->hash_2.getSecond());
        if (!buffer.contains(p)){
            buffer[p] = {record};
        } else {
            buffer[p].emplace_back(record);
        }
    }
    std::list<const Record *> addList, delList;
    for(auto record : old){
        auto p = std::make_pair(
            record->hash_1.getFirst() + record->hash_1.getSecond(),
            record->hash_2.getFirst() + record->hash_2.getSecond());
        if (!buffer.contains(p)){
            delList.emplace_back(record);
        } else {
            auto _list = buffer[p];
            _list.pop_back();
            if (_list.size() == 0){
                buffer.remove(p);
            }
        }

    }

    for(auto _list : buffer){
        addList.insert(addList.end(), _list.begin(), _list.end());
    }

    return make_pair(addList, delList);
}
