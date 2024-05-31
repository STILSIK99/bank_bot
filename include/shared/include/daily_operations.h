#pragma once

#include <QDate>

#include <list>
#include <QHash>

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
    void addStartSum(const long long);
    void setFinishSum(const long long);

    std::pair<
        std::list<const Record *>,
        std::list<const Record *>
    > getChanges(const std::list<const Record *> &);

};
