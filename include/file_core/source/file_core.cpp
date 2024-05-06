#include "file_core.h"
//--------------------------------PUBLIC SLOTS---------------------------------

// void FileCore::saveString2File(QString path, QString data){
//     saveBytes2File(path, data.toUtf8());
// }

void FileCore::saveBytes2File(int id, QByteArray *data, QString path){
    auto arr = path.split('/');
    if (arr.size() < 2){
        qDebug() << "Error save path.";
        return;
    }
    if (!makeDir(arr[0])){
        qDebug() << "Directory not created.";
        return;
    }
    path = getFileName(path);
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)){
        //logger error
        qDebug() << "error";
        auto error = file.errorString();
        emit(notSaved(id));
        return;
    }
    file.write(*data);
    file.close();
    emit(saved(id, path));
    emit(process(FileCore::id, data));
}


void FileCore::saveHeader(QString path, QString data){
    // if (data == "") return;
    auto dir = QFileInfo(path);
    if (!dir.dir().exists()){
        if (!makeDir(dir.absolutePath())) {
            qDebug() << "Error to save header";
            return;
        }
    }
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)){
        //logger error
        qDebug() << "Header not written.";
        return;
    }
    file.write(data.toUtf8());
    file.close();
}

void FileCore::unzip(int id, QByteArray *zippedData){
    auto array = FileUnzip::unzip(zippedData);
    for(auto file : array){
        emit(parseFile(id, file.second));
    }
}

//-----------------------------------PUBLIC------------------------------------

bool FileCore::init(const QString & path){
    if (!makeDir(path)){
        qDebug() << "Directory not created.";
        return false;
    }
    dir2save = path;
    return true;
}

FileCore::FileCore(int id_thread){
    QObject::connect(this, &FileDownloader::downloaded,
                     this, &FileCore::unzip);
    id = id_thread;
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

QString FileCore::getFileName(const QString & path){
    QString fullPath = QString("%1/%2").arg(dir2save, path);
    if (QFileInfo(fullPath).exists()){
        for(int i = 2; i < 1e9; ++i){
            static QString _path = fullPath + "_" + QString::number(i);
            if (!QFileInfo(_path).exists()){
                return _path;
            }
        }
    } else {
        return fullPath;
    }
    return getFileName(path + "_");
}

bool FileCore::makeDir(QString path){
    QString _path = ((dir2save == "")
                         ? path
                         : QString("%1/%2").arg(dir2save, path));
    QFileInfo _file(_path);
    if (_file.exists(_path)) return true;
    QDir _dir;
    return _dir.mkpath(_path);
}
