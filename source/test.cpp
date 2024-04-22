#include "test.h"
#include "statement.h"

bool TEST::testDecodeBase64(const QString & base64){
    // const QString path = "src/decoded.txt";
    // QFile f(path);
    // if (!f.open(QIODevice::ReadOnly)){
    //     return false;
    // }

}

bool TEST::testParseStatement(){
    QFile file("E:\\C++\\QT\\bank_bot\\bank_bot\\src\\Выписки\\KL_to_1C (3).txt");
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "Error test Statement::init";
        return 0;
    }
    auto data = new QByteArray(file.readAll());
    file.close();


    Statement st;
    auto result = st.init(data);
    delete data;
    return result;
}

bool TEST::testDataBaseConnection(){
    QString server = "127.0.0.1", user = "root", password = "root";
    DataCore *dc = new DataCore;
    auto result = dc->init(server, user, password);
    delete dc;
    return result;
}

bool TEST::testConfig(){
    QString path = "E:/commerse/bankbot/src/config.json";
    Config cfg(path);
    try{
        cfg.parseConfig();
    } catch (std::exception e){
        qDebug() << e.what();
        return false;
    }
    return true;
}
