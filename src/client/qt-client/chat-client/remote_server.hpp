#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <memory>
#include <queue>

#include <QDebug>
#include <QMessageBox>
#include <QTcpSocket>

class MainWindow;

class Server : public QObject
{
    Q_OBJECT
public:
    Server() = delete;
    Server(const Server&) = delete;
    Server(std::string, std::string, int, QWidget *parent = nullptr);
    ~Server();

    void destroy_connection();
    QString get_address();
    QTcpSocket *get_socket();
    QString get_nickname();
    qint64 send(QString);
    QString read();
private slots:
    void establish_connection();

signals:
    void connected();
    void readyRead();
    void error(QAbstractSocket::SocketError);
    void stop_thread();
    void slotDisconnected();

private:
    std::string nickname;
    std::string ip;
    int port;
    const int timeout = 5;
    QTcpSocket *master_socket = nullptr;

};

#endif // SERVER_HPP
