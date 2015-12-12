#include "main_window.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<QTcpSocket::SocketError>();
    qRegisterMetaType<std::vector<QString>>();

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
