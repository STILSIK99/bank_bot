#include "tools.h"

namespace TOOLS{

QString convertFile(QByteArray inputText){
    /*
        Функция предназначена для конвертации входящего файла
        с кодировкой Windows 1251
        в формат UTF-8.
         */
    return
        QTextCodec::codecForName("UTF-8")->fromUnicode(
            QTextCodec::codecForName("CP1251")->toUnicode(inputText)
            );

}

bool comparePrefix(const QString &a, const QString &b){
    for(int i = 0; i < std::min(a.length(), b.length()); ++i){
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool compareObjects(const QJsonObject & obj, const std::vector<QString> & names){
    for (auto name : names){
        if (!obj.contains(name)) return false;
        if (!obj[name].isString()) return false;
    }
    return true;
}

// const std::map<QString, QString> extractVars(Config * cfg, const QString & module){
//     if (!CONFIG::FIELDS.count(module)){
//         throw EXCEPTIONS::CodeException(EXCEPTIONS::VARIABLES_NOT_FOUND);
//     }
//     auto fields = CONFIG::FIELDS.at(module);
//     std::map<QString, QString> extracted;
//     for (auto field : fields){
//         extracted[field] = cfg->get(module + "_" + field);
//     }
//     return extracted;
// }


QString getLastLine(const QString & str, int step){
    for(int i = str.length() - 1 - step; i > 1; --i){
        if (str[i] == '\n' && str[i - 1] == '\r'){
            return str.right(str.length() - i);
        }
    }
    return str;
}

QDate extractDateFromRecord(const QString & date){
    if (date.at(2) == '.' && date.at(5) == '.')
        return QDate(
            date.right(4).toInt(),
            date.mid(3, 2).toInt(),
            date.left(2).toInt());
    return QDate(1900, 1, 1);
}

}



