#ifndef WORKER_H
#define WORKER_H

#include <QDebug>
#include <QString>
#include <QThread>
#include <QMutex>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <vector>
#include <queue>


class Worker : public QThread
{
    Q_OBJECT
public:
    Worker() = delete;
    Worker(const Worker&) = delete;
    Worker(QObject *, std::queue<QString>*, QMutex *);

    void run();
    void abort();

signals:
    void authorization_failed();
    void authorization_succsess();
    void online_users(std::vector<QString>);
    void msg_from_user(QString, QString);
    void user_connected(QString);
    void user_disconnected(QString);

private:
    QMutex *mutex;
    std::queue<QString> *msg_queue;
    bool stop = true;
};

#endif // WORKER_H
