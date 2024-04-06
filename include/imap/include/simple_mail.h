#pragma once

#include <QSslSocket>
#include <QObject>
#include <QDebug>

#include "email.h"

class SimpleMail : public QSslSocket, public Email{
    Q_OBJECT


public:
    SimpleMail(const QString &, const QString &, const QString &);
    ~SimpleMail();

public slots:
    void slotSendMessage(QString);
    void slotReadyRead();
    void slotConnect();

signals:
    void recieve(QString);

};
