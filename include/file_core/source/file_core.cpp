#include "file_core.h"
//--------------------------------PUBLIC SLOTS---------------------------------

// void FileCore::saveString2File(QString path, QString data){
//     saveBytes2File(path, data.toUtf8());
// }

void FileCore::saveBytes2File(int id, QByteArray *data, QString path){
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)){
        //logger error
        qDebug() << "error";
        emit(notSaved(id));
        return;
    }
    file.write(*data);
    file.close();
    delete data;
    emit(saved(id));
}

void FileCore::unzip(int id, QByteArray *zippedData){
    auto array = FileUnzip::unzip(zippedData);
    for(auto file : array){
        emit(parseFile(file.second));
    }
}

//-----------------------------------PUBLIC------------------------------------

bool FileCore::init(const QString & path){
    QDir dir(path);
    if (!dir.exists()){
        return dir.mkpath(path);
    }
    return true;
}

FileCore::FileCore(){
    QObject::connect(this, &FileDownloader::downloaded,
                     this, &FileCore::unzip);
}

FileCore::~FileCore(){}

void FileCore::readZip(const QString &path){
    qDebug() << "FileCore::readZip";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "error";
        return;
    }
    unzip(FILE_CORE::TEST_ID, new QByteArray(file.readAll()));
    file.close();
}

//----------------------------------PRIVATE------------------------------------
