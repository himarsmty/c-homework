#include "beginh/login.h"
#include "ui_login.h"

#include <QMessageBox>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QProgressBar>
#include <QPalette>
#include "extrah/extern.h"
#include "extrah/yrmssqlite.h"
#include "beginh/logup.h"
#include "sysh/systemcontroler.h"


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    accept();
    ui->setupUi(this);
    setFixedSize(700,500);//设置窗口尺寸
    setWindowFlag(Qt::WindowCloseButtonHint,false);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap("/home/mty/DDDCPP/YRMS/images/open.jpg")));
    this->setPalette(palette);
    ui->login->setDefault(true);
    ui->usrEditLine->setFocus();
    ui->title->setStyleSheet("color:#FFF;font-size:30px;");//设置标题字体
    ui->pwdEditLine->setEchoMode(QLineEdit::Password);//设置密码输入格式
    connect(ui->login,&QPushButton::clicked,this,&Login::logintomain);
}

Login::~Login()
{
    delete ui;
}
void Login::logintomain()
{
    QString dbName="usrinfo.db";
    if(connect_to_database(dbName))
    {
        QString t_data="select*from Users";
        QString input_number=ui->usrEditLine->text().trimmed();
        QString input_pwd=ui->pwdEditLine->text().trimmed();
        ui->usrEditLine->clear();
        ui->pwdEditLine->clear();
        ui->usrEditLine->setFocus();
        if(selectdata(t_data,input_number,input_pwd))
        {
            QSqlQuery query;
            query.exec(t_data);
            while(query.next())
            {
                if(input_number==query.value(1).toString()&&query.value(3).toString()=="系统管理员")
                {
                    syslogin=new Systemcontroler(NULL);
                    syslogin->exec();
                }
                else if(input_number==query.value(1).toString()&&query.value(3).toString()=="经理")
                {
                    Extern::managername=input_number;
                    managerlogin=new Managerwindow(this);
                    managerlogin->show();
                }
                else if(input_number==query.value(1).toString()&&query.value(3).toString()=="服务生")
                {
                    Extern::servername=input_number;
                    Extern::server_status=1;
                    serverlogin=new Serverwindow(this);
                    serverlogin->show();
                }
                else if(input_number==query.value(1).toString()&&query.value(3).toString()=="厨师")
                {
                    Extern::chefname=input_number;
                    cheflogin=new Chefwindow(this);
                    cheflogin->show();
                }
                else if(input_number==query.value(1).toString()&&query.value(3).toString()=="顾客")
                {
                    Extern::loginername=input_number;
                    Extern::allloginer.insert(input_number,0);
                    customer=new Customers(this);
                    customer->show();
                }
            }
        }
        else
        {
            QMessageBox::warning(this, tr("警告！"),
                                 tr("用户名或密码错误！"),
                                 QMessageBox::Retry);
            ui->usrEditLine->clear();
            ui->pwdEditLine->clear();
            ui->usrEditLine->setFocus();
        }
    }
}
void Login::on_logup_clicked()
{
    logupwindow=new Logup(NULL);
    logupwindow->exec();
}

void Login::on_exit_clicked()
{
    int db=QMessageBox::warning(this,tr("即将退出!!!"),tr("关闭登录界面将会导致整个程序关闭,确定继续执行?"),QMessageBox::Yes,QMessageBox::No);
    switch (db) {
    case QMessageBox::Yes:
        this->close();
        break;
    default:
        break;
    }
}
