#pragma once

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QUrl>
#include <QCryptographicHash>
#include <QDateTime>


#include "pc_tools.h"
#include "pc_variables.h"
#include "statement.h"

class ParserCore : public QObject{
    Q_OBJECT

private:
    // QString pathToSave;

    bool decodeBase64(int id, const QString &);
    void parseHTML(const QString &);

    QString exctractBase64(QStringList & lines, int leftPos, int rightPos);
    QString getUrlFromElement(const QString &);
    QString exctractUrl(QString & data, int position);

public:
    ParserCore();
    static QString getFilename(const QString &);
    QString generatePathToSave(const QString &);

public slots:
    void parseApplication(int, QString);
    void parseFile(int, QByteArray *);

signals:
    void downloadHttp(int, QString);
    void decodedBase64(int, QByteArray *);
    void saveFile(int, QByteArray *, QString);
    void notFound(int);
    void processStatement(Statement *);
};
