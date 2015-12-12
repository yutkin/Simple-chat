#include "worker.hpp"

Worker::Worker(QObject *parent, std::queue<QString> *q, QMutex *m) :
    QThread(parent)
{
    stop = false;
    msg_queue = q;
    mutex = m;
}


void Worker::run()
{
    while (!stop) {
        if (!msg_queue->empty())
        {
            mutex->lock();
                auto msg = msg_queue->back();
            mutex->unlock();
            qDebug() << msg;
            auto d = QJsonDocument::fromJson(msg.toUtf8());
            auto obj = d.object();

            if (obj.contains("authorization_status"))
            {
                auto status = obj["authorization_status"].toString();
                if (status == "succsess")
                {
                    emit authorization_succsess();
                }
                else
                {
                    emit authorization_failed();
                }
            }

            if (obj.contains("online_users"))
            {
                auto usr_array = obj["online_users"].toArray();
                std::vector<QString> online;
                for (const auto &i : usr_array) {
                    online.push_back(i.toString());
                }
                emit online_users(online);
            }

            if (obj.contains("user_connected"))
            {
                auto user = obj["user_connected"].toString();
                emit user_connected(user);
            }

            if (obj.contains("user_disconnected"))
            {
                auto user = obj["user_disconnected"].toString();
                emit user_disconnected(user);
            }

            if (obj.contains("msg_from_user") && obj.contains("msg"))
            {
                auto user = obj["msg_from_user"].toString();
                auto msg = obj["msg"].toString();
                emit msg_from_user(user, msg);
            }

            mutex->lock();
                msg_queue->pop();
            mutex->unlock();
        }
    }
}

void Worker::abort()
{
    stop = true;
}
