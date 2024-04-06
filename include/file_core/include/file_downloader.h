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
    std::map<QString, int> dict;


public:
    FileDownloader();
    ~FileDownloader();

public slots:
    void downloadFromUrl(int, QString);
    void downloadFinished(QNetworkReply *);

signals:
    void downloaded(int, QByteArray *);
    void downloadError(int);
};
