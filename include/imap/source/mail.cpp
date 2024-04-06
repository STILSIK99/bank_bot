#include "mail.h"

//-----------------------------PUBLIC SLOTS-----------------------------

void Mail::slotExecute(MailRequest * request){
    if (!request) return;
    request->id = ++commandId;
    commandQue.emplace_back(request);
    executeNext();
}

void Mail::slotGetReply(QString partReply){
    qDebug() << "Mail::slotGetReply";
    reply += partReply;
    if ((!isLastLine(reply)) && (currentRequest->id)) return;
    commandQue.pop_front();
    isProcess = false;
    qDebug() << "Size of message - " << reply.length();
    qDebug() << reply;
    emit(Mail::getReply(currentRequest, reply));
    executeNext();
}

void Mail::slotConnectToServer(){
    qDebug() << "Mail::slotConnectToServer";
    isProcess = true;
    currentRequest = new MailRequest(0, "CONNECT");
    commandQue.push_back(currentRequest);
    emit(SimpleMail::slotConnect());
}

//--------------------------------PUBLIC--------------------------------

Mail::Mail(const QString &s ,const QString &l, const QString &p) : SimpleMail(s, l, p){
    connect(this, &Mail::execute, this, &SimpleMail::slotSendMessage);
    connect(this, &SimpleMail::recieve, this, &Mail::slotGetReply);
}

void Mail::executeNext(){
    if (!commandQue.size()) return;
    if (isProcess) return;
    isProcess = true;
    reply = "";
    currentRequest = commandQue.front();
    emit(execute(currentRequest->toString()));
}

//-------------------------------PRIVATE--------------------------------

bool Mail::isLastLine(const QString & text){
    QString last = TOOLS::getLastLine(text);
    auto start = QString::number(currentRequest->id);
    return last.left(start.length()) == start;
}
