#include "file_core.h"
//--------------------------------PUBLIC SLOTS---------------------------------

void FileCore::slotSaveString2File(QString path, QString data){
    slotSaveBytes2File(path, data.toUtf8());
}

void FileCore::slotSaveBytes2File(QString path, QByteArray data){
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)){
        //logger error
        qDebug() << "error";
        return;
    }
    file.write(data);
    file.close();
    emit(saved(path));
}

void FileCore::slotUnzip(QByteArray *zippedData){
    auto array = FileUnzip::unzip(zippedData);
    for(auto file : array){
        emit(parseFile(file.second));
    }
}

//-----------------------------------PUBLIC------------------------------------


FileCore::FileCore(){
    QObject::connect(this, &FileDownloader::downloaded,
                     this, &FileCore::slotUnzip);
}

FileCore::~FileCore(){}


//----------------------------------PRIVATE------------------------------------
