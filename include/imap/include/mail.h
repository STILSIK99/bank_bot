#pragma once

#include "simple_mail.h"
#include "mail_request.h"
#include "imap_tools.h"

#include <list>


class Mail : public SimpleMail{
    Q_OBJECT
    int commandId = 1;
    std::list<MailRequest*> commandQue;
    MailRequest * currentRequest;

    bool isProcess = false;
    QString reply = "";

    bool isLastLine(const QString &);

public:
    Mail(const QString &,
         const QString &,
         const QString &);

    void executeNext();

public slots:
    void slotExecute(MailRequest *);
    void slotGetReply(QString); //const QString
    void slotConnectToServer();

signals:
    void execute(QString); //const QString
    void getReply(MailRequest *, const QString);
};
