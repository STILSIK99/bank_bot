#pragma once
#include <QString>
#include <list>

namespace DATABASE{

    const std::list<QString> TABLES = {
        "",
        "",
        ""
    };

    namespace REQUESTS{
        const QString INSERT = "";
        const QString DELETE = "";
        const QString SELECT = "";
        const QString CREATE_DATABASE = "CREATE DATABASE IF NOT EXISTS %1";
        };

    const QString DRIVER = "QMYSQL";
    const QString DATABASE_NAME = "bank_bot";

    };
