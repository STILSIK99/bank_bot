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
    dataByDate = std::map<QDate, DailyOperations *>();
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
        if (array[currentRow].isEmpty()) {
            ++currentRow;
            continue;
        }
        if (TOOLS::comparePrefix(array[currentRow], STATEMENTS::RECORD_START)){
            currentRow = readBlock(currentRow, array, STATEMENTS::RECORD_FINISH);
        }
        else break;
    }
    if (array[currentRow] != STATEMENTS::FILE_FINISH){
        delete fields;
        throw EXCEPTIONS::StatementException(EXCEPTIONS::STATE_FORMAT);
    }


    startDate = TOOLS::extractDateFromRecord(fields->at(STATEMENTS::DATE_START));
    finishDate = TOOLS::extractDateFromRecord(fields->at(STATEMENTS::DATE_FINISH));

    return accounting();
}

QString* Statement::convertCodec(QByteArray *data){
    auto decoded = new QString(
        QTextCodec::codecForName("UTF-8")->fromUnicode(
            QTextCodec::codecForName("CP1251")->toUnicode(*data)
    ));
    return decoded;
}

void Statement::deleteData(){
    // if (dataByDate) delete dataByDate;
}

//----------------------------------PRIVATE------------------------------------

bool Statement::accounting(){
    /*
     * Функция производит вычисления начального и конечного
     * остатка на счету на каждый день, соответствующий выписке
     *
     */
    qDebug() << "Statement::accounting";
    if (!fields->count(STATEMENTS::START_SUM)){
        qDebug() << "Start sum not found.";
        return false;
    }
    if (!fields->count(STATEMENTS::FINISH_SUM)){
        qDebug() << "Finish sum not found.";
        return false;
    }
    if (!fields->count(STATEMENTS::CHANGES_ADD)){
        qDebug() << "Add changes not found.";
        return false;
    }
    if (!fields->count(STATEMENTS::CHANGES_MINUS)){
        qDebug() << "Minus changes not found.";
        return false;
    }

    if (dataByDate.size() == 0){
        return true;
    }

    auto    start = dataByDate.begin(),
            finish = --(dataByDate.end());
    long long   all_add = 0,
                all_minus = 0,
                finish_sum = TOOLS::exctractSum(fields->at(STATEMENTS::FINISH_SUM));
    start->second->start_sum = TOOLS::exctractSum(
        fields->at(STATEMENTS::START_SUM));

    for(auto it = dataByDate.begin(); it != dataByDate.end(); ++it){
        static long long _finish;
        if (it != dataByDate.begin()) {
            it->second->start_sum = _finish;
        }
        _finish = it->second->start_sum + it->second->changes;
        it->second->finish_sum = _finish;
        all_add += it->second->all_add;
        all_minus += it->second->all_minus;
    }

    if (all_add != TOOLS::exctractSum(fields->at(STATEMENTS::CHANGES_ADD)) ||
        all_minus*(-1) != TOOLS::exctractSum(fields->at(STATEMENTS::CHANGES_MINUS))){
        qDebug() << "Accounting error";
        return false;
    }
    qDebug() << "Accounting finish";
    return finish->second->finish_sum == finish_sum;

}

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
    static QString number;  // номер счета
    static bool direction;
    while(row < array.size()){
        if (array[row] == stopString){
            if (array[row] == STATEMENTS::ACCOUNT_FINISH){
                fields = current;
            }
            if (array[row] == STATEMENTS::RECORD_FINISH){
                auto record = new Record(current, direction);
                auto date = record->getOperationDate();
                if (!dataByDate.count(date)){
                    dataByDate[date] = new DailyOperations(date);
                }
                dataByDate[date]->addRecord(record);
            }
            return ++row;
        }
        current->insert(toPair(array[row]));
        if (TOOLS::comparePrefix(array[row], STATEMENTS::ACCOUNT_NUMBER)){
            auto data = array[row].split('=');
            if (data.length() < 2){
                qDebug() << "Error number";
            } else {
                number = data[1];
            }
        }
        if (TOOLS::comparePrefix(array[row], STATEMENTS::PAYER_NUMBER)){
            auto data = array[row].split('=');
            if (data.length() < 2){
                qDebug() << "Error number";
            } else {
                direction = !TOOLS::comparePrefix(data[1], number);
            }
        }
        ++row;
    }
    return row;
}

