#include "usrh/desk.h"
#include "ui_desk.h"

#include <QMessageBox>
#include <QString>
#include <QSqlQuery>

#include "extrah/yrmssqlite.h"
#include "extrah/extern.h"
Desk::Desk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Desk)
{
    ui->setupUi(this);
    setFixedSize(667,214);
    setWindowFlag(Qt::WindowCloseButtonHint,false);
    setWindowFlag(Qt::WindowMinimizeButtonHint,true);
    setWindowFlag(Qt::WindowMaximizeButtonHint,false);
    QString dbName="dishes.db";
    if(connect_to_database(dbName))
    {
        QSqlQuery query;
        query.exec("select*from Deskinfo");
        while(query.next())//检查餐桌使用情况
        {
            if(query.value(1)==1)
            {
                int desknumber=query.value(0).toInt();
                qDebug()<<"the chosed desk is"<<desknumber;
                if(desknumber==1)
                {
                    ui->btn1->setEnabled(0);
                }
                else if(desknumber==2)
                {
                    ui->btn2->setEnabled(0);
                }
                else if(desknumber==3)
                {
                    ui->btn3->setEnabled(0);
                }
                else if(desknumber==4)
                {
                    ui->btn4->setEnabled(0);
                }
                else if(desknumber==5)
                {
                    ui->btn5->setEnabled(0);
                }
                else if(desknumber==6)
                {
                    ui->btn6->setEnabled(0);
                }
                else if(desknumber==7)
                {
                    ui->btn6->setEnabled(0);
                }
                else if(desknumber==8)
                {
                    ui->btn6->setEnabled(0);
                }
                else if(desknumber==9)
                {
                    ui->btn6->setEnabled(0);
                }
            }
        }
    }
}

Desk::~Desk()
{
    delete ui;
}

void Desk::on_btn1_clicked()
{
    ui->btn1->setEnabled(0);//更新显示餐桌信息
    QString dbName="dishes.db";
    if(connect_to_database(dbName))
    {
        QSqlQuery query;
        query.exec("update Deskinfo set States=1 where Id=1");//更新餐桌信息
    }
    QMessageBox::about(NULL,tr("欢迎光临"),tr("您已选座成功"));
    Extern::choisen=1;//临时与服务员交流餐桌信息
    QSqlQuery query;
    query.exec("CREATE TABLE '"+Extern::loginername+"'(name TEXT,singleprice TEXT,amount TEXT,fullprice TEXT,desknumber integer,status text);");
    query.exec("insert into '"+Extern::loginername+"'(desknumber) Values(1)");
    this->close();
}

void Desk::on_btn2_clicked()
{
    ui->btn2->setEnabled(0);
        Extern::cur_server_to_desk+=1;
    QString dbName="dishes.db";
    if(connect_to_database(dbName))
    {
        QSqlQuery query;
        query.exec("update Deskinfo set States=1 where Id=2");
    }
    QMessageBox::about(NULL,tr("欢迎光临"),tr("您已选座成功"));
    Extern::choisen=2;
    QSqlQuery query;
    query.exec("CREATE TABLE '"+Extern::loginername+"'(name TEXT,singleprice TEXT,amount TEXT,fullprice TEXT,desknumber integer,status text);");
    query.exec("insert into '"+Extern::loginername+"'(desknumber) Values(2)");
    this->close();
}

void Desk::on_btn3_clicked()
{
    ui->btn3->setEnabled(0);
    QString dbName="dishes.db";
    if(connect_to_database(dbName))
    {
        QSqlQuery query;
        query.exec("update Deskinfo set States=1 where Id=3");
    }
    QMessageBox::about(NULL,tr("欢迎光临"),tr("您已选座成功"));
    Extern::choisen=3;
    QSqlQuery query;
    query.exec("CREATE TABLE '"+Extern::loginername+"'(name TEXT,singleprice TEXT,amount TEXT,fullprice TEXT,desknumber integer,status text);");
    query.exec("insert into '"+Extern::loginername+"'(desknumber) Values(3)");
    this->close();
}

void Desk::on_btn4_clicked()
{
    ui->btn4->setEnabled(0);
    QString dbName="dishes.db";
    if(connect_to_database(dbName))
    {
        QSqlQuery query;
        query.exec("update Deskinfo set States=1 where Id=4");
    }
    QMessageBox::about(NULL,tr("欢迎光临"),tr("您已选座成功"));
    Extern::choisen=4;
    QSqlQuery query;
    query.exec("CREATE TABLE '"+Extern::loginername+"'(name TEXT,singleprice TEXT,amount TEXT,fullprice TEXT,desknumber integer,status text);");
    query.exec("insert into '"+Extern::loginername+"'(desknumber) Values(4)");
    this->close();
}

void Desk::on_btn5_clicked()
{
    ui->btn5->setEnabled(0);
    QString dbName="dishes.db";
    if(connect_to_database(dbName))
    {
        QSqlQuery query;
        query.exec("update Deskinfo set States=1 where Id=5");
    }
    QMessageBox::about(NULL,tr("欢迎光临"),tr("您已选座成功"));
    Extern::choisen=5;
    QSqlQuery query;
    query.exec("CREATE TABLE '"+Extern::loginername+"'(name TEXT,singleprice TEXT,amount TEXT,fullprice TEXT,desknumber integer,status text);");
    query.exec("insert into '"+Extern::loginername+"'(desknumber) Values(5)");
    this->close();
}

void Desk::on_btn6_clicked()
{
    ui->btn6->setEnabled(0);
    QString dbName="dishes.db";
    if(connect_to_database(dbName))
    {
        QSqlQuery query;
        query.exec("update Deskinfo set States=1 where Id=6");
    }
    QMessageBox::about(NULL,tr("欢迎光临"),tr("您已选座成功"));
    Extern::choisen=6;
    QSqlQuery query;
    query.exec("CREATE TABLE '"+Extern::loginername+"'(name TEXT,singleprice TEXT,amount TEXT,fullprice TEXT,desknumber integer,status text);");
    query.exec("insert into '"+Extern::loginername+"'(desknumber) Values(6)");
    this->close();
}

void Desk::on_btn7_clicked()
{
    ui->btn7->setEnabled(0);
    QString dbName="dishes.db";
    if(connect_to_database(dbName))
    {
        QSqlQuery query;
        query.exec("update Deskinfo set States=1 where Id=7");
    }
    QMessageBox::about(NULL,tr("欢迎光临"),tr("您已选座成功"));
    Extern::choisen=7;
    QSqlQuery query;
    query.exec("CREATE TABLE '"+Extern::loginername+"'(name TEXT,singleprice TEXT,amount TEXT,fullprice TEXT,desknumber integer,status text);");
    query.exec("insert into '"+Extern::loginername+"'(desknumber) Values(7)");
    this->close();
}

void Desk::on_btn8_clicked()
{
    ui->btn8->setEnabled(0);
    QString dbName="dishes.db";
    if(connect_to_database(dbName))
    {
        QSqlQuery query;
        query.exec("update Deskinfo set States=1 where Id=8");
    }
    QMessageBox::about(NULL,tr("欢迎光临"),tr("您已选座成功"));
    Extern::choisen=8;
    QSqlQuery query;
    query.exec("CREATE TABLE '"+Extern::loginername+"'(name TEXT,singleprice TEXT,amount TEXT,fullprice TEXT,desknumber integer,status text);");
    query.exec("insert into '"+Extern::loginername+"'(desknumber) Values(8)");
    this->close();
}

void Desk::on_btn9_clicked()
{
    ui->btn9->setEnabled(0);
    QString dbName="dishes.db";
    if(connect_to_database(dbName))
    {
        QSqlQuery query;
        query.exec("update Deskinfo set States=1 where Id=9");
    }
    QMessageBox::about(NULL,tr("欢迎光临"),tr("您已选座成功"));
    Extern::choisen=9;
    QSqlQuery query;
    query.exec("CREATE TABLE '"+Extern::loginername+"'(name TEXT,singleprice TEXT,amount TEXT,fullprice TEXT,desknumber integer,status text);");
    query.exec("insert into '"+Extern::loginername+"'(desknumber) Values(9)");
    this->close();
}

void Desk::on_commandLinkButton_clicked()
{
          this->close();
}
