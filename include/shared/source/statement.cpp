#include "statement.h"

//-----------------------------------PUBLIC------------------------------------

Statement::Statement(){}

Statement::~Statement(){
    for(auto el : dataByDate){
        delete el.second;
    }
    delete fields;
}

QString Statement::getAccountNumber(){
    qDebug() << "Statement::getAccountNumber";
    if (fields->count(STATEMENTS::ACCOUNT_NUMBER)){
        return fields->at(STATEMENTS::ACCOUNT_NUMBER);
    }
    qDebug() << "Number not found.";
    return "";
}

bool Statement::init(QByteArray * data){
    auto *_data = convertCodec(data);
    auto start = STATEMENTS::FILE_START;
    if (data->size() < start.size()) return false;
    for(int i = 0; i < start.size(); ++i){
        if (start[i] != _data->at(i)) return false;
    }
   //magic is ok
    auto array = _data->split(STATEMENTS::SPLITTER);

    if (array[0] != STATEMENTS::FILE_START ||
        array[1] != STATEMENTS::FILE_VERSION)
    {
        throw EXCEPTIONS::StatementException(EXCEPTIONS::STATE_FORMAT);
    }

    int currentRow = readBlock(2, array, STATEMENTS::ACCOUNT_START);
    currentRow = readBlock(currentRow, array, STATEMENTS::ACCOUNT_FINISH);

    while(currentRow < array.size()){
        if (TOOLS::comparePrefix(array[currentRow], STATEMENTS::RECORD_START)){
            currentRow = readBlock(currentRow, array, STATEMENTS::RECORD_FINISH);
        }
        else break;
    }
    if (array[currentRow] != STATEMENTS::FILE_FINISH){
        delete fields;
        throw EXCEPTIONS::StatementException(EXCEPTIONS::STATE_FORMAT);
    }


    return true;
}

QString* Statement::convertCodec(QByteArray *data){
    auto decoded = new QString(
        QTextCodec::codecForName("UTF-8")->fromUnicode(
            QTextCodec::codecForName("CP1251")->toUnicode(*data)
    ));
    return decoded;
}


//----------------------------------PRIVATE------------------------------------

std::pair<QString, QString> Statement::toPair(QString & str){
    auto line = str.split("=");
    if (line.length() < 2) return {line[0], ""};
    if (line.length() > 2){
        throw EXCEPTIONS::StatementException(EXCEPTIONS::STATE_PARAMETER);
    }
    return {line[0], line[1]};
}

int Statement::readBlock(int row, QStringList& array, const QString& stopString){
    std::map<QString, QString>  *current = new std::map<QString, QString>();
    while(row < array.size()){
        if (array[row] == stopString){
            if (array[row] == STATEMENTS::ACCOUNT_FINISH){
                fields = current;
            }
            if (array[row] == STATEMENTS::RECORD_FINISH){
                auto record = new Record(current);
                auto date = record->getOperationDate();
                if (!dataByDate.count(date)){
                    dataByDate[date] = new DailyOperations(date);
                }
                dataByDate[date]->addRecord(record);
            }
            return ++row;
        }
        current->insert(toPair(array[row]));
        ++row;
    }
    return row;
}

