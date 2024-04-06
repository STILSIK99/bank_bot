#include "file_downloader.h"

//----------------------------PUBLIC SLOTS------------------------------

void FileDownloader::downloadFromUrl(QString url){
    qDebug() << "FileDownloader::downloadFromUrl";
    qDebug() << url;
    QNetworkRequest request;
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(conf);
    request.setUrl(QUrl(url));
    manager->get(request);
}

void FileDownloader::downloadFinished(QNetworkReply * reply){
    qDebug() << "FileDownloader::downloaded";
    if (!reply) return;
    if (reply->error()){
        qDebug() << reply->errorString();
        return;
    }
    QByteArray *out = new QByteArray(reply->readAll());
    emit (downloaded(out));
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
