#include "parser_core.h"

//----------------------------PUBLIC SLOTS------------------------------

void ParserCore::parseApplication(int id, QString data){
    qDebug() << "ParserCore::parseApplication";
    auto arr = data.split("\r\n");
    bool isAttachment = false, isBase64 = false;
    int left = 0, right = 0, mid = 0;

    for(int i = 0; i < arr.size(); ++i){
        static PARSER::SEPARATOR_TYPE sep;
        sep = TOOLS::checkSeparator(arr[i]);
        if (sep == PARSER::SEPARATOR_TYPE::DISPOSITION){
            isAttachment = true;
            auto fileName = getFilename(arr[i + 1]);
            qDebug () << "Attachment: " << fileName;
            mid = i + 2;
            continue;
        }
        if (sep == PARSER::SEPARATOR_TYPE::ENCODING){
            if (TOOLS::checkEnd(arr[i], PARSER::STRINGS::BASE64)){
                isBase64 = true;
            }
            continue;
        }
        if (sep == PARSER::SEPARATOR_TYPE::PART){
            if (arr[i][arr[i].length() - 1] == '-'){
                right = i;
                if (!isAttachment || !isBase64 ||
                    !TOOLS::checkStart(arr[left], arr[right])){
                    continue;
                }
                // qDebug () << "Base64: " << decodeBase64(id, exctractBase64(arr, mid, right - 1));
                decodeBase64(id, exctractBase64(arr, mid, right - 1));
                return;
            } else {
                left = i;
                isAttachment = isBase64 = 0;
            }
            continue;
        }
        if (sep == PARSER::SEPARATOR_TYPE::HTML){
            int position = 0;
            for(int j = 0; j < i; ++j)
                position += arr[j].length();
            auto url = exctractUrl(data, position);
            emit(downloadHttp(id, url));
            qDebug() << url;
            return;
        }
    }
}

void ParserCore::parseFile(int id, QByteArray *data){
    Statement *state = new Statement;
    try{
        if (!state->init(data)){
            emit(notFound(id));
            state->clearData();
            delete state;
            delete data;
        } else {
            emit(saveFile(
                id, data,
                generatePathToSave(state->getAccountNumber())
                ));
            emit(processStatement(state));
        }
    } catch (...){
        qDebug() << "Parsing error.";
        delete state;
    }
}


//-------------------------------PUBLIC---------------------------------

ParserCore::ParserCore(){
    connect(this, &ParserCore::decodedBase64, this, &ParserCore::parseFile);
}

QString ParserCore::getFilename(const QString & line){
    static int preffix = PARSER::SEPARATOR::FILENAME.length();
    auto fileName = line.mid(preffix, line.length() - preffix);
    qDebug() << QUrl(fileName).toString();
    return QUrl(fileName).toString();
}

QString ParserCore::generatePathToSave(const QString & accountNumber){
    return QString("%2/%3").arg(
        QCryptographicHash::hash ( //Номер банковского счета
                accountNumber.toUtf8(),
            QCryptographicHash::Md5
            ).toHex().left(8),
        QCryptographicHash::hash( //Время обработки
            QDateTime::currentDateTime().toString(
                "yyyy-MM-dd HH:mm:ss.zzz").toUtf8(),
            QCryptographicHash::Md5
            ).toHex().left(8)
        );
}


//-------------------------------PRIVATE--------------------------------

QString ParserCore::exctractBase64(QStringList & lines,
                                   int leftPos, int rightPos){
    QString result = "";
    for(int i = leftPos; i <= rightPos; ++i){
        result += lines[i];
    }
    return result;
}

QString ParserCore::getUrlFromElement(const QString & text){
    QString result = "";
    int left_pos = 0, right_pos = 0;
    bool isHref = false;
    for(int i = 0; i < (text.length() - 4); ++i){
        if (text.mid(i, 4) == "href"){
            isHref = 1;
            continue;
        }
        if (isHref){
            if (text[i] == '"' &&
                text[i + 1] == 'h' &&
                left_pos == 0){
                left_pos = i + 1;
                continue;
            }
            if (text[i] == '"' &&
                left_pos != 0){
                right_pos = i;
                result = text.mid(left_pos, right_pos - left_pos);
                break;
            }
        }
    }
    result = result.replace("=\r\n", "");
    auto arr = result.split('/');
    bool isSber = false, isDownload = false;
    if (arr.size() > 4){
        if (arr[2].split('.')[1] == "sberbank"){
            isSber = true;
        }
        for(int i = 3; i < arr.size(); ++i){
            if (arr[i] == "download"){
                isDownload = true;
            }
        }
    }
    if (isSber && isDownload){
        return result;
    } else return "";
}

QString ParserCore::exctractUrl(QString & data, int position){
    QString result = "";
    int left_pos = 0, right_pos = 0;
    for(int i = position; i < (data.length() - 4); ++i){
        if (data.mid(i, 3) == "<a "){
            left_pos = i;
        }
        if (data.mid(i, 4) == "</a>"){
            right_pos = i;
            result = getUrlFromElement(data.mid(left_pos, right_pos - left_pos + 1));
            if (result != ""){
                break;
            }
        }
    }
    return result;
}


// QString ParserCore::exctractUrl(QStringList & lines, int left){
//     QString url = "";
//     for(int i = lines.size() - 1; i > left; --i){
//         for(auto URL : PARSER::STRINGS::URL2FILE){
//             if (!TOOLS::checkStart(lines[i], URL)){
//                 continue;
//             }
//             QString result = lines[i] + "\r\n" +lines[i + 1];
//             result = result.replace("=\r\n", "");
//             int _left = 0, _right = 0;
//             for(int i = 0; i < result.size(); ++i){
//                 if (result[i] == '"') {
//                     _left = i + 1;
//                     break;
//                 }
//             }
//             for(int i = _left; i < result.size(); ++i){
//                 if (result[i] == '"') {
//                     _right = i - 1;
//                     break;
//                 }
//             }
//             url = result.mid(_left, _right - _left + 1);
//         }
//     }
//     return "";
// }


bool ParserCore::decodeBase64(int id, const QString & data){
    qDebug() << "ParserCore::decodeBase64";
    try {
        auto decoded = new QByteArray(
            QByteArray::fromBase64(data.toUtf8())
            );
        qDebug () << decoded;
        emit (ParserCore::decodedBase64(id, decoded));
        return true;
    } catch (...) {
        qDebug() << "error";
        return false;
    }
}
