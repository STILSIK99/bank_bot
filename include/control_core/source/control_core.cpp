#include "control_core.h"

//--------------------------------PUBLIC SLOTS---------------------------------

void ControlCore::getMessageCount(int count){
    // если последняя сессия завершена, то начать новую
    if (!isSessionFinished) return;
    isSessionFinished = false;
    if (nextSession) {
        nextSession = false;
    }
    session = std::vector<bool> (count, false);
    headers = std::vector<QString>(count);
    messageCount = count;
    processed = count;
    emit(getMessages(count));
}

void ControlCore::notFound(int id){
    if (id > session.size() || id < 1) {
        //error
        return;
    }
    session[id - 1] = false;
    if (!--processed) initFinish();
}

void ControlCore::saved(int id, QString path){
    if (id > session.size() || id < 1){
        //error
        return;
    }
    session[id - 1] = true;
    if (id <= headers.size() && id > 0){
        emit(saveHeader(path + ".hdr", headers[id - 1]));
    }

    if (!--processed) initFinish();
}

void ControlCore::getHeader(int id, QString data){
    if (id > headers.size() || id < 1){
        return;
    }
    headers[id - 1] = data;
}

void ControlCore::startImap(){
    qDebug() << "ControlCore::startImap";
    // получение сигнала, чтобы запустить новую сессию
    if (!isSessionFinished){
        // ожидание следущей сессии
        nextSession = true;
        return;
    }
    emit(updateListMessages());
}

void ControlCore::notSaved(int id){
    if (id > session.size() || id < 1) {
        //error
        return;
    }
    session[id - 1] = false;
    if (!--processed) initFinish();
}


//-----------------------------------PUBLIC------------------------------------

ControlCore::ControlCore(){
    isSessionFinished = true;
    nextSession = false;
    messageCount = 0;
    processed = 0;
}

//----------------------------------PRIVATE------------------------------------

void ControlCore::initFinish(){
    // генерация инструкций по письмам
    for(int i = 0; i < session.size(); ++i){
        if (session[i]) emit(deleteMessage(i + 1)); //id 1..N
    }

    isSessionFinished = true;
    if (nextSession) startImap();
}
































