#pragma once

#include "mail.h"
#include "imap_variables.h"
#include <list>


class IMAPClient : public Mail{
    Q_OBJECT

private:

    // int messages = 0; // max id current messages

    void parseSelectMessage(const QString &);
    void fetchMessage(int);

public:

    IMAPClient(const QString &,
               const QString &,
               const QString &);

public slots:

    void connectToServer();

    void start();

    void parseReply(MailRequest *, QString);
    void updateListMessages();
    void deleteAllSavedMessages();
    void flagDeleteMessage(int);
    void fetchAllMessages(int);

signals:

    void saveHeader(int, QString);
    void saveBody(int, QString);
    void allSaved();
    void flagDelete(int);
    void messageCount(int);
};
