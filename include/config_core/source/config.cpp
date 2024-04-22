#include "config.h"

//--------------------------------PUBLIC SLOTS---------------------------------
//-----------------------------------PUBLIC------------------------------------

Config::Config(const QString _path): path(_path){
    if (!QFile::exists(path)){
        qDebug() << "Config::Config - File-not exists " << path;
    }
}


bool Config::save(){
    QFile cfg(path);
    if (!cfg.open(QIODevice::WriteOnly)){
        return false;
    }
    auto lines = toString();
    cfg.write(lines.toUtf8());
    cfg.close();
    return true;
}

Config::~Config(){
    for (auto email : emails){
        delete email;
    }
}

//----------------------------------PRIVATE------------------------------------

void Config::encode(QByteArray &){}
void Config::decode(QByteArray &){}

void Config::parseConfig(){
    /*

    Функция, которая читает конфиг-файл и инициализирует
    необходимые параметры.
    В случае отстутствия необходимых параметров, вызывает исключение.

     */

    if (!QFile::exists(path)){
        throw EXCEPTIONS::ConfigException(EXCEPTIONS::CONFIG_ACCESS);
    }
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)){
        throw EXCEPTIONS::ConfigException(EXCEPTIONS::CONFIG_ACCESS);
    }
    QString lines = file.readAll();
    file.close();
    // decode(lines);

    auto doc = QJsonDocument::fromJson(lines.toUtf8());
    if (!doc.isObject()){
        throw EXCEPTIONS::ConfigException(EXCEPTIONS::CONFIG_FORMAT);
    }

    QJsonObject cfg = doc.object();
    std::list<MailAccount*> temp;


    if (!verify(cfg, temp)){
        throw EXCEPTIONS::ConfigException(EXCEPTIONS::CONFIG_FORMAT);
    }

    emails = temp;
    readFull(cfg);
}


bool Config::verify(QJsonObject & object, std::list<MailAccount*> &temp){
    //check valid main config.json
    for(auto field : CONFIG::FIELDS){
        if (!object.contains(field.first)){
            return false;
        }
        if (!object[field.first].isObject()){
            return false;
        }
        if (!TOOLS::compareObjects(
                object[field.first].toObject(),
                field.second)
            ){
            return false;
        }
    }

    //check valid config(s) with emails
    QString emails = object[CONFIG::SECTIONS::MAIL].toObject()[CONFIG::INCLUDE].toString();
    QFileInfo cfg(emails);
    if (!cfg.exists()){
        return false;
    }
    if (cfg.isDir()){
        auto allCfg = QDir(emails).entryInfoList(QStringList() << "*.json", QDir::Files);
        for (auto file : allCfg){
            if (!readEmailsFromFile(file.absoluteFilePath(), temp)){
                //logger.
            }
        }
    }
    if (cfg.isFile()){
        if (!readEmailsFromFile(cfg.absoluteFilePath(), temp)){
            //logger.
        }
    }
    if (temp.size() == 0) return false;
    return true;
}

QString Config::toString() const {
    QJsonObject cfg;
    std::map<QString, QJsonObject> objs;
    //collect
    for(const auto & pair : parameters){
        auto arr = pair.first.split('_');
        if (arr.size() < 2) {
            cfg[pair.first] = pair.second;
            continue;
        }
        if (!objs.count(arr[0])){
            objs[arr[0]] = QJsonObject();
        }
        objs[arr[0]][arr[1]] = pair.second;
    }
    //add
    for(const auto & obj : objs){
        cfg[obj.first] = obj.second;
    }
    return QJsonDocument(cfg).toJson(QJsonDocument::Indented);
}

bool Config::readEmailsFromFile(const QString &path, std::list<MailAccount*> & array){
    if (!QFile::exists(path)) {
        //logger.
        return false;
    }
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)){
        //logger.
        return false;
    }
    auto doc = QJsonDocument::fromJson(f.readAll());
    if (doc.isArray()){
        for(auto el : doc.array()){
            if (!el.isObject()){
                //logger.
                continue;
            }
            try{
                array.emplace_back(emailFromJson(el.toObject()));
            }catch(...){
                //logger
            }
        }
    }
    if (doc.isObject()){
        try{
            array.emplace_back(emailFromJson(doc.object()));
        }catch(...){
            //logger
        }
    }
    return bool(array.size());
}

MailAccount* Config::emailFromJson(const QJsonObject & obj){
    if (TOOLS::compareObjects(obj, CONFIG::CONNECTION::ALL)){
        return new MailAccount(obj);
    }
    throw EXCEPTIONS::ConfigException(EXCEPTIONS::CONFIG_FORMAT);
}


void Config::readFull(QJsonObject & cfg){;
    for(auto field : CONFIG::FIELDS){
        auto [key, value] = field;
        auto varObject = cfg[key].toObject();
        for (auto field : value){
            if (varObject.contains(field)){
                parameters[key + "_" + field] = varObject[field].toString();
            }
        }
    }
}

