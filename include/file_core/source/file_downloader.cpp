#include "file_downloader.h"

//----------------------------PUBLIC SLOTS------------------------------

void FileDownloader::downloadFromUrl(int id, QString url){
    qDebug() << "FileDownloader::downloadFromUrl";
    qDebug() << url;
    QNetworkRequest request;
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(conf);
    request.setUrl(QUrl(url));
    manager->get(request);
    dict[url] = id;
}

void FileDownloader::downloadFinished(QNetworkReply * reply){
    qDebug() << "FileDownloader::downloaded";
    if (!reply) return;
    if (reply->error()){
        qDebug() << reply->errorString();
        if (dict.count(reply->url().toString())){
            emit(downloadError(dict[reply->url().toString()]));
        }
    } else {
        QByteArray *out = new QByteArray(reply->readAll());
        if (!dict.count(reply->url().toString())){
            qDebug() << "Not found";
            return;
        }
        emit (downloaded(dict[reply->url().toString()], out));
    }
    dict.erase(reply->url().toString());
    reply->deleteLater();
}


//-------------------------------PUBLIC---------------------------------

FileDownloader::FileDownloader(){
    manager = new QNetworkAccessManager;
    connect(manager, &QNetworkAccessManager::finished, this, &FileDownloader::downloadFinished);
}

FileDownloader::~FileDownloader(){
    delete manager;
}



//-------------------------------PRIVATE--------------------------------
