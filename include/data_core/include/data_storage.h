#pragma once
#include "data_base.h"
#include "statement.h"
#include <vector>
#include "tools.h"

using Dailys = std::map<QDate, DailyOperations *>;
using Changes = std::pair<std::list<const Record *>,std::list<const Record *>>;

class DataStorage : public DataBase{
    Q_OBJECT

private:
    void updateStartSums();

public:
    static std::vector<QString> fields;
    void initFields();
    bool createTables();
    void insertStartData();

    int insertAccountByNumber(const QString &);
    void deleteRecords(const int, std::list<const Record *> &);
    void insertRecords(const int, std::list<const Record *> &);
    void updateStartSum(const int, const QString &, const QString &);

    static void recalc(const Dailys &slave,
                Dailys &master,
                const QDate &start, const QDate &finish);

    static Changes dailyComparsion(const Dailys & master,
        Dailys & slave,const QDate & start, const QDate & finish);

    bool needBefore (Dailys &slave, Dailys &master);    //slave - data in storage
    bool needAfter (Dailys &slave, Dailys &master);     //master - data in statement

protected:
    int getAccount(const QString &);
    std::map<int, std::map<QDate, DailyOperations*> > storage;
    std::unordered_map<QString, int> accountsNumberId;
    std::map<int, std::pair<QDate, long long>> startSumsId;
    void loadAccounts();
    void loadStartSums();
    void loadDailyOperations();

public slots:


signals:

};
