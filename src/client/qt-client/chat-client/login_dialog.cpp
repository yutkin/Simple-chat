#include "login_dialog.hpp"
#include "ui_login_dialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    ui->nickname_edit->setAttribute(Qt::WA_MacShowFocusRect, false);
    ui->ip_edit->setAttribute(Qt::WA_MacShowFocusRect, false);
    ui->port_edit->setAttribute(Qt::WA_MacShowFocusRect, false);

    QString oIpRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp oIpRegex ("^" + oIpRange
                  + "\\." + oIpRange
                  + "\\." + oIpRange
                  + "\\." + oIpRange + "$");
    ui->ip_edit->setValidator(new QRegExpValidator(oIpRegex));

    ui->port_edit->setValidator(new QIntValidator(1,65535, this));
    connect(ui->login_btn, SIGNAL(clicked()), SLOT(login_btn_clicked()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::login_btn_clicked()
{
    auto nickname = ui->nickname_edit->text().toStdString();
    auto ip = ui->ip_edit->text().toStdString();
    auto port = ui->port_edit->text().toInt();

    emit recieved_credentials(nickname, ip, port);
    close();
}
