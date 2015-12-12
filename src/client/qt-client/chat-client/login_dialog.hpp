#ifndef LOGIN_DIALOG_HPP
#define LOGIN_DIALOG_HPP

#include <QDialog>

namespace Ui
{
    class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

signals:
    void recieved_credentials(const std::string&,
                              const std::string&, int);

private slots:
    void login_btn_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGIN_DIALOG_HPP
