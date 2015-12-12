#include "ui_main_window.h"

#include "main_window.hpp"
#include "login_dialog.hpp"
#include <QMessageBox>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionConnect, SIGNAL(triggered()),
            SLOT(action_connect_triggered()));

    connect(ui->actionDisconnect, SIGNAL(triggered()),
            SLOT(action_disconnect_triggered()));
}

void MainWindow::establish_connection(const std::string& nickname,
                                      const std::string& ip, int port)
{ 
    auto thread = new QThread(this);

    if (server != nullptr)
    {
        server->destroy_connection();
        delete server;
    }

    server = new Server(nickname, ip, port, this);

    connect(thread, SIGNAL(started()), server, SLOT(establish_connection()));

    connect(server, SIGNAL(connected()), this, SLOT(connection_established()));

    connect(server, SIGNAL(readyRead()), this, SLOT(message_received()));

    connect(server, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(connection_failed(QAbstractSocket::SocketError)));

    connect(server, SIGNAL(stop_thread()), thread, SLOT(quit()));

    thread->start();
}

void MainWindow::connection_established()
{
    qDebug() << "Connected successfully";
    worker = std::unique_ptr<Worker>(
                new Worker(this, &this->msg_queue, &this->mutex));

    connect(worker.get(), SIGNAL(authorization_failed()),
            SLOT(authorization_failed()));
    connect(worker.get(), SIGNAL(authorization_succsess()),
            SLOT(authorization_succsess()));
    connect(worker.get(), SIGNAL(online_users(std::vector<QString>)),
            SLOT(received_online_users_list(std::vector<QString>)));
    connect(worker.get(), SIGNAL(msg_from_user(QString, QString)),
            SLOT(msg_from_user_received(QString, QString)));
    connect(worker.get(), SIGNAL(user_connected(QString)),
            SLOT(new_user_handler(QString)));
    connect(worker.get(), SIGNAL(user_disconnected(QString)),
            SLOT(disconnected_user_handler(QString)));


    worker->start();
}

void MainWindow::connection_failed(QAbstractSocket::SocketError e)
{
    QString err_msg = server->get_socket()->errorString();

    server = nullptr;
    if (worker != nullptr)
        worker->abort();
    roommate = "";

    QMessageBox::critical(this, "Connection failed", err_msg);
}

void MainWindow::authorization_succsess()
{
    qDebug() << "Authorization passed...";
}

void MainWindow::authorization_failed()
{
    qDebug() << "Authorization failed...";
}

void MainWindow::message_received()
{
    mutex.lock();
        msg_queue.push(server->read());
    mutex.unlock();
}

void MainWindow::received_online_users_list(std::vector<QString> users)
{
    ui->listWidget->clear();
    for (const auto &i : users)
    {
        auto client_name = server->get_nickname();
        if (i != client_name)
            ui->listWidget->addItem(i);
    }
}

void MainWindow::new_user_handler(QString new_user)
{
    ui->listWidget->addItem(new_user);
}

void MainWindow::disconnected_user_handler(QString disconnected_user)
{
    if (disconnected_user == roommate) {
        roommate = "";
    }

    for(int i = 0; i < ui->listWidget->count(); ++i)
    {
        auto item = ui->listWidget->item(i);

        if (item->text() == disconnected_user) {
            delete item;
        }
    }
}

void MainWindow::keyPressed()
{
    if (server == nullptr || roommate == "" ||
            ui->plainTextEdit->toPlainText() == "")
    {
        return;
    }

    auto msg = "{\"method\": \"send_to_user\", \"user\": \"" +
               roommate + "\", " +
               "\"msg\": \""  + ui->plainTextEdit->toPlainText() + "\"}";
    server->send(msg);

    ui->plainTextEdit->clear();
}

void MainWindow::action_connect_triggered()
{
    if (server)
    {
        QMessageBox::information(this, "", "Close current connection.");
        return;
    }

    auto login_dialog = new LoginDialog(this);

    login_dialog->setAttribute(Qt::WA_DeleteOnClose);

    connect(login_dialog,
            SIGNAL(recieved_credentials(const std::string&,
                                        const std::string&, int)),
            SLOT(establish_connection(  const std::string&,
                                        const std::string&, int)));

    login_dialog->setModal(true);
    login_dialog->show();
}

void MainWindow::action_disconnect_triggered()
{
    if (server == nullptr)
        return;

    server->destroy_connection();
    server = nullptr;
    if (worker != nullptr)
        worker->abort();
        worker = nullptr;

    ui->listWidget->clear();
    delete foo;
    roommate = "";

    QMessageBox::information(this, "", "Disconnected from server");
}


MainWindow::~MainWindow()
{
    if (worker != nullptr)
        worker->abort();
        worker = nullptr;

    delete server;
    delete ui;
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    roommate = item->text();
    qDebug() << "ClientSide: [ Now sending msgs to " << roommate << " ]";

    foo = new QAction(this);
    foo->setShortcut(Qt::CTRL | Qt::Key_F);
    connect(foo, SIGNAL(triggered()), this, SLOT(keyPressed()));
    this->addAction(foo);
}

void MainWindow::msg_from_user_received(QString user, QString msg)
{
    qDebug() << user << " : " << msg;
}
