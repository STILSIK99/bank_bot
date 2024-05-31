#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QDate>
#include <vector>

#include "dc_variables.h"
#include "daily_operations.h"

#include <utility>

class DataBase : public QObject{
    Q_OBJECT
    QString server, user, password;
    QSqlDatabase dataBase;

private:
    bool createDataBase();
    Record* readRecord(QSqlQuery &);

public:
    bool connect(const QString &, const QString &, const QString &);
    bool isConnected();
    ~DataBase();

    //внесение изменений
    bool query(const QString &);

    //запрос данных
    bool query(const QString &, int col,
               std::vector<std::vector<QString>> &);
    bool mappedRecordQuery(
        const QString &,
        const std::vector<QString> &fields,
        const std::vector<bool> &isDate,
        std::map<int, std::map<QDate, DailyOperations*> > & data
        );

    void close();

signals:

    void errorConnection();
};
