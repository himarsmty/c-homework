#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QDebug>
#include <QTimer>

#include "sysh/systemcontroler.h"
#include "serverh/serverwindow.h"
#include "chefh/chefwindow.h"
#include "managerh/managerwindow.h"
#include "beginh/logup.h"
#include "usrh/customers.h"
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private:
    Ui::Login *ui;
    Systemcontroler *syslogin;
    Chefwindow *cheflogin;
    Managerwindow *managerlogin;
    Serverwindow *serverlogin;
    Logup *logupwindow;
    Customers *customer;
    static int progress_value;
private slots:
    void logintomain();
    void on_logup_clicked();
    void on_exit_clicked();
};

#endif // LOGIN_H
