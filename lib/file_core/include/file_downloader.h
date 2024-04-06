#pragma once

#include <QUrl>
#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QByteArray>
#include <QFile>

class FileDownloader : public QObject {
    Q_OBJECT

private:
    QNetworkAccessManager *manager;


public:
    FileDownloader();
    ~FileDownloader();

public slots:
    void downloadFromUrl(QString);
    void downloadFinished(QNetworkReply *);

signals:
    void downloaded(QByteArray *);

};
