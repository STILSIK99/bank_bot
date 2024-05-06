#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QObject>
#include <QString>
#include <QDebug>

#include <vector>

#include "dc_variables.h"


class DataBase : public QObject{
    Q_OBJECT
    QString server, user, password;
    QSqlDatabase dataBase;

private:
    bool createDataBase();


public:
    bool connect(const QString &, const QString &, const QString &);
    bool isConnected();
    ~DataBase();

    //внесение изменений
    bool query(const QString &);

    //запрос данных
    bool query(const QString &, int col,
               std::vector<std::vector<QString>> &);
    void close();

signals:

    void errorConnection();
};
