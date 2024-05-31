#include "bot_app.h"


//---------------------------------PUBLIC SLOTS--------------------------------

void BotApp::errorDatabaseConnection(){
    qDebug() << "Error database connection";
}

void BotApp::start(){
    emit(startProcess());
    timer->start(period);
}


//-----------------------------------PUBLIC------------------------------------

bool BotApp::init(){

    // if (!tests()){
    //     return false;
    // }

    int threadMaxCount = QThread::idealThreadCount() / 2;

    if (!initConfig()) return false;
    auto dataThread = initDatabase();
    connect(this, &BotApp::dataInit, dc, &DataCore::loadDataFromDB);
    emit(dataInit());
    // if (!initDatabase()) return false;

    int currentThread = 0;
    QString saveDir = cfg->getSaveDir();

    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &BotApp::start);

    for(auto& account : cfg->getListEmails()){
        IMAPClient * imap = new IMAPClient(
            account->server,
            account->login,
            account->password);
        imap->connectToServer();

        FileCore * fc = new FileCore(currentThread);
        fc->init(QString("%1/%2").arg(saveDir, account->login));

        ParserCore * pc = new ParserCore();

        ControlCore * cc = new ControlCore();

        connect(this, &BotApp::startProcess, cc, &ControlCore::startImap);
        connect(cc, &ControlCore::updateListMessages, imap, &IMAPClient::updateListMessages);
        connect(cc, &ControlCore::getMessages, imap, &IMAPClient::fetchAllMessages);
        connect(imap, &IMAPClient::messageCount, cc, &ControlCore::getMessageCount);
        connect(imap, &IMAPClient::saveBody, pc, &ParserCore::parseApplication);
        connect(imap, &IMAPClient::saveHeader, cc, &ControlCore::getHeader);
        connect(pc, &ParserCore::downloadHttp, fc, &FileCore::downloadFromUrl);

        connect(fc, &FileCore::parseFile, pc, &ParserCore::parseFile); // after unzip
        connect(fc, &FileCore::downloadError, cc, &ControlCore::notSaved);

        connect(fc, &FileCore::saved, cc, &ControlCore::saved);
        connect(cc, &ControlCore::saveHeader, fc, &FileCore::saveHeader);

        connect(cc, &ControlCore::deleteMessage, imap, &IMAPClient::flagDeleteMessage);
        connect(pc, &ParserCore::saveFile, fc, &FileCore::saveBytes2File);
        connect(pc, &ParserCore::notFound, cc, &ControlCore::notFound);

        connect(fc, &FileCore::process, dc, &DataCore::processBinary);
        connect(pc, &ParserCore::processStatement, dc, &DataCore::processStatement);

        QThread * thr;
        if (currentThread < threadMaxCount){
            thr = new QThread();
            threads.emplace_back(thr);
            thr->start();
        } else {
            thr = threads[currentThread % threadMaxCount];
        }

        imap->moveToThread(thr);
        fc->moveToThread(thr);
        pc->moveToThread(thr);
        cc->moveToThread(thr);

        ++currentThread;
    }

    threads.emplace_back(dataThread);

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
        period = cfg->getPeriod();
    } catch (std::exception e){
        qDebug() << e.what();
        delete cfg;
        return false;
    }
    return true;
}

QThread* BotApp::initDatabase(){
    auto connector = cfg->getDatabase();
    if (!dc) dc = new DataCore();
    auto thr = new QThread();
    dc->moveToThread(thr);
    thr->start();
    connect(this, &BotApp::startDatabase, dc, &DataCore::init);
    connect(dc, &DataBase::errorConnection,this, &BotApp::errorDatabaseConnection);
    emit(startDatabase(connector[0], connector[1], connector[2]));
    return thr;
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
    if (dc) delete dc;
    if (timer) delete timer;
}
