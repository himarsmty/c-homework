#include "managerh/managerwindow.h"
#include "ui_managerwindow.h"

#include "managerh/checkchef.h"
#include "managerh/checkserver.h"
#include "extrah/extern.h"
#include "managerh/stuffnamelist.h"
#include "managerh/serverlist.h"

#include <QMessageBox>
Managerwindow::Managerwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Managerwindow)
{
    ui->setupUi(this);
    QString s="YRMS[经理模式] "+Extern::managername+"已登录";
    setWindowTitle(s);
    setFixedSize(500,470);//设置固定窗口尺寸
    setWindowFlag(Qt::WindowCloseButtonHint,false);
    setWindowFlag(Qt::WindowMaximizeButtonHint,false);
}

Managerwindow::~Managerwindow()
{
    delete ui;
}

void Managerwindow::on_chefbtn_clicked()
{
    Stuffnamelist *chef=new Stuffnamelist(this);
    chef->exec();
}

void Managerwindow::on_serverptn_clicked()
{
    Serverlist *slist=new Serverlist(this);
    slist->exec();
}

void Managerwindow::on_pushButton_3_clicked()
{
    int db=QMessageBox::warning(this,tr("即将退出"),tr("您确定要退出吗"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    switch (db) {
    case QMessageBox::Yes:
        this->close();
        break;
    default:
        break;
    }
}
