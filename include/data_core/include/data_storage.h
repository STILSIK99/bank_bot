#pragma once
#include "data_base.h"
#include "statement.h"
#include <vector>
#include "tools.h"

class DataStorage : public DataBase{
    Q_OBJECT

private:


public:

    static std::vector<QString> fields;
    void initFields();
    bool createTables();
    void insertStartData();

public slots:


signals:

};
