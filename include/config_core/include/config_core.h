#pragma once

#include "config.h"
#include <vector>


class ConfigCore : public Config{

private:


public:
    ConfigCore(const QString &);
    const std::list<MailAccount *>& getListEmails();

    std::vector<QString> getDatabase();

    QString getSaveDir();

public slots:


};
