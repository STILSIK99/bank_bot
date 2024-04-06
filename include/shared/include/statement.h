#pragma once
#include <QByteArray>
#include <QString>
#include <QTextCodec>
#include <QDebug>

#include <map>

#include "record.h"
#include "exceptions.h"
#include "tools.h"
#include "daily_operations.h"

namespace STATEMENTS{
/*
         */
const QString SPLITTER = "\r\n";

const QString FILE_START = "1CClientBankExchange";
const QString FILE_VERSION = "ВерсияФормата=1.03";
const QString FILE_FINISH = "КонецФайла";

const QString ACCOUNT_START = "СекцияРасчСчет";
const QString ACCOUNT_FINISH = "КонецРасчСчет";

const QString RECORD_START = "СекцияДокумент";
const QString RECORD_FINISH = "КонецДокумента";

const QString ACCOUNT_NUMBER = "РасчСчет";

const QString DATE_START = "ДатаНачала";
const QString DATE_FINISH = "ДатаКонца";

// std::vector<QString> FIELDS{};

};


class Statement{
    /*
     * Класс для обработки файла выписки.
     * Распределяет операции по дням.
     *
     */
    std::map<QDate, DailyOperations *> dataByDate;
    std::map<QString, QString> *fields;

    std::pair<QString, QString> toPair(QString &);
    int readBlock(int, QStringList&, const QString&);



public:
    Statement();
    ~Statement();
    QString getAccountNumber();
    static QString* convertCodec(QByteArray *);

    bool init(QByteArray *);
};
