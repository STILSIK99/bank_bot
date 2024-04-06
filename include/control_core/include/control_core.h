#pragma once

#include <QObject>
#include <vector>


class ControlCore : public QObject{
    Q_OBJECT

private:
    std::vector<bool> session;
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
    void saved(int);
    void notSaved(int);

signals:
    void getMessages(int);
    void updateListMessages();
    void deleteMessage(int);
};
