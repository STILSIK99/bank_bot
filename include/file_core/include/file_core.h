#pragma once

#include <QFile>
#include <QString>
#include <QByteArray>
#include <QObject>
#include <QDebug>
#include <QDir>

#include "file_downloader.h"
#include "file_unzip.h"
#include "fc_variables.h"

class FileCore : public FileDownloader, public FileUnzip{
    Q_OBJECT

private:
    QString dir2save;

public:
    FileCore();
    ~FileCore();

    bool init(const QString &);
    void readZip(const QString &);

public slots:

    // void saveString2File(int id, QByteArray *data, QString path);
    void saveBytes2File(int id, QByteArray *data, QString path);
    void unzip(int, QByteArray *);

signals:
    void notSaved(int);
    void saved(int);
    void parseFile(QByteArray *);
};
