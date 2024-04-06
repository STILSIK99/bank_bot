#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QString>
#include <QDebug>

#include <vector>

#include "dc_variables.h"


class DataBase : public QObject{
    Q_OBJECT
    QString server, user, password;
    QSqlDatabase *dataBase;

private:
    bool createDataBase();


public:
    bool connect(const QString &, const QString &, const QString &);


public slots:

    //внесение изменений
    void query(const QString &);

    //запрос данных
    void query(const QString &, int col,
               std::vector<std::vector<QString>> &);
    // void close();

signals:


};
