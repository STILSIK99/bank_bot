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
    bool makeDir(QString);
    int id;
    QString getFileName(const QString & path);

public:
    FileCore(int);
    ~FileCore();

    bool init(const QString &);
    void readZip(const QString &);

public slots:

    // void saveString2File(int id, QByteArray *data, QString path);
    void saveBytes2File(int id, QByteArray *data, QString path);
    void saveHeader(QString path, QString data);
    void unzip(int, QByteArray *);

signals:
    void notSaved(int);
    void saved(int, QString);
    void parseFile(int, QByteArray *);


    void process(int, QByteArray *); // id, QByteArray
};
