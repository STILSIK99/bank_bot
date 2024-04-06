#include "data_base.h"

//--------------------------------PUBLIC SLOTS---------------------------------

void DataBase::query(const QString & request){ //внесение изменений
    qDebug() << "DataBase::query(QS)";
    QSqlQuery sql;
    if (!sql.exec(request)){
        qDebug() << sql.lastError().text();
        qDebug() << sql.executedQuery();
    }
}

void DataBase::query(const QString & request, int col,
        std::vector<std::vector<QString>> &result)
{
    qDebug() << "DataBase::query(QS)";
    result.clear();
    result.shrink_to_fit();
    QSqlQuery sql;
    if (!sql.exec(request)){
        qDebug() << sql.lastError().text();
        qDebug() << sql.executedQuery();
    }
    if (!sql.first()) return ;
    static int row;
    row = 0;
    do {
        result.emplace_back(std::vector<QString>(col));
        for(int i = 0; i < col; ++i){
            result[row][i] = sql.value(i).toString();
        }
        ++row;
    }while (sql.next());
}


//-----------------------------------PUBLIC------------------------------------

bool DataBase::connect(const QString & _server, const QString & _user, const QString & _pass){
    bool result = false;
    dataBase->addDatabase(DATABASE::DRIVER);
    dataBase->setHostName(_server);
    // setDatabaseName();
    dataBase->setUserName(_user);
    dataBase->setPassword(_pass);
    if (dataBase->open()){
        result = createDataBase();
    }
    if (result){
        server = _server, user = _user, password = _pass;
    }
    return result;
    //возможно нужно setDatabaseName
}

//----------------------------------PRIVATE------------------------------------

bool DataBase::createDataBase(){
    QSqlQuery request(QSqlDatabase::database());
    return request.exec(
            DATABASE::REQUESTS::CREATE_DATABASE.arg(DATABASE::DATABASE_NAME)
        );
}
