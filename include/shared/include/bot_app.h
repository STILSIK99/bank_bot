#pragma once

#include <QObject>
#include <QThread>

#include "config_core.h"
#include "control_core.h"
#include "data_core.h"
#include "file_core.h"
#include "imap_client.h"
#include "parser_core.h"
#include "test.h"




class BotApp : public QObject{
    Q_OBJECT


private:

    ConfigCore *cfg;
    DataCore *db;

    bool initConfig();
    bool initDatabase();
    std::vector<QThread*> threads;
    std::vector<
        std::tuple<
            IMAPClient*,
            FileCore*,
            ControlCore*,
            ParserCore*
    >> sessions;

public:
    bool tests();
    bool init();
    ~BotApp();

public slots:


signals:


};
