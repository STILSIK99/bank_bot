#include "config_core.h"


//--------------------------------PUBLIC SLOTS---------------------------------

//-----------------------------------PUBLIC------------------------------------

ConfigCore::ConfigCore(const QString & path): Config(path){

}

QString ConfigCore::getSaveDir(){
    QString key("%1_%2");
    return parameters[key.arg(CONFIG::SECTIONS::MAIL, CONFIG::SAVEDIR)];
}

const std::list<MailAccount *>& ConfigCore::getListEmails(){
    return Config::emails;
}

std::vector<QString> ConfigCore::getDatabase(){
    std::vector<QString> data;
    for(auto & el : CONFIG::CONNECTION::ALL){
        auto field = QString("%1_%2").arg(
            CONFIG::SECTIONS::DATABASE, el);
        if (!parameters.count(field)){
            qDebug() << "ConfigCore::getDatabase - parameter \""
                     << field << "\" not found";
            continue;
        }
        data.emplace_back(parameters[field]);
    }
    return data;
}

//----------------------------------PRIVATE------------------------------------
