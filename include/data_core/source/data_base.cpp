#include "data_base.h"

//--------------------------------PUBLIC SLOTS---------------------------------

bool DataBase::mappedRecordQuery(
    const QString &request,
    const std::vector<QString> &fields,
    const std::vector<bool> &isDate,
    std::map<int, std::map<QDate, DailyOperations*> > & data)
{
    qDebug() << "DataBase::mappedQuery(QS)";
    QSqlQuery sql;
    if (!sql.exec(request)){
        qDebug() << sql.lastError().text();
        qDebug() << request;
        return false;
    }
    if (!sql.first()) return true;
    do{
        auto record = readRecord(sql);
        int accountId = sql.value(0).toInt();
        if (!data.count(accountId)){
            data[accountId] = std::map<QDate, DailyOperations*>();
        }
        auto &daily = data[accountId];
        auto date = record->getOperationDate();
        if (!daily.count(date)){
            daily[date] = new DailyOperations(date);
        }
        daily[date]->addRecord(record);
    } while(sql.next());
    return true;
}

bool DataBase::query(const QString & request){ //внесение изменений
    qDebug() << "DataBase::query(QS)";
    QSqlQuery sql;
    if (!sql.exec(request)){
        qDebug() << sql.lastError().text();
        qDebug() << request;
        return false;
    }
    return true;
}

bool DataBase::query(const QString & request, int col,
        std::vector<std::vector<QString>> &result)
{
    qDebug() << "DataBase::query(QS, int, vector)";
    result.clear();
    result.shrink_to_fit();
    QSqlQuery sql;
    if (!sql.exec(request)){
        qDebug() << sql.lastError().text();
        qDebug() << request;
        return false;
    }
    if (!sql.first()) return true;
    static int row;
    row = 0;
    do {
        result.emplace_back(std::vector<QString>(col));
        for(int i = 0; i < col; ++i){
            result[row][i] = sql.value(i).toString();
        }
        ++row;
    }while (sql.next());
    return true;
}

void DataBase::close(){
    dataBase.close();
}

//-----------------------------------PUBLIC------------------------------------

bool DataBase::connect(const QString & _server, const QString & _user, const QString & _pass){
    QSqlDatabase db = QSqlDatabase::addDatabase(DATABASE::DRIVER);
    db.setHostName(_server);
    db.setDatabaseName(DATABASE::DATABASE_NAME);
    db.setUserName(_user);
    db.setPassword(_pass);
    if (db.open()){
        close();
        dataBase = db;
        server = _server, user = _user, password = _pass;
        query("SET NAMES 'CP1251';");
        return true;
    } else {
        qDebug() << db.lastError();
    }
    return false;
}

bool DataBase::isConnected(){
    return dataBase.isOpen();
}

DataBase::~DataBase(){
    if (isConnected()) close();
}

//----------------------------------PRIVATE------------------------------------

bool DataBase::createDataBase(){
    QSqlQuery request(QSqlDatabase::database());
    return request.exec(
            DATABASE::REQUESTS::CREATE_DATABASE.arg(DATABASE::DATABASE_NAME)
        );
}

Record* DataBase::readRecord(QSqlQuery &sql)
{
    // int accountId = sql.value(0).toInt();
    long long sum = TOOLS::exctractSum(sql.value(DATABASE::POSITIONS::OPERATION_SUM).toString());
    bool direction = (sum >= 0);

    auto data = new std::map<QString, QString>();
    //add DATE
    if (direction) {
        data->insert({
            DATABASE::FIELDS[5], //dc_variables.h
            sql.value(DATABASE::POSITIONS::INPUT_DATE
                               ).toDate().toString("dd.MM.yyyy")
        });
    } else {
        data->insert({
            DATABASE::FIELDS[6], //dc_variables.h
            sql.value(DATABASE::POSITIONS::OUTPUT_DATE
                      ).toDate().toString("dd.MM.yyyy")
        });
    }
    //add SUM
    data->insert({
        DATABASE::FIELDS[47], //dc_variables.h
        sql.value(DATABASE::POSITIONS::OPERATION_SUM).toString()
    });
    auto record = new Record(data, direction);
    //add HASHES
    record->hash_1 = HashSum(
        sql.value(DATABASE::POSITIONS::HASH_1_1).toULongLong(),
        sql.value(DATABASE::POSITIONS::HASH_1_2).toULongLong());
    record->hash_2 = HashSum(
        sql.value(DATABASE::POSITIONS::HASH_2_1).toULongLong(),
        sql.value(DATABASE::POSITIONS::HASH_2_2).toULongLong());

    return record;
}

