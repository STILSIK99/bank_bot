#include "imap_client.h"

//-----------------------------PUBLIC SLOTS-----------------------------

void IMAPClient::start(){
    // подключается к серверу
    Mail::slotConnectToServer();
    // авторизируется и получает список писем
    connectToServer();
}

void IMAPClient::fetchAllMessages(int count){
    // обработка входящего сигнала для загрузки писем
    for(int id = 1; id <= count; ++id){
        fetchMessage(id);
    }
}

void IMAPClient::connectToServer(){
    Mail::slotConnectToServer();
    emit(Mail::slotExecute(
        new MailRequest(
            POST_SERVER::COMMANDS::LOGIN.arg(
                Email::login, Email::password)
            )));
    emit(Mail::slotExecute(
        new MailRequest(
            POST_SERVER::COMMANDS::SELECT)));
}

void IMAPClient::parseReply(MailRequest * request, QString data){
    // обработчик ответов на запросы к почтовому серверу
    qDebug() << "IMAPClient::parseReply";
    auto lastLine = TOOLS::getLastLine(data);
    auto status = TOOLS::getWord(lastLine, 2);
    if (status != "OK"){
        //logger error
        qDebug() << "error";
        return ;
    }
    auto command = TOOLS::getWord(lastLine, 3);
    if (command == POST_SERVER::STRINGS::ACCESS){
        if (TOOLS::getWord(lastLine, 4) !=
            POST_SERVER::COMMAND_NAMES::SELECT){
            //logger error
            qDebug() << "error";
            return;
        }
        parseSelectMessage(data);
        // fetchAllMessages();
    }
    if (command == POST_SERVER::COMMAND_NAMES::FETCH){
        auto lastCommandWord = TOOLS::getWord(data, 4);
        if (lastCommandWord == POST_SERVER::STRINGS::FETCH_BODY){
            auto id = TOOLS::getWord(data, 2);
            if (!TOOLS::isDigit(id)){
                //logger error
                qDebug() << "error";
                return;
            }
            emit(saveBody(id.toInt(), data));
        }
        if (lastCommandWord == POST_SERVER::STRINGS::FETCH_HEADER){
            auto id = TOOLS::getWord(data, 2);
            if (!TOOLS::isDigit(id)){
                //logger error
                qDebug() << "error";
                return;
            }
            emit(saveHeader(id.toInt(), data));
        }
    }
    if (command.toLower() == POST_SERVER::STRINGS::COMPLETED){
        //may be set flag delete
    }
}

void IMAPClient::deleteAllSavedMessages(){
    emit(Mail::slotExecute(
        new MailRequest(
            POST_SERVER::COMMANDS::DELETE_MESSAGES)));
}

void IMAPClient::flagDeleteMessage(int id){
    emit(Mail::slotExecute(
        new MailRequest(
            POST_SERVER::COMMANDS::FLAGED_MESSAGE.arg(id))));
}

void IMAPClient::updateListMessages(){
    deleteAllSavedMessages();
    // emit(Mail::slotExecute(
    //     new MailRequest(
    //         POST_SERVER::COMMANDS::DELETE_MESSAGES)));
    emit(Mail::slotExecute(
        new MailRequest(
            POST_SERVER::COMMANDS::SELECT)));
}

// void IMAPClient::messageSaved(int id){
//     qDebug() << "SaveManager::messageSaved";
//     --id;
//     if (id < 0 || id >= saved.size()){
//         //logger error
//         qDebug() << "error";
//         return;
//     }
//     emit(IMAPClient::flagDelete(id));
//     if (countSaved == saved.size()){
//         emit(IMAPClient::allSaved());
//         setCount(0);
//     }
// }

// void IMAPClient::setMessageCount(int count){
//     qDebug() << "SaveManager::setMessageCount";
//     if (messageCount != 0){
//         //logger error
//         qDebug() << "error";
//         return;
//     }
//     setCount(count);
// }

//--------------------------------PUBLIC--------------------------------

IMAPClient::IMAPClient(
    const QString & _server, const QString & _login,
    const QString &_password): Mail(_server, _login, _password)
{
    connect(this, &Mail::getReply, this, &IMAPClient::parseReply);
    connect(this, &IMAPClient::flagDelete,
            this, &IMAPClient::flagDeleteMessage);
    connect(this, &IMAPClient::allSaved,
            this, &IMAPClient::deleteAllSavedMessages);
}

//-------------------------------PRIVATE--------------------------------

void IMAPClient::fetchMessage(int id){
    // генерирует запросы на загрузку письма по номеру в почтовом ящике
    emit(Mail::slotExecute(
        new MailRequest(
            POST_SERVER::COMMANDS::FETCH_HEADER.arg(id))));
    emit(Mail::slotExecute(
        new MailRequest(
            POST_SERVER::COMMANDS::FETCH_BODY.arg(id))));


}

void IMAPClient::parseSelectMessage(const QString & text){
    // извлекает информацию о кол-ве писем на почтовом сервере
    qDebug() << "IMAPClient::parseSelectMessage";
    auto lines = text.split("\r\n");
    qDebug() << lines[1];
    auto count = TOOLS::getWord(lines[1], 2);
    if (!TOOLS::isDigit(count)){
        //logger error
        qDebug() << "error";
        return;
    }
    emit(messageCount(count.toInt()));
}

// void IMAPClient::setCount(int count){
//     messageCount = count;
//     saved = std::vector<bool>(count, false);
//     countSaved = count;
// }
