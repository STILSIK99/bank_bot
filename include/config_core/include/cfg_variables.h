#pragma once
#include <QString>

#include <map>
#include <vector>

namespace CONFIG{
/*
 *
 */
    namespace SECTIONS{
        const QString MAIL = "IMAP";
        const QString DATABASE = "Database";
    }
    const QString PATH = "E:/C++/QT/bank_bot/bank_bot/src/config.json";

    namespace CONNECTION{
        const QString SERVER = "server";
        const QString LOGIN = "login";
        const QString PASSWORD = "password";

        const std::vector<QString> ALL {SERVER, LOGIN, PASSWORD};
    }

    //imap
    const QString REQUESTDELAY = "requestDelay";
    const QString INCLUDE = "include";
    const QString SAVEDIR = "saveMailDir";

    //database
    namespace DB {
        const QString DRIVER = "driver";
        const QString DATABASE_NAME = "database";
    }
    const std::map<QString, std::vector<QString>> FIELDS = {
        {SECTIONS::MAIL, {
                   INCLUDE,
                   REQUESTDELAY,
                   SAVEDIR}
        },
        {SECTIONS::DATABASE, {
                       DB::DRIVER,
                       CONNECTION::SERVER,
                       CONNECTION::LOGIN,
                       CONNECTION::PASSWORD,
                       DB::DATABASE_NAME
        }
    },
};


}
