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
    messageCount = count;
    emit(getMessageCount(count));
}

void ControlCore::notFound(int id){
    if (id > session.size() || id < 1) {
        //error
        return;
    }
    session[id - 1] = false;
    if (!--processed) initFinish();
}

void ControlCore::saved(int id){
    if (id > session.size() || id < 1){
        //error
        return;
    }
    session[id - 1] = true;
    if (!--processed) initFinish();
}

void ControlCore::startImap(){
    // получение сигнала, чтобы запустить новую сессию
    if (!isSessionFinished){
        // ожидание следущей сессии
        nextSession = true;
        return;
    }
    emit(updateListMessages());
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
































