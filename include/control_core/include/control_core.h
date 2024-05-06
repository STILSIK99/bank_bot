#pragma once

#include <QObject>
#include <vector>
#include <QDebug>


class ControlCore : public QObject{
    Q_OBJECT

private:
    std::vector<bool> session;

    std::vector<QString> headers;

    int processed;
    bool isSessionFinished;
    bool nextSession;
    int messageCount;

    void initFinish();

public:
    ControlCore();

public slots:
    void getMessageCount(int);
    void startImap();
    void notFound(int);
    void saved(int, QString);
    void notSaved(int);
    void getHeader(int, QString);

signals:
    void getMessages(int);
    void updateListMessages();
    void deleteMessage(int);
    void saveHeader(QString, QString); //path, data
};
