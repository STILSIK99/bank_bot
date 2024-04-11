#pragma once
#include <QString>

#include <map>
#include <vector>

namespace CONFIG{
/*
 *
 */
const QString MAIL = "IMAP";
const QString DATABASE = "Database";

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
    {MAIL, {
               INCLUDE,
               REQUESTDELAY}
    },
    {DATABASE, {
                   DB::DRIVER,
                   CONNECTION::SERVER,
                   CONNECTION::LOGIN,
                   CONNECTION::PASSWORD,
                   DB::DATABASE_NAME}
    },
};


}
