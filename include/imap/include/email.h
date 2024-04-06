#pragma once

#include <QString>

struct Email{
    QString server, login, password;

    Email(const QString &s, const QString &l, const QString &p)
        : server(s), login(l), password(p){};
};
