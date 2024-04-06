#include "simple_mail.h"

//-----------------------------PUBLIC SLOTS-----------------------------

void SimpleMail::slotSendMessage(QString message){
    qDebug() << "SimpleMail::slotSendMessage";
    if (!isEncrypted() || !isWritable()){
        qDebug() << "Socket not secure.";
        close();
    }
    write(message.toUtf8());
}

void SimpleMail::slotReadyRead(){
    qDebug() << "SimpleMail::slotReadyRead";
    qDebug() << "Bytes available " << bytesAvailable();
    if (!isReadable())  return;
    auto message = QString::fromUtf8(readAll());
    emit (recieve(message));
}

void SimpleMail::slotConnect(){
    qDebug() << "SimpleMail::slotConnect";
    const std::vector<QSsl::SslProtocol>
        PROTOCOLS = {
            QSsl::TlsV1_0, QSsl::TlsV1_0OrLater, QSsl::TlsV1_1,
            QSsl::TlsV1_1OrLater, QSsl::TlsV1_2, QSsl::TlsV1_2OrLater,
            QSsl::TlsV1SslV3
        };
    for(auto protocol : PROTOCOLS){
        connectToHostEncrypted(Email::server, 993);
        if (waitForEncrypted(2000) && waitForConnected(2000)){
            qDebug() << "Socket encrypted.";
            return;
        }
    }
    qDebug() << "Not connected";
}



//--------------------------------PUBLIC--------------------------------

SimpleMail::SimpleMail(const QString & s, const QString & l, const QString & p): Email(s, l, p){
    qDebug() << "SimpleMail::SimpleMail";
    connect(this, &QSslSocket::readyRead, this, &SimpleMail::slotReadyRead);
}

SimpleMail::~SimpleMail(){
    qDebug() << "SimpleMail::~SimpleMail";
}

//-------------------------------PRIVATE--------------------------------





