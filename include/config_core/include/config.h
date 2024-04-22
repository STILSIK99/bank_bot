#pragma once

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>
#include <QFile>
#include <QFileInfo>

#include <map>
#include <vector>

#include "exceptions.h"
#include "cfg_variables.h"
#include "tools.h"
#include "mail_account.h"


class Config : public QObject{
    /*

    Класс для работы с файлом конфигурации:

    - принимает на вход путь до файла;
    - чтение конфигурации из файла;
    - чтение параметра конфигурации;
    - внесение изменений в файл конфигурации.

    */

    Q_OBJECT
protected:
    std::map<QString, QString> parameters;
    std::list<MailAccount*> emails;
    QString path;

    void encode(QByteArray &);  // для шифрования файла-конфигурации
    void decode(QByteArray &);  // для расшифрования файла-конфигурации

    // проверка валидности содержимого файла-конфигурации
    bool verify(QJsonObject &, std::list<MailAccount*> &);

    // чтение учетных данных для почтовых ящиков
    bool readEmailsFromFile(const QString &, std::list<MailAccount*> &);

    void readFull(QJsonObject &);

    // QString toString() const;
    //
    MailAccount* emailFromJson(const QJsonObject &);

public:
    Config(const QString);
    ~Config();

    QString toString() const;
    bool save();
    void parseConfig();



public slots:


};

