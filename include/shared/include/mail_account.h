#pragma once

#include <QString>
#include <QJsonObject>

#include "cfg_variables.h"
#include "tools.h"

struct MailAccount{
    /*
     * Структура для работы с учетными данными почты
     */

    QString server;
    QString login;
    QString password;

    MailAccount(const QJsonObject & obj){
        if (TOOLS::compareObjects(obj, CONFIG::CONNECTION::ALL)){
            server = obj[CONFIG::CONNECTION::SERVER].toString();
            login = obj[CONFIG::CONNECTION::LOGIN].toString();
            password = obj[CONFIG::CONNECTION::PASSWORD].toString();
        }
    }

    MailAccount(const QString & _s, const QString &_l, const QString &_p)
        : server(_s), login(_l), password(_p){}

    ~MailAccount(){}
};
