#include "data_storage.h"
#include <QFile>

//--------------------------------PUBLIC SLOTS---------------------------------


//-----------------------------------PUBLIC------------------------------------

void DataStorage::updateStartSum(const int accountId, const QString & sum, const QString & date){
    if (!DataBase::query(
            DATABASE::REQUESTS::UPDATE_START_SUM.arg(
                QString::number(accountId), sum, date))){
        qDebug() <<
            QString(
                "StartSum not updated for "
                "number %1, date %2, sum %3"
            ).arg(QString::number(accountId), date, sum);
    }
}

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
        DataBase::query(insertion);
    }

}

int DataStorage::insertAccountByNumber(const QString & number)
{
    std::vector<std::vector<QString>> result;
    if (DataBase::query(
            DATABASE::REQUESTS::INSERT_ACCOUNT_NUMBER.arg(number),
            1, result))
    {
        if (result.size() > 0) {
            if (result[0].size() > 0){
                if (!DataBase::query(
                        DATABASE::REQUESTS::INSERT_START_SUM.arg(result[0][0]))){
                    qDebug() << "StartSum not inserted for number " << number;
                }
                return result[0][0].toInt();
            }
        }
    }
    qDebug() << "Error";
    return -1;
}

void DataStorage::insertRecords(const int accountId,
        std::list<const Record *> &data)
{
    for(auto el : data){
        if (!DataBase::query(el->buildInsert(accountId))){
            qDebug() << "Record not inserted.";
        };
    }
}

void DataStorage::deleteRecords(const int accountId,
        std::list<const Record *> &data)
{
    for(auto el : data){
        if (!DataBase::query(el->buildDelete(accountId))){
            qDebug() << "Record not inserted.";
        };
    }
}

void DataStorage::recalc(const Dailys &master, Dailys &slave,
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

Changes DataStorage::dailyComparsion(
    const Dailys & master, Dailys & slave,
    const QDate & start, const QDate & finish)
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

bool DataStorage::needBefore (Dailys &slave, Dailys &master){
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
        return (--_start)->second->finish_sum == startSum;

    } else {
        return _start->second->start_sum == startSum;
    }
}

bool DataStorage::needAfter (Dailys &slave, Dailys &master){
    if (!master.size() || !slave.size()) {
        return true;
    }

    //master
    auto finishSum = master.rbegin()->second->finish_sum;
    auto finishDate = master.rbegin()->first;

    //slave
    auto _finish = slave.upper_bound(finishDate);
    if (_finish == slave.begin()){
        //prev value
        return _finish->second->start_sum != finishSum;
    } else {
        return (--_finish)->second->finish_sum != finishSum;
    }
}


//----------------------------------PRIVATE------------------------------------
void DataStorage::updateStartSums(){
    for(const auto &_p : startSumsId){
        auto [accountId, sumAndDate] = _p;
        auto [date, sum] = sumAndDate;
        if (!storage.count(accountId)) continue;
        auto &accountStorage = storage[accountId];
        auto finish_sum = sum;

        if (accountStorage.size() == 0){
            accountStorage[date] = new DailyOperations(date);
            accountStorage[date]->addStartSum(sum);
            continue;
        } else if (accountStorage.begin()->first < date){
            // date in start and date in dailys no match
            auto it = accountStorage.lower_bound(date);
            auto finish_sum = sum;
            do{
                --it;
                if (!it->second) continue;
                it->second->setFinishSum(sum);
                finish_sum = it->second->start_sum;
            } while (it != accountStorage.begin());
        }
        // date in start and date in dailys match

        for(auto &_d : accountStorage){
            if (_d.second){
                _d.second->addStartSum(finish_sum);
                finish_sum = _d.second->finish_sum;
            }
        }
    }
}

//---------------------------------PROTECTED------------------------------------
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

void DataStorage::loadAccounts(){
    accountsNumberId.clear();
    std::vector<std::vector<QString>> result;
    if (DataBase::query(
            DATABASE::REQUESTS::SELECT_ACCOUNTS, 2, result
            )){
        for(auto &arr : result){
            accountsNumberId[arr[0]] = arr[1].toInt();
        }
    } else
        qDebug() << "Account ids not initialized.";
}

void DataStorage::loadStartSums(){
    startSumsId.clear();
    std::vector<std::vector<QString>> result;
    if (DataBase::query(
            DATABASE::REQUESTS::SELECT_START_SUMS, 3, result
            )){
        for(auto &arr : result){
            //arr -> {id, sum, date}
            startSumsId[arr[0].toInt()] = {
                TOOLS::extractDateFromDataBase(arr[2]),
                TOOLS::exctractSum(arr[1])
            };
        }
    } else
        qDebug() << "StartSums not initialized.";
}

void DataStorage::loadDailyOperations(){
    storage.clear();
    if (!DataBase::mappedRecordQuery(
            DATABASE::REQUESTS::SELECT_DAILY_OPERATIONS,
            DATABASE::FIELDS,
            DATABASE::IS_DATE_FIELD,
            storage
        ))
    {
        qDebug() << "Daily operations not initialized.";
        return ;
    }
    updateStartSums();
}
