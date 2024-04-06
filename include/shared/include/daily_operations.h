#pragma once

#include <QDate>

#include <list>

#include "record.h"


struct DailyOperations{
    /*
     * Класс для работы с данными по операциям счёта
     * в рамках одного дня.
     *
     */

    long long start_sum, finish_sum;
    std::list<const Record *> data;
    QDate date;

    DailyOperations(const QDate &);
    ~DailyOperations();

    void addRecord(const Record *);


};
