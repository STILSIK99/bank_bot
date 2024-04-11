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

    long long start_sum = 0, finish_sum = 0, changes = 0;
    long long all_add = 0, all_minus = 0;
    std::list<const Record *> data;
    QDate date;

    DailyOperations(const QDate &);
    ~DailyOperations();

    void addRecord(const Record *);


};
