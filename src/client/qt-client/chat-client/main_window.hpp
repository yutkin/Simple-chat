#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QMutex>
#include <QListWidgetItem>

#include "remote_server.hpp"
#include "worker.hpp"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void action_connect_triggered();
    void action_disconnect_triggered();

    void establish_connection(const std::string&,
                              const std::string&, int);

    void connection_established();
    void connection_failed(QAbstractSocket::SocketError);
    void authorization_failed();
    void authorization_succsess();
    void received_online_users_list(std::vector<QString>);
    void new_user_handler(QString);
    void disconnected_user_handler(QString);
    void keyPressed();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void msg_from_user_received(QString, QString);

public slots:
    void message_received();


private:
    Ui::MainWindow *ui;
    Server *server = nullptr;
    std::queue<QString> msg_queue;
    QMutex mutex;
    QString roommate = "";
    std::unique_ptr<Worker> worker;
    QAction *foo = nullptr;
};

#endif // MAIN_WINDOW_HPP
