#include "remote_server.hpp"

Server::Server(std::string _nickname, std::string _ip, int _port, QWidget *parent)
    : nickname(_nickname), ip(_ip), port(_port), QObject(parent) { }

Server::~Server()
{
    destroy_connection();
}

void Server::establish_connection()
{
    master_socket = new QTcpSocket(this);

    connect(master_socket, SIGNAL(connected()), SIGNAL(connected()));
    connect(master_socket, SIGNAL(readyRead()), SIGNAL(readyRead()));

    master_socket->connectToHost(ip.c_str(), port);
    if (!master_socket->waitForConnected(timeout*1000))
    {
        emit error(master_socket->error());
    } else {
        send(nickname.c_str());
    }

    connect(master_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            SIGNAL(error(QAbstractSocket::SocketError)));

    emit stop_thread();
}

void Server::destroy_connection()
{
    if (master_socket)
    {
        master_socket->disconnectFromHost();
        delete master_socket;
        master_socket = nullptr;
    }
}

QString Server::get_address()
{
    return QString::fromStdString(ip) + ":" + QString::number(port);
}

QTcpSocket *Server::get_socket()
{
    return master_socket;
}

QString Server::get_nickname()
{
    return QString::fromStdString(nickname);
}

qint64 Server::send(QString txt)
{
    if (master_socket == nullptr) {
        return -1;
    }
    QByteArray msg = txt.toStdString().c_str();
    return master_socket->write(msg);
}

QString Server::read()
{
    if (master_socket == nullptr) {
        return "";
    }
    return master_socket->readAll();
}
