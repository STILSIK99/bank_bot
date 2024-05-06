#pragma once
#include "data_base.h"
#include "statement.h"
#include <vector>
#include "tools.h"

using dailys = std::map<QDate, DailyOperations *>;

class DataStorage : public DataBase{
    Q_OBJECT

private:
    std::unordered_map<QString, int> accountsNumberId;
    int getAccount(const QString &);


public:


    static std::vector<QString> fields;
    void initFields();
    bool createTables();
    void insertStartData();

    int insertAccountByNumber(const QString &);
    void deleteRecords(const QString &, std::list<const Record *> &);
    void insertRecords(const QString &, std::list<const Record *> &);

    static void recalc(const dailys &slave,
                dailys &master,
                const QDate &start, const QDate &finish);

    static std::pair<
        std::list<const Record *>,
        std::list<const Record *>
        > dailyComparsion(
        const dailys & master,
        dailys & slave,
        const QDate & start, const QDate & finish
        );

    bool needBefore (dailys &slave, dailys &master);    //slave - data in storage
    bool needAfter (dailys &slave, dailys &master);     //master - data in statement

protected:
    void loadAccounts();

public slots:


signals:

};
