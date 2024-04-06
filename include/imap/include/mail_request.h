#pragma once

#include <QString>

struct MailRequest{
    int id;
    QString request;

    MailRequest(int _id, const QString &_r)
        :id(_id), request(_r)
        {}

    MailRequest(const QString &_r):
        request(_r)
    {}

    QString toString(){
        return QString::number(id) + " " + request + "\r\n";
    }
};
