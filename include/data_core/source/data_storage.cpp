#include "data_storage.h"
#include <QFile>

//--------------------------------PUBLIC SLOTS---------------------------------


//-----------------------------------PUBLIC------------------------------------

bool DataStorage::createTables(){
    for(auto table : DATABASE::TABLES){
        if (!DataBase::query(table)){
            return false;
        }
    }
    return true;
}

void DataStorage::insertStartData(){
    for(auto insertion : DATABASE::INSERTIONS){
        // qDebug() << insertion.toUtf8();
        // QTextCodec * codec1 = QTextCodec::codecForName("CP1251");
        // auto s = codec1->fromUnicode(insertion);
        DataBase::query(insertion);
    }


}
//----------------------------------PRIVATE------------------------------------
