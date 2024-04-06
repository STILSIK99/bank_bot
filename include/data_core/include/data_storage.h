#pragma once
#include "data_base.h"
#include "statement.h"

class DataStorage : public DataBase{
    Q_OBJECT

private:


public:

    bool init();

public slots:

    // void readFull();
    // void addOperation();
    // void delOperation();
    void processStatement(Statement *);


signals:

};
