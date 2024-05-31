#pragma once
#include "data_storage.h"
#include "daily_operations.h"


class DataCore : public DataStorage{
    Q_OBJECT

private:

    void addRecords(std::list<const Record *> &, const QString &);
    void delRecords(std::list<const Record *> &, const QString &);
    void exctractStartProperties(Statement *, QString &, QString &);

public:

    DataCore();
    ~DataCore() override;
    void test();



public slots:

    void init(const QString &, const QString &, const QString &);
    void processBinary(int, QByteArray *); // id_thread, data
    void processStatement(Statement *);

    void loadDataFromDB();

signals:

};
