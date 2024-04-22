#include "bot_app.h"


//---------------------------------PUBLIC SLOTS--------------------------------



//-----------------------------------PUBLIC------------------------------------

bool BotApp::init(){

    // if (!tests()){
    //     return false;
    // }

    int threadCount = QThread::idealThreadCount() / 2;

    if (!initConfig()) return false;
    if (!initDatabase()) return false;

    int currentThread = 0;
    QString saveDir = cfg->getSaveDir();

    for(auto& account : cfg->getListEmails()){
        IMAPClient * imap = new IMAPClient(
            account->server,
            account->login,
            account->password);

        FileCore * fc = new FileCore();
        fc->init(QString("%1/%2").arg(saveDir, account->login));



        currentThread = (currentThread + 1) % threadCount;
    }


    return true;
}

bool BotApp::tests(){

    if (TEST::testParseStatement()){
        qDebug() << "OK";
    } else {
        qDebug() << "TEST::testParseStatement is failed.";
        return false;
    }

    if (TEST::testDataBaseConnection()){
        qDebug() << "OK";
    } else {
        qDebug() << "TEST::testDataBaseConnection is failed.";
        return false;
    }

    if (TEST::testConfig()){
        qDebug() << "OK";
    } else {
        qDebug() << "TEST::testConfig is failed.";
        return false;
    }
    return true;
}

//----------------------------------PRIVATE------------------------------------

bool BotApp::initConfig(){
    if (cfg) delete cfg;
    cfg = new ConfigCore(CONFIG::PATH);
    try{
        cfg->parseConfig();
    } catch (std::exception e){
        qDebug() << e.what();
        delete cfg;
        return false;
    }
    return true;
}

bool BotApp::initDatabase(){
    auto connector = cfg->getDatabase();
    qDebug() << "DB from config";
    for(auto el : connector){
        qDebug() << el ;
    }
    if (!db) db = new DataCore();
    auto thr = new QThread();
    db->moveToThread(thr);
    thr->start();
    return db->init(connector[0], connector[1], connector[2]);
}

BotApp::~BotApp(){
    for(auto thr : threads){
        thr->terminate();
    }
    for(auto arr : sessions){
        if (std::get<1>(arr)) delete std::get<0> (arr);
        if (std::get<1>(arr)) delete std::get<1>(arr);
        if (std::get<2>(arr)) delete std::get<2>(arr);
        if (std::get<3>(arr)) delete std::get<3>(arr);
    }

    if (cfg) delete cfg;
    if (db) delete db;
}
