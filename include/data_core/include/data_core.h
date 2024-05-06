#pragma once
#include "data_storage.h"
#include "daily_operations.h"


class DataCore : public DataStorage{
    Q_OBJECT

private:
    std::map<QString, std::map<QDate, DailyOperations*> > storage;
    void addRecords(std::list<const Record *> &, const QString &);
    void delRecords(std::list<const Record *> &, const QString &);

    std::unordered_map<QString, int> accountsNumberId;

public:

    DataCore();
    ~DataCore() override;
    void test();



public slots:

    void init(const QString &, const QString &, const QString &);
    // void readFull();
    // void addOperation();
    // void delOperation();
    void processBinary(int, QByteArray *); // id_thread, data
    void processStatement(Statement *);

    void loadDataFromDB();

signals:

};
