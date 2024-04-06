#pragma once

#include <QFile>
#include <QString>
#include <QByteArray>
#include <QObject>
#include <QDebug>

#include "file_downloader.h"
#include "file_unzip.h"

class FileCore : public FileDownloader, public FileUnzip{
    Q_OBJECT

private:


public:
    FileCore();
    ~FileCore();


public slots:

    void slotSaveString2File(QString path, QString data);
    void slotSaveBytes2File(QString path, QByteArray data);
    void slotUnzip(QByteArray *);

signals:

    void saved(QString);
    void parseFile(QByteArray *);
};
