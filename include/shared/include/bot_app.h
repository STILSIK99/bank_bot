#pragma once

#include <QObject>
#include <QThread>
#include <QDateTime>
#include <QTimer>

#include <set>
#include <utility>

#include "control_core.h"
#include "config_core.h"
#include "data_core.h"
#include "file_core.h"
#include "imap_client.h"
#include "parser_core.h"
#include "test.h"




class BotApp : public QObject{
    Q_OBJECT


private:

    ConfigCore *cfg;
    DataCore *dc;
    QTimer *timer;
    int period;


    bool initConfig();
    QThread* initDatabase();
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
    void start();
    void errorDatabaseConnection();

signals:
    void startDatabase(const QString &, const QString &,const QString &);
    void startProcess();
    void dataInit();
};
