#include "data_base.h"

//--------------------------------PUBLIC SLOTS---------------------------------

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
    qDebug() << "DataBase::query(QS)";
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
