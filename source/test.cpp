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
    QFile file("E:\\C++\\QT\\bank_bot\\bank_bot\\src\\kl_to_1c.txt");
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
