#include "beginh/logup.h"
#include "ui_logup.h"
#include "extrah/yrmssqlite.h"

#include <QLineEdit>
#include <QMessageBox>
#include <QPalette>
#include <QString>

Logup::Logup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logup)
{
    ui->setupUi(this);
    setFixedSize(700,500);//设置最大窗口尺寸
    ui->codelineEdit->setEchoMode(QLineEdit::Password);
    ui->phnumLineEdit->setFocus();
    connect(ui->returbtn,&QPushButton::clicked,this,&Logup::close);
    connect(ui->logupbtn,&QPushButton::clicked,this,&Logup::logup);
}

Logup::~Logup()
{
    delete ui;
}
void Logup::logup()
{
    QString dbName="usrinfo.db";
    if(ui->phnumLineEdit->text().trimmed().size()!=11)//判断手机号格式是否正确
    {
        QMessageBox::warning(this,tr("警告！"),tr("请输入11位正确手机号！"),QMessageBox::Yes);
        ui->phnumLineEdit->clear();
        ui->codelineEdit->clear();
        ui->phnumLineEdit->setFocus();
    }
    else
    {
        if(connect_to_database(dbName))//连接成功数据库
        {
            QString add_pnumber=ui->phnumLineEdit->text().trimmed();
            QString add_pwdnumber=ui->codelineEdit->text().trimmed();
            QString add_selectdata="select*from Users";
            if(ADD_usrdata(add_selectdata,add_pnumber,add_pwdnumber))
            {
                QMessageBox::about(this,"欢迎","您已注册成功");
                this->close();
            }
            else
            {
                QMessageBox::about(NULL,tr("注册失败"),tr("用户已存在"));
                ui->phnumLineEdit->clear();
                ui->codelineEdit->clear();
                ui->phnumLineEdit->setFocus();
            }
        }
    }
}
