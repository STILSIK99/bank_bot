#include "data_storage.h"
#include <QFile>

//--------------------------------PUBLIC SLOTS---------------------------------


//-----------------------------------PUBLIC------------------------------------

bool DataStorage::createTables(){
    for(auto table : DATABASE::REQUESTS::TABLES){
        if (!DataBase::query(table)){
            return false;
        }
    }
    return true;
}

void DataStorage::insertStartData(){
    for(auto insertion : DATABASE::REQUESTS::INSERTIONS){
        // qDebug() << insertion.toUtf8();
        // QTextCodec * codec1 = QTextCodec::codecForName("CP1251");
        // auto s = codec1->fromUnicode(insertion);
        DataBase::query(insertion);
    }

}

int DataStorage::insertAccountByNumber(const QString & number){
    std::vector<std::vector<QString>> result;
    if (DataBase::query(
            DATABASE::REQUESTS::INSERT_ACCOUNT_NUMBER.arg(number),
            1, result))
    {
        if (result.size() > 0) {
            if (result[0].size() > 0){
                return result[0][0].toInt();
            }
        }
    }
    qDebug() << "Error";
    return -1;
}


void DataStorage::loadAccounts(){
    std::vector<std::vector<QString>> result;
    if (DataBase::query(
            DATABASE::REQUESTS::SELECT_ACCOUNTS, 2, result
    )){
        for(auto &arr : result){
            accountsNumberId[arr[0]] = arr[1].toInt();
        }
    } else
        qDebug() << "Error";
}

void DataStorage::insertRecords(const QString & number,
                                std::list<const Record *> &data){
    int account = getAccount(number);
    for(auto el : data){
        if (!DataBase::query(el->buildInsert(account))){
            qDebug() << "Record not inserted.";
        };
    }
}

void DataStorage::deleteRecords(const QString & number,
                                std::list<const Record *> &data){
    int account = getAccount(number);
    for(auto el : data){
        if (!DataBase::query(el->buildDelete(account))){
            qDebug() << "Record not inserted.";
        };
    }
}

void DataStorage::recalc(const std::map<QDate, DailyOperations*> &master,
            std::map<QDate, DailyOperations*> &slave,
            const QDate &start, const QDate &finish)
{
    auto _start = start;
    for(;_start <= finish; _start = _start.addDays(1)){
        if (slave.count(_start)){
            delete slave[_start];
            slave.erase(_start);
        }
        if (master.count(_start)){
            slave[_start] = master.at(_start);
        }
    }
    if (master.size() == 0) return;
    auto sum = master.rbegin()->second->finish_sum;
    for(auto it = slave.upper_bound(finish); it != slave.end(); ++it){
        it->second->start_sum = sum;
        sum += it->second->changes;
        it->second->finish_sum = sum;
    }
}

std::pair<
    std::list<const Record *>,
    std::list<const Record *>
    > DataStorage::dailyComparsion(
    const std::map<QDate, DailyOperations *> & master,
    std::map<QDate, DailyOperations *> & slave,
    const QDate & start,
    const QDate & finish
    )
{
    std::list<const Record *> addList, delList;
    for(auto date = start; date <= finish; date = date.addDays(1)){
        if (!master.count(date)){
            if (slave.count(date)){
                auto _del = slave[date];
                delList.insert(delList.end(), _del->data.begin(), _del->data.end());
            }
        } else {
            if (!slave.count(date)){
                auto _add = master.at(date);
                addList.insert(addList.end(), _add->data.begin(), _add->data.end());
            } else {
                auto [_add, _del] = master.at(date)->getChanges(slave.at(date)->data);
                addList.insert(addList.end(), _add.begin(), _add.end());
                delList.insert(delList.end(), _del.begin(), _del.end());
            }
        }
    }
    return std::make_pair(addList, delList);
}

bool DataStorage::needBefore (dailys &slave, dailys &master){
    if (!master.size() || !slave.size()) {
        return true;
    }

    //master
    auto startSum = master.begin()->second->start_sum;
    auto startDate = master.begin()->first;

    //slave
    auto _start = slave.lower_bound(startDate);
    if (_start == slave.end()){
        //prev value
        return --_start->second->finish_sum == startSum;

    } else {
        return _start->second->start_sum == startSum;
    }
}

bool DataStorage::needAfter (dailys &slave, dailys &master){
    if (!master.size() || !slave.size()) {
        return true;
    }

    //master
    auto finishSum = master.rbegin()->second->start_sum;
    auto finishDate = master.rbegin()->first;

    //slave
    auto _finish = slave.upper_bound(finishDate);
    if (_finish == slave.begin()){
        //prev value
        return _finish->second->start_sum == finishSum;
    } else {
        return --_finish->second->finish_sum == finishSum;
    }
}


//----------------------------------PRIVATE------------------------------------

int DataStorage::getAccount(const QString & number){
    if (!accountsNumberId.count(number)){
        int accountId = DataStorage::insertAccountByNumber(number);
        if (accountId != -1)
            accountsNumberId[number] = accountId;
        else {
            qDebug() << "Error";
            return -1;
        }
    }
    return accountsNumberId[number];
}

