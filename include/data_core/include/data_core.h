#pragma once
#include "data_storage.h"
#include "daily_operations.h"


class DataCore : public DataStorage{
    Q_OBJECT

private:
    std::map<QString, std::map<QDate, DailyOperations*>> storage;

public:

    bool init(const QString &, const QString &, const QString &);
    ~DataCore() override;
    void test();

public slots:

    // void readFull();
    // void addOperation();
    // void delOperation();
    void processStatement(Statement *);

signals:

};
